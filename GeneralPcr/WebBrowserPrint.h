// 【交接】 GeneralPcr\WebBrowserPrint.h
// 作用：WebBrowserPrint。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CWebBrowserPrint、SetWebBrowser、Print、ReadDlgSettings、GetPrinterName、GetPrinterCount、GetDefaultPrinterName、IsPrinterExist。
// WebBrowserPrint.h: interface for the CWebBrowserPrint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEBBROWSERPRINT_H__DA19EEF7_7132_11D3_BB8B_00C04FA3471C__INCLUDED_)
#define AFX_WEBBROWSERPRINT_H__DA19EEF7_7132_11D3_BB8B_00C04FA3471C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWebBrowserPrint  
{
public:
	enum Orientation { OrientationUndefined, OrientationPortrait, OrientationLandscape };
	enum PrintRange { PrintRangeUndefined, PrintRangeAll, PrintRangePages, PrintRangeSelection };
	enum PrintFrames { PrintFramesUndefined, PrintFramesScreen, PrintFramesSelected, PrintFramesIndividually };
	
	// 函数 CWebBrowserPrint
	// 作用：执行CWebBrowserPrint。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPrinterCount。
	CWebBrowserPrint();
	// 函数 ~CWebBrowserPrint
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPrinterCount。
	virtual ~CWebBrowserPrint();

	// 函数 SetWebBrowser
	// 作用：设置SetWebBrowser。
	// 参数：pWebBrowser：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPrinterCount。
	void SetWebBrowser(IWebBrowser2* pWebBrowser);
	// 函数 Print
	// 作用：执行Print。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetPrinterCount。
	bool Print();
	// 函数 ReadDlgSettings
	// 作用：读取ReadDlgSettings。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetPrinterCount。
	bool ReadDlgSettings();
	// 函数 GetPrinterName
	// 作用：读取GetPrinterName。
	// 参数：lIndex。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetPrinterCount。
	CString GetPrinterName(ULONG lIndex);
	// 函数 GetPrinterCount
	// 作用：读取GetPrinterCount。
	// 参数：无。
	// 返回：返回 ULONG。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	ULONG GetPrinterCount() { return m_lPrinterCount; }
	// 函数 GetDefaultPrinterName
	// 作用：读取GetDefaultPrinterName。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetDefaultPrinterName();

	// Page Setup dialog settings
	CString m_sPaperSize;
	CString m_sPaperSource;
	CString m_sHeader;
	CString m_sFooter;
	Orientation m_Orientation;
	float m_fLeftMargin;
	float m_fTopMargin;
	float m_fRightMargin;
	float m_fBottomMargin;

	// Print dialog settings
	CString m_sPrinterName;
	bool m_bPrintToFile;
	PrintRange m_PrintRange;
	ULONG m_lPrintRangePagesFrom;
	ULONG m_lPrintRangePagesTo;
	ULONG m_lCopies;
	bool m_bCollate;
	PrintFrames m_PrintFrames;
	bool m_bPrintLinks;
	bool m_bPrintLinkTable;
	// 函数 IsPrinterExist
	// 作用：判断IsPrinterExist是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsPrinterExist();

private:
	// 函数 ExchangeEditText
	// 作用：执行ExchangeEditText。
	// 参数：hwnd：窗口或数据交换对象；sText。
	// 返回：没有返回值。
	void ExchangeEditText(HWND hwnd, CString& sText);
	// 函数 ExchangeButtonState
	// 作用：执行ExchangeButtonState。
	// 参数：hwnd：窗口或数据交换对象；bState：是或否。
	// 返回：没有返回值。
	void ExchangeButtonState(HWND hwnd, bool& bState);
	// 函数 ExchangeEditNum
	// 作用：执行ExchangeEditNum。
	// 参数：hwnd：窗口或数据交换对象；fValue：小数。
	// 返回：没有返回值。
	void ExchangeEditNum(HWND hwnd, float& fValue);
	// 函数 ExchangeEditNum
	// 作用：执行ExchangeEditNum。
	// 参数：hwnd：窗口或数据交换对象；lValue。
	// 返回：没有返回值。
	void ExchangeEditNum(HWND hwnd, ULONG& lValue);
	// 函数 DoPageSetupDlgExchange
	// 作用：执行DoPageSetupDlgExchange。
	// 参数：hwnd：窗口或数据交换对象。
	// 返回：没有返回值。
	void DoPageSetupDlgExchange(HWND hwnd);
	// 函数 DoPrintDlgExchange
	// 作用：执行DoPrintDlgExchange。
	// 参数：hwnd：窗口或数据交换对象。
	// 返回：没有返回值。
	void DoPrintDlgExchange(HWND hwnd);
	// 函数 InvokeDlg
	// 作用：执行InvokeDlg。
	// 参数：cmdid；hwnd)：窗口或数据交换对象。
	// 返回：返回是或否。
	bool InvokeDlg(OLECMDID cmdid, void (CWebBrowserPrint::*pDoDlgExchangeFunc)(HWND hwnd));
	static LRESULT CALLBACK CbtProc(int nCode, WPARAM wParam, LPARAM lParam);

	IWebBrowser2* m_pWebBrowser;
	ULONG m_lPrinterCount;
	LPTSTR* m_ppPrinterNames;
	bool m_bPrinting;
};

#endif // !defined(AFX_WEBBROWSERPRINT_H__DA19EEF7_7132_11D3_BB8B_00C04FA3471C__INCLUDED_)
