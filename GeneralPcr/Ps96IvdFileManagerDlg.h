// 【交接】 GeneralPcr\Ps96IvdFileManagerDlg.h
// 作用：Ps96IvdFileManagerDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：CPs96IvdFileManagerDlg、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnCreate、OnLButtonDown、SetCtrlPos、SetPageSwitchBtPos、AddNewPage。
#pragma once
#include "filemanagedlg.h"

class CPs96IvdFileManagerDlg :public CFileManageDlg
{
public:
	// 函数 CPs96IvdFileManagerDlg
	// 作用：执行CPs96IvdFileManagerDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	CPs96IvdFileManagerDlg(CWnd* pParent = NULL);
	// 函数 ~CPs96IvdFileManagerDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPs96IvdFileManagerDlg(void);

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
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
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

public:
	CRect m_rcAddIcon;

protected:
	int m_iAddIconWHFat;
	int m_iAddIconWHThin;
	int m_iAddIconLeftIndent;
};

