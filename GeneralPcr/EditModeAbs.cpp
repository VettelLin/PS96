// 【交接】 GeneralPcr\EditModeAbs.cpp
// 作用：EditModeAbs。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CEditModeAbs。
#include "StdAfx.h"
#include "EditModeAbs.h"


// 函数 CEditModeAbs::CEditModeAbs
// 作用：执行CEditModeAbs。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CEditModeAbs::CEditModeAbs(void)
{
	m_eExpEditMode = EEEM_NOLIMIT;
}


// 函数 CEditModeAbs::~CEditModeAbs
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CEditModeAbs::~CEditModeAbs(void)
{
}

// 函数 CEditModeAbs::CEditModeAbs
// 作用：执行CEditModeAbs。
// 参数：editMode。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CEditModeAbs::CEditModeAbs(const CEditModeAbs& editMode)
{
	m_eExpEditMode = editMode.m_eExpEditMode;
}

void CEditModeAbs::operator=(const CEditModeAbs& editMode)
{
	m_eExpEditMode = editMode.m_eExpEditMode;
}


