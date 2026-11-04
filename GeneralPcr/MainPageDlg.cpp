// 【交接】 GeneralPcr\MainPageDlg.cpp
// 作用：MainPageDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMainPageDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、ON_WM_CREATE。
// SamSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "MainPageDlg.h"
#include "afxdialogex.h"


// CMainPageDlg dialog

IMPLEMENT_DYNAMIC(CMainPageDlg, CDialogEx)

// 函数 CMainPageDlg::CMainPageDlg
// 作用：执行CMainPageDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMainPageDlg::CMainPageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMainPageDlg::IDD, pParent)
{
	m_bCtrlCreated = FALSE;
	m_pCurSelSwt = NULL;
	m_pCurSelWnd = NULL;
	m_iSwitchBtBkH = 40;
	m_iSwitchBtH = 32;
	m_iSwitchBtBkW = 244;
	m_iSwitchBtW = 120;
}

// 函数 CMainPageDlg::~CMainPageDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMainPageDlg::~CMainPageDlg()
{

}

// 函数 CMainPageDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CMainPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainPageDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(ID_MAINPAGEDLG_BT_NEW,&CMainPageDlg::OnBnClickedBtNew)
	ON_BN_CLICKED(ID_MAINPAGEDLG_BT_OPEN,&CMainPageDlg::OnBnClickedBtOpen)
END_MESSAGE_MAP()

// 函数 CMainPageDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CMainPageDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect; 
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	int iTempInt1 = 336 * m_dHoriRatio;

	memDc.FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),RGB(0XE6,0XF4,0XF5));

	DrawRoundRectangleNew(&memDc,16 * m_dHoriRatio,12 * m_dVertRatio,1376 * m_dHoriRatio,rect.Height() - 12 * m_dVertRatio - 8 * m_dVertRatio,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	DrawRoundRectangleNew(&memDc,32 * m_dHoriRatio,28 * m_dVertRatio,m_iSwitchBtBkW,m_iSwitchBtBkH,8,8,8,8,TRUE,Color(0XE7,0XE7,0XE7),1,TRUE,COLOR_SOFT_THEME,1);

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CMainPageDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CMainPageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}
	return;
}

// 函数 CMainPageDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CMainPageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iSwitchBtBkH *= m_dVertRatio;
	if(0 != (m_iSwitchBtBkH % 2))
	{
		m_iSwitchBtBkH += 1;
	}
	m_iSwitchBtH *= m_dVertRatio;
	if(0 != (m_iSwitchBtH % 2))
	{
		m_iSwitchBtH -= 1;
	}

	m_iSwitchBtBkW *= m_dHoriRatio;
	if(0 != (m_iSwitchBtBkW % 2))
	{
		m_iSwitchBtBkW += 1;
	}
	m_iSwitchBtW *= m_dHoriRatio;
	if(0 != (m_iSwitchBtW % 2))
	{
		m_iSwitchBtW -= 1;
	}

	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

// 函数 CMainPageDlg::OnBnClickedBtNew
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPageSelected。
void CMainPageDlg::OnBnClickedBtNew()
{
	SetPageSelected(EHEDM_FIGURE);
}

// 函数 CMainPageDlg::OnBnClickedBtOpen
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPageSelected。
void CMainPageDlg::OnBnClickedBtOpen()
{
	SetPageSelected(EHEDM_LIST);
}

// 函数 CMainPageDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitDlg、InitSonDlg、CreateCtrl、InitCtrl、SetCtrlPos、ShowCtrl。
BOOL CMainPageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitDlg();
	InitSonDlg();
	CreateCtrl();
	m_bCtrlCreated = TRUE;
	InitCtrl();
	SetCtrlPos();
	ShowCtrl();

	SetPageSelected(EHEDM_FIGURE);

	return TRUE;
}

// 函数 CMainPageDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMainPageDlg::InitDlg()
{

}

// 函数 CMainPageDlg::InitSonDlg
// 作用：初始化InitSonDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMainPageDlg::InitSonDlg()
{
	
}

// 函数 CMainPageDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateLst、CreateSamPlateDlg。
void CMainPageDlg::CreateCtrl()
{
	CreateBt();
	CreateLst();
	CreateSamPlateDlg();
}

// 函数 CMainPageDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CMainPageDlg::CreateBt()
{
	m_btNew.Create(_T("新建"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_MAINPAGEDLG_BT_NEW);
	m_btOpen.Create(_T("打开"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_MAINPAGEDLG_BT_OPEN);
}

// 函数 CMainPageDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMainPageDlg::CreateLst()
{
	
}

// 函数 CMainPageDlg::CreateSamPlateDlg
// 作用：创建或加入CreateSamPlateDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMainPageDlg::CreateSamPlateDlg()
{
	
}

// 函数 CMainPageDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitLst、InitSamPlateDlg。
void CMainPageDlg::InitCtrl()
{
	InitBt();
	InitLst();
	InitSamPlateDlg();
}

// 函数 CMainPageDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetRoundRectParam、SetEdgeColor、Color、SetBkColor、SetTextColor、RGB。
void CMainPageDlg::InitBt()
{
	int iFontH = 16 * CFontSet::m_dTxRatio;

	m_btNew.SetRoundRectParam(TRUE,CLR_SOFT_THEME,FALSE);
	m_btNew.SetEdgeColor(COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XE7,0XE7,0XE7),Color(0XE7,0XE7,0XE7));
	m_btNew.SetBkColor(COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF));
	m_btNew.SetTextColor(RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),CLR_2LEVEL_THEME,CLR_2LEVEL_THEME);
	m_btNew.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	
	m_btOpen.SetRoundRectParam(TRUE,CLR_SOFT_THEME,FALSE);
	m_btOpen.SetEdgeColor(COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XE7,0XE7,0XE7),Color(0XE7,0XE7,0XE7));
	m_btOpen.SetBkColor(COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF));
	m_btOpen.SetTextColor(RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),CLR_2LEVEL_THEME,CLR_2LEVEL_THEME);
	m_btOpen.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CMainPageDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMainPageDlg::InitLst()
{
	
}

// 函数 CMainPageDlg::InitSamPlateDlg
// 作用：初始化InitSamPlateDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMainPageDlg::InitSamPlateDlg()
{
	
}

// 函数 CMainPageDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、SetWindowPos。
void CMainPageDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	int iTempInt3 = (m_iSwitchBtBkW - m_iSwitchBtW * 2) / 2;;
	int iXStart = 32 * m_dHoriRatio + iTempInt3;
	int iYStart = 28 * m_dVertRatio + (m_iSwitchBtBkH - m_iSwitchBtH) / 2;

	m_btNew.SetWindowPos(this,iXStart,iYStart,m_iSwitchBtW,m_iSwitchBtH,SWP_NOZORDER);
	m_btOpen.SetWindowPos(this,iXStart + m_iSwitchBtW,iYStart,m_iSwitchBtW,m_iSwitchBtH,SWP_NOZORDER);
}

// 函数 CMainPageDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CMainPageDlg::ShowCtrl()
{
	//m_btNew.ShowWindow(SW_SHOW);
	//m_btOpen.ShowWindow(SW_SHOW);
}

// 函数 CMainPageDlg::SetPageSelected
// 作用：设置SetPageSelected。
// 参数：eExpDisplayMode。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMainPageDlg::SetPageSelected(EHISTORYEXPDISPALYMODE eExpDisplayMode)
{
	if(EHEDM_FIGURE == eExpDisplayMode)
	{
		
	}
	else if(EHEDM_LIST == eExpDisplayMode)
	{
		
	}

	return;
}

