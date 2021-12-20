/* DO NOT EDIT THIS FILE - it is machine generated */

#include "Reduction.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


/******************** Free functions definitions ********************/

namespace reductionfreefuncs
{
RealArray1D<2> nodeVelocityBoundaryConditionCorner(int BC1, RealArray1D<2> BCValue1, int BC2, RealArray1D<2> BCValue2, RealArray2D<2,2> Mp, RealArray1D<2> Gp, RealArray1D<2> lp_np)
{
	return {0.0, 0.0};
}

template<size_t x>
RealArray1D<x> sumR1(RealArray1D<x> a, RealArray1D<x> b)
{
	return reductionfreefuncs::operator+(a, b);
}

template<size_t x0>
RealArray1D<x0> operator+(RealArray1D<x0> a, RealArray1D<x0> b)
{
	RealArray1D<x0> result;
	for (size_t ix0=0; ix0<x0; ix0++)
	{
		result[ix0] = a[ix0] + b[ix0];
	}
	return result;
}
}

/******************** Module definition ********************/

Reduction::Reduction(CartesianMesh2D& aMesh)
: mesh(aMesh)
, nbNodes(mesh.getNbNodes())
, maxCellsOfNode(CartesianMesh2D::MaxNbCellsOfNode)
, nbCells(mesh.getNbCells())
, maxNodesOfCell(CartesianMesh2D::MaxNbNodesOfCell)
, X(nbNodes)
, Vnode_n(nbNodes)
, Vnode_nplus1(nbNodes)
, lpc_n(nbNodes, std::vector<RealArray1D<2>>(maxCellsOfNode))
{
}

Reduction::~Reduction()
{
}

void
Reduction::jsonInit(const char* jsonContent)
{
	rapidjson::Document document;
	assert(!document.Parse(jsonContent).HasParseError());
	assert(document.IsObject());
	const rapidjson::Value::Object& options = document.GetObject();

	n = 0;

	// Copy node coordinates
	const auto& gNodes = mesh.getGeometry()->getNodes();
	for (size_t rNodes=0; rNodes<nbNodes; rNodes++)
	{
		X[rNodes][0] = gNodes[rNodes][0];
		X[rNodes][1] = gNodes[rNodes][1];
	}
}


/**
 * Job computeGeometry called @1.0 in simulate method.
 * In variables: 
 * Out variables: lpc_n
 */
void Reduction::computeGeometry() noexcept
{
	parallel_exec(nbCells, [&](const size_t& cCells)
	{
		const Id cId(cCells);
		{
			const auto nodesOfCellC(mesh.getNodesOfCell(cId));
			const size_t nbNodesOfCellC(nodesOfCellC.size());
			for (size_t pNodesOfCellC=0; pNodesOfCellC<nbNodesOfCellC; pNodesOfCellC++)
			{
				const Id pId(nodesOfCellC[pNodesOfCellC]);
				const size_t pNodes(pId);
				const size_t cCellsOfNodeP(indexOf(mesh.getCellsOfNode(pId), cId));
				lpc_n[pNodes][cCellsOfNodeP] = {1.0, 1.0};
			}
		}
	});
}

/**
 * Job executeTimeLoopN called @1.0 in simulate method.
 * In variables: Vnode_n, n, t_n
 * Out variables: Vnode_nplus1, t_nplus1
 */
void Reduction::executeTimeLoopN() noexcept
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
	
		
	
		// Evaluate loop condition with variables at time n
		continueLoop = (n <= 2);
	
		t_n = t_nplus1;
		parallel_exec(nbNodes, [&](const size_t& i1Nodes)
		{
			for (size_t i1=0; i1<2; i1++)
			{
				Vnode_n[i1Nodes][i1] = Vnode_nplus1[i1Nodes][i1];
			}
		});
	
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
 * Job updateTime called @1.0 in simulate method.
 * In variables: deltat, t_n
 * Out variables: t_nplus1
 */
void Reduction::updateTime() noexcept
{
	t_nplus1 = t_n + deltat;
}

/**
 * Job computeBoundaryNodeVelocities called @2.0 in simulate method.
 * In variables: lpc_n
 * Out variables: Vnode_nplus1
 */
void Reduction::computeBoundaryNodeVelocities() noexcept
{
	const Id pId(mesh.getTopLeftNode());
	const size_t pNodes(pId);
	RealArray1D<2> reduction0({0.0, 0.0});
	{
		const auto cellsOfNodeP(mesh.getCellsOfNode(pId));
		const size_t nbCellsOfNodeP(cellsOfNodeP.size());
		for (size_t cCellsOfNodeP=0; cCellsOfNodeP<nbCellsOfNodeP; cCellsOfNodeP++)
		{
			reduction0 = reductionfreefuncs::sumR1(reduction0, lpc_n[pNodes][cCellsOfNodeP]);
		}
	}
	Vnode_nplus1[pNodes] = reductionfreefuncs::nodeVelocityBoundaryConditionCorner(1, {0.0, 0.0}, 1, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0}, reduction0);
}

void Reduction::simulate()
{
	std::cout << "\n" << __BLUE_BKG__ << __YELLOW__ << __BOLD__ <<"\tStarting Reduction ..." << __RESET__ << "\n\n";
	
	std::cout << "[" << __GREEN__ << "TOPOLOGY" << __RESET__ << "]  HWLOC unavailable cannot get topological informations" << std::endl;
	
	std::cout << "[" << __GREEN__ << "OUTPUT" << __RESET__ << "]    " << __BOLD__ << "Disabled" << __RESET__ << std::endl;

	computeGeometry(); // @1.0
	executeTimeLoopN(); // @1.0
	updateTime(); // @1.0
	computeBoundaryNodeVelocities(); // @2.0
	
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
		std::cerr << "(Reduction.json)" << std::endl;
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
	Reduction* reduction = new Reduction(mesh);
	if (d.HasMember("reduction"))
	{
		rapidjson::StringBuffer strbuf;
		rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
		d["reduction"].Accept(writer);
		reduction->jsonInit(strbuf.GetString());
	}
	
	// Start simulation
	// Simulator must be a pointer when a finalize is needed at the end (Kokkos, omp...)
	reduction->simulate();
	
	delete reduction;
	return ret;
}
