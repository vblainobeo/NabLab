/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __EXPLICITHEATEQUATIONMODULE_H_
#define __EXPLICITHEATEQUATIONMODULE_H_

#include <arcane/utils/NumArray.h>
#include <arcane/datatype/RealArrayVariant.h>
#include <arcane/datatype/RealArray2Variant.h>
#include "ExplicitHeatEquation_axl.h"
#include "CartesianMesh2D.h"

using namespace Arcane;

/*** Free functions **********************************************************/

namespace explicitheatequationfreefuncs
{
	Real norm(RealArrayVariant a);
	Real dot(RealArrayVariant a, RealArrayVariant b);
	Real det(RealArrayVariant a, RealArrayVariant b);
	RealArrayVariant sumR1(RealArrayVariant a, RealArrayVariant b);
	Real minR0(Real a, Real b);
	Real sumR0(Real a, Real b);
	Real prodR0(Real a, Real b);
	RealArrayVariant operatorAdd(RealArrayVariant a, RealArrayVariant b);
	RealArrayVariant operatorMult(Real a, RealArrayVariant b);
	RealArrayVariant operatorSub(RealArrayVariant a, RealArrayVariant b);
}

/*** Module/Service **********************************************************/

class ExplicitHeatEquationModule
: public ArcaneExplicitHeatEquationObject
{
public:
	ExplicitHeatEquationModule(const ModuleBuildInfo& mbi);
	~ExplicitHeatEquationModule() {}

	// entry points
	virtual void init() override;
	virtual void executeTimeLoopN() override;

	VersionInfo versionInfo() const override { return VersionInfo(1, 0, 0); }

public:
	// jobs
	virtual void computeFaceLength();
	virtual void computeTn();
	virtual void computeV();
	virtual void initD();
	virtual void initTime();
	virtual void initXc();
	virtual void updateU();
	virtual void computeDeltaTn();
	virtual void computeFaceConductivity();
	virtual void initU();
	virtual void setUpTimeLoopN();
	virtual void computeAlphaCoeff();

private:
	// mesh attributes
	CartesianMesh2D* m_mesh;

	// other attributes
	Int32 m_lastDump;
	Int32 m_n;
	static constexpr Real m_u0 = 1.0;
	static constexpr Real2 m_vectOne = {1.0, 1.0};
	Real m_delta_t;
	Real m_t_n;
	Real m_t_nplus1;
	Real m_t_n0;
};

#endif
