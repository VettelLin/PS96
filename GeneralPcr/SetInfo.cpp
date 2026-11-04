// 【交接】 GeneralPcr\SetInfo.cpp
// 作用：SetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSetInfo。
#include "StdAfx.h"
#include "SetInfo.h"


// 函数 CSetInfo::CSetInfo
// 作用：执行CSetInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSetInfo::CSetInfo(void)
{
	m_eSamSortWay = ESSW_HORI;
	m_eSamSortDirection = ESSD_POSITIVE;
}

// 函数 CSetInfo::~CSetInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSetInfo::~CSetInfo(void)
{

}

// 函数 CSetInfo::CSetInfo
// 作用：执行CSetInfo。
// 参数：setInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSetInfo::CSetInfo(const CSetInfo& setInfo)
{
	m_eSamSortWay = setInfo.m_eSamSortWay;
	m_eSamSortDirection = setInfo.m_eSamSortDirection;
}

void CSetInfo::operator=(const CSetInfo& setInfo)
{
	m_eSamSortWay = setInfo.m_eSamSortWay;
	m_eSamSortDirection = setInfo.m_eSamSortDirection;
}
