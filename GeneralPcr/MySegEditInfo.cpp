// 【交接】 GeneralPcr\MySegEditInfo.cpp
// 作用：MySegEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMySegEditInfo、_T。
#include "StdAfx.h"
#include "MySegEditInfo.h"


// 函数 CMySegEditInfo::CMySegEditInfo
// 作用：执行CMySegEditInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CMySegEditInfo::CMySegEditInfo(void)
{
	m_strSegName = _T("");
	m_cycleNum = 0;
	m_bMeltSeg = FALSE;
}

// 函数 CMySegEditInfo::~CMySegEditInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMySegEditInfo::~CMySegEditInfo(void)
{

}

// 函数 CMySegEditInfo::CMySegEditInfo
// 作用：执行CMySegEditInfo。
// 参数：segEditInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMySegEditInfo::CMySegEditInfo(const CMySegEditInfo& segEditInfo)
{
	m_strSegName = segEditInfo.m_strSegName;
	m_cycleNum = segEditInfo.m_cycleNum;
	m_bMeltSeg = segEditInfo.m_bMeltSeg;
}

void CMySegEditInfo::operator=(const CMySegEditInfo& segEditInfo)
{
	m_strSegName = segEditInfo.m_strSegName;
	m_cycleNum = segEditInfo.m_cycleNum;
	m_bMeltSeg = segEditInfo.m_bMeltSeg;
}



