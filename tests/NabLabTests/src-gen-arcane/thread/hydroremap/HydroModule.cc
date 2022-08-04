/* DO NOT EDIT THIS FILE - it is machine generated */

#include "HydroModule.h"
#include <arcane/Concurrency.h>
#include <arcane/ITimeLoopMng.h>

using namespace Arcane;

/*** Free functions **********************************************************/

namespace hydrofreefuncs
{
	bool assertEquals(Real expected, Real actual)
	{
		const bool ret((expected == actual));
		if (!ret) 
			ARCANE_FATAL("** Assertion failed");
		return ret;
	}
}

/*** Module/Service **********************************************************/

HydroModule::HydroModule(const ModuleBuildInfo& bi)
: ArcaneHydroObject(bi)
{}

void HydroModule::init()
{
	// initialization of mesh attributes
	m_mesh = CartesianMesh2D::createInstance(mesh());

	// initialization of other attributes

	// constant time step
	m_global_delta_t = options()->deltaT();

	// calling jobs
	iniHv1(); // @1.0
	iniHv2(); // @1.0
	hj1(); // @2.0
	oracleHv1(); // @2.0
	oracleHv2(); // @2.0
	options()->r1()->rj1(); // @2.0
	hj2(); // @3.0
	oracleHv3(); // @3.0
	oracleHv4(); // @3.0
	options()->r2()->rj1(); // @3.0
	options()->r1()->rj2(); // @3.0
	oracleHv5(); // @4.0
	options()->r2()->rj2(); // @4.0
	hj3(); // @5.0
	oracleHv6(); // @5.0
	oracleHv7(); // @6.0

	// No compute loop entry point: end of computation triggered to avoid infinite loop in tests
	subDomain()->timeLoopMng()->stopComputeLoop(true);
}

/**
 * Job iniHv1 called @1.0 in simulate method.
 * In variables: 
 * Out variables: hv1
 */
void HydroModule::iniHv1()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			m_hv1[cCells] = 2.0;
		}
	});
}

/**
 * Job iniHv2 called @1.0 in simulate method.
 * In variables: 
 * Out variables: hv2
 */
void HydroModule::iniHv2()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			m_hv2[cCells] = 0.0;
		}
	});
}

/**
 * Job hj1 called @2.0 in simulate method.
 * In variables: hv2
 * Out variables: hv3
 */
void HydroModule::hj1()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			m_hv3[cCells] = m_hv2[cCells] + 1.0;
		}
	});
}

/**
 * Job oracleHv1 called @2.0 in simulate method.
 * In variables: hv1
 * Out variables: 
 */
void HydroModule::oracleHv1()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const bool testHv1(hydrofreefuncs::assertEquals(2.0, m_hv1[cCells]));
		}
	});
}

/**
 * Job oracleHv2 called @2.0 in simulate method.
 * In variables: hv2
 * Out variables: 
 */
void HydroModule::oracleHv2()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const bool testHv2(hydrofreefuncs::assertEquals(0.0, m_hv2[cCells]));
		}
	});
}

/**
 * Job hj2 called @3.0 in simulate method.
 * In variables: hv3
 * Out variables: hv5
 */
void HydroModule::hj2()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			m_hv5[cCells] = m_hv3[cCells] + 2.0;
		}
	});
}

/**
 * Job oracleHv3 called @3.0 in simulate method.
 * In variables: hv3
 * Out variables: 
 */
void HydroModule::oracleHv3()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const bool testHv3(hydrofreefuncs::assertEquals(1.0, m_hv3[cCells]));
		}
	});
}

/**
 * Job oracleHv4 called @3.0 in simulate method.
 * In variables: hv4
 * Out variables: 
 */
void HydroModule::oracleHv4()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const bool testHv4(hydrofreefuncs::assertEquals(4.0, m_hv4[cCells]));
		}
	});
}

/**
 * Job oracleHv5 called @4.0 in simulate method.
 * In variables: hv5
 * Out variables: 
 */
void HydroModule::oracleHv5()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const bool testHv5(hydrofreefuncs::assertEquals(3.0, m_hv5[cCells]));
		}
	});
}

/**
 * Job hj3 called @5.0 in simulate method.
 * In variables: hv4, hv5, hv6
 * Out variables: hv7
 */
void HydroModule::hj3()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			m_hv7[cCells] = m_hv4[cCells] + m_hv5[cCells] + m_hv6[cCells];
		}
	});
}

/**
 * Job oracleHv6 called @5.0 in simulate method.
 * In variables: hv6
 * Out variables: 
 */
void HydroModule::oracleHv6()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const bool testHv6(hydrofreefuncs::assertEquals(6.0, m_hv6[cCells]));
		}
	});
}

/**
 * Job oracleHv7 called @6.0 in simulate method.
 * In variables: hv7
 * Out variables: 
 */
void HydroModule::oracleHv7()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const bool testHv7(hydrofreefuncs::assertEquals(13.0, m_hv7[cCells]));
		}
	});
}

ARCANE_REGISTER_MODULE_HYDRO(HydroModule);
