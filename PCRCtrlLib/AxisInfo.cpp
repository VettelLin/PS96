// 【交接】 PCRCtrlLib\AxisInfo.cpp
// 作用：AxisInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CAxisInfo、CalculateLogValaue、log10。
#include "StdAfx.h"

#include<math.h>
#include "AxisInfo.h"

// 函数 CAxisInfo::CAxisInfo
// 作用：执行CAxisInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisInfo::CAxisInfo(void)
{
	m_dXMin = 0;
	m_dXMax = 1;
	m_dYMin = 0;
	m_dYMax = 1;
}

// 函数 CAxisInfo::~CAxisInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisInfo::~CAxisInfo(void)
{
	
}

// 函数 CAxisInfo::CAxisInfo
// 作用：执行CAxisInfo。
// 参数：axisInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisInfo::CAxisInfo(const CAxisInfo& axisInfo)
{
	m_dXMin = axisInfo.m_dXMin;
	m_dXMax = axisInfo.m_dXMax;
	m_dYMin = axisInfo.m_dYMin;
	m_dYMax = axisInfo.m_dYMax;
}

void CAxisInfo::operator=(const CAxisInfo& axisInfo)
{
	m_dXMin = axisInfo.m_dXMin;
	m_dXMax = axisInfo.m_dXMax;
	m_dYMin = axisInfo.m_dYMin;
	m_dYMax = axisInfo.m_dYMax;
}

BOOL CAxisInfo::operator==(const CAxisInfo& axisInfo)
{
	return m_dXMin == axisInfo.m_dXMin &&
		   m_dXMax == axisInfo.m_dXMax && 
		   m_dYMin == axisInfo.m_dYMin && 
		   m_dYMax == axisInfo.m_dYMax;
}

// 函数 CAxisInfo::CalculateLogValaue
// 作用：计算CalculateLogValaue。
// 参数：无。
// 返回：返回 CAxisInfo。
// 过程：函数里会调用 log10。
CAxisInfo CAxisInfo::CalculateLogValaue()
{
	CAxisInfo axisInfo;
	if(m_dXMin <= 0)
	{
		axisInfo.m_dXMin = 0;
	}
	else
	{
		axisInfo.m_dXMin = log10(m_dXMin);
	}
	
	if(m_dXMax <= 0)
	{
		axisInfo.m_dXMax = axisInfo.m_dXMin + 1;
	}
	else
	{
		axisInfo.m_dXMax = log10(m_dXMax);
	}

	if(m_dYMin <= 0)
	{
		axisInfo.m_dYMin = 0;
	}
	else
	{
		axisInfo.m_dYMin = log10(m_dYMin);
	}
	
	if(m_dYMax <= 0)
	{
		axisInfo.m_dYMax = axisInfo.m_dYMin + 1;
	}
	else
	{
		axisInfo.m_dYMax = log10(m_dYMax);
	}
	
	return axisInfo;
}
