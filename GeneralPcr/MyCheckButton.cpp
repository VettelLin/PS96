// 【交接】 GeneralPcr\MyCheckButton.cpp
// 作用：MyCheckButton 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyCheckButton、RGB、_T、BEGIN_MESSAGE_MAP、ON_WM_LBUTTONDOWN、ON_WM_LBUTTONUP、ON_WM_SIZE。
// RoundButton.cpp : implementation file

#include "stdafx.h"
#include "MyCheckButton.h"
#include <GdiPlus.h>
using namespace Gdiplus;

IMPLEMENT_DYNAMIC(CMyCheckButton, CButton)

// 函数 CMyCheckButton::CMyCheckButton
// 作用：执行CMyCheckButton。
// 参数：):CFontSet(TRUE。
// 返回：没有返回值。
// 过程：函数里会调用 RGB、_T。
CMyCheckButton::CMyCheckButton():CFontSet(TRUE)
{
	m_bkClrUnchked = RGB(0XFF,0XFF,0XF0);
	m_bkClrChked = RGB(0,170,222);
	m_bRoundStyle = FALSE;

	m_isBtChecked = FALSE;
	m_bHasBkPic = FALSE;
	m_bHasPngBkPic = FALSE;

	m_picPath = _T("");
	m_sonPicNums = 2;
	m_iconW = 0;
	m_iLeftIndent = 2;
	m_rightEnd = 0;
	m_txClrUnchecked = RGB(0,0,0);
	m_txClrChecked = RGB(0,0,0);
	m_pngBkClr = RGB(255,255,255);
	m_cheBtHoriFontRatio = 0;
	m_cheBtVerFontRatio = 0;
	m_bShieldClickMsg = FALSE;
	m_bNeedRedrawBk = FALSE;
	m_bParentProcMouseClick = FALSE;

	m_roundStyleBkClr = RGB(255,255,255);
	m_bTickStyle = FALSE;
	m_dwWordStyle = DT_LEFT | DT_VCENTER | DT_SINGLELINE;

	m_clrFrame = RGB(0,0,0);
	m_selStateSerail = 2;
}

// 函数 CMyCheckButton::~CMyCheckButton
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyCheckButton::~CMyCheckButton()
{
	
}

BEGIN_MESSAGE_MAP(CMyCheckButton, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CMyCheckButton message handlers

// 函数 CMyCheckButton::PreSubclassWindow
// 作用：执行PreSubclassWindow。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ModifyStyle。
void CMyCheckButton::PreSubclassWindow()
{
	ModifyStyle(0,BS_OWNERDRAW);
	CButton::PreSubclassWindow();
}

// 函数 CMyCheckButton::SetBkPicture
// 作用：设置SetBkPicture。
// 参数：idChecked；idUnChecked；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetBkPicture(UINT idChecked,UINT idUnChecked,BOOL bRedraw /*= FALSE*/)
{
	m_idChecked = idChecked;
	m_idUnChecked = idUnChecked;
	m_sonPicNums = 1;
	m_bHasBkPic = TRUE;
	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
}

// 函数 CMyCheckButton::SetBkPicture
// 作用：设置SetBkPicture。
// 参数：idPicture；sonPicNums；iconW。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyCheckButton::SetBkPicture(UINT idPicture,int sonPicNums /*= 2*/,int iconW /*= 0*/)
{
	m_idChecked = idPicture;
	m_sonPicNums = sonPicNums;
	m_bHasBkPic = TRUE;
	m_iconW = iconW;
}

// 函数 CMyCheckButton::SetPngBkPic
// 作用：设置SetPngBkPic。
// 参数：picPath；sonPicNums；iconW；pngBkClr；bInvalidate：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetPngBkPic(wstring picPath,int sonPicNums /*= 2*/,int iconW /*= 0*/,COLORREF pngBkClr /*= RGB(255,255,255)*/,BOOL bInvalidate /*= FALSE*/)
{
	m_picPath = picPath;
	m_sonPicNums = sonPicNums;
	m_iconW = iconW;
	m_bHasPngBkPic = TRUE;
	if(bInvalidate && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return;
}

// 函数 CMyCheckButton::SetBtChecked
// 作用：设置SetBtChecked。
// 参数：btState；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetBtChecked(BOOL btState,BOOL bRedraw /*= FALSE*/)
{
	if(btState)
	{
		m_isBtChecked = TRUE;
	}
	else
	{
		m_isBtChecked = FALSE;
	}
	
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyCheckButton::GetCheckState
// 作用：读取GetCheckState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyCheckButton::GetCheckState()
{
	return m_isBtChecked;
}

// 函数 CMyCheckButton::SetShieldClickMsgState
// 作用：设置SetShieldClickMsgState。
// 参数：bShieldClickMsg：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyCheckButton::SetShieldClickMsgState(BOOL bShieldClickMsg)
{
	m_bShieldClickMsg = bShieldClickMsg;
	return;
}

// 函数 CMyCheckButton::GetShieldClickMsgState
// 作用：读取GetShieldClickMsgState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyCheckButton::GetShieldClickMsgState()
{
	return m_bShieldClickMsg;
}

// 函数 CMyCheckButton::SetBkColor
// 作用：设置SetBkColor。
// 参数：bkClrUnchked；bkClrChked；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetBkColor(COLORREF bkClrUnchked,COLORREF bkClrChked,BOOL bRedraw /*= FALSE*/)
{
	m_bkClrUnchked = bkClrUnchked;
	m_bkClrChked = bkClrChked;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyCheckButton::GetBkColor
// 作用：读取GetBkColor。
// 参数：bkClrUnchked；bkClrChked。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyCheckButton::GetBkColor(COLORREF& bkClrUnchked,COLORREF& bkClrChked)
{
	bkClrUnchked = m_bkClrUnchked;
	bkClrChked = m_bkClrChked;
	return;
}

// 函数 CMyCheckButton::SetRoundStyle
// 作用：设置SetRoundStyle。
// 参数：bRoundSytle：是或否；roundStyleBkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetRoundStyle(BOOL bRoundSytle,COLORREF roundStyleBkClr,BOOL bRedraw /*= FALSE*/)
{
	m_bRoundStyle = bRoundSytle;
	m_roundStyleBkClr = roundStyleBkClr;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyCheckButton::GetRoundStyle
// 作用：读取GetRoundStyle。
// 参数：pRoundStyleBkClr：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyCheckButton::GetRoundStyle(COLORREF* pRoundStyleBkClr /*= NULL*/)
{
	if(NULL != pRoundStyleBkClr)
	{
		*pRoundStyleBkClr = m_roundStyleBkClr;
	}

	return m_bRoundStyle;
}

// 函数 CMyCheckButton::SetTickStyle
// 作用：设置SetTickStyle。
// 参数：bTickSytle：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetTickStyle(BOOL bTickSytle,BOOL bRedraw /*= FALSE*/)
{
	m_bTickStyle = bTickSytle;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return;
}

// 函数 CMyCheckButton::GetTickStyle
// 作用：读取GetTickStyle。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyCheckButton::GetTickStyle()
{
	return m_bTickStyle;
}

// 函数 CMyCheckButton::SetWordStyle
// 作用：设置SetWordStyle。
// 参数：dwWordStyle；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetWordStyle(DWORD dwWordStyle,BOOL bRedraw /*= FALSE*/)
{
	m_dwWordStyle = dwWordStyle;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return;
}

// 函数 CMyCheckButton::GetWordStyle
// 作用：读取GetWordStyle。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
DWORD CMyCheckButton::GetWordStyle()
{
	return m_dwWordStyle;
}

// 函数 CMyCheckButton::SetFrameColor
// 作用：设置SetFrameColor。
// 参数：clrFrame：颜色；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetFrameColor(COLORREF clrFrame,BOOL bRedraw /*= FALSE*/)
{
	m_clrFrame = clrFrame;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate();
	}
	return;
}

// 函数 CMyCheckButton::GetFrameColor
// 作用：读取GetFrameColor。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyCheckButton::GetFrameColor()
{
	return m_clrFrame;
}

// 函数 CMyCheckButton::SetSelectStateSerail
// 作用：设置SetSelectStateSerail。
// 参数：selStateSerial；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetSelectStateSerail(int selStateSerial,BOOL bRedraw /*= FALSE*/)
{
	m_selStateSerail = selStateSerial;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate();
	}
	return;
}

// 函数 CMyCheckButton::GetSelectStateSerail
// 作用：读取GetSelectStateSerail。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMyCheckButton::GetSelectStateSerail()
{
	return m_selStateSerail;
}

// 函数 CMyCheckButton::SetTextColor
// 作用：设置SetTextColor。
// 参数：txClrUnchecked；txClrChecked；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetTextColor(COLORREF txClrUnchecked,COLORREF txClrChecked /*= RGB(0,0,0)*/,BOOL bRedraw /*= FALSE*/)
{
	m_txClrUnchecked = txClrUnchecked;
	m_txClrChecked = txClrChecked;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
}

// 函数 CMyCheckButton::GetTextColor
// 作用：读取GetTextColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyCheckButton::GetTextColor()
{
	return m_txClrUnchecked;
}

// 函数 CMyCheckButton::SetBeNeedRedrawBk
// 作用：设置SetBeNeedRedrawBk。
// 参数：bNeedRedrawBk：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetBeNeedRedrawBk(BOOL bNeedRedrawBk,BOOL bRedraw /*= FALSE*/)
{
	m_bNeedRedrawBk = bNeedRedrawBk;

	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
	return;
}

// 函数 CMyCheckButton::GetBeNeedRedrawBk
// 作用：读取GetBeNeedRedrawBk。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyCheckButton::GetBeNeedRedrawBk()
{
	return m_bNeedRedrawBk;
}

// 函数 CMyCheckButton::SetPngBkColor
// 作用：设置SetPngBkColor。
// 参数：pngBkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetPngBkColor(COLORREF pngBkClr,BOOL bRedraw /*= FALSE*/)
{
	m_pngBkClr = pngBkClr;

	if(bRedraw)
	{
		if(NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
	}
	return;
}

// 函数 CMyCheckButton::GetPngBkColor
// 作用：读取GetPngBkColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyCheckButton::GetPngBkColor()
{
	return m_pngBkClr;
}

// 函数 CMyCheckButton::SetBeParentProcessMouseClick
// 作用：设置SetBeParentProcessMouseClick。
// 参数：bParentProcMouseClick：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetBeParentProcessMouseClick(BOOL bParentProcMouseClick,BOOL bRedraw /*= FALSE*/)
{
	m_bParentProcMouseClick = bParentProcMouseClick;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyCheckButton::GetBeParentProcessMouseClick
// 作用：读取GetBeParentProcessMouseClick。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMyCheckButton::GetBeParentProcessMouseClick()
{
	return m_bParentProcMouseClick;
}

// 函数 CMyCheckButton::SetIconTextInterval
// 作用：设置SetIconTextInterval。
// 参数：iLeftIndent：整数；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMyCheckButton::SetIconTextInterval(int iLeftIndent,BOOL bRedraw /*= FALSE*/)
{
	m_iLeftIndent = iLeftIndent;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMyCheckButton::GetIconTextInterval
// 作用：读取GetIconTextInterval。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMyCheckButton::GetIconTextInterval()
{
	return m_iLeftIndent;
}

// 函数 CMyCheckButton::DrawItem
// 作用：绘制DrawItem。
// 参数：lpDrawItemStruct。
// 返回：没有返回值。
// 过程：函数里会调用 Attach、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
void CMyCheckButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if(m_sonPicNums < 1)
	{
		return;
	}

	CRect rect = lpDrawItemStruct->rcItem;
	CDC cDC;
	cDC.Attach(lpDrawItemStruct->hDC);

	CDC memDC;
	memDC.CreateCompatibleDC(&cDC);
	CBitmap bitMapTemp;
	bitMapTemp.CreateCompatibleBitmap(&cDC,rect.Width(),rect.Height());
	CBitmap* pOldTempBitmap = memDC.SelectObject(&bitMapTemp);

	memDC.BitBlt(0,0,rect.Width(),rect.Height(),&cDC,0,0,SRCCOPY);

	if(m_bHasBkPic)
	{
		CDC dcMem;
		dcMem.CreateCompatibleDC(&cDC);
		CBitmap bitMap;

		if(1 == m_sonPicNums)
		{
			if(!m_isBtChecked)
			{
				bitMap.LoadBitmap(m_idUnChecked);
			}
			else
			{
				bitMap.LoadBitmap(m_idChecked);
			}
		}
		else
		{
			bitMap.LoadBitmap(m_idChecked);
		}
		
		BITMAP bit;
		bitMap.GetBitmap(&bit);
		CBitmap* pOldBitmap = dcMem.SelectObject(&bitMap);

		int startX = 0;
		int bkW = 0;
		if(1 == m_sonPicNums)
		{
			bkW = bit.bmWidth;
		}
		else 
		{
			if(!m_isBtChecked)
			{
				startX = 0;
			}
			else
			{
				startX = bit.bmWidth / m_sonPicNums;
			}
			bkW = bit.bmWidth / m_sonPicNums;
		}

		memDC.SetStretchBltMode(HALFTONE);
		memDC.StretchBlt(0,0,(double(m_iconW * GeneScreenXWidth)) / m_uiGeneDesWidth,rect.Height(),&dcMem,startX,0,bkW,bit.bmHeight,SRCCOPY);
		dcMem.SelectObject(pOldBitmap);
		bitMap.DeleteObject();
		dcMem.DeleteDC();
	}
	else if(m_bHasPngBkPic)
	{
		Graphics graphics(memDC.m_hDC);
		Image image(m_picPath.c_str());

		if(m_bNeedRedrawBk)
		{
			memDC.FillSolidRect(rect,m_pngBkClr);
		}

		ImageAttributes ImgAtt;
		ImgAtt.SetWrapMode(WrapModeTileFlipXY);
		if(0 != m_sonPicNums)
		{
			if(0 == m_iconW)
			{
				if(!m_isBtChecked)
				{
					graphics.DrawImage(&image,Rect(0,0,rect.Width(),rect.Height()),0,0,image.GetWidth() / m_sonPicNums,image.GetHeight(),UnitPixel,&ImgAtt);
				}
				else           
				{
					graphics.DrawImage(&image,Rect(0,0,rect.Width(),rect.Height()),image.GetWidth() / m_sonPicNums * (m_selStateSerail - 1),0,image.GetWidth() / m_sonPicNums,image.GetHeight(),UnitPixel,&ImgAtt);
				}
			}
			else
			{
				Rect rcImg;
				rcImg.X = 0;
				int iTemp = image.GetHeight();
				iTemp = (rect.Height() - iTemp) / 2;
				if(iTemp < 0)
				{
					iTemp = 0;
				}
				rcImg.Y = iTemp;
				rcImg.Width = m_iconW;
				rcImg.Height = image.GetHeight();
				if(rcImg.Height > rect.Height())
				{
					rcImg.Height = rect.Height();
				}

				int iStartX = 0;
				if(2 == m_sonPicNums)
				{
					if(m_isBtChecked)
					{
						iStartX = image.GetWidth() / m_sonPicNums;
					}
				}
				else if(3 == m_sonPicNums)
				{
					if(IsWindowEnabled())
					{
						if(m_isBtChecked)
						{
							iStartX = image.GetWidth() / m_sonPicNums;
						}
					}
					else
					{
						iStartX = image.GetWidth() / m_sonPicNums * 2;
					}
				}
				else if(4 == m_sonPicNums)
				{
					if(IsWindowEnabled())
					{
						if(m_isBtChecked)
						{
							iStartX = image.GetWidth() / m_sonPicNums;
						}
					}
					else
					{
						if(m_isBtChecked)
						{
							iStartX = image.GetWidth() / m_sonPicNums * 3;
						}
						else
						{
							iStartX = image.GetWidth() / m_sonPicNums * 2;
						}
					}
				}

				graphics.DrawImage(&image,rcImg,iStartX,0,image.GetWidth() / m_sonPicNums,image.GetHeight(),UnitPixel,&ImgAtt);
			}
		}

		graphics.ReleaseHDC(memDC.m_hDC);
	} 
	else
	{
		if(m_bTickStyle)
		{
			CRect tempRc(rect.left + (rect.Width() - 14) / 2,rect.top + (rect.Height() - 14) / 2,rect.left + (rect.Width() + 14) / 2,rect.top + (rect.Height() + 14) / 2);
			CBrush brush;
			brush.CreateSolidBrush(RGB(0,0,0));
			memDC.FrameRect(tempRc,&brush);
			tempRc.DeflateRect(1,1,1,1);
			if(m_isBtChecked)
			{
				memDC.FillSolidRect(tempRc,RGB(1,93,197));
			}
			else
			{
				memDC.FillSolidRect(tempRc,RGB(252,255,254));
			}
			brush.DeleteObject();
		}
		else if(m_bRoundStyle)
		{
			memDC.FillSolidRect(rect,m_roundStyleBkClr);
			Color bkClr;
			if(m_isBtChecked)
			{
				bkClr.SetFromCOLORREF(m_bkClrChked);
				DrawRound(&memDC,rect,TRUE,bkClr,1,TRUE,bkClr);
			}
			else
			{
				bkClr.SetFromCOLORREF(m_bkClrUnchked);
				DrawRound(&memDC,rect,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,bkClr);
			}
		}
		else
		{
			CPen pen;
			pen.CreatePen(PS_SOLID,1,m_clrFrame);
			CPen* pOldPen = memDC.SelectObject(&pen);
			
			if(m_isBtChecked)  
			{
				CBrush activeBrush;
				activeBrush.CreateSolidBrush(m_bkClrChked);

				memDC.FillRect(&rect,&activeBrush);
				activeBrush.DeleteObject();
			}
			else
			{
				CBrush normalBrush;
				normalBrush.CreateSolidBrush(m_bkClrUnchked);
				memDC.FillRect(&rect,&normalBrush);
				normalBrush.DeleteObject();
			}

			memDC.SelectObject(&pOldPen);
			pen.DeleteObject();
		}
	}

	CString strText;
	GetWindowText(strText);
	if(0 != strText.GetLength())
	{	
		CRect rcText = rect;
		rcText.left = m_iconW + m_iLeftIndent;
		rcText.right -= m_rightEnd;

		CFont *pOldFont = NULL;
		if(m_isBtChecked)
		{
			pOldFont = memDC.SelectObject(&m_fontSet);
			memDC.SetTextColor(m_txClrChecked);
		}
		else
		{
			pOldFont = memDC.SelectObject(&m_fontSet);
			memDC.SetTextColor(m_txClrUnchecked);
		}

		memDC.SetBkMode(TRANSPARENT);
		memDC.DrawText(strText,rcText,m_dwWordStyle);
		memDC.SelectObject(pOldFont);
	}

	cDC.BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);
	memDC.SelectObject(pOldTempBitmap);
	memDC.DeleteDC();

	cDC.Detach();
	return;
}

// 函数 CMyCheckButton::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 CButton::OnLButtonDown。
void CMyCheckButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bShieldClickMsg)
	{
		return;
	}
	CButton::OnLButtonDown(nFlags, point);
}


// 函数 CMyCheckButton::OnLButtonUp
// 作用：松开鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyCheckButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bShieldClickMsg)
	{
		return;
	}

	if(!m_bParentProcMouseClick)
	{
		m_isBtChecked = !m_isBtChecked;
		Invalidate();
	}
	
	CButton::OnLButtonUp(nFlags, point);
}

// 函数 CMyCheckButton::OnLButtonDblClk
// 作用：双击鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate。
void CMyCheckButton::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(m_bShieldClickMsg)
	{
		return;
	}

	if(!m_bParentProcMouseClick)
	{
		m_isBtChecked = !m_isBtChecked;
		Invalidate();
	}

	__super::OnLButtonDblClk(nFlags, point);
}

// 函数 CMyCheckButton::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 __super::OnSize。
void CMyCheckButton::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
}

// 函数 CMyCheckButton::OnCtlColor
// 作用：给子控件设置文字色和背景色。
// 参数：pDC：指针，指向调用方传入的对象；pWnd：指针，指向调用方传入的对象；nCtlColor：整数。
// 返回：返回 HBRUSH。
// 过程：函数里会调用 __super::OnCtlColor。
HBRUSH CMyCheckButton::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = __super::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

// 函数 CMyCheckButton::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyCheckButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
