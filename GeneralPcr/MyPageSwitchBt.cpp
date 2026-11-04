// 【交接】 GeneralPcr\MyPageSwitchBt.cpp
// 作用：MyPageSwitchBt 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyPageSwitchBt、RGB、_T、Color、MyDeletePtr、DeleteObject、BEGIN_MESSAGE_MAP。
// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "MyPageSwitchBt.h"
// CMyPageSwitchBt


int CMyPageSwitchBt::PageCount = 0;

IMPLEMENT_DYNAMIC(CMyPageSwitchBt, CButton)

// 函数 CMyPageSwitchBt::CMyPageSwitchBt
// 作用：执行CMyPageSwitchBt。
// 参数：bAutoDynamic：是或否；bUseFourthState：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 RGB、_T、Color。
CMyPageSwitchBt::CMyPageSwitchBt(BOOL bAutoDynamic /*= FALSE*/,BOOL bUseFourthState /*= TRUE*/)
{
	m_bTracking = FALSE;
	m_ctrlState = CTRL_BUTTON_NOFOCUS;
	m_bHasBkPic = FALSE;
	m_bHasPathBkPic = FALSE; 
	m_bHasPngBkPic = FALSE;
	m_sonPicNums = 1;
	m_iconW = 0;
	m_iconLeftIndent = 0;
	m_iconRightIndent = 0;
	m_rightEnd = 0;

	m_txClrNormal = RGB(0X39,0X45,0X65);
	m_txClrFocused = CLR_2LEVEL_THEME;
	m_txClrClicked = CLR_2LEVEL_THEME;
	m_txClrDisabled = CLR_2LEVEL_THEME;

	m_edgeClrNormal = RGB(0XDC,0XDC,0XDC);
	m_edgeClrFocused = RGB(0XDC,0XDC,0XDC);
	m_edgeClrClicked = RGB(0XDC,0XDC,0XDC);
	m_edgeClrDisabled = RGB(0XDC,0XDC,0XDC);

	m_bkClrNormal = RGB(0XFF,0XFF,0XFF);
	m_bkClrFocused = RGB(0XFF,0XFF,0XFF);
	m_bkClrClicked = CLR_SOFT_LIGHT;
	m_bkClrDisabled = CLR_SOFT_LIGHT;

	m_bDrawFrame = TRUE;
	m_strPngPicPath = _T("");

	m_bInMiddle = FALSE;

	m_bGradientBk = FALSE;
	m_glrStart = Color(0,0X65,0X3D);
	m_glrEnd = Color(0,0X9E,0X70);
	m_gradientMode = LinearGradientModeHorizontal;

	m_bFstPaint = TRUE;
	m_pMemDc = NULL;
	m_bAutoDynamic = bAutoDynamic;
	m_fstPaintWidth = 0;
	m_fstPaintHeight = 0;
	m_hBitmap = NULL;

	m_txFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	m_bAmoySwtStyle = FALSE;
	m_AmoySwtBkClr = RGB(251,251,251);
	m_bUseFourthState = bUseFourthState;

	m_bCkbtFunc = FALSE;
	m_curStateId = 0;
	m_pageId = ++PageCount;

	m_bAddPageIcon = FALSE;
	m_strFilePath = _T("");
	m_bBtPageRunning = FALSE;

	m_iCloseIconW = 10;
	m_iCloseIconH = 10;
	m_iCloseIconRightIndent = 11;

	m_bMouseInColseBtRect = FALSE;
}

// 函数 CMyPageSwitchBt::~CMyPageSwitchBt
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 MyDeletePtr、DeleteObject。
CMyPageSwitchBt::~CMyPageSwitchBt()
{
	m_bTracking = FALSE;

	MyDeletePtr(&m_pMemDc);

	if(NULL != m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
	}
}

BEGIN_MESSAGE_MAP(CMyPageSwitchBt, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,&CMyPageSwitchBt::OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER,&CMyPageSwitchBt::OnMouseHover)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_CAPTURECHANGED()
END_MESSAGE_MAP()

// CMyPageSwitchBt message handlers
// 函数 CMyPageSwitchBt::PreSubclassWindow
// 作用：执行PreSubclassWindow。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ModifyStyle。
void CMyPageSwitchBt::PreSubclassWindow()
{
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

// 函数 CMyPageSwitchBt::SetPngBkPic
// 作用：设置SetPngBkPic。
// 参数：strPicPath：字符串；sonPicNums；iconWidth；iconLeftIndent；iconRightIndent；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetPngBkPic(CString strPicPath,int sonPicNums,int iconWidth /*= 0*/,int iconLeftIndent /*= 0*/,int iconRightIndent /*= 0*/,BOOL bRedraw /*= FALSE*/)
{
	m_sonPicNums = sonPicNums;
	m_bHasPngBkPic = TRUE;
	m_strPngPicPath = strPicPath;
	m_iconW = iconWidth;
	m_iconLeftIndent = iconLeftIndent;
	m_iconRightIndent = iconRightIndent;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyPageSwitchBt::SetBkColor
// 作用：设置SetBkColor。
// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetBkColor(COLORREF bkClrNormal,COLORREF bkClrFocused,COLORREF bkClrClicked,COLORREF bkClrDisabled,BOOL bRedraw/* = FALSE*/)
{
	m_bkClrNormal = bkClrNormal;
	m_bkClrFocused = bkClrFocused;
	m_bkClrClicked = bkClrClicked;
	m_bkClrDisabled = bkClrDisabled;
	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
	return;
}

// 函数 CMyPageSwitchBt::GetBkColor
// 作用：读取GetBkColor。
// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyPageSwitchBt::GetBkColor(COLORREF& bkClrNormal,COLORREF& bkClrFocused,COLORREF& bkClrClicked,COLORREF& bkClrDisabled)
{
	bkClrNormal = m_bkClrNormal;
	bkClrFocused = m_bkClrFocused;
	bkClrClicked = m_bkClrClicked;
	bkClrDisabled = m_bkClrDisabled;
	return;
}

// 函数 CMyPageSwitchBt::SetTextColor
// 作用：设置SetTextColor。
// 参数：txClrNormal；txClrFocused；txClrClicked；txClrDisabled；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetTextColor(COLORREF txClrNormal,COLORREF txClrFocused,COLORREF txClrClicked,COLORREF txClrDisabled,BOOL bRedraw/* = FALSE*/)
{
	m_txClrNormal = txClrNormal;
	m_txClrFocused = txClrFocused;
	m_txClrClicked = txClrClicked;
	m_txClrDisabled = txClrDisabled;
	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
	return;
}

// 函数 CMyPageSwitchBt::GetTextColor
// 作用：读取GetTextColor。
// 参数：txClrNormal；txClrFocused；txClrClicked；txClrDisabled。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyPageSwitchBt::GetTextColor(COLORREF& txClrNormal,COLORREF& txClrFocused,COLORREF& txClrClicked,COLORREF& txClrDisabled)
{
	txClrNormal = m_txClrNormal;
	txClrFocused = m_txClrFocused;
	txClrClicked = m_txClrClicked;
	txClrDisabled = m_txClrDisabled;
	return;
}

// 函数 CMyPageSwitchBt::SetEdgeColor
// 作用：设置SetEdgeColor。
// 参数：edgeClrNormal；edgeClrFocused；edgeClrClicked；edgeClrDisabled；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetEdgeColor(COLORREF edgeClrNormal,COLORREF edgeClrFocused,COLORREF edgeClrClicked,COLORREF edgeClrDisabled,BOOL bRedraw/* = FALSE*/)
{
	m_edgeClrNormal = edgeClrNormal;
	m_edgeClrFocused = edgeClrFocused;
	m_edgeClrClicked = edgeClrClicked;
	m_edgeClrDisabled = edgeClrDisabled;
	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
	return;
}

// 函数 CMyPageSwitchBt::GetEdgeColor
// 作用：读取GetEdgeColor。
// 参数：edgeClrNormal；edgeClrFocused；edgeClrClicked；edgeClrDisabled。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyPageSwitchBt::GetEdgeColor(COLORREF& edgeClrNormal,COLORREF& edgeClrFocused,COLORREF& edgeClrClicked,COLORREF& edgeClrDisabled)
{
	edgeClrNormal = m_edgeClrNormal;
	edgeClrFocused = m_edgeClrFocused;
	edgeClrClicked = m_edgeClrClicked;
	edgeClrDisabled = m_edgeClrDisabled;
}

// 函数 CMyPageSwitchBt::SetDrawFrame
// 作用：设置SetDrawFrame。
// 参数：bDrawFrame：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetDrawFrame(BOOL bDrawFrame,BOOL bRedraw /*= FALSE*/)
{
	m_bDrawFrame = bDrawFrame;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyPageSwitchBt::GetDrawFrame
// 作用：读取GetDrawFrame。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::GetDrawFrame()
{
	return m_bDrawFrame;
}

// 函数 CMyPageSwitchBt::SetBeInMiddle
// 作用：设置SetBeInMiddle。
// 参数：bInMiddle：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetBeInMiddle(BOOL bInMiddle,BOOL bRedraw /*= FALSE*/)
{
	m_bInMiddle = bInMiddle;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyPageSwitchBt::GetBeInMiddle
// 作用：读取GetBeInMiddle。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::GetBeInMiddle()
{
	return m_bInMiddle;
}

// 函数 CMyPageSwitchBt::SetTextFormat
// 作用：设置SetTextFormat。
// 参数：txFormat；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetTextFormat(UINT txFormat,BOOL bRedraw /*= FALSE*/)
{
	m_txFormat = txFormat;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyPageSwitchBt::GetTextFormat
// 作用：读取GetTextFormat。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
UINT CMyPageSwitchBt::GetTextFormat()
{
	return m_txFormat;
}

// 函数 CMyPageSwitchBt::SetAmoySwtParam
// 作用：设置SetAmoySwtParam。
// 参数：bAmoySwtStyle：是或否；bkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetAmoySwtParam(BOOL bAmoySwtStyle,COLORREF bkClr,BOOL bRedraw /*= FALSE*/)
{
	m_bAmoySwtStyle = bAmoySwtStyle;
	m_AmoySwtBkClr = bkClr;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyPageSwitchBt::GetAmoySwtParam
// 作用：读取GetAmoySwtParam。
// 参数：bAmoySwtStyle：是或否；bkClr。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyPageSwitchBt::GetAmoySwtParam(BOOL& bAmoySwtStyle,COLORREF& bkClr)
{
	bAmoySwtStyle = m_bAmoySwtStyle;
	bkClr = m_AmoySwtBkClr;
	return;
}

// 函数 CMyPageSwitchBt::SetBeAmoySwtStyle
// 作用：设置SetBeAmoySwtStyle。
// 参数：bAmoySwtStyle：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetBeAmoySwtStyle(BOOL bAmoySwtStyle,BOOL bRedraw /*= FALSE*/)
{
	m_bAmoySwtStyle = bAmoySwtStyle;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyPageSwitchBt::GetBeAmoySwtStyle
// 作用：读取GetBeAmoySwtStyle。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::GetBeAmoySwtStyle()
{
	return m_bAmoySwtStyle;
}

// 函数 CMyPageSwitchBt::SetAmoySwtBkClr
// 作用：设置SetAmoySwtBkClr。
// 参数：bkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetAmoySwtBkClr(COLORREF bkClr,BOOL bRedraw /*= FALSE*/)
{
	m_AmoySwtBkClr = bkClr;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyPageSwitchBt::GetAmoySwtBkClr
// 作用：读取GetAmoySwtBkClr。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyPageSwitchBt::GetAmoySwtBkClr()
{
	return m_AmoySwtBkClr;
}

// 函数 CMyPageSwitchBt::SetGradientParam
// 作用：设置SetGradientParam。
// 参数：bGradientBk：是或否；glrStart；glrEnd；gradientMode；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetGradientParam(BOOL bGradientBk,Color glrStart,Color glrEnd,LinearGradientMode gradientMode,BOOL bRedraw /*= FALSE*/)
{
	m_bGradientBk = bGradientBk;
	m_glrStart = glrStart;
	m_glrEnd = glrEnd;
	m_gradientMode = gradientMode;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyPageSwitchBt::GetGradientParam
// 作用：读取GetGradientParam。
// 参数：bGradientBk：是或否；glrStart；glrEnd；gradientMode。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyPageSwitchBt::GetGradientParam(BOOL& bGradientBk,Color& glrStart,Color& glrEnd,LinearGradientMode& gradientMode)
{
	 bGradientBk = m_bGradientBk;
	 glrStart = m_glrStart;
	 glrEnd = m_glrEnd;
	 gradientMode = m_gradientMode;
}

// 函数 CMyPageSwitchBt::SetCkbtFuncParam
// 作用：设置SetCkbtFuncParam。
// 参数：bCkbtFunc：是或否；curState；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetCkbtFuncParam(BOOL bCkbtFunc,int curState,BOOL bRedraw /*= FALSE*/)
{
	m_bCkbtFunc = bCkbtFunc;
	m_curStateId = curState;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyPageSwitchBt::GetCkbtFuncParam
// 作用：读取GetCkbtFuncParam。
// 参数：bCkbtFunc：是或否；curState。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyPageSwitchBt::GetCkbtFuncParam(BOOL& bCkbtFunc,int& curState)
{
	bCkbtFunc = m_bCkbtFunc;
	curState = m_curStateId;
	return;
}

// 函数 CMyPageSwitchBt::SetBeCkbtFunc
// 作用：设置SetBeCkbtFunc。
// 参数：bCkbtFunc：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetBeCkbtFunc(BOOL bCkbtFunc,BOOL bRedraw /*= FALSE*/)
{
	m_bCkbtFunc = bCkbtFunc;
	
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyPageSwitchBt::GetBeCkbtFunc
// 作用：读取GetBeCkbtFunc。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::GetBeCkbtFunc()
{
	return m_bCkbtFunc;
}

// 函数 CMyPageSwitchBt::SetCkbtFuncCurState
// 作用：设置SetCkbtFuncCurState。
// 参数：curState；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetCkbtFuncCurState(int curState,BOOL bRedraw /*= FALSE*/)
{
	m_curStateId = curState;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyPageSwitchBt::GetCkbtFuncCurState
// 作用：读取GetCkbtFuncCurState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::GetCkbtFuncCurState()
{
	return m_curStateId;
}

// 函数 CMyPageSwitchBt::SetBeAddPageIcon
// 作用：设置SetBeAddPageIcon。
// 参数：bAddPageIcon：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetBeAddPageIcon(BOOL bAddPageIcon,BOOL bRedraw /*= FALSE*/)
{
	m_bAddPageIcon = bAddPageIcon;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyPageSwitchBt::GetBeAddPageIcon
// 作用：读取GetBeAddPageIcon。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::GetBeAddPageIcon()
{
	return m_bAddPageIcon;
}

// 函数 CMyPageSwitchBt::SetBeBtPageRunning
// 作用：设置SetBeBtPageRunning。
// 参数：bBtPageRunning：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyPageSwitchBt::SetBeBtPageRunning(BOOL bBtPageRunning,BOOL bRedraw /*= FALSE*/)
{
	m_bBtPageRunning = bBtPageRunning;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyPageSwitchBt::GetBeBtPageRunning
// 作用：读取GetBeBtPageRunning。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::GetBeBtPageRunning()
{
	return m_bBtPageRunning;
}

// 函数 CMyPageSwitchBt::SetPageId
// 作用：设置SetPageId。
// 参数：pageId。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyPageSwitchBt::SetPageId(int pageId)
{
	m_pageId = pageId;
}

// 函数 CMyPageSwitchBt::GetPageId
// 作用：读取GetPageId。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMyPageSwitchBt::GetPageId()
{
	return m_pageId;
}

// 函数 CMyPageSwitchBt::EnableWindow
// 作用：改变EnableWindow的显示或可用状态。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 _TrackMouseEvent、Invalidate。
void CMyPageSwitchBt::EnableWindow(BOOL bEnabled)
{
	if(bEnabled)
	{
		m_ctrlState = CTRL_BUTTON_NOFOCUS;
	}
	else
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_CANCEL | TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		_TrackMouseEvent(&tme);
		m_bTracking = FALSE;
	
		m_ctrlState = CTRL_BUTTON_DISABLE;
	}
	Invalidate(FALSE);
	//CButton::EnableWindow(bEnabled);
}

// 函数 CMyPageSwitchBt::DrawItem
// 作用：绘制DrawItem。
// 参数：lpDrawItemStruct。
// 返回：没有返回值。
// 过程：函数里会调用 clock、rcClient、Attach、GetSafeHdc、CreateCompatibleDC、CreateCompatibleBitmap。
void CMyPageSwitchBt::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
#ifdef _DEBUG
	clock_t startMs = clock();
#endif

	CRect rect = lpDrawItemStruct->rcItem;
	CRect rcClient(rect);
	CDC cDC;
	cDC.Attach(lpDrawItemStruct->hDC);
	ASSERT(NULL != cDC.GetSafeHdc());

	CDC memDCTemp;
	memDCTemp.CreateCompatibleDC(&cDC);
	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(&cDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDCTemp.SelectObject(&bitMapCB);

	memDCTemp.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&cDC,0,0,SRCCOPY);

	if(m_bAutoDynamic)
	{
		if(m_bFstPaint)
		{
			m_pMemDc = new CDC;
			BOOL ret = m_pMemDc->CreateCompatibleDC(&cDC);
			m_hBitmap = ::CreateCompatibleBitmap(cDC.m_hDC,rect.Width(),rect.Height()); //创建兼容位图
			m_pMemDc->SelectObject(m_hBitmap);	
			m_pMemDc->BitBlt(0,0,rect.Width(),rect.Height(),&cDC,0,0,SRCCOPY);

			m_fstPaintWidth = rect.Width();
			m_fstPaintHeight = rect.Height();
			m_bFstPaint = FALSE;
		}
		else
		{
			memDCTemp.StretchBlt(0,0,rect.Width(),rect.Height(),m_pMemDc,0,0,m_fstPaintWidth,m_fstPaintHeight,SRCCOPY);
		}
	}


	{
		Graphics graphics(memDCTemp.m_hDC);
		graphics.SetSmoothingMode(SmoothingModeAntiAlias);
		graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);

		COLORREF clrBk = RGB(0XFF,0XFF,0XFF);
		Color clrCloseBt = Color(0X8B,0X8E,0X93);

		if(m_bBtPageRunning && CTRL_BUTTON_DISABLE != m_ctrlState)
		{
			if(m_bMouseInColseBtRect)
			{
				clrCloseBt = Color(0X20,0X44,0X7C);
			}
			else
			{
				clrCloseBt = COLOR_2LEVEL_THEME;
			}
		}
		else
		{
			if(m_bMouseInColseBtRect)
			{
				clrCloseBt = Color(0X20,0X44,0X7C);
			}
			else
			{
				clrCloseBt = Color(0X8B,0X8E,0X93);
			}
		}

		//绘制背景
		if(CTRL_BUTTON_DISABLE == m_ctrlState)
		{
			clrBk = m_bkClrDisabled;
		}
		else
		{
			if(!m_bBtPageRunning)
			{
				clrBk = m_bkClrNormal;
			}
		}
		memDCTemp.FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),clrBk);

		if(m_bBtPageRunning && CTRL_BUTTON_DISABLE != m_ctrlState)
		{
			memDCTemp.FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),RGB(0XFF,0XFF,0XFF));
			int iTempInt1 = 100 * m_dHoriRatio;
			if(rect.Width() > iTempInt1)
			{
				LinearGradientBrush linGrBrush(RectF(0,0,iTempInt1,rect.Height()),COLOR_PAGEBT_RUNNING_UNSHOW_START,COLOR_PAGEBT_RUNNING_UNSHOW_MIDDLE,LinearGradientModeHorizontal);
				Status sRet = graphics.FillRectangle(&linGrBrush,0,0,iTempInt1,rect.Height());

				LinearGradientBrush linGrBrush2(RectF(iTempInt1,0,rect.Width() - iTempInt1,rect.Height()),COLOR_PAGEBT_RUNNING_UNSHOW_MIDDLE,COLOR_PAGEBT_RUNNING_UNSHOW_END,LinearGradientModeHorizontal);
				sRet = graphics.FillRectangle(&linGrBrush2,iTempInt1,0,rect.Width() - iTempInt1,rect.Height());
			}
			else
			{
				LinearGradientBrush linGrBrush(RectF(0,0,rect.Width(),rect.Height()),Color(139,0X06,0X91,0X9D),Color(0,0X06,0X91,0X9D),LinearGradientModeHorizontal);
				Status sRet = graphics.FillRectangle(&linGrBrush,0,0,rect.Width() - 6,rect.Height());
			}
		}

		//绘制实验图标
		Image image(m_strPngPicPath);
		int iStartX = 0;
		int iBkW = 0;
		if(1 == m_sonPicNums)
		{
			iBkW = image.GetWidth();
		}
		else if(2 == m_sonPicNums)
		{
			switch(m_ctrlState)
			{
			case CTRL_BUTTON_NOFOCUS:
				iStartX = 0;
				break;
			case CTRL_BUTTON_FOCUS:
				iStartX = 0;
				break;
			case CTRL_BUTTON_SELECTED:
				iStartX = image.GetWidth() / 2;
				break;
			case CTRL_BUTTON_DISABLE:
				iStartX = image.GetWidth() / 2;
				break;
			}
			iBkW = image.GetWidth() / 2;
		}
		else if(3 == m_sonPicNums)
		{
			switch(m_ctrlState)
			{
			case CTRL_BUTTON_NOFOCUS:
				iStartX = 0;
				break;
			case CTRL_BUTTON_FOCUS:
				iStartX = 0;
				break;
			case CTRL_BUTTON_SELECTED:
				iStartX = image.GetWidth() / 3;
				break;
			case CTRL_BUTTON_DISABLE:
				iStartX = image.GetWidth() / 3;
				break;
			}
			iBkW = image.GetWidth() / 3;
		}
		else if(4 == m_sonPicNums)
		{
			switch(m_ctrlState)
			{
			case CTRL_BUTTON_NOFOCUS:
				iStartX = 0;
				break;
			case CTRL_BUTTON_FOCUS:
				iStartX = image.GetWidth() / 4;
				break;
			case CTRL_BUTTON_SELECTED:
				iStartX = image.GetWidth() / 2;
				break;
			case CTRL_BUTTON_DISABLE:
				iStartX = image.GetWidth() / 4 * 3;
				break;
			}
			iBkW = image.GetWidth() / 4;
		}

		ImageAttributes ImgAtt;
		ImgAtt.SetWrapMode(WrapModeTileFlipXY);

		Rect destRect;
		if(0 != m_iconW)
		{
			destRect.X = m_iconLeftIndent;
			if(rect.Height() > image.GetHeight())
			{
				destRect.Y = (rect.Height() - image.GetHeight()) / 2;
			}

			if(iBkW > rect.Width() - m_iconLeftIndent)
			{
				destRect.Width = rect.Width() - m_iconLeftIndent;
			}
			else
			{
				destRect.Width = iBkW;
			}
			destRect.Height = rect.Height() - destRect.Y * 2;
		}
		else
		{
			if(m_bInMiddle)
			{
				if(rect.Width() > iBkW)
				{
					destRect.X = (rect.Width() - iBkW) / 2;
				}

				if(rect.Height() > image.GetHeight())
				{
					destRect.Y = (rect.Height() - image.GetHeight()) / 2;
				}
				destRect.Width = iBkW;
				destRect.Height = image.GetHeight();
			}
			else
			{
				destRect.X = 0;
				destRect.Y = 0;
				destRect.Width = rect.Width();
				destRect.Height = rect.Height();
			}
		}

		graphics.DrawImage(&image,destRect,0,0,iBkW,image.GetHeight(),UnitPixel,&ImgAtt);

		//绘制“x”标识
		m_rcCloseBt = CRect(rcClient.Width() - m_iCloseIconRightIndent - m_iCloseIconW,(rcClient.Height() - m_iCloseIconH) / 2,rcClient.Width() - m_iCloseIconRightIndent,rcClient.Height() / 2 + m_iCloseIconH / 2);
		Pen gdiplusPen(clrCloseBt,2 * m_dTxRatio);
		Point ptStart,ptEnd;
		ptStart.X = m_rcCloseBt.left;
		ptStart.Y = m_rcCloseBt.top;
		ptEnd.X = m_rcCloseBt.right;
		ptEnd.Y = m_rcCloseBt.bottom;
		graphics.DrawLine(&gdiplusPen,ptStart,ptEnd);
		ptStart.X = m_rcCloseBt.right;
		ptStart.Y = m_rcCloseBt.top;
		ptEnd.X = m_rcCloseBt.left;
		ptEnd.Y = m_rcCloseBt.bottom;
		graphics.DrawLine(&gdiplusPen,ptStart,ptEnd);

		graphics.ReleaseHDC(memDCTemp.m_hDC);
	}
	
	//如果设置了文本，则绘制文本
	CString strText;
	GetWindowText(strText);
	if(0 != strText.GetLength())
	{
		COLORREF clrTx = 0;

		switch(m_ctrlState)
		{
		case CTRL_BUTTON_NOFOCUS:
			clrTx = m_txClrNormal;
			break;
		case CTRL_BUTTON_FOCUS:
			clrTx = m_txClrFocused; 
			break;
		case CTRL_BUTTON_SELECTED:
			clrTx = m_txClrClicked;
			break;
		case CTRL_BUTTON_DISABLE:
			clrTx = m_txClrDisabled;
			break;
		}

		CFont *pOldFont = memDCTemp.SelectObject(&m_fontSet);
		CRect rectText = lpDrawItemStruct->rcItem;

		int nOldBkMode = memDCTemp.SetBkMode(TRANSPARENT);
		memDCTemp.SetTextColor(clrTx);
		rectText.left = (m_iconLeftIndent + m_iconW + m_iconRightIndent);

		rectText.right -= (m_iCloseIconW + m_iCloseIconRightIndent);
		m_txFormat |= DT_END_ELLIPSIS;
		memDCTemp.DrawText(strText,&rectText,m_txFormat);
		memDCTemp.SelectObject(pOldFont);
		memDCTemp.SetBkMode(nOldBkMode);
	}

	cDC.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDCTemp,0,0,SRCCOPY);
	memDCTemp.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDCTemp.DeleteDC();

	cDC.Detach();

#ifdef _DEBUG
	clock_t endMs = clock() - startMs;
	++endMs;
#endif
}

// 函数 CMyPageSwitchBt::OnMouseMove
// 作用：鼠标在窗口上移动。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PtInRect、SetCapture、ReleaseCapture、Invalidate、_TrackMouseEvent。
void CMyPageSwitchBt::OnMouseMove(UINT nFlags, CPoint point)
{
	BOOL bPreState = m_bMouseInColseBtRect;
	if(m_rcCloseBt.PtInRect(point))
	{
		m_bMouseInColseBtRect = TRUE;
		SetCapture();
	}
	else
	{
		m_bMouseInColseBtRect = FALSE;
		ReleaseCapture();
	}
	if(bPreState != m_bMouseInColseBtRect)
	{
		Invalidate(FALSE);
	}

	if(CTRL_BUTTON_DISABLE == m_ctrlState)
	{
		return;
	}

	if(!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}

// 函数 CMyPageSwitchBt::OnMouseLeave
// 作用：响应 Windows 或自定义消息 OnMouseLeave。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 Invalidate。
LRESULT CMyPageSwitchBt::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	if(CTRL_BUTTON_DISABLE == m_ctrlState)
	{
		return 1;
	}

	if(CTRL_BUTTON_NOFOCUS != m_ctrlState)
	{
		m_ctrlState = CTRL_BUTTON_NOFOCUS;
		Invalidate(FALSE);
	}
	m_bTracking = FALSE;

	return 0;
}

// 函数 CMyPageSwitchBt::OnMouseHover
// 作用：响应 Windows 或自定义消息 OnMouseHover。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 Invalidate。
LRESULT CMyPageSwitchBt::OnMouseHover(WPARAM wParam,LPARAM lParam)
{
	if(CTRL_BUTTON_DISABLE == m_ctrlState)
	{
		return 1;
	}

	if(CTRL_BUTTON_NOFOCUS == m_ctrlState)
	{
		m_ctrlState = CTRL_BUTTON_FOCUS;
		Invalidate(FALSE);
	}
	m_bTracking = FALSE;
	return 0;
}

// 函数 CMyPageSwitchBt::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PtInRect、GetParent、GetSafeHwnd、PostMessage、Invalidate。
void CMyPageSwitchBt::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_rcCloseBt.PtInRect(point) && !m_bBtPageRunning)
	{
		CWnd* pParent = GetParent();
		if(NULL != pParent->GetSafeHwnd())
		{
			pParent->PostMessage(WM_CLOSEPAGE,m_pageId,0);
		}
		return;
	}
	

	if(CTRL_BUTTON_DISABLE == m_ctrlState)
	{
		return;
	}
	
	if(CTRL_BUTTON_FOCUS == m_ctrlState)
	{
		m_ctrlState = CTRL_BUTTON_SELECTED;
		Invalidate(FALSE);
	}
	__super::OnLButtonDown(nFlags, point);
}

// 函数 CMyPageSwitchBt::OnLButtonUp
// 作用：松开鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyPageSwitchBt::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(CTRL_BUTTON_DISABLE == m_ctrlState)
	{
		return;
	}

	if(CTRL_BUTTON_SELECTED == m_ctrlState)
	{
		m_ctrlState = CTRL_BUTTON_FOCUS;
		Invalidate();
	}

	__super::OnLButtonUp(nFlags, point);
}

// 函数 CMyPageSwitchBt::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 __super::OnSize。
void CMyPageSwitchBt::OnSize(UINT nType, int cx, int cy)
{
 	__super::OnSize(nType, cx, cy);
}

// 函数 CMyPageSwitchBt::PreTranslateMessage
// 作用：消息送达窗口前先拦截键盘或鼠标。
// 参数：pMsg：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 __super::PreTranslateMessage。
BOOL CMyPageSwitchBt::PreTranslateMessage(MSG* pMsg)
{
	if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		switch(pMsg->wParam)
		{
		//case VK_RETURN:	return TRUE;
		case VK_ESCAPE:	return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

// 函数 CMyPageSwitchBt::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyPageSwitchBt::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// 函数 CMyPageSwitchBt::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CButton::OnCreate。
int CMyPageSwitchBt::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iCloseIconW *= m_dHoriRatio;
	m_iCloseIconH *= m_dVertRatio;
	m_iCloseIconRightIndent *= m_dHoriRatio;

	return CButton::OnCreate(lpCreateStruct);
}

// 函数 CMyPageSwitchBt::OnCaptureChanged
// 作用：响应 Windows 或自定义消息 OnCaptureChanged。
// 参数：pNewWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyPageSwitchBt::OnCaptureChanged(CWnd* pNewWnd)
{
	CWnd* pTemp = this;
	if(pNewWnd != pTemp)
	{
		Invalidate(FALSE);
	}
	return;
}
