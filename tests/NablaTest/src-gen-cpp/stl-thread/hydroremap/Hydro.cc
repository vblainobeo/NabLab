/* DO NOT EDIT THIS FILE - it is machine generated */

#include "Hydro.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "R1.h"
#include "R2.h"


/******************** Module definition ********************/

Hydro::Hydro(CartesianMesh2D& aMesh)
: mesh(aMesh)
, nbNodes(mesh.getNbNodes())
, nbCells(mesh.getNbCells())
, X(nbNodes)
, hv1(nbCells)
, hv2(nbCells)
, hv3(nbCells)
, hv4(nbCells)
, hv5(nbCells)
, hv6(nbCells)
, hv7(nbCells)
{
	// Copy node coordinates
	const auto& gNodes = mesh.getGeometry()->getNodes();
	for (size_t rNodes=0; rNodes<nbNodes; rNodes++)
	{
		X[rNodes][0] = gNodes[rNodes][0];
		X[rNodes][1] = gNodes[rNodes][1];
	}
}

Hydro::~Hydro()
{
}

void
Hydro::jsonInit(const char* jsonContent)
{
	rapidjson::Document document;
	assert(!document.Parse(jsonContent).HasParseError());
	assert(document.IsObject());
	const rapidjson::Value::Object& o = document.GetObject();

	// maxTime
	if (o.HasMember("maxTime"))
	{
		const rapidjson::Value& valueof_maxTime = o["maxTime"];
		assert(valueof_maxTime.IsDouble());
		maxTime = valueof_maxTime.GetDouble();
	}
	else
		maxTime = 0.1;
	// maxIter
	if (o.HasMember("maxIter"))
	{
		const rapidjson::Value& valueof_maxIter = o["maxIter"];
		assert(valueof_maxIter.IsInt());
		maxIter = valueof_maxIter.GetInt();
	}
	else
		maxIter = 500;
	// deltat
	if (o.HasMember("deltat"))
	{
		const rapidjson::Value& valueof_deltat = o["deltat"];
		assert(valueof_deltat.IsDouble());
		deltat = valueof_deltat.GetDouble();
	}
	else
		deltat = 1.0;
	// Non regression
	assert(o.HasMember("nonRegression"));
	const rapidjson::Value& valueof_nonRegression = o["nonRegression"];
	assert(valueof_nonRegression.IsString());
	nonRegression = valueof_nonRegression.GetString();
}


/**
 * Job hj1 called @1.0 in simulate method.
 * In variables: hv2
 * Out variables: hv3
 */
void Hydro::hj1() noexcept
{
	parallel_exec(nbCells, [&](const size_t& cCells)
	{
		hv3[cCells] = hv2[cCells];
	});
}

/**
 * Job hj2 called @2.0 in simulate method.
 * In variables: hv3
 * Out variables: hv5
 */
void Hydro::hj2() noexcept
{
	parallel_exec(nbCells, [&](const size_t& cCells)
	{
		hv5[cCells] = hv3[cCells];
	});
}

/**
 * Job hj3 called @4.0 in simulate method.
 * In variables: hv4, hv5, hv6
 * Out variables: hv7
 */
void Hydro::hj3() noexcept
{
	parallel_exec(nbCells, [&](const size_t& cCells)
	{
		hv7[cCells] = hv4[cCells] + hv5[cCells] + hv6[cCells];
	});
}

void Hydro::simulate()
{
	std::cout << "\n" << __BLUE_BKG__ << __YELLOW__ << __BOLD__ <<"\tStarting HydroRemap ..." << __RESET__ << "\n\n";
	
	std::cout << "[" << __GREEN__ << "TOPOLOGY" << __RESET__ << "]  HWLOC unavailable cannot get topological informations" << std::endl;
	
	std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    " << __BOLD__ << "Disabled" << __RESET__ << std::endl;

	hj1(); // @1.0
	r1->rj1(); // @1.0
	hj2(); // @2.0
	r2->rj1(); // @2.0
	r1->rj2(); // @2.0
	r2->rj2(); // @3.0
	hj3(); // @4.0
	
	std::cout << "\nFinal time = " << t << endl;
	std::cout << __YELLOW__ << "\n\tDone ! Took " << __MAGENTA__ << __BOLD__ << globalTimer.print() << __RESET__ << std::endl;
}

void Hydro::createDB(const std::string& db_name)
{
	leveldb::DB* db;
	leveldb::Options options;

	// Destroy if exists
	leveldb::DestroyDB(db_name, options);

	// Create data base
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, db_name, &db);
	assert(status.ok());
	// Batch to write all data at once
	leveldb::WriteBatch batch;
	batch.Put("hydro::t", serialize(t));
	batch.Put("hydro::X", serialize(X));
	batch.Put("hydro::hv1", serialize(hv1));
	batch.Put("hydro::hv2", serialize(hv2));
	batch.Put("hydro::hv3", serialize(hv3));
	batch.Put("hydro::hv4", serialize(hv4));
	batch.Put("hydro::hv5", serialize(hv5));
	batch.Put("hydro::hv6", serialize(hv6));
	batch.Put("hydro::hv7", serialize(hv7));
	batch.Put("r1::rv3", serialize(r1->rv3));
	batch.Put("r2::rv2", serialize(r2->rv2));
	status = db->Write(leveldb::WriteOptions(), &batch);
	// Checking everything was ok
	assert(status.ok());
	std::cerr << "Reference database " << db_name << " created." << std::endl;
	// Freeing memory
	delete db;
}

/******************** Non regression testing ********************/

bool compareDB(const std::string& current, const std::string& ref)
{
	// Final result
	bool result = true;

	// Loading ref DB
	leveldb::DB* db_ref;
	leveldb::Options options_ref;
	options_ref.create_if_missing = false;
	leveldb::Status status = leveldb::DB::Open(options_ref, ref, &db_ref);
	if (!status.ok())
	{
		std::cerr << "No ref database to compare with ! Looking for " << ref << std::endl;
		return false;
	}
	leveldb::Iterator* it_ref = db_ref->NewIterator(leveldb::ReadOptions());

	// Loading current DB
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = false;
	status = leveldb::DB::Open(options, current, &db);
	assert(status.ok());
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());

	// Results comparison
	std::cerr << "# Comparing results ..." << std::endl;
	for (it_ref->SeekToFirst(); it_ref->Valid(); it_ref->Next()) {
		auto key = it_ref->key();
		std::string value;
		auto status = db->Get(leveldb::ReadOptions(), key, &value);
		if (status.IsNotFound()) {
			std::cerr << "ERROR - Key : " << key.ToString() << " not found." << endl;
			result = false;
		}
		else {
			if (value == it_ref->value().ToString())
				std::cerr << key.ToString() << ": " << "OK" << std::endl;
			else {
				std::cerr << key.ToString() << ": " << "ERROR" << std::endl;
				result = false;
			}
		}
	}

	// looking for key in the db that are not in the ref (new variables)
	for (it->SeekToFirst(); it->Valid(); it->Next()) {
		auto key = it->key();
		std::string value;
		if (db_ref->Get(leveldb::ReadOptions(), key, &value).IsNotFound()) {
			std::cerr << "ERROR - Key : " << key.ToString() << " can not be compared (not present in the ref)." << std::endl;
			result = false;
		}
	}

	// Freeing memory
	delete db;
	delete db_ref;

	return result;
}

int main(int argc, char* argv[]) 
{
	string dataFile;
	int ret = 0;
	
	if (argc == 2)
	{
		dataFile = argv[1];
	}
	else
	{
		std::cerr << "[ERROR] Wrong number of arguments. Expecting 1 arg: dataFile." << std::endl;
		std::cerr << "(HydroRemap.json)" << std::endl;
		return -1;
	}
	
	// read json dataFile
	ifstream ifs(dataFile);
	rapidjson::IStreamWrapper isw(ifs);
	rapidjson::Document d;
	d.ParseStream(isw);
	assert(d.IsObject());
	
	// Mesh instanciation
	CartesianMesh2D mesh;
	assert(d.HasMember("mesh"));
	rapidjson::StringBuffer strbuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
	d["mesh"].Accept(writer);
	mesh.jsonInit(strbuf.GetString());
	
	// Module instanciation(s)
	Hydro* hydro = new Hydro(mesh);
	if (d.HasMember("hydro"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["hydro"].Accept(writer);
		hydro->jsonInit(strbuf.GetString());
	}
	R1* r1 = new R1(mesh);
	if (d.HasMember("r1"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["r1"].Accept(writer);
		r1->jsonInit(strbuf.GetString());
	}
	r1->setMainModule(hydro);
	R2* r2 = new R2(mesh);
	if (d.HasMember("r2"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["r2"].Accept(writer);
		r2->jsonInit(strbuf.GetString());
	}
	r2->setMainModule(hydro);
	
	// Start simulation
	// Simulator must be a pointer when a finalize is needed at the end (Kokkos, omp...)
	hydro->simulate();
	
	// Non regression testing
	if (hydro->getNonRegression() == "CreateReference")
		hydro->createDB("HydroRemapDB.ref");
	if (hydro->getNonRegression() == "CompareToReference") {
		hydro->createDB("HydroRemapDB.current");
		if (!compareDB("HydroRemapDB.current", "HydroRemapDB.ref"))
			ret = 1;
		leveldb::DestroyDB("HydroRemapDB.current", leveldb::Options());
	}
	
	delete r2;
	delete r1;
	delete hydro;
	return ret;
}
