// 【交接】 BWGenUILib\ColorComboBox.h
// 作用：ColorComboBox。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：DECLARE_DYNAMIC、CColorComboBox、AddString、GetColor、EnableShowText、DrawItem、MeasureItem、DECLARE_MESSAGE_MAP。
#pragma once


// CColorComboBox

class AFX_EXT_CLASS CColorComboBox : public CComboBox
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CColorComboBox：颜色。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CColorComboBox)

public:
	// 函数 CColorComboBox
	// 作用：执行CColorComboBox。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableShowText。
	CColorComboBox();
	// 函数 ~CColorComboBox
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableShowText。
	virtual ~CColorComboBox();

public:
	// 函数 AddString
	// 作用：创建或加入AddString。
	// 参数：lpszString；clrItem：颜色。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 EnableShowText。
	int AddString(LPCTSTR lpszString, COLORREF clrItem);
	// 函数 GetColor
	// 作用：读取GetColor。
	// 参数：iIndex：整数。
	// 返回：返回 COLORREF。
	// 过程：函数里会调用 EnableShowText。
	COLORREF GetColor(int iIndex);
	// 函数 EnableShowText
	// 作用：改变EnableShowText的显示或可用状态。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableShowText(BOOL bEnable) { m_bShowText = bEnable; }

protected:
	BOOL m_bShowText;

	int	m_iMaxItem;
	COLORREF*	m_pItemColor;
	CSize	m_sizeColorArea;
	int		m_iColorBorder;
	BOOL	m_bIsDropList;
	int		m_iEditHeight;

protected:
	// 函数 DrawItem
	// 作用：绘制DrawItem。
	// 参数：lpDrawItemStruct。
	// 返回：没有返回值。
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// 函数 MeasureItem
	// 作用：执行MeasureItem。
	// 参数：lpMeasureItemStruct。
	// 返回：没有返回值。
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()
};


