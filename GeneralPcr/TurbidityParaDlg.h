// 【交接】 GeneralPcr\TurbidityParaDlg.h
// 作用：TurbidityParaDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CTurbidityParaDlg、SetTurbidityPara、HasChanged、EnableMOTChannlePara、DoDataExchange、DECLARE_MESSAGE_MAP、OnInitDialog。
#pragma once

#include "Resource.h"
#include "CalibrateParaTurbidity.h"

// CTurbidityParaDlg dialog

class CTurbidityParaDlg : public CDialog
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CTurbidityParaDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CTurbidityParaDlg)

public:
	// 函数 CTurbidityParaDlg
	// 作用：执行CTurbidityParaDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CTurbidityParaDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CTurbidityParaDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CTurbidityParaDlg();

// Dialog Data
	enum { IDD = IDD_TURBIDITY_PARA_DLG };

public:
	BOOL	m_bSetChanged;
	// 函数 SetTurbidityPara
	// 作用：设置SetTurbidityPara。
	// 参数：pTuibidityPara：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTurbidityPara(CCalibrateParaTurbidity* pTuibidityPara) { m_pTuibidityPara = pTuibidityPara;}

private:
	CCalibrateParaTurbidity* m_pTuibidityPara;

	

	// 函数 HasChanged
	// 作用：判断HasChanged是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL HasChanged();
	// 函数 EnableMOTChannlePara
	// 作用：改变EnableMOTChannlePara的显示或可用状态。
	// 参数：nChannel：整数。
	// 返回：没有返回值。
	void EnableMOTChannlePara(int nChannel);

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
	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
	// 函数 OnOK
	// 作用：用户确认当前对话框。
	// 参数：无。
	// 返回：没有返回值。
	virtual void OnOK();
	BOOL m_bSaveDefault;

	CString m_strDye1;
	CString m_strChannel1;
	BOOL m_bUseMOT1;
	int m_nMotAhead1;
	float m_fMotRatio1;

	CString m_strDye2;
	CString m_strChannel2;
	BOOL m_bUseMOT2;
	int m_nMotAhead2;
	float m_fMotRatio2;

	CString m_strDye3;
	CString m_strChannel3;
	BOOL m_bUseMOT3;
	int m_nMotAhead3;
	float m_fMotRatio3;

	CString m_strDye4;
	CString m_strChannel4;
	BOOL m_bUseMOT4;
	int m_nMotAhead4;
	float m_fMotRatio4;

	CString m_strDye5;
	CString m_strChannel5;
	BOOL m_bUseMOT5;
	int m_nMotAhead5;
	float m_fMotRatio5;

	float m_fMOTMinRatio;

	// 函数 OnBnClickedCheckUseMot1
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckUseMot1();
	// 函数 OnBnClickedCheckUseMot2
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckUseMot2();
	// 函数 OnBnClickedCheckUseMot3
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckUseMot3();
	// 函数 OnBnClickedCheckUseMot4
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckUseMot4();
	// 函数 OnBnClickedCheckUseMot5
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckUseMot5();
	// 函数 OnBnClickedCheckCurveAdjust1
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckCurveAdjust1();
	// 函数 OnBnClickedCheckCurveAdjust2
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckCurveAdjust2();
	// 函数 OnBnClickedCheckCurveAdjust3
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckCurveAdjust3();
	// 函数 OnBnClickedCheckCurveAdjust4
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckCurveAdjust4();
	// 函数 OnBnClickedCheckCurveAdjust5
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCheckCurveAdjust5();
};
