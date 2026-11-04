// 【交接】 GeneralPcr\MyStepEditInfo.cpp
// 作用：MyStepEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMyStepEditInfo、_T。
#include "StdAfx.h"
#include "MyStepEditInfo.h"


// 函数 CMyStepEditInfo::CMyStepEditInfo
// 作用：执行CMyStepEditInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CMyStepEditInfo::CMyStepEditInfo(void)
{
	m_strSegName = _T("");
	m_strStepName = _T("");
	m_fAimTem = 50.0;
	m_bSelGradient = FALSE;
	m_fGradientMaxTem = 90.0;
	m_holdSec = 10;
	m_iCollect = FALSE;
	m_fRate = 4.0;	
	m_fIncrement = 0.5;
	m_bCollectExistExceptThisStep = FALSE;
	m_bCollectAllExistExceptThisStep = FALSE;
	m_bMeltSeg = FALSE;
}

// 函数 CMyStepEditInfo::~CMyStepEditInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyStepEditInfo::~CMyStepEditInfo(void)
{
}

// 函数 CMyStepEditInfo::CMyStepEditInfo
// 作用：执行CMyStepEditInfo。
// 参数：stepEditInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyStepEditInfo::CMyStepEditInfo(const CMyStepEditInfo& stepEditInfo)
{
	m_strSegName = stepEditInfo.m_strSegName;
	m_strStepName = stepEditInfo.m_strStepName;
	m_fAimTem = stepEditInfo.m_fAimTem;
	m_bSelGradient = stepEditInfo.m_bSelGradient;
	m_fGradientMaxTem = stepEditInfo.m_fGradientMaxTem;
	m_holdSec = stepEditInfo.m_holdSec;
	m_iCollect = stepEditInfo.m_iCollect;
	m_fRate = stepEditInfo.m_fRate;	
	m_fIncrement = stepEditInfo.m_fIncrement;
	m_bCollectExistExceptThisStep = stepEditInfo.m_bCollectExistExceptThisStep;
	m_bCollectAllExistExceptThisStep = stepEditInfo.m_bCollectAllExistExceptThisStep;
	m_bMeltSeg = stepEditInfo.m_bMeltSeg;
}

void CMyStepEditInfo::operator=(const CMyStepEditInfo& stepEditInfo)
{
	m_strSegName = stepEditInfo.m_strSegName;
	m_strStepName = stepEditInfo.m_strStepName;
	m_fAimTem = stepEditInfo.m_fAimTem;
	m_bSelGradient = stepEditInfo.m_bSelGradient;
	m_fGradientMaxTem = stepEditInfo.m_fGradientMaxTem;
	m_holdSec = stepEditInfo.m_holdSec;
	m_iCollect = stepEditInfo.m_iCollect;
	m_fRate = stepEditInfo.m_fRate;	
	m_fIncrement = stepEditInfo.m_fIncrement;
	m_bCollectExistExceptThisStep = stepEditInfo.m_bCollectExistExceptThisStep;
	m_bCollectAllExistExceptThisStep = stepEditInfo.m_bCollectAllExistExceptThisStep;
	m_bMeltSeg = stepEditInfo.m_bMeltSeg;
}


