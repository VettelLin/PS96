// 【交接】 GeneralPcr\RowInfo.cpp
// 作用：RowInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CRowInfo。
#include "StdAfx.h"
#include "RowInfo.h"


// 函数 CRowInfo::CRowInfo
// 作用：执行CRowInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CRowInfo::CRowInfo(void)
{
	m_rowH = 28;
	m_bSelected = FALSE;
	m_bDisabled = FALSE;
}


// 函数 CRowInfo::~CRowInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CRowInfo::~CRowInfo(void)
{
}

// 函数 CRowInfo::CRowInfo
// 作用：执行CRowInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CRowInfo::CRowInfo(const CRowInfo& info)
{
	m_rowH = info.m_rowH;
	m_bSelected = info.m_bSelected;
	m_bDisabled = info.m_bDisabled;
}

void CRowInfo::operator=(const CRowInfo& info)
{
	m_rowH = info.m_rowH;
	m_bSelected = info.m_bSelected;
	m_bDisabled = info.m_bDisabled;
}

