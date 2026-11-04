// 【交接】 GeneralPcr\UserLoginDlg.cpp
// 作用：UserLoginDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CUserLoginDlg、CDialogEx、InitFont1、DeleteObject、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND。
// AnaAmlParamDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"
#include "UserLoginDlg.h"
#include "afxdialogex.h"

// CUserLoginDlg dialog

IMPLEMENT_DYNAMIC(CUserLoginDlg, CDialogEx)

// 函数 CUserLoginDlg::CUserLoginDlg
// 作用：执行CUserLoginDlg。
// 参数：pParent：指针，指向调用方传入的对象；pListUser：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 InitFont1。
CUserLoginDlg::CUserLoginDlg(CWnd* pParent /*=NULL*/,CUserInfoList* pListUser /*= NULL*/)
	: CDialogEx(CUserLoginDlg::IDD, pParent),m_imgBk(_T(".\\BkPic\\LoginBk.png"))
{
	InitFont1(30);
	m_pListUser = pListUser;
}

// 函数 CUserLoginDlg::~CUserLoginDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject。
CUserLoginDlg::~CUserLoginDlg()
{
	m_fontSet1.DeleteObject();
}

// 函数 CUserLoginDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CUserLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUserLoginDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(ID_USERLOGINDLG_BT_OK,&CUserLoginDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_USERLOGINDLG_BT_CANCEL,&CUserLoginDlg::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CUserLoginDlg message handlers
// 函数 CUserLoginDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 clock、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CUserLoginDlg::OnEraseBkgnd(CDC* pDC)
{
#ifdef _DEBUG
	clock_t startMs = clock();
#endif

	CRect rect; 
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);
	
	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(&rect,CLR_SOFT_LIGHT);

	DrawRoundRectangleNew(&memDc,360 * m_dHoriRatio,240 * m_dVertRatio,600 * m_dHoriRatio,600 * m_dVertRatio - 1,16,0,0,16,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF));

	//绘制背景图片
	Graphics graphics(memDc.m_hDC);
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	Rect rcBkPic;
	rcBkPic.X = 360 * m_dHoriRatio + 600 * m_dHoriRatio;
	rcBkPic.Y = 240 * m_dVertRatio;
	rcBkPic.Width = 594 * m_dHoriRatio;
	rcBkPic.Height = 600 * m_dVertRatio;
	graphics.DrawImage(&m_imgBk,rcBkPic,0,0,m_imgBk.GetWidth(),m_imgBk.GetHeight(),UnitPixel,&ImgAtt);

	graphics.ReleaseHDC(memDc.m_hDC);

	memDc.SetBkMode(TRANSPARENT);
	memDc.SetTextColor(m_txClr1);
	CFont* pOldFont = memDc.SelectObject(&m_fontSet);

	memDc.FillSolidRect(394 * m_dHoriRatio,310 * m_dVertRatio,12 * m_dHoriRatio,4 * m_dVertRatio,CLR_SOFT_THEME);
	memDc.FillSolidRect(398 * m_dHoriRatio,306 * m_dVertRatio,4 * m_dHoriRatio,12 * m_dVertRatio,CLR_SOFT_THEME);

	memDc.DrawText(theApp.m_pLangInfo->GetText(207),CRect(422 * m_dHoriRatio,356 * m_dVertRatio,622 * m_dHoriRatio,386 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	memDc.SetTextColor(CLR_2LEVEL_THEME);
	memDc.SelectObject(&m_fontSet1);
	memDc.DrawText(theApp.m_pLangInfo->GetText(140),CRect(422 * m_dHoriRatio,290 * m_dVertRatio,722 * m_dHoriRatio,334 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);
	
	clock_t ckStart = clock();	
	Node<CRect>* pNodeRst = m_rcManage.m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDc,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}
	ckStart = clock() - ckStart;

	memDc.SelectObject(pOldFont);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

#ifdef _DEBUG
	clock_t existMs = clock() - startMs;
#endif

	return TRUE;
}

// 函数 CUserLoginDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、Width、Height、InitDlg、CreateCtrl、InitCtrl。
BOOL CUserLoginDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	SetWindowPos(NULL,theApp.m_rcWorkArea.left,theApp.m_rcWorkArea.top,theApp.m_rcWorkArea.Width(),theApp.m_rcWorkArea.Height(),SWP_NOZORDER);

	InitDlg();
	CreateCtrl();
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();

	ShowCtrl();

	return TRUE;
}

// 函数 CUserLoginDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont、SetMyFont1。
void CUserLoginDlg::InitDlg()
{
	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,20 * m_dTxRatio,FW_MEDIUM,TYPE_PIXEL);
	SetMyFont1(m_stTxFont,30 * m_dTxRatio,FW_MEDIUM,TYPE_PIXEL);
}

// 函数 CUserLoginDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateCb、CreateEd、CreateCkbt。
void CUserLoginDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateCb();
	CreateEd();
	CreateCkbt();
}

// 函数 CUserLoginDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitCb、InitEd、InitCkbt。
void CUserLoginDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitCb();
	InitEd();
	InitCkbt();
}

// 函数 CUserLoginDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、SetWindowPos、AddRectToDelete、CalcRectResult。
void CUserLoginDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	m_cbUserName.SetWindowPos(this,422 * m_dHoriRatio,473 * m_dVertRatio,480 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(422 * m_dHoriRatio,473 * m_dVertRatio,480 * m_dHoriRatio,40 * m_dVertRatio);

	m_edCode.SetWindowPos(this,422 * m_dHoriRatio,547 * m_dVertRatio,480 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(422 * m_dHoriRatio,547 * m_dVertRatio,480 * m_dHoriRatio,40 * m_dVertRatio);

	m_btOk.SetWindowPos(this,422 * m_dHoriRatio,633 * m_dVertRatio,384 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(422 * m_dHoriRatio,633 * m_dVertRatio,384 * m_dHoriRatio,40 * m_dVertRatio);

	m_btCancel.SetWindowPos(this,822 * m_dHoriRatio,633 * m_dVertRatio,80 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(822 * m_dHoriRatio,633 * m_dVertRatio,80 * m_dHoriRatio,40 * m_dVertRatio);

	m_rcManage.CalcRectResult();
}

// 函数 CUserLoginDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CUserLoginDlg::ShowCtrl()
{
	m_btOk.ShowWindow(SW_SHOW);
	m_btCancel.ShowWindow(SW_SHOW);
	m_cbUserName.ShowWindow(SW_SHOW);
	m_edCode.ShowWindow(SW_SHOW);
}

// 函数 CUserLoginDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CUserLoginDlg::CreateBt()
{
	m_btOk.Create(_T("登录"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_USERLOGINDLG_BT_OK);
	m_btCancel.Create(_T("退出"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_USERLOGINDLG_BT_CANCEL);
}

// 函数 CUserLoginDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CUserLoginDlg::CreateSt()
{
	
}

// 函数 CUserLoginDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CUserLoginDlg::CreateCb()
{
	CRect rcCreate(0,0,0,0);

	m_cbUserName.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_USERLOGINDLG_CB_USERNAME);
}

// 函数 CUserLoginDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CUserLoginDlg::CreateEd()
{
	m_edCode.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL | ES_PASSWORD, CRect(0,0,0,0), this,ID_USERLOGINDLG_ED_CODE);
}

// 函数 CUserLoginDlg::CreateCkbt
// 作用：创建或加入CreateCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CUserLoginDlg::CreateCkbt()
{
	
}

// 函数 CUserLoginDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBkColor、Color、SetBkColorEnd。
void CUserLoginDlg::InitBt()
{
	int iFontH = 18 * CFontSet::m_dTxRatio;

	m_btOk.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
#ifndef GRADIENT_SOME_BTBK
	m_btOk.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),FALSE);
	m_btOk.SetBkColor(COLOR_BTBK_NORMAL,COLOR_BTBK_HOVER,COLOR_BTBK_CLICKED,COLOR_BTBK_DISABLED);
#else
	m_btOk.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
	m_btOk.SetBkColor(Color(0X38,0XE0,0XEF),Color(0X3A,0XEF,0XFF),COLOR_SOFT_THEME,Color(0XF1,0XF1,0XF1));
	m_btOk.SetBkColorEnd(COLOR_SOFT_THEME,Color(0X38,0XE0,0XEF),Color(0X02,0X8D,0X99),Color(0XD8,0XD8,0XD8));
#endif
	m_btOk.SetTextColor(RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XC6,0XC4,0XC4));

	m_btCancel.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btCancel.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
}

// 函数 CUserLoginDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CUserLoginDlg::InitSt()
{
	
}

// 函数 CUserLoginDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
void CUserLoginDlg::InitCb()
{
	int iFontH = 18 * CFontSet::m_dTxRatio;

	m_cbUserName.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_cbUserName.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_cbUserName.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_cbUserName.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XC6,0XC6,0XC6));
	m_cbUserName.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbUserName.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	//m_cbUserName.SetWorkState(EWS_READONLY);
	m_cbUserName.SetLeftImageParam(TRUE,2,_T(".\\BkPic\\username.png"));
	m_cbUserName.m_iLeftIndent = 48 * m_dHoriRatio;
	m_cbUserName.m_iRightIndent = 44 * m_dHoriRatio;
	m_cbUserName.m_arrowInfo.m_clrArrow = Color(0X39,0X45,0X65);
	m_cbUserName.m_arrowInfo.m_arrowW = 12 * m_dHoriRatio; 
	m_cbUserName.m_arrowInfo.m_arrowH = 8 * m_dVertRatio;


#ifdef ONLY_ONE_DEFAULT_ACCOUNT

	#ifdef DEFAULT_ADMIN
		m_cbUserName.InsertString(0,DEFAULT_USER_REAGENT);
	#else

		#ifdef _DEBUG
			m_cbUserName.InsertString(0,DEFAULT_USER_REAGENT);
		#else
			m_cbUserName.InsertString(0,DEFAULT_USER_IVD);
		#endif
	#endif

	m_cbUserName.SetCurSel(0);

#else

	m_cbUserName.InsertString(0,DEFAULT_USER_IVD);
	m_cbUserName.InsertString(1,DEFAULT_USER_REAGENT);

	#ifdef PS96INSTRUMENT
		m_cbUserName.SetCurSel(0);
	#else
		m_cbUserName.SetCurSel(1);
	#endif

#endif
	
	if(NULL != m_pListUser)
	{
		POSITION pos = m_pListUser->GetHeadPosition();
		while (pos != NULL)
		{
			CDBUserInfo* pUser = m_pListUser->GetNext(pos);
			m_cbUserName.InsertString(pUser->GetName());
		}
	}	

	return;
}

// 函数 CUserLoginDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
void CUserLoginDlg::InitEd()
{
	int fontH = 18 * CFontSet::m_dTxRatio;

	m_edCode.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edCode.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edCode.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edCode.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XC6,0XC6,0XC6));
	m_edCode.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_edCode.SetTellParentTxChangedParam(TRUE,0);
	m_edCode.SetLeftImageParam(TRUE,2,_T(".\\BkPic\\code.png"));
	m_edCode.m_iLeftIndent = 48 * m_dHoriRatio;
	m_edCode.SetPasswordParam(ETM_PASSWORDDOT,2 * m_dHoriRatio,4 * m_dHoriRatio);

#ifdef _DEBUG
	m_edCode.SetText(_T("123456"));
#endif
}

// 函数 CUserLoginDlg::InitCkbt
// 作用：初始化InitCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CUserLoginDlg::InitCkbt()
{
	
}

// 函数 CUserLoginDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowText、GetText。
void CUserLoginDlg::SetCtrlText()
{
	m_btOk.SetWindowText(theApp.m_pLangInfo->GetText(144));
	m_btCancel.SetWindowText(theApp.m_pLangInfo->GetText(206));

	return;
}

// 函数 CUserLoginDlg::OnBnClickedOk
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 strUserName、_T、strCode、GetText、IsEmpty、PopWarningTipInfo。
void CUserLoginDlg::OnBnClickedOk()
{
	CString strUserName(_T("")),strCode(_T(""));

	strUserName = m_cbUserName.GetText();
	strCode = m_edCode.GetText();

	if(strUserName.IsEmpty())
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(142));
		return;
	}

	if(strCode.IsEmpty())
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(143));
		return;
	}

	int iRet = CheckUserInfo(strUserName,strCode);
	if(-1 == iRet)
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(145));
		return;
	}

	if(-2 == iRet)
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(146));
		return;
	}

	OnOK();
	return;
}

// 函数 CUserLoginDlg::OnBnClickedCancel
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 OnCancel。
void CUserLoginDlg::OnBnClickedCancel()
{
	OnCancel();
	return;
}

// 函数 CUserLoginDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::OnLButtonDown。
void CUserLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags,point);
}

// 函数 CUserLoginDlg::InitFont1
// 作用：初始化InitFont1。
// 参数：lfHeight。
// 返回：没有返回值。
// 过程：函数里会调用 _tcscpy、_T、CreateFontIndirect。
void CUserLoginDlg::InitFont1(int lfHeight)
{
	m_logFont1.lfHeight = lfHeight;
	m_logFont1.lfWidth = 0;
	m_logFont1.lfEscapement = 0;
	m_logFont1.lfOrientation = 400;
	m_logFont1.lfWeight = FW_NORMAL;
	m_logFont1.lfItalic = FALSE;
	m_logFont1.lfUnderline = FALSE;
	m_logFont1.lfStrikeOut = 0;
	m_logFont1.lfCharSet = ANSI_CHARSET;
	m_logFont1.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logFont1.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logFont1.lfQuality = PROOF_QUALITY;
	m_logFont1.lfPitchAndFamily = VARIABLE_PITCH | FF_SCRIPT;
	_tcscpy(m_logFont1.lfFaceName,  _T("微软雅黑"));

	m_fontSet1.CreateFontIndirect(&m_logFont1);  
}

// 函数 CUserLoginDlg::SetMyFont1
// 作用：设置SetMyFont1。
// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double、_tcscpy、DeleteObject、CreateFontIndirect。
void CUserLoginDlg::SetMyFont1(CString fontName,int nHeight,int nWeight /*= FW_NORMAL*/,FONT_UNIT_TYPE fontUnitType /*= TYPE_POUND*/) //nHeight单位为 磅，即1/72英寸
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFont1.lfHeight = (double(nHeight * fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFont1.lfHeight = nHeight;
	}

	_tcscpy(m_logFont1.lfFaceName, fontName);
	m_logFont1.lfWeight = nWeight;
	m_fontSet1.DeleteObject();
	m_fontSet1.CreateFontIndirect(&m_logFont1);
}

// 函数 CUserLoginDlg::CheckUserInfo
// 作用：判断CheckUserInfo是否成立。
// 参数：strName：字符串；strCode：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetName、SetPassword、SetStatus、SetPermissionType、GetHeadPosition、GetNext。
int CUserLoginDlg::CheckUserInfo(CString strName,CString strCode)
{
	BOOL bFindName = FALSE,bRightCode = FALSE;
	if(DEFAULT_USER_IVD == strName || DEFAULT_USER_REAGENT == strName || DEFAULT_DEVELOPER == strName)
	{
		bFindName = TRUE;
		if(DEFAULT_PASSWORD == strCode)
		{
			bRightCode = TRUE;

			m_userInfo.SetName(strName);   
			m_userInfo.SetPassword(strCode);  
			m_userInfo.SetStatus(1);
			if(DEFAULT_USER_IVD == strName)
			{
				m_userInfo.SetPermissionType(EPT_IVD);
			}
			else if (DEFAULT_DEVELOPER == strName)
			{
				m_userInfo.SetPermissionType(EPT_DEVELOPER);
			}	
			else
			{
				m_userInfo.SetPermissionType(EPT_ADMIN);
			}	
		}
	}
	else
	{
		if(NULL != m_pListUser)
		{
			POSITION pos = m_pListUser->GetHeadPosition();
			while (pos != NULL)
			{
				CDBUserInfo* pUser = m_pListUser->GetNext(pos);
				if(pUser->GetName() == strName)
				{
					bFindName = TRUE;
					if(pUser->GetPassword() == strCode)
					{
						bRightCode = TRUE;
						m_userInfo = *pUser;
					}
					break;;
				}
			}
		}
	}

	if(!bFindName)
	{
		return -1;
	}
	if(!bRightCode)
	{
		return -2;
	}

	return 0;
}
