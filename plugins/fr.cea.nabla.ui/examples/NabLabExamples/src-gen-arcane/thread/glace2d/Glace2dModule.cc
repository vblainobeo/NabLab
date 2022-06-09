/* DO NOT EDIT THIS FILE - it is machine generated */

#include "Glace2dModule.h"
#include <arcane/Concurrency.h>
#include <arcane/ITimeLoopMng.h>

using namespace Arcane;

/*** Free functions **********************************************************/

namespace glace2dfreefuncs
{
	const Real det(RealArray2Variant a)
	{
		return a[0][0] * a[1][1] - a[0][1] * a[1][0];
	}
	
	RealArrayVariant perp(RealArrayVariant a)
	{
		return Real2{a[1], -a[0]};
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
	
	const Real norm(RealArrayVariant a)
	{
		return std::sqrt(glace2dfreefuncs::dot(a, a));
	}
	
	RealArray2Variant tensProduct(RealArrayVariant a, RealArrayVariant b)
	{
		NumArray<Real,2> result(a.size(), a.size());
		for (Int32 ia=0; ia<a.size(); ia++)
		{
			for (Int32 ib=0; ib<a.size(); ib++)
			{
				result(ia, ib) = a(ia) * b(ib);
			}
		}
		return result;
	}
	
	RealArrayVariant matVectProduct(RealArray2Variant a, RealArrayVariant b)
	{
		NumArray<Real,1> result(a.dim1Size());
		for (Int32 ix=0; ix<a.dim1Size(); ix++)
		{
			NumArray<Real,1> tmp(a.dim2Size());
			for (Int32 iy=0; iy<a.dim2Size(); iy++)
			{
				tmp(iy) = a(ix, iy);
			}
			result(ix) = glace2dfreefuncs::dot(tmp, b);
		}
		return result;
	}
	
	const Real trace(RealArray2Variant a)
	{
		Real result(0.0);
		for (Int32 ia=0; ia<a.dim1Size(); ia++)
		{
			result = result + a(ia, ia);
		}
		return result;
	}
	
	RealArray2Variant inverse(RealArray2Variant a)
	{
		const Real alpha(1.0 / glace2dfreefuncs::det(a));
		return Real2x2{Real2{a[1][1] * alpha, -a[0][1] * alpha}, Real2{-a[1][0] * alpha, a[0][0] * alpha}};
	}
	
	RealArrayVariant sumR1(RealArrayVariant a, RealArrayVariant b)
	{
		return glace2dfreefuncs::operatorAdd(a, b);
	}
	
	const Real sumR0(const Real a, const Real b)
	{
		return a + b;
	}
	
	RealArray2Variant sumR2(RealArray2Variant a, RealArray2Variant b)
	{
		return glace2dfreefuncs::operatorAdd(a, b);
	}
	
	const Real minR0(const Real a, const Real b)
	{
		return std::min(a, b);
	}
	
	RealArrayVariant operatorAdd(RealArrayVariant a, RealArrayVariant b)
	{
		NumArray<Real,1> result(a.size());
		for (Int32 ix0=0; ix0<a.size(); ix0++)
		{
			result(ix0) = a(ix0) + b(ix0);
		}
		return result;
	}
	
	RealArray2Variant operatorAdd(RealArray2Variant a, RealArray2Variant b)
	{
		NumArray<Real,2> result(a.dim1Size(), a.dim2Size());
		for (Int32 ix0=0; ix0<a.dim1Size(); ix0++)
		{
			for (Int32 ix1=0; ix1<a.dim2Size(); ix1++)
			{
				result(ix0, ix1) = a(ix0, ix1) + b(ix0, ix1);
			}
		}
		return result;
	}
	
	RealArrayVariant operatorMult(const Real a, RealArrayVariant b)
	{
		NumArray<Real,1> result(b.size());
		for (Int32 ix0=0; ix0<b.size(); ix0++)
		{
			result(ix0) = a * b(ix0);
		}
		return result;
	}
	
	RealArrayVariant operatorSub(RealArrayVariant a, RealArrayVariant b)
	{
		NumArray<Real,1> result(a.size());
		for (Int32 ix0=0; ix0<a.size(); ix0++)
		{
			result(ix0) = a(ix0) - b(ix0);
		}
		return result;
	}
	
	RealArray2Variant operatorMult(const Real a, RealArray2Variant b)
	{
		NumArray<Real,2> result(b.dim1Size(), b.dim2Size());
		for (Int32 ix0=0; ix0<b.dim1Size(); ix0++)
		{
			for (Int32 ix1=0; ix1<b.dim2Size(); ix1++)
			{
				result(ix0, ix1) = a * b(ix0, ix1);
			}
		}
		return result;
	}
	
	RealArray2Variant operatorSub(RealArray2Variant a, RealArray2Variant b)
	{
		NumArray<Real,2> result(a.dim1Size(), a.dim2Size());
		for (Int32 ix0=0; ix0<a.dim1Size(); ix0++)
		{
			for (Int32 ix1=0; ix1<a.dim2Size(); ix1++)
			{
				result(ix0, ix1) = a(ix0, ix1) - b(ix0, ix1);
			}
		}
		return result;
	}
	
	RealArray2Variant operatorMult(RealArray2Variant a, RealArray2Variant b)
	{
		NumArray<Real,2> result(a.dim1Size(), a.dim2Size());
		for (Int32 ix0=0; ix0<a.dim1Size(); ix0++)
		{
			for (Int32 ix1=0; ix1<a.dim2Size(); ix1++)
			{
				result(ix0, ix1) = a(ix0, ix1) * b(ix0, ix1);
			}
		}
		return result;
	}
	
	RealArray2Variant operatorMult(RealArray2Variant a, const Real b)
	{
		NumArray<Real,2> result(a.dim1Size(), a.dim2Size());
		for (Int32 ix0=0; ix0<a.dim1Size(); ix0++)
		{
			for (Int32 ix1=0; ix1<a.dim2Size(); ix1++)
			{
				result(ix0, ix1) = a(ix0, ix1) * b;
			}
		}
		return result;
	}
}

/*** Module/Service **********************************************************/

Glace2dModule::Glace2dModule(const ModuleBuildInfo& bi)
: ArcaneGlace2dObject(bi)
{}

void Glace2dModule::init()
{
	// initialization of mesh attributes
	m_mesh = CartesianMesh2D::createInstance(mesh());

	// initialization of other attributes
	m_lastDump = numeric_limits<int>::min();
	m_n = 0;
	m_l.resize(4);
	m_Cjr_ic.resize(4);
	m_C.resize(4);
	m_F.resize(4);
	m_Ajr.resize(4);

	// Copy node coordinates
	ENUMERATE_NODE(inode, allNodes())
	{
		m_X_n0[inode][0] = m_X_n[inode][0];
		m_X_n0[inode][1] = m_X_n[inode][1];
	}

	// calling jobs
	iniCjrIc(); // @1.0
	iniTime(); // @1.0
	initialize(); // @2.0
	setUpTimeLoopN(); // @2.0
}

/**
 * Job computeCjr called @1.0 in executeTimeLoopN method.
 * In variables: X_n
 * Out variables: C
 */
void Glace2dModule::computeCjr()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rPlus1Id(nodesOfCellJ[(rNodesOfCellJ+1+nbNodesOfCellJ)%nbNodesOfCellJ]);
					const auto rMinus1Id(nodesOfCellJ[(rNodesOfCellJ-1+nbNodesOfCellJ)%nbNodesOfCellJ]);
					const auto rPlus1Nodes(rPlus1Id);
					const auto rMinus1Nodes(rMinus1Id);
					m_C[jCells][rNodesOfCellJ] = Real2(glace2dfreefuncs::operatorMult(0.5, Real2(glace2dfreefuncs::perp(Real2(glace2dfreefuncs::operatorSub(m_X_n[rPlus1Nodes], m_X_n[rMinus1Nodes]))))));
				}
			}
		}
	});
}

/**
 * Job computeInternalEnergy called @1.0 in executeTimeLoopN method.
 * In variables: E_n, uj_n
 * Out variables: e
 */
void Glace2dModule::computeInternalEnergy()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			m_e[jCells] = m_E_n[jCells] - 0.5 * glace2dfreefuncs::dot(m_uj_n[jCells], m_uj_n[jCells]);
		}
	});
}

/**
 * Job iniCjrIc called @1.0 in simulate method.
 * In variables: X_n0
 * Out variables: Cjr_ic
 */
void Glace2dModule::iniCjrIc()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rPlus1Id(nodesOfCellJ[(rNodesOfCellJ+1+nbNodesOfCellJ)%nbNodesOfCellJ]);
					const auto rMinus1Id(nodesOfCellJ[(rNodesOfCellJ-1+nbNodesOfCellJ)%nbNodesOfCellJ]);
					const auto rPlus1Nodes(rPlus1Id);
					const auto rMinus1Nodes(rMinus1Id);
					m_Cjr_ic[jCells][rNodesOfCellJ] = Real2(glace2dfreefuncs::operatorMult(0.5, Real2(glace2dfreefuncs::perp(Real2(glace2dfreefuncs::operatorSub(m_X_n0[rPlus1Nodes], m_X_n0[rMinus1Nodes]))))));
				}
			}
		}
	});
}

/**
 * Job iniTime called @1.0 in simulate method.
 * In variables: 
 * Out variables: t_n0
 */
void Glace2dModule::iniTime()
{
	m_t_n0 = 0.0;
}

/**
 * Job computeLjr called @2.0 in executeTimeLoopN method.
 * In variables: C
 * Out variables: l
 */
void Glace2dModule::computeLjr()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					m_l[jCells][rNodesOfCellJ] = glace2dfreefuncs::norm(m_C[jCells][rNodesOfCellJ]);
				}
			}
		}
	});
}

/**
 * Job computeV called @2.0 in executeTimeLoopN method.
 * In variables: C, X_n
 * Out variables: V
 */
void Glace2dModule::computeV()
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
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rId(nodesOfCellJ[rNodesOfCellJ]);
					const auto rNodes(rId);
					reduction0 = glace2dfreefuncs::sumR0(reduction0, glace2dfreefuncs::dot(m_C[jCells][rNodesOfCellJ], m_X_n[rNodes]));
				}
			}
			m_V[jCells] = 0.5 * reduction0;
		}
	});
}

/**
 * Job initialize called @2.0 in simulate method.
 * In variables: Cjr_ic, X_n0, gamma, pIniZd, pIniZg, rhoIniZd, rhoIniZg, xInterface
 * Out variables: E_n, m, p, rho, uj_n
 */
void Glace2dModule::initialize()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			Real rho_ic;
			Real p_ic;
			Real2 reduction0{0.0, 0.0};
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rId(nodesOfCellJ[rNodesOfCellJ]);
					const auto rNodes(rId);
					reduction0 = Real2(glace2dfreefuncs::sumR1(reduction0, m_X_n0[rNodes]));
				}
			}
			const Real2 center(Real2(glace2dfreefuncs::operatorMult(0.25, reduction0)));
			if (center[0] < m_xInterface) 
			{
				rho_ic = m_rhoIniZg;
				p_ic = m_pIniZg;
			}
			else
			{
				rho_ic = m_rhoIniZd;
				p_ic = m_pIniZd;
			}
			Real reduction1(0.0);
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rId(nodesOfCellJ[rNodesOfCellJ]);
					const auto rNodes(rId);
					reduction1 = glace2dfreefuncs::sumR0(reduction1, glace2dfreefuncs::dot(m_Cjr_ic[jCells][rNodesOfCellJ], m_X_n0[rNodes]));
				}
			}
			const Real V_ic(0.5 * reduction1);
			m_m[jCells] = rho_ic * V_ic;
			m_p[jCells] = p_ic;
			m_rho[jCells] = rho_ic;
			m_E_n[jCells] = p_ic / ((m_gamma - 1.0) * rho_ic);
			m_uj_n[jCells] = Real2{0.0, 0.0};
		}
	});
}

/**
 * Job setUpTimeLoopN called @2.0 in simulate method.
 * In variables: X_n0, t_n0
 * Out variables: X_n, t_n
 */
void Glace2dModule::setUpTimeLoopN()
{
	m_t_n = m_t_n0;
	arcaneParallelForeach(allNodes(), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(i1Nodes, view)
		{
			for (Int32 i1=0; i1<2; i1++)
			{
				m_X_n[i1Nodes][i1] = m_X_n0[i1Nodes][i1];
			}
		}
	});
}

/**
 * Job computeDensity called @3.0 in executeTimeLoopN method.
 * In variables: V, m
 * Out variables: rho
 */
void Glace2dModule::computeDensity()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			m_rho[jCells] = m_m[jCells] / m_V[jCells];
		}
	});
}

/**
 * Job executeTimeLoopN called @3.0 in simulate method.
 * In variables: E_n, X_n, lastDump, maxIterations, n, outputPeriod, stopTime, t_n, t_nplus1, uj_n
 * Out variables: E_nplus1, X_nplus1, t_nplus1, uj_nplus1
 */
void Glace2dModule::executeTimeLoopN()
{
	m_n++;
	computeCjr(); // @1.0
	computeInternalEnergy(); // @1.0
	computeLjr(); // @2.0
	computeV(); // @2.0
	computeDensity(); // @3.0
	computeEOSp(); // @4.0
	computeEOSc(); // @5.0
	computeAjr(); // @6.0
	computedeltatj(); // @6.0
	computeAr(); // @7.0
	computeBr(); // @7.0
	computeDt(); // @7.0
	computeBoundaryConditions(); // @8.0
	computeBt(); // @8.0
	computeMt(); // @8.0
	computeTn(); // @8.0
	computeU(); // @9.0
	computeFjr(); // @10.0
	computeXn(); // @10.0
	computeEn(); // @11.0
	computeUn(); // @11.0
	
	// Evaluate loop condition with variables at time n
	bool continueLoop = (m_t_nplus1 < options()->stopTime() && m_n + 1 < options()->maxIterations());
	
	m_t_n = m_t_nplus1;
	arcaneParallelForeach(allNodes(), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(i1Nodes, view)
		{
			for (Int32 i1=0; i1<2; i1++)
			{
				m_X_n[i1Nodes][i1] = m_X_nplus1[i1Nodes][i1];
			}
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			m_E_n[i1Cells] = m_E_nplus1[i1Cells];
		}
	});
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(i1Cells, view)
		{
			for (Int32 i1=0; i1<2; i1++)
			{
				m_uj_n[i1Cells][i1] = m_uj_nplus1[i1Cells][i1];
			}
		}
	});
	
	if (!continueLoop)
		subDomain()->timeLoopMng()->stopComputeLoop(true);
}

/**
 * Job computeEOSp called @4.0 in executeTimeLoopN method.
 * In variables: e, gamma, rho
 * Out variables: p
 */
void Glace2dModule::computeEOSp()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			m_p[jCells] = (m_gamma - 1.0) * m_rho[jCells] * m_e[jCells];
		}
	});
}

/**
 * Job computeEOSc called @5.0 in executeTimeLoopN method.
 * In variables: gamma, p, rho
 * Out variables: c
 */
void Glace2dModule::computeEOSc()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			m_c[jCells] = std::sqrt(m_gamma * m_p[jCells] / m_rho[jCells]);
		}
	});
}

/**
 * Job computeAjr called @6.0 in executeTimeLoopN method.
 * In variables: C, c, l, rho
 * Out variables: Ajr
 */
void Glace2dModule::computeAjr()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					m_Ajr[jCells][rNodesOfCellJ] = Real2x2(glace2dfreefuncs::operatorMult(((m_rho[jCells] * m_c[jCells]) / m_l[jCells][rNodesOfCellJ]), Real2x2(glace2dfreefuncs::tensProduct(m_C[jCells][rNodesOfCellJ], m_C[jCells][rNodesOfCellJ]))));
				}
			}
		}
	});
}

/**
 * Job computedeltatj called @6.0 in executeTimeLoopN method.
 * In variables: V, c, l
 * Out variables: deltatj
 */
void Glace2dModule::computedeltatj()
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
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					reduction0 = glace2dfreefuncs::sumR0(reduction0, m_l[jCells][rNodesOfCellJ]);
				}
			}
			m_deltatj[jCells] = 2.0 * m_V[jCells] / (m_c[jCells] * reduction0);
		}
	});
}

/**
 * Job computeAr called @7.0 in executeTimeLoopN method.
 * In variables: Ajr
 * Out variables: Ar
 */
void Glace2dModule::computeAr()
{
	arcaneParallelForeach(allNodes(), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rNodes, view)
		{
			const auto rId(rNodes.asItemLocalId());
			Real2x2 reduction0{{0.0, 0.0}, {0.0, 0.0}};
			{
				const auto cellsOfNodeR(m_mesh->getCellsOfNode(rId));
				const Int32 nbCellsOfNodeR(cellsOfNodeR.size());
				for (Int32 jCellsOfNodeR=0; jCellsOfNodeR<nbCellsOfNodeR; jCellsOfNodeR++)
				{
					const auto jId(cellsOfNodeR[jCellsOfNodeR]);
					const auto jCells(jId);
					const auto rNodesOfCellJ(m_mesh->indexOf(m_mesh->getNodesOfCell(jId), rId));
					reduction0 = Real2x2(glace2dfreefuncs::sumR2(reduction0, m_Ajr[jCells][rNodesOfCellJ]));
				}
			}
			for (Int32 i1=0; i1<2; i1++)
			{
				for (Int32 i2=0; i2<2; i2++)
				{
					m_Ar[rNodes][i1][i2] = reduction0[i1][i2];
				}
			}
		}
	});
}

/**
 * Job computeBr called @7.0 in executeTimeLoopN method.
 * In variables: Ajr, C, p, uj_n
 * Out variables: b
 */
void Glace2dModule::computeBr()
{
	arcaneParallelForeach(allNodes(), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rNodes, view)
		{
			const auto rId(rNodes.asItemLocalId());
			Real2 reduction0{0.0, 0.0};
			{
				const auto cellsOfNodeR(m_mesh->getCellsOfNode(rId));
				const Int32 nbCellsOfNodeR(cellsOfNodeR.size());
				for (Int32 jCellsOfNodeR=0; jCellsOfNodeR<nbCellsOfNodeR; jCellsOfNodeR++)
				{
					const auto jId(cellsOfNodeR[jCellsOfNodeR]);
					const auto jCells(jId);
					const auto rNodesOfCellJ(m_mesh->indexOf(m_mesh->getNodesOfCell(jId), rId));
					reduction0 = Real2(glace2dfreefuncs::sumR1(reduction0, Real2(glace2dfreefuncs::operatorAdd(Real2(glace2dfreefuncs::operatorMult(m_p[jCells], m_C[jCells][rNodesOfCellJ])), Real2(glace2dfreefuncs::matVectProduct(m_Ajr[jCells][rNodesOfCellJ], m_uj_n[jCells]))))));
				}
			}
			for (Int32 i1=0; i1<2; i1++)
			{
				m_b[rNodes][i1] = reduction0[i1];
			}
		}
	});
}

/**
 * Job computeDt called @7.0 in executeTimeLoopN method.
 * In variables: deltatCfl, deltatj, stopTime, t_n
 * Out variables: deltat
 */
void Glace2dModule::computeDt()
{
	Real reduction0(numeric_limits<double>::max());
	ENUMERATE_CELL(jCells, allCells())
	{
		reduction0 = glace2dfreefuncs::minR0(reduction0, m_deltatj[jCells]);
	}
	m_deltat = std::min((m_deltatCfl * reduction0), (options()->stopTime() - m_t_n));
	m_global_deltat = m_deltat;
}

/**
 * Job computeBoundaryConditions called @8.0 in executeTimeLoopN method.
 * In variables: Ar, b
 * Out variables: Mt, bt
 */
void Glace2dModule::computeBoundaryConditions()
{
	const Real2x2 I{Real2{1.0, 0.0}, Real2{0.0, 1.0}};
	arcaneParallelForeach(NodeGroup(m_mesh->getGroup("TopNodes")), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rTopNodes, view)
		{
			const auto rId(rTopNodes.asItemLocalId());
			const auto rNodes(rId);
			const Real2 N{0.0, 1.0};
			const Real2x2 NxN(Real2x2(glace2dfreefuncs::tensProduct(N, N)));
			const Real2x2 IcP(Real2x2(glace2dfreefuncs::operatorSub(I, NxN)));
			m_bt[rNodes] = Real2(glace2dfreefuncs::matVectProduct(IcP, m_b[rNodes]));
			m_Mt[rNodes] = Real2x2(glace2dfreefuncs::operatorAdd(Real2x2(glace2dfreefuncs::operatorMult(IcP, (Real2x2(glace2dfreefuncs::operatorMult(m_Ar[rNodes], IcP))))), Real2x2(glace2dfreefuncs::operatorMult(NxN, glace2dfreefuncs::trace(m_Ar[rNodes])))));
		}
	});
	arcaneParallelForeach(NodeGroup(m_mesh->getGroup("BottomNodes")), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rBottomNodes, view)
		{
			const auto rId(rBottomNodes.asItemLocalId());
			const auto rNodes(rId);
			const Real2 N{0.0, -1.0};
			const Real2x2 NxN(Real2x2(glace2dfreefuncs::tensProduct(N, N)));
			const Real2x2 IcP(Real2x2(glace2dfreefuncs::operatorSub(I, NxN)));
			m_bt[rNodes] = Real2(glace2dfreefuncs::matVectProduct(IcP, m_b[rNodes]));
			m_Mt[rNodes] = Real2x2(glace2dfreefuncs::operatorAdd(Real2x2(glace2dfreefuncs::operatorMult(IcP, (Real2x2(glace2dfreefuncs::operatorMult(m_Ar[rNodes], IcP))))), Real2x2(glace2dfreefuncs::operatorMult(NxN, glace2dfreefuncs::trace(m_Ar[rNodes])))));
		}
	});
	arcaneParallelForeach(NodeGroup(m_mesh->getGroup("LeftNodes")), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rLeftNodes, view)
		{
			const auto rId(rLeftNodes.asItemLocalId());
			const auto rNodes(rId);
			for (Int32 i1=0; i1<2; i1++)
			{
				for (Int32 i2=0; i2<2; i2++)
				{
					m_Mt[rNodes][i1][i2] = I[i1][i2];
				}
			}
			m_bt[rNodes] = Real2{0.0, 0.0};
		}
	});
	arcaneParallelForeach(NodeGroup(m_mesh->getGroup("RightNodes")), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rRightNodes, view)
		{
			const auto rId(rRightNodes.asItemLocalId());
			const auto rNodes(rId);
			for (Int32 i1=0; i1<2; i1++)
			{
				for (Int32 i2=0; i2<2; i2++)
				{
					m_Mt[rNodes][i1][i2] = I[i1][i2];
				}
			}
			m_bt[rNodes] = Real2{0.0, 0.0};
		}
	});
}

/**
 * Job computeBt called @8.0 in executeTimeLoopN method.
 * In variables: b
 * Out variables: bt
 */
void Glace2dModule::computeBt()
{
	arcaneParallelForeach(NodeGroup(m_mesh->getGroup("InnerNodes")), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rInnerNodes, view)
		{
			const auto rId(rInnerNodes.asItemLocalId());
			const auto rNodes(rId);
			for (Int32 i1=0; i1<2; i1++)
			{
				m_bt[rNodes][i1] = m_b[rNodes][i1];
			}
		}
	});
}

/**
 * Job computeMt called @8.0 in executeTimeLoopN method.
 * In variables: Ar
 * Out variables: Mt
 */
void Glace2dModule::computeMt()
{
	arcaneParallelForeach(NodeGroup(m_mesh->getGroup("InnerNodes")), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rInnerNodes, view)
		{
			const auto rId(rInnerNodes.asItemLocalId());
			const auto rNodes(rId);
			for (Int32 i1=0; i1<2; i1++)
			{
				for (Int32 i2=0; i2<2; i2++)
				{
					m_Mt[rNodes][i1][i2] = m_Ar[rNodes][i1][i2];
				}
			}
		}
	});
}

/**
 * Job computeTn called @8.0 in executeTimeLoopN method.
 * In variables: deltat, t_n
 * Out variables: t_nplus1
 */
void Glace2dModule::computeTn()
{
	m_t_nplus1 = m_t_n + m_deltat;
}

/**
 * Job computeU called @9.0 in executeTimeLoopN method.
 * In variables: Mt, bt
 * Out variables: ur
 */
void Glace2dModule::computeU()
{
	arcaneParallelForeach(allNodes(), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rNodes, view)
		{
			m_ur[rNodes] = Real2(glace2dfreefuncs::matVectProduct(Real2x2(glace2dfreefuncs::inverse(m_Mt[rNodes])), m_bt[rNodes]));
		}
	});
}

/**
 * Job computeFjr called @10.0 in executeTimeLoopN method.
 * In variables: Ajr, C, p, uj_n, ur
 * Out variables: F
 */
void Glace2dModule::computeFjr()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rId(nodesOfCellJ[rNodesOfCellJ]);
					const auto rNodes(rId);
					m_F[jCells][rNodesOfCellJ] = Real2(glace2dfreefuncs::operatorAdd(Real2(glace2dfreefuncs::operatorMult(m_p[jCells], m_C[jCells][rNodesOfCellJ])), Real2(glace2dfreefuncs::matVectProduct(m_Ajr[jCells][rNodesOfCellJ], (Real2(glace2dfreefuncs::operatorSub(m_uj_n[jCells], m_ur[rNodes])))))));
				}
			}
		}
	});
}

/**
 * Job computeXn called @10.0 in executeTimeLoopN method.
 * In variables: X_n, deltat, ur
 * Out variables: X_nplus1
 */
void Glace2dModule::computeXn()
{
	arcaneParallelForeach(allNodes(), [&](NodeVectorView view)
	{
		ENUMERATE_NODE(rNodes, view)
		{
			m_X_nplus1[rNodes] = Real2(glace2dfreefuncs::operatorAdd(m_X_n[rNodes], Real2(glace2dfreefuncs::operatorMult(m_deltat, m_ur[rNodes]))));
		}
	});
}

/**
 * Job computeEn called @11.0 in executeTimeLoopN method.
 * In variables: E_n, F, deltat, m, ur
 * Out variables: E_nplus1
 */
void Glace2dModule::computeEn()
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
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					const auto rId(nodesOfCellJ[rNodesOfCellJ]);
					const auto rNodes(rId);
					reduction0 = glace2dfreefuncs::sumR0(reduction0, glace2dfreefuncs::dot(m_F[jCells][rNodesOfCellJ], m_ur[rNodes]));
				}
			}
			m_E_nplus1[jCells] = m_E_n[jCells] - (m_deltat / m_m[jCells]) * reduction0;
		}
	});
}

/**
 * Job computeUn called @11.0 in executeTimeLoopN method.
 * In variables: F, deltat, m, uj_n
 * Out variables: uj_nplus1
 */
void Glace2dModule::computeUn()
{
	arcaneParallelForeach(allCells(), [&](CellVectorView view)
	{
		ENUMERATE_CELL(jCells, view)
		{
			const auto jId(jCells.asItemLocalId());
			Real2 reduction0{0.0, 0.0};
			{
				const auto nodesOfCellJ(m_mesh->getNodesOfCell(jId));
				const Int32 nbNodesOfCellJ(nodesOfCellJ.size());
				for (Int32 rNodesOfCellJ=0; rNodesOfCellJ<nbNodesOfCellJ; rNodesOfCellJ++)
				{
					reduction0 = Real2(glace2dfreefuncs::sumR1(reduction0, m_F[jCells][rNodesOfCellJ]));
				}
			}
			m_uj_nplus1[jCells] = Real2(glace2dfreefuncs::operatorSub(m_uj_n[jCells], Real2(glace2dfreefuncs::operatorMult((m_deltat / m_m[jCells]), reduction0))));
		}
	});
}

ARCANE_REGISTER_MODULE_GLACE2D(Glace2dModule);
