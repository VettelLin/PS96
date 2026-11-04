// 【交接】 GeneralPcr\HoleSelectSet.cpp
// 作用：HoleSelectSet。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CHoleSelectSet。
#include "StdAfx.h"
#include "HoleSelectSet.h"


// 函数 CHoleSelectSet::CHoleSelectSet
// 作用：执行CHoleSelectSet。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHoleSelectSet::CHoleSelectSet(void)
{
	m_eHoleDefDisplay = EHDD_PATIENTNAME;
}


// 函数 CHoleSelectSet::~CHoleSelectSet
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHoleSelectSet::~CHoleSelectSet(void)
{
}

// 函数 CHoleSelectSet::CHoleSelectSet
// 作用：执行CHoleSelectSet。
// 参数：holeSelSet。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHoleSelectSet::CHoleSelectSet(const CHoleSelectSet& holeSelSet)
{
	m_eHoleDefDisplay = holeSelSet.m_eHoleDefDisplay;
}

void CHoleSelectSet::operator=(const CHoleSelectSet& holeSelSet)
{
	m_eHoleDefDisplay = holeSelSet.m_eHoleDefDisplay;
}
