/* DO NOT EDIT THIS FILE - it is machine generated */

#include "IterationModule.h"
#include <arcane/Concurrency.h>
#include <arcane/ITimeLoopMng.h>

using namespace Arcane;

/*** Free functions **********************************************************/

namespace iterationfreefuncs
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

IterationModule::IterationModule(const ModuleBuildInfo& bi)
: ArcaneIterationObject(bi)
{}

void IterationModule::init()
{
	// initialization of mesh attributes
	m_mesh = CartesianMesh2D::createInstance(mesh());

	// initialization of other attributes
	m_n = 0;
	m_k = 0;
	m_l = 0;

	// constant time step
	m_global_deltat = m_delta_t;

	// calling jobs
	iniTime(); // @1.0
	iniVk(); // @1.0
	iniVn(); // @1.0
	setUpTimeLoopN(); // @2.0
}

/**
 * Job computeTn called @1.0 in executeTimeLoopN method.
 * In variables: delta_t, t_n
 * Out variables: t_nplus1
 */
void IterationModule::computeTn()
{
	m_t_nplus1 = m_t_n + m_delta_t;
}

/**
 * Job iniTime called @1.0 in simulate method.
 * In variables: 
 * Out variables: t_n0
 */
void IterationModule::iniTime()
{
	m_t_n0 = 0.0;
}

/**
 * Job iniVk called @1.0 in simulate method.
 * In variables: 
 * Out variables: vk_nplus1_k0
 */
void IterationModule::iniVk()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		m_vk_nplus1_k0[jCells] = 0.0;
	}
}

/**
 * Job iniVn called @1.0 in simulate method.
 * In variables: 
 * Out variables: vn_n0
 */
void IterationModule::iniVn()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		m_vn_n0[jCells] = 0.0;
	}
}

/**
 * Job setUpTimeLoopK called @1.0 in executeTimeLoopN method.
 * In variables: vk_nplus1_k0
 * Out variables: vk_nplus1_k
 */
void IterationModule::setUpTimeLoopK()
{
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vk_nplus1_k[i1Cells] = m_vk_nplus1_k0[i1Cells];
	}
}

/**
 * Job updateVk called @1.0 in executeTimeLoopK method.
 * In variables: vk_nplus1_k
 * Out variables: vk_nplus1_kplus1
 */
void IterationModule::updateVk()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		m_vk_nplus1_kplus1[jCells] = m_vk_nplus1_k[jCells] + 2;
	}
}

/**
 * Job updateVl called @1.0 in executeTimeLoopL method.
 * In variables: vl_nplus1_l
 * Out variables: vl_nplus1_lplus1
 */
void IterationModule::updateVl()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		m_vl_nplus1_lplus1[jCells] = m_vl_nplus1_l[jCells] + 1;
	}
}

/**
 * Job executeTimeLoopK called @2.0 in executeTimeLoopN method.
 * In variables: k, maxIterK, vk_nplus1_k
 * Out variables: vk_nplus1_kplus1
 */
void IterationModule::executeTimeLoopK()
{
	m_k = 0;
	bool continueLoop = true;
	do
	{
		m_k++;
		info() << "Start iteration k: " << std::setprecision(5) << m_k;
		updateVk(); // @1.0
	
		// Evaluate loop condition with variables at time n
		continueLoop = (m_k < m_maxIterK);
	
		ENUMERATE_CELL(i1Cells, allCells())
		{
			m_vk_nplus1_k[i1Cells] = m_vk_nplus1_kplus1[i1Cells];
		}
	} while (continueLoop);
}

/**
 * Job setUpTimeLoopN called @2.0 in simulate method.
 * In variables: t_n0, vn_n0
 * Out variables: t_n, vn_n
 */
void IterationModule::setUpTimeLoopN()
{
	m_t_n = m_t_n0;
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vn_n[i1Cells] = m_vn_n0[i1Cells];
	}
}

/**
 * Job executeTimeLoopN called @3.0 in simulate method.
 * In variables: maxIterN, n, t_n, vk_n, vl_n, vn_n
 * Out variables: t_nplus1, vk_nplus1, vl_nplus1, vn_nplus1
 */
void IterationModule::executeTimeLoopN()
{
	m_n++;
	computeTn(); // @1.0
	setUpTimeLoopK(); // @1.0
	executeTimeLoopK(); // @2.0
	tearDownTimeLoopK(); // @3.0
	iniVl(); // @4.0
	oracleVk(); // @4.0
	setUpTimeLoopL(); // @5.0
	executeTimeLoopL(); // @6.0
	tearDownTimeLoopL(); // @7.0
	oracleVl(); // @8.0
	updateVn(); // @8.0
	oracleVn(); // @9.0
	
	// Evaluate loop condition with variables at time n
	bool continueLoop = (m_n < m_maxIterN);
	
	m_t_n = m_t_nplus1;
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vn_n[i1Cells] = m_vn_nplus1[i1Cells];
	}
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vk_n[i1Cells] = m_vk_nplus1[i1Cells];
	}
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vl_n[i1Cells] = m_vl_nplus1[i1Cells];
	}
	
	if (!continueLoop)
		subDomain()->timeLoopMng()->stopComputeLoop(true);
}

/**
 * Job tearDownTimeLoopK called @3.0 in executeTimeLoopN method.
 * In variables: vk_nplus1_kplus1
 * Out variables: vk_nplus1
 */
void IterationModule::tearDownTimeLoopK()
{
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vk_nplus1[i1Cells] = m_vk_nplus1_kplus1[i1Cells];
	}
}

/**
 * Job iniVl called @4.0 in executeTimeLoopN method.
 * In variables: vk_nplus1
 * Out variables: vl_nplus1_l0
 */
void IterationModule::iniVl()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		m_vl_nplus1_l0[jCells] = m_vk_nplus1[jCells] + 8;
	}
}

/**
 * Job oracleVk called @4.0 in executeTimeLoopN method.
 * In variables: vk_nplus1
 * Out variables: 
 */
void IterationModule::oracleVk()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		const bool testVk(iterationfreefuncs::assertEquals(12.0, m_vk_nplus1[jCells]));
	}
}

/**
 * Job setUpTimeLoopL called @5.0 in executeTimeLoopN method.
 * In variables: vl_nplus1_l0
 * Out variables: vl_nplus1_l
 */
void IterationModule::setUpTimeLoopL()
{
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vl_nplus1_l[i1Cells] = m_vl_nplus1_l0[i1Cells];
	}
}

/**
 * Job executeTimeLoopL called @6.0 in executeTimeLoopN method.
 * In variables: l, maxIterL, vl_nplus1_l
 * Out variables: vl_nplus1_lplus1
 */
void IterationModule::executeTimeLoopL()
{
	m_l = 0;
	bool continueLoop = true;
	do
	{
		m_l++;
		info() << "Start iteration l: " << std::setprecision(5) << m_l;
		updateVl(); // @1.0
	
		// Evaluate loop condition with variables at time n
		continueLoop = (m_l < m_maxIterL);
	
		ENUMERATE_CELL(i1Cells, allCells())
		{
			m_vl_nplus1_l[i1Cells] = m_vl_nplus1_lplus1[i1Cells];
		}
	} while (continueLoop);
}

/**
 * Job tearDownTimeLoopL called @7.0 in executeTimeLoopN method.
 * In variables: vl_nplus1_lplus1
 * Out variables: vl_nplus1
 */
void IterationModule::tearDownTimeLoopL()
{
	ENUMERATE_CELL(i1Cells, allCells())
	{
		m_vl_nplus1[i1Cells] = m_vl_nplus1_lplus1[i1Cells];
	}
}

/**
 * Job oracleVl called @8.0 in executeTimeLoopN method.
 * In variables: vl_nplus1
 * Out variables: 
 */
void IterationModule::oracleVl()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		const bool testVl(iterationfreefuncs::assertEquals(27.0, m_vl_nplus1[jCells]));
	}
}

/**
 * Job updateVn called @8.0 in executeTimeLoopN method.
 * In variables: vl_nplus1, vn_n
 * Out variables: vn_nplus1
 */
void IterationModule::updateVn()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		m_vn_nplus1[jCells] = m_vn_n[jCells] + m_vl_nplus1[jCells] * 2;
	}
}

/**
 * Job oracleVn called @9.0 in executeTimeLoopN method.
 * In variables: n, vn_nplus1
 * Out variables: 
 */
void IterationModule::oracleVn()
{
	ENUMERATE_CELL(jCells, allCells())
	{
		const bool testVn(iterationfreefuncs::assertEquals(54.0 * m_n, m_vn_nplus1[jCells]));
	}
}

ARCANE_REGISTER_MODULE_ITERATION(IterationModule);
