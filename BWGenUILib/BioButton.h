// 【交接】 BWGenUILib\BioButton.h
// 作用：BioButton 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CBioButton、IsChecked、SetOnlyIcon、SetButtonFlat、SetButtonSemiflat、SetButtonNormal、SetButtonNoBorder。

#pragma once

//////////////////////////////////////////////////////////////////////
// CBioButton is a CButton derived class.

class AFX_EXT_CLASS CBioButton : public CButton
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CBioButton。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CBioButton)

public:
	// 函数 CBioButton
	// 作用：执行CBioButton。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CBioButton();
    virtual ~CBioButton();
	
	enum eButtonStyle
	{
		BTN_STYLE_FLAT = 0, 
		BTN_STYLE_SEMIFLAT = 1,
		BTN_STYLE_NORMAL = 2,
		BTN_STYLE_NOBORDER = 3,
		BTN_STYLE_CIRCLE = 4,
		BTN_STYLE_THIN_EDGE = 5,
	};

	enum eButtonIconAlign
	{
		BTN_ALIGN_HORZ = 0,
		BTN_ALIGN_VERT = 1,
		BTN_ALIGN_HORZ_RIGHT = 2
	};

	enum eButtonIconType
	{
		BTN_TYPE_NORMAL = 0,
		BTN_TYPE_PRESSED,
		BTN_TYPE_DISABLED,
		BTN_TYPE_HILITED,

		BTN_MAX_TYPES
	};

	enum eButtonColor
	{
		BTN_COLOR_BKGIN = 0, ///< 鼠标在内的背景色
		BTN_COLOR_TXTIN, ///< 鼠标在内的文本色
		BTN_COLOR_BKGOUT,
		BTN_COLOR_TXTOUT,
		BTN_COLOR_BKGFOCUS,
		BTN_COLOR_TXTFOCUS,
		
		BTN_MAX_COLORS
	};

protected:
	CFont	m_fontNormal;
	int		m_nStyle; ///< 按钮风格
	int		m_nAlign; ///< 按钮图标位置
	CToolTipCtrl*	m_pToolTip;
	CFont*	m_pFontText; ///< 文本的字体
	int		m_nCunstomNumber;	// 主要用于Tip、Tube数量的显示，初始化是-1，-1就是不显示
	
	HICON	m_hIcons[BTN_MAX_TYPES];
	CSize	m_sizeImage; // Initial size of the button.
	int		m_nBorderGap; // Gap between the button edge and the image.
	int		m_nImageGap; // Gap between the button text and the image.
	
	COLORREF	m_clrColors[BTN_MAX_COLORS];

	BOOL	m_bHasFlatBorder; ///< 扁平风格鼠标在上时是否绘制边框
	BOOL	m_bIsHilited; ///< 是否高亮，鼠标在按钮上
	BOOL	m_bLBtnDown; // TRUE if the left mouse button is pressed.
	BOOL	m_bPainted;	// Used during paint operations.
	BOOL	m_bIsChecked; ///< TRUE：被选中
	BOOL	m_bDefault; ///< 是否是默认按钮

	BOOL	m_bTransparent; ///< TRUE:按钮是透明的
	BOOL	m_bAutoDisabled; ///< 自动创建非激活图标，使用灰度图
	BOOL	m_bAutoBigger; ///< 在高亮时图标是否变大
	CSize	m_sizeBigImage; ///< 图标在高亮时的大小
	float	m_fBigPercent; ///< 变大比例

	BOOL	m_bGradualColor;
	COLORREF	m_clrTop;
	COLORREF	m_clrBottom;

	BOOL	m_bUser3DColor;
	COLORREF	m_clrUser3DTopLeft;
	COLORREF	m_clrUser3DRightBottom;

	COLORREF	m_clrThinEDGE;
	BOOL		m_bOnlyIcon;
	int			m_nCornerRadius;
	COLORREF	m_clrParentBgk;
	
public:
	// 函数 IsChecked
	// 作用：判断IsChecked是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL IsChecked(){return m_bIsChecked;}
	// 函数 SetOnlyIcon
	// 作用：设置SetOnlyIcon。
	// 参数：bOnlyIcon：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetOnlyIcon(BOOL bOnlyIcon) { m_bOnlyIcon = bOnlyIcon; }

	// 函数 SetButtonFlat
	// 作用：设置SetButtonFlat。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	void SetButtonFlat(BOOL bRedraw=TRUE);
	// 函数 SetButtonSemiflat
	// 作用：设置SetButtonSemiflat。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	void SetButtonSemiflat(BOOL bRedraw=TRUE);
	// 函数 SetButtonNormal
	// 作用：设置SetButtonNormal。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	void SetButtonNormal(BOOL bRedraw=TRUE);
	// 函数 SetButtonNoBorder
	// 作用：设置SetButtonNoBorder。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	void SetButtonNoBorder(BOOL bRedraw=TRUE);
	// 函数 SetButtonDefault
	// 作用：设置SetButtonDefault。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	void SetButtonDefault(BOOL bRedraw=TRUE);
	// 函数 SetButtonCircle
	// 作用：设置SetButtonCircle。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBorderGap。
	void SetButtonCircle(BOOL bRedraw=TRUE);
	// 函数 SetButtonThinEDGE
	// 作用：设置SetButtonThinEDGE。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBorderGap。
	void SetButtonThinEDGE(BOOL bRedraw=TRUE);

	// 函数 SetButtonChecked
	// 作用：设置SetButtonChecked。
	// 参数：bChecked：是或否；bRedraw：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBorderGap。
	void SetButtonChecked(BOOL bChecked, BOOL bRedraw=TRUE);

	// 函数 SetIconRight
	// 作用：设置SetIconRight。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBorderGap。
	void SetIconRight(BOOL bRedraw=TRUE);
	// 函数 SetIconVert
	// 作用：设置SetIconVert。
	// 参数：bRedraw：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBorderGap。
	void SetIconVert(BOOL bRedraw=TRUE);

	// 函数 SetBorderGap
	// 作用：设置SetBorderGap。
	// 参数：nGap：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBorderGap(int nGap){m_nBorderGap=nGap;}
	// 函数 SetImageGap
	// 作用：设置SetImageGap。
	// 参数：nGap：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetImageGap(int nGap){m_nImageGap=nGap;}

	// 函数 SetTextColor
	// 作用：设置SetTextColor。
	// 参数：clrIn：颜色；clrOut：颜色；clrFocus：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBkgInColor。
	void SetTextColor(COLORREF clrIn, COLORREF clrOut=NULL, COLORREF clrFocus=NULL);
	// 函数 SetBkgInColor
	// 作用：设置SetBkgInColor。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBkgInColor(COLORREF clr){m_clrColors[BTN_COLOR_BKGIN] = clr;}
	// 函数 SetTextInColor
	// 作用：设置SetTextInColor。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTextInColor(COLORREF clr){m_clrColors[BTN_COLOR_TXTIN] = clr;}
	// 函数 SetBkgOutColor
	// 作用：设置SetBkgOutColor。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBkgOutColor(COLORREF clr){m_clrColors[BTN_COLOR_BKGOUT] = clr;}
	// 函数 SetTextOutColor
	// 作用：设置SetTextOutColor。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTextOutColor(COLORREF clr){m_clrColors[BTN_COLOR_TXTOUT] = clr;}
	// 函数 SetBkgFocusColor
	// 作用：设置SetBkgFocusColor。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBkgFocusColor(COLORREF clr){m_clrColors[BTN_COLOR_BKGFOCUS] = clr;}
	// 函数 SetTextFocusColor
	// 作用：设置SetTextFocusColor。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTextFocusColor(COLORREF clr){m_clrColors[BTN_COLOR_TXTFOCUS] = clr;}

	// 函数 SetGradualColor
	// 作用：设置SetGradualColor。
	// 参数：clrTop：颜色；clrBottom：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetThinEDGEColor。
	void SetGradualColor(COLORREF clrTop, COLORREF clrBottom);
	// 函数 SetUser3DColor
	// 作用：设置SetUser3DColor。
	// 参数：clrTopLeft：颜色；clrRightBottom：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetThinEDGEColor。
	void SetUser3DColor(COLORREF clrTopLeft, COLORREF clrRightBottom);
	// 函数 SetThinEDGEColor
	// 作用：设置SetThinEDGEColor。
	// 参数：clrThinEdge：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetThinEDGEColor(COLORREF clrThinEdge) { m_clrThinEDGE = clrThinEdge; }
	// 函数 SetParentBkg
	// 作用：设置SetParentBkg。
	// 参数：clrParentBgk：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetParentBkg(COLORREF clrParentBgk) { m_clrParentBgk = clrParentBgk; }
	
	// 函数 SetHasFlatBorder
	// 作用：设置SetHasFlatBorder。
	// 参数：bHas：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetHasFlatBorder(BOOL bHas){m_bHasFlatBorder = bHas;}

	// 函数 SetIcon
	// 作用：设置SetIcon。
	// 参数：size；hIcon；hIconPushed；hIconHilited；bRedraw：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetTransparent。
	virtual BOOL SetIcon(CSize size, HICON hIcon, HICON hIconPushed=NULL, HICON hIconHilited=NULL, BOOL bRedraw=TRUE);
	// 函数 SetIcon
	// 作用：设置SetIcon。
	// 参数：size；nID：整数；nPushedID：整数；nHilitedID：整数；bRedraw：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetTransparent。
	virtual BOOL SetIcon(CSize size, UINT nID, UINT nPushedID=0, UINT nHilitedID=0, BOOL bRedraw=TRUE);
	// 函数 SetIcon
	// 作用：设置SetIcon。
	// 参数：size；lpszID；lpszPushedID；lpszHilitedID；bRedraw：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetTransparent。
	virtual BOOL SetIcon(CSize size, LPCTSTR lpszID, LPCTSTR lpszPushedID=NULL, LPCTSTR lpszHilitedID=NULL, BOOL bRedraw=TRUE);
	// 函数 SetDisabledIcon
	// 作用：设置SetDisabledIcon。
	// 参数：hIcon；bRedraw：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetTransparent。
	virtual BOOL SetDisabledIcon(HICON hIcon, BOOL bRedraw=FALSE);
	// 函数 SetDisabledIcon
	// 作用：设置SetDisabledIcon。
	// 参数：nID：整数；bRedraw：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetTransparent。
	virtual BOOL SetDisabledIcon(UINT nID, BOOL bRedraw=FALSE);
	// 函数 SetDisabledIcon
	// 作用：设置SetDisabledIcon。
	// 参数：lpszID；bRedraw：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetTransparent。
	virtual BOOL SetDisabledIcon(LPCTSTR lpszID, BOOL bRedraw=FALSE);

	// 函数 SetTransparent
	// 作用：设置SetTransparent。
	// 参数：bFlag：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTransparent(BOOL bFlag){m_bTransparent=bFlag;}
	// 函数 SetAutoDisabled
	// 作用：设置SetAutoDisabled。
	// 参数：bFlag：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAutoDisabled(BOOL bFlag){m_bAutoDisabled=bFlag;}
	// 函数 SetBigPercent
	// 作用：设置SetBigPercent。
	// 参数：fPercent：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBigPercent(float fPercent){m_fBigPercent=fPercent;} ///< 必须在设置图标之前设置

	// 函数 SetToolTip
	// 作用：设置SetToolTip。
	// 参数：strTip：字符串。
	// 返回：没有返回值。
	void SetToolTip(CString strTip);

	// 函数 SetFontSize
	// 作用：设置SetFontSize。
	// 参数：lHeight；lWeight。
	// 返回：没有返回值。
	void SetFontSize(long lHeight, long lWeight=FW_NORMAL);
	// 函数 SetFontPoint
	// 作用：设置SetFontPoint。
	// 参数：nPoint：整数；strFont：字符串。
	// 返回：没有返回值。
	void SetFontPoint(int nPoint, CString strFont);
	// 函数 SetCustomNumber
	// 作用：设置SetCustomNumber。
	// 参数：nNumber：整数。
	// 返回：没有返回值。
	void SetCustomNumber(int nNumber);

protected:
	// 函数 OffsetPoint
	// 作用：执行OffsetPoint。
	// 参数：point；size。
	// 返回：没有返回值。
	void OffsetPoint( CPoint& point, CSize size);

	// 函数 CleanUpGDI
	// 作用：执行CleanUpGDI。
	// 参数：无。
	// 返回：没有返回值。
	virtual void CleanUpGDI();
	// 函数 DrawButtonIcon
	// 作用：绘制DrawButtonIcon。
	// 参数：pDC：指针，指向调用方传入的对象；nState：整数；rcItem。
	// 返回：没有返回值。
	virtual void DrawButtonIcon(CDC* pDC, UINT nState, CRect& rcItem);

	// 函数 DrawButtonText
	// 作用：绘制DrawButtonText。
	// 参数：pDC：指针，指向调用方传入的对象；nState：整数；rcItem；clrText：颜色。
	// 返回：没有返回值。
	virtual void DrawButtonText(CDC* pDC, UINT nState, CRect& rcItem, COLORREF clrText);
	// 函数 DrawCustomNumber
	// 作用：绘制DrawCustomNumber。
	// 参数：pDC：指针，指向调用方传入的对象；nState：整数；rcItem；clrText：颜色。
	// 返回：没有返回值。
	void DrawCustomNumber(CDC* pDC, UINT nState, CRect& rcItem, COLORREF clrText);
	// 函数 DrawCustomText
	// 作用：绘制DrawCustomText。
	// 参数：pDC：指针，指向调用方传入的对象；nState：整数；rcItem；clrText：颜色；strText：字符串。
	// 返回：没有返回值。
	void DrawCustomText(CDC* pDC, UINT nState, CRect& rcItem, COLORREF clrText, CString& strText);

	// 函数 GetButtonText
	// 作用：读取GetButtonText。
	// 参数：bRemoveAmpersand：是或否。
	// 返回：返回一段文字。
	virtual CString GetButtonText(BOOL bRemoveAmpersand);
    virtual CPoint CalculateImagePosition(CDC* pDC, UINT nState, CRect& rcItem, BOOL bHasPushedImage);
    void NoteButtonDepressed(BOOL bDepressed);
	// 函数 DeferInitialUpdate
	// 作用：执行DeferInitialUpdate。
	// 参数：无。
	// 返回：没有返回值。
	void DeferInitialUpdate();

	// 函数 DrawItem
	// 作用：绘制DrawItem。
	// 参数：lpDrawItemStruct。
	// 返回：没有返回值。
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// 函数 PreSubclassWindow
	// 作用：执行PreSubclassWindow。
	// 参数：无。
	// 返回：没有返回值。
	virtual void PreSubclassWindow();

	// 函数 OnMouseMove
	// 作用：鼠标在窗口上移动。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnLButtonUp
	// 作用：松开鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT nIDEvent);
	// 函数 OnLButtonDblClk
	// 作用：双击鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();
	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

private:
	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：无。
	// 返回：没有返回值。
	void Initialize(void);
	// 函数 StripMnemonics
	// 作用：执行StripMnemonics。
	// 参数：strIn：字符串。
	// 返回：没有返回值。
	void StripMnemonics(CString& strIn);
	// 函数 DrawParentBackground
	// 作用：绘制DrawParentBackground。
	// 参数：pWnd：指针，指向调用方传入的对象；pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL DrawParentBackground (CWnd* pWnd, CDC* pDC);
	// 函数 CreateGrayscaleIcon
	// 作用：创建或加入CreateGrayscaleIcon。
	// 参数：hIcon。
	// 返回：返回 HICON。
	HICON CreateGrayscaleIcon(HICON hIcon);

	// 函数 DrawGradualBackground
	// 作用：绘制DrawGradualBackground。
	// 参数：pDC：指针，指向调用方传入的对象；rcItem。
	// 返回：没有返回值。
	void DrawGradualBackground(CDC* pDC, CRect& rcItem);
};
