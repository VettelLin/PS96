// 【交接】 GeneralPcr\Ps96IvdDlg.h
// 作用：Ps96IvdDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：CPs96IvdDlg、DoDataExchange、OnInitDialog、OnPaint、OnQueryDragIcon、DECLARE_MESSAGE_MAP、OnSysCommand、OnCreate。
#pragma once

#include "resource.h"
#include "MyButton.h"
#include "MyStatic.h"
#include "MyProgressBar.h"
#include "Ps96WorkDlg.h"
#include "RectManage.h"
#include "FontSet.h"

// CPs96IvdDlg dialog
class CPs96IvdDlg : public CDialogEx,public CFontSet
{
// Construction
public:
	// 函数 CPs96IvdDlg
	// 作用：执行CPs96IvdDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPs96IvdDlg(CWnd* pParent = NULL);	// standard constructor
	// 函数 ~CPs96IvdDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CPs96IvdDlg();
// Dialog Data
	enum { IDD = IDD_GENERALPCR_DIALOG };

	protected:
	// 函数 DoDataExchange
	// 作用：把对话框控件和成员变量绑在一起。
	// 参数：pDX：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();
	// 函数 OnQueryDragIcon
	// 作用：响应 Windows 或自定义消息 OnQueryDragIcon。
	// 参数：无。
	// 返回：返回 HCURSOR。
	afx_msg HCURSOR OnQueryDragIcon();
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

public:
	// 函数 OnSysCommand
	// 作用：响应 Windows 或自定义消息 OnSysCommand。
	// 参数：nID：整数；lParam。
	// 返回：没有返回值。
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 OnSizing
	// 作用：响应 Windows 或自定义消息 OnSizing。
	// 参数：nSide：整数；pRect：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnSizing(UINT nSide,LPRECT pRect);
	// 函数 OnShowWindow
	// 作用：响应 Windows 或自定义消息 OnShowWindow。
	// 参数：bShow：是或否；nStatus：整数。
	// 返回：没有返回值。
	afx_msg void OnShowWindow(BOOL bShow,UINT nStatus);
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	// 函数 OnLButtonDblClk
	// 作用：双击鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDblClk(UINT nFlags,CPoint point);

	// 函数 OnBnClickedBtMinimum
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtMinimum();
	// 函数 OnBnClickedBtZoom
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtZoom();
	// 函数 OnBnClickedBtClose
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtClose();

	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT_PTR nIDEvent);
		
			// 函数 InitDlg
			// 作用：初始化InitDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitDlg();
			// 函数 InitSonDlg
			// 作用：初始化InitSonDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSonDlg();
			// 函数 InitWorkDlg
			// 作用：初始化InitWorkDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitWorkDlg();

			// 函数 CreateCtrl
			// 作用：创建或加入CreateCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCtrl();
			// 函数 CreateProgressBar
			// 作用：创建或加入CreateProgressBar。
			// 参数：无。
			// 返回：没有返回值。
			void CreateProgressBar();
			// 函数 InitCtrl
			// 作用：初始化InitCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void InitCtrl();
			// 函数 SetCtrlPos
			// 作用：设置SetCtrlPos。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlPos();
			// 函数 ShowCtrl
			// 作用：改变ShowCtrl的显示或可用状态。
			// 参数：无。
			// 返回：没有返回值。
			void ShowCtrl();

			// 函数 DlgSizeChanged
			// 作用：执行DlgSizeChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DlgSizeChanged();

public:
	CMyButton m_btMinimum;
	CMyButton m_btZoom;
	CMyButton m_btClose;

	CPs96WorkDlg m_workDlg;

private:
	BOOL m_bCtrlCreated;

	int m_iCapH;	//标题栏高度
	int m_iFrameW;	//边框宽度

	COLORREF m_clrFrame;	//边框颜色

	CMyButton* m_pCurSelSwt;
	CWnd* m_pCurSelWnd;

	CRectManage m_rcManage;

	CDC* m_pMemDc;
	HBITMAP m_hBitmap;

	BOOL m_bPreZeroSize;	//记录上一个窗口大小是否是0
	BOOL m_bZeroToNewSize;	//标识从零开始到正常大小

	double m_dSizeRatio;	//记录主窗口的缩放比例

	BOOL m_bZooming;	//标识是否处于窗口大小调整过程

	UINT	m_nRunTimer;
	int		m_iTimerCount;

public:
	// 函数 OnDestroy
	// 作用：窗口销毁前做清理。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnDestroy();
};
