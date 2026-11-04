// 【交接】 GeneralPcr\BaseSetDlg.cpp
// 作用：BaseSetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CBaseSetDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、END_MESSAGE_MAP。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BaseSetDlg.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"

// CBaseSetDlg dialog
IMPLEMENT_DYNAMIC(CBaseSetDlg, CDialogEx)

// 函数 CBaseSetDlg::CBaseSetDlg
// 作用：执行CBaseSetDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CBaseSetDlg::CBaseSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBaseSetDlg::IDD, pParent)
{
	m_bCtrlCreated = FALSE;
}

// 函数 CBaseSetDlg::~CBaseSetDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CBaseSetDlg::~CBaseSetDlg()
{
}

// 函数 CBaseSetDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CBaseSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBaseSetDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// 函数 CBaseSetDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CBaseSetDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitMap);

	memDC.FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	Node<CRect>* pNodeRst = m_rcManage.m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDC,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}
	
	memDC.SelectObject(pOldBitmap);
	bitMap.DeleteObject();
	memDC.DeleteDC();

	return TRUE;
}

// 函数 CBaseSetDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CBaseSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}

	return;
}

// 函数 CBaseSetDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitSonDlg、CreateCtrl、InitCtrl、SetCtrlPos、ShowCtrl。
BOOL CBaseSetDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitSonDlg();
	CreateCtrl();
	m_bCtrlCreated = TRUE;
	InitCtrl();
	SetCtrlPos();
	ShowCtrl();

	return TRUE;
}

// 函数 CBaseSetDlg::InitSonDlg
// 作用：初始化InitSonDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CBaseSetDlg::InitSonDlg()
{
	m_instrumentInfoDlg.Create(IDD_MIDDLEDLG,this);
	m_expeInfoDlg.Create(IDD_MIDDLEDLG,this);
}

// 函数 CBaseSetDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateSt。
void CBaseSetDlg::CreateCtrl()
{
	CreateSt();
}

// 函数 CBaseSetDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CBaseSetDlg::CreateSt()
{
	
}

// 函数 CBaseSetDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitSt。
void CBaseSetDlg::InitCtrl()
{
	InitSt();
}

// 函数 CBaseSetDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CBaseSetDlg::InitSt()
{
	
}

// 函数 CBaseSetDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、Height、AddRectToDelete、SetWindowPos、CalcRectResult。
void CBaseSetDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	int iHeight = rect.Height() - 12 * m_dVertRatio - 10 * m_dVertRatio;

	m_rcManage.AddRectToDelete(16 * m_dHoriRatio,12 * m_dVertRatio,868 * m_dHoriRatio,iHeight);
	m_expeInfoDlg.SetWindowPos(this,16 * m_dHoriRatio,12 * m_dVertRatio,868 * m_dHoriRatio,iHeight,SWP_NOZORDER);

	m_rcManage.AddRectToDelete(900 * m_dHoriRatio,12 * m_dVertRatio,868 * m_dHoriRatio,iHeight);
	m_instrumentInfoDlg.SetWindowPos(this,900 * m_dHoriRatio,12 * m_dVertRatio,868 * m_dHoriRatio,iHeight,SWP_NOZORDER);

	m_rcManage.CalcRectResult();
}

// 函数 CBaseSetDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CBaseSetDlg::ShowCtrl()
{
	m_instrumentInfoDlg.ShowWindow(SW_SHOW);
	m_expeInfoDlg.ShowWindow(SW_SHOW);
}

// 函数 CBaseSetDlg::GetBaseInfo
// 作用：读取GetBaseInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：函数里会调用 GetExperiInfo、GetInstruInfo。
void CBaseSetDlg::GetBaseInfo(CExperimentInfo& info)
{
	m_expeInfoDlg.GetExperiInfo(info);
	m_instrumentInfoDlg.GetInstruInfo(info);

	return;
}

// 函数 CBaseSetDlg::SetBaseInfo
// 作用：设置SetBaseInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：函数里会调用 SetExperiInfo、SetInstruInfo。
void CBaseSetDlg::SetBaseInfo(CExperimentInfo& info)
{
	m_expeInfoDlg.SetExperiInfo(info);
	m_instrumentInfoDlg.SetInstruInfo(info);
	return;
}

// 函数 CBaseSetDlg::SetCtrlEnableState
// 作用：设置SetCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CBaseSetDlg::SetCtrlEnableState(BOOL bEnabled)
{
	m_instrumentInfoDlg.SetCtrlEnableState(bEnabled);
	m_expeInfoDlg.SetCtrlEnableState(bEnabled);
}

// 函数 CBaseSetDlg::ClearPage
// 作用：更新或清除ClearPage。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CBaseSetDlg::ClearPage()
{
	m_instrumentInfoDlg.ClearPage();
	m_expeInfoDlg.ClearPage();
}

// 函数 CBaseSetDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CBaseSetDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	m_eExpEditMode = eExpEditMode;

	m_expeInfoDlg.SetEditMode(m_eExpEditMode);
	m_instrumentInfoDlg.SetEditMode(m_eExpEditMode);
	return 0;
}

// 函数 CBaseSetDlg::FileOpened
// 作用：执行FileOpened。
// 参数：pExpData：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 SetBaseInfo、GetExperimentInfo。
void CBaseSetDlg::FileOpened(CExperimentData* pExpData)
{
	if(NULL == pExpData)
	{
		return;
	}

	SetBaseInfo(*pExpData->GetExperimentInfo());
	return;
}

// 函数 CBaseSetDlg::GetExpName
// 作用：读取GetExpName。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CBaseSetDlg::GetExpName()
{
	return m_expeInfoDlg.GetExpName();
}

// 函数 CBaseSetDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CBaseSetDlg::RefreshLanguageDisplay()
{
	m_expeInfoDlg.RefreshLanguageDisplay();
	m_instrumentInfoDlg.RefreshLanguageDisplay();

	return 0;
}


// 函数 CBaseSetDlg::SetSelectedInstrument
// 作用：设置SetSelectedInstrument。
// 参数：strModel：字符串；strSN：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CBaseSetDlg::SetSelectedInstrument(CString strModel, CString strSN)
{
	m_instrumentInfoDlg.SetSelectedInstrument(strModel, strSN);
}

// 函数 CBaseSetDlg::ReshowInstrumentList
// 作用：执行ReshowInstrumentList。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CBaseSetDlg::ReshowInstrumentList()
{
	m_instrumentInfoDlg.ReshowInstrumentList();
}
