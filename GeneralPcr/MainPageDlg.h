// 【交接】 GeneralPcr\MainPageDlg.h
// 作用：MainPageDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CMainPageDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnCreate、OnBnClickedBtNew。
#pragma once

#include "ExperimentData.h"
#include "MyButton.h"

//历史实验记录显示模式：图形模式、表格模式
typedef enum HistoryExpDisplayMode
{
	EHEDM_FIGURE,EHEDM_LIST
}EHISTORYEXPDISPALYMODE;

class CMainPageDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMainPageDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CMainPageDlg)

public:
	// 函数 CMainPageDlg
	// 作用：执行CMainPageDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CMainPageDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CMainPageDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CMainPageDlg();

// Dialog Data
	enum { IDD = IDD_SAMSETDLG };

protected:
	// 函数 DoDataExchange
	// 作用：把对话框控件和成员变量绑在一起。
	// 参数：pDX：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

public:
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
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnBnClickedBtNew
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtNew();
	// 函数 OnBnClickedBtOpen
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtOpen();

	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();

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
	// 函数 CreateLst
	// 作用：创建或加入CreateLst。
	// 参数：无。
	// 返回：没有返回值。
	void CreateLst();
	// 函数 CreateSamPlateDlg
	// 作用：创建或加入CreateSamPlateDlg。
	// 参数：无。
	// 返回：没有返回值。
	void CreateSamPlateDlg();
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
	// 函数 InitLst
	// 作用：初始化InitLst。
	// 参数：无。
	// 返回：没有返回值。
	void InitLst();
	// 函数 InitSamPlateDlg
	// 作用：初始化InitSamPlateDlg。
	// 参数：无。
	// 返回：没有返回值。
	void InitSamPlateDlg();
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

	// 函数 SetPageSelected
	// 作用：设置SetPageSelected。
	// 参数：eExpDisplayMode。
	// 返回：没有返回值。
	void SetPageSelected(EHISTORYEXPDISPALYMODE eExpDisplayMode);

public:
	CMyButton m_btNew;
	CMyButton m_btOpen;

private:
	BOOL m_bCtrlCreated;

	CMyButton* m_pCurSelSwt;
	CWnd* m_pCurSelWnd;

	int m_iSwitchBtBkH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtBkW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值
	int m_iSwitchBtW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值
};














