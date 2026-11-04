// 【交接】 GeneralPcr\SegDotPosInfo.cpp
// 作用：SegDotPosInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSegDotPosInfo、BeValidStepEmptyPos、BeValidSegmentEmptyPos。
#include "StdAfx.h"
#include "SegDotPosInfo.h"


// 函数 CSegDotPosInfo::CSegDotPosInfo
// 作用：执行CSegDotPosInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegDotPosInfo::CSegDotPosInfo(void)
{
	m_seg = -1;
	m_step = -1; 
	m_eDotPosType = EDP_NONE;
}


// 函数 CSegDotPosInfo::~CSegDotPosInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegDotPosInfo::~CSegDotPosInfo(void)
{
}

// 函数 CSegDotPosInfo::CSegDotPosInfo
// 作用：执行CSegDotPosInfo。
// 参数：segDotPosInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegDotPosInfo::CSegDotPosInfo(const CSegDotPosInfo& segDotPosInfo)
{
	m_seg = segDotPosInfo.m_seg;
	m_step = segDotPosInfo.m_step;
	m_eDotPosType = segDotPosInfo.m_eDotPosType;
	m_rcItem = segDotPosInfo.m_rcItem;
	m_pt = segDotPosInfo.m_pt;
}

void CSegDotPosInfo::operator=(const CSegDotPosInfo& segDotPosInfo)
{
	m_seg = segDotPosInfo.m_seg;
	m_step = segDotPosInfo.m_step;
	m_eDotPosType = segDotPosInfo.m_eDotPosType;
	m_rcItem = segDotPosInfo.m_rcItem;
	m_pt = segDotPosInfo.m_pt;
}

// 函数 CSegDotPosInfo::BeValidStepEmptyPos
// 作用：判断BeValidStepEmptyPos是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSegDotPosInfo::BeValidStepEmptyPos()
{
	return (-1 != m_seg && -1 != m_step && EDP_NONE == m_eDotPosType);
}

// 函数 CSegDotPosInfo::BeValidSegmentEmptyPos
// 作用：判断BeValidSegmentEmptyPos是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSegDotPosInfo::BeValidSegmentEmptyPos()
{
	return (-1 != m_seg && -1 == m_step && EDP_SEGEMPTY == m_eDotPosType);
}
