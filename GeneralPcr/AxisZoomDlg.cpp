// 【交接】 GeneralPcr\AxisZoomDlg.cpp
// 作用：AxisZoomDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CAxisZoomDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_CREATE、ON_WM_LBUTTONDOWN。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "AxisZoomDlg.h"
#include "GeneralPcr.h"

// CAxisZoomDlg dialog
IMPLEMENT_DYNAMIC(CAxisZoomDlg, CDialogEx)

// 函数 CAxisZoomDlg::CAxisZoomDlg
// 作用：执行CAxisZoomDlg。
// 参数：pParent：指针，指向调用方传入的对象；bHaveLogFunc：是或否；bLogMode：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisZoomDlg::CAxisZoomDlg(CWnd* pParent /*=NULL*/,BOOL bHaveLogFunc /*= FALSE*/,BOOL bLogMode /*= FALSE*/)
	: CDialogEx(CAxisZoomDlg::IDD, pParent)
{
	m_hWndParent = NULL;
	m_iCrvId = 0;
	m_iAngleRadius = 20;
	m_iFrameWidth = 1;
	m_iWndWidth = 600;
	m_iWndHeight = 456;
	m_iCapHeight = 60;
	m_bChanged = FALSE;

	m_bHaveLogFunc = bHaveLogFunc;
	m_bLogMode = bLogMode;
	m_bLogModeChanged = FALSE;
	m_bNewLogMode = FALSE;
	m_bUseDefFunc = TRUE;
}

// 函数 CAxisZoomDlg::~CAxisZoomDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CAxisZoomDlg::~CAxisZoomDlg()
{

}

// 函数 CAxisZoomDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CAxisZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAxisZoomDlg, CDialogEx)
	ON_WM_ERASEBKGND() 
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_AXISZOOMDLG_BT_DEFAULTSET,&CAxisZoomDlg::OnBnClickedDefaultSet)
	ON_BN_CLICKED(ID_AXISZOOMDLG_BT_SAVE,&CAxisZoomDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_AXISZOOMDLG_BT_CANCEL,&CAxisZoomDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// 函数 CAxisZoomDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CAxisZoomDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	CRect rect;
	GetClientRect(&rect);

	CDC memDc,memDc2;
	memDc.CreateCompatibleDC(pDC);
	memDc2.CreateCompatibleDC(pDC);

	CBitmap bitMapCB,bitMapCB2;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);
	bitMapCB2.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB2 = memDc2.SelectObject(&bitMapCB2);

	memDc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	memDc2.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(0,0,0));

	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = CLRALPHAVALUE;
	blendFunc.AlphaFormat = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	BOOL ret = memDc.AlphaBlend(0,0,rect.Width(),rect.Height(),&memDc2,0,0,rect.Width(),rect.Height(),blendFunc);

	CRect rcUseful;
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2 - m_iWndWidth / 2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;

	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top + m_iCapHeight,rcUseful.Width(),rcUseful.Height() - m_iCapHeight,0,0,m_iAngleRadius,m_iAngleRadius,FALSE,Color(197,197,197),m_iFrameWidth,TRUE,Color(255,255,255),1);
	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top,rcUseful.Width(),m_iCapHeight,m_iAngleRadius,m_iAngleRadius,0,0,FALSE,COLOR_SOFT_THEME,m_iFrameWidth,TRUE,COLOR_SOFT_THEME,1);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	DWORD dwTxStyle = DT_CENTER | DT_VCENTER | DT_SINGLELINE;
	double dX1 = rcUseful.left + 32 * m_dHoriRatio;
	double dX2 = rcUseful.left + 306 * m_dHoriRatio;
	CRect rcMinTx = CRect(dX1,rcUseful.top + 140 * m_dVertRatio,rcUseful.left + 102 * m_dHoriRatio,rcUseful.top + 167 * m_dVertRatio);
	CRect rcMaxTx = CRect(dX2,rcUseful.top + 140 * m_dVertRatio,rcUseful.left + 376 * m_dHoriRatio,rcUseful.top + 167 * m_dVertRatio);
#ifdef AXISZOOMDLG_MINMAX_INMIDDLE
	dX1 = rcUseful.left + 84 * m_dHoriRatio;
	dX2 = rcUseful.left + 358 * m_dHoriRatio;

	rcMinTx = CRect(dX1,rcUseful.top + 140 * m_dVertRatio,rcUseful.left + 284 * m_dHoriRatio,rcUseful.top + 167 * m_dVertRatio);
	rcMaxTx = CRect(dX2,rcUseful.top + 140 * m_dVertRatio,rcUseful.left + 558 * m_dHoriRatio,rcUseful.top + 167 * m_dVertRatio);
#endif 

	memDc.DrawText(pLangInfo->GetText(101),rcMinTx,dwTxStyle);
	memDc.DrawText(pLangInfo->GetText(102),rcMaxTx,dwTxStyle);

#ifdef AXISZOOMDLG_MINMAX_INMIDDLE
	dX1 = rcUseful.left + 32 * m_dHoriRatio;
	dX2 = rcUseful.left + 306 * m_dHoriRatio;
#endif
	
	memDc.DrawText(pLangInfo->GetText(103),CRect(dX1,rcUseful.top + 199 * m_dVertRatio,rcUseful.left + 72 * m_dHoriRatio,rcUseful.top + 223 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(103),CRect(dX2,rcUseful.top + 199 * m_dVertRatio,rcUseful.left + 346 * m_dHoriRatio,rcUseful.top + 223 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	memDc.DrawText(pLangInfo->GetText(104),CRect(dX1,rcUseful.top + 255 * m_dVertRatio,rcUseful.left + 72 * m_dHoriRatio,rcUseful.top + 279 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(104),CRect(dX2,rcUseful.top + 255 * m_dVertRatio,rcUseful.left + 346 * m_dHoriRatio,rcUseful.top + 279 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	memDc.SetTextColor(RGB(255,255,255));
	memDc.DrawText(pLangInfo->GetText(293),CRect(rcUseful.left + 10,rcUseful.top + 5,rcUseful.left + rcUseful.Width() - 10,rcUseful.top + m_iCapHeight - 5),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	memDc.SelectObject(pOldFont);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0XD8,0XD8,0XD8));
	CPen* pOldPen = memDc.SelectObject(&pen);
	memDc.MoveTo(rcUseful.left,rcUseful.top + 367 * m_dVertRatio);
	memDc.LineTo(rcUseful.left + m_iWndWidth,rcUseful.top + 367 * m_dVertRatio);
	memDc.SelectObject(pOldPen);

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	memDc2.SelectObject(&pOldBitmapCB2);
	bitMapCB2.DeleteObject();
	memDc2.DeleteDC();

	return TRUE;
}

// 函数 CAxisZoomDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CAxisZoomDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iWndWidth *= m_dHoriRatio;
	m_iWndHeight *= m_dVertRatio;
	m_iCapHeight *= m_dVertRatio;
	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CAxisZoomDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PostMessage、MAKELPARAM。
void CAxisZoomDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
#ifdef POPDLG_USESHADEBK
	CDialogEx::OnLButtonDown(nFlags, point);
#else
	if(point.y < m_iCapHeight)
	{
		PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
	}
	else
	{
		CDialogEx::OnLButtonDown(nFlags, point);
	}
#endif

	return;
}

// 函数 CAxisZoomDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、GetParent、Width、Height、SetRoundRect、CenterWindow。
BOOL CAxisZoomDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

#ifdef POPDLG_USESHADEBK
	SetWindowPos(GetParent(),theApp.m_rcWorkArea.left,theApp.m_rcWorkArea.top,theApp.m_rcWorkArea.Width(),theApp.m_rcWorkArea.Height(),SWP_NOZORDER);
#else
	SetWindowPos(GetParent(),0,0,m_iWndWidth,m_iWndHeight,SWP_NOZORDER);
	SetRoundRect(m_iAngleRadius,m_iAngleRadius);
	CenterWindow(GetParent());
#endif

	CreateCtrl();
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();

	ShowCtrl();

	return TRUE;
}

// 函数 CAxisZoomDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateEd、CreateCkbt。
void CAxisZoomDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateEd();
	CreateCkbt();
}

// 函数 CAxisZoomDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CAxisZoomDlg::CreateBt()
{
	m_btDefSet.Create(_T("默认"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_AXISZOOMDLG_BT_DEFAULTSET);
	m_btSave.Create(_T("保存"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_AXISZOOMDLG_BT_SAVE);
	m_btCancel.Create(_T("取消"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_AXISZOOMDLG_BT_CANCEL);
}

// 函数 CAxisZoomDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CAxisZoomDlg::CreateSt()
{
	
}

// 函数 CAxisZoomDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CAxisZoomDlg::CreateEd()
{
	m_edXMin.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_AXISZOOMDLG_ED_XMIN);
	m_edXMax.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_AXISZOOMDLG_ED_XMAX);
	m_edYMin.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_AXISZOOMDLG_ED_YMIN);
	m_edYMax.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_AXISZOOMDLG_ED_YMAX);
}

// 函数 CAxisZoomDlg::CreateCkbt
// 作用：创建或加入CreateCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CAxisZoomDlg::CreateCkbt()
{
	m_ckbtLogMode.Create(_T("Log"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_AXISZOOMDLG_CKBT_LOGMODE);
}

// 函数 CAxisZoomDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CAxisZoomDlg::InitDlg()
{
	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,16 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CAxisZoomDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitEd、InitCkbt。
void CAxisZoomDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitEd();
	InitCkbt();
}

// 函数 CAxisZoomDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBkColor、Color、SetBkColorEnd。
void CAxisZoomDlg::InitBt()
{
	int iFontH = 16 * m_dTxRatio;

	m_btDefSet.SetMyFont(m_stTxFont,iFontH);
	m_btDefSet.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);

	m_btSave.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
#ifndef GRADIENT_SOME_BTBK
	m_btSave.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),FALSE);
	m_btSave.SetBkColor(COLOR_BTBK_NORMAL,COLOR_BTBK_HOVER,COLOR_BTBK_CLICKED,COLOR_BTBK_DISABLED);
#else
	m_btSave.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
	m_btSave.SetBkColor(Color(0X38,0XE0,0XEF),Color(0X3A,0XEF,0XFF),COLOR_SOFT_THEME,Color(0XF1,0XF1,0XF1));
	m_btSave.SetBkColorEnd(COLOR_SOFT_THEME,Color(0X38,0XE0,0XEF),Color(0X02,0X8D,0X99),Color(0XD8,0XD8,0XD8));
#endif
	m_btSave.SetTextColor(RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XC6,0XC4,0XC4));

	m_btCancel.SetMyFont(m_stTxFont,iFontH);
	m_btCancel.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
}

// 函数 CAxisZoomDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CAxisZoomDlg::InitSt()
{
	
}

// 函数 CAxisZoomDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitEditCtrlParam、SetAxisInfo。
void CAxisZoomDlg::InitEd()
{
	InitEditCtrlParam(&m_edXMin);
	InitEditCtrlParam(&m_edXMax);
	InitEditCtrlParam(&m_edYMin);
	InitEditCtrlParam(&m_edYMax);

	SetAxisInfo(m_axisInfo,FALSE);
}

// 函数 CAxisZoomDlg::InitCkbt
// 作用：初始化InitCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetBtChecked、SetPngBkPic、_T、SetBeNeedRedrawBk、SetMyFont、SetMyFontChecked。
void CAxisZoomDlg::InitCkbt()
{
	int iFontH = 20 * m_dTxRatio;

	m_ckbtLogMode.SetBtChecked(m_bLogMode);
	m_ckbtLogMode.SetPngBkPic(_T(".\\BkPic\\CheckBox.png"),4,20 * m_dHoriRatio);
	m_ckbtLogMode.SetBeNeedRedrawBk(TRUE);
	m_ckbtLogMode.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtLogMode.SetMyFontChecked(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CAxisZoomDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、Width、Height、SetWindowPos。
void CAxisZoomDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	CRect rcUseful;
#ifdef POPDLG_USESHADEBK
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2 - m_iWndWidth / 2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;
#endif

	int iTempInt1 = 40 * m_dVertRatio;
	int iTempInt2 = 200 * m_dHoriRatio;
	int iTempInt3 = 90 * m_dHoriRatio;
	int iTempInt4 = 392 * m_dVertRatio;
	int iTempInt5 = 32 * m_dHoriRatio;

	m_edXMin.SetWindowPos(this,rcUseful.left + 84 * m_dHoriRatio,rcUseful.top + 191 * m_dVertRatio,iTempInt2,iTempInt1,SWP_NOZORDER);
	m_edXMax.SetWindowPos(this,rcUseful.left + 358 * m_dHoriRatio,rcUseful.top + 191 * m_dVertRatio,iTempInt2,iTempInt1,SWP_NOZORDER);
	m_edYMin.SetWindowPos(this,rcUseful.left + 84 * m_dHoriRatio,rcUseful.top + 247 * m_dVertRatio,iTempInt2,iTempInt1,SWP_NOZORDER);
	m_edYMax.SetWindowPos(this,rcUseful.left + 358 * m_dHoriRatio,rcUseful.top + 247 * m_dVertRatio,iTempInt2,iTempInt1,SWP_NOZORDER);

	m_ckbtLogMode.SetWindowPos(this,rcUseful.left + iTempInt5,rcUseful.top + 320 * m_dVertRatio,iTempInt3,iTempInt1,SWP_NOZORDER);

	m_btDefSet.SetWindowPos(this,rcUseful.left + iTempInt5,rcUseful.top + iTempInt4,iTempInt3,iTempInt1,SWP_NOZORDER);
	m_btSave.SetWindowPos(this,rcUseful.left + 356 * m_dHoriRatio,rcUseful.top + iTempInt4,iTempInt3,iTempInt1,SWP_NOZORDER);
	m_btCancel.SetWindowPos(this,rcUseful.left + 470 * m_dHoriRatio,rcUseful.top + iTempInt4,iTempInt3,iTempInt1,SWP_NOZORDER);
}

// 函数 CAxisZoomDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CAxisZoomDlg::ShowCtrl()
{
#ifndef PS96INSTRUMENT
	if(m_bHaveLogFunc)
	{
		m_ckbtLogMode.ShowWindow(SW_SHOW);
	}
#endif

	if(m_bUseDefFunc)
	{
		m_btDefSet.ShowWindow(SW_SHOW);
	}

	m_btSave.ShowWindow(SW_SHOW);
	m_btCancel.ShowWindow(SW_SHOW);
	m_edXMin.ShowWindow(SW_SHOW);
	m_edXMax.ShowWindow(SW_SHOW);
	m_edYMin.ShowWindow(SW_SHOW);
	m_edYMax.ShowWindow(SW_SHOW);
}

// 函数 CAxisZoomDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetWindowText、GetText。
void CAxisZoomDlg::SetCtrlText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_btSave.SetWindowText(pLangInfo->GetText(148));
	m_btCancel.SetWindowText(pLangInfo->GetText(150));
	m_btDefSet.SetWindowText(pLangInfo->GetText(295));

	return;
}

// 函数 CAxisZoomDlg::OnBnClickedDefaultSet
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCheckState、SetAxisInfo、CalculateLogValaue。
void CAxisZoomDlg::OnBnClickedDefaultSet()
{
	if(m_ckbtLogMode.GetCheckState())
	{
		SetAxisInfo(m_defLinearAxisInfo.CalculateLogValaue(),TRUE);
	}
	else
	{
		SetAxisInfo(m_defLinearAxisInfo,TRUE);
	}

	return;
}

// 函数 CAxisZoomDlg::OnBnClickedSave
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 strTemp、_T、GetText、_ttof、PopWarningTipInfo、GetCheckState。
void CAxisZoomDlg::OnBnClickedSave()
{
	CString strTemp(_T(""));

	strTemp = m_edXMin.GetText();
	m_newAxisInfo.m_dXMin = _ttof(strTemp);
	strTemp = m_edXMax.GetText();
	m_newAxisInfo.m_dXMax = _ttof(strTemp);
	strTemp = m_edYMin.GetText();
	m_newAxisInfo.m_dYMin = _ttof(strTemp);
	strTemp = m_edYMax.GetText();
	m_newAxisInfo.m_dYMax = _ttof(strTemp);

	if(m_newAxisInfo.m_dXMin >= m_newAxisInfo.m_dXMax || m_newAxisInfo.m_dYMin >= m_newAxisInfo.m_dYMax)
	{
		strTemp = theApp.m_pLangInfo->GetText(162);
		PopWarningTipInfo(strTemp);
		return;
	}

	if(m_newAxisInfo.m_dYMax > 65535)
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(259));
		return;
	}

	m_bChanged = !(m_axisInfo == m_newAxisInfo);

	m_bNewLogMode = m_ckbtLogMode.GetCheckState();
	m_bLogModeChanged = (m_bLogMode != m_bNewLogMode);

	OnOK();
	return;
}

// 函数 CAxisZoomDlg::OnBnClickedCancel
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 OnCancel。
void CAxisZoomDlg::OnBnClickedCancel()
{
	OnCancel();
	return;
}

// 函数 CAxisZoomDlg::SetAxisInfo
// 作用：设置SetAxisInfo。
// 参数：axisInfo；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 strTemp、_T、Format、SetText。
void CAxisZoomDlg::SetAxisInfo(CAxisInfo axisInfo,BOOL bRedraw)
{
	CString strTemp(_T(""));
	strTemp.Format(_T("%.2lf"),axisInfo.m_dXMin);
	m_edXMin.SetText(strTemp,bRedraw);
	strTemp.Format(_T("%.2lf"),axisInfo.m_dXMax);
	m_edXMax.SetText(strTemp,bRedraw);
	strTemp.Format(_T("%.2lf"),axisInfo.m_dYMin);
	m_edYMin.SetText(strTemp,bRedraw);
	strTemp.Format(_T("%.2lf"),axisInfo.m_dYMax);
	m_edYMax.SetText(strTemp,bRedraw);
}

// 函数 CAxisZoomDlg::SetRoundRect
// 作用：设置SetRoundRect。
// 参数：x；y。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetClientRect、CreateRoundRectRgn、SetWindowRgn。
BOOL CAxisZoomDlg::SetRoundRect(int x /*= 5*/,int y /*= 5*/)
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

// 函数 CAxisZoomDlg::InitEditCtrlParam
// 作用：初始化InitEditCtrlParam。
// 参数：pEdit：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
void CAxisZoomDlg::InitEditCtrlParam(CMyNewEdit* pEdit)
{
	if(NULL == pEdit)
	{
		return;
	}

	pEdit->SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	pEdit->SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	pEdit->SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	pEdit->SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XC6,0XC6,0XC6));
	pEdit->SetMyFont(m_stTxFont,16 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
	pEdit->SetTextClr1(RGB(0X56,0X56,0X56));

	return;
}

// 函数 CAxisZoomDlg::GetNewLogMode
// 作用：读取GetNewLogMode。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CAxisZoomDlg::GetNewLogMode()
{
	return m_bNewLogMode;
}

// 函数 CAxisZoomDlg::SetUseDefaultFuncState
// 作用：设置SetUseDefaultFuncState。
// 参数：bUseState：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CAxisZoomDlg::SetUseDefaultFuncState(BOOL bUseState)
{
	m_bUseDefFunc = bUseState;
}

// 函数 CAxisZoomDlg::GetUseDefaultFuncState
// 作用：读取GetUseDefaultFuncState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CAxisZoomDlg::GetUseDefaultFuncState()
{
	return m_bUseDefFunc;
}




