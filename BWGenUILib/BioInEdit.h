// 【交接】 BWGenUILib\BioInEdit.h
// 作用：BioInEdit 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CBioInEdit、GetInitText、EnableNumEdit、EnableMinus、SetPrecision、OnCreate、OnChar。
#pragma once

#include <Float.h>

// CBioInEdit

/**
 * \ingroup ScanSolution
 *
 * 完成在列表控件或树型控件中的文本编辑，发送消息到父类，父类只能是ListCtrl或TreeCtrl。
 * 如果是数字编辑，只能处理整数
 * \par requirements
 * win98 or later\n
 * win2k or later\n
 * MFC\n
 *
 * \version 1.0
 * first version
 *
 * \date 2005-01-21
 *
 * \author 车从俊
 *
 * \par license
 * 本产品代码归北京博奥生物芯片有限责任公司所有。
 * 
 * \todo 
 *
 * \bug 
 *
 */
class AFX_EXT_CLASS CBioInEdit : public CEdit
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CBioInEdit。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CBioInEdit)

public:
	// 函数 CBioInEdit
	// 作用：执行CBioInEdit。
	// 参数：nItem：整数；nSubItem：整数；strText：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableMinus。
	CBioInEdit(int nItem, int nSubItem, CString strText);
	// 函数 CBioInEdit
	// 作用：执行CBioInEdit。
	// 参数：hItem；nSubItem：整数；strText：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableMinus。
	CBioInEdit(HTREEITEM hItem, int nSubItem, CString strText);

	// 函数 ~CBioInEdit
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableMinus。
	virtual ~CBioInEdit();

	// 函数 GetInitText
	// 作用：读取GetInitText。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 EnableMinus。
	CString GetInitText();

	// 函数 EnableNumEdit
	// 作用：改变EnableNumEdit的显示或可用状态。
	// 参数：dMinValue：小数；dMaxValue：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableMinus。
	void EnableNumEdit(double dMinValue=-DBL_MAX, double dMaxValue=DBL_MAX);
	// 函数 EnableMinus
	// 作用：改变EnableMinus的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableMinus(){m_bIsMinus=TRUE;}
	// 函数 SetPrecision
	// 作用：设置SetPrecision。
	// 参数：nInPrecision：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPrecision(UINT nInPrecision){m_nPrecision=nInPrecision;}

	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 IsTabDown。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnChar
	// 作用：响应 Windows 或自定义消息 OnChar。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 IsTabDown。
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 OnKillFocus
	// 作用：响应 Windows 或自定义消息 OnKillFocus。
	// 参数：pNewWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 IsTabDown。
	afx_msg void OnKillFocus(CWnd* pNewWnd);

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

protected:
// Attributes

	/** \brief 父窗口类型集合
	*
	* 表示父窗口的类型，当前只完成ListCtrl、TreeCtrl
	*/
	enum eParentType
	{		
		TYPE_LISTCTRL = 0, ///< 列表控件
		TYPE_TREECTRL = 1  ///< 树行控件
	};
	eParentType m_nParentType;///< 父窗口的类型，需要据此判断发送的消息类型

	
	int m_nItem; ///< 当父窗口是ListCtrl时的行数
	int m_nSubItem;///< 每行数据列数

	CString m_strInitText;///< 编辑的初始字符串
	HTREEITEM m_hItem;///< 当父窗口是TreeCtrl时的项句柄

	BOOL m_bIsNumEdit;  ///< 表明是否是数字编辑
	BOOL m_bEscPressed; ///< 表明是否Esc键被输入
	BOOL m_bIsMinus; ///< 是否支持负数，默认为正数
	double m_dMinValue; ///< 最小值
	double m_dMaxValue; ///< 最大值
	UINT m_nPrecision; ///< 浮点数的精度

	CFont* m_pFont; 
	
	BOOL m_bTabDown;

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

public:
	// 函数 OnKeyDown
	// 作用：响应 Windows 或自定义消息 OnKeyDown。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


