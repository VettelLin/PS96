// 【交接】 GeneralPcr\StartPageDlg.h
// 作用：开机首页声明。m_vecInstruSerial 只保存读到的序列号，用于提示文字。
// 先看这些函数：DECLARE_DYNAMIC、CStartPageDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnLButtonDown、OnTimer、OnMsgDiscernInstrumentRst。
#pragma once

#include "FontSet.h"
#include "MyStatic.h"
#include "Gif.h"
#include "Resource.h"

class CStartPageDlg: public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CStartPageDlg：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CStartPageDlg)

public:
	// 函数 CStartPageDlg
	// 作用：执行CStartPageDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CStartPageDlg(CWnd* pParent = NULL);
	// 函数 ~CStartPageDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CStartPageDlg(void);

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
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 函数 OnMsgDiscernInstrumentRst
	// 作用：响应 Windows 或自定义消息 OnMsgDiscernInstrumentRst。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgDiscernInstrumentRst(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgDeviceFirstConnect
	// 作用：响应 Windows 或自定义消息 OnMsgDeviceFirstConnect。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgDeviceFirstConnect(WPARAM wParam,LPARAM lParam);

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
			void CreateEd();
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
			void InitEd();
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

	// 函数 DiscernInstrumentTd
	// 作用：执行DiscernInstrumentTd。
	// 参数：pParam：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	static	UINT DiscernInstrumentTd(LPVOID pParam);	//仪器识别线程

public:
	CString m_strStartPath;
	CString m_strWarningTip;	//警告信息（自检结果）
	vector<CString> m_vecInstruSerial;

	CMyStatic m_stTipInfo;	//提示信息
	CGif m_gifHanding;	//处理中gif

private:
	int m_iWidth;	//窗口宽度
	int m_iHeight;	//窗口高度
	int m_iHeaderH;	//标题高度

	int m_iRoundAngle;	//圆角数值
	int m_iFrameW;	//边框宽度
};

