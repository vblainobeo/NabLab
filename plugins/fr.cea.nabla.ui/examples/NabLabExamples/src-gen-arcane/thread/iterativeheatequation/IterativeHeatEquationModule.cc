/* DO NOT EDIT THIS FILE - it is machine generated */

#include "IterativeHeatEquationModule.h"
#include <arcane/Concurrency.h>
#include <arcane/ITimeLoopMng.h>

using namespace Arcane;

/*** Free functions **********************************************************/

namespace iterativeheatequationfreefuncs
{
	const bool check(const bool a)
	{
		if (a) 
			return true;
		else
			ARCANE_FATAL("Assertion failed");
	}
	
	const Real norm(RealArrayVariant a)
	{
		return std::sqrt(iterativeheatequationfreefuncs::dot(a, a));
	}
	
	const Real dot(RealArrayVariant a, RealArrayVariant b)
	{
		Real result(0.0);
		for (Int32 i=0; i<a.size(); i++)
		{
			result = result + a(i) * b(i);
		}
		return result;
	}
	
	const Real det(RealArrayVariant a, RealArrayVariant b)
	{
		return (a[0] * b[1] - a[1] * b[0]);
	}
	
	RealArrayVariant sumR1(RealArrayVariant a, RealArrayVariant b)
	{
		return iterativeheatequationfreefuncs::operatorAdd(a, b);
	}
	
	const Real minR0(const Real a, const Real b)
	{
		return std::min(a, b);
	}
	
	const Real sumR0(const Real a, const Real b)
	{
		return a + b;
	}
	
	const Real prodR0(const Real a, const Real b)
	{
		return a * b;
	}
	
	const Real maxR0(const Real a, const Real b)
	{
		return std::max(a, b);
	}
	
	RealArrayVariant operatorAdd(RealArrayVariant a, RealArrayVariant b)
	{
		NumArray<Real,1> result(a.size());
		for (Int32 ix0=0; ix0<a.size(); ix0++)
		{
			result.s(ix0) = a(ix0) + b(ix0);
		}
		return result;
	}
	
	RealArrayVariant operatorMult(const Real a, RealArrayVariant b)
	{
		NumArray<Real,1> result(b.size());
		for (Int32 ix0=0; ix0<b.size(); ix0++)
		{
			result.s(ix0) = a * b(ix0);
		}
		return result;
	}
	
	RealArrayVariant operatorSub(RealArrayVariant a, RealArrayVariant b)
	{
		NumArray<Real,1> result(a.size());
		for (Int32 ix0=0; ix0<a.size(); ix0++)
		{
			result.s(ix0) = a(ix0) - b(ix0);
		}
		return result;
	}
}

/*** Module/Service **********************************************************/

IterativeHeatEquationModule::IterativeHeatEquationModule(const ModuleBuildInfo& bi)
: ArcaneIterativeHeatEquationObject(bi)
{}

void IterativeHeatEquationModule::init()
{
	// initialization of mesh attributes
	m_mesh = CartesianMesh2D::createInstance(mesh());

	// initialization of other attributes
	m_lastDump = numeric_limits<int>::min();
	m_n = 0;
	m_k = 0;
	m_deltat = 0.001;
	m_alpha.resize(nbCell());

	// calling jobs
	computeFaceLength(); // @1.0
	computeV(); // @1.0
	initD(); // @1.0
	initTime(); // @1.0
	initXc(); // @1.0
	computeDeltaTn(); // @2.0
	computeFaceConductivity(); // @2.0
	initU(); // @2.0
	setUpTimeLoopN(); // @2.0
	computeAlphaCoeff(); // @3.0
}

/**
 * Job computeFaceLength called @1.0 in simulate method.
 * In variables: X
 * Out variables: faceLength
 */
void IterativeHeatEquationModule::computeFaceLength()
{
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(fFaces, view)
		{
			const auto fId(fFaces.asItemLocalId());
			Real reduction0(0.0);
			{
				const auto nodesOfFaceF(m_mesh->getNodesOfFace(fId));
				const Int32 nbNodesOfFaceF(nodesOfFaceF.size());
				for (Int32 pNodesOfFaceF=0; pNodesOfFaceF<nbNodesOfFaceF; pNodesOfFaceF++)
				{
					const auto pId(nodesOfFaceF[pNodesOfFaceF]);
					const auto pPlus1Id(nodesOfFaceF[(pNodesOfFaceF+1+nbNodesOfFaceF)%nbNodesOfFaceF]);
					const auto pNodes(pId);
					const auto pPlus1Nodes(pPlus1Id);
					reduction0 = iterativeheatequationfreefuncs::sumR0(reduction0, iterativeheatequationfreefuncs::norm(Real2(iterativeheatequationfreefuncs::operatorSub(m_X[pNodes], m_X[pPlus1Nodes]))));
				}
			}
			m_faceLength[fFaces] = 0.5 * reduction0;
		}
	});
}

/**
 * Job computeTn called @1.0 in executeTimeLoopN method.
 * In variables: deltat, t_n
 * Out variables: t_nplus1
 */
void IterativeHeatEquationModule::computeTn()
{
	m_t_nplus1 = m_t_n + m_deltat;
}

/**
 * Job computeV called @1.0 in simulate method.
 * In variables: X
 * Out variables: V
 */
void IterativeHeatEquationModule::computeV()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			Real reduction0(0.0);
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 pNodesOfCellJ=0; pNodesOfCellJ<nbNodesOfCellJ; pNodesOfCellJ++)
				{
					const auto pId(nodesOfCellJ[pNodesOfCellJ]);
					const auto pPlus1Id(nodesOfCellJ[(pNodesOfCellJ+1+nbNodesOfCellJ)%nbNodesOfCellJ]);
					const auto pNodes(pId);
					const auto pPlus1Nodes(pPlus1Id);
					reduction0 = iterativeheatequationfreefuncs::sumR0(reduction0, iterativeheatequationfreefuncs::det(m_X[pNodes], m_X[pPlus1Nodes]));
				}
			}
			m_V[jCells] = 0.5 * reduction0;
		}
	});
}

/**
 * Job initD called @1.0 in simulate method.
 * In variables: 
 * Out variables: D
 */
void IterativeHeatEquationModule::initD()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			m_D[cCells] = 1.0;
		}
	});
}

/**
 * Job initTime called @1.0 in simulate method.
 * In variables: 
 * Out variables: t_n0
 */
void IterativeHeatEquationModule::initTime()
{
	m_t_n0 = 0.0;
}

/**
 * Job initXc called @1.0 in simulate method.
 * In variables: X
 * Out variables: Xc
 */
void IterativeHeatEquationModule::initXc()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const auto cId(cCells.asItemLocalId());
			Real2 reduction0{0.0, 0.0};
			{
				const auto nodesOfCellC(m_mesh->getNodesOfCell(cId));
				const Int32 nbNodesOfCellC(nodesOfCellC.size());
				for (Int32 pNodesOfCellC=0; pNodesOfCellC<nbNodesOfCellC; pNodesOfCellC++)
				{
					const auto pId(nodesOfCellC[pNodesOfCellC]);
					const auto pNodes(pId);
					reduction0 = Real2(iterativeheatequationfreefuncs::sumR1(reduction0, m_X[pNodes]));
				}
			}
			m_Xc[cCells] = Real2(iterativeheatequationfreefuncs::operatorMult(0.25, reduction0));
		}
	});
}

/**
 * Job setUpTimeLoopK called @1.0 in executeTimeLoopN method.
 * In variables: u_n
 * Out variables: u_nplus1_k
 */
void IterativeHeatEquationModule::setUpTimeLoopK()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_u_nplus1_k[i1Cells] = m_u_n[i1Cells];
		}
	});
}

/**
 * Job updateU called @1.0 in executeTimeLoopK method.
 * In variables: alpha, u_n, u_nplus1_k
 * Out variables: u_nplus1_kplus1
 */
void IterativeHeatEquationModule::updateU()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const auto cId(cCells.asItemLocalId());
			Real reduction0(0.0);
			{
				const auto neighbourCellsC(m_mesh->getNeighbourCells(cId));
				const Int32 nbNeighbourCellsC(neighbourCellsC.size());
				for (Int32 dNeighbourCellsC=0; dNeighbourCellsC<nbNeighbourCellsC; dNeighbourCellsC++)
				{
					const auto dId(neighbourCellsC[dNeighbourCellsC]);
					const auto dCells(dId);
					reduction0 = iterativeheatequationfreefuncs::sumR0(reduction0, m_alpha[cCells][dCells] * m_u_nplus1_k[dCells]);
				}
			}
			m_u_nplus1_kplus1[cCells] = m_u_n[cCells] + m_alpha[cCells][cCells.index()] * m_u_nplus1_k[cCells] + reduction0;
		}
	});
}

/**
 * Job computeDeltaTn called @2.0 in simulate method.
 * In variables: D, V
 * Out variables: deltat
 */
void IterativeHeatEquationModule::computeDeltaTn()
{
	Real reduction0(numeric_limits<double>::max());
	ENUMERATE_CELL(cCells, allCells())
	{
		reduction0 = iterativeheatequationfreefuncs::minR0(reduction0, m_V[cCells] / m_D[cCells]);
	}
	m_deltat = reduction0 * 0.1;
	m_global_deltat = m_deltat;
}

/**
 * Job computeFaceConductivity called @2.0 in simulate method.
 * In variables: D
 * Out variables: faceConductivity
 */
void IterativeHeatEquationModule::computeFaceConductivity()
{
	arcaneParallelForeach(allFaces(), [&](FaceVectorView view)
	{
		ENUMERATE_FACE(fFaces, view)
		{
			const auto fId(fFaces.asItemLocalId());
			Real reduction0(1.0);
			{
				const auto cellsOfFaceF(m_mesh->getCellsOfFace(fId));
				const Int32 nbCellsOfFaceF(cellsOfFaceF.size());
				for (Int32 c1CellsOfFaceF=0; c1CellsOfFaceF<nbCellsOfFaceF; c1CellsOfFaceF++)
				{
					const auto c1Id(cellsOfFaceF[c1CellsOfFaceF]);
					const auto c1Cells(c1Id);
					reduction0 = iterativeheatequationfreefuncs::prodR0(reduction0, m_D[c1Cells]);
				}
			}
			Real reduction1(0.0);
			{
				const auto cellsOfFaceF(m_mesh->getCellsOfFace(fId));
				const Int32 nbCellsOfFaceF(cellsOfFaceF.size());
				for (Int32 c2CellsOfFaceF=0; c2CellsOfFaceF<nbCellsOfFaceF; c2CellsOfFaceF++)
				{
					const auto c2Id(cellsOfFaceF[c2CellsOfFaceF]);
					const auto c2Cells(c2Id);
					reduction1 = iterativeheatequationfreefuncs::sumR0(reduction1, m_D[c2Cells]);
				}
			}
			m_faceConductivity[fFaces] = 2.0 * reduction0 / reduction1;
		}
	});
}

/**
 * Job computeResidual called @2.0 in executeTimeLoopK method.
 * In variables: u_nplus1_k, u_nplus1_kplus1
 * Out variables: residual
 */
void IterativeHeatEquationModule::computeResidual()
{
	Real reduction0(-numeric_limits<double>::max());
	ENUMERATE_CELL(jCells, allCells())
	{
		reduction0 = iterativeheatequationfreefuncs::maxR0(reduction0, std::abs(m_u_nplus1_kplus1[jCells] - m_u_nplus1_k[jCells]));
	}
	m_residual = reduction0;
}

/**
 * Job executeTimeLoopK called @2.0 in executeTimeLoopN method.
 * In variables: epsilon, k, maxIterationsK, residual, u_nplus1_k
 * Out variables: u_nplus1_kplus1
 */
void IterativeHeatEquationModule::executeTimeLoopK()
{
	m_k = 0;
	bool continueLoop = true;
	do
	{
		m_k++;
		info() << "Start iteration k: " << std::setprecision(5) << m_k;
		updateU(); // @1.0
		computeResidual(); // @2.0
	
		// Evaluate loop condition with variables at time n
		continueLoop = (m_residual > m_epsilon && iterativeheatequationfreefuncs::check(m_k + 1 < m_maxIterationsK));
	
		arcaneParallelForeach(allCells(), [&](CellVectorView view)
		{
			ENUMERATE_CELL(i1Cells, view)
			{
				m_u_nplus1_k[i1Cells] = m_u_nplus1_kplus1[i1Cells];
			}
		});
	} while (continueLoop);
}

/**
 * Job initU called @2.0 in simulate method.
 * In variables: Xc, u0, vectOne
 * Out variables: u_n
 */
void IterativeHeatEquationModule::initU()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			if (iterativeheatequationfreefuncs::norm(Real2(iterativeheatequationfreefuncs::operatorSub(m_Xc[cCells], m_vectOne))) < 0.5) 
				m_u_n[cCells] = m_u0;
			else
				m_u_n[cCells] = 0.0;
		}
	});
}

/**
 * Job setUpTimeLoopN called @2.0 in simulate method.
 * In variables: t_n0
 * Out variables: t_n
 */
void IterativeHeatEquationModule::setUpTimeLoopN()
{
	m_t_n = m_t_n0;
}

/**
 * Job computeAlphaCoeff called @3.0 in simulate method.
 * In variables: V, Xc, deltat, faceConductivity, faceLength
 * Out variables: alpha
 */
void IterativeHeatEquationModule::computeAlphaCoeff()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(cCells, view)
		{
			const auto cId(cCells.asItemLocalId());
			Real alphaDiag(0.0);
			{
				const auto neighbourCellsC(m_mesh->getNeighbourCells(cId));
				const Int32 nbNeighbourCellsC(neighbourCellsC.size());
				for (Int32 dNeighbourCellsC=0; dNeighbourCellsC<nbNeighbourCellsC; dNeighbourCellsC++)
				{
					const auto dId(neighbourCellsC[dNeighbourCellsC]);
					const auto dCells(dId);
					const auto fId(m_mesh->getCommonFace(cId, dId));
					const auto fFaces(fId);
					const Real alphaExtraDiag(m_deltat / m_V[cCells] * (m_faceLength[fFaces] * m_faceConductivity[fFaces]) / iterativeheatequationfreefuncs::norm(Real2(iterativeheatequationfreefuncs::operatorSub(m_Xc[cCells], m_Xc[dCells]))));
					m_alpha[cCells][dCells] = alphaExtraDiag;
					alphaDiag = alphaDiag + alphaExtraDiag;
				}
			}
			m_alpha[cCells][cCells.index()] = -alphaDiag;
		}
	});
}

/**
 * Job tearDownTimeLoopK called @3.0 in executeTimeLoopN method.
 * In variables: u_nplus1_kplus1
 * Out variables: u_nplus1
 */
void IterativeHeatEquationModule::tearDownTimeLoopK()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_u_nplus1[i1Cells] = m_u_nplus1_kplus1[i1Cells];
		}
	});
}

/**
 * Job executeTimeLoopN called @4.0 in simulate method.
 * In variables: lastDump, maxIterations, n, outputPeriod, stopTime, t_n, t_nplus1, u_n
 * Out variables: t_nplus1, u_nplus1
 */
void IterativeHeatEquationModule::executeTimeLoopN()
{
	m_n++;
	computeTn(); // @1.0
	setUpTimeLoopK(); // @1.0
	executeTimeLoopK(); // @2.0
	tearDownTimeLoopK(); // @3.0
	
	// Evaluate loop condition with variables at time n
	bool continueLoop = (m_t_nplus1 < options()->stopTime() && m_n + 1 < options()->maxIterations());
	
	m_t_n = m_t_nplus1;
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_u_n[i1Cells] = m_u_nplus1[i1Cells];
		}
	});
	
	if (!continueLoop)
		subDomain()->timeLoopMng()->stopComputeLoop(true);
}

ARCANE_REGISTER_MODULE_ITERATIVEHEATEQUATION(IterativeHeatEquationModule);
