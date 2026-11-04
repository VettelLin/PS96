// 【交接】 GeneralPcr\Ps96SetDlg.h
// 作用：Ps96SetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CPs96SetDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnInitDialog、CreateCtrl、CreateBt。

#pragma once

#include "FontSet.h"
#include "MyButton.h"
#include "MyNewEdit.h"
#include "MyNewCb.h"
#include "MyCheckButton.h"
#include "RectManage.h"
#include "Resource.h"

class CPs96SetDlg : public CDialogEx,public CFontSet,public CRectManage
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CPs96SetDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CPs96SetDlg)

public:
	// 函数 CPs96SetDlg
	// 作用：执行CPs96SetDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPs96SetDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CPs96SetDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CPs96SetDlg();

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
	// 函数 CreateEd
	// 作用：创建或加入CreateEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual void CreateEd();
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
	// 函数 InitEd
	// 作用：初始化InitEd。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitEd();
			// 函数 InitOneEd
			// 作用：初始化InitOneEd。
			// 参数：pEd：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InitOneEd(CMyNewEdit* pEd);
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

	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	// 函数 OnBnClickedBtAnaSet
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtAnaSet();
	// 函数 OnBnClickedBtSaveLidTem
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtSaveLidTem();
	// 函数 OnBnClickedBtSaveLidPreheatTem
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtSaveLidPreheatTem();
	// 函数 OnBnClickedBtReadLidTem
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtReadLidTem();
	// 函数 OnBnClickedBtReadLidPreheatTem
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtReadLidPreheatTem();
	// 函数 OnBnClickedBtTransportLock
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtTransportLock();

	// 函数 OnBnClickedCkbtExportSamHori
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCkbtExportSamHori();
	// 函数 OnBnClickedCkbtExportSamVert
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCkbtExportSamVert();
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam,LPARAM lParam);

			// 函数 SaveLidTem
			// 作用：把SaveLidTem写入文件、仪器或界面。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SaveLidTem();
			// 函数 ReadLidTem
			// 作用：读取ReadLidTem。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadLidTem();
			// 函数 SaveLidPreheatTem
			// 作用：把SaveLidPreheatTem写入文件、仪器或界面。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SaveLidPreheatTem();
			// 函数 ReadLidPreheatTem
			// 作用：读取ReadLidPreheatTem。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadLidPreheatTem();

	// 函数 RefreshLanguageDisplay
	// 作用：更新或清除RefreshLanguageDisplay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int RefreshLanguageDisplay();

			// 函数 LanguageChanged
			// 作用：执行LanguageChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int LanguageChanged();

public:
	CMyNewEdit m_edLidTem;	//热盖工作温度
	CMyNewEdit m_edLidTemInit;	//仪器开机热盖预热温度

	CMyNewCb m_cbLangSel;

	CMyCheckButton m_ckbtExportSamHori;	//导出样本信息时横向导出
	CMyCheckButton m_ckbtExportSamVert;	//导出样本信息时纵向导出

	CMyButton m_btSaveLidTem;
	CMyButton m_btReadLidTem;
	CMyButton m_btSaveLidPreheatTem;
	CMyButton m_btReadLidPreheatTem;
	CMyButton m_btAnaSet;

	CMyButton	m_btnTransportLock;

private:
	BOOL m_bCtrlCreated;

	// 函数 GetShowPreheadLid
	// 作用：读取GetShowPreheadLid。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetShowPreheadLid();
};
