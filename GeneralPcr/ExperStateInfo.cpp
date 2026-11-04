// 【交接】 GeneralPcr\ExperStateInfo.cpp
// 作用：ExperStateInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CExperStateInfo、_T。
#include "StdAfx.h"
#include "ExperStateInfo.h"


// 函数 CExperStateInfo::CExperStateInfo
// 作用：执行CExperStateInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CExperStateInfo::CExperStateInfo(void)
{
	m_eInstruConnectState = EICS_NONE;
	m_eExperType = EET_NONE;

	m_strModel = _T("");
	m_strExperName = _T("");	
	m_strRemainTime = _T("");	
	m_strExperStartTime = _T("");	
	m_dProgress = 0;
	m_dExperTem = -1;
}

// 函数 CExperStateInfo::~CExperStateInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExperStateInfo::~CExperStateInfo(void)
{

}

// 函数 CExperStateInfo::CExperStateInfo
// 作用：执行CExperStateInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExperStateInfo::CExperStateInfo(const CExperStateInfo& info)
{
	m_eInstruConnectState = info.m_eInstruConnectState;
	m_eExperType = info.m_eExperType;

	m_strModel = info.m_strModel;
	m_strExperName = info.m_strExperName;	
	m_strRemainTime = info.m_strRemainTime;	
	m_strExperStartTime = info.m_strExperStartTime;	
	m_dProgress = info.m_dProgress;
	m_dExperTem = info.m_dExperTem;
}

void CExperStateInfo::operator=(const CExperStateInfo& info)
{
	m_eInstruConnectState = info.m_eInstruConnectState;
	m_eExperType = info.m_eExperType;

	m_strModel = info.m_strModel;
	m_strExperName = info.m_strExperName;	
	m_strRemainTime = info.m_strRemainTime;	
	m_strExperStartTime = info.m_strExperStartTime;	
	m_dProgress = info.m_dProgress;
	m_dExperTem = info.m_dExperTem;
}





