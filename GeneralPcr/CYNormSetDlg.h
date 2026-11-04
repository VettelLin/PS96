// 【交接】 GeneralPcr\CYNormSetDlg.h
// 作用：CYNormSetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CCYNormSetDlg、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnMsgTellParentTextChanged、CreateEd、InitEd、SetCtrlPos。
#pragma once

#include "MyNewEdit.h"
#include "Ps96SetDlg.h"

class CCYNormSetDlg :public CPs96SetDlg
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CCYNormSetDlg。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CCYNormSetDlg)

public:
	// 函数 CCYNormSetDlg
	// 作用：执行CCYNormSetDlg。
	// 参数：无。
	// 返回：没有返回值。
	CCYNormSetDlg(void);
	// 函数 ~CCYNormSetDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CCYNormSetDlg(void);

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
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam,LPARAM lParam);

	// 函数 CreateEd
	// 作用：创建或加入CreateEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual void CreateEd();
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
	// 函数 ResetCtrlPos
	// 作用：更新或清除ResetCtrlPos。
	// 参数：无。
	// 返回：没有返回值。
	virtual void ResetCtrlPos();
	// 函数 ShowCtrl
	// 作用：改变ShowCtrl的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	virtual void ShowCtrl();

	// 函数 SetCtrlText
	// 作用：设置SetCtrlText。
	// 参数：无。
	// 返回：没有返回值。
	virtual void SetCtrlText();

	// 函数 RefreshLanguageDisplay
	// 作用：更新或清除RefreshLanguageDisplay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int RefreshLanguageDisplay();

public:
	CMyNewEdit m_edClient;	//委托单位
	CMyNewEdit m_edCpAdr;	//委托单位的地址
};

