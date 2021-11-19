/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __ITERATIVEHEATEQUATION_H_
#define __ITERATIVEHEATEQUATION_H_

#include <fstream>
#include <iomanip>
#include <type_traits>
#include <limits>
#include <utility>
#include <cmath>
#include <rapidjson/document.h>
#include <Kokkos_Core.hpp>
#include <Kokkos_hwloc.hpp>
#include "nablalib/utils/Utils.h"
#include "nablalib/utils/Timer.h"
#include "nablalib/types/Types.h"
#include "nablalib/utils/kokkos/Parallel.h"
#include "CartesianMesh2D.h"
#include "PvdFileWriter2D.h"

using namespace nablalib::utils;
using namespace nablalib::types;
using namespace nablalib::utils::kokkos;

/******************** Free functions declarations ********************/

namespace iterativeheatequationfreefuncs
{
bool check(bool a);
template<size_t x>
double norm(RealArray1D<x> a);
template<size_t x>
double dot(RealArray1D<x> a, RealArray1D<x> b);
double det(RealArray1D<2> a, RealArray1D<2> b);
template<size_t x>
RealArray1D<x> sumR1(RealArray1D<x> a, RealArray1D<x> b);
double minR0(double a, double b);
double sumR0(double a, double b);
double prodR0(double a, double b);
double maxR0(double a, double b);
template<size_t x0>
RealArray1D<x0> operator+(RealArray1D<x0> a, RealArray1D<x0> b);
template<size_t x0>
RealArray1D<x0> operator*(double a, RealArray1D<x0> b);
template<size_t x0>
RealArray1D<x0> operator-(RealArray1D<x0> a, RealArray1D<x0> b);
}

/******************** Module declaration ********************/

class IterativeHeatEquation
{
	typedef Kokkos::TeamPolicy<Kokkos::DefaultExecutionSpace::scratch_memory_space>::member_type member_type;

public:
	IterativeHeatEquation(CartesianMesh2D& aMesh);
	~IterativeHeatEquation();

	void jsonInit(const char* jsonContent);

	void simulate();
	void computeFaceLength(const member_type& teamMember) noexcept;
	void computeTn() noexcept;
	void computeV(const member_type& teamMember) noexcept;
	void initD(const member_type& teamMember) noexcept;
	void initTime() noexcept;
	void initXc(const member_type& teamMember) noexcept;
	void setUpTimeLoopK(const member_type& teamMember) noexcept;
	void updateU(const member_type& teamMember) noexcept;
	void computeDeltaTn(const member_type& teamMember) noexcept;
	void computeFaceConductivity(const member_type& teamMember) noexcept;
	void computeResidual(const member_type& teamMember) noexcept;
	void executeTimeLoopK() noexcept;
	void initU(const member_type& teamMember) noexcept;
	void setUpTimeLoopN() noexcept;
	void computeAlphaCoeff(const member_type& teamMember) noexcept;
	void tearDownTimeLoopK(const member_type& teamMember) noexcept;
	void executeTimeLoopN() noexcept;

private:
	void dumpVariables(int iteration, bool useTimer=true);

	/**
	 * Utility function to get work load for each team of threads
	 * In  : thread and number of element to use for computation
	 * Out : pair of indexes, 1st one for start of chunk, 2nd one for size of chunk
	 */
	const std::pair<size_t, size_t> computeTeamWorkRange(const member_type& thread, const size_t& nb_elmt) noexcept;

	// Mesh and mesh variables
	CartesianMesh2D& mesh;
	size_t nbNodes, nbCells, nbFaces, maxNodesOfCell, maxNodesOfFace, maxCellsOfFace, maxNeighbourCells;

	// Options and global variables
	PvdFileWriter2D* writer;
	std::string outputPath;
	int outputPeriod;
	int lastDump;
	int n;
	int k;
	double u0;
	static constexpr RealArray1D<2> vectOne = {1.0, 1.0};
	double stopTime;
	int maxIterations;
	int maxIterationsK;
	double epsilon;
	double deltat;
	double t_n;
	double t_nplus1;
	double t_n0;
	Kokkos::View<RealArray1D<2>*> X;
	Kokkos::View<RealArray1D<2>*> Xc;
	Kokkos::View<double*> u_n;
	Kokkos::View<double*> u_nplus1;
	Kokkos::View<double*> u_nplus1_k;
	Kokkos::View<double*> u_nplus1_kplus1;
	Kokkos::View<double*> V;
	Kokkos::View<double*> D;
	Kokkos::View<double*> faceLength;
	Kokkos::View<double*> faceConductivity;
	Kokkos::View<double**> alpha;
	double residual;

	// Timers
	Timer globalTimer;
	Timer cpuTimer;
	Timer ioTimer;
};

#endif
