// 【交接】 GeneralPcr\WebBrowserPrint.cpp
// 作用：WebBrowserPrint。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：void、GetComboList、SendMessage、DeleteStrings、GetEditText、GetWindowTextLength、GetWindowText、GetRegValue。
//--------------------------------------------------------------------------
// (C) Copyright 1999 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS-IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// --- THIS CODE IS NOT SUPPORTED BY MICROSOFT ---
//
// This is unsupported code and Microsoft makes no guarantee that the
// techniques used in this sample will function properly in future
// versions of the Internet Explorer product.  This sample takes advantage
// of the fact that the resource identifiers in the "Page Setup" and
// "Print" dialogs are consistent between IE4 and IE5.  Therefore, it is
// possible that this technique will not work properly in future versions
// of Internet Explorer due to changes in the user interface or other
// modifications made to the product at a later date.  The product is not
// designed or tested to accommodate this technique, and the fact that it
// works is fortuitous but not by design.  Please use caution when adding
// this functionality to an application, and bear in mind this warning
// when testing your application with future versions of Internet Explorer.
//
// Author: Dave Templin
//         Support Engineer - Internet Client SDK
//         Microsoft Developer Support
//--------------------------------------------------------------------------
// WebBrowserPrint.cpp: implementation of the CWebBrowserPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <Windows.h>
#include< Winspool.h>
#include "WebBrowserPrint.h"

const size_t BUFSIZE = 255;
static TCHAR g_szBuf[BUFSIZE];
static HHOOK g_hHook = NULL;
static HWND g_hWnd = NULL;
static bool g_bSuccess = false;
static CWebBrowserPrint* g_pWebBrowserPrint = NULL;
static void (CWebBrowserPrint::*g_pDoDlgExchangeFunc)(HWND hwnd) = NULL;

ULONG GetComboList(HWND hwnd, LPTSTR*& ppTextItems)
{
	if (!IsWindow(hwnd))
	{
		g_bSuccess = false;
		return 0;
	}

	//On Win9x, the list of printers is filled completely only when the combo box is dropped down
	//So send F4 keypresses to drop down and retract the combo box
	SendMessage(hwnd, WM_KEYDOWN, 115, 1);
	SendMessage(hwnd, WM_KEYUP, 115, 1);
	SendMessage(hwnd, WM_KEYDOWN, 115, 1);
	SendMessage(hwnd, WM_KEYUP, 115, 1);

	ULONG count = SendMessage(hwnd, CB_GETCOUNT, 0, 0);
	ppTextItems = new LPTSTR[count];  // allocate storage for count TSTR's

	for (ULONG i = 0; i < count; ++i)
	{
		ULONG textlen = SendMessage(hwnd, CB_GETLBTEXTLEN, i, 0) + 1;
		ppTextItems[i] = new TCHAR[textlen];
		SendMessage(hwnd, CB_GETLBTEXT, i, (WPARAM)ppTextItems[i]);
	}

	return count;
}

void DeleteStrings(ULONG& lCount, LPTSTR*& m_ppTextItems)
{
	if (lCount == 0) return;
	for (ULONG i = 0; i < lCount; ++i)
		delete [] m_ppTextItems[i];
	delete [] m_ppTextItems;
	lCount = 0;
}
 
CString GetEditText(HWND hwnd)
{
	CString sText;
	size_t textlen = GetWindowTextLength(hwnd) + 1;
	LPTSTR szText = new TCHAR[textlen];
	GetWindowText(hwnd, szText, textlen);
	sText = szText;
	delete [] szText;
	return sText;
}

CString GetRegValue(LPCTSTR szValueName)
{
	CString sValue;
	HKEY hKey;
	ULONG r;
	DWORD dwType;
	DWORD dwData = BUFSIZE;
	g_szBuf[0] = TCHAR('\0');
	r = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\PageSetup"), 0, KEY_READ, &hKey);
	r = RegQueryValueEx(hKey, szValueName, 0, &dwType, (LPBYTE)g_szBuf, &dwData);
	r = RegCloseKey(hKey);
	sValue = g_szBuf;
	return sValue;
}
void RestoreRegValue(LPCTSTR szValueName, LPCTSTR szValue)
{
	HKEY hKey;
	ULONG r;
	DWORD dwData = _tcslen(szValue) + 1;
	r = RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Microsoft\\Internet Explorer\\PageSetup"), 0, KEY_WRITE, &hKey);
	r = RegSetValueEx(hKey, szValueName, 0, REG_SZ, (LPBYTE)szValue, dwData);
	r = RegCloseKey(hKey);
}

// 函数 CWebBrowserPrint::CWebBrowserPrint
// 作用：执行CWebBrowserPrint。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CWebBrowserPrint::CWebBrowserPrint()
: m_pWebBrowser(NULL), m_lPrinterCount(0)
{
}

// 函数 CWebBrowserPrint::~CWebBrowserPrint
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Release、DeleteStrings。
CWebBrowserPrint::~CWebBrowserPrint()
{
	if (m_pWebBrowser)
		m_pWebBrowser->Release();
	m_pWebBrowser = NULL;
	DeleteStrings(m_lPrinterCount, m_ppPrinterNames);
}

// 函数 CWebBrowserPrint::SetWebBrowser
// 作用：设置SetWebBrowser。
// 参数：pWebBrowser：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 Release、AddRef。
void CWebBrowserPrint::SetWebBrowser(IWebBrowser2* pWebBrowser)
{
	if (m_pWebBrowser)
	{
		m_pWebBrowser->Release();
		m_pWebBrowser = NULL;
	}

	if (pWebBrowser)
	{
		m_pWebBrowser = pWebBrowser;
		m_pWebBrowser->AddRef();
		m_bPrinting = false;
	}
}

// 函数 CWebBrowserPrint::ExchangeEditText
// 作用：执行ExchangeEditText。
// 参数：hwnd：窗口或数据交换对象；sText。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindow、SetWindowText、GetWindowTextLength、GetWindowText。
void CWebBrowserPrint::ExchangeEditText(HWND hwnd, CString& sText)
{
	if (!IsWindow(hwnd))
	{
		g_bSuccess = false;
		return;
	}

	if (m_bPrinting)
		SetWindowText(hwnd, sText);
	else
	{
		size_t textlen = GetWindowTextLength(hwnd) + 1;				
		LPTSTR szText = new TCHAR[textlen];
		GetWindowText(hwnd, szText, textlen);
		sText = szText;
		delete [] szText;
	}
}

// 函数 CWebBrowserPrint::ExchangeButtonState
// 作用：执行ExchangeButtonState。
// 参数：hwnd：窗口或数据交换对象；bState：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindow、SendMessage。
void CWebBrowserPrint::ExchangeButtonState(HWND hwnd, bool& bState)
{
	if (!IsWindow(hwnd))
	{
		g_bSuccess = false;
		return;
	}

	if (m_bPrinting)
	{
		bool bCurrentState = SendMessage(hwnd, BM_GETCHECK, 0, 0) ? true : false;
		if (bState && bState != bCurrentState)
			SendMessage(hwnd, BM_CLICK, 0, 0);
	}
	else
		bState = SendMessage(hwnd, BM_GETCHECK, 0, 0) != FALSE ? true : false;
}

// 函数 CWebBrowserPrint::ExchangeEditNum
// 作用：执行ExchangeEditNum。
// 参数：hwnd：窗口或数据交换对象；iValue：整数。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindow、wsprintf、_T、SetWindowText、GetEditText、_tcstol。
void CWebBrowserPrint::ExchangeEditNum(HWND hwnd, ULONG& iValue)
{
	if (!IsWindow(hwnd))
	{
		g_bSuccess = false;
		return;
	}
	
	if (m_bPrinting)
	{
		wsprintf(g_szBuf, _T("%d"), iValue); 
		SetWindowText(hwnd, g_szBuf);
	}
	else
	{
		CString sText = GetEditText(hwnd);
		LPTSTR szStop = NULL;
		iValue = _tcstol(sText, &szStop, 10);
	}
}

// 函数 CWebBrowserPrint::ExchangeEditNum
// 作用：执行ExchangeEditNum。
// 参数：hwnd：窗口或数据交换对象；fValue：小数。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindow、wsprintf、_T、SetWindowText、GetEditText、_tcstod。
void CWebBrowserPrint::ExchangeEditNum(HWND hwnd, float& fValue)
{
	if (!IsWindow(hwnd))
	{
		g_bSuccess = false;
		return;
	}

	if (m_bPrinting)
	{
		ULONG wp = (ULONG)fValue;
		ULONG fp = (ULONG)(1000 * (fValue - wp));
		wsprintf(g_szBuf, _T("%d.%03d"), wp, fp); 
		SetWindowText(hwnd, g_szBuf);
	}
	else
	{
		CString sText = GetEditText(hwnd);
		LPTSTR szStop = NULL;
		fValue = (float)_tcstod(sText, &szStop);
	}
}

// 函数 CWebBrowserPrint::CbtProc
// 作用：执行CbtProc。
// 参数：nCode：整数；wParam；lParam。
// 返回：返回 LRESULT CALLBACK。
// 过程：函数里会调用 CallNextHookEx。
LRESULT CALLBACK CWebBrowserPrint::CbtProc(int nCode, WPARAM wParam, LPARAM lParam) 
{  
	switch (nCode)
	{
		case HCBT_CREATEWND:
		{
			HWND hWnd = (HWND)wParam;
			LPCBT_CREATEWND pcbt = (LPCBT_CREATEWND)lParam;
			LPCREATESTRUCT pcs = pcbt->lpcs;
			if ((DWORD)pcs->lpszClass == 0x00008002)
			{
				g_hWnd = hWnd;          // Get hwnd of Page Setup dialog
				pcs->x = -2 * pcs->cx;  // Move dialog off screen
			}
			break;
		}	
		case HCBT_ACTIVATE:
		{
			HWND hwnd = (HWND)wParam;
			if (hwnd == g_hWnd)
			{
				g_hWnd = NULL;
				(g_pWebBrowserPrint->*g_pDoDlgExchangeFunc)(hwnd);  // Call thru func ptr
				g_bSuccess = true;
			}
			break;
		}
	}
    return CallNextHookEx(g_hHook, nCode, wParam, lParam); 
} 

// 函数 CWebBrowserPrint::DoPageSetupDlgExchange
// 作用：执行DoPageSetupDlgExchange。
// 参数：hwnd：窗口或数据交换对象。
// 返回：没有返回值。
// 过程：函数里会调用 ExchangeEditText、GetDlgItem、ExchangeButtonState、ExchangeEditNum、SendMessage。
void CWebBrowserPrint::DoPageSetupDlgExchange(HWND hwnd)
{
	bool bPortrait = (m_Orientation == OrientationPortrait);
	bool bLandscape = (m_Orientation == OrientationLandscape);

	ExchangeEditText(GetDlgItem(hwnd, 0x0471), m_sPaperSize);
	ExchangeEditText(GetDlgItem(hwnd, 0x0472), m_sPaperSource);
	ExchangeEditText(GetDlgItem(hwnd, 0x1fd3), m_sHeader);
	ExchangeEditText(GetDlgItem(hwnd, 0x1fd5), m_sFooter);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0420), bPortrait);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0421), bLandscape);
	ExchangeEditNum(GetDlgItem(hwnd, 0x0483), m_fLeftMargin);
	ExchangeEditNum(GetDlgItem(hwnd, 0x0485), m_fRightMargin);
	ExchangeEditNum(GetDlgItem(hwnd, 0x0484), m_fTopMargin);
	ExchangeEditNum(GetDlgItem(hwnd, 0x0486), m_fBottomMargin);

	if (m_bPrinting)
		SendMessage(GetDlgItem(hwnd, 0x0001), BM_CLICK, 0, 0);  // Invoke OK button
	else
		SendMessage(GetDlgItem(hwnd, 0x0002), BM_CLICK, 0, 0);  // Invoke Cancel button

	if (bPortrait)
		m_Orientation = OrientationPortrait;
	else if (bLandscape)
		m_Orientation = OrientationLandscape;
	else
		m_Orientation = OrientationUndefined;
}

// 函数 CWebBrowserPrint::DoPrintDlgExchange
// 作用：执行DoPrintDlgExchange。
// 参数：hwnd：窗口或数据交换对象。
// 返回：没有返回值。
// 过程：函数里会调用 ExchangeEditText、GetDlgItem、ExchangeButtonState、ExchangeEditNum、DeleteStrings、GetComboList。
void CWebBrowserPrint::DoPrintDlgExchange(HWND hwnd)
{
	bool bPrintRangeAll = (m_PrintRange == PrintRangeAll);
	bool bPrintRangePages = (m_PrintRange == PrintRangePages);
	bool bPrintRangeSelection = (m_PrintRange == PrintRangeSelection);

	bool bPrintFramesScreen = (m_PrintFrames == PrintFramesScreen);
	bool bPrintFramesSelected = (m_PrintFrames == PrintFramesSelected);
	bool bPrintFramesIndividually = (m_PrintFrames == PrintFramesIndividually);

	ExchangeEditText(GetDlgItem(hwnd, 0x0473), m_sPrinterName);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0410), m_bPrintToFile);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0420), bPrintRangeAll);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0422), bPrintRangePages);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0421), bPrintRangeSelection);
	ExchangeEditNum(GetDlgItem(hwnd, 0x0480), m_lPrintRangePagesFrom);
	ExchangeEditNum(GetDlgItem(hwnd, 0x0481), m_lPrintRangePagesTo);
	ExchangeEditNum(GetDlgItem(hwnd, 0x0482), m_lCopies);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0411), m_bCollate);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0423), bPrintFramesScreen);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0424), bPrintFramesSelected);
	ExchangeButtonState(GetDlgItem(hwnd, 0x0425), bPrintFramesIndividually);
	ExchangeButtonState(GetDlgItem(hwnd, 0x1fcc), m_bPrintLinks);
	ExchangeButtonState(GetDlgItem(hwnd, 0x1fce), m_bPrintLinkTable);

	DeleteStrings(m_lPrinterCount, m_ppPrinterNames);
	m_lPrinterCount = GetComboList(GetDlgItem(hwnd, 0x0473), m_ppPrinterNames);

	if (m_bPrinting)
		SendMessage(GetDlgItem(hwnd, 0x0001), BM_CLICK, 0, 0);  // Invoke OK button
	else
		SendMessage(GetDlgItem(hwnd, 0x0002), BM_CLICK, 0, 0);  // Invoke Cancel button

	if (bPrintRangeAll)
		m_PrintRange = PrintRangeAll;
	else if (bPrintRangePages)
		m_PrintRange = PrintRangePages;
	else if (bPrintRangeSelection)
		m_PrintRange = PrintRangeSelection;
	else
		m_PrintRange = PrintRangeUndefined;

	if (bPrintFramesScreen)
		m_PrintFrames = PrintFramesScreen;
	else if (bPrintFramesSelected)
		m_PrintFrames = PrintFramesSelected;
	else if (bPrintFramesIndividually)
		m_PrintFrames = PrintFramesIndividually;
	else
		m_PrintFrames = PrintFramesUndefined;
}

// 函数 CWebBrowserPrint::InvokeDlg
// 作用：执行InvokeDlg。
// 参数：cmdid；hwnd)：窗口或数据交换对象。
// 返回：返回是或否。失败时返回 false。
// 过程：函数里会调用 SetWindowsHookEx、GetCurrentThreadId、ExecWB、UnhookWindowsHookEx。
bool CWebBrowserPrint::InvokeDlg(OLECMDID cmdid, void (CWebBrowserPrint::*pDoDlgExchangeFunc)(HWND hwnd))
{
	if (!m_pWebBrowser)
		return false;
	if (g_hHook)
		return false;
	g_hHook = SetWindowsHookEx(WH_CBT, CbtProc, NULL, GetCurrentThreadId());
	if (!g_hHook)
		return false;
	g_bSuccess = false;
	g_pWebBrowserPrint = this;
	g_pDoDlgExchangeFunc = pDoDlgExchangeFunc;
	HRESULT hr = m_pWebBrowser->ExecWB(cmdid, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	UnhookWindowsHookEx(g_hHook);
	g_pWebBrowserPrint = NULL;
	g_hHook = NULL;
	return g_bSuccess;
}

// 函数 CWebBrowserPrint::ReadDlgSettings
// 作用：读取ReadDlgSettings。
// 参数：无。
// 返回：返回是或否。失败时返回 false。
// 过程：函数里会调用 DeleteStrings、InvokeDlg。
bool CWebBrowserPrint::ReadDlgSettings()
{
	DeleteStrings(m_lPrinterCount, m_ppPrinterNames);
	if ( !InvokeDlg(OLECMDID_PAGESETUP, &CWebBrowserPrint::DoPageSetupDlgExchange) )
		return false;
	if ( !InvokeDlg(OLECMDID_PRINT, &CWebBrowserPrint::DoPrintDlgExchange) )
		return false;
	return true;
}
// 函数 CWebBrowserPrint::IsPrinterExist
// 作用：判断IsPrinterExist是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 EnumPrinters。
BOOL CWebBrowserPrint::IsPrinterExist()
{
	DWORD wdFlag = PRINTER_ENUM_LOCAL|PRINTER_ENUM_CONNECTIONS;
	DWORD wdFoundedPrinters = 0;//printers count
	DWORD wdNeededBuffer = 0;//size in bytes

	::EnumPrinters( wdFlag,NULL,1,NULL,0,&wdNeededBuffer,&wdFoundedPrinters);
	PRINTER_INFO_1 *pPrinterEnum = (PRINTER_INFO_1 *) new BYTE[wdNeededBuffer] ;
	::EnumPrinters(wdFlag,NULL,1,(LPBYTE)pPrinterEnum,wdNeededBuffer,&wdNeededBuffer,&wdFoundedPrinters);

	delete pPrinterEnum;
	pPrinterEnum = NULL;

	return wdFoundedPrinters>0;
}
// 函数 CWebBrowserPrint::Print
// 作用：执行Print。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 IsPrinterExist、GetRegValue、_T、InvokeDlg、RestoreRegValue。
bool CWebBrowserPrint::Print()
{
	if (!IsPrinterExist()) 
	{
		return FALSE;
	}

	CString sHeader = GetRegValue(_T("header"));
	CString sFooter = GetRegValue(_T("footer"));
	CString sLeftMargin = GetRegValue(_T("margin_left"));
	CString sRightMargin = GetRegValue(_T("margin_right"));
	CString sTopMargin = GetRegValue(_T("margin_top"));
	CString sBottomMargin = GetRegValue(_T("margin_bottom"));		

	bool bSuccess = false;
	m_bPrinting = true;
	if ( InvokeDlg(OLECMDID_PAGESETUP, &CWebBrowserPrint::DoPageSetupDlgExchange) )
		if ( InvokeDlg(OLECMDID_PRINTPREVIEW, &CWebBrowserPrint::DoPrintDlgExchange) )
			bSuccess = true;
	m_bPrinting = false;

//	RestoreRegValue(_T("header"), sHeader);
//	RestoreRegValue(_T("footer"), sFooter);
//	RestoreRegValue(_T("margin_left"), sLeftMargin);
//	RestoreRegValue(_T("margin_right"), sRightMargin);
//	RestoreRegValue(_T("margin_top"), sTopMargin);
//	RestoreRegValue(_T("margin_bottom"), sBottomMargin);		

	return bSuccess;
}

// 函数 CWebBrowserPrint::GetPrinterName
// 作用：读取GetPrinterName。
// 参数：lIndex。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CWebBrowserPrint::GetPrinterName(ULONG lIndex)
{
	CString sPrinterName;
	if (lIndex < m_lPrinterCount)
		sPrinterName = m_ppPrinterNames[lIndex];
	return sPrinterName;
}

// 函数 CWebBrowserPrint::GetDefaultPrinterName
// 作用：读取GetDefaultPrinterName。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetProfileString、_T、_tcsstr。
CString CWebBrowserPrint::GetDefaultPrinterName()
{
	CString sPrinterName;

	GetProfileString(_T("windows"), _T("device"), _T(",,,"), g_szBuf, BUFSIZE);
	LPTSTR pch = _tcsstr(g_szBuf, _T(","));
	if (pch)
	{
		*pch = _T('\0');
		sPrinterName = g_szBuf;
	}

	return sPrinterName;
}
