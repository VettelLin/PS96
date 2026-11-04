// 【交接】 BWGenUILib\dllmain.cpp
// 作用：动态库入口。系统加载或卸载这个 DLL 时调用，里面不做实验业务。
// 先看这些函数：DllMain、UNREFERENCED_PARAMETER、TRACE0、CDynLinkLibrary、AfxTermExtensionModule、CBWGenUILibResource、AfxGetResourceHandle、AfxSetResourceHandle。
// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>
#include "BWGenUILib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static AFX_EXTENSION_MODULE BWGenUILibDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("BWGenUILib.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(BWGenUILibDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(BWGenUILibDLL);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("BWGenUILib.DLL Terminating!\n");

		// Terminate the library before destructors are called
		AfxTermExtensionModule(BWGenUILibDLL);
	}
	return 1;   // ok
}

///////////////////////////////////////////////////////////////////////
// CBWGenUILibResource implementation:

// 函数 CBWGenUILibResource::CBWGenUILibResource
// 作用：执行CBWGenUILibResource。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 AfxGetResourceHandle、AfxSetResourceHandle。
CBWGenUILibResource::CBWGenUILibResource()
{
	m_hInstOld = AfxGetResourceHandle ();
	ASSERT (m_hInstOld != NULL);

	AfxSetResourceHandle(BWGenUILibDLL.hResource);
}

// 函数 CBWGenUILibResource::~CBWGenUILibResource
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 AfxSetResourceHandle。
CBWGenUILibResource::~CBWGenUILibResource()
{
	AfxSetResourceHandle (m_hInstOld);
}
