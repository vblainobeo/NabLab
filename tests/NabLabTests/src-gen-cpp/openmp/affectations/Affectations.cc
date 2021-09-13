/* DO NOT EDIT THIS FILE - it is machine generated */

#include "Affectations.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


/******************** Module definition ********************/

Affectations::Affectations(CartesianMesh2D& aMesh)
: mesh(aMesh)
, nbNodes(mesh.getNbNodes())
, nbCells(mesh.getNbCells())
, X(nbNodes)
, e1(nbCells)
, e2_n(nbCells)
, e2_nplus1(nbCells)
, e2_nplus1_k(nbCells)
, e2_nplus1_kplus1(nbCells)
, e2_nplus1_k0(nbCells)
, e_n(nbCells)
, e_nplus1(nbCells)
, e_n0(nbCells)
{
	// Copy node coordinates
	const auto& gNodes = mesh.getGeometry()->getNodes();
	for (size_t rNodes=0; rNodes<nbNodes; rNodes++)
	{
		X[rNodes][0] = gNodes[rNodes][0];
		X[rNodes][1] = gNodes[rNodes][1];
	}
}

Affectations::~Affectations()
{
}

void
Affectations::jsonInit(const char* jsonContent)
{
	rapidjson::Document document;
	assert(!document.Parse(jsonContent).HasParseError());
	assert(document.IsObject());
	const rapidjson::Value::Object& o = document.GetObject();

}


/**
 * Job computeE1 called @1.0 in executeTimeLoopN method.
 * In variables: e_n
 * Out variables: e1
 */
void Affectations::computeE1() noexcept
{
	#pragma omp parallel for shared(e1)
	for (size_t cCells=0; cCells<nbCells; cCells++)
	{
		e1[cCells] = e_n[cCells] + 3.0;
	}
}

/**
 * Job computeE2 called @1.0 in executeTimeLoopK method.
 * In variables: e2_nplus1_k
 * Out variables: e2_nplus1_kplus1
 */
void Affectations::computeE2() noexcept
{
	#pragma omp parallel for shared(e2_nplus1_kplus1)
	for (size_t cCells=0; cCells<nbCells; cCells++)
	{
		e2_nplus1_kplus1[cCells] = e2_nplus1_k[cCells] + 0.4;
	}
}

/**
 * Job initE called @1.0 in simulate method.
 * In variables: 
 * Out variables: e_n0
 */
void Affectations::initE() noexcept
{
	#pragma omp parallel for shared(e_n0)
	for (size_t cCells=0; cCells<nbCells; cCells++)
	{
		e_n0[cCells] = {0.0, 0.0};
	}
}

/**
 * Job initTandU called @1.0 in simulate method.
 * In variables: 
 * Out variables: t_n0, u_n0
 */
void Affectations::initTandU() noexcept
{
	t_n0 = 0.0;
	u_n0 = {0.0, 0.0};
}

/**
 * Job updateT called @1.0 in executeTimeLoopN method.
 * In variables: deltat, t_n
 * Out variables: t_nplus1
 */
void Affectations::updateT() noexcept
{
	t_nplus1 = t_n + deltat;
}

/**
 * Job updateU called @1.0 in executeTimeLoopN method.
 * In variables: u_n
 * Out variables: u_nplus1
 */
void Affectations::updateU() noexcept
{
	u_nplus1 = u_n * 2;
}

/**
 * Job initE2 called @2.0 in executeTimeLoopN method.
 * In variables: e1
 * Out variables: e2_nplus1_k0
 */
void Affectations::initE2() noexcept
{
	#pragma omp parallel for shared(e2_nplus1_k0)
	for (size_t cCells=0; cCells<nbCells; cCells++)
	{
		for (size_t i1=0; i1<2; i1++)
		{
			e2_nplus1_k0[cCells][i1] = e1[cCells][i1];
		}
	}
}

/**
 * Job setUpTimeLoopN called @2.0 in simulate method.
 * In variables: e_n0, t_n0, u_n0
 * Out variables: e_n, t_n, u_n
 */
void Affectations::setUpTimeLoopN() noexcept
{
	t_n = t_n0;
	for (size_t i1=0; i1<2; i1++)
	{
		u_n[i1] = u_n0[i1];
	}
	#pragma omp parallel for shared(e_n)
	for (size_t i1Cells=0; i1Cells<nbCells; i1Cells++)
	{
		for (size_t i1=0; i1<2; i1++)
		{
			e_n[i1Cells][i1] = e_n0[i1Cells][i1];
		}
	}
}

/**
 * Job executeTimeLoopN called @3.0 in simulate method.
 * In variables: e2_n, e_n, t_n, u_n
 * Out variables: e2_nplus1, e_nplus1, t_nplus1, u_nplus1
 */
void Affectations::executeTimeLoopN() noexcept
{
	n = 0;
	bool continueLoop = true;
	do
	{
		globalTimer.start();
		cpuTimer.start();
		n++;
		if (n!=1)
			std::cout << "[" << __CYAN__ << __BOLD__ << setw(3) << n << __RESET__ "] t = " << __BOLD__
				<< setiosflags(std::ios::scientific) << setprecision(8) << setw(16) << t_n << __RESET__;
	
		computeE1(); // @1.0
		updateT(); // @1.0
		updateU(); // @1.0
		initE2(); // @2.0
		setUpTimeLoopK(); // @3.0
		executeTimeLoopK(); // @4.0
		tearDownTimeLoopK(); // @5.0
		updateE(); // @6.0
		
	
		// Evaluate loop condition with variables at time n
		continueLoop = (n + 1 < maxIter && t_nplus1 < maxTime);
	
		t_n = t_nplus1;
		for (size_t i1=0; i1<2; i1++)
		{
			u_n[i1] = u_nplus1[i1];
		}
		#pragma omp parallel for shared(e2_n)
		for (size_t i1Cells=0; i1Cells<nbCells; i1Cells++)
		{
			for (size_t i1=0; i1<2; i1++)
			{
				e2_n[i1Cells][i1] = e2_nplus1[i1Cells][i1];
			}
		}
		#pragma omp parallel for shared(e_n)
		for (size_t i1Cells=0; i1Cells<nbCells; i1Cells++)
		{
			for (size_t i1=0; i1<2; i1++)
			{
				e_n[i1Cells][i1] = e_nplus1[i1Cells][i1];
			}
		}
	
		cpuTimer.stop();
		globalTimer.stop();
	
		// Timers display
			std::cout << " {CPU: " << __BLUE__ << cpuTimer.print(true) << __RESET__ ", IO: " << __RED__ << "none" << __RESET__ << "} ";
		
		// Progress
		std::cout << progress_bar(n, maxIter, t_n, maxTime, 25);
		std::cout << __BOLD__ << __CYAN__ << Timer::print(
			eta(n, maxIter, t_n, maxTime, deltat, globalTimer), true)
			<< __RESET__ << "\r";
		std::cout.flush();
	
		cpuTimer.reset();
		ioTimer.reset();
	} while (continueLoop);
}

/**
 * Job setUpTimeLoopK called @3.0 in executeTimeLoopN method.
 * In variables: e2_nplus1_k0
 * Out variables: e2_nplus1_k
 */
void Affectations::setUpTimeLoopK() noexcept
{
	#pragma omp parallel for shared(e2_nplus1_k)
	for (size_t i1Cells=0; i1Cells<nbCells; i1Cells++)
	{
		for (size_t i1=0; i1<2; i1++)
		{
			e2_nplus1_k[i1Cells][i1] = e2_nplus1_k0[i1Cells][i1];
		}
	}
}

/**
 * Job executeTimeLoopK called @4.0 in executeTimeLoopN method.
 * In variables: e2_nplus1_k
 * Out variables: e2_nplus1_kplus1
 */
void Affectations::executeTimeLoopK() noexcept
{
	k = 0;
	bool continueLoop = true;
	do
	{
		k++;
		computeE2(); // @1.0
		
	
		// Evaluate loop condition with variables at time n
		continueLoop = (k + 1 < 10);
	
		#pragma omp parallel for shared(e2_nplus1_k)
		for (size_t i1Cells=0; i1Cells<nbCells; i1Cells++)
		{
			for (size_t i1=0; i1<2; i1++)
			{
				e2_nplus1_k[i1Cells][i1] = e2_nplus1_kplus1[i1Cells][i1];
			}
		}
	} while (continueLoop);
}

/**
 * Job tearDownTimeLoopK called @5.0 in executeTimeLoopN method.
 * In variables: e2_nplus1_kplus1
 * Out variables: e2_nplus1
 */
void Affectations::tearDownTimeLoopK() noexcept
{
	#pragma omp parallel for shared(e2_nplus1)
	for (size_t i1Cells=0; i1Cells<nbCells; i1Cells++)
	{
		for (size_t i1=0; i1<2; i1++)
		{
			e2_nplus1[i1Cells][i1] = e2_nplus1_kplus1[i1Cells][i1];
		}
	}
}

/**
 * Job updateE called @6.0 in executeTimeLoopN method.
 * In variables: e2_nplus1
 * Out variables: e_nplus1
 */
void Affectations::updateE() noexcept
{
	#pragma omp parallel for shared(e_nplus1)
	for (size_t cCells=0; cCells<nbCells; cCells++)
	{
		e_nplus1[cCells] = e2_nplus1[cCells] - 3;
	}
}

void Affectations::simulate()
{
	std::cout << "\n" << __BLUE_BKG__ << __YELLOW__ << __BOLD__ <<"\tStarting Affectations ..." << __RESET__ << "\n\n";
	
	std::cout << "[" << __GREEN__ << "TOPOLOGY" << __RESET__ << "]  HWLOC unavailable cannot get topological informations" << std::endl;
	
	std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    " << __BOLD__ << "Disabled" << __RESET__ << std::endl;

	initE(); // @1.0
	initTandU(); // @1.0
	setUpTimeLoopN(); // @2.0
	executeTimeLoopN(); // @3.0
	
	std::cout << "\nFinal time = " << t_n << endl;
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
		std::cerr << "(Affectations.json)" << std::endl;
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
	Affectations* affectations = new Affectations(mesh);
	if (d.HasMember("affectations"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["affectations"].Accept(writer);
		affectations->jsonInit(strbuf.GetString());
	}
	
	// Start simulation
	// Simulator must be a pointer when a finalize is needed at the end (Kokkos, omp...)
	affectations->simulate();
	
	delete affectations;
	return ret;
}
