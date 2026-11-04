// 【交接】 GeneralPcr\RowColEditInfo.cpp
// 作用：RowColEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CRowColEditInfo、_T、BeValidRowCol、Clear。
#include "StdAfx.h"
#include "RowColEditInfo.h"


// 函数 CRowColEditInfo::CRowColEditInfo
// 作用：执行CRowColEditInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CRowColEditInfo::CRowColEditInfo(void)
{
	m_rowId = -1;
	m_colId = -1;
	m_strText = _T("");
	m_strNewText = _T("");
}

// 函数 CRowColEditInfo::~CRowColEditInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CRowColEditInfo::~CRowColEditInfo(void)
{

}

// 函数 CRowColEditInfo::CRowColEditInfo
// 作用：执行CRowColEditInfo。
// 参数：rowColEditInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CRowColEditInfo::CRowColEditInfo(const CRowColEditInfo& rowColEditInfo)
{
	m_rowId = rowColEditInfo.m_rowId;
	m_colId = rowColEditInfo.m_colId;
	m_strText = rowColEditInfo.m_strText;
	m_strNewText = rowColEditInfo.m_strNewText;
}

void CRowColEditInfo::operator=(const CRowColEditInfo& rowColEditInfo)
{
	m_rowId = rowColEditInfo.m_rowId;
	m_colId = rowColEditInfo.m_colId;
	m_strText = rowColEditInfo.m_strText;
	m_strNewText = rowColEditInfo.m_strNewText;
}

BOOL CRowColEditInfo::operator==(const CRowColEditInfo& rowColEditInfo)
{
	return m_rowId == rowColEditInfo.m_rowId && 
	m_colId == rowColEditInfo.m_colId;
}

// 函数 CRowColEditInfo::BeValidRowCol
// 作用：判断BeValidRowCol是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CRowColEditInfo::BeValidRowCol()
{
	if(m_rowId < 0)
	{
		return FALSE;
	}
	if(m_colId < 0)
	{
		return FALSE;
	}

	return TRUE;
}

// 函数 CRowColEditInfo::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CRowColEditInfo::Clear()
{
	m_rowId = -1;
	m_colId = -1;
}


