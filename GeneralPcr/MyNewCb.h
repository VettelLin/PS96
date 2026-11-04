// 【交接】 GeneralPcr\MyNewCb.h
// 作用：MyNewCb 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyNewCb、DECLARE_MESSAGE_MAP、OnPaint、OnCreate、PreTranslateMessage、LBtDownSpecialProc、GetString。
#pragma once
#include "MyNewEdit.h"
#include "ArrowInfo.h"
#include "MySelWnd.h"

typedef enum CbSelWndState{
	ECSWS_SHOW,ECSWS_HIDE
}ECBSELWNDSTATE;

class CMyNewCb :public CMyNewEdit
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyNewCb。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyNewCb)

public:
	// 函数 CMyNewCb
	// 作用：执行CMyNewCb。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	CMyNewCb(CWnd* pParent = NULL);
	// 函数 ~CMyNewCb
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMyNewCb(void);

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

public:
	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	virtual afx_msg void OnPaint();
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 函数 LBtDownSpecialProc
	// 作用：执行LBtDownSpecialProc。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int LBtDownSpecialProc();

			// 函数 GetString
			// 作用：读取GetString。
			// 参数：iIndex：整数；strText：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetString(int iIndex,CString& strText);
			// 函数 SetItemText
			// 作用：设置SetItemText。
			// 参数：iIndex：整数；strText：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetItemText(int iIndex,CString strText);
			// 函数 InsertString
			// 作用：创建或加入InsertString。
			// 参数：iIndex：整数；strText：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertString(int iIndex,CString strText,BOOL bRedraw = FALSE);
			// 函数 InsertString
			// 作用：创建或加入InsertString。
			// 参数：strText：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertString(CString strText,BOOL bRedraw = FALSE);
			// 函数 DeleteString
			// 作用：更新或清除DeleteString。
			// 参数：iIndex：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteString(int iIndex,BOOL bRedraw = FALSE);
			// 函数 Clear
			// 作用：更新或清除Clear。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int Clear(BOOL bRedraw = FALSE);

	// 函数 OnMsgRowSelectedChange
	// 作用：响应 Windows 或自定义消息 OnMsgRowSelectedChange。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgRowSelectedChange(WPARAM wParam,LPARAM lParam);	
	// 函数 OnMsgHideSonCtrl
	// 作用：响应 Windows 或自定义消息 OnMsgHideSonCtrl。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgHideSonCtrl(WPARAM wParam,LPARAM lParam);	
	// 函数 OnKillFocus
	// 作用：响应 Windows 或自定义消息 OnKillFocus。
	// 参数：pNewWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnKillFocus(CWnd* pNewWnd);

			// 函数 CalcSelWndHeight
			// 作用：计算CalcSelWndHeight。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcSelWndHeight();
	// 函数 SetText
	// 作用：设置SetText。
	// 参数：strText：字符串；bRedraw：是或否；bForbidTellParent：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SetText(CString strText,BOOL bRedraw = TRUE,BOOL bForbidTellParent = FALSE);

			// 函数 SetCurSel
			// 作用：设置SetCurSel。
			// 参数：iIndex：整数；bRedraw：是或否；bForbidTellParent：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCurSel(int iIndex,BOOL bRedraw = TRUE,BOOL bForbidTellParent = FALSE);
			// 函数 GetCurSel
			// 作用：读取GetCurSel。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCurSel();

			// 函数 GetItemCount
			// 作用：读取GetItemCount。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetItemCount();	//获取供选择的所有项的个数

			// 函数 SetDropDown
			// 作用：设置SetDropDown。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetDropDown();	//设置下拉状态
			// 函数 SetDropUp
			// 作用：设置SetDropUp。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetDropUp();	//取消下拉状态

			// 函数 RefreshText
			// 作用：更新或清除RefreshText。
			// 参数：iIndex：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshText(int iIndex,BOOL bRedraw = FALSE);	//语言设置改变后，刷新文本信息

public:
	CMySelWnd m_selWnd;
	CArrowInfo m_arrowInfo;

	ECBSELWNDSTATE m_eCbSelWndState;

private:
	int m_iSelWndH;	//item选择窗口高度
	BOOL m_bFstDown;	//标识是否是第一次弹出下拉选择窗口
};

