// 【交接】 GeneralPcr\MySamPlateDlg.cpp
// 作用：MySamPlateDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMySamPalteDlg、RGB、Color、SetLimitMaxParam、InitFontHeader、InitFontTitle、InitFontAbbr。
// PcrSegmentExpWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "MySamPlateDlg.h"
#include "LanguageInfo.h"
#include "Resource.h"

// CMySamPalteDlg

map<eSampleType,CString> CMySamPalteDlg::m_mapSamTypeToTx;
map<CString,eSampleType> CMySamPalteDlg::m_mapTxToSamType;
map<eSampleType,CHoleColorInfo> CMySamPalteDlg::m_mapSamTypeToHoleClrInfo;
map<eSampleType,CString> CMySamPalteDlg::m_mapSamTypeToAbbr;

IMPLEMENT_DYNAMIC(CMySamPalteDlg, CDialogEx)
// 函数 CMySamPalteDlg::CMySamPalteDlg
// 作用：执行CMySamPalteDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 RGB、Color、SetLimitMaxParam、InitFontHeader、InitFontTitle、InitFontAbbr。
CMySamPalteDlg::CMySamPalteDlg()
{
	m_rowNum = 0;
	m_colNum = 0;
	m_colIdStartShow = -1;
	m_colIdEndShow = -1;
	m_rowIdStartShow = -1;
	m_rowIdEndShow = -1;
	m_pxFrame = 1;
	m_pxRowColLine = 1;
	m_ssColLeftIndent = 0;
	m_esColRightIndent = 0;
	m_ssRowTopIndent = 0;
	m_esRowBottomIndent = 0;

	m_pxColW = 110;	
	m_pxRowH = 80;	
	m_pxRowHeaderW = 50;
	m_pxColHeaderH = 46;
	m_bUseFixedHW = TRUE;
	m_clrBk = RGB(0XFF,0XFF,0XFF);
	m_clrHeaderBk = Color(0XF1,0XF4,0XF9);
	m_clrHeaderSelectedBk = Color(0XBB,0XCA,0XE3);
	
	m_clrBodyBk = RGB(0XFF,0XFF,0XFF);
	m_clrFrame = RGB(0XD8,0XD8,0XD8);
	m_clrRowColLine = RGB(197,197,197);
	m_clrHeaderText = RGB(0X39,0X45,0X65);
	m_bGradientHeader = FALSE;
	m_clrGraHeadStart = Color(0XAA,0XAB,0XAC);
	m_clrGraHeadEnd = Color(0XBA,0XBB,0XBC);
	m_bEditable = TRUE;

	m_totalColW = 60;
	m_totalRowH = 30;
	m_cdcW = 60;
	m_cdcH = 160;

	m_horiScroll.m_scrollH = 30;
	m_vertScroll.m_scrollW = 30;

	m_horiScroll.m_eScrollType = EST_HORI;
	m_vertScroll.m_eScrollType = EST_VERT;

	m_eScrollHVCM = ESHVCM_HORI;
	m_bShowFrameLine = FALSE;
	m_bShowRowColLine = FALSE;
	m_lnkHistoryDotPosInfo.SetLimitMaxParam(TRUE,100);
	
	m_rowIdSeparatorStart = -1;
	m_rowIdSeparatorEnd = -1;
	m_esSeparatorBottomIndent = 0;
	m_bSingleSelect = FALSE;

	m_clrHeadBodySepa = RGB(197,197,197);
	m_bTellParentSiteSelChange = FALSE;

	InitFontHeader(16);
	InitFontTitle(16);
	InitFontAbbr(12);

	m_pTubeInfo = NULL;
	m_pPlateInfo = NULL;
	m_strTotalTitle = _T("All");
	m_iTotalSiteNum = 0;
	m_bAllSelected = FALSE;
	m_bDraggableStart = FALSE;
	m_bDragMove = FALSE;
	m_iRectW = 50;
	m_iRectH = 40;
	m_bShowSplitLine = FALSE;

	m_clrFourAngleBk = CLR_SOFT_LIGHT;
	m_bRoundRectStyle = TRUE;
	m_iRoundAngleSize = 8;
	m_clrIndepent = Color(0XF2,0XF5,0XFA);

	m_bShowTopTx = FALSE;
	m_bShowBottomTx = FALSE;

	m_iLeftIndent = 20;
	m_iRightIndent = 24;
	m_iTopIndent = 15;
	m_iBottomIndent = 17;
	m_iHoriInterval = 8;
	m_iVertInterval = 18;

	m_bShieldDeleteKey = FALSE;
	m_bParentProcessDeleteKey = FALSE;
	m_bLeftBtDown = FALSE;

#ifdef PS384INSTRUMENT
	m_iRoundAngleLT = 4;
	m_iRoundAngleRT = 4;
	m_iRoundAngleRB = 4;
	m_iRoundAngleLB = 4;
#else
	m_iRoundAngleLT = 8;
	m_iRoundAngleRT = 8;
	m_iRoundAngleRB = 8;
	m_iRoundAngleLB = 8;
#endif

	m_bShowSiteId = TRUE;
	m_bShowLastChanBlock = TRUE;
}

// 函数 CMySamPalteDlg::~CMySamPalteDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 MyMulitDeletePtr、DeleteObject。
CMySamPalteDlg::~CMySamPalteDlg()
{
	MyMulitDeletePtr(&m_pTubeInfo);
	MyMulitDeletePtr(&m_pPlateInfo);

	m_fontSetHeader.DeleteObject(); 
	m_fontSetTitle.DeleteObject();
	m_fontAbbr.DeleteObject();
}

BEGIN_MESSAGE_MAP(CMySamPalteDlg, CDialogEx)
   ON_WM_ERASEBKGND()
   ON_WM_LBUTTONDBLCLK()
   ON_WM_RBUTTONDOWN()
   ON_WM_LBUTTONDOWN()
   ON_WM_LBUTTONUP()
   ON_WM_MOUSEMOVE()
   ON_WM_MOUSEWHEEL()
   ON_WM_PAINT()
   ON_WM_CREATE()
   ON_WM_SIZE()
   ON_MESSAGE(WM_EDITENTERPUSHED,&CMySamPalteDlg::OnMsgEditEnterPushed)
END_MESSAGE_MAP()

// 函数 CMySamPalteDlg::OnPaint
// 作用：窗口需要重画时绘制内容。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 clock、dc、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width。
void CMySamPalteDlg::OnPaint()
{
#ifdef _DEBUG
	clock_t startMs = clock();
#endif

	CPaintDC dc(this); 

	CRect rcClient;
	GetClientRect(&rcClient);

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(&dc,rcClient.Width(),rcClient.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitMap);

	CFont* pOldFont = memDC.SelectObject(&m_fontSet);
	memDC.SetBkMode(TRANSPARENT);
	memDC.SetTextColor(m_txClr1);

	//绘制边框
	if(m_bRoundRectStyle)
	{
		Color clrFrame = 0;
		clrFrame.SetFromCOLORREF(m_clrFrame);
		CRect rcTemp(0,0,m_rcBody.right + m_pxFrame,m_rcBody.bottom + m_pxFrame);
		memDC.FillSolidRect(rcTemp.left,rcTemp.top,rcTemp.Width(),rcTemp.Height(),m_clrFourAngleBk);
		DrawRoundRectangleNew(&memDC,rcTemp.left,rcTemp.top,rcTemp.Width() - m_pxFrame,rcTemp.Height() - m_pxFrame,m_iRoundAngleSize,m_iRoundAngleSize,0,0,TRUE, clrFrame,m_pxFrame,TRUE,m_clrIndepent,1);
	}
	else
	{
		if(m_bShowFrameLine)
		{
			CPen penFrame;
			penFrame.CreatePen(PS_SOLID,m_pxFrame,m_clrFrame);
			CPen* pOldPen = memDC.SelectObject(&penFrame);
			memDC.Rectangle(&rcClient);
			memDC.SelectObject(pOldPen);
		}
	}

	DrawTotalHeader(&memDC);
	DrawRowHeader(&memDC);
	DrawColHeader(&memDC);
	DrawBody(&memDC);
	DrawHoriScroll(&memDC);
	DrawVertScroll(&memDC);

	//去除底部边框线条效果
	if(m_bRoundRectStyle)
	{
		CPoint pt;
		CPen penBottomFrame;
		
		//根据最后一个行标题选中情况确定画笔颜色
		penBottomFrame.CreatePen(PS_SOLID,m_pxFrame,RGB(m_clrHeaderBk.GetR(),m_clrHeaderBk.GetG(),m_clrHeaderBk.GetB()));
		CPen* pOldPen = memDC.SelectObject(&penBottomFrame);

		pt.x = m_pxFrame;
		pt.y = m_rcLst.bottom - m_pxFrame;
		memDC.MoveTo(pt);
		pt.x = m_rcRowHeader.right;
		memDC.LineTo(pt);
		penBottomFrame.DeleteObject();

		penBottomFrame.CreatePen(PS_SOLID,m_pxFrame,m_clrBodyBk);

		pt.x = m_rcRowHeader.right + 1;
		pt.y = m_rcLst.bottom - m_pxFrame;
		memDC.MoveTo(pt);
		pt.x = m_rcBody.right;
		memDC.LineTo(pt);

		memDC.SelectObject(pOldPen);
		penBottomFrame.DeleteObject();
	}

	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDC,0,0,SRCCOPY);   

	memDC.SelectObject(pOldBitmap);
	memDC.SelectObject(pOldFont);
	bitMap.DeleteObject();
	memDC.DeleteDC();

#ifdef _DEBUG
	clock_t existMs = clock() - startMs;
#endif

	return;
}

// 函数 CMySamPalteDlg::DrawTotalHeader
// 作用：绘制DrawTotalHeader。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CreateCompatibleDC、tempRcHeader、Width、Height、CreateCompatibleBitmap、SelectObject。
int CMySamPalteDlg::DrawTotalHeader(CDC* pDC)
{
	if(NULL == pDC)
	{
		return -1;
	}

	CDC memDcHeader;
	memDcHeader.CreateCompatibleDC(pDC);

	CRect tempRcHeader(0,0,m_rcRowHeader.Width(),m_rcColHeader.Height());

	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(pDC,m_rcRowHeader.Width(),m_rcColHeader.Height());
	CBitmap* pOldBitmap = memDcHeader.SelectObject(&bitMap);
	memDcHeader.SetBkMode(TRANSPARENT);

	if(m_bGradientHeader)
	{
		Graphics graphics(memDcHeader.m_hDC);
		LinearGradientBrush linGrBrush(RectF(0,0,m_rcRowHeader.Width(),m_rcColHeader.Height()),m_clrGraHeadStart,m_clrGraHeadEnd,LinearGradientModeVertical);
		graphics.FillRectangle(&linGrBrush,0,0,m_rcRowHeader.Width(),m_rcColHeader.Height());
		graphics.ReleaseHDC(memDcHeader.m_hDC);
	}
	else
	{
		Color clrBk = m_clrHeaderBk;
		if(m_bAllSelected)
		{
			clrBk = m_clrHeaderSelectedBk;
		}
		memDcHeader.FillSolidRect(&tempRcHeader,RGB(clrBk.GetR(),clrBk.GetG(),clrBk.GetB()));
	}

	memDcHeader.SetTextColor(m_clrHeaderText);
	CFont* pOldFont = memDcHeader.SelectObject(&m_fontSetHeader);
	memDcHeader.DrawText(m_strTotalTitle,&tempRcHeader,DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	if(m_bShowSplitLine)
	{
		//绘制分隔线
		CPen penLine;
		penLine.CreatePen(PS_SOLID,2,m_clrHeadBodySepa);
		CPen* pOldPen = memDcHeader.SelectObject(&penLine);

		POINT pt;
		pt.x = 1;
		pt.y = m_pxColHeaderH - 1;
		memDcHeader.MoveTo(pt);
		pt.x = m_pxRowHeaderW - 1;
		memDcHeader.LineTo(pt);

		pt.x = m_pxRowHeaderW - 1;
		pt.y = 1;
		memDcHeader.MoveTo(pt);
		pt.y = m_pxColHeaderH - 1;
		memDcHeader.LineTo(pt);

		memDcHeader.SelectObject(pOldPen);
	}

	if(m_bRoundRectStyle)
	{
		//检查使用稳定性
		memDcHeader.TransparentBlt(0,0,tempRcHeader.Width(),tempRcHeader.Height(),pDC,m_rcTotalHeader.left,m_rcTotalHeader.top,m_rcTotalHeader.Width(),m_rcTotalHeader.Height(),RGB(m_clrIndepent.GetR(),m_clrIndepent.GetG(),m_clrIndepent.GetB()));
		pDC->TransparentBlt(m_rcTotalHeader.left,m_rcTotalHeader.top,m_rcTotalHeader.Width(),m_rcTotalHeader.Height(),&memDcHeader,0,0,tempRcHeader.Width(),tempRcHeader.Height(),m_clrFourAngleBk);
	}
	else
	{
		pDC->BitBlt(m_rcTotalHeader.left,m_rcTotalHeader.top,m_rcTotalHeader.Width(),m_rcTotalHeader.Height(),&memDcHeader,0,0,SRCCOPY); 
	} 

	memDcHeader.SelectObject(pOldFont);
	memDcHeader.SelectObject(pOldBitmap);

	memDcHeader.DeleteDC();
	bitMap.DeleteObject();

	return 0;
}

// 函数 CMySamPalteDlg::DrawRowHeader
// 作用：绘制DrawRowHeader。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、CreateCompatibleDC、tempRcHeader、Width、CreateCompatibleBitmap、SelectObject。
int CMySamPalteDlg::DrawRowHeader(CDC* pDC)
{
	if(NULL == pDC)
	{
		return -1;
	}

	if(m_rowNum < 1)
	{
		return -2;
	}

	if(m_lnkRowInfo.GetSize() != m_rowNum)
	{
		return -3;
	}

	CDC memDcHeader;
	memDcHeader.CreateCompatibleDC(pDC);

	CRect tempRcHeader(0,0,m_rcRowHeader.Width(),m_cdcH);

	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(pDC,m_rcRowHeader.Width(),m_cdcH);
	CBitmap* pOldBitmap = memDcHeader.SelectObject(&bitMap);
	memDcHeader.SetBkMode(TRANSPARENT);

	if(m_bGradientHeader)
	{
		Graphics graphics(memDcHeader.m_hDC);
		LinearGradientBrush linGrBrush(RectF(0,0,m_rcRowHeader.Width(),m_cdcH),m_clrGraHeadStart,m_clrGraHeadEnd,LinearGradientModeVertical);
		graphics.FillRectangle(&linGrBrush,0,0,m_rcRowHeader.Width(),m_cdcH);
		graphics.ReleaseHDC(memDcHeader.m_hDC);
	}
	else
	{
		memDcHeader.FillSolidRect(&tempRcHeader,RGB(m_clrHeaderBk.GetR(),m_clrHeaderBk.GetG(),m_clrHeaderBk.GetB()));
	}

	memDcHeader.SetTextColor(m_clrHeaderText);

	CRect tempRc;
	tempRc.left = 0;
	tempRc.right = m_pxRowHeaderW;
	CFont* pOldFont = memDcHeader.SelectObject(&m_fontSetHeader);
	CString strTag(_T(""));
	for(int i = m_rowIdStartShow;i <= m_rowIdEndShow;++i)
	{
		tempRc.top = GetRowStartDrawInMemoryVertPixel(i);
		tempRc.bottom = tempRc.top + m_lnkRowInfo[i]->m_rowH;
		CRowInfo& rowInfo = m_lnkRowInfo.GetAt(i)->data;
		if(rowInfo.m_bSelected)
		{
			memDcHeader.FillSolidRect(&tempRc,RGB(m_clrHeaderSelectedBk.GetR(),m_clrHeaderSelectedBk.GetG(),m_clrHeaderSelectedBk.GetB()));
		}
		else
		{
			memDcHeader.FillSolidRect(&tempRc,RGB(m_clrHeaderBk.GetR(),m_clrHeaderBk.GetG(),m_clrHeaderBk.GetB()));
		}
		GetRowTag(i,strTag);
		memDcHeader.DrawText(strTag,&tempRc,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if(m_bShowSplitLine)
	{
		//绘制Header和Body分隔线
		CPen penLine;
		penLine.CreatePen(PS_SOLID,2,m_clrHeadBodySepa);
		CPen* pOldPen = memDcHeader.SelectObject(&penLine);

		POINT pt;
		pt.y = 1;
		pt.x = m_pxRowHeaderW - 1;
		memDcHeader.MoveTo(pt);
		pt.y = m_cdcH - 1;
		memDcHeader.LineTo(pt);

		memDcHeader.SelectObject(pOldPen);
	}

	pDC->BitBlt(m_rcRowHeader.left,m_rcRowHeader.top,m_rcRowHeader.Width(),m_rcRowHeader.Height(),&memDcHeader,0,m_ssRowTopIndent,SRCCOPY);  

	memDcHeader.SelectObject(pOldFont);
	memDcHeader.SelectObject(pOldBitmap);

	memDcHeader.DeleteDC();
	bitMap.DeleteObject();

	return 0;
}

// 函数 CMySamPalteDlg::DrawColHeader
// 作用：绘制DrawColHeader。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、CreateCompatibleDC、tempRcHeader、Height、CreateCompatibleBitmap、SelectObject。
int CMySamPalteDlg::DrawColHeader(CDC* pDC)
{
	if(NULL == pDC)
	{
		return -1;
	}

	if(m_colNum < 1)
	{
		return -2;
	}

	if(m_lnkTitleInfo.GetSize() != m_colNum)
	{
		return -3;
	}

	CDC memDcHeader;
	memDcHeader.CreateCompatibleDC(pDC);

	CRect tempRcHeader(0,0,m_cdcW,m_rcColHeader.Height());

	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(pDC,m_cdcW,m_rcColHeader.Height());
	CBitmap* pOldBitmap = memDcHeader.SelectObject(&bitMap);
	memDcHeader.SetBkMode(TRANSPARENT);

	if(m_bGradientHeader)
	{
		Graphics graphics(memDcHeader.m_hDC);
		LinearGradientBrush linGrBrush(RectF(0,0,m_cdcW,m_pxColHeaderH),m_clrGraHeadStart,m_clrGraHeadEnd,LinearGradientModeVertical);
		graphics.FillRectangle(&linGrBrush,0,0,m_cdcW,m_pxColHeaderH);
		graphics.ReleaseHDC(memDcHeader.m_hDC);
	}
	else
	{
		memDcHeader.FillSolidRect(&tempRcHeader,RGB(m_clrHeaderBk.GetR(),m_clrHeaderBk.GetG(),m_clrHeaderBk.GetB()));
	}

	memDcHeader.SetTextColor(m_clrHeaderText);

	CRect tempRc;
	tempRc.top = 0;
	tempRc.bottom = m_pxColHeaderH;
	CFont* pOldFont = memDcHeader.SelectObject(&m_fontSetHeader);
	CString strTag(_T(""));
	for(int i = m_colIdStartShow;i <= m_colIdEndShow;++i)
	{
		tempRc.left = GetColStartDrawInMemoryHoriPixel(i);
		tempRc.right = tempRc.left + m_lnkTitleInfo[i]->m_colWidth;
		CTitleInfo& titleInfo = m_lnkTitleInfo.GetAt(i)->data;
		if(titleInfo.m_bSelected)
		{
			memDcHeader.FillSolidRect(&tempRc,RGB(m_clrHeaderSelectedBk.GetR(),m_clrHeaderSelectedBk.GetG(),m_clrHeaderSelectedBk.GetB()));
		}
		else
		{
			memDcHeader.FillSolidRect(&tempRc,RGB(m_clrHeaderBk.GetR(),m_clrHeaderBk.GetG(),m_clrHeaderBk.GetB()));
		}

		GetColTag(i,strTag);
		memDcHeader.DrawText(strTag,&tempRc,DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	if(m_bShowSplitLine)
	{
		//绘制Header和Body分隔线
		CPen penLine;
		penLine.CreatePen(PS_SOLID,2,m_clrHeadBodySepa);
		CPen* pOldPen = memDcHeader.SelectObject(&penLine);

		POINT pt;
		pt.x = 1;
		pt.y = m_pxColHeaderH - 1;
		memDcHeader.MoveTo(pt);
		pt.x = m_cdcW - 1;
		memDcHeader.LineTo(pt);

		memDcHeader.SelectObject(pOldPen);
	}

	int iRealW = m_rcColHeader.Width();
	if(m_cdcW < iRealW)
	{
		iRealW = m_cdcW;
	}
	memDcHeader.TransparentBlt(m_ssColLeftIndent,0,iRealW,m_rcColHeader.Height(),pDC,m_rcColHeader.left,m_rcColHeader.top,iRealW,m_rcColHeader.Height(),RGB(m_clrIndepent.GetR(),m_clrIndepent.GetG(),m_clrIndepent.GetB()));
	pDC->TransparentBlt(m_rcColHeader.left,m_rcColHeader.top,iRealW,m_rcColHeader.Height(),&memDcHeader,m_ssColLeftIndent,0,iRealW,m_rcColHeader.Height(),m_clrFourAngleBk);

	//pDC->BitBlt(m_rcColHeader.left,m_rcColHeader.top,m_rcColHeader.Width(),m_rcColHeader.Height(),&memDcHeader,m_ssColLeftIndent,0,SRCCOPY);  

	memDcHeader.SelectObject(pOldFont);
	memDcHeader.SelectObject(pOldBitmap);

	memDcHeader.DeleteDC();
	bitMap.DeleteObject();
	
	return 0;
}

// 函数 CMySamPalteDlg::DrawBody
// 作用：绘制DrawBody。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、CreateCompatibleDC、Width、Height、CreateCompatibleBitmap、SelectObject。
int CMySamPalteDlg::DrawBody(CDC* pDC)
{
	if(NULL == pDC)
	{
		return -1;
	}

	if(m_colNum < 1)
	{
		return -2;
	}

	if(m_lnkTitleInfo.GetSize() != m_colNum)
	{
		return -3;
	}

	CDC memDcBody;
	memDcBody.CreateCompatibleDC(pDC);

	CBitmap bitMap;
	int ltempCdcW = m_cdcW,tempCdcH = m_cdcH;
	if(-1 == m_rowIdStartShow || m_cdcW < m_rcBody.Width())
	{
		ltempCdcW = m_rcBody.Width();
	}
	if(-1 == m_rowIdStartShow || m_cdcH < m_rcBody.Height())
	{
		tempCdcH = m_rcBody.Height();
	}
	bitMap.CreateCompatibleBitmap(pDC,ltempCdcW,tempCdcH);
	CBitmap* pOldBitmap = memDcBody.SelectObject(&bitMap);

	memDcBody.FillSolidRect(0,0,ltempCdcW,tempCdcH,m_clrBodyBk);

	CRect tempRc;
	tempRc.top = m_pxColHeaderH;
	CFont* pOldFont = memDcBody.SelectObject(&m_fontSet);
	memDcBody.SetTextColor(m_txClr1);
	memDcBody.SetBkMode(TRANSPARENT);

	CPen penLine;
	penLine.CreatePen(PS_SOLID,m_pxRowColLine,m_clrRowColLine);
	CPen* pOldPen = memDcBody.SelectObject(&penLine);

	Graphics graphics(memDcBody.m_hDC);
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	CString strTemp(_T(""));

	if(-1 == m_rowIdStartShow || m_cdcH < m_rcBody.Height())
	{
		if(m_bShowRowColLine)
		{
			//绘制水平分割线
			for(int i = m_rowIdSeparatorStart;i <= m_rowIdSeparatorEnd;++i)
			{
				POINT pt;
				pt.x = 0;
				pt.y = (i + 1) * m_pxRowH - m_pxRowColLine;
				memDcBody.MoveTo(pt);
				pt.x = ltempCdcW;
				memDcBody.LineTo(pt);
			}

			//绘制垂直分割线
			for(int j = m_colIdStartShow;j <= m_colIdEndShow;++j)
			{
				if(j != m_colIdEndShow)
				{
					POINT pt;
					pt.x = GetColStartDrawInMemoryHoriPixel(j + 1) - m_pxRowColLine;
					pt.y = 0;
					memDcBody.MoveTo(pt);
					pt.y = tempCdcH;
					memDcBody.LineTo(pt);
				}
			}
		}
	}

	if(-1 != m_rowIdStartShow)
	{
		int iFrameLineW = 2,iBottomTxRgnH = 30 * m_dVertRatio,iAbbrH = 30 * m_dVertRatio;
		int iChanCount = 0; 
		int iClrWH = 12 * m_dHoriRatio,iClrHoriInterval = 4 * m_dHoriRatio;
		COLORREF clrChan = 0;
		CString strChanName(_T(""));

		if(m_bShowBottomTx)
		{
			iClrHoriInterval = 12 * m_dHoriRatio;
		}

		for(int i = m_rowIdStartShow;i <= m_rowIdEndShow;++i)
		{
			CRowInfo& rowInfo = *m_lnkRowInfo[i];

			tempRc.top = GetRowStartDrawInMemoryVertPixel(i);
			tempRc.left = 0;
			tempRc.right = ltempCdcW;
			tempRc.bottom = tempRc.top + rowInfo.m_rowH;
			tempRc.DeflateRect(0,1,0,1);
			for(int j = m_colIdStartShow;j <= m_colIdEndShow;++j)
			{
				CTitleInfo& titleInfo = m_lnkTitleInfo.GetAt(j)->data;
				CCellInfo& cellInfo = m_2LnkCellInfo[i]->GetAt(j)->data;
				tempRc.left = GetColStartDrawInMemoryHoriPixel(j);
				tempRc.right = tempRc.left + m_lnkTitleInfo[j]->m_colWidth;

#ifdef PS384INSTRUMENT
				tempRc.top = GetRowStartDrawInMemoryVertPixel(i);
				tempRc.bottom = tempRc.top + rowInfo.m_rowH;
				tempRc.DeflateRect(tempRc.Width()/20, tempRc.Height()/20);
#else
				tempRc.left += (tempRc.Width() - m_iRectW) / 2;
				tempRc.right = tempRc.left + m_iRectW;
				tempRc.top += (tempRc.Height() - m_iRectH) / 2;
				tempRc.bottom = tempRc.top + m_iRectH;
#endif

				CRect rcTop,rcBottom,rcChanClr,rcChanText,rcTypeAbbr;
				int iIndex = i * m_colNum + j;
				iChanCount = m_pTubeInfo[iIndex].GetChannelNum();
				if(!m_bShowLastChanBlock)
				{
					iChanCount -= 1;
				}
				
				if(m_bShowTopTx)
				{
					rcTop.left = tempRc.left;
					rcTop.right = tempRc.right;
					rcTop.top = tempRc.top;
					rcTop.bottom = rcTop.top + m_iRectH / 3;
				}
				
				if(m_bShowBottomTx)
				{
					rcBottom.left = tempRc.left;
					rcBottom.right = tempRc.right;
					rcBottom.top = tempRc.bottom - iBottomTxRgnH;
					rcBottom.bottom = rcBottom.top + iBottomTxRgnH;
				}

#ifdef PS384INSTRUMENT
				rcChanClr.left = tempRc.left + int(2 * m_dHoriRatio);
				rcChanClr.right = rcChanClr.left + iClrWH;
				rcChanClr.top = tempRc.top + int(2 * m_dVertRatio);
				rcChanClr.bottom = rcChanClr.top + iClrWH;

				rcTypeAbbr = tempRc;
				rcTypeAbbr.DeflateRect(rcTypeAbbr.Width()/10, rcTypeAbbr.Height()/6, 0, 0);
#else
				if(iChanCount > 0)
				{
					iClrWH = (tempRc.Width() - iClrHoriInterval * (iChanCount + 1)) / iChanCount;
				}
				rcChanClr.left = tempRc.left + iClrHoriInterval;
				rcChanClr.right = rcChanClr.left + iClrWH;
				rcChanClr.top = tempRc.top + 4 * m_dVertRatio;
				rcChanClr.bottom = rcChanClr.top + iClrWH;

				iAbbrH = 16 * m_dVertRatio;
				rcTypeAbbr.left = tempRc.left + 5 * m_dHoriRatio;
				rcTypeAbbr.right = tempRc.right;
				rcTypeAbbr.top = tempRc.bottom - iAbbrH;
				if(m_bShowBottomTx)
				{
					rcTypeAbbr.top -= iBottomTxRgnH;
				}
				rcTypeAbbr.bottom = rcTypeAbbr.top + iAbbrH;
#endif

				CHoleColorInfo holeClrInfo;
				GetHoleColorInfo(i,j,holeClrInfo);
				
				if(m_pTubeInfo[iIndex].GetBeNoneSampleType() && !m_pPlateInfo[iIndex].m_bSelected)
				{
					iFrameLineW = 2;
				}
				else
				{
					iFrameLineW = 2;
				}
				DrawRoundRectangleNew(&memDcBody,tempRc.left,tempRc.top,tempRc.Width(),tempRc.Height(),m_iRoundAngleLT,m_iRoundAngleRT,m_iRoundAngleRB,m_iRoundAngleLB,TRUE,holeClrInfo.m_clrFrame,iFrameLineW,m_pPlateInfo[i * m_colNum + j].m_bSelected,holeClrInfo.m_clrFill);

				COLORREF clrTemp = holeClrInfo.m_clrTxUnSelected;
				if(m_pPlateInfo[iIndex].m_bSelected)
				{
					clrTemp = holeClrInfo.m_clrTxSelected;
				}

				if(m_bShowSiteId)
				{
					memDcBody.SetTextColor(clrTemp);
					strTemp.Format(_T("%d"),iIndex + 1);
					memDcBody.DrawText(strTemp,&tempRc,DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
				}

				if(m_bShowTopTx)
				{
					memDcBody.DrawText(m_pTubeInfo[iIndex].GetSampleName(),&rcTop,DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
				}
				if(m_bShowBottomTx)
				{
					memDcBody.DrawText(m_pTubeInfo[iIndex].GetSampleID(),&rcBottom,DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
				}

#ifdef PS384INSTRUMENT
				COLORREF clrOldText2 = memDcBody.SetTextColor(RGB(0X39,0X45,0X65));
				memDcBody.DrawText(GetSampleTypeAbbr(m_pTubeInfo[iIndex].GetSampleType()),&rcTypeAbbr,DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
				memDcBody.SetTextColor(clrOldText2);

				////绘制通道颜色块
				//for(int k = 0;k < iChanCount;++k)
				//{
				//	if(m_pTubeInfo[iIndex].GetSampleChannelSelectState(k))
				//	{
				//		COLORREF clrOldText = memDcBody.SetTextColor(RGB(0X39,0X45,0X65));
				//		strChanName = m_pTubeInfo[iIndex].GetDyeName(k);
				//		clrChan = m_pTubeInfo[iIndex].GetSampleDyeTargetColor(k);
				//		//memDcBody.FillSolidRect(&rcChanClr,clrChan);

				//		Color clrFill = 0;
				//		clrFill.SetFromCOLORREF(clrChan);
				//		DrawRoundRectangleNew(&memDcBody,rcChanClr.left,rcChanClr.top,rcChanClr.Width(),rcChanClr.Height(),2,2,2,2,FALSE,Color(0,0,0),1,TRUE,clrFill);

				//		rcChanText = rcChanClr;
				//		rcChanText.left = rcChanText.right + 2;
				//		rcChanText.right = tempRc.right;
				//		rcChanText.top -= 5 * m_dVertRatio;
				//		rcChanText.bottom += 5 * m_dVertRatio;
				//		memDcBody.DrawText(strChanName,&rcChanText,DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
				//		memDcBody.SetTextColor(clrOldText);
				//	}
				//	rcChanClr.top = rcChanClr.bottom + m_iRectH / 6;
				//	rcChanClr.bottom = rcChanClr.top + iClrWH;
				//}
#else
				CFont* pOldFontTemp = memDcBody.SelectObject(&m_fontAbbr);

				COLORREF clrOldText2 = memDcBody.SetTextColor(RGB(0X39,0X45,0X65));
				memDcBody.DrawText(GetSampleTypeAbbr(m_pTubeInfo[iIndex].GetSampleType()),&rcTypeAbbr,DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
				memDcBody.SetTextColor(clrOldText2);

				memDcBody.SelectObject(pOldFontTemp);

#ifndef SHIELD_COLOR_BLOCK
				//绘制通道颜色块
				for(int k = 0;k < iChanCount;++k)
				{
					if(m_pTubeInfo[iIndex].GetSampleChannelSelectState(k))
					{
						COLORREF clrOldText = memDcBody.SetTextColor(RGB(0X39,0X45,0X65));
						strChanName = m_pTubeInfo[iIndex].GetDyeName(k);
						clrChan = m_pTubeInfo[iIndex].GetSampleDyeTargetColor(k);
						memDcBody.FillSolidRect(&rcChanClr,clrChan);

						/*Color clrFill = 0;
						clrFill.SetFromCOLORREF(clrChan);
						DrawRoundRectangleNew(&memDcBody,rcChanClr.left,rcChanClr.top,rcChanClr.Width(),rcChanClr.Height(),2,2,2,2,FALSE,Color(0,0,0),1,TRUE,clrFill);*/

						/*rcChanText = rcChanClr;
						rcChanText.left = rcChanText.right + 2;
						rcChanText.right = tempRc.right;
						rcChanText.top -= 5 * m_dVertRatio;
						rcChanText.bottom += 5 * m_dVertRatio;
						memDcBody.DrawText(strChanName,&rcChanText,DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
						memDcBody.SetTextColor(clrOldText);*/
					}
					rcChanClr.left = rcChanClr.right + iClrHoriInterval;
					rcChanClr.right = rcChanClr.left + iClrWH;
				}
#endif

#endif
			}
		}
		 
		m_bShowRowColLine = FALSE;
		if(m_bShowRowColLine)
		{
			//绘制水平分割线
			for(int i = m_rowIdStartShow;i <= m_rowIdEndShow;++i)
			{
				if(i != m_rowIdEndShow)
				{
					POINT pt;
					pt.x = 0;
					pt.y = GetRowStartDrawInMemoryVertPixel(i + 1) - m_pxRowColLine;
					memDcBody.MoveTo(pt);
					pt.x = ltempCdcW;
					memDcBody.LineTo(pt);
				}
				else if(m_cdcH < m_rcBody.Height())
				{
					POINT pt;
					pt.x = 0;
					pt.y = GetRowStartDrawInMemoryVertPixel(i + 1) - m_pxRowColLine;
					memDcBody.MoveTo(pt);
					pt.x = ltempCdcW;
					memDcBody.LineTo(pt);
				}
			}

			//绘制垂直分割线
			for(int j = m_colIdStartShow;j <= m_colIdEndShow;++j)
			{
				if(j != m_colIdEndShow)
				{
					POINT pt;
					pt.x = GetColStartDrawInMemoryHoriPixel(j + 1) - m_pxRowColLine;
					pt.y = 0;
					memDcBody.MoveTo(pt);
					pt.y = m_cdcH;
					memDcBody.LineTo(pt);
				}
			}
		}
	}

	graphics.ReleaseHDC(memDcBody.m_hDC);
	pDC->BitBlt(m_rcBody.left,m_rcBody.top,m_rcBody.Width(),m_rcBody.Height(),&memDcBody,m_ssColLeftIndent,m_ssRowTopIndent,SRCCOPY);   

	memDcBody.SelectObject(&pOldPen);
	memDcBody.SelectObject(pOldFont);
	memDcBody.SelectObject(pOldBitmap);

	memDcBody.DeleteDC();
	bitMap.DeleteObject();

	return 0;
}

// 函数 CMySamPalteDlg::DrawHoriScroll
// 作用：绘制DrawHoriScroll。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clock、FillSolidRect、CreateSolidBrush、RGB、FrameRect、InflateRect。
int CMySamPalteDlg::DrawHoriScroll(CDC* pDC)
{
	if(NULL == pDC)
	{
		return -1;
	}
	if(!m_horiScroll.m_bScrollNeedShow)
	{
		return 1;
	}

#ifdef _DEBUG
	clock_t startMs = clock();
#endif

	pDC->FillSolidRect(&m_horiScroll.m_rcScroll,m_horiScroll.m_clrBk);

	CBrush lineBrush;
	lineBrush.CreateSolidBrush(RGB(197,197,197));
	pDC->FrameRect(&m_horiScroll.m_rcScroll,&lineBrush);

	CRect rcTemp;
	rcTemp = m_horiScroll.m_rcStartArrow;
	rcTemp.InflateRect(m_pxFrame,0,0,m_pxFrame);
	pDC->FrameRect(&rcTemp,&lineBrush);

	//绘制左向箭头
	Graphics graphics(pDC->m_hDC);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush brush(Color(128,128,128));
	int triangleW = 7,triangleH = 9;
	int tempInt1 = rcTemp.right - (rcTemp.Width() - triangleW) / 2;
	int tempInt2 = rcTemp.top + (rcTemp.Height() - triangleH) / 2;
	Point pt1(tempInt1,tempInt2);
	Point pt2(tempInt1,tempInt2 + triangleH);
	Point pt3(tempInt1 - triangleW,tempInt2 + triangleH / 2);

	Point crvPts[3] = {pt1,pt2,pt3};
	graphics.FillPolygon(&brush,crvPts,3,FillModeAlternate);

	rcTemp = m_horiScroll.m_rcEndArrow;
	if(ESHVCM_HORI == m_eScrollHVCM)
	{
		rcTemp.InflateRect(0,0,m_pxFrame,m_pxFrame);
	}
	else
	{
		rcTemp.InflateRect(0,0,0,m_pxFrame);
	}
	pDC->FrameRect(&rcTemp,&lineBrush);

	//绘制右向箭头
	tempInt1 = rcTemp.left + (rcTemp.Width() - triangleW) / 2;
	tempInt2 = rcTemp.top + (rcTemp.Height() - triangleH) / 2;
	Point pt12(tempInt1,tempInt2);
	Point pt22(tempInt1,tempInt2 + triangleH);
	Point pt32(tempInt1 + triangleW,tempInt2 + triangleH / 2);

	Point crvPts2[3] = {pt12,pt22,pt32};
	graphics.FillPolygon(&brush,crvPts2,3,FillModeAlternate);
	graphics.ReleaseHDC(pDC->m_hDC);

	CPen penSliderFrame;
	penSliderFrame.CreatePen(PS_SOLID,1,RGB(164,164,164));
	CPen* pOldPen = pDC->SelectObject(&penSliderFrame);
	rcTemp = m_horiScroll.m_rcSlider;
	rcTemp.DeflateRect(0,1,0,-1);
	pDC->Rectangle(&rcTemp);
	pDC->SelectObject(pOldPen);
	
#ifdef _DEBUG
	clock_t existMs = clock() - startMs;
#endif

	return 0;
}

// 函数 CMySamPalteDlg::DrawVertScroll
// 作用：绘制DrawVertScroll。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clock、FillSolidRect、CreateSolidBrush、RGB、FrameRect、InflateRect。
int CMySamPalteDlg::DrawVertScroll(CDC* pDC)
{
	if(NULL == pDC)
	{
		return -1;
	}

	if(!m_vertScroll.m_bScrollNeedShow)
	{
		return 1;
	}

#ifdef _DEBUG
	clock_t startMs = clock();
#endif

	pDC->FillSolidRect(&m_vertScroll.m_rcScroll,m_vertScroll.m_clrBk);

	CBrush lineBrush;
	lineBrush.CreateSolidBrush(RGB(197,197,197));
	pDC->FrameRect(&m_vertScroll.m_rcScroll,&lineBrush);

	CRect rcTemp;
	rcTemp = m_vertScroll.m_rcStartArrow;
	rcTemp.InflateRect(0,m_pxFrame,m_pxFrame,0);
	pDC->FrameRect(&rcTemp,&lineBrush);

	//绘制顶向箭头
	Graphics graphics(pDC->m_hDC);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	SolidBrush brush(Color(128,128,128));
	int triangleW = 9,triangleH = 7;
	int tempInt1 = rcTemp.left + (rcTemp.Width() - triangleW) / 2;
	int tempInt2 = rcTemp.top + (rcTemp.Height() - triangleH) / 2;
	Point pt1(tempInt1,tempInt2 + triangleH);
	Point pt2(tempInt1 + triangleW,tempInt2 + triangleH);
	Point pt3(tempInt1 + triangleW / 2,tempInt2);

	Point crvPts[3] = {pt1,pt2,pt3};
	graphics.FillPolygon(&brush,crvPts,3,FillModeAlternate);

	rcTemp = m_vertScroll.m_rcEndArrow;
	if(ESHVCM_HORI == m_eScrollHVCM)
	{
		rcTemp.InflateRect(0,0,m_pxFrame,0);
	}
	else
	{
		rcTemp.InflateRect(0,0,m_pxFrame,m_pxFrame);
	}
	pDC->FrameRect(&rcTemp,&lineBrush);
	//绘制底向箭头
	tempInt1 = rcTemp.left + (rcTemp.Width() - triangleW) / 2;
	tempInt2 = rcTemp.bottom - (rcTemp.Height() - triangleH) / 2;
	Point pt12(tempInt1,tempInt2 - triangleH);
	Point pt22(tempInt1 + triangleW,tempInt2 - triangleH);
	Point pt32(tempInt1 + triangleW / 2,tempInt2);

	Point crvPts2[3] = {pt12,pt22,pt32};
	graphics.FillPolygon(&brush,crvPts2,3,FillModeAlternate);
	graphics.ReleaseHDC(pDC->m_hDC);

	CPen penSliderFrame;
	penSliderFrame.CreatePen(PS_SOLID,1,RGB(164,164,164));
	CPen* pOldPen = pDC->SelectObject(&penSliderFrame);
	rcTemp = m_vertScroll.m_rcSlider;
	rcTemp.DeflateRect(1,0,-1,0);
	pDC->Rectangle(&rcTemp);
	pDC->SelectObject(pOldPen);
	
#ifdef _DEBUG
	clock_t existMs = clock() - startMs;
#endif

	return 0;
}

// 函数 CMySamPalteDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// 函数 CMySamPalteDlg::OnRButtonDown
// 作用：按下鼠标右键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindowVisible、ShowWindow、CRect、ClientToScreen、MoveWindow、SetCapture。
void CMySamPalteDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	return;

	if(m_sonWnd.IsWindowVisible())
	{
		m_sonWnd.ShowWindow(SW_HIDE);
	}
	else 
	{
		CRect rcTemp = CRect(point.x,point.y,point.x + 100,point.y + 60);
		ClientToScreen(&rcTemp);
		m_sonWnd.MoveWindow(&rcTemp,FALSE);
		m_sonWnd.ShowWindow(SW_SHOW);
		m_sonWnd.SetCapture();
	}
	
	if(!m_bEditable)
	{
		return;
	}
}

// 函数 CMySamPalteDlg::OnLButtonDblClk
// 作用：双击鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 CalcPtRowCol。
void CMySamPalteDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(!m_bEditable)
	{
		return;
	}

	CDotPosInfo dotPosInfo = CalcPtRowCol(point);	
	if(EDT_BODY == dotPosInfo.m_eDotPosType && !m_lnkRowInfo[dotPosInfo.m_rowId]->m_bDisabled)
	{
		
	}

	return;
}

// 函数 CMySamPalteDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 SetFocus、CalcPtRowCol、SetCapture。
void CMySamPalteDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bLeftBtDown = TRUE;

	if(!m_bEditable)
	{
		return CDialogEx::OnLButtonDown(nFlags,point);
	}

	SetFocus();

	m_dotPosLeftBtDown = CalcPtRowCol(point);

	if(m_horiScroll.m_bInSlider)
	{
		m_horiScroll.m_bLeftBtDown = TRUE;
		m_horiScroll.m_prePt = point;
		SetCapture();
	}
	else if(m_vertScroll.m_bInSlider)
	{
		m_vertScroll.m_bLeftBtDown = TRUE;
		m_vertScroll.m_prePt = point;
		SetCapture();
	}
	else
	{
		//计算鼠标点击时所在的行和列
		CDotPosInfo dotPosInfo = CalcPtRowCol(point);
		if(EDT_BODY == dotPosInfo.m_eDotPosType && -1 != dotPosInfo.m_rowId && !m_lnkRowInfo[dotPosInfo.m_rowId]->m_bDisabled)
		{
			m_bDraggableStart = TRUE;
			m_dragStartDotPosInfo = dotPosInfo;
			SetCapture();
		}
	}

DEFPROCESS:
	CDialogEx::OnLButtonDown(nFlags,point);

	return;
}

// 函数 CMySamPalteDlg::OnLButtonUp
// 作用：松开鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeValidPlate、ReleaseCapture、CalcPtRowCol、AddTail、push_back。
void CMySamPalteDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(!m_bLeftBtDown)
	{
		return CDialogEx::OnLButtonUp(nFlags,point);;
	}
	m_bLeftBtDown = FALSE;

	if(!m_bEditable)
	{
		return CDialogEx::OnLButtonUp(nFlags,point);
	}

	if(!GetBeValidPlate())
	{
		return;
	}

	if(m_horiScroll.m_bLeftBtDown || m_vertScroll.m_bLeftBtDown)
	{
		ReleaseCapture();
	}

	if(m_bDraggableStart)
	{
		m_bDraggableStart = FALSE;
		ReleaseCapture();
	}

	m_preDotPosInfo = m_curDotPosInfo;  
	m_curDotPosInfo = CalcPtRowCol(point);
	m_lnkHistoryDotPosInfo.AddTail(m_curDotPosInfo);
	m_dotPosLeftBtUp = m_curDotPosInfo;

	m_horiScroll.m_bLeftBtDown = FALSE;
	m_horiScroll.m_bStartDragSlider = FALSE;
	m_horiScroll.m_bSliderDragMove = FALSE;

	m_vertScroll.m_bLeftBtDown = FALSE;
	m_vertScroll.m_bStartDragSlider = FALSE;
	m_vertScroll.m_bSliderDragMove = FALSE;

	BOOL bCtrlPushed = MK_CONTROL & nFlags;
	BOOL bNeedRedraw = FALSE,bSelChange = FALSE;

	vector<BOOL> vecOriginSel;
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		vecOriginSel.push_back(m_pPlateInfo[i].m_bSelected);
	}

	if(m_bDragMove)	//拖动鼠标选中区域处理
	{
		m_bDragMove = FALSE;
		CPoint ptNew = point;
		if(point.y > m_rcBody.bottom)
		{
			ptNew.y = m_rcBody.bottom - 1;
		}
		if(point.y < m_rcBody.top)
		{
			ptNew.y = m_rcBody.top + 1;
		}
		if(point.x > m_rcBody.right)
		{
			ptNew.x = m_rcBody.right - 1;
		}
		if(point.x < m_rcBody.left)
		{
			ptNew.x = m_rcBody.left + 1;
		}
		CDotPosInfo tempDotPosInfo = CalcPtRowCol(ptNew);

		int startX = 0,endX = 0,startY,endY = 0;
		if(m_dragStartDotPosInfo.m_rowId <= tempDotPosInfo.m_rowId)
		{
			startX = m_dragStartDotPosInfo.m_rowId;
			endX = tempDotPosInfo.m_rowId;
		}
		else
		{
			endX = m_dragStartDotPosInfo.m_rowId;
			startX = tempDotPosInfo.m_rowId;
		}
		
		if(m_dragStartDotPosInfo.m_colId <= tempDotPosInfo.m_colId)
		{
			startY = m_dragStartDotPosInfo.m_colId;
			endY = tempDotPosInfo.m_colId;
		}
		else
		{
			endY = m_dragStartDotPosInfo.m_colId;
			startY = tempDotPosInfo.m_colId;
		}

		if(-1 == startX)
		{
			startX = 0;
		}
		if(-1 == endX)
		{
			endX = 0;
		}
		if(-1 == startY)
		{
			startY = 0;
		}
		if(-1 == endY)
		{
			endY = 0;
		}

		if(!bCtrlPushed)
		{
			for(int i = 0;i < m_iTotalSiteNum;++i)
			{
				m_pPlateInfo[i].m_bSelected = FALSE;
			}
		}

		int index = 0;
		for(int i = startY;i <= endY;++i)
		{
			for(int j = startX;j <= endX;++j)
			{
				index = j * m_colNum + i;
				m_pPlateInfo[index].m_bSelected = TRUE;
			}
		}

		UpdateRowSelectState(FALSE);
		UpdateColSelectState(FALSE);
		GetBeAllSelected();

		bNeedRedraw = TRUE;
		//判断选中孔位是否改变
		for(int i = 0;i < m_iTotalSiteNum;++i)
		{
			if(vecOriginSel[i] != m_pPlateInfo[i].m_bSelected)
			{
				bSelChange = TRUE;
				break;
			}
		}	
	}
	else	
	{
		//更新孔板选择状态
		if(EDT_TOTALHEADER == m_dotPosLeftBtUp.m_eDotPosType)
		{
			SetAllSelectState(!m_bAllSelected);
			bNeedRedraw = TRUE;
			bSelChange = TRUE;
		}
		else if(EDT_ROWHEADER == m_dotPosLeftBtUp.m_eDotPosType && -1 != m_dotPosLeftBtUp.m_rowId)
		{
			BOOL bSelected = m_lnkRowInfo[m_dotPosLeftBtUp.m_rowId]->m_bSelected;

			for(int j = 0;j < m_rowNum;++j)
			{
				if(j == m_dotPosLeftBtUp.m_rowId)
				{
					for(int i = 0;i < m_colNum;++i)
					{
						m_pPlateInfo[j * m_colNum + i].m_bSelected = TRUE;
					}
				}
				else if(!bCtrlPushed)
				{
					for(int i = 0;i < m_colNum;++i)
					{
						m_pPlateInfo[j * m_colNum + i].m_bSelected = FALSE;
					}
				}
			}

			UpdateRowSelectState(FALSE);
			UpdateColSelectState(FALSE);
			GetBeAllSelected();
			bNeedRedraw = TRUE;
			bSelChange = TRUE;
		}
		else if(EDT_COLHEADER == m_dotPosLeftBtUp.m_eDotPosType && -1 != m_dotPosLeftBtUp.m_colId)
		{
			BOOL bSelected = m_lnkTitleInfo[m_dotPosLeftBtUp.m_colId]->m_bSelected;
			for(int j = 0;j < m_colNum;++j)
			{
				if(j == m_dotPosLeftBtUp.m_colId)
				{
					for(int i = 0;i < m_rowNum;++i)
					{
						m_pPlateInfo[i * m_colNum + m_dotPosLeftBtUp.m_colId].m_bSelected = TRUE;
					}
				}
				else if(!bCtrlPushed)
				{
					for(int i = 0;i < m_rowNum;++i)
					{
						m_pPlateInfo[i * m_colNum + j].m_bSelected = FALSE;
					}
				}
			}

			UpdateColSelectState(FALSE);
			UpdateRowSelectState(FALSE);
			GetBeAllSelected();
			bNeedRedraw = TRUE;
			bSelChange = TRUE;
		}
		else if(EDT_BODY == m_dotPosLeftBtUp.m_eDotPosType && -1 != m_dotPosLeftBtUp.m_rowId && -1 != m_dotPosLeftBtUp.m_colId)
		{
			int iSiteIndex = m_dotPosLeftBtUp.m_rowId * m_colNum + m_dotPosLeftBtUp.m_colId;

			CRowInfo& rowInfo = *m_lnkRowInfo[m_dotPosLeftBtUp.m_rowId];
			CTitleInfo& titleInfo = *m_lnkTitleInfo[m_dotPosLeftBtUp.m_colId];
			CPlateInfo& plateInfo = m_pPlateInfo[iSiteIndex];
			
			BOOL bSelected = plateInfo.m_bSelected;
			if(bCtrlPushed)
			{
				plateInfo.m_bSelected = !bSelected;
				bNeedRedraw = TRUE;
				bSelChange = TRUE;
			}
			else
			{
				bNeedRedraw = TRUE;
				bSelChange = TRUE;
				for(int i = 0;i < m_iTotalSiteNum;++i)
				{
					if(i == iSiteIndex)
					{
						m_pPlateInfo[i].m_bSelected = m_bSingleSelect || bSelected;	//可优化，20220301
						if(m_bSingleSelect && m_preDotPosInfo == m_dotPosLeftBtUp && 1 == vecOriginSel.size())
						{
							bNeedRedraw = FALSE;
							bSelChange = FALSE;
						}
					}
					else
					{
						if(m_bSingleSelect)
						{
							m_pPlateInfo[i].m_bSelected = FALSE;
						}
					}
				}
			}
			
			//更新行列选择状态
			UpdateRowSelectState(FALSE);
			UpdateColSelectState(FALSE);
			GetBeAllSelected();
		}
	}

REDRAWLST:
	if(bNeedRedraw)
	{
		Invalidate(FALSE);
	}
	
	if(m_bTellParentSiteSelChange)
	{
		CWnd* pParent = GetParent();
		if(bSelChange && NULL != pParent->GetSafeHwnd())	//选中行改变，通知父窗口
		{
			pParent->PostMessage(WM_TELLPARENTSITESELECTCHANGED,0,0);
		}   
	}
	
	CDialogEx::OnLButtonUp(nFlags,point);
	return;
}

// 函数 CMySamPalteDlg::OnMouseMove
// 作用：鼠标在窗口上移动。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PtInRect、ProcessHoriSrcoll、ProcessVertSrcoll、dc、CreatePen、RGB。
void CMySamPalteDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if(!m_bEditable)
	{
		return;
	}

	if(m_horiScroll.m_bScrollNeedShow && m_horiScroll.m_rcSlider.PtInRect(point))
	{
		m_horiScroll.m_bInSlider = TRUE;
		if(m_horiScroll.m_bLeftBtDown)
		{
			m_horiScroll.m_bStartDragSlider = TRUE;
		}

		if(m_horiScroll.m_bStartDragSlider && (MK_LBUTTON & nFlags))
		{
			m_horiScroll.m_bSliderDragMove = TRUE;
		}
	}
	else
	{
		m_horiScroll.m_bInSlider = FALSE;
	}

	if(m_vertScroll.m_bScrollNeedShow && m_vertScroll.m_rcSlider.PtInRect(point))
	{
		m_vertScroll.m_bInSlider = TRUE;
		if(m_vertScroll.m_bLeftBtDown)
		{
			m_vertScroll.m_bStartDragSlider = TRUE;
		}

		if(m_vertScroll.m_bStartDragSlider && (MK_LBUTTON & nFlags))
		{
			m_vertScroll.m_bSliderDragMove = TRUE;
		}
	}
	else
	{
		m_vertScroll.m_bInSlider = FALSE;
	}

	if(m_horiScroll.m_bScrollNeedShow && m_horiScroll.m_bSliderDragMove)
	{
		ProcessHoriSrcoll(nFlags,point);
	}
	else if(m_vertScroll.m_bScrollNeedShow && m_vertScroll.m_bSliderDragMove)
	{
		ProcessVertSrcoll(nFlags,point);
	}

	//处理拖动选择样本孔位
	if(m_bDraggableStart && (nFlags & MK_LBUTTON))
	{	
		m_bDragMove = TRUE;

		CPoint ptNew = point;
		if(!m_rcBody.PtInRect(point))
		{
			if(point.y > m_rcBody.bottom)
			{
				ptNew.y = m_rcBody.bottom;
			}
			if(point.y < m_rcBody.top)
			{
				ptNew.y = m_rcBody.top;
			}
			if(point.x > m_rcBody.right)
			{
				ptNew.x = m_rcBody.right;
			}
			if(point.x < m_rcBody.left)
			{
				ptNew.x = m_rcBody.left;
			}
		}

		CClientDC dc(this);
		CPen penStroke;
		if(penStroke.CreatePen(PS_DASH,1,RGB(0X31,0X24,0X1B)))
		{
			//选画笔
			CPen* pOldPen = dc.SelectObject(&penStroke);
			dc.SelectStockObject(NULL_BRUSH);
			int n = dc.GetROP2();
			dc.SetROP2(R2_NOTXORPEN);		
			dc.Rectangle(m_dragStartDotPosInfo.m_pt.x,m_dragStartDotPosInfo.m_pt.y,m_ptPreOnMove.x,m_ptPreOnMove.y);
			dc.Rectangle(m_dragStartDotPosInfo.m_pt.x,m_dragStartDotPosInfo.m_pt.y,ptNew.x,ptNew.y);

			//恢复画笔
			dc.SelectObject(pOldPen);
			dc.SetROP2(n);
		}
		m_ptPreOnMove = ptNew;
	}
	else
	{
		m_ptPreOnMove = point;
	}
	
	return;
}

// 函数 CMySamPalteDlg::OnMouseWheel
// 作用：转动鼠标滚轮。
// 参数：nFlags：整数；zDelta；pt。
// 返回：返回是或否。
// 过程：函数里会调用 ScrollRow、ScrollCol。
BOOL CMySamPalteDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(!m_bEditable)
	{
		return __super::OnMouseWheel(nFlags, zDelta, pt);
	}

	if(m_vertScroll.m_bScrollNeedShow)
	{
		if(zDelta > 0)
		{
			ScrollRow(-m_pxRowH * 2);
		}
		else
		{
			ScrollRow(m_pxRowH * 2);
		}
	}
	else if(m_horiScroll.m_bScrollNeedShow)
	{
		if(zDelta > 0)
		{
			ScrollCol(-m_pxRowH * 2);
		}
		else
		{
			ScrollCol(m_pxRowH * 2);
		}
	}
	
	return __super::OnMouseWheel(nFlags, zDelta, pt);
}

// 函数 CMySamPalteDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Create、InsertRow、_T。
int CMySamPalteDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CDialogEx::OnCreate(lpCreateStruct);

	m_iRectW = 50 * m_dHoriRatio;
	m_iRectH = 42 * m_dVertRatio;

	m_iRoundAngleLT *= m_dTxRatio;
	m_iRoundAngleRT *= m_dTxRatio;
	m_iRoundAngleRB *= m_dTxRatio;
	m_iRoundAngleLB *= m_dTxRatio;

	m_sonWnd.Create(IDD_POPUPDLG,this);
	m_sonWnd.InsertRow(0,_T("1"));
	m_sonWnd.InsertRow(0,_T("2"));
	m_sonWnd.InsertRow(0,_T("3"));
	m_sonWnd.InsertRow(0,_T("4"));
	m_sonWnd.InsertRow(0,_T("中华人民共和国"));

	return 1;
}

// 函数 CMySamPalteDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 CRect、Width、Height、CalcTotalColumnWidth、CalcTotalRowHeight、CalcScrollPos。
void CMySamPalteDlg::OnSize(UINT nType, int cx, int cy)
{
	m_rcLst = CRect(0,0,cx,cy);
	m_rcTotalHeader = CRect(m_pxFrame,m_pxFrame,m_pxRowHeaderW,m_pxColHeaderH);
	m_rcRowHeader = CRect(m_pxFrame,m_pxColHeaderH,m_pxRowHeaderW,cy - m_pxFrame);
	m_rcColHeader = CRect(m_pxRowHeaderW,m_pxFrame,cx - m_pxFrame,m_pxColHeaderH); 
	m_rcBody = CRect(m_pxRowHeaderW,m_pxColHeaderH,cx - m_pxFrame,cy - m_pxFrame);

	if(0 != m_colNum)
	{
		m_pxColW = (cx - m_pxFrame * 2 - m_pxRowHeaderW) / m_colNum;
	}

	if(0 != m_rowNum)
	{
		m_pxRowH = (cy - m_pxFrame * 2 - m_pxColHeaderH) / m_rowNum;
	}

	for(int i = 0;i < m_rowNum;++i)
	{
		m_lnkRowInfo[i]->m_rowH = m_pxRowH;
	}

	for(int i = 0;i < m_colNum;++i)
	{
		m_lnkTitleInfo[i]->m_colWidth = m_pxColW;
	}

#ifdef SAMPLATE_16SITE
	int iColRemainder = 0,iRowRemainder = 0;

	//重新计算行高和列宽
	if(m_colNum > 0)
	{
		m_pxColW = m_rcBody.Width() / m_colNum;
		iColRemainder = m_rcBody.Width() % m_colNum;
	}
	if(m_rowNum > 0)
	{
		m_pxRowH = m_rcBody.Height() / m_rowNum;
		iRowRemainder = m_rcBody.Height() % m_rowNum;
	}

	for(int i = 0;i < m_colNum;++i)
	{
		if(i == m_colNum - 1)
		{
			m_lnkTitleInfo[i]->m_colWidth = m_pxColW + iColRemainder;
		}
		else
		{
			m_lnkTitleInfo[i]->m_colWidth = m_pxColW;
		}
	}
	for(int i = 0;i < m_rowNum;++i)
	{
		if(i == m_rowNum - 1)
		{
			m_lnkRowInfo[i]->m_rowH = m_pxRowH +iRowRemainder;
		}
		else
		{
			m_lnkRowInfo[i]->m_rowH = m_pxRowH;
		}
	}
#endif

	CalcTotalColumnWidth();
	CalcTotalRowHeight();

	CalcScrollPos();
	CalcRowColToShow();
	CalcRowColToShowOnNoRowData();

	CDialogEx::OnSize(nType, cx, cy);
} 

// 函数 CMySamPalteDlg::PreTranslateMessage
// 作用：消息送达窗口前先拦截键盘或鼠标。
// 参数：pMsg：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetParent、GetSafeHwnd、PostMessage、DeleteSelectedTubeInfo。
BOOL CMySamPalteDlg::PreTranslateMessage(MSG* pMsg)
{
	if(WM_KEYDOWN == pMsg->message)
	{
		int tt = 0;
		++tt;

		if(!m_bShieldDeleteKey && VK_DELETE == pMsg->wParam)
		{
			if(m_bParentProcessDeleteKey)
			{
				CWnd* pParent = GetParent();
				if(NULL != pParent->GetSafeHwnd())
				{
					pParent->PostMessage(SAMPLATE_DELETEKEY_PRESSED,0,0);
				}
			}
			else
			{
				DeleteSelectedTubeInfo(TRUE);
			}
		}
	}

	if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		switch(pMsg->wParam)
		{
		case VK_DELETE:
			if(1)
			{
				int tt = 0;
				++tt;
			}
			return TRUE;
		case VK_ESCAPE:	return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

// 函数 CMySamPalteDlg::OnMsgEditEnterPushed
// 作用：响应 Windows 或自定义消息 OnMsgEditEnterPushed。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
LRESULT CMySamPalteDlg::OnMsgEditEnterPushed(WPARAM wParam,LPARAM lParam)
{
	return 1;
}

// 函数 CMySamPalteDlg::ProcessHoriSrcoll
// 作用：执行ProcessHoriSrcoll。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 Width、CalcCurPixelPos、ScrollColToFixPos、Invalidate、DeflateRect。
void CMySamPalteDlg::ProcessHoriSrcoll(UINT nFlags, CPoint point)
{
	if(m_horiScroll.m_bSliderDragMove)
	{
		int horiShift = point.x - m_horiScroll.m_prePt.x;
		if(m_horiScroll.m_rcSlider.left + horiShift < m_horiScroll.m_rcStartArrow.right)
		{
			int sliderWidth = m_horiScroll.m_rcSlider.Width();
			m_horiScroll.m_rcSlider.left = m_horiScroll.m_rcStartArrow.right;
			m_horiScroll.m_rcSlider.right = m_horiScroll.m_rcSlider.left + sliderWidth;
			if(0 != m_horiScroll.m_curSliderPos)
			{
				m_horiScroll.m_curSliderPos = 0;
				m_horiScroll.CalcCurPixelPos();
				ScrollColToFixPos(m_horiScroll.m_curPixelPos);
				Invalidate(FALSE);
			}
		}
		else if(m_horiScroll.m_rcSlider.right + horiShift > m_horiScroll.m_rcEndArrow.left)
		{
			int sliderWidth = m_horiScroll.m_rcSlider.Width();
			m_horiScroll.m_rcSlider.right = m_horiScroll.m_rcEndArrow.left;
			m_horiScroll.m_rcSlider.left = m_horiScroll.m_rcSlider.right - sliderWidth;

			if(m_horiScroll.m_validScope != m_horiScroll.m_curSliderPos)
			{
				m_horiScroll.m_curSliderPos = m_horiScroll.m_validScope;
				m_horiScroll.CalcCurPixelPos();
				ScrollColToFixPos(m_horiScroll.m_curPixelPos);
				Invalidate(FALSE);
			}
		}
		else
		{
			m_horiScroll.m_rcSlider.DeflateRect(horiShift,0,-horiShift,0);
			m_horiScroll.m_curSliderPos += horiShift;
			m_horiScroll.CalcCurPixelPos();
			ScrollColToFixPos(m_horiScroll.m_curPixelPos);
			Invalidate(FALSE);
		}
	}
	m_horiScroll.m_prePt = point;

	return;
}

// 函数 CMySamPalteDlg::ProcessVertSrcoll
// 作用：执行ProcessVertSrcoll。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 Height、CalcCurPixelPos、ScrollRowToFixPos、Invalidate、DeflateRect。
void CMySamPalteDlg::ProcessVertSrcoll(UINT nFlags, CPoint point)
{
	if(m_vertScroll.m_bSliderDragMove)
	{
		int vertShift = point.y - m_vertScroll.m_prePt.y;
		if(m_vertScroll.m_rcSlider.top + vertShift < m_vertScroll.m_rcStartArrow.bottom)
		{
			int sliderHeight = m_vertScroll.m_rcSlider.Height();
			m_vertScroll.m_rcSlider.top = m_vertScroll.m_rcStartArrow.bottom;
			m_vertScroll.m_rcSlider.bottom = m_vertScroll.m_rcSlider.top + sliderHeight;
			if(0 != m_vertScroll.m_curSliderPos)
			{
				m_vertScroll.m_curSliderPos = 0;
				m_vertScroll.CalcCurPixelPos();
				ScrollRowToFixPos(m_vertScroll.m_curPixelPos);
				Invalidate(FALSE);
			}
		}
		else if(m_vertScroll.m_rcSlider.bottom + vertShift > m_vertScroll.m_rcEndArrow.top)
		{
			int sliderHeight = m_vertScroll.m_rcSlider.Height();
			m_vertScroll.m_rcSlider.bottom = m_vertScroll.m_rcEndArrow.top;
			m_vertScroll.m_rcSlider.top = m_vertScroll.m_rcSlider.bottom - sliderHeight;

			if(m_vertScroll.m_validScope != m_vertScroll.m_curSliderPos)
			{
				m_vertScroll.m_curSliderPos = m_vertScroll.m_validScope;
				m_vertScroll.CalcCurPixelPos();
				ScrollRowToFixPos(m_vertScroll.m_curPixelPos);
				Invalidate(FALSE);
			}
		}
		else
		{
			m_vertScroll.m_rcSlider.DeflateRect(0,vertShift,0,-vertShift);
			m_vertScroll.m_curSliderPos += vertShift;
			m_vertScroll.CalcCurPixelPos();
			ScrollRowToFixPos(m_vertScroll.m_curPixelPos);
			Invalidate(FALSE);
		}
	}
	m_vertScroll.m_prePt = point;

	return;
}

// 函数 CMySamPalteDlg::GetColStartDrawInMemoryHoriPixel
// 作用：读取GetColStartDrawInMemoryHoriPixel。
// 参数：colId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColStartDrawInMemoryHoriPixel(int colId)
{
	if(colId < m_colIdStartShow)
	{
		return -1;
	}

	int horiPixel = 0;
	for(int i = m_colIdStartShow;i < colId;++i)
	{
		horiPixel += m_lnkTitleInfo[i]->m_colWidth;
	}
	return horiPixel;
}

// 函数 CMySamPalteDlg::GetRowStartDrawInMemoryVertPixel
// 作用：读取GetRowStartDrawInMemoryVertPixel。
// 参数：rowId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetRowStartDrawInMemoryVertPixel(int rowId)
{
	if(rowId < m_rowIdStartShow)
	{
		return -1;
	}

	int horiPixel = 0;
	for(int i = m_rowIdStartShow;i < rowId;++i)
	{
		horiPixel += m_lnkRowInfo[i]->m_rowH;
	}
	return horiPixel;
}

// 函数 CMySamPalteDlg::GetWidth
// 作用：读取GetWidth。
// 参数：colStart；colEnd。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetWidth(int colStart,int colEnd)
{
	if(colStart < 0 || colStart >= m_colNum)
	{
		return -1;
	}
	if(colEnd < 0 || colEnd >= m_colNum)
	{
		return -1;
	}

	int width = 0;
	for(int i = colStart;i <= colEnd;++i)
	{
		width += m_lnkTitleInfo[i]->m_colWidth;
	}
	return width;
}

// 函数 CMySamPalteDlg::GetHeight
// 作用：读取GetHeight。
// 参数：rowStart；rowEnd。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetHeight(int rowStart,int rowEnd)
{
	if(rowStart < 0 || rowStart >= m_rowNum)
	{
		return -1;
	}
	if(rowEnd < 0 || rowEnd >= m_rowNum)
	{
		return -1;
	}

	int width = 0;
	for(int i = rowStart;i <= rowEnd;++i)
	{
		width += m_lnkRowInfo[i]->m_rowH;
	}
	return width;
}

// 函数 CMySamPalteDlg::CalcPtRowCol
// 作用：计算CalcPtRowCol。
// 参数：pt。
// 返回：返回 CDotPosInfo。
// 过程：函数里会调用 PtInRect。
CDotPosInfo CMySamPalteDlg::CalcPtRowCol(CPoint pt)
{
	CDotPosInfo dotPosInfo;
	dotPosInfo.m_pt = pt;
	if(!m_rcLst.PtInRect(pt))
	{
		return dotPosInfo;
	}

	if(0 == m_colNum)
	{
		return dotPosInfo;
	}

	//pt在header（标题栏）内
	if(m_rcTotalHeader.PtInRect(pt))
	{
		dotPosInfo.m_eDotPosType = EDT_TOTALHEADER;
	}
	else if(m_rcRowHeader.PtInRect(pt))
	{
		dotPosInfo.m_eDotPosType = EDT_ROWHEADER;
		int sum = m_pxFrame + m_pxColHeaderH + m_lnkRowInfo[m_rowIdStartShow]->m_rowH - m_ssRowTopIndent;
		if(pt.y <= sum)
		{
			dotPosInfo.m_rowId = m_rowIdStartShow;
			return dotPosInfo;
		}
		else
		{
			for(int i = m_rowIdStartShow + 1;i <= m_rowIdEndShow;++i)
			{
				sum += m_lnkRowInfo[i]->m_rowH;
				if(pt.y <= sum)
				{
					dotPosInfo.m_rowId = i;
					return dotPosInfo;
				}
			}
		}
	}
	else if(m_rcColHeader.PtInRect(pt))
	{
		dotPosInfo.m_eDotPosType = EDT_COLHEADER;
		int sum = m_pxFrame + m_pxRowHeaderW + m_lnkTitleInfo[m_colIdStartShow]->m_colWidth - m_ssColLeftIndent;
		if(pt.x <= sum)
		{
			dotPosInfo.m_colId = m_colIdStartShow;
			return dotPosInfo;
		}
		else
		{
			for(int i = m_colIdStartShow + 1;i <= m_colIdEndShow;++i)
			{
				sum += m_lnkTitleInfo[i]->m_colWidth;
				if(pt.x <= sum)
				{
					dotPosInfo.m_colId = i;
					return dotPosInfo;
				}
			}
		}
	}
	else if(m_rcBody.PtInRect(pt) && 0 != m_rowNum)	//pt在body内
	{
		dotPosInfo.m_eDotPosType = EDT_BODY;

		int sum = m_pxFrame + m_pxRowHeaderW + m_lnkTitleInfo[m_colIdStartShow]->m_colWidth - m_ssColLeftIndent;
		if(pt.x <= sum)
		{
			dotPosInfo.m_colId = m_colIdStartShow;
		}
		else
		{
			for(int i = m_colIdStartShow + 1;i <= m_colIdEndShow;++i)
			{
				sum += m_lnkTitleInfo[i]->m_colWidth;
				if(pt.x <= sum)
				{
					dotPosInfo.m_colId = i;
					break;
				}
			}
		}

		sum = m_pxFrame + m_pxColHeaderH + m_lnkRowInfo[m_rowIdStartShow]->m_rowH - m_ssRowTopIndent;
		if(pt.y <= sum)
		{
			dotPosInfo.m_rowId = m_rowIdStartShow;
			return dotPosInfo;
		}
		else
		{
			for(int i = m_rowIdStartShow + 1;i <= m_rowIdEndShow;++i)
			{
				sum += m_lnkRowInfo[i]->m_rowH;
				if(pt.y <= sum)
				{
					dotPosInfo.m_rowId = i;
					return dotPosInfo;
				}
			}
		}
	}
	else if(m_horiScroll.m_bScrollNeedShow && m_horiScroll.m_rcScroll.PtInRect(pt))
	{
		dotPosInfo.m_eDotPosType = EDT_HORISCROLL;
		return dotPosInfo;
	}
	else if(m_vertScroll.m_bScrollNeedShow && m_vertScroll.m_rcScroll.PtInRect(pt))
	{
		dotPosInfo.m_eDotPosType = EDT_VERTSCROLL;
		return dotPosInfo;
	}

	return dotPosInfo;
}

// 函数 CMySamPalteDlg::InsertColumn
// 作用：创建或加入InsertColumn。
// 参数：colId；strColTitle：字符串；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 InsertAtPre、CalcTotalColumnWidth、CalcRowColToShow、Width、CalcScrollPos、GetSafeHwnd。
int CMySamPalteDlg::InsertColumn(int colId,CString strColTitle,BOOL bRedraw /*= TRUE*/)
{
	if(colId < 0)
	{
		return -1;
	}

	if(colId > m_colNum)
	{
		colId = m_colNum;
	}

	CTitleInfo titleInfo;
	titleInfo.m_strTitle = strColTitle;
	int ret = m_lnkTitleInfo.InsertAtPre(colId,titleInfo);
	if(0 == ret)
	{
		++m_colNum;
		if(m_rowNum > 0)
		{
			for(int i = 0;i < m_rowNum;++i)
			{
				m_2LnkCellInfo[i]->InsertAtPre(colId);
			}		
		}

		CalcTotalColumnWidth();
		CalcRowColToShow();

		//更新水平滚动条当前位置
		if(m_totalColW > m_rcBody.Width())
		{
			m_horiScroll.m_curPixelPos = 0;
			for(int i = 0;i < m_colIdStartShow;++i)
			{
				m_horiScroll.m_curPixelPos += m_lnkTitleInfo[i]->m_colWidth;
			}
			if(-1 != m_colIdStartShow)
			{
				m_horiScroll.m_curPixelPos += m_ssColLeftIndent;
			}
		}
		else
		{
			m_horiScroll.m_curPixelPos = 0;
		}
		CalcScrollPos();

		if(bRedraw && NULL != GetSafeHwnd())
		{
			Invalidate(FALSE);
		}
		return 0;
	}
	else
	{
		return -2;
	}
}

// 函数 CMySamPalteDlg::InsertRow
// 作用：创建或加入InsertRow。
// 参数：rowId；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 InsertAtPre、GetBeEditable、AddTail、CalcTotalRowHeight、CalcRowColToShow、Height。
int CMySamPalteDlg::InsertRow(int rowId,BOOL bRedraw /*= TRUE*/)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId > m_rowNum)
	{
		rowId = m_rowNum;
	}

	m_2LnkCellInfo.InsertAtPre(rowId);
	m_lnkRowInfo.InsertAtPre(rowId);
	++m_rowNum;

	for(int i = 0;i < m_colNum;++i)
	{
		CCellInfo cellInfo;
		CTitleInfo* pTitleInfo = m_lnkTitleInfo[i];
		if(pTitleInfo->GetBeEditable())
		{
			cellInfo.m_bEditable = TRUE;
			cellInfo.m_maxMinInfo = pTitleInfo->m_maxMinInfo;
		}
		else if(pTitleInfo->m_bCbtable)
		{
			cellInfo.m_bCbAble = TRUE;
		}
		m_2LnkCellInfo[rowId]->AddTail(cellInfo);
	}

	CalcTotalRowHeight();
	CalcRowColToShow();

	//更新垂直滚动条当前位置
	if(m_totalRowH > m_rcBody.Height())
	{
		m_vertScroll.m_curPixelPos = 0;
		for(int i = 0;i < m_rowIdStartShow;++i)
		{
			m_vertScroll.m_curPixelPos += m_lnkRowInfo[i]->m_rowH;
		}
		if(-1 != m_rowIdStartShow)
		{
			m_vertScroll.m_curPixelPos += m_ssRowTopIndent;
		}
	}
	else
	{
		m_vertScroll.m_curPixelPos = 0;
	}
	CalcScrollPos();

	//设置最大最小值限制信息
	for(int i = 0;i < m_colNum;++i)
	{
		m_2LnkCellInfo[rowId]->GetAt(i)->data.m_maxMinInfo = m_lnkTitleInfo[i]->m_maxMinInfo;
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::DeleteColumn
// 作用：更新或清除DeleteColumn。
// 参数：colId；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHead、DeleteAt、CalcTotalColumnWidth、CalcColToShow、Width、CalcScrollPos。
int CMySamPalteDlg::DeleteColumn(int colId,BOOL bRedraw /*= TRUE*/)
{
	if(colId < 0)
	{
		return -1;
	}
	if(colId >= m_colNum)
	{
		return -2;
	}

	int colW = m_lnkTitleInfo[colId]->m_colWidth;

	Node<CLinkList<CCellInfo>>* pNode = m_2LnkCellInfo.GetHead();
	while(NULL != pNode)
	{
		pNode->data.DeleteAt(colId);
		pNode = pNode->pNext;
	}
	m_lnkTitleInfo.DeleteAt(colId);
	--m_colNum;

	CalcTotalColumnWidth();

	if(colId < m_colIdStartShow)
	{
		CalcColToShow(m_colIdStartShow - 1);
	}
	else
	{
		CalcColToShow(m_colIdStartShow);
	}

	//更新水平滚动条当前位置
	if(m_totalColW > m_rcBody.Width())
	{
		m_horiScroll.m_curPixelPos = 0;
		for(int i = 0;i < m_colIdStartShow;++i)
		{
			m_horiScroll.m_curPixelPos += m_lnkTitleInfo[i]->m_colWidth;
		}
		if(-1 != m_colIdStartShow)
		{
			m_horiScroll.m_curPixelPos += m_ssColLeftIndent;
		}
	}
	else
	{
		m_horiScroll.m_curPixelPos = 0;
	}
	CalcScrollPos();

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::DeleteRow
// 作用：更新或清除DeleteRow。
// 参数：rowId；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 DeleteAt、CalcTotalRowHeight、CalcRowToShow、Height、CalcScrollPos、GetSafeHwnd。
int CMySamPalteDlg::DeleteRow(int rowId,BOOL bRedraw /*= TRUE*/)
{
	if(rowId < 0)
	{
		return -1;
	}
	if(rowId >= m_rowNum)
	{
		return -2;
	}

	int rowH = m_lnkRowInfo[rowId]->m_rowH;

	m_2LnkCellInfo.DeleteAt(rowId);
	m_lnkRowInfo.DeleteAt(rowId);
	--m_rowNum;

	CalcTotalRowHeight();

	if(rowId < m_rowIdStartShow)
	{
		CalcRowToShow(m_rowIdStartShow - 1);
	}
	else
	{
		CalcRowToShow(m_rowIdStartShow);
	}
	
	//更新垂直滚动条当前位置
	if(m_totalRowH > m_rcBody.Height())
	{
		m_vertScroll.m_curPixelPos = 0;
		for(int i = 0;i < m_rowIdStartShow;++i)
		{
			m_vertScroll.m_curPixelPos += m_lnkRowInfo[i]->m_rowH;
		}
		if(-1 != m_rowIdStartShow)
		{
			m_vertScroll.m_curPixelPos += m_ssRowTopIndent;
		}
	}
	else
	{
		m_vertScroll.m_curPixelPos = 0;
	}
	CalcScrollPos();

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::DeleteMultiRow
// 作用：更新或清除DeleteMultiRow。
// 参数：vecSelectedRow；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size、DeleteAt、CalcTotalRowHeight、Height、CalcScrollPos、CalcRowToShow。
int CMySamPalteDlg::DeleteMultiRow(vector<int> vecSelectedRow,BOOL bRedraw /*= TRUE*/)
{
	if(vecSelectedRow.size() < 1)
	{
		return -1;
	}

	int rowH = 0;
	int fstDeleteRowId = vecSelectedRow[0];

	for(int i = vecSelectedRow.size() - 1;i >= 0;--i)
	{
		if(vecSelectedRow[i] >= 0 && vecSelectedRow[i] < m_rowNum)
		{
			rowH += m_lnkRowInfo[vecSelectedRow[i]]->m_rowH;
			m_2LnkCellInfo.DeleteAt(vecSelectedRow[i]);
			m_lnkRowInfo.DeleteAt(vecSelectedRow[i]);
			--m_rowNum;
		}
	}
	
	CalcTotalRowHeight();

	//更新垂直滚动条当前位置
	if(m_totalRowH > m_rcBody.Height())
	{
		m_vertScroll.m_curPixelPos -= rowH;
		if(m_vertScroll.m_curPixelPos < 0)
		{
			m_vertScroll.m_curPixelPos = 0;
		}
	}
	else
	{
		m_vertScroll.m_curPixelPos = 0;
	}

	CalcScrollPos();

	if(fstDeleteRowId < m_rowIdStartShow)
	{
		CalcRowToShow(m_rowIdStartShow - 1);
	}
	else
	{
		CalcRowToShow(m_rowIdStartShow);
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::DeleteData
// 作用：更新或清除DeleteData。
// 参数：bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetHead、GetSafeHwnd、Invalidate。
void CMySamPalteDlg::DeleteData(BOOL bRedraw /*= FALSE*/)
{
	Node<CLinkList<CCellInfo>>* pNode = m_2LnkCellInfo.GetHead();
	while(NULL != pNode)
	{
		Node<CCellInfo>* pNodeCellInfo = pNode->data.GetHead();
		while(NULL != pNodeCellInfo)
		{
			pNodeCellInfo->data.DeleteData();
			pNodeCellInfo = pNodeCellInfo->pNext;
		}
		pNode = pNode->pNext;
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::Clear
// 作用：更新或清除Clear。
// 参数：bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 CalcTotalRowHeight、CalcScrollPos、GetSafeHwnd、Invalidate。
void CMySamPalteDlg::Clear(BOOL bRedraw /*= FALSE*/)
{
	m_2LnkCellInfo.Clear();
	m_lnkRowInfo.Clear();
	m_rowNum = 0;

	CalcTotalRowHeight();

	//更新垂直滚动条当前位置
	m_vertScroll.m_curPixelPos = 0;
	CalcScrollPos();

	m_rowIdStartShow = -1;
	m_rowIdEndShow = -1;
	m_ssRowTopIndent = 0;
	m_esRowBottomIndent = 0;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetSelectedRowId
// 作用：读取GetSelectedRowId。
// 参数：无。
// 返回：返回 vector<int>。
// 过程：函数里会调用 clear、push_back。
vector<int> CMySamPalteDlg::GetSelectedRowId()
{
	vector<int> vecSeletedRow;
	vecSeletedRow.clear();
	if(m_rowNum <= 0)
	{
		return vecSeletedRow;
	}

	for(int i = 0;i < m_rowNum;++i)
	{
		if(m_lnkRowInfo[i]->m_bSelected)
		{
			vecSeletedRow.push_back(i);
		}
	}

	return vecSeletedRow;
}

// 函数 CMySamPalteDlg::SetColumnTitleInfo
// 作用：设置SetColumnTitleInfo。
// 参数：colId；titleInfo；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetColumnTitleInfo(int colId,CTitleInfo titleInfo,BOOL bRedraw /*= TRUE*/)
{
	if(colId >= m_colNum)
	{
		return -1;
	}

	if(colId < 0)
	{
		return -2;
	}

	*(m_lnkTitleInfo[colId]) = titleInfo;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetColumnTitleInfo
// 作用：读取GetColumnTitleInfo。
// 参数：colId；titleInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColumnTitleInfo(int colId,CTitleInfo& titleInfo)
{
	if(colId >= m_colNum)
	{
		return -1;
	}

	if(colId < 0)
	{
		return -2;
	}

	titleInfo = *(m_lnkTitleInfo[colId]);
	return 0;
}

// 函数 CMySamPalteDlg::SetColumnCheckFunc
// 作用：设置SetColumnCheckFunc。
// 参数：colId；bHaveCheckFunc：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetColumnCheckFunc(int colId,BOOL bHaveCheckFunc,BOOL bRedraw /*= FALSE*/)
{
	if(colId >= m_colNum)
	{
		return -1;
	}

	if(colId < 0)
	{
		return -2;
	}

	m_lnkTitleInfo[colId]->m_bCheckFunc = bHaveCheckFunc;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetColumnCheckFunc
// 作用：读取GetColumnCheckFunc。
// 参数：colId；bHaveCheckFunc：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColumnCheckFunc(int colId,BOOL& bHaveCheckFunc)
{
	if(colId >= m_colNum)
	{
		return -1;
	}

	if(colId < 0)
	{
		return -2;
	}

	bHaveCheckFunc = m_lnkTitleInfo[colId]->m_bCheckFunc;
	return 0;
}

// 函数 CMySamPalteDlg::SetColumnColorFunc
// 作用：设置SetColumnColorFunc。
// 参数：colId；bHaveColorFunc：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetColumnColorFunc(int colId,BOOL bHaveColorFunc,BOOL bRedraw /*= FALSE*/)
{
	if(colId >= m_colNum)
	{
		return -1;
	}

	if(colId < 0)
	{
		return -2;
	}

	m_lnkTitleInfo[colId]->m_bColorFunc = bHaveColorFunc;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetColumnColorFunc
// 作用：读取GetColumnColorFunc。
// 参数：colId；bHaveColorFunc：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColumnColorFunc(int colId,BOOL& bHaveColorFunc)
{
	if(colId >= m_colNum)
	{
		return -1;
	}

	if(colId < 0)
	{
		return -2;
	}

	bHaveColorFunc = m_lnkTitleInfo[colId]->m_bColorFunc;
	return 0;
}

// 函数 CMySamPalteDlg::SetColumnWidth
// 作用：设置SetColumnWidth。
// 参数：colId；colWidth；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CalcTotalColumnWidth、CalcScrollPos、CalcRowColToShow、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetColumnWidth(int colId,int colWidth,BOOL bRedraw /*= FALSE*/)
{
	if(colId < 0)
	{
		return -1;
	}

	if(colId >= m_colNum)
	{
		return -2;
	}

	CTitleInfo* pTitleInfo = m_lnkTitleInfo[colId];
	if(NULL == pTitleInfo)
	{
		return -3;
	}
	pTitleInfo->m_colWidth = colWidth;

	CalcTotalColumnWidth();
	CalcScrollPos();
	CalcRowColToShow();
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	
	return 0;
}

// 函数 CMySamPalteDlg::GetColumnWidth
// 作用：读取GetColumnWidth。
// 参数：colId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColumnWidth(int colId)
{
	if(colId < 0)
	{
		return -1;
	}

	if(colId >= m_colNum)
	{
		return -1;
	}

	CTitleInfo* pTitleInfo = m_lnkTitleInfo[colId];
	if(NULL == pTitleInfo)
	{
		return -3;
	}
	return pTitleInfo->m_colWidth;
}

// 函数 CMySamPalteDlg::SetItemHeight
// 作用：设置SetItemHeight。
// 参数：itemH；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetItemHeight(int itemH,BOOL bRedraw /*= FALSE*/)
{
	m_pxRowH = itemH;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetItemHeight
// 作用：读取GetItemHeight。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetItemHeight()
{
	return m_pxRowH;
}

// 函数 CMySamPalteDlg::SetFixedRowHeightColumnWidth
// 作用：设置SetFixedRowHeightColumnWidth。
// 参数：iRowH：整数；iColW：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetFixedRowHeightColumnWidth(int iRowH,int iColW,BOOL bRedraw /*= FALSE*/)
{
	m_pxRowH = iRowH;
	m_pxColW = iColW;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetFixedRowHeightColumnWidth
// 作用：读取GetFixedRowHeightColumnWidth。
// 参数：iRowH：整数；iColW：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetFixedRowHeightColumnWidth(int& iRowH,int& iColW)
{
	iRowH = m_pxRowH;
	iColW = m_pxColW;
	return 0;
}

// 函数 CMySamPalteDlg::SetColumnText
// 作用：设置SetColumnText。
// 参数：colId；strColTitle：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::SetColumnText(int colId,CString strColTitle)
{
	if(colId < 0)
	{
		return -1;
	}
	if(colId >= m_colNum)
	{
		return -2;
	}
	(*(m_lnkTitleInfo[colId])).m_strTitle = strColTitle;
	return 0;
}

// 函数 CMySamPalteDlg::GetColumnText
// 作用：读取GetColumnText。
// 参数：colId。
// 返回：返回一段文字。
// 过程：函数里会调用 _T。
CString CMySamPalteDlg::GetColumnText(int colId)
{
	if(colId < 0)
	{
		return _T("");
	}
	if(colId >= m_colNum)
	{
		return _T("");
	}
	return (*(m_lnkTitleInfo[colId])).m_strTitle;
}

// 函数 CMySamPalteDlg::SetColumnMaxMinInfo
// 作用：设置SetColumnMaxMinInfo。
// 参数：colId；maxMinInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt。
int CMySamPalteDlg::SetColumnMaxMinInfo(int colId,CMaxMinInfo maxMinInfo)
{
	if(colId < 0)
	{
		return -1;
	}
	if(colId >= m_colNum)
	{
		return -2;
	}

	m_lnkTitleInfo[colId]->m_maxMinInfo = maxMinInfo;

	for(int i = 0;i < m_rowNum;++i)
	{
		m_2LnkCellInfo[i]->GetAt(colId)->data.m_maxMinInfo = maxMinInfo;
	}

	return 0;
}

// 函数 CMySamPalteDlg::GetColumnMaxMinInfo
// 作用：读取GetColumnMaxMinInfo。
// 参数：colId；maxMinInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColumnMaxMinInfo(int colId,CMaxMinInfo& maxMinInfo)
{
	if(colId < 0)
	{
		return -1;
	}
	if(colId >= m_colNum)
	{
		return -2;
	}

	maxMinInfo = m_lnkTitleInfo[colId]->m_maxMinInfo;
	return 0;
}

// 函数 CMySamPalteDlg::SetItemText
// 作用：设置SetItemText。
// 参数：rowId；colId；strText：字符串；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetItemText(int rowId,int colId,CString strText,BOOL bRedraw /*= FALSE*/)
{
	if(colId < 0)
	{
		return -1;
	}
	if(colId >= m_colNum)
	{
		return -2;
	}
	if(rowId < 0)
	{
		return -3;
	}
	if(rowId >= m_rowNum)
	{
		return -4;
	}

	(*m_2LnkCellInfo[rowId])[colId]->SetItemText(strText);

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetItemText
// 作用：读取GetItemText。
// 参数：rowId；colId。
// 返回：返回一段文字。
// 过程：函数里会调用 _T。
CString CMySamPalteDlg::GetItemText(int rowId,int colId)
{
	if(colId < 0)
	{
		return _T("");
	}
	if(colId >= m_colNum)
	{
		return _T("");
	}
	if(rowId < 0)
	{
		return _T("");
	}
	if(rowId >= m_rowNum)
	{
		return _T("");
	}

	return (*m_2LnkCellInfo[rowId])[colId]->GetItemText();
}

// 函数 CMySamPalteDlg::SetRowSelectState
// 作用：设置SetRowSelectState。
// 参数：rowId；bSelected：是或否；bSingleSel：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHead、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetRowSelectState(int rowId,BOOL bSelected,BOOL bSingleSel /*= FALSE*/,BOOL bRedraw /*= FALSE*/)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	if(bSelected && bSingleSel)
	{
		Node<CRowInfo>* pNode = m_lnkRowInfo.GetHead();
		while(NULL != pNode)
		{
			pNode->data.m_bSelected = FALSE;
			pNode = pNode->pNext;
		}
	}

	m_lnkRowInfo[rowId]->m_bSelected = bSelected;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetRowSelectState
// 作用：读取GetRowSelectState。
// 参数：rowId；bSelected：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetRowSelectState(int rowId,BOOL& bSelected)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	bSelected = m_lnkRowInfo[rowId]->m_bSelected;
	return 0;
}

// 函数 CMySamPalteDlg::SetRowDisableState
// 作用：设置SetRowDisableState。
// 参数：rowId；bDisabled：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetRowDisableState(int rowId,BOOL bDisabled,BOOL bRedraw /*= FALSE*/)
{
	if(rowId < 0)
	{
		return -1;
	}
	if(rowId >= m_rowNum)
	{
		return -2;
	}
	m_lnkRowInfo[rowId]->m_bDisabled = bDisabled;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetRowDisableState
// 作用：读取GetRowDisableState。
// 参数：rowId；bDisabled：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetRowDisableState(int rowId,BOOL& bDisabled)
{
	if(rowId < 0)
	{
		return -1;
	}
	if(rowId >= m_rowNum)
	{
		return -2;
	}
	bDisabled = m_lnkRowInfo[rowId]->m_bDisabled;
	return 0;
}

// 函数 CMySamPalteDlg::SetCellCheckState
// 作用：设置SetCellCheckState。
// 参数：rowId；colId；bChecked：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt、SetItemCheckState、GetSafeHwnd、Invalidate、strText、_T。
int CMySamPalteDlg::SetCellCheckState(int rowId,int colId,BOOL bChecked,BOOL bRedraw /*= FALSE*/)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	if(colId < 0)
	{
		return -3;
	}

	if(colId >= m_colNum)
	{
		return -4;
	}

	if(!m_lnkTitleInfo[colId]->m_bCheckFunc)
	{
		return -5;
	}

	m_2LnkCellInfo[rowId]->GetAt(colId)->data.SetItemCheckState(bChecked);
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	CString strText(_T("FALSE"));
	if(bChecked)
	{
		strText = _T("TRUE");
	}
	
	return 0;
}

// 函数 CMySamPalteDlg::GetCellCheckState
// 作用：读取GetCellCheckState。
// 参数：rowId；colId；bChecked：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt、GetItemCheckState。
int CMySamPalteDlg::GetCellCheckState(int rowId,int colId,BOOL& bChecked)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	if(colId < 0)
	{
		return -3;
	}

	if(colId >= m_colNum)
	{
		return -4;
	}

	if(!m_lnkTitleInfo[colId]->m_bCheckFunc)
	{
		return -5;
	}

	bChecked = m_2LnkCellInfo[rowId]->GetAt(colId)->data.GetItemCheckState();
	return 0;
}

// 函数 CMySamPalteDlg::SetCellDisableState
// 作用：设置SetCellDisableState。
// 参数：rowId；colId；bDisabled：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetCellDisableState(int rowId,int colId,BOOL bDisabled,BOOL bRedraw /*= FALSE*/)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	if(colId < 0)
	{
		return -3;
	}

	if(colId >= m_colNum)
	{
		return -4;
	}

	m_2LnkCellInfo[rowId]->GetAt(colId)->data.m_bDisabled = bDisabled;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetCellDisableState
// 作用：读取GetCellDisableState。
// 参数：rowId；colId；bDisabled：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt。
int CMySamPalteDlg::GetCellDisableState(int rowId,int colId,BOOL& bDisabled)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	if(colId < 0)
	{
		return -3;
	}

	if(colId >= m_colNum)
	{
		return -4;
	}

	bDisabled = m_2LnkCellInfo[rowId]->GetAt(colId)->data.m_bDisabled;
	return 0;
}

// 函数 CMySamPalteDlg::SetCellSelfCbInfo
// 作用：设置SetCellSelfCbInfo。
// 参数：rowId；colId；bCbable：是或否；bUseCellLnkCbStr：是或否；lnkCbStr；bEditableCb：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetCellSelfCbInfo(int rowId,int colId,BOOL bCbable,BOOL bUseCellLnkCbStr,CLinkList<CString>& lnkCbStr,BOOL bEditableCb,BOOL bRedraw /*= FALSE*/)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	if(colId < 0)
	{
		return -3;
	}

	if(colId >= m_colNum)
	{
		return -4;
	}

	CCellInfo& cellInfo = m_2LnkCellInfo[rowId]->GetAt(colId)->data;
	cellInfo.m_bCbAble = bCbable;
	cellInfo.m_bUseCellLnkCbStr = bUseCellLnkCbStr;
	cellInfo.m_lnkCbStr = lnkCbStr;
	cellInfo.m_bEditableCb = bEditableCb;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetCellSelfCbInfo
// 作用：读取GetCellSelfCbInfo。
// 参数：rowId；colId；bCbable：是或否；bUseCellLnkCbStr：是或否；lnkCbStr；bEditableCb：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt。
int CMySamPalteDlg::GetCellSelfCbInfo(int rowId,int colId,BOOL& bCbable,BOOL& bUseCellLnkCbStr,CLinkList<CString>& lnkCbStr,BOOL& bEditableCb)
{
	if(rowId < 0)
	{
		return -1;
	}

	if(rowId >= m_rowNum)
	{
		return -2;
	}

	if(colId < 0)
	{
		return -3;
	}

	if(colId >= m_colNum)
	{
		return -4;
	}

	CCellInfo& cellInfo = m_2LnkCellInfo[rowId]->GetAt(colId)->data;
	bCbable = cellInfo.m_bCbAble;
	bUseCellLnkCbStr = cellInfo.m_bUseCellLnkCbStr;
	lnkCbStr = cellInfo.m_lnkCbStr;
	bEditableCb = cellInfo.m_bEditableCb;
	return 0;
}

// 函数 CMySamPalteDlg::GetRowNum
// 作用：读取GetRowNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetRowNum()
{
	return m_rowNum;
}

// 函数 CMySamPalteDlg::GetColNum
// 作用：读取GetColNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColNum()
{
	return m_colNum;
}

// 函数 CMySamPalteDlg::SetBeGradientHeader
// 作用：设置SetBeGradientHeader。
// 参数：bGradientHeader：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBeGradientHeader(BOOL bGradientHeader,BOOL bRedraw /*= FALSE*/)
{
	m_bGradientHeader = bGradientHeader;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBeGradientHeader
// 作用：读取GetBeGradientHeader。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeGradientHeader()
{
	return m_bGradientHeader;
}

// 函数 CMySamPalteDlg::SetBkColor
// 作用：设置SetBkColor。
// 参数：bkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBkColor(COLORREF bkClr,BOOL bRedraw /*= FALSE*/)
{
	m_clrBk = bkClr;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBkColor
// 作用：读取GetBkColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMySamPalteDlg::GetBkColor()
{
	return m_clrBk;
}

// 函数 CMySamPalteDlg::SetHeaderBkColor
// 作用：设置SetHeaderBkColor。
// 参数：headerBkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetHeaderBkColor(COLORREF headerBkClr,BOOL bRedraw /*= FALSE*/)
{
	m_clrHeaderBk = headerBkClr;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetHeaderBkColor
// 作用：读取GetHeaderBkColor。
// 参数：无。
// 返回：返回 Color。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
Color CMySamPalteDlg::GetHeaderBkColor()
{
	return m_clrHeaderBk;
}

// 函数 CMySamPalteDlg::SetBodyBkColor
// 作用：设置SetBodyBkColor。
// 参数：bodyBkClr；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBodyBkColor(COLORREF bodyBkClr,BOOL bRedraw /*= FALSE*/)
{
	m_clrBodyBk = bodyBkClr;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBodyBkColor
// 作用：读取GetBodyBkColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMySamPalteDlg::GetBodyBkColor()
{
	return m_clrBodyBk;
}

// 函数 CMySamPalteDlg::SetRowHeaderWidth
// 作用：设置SetRowHeaderWidth。
// 参数：iRowW：整数；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetRowHeaderWidth(int iRowW,BOOL bRedraw /*= FALSE*/)
{
	m_pxRowHeaderW = iRowW;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetRowHeaderWidth
// 作用：读取GetRowHeaderWidth。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetRowHeaderWidth()
{
	return m_pxRowHeaderW;
}

// 函数 CMySamPalteDlg::SetColumnHeaderHeight
// 作用：设置SetColumnHeaderHeight。
// 参数：iColH：整数；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetColumnHeaderHeight(int iColH,BOOL bRedraw /*= FALSE*/)
{
	m_pxColHeaderH = iColH;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetColumnHeaderHeight
// 作用：读取GetColumnHeaderHeight。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetColumnHeaderHeight()
{
	return m_pxColHeaderH;
}

// 函数 CMySamPalteDlg::SetFrameLineWidth
// 作用：设置SetFrameLineWidth。
// 参数：frameLineWidth；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetFrameLineWidth(int frameLineWidth,BOOL bRedraw /*= FALSE*/)
{
	m_pxFrame = frameLineWidth;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetFrameLineWidth
// 作用：读取GetFrameLineWidth。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetFrameLineWidth()
{
	return m_pxFrame;
}

// 函数 CMySamPalteDlg::SetFrameLineColor
// 作用：设置SetFrameLineColor。
// 参数：frameLineColor：颜色；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetFrameLineColor(COLORREF frameLineColor,BOOL bRedraw /*= FALSE*/)
{
	m_clrFrame = frameLineColor;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetFrameLineColor
// 作用：读取GetFrameLineColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMySamPalteDlg::GetFrameLineColor()
{
	return m_clrFrame;
}

// 函数 CMySamPalteDlg::SetRowColLineWidth
// 作用：设置SetRowColLineWidth。
// 参数：rowColLineWidth；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetRowColLineWidth(int rowColLineWidth,BOOL bRedraw /*= FALSE*/)
{
	m_pxRowColLine = rowColLineWidth;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetRowColLineWidth
// 作用：读取GetRowColLineWidth。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetRowColLineWidth()
{
	return m_pxRowColLine;
}


// 函数 CMySamPalteDlg::SetRowColLineColor
// 作用：设置SetRowColLineColor。
// 参数：rowColLineColor：颜色；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetRowColLineColor(COLORREF rowColLineColor,BOOL bRedraw /*= FALSE*/)
{
	m_clrRowColLine = rowColLineColor;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetRowColLineColor
// 作用：读取GetRowColLineColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMySamPalteDlg::GetRowColLineColor()
{
	return m_clrRowColLine;
}

// 函数 CMySamPalteDlg::SetBeShowFrameLine
// 作用：设置SetBeShowFrameLine。
// 参数：bShowFrameLine：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBeShowFrameLine(int bShowFrameLine,BOOL bRedraw /*= FALSE*/)
{
	m_bShowFrameLine = bShowFrameLine;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBeShowFrameLine
// 作用：读取GetBeShowFrameLine。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeShowFrameLine()
{
	return m_bShowFrameLine;
}

// 函数 CMySamPalteDlg::SetBeShowRowColLine
// 作用：设置SetBeShowRowColLine。
// 参数：bShowRowColLine：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBeShowRowColLine(int bShowRowColLine,BOOL bRedraw /*= FALSE*/)
{
	m_bShowRowColLine = bShowRowColLine;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBeShowRowColLine
// 作用：读取GetBeShowRowColLine。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeShowRowColLine()
{
	return m_bShowRowColLine;
}

// 函数 CMySamPalteDlg::SetHeaderTextColor
// 作用：设置SetHeaderTextColor。
// 参数：headTextColor：颜色；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetHeaderTextColor(COLORREF headTextColor,BOOL bRedraw /*= FALSE*/)
{
	m_clrHeaderText = headTextColor;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetHeaderTextColor
// 作用：读取GetHeaderTextColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMySamPalteDlg::GetHeaderTextColor()
{
	return m_clrHeaderText;
}

// 函数 CMySamPalteDlg::SetBeSingleSelect
// 作用：设置SetBeSingleSelect。
// 参数：bSingleSelect：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSelectedRowId、size、SetRowSelectState、GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBeSingleSelect(BOOL bSingleSelect,BOOL bRedraw /*= FALSE*/)
{
	m_bSingleSelect = bSingleSelect;

	vector<int> vecSelectedRow = GetSelectedRowId();	//如果有多行被选中，设置第一行选中
	for(int i = 1;i < vecSelectedRow.size();++i)
	{
		SetRowSelectState(vecSelectedRow[i],FALSE);
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBeSingleSelect
// 作用：读取GetBeSingleSelect。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeSingleSelect()
{
	return m_bSingleSelect;
}

// 函数 CMySamPalteDlg::SetTitle
// 作用：设置SetTitle。
// 参数：strTitle：字符串；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetTitle(CString strTitle,BOOL bRedraw /*= FALSE*/)
{
	m_strTotalTitle = strTitle;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetTitle
// 作用：读取GetTitle。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CMySamPalteDlg::GetTitle()
{
	return m_strTotalTitle;
}

// 函数 CMySamPalteDlg::SetBeEditable
// 作用：设置SetBeEditable。
// 参数：bEditable：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBeEditable(BOOL bEditable,BOOL bRedraw /*= FALSE*/)
{
	m_bEditable = bEditable;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBeEditable
// 作用：读取GetBeEditable。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeEditable()
{
	return m_bEditable;
}

// 函数 CMySamPalteDlg::GetRowTag
// 作用：读取GetRowTag。
// 参数：iRowId：整数；strTag：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Format、_T。
int CMySamPalteDlg::GetRowTag(int iRowId,CString& strTag)
{
	if(iRowId < 0)
	{
		return -1;
	}
	if(iRowId >= m_rowNum)
	{
		return -2;
	}
	strTag.Format(_T("%c"),'A' + iRowId);
	return 0;
}

// 函数 CMySamPalteDlg::GetColTag
// 作用：读取GetColTag。
// 参数：iColId：整数；strTag：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Format、_T。
int CMySamPalteDlg::GetColTag(int iColId,CString& strTag)
{
	if(iColId < 0)
	{
		return -1;
	}
	if(iColId >= m_colNum)
	{
		return -2;
	}
	strTag.Format(_T("%d"),iColId + 1);
	return 0;
}

// 函数 CMySamPalteDlg::GetSiteTag
// 作用：读取GetSiteTag。
// 参数：iSiteIndex：整数；strTag：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Format、_T。
int CMySamPalteDlg::GetSiteTag(int iSiteIndex,CString& strTag)
{
	if(iSiteIndex < 0)
	{
		return -1;
	}
	if(iSiteIndex >= m_iTotalSiteNum)
	{
		return -2;
	}
	if(m_rowNum < 1)
	{
		return -3;
	}
	if(m_colNum < 1)
	{
		return -4;
	}

	strTag.Format(_T("%c%d"),'A' + iSiteIndex / m_colNum,iSiteIndex % m_colNum + 1);
	return 0;
}

// 函数 CMySamPalteDlg::GetSiteTag
// 作用：读取GetSiteTag。
// 参数：iRowId：整数；iColId：整数；strTag：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Format、_T。
int CMySamPalteDlg::GetSiteTag(int iRowId,int iColId,CString& strTag)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(iRowId < 0)
	{
		return -3;
	}
	if(iRowId >= m_rowNum)
	{
		return -4;
	}
	if(iColId < 0)
	{
		return -5;
	}
	if(iColId >= m_colNum)
	{
		return -6;
	}
	strTag.Format(_T("%c%d"),'A' + iRowId,iColId + 1);
	return 0;
}

// 函数 CMySamPalteDlg::SetRowColNum
// 作用：设置SetRowColNum。
// 参数：iRowNum：整数；iColNum：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Width、Height、MyMulitDeletePtr、Clear、AddTail、CalcTotalColumnWidth。
int CMySamPalteDlg::SetRowColNum(int iRowNum,int iColNum,BOOL bRedraw /*= FALSE*/)
{
	if(iRowNum < 1)
	{
		return -1;
	}
	if(iColNum < 1)
	{
		return -2;
	}

	if(m_rowNum == iRowNum && m_colNum == iColNum)
	{
		return 1;
	}

	//重新计算行高和列宽
	m_pxColW = m_rcBody.Width() / iColNum;
	int iColRemainder = m_rcBody.Width() % iColNum;

	m_pxRowH = m_rcBody.Height() / iRowNum;
	int iRowRemainder = m_rcBody.Height() % iRowNum;

	MyMulitDeletePtr(&m_pTubeInfo);
	MyMulitDeletePtr(&m_pPlateInfo);

	m_lnkTitleInfo.Clear();
	m_lnkRowInfo.Clear();
	m_2LnkCellInfo.Clear();

	CTitleInfo titleInfo;
	titleInfo.m_colWidth = m_pxColW;
	for(int i = 0;i < iColNum;++i)
	{
		if(i == iColNum - 1)
		{
			titleInfo.m_colWidth += iColRemainder;
		}
		m_lnkTitleInfo.AddTail(titleInfo);
	}
	CRowInfo rowInfo;
	rowInfo.m_rowH = m_pxRowH;
	for(int i = 0;i < iRowNum;++i)
	{
		if(i == iRowNum - 1)
		{
			rowInfo.m_rowH += iRowRemainder;
		}
		m_lnkRowInfo.AddTail(rowInfo);
	}

	m_iTotalSiteNum = iRowNum * iColNum;
	m_pTubeInfo = new CTubeInfo[m_iTotalSiteNum];
	if(NULL == m_pTubeInfo)
	{
		return -3;
	}

	m_pPlateInfo = new CPlateInfo[m_iTotalSiteNum];
	if(NULL == m_pPlateInfo)
	{
		MyMulitDeletePtr(&m_pTubeInfo);
		return -4;
	}

	m_rowNum = iRowNum;
	m_colNum = iColNum;

	CalcTotalColumnWidth();
	CalcRowColToShow();

	//更新水平滚动条当前位置
	if(m_totalColW > m_rcBody.Width())
	{
		m_horiScroll.m_curPixelPos = 0;
		for(int i = 0;i < m_colIdStartShow;++i)
		{
			m_horiScroll.m_curPixelPos += m_lnkTitleInfo[i]->m_colWidth;
		}
		if(-1 != m_colIdStartShow)
		{
			m_horiScroll.m_curPixelPos += m_ssColLeftIndent;
		}
	}
	else
	{
		m_horiScroll.m_curPixelPos = 0;
	}
	CalcScrollPos();

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetBeValidPlate
// 作用：读取GetBeValidPlate。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSize。
BOOL CMySamPalteDlg::GetBeValidPlate()
{
	if(m_rowNum < 1 || m_colNum < 1 || m_iTotalSiteNum < 1 || NULL == m_pTubeInfo || NULL == m_pPlateInfo || m_lnkRowInfo.GetSize() != m_rowNum || m_lnkTitleInfo.GetSize() != m_colNum)
	{
		return FALSE;
	}
	return TRUE;
}

// 函数 CMySamPalteDlg::UpdateRowSelectState
// 作用：更新或清除UpdateRowSelectState。
// 参数：iRowId：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::UpdateRowSelectState(int iRowId,BOOL bRedraw)
{
	if(iRowId < 0)
	{
		return -1;
	}
	if(iRowId >= m_rowNum)
	{
		return -2;
	}
	if(NULL == m_pPlateInfo)
	{
		return -3;
	}
	if(iRowId >= m_lnkRowInfo.GetSize())
	{
		return -4;
	}
	
	BOOL bSelected = TRUE;
	int iStart = iRowId * m_colNum,iEnd = iStart + m_colNum;
	for(int i = iStart;i < iEnd;++i)
	{
		if(!m_pPlateInfo[i].m_bSelected)
		{
			bSelected = FALSE;
			break;
		}
	}

	m_lnkRowInfo[iRowId]->m_bSelected = bSelected;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::UpdateColSelectState
// 作用：更新或清除UpdateColSelectState。
// 参数：iColId：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::UpdateColSelectState(int iColId,BOOL bRedraw)
{
	if(iColId < 0)
	{
		return -1;
	}
	if(iColId >= m_colNum)
	{
		return -2;
	}
	if(NULL == m_pPlateInfo)
	{
		return -3;
	}
	if(iColId >= m_lnkTitleInfo.GetSize())
	{
		return -4;
	}

	BOOL bSelected = TRUE;
	for(int i = 0;i < m_rowNum;++i)
	{
		if(!m_pPlateInfo[i * m_colNum + iColId].m_bSelected)
		{
			bSelected = FALSE;
			break;
		}
	}

	m_lnkTitleInfo[iColId]->m_bSelected = bSelected;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::UpdateRowSelectState
// 作用：更新或清除UpdateRowSelectState。
// 参数：bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::UpdateRowSelectState(BOOL bRedraw)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(NULL == m_pPlateInfo)
	{
		return -3;
	}
	if(m_rowNum > m_lnkRowInfo.GetSize())
	{
		return -4;
	}
	if(m_colNum > m_lnkTitleInfo.GetSize())
	{
		return -5;
	}

	for(int i = 0;i < m_rowNum;++i)
	{
		BOOL bSelected = FALSE;
		for(int j = 0;j < m_colNum;++j)
		{
			if(m_pPlateInfo[i * m_colNum + j].m_bSelected)
			{
				bSelected = TRUE;
				break;
			}
		}
		m_lnkRowInfo[i]->m_bSelected = bSelected;
	}
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::UpdateColSelectState
// 作用：更新或清除UpdateColSelectState。
// 参数：bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::UpdateColSelectState(BOOL bRedraw)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(NULL == m_pPlateInfo)
	{
		return -3;
	}
	if(m_rowNum > m_lnkRowInfo.GetSize())
	{
		return -4;
	}
	if(m_colNum > m_lnkTitleInfo.GetSize())
	{
		return -5;
	}

	for(int i = 0;i < m_colNum;++i)
	{
		BOOL bSelected = FALSE;
		for(int j = 0;j < m_rowNum;++j)
		{
			if(m_pPlateInfo[j * m_colNum + i].m_bSelected)
			{
				bSelected = TRUE;
				break;
			}
		}
		m_lnkTitleInfo[i]->m_bSelected = bSelected;
	}
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::SetAllSelectState
// 作用：设置SetAllSelectState。
// 参数：bSelected：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate、GetParent、PostMessage。
void CMySamPalteDlg::SetAllSelectState(BOOL bSelected,BOOL bRedraw /*= FALSE*/)
{
	BOOL bPreAllSelected = m_bAllSelected;

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		m_pPlateInfo[i].m_bSelected = bSelected;
	}
	for(int i = 0;i < m_rowNum;++i)
	{
		m_lnkRowInfo[i]->m_bSelected = bSelected;
	}
	for(int i = 0;i < m_colNum;++i)
	{
		m_lnkTitleInfo[i]->m_bSelected = bSelected;
	}
	m_bAllSelected = bSelected;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	if(m_bTellParentSiteSelChange && (bPreAllSelected != bSelected))
	{
		CWnd* pParent = GetParent();
		if(NULL != pParent->GetSafeHwnd())	
		{
			pParent->PostMessage(WM_TELLPARENTSITESELECTCHANGED,0,0);
		}   
	}

	return ;
}

// 函数 CMySamPalteDlg::SetAllSelectStateImmediately
// 作用：设置SetAllSelectStateImmediately。
// 参数：bSelected：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate、GetParent、SendMessage。
void CMySamPalteDlg::SetAllSelectStateImmediately(BOOL bSelected,BOOL bRedraw /*= FALSE*/)
{
	BOOL bPreAllSelected = m_bAllSelected;

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		m_pPlateInfo[i].m_bSelected = bSelected;
	}
	for(int i = 0;i < m_rowNum;++i)
	{
		m_lnkRowInfo[i]->m_bSelected = bSelected;
	}
	for(int i = 0;i < m_colNum;++i)
	{
		m_lnkTitleInfo[i]->m_bSelected = bSelected;
	}
	m_bAllSelected = bSelected;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	if(m_bTellParentSiteSelChange && (bPreAllSelected != bSelected))
	{
		CWnd* pParent = GetParent();
		if(NULL != pParent->GetSafeHwnd())	
		{
			pParent->SendMessage(WM_TELLPARENTSITESELECTCHANGED,0,0);
		}   
	}

	return ;
}

// 函数 CMySamPalteDlg::GetBeAllSelected
// 作用：读取GetBeAllSelected。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeAllSelected()
{
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		if(!m_pPlateInfo[i].m_bSelected)
		{
			m_bAllSelected = FALSE;
			return m_bAllSelected;
		}
	}
	m_bAllSelected = TRUE;
	return m_bAllSelected;
}

// 函数 CMySamPalteDlg::SetCurSelectSite
// 作用：设置SetCurSelectSite。
// 参数：vecSelSite；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
int CMySamPalteDlg::SetCurSelectSite(vector<int>& vecSelSite,BOOL bRedraw /*= FALSE*/)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(NULL == m_pPlateInfo)
	{
		return -3;
	}
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		m_pPlateInfo[i].m_bSelected = FALSE;
	}
	for(int i = 0;i < vecSelSite.size();++i)
	{
		m_pPlateInfo[vecSelSite[i]].m_bSelected = TRUE;
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetCurSelectSite
// 作用：读取GetCurSelectSite。
// 参数：vecSelSite。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、push_back。
int CMySamPalteDlg::GetCurSelectSite(vector<int>& vecSelSite)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(NULL == m_pPlateInfo)
	{
		return -3;
	}

	vecSelSite.clear();
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		if(m_pPlateInfo[i].m_bSelected)
		{
			vecSelSite.push_back(i);
		}
	}

	return 0;
}

// 函数 CMySamPalteDlg::GetSamInfo
// 作用：读取GetSamInfo。
// 参数：iSiteIndex：整数；samInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetSamInfo(int iSiteIndex,CTubeInfo& samInfo)
{
	if(iSiteIndex < 0)
	{
		return -1;
	}
	if(iSiteIndex >= m_iTotalSiteNum)
	{
		return -2;
	}
	if(m_rowNum < 1)
	{
		return -3;
	}
	if(m_colNum < 1)
	{
		return -4;
	}
	if(NULL == m_pTubeInfo)
	{
		return -5;
	}
	samInfo = m_pTubeInfo[iSiteIndex];
	return 0;
}

// 函数 CMySamPalteDlg::GetSamInfo
// 作用：读取GetSamInfo。
// 参数：iRowId：整数；iColId：整数；samInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetSamInfo(int iRowId,int iColId,CTubeInfo& samInfo)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(iRowId < 0)
	{
		return -3;
	}
	if(iRowId >= m_rowNum)
	{
		return -4;
	}
	if(iColId < 0)
	{
		return -5;
	}
	if(iColId >= m_colNum)
	{
		return -6;
	}
	if(NULL == m_pTubeInfo)
	{
		return -7;
	}
	samInfo = m_pTubeInfo[iRowId * m_colNum + iColId];
	return 0;
}

// 函数 CMySamPalteDlg::GetTubeInfoPtr
// 作用：读取GetTubeInfoPtr。
// 参数：iSiteIndex：整数；ppTubeInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetTubeInfoPtr(int iSiteIndex,CTubeInfo** ppTubeInfo)
{
	if(iSiteIndex < 0)
	{
		return -1;
	}
	if(iSiteIndex >= m_iTotalSiteNum)
	{
		return -2;
	}
	if(m_rowNum < 1)
	{
		return -3;
	}
	if(m_colNum < 1)
	{
		return -4;
	}
	if(NULL == m_pTubeInfo)
	{
		return -5;
	}

	if(NULL == ppTubeInfo)
	{
		return -6;
	}

	*ppTubeInfo = &(m_pTubeInfo[iSiteIndex]);
	return 0;
}

// 函数 CMySamPalteDlg::GetTubeInfoPtr
// 作用：读取GetTubeInfoPtr。
// 参数：无。
// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTubeInfo* CMySamPalteDlg::GetTubeInfoPtr()
{
	return m_pTubeInfo;
}

// 函数 CMySamPalteDlg::GetSamInfo
// 作用：读取GetSamInfo。
// 参数：vecSamInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、push_back。
int CMySamPalteDlg::GetSamInfo(vector<CTubeInfo>& vecSamInfo)
{
	vecSamInfo.clear();
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(NULL == m_pTubeInfo)
	{
		return -3;
	}
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		vecSamInfo.push_back(m_pTubeInfo[i]);
	}
	return 0;
}

// 函数 CMySamPalteDlg::SetSamInfo
// 作用：设置SetSamInfo。
// 参数：vecSamInfo；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetSamInfo(vector<CTubeInfo>& vecSamInfo,BOOL bRedraw /*= FALSE*/)
{
	if(m_iTotalSiteNum != vecSamInfo.size())
	{
		return -1;
	}

	if(m_rowNum < 1)
	{
		return -2;
	}
	if(m_colNum < 1)
	{
		return -3;
	}
	if(NULL == m_pTubeInfo)
	{
		return -4;
	}

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		m_pTubeInfo[i] = vecSamInfo[i];
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetTubeInfo
// 作用：设置SetTubeInfo。
// 参数：pTubeAryPtr：指针，指向调用方传入的对象；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetAt、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetTubeInfo(CPtrArray* pTubeAryPtr,BOOL bRedraw /*= FALSE*/)
{
	if(NULL == pTubeAryPtr)
	{
		return -1;
	}
	if(m_iTotalSiteNum != pTubeAryPtr->GetSize())
	{
		return -2;
	}

	if(m_rowNum < 1)
	{
		return -3;
	}
	if(m_colNum < 1)
	{
		return -4;
	}
	if(NULL == m_pTubeInfo)
	{
		return -5;
	}

	CTubeInfo* pTubeInfo = NULL;
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		pTubeInfo = (CTubeInfo*)pTubeAryPtr->GetAt(i);
		if(NULL == pTubeInfo)
		{
			continue;
		}
		m_pTubeInfo[i] = *pTubeInfo;
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetTubeInfo
// 作用：设置SetTubeInfo。
// 参数：pTubeInfo：指针，指向调用方传入的对象；iSiteNum：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetTubeInfo(CTubeInfo* pTubeInfo,int iSiteNum,BOOL bRedraw /*= FALSE*/)
{
	if(NULL == pTubeInfo)
	{
		return -1;
	}
	if(iSiteNum < 1)
	{
		return -2;
	}
	if(NULL == m_pTubeInfo)
	{
		return -3;
	}
	if(m_iTotalSiteNum < 1)
	{
		return -4;
	}

	int iTempNum = iSiteNum;
	if(iSiteNum > m_iTotalSiteNum)
	{
		iTempNum = m_iTotalSiteNum;
	}

	for(int i = 0;i < iTempNum;++i)
	{
		m_pTubeInfo[i] = pTubeInfo[i];
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetTubeInfo
// 作用：设置SetTubeInfo。
// 参数：vecPTubeInfo；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size、GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetTubeInfo(vector<CTubeInfo*>& vecPTubeInfo,BOOL bRedraw /*= FALSE*/)
{
	int iTempNum = vecPTubeInfo.size();
	if(iTempNum < 1)
	{
		return -1;
	}

	if(NULL == m_pTubeInfo)
	{
		return -2;
	}
	if(m_iTotalSiteNum < 1)
	{
		return -3;
	}

	if(iTempNum > m_iTotalSiteNum)
	{
		iTempNum = m_iTotalSiteNum;
	}

	for(int i = 0;i < iTempNum;++i)
	{
		if(NULL != vecPTubeInfo[i])
		{
			m_pTubeInfo[i] = *(vecPTubeInfo[i]);
		}
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetSamInfo
// 作用：设置SetSamInfo。
// 参数：iSiteIndex：整数；samInfo；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetSamInfo(int iSiteIndex,CTubeInfo& samInfo,BOOL bRedraw /*= FALSE*/)
{
	if(iSiteIndex < 0)
	{
		return -1;
	}
	if(iSiteIndex >= m_iTotalSiteNum)
	{
		return -2;
	}
	if(m_rowNum < 1)
	{
		return -3;
	}
	if(m_colNum < 1)
	{
		return -4;
	}
	if(NULL == m_pTubeInfo)
	{
		return -5;
	}
	m_pTubeInfo[iSiteIndex] = samInfo;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetSamInfo
// 作用：设置SetSamInfo。
// 参数：iRowId：整数；iColId：整数；samInfo；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetSamInfo(int iRowId,int iColId,CTubeInfo& samInfo,BOOL bRedraw /*= FALSE*/)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(iRowId < 0)
	{
		return -3;
	}
	if(iRowId >= m_rowNum)
	{
		return -4;
	}
	if(iColId < 0)
	{
		return -5;
	}
	if(iColId >= m_colNum)
	{
		return -6;
	}
	if(NULL == m_pTubeInfo)
	{
		return -7;
	}
	m_pTubeInfo[iRowId * m_colNum + iColId] = samInfo;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetSamInfo
// 作用：设置SetSamInfo。
// 参数：iSiteIndex：整数；eItemInfoType；strData：字符串；intData；dData：小数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetTubeLabel、SetSampleName、SetSampleType、TextToSampleType、SetIsRepeatTube、SetSampleID。
int CMySamPalteDlg::SetSamInfo(int iSiteIndex,EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/,BOOL bRedraw /*= FALSE*/)
{
	if(iSiteIndex < 0)
	{
		return -1;
	}
	if(iSiteIndex >= m_iTotalSiteNum)
	{
		return -2;
	}
	if(m_rowNum < 1)
	{
		return -3;
	}
	if(m_colNum < 1)
	{
		return -4;
	}
	if(NULL == m_pTubeInfo)
	{
		return -5;
	}

	CTubeInfo& samInfo = m_pTubeInfo[iSiteIndex];

	switch(eItemInfoType)
	{
	case ITEMHOLEINFO: samInfo.SetTubeLabel(strData); break;
	case ITEMSAMNAME: samInfo.SetSampleName(strData); break;
	case ITEMSAMTYPE: samInfo.SetSampleType(TextToSampleType(strData)); break;
	//case ITEMSTDDENSITY: samInfo.m_dDensity = dData; break;
	case ITEMREPETITIVETUBE: samInfo.SetIsRepeatTube(intData); break;
	case ITEMSAMID: samInfo.SetSampleID(strData); break;
	case ITEMPATIENTNAME: samInfo.m_strPatientName = strData; break;
	case ITEMSEXUALITY: samInfo.m_nPatientSex = (ePatientSexuality)intData; break;
	case ITEMAGE: samInfo.m_nPatientAge = intData; break;
	case ITEMSAMCOLLECTDATE: samInfo.m_strCollectDate = strData; break;
	case ITEMSENDINGDOCTOR: samInfo.m_strProposer = strData; break;
	case ITEMSENDINGSECTION: samInfo.m_strDepartment = strData; break;
	case ITEMANAMNESISNO: samInfo.m_strCaseID = strData; break;
	case ITEMBEDNO: samInfo.m_strBedNo = strData; break;
	case ITEMHOSPITALID: samInfo.m_strHospital = strData; break;
	case ITEMOUTPATIENTNO: samInfo.m_strClinicID = strData; break;
	case ITEMREMARKS: samInfo.SetComments(strData); break;
	case ITEM_REPETITIVETUBETAG:	break;

	default:	break;
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate();
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetSamInfo
// 作用：设置SetSamInfo。
// 参数：iRowId：整数；iColId：整数；eItemInfoType；strData：字符串；intData；dData：小数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetTubeLabel、SetSampleName、SetSampleType、SetIsRepeatTube、SetSampleID、SetComments。
int CMySamPalteDlg::SetSamInfo(int iRowId,int iColId,EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/,BOOL bRedraw /*= FALSE*/)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(iRowId < 0)
	{
		return -3;
	}
	if(iRowId >= m_rowNum)
	{
		return -4;
	}
	if(iColId < 0)
	{
		return -5;
	}
	if(iColId >= m_colNum)
	{
		return -6;
	}
	if(NULL == m_pTubeInfo)
	{
		return -7;
	}

	CTubeInfo& tubeInfo = m_pTubeInfo[iRowId * m_colNum + iColId];

	switch(eItemInfoType)
	{
	case ITEMHOLEINFO: tubeInfo.SetTubeLabel(strData); break;
	case ITEMSAMNAME: tubeInfo.SetSampleName(strData); break;
	case ITEMSAMTYPE: tubeInfo.SetSampleType((eSampleType)intData); break;
		//case ITEMSTDDENSITY: tubeInfo.m_dDensity = dData; break;
	case ITEMREPETITIVETUBE: tubeInfo.SetIsRepeatTube(intData); break;
	case ITEMSAMID: tubeInfo.SetSampleID(strData); break;
	case ITEMPATIENTNAME: tubeInfo.m_strPatientName = strData; break;
	case ITEMSEXUALITY: tubeInfo.m_nPatientSex = (ePatientSexuality)intData; break;
	case ITEMAGE: tubeInfo.m_nPatientAge = intData; break;
	case ITEMSAMCOLLECTDATE: tubeInfo.m_strCollectDate = strData; break;
	case ITEMSENDINGDOCTOR: tubeInfo.m_strProposer = strData; break;
	case ITEMSENDINGSECTION: tubeInfo.m_strDepartment = strData; break;
	case ITEMANAMNESISNO: tubeInfo.m_strCaseID = strData; break;
	case ITEMBEDNO: tubeInfo.m_strBedNo = strData; break;
	case ITEMHOSPITALID: tubeInfo.m_strHospital = strData; break;
	case ITEMOUTPATIENTNO: tubeInfo.m_strClinicID = strData; break;
	case ITEMREMARKS: tubeInfo.SetComments(strData); break;

	default:	break;
	}

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate();
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetRectWidth
// 作用：设置SetRectWidth。
// 参数：iRectW：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetRectWidth(int iRectW,BOOL bRedraw /*= FALSE*/)
{
	m_iRectW = iRectW;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetRectHeight
// 作用：设置SetRectHeight。
// 参数：iRectH：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
int CMySamPalteDlg::SetRectHeight(int iRectH,BOOL bRedraw /*= FALSE*/)
{
	m_iRectH = iRectH;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return 0;
}

// 函数 CMySamPalteDlg::SetBeShowTopText
// 作用：设置SetBeShowTopText。
// 参数：bShowTopTx：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBeShowTopText(BOOL bShowTopTx,BOOL bRedraw /*= FALSE*/)
{
	m_bShowTopTx = bShowTopTx;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBeShowTopText
// 作用：读取GetBeShowTopText。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeShowTopText()
{
	return m_bShowTopTx;
}

// 函数 CMySamPalteDlg::SetBeShowBottomText
// 作用：设置SetBeShowBottomText。
// 参数：bShowBottomTx：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetBeShowBottomText(BOOL bShowBottomTx,BOOL bRedraw /*= FALSE*/)
{
	m_bShowBottomTx = bShowBottomTx;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetBeShowBottomText
// 作用：读取GetBeShowBottomText。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeShowBottomText()
{
	return m_bShowBottomTx;
}

// 函数 CMySamPalteDlg::GetPlateSelectState
// 作用：读取GetPlateSelectState。
// 参数：vecSelState。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、push_back。
int CMySamPalteDlg::GetPlateSelectState(vector<BOOL>& vecSelState)
{
	vecSelState.clear();

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		vecSelState.push_back(m_pPlateInfo[i].m_bSelected);
	}
	return 0;
}

// 函数 CMySamPalteDlg::GetPlateSelectedSite
// 作用：读取GetPlateSelectedSite。
// 参数：vecSelectedSite。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、push_back。
int CMySamPalteDlg::GetPlateSelectedSite(vector<BOOL>& vecSelectedSite)
{
	vecSelectedSite.clear();

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		if(m_pPlateInfo[i].m_bSelected)
		{
			vecSelectedSite.push_back(i);
		}
	}
	return 0;
}

// 函数 CMySamPalteDlg::SetFourAngleBkColor
// 作用：设置SetFourAngleBkColor。
// 参数：clrFourAngleBk：颜色；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetFourAngleBkColor(COLORREF clrFourAngleBk,BOOL bRedraw /*= FALSE*/)
{
	m_clrFourAngleBk = clrFourAngleBk;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetFourAngleBkColor
// 作用：读取GetFourAngleBkColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CMySamPalteDlg::GetFourAngleBkColor()
{
	return m_clrFourAngleBk;
}

// 函数 CMySamPalteDlg::SetInterval
// 作用：设置SetInterval。
// 参数：iHori：整数；iVert：整数；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetInterval(int iHori,int iVert,BOOL bRedraw /*= FALSE*/)
{
	m_iHoriInterval = iHori;
	m_iVertInterval = iVert;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetHoriInterval
// 作用：读取GetHoriInterval。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetHoriInterval()
{
	return m_iHoriInterval;
}

// 函数 CMySamPalteDlg::GetVertInterval
// 作用：读取GetVertInterval。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMySamPalteDlg::GetVertInterval()
{
	return m_iVertInterval;
}

// 函数 CMySamPalteDlg::SetBeShieldDeleteKey
// 作用：设置SetBeShieldDeleteKey。
// 参数：bShieldDeleteKey：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMySamPalteDlg::SetBeShieldDeleteKey(BOOL bShieldDeleteKey)
{
	m_bShieldDeleteKey = bShieldDeleteKey;
}

// 函数 CMySamPalteDlg::GetBeShieldDeleteKey
// 作用：读取GetBeShieldDeleteKey。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeShieldDeleteKey()
{
	return m_bShieldDeleteKey;
}

// 函数 CMySamPalteDlg::SetBeParentProcessDeleteKey
// 作用：设置SetBeParentProcessDeleteKey。
// 参数：bParentProcessDeleteKey：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMySamPalteDlg::SetBeParentProcessDeleteKey(BOOL bParentProcessDeleteKey)
{
	m_bParentProcessDeleteKey = bParentProcessDeleteKey;
}

// 函数 CMySamPalteDlg::GetBeParentProcessDeleteKey
// 作用：读取GetBeParentProcessDeleteKey。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeParentProcessDeleteKey()
{
	return m_bParentProcessDeleteKey;
}

// 函数 CMySamPalteDlg::SetSiteIdShowState
// 作用：设置SetSiteIdShowState。
// 参数：bShow：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetSiteIdShowState(BOOL bShow,BOOL bRedraw /*= FALSE*/)
{
	m_bShowSiteId = bShow;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetSiteIdShowState
// 作用：读取GetSiteIdShowState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetSiteIdShowState()
{
	return m_bShowSiteId;
}

// 函数 CMySamPalteDlg::SetLastChanBlockShowState
// 作用：设置SetLastChanBlockShowState。
// 参数：bShow：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CMySamPalteDlg::SetLastChanBlockShowState(BOOL bShow,BOOL bRedraw /*= FALSE*/)
{
	m_bShowLastChanBlock = bShow;
	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate(FALSE);
	}
	return;
}

// 函数 CMySamPalteDlg::GetLastChanBlockShowState
// 作用：读取GetLastChanBlockShowState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetLastChanBlockShowState()
{
	return m_bShowLastChanBlock;
}

// 函数 CMySamPalteDlg::DeleteSelectedTubeInfo
// 作用：更新或清除DeleteSelectedTubeInfo。
// 参数：bTemplateMode：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Reset、Invalidate、GetParent、GetSafeHwnd、PostMessage。
int CMySamPalteDlg::DeleteSelectedTubeInfo(BOOL bTemplateMode)
{
	if(m_iTotalSiteNum < 1)
	{
		return -1;
	}

	if(NULL == m_pPlateInfo)
	{
		return -2;
	}

	if(NULL == m_pTubeInfo)
	{
		return -3;
	}

	BOOL bExistSelectedSite = FALSE;
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		if(m_pPlateInfo[i].m_bSelected)
		{
			bExistSelectedSite = TRUE;
			m_pTubeInfo[i].Reset(bTemplateMode);
		}
	}

	if(bExistSelectedSite)
	{
		Invalidate(FALSE);
		if(m_bTellParentSiteSelChange)
		{
			CWnd* pParent = GetParent();
			if(NULL != pParent->GetSafeHwnd())	//样本信息改变，通知父窗口
			{
				pParent->PostMessage(WM_TELLPARENTSITESELECTCHANGED,0,0);
			}   
		}
	}

	return 0;
}

// 函数 CMySamPalteDlg::DeleteTubeInfo
// 作用：更新或清除DeleteTubeInfo。
// 参数：vecId；bTemplateMode：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size、Reset、Invalidate、GetParent、GetSafeHwnd、PostMessage。
int CMySamPalteDlg::DeleteTubeInfo(vector<int> vecId,BOOL bTemplateMode)
{
	if(m_iTotalSiteNum < 1)
	{
		return -1;
	}

	if(NULL == m_pPlateInfo)
	{
		return -2;
	}

	if(NULL == m_pTubeInfo)
	{
		return -3;
	}

	if(vecId.size() < 1)
	{
		return -4;
	}

	for(int i = 0;i < vecId.size();++i)
	{
		if(vecId[i] < m_iTotalSiteNum)
		{
			m_pTubeInfo[vecId[i]].Reset(bTemplateMode);
		}
	}

	Invalidate(FALSE);
	if(m_bTellParentSiteSelChange)
	{
		CWnd* pParent = GetParent();
		if(NULL != pParent->GetSafeHwnd())	//样本信息改变，通知父窗口
		{
			pParent->PostMessage(WM_TELLPARENTSITESELECTCHANGED,0,0);
		}   
	}

	return 0;
}

// 函数 CMySamPalteDlg::DeleteTubeInfo
// 作用：更新或清除DeleteTubeInfo。
// 参数：vecId；eDeletType；bTemplateMode：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size、Reset、ResetInfo1、ResetInfo2、Invalidate、GetParent。
int CMySamPalteDlg::DeleteTubeInfo(vector<int> vecId,EDELETETYPE eDeletType,BOOL bTemplateMode)
{
	if(m_iTotalSiteNum < 1)
	{
		return -1;
	}

	if(NULL == m_pPlateInfo)
	{
		return -2;
	}

	if(NULL == m_pTubeInfo)
	{
		return -3;
	}

	if(vecId.size() < 1)
	{
		return -4;
	}

	for(int i = 0;i < vecId.size();++i)
	{
		if(vecId[i] < m_iTotalSiteNum)
		{
			if(EDT_DELETEALL == eDeletType)
			{
				m_pTubeInfo[vecId[i]].Reset(bTemplateMode);
			}
			else if(EDT_DELETE1 == eDeletType)
			{
				m_pTubeInfo[vecId[i]].ResetInfo1(bTemplateMode);
			}
			else if(EDT_DELETE2 == eDeletType)
			{
				m_pTubeInfo[vecId[i]].ResetInfo2(bTemplateMode);
			}
		}
	}

	Invalidate(FALSE);
	if(m_bTellParentSiteSelChange)
	{
		CWnd* pParent = GetParent();
		if(NULL != pParent->GetSafeHwnd())	//样本信息改变，通知父窗口
		{
			pParent->PostMessage(WM_TELLPARENTSITESELECTCHANGED,0,0);
		}   
	}

	return 0;
}

// 函数 CMySamPalteDlg::DeleteAllTubeInfo
// 作用：更新或清除DeleteAllTubeInfo。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Reset、SetAllSelectState。
int CMySamPalteDlg::DeleteAllTubeInfo()
{
	if(m_iTotalSiteNum < 1)
	{
		return -1;
	}

	if(NULL == m_pPlateInfo)
	{
		return -2;
	}

	if(NULL == m_pTubeInfo)
	{
		return -3;
	}

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		m_pTubeInfo[i].Reset(FALSE);
	}

	SetAllSelectState(FALSE,TRUE);

	return 0;
}

// 函数 CMySamPalteDlg::GetSameTubeInfo
// 作用：读取GetSameTubeInfo。
// 参数：tubeInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetPlateSelectedSite、size、strTemp、_T、GetTubeFlag、SetTubeFlag。
int CMySamPalteDlg::GetSameTubeInfo(CTubeInfo& tubeInfo)
{
	if(NULL == m_pTubeInfo)
	{
		return -1;
	}

	vector<int> vecSelectedSite;
	GetPlateSelectedSite(vecSelectedSite);
	if(vecSelectedSite.size() < 1)
	{
		return 1;
	}

	CString strTemp(_T(""));
	COLORREF clrTemp = 0;
	int iTemp = 0;
	eSampleType eTemp = SAMPLE_TYPE_NONE;
	BOOL bFind = FALSE;

	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetTubeFlag();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetTubeFlag())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetTubeFlag(strTemp);
	}
	
	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetSampleID();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetSampleID())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetSampleID(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetSampleName();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetSampleName())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetSampleName(strTemp);
	}

	bFind = FALSE;
	clrTemp = m_pTubeInfo[vecSelectedSite[0]].GetSampleColor();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(clrTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetSampleColor())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetSampleColor(clrTemp);
	}

	eTemp = m_pTubeInfo[vecSelectedSite[0]].GetSampleType();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(eTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetSampleType())
		{
			eTemp = SAMPLE_TYPE_MULLTI_DIFFERENT;
			break;
		}
	}
	tubeInfo.SetSampleType(eTemp);

	bFind = FALSE;
	iTemp = m_pTubeInfo[vecSelectedSite[0]].GetIsRepeatTube();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(iTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetIsRepeatTube())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetIsRepeatTube(iTemp);
	}

	bFind = FALSE;
	iTemp = m_pTubeInfo[vecSelectedSite[0]].GetRepeatNo();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(iTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetRepeatNo())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetRepeatNo(iTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetComments();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetComments())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetComments(strTemp);
	}

	bFind = FALSE;
	iTemp = m_pTubeInfo[vecSelectedSite[0]].GetCalibrateChannel();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(iTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetCalibrateChannel())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetCalibrateChannel(iTemp);
	}

	bFind = FALSE;
	int iDyeTargetNum = m_pTubeInfo[vecSelectedSite[0]].GetTargetCount();
	if(iDyeTargetNum > 0)
	{
		tubeInfo.InitDyeChannel(iDyeTargetNum);
		for(int i = 1;i < vecSelectedSite.size();++i)
		{
			if(iDyeTargetNum != (m_pTubeInfo[vecSelectedSite[i]]).GetTargetCount())
			{
				bFind = TRUE;
				break;
			}
		}
	}
	else
	{
		bFind = TRUE;
	}

	if(!bFind)
	{
		BOOL* pBFind = new BOOL[iDyeTargetNum];
		if(NULL != pBFind)
		{
			for(int j = 0;j < iDyeTargetNum;++j)
			{
				pBFind[j] = FALSE;
				iTemp = m_pTubeInfo[vecSelectedSite[0]].GetSampleChannelSelectState(j);
				for(int i = 1;i < vecSelectedSite.size();++i)
				{
					if(iTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetSampleChannelSelectState(j))
					{
						pBFind[j] = TRUE;
						break;
					}
				}
				if(!pBFind[j])
				{
					tubeInfo.SetSampleChannelSelectState(j,iTemp);
				}

				pBFind[j] = FALSE;
				strTemp = m_pTubeInfo[vecSelectedSite[0]].GetDyeName(j);
				for(int i = 1;i < vecSelectedSite.size();++i)
				{
					if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetDyeName(j))
					{
						pBFind[j] = TRUE;
						break;
					}
				}
				if(!pBFind[j])
				{
					tubeInfo.SetDyeName(j,strTemp);
				}

				pBFind[j] = FALSE;
				strTemp = m_pTubeInfo[vecSelectedSite[0]].GetTargetName(j);
				for(int i = 1;i < vecSelectedSite.size();++i)
				{
					if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetTargetName(j))
					{
						pBFind[j] = TRUE;
						break;
					}
				}
				if(!pBFind[j])
				{
					tubeInfo.SetTargetName(j,strTemp);
				}

				pBFind[j] = FALSE;
				clrTemp = m_pTubeInfo[vecSelectedSite[0]].GetSampleDyeTargetColor(j);
				for(int i = 1;i < vecSelectedSite.size();++i)
				{
					if(clrTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetSampleDyeTargetColor(j))
					{
						pBFind[j] = TRUE;
						break;
					}
				}
				if(!pBFind[j])
				{
					tubeInfo.SetSampleDyeTargetColor(j,clrTemp);
				}
			}
			delete [] pBFind;
		}
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetPatientID();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetPatientID())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetPaitentID(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetClinicID();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetClinicID())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetClinicID(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetCaseID();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetCaseID())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetCaseID(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetPatientName();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetPatientName())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetPatientName(strTemp);
	}

	bFind = FALSE;
	ePatientSexuality eSex = SEXUALITY_NONE;
	eSex = m_pTubeInfo[vecSelectedSite[0]].GetSexuality();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(eSex != (m_pTubeInfo[vecSelectedSite[i]]).GetSexuality())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetSexuality(eSex);
	}

	bFind = FALSE;
	iTemp = m_pTubeInfo[vecSelectedSite[0]].GetPaitentAge();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(iTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetPaitentAge())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetPaitentAge(iTemp);
	}

	bFind = FALSE;
	ePatientAgeUnit eAgeUnit = AGE_UNIT_YEAR;
	eAgeUnit = m_pTubeInfo[vecSelectedSite[0]].GetAgeUnit();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(eAgeUnit != (m_pTubeInfo[vecSelectedSite[i]]).GetAgeUnit())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetAgeUnit(eAgeUnit);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetAreaNo();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetAreaNo())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetAreaNo(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetRoomNo();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetRoomNo())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetRoomNo(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetBedNo();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetBedNo())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetBedNo(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetProposer();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetProposer())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetProposer(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetDepartment();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetDepartment())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetDepartment(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetHospital();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetHospital())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetHospital(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetCollectDate();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetCollectDate())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetCollectDate(strTemp);
	}

	bFind = FALSE;
	strTemp = m_pTubeInfo[vecSelectedSite[0]].GetApplyDate();
	for(int i = 1;i < vecSelectedSite.size();++i)
	{
		if(strTemp != (m_pTubeInfo[vecSelectedSite[i]]).GetApplyDate())
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		tubeInfo.SetApplyDate(strTemp);
	}

	return 0;
}

// 函数 CMySamPalteDlg::SetAllTubeChanInfo
// 作用：设置SetAllTubeChanInfo。
// 参数：iChanId：整数；bSelected：是或否；strDyeName：字符串；strTargetName：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetTargetCount、GetTargetInfo、SetBeSelected、SetDyeName、SetTargetName。
int CMySamPalteDlg::SetAllTubeChanInfo(int iChanId,BOOL bSelected,CString strDyeName,CString strTargetName)
{
	if(iChanId < 0)
	{
		return -1;
	}

	if(NULL == m_pTubeInfo)
	{
		return -2;
	}

	int iChanNum = 0;
	CTubeInfo* pTubeInfo = NULL;
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		pTubeInfo = &m_pTubeInfo[i];
		if(NULL == pTubeInfo)
		{
			continue;
		}

		iChanNum = pTubeInfo->GetTargetCount();
		if(iChanId >= iChanNum)
		{
			continue;
		}

		pDyeTargetInfo = pTubeInfo->GetTargetInfo(iChanId);
		if(NULL == pDyeTargetInfo)
		{
			continue;
		}

		pDyeTargetInfo->SetBeSelected(bSelected);
		pDyeTargetInfo->SetDyeName(strDyeName);
		pDyeTargetInfo->SetTargetName(strTargetName);
	}

	return 0;
}

// 函数 CMySamPalteDlg::GetOneChannelDyeNameFromTubeInfo
// 作用：读取GetOneChannelDyeNameFromTubeInfo。
// 参数：iChanId：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 strDyeName、_T、GetDyeName、IsEmpty。
CString CMySamPalteDlg::GetOneChannelDyeNameFromTubeInfo(int iChanId)
{
	CString strDyeName(_T(""));

	if(m_iTotalSiteNum < 1 || NULL == m_pTubeInfo)
	{
		return strDyeName;
	}

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		strDyeName = m_pTubeInfo[i].GetDyeName(iChanId);
		if(!strDyeName.IsEmpty())
		{
			break;
		}
	}

	return strDyeName;
}

// 函数 CMySamPalteDlg::GetAllSampleType
// 作用：读取GetAllSampleType。
// 参数：vecSamType。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、push_back、GetSampleType。
int CMySamPalteDlg::GetAllSampleType(vector<eSampleType>& vecSamType)
{
	vecSamType.clear();

	if(m_iTotalSiteNum < 1)
	{
		return -1;
	}

	if(NULL == m_pTubeInfo)
	{
		return -2;
	}

	for(int i = 0;i < m_iTotalSiteNum;++i)
	{
		vecSamType.push_back(m_pTubeInfo[i].GetSampleType());
	}

	return 0;
}

// 函数 CMySamPalteDlg::SampleTypeToText
// 作用：执行SampleTypeToText。
// 参数：eType。
// 返回：返回一段文字。
// 过程：函数里会调用 find、end、_T。
CString CMySamPalteDlg::SampleTypeToText(eSampleType eType)
{
	map<eSampleType,CString>::iterator iter = m_mapSamTypeToTx.find(eType);
	if(m_mapSamTypeToTx.end() == iter)
	{
		return _T("");
	}

	return iter->second;
}

// 函数 CMySamPalteDlg::TextToSampleType
// 作用：执行TextToSampleType。
// 参数：strText：字符串。
// 返回：返回 eSampleType。
// 过程：函数里会调用 find、end。
eSampleType CMySamPalteDlg::TextToSampleType(CString strText)
{
	map<CString,eSampleType>::iterator iter = m_mapTxToSamType.find(strText);
	if(m_mapTxToSamType.end() == iter)
	{
		return SAMPLE_TYPE_NONE;
	}

	return iter->second;
}

// 函数 CMySamPalteDlg::InitMapSampleTypeToText
// 作用：初始化InitMapSampleTypeToText。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetInstance、GetText。
int CMySamPalteDlg::InitMapSampleTypeToText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_mapSamTypeToTx[SAMPLE_TYPE_NONE] = pLangInfo->GetText(292);
	m_mapSamTypeToTx[SAMPLE_TYPE_UNKNOWN] = pLangInfo->GetText(211);
	m_mapSamTypeToTx[SAMPLE_TYPE_STANDARD] = pLangInfo->GetText(212);
	m_mapSamTypeToTx[SAMPLE_TYPE_NTC] = pLangInfo->GetText(213);
	m_mapSamTypeToTx[SAMPLE_TYPE_NEGATIVE] = pLangInfo->GetText(214);
	m_mapSamTypeToTx[SAMPLE_TYPE_POSITIVE] = pLangInfo->GetText(215);
	m_mapSamTypeToTx[SAMPLE_TYPE_POS_CRITICAL] = pLangInfo->GetText(216);
	m_mapSamTypeToTx[SAMPLE_TYPE_CALIBRATOR] = pLangInfo->GetText(217);
	m_mapSamTypeToTx[SAMPLE_TYPE_BUFFER] = pLangInfo->GetText(218);
	m_mapSamTypeToTx[SAMPLE_TYPE_IC] = pLangInfo->GetText(457);

	return 0;
}

// 函数 CMySamPalteDlg::InitMapTextToSampleType
// 作用：初始化InitMapTextToSampleType。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetInstance、GetText。
int CMySamPalteDlg::InitMapTextToSampleType() 
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_mapTxToSamType[pLangInfo->GetText(292,LANGUAGE_CHS)] = SAMPLE_TYPE_NONE;
	m_mapTxToSamType[pLangInfo->GetText(211,LANGUAGE_CHS)] = SAMPLE_TYPE_UNKNOWN;
	m_mapTxToSamType[pLangInfo->GetText(212,LANGUAGE_CHS)] = SAMPLE_TYPE_STANDARD;
	m_mapTxToSamType[pLangInfo->GetText(213,LANGUAGE_CHS)] = SAMPLE_TYPE_NTC;
	m_mapTxToSamType[pLangInfo->GetText(214,LANGUAGE_CHS)] = SAMPLE_TYPE_NEGATIVE;
	m_mapTxToSamType[pLangInfo->GetText(215,LANGUAGE_CHS)] = SAMPLE_TYPE_POSITIVE;
	m_mapTxToSamType[pLangInfo->GetText(216,LANGUAGE_CHS)] = SAMPLE_TYPE_POS_CRITICAL;
	m_mapTxToSamType[pLangInfo->GetText(217,LANGUAGE_CHS)] = SAMPLE_TYPE_CALIBRATOR;
	m_mapTxToSamType[pLangInfo->GetText(218,LANGUAGE_CHS)] = SAMPLE_TYPE_BUFFER;
	m_mapTxToSamType[pLangInfo->GetText(457,LANGUAGE_CHS)] = SAMPLE_TYPE_IC;	

	m_mapTxToSamType[pLangInfo->GetText(292,LANGUAGE_ENG)] = SAMPLE_TYPE_NONE;
	m_mapTxToSamType[pLangInfo->GetText(211,LANGUAGE_ENG)] = SAMPLE_TYPE_UNKNOWN;
	m_mapTxToSamType[pLangInfo->GetText(212,LANGUAGE_ENG)] = SAMPLE_TYPE_STANDARD;
	m_mapTxToSamType[pLangInfo->GetText(213,LANGUAGE_ENG)] = SAMPLE_TYPE_NTC;
	m_mapTxToSamType[pLangInfo->GetText(214,LANGUAGE_ENG)] = SAMPLE_TYPE_NEGATIVE;
	m_mapTxToSamType[pLangInfo->GetText(215,LANGUAGE_ENG)] = SAMPLE_TYPE_POSITIVE;
	m_mapTxToSamType[pLangInfo->GetText(216,LANGUAGE_ENG)] = SAMPLE_TYPE_POS_CRITICAL;
	m_mapTxToSamType[pLangInfo->GetText(217,LANGUAGE_ENG)] = SAMPLE_TYPE_CALIBRATOR;
	m_mapTxToSamType[pLangInfo->GetText(218,LANGUAGE_ENG)] = SAMPLE_TYPE_BUFFER;	
	m_mapTxToSamType[pLangInfo->GetText(457,LANGUAGE_ENG)] = SAMPLE_TYPE_IC;	

	return 0;
}

// 函数 CMySamPalteDlg::InitMapSamTypeToHoleClrInfo
// 作用：初始化InitMapSamTypeToHoleClrInfo。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Color、RGB。
int CMySamPalteDlg::InitMapSamTypeToHoleClrInfo()
{
	int iAlpha = 255 * 0.2;

	CHoleColorInfo holeClrInfo;

#ifdef N16USENEWSAMPLETYPE
	holeClrInfo.m_clrFrame = Color(0XC6,0XC6,0XC6);
	holeClrInfo.m_clrFill = Color(255 * 0.3,0XC6,0XC6,0XC6);
	holeClrInfo.m_clrTxUnSelected = RGB(0X66,0X66,0X66);
	holeClrInfo.m_clrTxSelected = RGB(0X66,0X66,0X66);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_NONE] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0X9B,0X51,0XE0);
	holeClrInfo.m_clrFill = Color(iAlpha,0X9B,0X51,0XE0);
	holeClrInfo.m_clrTxUnSelected = RGB(0X9B,0X51,0XE0);
	holeClrInfo.m_clrTxSelected = RGB(0X9B,0X51,0XE0);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_UNKNOWN] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0X21,0X96,0X53);
	holeClrInfo.m_clrFill = Color(iAlpha,0X21,0X96,0X53);
	holeClrInfo.m_clrTxUnSelected = RGB(0X21,0X96,0X53);
	holeClrInfo.m_clrTxSelected = RGB(0X21,0X96,0X53);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_STANDARD] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0XEB,0X57,0X57);
	holeClrInfo.m_clrFill = Color(iAlpha,0XEB,0X57,0X57);
	holeClrInfo.m_clrTxUnSelected = RGB(0XEB,0X57,0X57);
	holeClrInfo.m_clrTxSelected = RGB(0XEB,0X57,0X57);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_POSITIVE] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0X2F,0X80,0XED);
	holeClrInfo.m_clrFill = Color(iAlpha,0X2F,0X80,0XED);
	holeClrInfo.m_clrTxUnSelected = RGB(0X2F,0X80,0XED);
	holeClrInfo.m_clrTxSelected = RGB(0X2F,0X80,0XED);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_NEGATIVE] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0XF2,0X99,0X4A);
	holeClrInfo.m_clrFill = Color(iAlpha,0XF2,0X99,0X4A);
	holeClrInfo.m_clrTxUnSelected = RGB(0XF2,0X99,0X4A);
	holeClrInfo.m_clrTxSelected = RGB(0XF2,0X99,0X4A);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_NTC] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0XF2,0X31,0X31);
	holeClrInfo.m_clrFill = Color(iAlpha,0XF2,0X31,0X31);
	holeClrInfo.m_clrTxUnSelected = RGB(0XF2,0X31,0X31);
	holeClrInfo.m_clrTxSelected = RGB(0XF2,0X31,0X31);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_POS_CRITICAL] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0XF0,0X31,0XF2);
	holeClrInfo.m_clrFill = Color(iAlpha,0XF0,0X31,0XF2);
	holeClrInfo.m_clrTxUnSelected = RGB(0XF0,0X31,0XF2);
	holeClrInfo.m_clrTxSelected = RGB(0XF0,0X31,0XF2);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_CALIBRATOR] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0,0X70,0XC0);
	holeClrInfo.m_clrFill = Color(iAlpha,0,0X70,0XC0);
	holeClrInfo.m_clrTxUnSelected = RGB(0,0X70,0XC0);
	holeClrInfo.m_clrTxSelected = RGB(0,0X70,0XC0);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_BUFFER] = holeClrInfo;

	// 内部质控暂时使用缓冲液的颜色
	holeClrInfo.m_clrFrame = Color(0,0X70,0XC0);
	holeClrInfo.m_clrFill = Color(iAlpha,0,0X70,0XC0);
	holeClrInfo.m_clrTxUnSelected = RGB(0,0X70,0XC0);
	holeClrInfo.m_clrTxSelected = RGB(0,0X70,0XC0);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_IC] = holeClrInfo;

#else
	holeClrInfo.m_clrFrame = Color(0XC6,0XC6,0XC6);
	holeClrInfo.m_clrFill = Color(255 * 0.3,0XC6,0XC6,0XC6);
	holeClrInfo.m_clrTxUnSelected = RGB(0X66,0X66,0X66);
	holeClrInfo.m_clrTxSelected = RGB(0X66,0X66,0X66);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_NONE] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0X20,0X44,0X7C);
	holeClrInfo.m_clrFill = Color(iAlpha,0X39,0X45,0X65);
	holeClrInfo.m_clrTxUnSelected = RGB(0X20,0X44,0X7C);
	holeClrInfo.m_clrTxSelected = RGB(iAlpha,0X39,0X45,0X65);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_UNKNOWN] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0X20,0X9F,0X85);
	holeClrInfo.m_clrFill = Color(iAlpha,0X20,0X9F,0X85);
	holeClrInfo.m_clrTxUnSelected = RGB(0X20,0X9F,0X85);
	holeClrInfo.m_clrTxSelected = RGB(0X20,0X9F,0X85);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_STANDARD] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0X33,0X83,0XFD);
	holeClrInfo.m_clrFill = Color(iAlpha,0X33,0X83,0XFD);
	holeClrInfo.m_clrTxUnSelected = RGB(0X33,0X83,0XFD);
	holeClrInfo.m_clrTxSelected = RGB(0X33,0X83,0XFD);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_NTC] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0X24,0XB7,0XEA);
	holeClrInfo.m_clrFill = Color(iAlpha,0X24,0XB7,0XEA);
	holeClrInfo.m_clrTxUnSelected = RGB(0X24,0XB7,0XEA);
	holeClrInfo.m_clrTxSelected = RGB(0X24,0XB7,0XEA);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_NEGATIVE] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0XC5,0X64,0X62);
	holeClrInfo.m_clrFill = Color(iAlpha,0XC5,0X64,0X62);
	holeClrInfo.m_clrTxUnSelected = RGB(0XC5,0X64,0X62);
	holeClrInfo.m_clrTxSelected = RGB(0XC5,0X64,0X62);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_POSITIVE] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0XF2,0X31,0X31);
	holeClrInfo.m_clrFill = Color(iAlpha,0XF2,0X31,0X31);
	holeClrInfo.m_clrTxUnSelected = RGB(0XF2,0X31,0X31);
	holeClrInfo.m_clrTxSelected = RGB(0XF2,0X31,0X31);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_POS_CRITICAL] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0XF0,0X31,0XF2);
	holeClrInfo.m_clrFill = Color(iAlpha,0XF0,0X31,0XF2);
	holeClrInfo.m_clrTxUnSelected = RGB(0XF0,0X31,0XF2);
	holeClrInfo.m_clrTxSelected = RGB(0XF0,0X31,0XF2);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_CALIBRATOR] = holeClrInfo;

	holeClrInfo.m_clrFrame = Color(0,0X70,0XC0);
	holeClrInfo.m_clrFill = Color(iAlpha,0,0X70,0XC0);
	holeClrInfo.m_clrTxUnSelected = RGB(0,0X70,0XC0);
	holeClrInfo.m_clrTxSelected = RGB(0,0X70,0XC0);
	m_mapSamTypeToHoleClrInfo[SAMPLE_TYPE_BUFFER] = holeClrInfo;
#endif

	return 0;
}

// 函数 CMySamPalteDlg::InitMapSamTypeToAbbr
// 作用：初始化InitMapSamTypeToAbbr。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 _T。
int CMySamPalteDlg::InitMapSamTypeToAbbr()
{
	m_mapSamTypeToAbbr[SAMPLE_TYPE_UNKNOWN] = _T("UN");
	m_mapSamTypeToAbbr[SAMPLE_TYPE_STANDARD] = _T("ST");
	m_mapSamTypeToAbbr[SAMPLE_TYPE_POSITIVE] = _T("PC");
	m_mapSamTypeToAbbr[SAMPLE_TYPE_NEGATIVE] = _T("NC");
	m_mapSamTypeToAbbr[SAMPLE_TYPE_NTC] = _T("NT");
	m_mapSamTypeToAbbr[SAMPLE_TYPE_IC] = _T("IC");

	return 0;
}

// 函数 CMySamPalteDlg::GetSampleTypeAbbr
// 作用：读取GetSampleTypeAbbr。
// 参数：eType。
// 返回：返回一段文字。
// 过程：函数里会调用 find、end、_T。
CString CMySamPalteDlg::GetSampleTypeAbbr(eSampleType eType)
{
	map<eSampleType,CString>::iterator iter = m_mapSamTypeToAbbr.find(eType);
	if(m_mapSamTypeToAbbr.end() == iter)
	{
		return _T("");
	}

	return iter->second;
}

// 函数 CMySamPalteDlg::CalcTotalColumnWidth
// 作用：计算CalcTotalColumnWidth。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHead。
int CMySamPalteDlg::CalcTotalColumnWidth()
{
	m_totalColW = 0;

	Node<CTitleInfo>* pNode = m_lnkTitleInfo.GetHead();
	while(NULL != pNode)
	{
		m_totalColW += pNode->data.m_colWidth;
		pNode = pNode->pNext;
	}

	return m_totalColW;
}

// 函数 CMySamPalteDlg::CalcTotalRowHeight
// 作用：计算CalcTotalRowHeight。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHead。
int CMySamPalteDlg::CalcTotalRowHeight()
{
	m_totalRowH = 0;
	Node<CRowInfo>* pNode = m_lnkRowInfo.GetHead();
	while(NULL != pNode)
	{
		m_totalRowH += pNode->data.m_rowH;
		pNode = pNode->pNext;
	}

	return m_totalRowH;
}

// 函数 CMySamPalteDlg::CalcRowColToShow
// 作用：计算CalcRowColToShow。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Width、GetWidth、Height。
int CMySamPalteDlg::CalcRowColToShow()
{
	if(m_colNum > 0)
	{
		if(m_totalColW > m_rcBody.Width())
		{
			if(-1 == m_colIdStartShow)
			{
				m_colIdStartShow = 0;
				m_ssColLeftIndent = 0;
			}

			int sum = m_lnkTitleInfo[m_colIdStartShow]->m_colWidth - m_ssColLeftIndent;
			int i = m_colIdStartShow + 1;
			for(;i < m_colNum;++i)
			{
				int colWidth = m_lnkTitleInfo[i]->m_colWidth;
				sum += colWidth;
				if(sum == m_rcBody.Width())
				{
					m_colIdEndShow = i;
					m_esColRightIndent = 0;
					break;
				}
				else if(sum > m_rcBody.Width())
				{
					m_colIdEndShow = i;
					m_esColRightIndent = sum - m_rcBody.Width();
					break;
				}
			}
		}
		else
		{
			m_colIdStartShow = 0;
			m_colIdEndShow = m_colNum - 1;
			m_ssColLeftIndent = 0;
			m_esColRightIndent = 0;
		}
	}
	else
	{
		m_colIdStartShow = -1;
		m_colIdEndShow = -1;
		m_ssColLeftIndent = 0;
		m_esColRightIndent = 0;
	}
	m_cdcW = GetWidth(m_colIdStartShow,m_colIdEndShow); 

	if(m_rowNum > 0)
	{
		if(m_totalRowH > m_rcBody.Height())
		{
			if(-1 == m_rowIdStartShow)
			{
				m_rowIdStartShow = 0;
				m_ssRowTopIndent = 0;
			}

			int sum = m_lnkRowInfo[m_rowIdStartShow]->m_rowH - m_ssRowTopIndent;
			int i = m_rowIdStartShow + 1;
			for(;i < m_rowNum;++i)
			{
				int rowH = m_lnkRowInfo[m_rowIdStartShow]->m_rowH;
				sum += rowH;
				if(sum == m_rcBody.Height())
				{
					m_rowIdEndShow = i;
					m_esRowBottomIndent = 0;
					break;
				}
				else if(sum > m_rcBody.Height())
				{
					m_rowIdEndShow = i;
					m_esRowBottomIndent = sum - m_rcBody.Height();
					break;
				}
			}
		}
		else
		{
			m_rowIdStartShow = 0;
			m_rowIdEndShow = m_rowNum - 1;
			m_ssRowTopIndent = 0;
			m_esRowBottomIndent = 0;
		}
	}
	else
	{
		m_rowIdStartShow = -1;
		m_rowIdEndShow = -1;
		m_ssRowTopIndent = 0;
		m_esRowBottomIndent = 0;
	}
	m_cdcH = GetHeight(m_rowIdStartShow,m_rowIdEndShow); 

	return 0;
}

// 函数 CMySamPalteDlg::CalcRowColToShowOnNoRowData
// 作用：计算CalcRowColToShowOnNoRowData。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Height。
int CMySamPalteDlg::CalcRowColToShowOnNoRowData()
{
	if(m_rcBody.Height() < 1)
	{
		return -1;
	}

	if(m_pxRowH <= 0)
	{
		return -2;
	}

	int sum = m_pxRowH;
	m_rowIdSeparatorStart = 0;
	m_rowIdSeparatorEnd = 0;
	while(sum < m_rcBody.Height())
	{
		sum += m_pxRowH;
		++m_rowIdSeparatorEnd;
	}
	m_esSeparatorBottomIndent = sum - m_rcBody.Height();

	return 0;
}

// 函数 CMySamPalteDlg::CalcColToShow
// 作用：计算CalcColToShow。
// 参数：newStartCol。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Width、GetWidth。
int CMySamPalteDlg::CalcColToShow(int newStartCol)
{
	if(m_colNum > 0 && newStartCol < m_colNum)
	{
		if(m_totalColW > m_rcBody.Width())
		{
			int errNum = 0;
			int sum = 0;
			int i = 0;

REFIND:
			if(newStartCol < 0)
			{
				m_colIdStartShow = 0;

				//防止陷入死循环,20211122,孙文郎
				if(++errNum > 10)
				{
					m_colIdStartShow = 0;
					m_colIdEndShow = m_colNum - 1;
					m_ssColLeftIndent = 0;
					m_esColRightIndent = 0;
					m_cdcW = GetWidth(m_colIdStartShow,m_colIdEndShow); 
					return -1;
				}
			}

			m_colIdStartShow = newStartCol;
			m_ssColLeftIndent = 0;
			m_esColRightIndent = 0;  

			sum = m_lnkTitleInfo[m_colIdStartShow]->m_colWidth;
			i = m_colIdStartShow + 1;
			for(;i < m_colNum;++i)
			{
				int colWidth = m_lnkTitleInfo[i]->m_colWidth;
				sum += colWidth;
				if(sum == m_rcBody.Width())
				{
					m_colIdEndShow = i;
					m_esColRightIndent = 0;
					break;
				}
				else if(sum > m_rcBody.Width())
				{
					m_colIdEndShow = i;
					m_esColRightIndent = sum - m_rcBody.Width();
					break;
				}
				else if(m_colNum - 1 == i)
				{
					--newStartCol;
					goto REFIND;
				}
			}
		}
		else
		{
			m_colIdStartShow = 0;
			m_colIdEndShow = m_colNum - 1;
			m_ssColLeftIndent = 0;
			m_esColRightIndent = 0;
		}
	}
	else
	{
		m_colIdStartShow = -1;
		m_colIdEndShow = -1;
		m_ssColLeftIndent = 0;
		m_esColRightIndent = 0;
	}
	m_cdcW = GetWidth(m_colIdStartShow,m_colIdEndShow); 

	return 0;
}

// 函数 CMySamPalteDlg::CalcRowToShow
// 作用：计算CalcRowToShow。
// 参数：newStartRow。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Height、GetHeight。
int CMySamPalteDlg::CalcRowToShow(int newStartRow)
{
	if(m_rowNum > 0 && newStartRow < m_rowNum)
	{
		if(m_totalRowH > m_rcBody.Height())
		{
			int errNum = 0;
			int sum = 0;
			int i = 0;

REFIND:
			if(newStartRow < 0)
			{
				m_rowIdStartShow = 0;

				//防止陷入死循环,20211122,孙文郎
				if(++errNum > 10)
				{
					m_rowIdStartShow = 0;
					m_rowIdEndShow = m_rowNum - 1;
					m_ssRowTopIndent = 0;
					m_esRowBottomIndent = 0;
					m_cdcH = GetHeight(m_rowIdStartShow,m_rowIdEndShow); 
					return -1;
				}
			}

			sum = m_lnkRowInfo[m_rowIdStartShow]->m_rowH - m_ssRowTopIndent;
			i = m_rowIdStartShow + 1;
			for(;i < m_rowNum;++i)
			{
				int rowH = m_lnkRowInfo[m_rowIdStartShow]->m_rowH;
				sum += rowH;
				if(sum == m_rcBody.Height())
				{
					m_rowIdEndShow = i;
					m_esRowBottomIndent = 0;
					break;
				}
				else if(sum > m_rcBody.Height())
				{
					m_rowIdEndShow = i;
					m_esRowBottomIndent = sum - m_rcBody.Height();
					break;
				}
				else
				{
					--newStartRow;
					goto REFIND;
				}
			}
		}
		else
		{
			m_rowIdStartShow = 0;
			m_rowIdEndShow = m_rowNum - 1;
			m_ssRowTopIndent = 0;
			m_esRowBottomIndent = 0;
		}
	}
	else
	{
		m_rowIdStartShow = -1;
		m_rowIdEndShow = -1;
		m_ssRowTopIndent = 0;
		m_esRowBottomIndent = 0;
	}
	m_cdcH = GetHeight(m_rowIdStartShow,m_rowIdEndShow); 

	return 0;
}

// 函数 CMySamPalteDlg::ScrollCol
// 作用：执行ScrollCol。
// 参数：pxHoriShift。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Width、abs。
int CMySamPalteDlg::ScrollCol(int pxHoriShift)
{
	if(m_colNum <= 0)
	{
		return -1;
	}

	if(pxHoriShift > 0 && m_horiScroll.m_curPixelPos + pxHoriShift > m_totalColW - m_rcBody.Width())
	{
		pxHoriShift -= (m_horiScroll.m_curPixelPos + pxHoriShift - m_totalColW + m_rcBody.Width());
	}

	if(pxHoriShift < 0 && m_horiScroll.m_curPixelPos + pxHoriShift < 0)
	{
		pxHoriShift -= (m_horiScroll.m_curPixelPos + pxHoriShift);
	}

	if(0 == pxHoriShift)
	{
		return 1;
	}

	int tempHoriShift = pxHoriShift;

	if(m_totalColW > m_rcBody.Width())
	{
		if(-1 == m_colIdStartShow)
		{
			m_colIdStartShow = 0;
			m_ssColLeftIndent = 0;
		}
		else
		{
			if(pxHoriShift > 0)
			{
				int colWidth = m_lnkTitleInfo[m_colIdStartShow]->m_colWidth;
				if(colWidth - m_ssColLeftIndent > pxHoriShift)
				{
					m_ssColLeftIndent += pxHoriShift;
				}
				else
				{
					int remainder = pxHoriShift - (colWidth - m_ssColLeftIndent);
					for(int i = m_colIdStartShow + 1;i < m_colNum;remainder -= m_lnkTitleInfo[i]->m_colWidth,++i)
					{
						if(remainder < m_lnkTitleInfo[i]->m_colWidth)
						{
							m_colIdStartShow = i;
							m_ssColLeftIndent = remainder;
							break;
						}
					}
				}
			}
			else
			{
				pxHoriShift = abs(pxHoriShift);
				if(m_ssColLeftIndent >= pxHoriShift)
				{
					m_ssColLeftIndent -= pxHoriShift;
				}
				else
				{
					int remainder = pxHoriShift - m_ssColLeftIndent;
					for(int i = m_colIdStartShow - 1;i >= 0;remainder -= m_lnkTitleInfo[i]->m_colWidth,--i)
					{
						//=号在这里至关重要,20211122,孙文郎
						if(remainder <= m_lnkTitleInfo[i]->m_colWidth)
						{
							m_colIdStartShow = i;
							m_ssColLeftIndent = m_lnkTitleInfo[i]->m_colWidth - remainder;
							break;
						}
					}
				}
			}
		}

		int sum = m_lnkTitleInfo[m_colIdStartShow]->m_colWidth - m_ssColLeftIndent;
		int i = m_colIdStartShow + 1;
		for(;i < m_colNum;++i)
		{
			sum += m_lnkTitleInfo[i]->m_colWidth;
			if(sum == m_rcBody.Width())
			{
				m_colIdEndShow = i;
				m_esColRightIndent = 0;
				break;
			}
			else if(sum > m_rcBody.Width())
			{
				m_colIdEndShow = i;
				m_esColRightIndent = sum - m_rcBody.Width();
				break;
			}
			else if(i + 1 == m_colNum)
			{
				if(abs(sum - m_rcBody.Width()) < 2)
				{
					m_colIdEndShow = i;
					m_esColRightIndent = 0;
				}
			}
		}
	}
	m_cdcW = GetWidth(m_colIdStartShow,m_colIdEndShow); 

	m_horiScroll.m_curPixelPos += tempHoriShift;
	m_horiScroll.CalcSliderPos();
	Invalidate(FALSE);

	return 0;
}

// 函数 CMySamPalteDlg::ScrollRow
// 作用：执行ScrollRow。
// 参数：pxVertShift。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Height、abs。
int CMySamPalteDlg::ScrollRow(int pxVertShift)
{
	if(m_rowNum <= 0)
	{
		return -1;
	}

	if((pxVertShift > 0) && (m_vertScroll.m_curPixelPos + pxVertShift > m_totalRowH - m_rcBody.Height()))
	{
		pxVertShift -= (m_vertScroll.m_curPixelPos + pxVertShift - m_totalRowH + m_rcBody.Height());
	}

	if((pxVertShift < 0) && (m_vertScroll.m_curPixelPos + pxVertShift < 0))
	{
		pxVertShift -= (m_vertScroll.m_curPixelPos + pxVertShift);
	}

	if(0 == pxVertShift)
	{
		return 1;
	}

#ifdef _DEBUG
	int temp1 = m_rowIdStartShow;
	int temp2 = m_ssRowTopIndent;

	if(2 == temp1 && 4 == temp2)
	{
		int tt = 0;
		++tt;
	}
#endif

	int tempVertShift = pxVertShift;

	if(m_totalRowH > m_rcBody.Height())
	{
		if(-1 == m_rowIdStartShow)
		{
			m_rowIdStartShow = 0;
			m_ssRowTopIndent = 0;
		}
		else
		{
			if(pxVertShift > 0)
			{
				int rowH = m_lnkRowInfo[m_rowIdStartShow]->m_rowH;
				if(rowH - m_ssRowTopIndent > pxVertShift)
				{
					m_ssRowTopIndent += pxVertShift;
				}
				else
				{
					int remainder = pxVertShift - (rowH - m_ssRowTopIndent);
					for(int i = m_rowIdStartShow + 1;i < m_rowNum;remainder -= m_lnkRowInfo[i]->m_rowH,++i)
					{
						if(remainder < m_lnkRowInfo[i]->m_rowH)
						{
							m_rowIdStartShow = i;
							m_ssRowTopIndent = remainder;
							break;
						}
					}
				}
			}
			else
			{
				pxVertShift = abs(pxVertShift);
				if(m_ssRowTopIndent >= pxVertShift)
				{
					m_ssRowTopIndent -= pxVertShift;
				}
				else
				{
					int remainder = pxVertShift - m_ssRowTopIndent;
					for(int i = m_rowIdStartShow - 1;i >= 0;remainder -= m_lnkRowInfo[i]->m_rowH,--i)
					{
						//=号在这里至关重要,20211122,孙文郎
						if(remainder <= m_lnkRowInfo[i]->m_rowH)
						{
							m_rowIdStartShow = i;
							m_ssRowTopIndent = m_lnkRowInfo[i]->m_rowH - remainder;
							break;
						}
					}
				}
			}
		}

		int sum = m_lnkRowInfo[m_rowIdStartShow]->m_rowH - m_ssRowTopIndent;
		int i = m_rowIdStartShow + 1;
		for(;i < m_rowNum;++i)
		{
			sum += m_lnkRowInfo[i]->m_rowH;
			if(sum == m_rcBody.Height())
			{
				m_rowIdEndShow = i;
				m_esRowBottomIndent = 0;
				break;
			}
			else if(sum > m_rcBody.Height())
			{
				m_rowIdEndShow = i;
				m_esRowBottomIndent = sum - m_rcBody.Height();
				break;
			}
			else if(i + 1 == m_rowNum)
			{
				if(abs(sum - m_rcBody.Height()) < 2)
				{
					m_rowIdEndShow = i;
					m_esRowBottomIndent = 0;
				}
#ifdef _DEBUG
				if(sum < m_rcBody.Height())
				{
					int tt = 0;
					++tt;
				}

				if(tempVertShift != pxVertShift)
				{  
					int kk = 0;
					++kk;
				}
#endif
			}
		}
	}
	m_cdcH = GetHeight(m_rowIdStartShow,m_rowIdEndShow); 

	m_vertScroll.m_curPixelPos += tempVertShift;

#ifdef _DEBUG
	if(m_rowIdStartShow * 28 + m_ssRowTopIndent > m_vertScroll.m_curPixelPos)
	{
		int kk = 0;
		++kk;
	}

	if(240 == m_vertScroll.m_curPixelPos && 10 == m_rowIdStartShow)
	{
		int kk = 0;
		++kk;
	}
#endif

	m_vertScroll.CalcSliderPos();
	Invalidate(FALSE);

	return 0;
}

// 函数 CMySamPalteDlg::ScrollColToFixPos
// 作用：执行ScrollColToFixPos。
// 参数：pxFixPos。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Width、abs、GetWidth。
int CMySamPalteDlg::ScrollColToFixPos(int pxFixPos)
{
	if(m_colNum <= 0)
	{
		return -1;
	}
	if(pxFixPos < 0)
	{
		return -2;
	}

	int newSum = 0;
	if(m_colNum > 0)
	{
		int sum = 0;
		for(int i = 0;i < m_colNum;++i)
		{
			sum += m_lnkTitleInfo[i]->m_colWidth;
			if(sum == pxFixPos)
			{
				m_colIdStartShow = i;
				m_ssColLeftIndent = 0;
				break;
			}
			else if(sum > pxFixPos)
			{
				m_colIdStartShow = i;
				m_ssColLeftIndent = m_lnkTitleInfo[i]->m_colWidth - (sum - pxFixPos);
				break;
			}
		}

		if(m_totalColW > m_rcBody.Width())
		{
			if(-1 == m_colIdStartShow)
			{
				m_colIdStartShow = 0;
				m_ssColLeftIndent = 0;
			}

			newSum = m_lnkTitleInfo[m_colIdStartShow]->m_colWidth - m_ssColLeftIndent;
			int i = m_colIdStartShow + 1;
			for(;i < m_colNum;++i)
			{
				newSum += m_lnkTitleInfo[i]->m_colWidth;
				if(newSum == m_rcBody.Width())
				{
					m_colIdEndShow = i;
					m_esColRightIndent = 0;
					break;
				}
				else if(newSum > m_rcBody.Width())
				{
					m_colIdEndShow = i;
					m_esColRightIndent = newSum - m_rcBody.Width();
					break;
				}
				else if(i + 1 == m_colNum)
				{
					if(abs(newSum - m_rcBody.Width()) < 2)
					{
						m_colIdEndShow = i;
						m_esColRightIndent = 0;
					}
				}
			}
		}
		else
		{
			m_colIdEndShow = m_colNum - 1;
			m_esColRightIndent = 0;
		}
	}
	else
	{
		m_colIdStartShow = -1;
		m_colIdEndShow = -1;
		m_ssColLeftIndent = 0;
		m_esColRightIndent = 0;
	}
	m_cdcW = GetWidth(m_colIdStartShow,m_colIdEndShow);

	return 0;
}

// 函数 CMySamPalteDlg::ScrollRowToFixPos
// 作用：执行ScrollRowToFixPos。
// 参数：pxFixPos。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Height、abs、GetHeight。
int CMySamPalteDlg::ScrollRowToFixPos(int pxFixPos)
{
	if(m_rowNum <= 0)
	{
		return -1;
	}
	if(pxFixPos < 0)
	{
		return -2;
	}

	if(m_rowNum > 0)
	{
		int sum = 0;
		for(int i = 0;i < m_rowNum;++i)
		{
			sum += m_lnkRowInfo[i]->m_rowH;
			if(sum == pxFixPos)
			{
				m_rowIdStartShow = i;
				m_ssRowTopIndent = 0;
				break;
			}
			else if(sum > pxFixPos)
			{
				m_rowIdStartShow = i;
				m_ssRowTopIndent = m_lnkRowInfo[i]->m_rowH - (sum - pxFixPos);
				break;
			}
		}

		if(m_totalRowH > m_rcBody.Height())
		{
			if(-1 == m_rowIdStartShow)
			{
				m_rowIdStartShow = 0;
				m_ssRowTopIndent = 0;
			}

			int newSum = m_lnkRowInfo[m_rowIdStartShow]->m_rowH - m_ssRowTopIndent;
			int i = m_rowIdStartShow + 1;
			for(;i < m_rowNum;++i)
			{
				newSum += m_lnkRowInfo[i]->m_rowH;
				if(newSum == m_rcBody.Height())
				{
					m_rowIdEndShow = i;
					m_esRowBottomIndent = 0;
					break;
				}
				else if(newSum > m_rcBody.Height())
				{
					m_rowIdEndShow = i;
					m_esRowBottomIndent = newSum - m_rcBody.Height();
					break;
				}
				else if(i + 1 == m_rowNum)
				{
					if(abs(newSum - m_rcBody.Height()) < 2)
					{
						m_rowIdEndShow = i;
						m_esRowBottomIndent = 0;
					}
				}
			}
		}
		else
		{
			m_rowIdEndShow = m_rowNum - 1;
			m_esRowBottomIndent = 0;
		}
	}
	else
	{
		m_rowIdStartShow = -1;
		m_rowIdEndShow = -1;
		m_ssRowTopIndent = 0;
		m_esRowBottomIndent = 0;
	}
	m_cdcH = GetHeight(m_rowIdStartShow,m_rowIdEndShow);

#ifdef _DEBUG
	if(m_rowIdEndShow < m_rowIdStartShow)
	{
		int tt = 0;
		++tt;
	}
#endif

	return 0;
}

// 函数 CMySamPalteDlg::CalcScrollPos
// 作用：计算CalcScrollPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Width、Height、CRect、CalcSliderPos。
void CMySamPalteDlg::CalcScrollPos()
{
	if(m_totalColW > m_rcBody.Width())
	{
		m_horiScroll.m_bScrollNeedShow = TRUE;	
	}
	else
	{
		m_horiScroll.m_bScrollNeedShow = FALSE;	
	}

	if(m_totalRowH > m_rcBody.Height())
	{
		m_vertScroll.m_bScrollNeedShow = TRUE;		
	}
	else
	{
		m_vertScroll.m_bScrollNeedShow = FALSE;	
	}

	if(m_horiScroll.m_bScrollNeedShow)
	{
		m_rcBody.bottom = m_rcLst.bottom - m_pxFrame - m_horiScroll.m_scrollH;
		if(m_vertScroll.m_bScrollNeedShow)
		{
			if(ESHVCM_HORI == m_eScrollHVCM)
			{
				m_horiScroll.m_rcScroll = CRect(m_pxFrame,m_rcLst.Height() - m_pxFrame - m_horiScroll.m_scrollH,m_rcLst.Width() - m_pxFrame,m_rcLst.Height() - m_pxFrame);
			}
			else
			{
				m_horiScroll.m_rcScroll = CRect(m_pxFrame,m_rcLst.Height()- m_pxFrame - m_horiScroll.m_scrollH,m_rcLst.Width() - m_pxFrame - m_vertScroll.m_scrollW,m_rcLst.Height() - m_pxFrame);
			}
		}
		else
		{
			m_horiScroll.m_rcScroll = CRect(m_pxFrame,m_rcLst.Height() - m_pxFrame - m_horiScroll.m_scrollH,m_rcLst.Width() - m_pxFrame,m_rcLst.Height() - m_pxFrame);
		}
	}
	else
	{
		m_rcBody.bottom = m_rcLst.bottom - m_pxFrame;
	}
	
	if(m_vertScroll.m_bScrollNeedShow)
	{
		m_rcBody.right = m_rcLst.right - m_pxFrame - m_vertScroll.m_scrollW;
		m_rcColHeader.right = m_rcLst.right - m_pxFrame - m_vertScroll.m_scrollW;
		if(m_horiScroll.m_bScrollNeedShow)
		{
			if(ESHVCM_VERT == m_eScrollHVCM)
			{
				m_vertScroll.m_rcScroll = CRect(m_rcLst.Width() - m_pxFrame - m_vertScroll.m_scrollW,m_pxFrame,m_rcLst.Width() - m_pxFrame,m_rcLst.Height() - m_pxFrame);
			}
			else
			{
				m_vertScroll.m_rcScroll = CRect(m_rcLst.Width() - m_pxFrame - m_vertScroll.m_scrollW,m_pxFrame,m_rcLst.Width() - m_pxFrame,m_rcLst.Height() - m_pxFrame - m_horiScroll.m_scrollH);
			}
		}
		else
		{
			m_vertScroll.m_rcScroll = CRect(m_rcLst.Width() - m_pxFrame - m_vertScroll.m_scrollW,m_pxFrame,m_rcLst.Width() - m_pxFrame,m_rcLst.Height() - m_pxFrame);
		}
	}
	else
	{
		m_rcBody.right = m_rcLst.right - m_pxFrame;
		m_rcColHeader.right = m_rcLst.right - m_pxFrame;
	}

	//防止水平滚动条信息设置错误，20211120，孙文郎
	if(m_horiScroll.m_bScrollNeedShow)
	{
		m_horiScroll.m_pixelTotal = m_totalColW;
		m_horiScroll.m_pixelForShow = m_rcBody.Width();
		m_horiScroll.CalcSliderPos();
	}
	else
	{
		m_horiScroll.m_rcScroll = CRect(0,0,0,0);
	}
	
	if(m_vertScroll.m_bScrollNeedShow)
	{
		m_vertScroll.m_pixelTotal = m_totalRowH;
		m_vertScroll.m_pixelForShow = m_rcBody.Height();
		m_vertScroll.CalcSliderPos();
	}
	else
	{
		m_vertScroll.m_rcScroll = CRect(0,0,0,0);
	}

	return;
}

// 函数 CMySamPalteDlg::CheckMaxMinSet
// 作用：判断CheckMaxMinSet是否成立。
// 参数：strTemp：字符串；maxMinInfo。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeSetMinValue、GetBeOnlyFloatNumber、_ttof、GetBeOnlyIntergerNumber、_ttoi、GetMinValue。
void CMySamPalteDlg::CheckMaxMinSet(CString& strTemp,CMaxMinInfo& maxMinInfo)
{
	double dData = 0;

	if(maxMinInfo.GetBeSetMinValue())
	{
		if(maxMinInfo.GetBeOnlyFloatNumber())
		{
			dData = _ttof(strTemp);
		}
		else if(maxMinInfo.GetBeOnlyIntergerNumber())
		{
			dData = _ttoi(strTemp);
		}
		else
		{
			dData = _ttof(strTemp);
		}

		if(dData < maxMinInfo.GetMinValue())
		{
			dData = maxMinInfo.GetMinValue();
			if(maxMinInfo.GetBeOnlyFloatNumber())
			{
				strTemp.Format(_T("%.2lf"),dData);
			}
			else if(maxMinInfo.GetBeOnlyIntergerNumber())
			{
				int iData = dData;
				strTemp.Format(_T("%d"),iData);
			}
			else
			{
				strTemp.Format(_T("%.2lf"),dData);
			}
		}
	}

	return;
}

// 函数 CMySamPalteDlg::GetHoleColorInfo
// 作用：读取GetHoleColorInfo。
// 参数：iRowId：整数；iColId：整数；holeClrInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSampleType、find、end。
int CMySamPalteDlg::GetHoleColorInfo(int iRowId,int iColId,CHoleColorInfo& holeClrInfo)
{
	if(m_rowNum < 1)
	{
		return -1;
	}
	if(m_colNum < 1)
	{
		return -2;
	}
	if(iRowId < 0)
	{
		return -3;
	}
	if(iRowId >= m_rowNum)
	{
		return -4;
	}
	if(iColId < 0)
	{
		return -5;
	}
	if(iColId >= m_colNum)
	{
		return -6;
	}
	if(NULL == m_pTubeInfo)
	{
		return -7;
	}

	eSampleType stTemp = m_pTubeInfo[iRowId * m_colNum + iColId].GetSampleType();
	map<eSampleType,CHoleColorInfo>::iterator iter = m_mapSamTypeToHoleClrInfo.find(stTemp);
	if(m_mapSamTypeToHoleClrInfo.end() == iter)
	{
		return -8;
	}

	holeClrInfo = iter->second;
	return 0;
}

// 函数 CMySamPalteDlg::SetBeTellParentRowSelChange
// 作用：设置SetBeTellParentRowSelChange。
// 参数：beTellParentSiteSelChange。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMySamPalteDlg::SetBeTellParentRowSelChange(BOOL beTellParentSiteSelChange)
{
	m_bTellParentSiteSelChange = beTellParentSiteSelChange;
	return;
}

// 函数 CMySamPalteDlg::GetBeTellParentRowSelChange
// 作用：读取GetBeTellParentRowSelChange。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMySamPalteDlg::GetBeTellParentRowSelChange()
{
	return m_bTellParentSiteSelChange;
}

// 函数 CMySamPalteDlg::InitFontHeader
// 作用：初始化InitFontHeader。
// 参数：lfHeight。
// 返回：没有返回值。
// 过程：函数里会调用 _tcscpy、_T、CreateFontIndirect。
void CMySamPalteDlg::InitFontHeader(int lfHeight)
{
	m_logFontHeader.lfHeight = lfHeight;
	m_logFontHeader.lfWidth = 0;
	m_logFontHeader.lfEscapement = 0;
	m_logFontHeader.lfOrientation = 400;
	m_logFontHeader.lfWeight = FW_NORMAL;
	m_logFontHeader.lfItalic = FALSE;
	m_logFontHeader.lfUnderline = FALSE;
	m_logFontHeader.lfStrikeOut = 0;
	m_logFontHeader.lfCharSet = ANSI_CHARSET;
	m_logFontHeader.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logFontHeader.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logFontHeader.lfQuality = PROOF_QUALITY;
	m_logFontHeader.lfPitchAndFamily = VARIABLE_PITCH | FF_SCRIPT;
	_tcscpy(m_logFontHeader.lfFaceName,  _T("微软雅黑"));

	m_fontSetHeader.CreateFontIndirect(&m_logFontHeader);  
}

// 函数 CMySamPalteDlg::SetMyHeaderFont
// 作用：设置SetMyHeaderFont。
// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double、_tcscpy、DeleteObject、CreateFontIndirect。
void CMySamPalteDlg::SetMyHeaderFont(CString fontName,int nHeight,int nWeight /*= FW_NORMAL*/,FONT_UNIT_TYPE fontUnitType /*= TYPE_PIXEL*/) //nHeight单位为 磅，即1/72英寸
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFontHeader.lfHeight = (double(nHeight * fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFontHeader.lfHeight = nHeight;
	}

	_tcscpy(m_logFontHeader.lfFaceName, fontName);
	m_logFontHeader.lfWeight = nWeight;
	m_fontSetHeader.DeleteObject();
	m_fontSetHeader.CreateFontIndirect(&m_logFontHeader);
}

// 函数 CMySamPalteDlg::SetMyHeaderFont
// 作用：设置SetMyHeaderFont。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、CreateFontIndirect。
void CMySamPalteDlg::SetMyHeaderFont() 
{
	m_fontSetHeader.DeleteObject();
	m_fontSetHeader.CreateFontIndirect(&m_logFontHeader);
}

// 函数 CMySamPalteDlg::InitFontTitle
// 作用：初始化InitFontTitle。
// 参数：lfHeight。
// 返回：没有返回值。
// 过程：函数里会调用 _tcscpy、_T、CreateFontIndirect。
void CMySamPalteDlg::InitFontTitle(int lfHeight)
{
	m_logFontTitle.lfHeight = lfHeight;
	m_logFontTitle.lfWidth = 0;
	m_logFontTitle.lfEscapement = 0;
	m_logFontTitle.lfOrientation = 400;
	m_logFontTitle.lfWeight = FW_NORMAL;
	m_logFontTitle.lfItalic = FALSE;
	m_logFontTitle.lfUnderline = FALSE;
	m_logFontTitle.lfStrikeOut = 0;
	m_logFontTitle.lfCharSet = ANSI_CHARSET;
	m_logFontTitle.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logFontTitle.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logFontTitle.lfQuality = PROOF_QUALITY;
	m_logFontTitle.lfPitchAndFamily = VARIABLE_PITCH | FF_SCRIPT;
	_tcscpy(m_logFontTitle.lfFaceName, _T("微软雅黑"));

	m_fontSetTitle.CreateFontIndirect(&m_logFontTitle);  
}

// 函数 CMySamPalteDlg::SetMyTitleFont
// 作用：设置SetMyTitleFont。
// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double、_tcscpy、DeleteObject、CreateFontIndirect。
void CMySamPalteDlg::SetMyTitleFont(CString fontName,int nHeight,int nWeight /*= FW_NORMAL*/,FONT_UNIT_TYPE fontUnitType /*= TYPE_PIXEL*/)
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFontTitle.lfHeight = (double(nHeight * fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFontTitle.lfHeight = nHeight;
	}

	_tcscpy(m_logFontTitle.lfFaceName,fontName);
	m_logFontTitle.lfWeight = nWeight;
	m_fontSetTitle.DeleteObject();
	m_fontSetTitle.CreateFontIndirect(&m_logFontTitle);
}

// 函数 CMySamPalteDlg::SetMyTitleFont
// 作用：设置SetMyTitleFont。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、CreateFontIndirect。
void CMySamPalteDlg::SetMyTitleFont()
{
	m_fontSetTitle.DeleteObject();
	m_fontSetTitle.CreateFontIndirect(&m_logFontTitle);
}

// 函数 CMySamPalteDlg::InitFontAbbr
// 作用：初始化InitFontAbbr。
// 参数：lfHeight。
// 返回：没有返回值。
// 过程：函数里会调用 _tcscpy、_T、CreateFontIndirect。
void CMySamPalteDlg::InitFontAbbr(int lfHeight)
{
	m_logFontAbbr.lfHeight = lfHeight;
	m_logFontAbbr.lfWidth = 0;
	m_logFontAbbr.lfEscapement = 0;
	m_logFontAbbr.lfOrientation = 400;
	m_logFontAbbr.lfWeight = FW_NORMAL;
	m_logFontAbbr.lfItalic = FALSE;
	m_logFontAbbr.lfUnderline = FALSE;
	m_logFontAbbr.lfStrikeOut = 0;
	m_logFontAbbr.lfCharSet = ANSI_CHARSET;
	m_logFontAbbr.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logFontAbbr.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logFontAbbr.lfQuality = PROOF_QUALITY;
	m_logFontAbbr.lfPitchAndFamily = VARIABLE_PITCH | FF_SCRIPT;
	_tcscpy(m_logFontAbbr.lfFaceName, _T("微软雅黑"));

	m_fontAbbr.CreateFontIndirect(&m_logFontAbbr);  
}

// 函数 CMySamPalteDlg::SetMyFontAbbr
// 作用：设置SetMyFontAbbr。
// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double、_tcscpy、DeleteObject、CreateFontIndirect。
void CMySamPalteDlg::SetMyFontAbbr(CString fontName,int nHeight,int nWeight /*= FW_NORMAL*/,FONT_UNIT_TYPE fontUnitType /*= TYPE_PIXEL*/)
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFontAbbr.lfHeight = (double(nHeight * fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFontAbbr.lfHeight = nHeight;
	}

	_tcscpy(m_logFontAbbr.lfFaceName,fontName);
	m_logFontAbbr.lfWeight = nWeight;
	m_fontAbbr.DeleteObject();
	m_fontAbbr.CreateFontIndirect(&m_logFontAbbr);
}

// 函数 CMySamPalteDlg::SetMyFontAbbr
// 作用：设置SetMyFontAbbr。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、CreateFontIndirect。
void CMySamPalteDlg::SetMyFontAbbr()
{
	m_fontAbbr.DeleteObject();
	m_fontAbbr.CreateFontIndirect(&m_logFontAbbr);
}

