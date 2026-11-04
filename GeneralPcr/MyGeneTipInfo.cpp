// 【交接】 GeneralPcr\MyGeneTipInfo.cpp
// 作用：MyGeneTipInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMyGeneTipInfo、_T。
#include "StdAfx.h"
#include "MyGeneTipInfo.h"


// 函数 CMyGeneTipInfo::CMyGeneTipInfo
// 作用：执行CMyGeneTipInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CMyGeneTipInfo::CMyGeneTipInfo(void)
{
	m_pParent = NULL;
	m_strTipInfo = _T("");
	m_eGeneTipType = EGTT_NORMAL;
}

// 函数 CMyGeneTipInfo::~CMyGeneTipInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyGeneTipInfo::~CMyGeneTipInfo(void)
{

}

// 函数 CMyGeneTipInfo::CMyGeneTipInfo
// 作用：执行CMyGeneTipInfo。
// 参数：geneTipInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyGeneTipInfo::CMyGeneTipInfo(const CMyGeneTipInfo& geneTipInfo)
{
	m_pParent = geneTipInfo.m_pParent;
	m_strTipInfo = geneTipInfo.m_strTipInfo;
	m_eGeneTipType = geneTipInfo.m_eGeneTipType;
}

void CMyGeneTipInfo::operator=(const CMyGeneTipInfo& geneTipInfo)
{
	m_pParent = geneTipInfo.m_pParent;
	m_strTipInfo = geneTipInfo.m_strTipInfo;
	m_eGeneTipType = geneTipInfo.m_eGeneTipType;
}



