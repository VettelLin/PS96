// 【交接】 GeneralPcr\PrjManageDlg.h
// 作用：PrjManageDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CPrjManageDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnCreate、OnInitDialog。
#pragma once

#include "FontSet.h"
#include "MyLstCtrl.h"
#include "PrjManageBaseInfoDlg.h"
#include "ReagentItem.h"
#include "MyButton.h"
#include "RectManage.h"

// CPrjManageDlg dialog

typedef enum PrjManageSonPage{
	EPMSP_BASE,EPMSP_RSTJUDGE
}EPRJMANAGESONPAGE;

class CGeneralPcrDlg;

class CPrjManageDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CPrjManageDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CPrjManageDlg)

public:
	// 函数 CPrjManageDlg
	// 作用：执行CPrjManageDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPrjManageDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CPrjManageDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CPrjManageDlg();

// Dialog Data
	enum { IDD = IDD_PRJMANAGEDLG };

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
			// 函数 CreateLst
			// 作用：创建或加入CreateLst。
			// 参数：无。
			// 返回：没有返回值。
			void CreateLst();
			// 函数 InitCtrl
			// 作用：初始化InitCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void InitCtrl();
			// 函数 InitLst
			// 作用：初始化InitLst。
			// 参数：无。
			// 返回：没有返回值。
			void InitLst();
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
			
			// 函数 SetCtrlText
			// 作用：设置SetCtrlText。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlText();

			// 函数 SetPrjManageLstInfo
			// 作用：设置SetPrjManageLstInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetPrjManageLstInfo();

			// 函数 SetReagentItem
			// 作用：设置SetReagentItem。
			// 参数：reagentItem；bSetEditableState：是或否。
			// 返回：没有返回值。
			void SetReagentItem(CReagentItem& reagentItem,BOOL bSetEditableState = TRUE);
			// 函数 GetReagentItem
			// 作用：读取GetReagentItem。
			// 参数：reagentItem。
			// 返回：没有返回值。
			void GetReagentItem(CReagentItem& reagentItem);

			// 函数 SetPrjEditableState
			// 作用：设置SetPrjEditableState。
			// 参数：bEditable：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetPrjEditableState(BOOL bEditable,BOOL bRedraw);

	// 函数 OnMsgRowSelectedChange
	// 作用：响应 Windows 或自定义消息 OnMsgRowSelectedChange。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgRowSelectedChange(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgChannelDyeNameChanged
	// 作用：响应 Windows 或自定义消息 OnMsgChannelDyeNameChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgChannelDyeNameChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnBnClickedSwtBtPrjBaseInfoDlg
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtPrjBaseInfoDlg();
	// 函数 OnBnClickedSwtBtJudgeDlg
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtJudgeDlg();

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
	// 函数 OnBnClickedDelete
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedDelete();

	// 函数 SetNewPrjBaseInfo
	// 作用：设置SetNewPrjBaseInfo。
	// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
	// 返回：没有返回值。
	void SetNewPrjBaseInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/);

			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：ePrjManageSonPage。
			// 返回：没有返回值。
			void SetPageSelected(EPRJMANAGESONPAGE ePrjManageSonPage);

			// 函数 ResetPrjManageLstText
			// 作用：更新或清除ResetPrjManageLstText。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ResetPrjManageLstText();

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshLanguageDisplay();

protected:
	// 函数 InsertOneItemToList
	// 作用：创建或加入InsertOneItemToList。
	// 参数：iIndex：整数；pItem：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void InsertOneItemToList(int iIndex, CReagentItem* pItem);

public:
	int	m_iFunBtnHeight;



	CMyLstCtrl m_lstSelPrj;

	CPrjManageBaseInfoDlg m_prjManageBaseInfoDlg;

	CGeneralPcrDlg* m_pMainDlg;

	CMyButton m_swtBtPrjBaseInfoDlg;
	CMyButton m_swtBtRstJudgeDlg;

private:
	BOOL m_bCtrlCreated;
	CMyButton m_btnNew;
	CMyButton m_btnOpen;
	CMyButton m_btnSave;
	CMyButton m_btnDelete;

	int m_iSwitchBtBkH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtBkW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值
	int m_iSwitchBtW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值

	CMyButton* m_pCurSelSwt;
	CWnd* m_pCurSelWnd;
};
