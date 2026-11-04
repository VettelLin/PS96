// 【交接】 GeneralPcr\InstrumentInfoDlg.h
// 作用：InstrumentInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CInstrumentInfoDlg、GetInstruInfo、SetInstruInfo、ClearPage、RefreshLanguageDisplay、SetCtrlEnableState、SetSelectedInstrument。
#pragma once

#include "MyButton.h"
#include "MyStatic.h"
#include "MyCheckButton.h"
#include "MyNewCb.h"
#include "MyNewEdit.h"
#include "ExperimentInfo.h"
#include "resource.h"
#include "EditModeAbs.h"
#include "MyNewCb.h"
#include "RectManage.h"

const UINT WM_INSTRUMENT_REINITIALIZE = WM_USER + 1601; // 连接仪器重新初始化
const UINT WM_INSTRUMENT_SELECTED = WM_USER + 1602; // 当前选择使用设备序号



class CInstrumentInfoDlg : public CDialogEx,public CFontSet,public CEditModeAbs
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CInstrumentInfoDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CInstrumentInfoDlg)

public:
	// 函数 CInstrumentInfoDlg
	// 作用：执行CInstrumentInfoDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CInstrumentInfoDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CInstrumentInfoDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CInstrumentInfoDlg();

// Dialog Data
	enum {IDD = IDD_MIDDLEDLG};

public:
	// 函数 GetInstruInfo
	// 作用：读取GetInstruInfo。
	// 参数：info。
	// 返回：没有返回值。
	void GetInstruInfo(CExperimentInfo& info);
	// 函数 SetInstruInfo
	// 作用：设置SetInstruInfo。
	// 参数：info。
	// 返回：没有返回值。
	void SetInstruInfo(CExperimentInfo& info);

	// 函数 ClearPage
	// 作用：更新或清除ClearPage。
	// 参数：无。
	// 返回：没有返回值。
	void ClearPage();
	// 函数 RefreshLanguageDisplay
	// 作用：更新或清除RefreshLanguageDisplay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int RefreshLanguageDisplay();
	// 函数 SetCtrlEnableState
	// 作用：设置SetCtrlEnableState。
	// 参数：bEnabled：是或否。
	// 返回：没有返回值。
	void SetCtrlEnableState(BOOL bEnabled);
	// 函数 SetSelectedInstrument
	// 作用：设置SetSelectedInstrument。
	// 参数：strModel：字符串；strSN：字符串。
	// 返回：没有返回值。
	void SetSelectedInstrument(CString strModel, CString strSN);
	// 函数 ReshowInstrumentList
	// 作用：执行ReshowInstrumentList。
	// 参数：无。
	// 返回：没有返回值。
	void ReshowInstrumentList();
	// 函数 SetEditMode
	// 作用：设置SetEditMode。
	// 参数：eExpEditMode。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int SetEditMode(EEXPEDITMODE eExpEditMode);


protected:
	// 函数 CreateCtrl
	// 作用：创建或加入CreateCtrl。
	// 参数：无。
	// 返回：没有返回值。
	void CreateCtrl();
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
	// 函数 InitCb
	// 作用：初始化InitCb。
	// 参数：无。
	// 返回：没有返回值。
	void InitCb();
	// 函数 SetCtrlPos
	// 作用：设置SetCtrlPos。
	// 参数：无。
	// 返回：没有返回值。
	void SetCtrlPos();
	// 函数 ResetCtrlPos
	// 作用：更新或清除ResetCtrlPos。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	void ResetCtrlPos(BOOL bRedraw = FALSE);
	// 函数 ShowCtrl
	// 作用：改变ShowCtrl的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	void ShowCtrl();

	// 函数 SetCtrlText
	// 作用：设置SetCtrlText。
	// 参数：无。
	// 返回：没有返回值。
	void SetCtrlText();

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

	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType,int cx,int cy);
	// 函数 OnBnClickedFindInstrument
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedFindInstrument();
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam);

protected:
	// 函数 InitInstrument
	// 作用：初始化InitInstrument。
	// 参数：无。
	// 返回：没有返回值。
	void InitInstrument();
	// 函数 CombineModelAndSN
	// 作用：执行CombineModelAndSN。
	// 参数：strModel：字符串；strSN：字符串。
	// 返回：返回一段文字。
	CString CombineModelAndSN(CString strModel,CString strSN);
	// 函数 CanRunExperiment
	// 作用：判断CanRunExperiment是否成立。
	// 参数：iSelDevice：整数。
	// 返回：没有返回值。
	void CanRunExperiment(int iSelDevice);

public:
	CMyNewCb m_cbInstrumentType;
	CMyButton m_btnFindInstrument; // 查找设备

	CMyCheckButton m_ckbtLidSet;
	CMyCheckButton m_ckbtTempCtrl;


private:
	BOOL m_bCtrlCreated;
};
