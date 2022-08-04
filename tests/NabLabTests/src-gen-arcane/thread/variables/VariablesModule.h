/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __VARIABLESMODULE_H_
#define __VARIABLESMODULE_H_

#include <arcane/utils/NumArray.h>
#include <arcane/datatype/RealArrayVariant.h>
#include <arcane/datatype/RealArray2Variant.h>
#include "Variables_axl.h"
#include "CartesianMesh2D.h"

using namespace Arcane;

/*** Free functions **********************************************************/

namespace variablesfreefuncs
{
	bool assertEquals(Int32 expected, Int32 actual);
	bool assertEquals(RealArrayVariant expected, RealArrayVariant actual);
	bool assertEquals(Real expected, Real actual);
	RealArrayVariant operatorAdd(RealArrayVariant a, RealArrayVariant b);
}

/*** Module/Service **********************************************************/

class VariablesModule
: public ArcaneVariablesObject
{
public:
	VariablesModule(const ModuleBuildInfo& mbi);
	~VariablesModule() {}

	// entry points
	virtual void init() override;

	VersionInfo versionInfo() const override { return VersionInfo(1, 0, 0); }

public:
	// jobs
	virtual void dynamicVecInitialization();
	virtual void varVecInitialization();
	virtual void oracle();

private:
	// mesh attributes
	CartesianMesh2D* m_mesh;

	// other attributes
	static constexpr Real m_maxTime = 0.1;
	static constexpr Int32 m_maxIter = 500;
	static constexpr Real m_delta_t = 1.0;
	static constexpr Real m_t = 0.0;
	Real2 m_optVect3;
	static constexpr Int32 m_constexprDim = 2;
	static constexpr Real2 m_constexprVec = Real2{1.1, 1.1};
	Real2 m_varVec;
	Int32 m_checkDynamicDim;
	NumArray<Real,1> m_dynamicVec;
};

#endif
