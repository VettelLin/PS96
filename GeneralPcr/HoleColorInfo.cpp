// 【交接】 GeneralPcr\HoleColorInfo.cpp
// 作用：HoleColorInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CHoleColorInfo、Color、RGB。
#include "StdAfx.h"
#include "HoleColorInfo.h"


// 函数 CHoleColorInfo::CHoleColorInfo
// 作用：执行CHoleColorInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Color、RGB。
CHoleColorInfo::CHoleColorInfo(void)
{
	m_clrFrame = Color(0X0,0X0,0X0);
	m_clrFill = Color(255 / 5,0X0,0X0,0X0);
	m_clrTxUnSelected = RGB(0,0,0);
	m_clrTxSelected = RGB(0,0,0);
}

// 函数 CHoleColorInfo::~CHoleColorInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHoleColorInfo::~CHoleColorInfo(void)
{
	
}

// 函数 CHoleColorInfo::CHoleColorInfo
// 作用：执行CHoleColorInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHoleColorInfo::CHoleColorInfo(const CHoleColorInfo& info)
{
	m_clrFrame = info.m_clrFrame;
	m_clrFill = info.m_clrFill;	
	m_clrTxUnSelected = info.m_clrTxUnSelected;
	m_clrTxSelected = info.m_clrTxSelected;
}

void CHoleColorInfo::operator=(const CHoleColorInfo& info)
{
	m_clrFrame = info.m_clrFrame;
	m_clrFill = info.m_clrFill;
	m_clrTxUnSelected = info.m_clrTxUnSelected;
	m_clrTxSelected = info.m_clrTxSelected;
}


