// 【交接】 GeneralPcr\FuncBtDlg.h
// 作用：FuncBtDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CFuncBtDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnCreate、OnInitDialog。
#pragma once

#include "MyButton.h"
#include "MyCheckButton.h"
#include "LinkList.h"
#include "FontSet.h"
#include "Resource.h"
#include "RectManage.h"

class CGeneralPcrDlg;

class CFuncBtDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CFuncBtDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CFuncBtDlg)

public:
	// 函数 CFuncBtDlg
	// 作用：执行CFuncBtDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CFuncBtDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CFuncBtDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CFuncBtDlg();

// Dialog Data
	enum { IDD = IDD_MIDDLEDLG };

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
	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
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
			// 函数 SetCtrlPos
			// 作用：设置SetCtrlPos。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlPos();
			// 函数 SetCtrlPosModeExpProcSet
			// 作用：设置SetCtrlPosModeExpProcSet。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlPosModeExpProcSet();
			// 函数 SetCtrlPosModeExpSamSet
			// 作用：设置SetCtrlPosModeExpSamSet。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlPosModeExpSamSet();
			// 函数 SetCtrlPosModeExpDataAnalyse
			// 作用：设置SetCtrlPosModeExpDataAnalyse。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlPosModeExpDataAnalyse();

			// 函数 SetChanBtPos
			// 作用：设置SetChanBtPos。
			// 参数：无。
			// 返回：没有返回值。
			void SetChanBtPos();

			// 函数 ShowCtrl
			// 作用：改变ShowCtrl的显示或可用状态。
			// 参数：无。
			// 返回：没有返回值。
			void ShowCtrl();
			// 函数 SetChanBtShowState
			// 作用：设置SetChanBtShowState。
			// 参数：bShow：是或否。
			// 返回：没有返回值。
			void SetChanBtShowState(BOOL bShow);

			// 函数 SetChannelBtNum
			// 作用：设置SetChannelBtNum。
			// 参数：iChanBtNum：整数；vecChanDyeName；bShowChanBt：是或否。
			// 返回：没有返回值。
			void SetChannelBtNum(int iChanBtNum,vector<CString>& vecChanDyeName,BOOL bShowChanBt = TRUE);	//设置通道切换按钮个数，实时生效
			// 函数 SetChanBtSelectState
			// 作用：设置SetChanBtSelectState。
			// 参数：vecSelState。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetChanBtSelectState(vector<int> vecSelState);

			// 函数 SetOneChannelBtText
			// 作用：设置SetOneChannelBtText。
			// 参数：iChanId：整数；strText：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetOneChannelBtText(int iChanId,CString strText);

			// 函数 SetCtrlText
			// 作用：设置SetCtrlText。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlText();

			// 函数 ResetRectManage
			// 作用：更新或清除ResetRectManage。
			// 参数：无。
			// 返回：没有返回值。
			void ResetRectManage();

	// 函数 OnBnClickedDelete
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedDelete();
	// 函数 OnBnClickedSaveAs
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSaveAs();
	// 函数 OnBnClickedNew
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedNew();
	// 函数 OnBnClickedOpen
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedOpen();
	// 函数 OnBnClickedSave
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSave();
	// 函数 OnBnClickedAnalyse
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedAnalyse();
	// 函数 OnBnClickedExport
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedExport();
	// 函数 OnBnClickedImport
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedImport();

	// 函数 OnBnClickedLoadOriginalAmpData
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedLoadOriginalAmpData();
	// 函数 OnBnClickedLisFunc
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedLisFunc();

	// 函数 OnExportExperimentData
	// 作用：响应 Windows 或自定义消息 OnExportExperimentData。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnExportExperimentData();
	// 函数 OnExportCurvePicture
	// 作用：响应 Windows 或自定义消息 OnExportCurvePicture。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnExportCurvePicture();
	// 函数 OnExportTemperatureData
	// 作用：响应 Windows 或自定义消息 OnExportTemperatureData。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnExportTemperatureData();

	// 函数 OnSaveAsExperimentFile
	// 作用：响应 Windows 或自定义消息 OnSaveAsExperimentFile。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnSaveAsExperimentFile();
	// 函数 OnSaveAsTemplateFile
	// 作用：响应 Windows 或自定义消息 OnSaveAsTemplateFile。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnSaveAsTemplateFile();

	// 函数 OnBnClickedAnaParamSet
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedAnaParamSet();

	// 函数 OnAnaParamMenuSetCross
	// 作用：响应 Windows 或自定义消息 OnAnaParamMenuSetCross。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnAnaParamMenuSetCross();
	// 函数 OnAnaParamMenuSetFilter
	// 作用：响应 Windows 或自定义消息 OnAnaParamMenuSetFilter。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnAnaParamMenuSetFilter();
	// 函数 OnSetBaseSet
	// 作用：响应 Windows 或自定义消息 OnSetBaseSet。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnSetBaseSet();
	// 函数 OnSetMotChannelAdjust
	// 作用：响应 Windows 或自定义消息 OnSetMotChannelAdjust。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnSetMotChannelAdjust();
	// 函数 OnSetMeltAnaParam
	// 作用：响应 Windows 或自定义消息 OnSetMeltAnaParam。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnSetMeltAnaParam();

	// 函数 OnChanBtClicked
	// 作用：响应 Windows 或自定义消息 OnChanBtClicked。
	// 参数：nID：整数。
	// 返回：没有返回值。
	afx_msg void OnChanBtClicked(UINT nID);

			// 函数 SetModeExpBaseSet
			// 作用：设置SetModeExpBaseSet。
			// 参数：无。
			// 返回：没有返回值。
			void SetModeExpBaseSet();
			// 函数 SetModeExpProcSet
			// 作用：设置SetModeExpProcSet。
			// 参数：无。
			// 返回：没有返回值。
			void SetModeExpProcSet();
			// 函数 SetModeExpSamSet
			// 作用：设置SetModeExpSamSet。
			// 参数：无。
			// 返回：没有返回值。
			void SetModeExpSamSet();
			// 函数 SetModeExpRunMonitor
			// 作用：设置SetModeExpRunMonitor。
			// 参数：无。
			// 返回：没有返回值。
			void SetModeExpRunMonitor();
			// 函数 SetModeExpDataAnalyse
			// 作用：设置SetModeExpDataAnalyse。
			// 参数：无。
			// 返回：没有返回值。
			void SetModeExpDataAnalyse();

	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL PreTranslateMessage(MSG* pMsg);

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshLanguageDisplay();

public:
	CMyButton m_btClearList;
	CMyButton m_btNew;
	CMyButton m_btOpen;
	CMyButton m_btDelete;
	CMyButton m_btSave;
	CMyButton m_btSaveAs;
	CMyButton m_btAnalyse;
	CMyButton m_btExport;
	CMyButton m_btLis;	//LIS相关功能

	CMyButton m_btPrint;
	CMyCheckButton m_ckbtVerify;
	CMyButton m_btSift;
	CMyButton m_btSetBadHole;
	
	CMyButton m_btUpLoadLisData;
	CMyButton m_btImport;	//导入

	CMyButton m_btReadExeclData; //从Excel中加载原始扩增数据

	CMyButton m_btAnaParamSet;	//分析参数设置，包括滤波参数、串扰设置

	CMyButton m_btReadEeprom;
	CMyButton m_btWriteEeprom;

	static CGeneralPcrDlg*	m_pMainWnd;

	CLinkList<CMyCheckButton*> m_lnkChanBtPtr;

private:
	BOOL m_bCtrlCreated;

	int m_iChanBtW;
	int m_ichanBtH;
	int m_iChanBtInterval;	//通道切换按钮间隔

	BOOL m_bChanShow;	//标识通道切换按钮的显示状态

	CRectManage m_rcManage;
};





