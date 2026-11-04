// 【交接】 GeneralPcr\AxisMaxMinInfo.cpp
// 作用：AxisMaxMinInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CAxisMaxMinInfo。
#include "StdAfx.h"
#include "AxisMaxMinInfo.h"


// 函数 CAxisMaxMinInfo::CAxisMaxMinInfo
// 作用：执行CAxisMaxMinInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisMaxMinInfo::CAxisMaxMinInfo(void)
{
	m_dXMax = 0;
	m_dXMin = 40;
	m_dYMax = 0;
	m_dYMin = 1;
}


// 函数 CAxisMaxMinInfo::~CAxisMaxMinInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisMaxMinInfo::~CAxisMaxMinInfo(void)
{

}

// 函数 CAxisMaxMinInfo::CAxisMaxMinInfo
// 作用：执行CAxisMaxMinInfo。
// 参数：axisMaxMinInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisMaxMinInfo::CAxisMaxMinInfo(const CAxisMaxMinInfo& axisMaxMinInfo)
{
	m_dXMax = axisMaxMinInfo.m_dXMax;
	m_dXMin = axisMaxMinInfo.m_dXMin;
	m_dYMax = axisMaxMinInfo.m_dYMax;
	m_dYMin = axisMaxMinInfo.m_dYMin;
}

void CAxisMaxMinInfo::operator=(const CAxisMaxMinInfo& axisMaxMinInfo)
{
	m_dXMax = axisMaxMinInfo.m_dXMax;
	m_dXMin = axisMaxMinInfo.m_dXMin;
	m_dYMax = axisMaxMinInfo.m_dYMax;
	m_dYMin = axisMaxMinInfo.m_dYMin;
}
