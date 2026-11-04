// 【交接】 GeneralPcr\MyNewCb.cpp
// 作用：MyNewCb 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyNewCb、BEGIN_MESSAGE_MAP、ON_MESSAGE、ON_WM_KILLFOCUS、ON_WM_SIZE、END_MESSAGE_MAP、OnPaint。
#include "StdAfx.h"
#include "MyNewCb.h"

IMPLEMENT_DYNAMIC(CMyNewCb,CMyNewEdit)

// 函数 CMyNewCb::CMyNewCb
// 作用：执行CMyNewCb。
// 参数：CMyNewEdit(pParent。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyNewCb::CMyNewCb(CWnd* pParent /*= NULL*/) : CMyNewEdit(pParent)
{
	m_eCbSelWndState = ECSWS_HIDE;
	m_iSelWndH = 100;
	m_bFstDown = TRUE;
}

// 函数 CMyNewCb::~CMyNewCb
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyNewCb::~CMyNewCb(void)
{
	
}

BEGIN_MESSAGE_MAP(CMyNewCb, CMyNewEdit)
	 ON_MESSAGE(WM_ROWSELECTCHANGE,&CMyNewCb::OnMsgRowSelectedChange) 
	 ON_MESSAGE(WM_HIDESONCTRL,&CMyNewCb::OnMsgHideSonCtrl) 
	 ON_WM_KILLFOCUS()
	 ON_WM_SIZE()
END_MESSAGE_MAP()

// 函数 CMyNewCb::OnPaint
// 作用：窗口需要重画时绘制内容。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 dc、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
void CMyNewCb::OnPaint()
{
	CPaintDC dc(this); 

	CRect rcClient;
	GetClientRect(&rcClient);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());

	CBitmap* pOldBitmap = memDC.SelectObject(&bitMap);

	Color clrFrame,clrMainWndBk;
	COLORREF clrTx,clrTxSel,clrBkSel;
	switch(m_eCtrlState)
	{
	case ECS_NORMAL: clrFrame = m_clrFrameNormal;
		clrTx = m_clrTxNormal;
		clrTxSel = m_clrTxSelNormal;
		clrBkSel = m_clrBkSelNormal;
		clrMainWndBk = m_clrMainWndNormal;	break;
	case ECS_HOVER: clrFrame = m_clrFrameHover;
		clrTx = m_clrTxHover;
		clrTxSel = m_clrTxSelHover;
		clrBkSel = m_clrBkSelHover;
		clrMainWndBk = m_clrMainWndHover;	break;
	case ECS_SELECTED: clrFrame = m_clrFrameSelected;
		clrTx = m_clrTxSelected;
		clrTxSel = m_clrTxSelSelected;
		clrBkSel = m_clrBkSelSelected;
		clrMainWndBk = m_clrMainWndSelected;	break;
	case ECS_DISABLE: clrFrame = m_clrFrameDisabled;
		clrTx = m_clrTxDisabled;
		clrTxSel = m_clrTxSelDisabled;
		clrBkSel = m_clrBkSelDisabled;
		clrMainWndBk = m_clrMainWndDisabled;	break;
	}

	if(EFS_RECTANGLE == m_eFrameStyle)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID,m_pxFrameW,RGB(clrFrame.GetR(),clrFrame.GetG(),clrFrame.GetB()));
		CPen* pOldPen = memDC.SelectObject(&pen);
		memDC.Rectangle(&rcClient);
		memDC.SelectObject(&pOldPen);
		pen.DeleteObject();

		CRect rect = rcClient;
		rect.DeflateRect(m_pxFrameW,m_pxFrameW,m_pxFrameW,m_pxFrameW);
		memDC.FillSolidRect(&rect,RGB(clrMainWndBk.GetR(),clrMainWndBk.GetG(),clrMainWndBk.GetB()));
		memDC.SetBkMode(TRANSPARENT);
	}
	else
	{
		memDC.FillSolidRect(rcClient.left,rcClient.top,rcClient.Width(),rcClient.Height(),RGB(m_clrMainWndNormal.GetR(),m_clrMainWndNormal.GetG(),m_clrMainWndNormal.GetB()));
		DrawRoundRectangleNew(&memDC,rcClient.left,rcClient.top,rcClient.Width() - 1,rcClient.Height() - 1,m_iFrameRoundAngle,m_iFrameRoundAngle,m_iFrameRoundAngle,m_iFrameRoundAngle,TRUE,clrFrame,1,TRUE,clrMainWndBk,1);
	}

	//绘制左侧图标
	if(m_bShowLeftImg && !m_strLeftImgPath.IsEmpty() && m_iLeftImgSonPicNum > 0)
	{
		CRect rcImg(m_pxFrameW,m_pxFrameW,m_iLeftIndent + m_pxFrameW,m_rcCtrl.bottom - m_pxFrameW);

		//绘制背景图片
		Graphics graphics(memDC.m_hDC);
		ImageAttributes ImgAtt;
		ImgAtt.SetWrapMode(WrapModeTileFlipXY);
		graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
		graphics.SetSmoothingMode(SmoothingModeAntiAlias);

		Image img(m_strLeftImgPath);
		int iTempInt1 = 0;
		int iIconW = img.GetWidth() / m_iLeftImgSonPicNum;

		Rect rcPic;
		if(rcImg.Width() <= iIconW)
		{
			rcPic.X = 0;
			rcPic.Width = rcImg.Width();
		}
		else
		{
			rcPic.X = rcImg.left + (rcImg.Width() - iIconW) / 2;
			rcPic.Width = iIconW;
		}
		if(rcImg.Height() <= img.GetHeight())
		{
			rcPic.Y = 0;
			rcPic.Height = rcImg.Height();
		}
		else
		{
			rcPic.Y = rcImg.top + (rcImg.Height() - img.GetHeight()) / 2;
			rcPic.Height = img.GetHeight();
		}

		int iStartX = 0;
		if(m_iLeftImgSonPicNum > 1)
		{
			if(ECS_HOVER == m_eCtrlState || ECS_SELECTED == m_eCtrlState)
			{
				iStartX = iIconW;
			}
		}

		graphics.DrawImage(&img,rcPic,iStartX,0,iIconW,img.GetHeight(),UnitPixel,&ImgAtt);

		graphics.ReleaseHDC(memDC.m_hDC);
	}

	if(_T("") != m_strText)
	{
		CheckLnkCharWidth();

		memDC.SetTextColor(clrTx);
		if(-1 == m_iCharStartShowIndex || -1 == m_iCharEndShowIndex)
		{
			m_iCharStartShowIndex = 0;
			m_iCharEndShowIndex = m_strText.GetLength() - 1;
			m_iCharShowLI = 0;
			m_iCharShowRI = 0;
		}
		m_iCdcW = GetWidth(m_iCharStartShowIndex,m_iCharEndShowIndex);

		if(m_iCdcW > 0)
		{
			CDC memDCText;
			memDCText.CreateCompatibleDC(&dc);
			CBitmap bitMapText;
			bitMapText.CreateCompatibleBitmap(&dc,m_iCdcW,rcClient.Height() - m_pxFrameW * 2);
			CBitmap* pOldBitmapText = memDCText.SelectObject(&bitMapText);

			CRect rcText(0,0,m_iCdcW,rcClient.Height() - m_pxFrameW * 2);
			memDCText.FillSolidRect(&rcText,RGB(clrMainWndBk.GetR(),clrMainWndBk.GetG(),clrMainWndBk.GetB()));
			memDCText.SetBkMode(TRANSPARENT);
			memDCText.SetTextColor(clrTx);
			CFont* pOldFont = memDCText.SelectObject(&m_fontSet);

			CSize size = memDCText.GetTextExtent(_T("A"));

			CString strToDraw = m_strText.Mid(m_iCharStartShowIndex,m_iCharEndShowIndex - m_iCharStartShowIndex + 1);
			memDCText.DrawText(strToDraw,strToDraw.GetLength(),&rcText,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			memDCText.SelectObject(pOldFont);

			if(m_iSelCharNum > 0)
			{
				int iXBkStart = 0,iXBkEnd = m_iCdcW;
				int iSelStart = m_iSelStart,iSelEnd = m_iSelEnd,iTemp = m_iSelStart;
				int iSelStartDraw = m_iCharStartShowIndex,iSelEndDraw = m_iCharEndShowIndex;
				if(iSelStart > iSelEnd)
				{
					iSelStart = iSelEnd;
					iSelEnd = iTemp;
				}
				if(iSelStart >= m_iCharStartShowIndex)
				{
					iXBkStart = GetWidth(m_iCharStartShowIndex,iSelStart);
					iSelStartDraw = iSelStart + 1;
				}
				if(iSelEnd <= m_iCharEndShowIndex)
				{
					iXBkEnd = GetWidth(m_iCharStartShowIndex,iSelEnd);
					iSelEndDraw = iSelEnd;
				}

				if(iXBkEnd > iXBkStart)
				{
					m_iSelDrawCDcW = GetWidth(iSelStartDraw,iSelEndDraw);

					CDC memDCSel;
					memDCSel.CreateCompatibleDC(&dc);

					CRect rcSelDraw(0,0,m_iSelDrawCDcW,size.cy);

					CBitmap bitMapSel;
					bitMapSel.CreateCompatibleBitmap(&dc,rcSelDraw.Width(),rcSelDraw.Height());
					CBitmap* pOldBitmapSelDraw = memDCSel.SelectObject(&bitMapSel);

					memDCSel.FillSolidRect(&rcSelDraw,clrBkSel);

					CFont* pOldFontSel = memDCSel.SelectObject(&m_fontSet);
					memDCSel.SetTextColor(clrTxSel);
					memDCSel.SetBkMode(TRANSPARENT);

					CString strSelDraw(_T(""));
					strSelDraw = m_strText.Mid(iSelStartDraw,iSelEndDraw - iSelStartDraw + 1);
					memDCSel.DrawText(strSelDraw,strSelDraw.GetLength(),&rcSelDraw,DT_LEFT | DT_VCENTER | DT_SINGLELINE);
					memDCSel.SelectObject(pOldFontSel);

					memDCText.BitBlt(iXBkStart,(rcText.Height() - size.cy) / 2,rcSelDraw.Width(),rcSelDraw.Height(),&memDCSel,0,0,SRCCOPY);

					memDCSel.SelectObject(pOldBitmapSelDraw);
					bitMapSel.DeleteObject();
					memDCSel.DeleteDC();
				}

			}

			memDC.BitBlt(m_pxFrameW + m_iLeftIndent,m_pxFrameW,m_iCharShowW,rcClient.Height() - m_pxFrameW * 2,&memDCText,m_iCharShowLI,0,SRCCOPY); 

			memDCText.SelectObject(pOldBitmapText);
			bitMapText.DeleteObject();
			memDCText.DeleteDC();
		}
	}

	//绘制箭头
	Graphics graphics(memDC.m_hDC);
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	m_arrowInfo.CalcPtData(m_rcRightIndent);

	if(EAS_FILL == m_arrowInfo.m_eArrowStyle)
	{
		SolidBrush brush(m_arrowInfo.m_clrArrow);
		graphics.FillPolygon(&brush,m_arrowInfo.m_aryPtTriangle,3,FillModeAlternate);
	}
	else
	{
		if(ECSWS_SHOW == m_eCbSelWndState)
		{
			Pen pen(m_arrowInfo.m_clrLineDropDown,m_arrowInfo.m_iLineW);
			graphics.DrawLines(&pen,m_arrowInfo.m_aryPtTriangleDropDown,3);
		}
		else
		{
			Pen pen(m_arrowInfo.m_clrLineNormal,m_arrowInfo.m_iLineW);
			graphics.DrawLines(&pen,m_arrowInfo.m_aryPtTriangle,3);
		}
	}

	graphics.ReleaseHDC(memDC.m_hDC);

	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDC,0,0,SRCCOPY);   

	memDC.SelectObject(pOldBitmap);
	bitMap.DeleteObject();
	memDC.DeleteDC();

	return;
}

// 函数 CMyNewCb::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Create。
int CMyNewCb::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CMyNewEdit::OnCreate(lpCreateStruct);
	m_selWnd.m_bTellParentRowSelChange = TRUE;
	m_selWnd.m_pParent = this;
	m_selWnd.Create(IDD_POPUPDLG,this);	
	return 1;
}

// 函数 CMyNewCb::PreTranslateMessage
// 作用：消息送达窗口前先拦截键盘或鼠标。
// 参数：pMsg：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 __super::PreTranslateMessage。
BOOL CMyNewCb::PreTranslateMessage(MSG* pMsg)
{
	if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:	return TRUE;
		case VK_ESCAPE:	return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

// 函数 CMyNewCb::LBtDownSpecialProc
// 作用：执行LBtDownSpecialProc。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 ShowWindow、SetSelectedRow、ClientToScreen、MoveWindow、Width、CalcSelWndHeight。
int CMyNewCb::LBtDownSpecialProc()
{
	if(ECSWS_SHOW == m_eCbSelWndState)
	{
		m_selWnd.ShowWindow(SW_HIDE);
		m_eCbSelWndState = ECSWS_HIDE;
	}
	else
	{ 
		CRect rcTemp = m_rcCtrl;
		if(m_bFstDown)
		{
			m_selWnd.SetSelectedRow(m_strText);
			m_bFstDown = FALSE;
		}
		ClientToScreen(&rcTemp);
		m_selWnd.MoveWindow(rcTemp.left,rcTemp.bottom,m_rcCtrl.Width(),CalcSelWndHeight());
		m_selWnd.ShowWindow(SW_SHOW);
		m_eCbSelWndState = ECSWS_SHOW;
	}
	
	return 0;
}

// 函数 CMyNewCb::GetString
// 作用：读取GetString。
// 参数：iIndex：整数；strText：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetRowString。
int CMyNewCb::GetString(int iIndex,CString& strText)
{
	if(iIndex < 0)
	{
		return -1;
	}
	if(iIndex >= m_selWnd.m_rowNum)
	{
		return -2;
	}
	return m_selWnd.GetRowString(iIndex,strText);
}

// 函数 CMyNewCb::SetItemText
// 作用：设置SetItemText。
// 参数：iIndex：整数；strText：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMyNewCb::SetItemText(int iIndex,CString strText)
{
	return m_selWnd.SetItemText(iIndex,strText);
}

// 函数 CMyNewCb::InsertString
// 作用：创建或加入InsertString。
// 参数：iIndex：整数；strText：字符串；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 InsertRow。
int CMyNewCb::InsertString(int iIndex,CString strText,BOOL bRedraw /*= FALSE*/)
{
	return m_selWnd.InsertRow(iIndex,strText,bRedraw);
}

// 函数 CMyNewCb::InsertString
// 作用：创建或加入InsertString。
// 参数：strText：字符串；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 InsertRow。
int CMyNewCb::InsertString(CString strText,BOOL bRedraw /*= FALSE*/)
{
	return m_selWnd.InsertRow(strText,bRedraw);
}

// 函数 CMyNewCb::DeleteString
// 作用：更新或清除DeleteString。
// 参数：iIndex：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 DeleteRow。
int CMyNewCb::DeleteString(int iIndex,BOOL bRedraw /*= FALSE*/)
{
	return m_selWnd.DeleteRow(iIndex,bRedraw);
}

// 函数 CMyNewCb::Clear
// 作用：更新或清除Clear。
// 参数：bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 DeleteAll。
int CMyNewCb::Clear(BOOL bRedraw /*= FALSE*/)
{
	DeleteAll(bRedraw);
	m_bFstDown = TRUE;
	return m_selWnd.DeleteAll();
}

// 函数 CMyNewCb::OnMsgRowSelectedChange
// 作用：响应 Windows 或自定义消息 OnMsgRowSelectedChange。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 strText、_T、GetRowString、SetText、LBtDownSpecialProc。
LRESULT CMyNewCb::OnMsgRowSelectedChange(WPARAM wParam,LPARAM lParam)
{
	CString strText(_T(""));
	if(0 != m_selWnd.GetRowString(wParam,strText))
	{
		return 1;
	}

	SetText(strText);
	LBtDownSpecialProc();

	return 0;
}

// 函数 CMyNewCb::OnMsgHideSonCtrl
// 作用：响应 Windows 或自定义消息 OnMsgHideSonCtrl。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 ShowWindow、IsWindowVisible、GetParent、GetSafeHwnd、PostMessage。
LRESULT CMyNewCb::OnMsgHideSonCtrl(WPARAM wParam,LPARAM lParam)
{
	m_selWnd.ShowWindow(SW_HIDE);
	m_eCbSelWndState = ECSWS_HIDE;

	if(!wParam)	
	{
		m_ePreCtrlState = m_eCtrlState;
		if(m_bEidtable)
		{
			m_eCtrlState = ECS_NORMAL;

			if(m_bFuncEdit && IsWindowVisible())
			{
				CWnd* pParent = GetParent();
				if(NULL != pParent->GetSafeHwnd())
				{
					pParent->PostMessage(WM_FUNCEDITKILLFOCUS,m_iCtrlTag,0);
				}
				ShowWindow(SW_HIDE);
			}
		}
	}

	return 0;
}

// 函数 CMyNewCb::OnKillFocus
// 作用：响应 Windows 或自定义消息 OnKillFocus。
// 参数：pNewWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CMyNewEdit::OnKillFocus。
void CMyNewCb::OnKillFocus(CWnd* pNewWnd)
{
	CWnd* pSelWnd = &m_selWnd;
	
	CMyNewEdit::OnKillFocus(pNewWnd);
	
	return;
}

// 函数 CMyNewCb::CalcSelWndHeight
// 作用：计算CalcSelWndHeight。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetClientRect、ClientToScreen、Height。
int CMyNewCb::CalcSelWndHeight()
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);

	if(m_selWnd.m_totalRowH < GeneCRDlg.Height() - rect.bottom)
	{
		m_iSelWndH = m_selWnd.m_totalRowH + m_selWnd.m_pxFrameW * 2;
	}
	else
	{
		m_iSelWndH = GeneCRDlg.Height() - rect.bottom - 5;
	}
	return m_iSelWndH;
}

// 函数 CMyNewCb::SetText
// 作用：设置SetText。
// 参数：strText：字符串；bRedraw：是或否；bForbidTellParent：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Clear、GetLength、GetSafeHwnd、GetDC、SelectObject、GetTextExtent。
int CMyNewCb::SetText(CString strText,BOOL bRedraw /*= TRUE*/,BOOL bForbidTellParent /*= FALSE*/)
{
	BOOL bDifferentText = (m_strText != strText);

	m_strText = strText;
	m_lnkCharW.Clear();
	int iCharNum = m_strText.GetLength();
	if(iCharNum > 0 && NULL != GetSafeHwnd())
	{
		CDC* pDc = GetDC();
		if(NULL != pDc)
		{
			CFont* pOldFont = pDc->SelectObject(&m_fontSet);
			CSize size;
			for(int i = 0;i < iCharNum;++i)
			{
				size = pDc->GetTextExtent(m_strText.Mid(i,1));
				int iCharW = size.cx;
				m_lnkCharW.AddTail(iCharW);
			}

			pDc->SelectObject(pOldFont);
			ReleaseDC(pDc);	
		}
	}

	if(0 == iCharNum)	
	{
		m_caretInfo.m_iCurCharIndex = -1;
		m_caretInfo.m_pxXStart = m_pxFrameW + m_iLeftIndent;
		m_iCharStartShowIndex = -1;
		m_iCharEndShowIndex = -1;
		m_iCharShowLI = 0;
		m_iCharShowRI = 0;
	}
	else if(m_lnkCharW.GetSize() == iCharNum)
	{
		m_iCharEndShowIndex = iCharNum - 1;
		m_iCharShowRI = 0;
		CalcCharEndStartShowIndex();
	}
	else
	{
		m_caretInfo.m_iCurCharIndex = -1;
		m_caretInfo.m_pxXStart = m_pxFrameW + m_iLeftIndent;
		m_iCharStartShowIndex = -1;
		m_iCharEndShowIndex = -1;
		m_iCharShowLI = 0;
		m_iCharShowRI = 0;

		return -1;
	}

	m_caretInfo.m_iCurCharIndex = iCharNum - 1;
	if(-1 == m_caretInfo.m_iCurCharIndex)
	{
		m_caretInfo.m_pxXStart = m_pxFrameW + m_iLeftIndent;
	}
	else
	{
		if(-1 != m_iCharStartShowIndex && -1 != m_iCharEndShowIndex)
		{
			m_caretInfo.m_pxXStart = m_pxFrameW + m_iLeftIndent + *m_lnkCharW[m_iCharStartShowIndex] - m_iCharShowLI + GetWidth(m_iCharStartShowIndex + 1,m_caretInfo.m_iCurCharIndex);
		}
		else
		{
			m_caretInfo.m_pxXStart = m_pxFrameW + m_iLeftIndent;
		}
	}

	if(EWS_READONLY != m_eWorkState)
	{
		CPoint pt;
		pt.x = m_caretInfo.m_pxXStart;
		pt.y = m_caretInfo.m_pxYStart;

		CWnd* pFocusWnd = GetFocus();
		if(NULL != pFocusWnd && m_hWnd == pFocusWnd->m_hWnd)
		{
			SetCaretPos(pt);
		}
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	if(!bForbidTellParent && bDifferentText)
	{
		TellParentSetNewTextProcess();
	}

	return 0;
}

// 函数 CMyNewCb::SetCurSel
// 作用：设置SetCurSel。
// 参数：iIndex：整数；bRedraw：是或否；bForbidTellParent：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、strTemp、_T、SetRowSingleSelected、SetText。
int CMyNewCb::SetCurSel(int iIndex,BOOL bRedraw /*= TRUE*/,BOOL bForbidTellParent /*= FALSE*/)
{
	if(iIndex < -1)
	{
		return -1;
	}

	if(iIndex >= m_selWnd.m_lnkItemForSelInfo.GetSize())
	{
		return -2;
	}

	CString strTemp(_T(""));
	if(-1 != iIndex)
	{
		strTemp = m_selWnd.m_lnkItemForSelInfo[iIndex]->m_strText;
		m_selWnd.SetRowSingleSelected(iIndex);
	}

	if(0 == SetText(strTemp,bRedraw,bForbidTellParent))
	{
		return 0;
	}
	else
	{
		return -3;
	}
}

// 函数 CMyNewCb::GetCurSel
// 作用：读取GetCurSel。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetFirstSelectedRow。
int CMyNewCb::GetCurSel()
{
	return m_selWnd.GetFirstSelectedRow(m_strText);
}

// 函数 CMyNewCb::GetItemCount
// 作用：读取GetItemCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMyNewCb::GetItemCount()
{
	return m_selWnd.GetItemCount();
}

// 函数 CMyNewCb::SetDropDown
// 作用：设置SetDropDown。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetSelectedRow、ClientToScreen、MoveWindow、Width、CalcSelWndHeight、ShowWindow。
int CMyNewCb::SetDropDown()
{
	if(ECSWS_SHOW == m_eCbSelWndState)
	{
		return 1;
	}
	else
	{ 
		CRect rcTemp = m_rcCtrl;
		if(m_bFstDown)
		{
			m_selWnd.SetSelectedRow(m_strText);
			m_bFstDown = FALSE;
		}
		ClientToScreen(&rcTemp);
		m_selWnd.MoveWindow(rcTemp.left,rcTemp.bottom,m_rcCtrl.Width(),CalcSelWndHeight());
		m_selWnd.ShowWindow(SW_SHOW);
		m_eCbSelWndState = ECSWS_SHOW;
	}

	return 0;
}

// 函数 CMyNewCb::SetDropUp
// 作用：设置SetDropUp。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 ShowWindow。
int CMyNewCb::SetDropUp()
{
	if(ECSWS_SHOW == m_eCbSelWndState)
	{
		m_selWnd.ShowWindow(SW_HIDE);
		m_eCbSelWndState = ECSWS_HIDE;
	}
	else
	{ 
		return 1;
	}

	return 0;
}

// 函数 CMyNewCb::RefreshText
// 作用：更新或清除RefreshText。
// 参数：iIndex：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetCurSel。
int CMyNewCb::RefreshText(int iIndex,BOOL bRedraw /*= FALSE*/)
{
	if(EWS_READONLY != m_eWorkState)
	{
		return 1;
	}

	SetCurSel(iIndex,bRedraw,TRUE);

	return 0;
}
