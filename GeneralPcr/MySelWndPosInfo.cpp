// 【交接】 GeneralPcr\MySelWndPosInfo.cpp
// 作用：MySelWndPosInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMySelWndDotPosInfo、BeSameRow、Clear。
#include "StdAfx.h"
#include "MySelWndPosInfo.h"

// 函数 CMySelWndDotPosInfo::CMySelWndDotPosInfo
// 作用：执行CMySelWndDotPosInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMySelWndDotPosInfo::CMySelWndDotPosInfo(void)
{
	m_eDotPosType = EMSWDPT_NONE;
	m_rowId = -1;
}

// 函数 CMySelWndDotPosInfo::~CMySelWndDotPosInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMySelWndDotPosInfo::~CMySelWndDotPosInfo(void)
{

}

// 函数 CMySelWndDotPosInfo::CMySelWndDotPosInfo
// 作用：执行CMySelWndDotPosInfo。
// 参数：dotPosInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMySelWndDotPosInfo::CMySelWndDotPosInfo(const CMySelWndDotPosInfo& dotPosInfo)
{
	m_eDotPosType = dotPosInfo.m_eDotPosType;
	m_rowId = dotPosInfo.m_rowId;
	m_pt = dotPosInfo.m_pt;
}

void CMySelWndDotPosInfo::operator=(const CMySelWndDotPosInfo& dotPosInfo)
{
	m_eDotPosType = dotPosInfo.m_eDotPosType;
	m_rowId = dotPosInfo.m_rowId;
	m_pt = dotPosInfo.m_pt;
}

BOOL CMySelWndDotPosInfo::operator==(const CMySelWndDotPosInfo& dotPosInfo)
{
	return m_eDotPosType == dotPosInfo.m_eDotPosType && 
			m_rowId == dotPosInfo.m_rowId;
}

// 函数 CMySelWndDotPosInfo::BeSameRow
// 作用：判断BeSameRow是否成立。
// 参数：dotPosInfo。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySelWndDotPosInfo::BeSameRow(CMySelWndDotPosInfo& dotPosInfo)
{
	if(EMSWDPT_NONE == dotPosInfo.m_eDotPosType)
	{
		return FALSE;
	}
	if(-1 == m_rowId)
	{
		return FALSE;
	}
	return m_rowId == dotPosInfo.m_rowId;
}

// 函数 CMySelWndDotPosInfo::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMySelWndDotPosInfo::Clear()
{
	m_rowId = -1;
	m_pt.x = 0;
	m_pt.y = 0;
}
