/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __HYDRO_H_
#define __HYDRO_H_

#include <fstream>
#include <iomanip>
#include <type_traits>
#include <limits>
#include <utility>
#include <cmath>
#include <rapidjson/document.h>
#include <omp.h>
#include "nablalib/utils/Utils.h"
#include "nablalib/utils/Timer.h"
#include "nablalib/types/Types.h"
#include "CartesianMesh2D.h"

using namespace nablalib::utils;
using namespace nablalib::types;


class R1;
class R2;

/******************** Free functions declarations ********************/

namespace hydrofreefuncs
{
bool assertEquals(double expected, double actual);
}

/******************** Module declaration ********************/

class Hydro
{
	friend class R1;
	friend class R2;


private:
	// Mesh and mesh variables
	CartesianMesh2D& mesh;
	size_t nbNodes;
	size_t nbCells;

	// Additional modules
	R1* r1;
	R2* r2;


	// Timers
	Timer globalTimer;
	Timer cpuTimer;
	Timer ioTimer;
	

public:
	Hydro(CartesianMesh2D& aMesh);
	~Hydro();

	void jsonInit(const char* jsonContent);

	void simulate();
	void iniHv1() noexcept;
	void iniHv2() noexcept;
	void hj1() noexcept;
	void oracleHv1() noexcept;
	void oracleHv2() noexcept;
	void hj2() noexcept;
	void oracleHv3() noexcept;
	void oracleHv4() noexcept;
	void oracleHv5() noexcept;
	void hj3() noexcept;
	void oracleHv6() noexcept;
	void oracleHv7() noexcept;

	// Options and global variables.
	// Module variables are public members of the class to be accessible from Python.
	int maxIter;
	double maxTime;
	double delta_t;
	static constexpr double t = 0.0;
	std::vector<RealArray1D<2>> X;
	std::vector<double> hv1;
	std::vector<double> hv2;
	std::vector<double> hv3;
	std::vector<double> hv4;
	std::vector<double> hv5;
	std::vector<double> hv6;
	std::vector<double> hv7;
};

#endif
