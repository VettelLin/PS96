// 【交接】 GeneralPcr\TubeChanEditInfo.cpp
// 作用：TubeChanEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTubeChanEditInfo、_T、GetBeAllTubeSameSet。
#include "StdAfx.h"
#include "TubeChanEditInfo.h"


// 函数 CTubeChanEditInfo::CTubeChanEditInfo
// 作用：执行CTubeChanEditInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CTubeChanEditInfo::CTubeChanEditInfo(void)
{
	m_iRowId = -1;
	m_iColId = -1;
	m_bChecked = FALSE;
	m_strData = _T("");
	m_clrData = 255;
	m_dData = 0.0;
	m_iDpd = 4;
}

// 函数 CTubeChanEditInfo::~CTubeChanEditInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTubeChanEditInfo::~CTubeChanEditInfo(void)
{
}

// 函数 CTubeChanEditInfo::CTubeChanEditInfo
// 作用：执行CTubeChanEditInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTubeChanEditInfo::CTubeChanEditInfo(const CTubeChanEditInfo& info)
{
	m_iRowId = info.m_iRowId;
	m_iColId = info.m_iColId;
	m_bChecked = info.m_bChecked;
	m_dData = info.m_dData;
	m_strData = info.m_strData;
	m_clrData = info.m_clrData;
	m_iDpd = info.m_iDpd;
	return;
}

void CTubeChanEditInfo::operator=(const CTubeChanEditInfo& info)
{
	m_iRowId = info.m_iRowId;
	m_iColId = info.m_iColId;
	m_dData = info.m_dData;
	m_bChecked = info.m_bChecked;
	m_strData = info.m_strData;
	m_clrData = info.m_clrData;
	m_iDpd = info.m_iDpd;
	return;
}

// 函数 CTubeChanEditInfo::GetBeAllTubeSameSet
// 作用：读取GetBeAllTubeSameSet。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeChanEditInfo::GetBeAllTubeSameSet()
{
	//return (2 == m_iColId || 4 == m_iColId);
	return 2 == m_iColId;
}
