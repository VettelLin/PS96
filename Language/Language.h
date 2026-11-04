// 【交接】 Language\Language.h
// 作用：Language。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CLanguageApp、InitInstance、DECLARE_MESSAGE_MAP。
// Language.h : main header file for the Language DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CLanguageApp
// See Language.cpp for the implementation of this class
//

class CLanguageApp : public CWinApp
{
public:
	// 函数 CLanguageApp
	// 作用：执行CLanguageApp。
	// 参数：无。
	// 返回：没有返回值。
	CLanguageApp();

// Overrides
public:
	// 函数 InitInstance
	// 作用：初始化InitInstance。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL InitInstance();

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()
};
