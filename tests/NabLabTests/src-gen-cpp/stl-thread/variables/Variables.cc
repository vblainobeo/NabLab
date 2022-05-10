/* DO NOT EDIT THIS FILE - it is machine generated */

#include "Variables.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


/******************** Free functions definitions ********************/

namespace variablesfreefuncs
{
bool assertEquals(int expected, int actual)
{
	const bool ret((expected == actual));
	if (!ret) 
		throw std::runtime_error("** Assertion failed");
	return ret;
}

template<size_t x>
bool assertEquals(RealArray1D<x> expected, RealArray1D<x> actual)
{
	parallel_exec(x, [&](const size_t& i)
	{
		if (expected[i] != actual[i]) 
			throw std::runtime_error("** Assertion failed");
	});
	return true;
}

bool assertEquals(double expected, double actual)
{
	const bool ret((expected == actual));
	if (!ret) 
		throw std::runtime_error("** Assertion failed");
	return ret;
}

template<size_t x0>
RealArray1D<x0> operatorAdd(RealArray1D<x0> a, RealArray1D<x0> b)
{
	RealArray1D<x0> result;
	parallel_exec(x0, [&](const size_t& ix0)
	{
		result[ix0] = a[ix0] + b[ix0];
	});
	return result;
}
}

/******************** Module definition ********************/

Variables::Variables(CartesianMesh2D& aMesh)
: mesh(aMesh)
, nbNodes(mesh.getNbNodes())
, X(nbNodes)
{
}

Variables::~Variables()
{
}

void
Variables::jsonInit(const char* jsonContent)
{
	rapidjson::Document document;
	assert(!document.Parse(jsonContent).HasParseError());
	assert(document.IsObject());
	const rapidjson::Value::Object& options = document.GetObject();

	assert(options.HasMember("optDim"));
	const rapidjson::Value& valueof_optDim = options["optDim"];
	assert(valueof_optDim.IsInt());
	optDim = valueof_optDim.GetInt();
	assert(options.HasMember("optVect1"));
	const rapidjson::Value& valueof_optVect1 = options["optVect1"];
	assert(valueof_optVect1.IsArray());
	assert(valueof_optVect1.Size() == 2);
	for (size_t i1=0 ; i1<2 ; i1++)
	{
		assert(valueof_optVect1[i1].IsDouble());
		optVect1[i1] = valueof_optVect1[i1].GetDouble();
	}
	assert(options.HasMember("optVect2"));
	const rapidjson::Value& valueof_optVect2 = options["optVect2"];
	assert(valueof_optVect2.IsArray());
	assert(valueof_optVect2.Size() == 2);
	for (size_t i1=0 ; i1<2 ; i1++)
	{
		assert(valueof_optVect2[i1].IsDouble());
		optVect2[i1] = valueof_optVect2[i1].GetDouble();
	}
	optVect3 = variablesfreefuncs::operatorAdd(optVect1, optVect2);
	varVec = {1.0, 1.0};
	dynamicVec.initSize(optDim);

	// Copy node coordinates
	const auto& gNodes = mesh.getGeometry()->getNodes();
	for (size_t rNodes=0; rNodes<nbNodes; rNodes++)
	{
		X[rNodes][0] = gNodes[rNodes][0];
		X[rNodes][1] = gNodes[rNodes][1];
	}
}

/**
 * Job dynamicVecInitialization called @1.0 in simulate method.
 * In variables: optDim
 * Out variables: checkDynamicDim, dynamicVec
 */
void Variables::dynamicVecInitialization() noexcept
{
	int cpt(0);
	parallel_exec(optDim, [&](const size_t& i)
	{
		dynamicVec[i] = 3.3;
	});
	for (size_t i=0; i<optDim; i++)
	{
		cpt = cpt + 1;
	}
	checkDynamicDim = cpt;
}

/**
 * Job varVecInitialization called @1.0 in simulate method.
 * In variables: constexprDim
 * Out variables: varVec
 */
void Variables::varVecInitialization() noexcept
{
	varVec = {2.2, 2.2};
}

/**
 * Job oracle called @2.0 in simulate method.
 * In variables: checkDynamicDim, constexprDim, constexprVec, dynamicVec, optDim, optVect1, optVect2, optVect3, varVec
 * Out variables: 
 */
void Variables::oracle() noexcept
{
	const bool testOptDim(variablesfreefuncs::assertEquals(2, optDim));
	const bool testOptVect1(variablesfreefuncs::assertEquals({1.0, 1.0}, optVect1));
	const bool testOptVect2(variablesfreefuncs::assertEquals({2.0, 2.0}, optVect2));
	const bool testOptVect3(variablesfreefuncs::assertEquals({3.0, 3.0}, optVect3));
	const bool testConstexprDim(variablesfreefuncs::assertEquals(2, constexprDim));
	const bool testConstexprVec(variablesfreefuncs::assertEquals({1.1, 1.1}, constexprVec));
	const bool testVarVec(variablesfreefuncs::assertEquals({2.2, 2.2}, varVec));
	const bool testDynamicVecLength(variablesfreefuncs::assertEquals(2, checkDynamicDim));
	parallel_exec(optDim, [&](const size_t& i)
	{
		const bool testDynamicVec(variablesfreefuncs::assertEquals(3.3, dynamicVec[i]));
	});
}

void Variables::simulate()
{
	std::cout << "\n" << __BLUE_BKG__ << __YELLOW__ << __BOLD__ <<"\tStarting Variables ..." << __RESET__ << "\n\n";
	
	std::cout << "[" << __GREEN__ << "TOPOLOGY" << __RESET__ << "]  HWLOC unavailable cannot get topological informations" << std::endl;
	
	std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    " << __BOLD__ << "Disabled" << __RESET__ << std::endl;

	dynamicVecInitialization(); // @1.0
	varVecInitialization(); // @1.0
	oracle(); // @2.0
	
	std::cout << "\nFinal time = " << t << endl;
	std::cout << __YELLOW__ << "\n\tDone ! Took " << __MAGENTA__ << __BOLD__ << globalTimer.print() << __RESET__ << std::endl;
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
		std::cerr << "(Variables.json)" << std::endl;
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
	Variables* variables = new Variables(mesh);
	assert(d.HasMember("variables"));
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["variables"].Accept(writer);
		variables->jsonInit(strbuf.GetString());
	}
	
	// Start simulation
	// Simulator must be a pointer when a finalize is needed at the end (Kokkos, omp...)
	variables->simulate();
	
	delete variables;
	return ret;
}
