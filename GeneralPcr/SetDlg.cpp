// 【交接】 GeneralPcr\SetDlg.cpp
// 作用：SetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CSetDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、ON_BN_CLICKED。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "SetDlg.h"
#include "GeneralPcrDlg.h"
#include "GeneralPcr.h"

// CSetDlg dialog
IMPLEMENT_DYNAMIC(CSetDlg, CDialogEx)

// 函数 CSetDlg::CSetDlg
// 作用：执行CSetDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetDlg::IDD, pParent)
{
	m_iFunBtnHeight = 40;
	m_pCurSelSwt = NULL;
	m_pCurSelDlg = NULL;
	m_bCtrlCreated = FALSE;
}

// 函数 CSetDlg::~CSetDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSetDlg::~CSetDlg()
{

}

// 函数 CSetDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()

	ON_BN_CLICKED(ID_BOTTOMFUNCDLG_BT_ADD,OnBnClickedAdd)	
	ON_BN_CLICKED(ID_BOTTOMFUNCDLG_BT_EDIT,OnBnClickedEdit)	
	ON_BN_CLICKED(ID_BOTTOMFUNCDLG_BT_DELETE,OnBnClickedDelete) 

	ON_BN_CLICKED(ID_SETDLG_SWTBT_LISSET,OnBnClickedSwtLisSet)
	ON_BN_CLICKED(ID_SETDLG_SWTBT_USERMANAGESET,OnBnClickedSwtUserManageSet)
	ON_BN_CLICKED(ID_SETDLG_SWTBT_PS96SET,OnBnClickedSwtPs96Set)
	ON_BN_CLICKED(ID_SETDLG_SWTBT_SYSTEMSET,OnBnClickedSwtSystemSet)
END_MESSAGE_MAP()

// 函数 CSetDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、FillSolidRect、Width、Height、int、RGB。
BOOL CSetDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);

	CRect rectFun = rect;
	rectFun.bottom = rectFun.top + int(m_iFunBtnHeight*m_dVertRatio);
	pDC->FillSolidRect(rectFun, RGB(255, 255, 255));

	int iStartY = int((12+m_iFunBtnHeight) * m_dVertRatio);
	DrawRoundRectangleNew(pDC,0,iStartY,int(136 * m_dHoriRatio),rect.Height() - iStartY,0,16,0,0,FALSE,Color(0XFF,0XFF,0XFF),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	return TRUE;
}

// 函数 CSetDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 CreateBt、InitDlg、IntFunBtn、InitBt、SetCtrlPos、SetCtrlText。
BOOL CSetDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	CreateBt();
	InitDlg();
	IntFunBtn();
	InitBt();
	m_bCtrlCreated = TRUE;
	SetCtrlPos();

	SetCtrlText();
	SetPageSelected(PS96SETDLG);

	ShowCtrl();

	return TRUE;
}

// 函数 CSetDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CSetDlg::CreateBt()
{
	m_btnAdd.Create(_T("新增"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0 ,0, 0, 0),this,ID_BOTTOMFUNCDLG_BT_ADD);
	m_btnEdit.Create(_T("编辑"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0 ,0, 0, 0),this,ID_BOTTOMFUNCDLG_BT_EDIT);
	m_btnDelete.Create(_T("删除"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0 ,0, 0, 0),this,ID_BOTTOMFUNCDLG_BT_DELETE);

	m_swtLisSet.Create(_T("LIS设置"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_SETDLG_SWTBT_LISSET);
	m_swtUserManageSet.Create(_T("用户管理"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_SETDLG_SWTBT_USERMANAGESET);
	m_swtInstru1Set.Create(_T("PS96 设置"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_SETDLG_SWTBT_PS96SET);
	m_swtSysSet.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_SETDLG_SWTBT_SYSTEMSET);
}

// 函数 CSetDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont、Create。
void CSetDlg::InitDlg()
{
	SetTextClr1(RGB(86,86,86));
	SetMyFont(m_stTxFont,14,FW_NORMAL,TYPE_PIXEL);

	m_lisSetDlg.Create(IDD_MIDDLEDLG,this);
	m_userManageSetDlg.Create(IDD_MIDDLEDLG,this);
	m_ps96SetDlg.Create(IDD_MIDDLEDLG,this);
}


// 函数 CSetDlg::IntFunBtn
// 作用：执行IntFunBtn。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPngBkPic、_T、SetMyFont、SetWordStyle。
void CSetDlg::IntFunBtn()
{
	int iFontH = 16 * m_dTxRatio;

	int iTempInt1 = 16 * m_dHoriRatio;
	int iTempInt2 = 10 * m_dHoriRatio;

	m_btnAdd.SetPngBkPic(_T(".\\BkPic\\btnew.png"),2,iTempInt1,0,iTempInt2);
	m_btnAdd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btnAdd.SetWordStyle(DT_LEFT | DT_SINGLELINE | DT_VCENTER);

	m_btnEdit.SetPngBkPic(_T(".\\BkPic\\btedit.png"),2,iTempInt1,0,iTempInt2);
	m_btnEdit.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btnEdit.SetWordStyle(DT_LEFT | DT_SINGLELINE | DT_VCENTER);

	m_btnDelete.SetPngBkPic(_T(".\\BkPic\\btdelete.png"),2,iTempInt1,0,iTempInt2);
	m_btnDelete.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btnDelete.SetWordStyle(DT_LEFT | DT_SINGLELINE | DT_VCENTER);
}

// 函数 CSetDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、Rect、CRect、Color、_T、SetMyFont。
void CSetDlg::InitBt()
{
	int iFontH = 18 * m_dTxRatio;

	CIconBtInfo iconBtInfo;

	if(theApp.GetBeEnglish())
	{
		iconBtInfo.m_rcIcon = Rect(10 * m_dHoriRatio,18 * m_dVertRatio,24 * m_dHoriRatio,24 * m_dVertRatio);
		iconBtInfo.m_rcText = CRect(35 * m_dHoriRatio,16 * m_dVertRatio,135 * m_dHoriRatio,43 * m_dVertRatio);
	}
	else
	{
		iconBtInfo.m_rcIcon = Rect(12 * m_dHoriRatio,18 * m_dVertRatio,24 * m_dHoriRatio,24 * m_dVertRatio);
		iconBtInfo.m_rcText = CRect(40 * m_dHoriRatio,16 * m_dVertRatio,132 * m_dHoriRatio,43 * m_dVertRatio);
	}

	iconBtInfo.m_bRoundRectBk = FALSE;
	iconBtInfo.m_iSonIconNum = 2;
	iconBtInfo.m_bSonIconPosOrder = FALSE;
	iconBtInfo.m_clrNormal = Color(0XFF,0XFF,0XFF);
	iconBtInfo.m_clrHover = Color(0XFF,0XFF,0XFF);

	iconBtInfo.m_clrSelected = COLOR_SOFT_THEME;
	iconBtInfo.m_clrDisabled = COLOR_SOFT_THEME;

	iconBtInfo.m_strIconPath = _T(".\\BkPic\\SystemSet.png");
	m_swtInstru1Set.SetMyFont(m_stTxFont,iFontH);
	m_swtInstru1Set.SetIconBtInfo(iconBtInfo);
	m_swtInstru1Set.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF));

	iconBtInfo.m_strIconPath = _T(".\\BkPic\\UserManage.png");
	m_swtUserManageSet.SetMyFont(m_stTxFont,iFontH);
	m_swtUserManageSet.SetIconBtInfo(iconBtInfo);
	m_swtUserManageSet.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF));

	iconBtInfo.m_strIconPath = _T(".\\BkPic\\system.png");
	m_swtSysSet.SetMyFont(m_stTxFont,iFontH);
	m_swtSysSet.SetIconBtInfo(iconBtInfo);
	m_swtSysSet.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF));

	m_swtLisSet.SetMyFont(m_stTxFont,iFontH);
	m_swtLisSet.SetIconBtInfo(iconBtInfo);
	m_swtLisSet.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF));

	return;
}

// 函数 CSetDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、SetWindowPos、int、MoveWindow。
void CSetDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	int iTempInt1 = 24 * m_dVertRatio;
	int iTempInt2 = 7 * m_dVertRatio;
	int iTempInt3 = 72 * m_dHoriRatio;

	m_btnAdd.SetWindowPos(this, int(18 * m_dHoriRatio), iTempInt2, iTempInt3, iTempInt1,SWP_NOZORDER);
	m_btnEdit.SetWindowPos(this, int(118 * m_dHoriRatio),iTempInt2, iTempInt3,iTempInt1,SWP_NOZORDER);
	m_btnDelete.SetWindowPos(this, int(218 * m_dHoriRatio),iTempInt2, iTempInt3,iTempInt1,SWP_NOZORDER);

	int startX = 0 * m_dHoriRatio;
	int startY = int((28+m_iFunBtnHeight) * m_dVertRatio);
	int swtWidth = 136 * m_dHoriRatio;
	int iHeight = 60 * m_dVertRatio;
	int iInterval = 26 * m_dVertRatio;
	int iTempH = iHeight + iInterval;

	m_swtInstru1Set.MoveWindow(startX,startY,swtWidth,iHeight,FALSE);
	startY += iTempH;
	m_swtUserManageSet.MoveWindow(startX,startY,swtWidth,iHeight,FALSE);
	startY += iTempH;
	m_swtSysSet.MoveWindow(startX,startY,swtWidth,iHeight,FALSE);

	startY += iTempH;
	m_swtLisSet.MoveWindow(startX,startY,swtWidth,iHeight,FALSE);
	
	int dlgH = 882 * m_dVertRatio;
	m_lisSetDlg.MoveWindow(int(152 * m_dHoriRatio),int((12+m_iFunBtnHeight) * m_dVertRatio),int(1752 * m_dHoriRatio), dlgH,FALSE);
	m_userManageSetDlg.MoveWindow(int(152 * m_dHoriRatio),int((12+m_iFunBtnHeight) * m_dVertRatio),int(1752 * m_dHoriRatio),dlgH,FALSE);
	m_ps96SetDlg.MoveWindow(int(152 * m_dHoriRatio),int((12+m_iFunBtnHeight) * m_dVertRatio),int(1752 * m_dHoriRatio),dlgH,FALSE);

	return;
}

// 函数 CSetDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CSetDlg::ShowCtrl()
{
	m_btnAdd.ShowWindow(SW_SHOW);
	m_btnEdit.ShowWindow(SW_SHOW);
	m_btnDelete.ShowWindow(SW_SHOW);

	m_swtInstru1Set.ShowWindow(SW_SHOW);
	m_swtUserManageSet.ShowWindow(SW_SHOW);
	//m_swtSysSet.ShowWindow(SW_SHOW);
	//m_swtLisSet.ShowWindow(SW_SHOW);

	return;
}

// 函数 CSetDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowText、GetText。
void CSetDlg::SetCtrlText()
{
	m_btnAdd.SetWindowText(theApp.m_pLangInfo->GetText(372));
	m_btnEdit.SetWindowText(theApp.m_pLangInfo->GetText(353));
	m_btnDelete.SetWindowText(theApp.m_pLangInfo->GetText(172));

	m_swtInstru1Set.SetWindowText(theApp.m_pLangInfo->GetText(205));
	m_swtUserManageSet.SetWindowText(theApp.m_pLangInfo->GetText(349));
	m_swtSysSet.SetWindowText(theApp.m_pLangInfo->GetText(431));
	return;
}

// 函数 CSetDlg::SetPageSelected
// 作用：设置SetPageSelected。
// 参数：eSetPageType。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、ShowWindow、EnableWindow、UpdateFuncBtMode。
void CSetDlg::SetPageSelected(SETPAGETYPE eSetPageType)
{
	if(LISSETDLG == eSetPageType)
	{
		if(NULL != m_pCurSelDlg->GetSafeHwnd())
		{
			m_pCurSelDlg->ShowWindow(SW_HIDE);
		}
		if(NULL != m_pCurSelSwt->GetSafeHwnd())
		{
			m_pCurSelSwt->EnableWindow(TRUE);
		}
		m_swtLisSet.EnableWindow(FALSE);
		m_lisSetDlg.ShowWindow(SW_SHOW);
		m_pCurSelDlg = &m_lisSetDlg;
		m_pCurSelSwt = &m_swtLisSet;
	}
	else if(USERMANAGESETDLG == eSetPageType)
	{
		if(NULL != m_pCurSelDlg->GetSafeHwnd())
		{
			m_pCurSelDlg->ShowWindow(SW_HIDE);
		}
		if(NULL != m_pCurSelSwt->GetSafeHwnd())
		{
			m_pCurSelSwt->EnableWindow(TRUE);
		}
		m_swtUserManageSet.EnableWindow(FALSE);
		m_userManageSetDlg.ShowWindow(SW_SHOW);
		m_pCurSelDlg = &m_userManageSetDlg;
		m_pCurSelSwt = &m_swtUserManageSet;
	}
	else if(PS96SETDLG == eSetPageType)
	{
		if(NULL != m_pCurSelDlg->GetSafeHwnd())
		{
			m_pCurSelDlg->ShowWindow(SW_HIDE);
		}
		if(NULL != m_pCurSelSwt->GetSafeHwnd())
		{
			m_pCurSelSwt->EnableWindow(TRUE);
		}
		m_swtInstru1Set.EnableWindow(FALSE);
		m_ps96SetDlg.ShowWindow(SW_SHOW);
		m_pCurSelDlg = &m_ps96SetDlg;
		m_pCurSelSwt = &m_swtInstru1Set;
	}

	UpdateFuncBtMode();

	return;
}

// 函数 CSetDlg::UpdateFuncBtMode
// 作用：更新或清除UpdateFuncBtMode。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、IsWindowVisible、ShowWindow。
void CSetDlg::UpdateFuncBtMode()
{
	CGeneralPcrDlg* pMainDlg = (CGeneralPcrDlg*)theApp.m_pMainWnd;

	if(NULL != m_ps96SetDlg.GetSafeHwnd() && m_ps96SetDlg.IsWindowVisible())
	{
		m_btnAdd.ShowWindow(SW_HIDE);
		m_btnEdit.ShowWindow(SW_HIDE);
		m_btnDelete.ShowWindow(SW_HIDE);
	}
	else if(NULL != m_userManageSetDlg.GetSafeHwnd() && m_userManageSetDlg.IsWindowVisible())
	{
		m_btnAdd.ShowWindow(SW_SHOW);
		m_btnEdit.ShowWindow(SW_SHOW);
		m_btnDelete.ShowWindow(SW_SHOW);
	}
}

// 函数 CSetDlg::OnBnClickedSwtLisSet
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPageSelected。
void CSetDlg::OnBnClickedSwtLisSet()
{
	SetPageSelected(LISSETDLG);
}

// 函数 CSetDlg::OnBnClickedSwtUserManageSet
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPageSelected。
void CSetDlg::OnBnClickedSwtUserManageSet()
{
	SetPageSelected(USERMANAGESETDLG);
}

// 函数 CSetDlg::OnBnClickedSwtPs96Set
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPageSelected。
void CSetDlg::OnBnClickedSwtPs96Set()
{
	SetPageSelected(PS96SETDLG);
}

// 函数 CSetDlg::OnBnClickedSwtSystemSet
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPageSelected。
void CSetDlg::OnBnClickedSwtSystemSet()
{
	SetPageSelected(SYSTEMSETDLG);
}

// 函数 CSetDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CSetDlg::OnSize(UINT nType, int cx, int cy)
{
	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}

	__super::OnSize(nType, cx, cy);
}	

// 函数 CSetDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetWindowText、GetText、SetMyFont。
int CSetDlg::RefreshLanguageDisplay()
{
	m_btnAdd.SetWindowText(theApp.m_pLangInfo->GetText(372));
	m_btnEdit.SetWindowText(theApp.m_pLangInfo->GetText(353));
	m_btnDelete.SetWindowText(theApp.m_pLangInfo->GetText(172));

	m_swtInstru1Set.SetMyFont(m_stTxFont);
	m_swtInstru1Set.SetWindowText(theApp.m_pLangInfo->GetText(205));

	m_swtUserManageSet.SetMyFont(m_stTxFont);
	m_swtUserManageSet.SetWindowText(theApp.m_pLangInfo->GetText(349));

	m_swtSysSet.SetMyFont(m_stTxFont);
	m_swtSysSet.SetWindowText(theApp.m_pLangInfo->GetText(431));

	m_ps96SetDlg.RefreshLanguageDisplay();
	m_userManageSetDlg.RefreshLanguageDisplay();

	return 0;
}

// 函数 CSetDlg::OnBnClickedAdd
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindowVisible、AddUser。
void CSetDlg::OnBnClickedAdd()
{
	if(m_userManageSetDlg.IsWindowVisible())
	{
		m_userManageSetDlg.AddUser();
	}
}

// 函数 CSetDlg::OnBnClickedEdit
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindowVisible、EditUser。
void CSetDlg::OnBnClickedEdit()
{
	if(m_userManageSetDlg.IsWindowVisible())
	{
		m_userManageSetDlg.EditUser();
	}
}

// 函数 CSetDlg::OnBnClickedDelete
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 IsWindowVisible、DeleteUser。
void CSetDlg::OnBnClickedDelete()
{
	if(m_userManageSetDlg.IsWindowVisible())
	{
		m_userManageSetDlg.DeleteUser();
	}
}
