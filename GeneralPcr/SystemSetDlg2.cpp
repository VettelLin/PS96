// 【交接】 GeneralPcr\SystemSetDlg2.cpp
// 作用：SystemSetDlg2。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：IMPLEMENT_DYNAMIC、CSystemSetDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、END_MESSAGE_MAP。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "SystemSetDlg.h"
#include "GeneralPcrDlg.h"
#include "GeneralPcr.h"

// CSystemSetDlg dialog
IMPLEMENT_DYNAMIC(CSystemSetDlg, CDialogEx)

// 函数 CSystemSetDlg::CSystemSetDlg
// 作用：执行CSystemSetDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSystemSetDlg::CSystemSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSystemSetDlg::IDD, pParent)
{
	m_bCtrlCreated = FALSE;
}

// 函数 CSystemSetDlg::~CSystemSetDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSystemSetDlg::~CSystemSetDlg()
{
}

// 函数 CSystemSetDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CSystemSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSystemSetDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// 函数 CSystemSetDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CSystemSetDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(0,0,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);
	DrawRoundRectangleNew(&memDc,0,0,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	Node<CRect>* pNodeRst = m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDc,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CSystemSetDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CSystemSetDlg::OnSize(UINT nType,int cx,int cy)
{
	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}

	__super::OnSize(nType,cx,cy);
}	

// 函数 CSystemSetDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 CreateCtrl、InitDlg、InitCtrl、SetCtrlPos、SetCtrlText、ShowCtrl。
BOOL CSystemSetDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	CreateCtrl();
	InitDlg();
	InitCtrl();
	m_bCtrlCreated = TRUE;
	SetCtrlPos();
	SetCtrlText();
	ShowCtrl();

	return TRUE;
}

// 函数 CSystemSetDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateEd、CreateLst。
void CSystemSetDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateEd();
	CreateLst();
}

// 函数 CSystemSetDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSystemSetDlg::CreateBt()
{

}

// 函数 CSystemSetDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSystemSetDlg::CreateSt()
{
	
}

// 函数 CSystemSetDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSystemSetDlg::CreateEd()
{
	
}

// 函数 CSystemSetDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CSystemSetDlg::CreateLst()
{
	m_lstUserInfo.Create(IDD_MIDDLEDLG,this);
}

// 函数 CSystemSetDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CSystemSetDlg::InitDlg()
{
	SetTextClr1(RGB(86,86,86));
	SetMyFont(theApp.m_strTextFont,14,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CSystemSetDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitEd、InitLst。
void CSystemSetDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitEd();
	InitLst();
}

// 函数 CSystemSetDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSystemSetDlg::InitBt()
{
	
}

// 函数 CSystemSetDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSystemSetDlg::InitSt()
{
	
}

// 函数 CSystemSetDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSystemSetDlg::InitEd()
{
	
}

// 函数 CSystemSetDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetHeaderHeight、SetMyHeaderFont、SetScrollArrowWH、SetFourAngleBkColor、RGB、SetItemHeight。
void CSystemSetDlg::InitLst()
{
	int iFontH = 16 * m_dTxRatio;

	m_lstUserInfo.SetHeaderHeight(24 * m_dVertRatio);
	m_lstUserInfo.SetMyHeaderFont(theApp.m_strTextFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_lstUserInfo.SetScrollArrowWH(4 * m_dHoriRatio,8 * m_dVertRatio);
	m_lstUserInfo.SetFourAngleBkColor(RGB(0XFF,0XFF,0XFF));
	m_lstUserInfo.SetItemHeight(53 * m_dVertRatio);

	int iTempInt1 = 34 * m_dVertRatio;
	m_lstUserInfo.m_horiScroll.m_arrowWH = iTempInt1;
	m_lstUserInfo.m_horiScroll.m_scrollH = iTempInt1;
	m_lstUserInfo.m_vertScroll.m_arrowWH = iTempInt1;
	m_lstUserInfo.m_vertScroll.m_scrollW = iTempInt1;
	m_lstUserInfo.SetMyFont(theApp.m_strTextFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_lstUserInfo.SetTextClr1(RGB(0X39,0X45,0X65));

	m_lstUserInfo.InsertColumn(0,_T(""),FALSE);
	m_lstUserInfo.InsertColumn(1,_T(""),FALSE);
	m_lstUserInfo.InsertColumn(2,_T(""),FALSE);
	m_lstUserInfo.InsertColumn(3,_T(""),FALSE);
	
	int iTempInt2 = 0,iW = 1720 * m_dHoriRatio;
	iTempInt2 = 60 * m_dHoriRatio;
	m_lstUserInfo.SetColumnWidth(0,iTempInt2);
	iW -= iTempInt2;
	iTempInt2 = 466 * m_dHoriRatio;
	m_lstUserInfo.SetColumnWidth(1,iTempInt2);
	iW -= iTempInt2;
	iTempInt2 = 540 * m_dHoriRatio;
	m_lstUserInfo.SetColumnWidth(2,iTempInt2);
	iW -= iTempInt2;
	iW -= m_lstUserInfo.GetFrameLineWidth() * 2;
	m_lstUserInfo.SetColumnWidth(3,iW);

	return;
}

// 函数 CSystemSetDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、MoveWindow、AddRectToDelete、CalcRectResult。
void CSystemSetDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(rect);

	m_rcInit = rect;
	ClearRectToDelete();

	m_lstUserInfo.MoveWindow(16 * m_dHoriRatio,16 * m_dVertRatio,1720 * m_dHoriRatio,840 * m_dVertRatio,FALSE);
	AddRectToDelete(16 * m_dHoriRatio,16 * m_dVertRatio,1720 * m_dHoriRatio,840 * m_dVertRatio);

	CalcRectResult();

	return;
}

// 函数 CSystemSetDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CSystemSetDlg::ShowCtrl()
{
	m_lstUserInfo.ShowWindow(SW_SHOW);
}

// 函数 CSystemSetDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetColumnText、GetText。
void CSystemSetDlg::SetCtrlText()
{
	m_lstUserInfo.SetColumnText(0,theApp.m_pLangInfo->GetText(29));
	m_lstUserInfo.SetColumnText(1,theApp.m_pLangInfo->GetText(350));
	m_lstUserInfo.SetColumnText(2,theApp.m_pLangInfo->GetText(351));
	m_lstUserInfo.SetColumnText(3,theApp.m_pLangInfo->GetText(352));

	return;
}

// 函数 CSystemSetDlg::ResetLstColumnText
// 作用：更新或清除ResetLstColumnText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetColumnText、GetText。
void CSystemSetDlg::ResetLstColumnText()
{
	m_lstUserInfo.SetColumnText(0,theApp.m_pLangInfo->GetText(29));
	m_lstUserInfo.SetColumnText(1,theApp.m_pLangInfo->GetText(350));
	m_lstUserInfo.SetColumnText(2,theApp.m_pLangInfo->GetText(351));
	m_lstUserInfo.SetColumnText(3,theApp.m_pLangInfo->GetText(352));

	return;
}

// 函数 CSystemSetDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetMyHeaderFont、SetMyFont、ResetLstColumnText。
int CSystemSetDlg::RefreshLanguageDisplay()
{
	int iFontH = 16 * m_dTxRatio;

	m_lstUserInfo.SetMyHeaderFont(theApp.m_strTextFont,iFontH);
	m_lstUserInfo.SetMyFont(theApp.m_strTextFont);
	ResetLstColumnText();

	return 0;
}




