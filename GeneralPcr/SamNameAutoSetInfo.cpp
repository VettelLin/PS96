// 【交接】 GeneralPcr\SamNameAutoSetInfo.cpp
// 作用：SamNameAutoSetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSamNameAutoSetInfo、_T。
#include "StdAfx.h"
#include "SamNameAutoSetInfo.h"


// 函数 CSamNameAutoSetInfo::CSamNameAutoSetInfo
// 作用：执行CSamNameAutoSetInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CSamNameAutoSetInfo::CSamNameAutoSetInfo(void)
{
	m_strPrjName = _T("");
	m_strSamIdPrefix = _T("");
	m_startValue = 1;
	m_interval = 1;
	m_bitNum = 1; 
	m_eSamSortWay = ESSW_HORI;
}

// 函数 CSamNameAutoSetInfo::~CSamNameAutoSetInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSamNameAutoSetInfo::~CSamNameAutoSetInfo(void)
{

}

// 函数 CSamNameAutoSetInfo::CSamNameAutoSetInfo
// 作用：执行CSamNameAutoSetInfo。
// 参数：samIdAutoSetInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSamNameAutoSetInfo::CSamNameAutoSetInfo(const CSamNameAutoSetInfo& samIdAutoSetInfo)
{
	m_strPrjName = samIdAutoSetInfo.m_strPrjName;
	m_strSamIdPrefix = samIdAutoSetInfo.m_strSamIdPrefix;
	m_startValue = samIdAutoSetInfo.m_startValue;
	m_interval = samIdAutoSetInfo.m_interval;
	m_bitNum = samIdAutoSetInfo.m_bitNum;
	m_eSamSortWay = samIdAutoSetInfo.m_eSamSortWay;
}

void CSamNameAutoSetInfo::operator=(const CSamNameAutoSetInfo& samIdAutoSetInfo)
{
	m_strPrjName = samIdAutoSetInfo.m_strPrjName;
	m_strSamIdPrefix = samIdAutoSetInfo.m_strSamIdPrefix;
	m_startValue = samIdAutoSetInfo.m_startValue;
	m_interval = samIdAutoSetInfo.m_interval;
	m_bitNum = samIdAutoSetInfo.m_bitNum;
	m_eSamSortWay = samIdAutoSetInfo.m_eSamSortWay;
}
