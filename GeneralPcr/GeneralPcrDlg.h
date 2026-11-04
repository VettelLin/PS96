// 【交接】 GeneralPcr\GeneralPcrDlg.h
// 作用：GeneralPcrDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：CGeneralPcrDlg、DoDataExchange、OnInitDialog、OnPaint、OnQueryDragIcon、DECLARE_MESSAGE_MAP、OnSysCommand、OnCreate。
#pragma once

#include "resource.h"
#include "MyButton.h"
#include "MyStatic.h"
#include "MyProgressBar.h"
#include "WorkDlg.h"
#include "SetDlg.h"
#include "PrjManageDlg.h"
#include "RectManage.h"
#include "ExperStateInfo.h"
#include "FontSet.h"

typedef enum EMainFuncType
{
	EMFT_WORK = 1,EMFT_SET,EMFT_PRJMANAGE
}EMAINFUNCTYPE;

// CGeneralPcrDlg dialog
class CGeneralPcrDlg : public CDialogEx,public CFontSet
{
// Construction
public:
	// 函数 CGeneralPcrDlg
	// 作用：执行CGeneralPcrDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CGeneralPcrDlg(CWnd* pParent = NULL);	// standard constructor
	// 函数 ~CGeneralPcrDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CGeneralPcrDlg();
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

	// 函数 OnBnClickedSwtBtMainPage
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtMainPage();
	// 函数 OnBnClickedSwtBtPrjManage
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtPrjManage();
	// 函数 OnBnClickedSwtBtSet
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtSet();

	// 函数 OnBnClickedSwtBtWork
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtWork();
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
	// 函数 OnDestroy
	// 作用：窗口销毁前做清理。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnDestroy();

			// 函数 CreateCtrl
			// 作用：创建或加入CreateCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCtrl();
			// 函数 CreateBt
			// 作用：创建或加入CreateBt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateBt();
			// 函数 CreateSt
			// 作用：创建或加入CreateSt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSt();
			// 函数 InitCtrl
			// 作用：初始化InitCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void InitCtrl();
			// 函数 InitBt
			// 作用：初始化InitBt。
			// 参数：无。
			// 返回：没有返回值。
			void InitBt();
			// 函数 InitSt
			// 作用：初始化InitSt。
			// 参数：无。
			// 返回：没有返回值。
			void InitSt();
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
			// 函数 InitSetDlg
			// 作用：初始化InitSetDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSetDlg();
			// 函数 InitPrjManageDlg
			// 作用：初始化InitPrjManageDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitPrjManageDlg();

			// 函数 SetCtrlText
			// 作用：设置SetCtrlText。
			// 参数：bOnlyConnectStatus：是或否。
			// 返回：没有返回值。
			void SetCtrlText(BOOL bOnlyConnectStatus=FALSE);

			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：eMainFuncType。
			// 返回：没有返回值。
			void SetPageSelected(EMAINFUNCTYPE eMainFuncType);

			// 函数 New
			// 作用：执行New。
			// 参数：无。
			// 返回：没有返回值。
			void New();	//新建功能
			// 函数 Delete
			// 作用：更新或清除Delete。
			// 参数：无。
			// 返回：没有返回值。
			void Delete();	//删除功能
			// 函数 Open
			// 作用：读入Open。
			// 参数：无。
			// 返回：没有返回值。
			void Open();	//打开功能

			// 函数 SetLidTem
			// 作用：设置SetLidTem。
			// 参数：iLidTem：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLidTem(int iLidTem);	//更改热盖温度后，更新到已经打开的实验文件
			// 函数 ReadLidTem
			// 作用：读取ReadLidTem。
			// 参数：dLidTem：小数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadLidTem(double& dLidTem);
			// 函数 SetLidPreheatTem
			// 作用：设置SetLidPreheatTem。
			// 参数：iLidTem：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLidPreheatTem(int iLidTem);
			// 函数 ReadLidPreheatTem
			// 作用：读取ReadLidPreheatTem。
			// 参数：fLidTem：小数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadLidPreheatTem(float& fLidTem);
			// 函数 TransportLock
			// 作用：执行TransportLock。
			// 参数：strErrInfo：字符串。
			// 返回：返回是或否。
			BOOL TransportLock(CString &strErrInfo);

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshLanguageDisplay();
			// 函数 SetDefaultGeneName
			// 作用：设置SetDefaultGeneName。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetDefaultGeneName();

public:
	CMyButton m_btMainPage;
	CMyButton m_btWork;
	CMyButton m_btPrjManage;
	CMyButton m_btSet;
	
	CMyButton m_btMinimum;
	CMyButton m_btZoom;
	CMyButton m_btClose;

	CMyStatic m_stUserName;
	CMyStatic m_stLisConState;
	CMyStatic m_stPrinterConState;

	CWorkDlg m_workDlg;
	CSetDlg m_setDlg;
	CPrjManageDlg m_prjManageDlg;

private:
	int m_iCapH;	//标题栏高度

	CMyButton* m_pCurSelSwt;
	CWnd* m_pCurSelWnd;

	CRectManage m_rcManage;

	CDC* m_pMemDc;
	HBITMAP m_hBitmap;

	BOOL m_bPreZeroSize;	//记录上一个窗口大小是否是0
	BOOL m_bZeroToNewSize;	//标识从零开始到正常大小

	UINT	m_nRunTimer;
	int		m_iTimerCount;
};
