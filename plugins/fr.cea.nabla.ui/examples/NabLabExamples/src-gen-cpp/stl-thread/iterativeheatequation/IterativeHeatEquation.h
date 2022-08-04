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
#include "nablalib/utils/Utils.h"
#include "nablalib/utils/Timer.h"
#include "nablalib/types/Types.h"
#include "nablalib/utils/stl/Parallel.h"
#include "CartesianMesh2D.h"
#include "PvdFileWriter2D.h"

using namespace nablalib::utils;
using namespace nablalib::types;
using namespace nablalib::utils::stl;


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
RealArray1D<x0> operatorAdd(RealArray1D<x0> a, RealArray1D<x0> b);
template<size_t x0>
RealArray1D<x0> operatorMult(double a, RealArray1D<x0> b);
template<size_t x0>
RealArray1D<x0> operatorSub(RealArray1D<x0> a, RealArray1D<x0> b);
}

/******************** Module declaration ********************/

class IterativeHeatEquation
{

private:
	void dumpVariables(int iteration, bool useTimer=true);

	// Mesh and mesh variables
	CartesianMesh2D& mesh;
	size_t nbNodes;
	size_t nbCells;
	size_t nbFaces;

	PvdFileWriter2D* writer;
	std::string outputPath;

	// Timers
	Timer globalTimer;
	Timer cpuTimer;
	Timer ioTimer;
	

public:
	IterativeHeatEquation(CartesianMesh2D& aMesh);
	~IterativeHeatEquation();

	void jsonInit(const char* jsonContent);

	void simulate();
	void computeFaceLength() noexcept;
	void computeTn() noexcept;
	void computeV() noexcept;
	void initD() noexcept;
	void initTime() noexcept;
	void initXc() noexcept;
	void setUpTimeLoopK() noexcept;
	void updateU() noexcept;
	void computeDeltaTn() noexcept;
	void computeFaceConductivity() noexcept;
	void computeResidual() noexcept;
	void executeTimeLoopK() noexcept;
	void initU() noexcept;
	void setUpTimeLoopN() noexcept;
	void computeAlphaCoeff() noexcept;
	void tearDownTimeLoopK() noexcept;
	void executeTimeLoopN() noexcept;

	// Options and global variables.
	// Module variables are public members of the class to be accessible from Python.
	int outputPeriod;
	int lastDump;
	int n;
	int k;
	double stopTime;
	int maxIterations;
	static constexpr double u0 = 1.0;
	static constexpr RealArray1D<2> vectOne = {1.0, 1.0};
	static constexpr int maxIterationsK = 1000;
	static constexpr double epsilon = 1.0E-8;
	double delta_t;
	double t_n;
	double t_nplus1;
	double t_n0;
	std::vector<RealArray1D<2>> X;
	std::vector<RealArray1D<2>> Xc;
	std::vector<double> u_n;
	std::vector<double> u_nplus1;
	std::vector<double> u_nplus1_k;
	std::vector<double> u_nplus1_kplus1;
	std::vector<double> V;
	std::vector<double> D;
	std::vector<double> faceLength;
	std::vector<double> faceConductivity;
	std::vector<std::vector<double>> alpha;
	double residual;
};

#endif
