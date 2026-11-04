// 【交接】 BWGenUILib\BWColorWnd.h
// 作用：BWColorWnd 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：_T、DECLARE_DYNAMIC、CBWColorWnd、SetColor、HasChanged、SetChanged、GetColorCount、GetColor。
#pragma once

const CString CLASSNAME_BWCOLORWND =  _T("BWCOLORWND");

// CBWColorWnd

class AFX_EXT_CLASS CBWColorWnd : public CWnd
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CBWColorWnd：颜色。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CBWColorWnd)

public:
	// 函数 CBWColorWnd
	// 作用：执行CBWColorWnd。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 HasChanged。
	CBWColorWnd();
	// 函数 CBWColorWnd
	// 作用：执行CBWColorWnd。
	// 参数：iItem：整数；iSubItem：整数；clrInit：颜色；iCount：整数；pArrayColor：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 HasChanged。
	CBWColorWnd(int iItem, int iSubItem, COLORREF clrInit, int iCount, COLORREF* pArrayColor);
	// 函数 ~CBWColorWnd
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 HasChanged。
	virtual ~CBWColorWnd();

// Attributes
public:
	// 函数 SetColor
	// 作用：设置SetColor。
	// 参数：iCount：整数；pInputColor：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 HasChanged。
	void SetColor(int iCount, COLORREF* pInputColor);
	// 函数 HasChanged
	// 作用：判断HasChanged是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL HasChanged() { return m_bChanged; }
	// 函数 SetChanged
	// 作用：设置SetChanged。
	// 参数：bChanged：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetChanged(BOOL bChanged) { m_bChanged = bChanged; }

	// 函数 GetColorCount
	// 作用：读取GetColorCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetColorCount() { return m_iColorCount; }
	// 函数 GetColor
	// 作用：读取GetColor。
	// 参数：iIndex：整数。
	// 返回：返回 COLORREF。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	COLORREF GetColor(int iIndex) { return m_pArrayColor[iIndex]; }

	// 函数 SetPopup
	// 作用：设置SetPopup。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPopup(BOOL bEnable) { m_bPopup = bEnable; }
	// 函数 GetInitColor
	// 作用：读取GetInitColor。
	// 参数：无。
	// 返回：返回 COLORREF。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	COLORREF GetInitColor() { return m_clrInit; }

protected:
	int			m_iColorCount;
	COLORREF*	m_pArrayColor;
	int		m_iColCount;
	int		m_iRowCount;
	BOOL	m_bChanged;

	typedef CArray<CRect, CRect> CCRectArray;
	CCRectArray	m_arrayCellArea;

	int m_iRowClicked;
	int m_iColClicked;

	BOOL	m_bPopup;

	int m_iItem;
	int	m_iSubItem;
	COLORREF m_clrInit;

protected:
	// 函数 RegisterWindowClass
	// 作用：执行RegisterWindowClass。
	// 参数：无。
	// 返回：返回是或否。
	BOOL RegisterWindowClass();

	// 函数 CalculateColAndRow
	// 作用：计算CalculateColAndRow。
	// 参数：iCount：整数。
	// 返回：没有返回值。
	void CalculateColAndRow(int iCount);
	// 函数 SendDisplayInfo
	// 作用：执行SendDisplayInfo。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	void SendDisplayInfo(int iIndex = -1);

public:
	// 函数 Create
	// 作用：创建或加入Create。
	// 参数：dwStyle；rect：矩形区域；pParentWnd：指针，指向调用方传入的对象；nID：整数。
	// 返回：返回是或否。
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()
	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();
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
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnKillFocus
	// 作用：响应 Windows 或自定义消息 OnKillFocus。
	// 参数：pNewWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnKillFocus(CWnd* pNewWnd);
};


