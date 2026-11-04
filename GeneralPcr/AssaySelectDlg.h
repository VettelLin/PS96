// 【交接】 GeneralPcr\AssaySelectDlg.h
// 作用：AssaySelectDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CAssaySelDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnBnClickedLoadProc、OnBnClickedAddTemplate。

#pragma once

#include "FontSet.h"
#include "MyButton.h"
#include "MyLstCtrl.h"
#include "RectManage.h"
#include "ExperimentData.h"
#include "EditModeAbs.h"
#include "Resource.h"
#include "MyNewCb.h"

class CPs96SimpleDlg;

class CAssaySelDlg : public CDialogEx,public CFontSet,public CEditModeAbs
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CAssaySelDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CAssaySelDlg)

public:
	// 函数 CAssaySelDlg
	// 作用：执行CAssaySelDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CAssaySelDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CAssaySelDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CAssaySelDlg();

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
	afx_msg void OnSize(UINT nType,int cx,int cy);
	// 函数 OnBnClickedLoadProc
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedLoadProc();
	// 函数 OnBnClickedAddTemplate
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedAddTemplate();
	// 函数 OnBnClickedDeleteTemplate
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedDeleteTemplate();
	// 函数 OnBnClickedExportIdTemplate
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedExportIdTemplate();
	// 函数 OnBnClickedExportResult
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedExportResult();
	// 函数 OnMsgRowSelectedChange
	// 作用：响应 Windows 或自定义消息 OnMsgRowSelectedChange。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgRowSelectedChange(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam);
	// 函数 OnBnClickedEditUpThreshold
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedEditUpThreshold();

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
			// 函数 CreateEd
			// 作用：创建或加入CreateEd。
			// 参数：无。
			// 返回：没有返回值。
			void CreateEd();
			// 函数 CreateCb
			// 作用：创建或加入CreateCb。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCb();
			// 函数 CreateLst
			// 作用：创建或加入CreateLst。
			// 参数：无。
			// 返回：没有返回值。
			void CreateLst();

			// 函数 InitDlg
			// 作用：初始化InitDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitDlg();
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
			// 函数 InitEd
			// 作用：初始化InitEd。
			// 参数：无。
			// 返回：没有返回值。
			void InitEd();
			// 函数 InitCb
			// 作用：初始化InitCb。
			// 参数：无。
			// 返回：没有返回值。
			void InitCb();
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

			// 函数 SetEditMode
			// 作用：设置SetEditMode。
			// 参数：eExpEditMode。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetEditMode(EEXPEDITMODE eExpEditMode);

			// 函数 SetLstAssays
			// 作用：设置SetLstAssays。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLstAssays();

			// 函数 HandleTemplateFileLstRowSelectChanged
			// 作用：执行HandleTemplateFileLstRowSelectChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int HandleTemplateFileLstRowSelectChanged();

			// 函数 RefreshExpEmbody
			// 作用：更新或清除RefreshExpEmbody。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshExpEmbody();
			// 函数 ClearExpEmbody
			// 作用：更新或清除ClearExpEmbody。
			// 参数：无。
			// 返回：没有返回值。
			void ClearExpEmbody();

			// 函数 SetExpDataPtr
			// 作用：设置SetExpDataPtr。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void SetExpDataPtr(CExperimentData* pExpData);

			// 函数 SetTemplateListSelectedRow
			// 作用：设置SetTemplateListSelectedRow。
			// 参数：iIndex：整数。
			// 返回：没有返回值。
			void SetTemplateListSelectedRow(int iIndex);
			// 函数 NewTemplateAdded
			// 作用：执行NewTemplateAdded。
			// 参数：iIndex：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int NewTemplateAdded(int iIndex,BOOL bRedraw = TRUE);
			// 函数 DeleteTemplateListRow
			// 作用：更新或清除DeleteTemplateListRow。
			// 参数：iIndex：整数。
			// 返回：没有返回值。
			void DeleteTemplateListRow(int iIndex);
			// 函数 InitOneBt
			// 作用：初始化InitOneBt。
			// 参数：pBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitOneBt(CMyButton* pBt);

			// 函数 ReshowReportTemplate
			// 作用：执行ReshowReportTemplate。
			// 参数：无。
			// 返回：没有返回值。
			void ReshowReportTemplate();
			// 函数 ReorderTemplateList
			// 作用：执行ReorderTemplateList。
			// 参数：iIndex：整数。
			// 返回：没有返回值。
			void ReorderTemplateList(int iIndex);

public:
	CMyButton m_btLoadProc;
	CMyButton m_btAddTem;
	CMyButton m_btDelTem;
	CMyButton m_btExportIdTemplate;
	CMyButton m_btExportResult;

	CMyLstCtrl m_lstAssaySel;

	CExperimentData* m_pExpData;
	CPs96SimpleDlg* m_pParent;

	CMyNewCb	m_cbReportTemplate;
	CMyNewEdit	m_edRemark;	

	//CMyNewCb	m_cbUpThreshold;
	//CMyNewEdit	m_edUpThreshold;	
	CMyButton	m_btnEditThreshold;

private:
	BOOL m_bCtrlCreated;
	CRectManage m_rcManage;
};



