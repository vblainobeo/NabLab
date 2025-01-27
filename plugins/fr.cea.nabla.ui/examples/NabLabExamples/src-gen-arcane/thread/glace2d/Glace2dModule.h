/* DO NOT EDIT THIS FILE - it is machine generated */

#ifndef __GLACE2DMODULE_H_
#define __GLACE2DMODULE_H_

#include <arcane/utils/NumArray.h>
#include <arcane/datatype/RealArrayVariant.h>
#include <arcane/datatype/RealArray2Variant.h>
#include "Glace2d_axl.h"
#include "CartesianMesh2D.h"

using namespace Arcane;

/*** Free functions **********************************************************/

namespace glace2dfreefuncs
{
	Real det(RealArray2Variant a);
	RealArrayVariant perp(RealArrayVariant a);
	Real dot(RealArrayVariant a, RealArrayVariant b);
	Real norm(RealArrayVariant a);
	RealArray2Variant tensProduct(RealArrayVariant a, RealArrayVariant b);
	RealArrayVariant matVectProduct(RealArray2Variant a, RealArrayVariant b);
	Real trace(RealArray2Variant a);
	RealArray2Variant inverse(RealArray2Variant a);
	RealArrayVariant sumR1(RealArrayVariant a, RealArrayVariant b);
	Real sumR0(Real a, Real b);
	RealArray2Variant sumR2(RealArray2Variant a, RealArray2Variant b);
	Real minR0(Real a, Real b);
	RealArrayVariant operatorAdd(RealArrayVariant a, RealArrayVariant b);
	RealArray2Variant operatorAdd(RealArray2Variant a, RealArray2Variant b);
	RealArrayVariant operatorMult(Real a, RealArrayVariant b);
	RealArrayVariant operatorSub(RealArrayVariant a, RealArrayVariant b);
	RealArray2Variant operatorMult(Real a, RealArray2Variant b);
	RealArray2Variant operatorSub(RealArray2Variant a, RealArray2Variant b);
	RealArray2Variant operatorMult(RealArray2Variant a, RealArray2Variant b);
	RealArray2Variant operatorMult(RealArray2Variant a, Real b);
}

/*** Module/Service **********************************************************/

class Glace2dModule
: public ArcaneGlace2dObject
{
public:
	Glace2dModule(const ModuleBuildInfo& mbi);
	~Glace2dModule() {}

	// entry points
	virtual void init() override;
	virtual void executeTimeLoopN() override;

	VersionInfo versionInfo() const override { return VersionInfo(1, 0, 0); }

public:
	// jobs
	virtual void computeCjr();
	virtual void computeInternalEnergy();
	virtual void iniCjrIc();
	virtual void iniTime();
	virtual void computeLjr();
	virtual void computeV();
	virtual void initialize();
	virtual void setUpTimeLoopN();
	virtual void computeDensity();
	virtual void computeEOSp();
	virtual void computeEOSc();
	virtual void computeAjr();
	virtual void computedeltatj();
	virtual void computeAr();
	virtual void computeBr();
	virtual void computeDt();
	virtual void computeBoundaryConditions();
	virtual void computeBt();
	virtual void computeMt();
	virtual void computeTn();
	virtual void computeU();
	virtual void computeFjr();
	virtual void computeXn();
	virtual void computeEn();
	virtual void computeUn();

private:
	// mesh attributes
	CartesianMesh2D* m_mesh;

	// other attributes
	Int32 m_lastDump;
	Int32 m_n;
	static constexpr Real m_gamma = 1.4;
	static constexpr Real m_xInterface = 0.5;
	static constexpr Real m_delta_tCfl = 0.4;
	static constexpr Real m_rho_IniZg = 1.0;
	static constexpr Real m_rho_IniZd = 0.125;
	static constexpr Real m_pIniZg = 1.0;
	static constexpr Real m_pIniZd = 0.1;
	Real m_t_n;
	Real m_t_nplus1;
	Real m_t_n0;
	Real m_delta_t;
};

#endif
