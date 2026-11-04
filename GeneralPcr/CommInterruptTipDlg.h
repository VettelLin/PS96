// 【交接】 GeneralPcr\CommInterruptTipDlg.h
// 作用：CommInterruptTipDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CCommInterruptTipDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnCreate、OnInitDialog、CreateCtrl。

#pragma once

#include "MyButton.h"
#include "MyStatic.h"
#include "RectManage.h"
#include "resource.h"
#include "InstancePCR.h"
#include "ExperimentData.h"



class CCommInterruptTipDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CCommInterruptTipDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CCommInterruptTipDlg)

public:
	// 函数 CCommInterruptTipDlg
	// 作用：执行CCommInterruptTipDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CCommInterruptTipDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CCommInterruptTipDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CCommInterruptTipDlg();

	enum {IDD = IDD_POPUPDLG};

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
			// 函数 CreateSt
			// 作用：创建或加入CreateSt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSt();
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
	// 函数 OnBnClickedCancel
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCancel();
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT_PTR nIDEvent);

			// 函数 SetNoteInfo
			// 作用：设置SetNoteInfo。
			// 参数：strNoteInfo：字符串。
			// 返回：没有返回值。
			void SetNoteInfo(CString strNoteInfo);
			// 函数 GetNoteInfo
			// 作用：读取GetNoteInfo。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetNoteInfo();

			// 函数 SetNoteInfoStyle
			// 作用：设置SetNoteInfoStyle。
			// 参数：style。
			// 返回：没有返回值。
			void SetNoteInfoStyle(DWORD style);
			// 函数 GetNoteInfoStyle
			// 作用：读取GetNoteInfoStyle。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			DWORD GetNoteInfoStyle();

			// 函数 SetRoundRect
			// 作用：设置SetRoundRect。
			// 参数：x；y。
			// 返回：返回是或否。
			BOOL SetRoundRect(int x = 5,int y = 5);

public:
	CMyButton m_btStop;
	CMyStatic m_stIcon;
	CMyStatic m_stNoteInfo;
	CMyStatic m_stTimeInfo;

	int m_retCode;	//弹窗返回值，0:重新连接PCR正常 1:连接到时 2:中止实验
	CInstancePCR*	m_pInstancePCR; // PCR实例
	CExperimentData* m_pExpData; // 实验数据
	int m_iRemainSec;	//实验剩余时间

private:
	int m_roundValue;	//圆角数值
	int m_frameWidth;	//边框宽度

	CString m_strNoteInfo;	//提示信息
	CString m_strReconnect;

	int   m_noteFontSize;//单位为磅
	DWORD m_dwNoteStyle;
	int m_width;
	int m_height;
	int m_iCapHeight;
	CRectManage m_rcManage;

	UINT	m_nRunTimer1;
	UINT	m_nRunTimer2;
	int		m_iTimeCount;
	
	// 函数 PrepareRunning
	// 作用：执行PrepareRunning。
	// 参数：无。
	// 返回：返回是或否。
	BOOL PrepareRunning();
	// 函数 RunLidHeader
	// 作用：执行RunLidHeader。
	// 参数：无。
	// 返回：返回是或否。
	BOOL RunLidHeader();
};
