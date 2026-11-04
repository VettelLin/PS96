// 【交接】 GeneralPcr\CYExpInfoDlg.h
// 作用：CYExpInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CCYExpInfoDlg、DECLARE_MESSAGE_MAP、OnEraseBkgnd、CreateEd、InitEd、SetCtrlPos、ShowCtrl。
#pragma once

//康研葆使用的实验信息页面

#include "ExpeInfoDlg.h"
#include "MyNewEdit.h"

class CCYExpInfoDlg : public CExpeInfoDlg
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CCYExpInfoDlg。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CCYExpInfoDlg)

public:
	// 函数 CCYExpInfoDlg
	// 作用：执行CCYExpInfoDlg。
	// 参数：无。
	// 返回：没有返回值。
	CCYExpInfoDlg(void);
	// 函数 ~CCYExpInfoDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CCYExpInfoDlg(void);

protected:
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

	// 函数 CreateEd
	// 作用：创建或加入CreateEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateEd();
	// 函数 InitEd
	// 作用：初始化InitEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitEd();
	// 函数 SetCtrlPos
	// 作用：设置SetCtrlPos。
	// 参数：无。
	// 返回：没有返回值。
	virtual void SetCtrlPos();
	// 函数 ShowCtrl
	// 作用：改变ShowCtrl的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	virtual void ShowCtrl();

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

public:
	CMyNewEdit m_edReportNo;
};


