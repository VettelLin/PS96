// 【交接】 GeneralPcr\HtmlCtrl.h
// 作用：HtmlCtrl。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CHtmlCtrl、CreateFromStatic、PostNcDestroy、OnDestroy、OnMouseActivate、OnTimer、OnBeforeNavigate2、OnAppCmd。
////////////////////////////////////////////////////////////////
// Compiles with Visual C++ 6.0, runs on Windows 98 and probably NT too.
#pragma once
//
#include <AFXHTML.H>
#include "WebBrowserPrint.h"

class CHtmlCtrl : public CHtmlView
{
public:
	// 函数 CHtmlCtrl
	// 作用：执行CHtmlCtrl。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CHtmlCtrl() {m_bPrintPreview=FALSE; }
	// 函数 ~CHtmlCtrl
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CHtmlCtrl() { }

	// 函数 CreateFromStatic
	// 作用：创建或加入CreateFromStatic。
	// 参数：nID：整数；pParent：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	// 过程：函数里会调用 PostNcDestroy。
	BOOL CreateFromStatic(UINT nID, CWnd* pParent);

	// Normally, CHtmlView destroys itself in PostNcDestroy,
	// but we don't want to do that for a control since a control
	// is usually implemented as a stack object in a dialog.
	//
	virtual void PostNcDestroy() {  }

	// overrides to bypass MFC doc/view frame dependencies
	// 函数 OnDestroy
	// 作用：窗口销毁前做清理。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnDestroy();
	// 函数 OnMouseActivate
	// 作用：响应 Windows 或自定义消息 OnMouseActivate。
	// 参数：pDesktopWnd：指针，指向调用方传入的对象；nHitTest：整数；msg。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int  OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT msg);
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT nIDEvent);

	// override to trap "app:" pseudo protocol
	// 函数 OnBeforeNavigate2
	// 作用：响应 Windows 或自定义消息 OnBeforeNavigate2。
	// 参数：lpszURL；nFlags：整数；lpszTargetFrameName；baPostedData；lpszHeaders；pbCancel。
	// 返回：没有返回值。
	// 过程：函数里会调用 OnDownloadComplete。
	virtual void OnBeforeNavigate2( LPCTSTR lpszURL,
		DWORD nFlags,
		LPCTSTR lpszTargetFrameName,
		CByteArray& baPostedData,
		LPCTSTR lpszHeaders,
		BOOL* pbCancel );

	// override to handle links to "app:mumble...". lpszWhere will be "mumble"
	// 函数 OnAppCmd
	// 作用：响应 Windows 或自定义消息 OnAppCmd。
	// 参数：lpszWhere。
	// 返回：没有返回值。
	// 过程：函数里会调用 OnDownloadComplete。
	virtual void OnAppCmd(LPCTSTR lpszWhere);

	//to determin if print preview the source
	// 函数 OnDownloadComplete
	// 作用：响应 Windows 或自定义消息 OnDownloadComplete。
	// 参数：无。
	// 返回：没有返回值。
	virtual void OnDownloadComplete( ){}
	// 函数 OnDocumentComplete
	// 作用：响应 Windows 或自定义消息 OnDocumentComplete。
	// 参数：LPCTSTR。
	// 返回：没有返回值。
	virtual void OnDocumentComplete(LPCTSTR);

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP();
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CHtmlCtrl。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CHtmlCtrl)

public:
	//打印设置
	// 函数 InitWebBrowserPrint
	// 作用：初始化InitWebBrowserPrint。
	// 参数：strHeader：字符串；strFooter：字符串；bLandScapeOrientation：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 IsPrinterExist。
	void InitWebBrowserPrint(CString strHeader = _T(""),CString strFooter = _T(""),BOOL bLandScapeOrientation = FALSE);
	//打印动作
	// 函数 PrintPreview
	// 作用：执行PrintPreview。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 IsPrinterExist。
	void PrintPreview();

	// 函数 Navigate2AsPrintPreview
	// 作用：执行Navigate2AsPrintPreview。
	// 参数：strURL：字符串；bPrintPreview：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 IsPrinterExist。
	void Navigate2AsPrintPreview(CString strURL,BOOL bPrintPreview = TRUE);

	// 函数 IsPrinterExit
	// 作用：判断IsPrinterExit是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 IsPrinterExist。
	BOOL IsPrinterExit()
	{
		return m_WebBrowserPrint.IsPrinterExist() ;
	}

private:
	//负责打印
	CWebBrowserPrint m_WebBrowserPrint;
	BOOL m_bPrintPreview;
};

