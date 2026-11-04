// 【交接】 GeneralPcr\SamInfoDlg.h
// 作用：SamInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CSamInfoDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnMsgDateCtrlChanged、OnMsgTellParentTextChanged。
#pragma once

#include "MyNewEdit.h"
#include "MyNewCb.h"
#include "MyDateTimeCtrl.h"
#include "SamNameAutoSetInfo.h"
#include "CalibAutoSetInfo.h"
#include "SelfDefType.h"
#include "TubeInfo.h"
#include "FontSet.h"
#include "EditModeAbs.h"
#include "RectManage.h"
#include "InterfaceC.h"
#include "ExperimentData.h"

class CSamInfoDlg : public CDialogEx,public CFontSet,public CEditModeAbs,public CRectManage
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CSamInfoDlg：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CSamInfoDlg)

public:
	// 函数 CSamInfoDlg
	// 作用：执行CSamInfoDlg。
	// 参数：pParent：指针，指向调用方传入的对象；pIfC：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CSamInfoDlg(CWnd* pParent = NULL,CInterfaceC* pIfC = NULL);   // standard constructor
	// 函数 ~CSamInfoDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CSamInfoDlg();

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

	// 函数 OnMsgDateCtrlChanged
	// 作用：响应 Windows 或自定义消息 OnMsgDateCtrlChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgDateCtrlChanged(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam);

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
			// 函数 CreateCkbt
			// 作用：创建或加入CreateCkbt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCkbt();
			// 函数 CreateSt
			// 作用：创建或加入CreateSt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSt();
	// 函数 CreateCb
	// 作用：创建或加入CreateCb。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateCb();
	// 函数 CreateEd
	// 作用：创建或加入CreateEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateEd();
	// 函数 CreateDt
	// 作用：创建或加入CreateDt。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateDt();

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
			// 函数 InitCkbt
			// 作用：初始化InitCkbt。
			// 参数：无。
			// 返回：没有返回值。
			void InitCkbt();
			// 函数 InitSt
			// 作用：初始化InitSt。
			// 参数：无。
			// 返回：没有返回值。
			void InitSt();
	// 函数 InitCb
	// 作用：初始化InitCb。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitCb();
			// 函数 InitOneCb
			// 作用：初始化InitOneCb。
			// 参数：pCb：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InitOneCb(CMyNewCb* pCb);
	// 函数 InitEd
	// 作用：初始化InitEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitEd();
			// 函数 InitOneEd
			// 作用：初始化InitOneEd。
			// 参数：pEd：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InitOneEd(CMyNewEdit* pEd);
	// 函数 InitDt
	// 作用：初始化InitDt。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitDt();
		
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

	// 函数 ClearSamInfo
	// 作用：更新或清除ClearSamInfo。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void ClearSamInfo();
	// 函数 SetSamInfo
	// 作用：设置SetSamInfo。
	// 参数：tubeInfo。
	// 返回：没有返回值。
	virtual	void SetSamInfo(CTubeInfo& tubeInfo);

	// 函数 SetEditable
	// 作用：设置SetEditable。
	// 参数：bEditable：是或否。
	// 返回：没有返回值。
	virtual	void SetEditable(BOOL bEditable);
	// 函数 GetEditable
	// 作用：读取GetEditable。
	// 参数：无。
	// 返回：返回是或否。
	virtual	BOOL GetEditable();

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

	// 函数 SetCYSamInfo
	// 作用：设置SetCYSamInfo。
	// 参数：pExpData：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SetCYSamInfo(CExperimentData* pExpData);

public:
	CMyNewCb m_cbSamType;
	CMyNewCb m_cbSexuality;
	
	CMyNewEdit m_edNewId;	//新样本ID
	CMyNewEdit m_edSamName;	//样本号（样本名称）
	CMyNewEdit m_edPaitentName;
	CMyNewEdit m_edAge;
	
	CMyNewEdit m_edSendingDoctor;
	CMyNewEdit m_edSendingSection;	//送检科室
	CMyNewEdit m_edAnamnesisNo;	//病历号
	CMyNewEdit m_edBedNo;	//病床号
	CMyNewEdit m_edHospitalId;	//住院号
	CMyNewEdit m_edOutpatientNo;	//门诊号
	CMyNewEdit m_edRemarks;	//备注

	COleDateTime m_collectDate;
	CMyDateTimeCtrl m_dtCollectDate;

	BOOL m_bEditable;	//页面是否可编辑

	CInterfaceC* m_pIfC;

	BOOL m_bClear;

	BOOL m_bCtrlCreated;
};

