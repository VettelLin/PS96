// 【交接】 GeneralPcr\ColorSelectDlg.cpp
// 作用：ColorSelectDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CColorSelectDlg、CDialogEx、InitColorInfo、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_CREATE。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "ColorSelectDlg.h"
#include "GeneralPcr.h"

// CColorSelectDlg dialog
IMPLEMENT_DYNAMIC(CColorSelectDlg, CDialogEx)

// 函数 CColorSelectDlg::CColorSelectDlg
// 作用：执行CColorSelectDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 InitColorInfo。
CColorSelectDlg::CColorSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColorSelectDlg::IDD, pParent)
{
	m_frameWidth = 1;
	m_roundValue = 8;
	m_iWndWidth = 255;
	m_iWndHeight = 275;
	m_iCaptionHeight = 52;
	m_pParent = pParent;
	m_iCellRowId = -1;
	m_iCellColId = -1;

	m_iHoriInterval = 5;
	m_iVertInterval = 0;
	m_iStartX = 5;
	m_iStartY = 8;
	m_iClrBlockW = 20;
	m_iClrBlockH = 20;

	m_iThemeStartX = 0;
	m_iThemeStartY = 0;
	m_iBodyStartX = 0;
	m_iBodyStartY = 0;
	m_iStandardStartX = 0;
	m_iStandardStartY = 0;
	m_iDefStartX = 0;
	m_iDefStartY = 0;

	InitColorInfo();
}

// 函数 CColorSelectDlg::~CColorSelectDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CColorSelectDlg::~CColorSelectDlg()
{

}

// 函数 CColorSelectDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CColorSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CColorSelectDlg, CDialogEx)
	ON_WM_ERASEBKGND() 
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(ID_CROSSSETDLG_BT_SAVE,&CColorSelectDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_CROSSSETDLG_BT_CANCEL,&CColorSelectDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// 函数 CColorSelectDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CColorSelectDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);

	DrawRoundRectangleNew(&memDc,0,0,rect.Width() - m_frameWidth,rect.Height() - m_frameWidth,m_roundValue,m_roundValue,m_roundValue,m_roundValue,TRUE,Color(0XC2,0XC1,0XC1),m_frameWidth,TRUE,Color(0XFF,0XFF,0XFF),1);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	//绘制颜色块
	int iStartX = m_iStartX,iStartY = m_iStartY;
	int iTxStartX = 12 * m_dHoriRatio,iTxEndX = 100 * m_dHoriRatio,iTxHeight = 25 * m_dVertRatio;
	int iTempInt1 = 0,iTempInt2 = 0,iTempInt3 = m_iClrBlockH + 5 * m_dVertRatio + 2 * m_dVertRatio,iTempInt4 = m_iClrBlockH + 5 * m_dVertRatio;
	
	int iRowNum = COLORROWNUM;
	int iColNum = COLORCOLUMNNUM;

	Graphics graphics(memDc.m_hDC);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	Pen pen(Color(226,228,231),1);

	memDc.DrawText(theApp.m_pLangInfo->GetText(302),CRect(iTxStartX,iStartY,iTxEndX,iStartY + iTxHeight),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	iStartY += iTxHeight;
	iStartY += 2 * m_dVertRatio;

	m_iThemeStartX = iStartX;
	m_iThemeStartY = iStartY;
	for(int j = 0;j < iColNum;++j)
	{
		iTempInt1 = m_iThemeStartX + j * m_iClrBlockW + j * m_iHoriInterval;
		SolidBrush brush(m_aryThemeClr[j]);
		graphics.FillRectangle(&brush,iTempInt1,m_iThemeStartY,m_iClrBlockW,m_iClrBlockH);
		graphics.DrawRectangle(&pen,iTempInt1,m_iThemeStartY,m_iClrBlockW,m_iClrBlockH);
	}
	m_rcClrTheme = CRect(m_iThemeStartX,m_iThemeStartY,m_iThemeStartX + iColNum * m_iClrBlockW + (iColNum - 1) * m_iHoriInterval,m_iThemeStartY + m_iClrBlockH);
	iStartY += iTempInt4;

	m_iBodyStartX = iStartX;
	m_iBodyStartY = iStartY;
	for(int i = 0;i < iRowNum;++i)
	{
		for(int j = 0;j < iColNum;++j)
		{
			iTempInt1 = m_iBodyStartX + j * m_iClrBlockW + j * m_iHoriInterval;
			iTempInt2 = m_iBodyStartY + i * m_iClrBlockH + i * m_iVertInterval;

			SolidBrush brush(m_aryClr[i][j]);
			graphics.FillRectangle(&brush,iTempInt1,iTempInt2,m_iClrBlockW,m_iClrBlockH + 1);
		}
	}
	for(int j = 0;j < iColNum;++j)
	{
		iTempInt1 = m_iBodyStartX + j * m_iClrBlockW + j * m_iHoriInterval;
		graphics.DrawRectangle(&pen,iTempInt1,m_iBodyStartY,m_iClrBlockW,iRowNum * m_iClrBlockH + (iRowNum - 1) * m_iVertInterval + 1);
	}
	m_rcClrBody = CRect(m_iBodyStartX,m_iBodyStartY,m_iBodyStartX + iColNum * m_iClrBlockW + (iColNum - 1) * m_iHoriInterval,m_iBodyStartY + iRowNum * m_iClrBlockH + (iRowNum - 1) * m_iVertInterval);
	iStartY += (iRowNum * m_iClrBlockH + (iRowNum - 1) * m_iVertInterval); 
	iStartY += 5 * m_dVertRatio;

	memDc.DrawText(theApp.m_pLangInfo->GetText(303),CRect(iTxStartX,iStartY,iTxEndX,iStartY + iTxHeight),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	iStartY += iTxHeight;
	iStartY += 2 * m_dVertRatio;

	m_iStandardStartX = iStartX;
	m_iStandardStartY = iStartY;
	for(int j = 0;j < iColNum;++j)
	{
		iTempInt1 = m_iStandardStartX + j * m_iClrBlockW + j * m_iHoriInterval;
		SolidBrush brush(m_aryStandardClr[j]);
		graphics.FillRectangle(&brush,iTempInt1,m_iStandardStartY,m_iClrBlockW,m_iClrBlockH);
		graphics.DrawRectangle(&pen,iTempInt1,m_iStandardStartY,m_iClrBlockW,m_iClrBlockH);
	}
	m_rcClrStandard = CRect(m_iStandardStartX,m_iStandardStartY,m_iStandardStartX + iColNum * m_iClrBlockW + (iColNum - 1) * m_iHoriInterval,m_iStandardStartY + m_iClrBlockH);
	iStartY += iTempInt4;

	memDc.DrawText(theApp.m_pLangInfo->GetText(304),CRect(iTxStartX,iStartY,iTxEndX,iStartY + iTxHeight),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	iStartY += iTxHeight;
	iStartY += 2 * m_dVertRatio;

	m_iDefStartX = iStartX;
	m_iDefStartY = iStartY;
	for(int j = 0;j < DEFAULTCOLORNUM;++j)
	{
		iTempInt1 = m_iDefStartX + j * m_iClrBlockW + j * m_iHoriInterval;
		SolidBrush brush(m_aryDefClr[j]);
		graphics.FillRectangle(&brush,iTempInt1,m_iDefStartY,m_iClrBlockW,m_iClrBlockH);
		graphics.DrawRectangle(&pen,iTempInt1,m_iDefStartY,m_iClrBlockW,m_iClrBlockH);
	}
	m_rcClrDefault = CRect(m_iDefStartX,m_iDefStartY,m_iDefStartX + DEFAULTCOLORNUM * m_iClrBlockW + (DEFAULTCOLORNUM - 1) * m_iHoriInterval,m_iDefStartY + m_iClrBlockH);

	graphics.ReleaseHDC(memDc.m_hDC);

	memDc.SelectObject(pOldFont);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CColorSelectDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CColorSelectDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iWndWidth *= m_dHoriRatio;
	m_iWndHeight *= m_dVertRatio;

	m_iHoriInterval *= m_dHoriRatio;
	m_iVertInterval *= m_dVertRatio;
	m_iStartX *= m_dHoriRatio;
	m_iStartY *= m_dVertRatio;
	m_iClrBlockW *= m_dHoriRatio;
	m_iClrBlockH *= m_dVertRatio;

	m_roundValue *= m_dHoriRatio;
	m_frameWidth *= m_dHoriRatio;
	if(m_frameWidth < 1)
	{
		m_frameWidth = 1;
	}

	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CColorSelectDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::OnLButtonDown。
void CColorSelectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	return CDialogEx::OnLButtonDown(nFlags,point);
}

// 函数 CColorSelectDlg::OnLButtonUp
// 作用：松开鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、PtInRect。
void CColorSelectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(NULL == m_pParent->GetSafeHwnd())
	{
		return CDialogEx::OnLButtonUp(nFlags,point);
	}

	BOOL bInTheme = FALSE,bInThemeBody = FALSE,bInStandard = FALSE,bInDef = FALSE;
	if(m_rcClrTheme.PtInRect(point))
	{
		bInTheme = TRUE;
	}
	else if(m_rcClrBody.PtInRect(point))
	{
		bInThemeBody = TRUE;
	}
	else if(m_rcClrStandard.PtInRect(point))
	{
		bInStandard = TRUE;
	}
	else if(m_rcClrDefault.PtInRect(point))
	{
		bInDef = TRUE;
	}

	if(!bInTheme && !bInThemeBody && !bInStandard && !bInDef)
	{
		return CDialogEx::OnLButtonUp(nFlags,point);
	}

	CRect rcTemp;
	Color clrSelected = 0;

	if(bInTheme)
	{
		for(int j = 0;j < COLORCOLUMNNUM;++j)
		{
			rcTemp.left = m_iThemeStartX + j * m_iClrBlockW + j * m_iHoriInterval;
			rcTemp.top = m_iThemeStartY;
			rcTemp.right = rcTemp.left + m_iClrBlockW;
			rcTemp.bottom = rcTemp.top + m_iClrBlockH;
			if(rcTemp.PtInRect(point))
			{
				clrSelected = m_aryThemeClr[j];
				break;
			}
		}
	}
	else if(bInThemeBody)
	{
		for(int i = 0;i < COLORROWNUM;++i)
		{
			for(int j = 0;j < COLORCOLUMNNUM;++j)
			{
				rcTemp.left = m_iBodyStartX + j * m_iClrBlockW + j * m_iHoriInterval;
				rcTemp.top = m_iBodyStartY + i * m_iClrBlockH + i * m_iVertInterval;
				rcTemp.right = rcTemp.left + m_iClrBlockW;
				rcTemp.bottom = rcTemp.top + m_iClrBlockH;
				if(rcTemp.PtInRect(point))
				{
					clrSelected = m_aryClr[i][j];
					break;
				}
			}
		}
	}
	else if(bInStandard)
	{
		for(int j = 0;j < COLORCOLUMNNUM;++j)
		{
			rcTemp.left = m_iStandardStartX + j * m_iClrBlockW + j * m_iHoriInterval;
			rcTemp.top = m_iStandardStartY;
			rcTemp.right = rcTemp.left + m_iClrBlockW;
			rcTemp.bottom = rcTemp.top + m_iClrBlockH;
			if(rcTemp.PtInRect(point))
			{
				clrSelected = m_aryStandardClr[j];
				break;
			}
		}
	}
	else if(bInDef)
	{
		for(int j = 0;j < DEFAULTCOLORNUM;++j)
		{
			rcTemp.left = m_iDefStartX + j * m_iClrBlockW + j * m_iHoriInterval;
			rcTemp.top = m_iDefStartY;
			rcTemp.right = rcTemp.left + m_iClrBlockW;
			rcTemp.bottom = rcTemp.top + m_iClrBlockH;
			if(rcTemp.PtInRect(point))
			{
				clrSelected = m_aryDefClr[j];
				break;
			}
		}
	}
	
	m_pParent->PostMessage(WM_SELECTNEWCOLOR,clrSelected.ToCOLORREF(),MAKELPARAM(m_iCellRowId,m_iCellColId));
	ShowWindow(SW_HIDE);

	return;
}

// 函数 CColorSelectDlg::OnSetFocus
// 作用：响应 Windows 或自定义消息 OnSetFocus。
// 参数：pOldWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::OnSetFocus(CWnd* pOldWnd)
{
	return;
}

// 函数 CColorSelectDlg::OnKillFocus
// 作用：响应 Windows 或自定义消息 OnKillFocus。
// 参数：pNewWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindowVisible、ShowWindow。
void CColorSelectDlg::OnKillFocus(CWnd* pNewWnd)
{
	CWnd* pEdit = &m_edRgbValue;
	if(IsWindowVisible() && pEdit != pNewWnd)
	{
		ShowWindow(SW_HIDE);
	}

	return;
}

// 函数 CColorSelectDlg::OnShowWindow
// 作用：响应 Windows 或自定义消息 OnShowWindow。
// 参数：bShow：是或否；nStatus：整数。
// 返回：没有返回值。
// 过程：函数里会调用 SetFocus。
void CColorSelectDlg::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);

	if(bShow)
	{
		SetFocus();
	}
	return;
}

// 函数 CColorSelectDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、GetParent、CreateCtrl、InitDlg、InitCtrl、SetCtrlPos。
BOOL CColorSelectDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	SetWindowPos(GetParent(),0,0,m_iWndWidth,m_iWndHeight,SWP_NOZORDER);

	CreateCtrl();
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	ShowCtrl();

	return TRUE;
}

// 函数 CColorSelectDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateCkBt、CreateSt、CreateEd、CreateCb、CreateLst。
void CColorSelectDlg::CreateCtrl()
{
	CreateBt();
	CreateCkBt();
	CreateSt();
	CreateEd();
	CreateCb();
	CreateLst();
}

// 函数 CColorSelectDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CColorSelectDlg::CreateBt()
{
	m_btSave.Create(_T("确定"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_CROSSSETDLG_BT_SAVE);
	m_btCancel.Create(_T("取消"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_CROSSSETDLG_BT_CANCEL);
}

// 函数 CColorSelectDlg::CreateCkBt
// 作用：创建或加入CreateCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::CreateCkBt()
{
	
}

// 函数 CColorSelectDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::CreateSt()
{
	
}

// 函数 CColorSelectDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CColorSelectDlg::CreateEd()
{
	m_edRgbValue.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_CROSSSETDLG_ED_RGBVALUE);
}

// 函数 CColorSelectDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::CreateCb()
{
	
}

// 函数 CColorSelectDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::CreateLst()
{
	
}

// 函数 CColorSelectDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CColorSelectDlg::InitDlg()
{
	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,14 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CColorSelectDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCkBt、InitSt、InitEd、InitCb、InitLst。
void CColorSelectDlg::InitCtrl()
{
	InitBt();
	InitCkBt();
	InitSt();
	InitEd();
	InitCb();
	InitLst();
}

// 函数 CColorSelectDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB。
void CColorSelectDlg::InitBt()
{
	int iFontH = 12 * CFontSet::m_dTxRatio;

	m_btSave.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btSave.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);

	m_btCancel.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btCancel.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
}

// 函数 CColorSelectDlg::InitCkBt
// 作用：初始化InitCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::InitCkBt()
{
	
}

// 函数 CColorSelectDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::InitSt()
{
	
}

// 函数 CColorSelectDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、SetTextColor、RGB。
void CColorSelectDlg::InitEd()
{
	int iFontH = 12 * m_dTxRatio;

	m_edRgbValue.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edRgbValue.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edRgbValue.SetSelectedBkColor(CLR_SOFT_THEME,CLR_SOFT_THEME,CLR_SOFT_THEME,CLR_SOFT_THEME);
	m_edRgbValue.SetTextColor(RGB(0X66,0X66,0X66),RGB(0X66,0X66,0X66),RGB(0X66,0X66,0X66),RGB(0XC6,0XC6,0XC6));
	m_edRgbValue.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edRgbValue.EnableWindow(FALSE);
}

// 函数 CColorSelectDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::InitCb()
{
	
}

// 函数 CColorSelectDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CColorSelectDlg::InitLst()
{
	return;
}

// 函数 CColorSelectDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、rcUseful、SetWindowPos。
void CColorSelectDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	CRect rcUseful(0,0,0,0);
	m_btSave.SetWindowPos(this,rcUseful.left + 92 * m_dHoriRatio,rcUseful.top + 192 * m_dVertRatio,60 * m_dHoriRatio,24 * m_dVertRatio,SWP_NOZORDER);
	m_btCancel.SetWindowPos(this,rcUseful.left + 731 * m_dHoriRatio,rcUseful.top + 334 * m_dVertRatio,90 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);
	m_edRgbValue.SetWindowPos(this,rcUseful.left + 40 * m_dHoriRatio,rcUseful.top + 156 * m_dVertRatio,112 * m_dHoriRatio,24 * m_dVertRatio,SWP_NOZORDER);
}

// 函数 CColorSelectDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CColorSelectDlg::ShowCtrl()
{
	//m_btSave.ShowWindow(SW_SHOW);
	//m_edRgbValue.ShowWindow(SW_SHOW);
	//m_btCancel.ShowWindow(SW_SHOW);

	return;
}

// 函数 CColorSelectDlg::OnBnClickedSave
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CColorSelectDlg::OnBnClickedSave()
{
	ShowWindow(SW_HIDE);
	return;
}

// 函数 CColorSelectDlg::OnBnClickedCancel
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CColorSelectDlg::OnBnClickedCancel()
{
	ShowWindow(SW_HIDE);
	return;
}

// 函数 CColorSelectDlg::SetRoundRect
// 作用：设置SetRoundRect。
// 参数：x；y。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetClientRect、CreateRoundRectRgn、SetWindowRgn。
BOOL CColorSelectDlg::SetRoundRect(int x /*= 5*/,int y /*= 5*/)
{
	CRgn rgnWnd;
	CRect rcWnd;
	GetClientRect(&rcWnd);
	rgnWnd.CreateRoundRectRgn(rcWnd.left,rcWnd.top,rcWnd.right,rcWnd.bottom,x,y);
	if(!SetWindowRgn(rgnWnd,TRUE))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

// 函数 CColorSelectDlg::InitColorInfo
// 作用：初始化InitColorInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Color。
void CColorSelectDlg::InitColorInfo()
{
	m_aryClr[0][0] = Color(242,242,242);
	m_aryClr[1][0] = Color(217,217,217);
	m_aryClr[2][0] = Color(191,191,191);
	m_aryClr[3][0] = Color(165,165,165);
	m_aryClr[4][0] = Color(128,128,128);

	m_aryClr[0][1] = Color(127,127,127);
	m_aryClr[1][1] = Color(89,89,89);
	m_aryClr[2][1] = Color(64,64,64);
	m_aryClr[3][1] = Color(38,38,38);
	m_aryClr[4][1] = Color(13,13,13);

	m_aryClr[0][2] = Color(221,217,195);
	m_aryClr[1][2] = Color(196,189,151);
	m_aryClr[2][2] = Color(147,137,83);
	m_aryClr[3][2] = Color(73,68,41);
	m_aryClr[4][2] = Color(29,27,16);

	m_aryClr[0][3] = Color(198,217,240);
	m_aryClr[1][3] = Color(141,179,226);
	m_aryClr[2][3] = Color(84,141,212);
	m_aryClr[3][3] = Color(23,54,93);
	m_aryClr[4][3] = Color(15,36,62);

	m_aryClr[0][4] = Color(219,229,241);
	m_aryClr[1][4] = Color(184,204,228);
	m_aryClr[2][4] = Color(149,179,215);
	m_aryClr[3][4] = Color(54,96,146);
	m_aryClr[4][4] = Color(36,64,97);

	m_aryClr[0][5] = Color(242,220,219);
	m_aryClr[1][5] = Color(229,185,183);
	m_aryClr[2][5] = Color(217,150,148);
	m_aryClr[3][5] = Color(149,55,52);
	m_aryClr[4][5] = Color(99,36,35);


	m_aryClr[0][6] = Color(235,241,221);
	m_aryClr[1][6] = Color(215,227,188);
	m_aryClr[2][6] = Color(195,214,155);
	m_aryClr[3][6] = Color(118,146,60);
	m_aryClr[4][6] = Color(79,97,40);

	m_aryClr[0][7] = Color(229,224,236);
	m_aryClr[1][7] = Color(204,193,217);
	m_aryClr[2][7] = Color(178,161,199);
	m_aryClr[3][7] = Color(95,73,122);
	m_aryClr[4][7] = Color(63,49,81);

	m_aryClr[0][8] = Color(219,238,243);
	m_aryClr[1][8] = Color(183,221,232);
	m_aryClr[2][8] = Color(146,205,220);
	m_aryClr[3][8] = Color(49,133,155);
	m_aryClr[4][8] = Color(32,88,103);

	m_aryClr[0][9] = Color(253,234,218);
	m_aryClr[1][9] = Color(251,213,181);
	m_aryClr[2][9] = Color(250,192,143);
	m_aryClr[3][9] = Color(227,108,9);
	m_aryClr[4][9] = Color(151,72,6);

	m_aryThemeClr[0] = Color(255,255,255);
	m_aryThemeClr[1] = Color(0,0,0);
	m_aryThemeClr[2] = Color(238,236,225);
	m_aryThemeClr[3] = Color(31,73,125);
	m_aryThemeClr[4] = Color(79,129,189);
	m_aryThemeClr[5] = Color(192,80,77);
	m_aryThemeClr[6] = Color(155,187,89);
	m_aryThemeClr[7] = Color(128,100,162);
	m_aryThemeClr[8] = Color(75,172,198);
	m_aryThemeClr[9] = Color(247,150,70);

	m_aryStandardClr[0] = Color(192,0,0);
	m_aryStandardClr[1] = Color(255,0,0);
	m_aryStandardClr[2] = Color(255,192,0);
	m_aryStandardClr[3] = Color(255,255,0);
	m_aryStandardClr[4] = Color(146,208,80);
	m_aryStandardClr[5] = Color(0,176,80);
	m_aryStandardClr[6] = Color(0,176,240);
	m_aryStandardClr[7] = Color(0,112,192);
	m_aryStandardClr[8] = Color(0,32,96);
	m_aryStandardClr[9] = Color(112,48,160);
	
	m_aryDefClr[0] = Color(0,0,255);
	m_aryDefClr[1] = Color(255,0,0);
	m_aryDefClr[2] = Color(0,255,0);
	m_aryDefClr[3] = Color(138,0,0);
	m_aryDefClr[4] = Color(225,199,21);
	m_aryDefClr[5] = Color(0XFA,0X91,0X91);
}



