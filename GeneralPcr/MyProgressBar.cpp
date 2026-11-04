// 【交接】 GeneralPcr\MyProgressBar.cpp
// 作用：MyProgressBar 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyProgressBar、_T、Color、DeleteObject、MyDeletePtr、BEGIN_MESSAGE_MAP、ON_WM_SIZE。
// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "MyProgressBar.h"

IMPLEMENT_DYNAMIC(CMyProgressBar, CStatic)

// 函数 CMyProgressBar::CMyProgressBar
// 作用：执行CMyProgressBar。
// 参数：bAutoDynamic：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 _T、Color。
CMyProgressBar::CMyProgressBar(BOOL bAutoDynamic /*= FALSE*/)
{
	m_bkColor = CLR_SOFT_THEME;
	m_iconWidth = 0;

	m_bSingleLine = TRUE;
	m_nFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;

	m_bFstPaint = TRUE;
	m_pMemDc = NULL;
	m_bAutoDynamic = bAutoDynamic;
	m_fstPaintWidth = 0;
	m_fstPaintHeight = 0;
	m_hBitmap = NULL;

	m_dProgress = 0;
	m_pngPicPath = _T("");

	m_clrRopBk = Color(0XFF,0XFF,0XFF);
	m_clrRopFrame = Color(0XFF,0XFF,0XFF);

	m_clrBk = COLOR_2LEVEL_THEME;
	m_clrFrame = COLOR_2LEVEL_THEME;
#ifdef XINYI_THEME
	m_clrBk = Color(0,37,94);
	m_clrFrame = Color(0,37,94);
#endif
}

// 函数 CMyProgressBar::~CMyProgressBar
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、MyDeletePtr。
CMyProgressBar::~CMyProgressBar()
{
	if(NULL != m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
	}

	MyDeletePtr(&m_pMemDc);
}

BEGIN_MESSAGE_MAP(CMyProgressBar, CStatic)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// 函数 CMyProgressBar::SetSingleLineState
// 作用：设置SetSingleLineState。
// 参数：bSingleLine：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyProgressBar::SetSingleLineState(BOOL bSingleLine/* = TRUE*/)
{
	m_bSingleLine = bSingleLine;
}

// 函数 CMyProgressBar::GetSingleLineState
// 作用：读取GetSingleLineState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyProgressBar::GetSingleLineState()
{
	return m_bSingleLine;
}

// 函数 CMyProgressBar::SetWordStyle
// 作用：设置SetWordStyle。
// 参数：nFormat：整数；bInvalidate：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyProgressBar::SetWordStyle(UINT nFormat,BOOL bInvalidate /*= FALSE*/)
{
	m_nFormat = nFormat;
	if(bInvalidate)
	{
		Invalidate();
	}
}

// 函数 CMyProgressBar::GetWordStyle
// 作用：读取GetWordStyle。
// 参数：nFormat：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyProgressBar::GetWordStyle(UINT& nFormat)
{
	nFormat = m_nFormat;
}

// 函数 CMyProgressBar::DrawItem
// 作用：绘制DrawItem。
// 参数：lpDrawItemStruct。
// 返回：没有返回值。
// 过程：函数里会调用 clock、rcClient、Attach、GetSafeHdc、CreateCompatibleDC、CreateCompatibleBitmap。
void CMyProgressBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
#ifdef _DEBUG
	clock_t startMs = clock();
#endif

	CRect rect = lpDrawItemStruct->rcItem;
	CRect rcClient(rect);
	CDC cDC;
	cDC.Attach(lpDrawItemStruct->hDC);
	ASSERT(NULL != cDC.GetSafeHdc());

	CDC memDC;
	memDC.CreateCompatibleDC(&cDC);
	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(&cDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDC.SelectObject(&bitMapCB);

	if(m_bAutoDynamic)
	{
		if(m_bFstPaint)
		{
			memDC.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&cDC,0,0,SRCCOPY);

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
			memDC.StretchBlt(0,0,rect.Width(),rect.Height(),m_pMemDc,0,0,m_fstPaintWidth,m_fstPaintHeight,SRCCOPY);
		}
	}
	else
	{
		memDC.FillSolidRect(&rect,m_bkColor); 
	}

	int iArcAngle = 4 * m_dVertRatio;
	
	DrawRoundRectangleNew(&memDC,rect.left,rect.top,rect.Width() - 1,rect.Height() - 1,iArcAngle,iArcAngle,iArcAngle,iArcAngle,FALSE,m_clrFrame,1,TRUE,m_clrBk,1);
	
	int iColorW = rect.Width() * m_dProgress;
	if(iColorW > 0)
	{
		if(iColorW <= iArcAngle * 2)
		{
			CDC memDcTemp;
			memDcTemp.CreateCompatibleDC(&cDC);
			CBitmap bitMapCBTemp;
			bitMapCBTemp.CreateCompatibleBitmap(&cDC,rect.Width(),rect.Height());
			CBitmap* pOldBitmapCbTemp = memDcTemp.SelectObject(&bitMapCBTemp);

			memDcTemp.BitBlt(rect.left,rect.top,rect.Width(),rect.Height(),&memDC,rect.left,rect.top,SRCCOPY);
			DrawRoundRectangleNew(&memDcTemp,rect.left + 1,rect.top + 1,rect.Width() - 3,rect.Height() - 3,iArcAngle,iArcAngle,iArcAngle,iArcAngle,FALSE,m_clrRopFrame,1,TRUE,m_clrRopBk,1);
			memDC.BitBlt(rect.left,rect.top,iColorW,rect.Height(),&memDcTemp,rect.left,rect.top,SRCCOPY);

			memDcTemp.SelectObject(pOldBitmapCbTemp);
			bitMapCBTemp.DeleteObject();
			memDcTemp.DeleteDC();
		}
		else
		{
			DrawRoundRectangleNew(&memDC,rect.left + 1,rect.top + 1,(rect.Width() - 2) * m_dProgress - 1,rect.Height() - 3,iArcAngle,iArcAngle,iArcAngle,iArcAngle,FALSE,m_clrRopFrame,1,TRUE,m_clrRopBk,1);
		}
	}
	
	CString strText;
	GetWindowText(strText);
	if(0 != strText.GetLength())
	{
		int nOldBkMode = memDC.SetBkMode(TRANSPARENT);
		CFont *pOldFont = memDC.SelectObject(&m_fontSet);
		CSize szExtent = memDC.GetTextExtent(strText,_tcslen(strText));
		memDC.SetTextColor(m_textColor);
	
		rect.left = m_iconWidth;

		int strHeight = rect.Height();
		if((!(m_nFormat & DT_SINGLELINE)) && (m_nFormat & DT_VCENTER))
		{
			CRect rectNew(rect);
			strHeight = memDC.DrawText(strText,&rectNew,m_nFormat | DT_CALCRECT);
		}
		rect.top += (rect.Height() - strHeight) / 2;
		memDC.DrawText(strText,&rect,m_nFormat);

		memDC.SelectObject(pOldFont);
		memDC.SetBkMode(nOldBkMode);
	}
	
	cDC.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDC,0,0,SRCCOPY);

	memDC.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDC.DeleteDC();

	cDC.Detach();

#ifdef _DEBUG
	clock_t endMs = clock();
#endif

	return;
}

// 函数 CMyProgressBar::PreSubclassWindow
// 作用：执行PreSubclassWindow。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ModifyStyle。
void CMyProgressBar::PreSubclassWindow()
{
	ModifyStyle(0,SS_OWNERDRAW);
	CStatic::PreSubclassWindow();
}

// 函数 CMyProgressBar::SetBkColor
// 作用：设置SetBkColor。
// 参数：bkColor：颜色。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyProgressBar::SetBkColor(COLORREF bkColor)
{
	m_bkColor = bkColor;
}

// 函数 CMyProgressBar::GetBkColor
// 作用：读取GetBkColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyProgressBar::GetBkColor()
{
	return m_bkColor;
}

// 函数 CMyProgressBar::SetTextColor
// 作用：设置SetTextColor。
// 参数：textColor：颜色；bInvalidate：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyProgressBar::SetTextColor(COLORREF textColor,BOOL bInvalidate /*= FALSE*/)
{
	m_textColor = textColor;
	if(bInvalidate)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
}

// 函数 CMyProgressBar::GetTextColor
// 作用：读取GetTextColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyProgressBar::GetTextColor()
{
	return m_textColor;
}

// 函数 CMyProgressBar::SetBmpBkPic
// 作用：设置SetBmpBkPic。
// 参数：bkPicId；iconWidth；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate、UpdateWindow。
void CMyProgressBar::SetBmpBkPic(int bkPicId,int iconWidth /*= 0*/,BOOL bRedraw /*= FALSE*/)
{
	m_bkPicID = bkPicId;
	m_iconWidth = iconWidth;

	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
			UpdateWindow();
		}
	}
}

// 函数 CMyProgressBar::SetPngBkPic
// 作用：设置SetPngBkPic。
// 参数：picPath；bInvalidate：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyProgressBar::SetPngBkPic(wstring picPath,BOOL bInvalidate /*= FALSE*/)
{
	m_pngPicPath = picPath;
	if(bInvalidate)
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyProgressBar::SetCurProgress
// 作用：设置SetCurProgress。
// 参数：dProgress：小数；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyProgressBar::SetCurProgress(double dProgress,BOOL bRedraw /*= FALSE*/)
{
	if(dProgress < 0)
	{
		dProgress = 0;
	}

	if(dProgress > 1)  
	{
		dProgress = 1;
	}

	m_dProgress = dProgress;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}	

	return;
}

// 函数 CMyProgressBar::SetZero
// 作用：设置SetZero。
// 参数：bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyProgressBar::SetZero(BOOL bRedraw /*= FALSE*/)
{
	m_dProgress = 0;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}	

	return;
}

// 函数 CMyProgressBar::SetOneHundred
// 作用：设置SetOneHundred。
// 参数：bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyProgressBar::SetOneHundred(BOOL bRedraw /*= FALSE*/)
{
	m_dProgress = 1;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}	

	return;
}

// 函数 CMyProgressBar::GetProgress
// 作用：读取GetProgress。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CMyProgressBar::GetProgress()
{
	return m_dProgress;
}

// 函数 CMyProgressBar::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 CStatic::OnSize。
void CMyProgressBar::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
}

// 函数 CMyProgressBar::WindowProc
// 作用：执行WindowProc。
// 参数：message；wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 DefWindowProc。
LRESULT CMyProgressBar::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(WM_NCHITTEST == message || WM_NCLBUTTONDOWN == message || WM_NCLBUTTONDBLCLK == message)
	{
		return ::DefWindowProc(m_hWnd,message,wParam,lParam);
	}

	return __super::WindowProc(message, wParam, lParam);
}

// 函数 CMyProgressBar::OnVScroll
// 作用：垂直滚动条移动。
// 参数：nSBCode：整数；nPos：整数；pScrollBar：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 __super::OnVScroll。
void CMyProgressBar::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}

// 函数 CMyProgressBar::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyProgressBar::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
