// 【交接】 GeneralPcr\PrjManageBaseInfoDlg.h
// 作用：PrjManageBaseInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CPrjManageBaseInfoDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnInitDialog、InitSonDlg。

#pragma once

#include "MyButton.h"
#include "MyInsertBt.h"
#include "PrjBaseInfoDlg.h"
#include "MyLstCtrl.h"
#include "MySamPlateDlg.h"
#include "SamBaseInfoEditDlg.h"
#include "MySegDlg.h"
#include "ReagentItem.h"
#include "InterfaceB.h"
#include "RectManage.h"

class CPrjManageBaseInfoDlg : public CDialogEx,public CFontSet,public CInterfaceB
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CPrjManageBaseInfoDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CPrjManageBaseInfoDlg)

public:
	// 函数 CPrjManageBaseInfoDlg
	// 作用：执行CPrjManageBaseInfoDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPrjManageBaseInfoDlg (CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CPrjManageBaseInfoDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CPrjManageBaseInfoDlg ();

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

	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
			// 函数 InitSonDlg
			// 作用：初始化InitSonDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSonDlg();
			// 函数 InitPrjBaseInfoDlg
			// 作用：初始化InitPrjBaseInfoDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitPrjBaseInfoDlg();
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
			// 函数 CreateEd
			// 作用：创建或加入CreateEd。
			// 参数：无。
			// 返回：没有返回值。
			void CreateEd();
			// 函数 CreateLst
			// 作用：创建或加入CreateLst。
			// 参数：无。
			// 返回：没有返回值。
			void CreateLst();
			// 函数 CreateSegment
			// 作用：创建或加入CreateSegment。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSegment();
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
			// 函数 InitSt
			// 作用：初始化InitSt。
			// 参数：无。
			// 返回：没有返回值。
			void InitSt();
			// 函数 InitEd
			// 作用：初始化InitEd。
			// 参数：无。
			// 返回：没有返回值。
			void InitEd();
			// 函数 InitLst
			// 作用：初始化InitLst。
			// 参数：无。
			// 返回：没有返回值。
			void InitLst();
			// 函数 InitSegment
			// 作用：初始化InitSegment。
			// 参数：无。
			// 返回：没有返回值。
			void InitSegment();

			// 函数 InitLstBaseParam
			// 作用：初始化InitLstBaseParam。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstBaseParam();
			// 函数 InitLstMeltParam
			// 作用：初始化InitLstMeltParam。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstMeltParam();
			// 函数 InitLstCrossParam
			// 作用：初始化InitLstCrossParam。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstCrossParam();
			// 函数 InitLstChanSet
			// 作用：初始化InitLstChanSet。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstChanSet();
			// 函数 SetCtrlPos
			// 作用：设置SetCtrlPos。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlPos();
			// 函数 SetLstChanTargetColumnWidth
			// 作用：设置SetLstChanTargetColumnWidth。
			// 参数：iChanNum：整数。
			// 返回：没有返回值。
			void SetLstChanTargetColumnWidth(int iChanNum);

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

			// 函数 InitInsertBt
			// 作用：初始化InitInsertBt。
			// 参数：pInsertBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitInsertBt(CMyInsertBt *pInsertBt);
			// 函数 InitOtherBt
			// 作用：初始化InitOtherBt。
			// 参数：pBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitOtherBt(CMyButton *pBt);

			// 函数 ResetLstChanCross
			// 作用：更新或清除ResetLstChanCross。
			// 参数：iChanCount：整数；lnkDyeName。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ResetLstChanCross(int iChanCount,CLinkList<CString>& lnkDyeName);
			// 函数 ResetLstCrossOneChannelName
			// 作用：更新或清除ResetLstCrossOneChannelName。
			// 参数：iChanId：整数；strDye：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ResetLstCrossOneChannelName(int iChanId,CString strDye);	//项目的某个通道染料名称改变了

			// 函数 SetPrjInfoBaseInfo
			// 作用：设置SetPrjInfoBaseInfo。
			// 参数：reagentItem。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetPrjInfoBaseInfo(CReagentItem& reagentItem);
			// 函数 GetPrjInfoBaseInfo
			// 作用：读取GetPrjInfoBaseInfo。
			// 参数：reagentItem。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetPrjInfoBaseInfo(CReagentItem& reagentItem);
			
			// 函数 SetChanTargetInfo
			// 作用：设置SetChanTargetInfo。
			// 参数：reagentItem。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetChanTargetInfo(CReagentItem& reagentItem);
			// 函数 GetChanTargetInfo
			// 作用：读取GetChanTargetInfo。
			// 参数：reagentItem。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetChanTargetInfo(CReagentItem& reagentItem);

			// 函数 SetLstAmlAnaBaseParam
			// 作用：设置SetLstAmlAnaBaseParam。
			// 参数：pAnalysisPara：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLstAmlAnaBaseParam(CDataAnalysisPara* pAnalysisPara);
			// 函数 GetLstAmlAnaBaseParam
			// 作用：读取GetLstAmlAnaBaseParam。
			// 参数：pAnalysisPara：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetLstAmlAnaBaseParam(CDataAnalysisPara* pAnalysisPara);

			// 函数 SetLstMeltParam
			// 作用：设置SetLstMeltParam。
			// 参数：pAnalysisPara：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLstMeltParam(CDataAnalysisPara* pAnalysisPara);
			// 函数 GetLstMeltParam
			// 作用：读取GetLstMeltParam。
			// 参数：pAnalysisPara：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetLstMeltParam(CDataAnalysisPara* pAnalysisPara);

			// 函数 SetChanCrossParam
			// 作用：设置SetChanCrossParam。
			// 参数：pCrosstalkPara：指针，指向调用方传入的对象；iChanCount：整数；lnkDyeName。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetChanCrossParam(double* pCrosstalkPara,int iChanCount,CLinkList<CString>& lnkDyeName);
			// 函数 GetChanCrossParam
			// 作用：读取GetChanCrossParam。
			// 参数：pCrosstalkPara：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetChanCrossParam(double* pCrosstalkPara);

	// 函数 OnBnClickedInsertSegment
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedInsertSegment();
	// 函数 OnBnClickedInsertStep
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedInsertStep();
	// 函数 OnBnClickedEditStep
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedEditStep();
	// 函数 OnBnClickedEditSegment
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedEditSegment();
	// 函数 OnBnClickedDelete
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedDelete();

	// 函数 OnFileMenuSegInsertBefore
	// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertBefore。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuSegInsertBefore();
	// 函数 OnFileMenuSegInsertAfter
	// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertAfter。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuSegInsertAfter();
	// 函数 OnFileMenuSegInsertLast
	// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertLast。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuSegInsertLast();

	// 函数 OnFileMenuStepInsertBefore
	// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertBefore。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuStepInsertBefore();
	// 函数 OnFileMenuStepInsertAfter
	// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertAfter。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuStepInsertAfter();
	// 函数 OnFileMenuStepInsertLast
	// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertLast。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuStepInsertLast();

	// 函数 OnMsgPrjTypeChanged
	// 作用：响应 Windows 或自定义消息 OnMsgPrjTypeChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgPrjTypeChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTellParentLstCellChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentLstCellChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentLstCellChanged(WPARAM wParam,LPARAM lParam);		

	// 函数 OnBnClickedAddTarget
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedAddTarget();
	// 函数 OnBnClickedDeleteTarget
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedDeleteTarget();
	// 函数 OnMsgRowSelectedChange
	// 作用：响应 Windows 或自定义消息 OnMsgRowSelectedChange。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgRowSelectedChange(WPARAM wParam,LPARAM lParam);

			// 函数 SetReagentItem
			// 作用：设置SetReagentItem。
			// 参数：reagentItem。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetReagentItem(CReagentItem& reagentItem);
			// 函数 GetReagentItem
			// 作用：读取GetReagentItem。
			// 参数：reagentItem。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetReagentItem(CReagentItem& reagentItem);

			// 函数 SetEditState
			// 作用：设置SetEditState。
			// 参数：bEditable：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetEditState(BOOL bEditable,BOOL bRedraw = FALSE);

	// 函数 SetNewPrjBaseInfo
	// 作用：设置SetNewPrjBaseInfo。
	// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
	// 返回：没有返回值。
	virtual	void SetNewPrjBaseInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/);

			// 函数 SetPrjDyeInfo
			// 作用：设置SetPrjDyeInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetPrjDyeInfo();

			// 函数 ResetLstAmlColumnText
			// 作用：更新或清除ResetLstAmlColumnText。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstAmlColumnText();
			// 函数 ResetLstMeltColumnText
			// 作用：更新或清除ResetLstMeltColumnText。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstMeltColumnText();
			// 函数 ResetLstChanSetText
			// 作用：更新或清除ResetLstChanSetText。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstChanSetText();
			// 函数 ResetLstCrossText
			// 作用：更新或清除ResetLstCrossText。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstCrossText();

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshLanguageDisplay();
			// 函数 IsAmlBaseParamLegal
			// 作用：判断IsAmlBaseParamLegal是否成立。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int IsAmlBaseParamLegal();

protected:
	// 函数 SetOneAmlBaseParam
	// 作用：设置SetOneAmlBaseParam。
	// 参数：iRowIndex：整数；pInputParam：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void SetOneAmlBaseParam(int iRowIndex, tagAnaAmplifyPara* pInputParam);
	// 函数 ResetAmlListColumnWidth
	// 作用：更新或清除ResetAmlListColumnWidth。
	// 参数：无。
	// 返回：没有返回值。
	void ResetAmlListColumnWidth();
	// 函数 ResetAmlListChannelArray
	// 作用：更新或清除ResetAmlListChannelArray。
	// 参数：无。
	// 返回：没有返回值。
	void ResetAmlListChannelArray();

public:
	CPrjBaseInfoDlg m_prjBaseInfoDlg;

	CMyLstCtrl m_lstChanSet;

	CMyLstCtrl m_lstAmlBaseParam;	//基本参数
	CMyButton m_btnAddTarget; // 增加一个基因参数
	CMyButton m_btnDeleteTarget; // 删除一个基因参数

	CMyLstCtrl m_lstMeltParam;	//熔解曲线参数
	CMyLstCtrl m_lstCrossParam;	//交叉干扰参数


	CMySegDlg m_segDlg;

	CMyInsertBt m_btInsertSegment;
	CMyInsertBt m_btInsertStep;
	CMyButton m_btEditStep;
	CMyButton m_btEditSegment;
	CMyButton m_btDelete;

	CFontSet m_fontNormal;

	int m_iDyeChangeChanId;	//记录染料名称变更时的通道Id
	CString m_strDyeChangeName;	//记录染料名称变更时的染料名称

private:
	BOOL m_bCtrlCreated;
	BOOL m_bEditable;	//标识当前窗口是否可编辑
	CRectManage m_rcManage;
};


