// 【交接】 GeneralPcr\TubeFullFluInfo.h
// 作用：TubeFullFluInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTubeFullFluInfo、BeAllAllocated、Clear。
#pragma once


#include <vector>

using namespace std;

class AFX_EXT_CLASS CTubeFullFluInfo
{
public:
	// 函数 CTubeFullFluInfo
	// 作用：执行CTubeFullFluInfo。
	// 参数：无。
	// 返回：没有返回值。
	CTubeFullFluInfo(void);
	// 函数 ~CTubeFullFluInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CTubeFullFluInfo(void);

	// 函数 BeAllAllocated
	// 作用：判断BeAllAllocated是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL BeAllAllocated();	//是否都成功申请了内存空间
	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();

public:
	vector<UINT>* m_pOriginFlu;
	vector<double>* m_pCrossTalkedFlu;
	vector<double>* m_pFilteredFlu;
	vector<double>* m_pNormalizedFlu;
	vector<double>* m_pLogNormalizedFlu;
	vector<double>* m_pDeltaRnedFlu;
	vector<double>* m_pLogDeltaRnedFlu;
	vector<double>* m_pDMeltTem;
	double* m_pCtBySecDev;	//二阶导方式计算出的Ct值
	double* m_pCtBySpline;	//插值法方式计算出的Ct值
	double* m_pSplineThreNormalize;	//插值法默认阈值(归一化)
	double* m_pLogSplineThreNorm;	//插值法对数阈值（归一化）
	double* m_pSplineThreDeltaRn;	//插值法默认阈值(DeltaRn)
	double* m_pLogSplineThreDeltaRn;	//插值法对数阈值（DeltaRn）
	BOOL* m_pBePeakCrv;	//标识是否是扩增曲线
};

