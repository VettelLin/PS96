// 【交接】 GeneralPcr\MyStatic.cpp
// 作用：MyStatic 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyStatic、RGB、_T、MyDeletePtr、DeleteObject、BEGIN_MESSAGE_MAP、ON_WM_SIZE。
// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "MyStatic.h"

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

// 函数 CMyStatic::CMyStatic
// 作用：执行CMyStatic。
// 参数：bAutoDynamic：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 RGB、_T。
CMyStatic::CMyStatic(BOOL bAutoDynamic /*= FALSE*/)
{
	m_bkColor = RGB(0XFF,0XFA,0XF0);

	m_iconWidth = 0;

	m_bSingleLine = TRUE;
	m_bHasBkPic = FALSE;
	m_bHasPngBkPic = FALSE;
	m_pngPicPath = _T("");
	m_nFormat = DT_LEFT | DT_VCENTER | DT_WORDBREAK;

	m_bDynamic = FALSE;

	m_bFstPaint = TRUE;
	m_pMemDc = NULL;
	m_bAutoDynamic = bAutoDynamic;
	m_fstPaintWidth = 0;
	m_fstPaintHeight = 0;
	m_sonPicNums = 1;
	m_curState = 1;
	m_hBitmap = NULL;

	m_iconLeftIndent = 0;
	m_iconRightIndent = 0;

	m_bTwinkle = FALSE;
	m_bTwinkleShow = TRUE;

	m_bHaveRoundRectBk = FALSE;
	m_clrFourAngleBk = CLR_SOFT_THEME;
	m_clrRoundRectBk = COLOR_2LEVEL_THEME;
	m_iArcRadius = 4;
}

// 函数 CMyStatic::~CMyStatic
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 MyDeletePtr、DeleteObject。
CMyStatic::~CMyStatic()
{
	MyDeletePtr(&m_pMemDc);

	if(NULL != m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
	}
}

BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// 函数 CMyStatic::SetSingleLineState
// 作用：设置SetSingleLineState。
// 参数：bSingleLine：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyStatic::SetSingleLineState(BOOL bSingleLine/* = TRUE*/)
{
	m_bSingleLine = bSingleLine;
}

// 函数 CMyStatic::GetSingleLineState
// 作用：读取GetSingleLineState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyStatic::GetSingleLineState()
{
	return m_bSingleLine;
}

// 函数 CMyStatic::SetWordStyle
// 作用：设置SetWordStyle。
// 参数：nFormat：整数；bInvalidate：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyStatic::SetWordStyle(UINT nFormat,BOOL bInvalidate /*= FALSE*/)
{
	m_nFormat = nFormat;
	if(bInvalidate)
	{
		Invalidate();
	}
}

// 函数 CMyStatic::GetWordStyle
// 作用：读取GetWordStyle。
// 参数：nFormat：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyStatic::GetWordStyle(UINT& nFormat)
{
	nFormat = m_nFormat;
}

// 函数 CMyStatic::DrawItem
// 作用：绘制DrawItem。
// 参数：lpDrawItemStruct。
// 返回：没有返回值。
// 过程：函数里会调用 clock、rcClient、Attach、GetSafeHdc、CreateCompatibleDC、CreateCompatibleBitmap。
void CMyStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
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

	if(m_bHaveRoundRectBk)
	{
		memDCTemp.FillSolidRect(&rect,m_clrFourAngleBk);
		DrawRoundRectangleNew(&memDCTemp,rect.left,rect.top,rect.Width() - 1,rect.Height() - 1,m_iArcRadius,m_iArcRadius,m_iArcRadius,m_iArcRadius,FALSE,m_clrRoundRectBk,1,TRUE,m_clrRoundRectBk,1);
	}

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

	if(m_bHasBkPic)
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC(&cDC);
		CBitmap bitMap;
		bitMap.LoadBitmap(m_bkPicID);
		CBitmap* pOldBitmap = dcMem.SelectObject(&bitMap);
		BITMAP bit;
		bitMap.GetBitmap(&bit);
		memDCTemp.SetStretchBltMode(HALFTONE);
		memDCTemp.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,bit.bmWidth,bit.bmHeight,SRCCOPY);
		dcMem.SelectObject(pOldBitmap);
		bitMap.DeleteObject();
		dcMem.DeleteDC();
	}
	else if(m_bHasPngBkPic)
	{
		if(m_bTwinkle)
		{
			if(!m_bTwinkleShow)
			{
				if(-1 == m_curState || m_curState > m_sonPicNums)
				{
					memDCTemp.FillSolidRect(rcClient,RGB(3,91,199));
				}
				else
				{
					memDCTemp.FillSolidRect(rcClient,RGB(3,91,199));
					int curState = 2;
					if(3 == m_curState || 5 == m_curState)
					{
						curState = 4;
					}
					Graphics graphics(memDCTemp.m_hDC);
					Image image(m_pngPicPath);

					int bkW = image.GetWidth() / m_sonPicNums;
					int startX = (curState - 1) * bkW;

					graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
					ImageAttributes ImgAtt;
					ImgAtt.SetWrapMode(WrapModeTileFlipXY);
					Rect destRect;
					destRect.X = m_iconLeftIndent;
					if(rect.Height() > image.GetHeight())
					{
						destRect.Y = (rect.Height() - image.GetHeight()) / 2;
					}

					if(bkW > rect.Width() - m_iconLeftIndent)
					{
						destRect.Width = rect.Width() - m_iconLeftIndent;
					}
					else
					{
						destRect.Width = bkW;
					}

					destRect.Height = rect.Height() - destRect.Y * 2;

					if(0 == m_iconWidth)
					{
						destRect = Rect(rect.left,rect.top,rect.Width(),rect.Height());
					}

					graphics.DrawImage(&image,destRect,startX,0,bkW,image.GetHeight(),UnitPixel,&ImgAtt);
					graphics.ReleaseHDC(memDCTemp.m_hDC);
				}
			}
			else
			{
				Graphics graphics(memDCTemp.m_hDC);
				Image image(m_pngPicPath);

				int bkW = image.GetWidth() / m_sonPicNums;
				int startX = (m_curState - 1) * bkW;

				graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
				ImageAttributes ImgAtt;
				ImgAtt.SetWrapMode(WrapModeTileFlipXY);
				Rect destRect;
				destRect.X = m_iconLeftIndent;
				if(rect.Height() > image.GetHeight())
				{
					destRect.Y = (rect.Height() - image.GetHeight()) / 2;
				}

				if(bkW > rect.Width() - m_iconLeftIndent)
				{
					destRect.Width = rect.Width() - m_iconLeftIndent;
				}
				else
				{
					destRect.Width = bkW;
				}

				destRect.Height = rect.Height() - destRect.Y * 2;

				if(0 == m_iconWidth)
				{
					destRect = Rect(rect.left,rect.top,rect.Width(),rect.Height());
				}

				graphics.DrawImage(&image,destRect,startX,0,bkW,image.GetHeight(),UnitPixel,&ImgAtt);
				graphics.ReleaseHDC(memDCTemp.m_hDC);
			}
		}
		else
		{
			if(-1 == m_curState || m_curState > m_sonPicNums)
			{
				memDCTemp.FillSolidRect(rcClient,RGB(38,38,38));
			}
			else
			{
				Graphics graphics(memDCTemp.m_hDC);
				Image image(m_pngPicPath);

				int bkW = image.GetWidth() / m_sonPicNums;
				int startX = (m_curState - 1) * bkW;

				graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
				ImageAttributes ImgAtt;
				ImgAtt.SetWrapMode(WrapModeTileFlipXY);
				Rect destRect;
				destRect.X = m_iconLeftIndent;
				if(rect.Height() > image.GetHeight())
				{
					destRect.Y = (rect.Height() - image.GetHeight()) / 2;
				}

				if(bkW > rect.Width() - m_iconLeftIndent)
				{
					destRect.Width = rect.Width() - m_iconLeftIndent;
				}
				else
				{
					destRect.Width = bkW;
				}

				destRect.Height = rect.Height() - destRect.Y * 2;

				if(0 == m_iconWidth)
				{
					destRect = Rect(rect.left,rect.top,rect.Width(),rect.Height());
				}

				graphics.DrawImage(&image,destRect,startX,0,bkW,image.GetHeight(),UnitPixel,&ImgAtt);
				graphics.ReleaseHDC(memDCTemp.m_hDC);
			}
		}
	}
	else
	{
		if(m_bDynamic)
		{
			memDCTemp.FillSolidRect(&rect,m_bkColor);
		}
	}

	CString strText;
	GetWindowText(strText);
	if(0 != strText.GetLength())
	{
		int nOldBkMode = memDCTemp.SetBkMode(TRANSPARENT);
		CFont *pOldFont = memDCTemp.SelectObject(&m_fontSet);
		memDCTemp.SetTextColor(m_textColor);
	
		rect.left =  m_iconLeftIndent + m_iconRightIndent + m_iconWidth;

		if(m_bSingleLine)
		{
			m_nFormat |= DT_SINGLELINE;
		}	
		
		int strHeight = rect.Height();
		if((!(m_nFormat & DT_SINGLELINE)) && (m_nFormat & DT_VCENTER))
		{
			CRect rectNew(rect);
			memDCTemp.DrawText(strText,&rectNew,m_nFormat | DT_CALCRECT);
			strHeight = rectNew.Height();
		}

		int iTemp1 = (rect.Height() - strHeight) / 2;
		rect.top += iTemp1;
		rect.bottom -= iTemp1;
		memDCTemp.DrawText(strText,&rect,m_nFormat);
		memDCTemp.SelectObject(pOldFont);
		memDCTemp.SetBkMode(nOldBkMode);
	}
	
	cDC.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDCTemp,0,0,SRCCOPY);

	memDCTemp.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDCTemp.DeleteDC();

	cDC.Detach();

#ifdef _DEBUG
	clock_t endMs = clock();
#endif

	return;
}

// 函数 CMyStatic::PreSubclassWindow
// 作用：执行PreSubclassWindow。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ModifyStyle。
void CMyStatic::PreSubclassWindow()
{
	ModifyStyle(0,SS_OWNERDRAW);
	CStatic::PreSubclassWindow();
}

// 函数 CMyStatic::SetCurState
// 作用：设置SetCurState。
// 参数：curState；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate、UpdateWindow。
void CMyStatic::SetCurState(int curState,BOOL bRedraw /*= FALSE*/)
{
	m_curState = curState;

	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
			UpdateWindow();
		}
	}
}

// 函数 CMyStatic::SetBkColor
// 作用：设置SetBkColor。
// 参数：bkColor：颜色。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyStatic::SetBkColor(COLORREF bkColor)
{
	m_bkColor = bkColor;
}

// 函数 CMyStatic::GetBkColor
// 作用：读取GetBkColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyStatic::GetBkColor()
{
	return m_bkColor;
}

// 函数 CMyStatic::SetTextColor
// 作用：设置SetTextColor。
// 参数：textColor：颜色；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyStatic::SetTextColor(COLORREF textColor,BOOL bRedraw /*= FALSE*/)
{
	m_textColor = textColor;
	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
}

// 函数 CMyStatic::GetTextColor
// 作用：读取GetTextColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyStatic::GetTextColor()
{
	return m_textColor;
}

// 函数 CMyStatic::SetBmpBkPic
// 作用：设置SetBmpBkPic。
// 参数：bkPicId；iconWidth；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate、UpdateWindow。
void CMyStatic::SetBmpBkPic(int bkPicId,int iconWidth /*= 0*/,BOOL bRedraw /*= FALSE*/)
{
	m_bkPicID = bkPicId;
	m_iconWidth = iconWidth;
	m_bHasBkPic = TRUE;

	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
			UpdateWindow();
		}
	}
}

// 函数 CMyStatic::SetPngBkPic
// 作用：设置SetPngBkPic。
// 参数：picPath；sonPicNums；iconWidth；iconLeftIndent；iconRightIndent；bInvalidate：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyStatic::SetPngBkPic(CString picPath,int sonPicNums/* = 1*/,int iconWidth /*= 0*/,int iconLeftIndent /*= 0*/,int iconRightIndent /*= 0*/,BOOL bInvalidate /*= FALSE*/)
{
	m_pngPicPath = picPath;
	m_iconWidth = iconWidth;
	m_iconLeftIndent = iconLeftIndent;
	m_iconRightIndent = iconRightIndent;
	m_bHasPngBkPic = TRUE;
	if(sonPicNums > 0)
	{
		m_sonPicNums = sonPicNums;
	}
	
	if(bInvalidate)
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyStatic::SetRoundRectBkParam
// 作用：设置SetRoundRectBkParam。
// 参数：bHaveRoundRectBk：是或否；clrFourAngle：颜色；clrRoundRectBk：矩形区域；iArcRadius：整数；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyStatic::SetRoundRectBkParam(BOOL bHaveRoundRectBk,COLORREF clrFourAngle,Color clrRoundRectBk,int iArcRadius,BOOL bRedraw /*= FALSE*/)
{
	m_bHaveRoundRectBk = bHaveRoundRectBk;
	m_clrFourAngleBk = clrFourAngle;
	m_clrRoundRectBk = clrRoundRectBk;
	m_iArcRadius = iArcRadius;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyStatic::GetRoundRectBkColor
// 作用：读取GetRoundRectBkColor。
// 参数：无。
// 返回：返回 Color。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
Color CMyStatic::GetRoundRectBkColor()
{
	return m_clrRoundRectBk;
}

// 函数 CMyStatic::GetRoundRectArcSize
// 作用：读取GetRoundRectArcSize。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMyStatic::GetRoundRectArcSize()
{
	return m_iArcRadius;
}

// 函数 CMyStatic::SetBDynamic
// 作用：设置SetBDynamic。
// 参数：bDyNaminc：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyStatic::SetBDynamic(BOOL bDyNaminc)
{
	m_bDynamic = bDyNaminc;
}

// 函数 CMyStatic::GetBDynamic
// 作用：读取GetBDynamic。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyStatic::GetBDynamic()
{
	return m_bDynamic;
}

// 函数 CMyStatic::StartTwinkle
// 作用：执行StartTwinkle。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTimer。
void CMyStatic::StartTwinkle()
{
	SetTimer(INSTRUSTATELAMPTWINKLE,1000,NULL);
	m_bTwinkle = TRUE;
}

// 函数 CMyStatic::StopTwinkle
// 作用：执行StopTwinkle。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 KillTimer、Invalidate。
void CMyStatic::StopTwinkle()
{
	KillTimer(INSTRUSTATELAMPTWINKLE);
	m_bTwinkle = FALSE;
	Invalidate(FALSE);
}

// 函数 CMyStatic::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 CStatic::OnSize。
void CMyStatic::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
}

// 函数 CMyStatic::WindowProc
// 作用：执行WindowProc。
// 参数：message；wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 DefWindowProc。
LRESULT CMyStatic::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if(WM_NCHITTEST == message || WM_NCLBUTTONDOWN == message || WM_NCLBUTTONDBLCLK == message)
	{
		return ::DefWindowProc(m_hWnd,message,wParam,lParam);
	}

	return __super::WindowProc(message, wParam, lParam);
}

// 函数 CMyStatic::OnVScroll
// 作用：垂直滚动条移动。
// 参数：nSBCode：整数；nPos：整数；pScrollBar：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 __super::OnVScroll。
void CMyStatic::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	__super::OnVScroll(nSBCode, nPos, pScrollBar);
}

// 函数 CMyStatic::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyStatic::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// 函数 CMyStatic::OnTimer
// 作用：定时器到期时刷新界面或推进状态。
// 参数：nIDEvent：整数。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyStatic::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)      
	{      
	case INSTRUSTATELAMPTWINKLE:       
		m_bTwinkleShow = !m_bTwinkleShow;
		Invalidate(FALSE);
		break;      
	default:   
		break;     

	} 
	CStatic::OnTimer(nIDEvent);
}
