// 【交接】 GeneralPcr\WorkDlg.h
// 作用：WorkDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CWorkDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnSize、OnEraseBkgnd、OnShowWindow、OnInitDialog。
#pragma once

#include "MiddleDlg.h"
#include "FileManageDlg.h"
#include "LinkList.h"
#include "RectManage.h"
#include "FontSet.h"
// CWorkDlg dialog

class CWorkDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CWorkDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CWorkDlg)

public:
	// 函数 CWorkDlg
	// 作用：执行CWorkDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CWorkDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CWorkDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CWorkDlg();

// Dialog Data
	enum { IDD = IDD_WORKDLG };

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
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnShowWindow
	// 作用：响应 Windows 或自定义消息 OnShowWindow。
	// 参数：bShow：是或否；nStatus：整数。
	// 返回：没有返回值。
	afx_msg void OnShowWindow(BOOL bShow,UINT nStatus);

	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
	// 函数 CreateCtrl
	// 作用：创建或加入CreateCtrl。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateCtrl();
			// 函数 CreateCkbt
			// 作用：创建或加入CreateCkbt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCkbt();
	// 函数 InitCtrl
	// 作用：初始化InitCtrl。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitCtrl();
			// 函数 InitCkbt
			// 作用：初始化InitCkbt。
			// 参数：无。
			// 返回：没有返回值。
			void InitCkbt();
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
			// 函数 InitSonDlg
			// 作用：初始化InitSonDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSonDlg();
	// 函数 InitFileManageDlg
	// 作用：初始化InitFileManageDlg。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitFileManageDlg();

	// 函数 SetPageSelected
	// 作用：设置SetPageSelected。
	// 参数：pageId。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int SetPageSelected(int pageId);

			// 函数 AddNewPage
			// 作用：创建或加入AddNewPage。
			// 参数：pageId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AddNewPage(int pageId);
			// 函数 DeletePage
			// 作用：更新或清除DeletePage。
			// 参数：pageId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeletePage(int pageId);

			// 函数 OpenFile
			// 作用：读入OpenFile。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int OpenFile();	//打开工程文件
	// 函数 OpenPowerOffProtectFile
	// 作用：读入OpenPowerOffProtectFile。
	// 参数：strFilePath：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int OpenPowerOffProtectFile(CString strFilePath);
			// 函数 OpenOriginalData
			// 作用：读入OpenOriginalData。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int OpenOriginalData();	//打开原始扩增数据文件

			// 函数 SavePrj
			// 作用：把SavePrj写入文件、仪器或界面。
			// 参数：iIndex：整数；bNew：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SavePrj(int iIndex,BOOL bNew);
			// 函数 DeletePrj
			// 作用：更新或清除DeletePrj。
			// 参数：iIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeletePrj(int iIndex);

			// 函数 GetMiddleDlg
			// 作用：读取GetMiddleDlg。
			// 参数：iPageId：整数。
			// 返回：返回指针 CMiddleDlg*。指针为空表示没有取到对象。
			CMiddleDlg* GetMiddleDlg(int iPageId);

			// 函数 Delete
			// 作用：更新或清除Delete。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int Delete();

			// 函数 NewTemplateAdded
			// 作用：执行NewTemplateAdded。
			// 参数：iIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int NewTemplateAdded(int iIndex);	//新的模板文件成功添加

			// 函数 GetCurrentPageId
			// 作用：读取GetCurrentPageId。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCurrentPageId();	//获取当前选中页面的ID

			// 函数 IsRunningProcessExist
			// 作用：判断IsRunningProcessExist是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsRunningProcessExist(); //获取是否有正在运行的实验

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshLanguageDisplay();

			// 函数 SetDefaultGeneName
			// 作用：设置SetDefaultGeneName。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetDefaultGeneName();
			// 函数 SetInstrumentConnectState
			// 作用：设置SetInstrumentConnectState。
			// 参数：strModel：字符串；strSN：字符串；bConnected：是或否；bReshowList：是或否。
			// 返回：没有返回值。
			void SetInstrumentConnectState(CString strModel, CString strSN, BOOL bConnected, BOOL bReshowList);
			// 函数 OnMsgInstrumentReinitialize
			// 作用：响应 Windows 或自定义消息 OnMsgInstrumentReinitialize。
			// 参数：wParam；lParam。
			// 返回：返回 LRESULT。
			afx_msg LRESULT OnMsgInstrumentReinitialize(WPARAM wParam,LPARAM lParam);

public:
	CLinkList<CMiddleDlg*> m_lnkPageDlgPtr;
	CMiddleDlg* m_pCurSelPageDlg;
	CFileManageDlg m_fileManageDlg;

	CRectManage m_rcManage;

private:
	BOOL m_bCtrlCreated;
};
