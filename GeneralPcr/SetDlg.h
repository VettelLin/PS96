// 【交接】 GeneralPcr\SetDlg.h
// 作用：SetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CSetDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnInitDialog、CreateBt、InitDlg。

#pragma once

#include "MyButton.h"
#include "MyStatic.h"
#include "LisSetDlg.h"
#include "UserManageSetDlg.h"
#include "Ps96SetDlg.h"
#include "CYNormSetDlg.h"
#include "SystemSetDlg.h"
#include "RectManage.h"

typedef enum _SETPAGETYPE
{
	LISSETDLG = 1,USERMANAGESETDLG,PS96SETDLG,SYSTEMSETDLG
}SETPAGETYPE;

class CSetDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CSetDlg：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CSetDlg)

public:
	// 函数 CSetDlg
	// 作用：执行CSetDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CSetDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CSetDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CSetDlg();

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
			// 函数 CreateBt
			// 作用：创建或加入CreateBt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateBt();
			// 函数 InitDlg
			// 作用：初始化InitDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitDlg();

			// 函数 IntFunBtn
			// 作用：执行IntFunBtn。
			// 参数：无。
			// 返回：没有返回值。
			void IntFunBtn();
			// 函数 InitBt
			// 作用：初始化InitBt。
			// 参数：无。
			// 返回：没有返回值。
			void InitBt();
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

			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：eSetPageType。
			// 返回：没有返回值。
			void SetPageSelected(SETPAGETYPE eSetPageType);
			// 函数 UpdateFuncBtMode
			// 作用：更新或清除UpdateFuncBtMode。
			// 参数：无。
			// 返回：没有返回值。
			void UpdateFuncBtMode();

			// 函数 OnBnClickedSwtLisSet
			// 作用：响应按钮点击。
			// 参数：无。
			// 返回：没有返回值。
			afx_msg void OnBnClickedSwtLisSet();
			// 函数 OnBnClickedSwtUserManageSet
			// 作用：响应按钮点击。
			// 参数：无。
			// 返回：没有返回值。
			afx_msg void OnBnClickedSwtUserManageSet();
			// 函数 OnBnClickedSwtPs96Set
			// 作用：响应按钮点击。
			// 参数：无。
			// 返回：没有返回值。
			afx_msg void OnBnClickedSwtPs96Set();
			// 函数 OnBnClickedSwtSystemSet
			// 作用：响应按钮点击。
			// 参数：无。
			// 返回：没有返回值。
			afx_msg void OnBnClickedSwtSystemSet();

			// 函数 OnBnClickedAdd
			// 作用：响应按钮点击。
			// 参数：无。
			// 返回：没有返回值。
			afx_msg void OnBnClickedAdd();
			// 函数 OnBnClickedEdit
			// 作用：响应按钮点击。
			// 参数：无。
			// 返回：没有返回值。
			afx_msg void OnBnClickedEdit();	
			// 函数 OnBnClickedDelete
			// 作用：响应按钮点击。
			// 参数：无。
			// 返回：没有返回值。
			afx_msg void OnBnClickedDelete();

			// 函数 OnSize
			// 作用：窗口大小变化时重新摆放控件。
			// 参数：nType：整数；cx；cy。
			// 返回：没有返回值。
			afx_msg void OnSize(UINT nType, int cx, int cy);

					// 函数 RefreshLanguageDisplay
					// 作用：更新或清除RefreshLanguageDisplay。
					// 参数：无。
					// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
					int RefreshLanguageDisplay();

public:
	int	m_iFunBtnHeight;
	CMyButton m_btnAdd;	//新增
	CMyButton m_btnEdit;	//编辑
	CMyButton m_btnDelete;
	

	CMyButton* m_pCurSelSwt;
	CDialogEx* m_pCurSelDlg;

	CMyButton m_swtLisSet;
	CMyButton m_swtUserManageSet;
	CMyButton m_swtInstru1Set;	
	CMyButton m_swtSysSet;

	CLisSetDlg m_lisSetDlg;
	CUserManageSetDlg m_userManageSetDlg;

#ifdef CAN_YOUNG
	CCYNormSetDlg m_ps96SetDlg;
#else
	CPs96SetDlg m_ps96SetDlg;
#endif

private:
	BOOL m_bCtrlCreated;
};



