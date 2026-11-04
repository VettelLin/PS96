// 【交接】 GeneralPcr\ExpeInfoDlg.h
// 作用：ExpeInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CExpeInfoDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnBnClickedSelectPath、OnMsgTellParentTextChanged。
#pragma once

#include "MyButton.h"
#include "MyStatic.h"
#include "MyNewEdit.h"
#include "ExperimentInfo.h"
#include "EditModeAbs.h"
#include "RectManage.h"
#include "resource.h"

class CExpeInfoDlg : public CDialogEx,public CFontSet,public CEditModeAbs,public CRectManage
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CExpeInfoDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CExpeInfoDlg)

public:
	// 函数 CExpeInfoDlg
	// 作用：执行CExpeInfoDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CExpeInfoDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CExpeInfoDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CExpeInfoDlg();

// Dialog Data
	enum {IDD = IDD_MIDDLEDLG};

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
	afx_msg void OnSize(UINT nType,int cx,int cy);
	// 函数 OnBnClickedSelectPath
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSelectPath();
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam);

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
			// 函数 CreateSt
			// 作用：创建或加入CreateSt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSt();
			// 函数 CreateCb
			// 作用：创建或加入CreateCb。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCb();
	// 函数 CreateEd
	// 作用：创建或加入CreateEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateEd();
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
			// 函数 InitCb
			// 作用：初始化InitCb。
			// 参数：无。
			// 返回：没有返回值。
			void InitCb();
	// 函数 InitEd
	// 作用：初始化InitEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitEd();
			// 函数 InitOneEd
			// 作用：初始化InitOneEd。
			// 参数：pEdit：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InitOneEd(CMyNewEdit* pEdit);
	// 函数 SetCtrlPos
	// 作用：设置SetCtrlPos。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void SetCtrlPos();
	// 函数 ShowCtrl
	// 作用：改变ShowCtrl的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void ShowCtrl();

	// 函数 SetCtrlText
	// 作用：设置SetCtrlText。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void SetCtrlText();

	// 函数 GetExperiInfo
	// 作用：读取GetExperiInfo。
	// 参数：experiInfo。
	// 返回：没有返回值。
	virtual	void GetExperiInfo(CExperimentInfo& experiInfo);
	// 函数 SetExperiInfo
	// 作用：设置SetExperiInfo。
	// 参数：experiInfo。
	// 返回：没有返回值。
	virtual	void SetExperiInfo(CExperimentInfo& experiInfo);

	// 函数 SetCtrlEnableState
	// 作用：设置SetCtrlEnableState。
	// 参数：bEnabled：是或否。
	// 返回：没有返回值。
	virtual	void SetCtrlEnableState(BOOL bEnabled);
	// 函数 ClearPage
	// 作用：更新或清除ClearPage。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void ClearPage();
	// 函数 RefreshLanguageDisplay
	// 作用：更新或清除RefreshLanguageDisplay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int RefreshLanguageDisplay();
	// 函数 SetEditMode
	// 作用：设置SetEditMode。
	// 参数：eExpEditMode。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int SetEditMode(EEXPEDITMODE eExpEditMode);

			// 函数 GetExpName
			// 作用：读取GetExpName。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetExpName();

public:
	CMyButton m_btSelectDir;

	CMyNewEdit m_edExpeName;
	CMyNewEdit m_edSavePath;
	CMyNewEdit m_edRemark;

private:
	BOOL m_bCtrlCreated;
};
