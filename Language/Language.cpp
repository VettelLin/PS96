// 【交接】 Language\Language.cpp
// 作用：Language。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：BEGIN_MESSAGE_MAP、END_MESSAGE_MAP、CLanguageApp、InitInstance。
// Language.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CLanguageApp

BEGIN_MESSAGE_MAP(CLanguageApp, CWinApp)
END_MESSAGE_MAP()


// CLanguageApp construction

// 函数 CLanguageApp::CLanguageApp
// 作用：执行CLanguageApp。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLanguageApp::CLanguageApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CLanguageApp object

CLanguageApp theApp;


// CLanguageApp initialization

// 函数 CLanguageApp::InitInstance
// 作用：初始化InitInstance。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 CWinApp::InitInstance。
BOOL CLanguageApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
