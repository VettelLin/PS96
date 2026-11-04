// 【交接】 GeneralPcr\MyGeneTipDlg.cpp
// 作用：MyGeneTipDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyGeneTipDlg、CDialogEx、_T、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_CREATE。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "MyGeneTipDlg.h"
#include "GeneralPcrDlg.h"
#include "GeneralPcr.h"

// CMyGeneTipDlg dialog
IMPLEMENT_DYNAMIC(CMyGeneTipDlg, CDialogEx)

// 函数 CMyGeneTipDlg::CMyGeneTipDlg
// 作用：执行CMyGeneTipDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CMyGeneTipDlg::CMyGeneTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyGeneTipDlg::IDD, pParent)
{
	m_frameWidth = 1;
	m_roundValue = 20;
	m_strNoteInfo = _T("");
	m_noteFontSize = 20;
	m_dwNoteStyle = DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_NOFULLWIDTHCHARBREAK;
	m_eGeneTipType = EGTT_NORMAL;
	m_width = 480;
	m_height = 420;
	m_iCapHeight = 60;
	m_retCode = IDCANCEL;
}

// 函数 CMyGeneTipDlg::~CMyGeneTipDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyGeneTipDlg::~CMyGeneTipDlg()
{
}

// 函数 CMyGeneTipDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CMyGeneTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyGeneTipDlg, CDialogEx)
	ON_WM_ERASEBKGND() 
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_GENERALTIPDLG_BT_OK,&CMyGeneTipDlg::OnBnClickedOk)
	ON_BN_CLICKED(ID_GENERALTIPDLG_BT_CANCEL,&CMyGeneTipDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// 函数 CMyGeneTipDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CMyGeneTipDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	
#ifdef POPDLG_USESHADEBK
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
	rcUseful.left = rect.left + (rect.Width() - m_width) / 2;
	rcUseful.top = rect.top + (rect.Height() - m_height) / 2;
	rcUseful.right = rcUseful.left + m_width;
	rcUseful.bottom = rcUseful.top + m_height;

	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top + m_iCapHeight,rcUseful.Width(),rcUseful.Height() - m_iCapHeight,0,0,m_roundValue,m_roundValue,FALSE,Color(197,197,197),m_frameWidth,TRUE,Color(255,255,255),1);
	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top,m_width,m_iCapHeight,m_roundValue,m_roundValue,0,0,FALSE,Color(0X5F,0X6F,0X7F),m_frameWidth,TRUE,COLOR_SOFT_THEME,1);

	memDc.DrawText(pLangInfo->GetText(147),CRect(rcUseful.left + 10,rcUseful.top + 5,rcUseful.right - 10,rcUseful.top + m_iCapHeight - 5),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	memDc.SelectObject(pOldFont);

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(0XD8,0XD8,0XD8));
	CPen* pOldPen = memDc.SelectObject(&pen);
	memDc.MoveTo(rcUseful.left,rcUseful.top + 331 * m_dVertRatio);
	memDc.LineTo(rcUseful.left + m_width,rcUseful.top + 331 * m_dVertRatio);
	memDc.SelectObject(pOldPen);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);
	clock_t ckStart = clock();	
	Node<CRect>* pNodeRst = m_rcManage.m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDc,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}
	ckStart = clock() - ckStart;

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	memDc2.SelectObject(&pOldBitmapCB2);
	bitMapCB2.DeleteObject();
	memDc2.DeleteDC();
#else
	double dHoriRatio = theApp.m_dHoriRatio;
	double dVertRatio = theApp.m_dVertRatio;

	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	CPen pen;
	CPen* pOldPen = NULL;
	DrawRoundRectangleNew(&memDc,0 * dHoriRatio,0 * dVertRatio,rect.Width() - m_frameWidth * 2,rect.Height() - m_frameWidth * 2,m_roundValue,m_roundValue,m_roundValue,m_roundValue,TRUE,Color(197,197,197),m_frameWidth,FALSE,Color(3,91,199),1);
	DrawRoundRectangleNew(&memDc,0 * dHoriRatio,0 * dVertRatio,330 * dHoriRatio,40 * dVertRatio,4,4,0,0,TRUE,Color(3,91,199),2,TRUE,Color(3,91,199),1);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);
	memDc.DrawText(pLangInfo->GetText(147),CRect(10,5,rect.Width() - 10,40 * dVertRatio - 5),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	memDc.SelectObject(pOldFont);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();
#endif

	return TRUE;
}

// 函数 CMyGeneTipDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CMyGeneTipDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_width *= m_dHoriRatio;
	m_height *= m_dVertRatio;
	m_iCapHeight *= m_dVertRatio;
	m_noteFontSize *= m_dTxRatio;

	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CMyGeneTipDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PostMessage、MAKELPARAM。
void CMyGeneTipDlg::OnLButtonDown(UINT nFlags, CPoint point)
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

// 函数 CMyGeneTipDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、GetParent、Width、Height、SetRoundRect、CenterWindow。
BOOL CMyGeneTipDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

#ifdef POPDLG_USESHADEBK
	SetWindowPos(GetParent(),theApp.m_rcWorkArea.left,theApp.m_rcWorkArea.top,theApp.m_rcWorkArea.Width(),theApp.m_rcWorkArea.Height(),SWP_NOZORDER);
#else
	SetWindowPos(GetParent(),0,0,m_width,m_height,SWP_NOZORDER);
	SetRoundRect(m_roundValue,m_roundValue);
	CenterWindow(GetParent());
#endif

	CreateCtrl();
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();
	CheckNoteInfoSize();

	ShowCtrl();

	return TRUE;
}

// 函数 CMyGeneTipDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateCkBt、CreateSt、CreateEd。
void CMyGeneTipDlg::CreateCtrl()
{
	CreateBt();
	CreateCkBt();
	CreateSt();
	CreateEd();
}

// 函数 CMyGeneTipDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CMyGeneTipDlg::CreateBt()
{
	m_btOk.Create(_T("确定"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_GENERALTIPDLG_BT_OK);
	m_btCancel.Create(_T("取消"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_GENERALTIPDLG_BT_CANCEL);
}

// 函数 CMyGeneTipDlg::CreateCkBt
// 作用：创建或加入CreateCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyGeneTipDlg::CreateCkBt()
{
	
}

// 函数 CMyGeneTipDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CMyGeneTipDlg::CreateSt()
{
	m_stNoteInfo.Create(_T(""),WS_CHILD,CRect(0,0,0,0),this,ID_GENERALTIPDLG_ST_NOTEINFO);
	m_stIcon.Create(_T(""),WS_CHILD,CRect(0,0,0,0),this,ID_GENERALTIPDLG_ST_ICON);
}

// 函数 CMyGeneTipDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyGeneTipDlg::CreateEd()
{
	
}

// 函数 CMyGeneTipDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CMyGeneTipDlg::InitDlg()
{
	int iFontH = 24 * m_dTxRatio;

	SetTextClr1(RGB(0XFF,0XFF,0XFF));
	SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CMyGeneTipDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCkBt、InitSt、InitEd。
void CMyGeneTipDlg::InitCtrl()
{
	InitBt();
	InitCkBt();
	InitSt();
	InitEd();
}

// 函数 CMyGeneTipDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBkColor、Color、SetBkColorEnd。
void CMyGeneTipDlg::InitBt()
{
	int iFontH = 18 * m_dTxRatio;

	m_btOk.SetMyFont(m_stTxFont,iFontH);
#ifndef GRADIENT_SOME_BTBK
	m_btOk.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),FALSE);
	m_btOk.SetBkColor(COLOR_BTBK_NORMAL,COLOR_BTBK_HOVER,COLOR_BTBK_CLICKED,COLOR_BTBK_DISABLED);
#else
	m_btOk.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
	m_btOk.SetBkColor(Color(0X38,0XE0,0XEF),Color(0X3A,0XEF,0XFF),COLOR_SOFT_THEME,Color(0XF1,0XF1,0XF1));
	m_btOk.SetBkColorEnd(COLOR_SOFT_THEME,Color(0X38,0XE0,0XEF),Color(0X02,0X8D,0X99),Color(0XD8,0XD8,0XD8));
#endif
	m_btOk.SetTextColor(RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XC6,0XC4,0XC4));

	m_btCancel.SetMyFont(m_stTxFont,iFontH);
	m_btCancel.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
}

// 函数 CMyGeneTipDlg::InitCkBt
// 作用：初始化InitCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyGeneTipDlg::InitCkBt()
{
	
}

// 函数 CMyGeneTipDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetBDynamic、SetBkColor、RGB、SetMyFont、SetTextColor、SetWordStyle。
void CMyGeneTipDlg::InitSt()
{
	m_stNoteInfo.SetBDynamic(TRUE);
	m_stNoteInfo.SetBkColor(RGB(0XFF,0XFF,0XFF));
	m_stNoteInfo.SetMyFont(m_stTxFont,m_noteFontSize,FW_NORMAL,TYPE_PIXEL);
	m_stNoteInfo.SetTextColor(RGB(0X39,0X45,0X65));
	m_stNoteInfo.SetWordStyle(m_dwNoteStyle);
	m_stNoteInfo.SetWindowText(m_strNoteInfo);

	CString strTemp(_T(""));
	m_stIcon.SetBkColor(RGB(0XFF,0XFF,0XFF));
	if(EGTT_NORMAL == m_eGeneTipType)
	{
		strTemp = _T(".\\BkPic\\normaltip.png");
	}
	else if(EGTT_QUERY == m_eGeneTipType)
	{
		strTemp = _T(".\\BkPic\\querytip.png");
	}
	else if(EGTT_WARNING == m_eGeneTipType)
	{
		strTemp = _T(".\\BkPic\\warningtip.png");
	}
	m_stIcon.SetPngBkPic(strTemp);
}

// 函数 CMyGeneTipDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyGeneTipDlg::InitEd()
{
	
}

// 函数 CMyGeneTipDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、Width、Height、SetWindowPos、AddRectToDelete。
void CMyGeneTipDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	CRect rcUseful;
#ifdef POPDLG_USESHADEBK
	rcUseful.left = rect.left + (rect.Width() - m_width) / 2;
	rcUseful.top = rect.top + (rect.Height() - m_height) / 2;
	rcUseful.right = rcUseful.left + m_width;
	rcUseful.bottom = rcUseful.top + m_height;
#endif
	
	int width = 90 * m_dHoriRatio;
	int height = 40 * m_dVertRatio;

	m_stIcon.SetWindowPos(this,rcUseful.left + 56 * m_dHoriRatio,rcUseful.top + 180 * m_dVertRatio,60 * m_dHoriRatio,61 * m_dVertRatio,SWP_NOZORDER);
	
	m_stNoteInfo.SetWindowPos(this,rcUseful.left + 156 * m_dHoriRatio,rcUseful.top + 138 * m_dVertRatio,290 * m_dHoriRatio,150 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(rcUseful.left + 156 * m_dHoriRatio,rcUseful.top + 138 * m_dVertRatio,290 * m_dHoriRatio,150 * m_dVertRatio);

	if(EGTT_NORMAL == m_eGeneTipType || EGTT_WARNING == m_eGeneTipType)
	{
		m_btOk.SetWindowPos(this,rcUseful.left + 342 * m_dHoriRatio,rcUseful.top + 356 * m_dVertRatio,width,height,SWP_NOZORDER);
		m_rcManage.AddRectToDelete(rcUseful.left + 342 * m_dHoriRatio,rcUseful.top + 356 * m_dVertRatio,width,height);
	}
	else if(EGTT_QUERY == m_eGeneTipType)
	{
		m_btOk.SetWindowPos(this,rcUseful.left + 228 * m_dHoriRatio,rcUseful.top + 356 * m_dVertRatio,width,height,SWP_NOZORDER);
		m_rcManage.AddRectToDelete(rcUseful.left + 228 * m_dHoriRatio,rcUseful.top + 356 * m_dVertRatio,width,height);

		m_btCancel.SetWindowPos(this,rcUseful.left + 342 * m_dHoriRatio,rcUseful.top + 356 * m_dVertRatio,width,height,SWP_NOZORDER);
		m_rcManage.AddRectToDelete(rcUseful.left + 342 * m_dHoriRatio,rcUseful.top + 356 * m_dVertRatio,width,height);
	}
	
	m_rcManage.CalcRectResult();

	return;
}

// 函数 CMyGeneTipDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CMyGeneTipDlg::ShowCtrl()
{
	m_stNoteInfo.ShowWindow(SW_SHOW);
	m_stIcon.ShowWindow(SW_SHOW);

	if(EGTT_NORMAL == m_eGeneTipType || EGTT_WARNING == m_eGeneTipType)
	{
		m_btOk.ShowWindow(SW_SHOW);
	}
	else if(EGTT_QUERY == m_eGeneTipType)
	{
		m_btOk.ShowWindow(SW_SHOW);
		m_btCancel.ShowWindow(SW_SHOW);
	}
}

// 函数 CMyGeneTipDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetWindowText、GetText。
void CMyGeneTipDlg::SetCtrlText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	if(EGTT_QUERY == m_eGeneTipType)
	{
		m_btOk.SetWindowText(pLangInfo->GetText(151));
		m_btCancel.SetWindowText(pLangInfo->GetText(152));
	}
	else
	{
		m_btOk.SetWindowText(pLangInfo->GetText(149));
		m_btCancel.SetWindowText(pLangInfo->GetText(150));
	}

	return;
}

// 函数 CMyGeneTipDlg::OnBnClickedOk
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 OnOK。
void CMyGeneTipDlg::OnBnClickedOk()
{
	if(EGTT_NORMAL == m_eGeneTipType || EGTT_WARNING == m_eGeneTipType)
	{
		m_retCode = IDOK;
	}
	else if(EGTT_QUERY == m_eGeneTipType)
	{
		m_retCode = IDYES;
	}
	else
	{
		m_retCode = IDOK;
	}
	OnOK();
	return;
}

// 函数 CMyGeneTipDlg::OnBnClickedCancel
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 OnCancel。
void CMyGeneTipDlg::OnBnClickedCancel()
{
	if(EGTT_NORMAL == m_eGeneTipType || EGTT_WARNING == m_eGeneTipType)
	{
		m_retCode = IDCANCEL;
	}
	else if(EGTT_QUERY == m_eGeneTipType)
	{
		m_retCode = IDCANCEL;
	}
	else
	{
		m_retCode = IDCANCEL;
	}
	OnCancel();
	return;
}

// 函数 CMyGeneTipDlg::SetNoteInfo
// 作用：设置SetNoteInfo。
// 参数：strNoteInfo：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyGeneTipDlg::SetNoteInfo(CString strNoteInfo)
{
	m_strNoteInfo = strNoteInfo;
}

// 函数 CMyGeneTipDlg::GetNoteInfo
// 作用：读取GetNoteInfo。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CMyGeneTipDlg::GetNoteInfo()
{
	return m_strNoteInfo;
}

// 函数 CMyGeneTipDlg::SetGeneTipType
// 作用：设置SetGeneTipType。
// 参数：eGeneType。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyGeneTipDlg::SetGeneTipType(EGENETIPTYPE eGeneType)
{
	m_eGeneTipType = eGeneType;
}

// 函数 CMyGeneTipDlg::GetGeneTipType
// 作用：读取GetGeneTipType。
// 参数：无。
// 返回：返回 EGENETIPTYPE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
EGENETIPTYPE CMyGeneTipDlg::GetGeneTipType()
{
	return m_eGeneTipType;
}

// 函数 CMyGeneTipDlg::SetNoteInfoStyle
// 作用：设置SetNoteInfoStyle。
// 参数：style。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyGeneTipDlg::SetNoteInfoStyle(DWORD style)
{
	m_dwNoteStyle = style;
}

// 函数 CMyGeneTipDlg::GetNoteInfoStyle
// 作用：读取GetNoteInfoStyle。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
DWORD CMyGeneTipDlg::GetNoteInfoStyle()
{
	return m_dwNoteStyle;
}

// 函数 CMyGeneTipDlg::SetRoundRect
// 作用：设置SetRoundRect。
// 参数：x；y。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetClientRect、CreateRoundRectRgn、SetWindowRgn。
BOOL CMyGeneTipDlg::SetRoundRect(int x /*= 5*/,int y /*= 5*/)
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

// 函数 CMyGeneTipDlg::CheckNoteInfoSize
// 作用：判断CheckNoteInfoSize是否成立。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 clock、GetSafeHwnd、GetDC、SelectObject、GetTextExtent、GetClientRect。
void CMyGeneTipDlg::CheckNoteInfoSize()
{
	clock_t startMs = clock();

	if(NULL == m_stNoteInfo.GetSafeHwnd())
	{
		return;
	}
	CDC* pDc = m_stNoteInfo.GetDC();
	CFont* pOldFont = pDc->SelectObject(&(m_stNoteInfo.m_fontSet));
	CSize sizeStr = pDc->GetTextExtent(m_strNoteInfo);

	CRect rcStatic;
	m_stNoteInfo.GetClientRect(&rcStatic);
	int iStWidth = rcStatic.Width();

	if(sizeStr.cx > iStWidth)
	{
		m_noteFontSize = 19 * m_dTxRatio;
		pDc->SelectObject(pOldFont);
		m_stNoteInfo.SetMyFont(m_stTxFont,m_noteFontSize,FW_NORMAL,TYPE_PIXEL);
		pDc->SelectObject(&(m_stNoteInfo.m_fontSet));
		sizeStr = pDc->GetTextExtent(m_strNoteInfo);

		if(sizeStr.cx > iStWidth)
		{
			m_dwNoteStyle = DT_LEFT | DT_VCENTER | DT_WORDBREAK | DT_EDITCONTROL | DT_NOFULLWIDTHCHARBREAK; 
			m_stNoteInfo.SetSingleLineState(FALSE);
			m_stNoteInfo.SetWordStyle(m_dwNoteStyle); 
		}
		else
		{
			m_stNoteInfo.SetSingleLineState(TRUE);
		}
	}

	pDc->SelectObject(pOldFont);
	ReleaseDC(pDc);

	return;
}



