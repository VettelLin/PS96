// 【交接】 GeneralPcr\PlateInfo.cpp
// 作用：PlateInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CPlateInfo。
#include "StdAfx.h"
#include "PlateInfo.h"


// 函数 CPlateInfo::CPlateInfo
// 作用：执行CPlateInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPlateInfo::CPlateInfo(void)
{
	m_bSelected = FALSE;
}


// 函数 CPlateInfo::~CPlateInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPlateInfo::~CPlateInfo(void)
{
	
}

// 函数 CPlateInfo::CPlateInfo
// 作用：执行CPlateInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPlateInfo::CPlateInfo(const CPlateInfo& info)
{
	m_bSelected = info.m_bSelected;
}

void CPlateInfo::operator=(const CPlateInfo& info)
{
	m_bSelected = info.m_bSelected;
}
