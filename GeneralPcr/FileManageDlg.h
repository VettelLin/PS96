// 【交接】 GeneralPcr\FileManageDlg.h
// 作用：FileManageDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CFileManageDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnCreate、OnInitDialog。
#pragma once

#include "MyPageSwitchBt.h"

#include "resource.h"
#include "RectManage.h"
#include "ExperimentData.h"

#include <GdiPlus.h>
#include <vector>

using namespace std;

// CFileManageDlg dialog

class CWorkDlg;

#define BT_X_INDENT	1	//从第二个按钮开始，页面按钮左移像素数
#define BT_TOP_START	0	//页面切换按钮顶部

class CFileManageDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CFileManageDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CFileManageDlg)

public:
	// 函数 CFileManageDlg
	// 作用：执行CFileManageDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CFileManageDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CFileManageDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CFileManageDlg();

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

			// 函数 InitDlg
			// 作用：初始化InitDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitDlg();

	// 函数 SetCtrlPos
	// 作用：设置SetCtrlPos。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void SetCtrlPos();
	// 函数 SetPageSwitchBtPos
	// 作用：设置SetPageSwitchBtPos。
	// 参数：iStart：整数。
	// 返回：没有返回值。
	virtual	void SetPageSwitchBtPos(int iStart);
			// 函数 ShowCtrl
			// 作用：改变ShowCtrl的显示或可用状态。
			// 参数：无。
			// 返回：没有返回值。
			void ShowCtrl();

public:
	// 函数 OnPageSelected
	// 作用：响应 Windows 或自定义消息 OnPageSelected。
	// 参数：nID：整数。
	// 返回：没有返回值。
	afx_msg void OnPageSelected(UINT nID);
	// 函数 OnMsgClosePage
	// 作用：响应 Windows 或自定义消息 OnMsgClosePage。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgClosePage(WPARAM wParam,LPARAM lParam);

			// 函数 AddPage
			// 作用：创建或加入AddPage。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AddPage();	//添加新页面，外部使用
	// 函数 AddNewPage
	// 作用：创建或加入AddNewPage。
	// 参数：pExpData：指针，指向调用方传入的对象；strFileName：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int AddNewPage(CExperimentData* pExpData,CString strFileName = _T(""));
	// 函数 DeletePage
	// 作用：更新或清除DeletePage。
	// 参数：pageId。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int DeletePage(int pageId);
			// 函数 SetNewFileSavePath
			// 作用：设置SetNewFileSavePath。
			// 参数：strNewFileSavePath：字符串。
			// 返回：没有返回值。
			void SetNewFileSavePath(CString strNewFileSavePath);	//实验开始后，更新实验路径信息到实验切换按钮中
			// 函数 SetPageFirstColumn
			// 作用：设置SetPageFirstColumn。
			// 参数：pageId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetPageFirstColumn(int pageId);	//设置页面按钮为第一列位置
			// 函数 SetPageSwitchBtState
			// 作用：设置SetPageSwitchBtState。
			// 参数：pageId；bRunning：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetPageSwitchBtState(int pageId,BOOL bRunning,BOOL bRedraw = TRUE);	//设置按钮为非运行状态（普通状态）
			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：pageId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetPageSelected(int pageId);
			// 函数 SetCurrentSelectPageString
			// 作用：设置SetCurrentSelectPageString。
			// 参数：strFileName：字符串；strFilePath：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCurrentSelectPageString(CString strFileName,CString strFilePath);
			// 函数 SetExperName
			// 作用：设置SetExperName。
			// 参数：pageId；strExpeName：字符串。
			// 返回：没有返回值。
			void SetExperName(int pageId,CString strExpeName);
			// 函数 CheckFileExistOrNot
			// 作用：判断CheckFileExistOrNot是否成立。
			// 参数：strFilePath：字符串。
			// 返回：返回是或否。
			BOOL CheckFileExistOrNot(CString strFilePath);	//判断文件是否已经打开
			// 函数 SetPageFilePath
			// 作用：设置SetPageFilePath。
			// 参数：iPageId：整数；strFilePath：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetPageFilePath(int iPageId,CString strFilePath);
			// 函数 CheckFileNameExistOrNot
			// 作用：判断CheckFileNameExistOrNot是否成立。
			// 参数：strFileName：字符串。
			// 返回：返回是或否。
			BOOL CheckFileNameExistOrNot(CString strFileName);	//判断是否存在 相同文件名 的实验已被打开

	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual	BOOL PreTranslateMessage(MSG* pMsg);

			// 函数 InitPageSwitchBt
			// 作用：初始化InitPageSwitchBt。
			// 参数：pPageSwitchBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitPageSwitchBt(CMyPageSwitchBt* pPageSwitchBt);

public:
	CLinkList<CMyPageSwitchBt*> m_lnkPageSwitchBtPtr;

	Image m_imgLogo;
	Image m_imgLogo2;

public:
	int m_iBtHeight;	//按钮默认高度

	CMyPageSwitchBt* m_pCurSelBt;

	CWorkDlg* m_pWorkDlg;

	BOOL m_bCtrlCreated;

	int m_iLeftIndent;	//标识第一个按钮到窗口左侧的距离
	int m_iRightIndent;	//标识最后一个按钮到窗口左侧的距离
	int m_iBtDefWidth;	//按钮默认宽度
	int m_iBtRealWidth;	//实际使用的按钮宽度
	int m_iBtPreRealW;	//记录上一次使用的按钮宽度
	int m_iBtRegionW;	//按钮区域宽度

	CRectManage m_rcManage;
};


