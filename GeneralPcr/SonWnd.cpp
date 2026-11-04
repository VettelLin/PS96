// 【交接】 GeneralPcr\SonWnd.cpp
// 作用：SonWnd。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：IMPLEMENT_DYNAMIC、CSonWnd、BEGIN_MESSAGE_MAP、ON_WM_PAINT、ON_WM_ERASEBKGND、ON_WM_RBUTTONDOWN、ON_WM_LBUTTONDOWN、ON_WM_MOUSEMOVE。
// SonWnd.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "SonWnd.h"


// CSonWnd

IMPLEMENT_DYNAMIC(CSonWnd, CDialogEx)

// 函数 CSonWnd::CSonWnd
// 作用：执行CSonWnd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSonWnd::CSonWnd()
{

}

// 函数 CSonWnd::~CSonWnd
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSonWnd::~CSonWnd()
{
}


BEGIN_MESSAGE_MAP(CSonWnd, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// 函数 CSonWnd::OnPaint
// 作用：窗口需要重画时绘制内容。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 dc、GetClientRect、FillSolidRect、RGB。
void CSonWnd::OnPaint()
{
	CPaintDC dc(this); 

	CRect rcClient;
	GetClientRect(&rcClient);

	dc.FillSolidRect(&rcClient,RGB(255,0,0));

	return;
}

// 函数 CSonWnd::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSonWnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// 函数 CSonWnd::OnRButtonDown
// 作用：按下鼠标右键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、PtInRect、ShowWindow、ReleaseCapture。
void CSonWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	if(!rect.PtInRect(point))
	{
		ShowWindow(SW_HIDE);
		ReleaseCapture();
	}
	return;
}

// 函数 CSonWnd::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、PtInRect、ShowWindow、ReleaseCapture。
void CSonWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	if(!rect.PtInRect(point))
	{
		ShowWindow(SW_HIDE);
		ReleaseCapture();
	}
	return;
}

// 函数 CSonWnd::OnMouseMove
// 作用：鼠标在窗口上移动。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、PtInRect。
void CSonWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	if(!rect.PtInRect(point))
	{
		int tt = 0;
		++tt;
	}

	return;
}

