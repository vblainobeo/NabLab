/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __REDUCTION_H_
#define __REDUCTION_H_

#include <fstream>
#include <iomanip>
#include <type_traits>
#include <limits>
#include <utility>
#include <cmath>
#include "nablalib/utils/Utils.h"
#include "nablalib/utils/Timer.h"
#include "nablalib/types/Types.h"
#include "nablalib/utils/stl/Parallel.h"
#include "CartesianMesh2D.h"

using namespace nablalib::utils;
using namespace nablalib::types;
using namespace nablalib::utils::stl;

/******************** Free functions declarations ********************/

namespace reductionfreefuncs
{
RealArray1D<2> nodeVelocityBoundaryConditionCorner(int BC1, RealArray1D<2> BCValue1, int BC2, RealArray1D<2> BCValue2, RealArray2D<2,2> Mp, RealArray1D<2> Gp, RealArray1D<2> lp_np);
template<size_t x>
RealArray1D<x> sumR1(RealArray1D<x> a, RealArray1D<x> b);
}

/******************** Module declaration ********************/

class Reduction
{
public:
	struct Options
	{
		double maxTime;
		int maxIter;
		double deltat;

		void jsonInit(const char* jsonContent);
	};

	Reduction(CartesianMesh2D& aMesh, Options& aOptions);
	~Reduction();

	void simulate();
	void computeGeometry() noexcept;
	void executeTimeLoopN() noexcept;
	void updateTime() noexcept;
	void computeBoundaryNodeVelocities() noexcept;

private:
	// Mesh and mesh variables
	CartesianMesh2D& mesh;
	size_t nbNodes, maxCellsOfNode, nbCells, maxNodesOfCell;

	// User options
	Options& options;

	// Timers
	Timer globalTimer;
	Timer cpuTimer;
	Timer ioTimer;

public:
	// Global variables
	int n;
	double t_n;
	double t_nplus1;
	std::vector<RealArray1D<2>> X;
	std::vector<RealArray1D<2>> Vnode_n;
	std::vector<RealArray1D<2>> Vnode_nplus1;
	std::vector<std::vector<RealArray1D<2>>> lpc_n;
};

#endif
