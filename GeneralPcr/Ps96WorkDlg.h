// 【交接】 GeneralPcr\Ps96WorkDlg.h
// 作用：Ps96WorkDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：CPs96WorkDlg、DECLARE_MESSAGE_MAP、OnEraseBkgnd、InitFileManageDlg、SetPageSelected、OpenFile、OpenPowerOffProtectFile、SetCtrlPos。
#pragma once
#include "WorkDlg.h"
#include "Ps96IvdFileManagerDlg.h"

class CPs96WorkDlg : public CWorkDlg
{
public:
	// 函数 CPs96WorkDlg
	// 作用：执行CPs96WorkDlg。
	// 参数：无。
	// 返回：没有返回值。
	CPs96WorkDlg(void);
	// 函数 ~CPs96WorkDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPs96WorkDlg(void);

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

	// 函数 InitFileManageDlg
	// 作用：初始化InitFileManageDlg。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitFileManageDlg();
	// 函数 SetPageSelected
	// 作用：设置SetPageSelected。
	// 参数：iPageId：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int SetPageSelected(int iPageId);
	// 函数 OpenFile
	// 作用：读入OpenFile。
	// 参数：iFileFormat：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int OpenFile(int iFileFormat);	//iFileFormat: 0--全格式，1-qstd格式，2-qsts格式
	// 函数 OpenPowerOffProtectFile
	// 作用：读入OpenPowerOffProtectFile。
	// 参数：strFilePath：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int OpenPowerOffProtectFile(CString strFilePath);
	// 函数 SetCtrlPos
	// 作用：设置SetCtrlPos。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void SetCtrlPos();

			// 函数 AddTemplate
			// 作用：创建或加入AddTemplate。
			// 参数：无。
			// 返回：返回是或否。
			BOOL AddTemplate();
			// 函数 DeleteTemplate
			// 作用：更新或清除DeleteTemplate。
			// 参数：iIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteTemplate(int iIndex);

			// 函数 RefreshExpDlgRunState
			// 作用：更新或清除RefreshExpDlgRunState。
			// 参数：iPageId：整数；bOccupy：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshExpDlgRunState(int iPageId,BOOL bOccupy);

public:
	CPs96IvdFileManagerDlg m_ps96FileManagerDlg;
};

