// 【交接】 GeneralPcr\MyUrlBt.cpp
// 作用：MyUrlBt 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyUrlBt、RGB、Color、MyDeletePtr、DeleteObject、BEGIN_MESSAGE_MAP、ON_WM_MOUSEMOVE。
// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "MyUrlBt.h"
// CMyUrlBt

IMPLEMENT_DYNAMIC(CMyUrlBt,CButton)

// 函数 CMyUrlBt::CMyUrlBt
// 作用：执行CMyUrlBt。
// 参数：bAutoDynamic：是或否；bUseFourthState：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 RGB、Color。
CMyUrlBt::CMyUrlBt(BOOL bAutoDynamic /*= FALSE*/,BOOL bUseFourthState /*= TRUE*/)
{
	m_bTracking = FALSE;
	m_ctrlState = CTRL_URLBT_NOFOCUS;
	m_bHasBkPic = FALSE;
	m_bHasPathBkPic = FALSE; 
	m_bHasPngBkPic = FALSE;
	m_textColor = RGB(0,0,0);
	m_bStaticSize = FALSE;
	m_bOnPaneDlg = FALSE;
	m_paneStandardWidth = 1920;
	m_paneStandardHeight = 1080;
	m_btHoriFontRatio = 0;
	m_btVerFontRatio = 0;
	m_sonPicNums = 1;
	m_iconW = 0;
	m_iconLeftIndent = 0;
	m_iconRightIndent = 0;
	m_rightEnd = 0;

	m_txClrNormal = RGB(0,0,0);
	m_txClrFocused = RGB(0,0,0);
	m_txClrClicked = RGB(0,0,0);
	m_txClrDisabled = RGB(0,0,0);

	m_edgeClrNormal = RGB(0XDC,0XDC,0XDC);
	m_edgeClrFocused = RGB(0XDC,0XDC,0XDC);
	m_edgeClrClicked = RGB(0XDC,0XDC,0XDC);
	m_edgeClrDisabled = RGB(0XDC,0XDC,0XDC);

	m_bkClrNormal = RGB(0XFF,0XFF,0XF0);
	m_bkClrFocused = RGB(0XFF,0XFA,0XCD);
	m_bkClrClicked = RGB(0XE6,0XE6,0XFA);
	m_bkClrDisabled = RGB(0XCF,0XCF,0XCF);

	m_bDrawFrame = TRUE;
	m_pngPicPath = L"";

	m_bRoundRectBk = FALSE;
	m_clrRoundRectBk = Color(3,91,199);
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

	m_txFormat = DT_CENTER | DT_SINGLELINE | DT_VCENTER;
	m_bAmoySwtStyle = FALSE;
	m_AmoySwtBkClr = RGB(251,251,251);
	m_bUseFourthState = bUseFourthState;

	m_bCkbtFunc = FALSE;
	m_curStateId = 0;
	m_bMinBt = FALSE;
}

// 函数 CMyUrlBt::~CMyUrlBt
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 MyDeletePtr、DeleteObject。
CMyUrlBt::~CMyUrlBt()
{
	m_bTracking = FALSE;

	MyDeletePtr(&m_pMemDc);

	if(NULL != m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
	}
}

BEGIN_MESSAGE_MAP(CMyUrlBt, CButton)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,&CMyUrlBt::OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER,&CMyUrlBt::OnMouseHover)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CMyUrlBtmessage handlers
// 函数 CMyUrlBt::PreSubclassWindow
// 作用：执行PreSubclassWindow。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ModifyStyle。
void CMyUrlBt::PreSubclassWindow()
{
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

// 函数 CMyUrlBt::SetBmpBkPic
// 作用：设置SetBmpBkPic。
// 参数：idPic；sonPicNums；btIconW；iconLeftIndent；iconRightIndent；rightEnd；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetBmpBkPic(UINT idPic,int sonPicNums /*= 2*/,int btIconW /*= 0*/,int iconLeftIndent /*= 0*/,int iconRightIndent /*= 0*/,int rightEnd /*= 0*/,BOOL bRedraw /*= FALSE*/)
{
	m_idNormal = idPic;
	m_sonPicNums = sonPicNums;
	m_iconW = btIconW;
	m_iconLeftIndent = iconLeftIndent;
	m_iconRightIndent = iconRightIndent;
	m_rightEnd = rightEnd;
	m_bHasBkPic = TRUE;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::SetPngBkPic
// 作用：设置SetPngBkPic。
// 参数：picPath；sonPicNums；iconWidth；iconLeftIndent；iconRightIndent；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetPngBkPic(wstring picPath,int sonPicNums,int iconWidth /*= 0*/,int iconLeftIndent /*= 0*/,int iconRightIndent /*= 0*/,BOOL bRedraw /*= FALSE*/)
{
	m_sonPicNums = sonPicNums;
	m_bHasPngBkPic = TRUE;
	m_pngPicPath = picPath;
	m_iconW = iconWidth;
	m_iconLeftIndent = iconLeftIndent;
	m_iconRightIndent = iconRightIndent;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::SetNewBmpBkPic
// 作用：设置SetNewBmpBkPic。
// 参数：idPic；sonPicNums；bInvalidate：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetNewBmpBkPic(UINT idPic,int sonPicNums,BOOL bInvalidate)
{
	m_idNormal = idPic;
	m_sonPicNums = sonPicNums;
	m_bHasBkPic = TRUE;
	if(bInvalidate && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::SetBmpBkPic
// 作用：设置SetBmpBkPic。
// 参数：idNormal；idFocus；idSelected；idDisabled；btIconW；iconLeftIndent；iconRightIndent；rightEnd。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::SetBmpBkPic(UINT idNormal,UINT idFocus,UINT idSelected,UINT idDisabled,int btIconW /*= 0*/,int iconLeftIndent /*= 0*/,int iconRightIndent /*= 0*/,int rightEnd /*= 0*/)
{
	m_idNormal = idNormal;
	m_idFocus = idFocus;
	m_idSelected = idSelected;
	m_idDisabled = idDisabled;
	m_sonPicNums = 1;
	m_iconW = btIconW;
	m_iconLeftIndent = iconLeftIndent;
	m_iconRightIndent = iconRightIndent;
	m_rightEnd = rightEnd;
	m_bHasBkPic = TRUE;
}

// 函数 CMyUrlBt::SetTextColor
// 作用：设置SetTextColor。
// 参数：textColor：颜色。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::SetTextColor(COLORREF textColor)
{
	m_textColor = textColor;
}

// 函数 CMyUrlBt::GetTextColor
// 作用：读取GetTextColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyUrlBt::GetTextColor()
{
	return m_textColor;
}

// 函数 CMyUrlBt::SetBkColor
// 作用：设置SetBkColor。
// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetBkColor(COLORREF bkClrNormal,COLORREF bkClrFocused,COLORREF bkClrClicked,COLORREF bkClrDisabled,BOOL bRedraw/* = FALSE*/)
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

// 函数 CMyUrlBt::GetBkColor
// 作用：读取GetBkColor。
// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::GetBkColor(COLORREF& bkClrNormal,COLORREF& bkClrFocused,COLORREF& bkClrClicked,COLORREF& bkClrDisabled)
{
	bkClrNormal = m_bkClrNormal;
	bkClrFocused = m_bkClrFocused;
	bkClrClicked = m_bkClrClicked;
	bkClrDisabled = m_bkClrDisabled;
	return;
}

// 函数 CMyUrlBt::SetTextColor
// 作用：设置SetTextColor。
// 参数：txClrNormal；txClrFocused；txClrClicked；txClrDisabled；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetTextColor(COLORREF txClrNormal,COLORREF txClrFocused,COLORREF txClrClicked,COLORREF txClrDisabled,BOOL bRedraw/* = FALSE*/)
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

// 函数 CMyUrlBt::GetTextColor
// 作用：读取GetTextColor。
// 参数：txClrNormal；txClrFocused；txClrClicked；txClrDisabled。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::GetTextColor(COLORREF& txClrNormal,COLORREF& txClrFocused,COLORREF& txClrClicked,COLORREF& txClrDisabled)
{
	txClrNormal = m_txClrNormal;
	txClrFocused = m_txClrFocused;
	txClrClicked = m_txClrClicked;
	txClrDisabled = m_txClrDisabled;
	return;
}

// 函数 CMyUrlBt::SetEdgeColor
// 作用：设置SetEdgeColor。
// 参数：edgeClrNormal；edgeClrFocused；edgeClrClicked；edgeClrDisabled；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetEdgeColor(COLORREF edgeClrNormal,COLORREF edgeClrFocused,COLORREF edgeClrClicked,COLORREF edgeClrDisabled,BOOL bRedraw/* = FALSE*/)
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

// 函数 CMyUrlBt::GetEdgeColor
// 作用：读取GetEdgeColor。
// 参数：edgeClrNormal；edgeClrFocused；edgeClrClicked；edgeClrDisabled。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::GetEdgeColor(COLORREF& edgeClrNormal,COLORREF& edgeClrFocused,COLORREF& edgeClrClicked,COLORREF& edgeClrDisabled)
{
	edgeClrNormal = m_edgeClrNormal;
	edgeClrFocused = m_edgeClrFocused;
	edgeClrClicked = m_edgeClrClicked;
	edgeClrDisabled = m_edgeClrDisabled;
}

// 函数 CMyUrlBt::SetRoundRectParam
// 作用：设置SetRoundRectParam。
// 参数：bRoundRect：是或否；clrRoundRectBk：矩形区域；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetRoundRectParam(BOOL bRoundRect,Color clrRoundRectBk,BOOL bRedraw /*= FALSE*/)
{
	m_bRoundRectBk = bRoundRect;
	m_clrRoundRectBk = clrRoundRectBk;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::GetRoundRectParam
// 作用：读取GetRoundRectParam。
// 参数：bRoundRect：是或否；clrRoundRectBk：矩形区域。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::GetRoundRectParam(BOOL& bRoundRect,Color& clrRoundRectBk)
{
	bRoundRect = m_bRoundRectBk;
	clrRoundRectBk = m_clrRoundRectBk;
}

// 函数 CMyUrlBt::SetDrawFrame
// 作用：设置SetDrawFrame。
// 参数：bDrawFrame：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetDrawFrame(BOOL bDrawFrame,BOOL bRedraw /*= FALSE*/)
{
	m_bDrawFrame = bDrawFrame;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::GetDrawFrame
// 作用：读取GetDrawFrame。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyUrlBt::GetDrawFrame()
{
	return m_bDrawFrame;
}

// 函数 CMyUrlBt::SetBeInMiddle
// 作用：设置SetBeInMiddle。
// 参数：bInMiddle：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetBeInMiddle(BOOL bInMiddle,BOOL bRedraw /*= FALSE*/)
{
	m_bInMiddle = bInMiddle;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::GetBeInMiddle
// 作用：读取GetBeInMiddle。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyUrlBt::GetBeInMiddle()
{
	return m_bInMiddle;
}

// 函数 CMyUrlBt::SetTextFormat
// 作用：设置SetTextFormat。
// 参数：txFormat；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetTextFormat(UINT txFormat,BOOL bRedraw /*= FALSE*/)
{
	m_txFormat = txFormat;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyUrlBt::GetTextFormat
// 作用：读取GetTextFormat。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
UINT CMyUrlBt::GetTextFormat()
{
	return m_txFormat;
}

// 函数 CMyUrlBt::SetAmoySwtParam
// 作用：设置SetAmoySwtParam。
// 参数：bAmoySwtStyle：是或否；bkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetAmoySwtParam(BOOL bAmoySwtStyle,COLORREF bkClr,BOOL bRedraw /*= FALSE*/)
{
	m_bAmoySwtStyle = bAmoySwtStyle;
	m_AmoySwtBkClr = bkClr;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyUrlBt::GetAmoySwtParam
// 作用：读取GetAmoySwtParam。
// 参数：bAmoySwtStyle：是或否；bkClr。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::GetAmoySwtParam(BOOL& bAmoySwtStyle,COLORREF& bkClr)
{
	bAmoySwtStyle = m_bAmoySwtStyle;
	bkClr = m_AmoySwtBkClr;
	return;
}

// 函数 CMyUrlBt::SetBeAmoySwtStyle
// 作用：设置SetBeAmoySwtStyle。
// 参数：bAmoySwtStyle：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetBeAmoySwtStyle(BOOL bAmoySwtStyle,BOOL bRedraw /*= FALSE*/)
{
	m_bAmoySwtStyle = bAmoySwtStyle;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyUrlBt::GetBeAmoySwtStyle
// 作用：读取GetBeAmoySwtStyle。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyUrlBt::GetBeAmoySwtStyle()
{
	return m_bAmoySwtStyle;
}

// 函数 CMyUrlBt::SetAmoySwtBkClr
// 作用：设置SetAmoySwtBkClr。
// 参数：bkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetAmoySwtBkClr(COLORREF bkClr,BOOL bRedraw /*= FALSE*/)
{
	m_AmoySwtBkClr = bkClr;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyUrlBt::GetAmoySwtBkClr
// 作用：读取GetAmoySwtBkClr。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyUrlBt::GetAmoySwtBkClr()
{
	return m_AmoySwtBkClr;
}

// 函数 CMyUrlBt::SetGradientParam
// 作用：设置SetGradientParam。
// 参数：bGradientBk：是或否；glrStart；glrEnd；gradientMode；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetGradientParam(BOOL bGradientBk,Color glrStart,Color glrEnd,LinearGradientMode gradientMode,BOOL bRedraw /*= FALSE*/)
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

// 函数 CMyUrlBt::GetGradientParam
// 作用：读取GetGradientParam。
// 参数：bGradientBk：是或否；glrStart；glrEnd；gradientMode。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::GetGradientParam(BOOL& bGradientBk,Color& glrStart,Color& glrEnd,LinearGradientMode& gradientMode)
{
	 bGradientBk = m_bGradientBk;
	 glrStart = m_glrStart;
	 glrEnd = m_glrEnd;
	 gradientMode = m_gradientMode;
}

// 函数 CMyUrlBt::SetCkbtFuncParam
// 作用：设置SetCkbtFuncParam。
// 参数：bCkbtFunc：是或否；curState；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetCkbtFuncParam(BOOL bCkbtFunc,int curState,BOOL bRedraw /*= FALSE*/)
{
	m_bCkbtFunc = bCkbtFunc;
	m_curStateId = curState;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::GetCkbtFuncParam
// 作用：读取GetCkbtFuncParam。
// 参数：bCkbtFunc：是或否；curState。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::GetCkbtFuncParam(BOOL& bCkbtFunc,int& curState)
{
	bCkbtFunc = m_bCkbtFunc;
	curState = m_curStateId;
	return;
}

// 函数 CMyUrlBt::SetBeCkbtFunc
// 作用：设置SetBeCkbtFunc。
// 参数：bCkbtFunc：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetBeCkbtFunc(BOOL bCkbtFunc,BOOL bRedraw /*= FALSE*/)
{
	m_bCkbtFunc = bCkbtFunc;
	
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::GetBeCkbtFunc
// 作用：读取GetBeCkbtFunc。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyUrlBt::GetBeCkbtFunc()
{
	return m_bCkbtFunc;
}

// 函数 CMyUrlBt::SetCkbtFuncCurState
// 作用：设置SetCkbtFuncCurState。
// 参数：curState；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetCkbtFuncCurState(int curState,BOOL bRedraw /*= FALSE*/)
{
	m_curStateId = curState;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyUrlBt::GetCkbtFuncCurState
// 作用：读取GetCkbtFuncCurState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyUrlBt::GetCkbtFuncCurState()
{
	return m_curStateId;
}

// 函数 CMyUrlBt::SetBeMinimizeBt
// 作用：设置SetBeMinimizeBt。
// 参数：bMinBt：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyUrlBt::SetBeMinimizeBt(BOOL bMinBt,BOOL bRedraw /*= FALSE*/)
{
	m_bMinBt = bMinBt;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyUrlBt::GetBeMinimizeBt
// 作用：读取GetBeMinimizeBt。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyUrlBt::GetBeMinimizeBt()
{
	return m_bMinBt;
}

// 函数 CMyUrlBt::EnableWindow
// 作用：改变EnableWindow的显示或可用状态。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 _TrackMouseEvent。
void CMyUrlBt::EnableWindow(BOOL bEnabled)
{
	if(bEnabled)
	{
		m_ctrlState = CTRL_URLBT_NOFOCUS;
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
	
		m_ctrlState = CTRL_URLBT_DISABLE;
	}
	CButton::EnableWindow(bEnabled);
}

// 函数 CMyUrlBt::SetBStaticSize
// 作用：设置SetBStaticSize。
// 参数：bStaticSize：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyUrlBt::SetBStaticSize(BOOL bStaticSize)
{
	m_bStaticSize = bStaticSize;
}

// 函数 CMyUrlBt::SetRatioMode
// 作用：设置SetRatioMode。
// 参数：bIsStaticRatio：是或否；bOnPaneDlg：是或否；bInvalidate：是或否；paneStandardWidth；paneStandardHeight。
// 返回：没有返回值。
// 过程：函数里会调用 _T、double、GetLogFont、Width、Height、GetParent。
void CMyUrlBt::SetRatioMode(BOOL bIsStaticRatio/* = FALSE*/,BOOL bOnPaneDlg/* = FALSE*/,BOOL bInvalidate /*= FALSE*/,int paneStandardWidth /*= 1920*/,int paneStandardHeight/* = 1080*/)
{
	if((paneStandardWidth <= 0) || (paneStandardHeight <= 0))
	{
		AfxMessageBox(_T("CMyUrlBt::SetRatioMode失败，paneStandardWidth和paneStandardHeight必须都大于零!"));
		return;
	}
	m_bStaticSize = bIsStaticRatio;
	m_bOnPaneDlg = bOnPaneDlg;
	m_paneStandardWidth = paneStandardWidth;
	m_paneStandardHeight = paneStandardHeight;

	if(!m_bStaticSize)
	{
		if(!m_bOnPaneDlg)
		{
			m_btHoriFontRatio = (double(m_fontOriginalHeight * GeneDpi)) / m_uiGeneDesDpi / GeneScreenXWidth;
			m_btVerFontRatio = (double(m_fontOriginalHeight * GeneDpi)) / m_uiGeneDesDpi / GeneScreenYHeight;
			GetLogFont().lfHeight = GeneCRDlg.Width() * m_btHoriFontRatio * 0.5 + GeneCRDlg.Height() * m_btVerFontRatio * 0.5;  
		}
		else
		{	//父窗口是对话框
			CRect rect;
			GetParent()->GetClientRect(&rect);
			m_btHoriFontRatio = (double(m_fontOriginalHeight * GeneDpi)) / m_uiGeneDesDpi / m_paneStandardWidth;
			m_btVerFontRatio = (double(m_fontOriginalHeight * GeneDpi)) / m_uiGeneDesDpi / m_paneStandardHeight;
			GetLogFont().lfHeight = rect.Width() * m_btHoriFontRatio * 0.5 + rect.Height() * m_btVerFontRatio * 0.5;
		}
	}
	else
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		GetLogFont().lfHeight =  rcClient.Height() * 0.7;  
	}

	SetMyFont();

	if(bInvalidate)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
}

// 函数 CMyUrlBt::DrawItem
// 作用：绘制DrawItem。
// 参数：lpDrawItemStruct。
// 返回：没有返回值。
// 过程：函数里会调用 clock、rcClient、Attach、GetSafeHdc、CreateCompatibleDC、CreateCompatibleBitmap。
void CMyUrlBt::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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

	//如果设置了文本，则绘制文本
	CString strText;
	GetWindowText(strText);
	if(0 != strText.GetLength())
	{
		switch(m_ctrlState)
		{
		case CTRL_URLBT_NOFOCUS:
			m_textColor = m_txClrNormal;
			break;
		case CTRL_URLBT_FOCUS:
			m_textColor = m_txClrFocused; 
			break;
		case CTRL_URLBT_SELECTED:
			m_textColor = m_txClrClicked;
			break;
		case CTRL_URLBT_DISABLE:
			if(m_bUseFourthState)
			{
				m_textColor = m_txClrDisabled;
			}
			else
			{
				m_textColor = m_txClrClicked;
			}
			break;
		}

		CFont *pOldFont = memDCTemp.SelectObject(&m_fontSet);
		CRect rectText = lpDrawItemStruct->rcItem;

		UINT state = lpDrawItemStruct->itemState;
		if(state & ODS_SELECTED)
		{
			rectText.OffsetRect(1,1);
		}

		int nOldBkMode = memDCTemp.SetBkMode(TRANSPARENT);
		memDCTemp.SetTextColor(m_textColor);
		rectText.left = (m_iconLeftIndent + m_iconW + m_iconRightIndent);
		if(!m_bStaticSize)
		{
			rectText.left *= GeneScreenXWidth / m_uiGeneDesWidth;
		}

		memDCTemp.DrawText(strText,&rectText,m_txFormat);

		CRect rcTemp;
		memDCTemp.DrawText(strText,&rcTemp,DT_CALCRECT);
		POINT ptStart,ptEnd;
		if(m_txFormat & DT_CENTER)
		{
			ptStart.x = (rectText.Width() - rcTemp.Width()) / 2;
			ptEnd.x = ptStart.x + rcTemp.Width();
		}
		else
		{
			ptStart.x = 0;
			ptEnd.x = rcTemp.Width();
		}

		if(m_txFormat & DT_VCENTER)
		{
			ptStart.y = ptEnd.y = (rectText.Height() - rcTemp.Height()) / 2 + rcTemp.Height() + 1;
		}
		else
		{
			ptStart.x = ptEnd.x = rcTemp.Height() + 1;
		}
		
		CPen pen;
		pen.CreatePen(PS_SOLID,1,m_textColor);
		CPen* pOldPen = memDCTemp.SelectObject(&pen);
		memDCTemp.MoveTo(ptStart);
		memDCTemp.LineTo(ptEnd);
		memDCTemp.SelectObject(pOldPen);
		pen.DeleteObject();

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

// 函数 CMyUrlBt::OnMouseMove
// 作用：鼠标在窗口上移动。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 _TrackMouseEvent。
void CMyUrlBt::OnMouseMove(UINT nFlags, CPoint point)
{
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

// 函数 CMyUrlBt::OnMouseLeave
// 作用：响应 Windows 或自定义消息 OnMouseLeave。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 Invalidate。
LRESULT CMyUrlBt::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
	if(CTRL_URLBT_NOFOCUS != m_ctrlState)
	{
		m_ctrlState = CTRL_URLBT_NOFOCUS;
		Invalidate();
	}
	m_bTracking = FALSE;
	return 0;
}

// 函数 CMyUrlBt::OnMouseHover
// 作用：响应 Windows 或自定义消息 OnMouseHover。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 Invalidate。
LRESULT CMyUrlBt::OnMouseHover(WPARAM wParam,LPARAM lParam)
{
	if(CTRL_URLBT_NOFOCUS == m_ctrlState)
	{
		m_ctrlState = CTRL_URLBT_FOCUS;
		Invalidate();
	}
	m_bTracking = FALSE;
	return 0;
}

// 函数 CMyUrlBt::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyUrlBt::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(CTRL_URLBT_FOCUS == m_ctrlState)
	{
		m_ctrlState = CTRL_URLBT_SELECTED;
		Invalidate();
	}
	__super::OnLButtonDown(nFlags, point);
}

// 函数 CMyUrlBt::OnLButtonUp
// 作用：松开鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyUrlBt::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(CTRL_URLBT_SELECTED == m_ctrlState)
	{
		m_ctrlState = CTRL_URLBT_FOCUS;
		Invalidate();
	}
	__super::OnLButtonUp(nFlags, point);
}

// 函数 CMyUrlBt::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindow、GetLogFont、Width、Height、GetParent、GetClientRect。
void CMyUrlBt::OnSize(UINT nType, int cx, int cy)
{
	if(IsWindow(m_hWnd))
	{
		if(!m_bStaticSize)
		{
			if(!m_bOnPaneDlg)
			{
				GetLogFont().lfHeight = GeneCRDlg.Width() * m_btHoriFontRatio * 0.6 + GeneCRDlg.Height() * m_btVerFontRatio * 0.4; 
			}
			else
			{	//父窗口是对话框
				CRect rect;
				GetParent()->GetClientRect(&rect);
				GetLogFont().lfHeight = rect.Width() * m_btHoriFontRatio * 0.5 + rect.Height() * m_btVerFontRatio * 0.5;
			}
		}
		else
		{
			CRect rcClient;
			GetClientRect(&rcClient);
			GetLogFont().lfHeight =  rcClient.Height() * 0.7;  
		}

		SetMyFont();
		Invalidate();
	}

 	__super::OnSize(nType, cx, cy);
}

// 函数 CMyUrlBt::PreTranslateMessage
// 作用：消息送达窗口前先拦截键盘或鼠标。
// 参数：pMsg：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 __super::PreTranslateMessage。
BOOL CMyUrlBt::PreTranslateMessage(MSG* pMsg)
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

// 函数 CMyUrlBt::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyUrlBt::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
