// 【交接】 BWGenUILib\BWInEdit.h
// 作用：BWInEdit 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CBWInEdit、EnableNumEdit、SetPrecision、SetUserFont、IsTabDown、SetFlag、GetInitText。
#pragma once

#include <Float.h>

// CBWInEdit

class AFX_EXT_CLASS CBWInEdit : public CEdit
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CBWInEdit。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetPrecision。
	DECLARE_DYNAMIC(CBWInEdit)

public:
	// 函数 CBWInEdit
	// 作用：执行CBWInEdit。
	// 参数：m_iItem；iSubItem：整数；strText：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetPrecision。
	CBWInEdit(int m_iItem, int iSubItem, CString strText);
	// 函数 ~CBWInEdit
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetPrecision。
	virtual ~CBWInEdit();

	// 函数 EnableNumEdit
	// 作用：改变EnableNumEdit的显示或可用状态。
	// 参数：dMinValue：小数；dMaxValue：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetPrecision。
	void EnableNumEdit(double dMinValue=-DBL_MAX, double dMaxValue=DBL_MAX);
	// 函数 SetPrecision
	// 作用：设置SetPrecision。
	// 参数：nInPrecision：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPrecision(UINT nInPrecision){m_nPrecision=nInPrecision;}
	// 函数 SetUserFont
	// 作用：设置SetUserFont。
	// 参数：lf。
	// 返回：没有返回值。
	// 过程：函数里会调用 IsTabDown。
	void SetUserFont(LOGFONT lf);
	// 函数 IsTabDown
	// 作用：判断IsTabDown是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL IsTabDown(){return m_bTabDown;}
	// 函数 SetFlag
	// 作用：设置SetFlag。
	// 参数：nFlag：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetFlag(UINT nFlag) { m_nFlag = nFlag; }
	// 函数 GetInitText
	// 作用：读取GetInitText。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetInitText() { return m_strInitText; }

protected:
	int m_iItem; // 数据所在行数，可以表示其它含义
	int m_iSubItem;// 每行数据列数，可以表示其它含义
	UINT m_nFlag; // 附加标记
	CString m_strInitText;// 编辑的初始字符串

	BOOL m_bIsNumEdit;  // 表明是否是数字编辑
	double m_dMinValue; // 最小值
	double m_dMaxValue; // 最大值
	UINT m_nPrecision; // 浮点数的精度

	CFont* m_pFont; 
	BOOL m_bTabDown;
	BOOL m_bEscPressed; ///< 表明是否Esc键被输入


protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnChar
	// 作用：响应 Windows 或自定义消息 OnChar。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 OnKillFocus
	// 作用：响应 Windows 或自定义消息 OnKillFocus。
	// 参数：pNewWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	// 函数 OnKeyDown
	// 作用：响应 Windows 或自定义消息 OnKeyDown。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


