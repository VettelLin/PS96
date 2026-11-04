// 【交接】 GeneralPcr\TubeFullFluInfo.cpp
// 作用：TubeFullFluInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTubeFullFluInfo、MyMulitDeletePtr、BeAllAllocated、Clear。
#include "StdAfx.h"
#include "TubeFullFluInfo.h"

// 函数 CTubeFullFluInfo::CTubeFullFluInfo
// 作用：执行CTubeFullFluInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTubeFullFluInfo::CTubeFullFluInfo(void)
{
	m_pOriginFlu = NULL;
	m_pCrossTalkedFlu = NULL;
	m_pFilteredFlu = NULL;
	m_pNormalizedFlu = NULL;
	m_pLogNormalizedFlu = NULL;
	m_pDeltaRnedFlu = NULL;
	m_pLogDeltaRnedFlu = NULL;
	m_pDMeltTem = NULL;

	m_pCtBySecDev = NULL;
	m_pCtBySpline = NULL;
	
	m_pSplineThreNormalize = NULL;
	m_pLogSplineThreNorm = NULL;
	m_pSplineThreDeltaRn = NULL;
	m_pLogSplineThreDeltaRn = NULL;

	m_pBePeakCrv = NULL;
}
 
// 函数 CTubeFullFluInfo::~CTubeFullFluInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 MyMulitDeletePtr。
CTubeFullFluInfo::~CTubeFullFluInfo(void)
{
	MyMulitDeletePtr(&m_pOriginFlu);
	MyMulitDeletePtr(&m_pCrossTalkedFlu);
	MyMulitDeletePtr(&m_pFilteredFlu);
	MyMulitDeletePtr(&m_pNormalizedFlu);
	MyMulitDeletePtr(&m_pLogNormalizedFlu);
	MyMulitDeletePtr(&m_pDeltaRnedFlu);
	MyMulitDeletePtr(&m_pLogDeltaRnedFlu);
	MyMulitDeletePtr(&m_pDMeltTem);

	MyMulitDeletePtr(&m_pCtBySecDev);
	MyMulitDeletePtr(&m_pCtBySpline);
	MyMulitDeletePtr(&m_pSplineThreNormalize);
	MyMulitDeletePtr(&m_pLogSplineThreNorm);
	MyMulitDeletePtr(&m_pSplineThreDeltaRn);
	MyMulitDeletePtr(&m_pLogSplineThreDeltaRn);
	MyMulitDeletePtr(&m_pBePeakCrv);
}

// 函数 CTubeFullFluInfo::BeAllAllocated
// 作用：判断BeAllAllocated是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeFullFluInfo::BeAllAllocated()
{
	if(NULL == m_pOriginFlu)
	{
		return FALSE;
	}
	if(NULL == m_pCrossTalkedFlu)
	{
		return FALSE;
	}
	if(NULL == m_pFilteredFlu)
	{
		return FALSE;
	}
	if(NULL == m_pNormalizedFlu)
	{
		return FALSE;
	}
	if(NULL == m_pLogNormalizedFlu)
	{
		return FALSE;
	}
	if(NULL == m_pDeltaRnedFlu)
	{
		return FALSE;
	}
	if(NULL == m_pLogDeltaRnedFlu)
	{
		return FALSE;
	}
	if(NULL == m_pDMeltTem)
	{
		return FALSE;
	}

	if(NULL == m_pCtBySecDev)
	{
		return FALSE;
	}

	if(NULL == m_pCtBySpline)
	{
		return FALSE;
	}

	if(NULL == m_pSplineThreNormalize)
	{
		return FALSE;
	}

	if(NULL == m_pLogSplineThreNorm)
	{
		return FALSE;
	}

	if(NULL == m_pSplineThreDeltaRn)
	{
		return FALSE;
	}

	if(NULL == m_pLogSplineThreDeltaRn)
	{
		return FALSE;
	}

	if(NULL == m_pBePeakCrv)
	{
		return FALSE;
	}

	return TRUE;
}

// 函数 CTubeFullFluInfo::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 MyMulitDeletePtr。
void CTubeFullFluInfo::Clear()
{
	MyMulitDeletePtr(&m_pOriginFlu);
	MyMulitDeletePtr(&m_pCrossTalkedFlu);
	MyMulitDeletePtr(&m_pFilteredFlu);
	MyMulitDeletePtr(&m_pNormalizedFlu);
	MyMulitDeletePtr(&m_pLogNormalizedFlu);
	MyMulitDeletePtr(&m_pDeltaRnedFlu);
	MyMulitDeletePtr(&m_pLogDeltaRnedFlu);
	MyMulitDeletePtr(&m_pDMeltTem);

	MyMulitDeletePtr(&m_pCtBySecDev);
	MyMulitDeletePtr(&m_pCtBySpline);
	MyMulitDeletePtr(&m_pSplineThreNormalize);
	MyMulitDeletePtr(&m_pLogSplineThreNorm);
	MyMulitDeletePtr(&m_pSplineThreDeltaRn);
	MyMulitDeletePtr(&m_pLogSplineThreDeltaRn);
	MyMulitDeletePtr(&m_pBePeakCrv);
}
