// 【交接】 GeneralPcr\MyDateTimeCtrl.h
// 作用：MyDateTimeCtrl 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyDateTimeCtrl、DECLARE_MESSAGE_MAP、OnSize、OnNcPaint、OnPaint、OnLButtonDown、OnEraseBkgnd。
#pragma once

#include "FontSet.h"

// CMyDateTimeCtrl

class CMyDateTimeCtrl : public CDateTimeCtrl,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyDateTimeCtrl。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyDateTimeCtrl)

public:
	// 函数 CMyDateTimeCtrl
	// 作用：执行CMyDateTimeCtrl。
	// 参数：无。
	// 返回：没有返回值。
	CMyDateTimeCtrl();
	// 函数 ~CMyDateTimeCtrl
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyDateTimeCtrl();

protected:
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
	// 函数 OnNcPaint
	// 作用：绘制标题栏等非客户区。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnNcPaint();
	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnDtnDatetimechange
	// 作用：响应 Windows 或自定义消息 OnDtnDatetimechange。
	// 参数：pNMHDR：指针，指向调用方传入的对象；pResult：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult);

			// 函数 SetTellParentDtChangedParam
			// 作用：设置SetTellParentDtChangedParam。
			// 参数：bTell：是或否；iDtTypeTag：整数。
			// 返回：没有返回值。
			void SetTellParentDtChangedParam(BOOL bTell,int iDtTypeTag);
			// 函数 IsTllParentDtChanged
			// 作用：判断IsTllParentDtChanged是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsTllParentDtChanged();
			// 函数 GetDtTypeTag
			// 作用：读取GetDtTypeTag。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetDtTypeTag();

protected:
	BOOL m_bTellParentDtChanged;	//通知父窗口日期已变更
	int m_iDtTypeTag;
};


