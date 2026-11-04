// 【交接】 GeneralPcr\DotPosInfo.cpp
// 作用：DotPosInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CDotPosInfo、BeSameRowCol、BeSameRow、BeSameCol、BeValidCellPos。
#include "StdAfx.h"
#include "DotPosInfo.h"


// 函数 CDotPosInfo::CDotPosInfo
// 作用：执行CDotPosInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDotPosInfo::CDotPosInfo(void)
{
	m_eDotPosType = EDT_NONE;
	m_rowId = -1;
	m_colId = -1;
}

// 函数 CDotPosInfo::~CDotPosInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDotPosInfo::~CDotPosInfo(void)
{

}

// 函数 CDotPosInfo::CDotPosInfo
// 作用：执行CDotPosInfo。
// 参数：dotPosInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDotPosInfo::CDotPosInfo(const CDotPosInfo& dotPosInfo)
{
	m_eDotPosType = dotPosInfo.m_eDotPosType;
	m_rowId = dotPosInfo.m_rowId;
	m_colId = dotPosInfo.m_colId;
	m_pt = dotPosInfo.m_pt;
}

void CDotPosInfo::operator=(const CDotPosInfo& dotPosInfo)
{
	m_eDotPosType = dotPosInfo.m_eDotPosType;
	m_rowId = dotPosInfo.m_rowId;
	m_colId = dotPosInfo.m_colId;
	m_pt = dotPosInfo.m_pt;
}

BOOL CDotPosInfo::operator==(const CDotPosInfo& dotPosInfo)
{
	return m_eDotPosType == dotPosInfo.m_eDotPosType && 
			m_rowId == dotPosInfo.m_rowId && 
			m_colId == dotPosInfo.m_colId;
}

// 函数 CDotPosInfo::BeSameRowCol
// 作用：判断BeSameRowCol是否成立。
// 参数：dotPosInfo。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CDotPosInfo::BeSameRowCol(CDotPosInfo& dotPosInfo)
{
	if(EDT_NONE == dotPosInfo.m_eDotPosType)
	{
		return FALSE;
	}
	if(-1 == m_rowId && -1 == m_colId)
	{
		return FALSE;
	}

	return m_rowId == dotPosInfo.m_rowId &&
		m_colId == dotPosInfo.m_colId;
}

// 函数 CDotPosInfo::BeSameRow
// 作用：判断BeSameRow是否成立。
// 参数：dotPosInfo。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CDotPosInfo::BeSameRow(CDotPosInfo& dotPosInfo)
{
	if(EDT_NONE == dotPosInfo.m_eDotPosType)
	{
		return FALSE;
	}
	if(-1 == m_rowId)
	{
		return FALSE;
	}
	return m_rowId == dotPosInfo.m_rowId;
}

// 函数 CDotPosInfo::BeSameCol
// 作用：判断BeSameCol是否成立。
// 参数：dotPosInfo。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CDotPosInfo::BeSameCol(CDotPosInfo& dotPosInfo)
{
	if(EDT_NONE == dotPosInfo.m_eDotPosType)
	{
		return FALSE;
	}
	if(-1 == m_colId)
	{
		return FALSE;
	}
	return m_colId == dotPosInfo.m_colId;
}

// 函数 CDotPosInfo::BeValidCellPos
// 作用：判断BeValidCellPos是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CDotPosInfo::BeValidCellPos()
{
	return EDT_BODY == m_eDotPosType && -1 != m_rowId && -1 != m_colId;
}
