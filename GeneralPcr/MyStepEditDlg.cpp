// 【交接】 GeneralPcr\MyStepEditDlg.cpp
// 作用：MyStepEditDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyStepEditDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_CREATE、ON_WM_LBUTTONDOWN。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "MyStepEditDlg.h"
#include "GeneralPcrDlg.h"
#include "GeneralPcr.h"

// CMyStepEditDlg dialog
IMPLEMENT_DYNAMIC(CMyStepEditDlg, CDialogEx)

// 函数 CMyStepEditDlg::CMyStepEditDlg
// 作用：执行CMyStepEditDlg。
// 参数：stepEditInfo；pParent：指针，指向调用方传入的对象；bShieldGradientSet：是或否；bShowTemRate：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyStepEditDlg::CMyStepEditDlg(CMyStepEditInfo stepEditInfo,CWnd* pParent /*=NULL*/,BOOL bShieldGradientSet /*= FALSE*/,BOOL bShowTemRate /*= TRUE*/)
	: CDialogEx(CMyStepEditDlg::IDD, pParent)
{
	m_hWndParent = NULL;
	m_stepEditInfo = stepEditInfo;
	m_roundValue = 10;
	m_frameWidth = 1;
	m_iWndWidth = 480;
	m_iWndHeight = 436;
	m_iCapHeight = 50;
	m_bShieldGradientSet = bShieldGradientSet;
	m_bShowTemRate = bShowTemRate;
	m_iVertDiff = 52;
}

// 函数 CMyStepEditDlg::~CMyStepEditDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyStepEditDlg::~CMyStepEditDlg()
{

}

// 函数 CMyStepEditDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CMyStepEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyStepEditDlg, CDialogEx)
	ON_WM_ERASEBKGND() 
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_STEPEDITDLG_CKBT_COLLECT,&CMyStepEditDlg::OnBnClickedCollect)
	ON_BN_CLICKED(ID_STEPEDITDLG_CKBT_NOTCOLLECT,&CMyStepEditDlg::OnBnClickedNotCollect)
	ON_BN_CLICKED(ID_STEPEDITDLG_CKBT_COLLECTALL,&CMyStepEditDlg::OnBnClickedCollectAll)
	ON_BN_CLICKED(ID_STEPEDITDLG_CKBT_SELECTGRADIENT,&CMyStepEditDlg::OnBnClickedSelectGradient)
	ON_BN_CLICKED(ID_STEPEDITDLG_BT_SAVE,&CMyStepEditDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_STEPEDITDLG_BT_CANCEL,&CMyStepEditDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// 函数 CMyStepEditDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CMyStepEditDlg::OnEraseBkgnd(CDC* pDC)
{
	if(NULL == pDC)
	{
		return TRUE;
	}
	
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	CRect rect;
	GetClientRect(&rect);

	CDC memDc,memDc2;
	memDc.CreateCompatibleDC(pDC);
	memDc2.CreateCompatibleDC(pDC);

	CBitmap bitMapCB,bitMapCB2;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	bitMapCB2.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);
	CBitmap* pOldBitmapCB2 = memDc2.SelectObject(&bitMapCB2);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	memDc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	memDc2.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(0,0,0));

	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = CLRALPHAVALUE;
	blendFunc.AlphaFormat = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	BOOL ret = memDc.AlphaBlend(0,0,rect.Width(),rect.Height(),&memDc2,0,0,rect.Width(),rect.Height(),blendFunc);

	CRect rcUseful;
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;

	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top + m_iCapHeight,rcUseful.Width(),rcUseful.Height() - m_iCapHeight,0,0,m_roundValue,m_roundValue,FALSE,Color(197,197,197),m_frameWidth,TRUE,Color(255,255,255),1);
	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top,rcUseful.Width(),m_iCapHeight,m_roundValue,m_roundValue,0,0,FALSE,Color(3,91,199),2,TRUE,COLOR_SOFT_THEME,1);

	int tempInt1 = rcUseful.left + int(220 * m_dHoriRatio);
	int iTempInt3 = rcUseful.left + int(42 * m_dHoriRatio);

	memDc.DrawText(pLangInfo->GetText(57),CRect(iTempInt3, rcUseful.top+int(92*m_dVertRatio), tempInt1, rcUseful.top + 116 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(58),CRect(iTempInt3, rcUseful.top+int(144*m_dVertRatio), tempInt1, rcUseful.top + 168 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(133),CRect(iTempInt3, rcUseful.top+int(196*m_dVertRatio), tempInt1, rcUseful.top + 220 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(134),CRect(iTempInt3, rcUseful.top+int(248*m_dVertRatio), tempInt1, rcUseful.top + 272 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(135),CRect(iTempInt3, rcUseful.top+int(300*m_dVertRatio), tempInt1, rcUseful.top + 324 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	
	int tempInt2 = rcUseful.left + 450 * m_dHoriRatio;
	int tempInt4 = rcUseful.left + 428 * m_dHoriRatio;
	memDc.DrawText(_T("℃"),CRect(tempInt4, rcUseful.top+int(196*m_dVertRatio), tempInt2,rcUseful.top+int(220*m_dVertRatio)),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(_T("S"),CRect(tempInt4, rcUseful.top+int(248*m_dVertRatio), tempInt2,rcUseful.top+int(272*m_dVertRatio)),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	
	memDc.SetTextColor(RGB(255,255,255));
	memDc.DrawText(pLangInfo->GetText(44),CRect(rcUseful.left + 10,rcUseful.top + 5,rcUseful.right - 10,rcUseful.top + m_iCapHeight - 5),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	memDc.SelectObject(pOldFont);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	memDc2.SelectObject(&pOldBitmapCB2);
	bitMapCB2.DeleteObject();
	memDc2.DeleteDC();

	return TRUE;
}

// 函数 CMyStepEditDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CMyStepEditDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iWndWidth *= m_dHoriRatio;
	m_iWndHeight *= m_dVertRatio;
	m_iCapHeight *= m_dVertRatio;
	m_iVertDiff *= m_dVertRatio;
	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CMyStepEditDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PostMessage、MAKELPARAM。
void CMyStepEditDlg::OnLButtonDown(UINT nFlags, CPoint point)
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

// 函数 CMyStepEditDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、GetParent、Width、Height、SetRoundRect、CenterWindow。
BOOL CMyStepEditDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

#ifdef POPDLG_USESHADEBK
	SetWindowPos(GetParent(),theApp.m_rcWorkArea.left,theApp.m_rcWorkArea.top,theApp.m_rcWorkArea.Width(),theApp.m_rcWorkArea.Height(),SWP_NOZORDER);
#else
	SetWindowPos(GetParent(),0 * m_dHoriRatio,0 * m_dVertRatio,m_iWndHeight,SWP_NOZORDER);
	SetRoundRect(m_roundValue,m_roundValue);
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

// 函数 CMyStepEditDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateCkBt、CreateSt、CreateEd、CreateCb。
void CMyStepEditDlg::CreateCtrl()
{
	CreateBt();
	CreateCkBt();
	CreateSt();
	CreateEd();
	CreateCb();
}

// 函数 CMyStepEditDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CMyStepEditDlg::CreateBt()
{
	m_btSave.Create(_T("保存"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_STEPEDITDLG_BT_SAVE);
	m_btCancel.Create(_T("取消"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_STEPEDITDLG_BT_CANCEL);
}

// 函数 CMyStepEditDlg::CreateCkBt
// 作用：创建或加入CreateCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CMyStepEditDlg::CreateCkBt()
{
	m_ckbtCollect.Create(_T("采集"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_STEPEDITDLG_CKBT_COLLECT);
	m_ckbtNotCollect.Create(_T("不采集"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_STEPEDITDLG_CKBT_NOTCOLLECT);
	m_ckbtCollectAll.Create(_T("全点采集"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_STEPEDITDLG_CKBT_COLLECTALL);
	m_ckbtSelectGradient.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_STEPEDITDLG_CKBT_SELECTGRADIENT);
}

// 函数 CMyStepEditDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyStepEditDlg::CreateSt()
{
	
}

// 函数 CMyStepEditDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CMyStepEditDlg::CreateEd()
{
	m_edSegName.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_STEPEDITDLG_ED_SEGNAME);
	m_edStepTag.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_STEPEDITDLG_ED_STEPTAG);
	m_edAimTem.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_STEPEDITDLG_ED_AIMTEM);
	m_edGradientMaxTem.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_STEPEDITDLG_ED_GRADIENTMAXTEM);
	m_edHoldSec.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_STEPEDITDLG_ED_HOLDSEC);
}

// 函数 CMyStepEditDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CMyStepEditDlg::CreateCb()
{
	CRect rcCreate(0,0,0,0);
	m_cbMeltTemInterval.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_STEPEDITDLG_CB_MELTTEMINTERVAL);
	m_cbTemRate.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_STEPEDITDLG_CB_TEMRATE);
}

// 函数 CMyStepEditDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CMyStepEditDlg::InitDlg()
{
	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,16 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CMyStepEditDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCkBt、InitSt、InitEd、InitCb。
void CMyStepEditDlg::InitCtrl()
{
	InitBt();
	InitCkBt();
	InitSt();
	InitEd();
	InitCb();
}

// 函数 CMyStepEditDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBkColor、Color、SetBkColorEnd。
void CMyStepEditDlg::InitBt()
{
	int iFontH = 18 * CFontSet::m_dTxRatio;

	m_btSave.SetMyFont(m_stTxFont,iFontH);
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

// 函数 CMyStepEditDlg::InitCkBt
// 作用：初始化InitCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPngBkPic、_T、int、SetIconTextInterval、SetTextColor、RGB。
void CMyStepEditDlg::InitCkBt()
{
	int iFtH = 16 * m_dTxRatio;
	int iLeftIndent = 8 * m_dHoriRatio;

	m_ckbtNotCollect.SetPngBkPic(_T(".\\BkPic\\singleselect.png"),4,int(14 * m_dHoriRatio));
	m_ckbtNotCollect.SetIconTextInterval(iLeftIndent);
	m_ckbtNotCollect.SetTextColor(RGB(0X60,0X62,0X66),CLR_SOFT_THEME);
	m_ckbtNotCollect.SetMyFont(m_stTxFont,iFtH);
	m_ckbtNotCollect.SetBeNeedRedrawBk(TRUE);
	m_ckbtNotCollect.SetBeParentProcessMouseClick(TRUE);
	m_ckbtNotCollect.SetMyFontChecked(m_stTxFont,iFtH);
	m_ckbtNotCollect.SetBtChecked(1 == m_stepEditInfo.m_iCollect);
	m_ckbtNotCollect.EnableWindow(1 != m_stepEditInfo.m_iCollect);

	m_ckbtCollect.SetPngBkPic(_T(".\\BkPic\\singleselect.png"),4,int(14 * m_dHoriRatio));
	m_ckbtCollect.SetIconTextInterval(iLeftIndent);
	m_ckbtCollect.SetTextColor(RGB(0X60,0X62,0X66),CLR_SOFT_THEME);
	m_ckbtCollect.SetMyFont(m_stTxFont,iFtH);
	m_ckbtCollect.SetBeNeedRedrawBk(TRUE);
	m_ckbtCollect.SetBeParentProcessMouseClick(TRUE);
	m_ckbtCollect.SetMyFontChecked(m_stTxFont,iFtH);
	m_ckbtCollect.SetBtChecked(2 == m_stepEditInfo.m_iCollect);
	m_ckbtCollect.EnableWindow(2 != m_stepEditInfo.m_iCollect);

	m_ckbtCollectAll.SetPngBkPic(_T(".\\BkPic\\singleselect.png"), 4, int(int(14 * m_dHoriRatio)));
	m_ckbtCollectAll.SetIconTextInterval(iLeftIndent);
	m_ckbtCollectAll.SetTextColor(RGB(0X60,0X62,0X66),CLR_SOFT_THEME);
	m_ckbtCollectAll.SetMyFont(m_stTxFont,iFtH);
	m_ckbtCollectAll.SetBeNeedRedrawBk(TRUE);
	m_ckbtCollectAll.SetBeParentProcessMouseClick(TRUE);
	m_ckbtCollectAll.SetMyFontChecked(m_stTxFont,iFtH);
	m_ckbtCollectAll.SetBtChecked(3 == m_stepEditInfo.m_iCollect);
	m_ckbtCollectAll.EnableWindow(3 != m_stepEditInfo.m_iCollect);

	m_ckbtSelectGradient.SetPngBkPic(_T(".\\BkPic\\CheckBox.png"),4,20 * m_dHoriRatio);
	m_ckbtSelectGradient.SetIconTextInterval(iLeftIndent);
	m_ckbtSelectGradient.SetBeNeedRedrawBk(TRUE);
	m_ckbtSelectGradient.SetSelectStateSerail(2);
	m_ckbtSelectGradient.SetMyFont(m_stTxFont,iFtH);
	m_ckbtSelectGradient.SetMyFontChecked(m_stTxFont,iFtH);
	m_ckbtSelectGradient.SetFrameColor(RGB(197,197,197));
	m_ckbtSelectGradient.SetBeParentProcessMouseClick(TRUE);
	m_ckbtSelectGradient.SetTickStyle(TRUE);
	m_ckbtSelectGradient.SetBtChecked(m_stepEditInfo.m_bSelGradient);
	if(m_stepEditInfo.m_bMeltSeg)
	{
		m_ckbtSelectGradient.EnableWindow(FALSE);
	}
	
	return;
}

// 函数 CMyStepEditDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyStepEditDlg::InitSt()
{
	
}

// 函数 CMyStepEditDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 tempstr、_T、SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor。
void CMyStepEditDlg::InitEd()
{
	int iFontH = 16 * m_dTxRatio;

	CString tempstr(_T(""));

	m_edSegName.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edSegName.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edSegName.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edSegName.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edSegName.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edSegName.SetTextClr1(RGB(0X56,0X56,0X56));
	m_edSegName.SetText(m_stepEditInfo.m_strSegName);
	m_edSegName.SetBeEditable(FALSE);

	m_edStepTag.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edStepTag.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edStepTag.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edStepTag.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edStepTag.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edStepTag.SetTextClr1(RGB(0X56,0X56,0X56));
	m_edStepTag.SetText(m_stepEditInfo.m_strStepName);
	m_edStepTag.SetBeEditable(FALSE);

	m_edAimTem.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edAimTem.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edAimTem.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edAimTem.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edAimTem.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edAimTem.SetTextClr1(RGB(0X56,0X56,0X56));
	tempstr.Format(_T("%.1lf"),m_stepEditInfo.m_fAimTem);
	m_edAimTem.SetText(tempstr);

	m_edGradientMaxTem.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edGradientMaxTem.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edGradientMaxTem.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edGradientMaxTem.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edGradientMaxTem.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edGradientMaxTem.SetTextClr1(RGB(0X56,0X56,0X56));
	tempstr.Format(_T("%.1lf"),m_stepEditInfo.m_fGradientMaxTem);
	m_edGradientMaxTem.SetText(tempstr);
	m_edGradientMaxTem.SetBeEditable(m_stepEditInfo.m_bSelGradient);

	m_edHoldSec.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edHoldSec.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edHoldSec.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edHoldSec.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edHoldSec.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edHoldSec.SetTextClr1(RGB(0X56,0X56,0X56));	
	tempstr.Format(_T("%d"),m_stepEditInfo.m_holdSec);
	m_edHoldSec.SetText(tempstr);
}

// 函数 CMyStepEditDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 int、SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB。
void CMyStepEditDlg::InitCb()
{
	int iFontH = int(16 * m_dTxRatio);

	m_cbMeltTemInterval.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_cbMeltTemInterval.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_cbMeltTemInterval.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_cbMeltTemInterval.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_cbMeltTemInterval.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbMeltTemInterval.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbMeltTemInterval.m_iRightIndent = int(44 * m_dHoriRatio);
	m_cbMeltTemInterval.m_arrowInfo.m_clrArrow = Color(0X39,0X45,0X65);
	m_cbMeltTemInterval.m_arrowInfo.m_arrowW = int(12 * m_dHoriRatio);
	m_cbMeltTemInterval.m_arrowInfo.m_arrowH = int(8 * m_dVertRatio);

	m_cbMeltTemInterval.InsertString(0,_T("0.20"));
	m_cbMeltTemInterval.InsertString(1,_T("0.50"));
	m_cbMeltTemInterval.InsertString(2,_T("0.80"));
	m_cbMeltTemInterval.InsertString(3,_T("1.00"));

	CString strTemp(_T(""));
	strTemp.Format(_T("%.2lf"),m_stepEditInfo.m_fIncrement);
	m_cbMeltTemInterval.SetText(strTemp,FALSE,TRUE);

	m_cbMeltTemInterval.SetBeEditable(3 == m_stepEditInfo.m_iCollect);


	m_cbTemRate.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_cbTemRate.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_cbTemRate.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_cbTemRate.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_cbTemRate.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbTemRate.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbTemRate.SetWorkState(EWS_READONLY);
	m_cbTemRate.m_iRightIndent = int(44 * m_dHoriRatio);
	m_cbTemRate.m_arrowInfo.m_clrArrow = Color(0X39,0X45,0X65);
	m_cbTemRate.m_arrowInfo.m_arrowW = int(12 * m_dHoriRatio);
	m_cbTemRate.m_arrowInfo.m_arrowH = int(8 * m_dVertRatio);

#ifdef N96INSTRUMENT
	m_cbTemRate.InsertString(0,_T("0.5"));
	m_cbTemRate.InsertString(1,_T("1.0"));
	m_cbTemRate.InsertString(2,_T("2.0"));
	m_cbTemRate.InsertString(3,_T("4.0"));
	m_cbTemRate.InsertString(4,_T("6.0"));
#else
	m_cbTemRate.InsertString(0,_T("1.0"));
	m_cbTemRate.InsertString(1,_T("2.0"));
	m_cbTemRate.InsertString(2,_T("4.0"));
	m_cbTemRate.InsertString(3,_T("8.0"));
	m_cbTemRate.InsertString(4,_T("12.0"));
#endif

	strTemp.Format(_T("%.1lf"),m_stepEditInfo.m_fRate);
	m_cbTemRate.SetText(strTemp);

	return;
}

// 函数 CMyStepEditDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、Width、Height、int、SetWindowPos。
void CMyStepEditDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	CRect rcUseful;
#ifdef POPDLG_USESHADEBK
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;
#endif

	int tempInt1 = rcUseful.left + int(226 * m_dHoriRatio);
	int tempInt2 = int(40 * m_dVertRatio);
	int iTempInt3 = int(190 * m_dHoriRatio);

	m_btSave.SetWindowPos(this,rcUseful.left+int(228*m_dHoriRatio), rcUseful.top+int(372*m_dVertRatio), int(90*m_dHoriRatio), tempInt2,SWP_NOZORDER);
	m_btCancel.SetWindowPos(this,rcUseful.left+int(342*m_dHoriRatio), rcUseful.top+int(372*m_dVertRatio), int(90*m_dHoriRatio), tempInt2,SWP_NOZORDER);

	m_edSegName.SetWindowPos(this,tempInt1, rcUseful.top+int(84*m_dVertRatio), iTempInt3,tempInt2,SWP_NOZORDER);
	m_edStepTag.SetWindowPos(this,tempInt1, rcUseful.top+int(136*m_dVertRatio), iTempInt3,tempInt2,SWP_NOZORDER);
	m_edAimTem.SetWindowPos(this,tempInt1,rcUseful.top+int(188*m_dVertRatio), iTempInt3,tempInt2,SWP_NOZORDER);
	m_edHoldSec.SetWindowPos(this,tempInt1,rcUseful.top+int(240*m_dVertRatio), iTempInt3,tempInt2,SWP_NOZORDER);

	m_ckbtNotCollect.SetWindowPos(this, tempInt1, rcUseful.top+int(301*m_dVertRatio), int(96*m_dHoriRatio), int(22*m_dVertRatio), SWP_NOZORDER);
	m_ckbtCollect.SetWindowPos(this, tempInt1+int(106*m_dHoriRatio), rcUseful.top+int(301*m_dVertRatio), int(82*m_dHoriRatio), int(22*m_dVertRatio),SWP_NOZORDER);
}

// 函数 CMyStepEditDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CMyStepEditDlg::ShowCtrl()
{
	m_btSave.ShowWindow(SW_SHOW);
	m_btCancel.ShowWindow(SW_SHOW);

	m_edSegName.ShowWindow(SW_SHOW);
	m_edStepTag.ShowWindow(SW_SHOW);
	m_edAimTem.ShowWindow(SW_SHOW);
	m_edHoldSec.ShowWindow(SW_SHOW);

	m_ckbtCollect.ShowWindow(SW_SHOW);
	m_ckbtNotCollect.ShowWindow(SW_SHOW);
}

// 函数 CMyStepEditDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetWindowText、GetText。
void CMyStepEditDlg::SetCtrlText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_btSave.SetWindowText(pLangInfo->GetText(148));
	m_btCancel.SetWindowText(pLangInfo->GetText(150));
	m_ckbtCollect.SetWindowText(pLangInfo->GetText(137));
	m_ckbtNotCollect.SetWindowText(pLangInfo->GetText(136));
	m_ckbtCollectAll.SetWindowText(pLangInfo->GetText(305));

	return;
}

// 函数 CMyStepEditDlg::OnBnClickedCollect
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCheckState、SetBtChecked、EnableWindow、SetBeEditable。
void CMyStepEditDlg::OnBnClickedCollect()
{
	BOOL bCkbtState = m_ckbtCollect.GetCheckState();
	m_ckbtCollect.SetBtChecked(!bCkbtState,TRUE);
	m_ckbtCollect.EnableWindow(FALSE);

	m_ckbtNotCollect.SetBtChecked(bCkbtState,TRUE);
	m_ckbtNotCollect.EnableWindow(TRUE);

	m_ckbtCollectAll.SetBtChecked(bCkbtState,TRUE);
	m_ckbtCollectAll.EnableWindow(TRUE);

	m_cbMeltTemInterval.SetBeEditable(FALSE,TRUE);

	m_ckbtSelectGradient.EnableWindow(TRUE);
	return;
}

// 函数 CMyStepEditDlg::OnBnClickedNotCollect
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCheckState、SetBtChecked、EnableWindow、SetBeEditable。
void CMyStepEditDlg::OnBnClickedNotCollect()
{
	BOOL bCkbtState = m_ckbtNotCollect.GetCheckState();
	m_ckbtNotCollect.SetBtChecked(!bCkbtState,TRUE);
	m_ckbtNotCollect.EnableWindow(FALSE);

	m_ckbtCollect.SetBtChecked(bCkbtState,TRUE);
	m_ckbtCollect.EnableWindow(TRUE);

	m_ckbtCollectAll.SetBtChecked(bCkbtState,TRUE);
	m_ckbtCollectAll.EnableWindow(TRUE);

	m_cbMeltTemInterval.SetBeEditable(FALSE,TRUE);

	m_ckbtSelectGradient.EnableWindow(TRUE);
	return;
}

// 函数 CMyStepEditDlg::OnBnClickedCollectAll
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCheckState、SetBtChecked、EnableWindow、SetBeEditable。
void CMyStepEditDlg::OnBnClickedCollectAll()
{
	BOOL bCkbtState = m_ckbtCollectAll.GetCheckState();
	m_ckbtCollectAll.SetBtChecked(!bCkbtState,TRUE);
	m_ckbtCollectAll.EnableWindow(FALSE);

	m_ckbtCollect.SetBtChecked(bCkbtState,TRUE);
	m_ckbtCollect.EnableWindow(TRUE);

	m_ckbtNotCollect.SetBtChecked(bCkbtState,TRUE);
	m_ckbtNotCollect.EnableWindow(TRUE);

	m_cbMeltTemInterval.SetBeEditable(TRUE,TRUE);

	if(m_ckbtSelectGradient.GetCheckState())
	{
		m_ckbtSelectGradient.SetBtChecked(FALSE,TRUE);
		m_edGradientMaxTem.SetBeEditable(FALSE,TRUE);
	}
	m_ckbtSelectGradient.EnableWindow(FALSE);
	return;
}

// 函数 CMyStepEditDlg::OnBnClickedSelectGradient
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetBtChecked、GetCheckState、SetBeEditable、_ttof、GetText、SetText。
void CMyStepEditDlg::OnBnClickedSelectGradient()
{
	m_ckbtSelectGradient.SetBtChecked(!m_ckbtSelectGradient.GetCheckState(),TRUE);
	m_edGradientMaxTem.SetBeEditable(m_ckbtSelectGradient.GetCheckState(),TRUE);

	if(m_ckbtSelectGradient.GetCheckState())
	{
		float fStart = _ttof(m_edAimTem.GetText());
		float fEnd = _ttof(m_edGradientMaxTem.GetText());
		if(fStart < GRADIENT_MINVALUE || fStart > GRADIENT_MAXVALUE)
		{
			m_edAimTem.SetText(_T("60.0"),TRUE,TRUE);
			if(fEnd < 60)
			{
				m_edGradientMaxTem.SetText(_T("70.0"),TRUE,TRUE);
			}
		}

		if(fEnd < GRADIENT_MINVALUE || fEnd > GRADIENT_MAXVALUE)
		{
			m_edGradientMaxTem.SetText(_T("70.0"),TRUE,TRUE);
			if(fStart > 70)
			{
				m_edAimTem.SetText(_T("60.0"),TRUE,TRUE);
			}
		}
	}

	return;
}

// 函数 CMyStepEditDlg::OnBnClickedSave
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 tempStr、_T、GetText、_ttof、Format、PopNormalTipInfo。
void CMyStepEditDlg::OnBnClickedSave()
{
	CString tempStr(_T(""));

	float fAimTem = 0;
	tempStr = m_edAimTem.GetText();
	fAimTem = _ttof(tempStr);
	if(fAimTem < MINTEMPERATURE || fAimTem > MAXTEMPERATURE)
	{
		tempStr.Format(theApp.m_pLangInfo->GetText(229),MINTEMPERATURE,MAXTEMPERATURE);
		PopNormalTipInfo(tempStr);
		return;
	}

	int holdSec = 0;
	tempStr = m_edHoldSec.GetText();
	holdSec = _ttoi(tempStr);
	if(holdSec < MINSTEPHOLDSEC || holdSec > MAXSTEPHOLDSEC)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(231));
		return;
	}

	float fTemRate = 0;
	tempStr = m_cbTemRate.GetText();
	fTemRate = _ttof(tempStr);
	if(fTemRate <= 0 || fTemRate > AMLTEMRATE_MAXVALUE)
	{
		tempStr.Format(theApp.m_pLangInfo->GetText(232),AMLTEMRATE_MAXVALUE);
		PopNormalTipInfo(tempStr);
		return;
	}

	tempStr = m_edSegName.GetText();
	if(_T("") == tempStr || tempStr.GetLength() > 20)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(233));
		return;
	}
	m_stepEditInfo.m_strSegName = tempStr;

	tempStr = m_edStepTag.GetText();
	if(_T("") == tempStr || tempStr.GetLength() > 20)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(234));
		return;
	}
	m_stepEditInfo.m_strStepName = tempStr;

	m_stepEditInfo.m_fAimTem = fAimTem;

	m_stepEditInfo.m_fGradientMaxTem = _ttof(m_edGradientMaxTem.GetText());

	m_stepEditInfo.m_holdSec = holdSec;

	m_stepEditInfo.m_fRate = fTemRate;

	m_stepEditInfo.m_bSelGradient = m_ckbtSelectGradient.GetCheckState();

	if(m_stepEditInfo.m_bSelGradient)
	{
		if(m_stepEditInfo.m_fAimTem < GRADIENT_MINVALUE || m_stepEditInfo.m_fAimTem > GRADIENT_MAXVALUE)
		{
			tempStr.Format(theApp.m_pLangInfo->GetText(310),GRADIENT_MINVALUE,GRADIENT_MAXVALUE);
			PopNormalTipInfo(tempStr);
			return;
		}

		if(m_stepEditInfo.m_fGradientMaxTem < GRADIENT_MINVALUE || m_stepEditInfo.m_fGradientMaxTem > GRADIENT_MAXVALUE)
		{
			tempStr.Format(theApp.m_pLangInfo->GetText(310),GRADIENT_MINVALUE,GRADIENT_MAXVALUE);
			PopNormalTipInfo(tempStr);
			return;
		}

		if(m_stepEditInfo.m_fGradientMaxTem - m_stepEditInfo.m_fAimTem > 24 || m_stepEditInfo.m_fGradientMaxTem < m_stepEditInfo.m_fAimTem)
		{
			PopNormalTipInfo(theApp.m_pLangInfo->GetText(235));
			return;
		}
	}

	if(m_ckbtNotCollect.GetCheckState())
	{
		m_stepEditInfo.m_iCollect = 1;
	}
	else if(m_ckbtCollect.GetCheckState())
	{
		if(m_stepEditInfo.m_bCollectExistExceptThisStep)
		{
			PopNormalTipInfo(theApp.m_pLangInfo->GetText(308));
			return;
		}
		m_stepEditInfo.m_iCollect = 2;
	}
	else
	{
		if(m_stepEditInfo.m_bCollectAllExistExceptThisStep)
		{
			PopNormalTipInfo(theApp.m_pLangInfo->GetText(309));
			return;
		}
		m_stepEditInfo.m_iCollect = 3;
	}

	float fIncrement = _ttof(m_cbMeltTemInterval.GetText());
	if(fIncrement <= 0.1)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(307));
		return;
	}
	m_stepEditInfo.m_fIncrement = fIncrement;

	OnOK();
	return;
}

// 函数 CMyStepEditDlg::OnBnClickedCancel
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 OnCancel。
void CMyStepEditDlg::OnBnClickedCancel()
{
	OnCancel();
	return;
}

// 函数 CMyStepEditDlg::SetRoundRect
// 作用：设置SetRoundRect。
// 参数：x；y。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetClientRect、CreateRoundRectRgn、SetWindowRgn。
BOOL CMyStepEditDlg::SetRoundRect(int x /*= 5*/,int y /*= 5*/)
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
