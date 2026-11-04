// 【交接】 GeneralPcr\CaretInfo.cpp
// 作用：CaretInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCaretInfo。
#include "StdAfx.h"
#include "CaretInfo.h"


// 函数 CCaretInfo::CCaretInfo
// 作用：执行CCaretInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCaretInfo::CCaretInfo(void)
{
	m_pxXStart = 0;
	m_pxYStart = 0;
	m_pxWidth = 1;
	m_pxHeight = 14;
	m_iCurCharIndex = -1;
}

// 函数 CCaretInfo::~CCaretInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCaretInfo::~CCaretInfo(void)
{

}

// 函数 CCaretInfo::CCaretInfo
// 作用：执行CCaretInfo。
// 参数：caretInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCaretInfo::CCaretInfo(const CCaretInfo& caretInfo)
{
	m_pxXStart = caretInfo.m_pxXStart;
	m_pxYStart = caretInfo.m_pxYStart;
	m_pxWidth = caretInfo.m_pxWidth;
	m_pxHeight = caretInfo.m_pxHeight;
	m_iCurCharIndex = caretInfo.m_iCurCharIndex;
}

void CCaretInfo::operator=(const CCaretInfo& caretInfo)
{
	m_pxXStart = caretInfo.m_pxXStart;
	m_pxYStart = caretInfo.m_pxYStart;
	m_pxWidth = caretInfo.m_pxWidth;
	m_pxHeight = caretInfo.m_pxHeight;
	m_iCurCharIndex = caretInfo.m_iCurCharIndex;
}
