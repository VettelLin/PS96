// 【交接】 GeneralPcr\CYSamInfoDlg.h
// 作用：CYSamInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CCYSamInfoDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnMsgDateCtrlChanged、OnMsgTellParentTextChanged、OnMsgTellParentSetNewText。
#pragma once

#include "SamInfoDlg.h"
#include "MyNewCb.h"
#include "MyNewEdit.h"

class CCYSamInfoDlg : public CSamInfoDlg
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CCYSamInfoDlg。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CCYSamInfoDlg)

public:
	// 函数 CCYSamInfoDlg
	// 作用：执行CCYSamInfoDlg。
	// 参数：pParent：指针，指向调用方传入的对象；pIfC：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	CCYSamInfoDlg(CWnd* pParent = NULL,CInterfaceC* pIfC = NULL);
	// 函数 ~CCYSamInfoDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CCYSamInfoDlg(void);

protected:
	// 函数 DoDataExchange
	// 作用：把对话框控件和成员变量绑在一起。
	// 参数：pDX：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	virtual void DoDataExchange(CDataExchange* pDX);

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
	// 函数 OnMsgDateCtrlChanged
	// 作用：响应 Windows 或自定义消息 OnMsgDateCtrlChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgDateCtrlChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam,LPARAM lParam);

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
	virtual void CreateDt();

	// 函数 InitCb
	// 作用：初始化InitCb。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitCb();
	// 函数 InitEd
	// 作用：初始化InitEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitEd();
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
	// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SetCYSamInfo(CExperimentData* pExpData,BOOL bRedraw = FALSE);

public:
	CMyNewCb m_cbSamCategory;	//样品类别

	CMyNewEdit m_edSamCount;	//样品数量
	CMyNewEdit m_edSamState;	//样品状态
	CMyNewEdit m_edProductBN;	//产品批号
	CMyNewEdit m_edTestItem;	//检测项目
	CMyNewEdit m_edComment;	//实验备注，不同于单个样本孔位的备注

	COleDateTime m_oleCYDt;
	CMyDateTimeCtrl m_dtCYCollectDate;
};

