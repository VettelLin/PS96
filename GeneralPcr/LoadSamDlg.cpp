// 【交接】 GeneralPcr\LoadSamDlg.cpp
// 作用：LoadSamDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CLoadSamDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、ON_BN_CLICKED。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "LoadSamDlg.h"
#include "GeneralPcrDlg.h"
#include "GeneralPcr.h"
#include "Ps96SimpleDlg.h"

// CLoadSamDlg dialog
IMPLEMENT_DYNAMIC(CLoadSamDlg, CDialogEx)

// 函数 CLoadSamDlg::CLoadSamDlg
// 作用：执行CLoadSamDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLoadSamDlg::CLoadSamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoadSamDlg::IDD, pParent)
{
	m_pParent = NULL;
	if(NULL != pParent)
	{
		m_pParent = (CPs96SimpleDlg*)pParent;
	}
	m_bCtrlCreated = FALSE;
	m_pExpData = NULL;
}

// 函数 CLoadSamDlg::~CLoadSamDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLoadSamDlg::~CLoadSamDlg()
{

}

// 函数 CLoadSamDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CLoadSamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoadSamDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_LOADSAMDLG_BT_LOAD,OnBnClickedLoadId)
END_MESSAGE_MAP()

// 函数 CLoadSamDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CLoadSamDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);
	DrawRoundRectangleNew(&memDc,0,0,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	
	memDc.SetBkMode(TRANSPARENT);
	memDc.SetTextColor(m_txClr1);
	CFont* pOldFont = memDc.SelectObject(&m_fontSet);

	CRect rcLegend;
	rcLegend.left = int(16 * m_dHoriRatio);
//	rcLegend.right = rcLegend.left + 966 * m_dHoriRatio;
	rcLegend.right = rect.right - int(16 * m_dHoriRatio);
	//rcLegend.top = 611 * m_dVertRatio;
	//rcLegend.bottom = rcLegend.top + 35 * m_dVertRatio;
	rcLegend.bottom = rect.bottom;
	rcLegend.top = rcLegend.bottom - int(35 * m_dVertRatio);
	DrawLegend(&memDc,&rcLegend,m_segLgdInfo);

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

	return TRUE;
}

// 函数 CLoadSamDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CLoadSamDlg::OnSize(UINT nType, int cx, int cy)
{
	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}

	__super::OnSize(nType, cx, cy);
}	

// 函数 CLoadSamDlg::OnBnClickedLoadId
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ImportId。
void CLoadSamDlg::OnBnClickedLoadId()
{
	ImportId();
	return;
}

// 函数 CLoadSamDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitSegLegend、CreateCtrl、InitDlg、InitCtrl、SetCtrlPos、SetCtrlText。
BOOL CLoadSamDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();
	InitSegLegend();
	CreateCtrl();
	InitDlg();
	InitCtrl();
	m_bCtrlCreated = TRUE;
	SetCtrlPos();

	SetCtrlText();

	ShowCtrl();

	return TRUE;
}

// 函数 CLoadSamDlg::InitSegLegend
// 作用：初始化InitSegLegend。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Color、GetText、AddSingleLegendInfo、GetBeEnglish、SetMyFont、SetTextClr1。
void CLoadSamDlg::InitSegLegend()
{
	CSingleLgdInfo singleLgdInfo;

	singleLgdInfo.m_clrFill = Color(0X9B,0X51,0XE0);
	singleLgdInfo.m_strTx = theApp.m_pLangInfo->GetText(211);
	m_segLgdInfo.AddSingleLegendInfo(singleLgdInfo);

	singleLgdInfo.m_clrFill = Color(0X21,0X96,0X53);
	singleLgdInfo.m_strTx = theApp.m_pLangInfo->GetText(212);
	m_segLgdInfo.AddSingleLegendInfo(singleLgdInfo);

	singleLgdInfo.m_clrFill = Color(0XEB,0X57,0X57);
	singleLgdInfo.m_strTx = theApp.m_pLangInfo->GetText(215);
	m_segLgdInfo.AddSingleLegendInfo(singleLgdInfo);

	singleLgdInfo.m_clrFill = Color(0X2F,0X80,0XED);
	singleLgdInfo.m_strTx = theApp.m_pLangInfo->GetText(214);
	m_segLgdInfo.AddSingleLegendInfo(singleLgdInfo);

	singleLgdInfo.m_clrFill = Color(0XF2,0X99,0X4A);
	singleLgdInfo.m_strTx = theApp.m_pLangInfo->GetText(213);
	m_segLgdInfo.AddSingleLegendInfo(singleLgdInfo);

#ifdef CAN_YOUNG
	singleLgdInfo.m_clrFill = Color(0,0X70,0XC0);
	singleLgdInfo.m_strTx = theApp.m_pLangInfo->GetText(457);
	m_segLgdInfo.AddSingleLegendInfo(singleLgdInfo);
#endif

	m_segLgdInfo.m_iLeftIndent = 41 * m_dHoriRatio; 
	m_segLgdInfo.m_iRoundRadius = 6 * m_dHoriRatio; 
	m_segLgdInfo.m_iInrIconToTx = 8 * m_dHoriRatio; 
	m_segLgdInfo.m_iInrTxToIcon = 20 * m_dHoriRatio; 

	int iFontH = 17 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		m_segLgdInfo.m_iOneCharW = 14 * m_dHoriRatio;
	}
	else
	{
		m_segLgdInfo.m_iOneCharW = 20 * m_dHoriRatio;
	}

	m_segLgdInfo.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_segLgdInfo.SetTextClr1(RGB(0X39,0X45,0X65));
}

// 函数 CLoadSamDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateCkbt、CreateSt、CreateEd、CreateLst、CreateSamPlateDlg。
void CLoadSamDlg::CreateCtrl()
{
	CreateBt();
	CreateCkbt();
	CreateSt();
	CreateEd();
	CreateLst();
	CreateSamPlateDlg();

	m_segDlg.Create(IDD_MIDDLEDLG,this);
}

// 函数 CLoadSamDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CLoadSamDlg::CreateBt()
{
	m_btLoad.Create(_T("加载"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_LOADSAMDLG_BT_LOAD);
	m_swtBtSegMonitor.Create(_T("运行程序"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_RUNMONITORDLG_RUNSEGMENT);
}

// 函数 CLoadSamDlg::CreateCkbt
// 作用：创建或加入CreateCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::CreateCkbt()
{
	

}

// 函数 CLoadSamDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::CreateSt()
{
	
}

// 函数 CLoadSamDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::CreateEd()
{
	
}

// 函数 CLoadSamDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::CreateLst()
{
	
}

// 函数 CLoadSamDlg::CreateSamPlateDlg
// 作用：创建或加入CreateSamPlateDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CLoadSamDlg::CreateSamPlateDlg()
{
	m_samPlateDlg.Create(IDD_MIDDLEDLG,this);
}

// 函数 CLoadSamDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CLoadSamDlg::InitDlg()
{
	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,18 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CLoadSamDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCkbt、InitSt、InitEd、InitLst、InitSamPlateDlg。
void CLoadSamDlg::InitCtrl()
{
	InitBt();
	InitCkbt();
	InitSt();
	InitEd();
	InitLst();
	InitSamPlateDlg();
	InitSegment();
}

// 函数 CLoadSamDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitOneBt、Rect、CRect、Color、SetMyFont、SetIconBtInfo。
void CLoadSamDlg::InitBt()
{
	InitOneBt(&m_btLoad);
	//InitOneBt(&m_swtBtSegMonitor);

	CIconBtInfo iconBtInfo;
	iconBtInfo.m_bUseIcon = FALSE;
	iconBtInfo.m_rcIcon = Rect(18 * m_dHoriRatio,18 * m_dVertRatio,24 * m_dHoriRatio,24 * m_dVertRatio);
	iconBtInfo.m_rcText = CRect(2 * m_dHoriRatio,16 * m_dVertRatio,218 * m_dHoriRatio,43 * m_dVertRatio);
	iconBtInfo.m_bRoundRectBk = FALSE;
	iconBtInfo.m_iSonIconNum = 2;
	iconBtInfo.m_bSonIconPosOrder = FALSE;
	iconBtInfo.m_clrNormal = Color(0XFF,0XFF,0XFF);
	iconBtInfo.m_clrHover = Color(0XFF,0XFF,0XFF);
	iconBtInfo.m_clrSelected = COLOR_SOFT_THEME;
	iconBtInfo.m_clrDisabled = COLOR_SOFT_THEME;
	int iFontH = 26 * CFontSet::m_dTxRatio;

	m_swtBtSegMonitor.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_swtBtSegMonitor.SetIconBtInfo(iconBtInfo);
	m_swtBtSegMonitor.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF));
	m_swtBtSegMonitor.EnableWindow(FALSE);

	return;
}

// 函数 CLoadSamDlg::InitOneBt
// 作用：初始化InitOneBt。
// 参数：pBt：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBkColor、Color、SetEdgeColor。
void CLoadSamDlg::InitOneBt(CMyButton* pBt)
{
	if(NULL == pBt)
	{
		return;
	}

	int iFontH = 26 * CFontSet::m_dTxRatio;

	pBt->SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	pBt->SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
	pBt->SetBkColor(Color(0XF1,0XF4,0XF9),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF) , Color(0XFF,0XFF,0XFF));
	pBt->SetEdgeColor(Color(0XD8,0XD8,0XD8),Color(0XD8,0XD8,0XD8),Color(0XD8,0XD8,0XD8),Color(0XD8,0XD8,0XD8));
	pBt->SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));

	return;
}	

// 函数 CLoadSamDlg::InitCkbt
// 作用：初始化InitCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::InitCkbt()
{
	int iFontH = 18 * m_dTxRatio;

}

// 函数 CLoadSamDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::InitSt()
{
	
}

// 函数 CLoadSamDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::InitEd()
{
	int iFontH = 18 * m_dTxRatio;

}

// 函数 CLoadSamDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLoadSamDlg::InitLst()
{
	
}

// 函数 CLoadSamDlg::InitSamPlateDlg
// 作用：初始化InitSamPlateDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetRowHeaderWidth、SetColumnHeaderHeight、SetRowColNum、SetRectWidth、SetRectHeight、SetBkColor。
void CLoadSamDlg::InitSamPlateDlg()
{
	int iFontH = 16 * m_dTxRatio,iFontTitleH = 18 * m_dTxRatio;
	int iFontAbbrH = 20 * m_dTxRatio;

	m_samPlateDlg.SetRowHeaderWidth(36 * m_dHoriRatio);
	m_samPlateDlg.SetColumnHeaderHeight(36 * m_dVertRatio);
	
	m_samPlateDlg.SetRowColNum(8,12);
	m_samPlateDlg.SetRectWidth(70 * m_dHoriRatio);
	m_samPlateDlg.SetRectHeight(64 * m_dVertRatio);

	m_samPlateDlg.SetBkColor(RGB(0XE6,0XF4,0XF5));
	m_samPlateDlg.SetFourAngleBkColor(RGB(0XFF,0XFF,0XFF));
	m_samPlateDlg.SetMyFont(m_stTxFont,iFontH);
	m_samPlateDlg.SetMyHeaderFont(m_stTxFont,iFontTitleH);
	m_samPlateDlg.SetMyTitleFont(m_stTxFont,iFontTitleH,FW_SEMIBOLD);
	m_samPlateDlg.SetMyFontAbbr(m_stTxFont,iFontAbbrH);
	m_samPlateDlg.SetBeTellParentRowSelChange(TRUE);
	m_samPlateDlg.SetBeSingleSelect(TRUE);
	m_samPlateDlg.SetBeParentProcessDeleteKey(TRUE);

	m_samPlateDlg.SetBeShowBottomText(TRUE);
	m_samPlateDlg.SetSiteIdShowState(FALSE);
	m_samPlateDlg.SetLastChanBlockShowState(FALSE);

	return;
}

// 函数 CLoadSamDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、rcTemp、int、SetWindowPos、Width。
void CLoadSamDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	CRect rcTemp(16 * m_dHoriRatio,16 * m_dVertRatio,982 * m_dHoriRatio,611 * m_dVertRatio);
	if (rcTemp.bottom > rect.bottom - int(35*m_dVertRatio))
		rcTemp.bottom = rect.bottom - int(35*m_dVertRatio);

	m_samPlateDlg.SetWindowPos(this,rcTemp.left,rcTemp.top,rcTemp.Width(),rcTemp.Height(),SWP_NOZORDER);
	m_rcManage.AddRectToDelete(rcTemp);

	rcTemp.left = 1082 * m_dHoriRatio;
	rcTemp.right = 1322 * m_dHoriRatio;
	if(theApp.GetBeEnglish())
	{
		rcTemp.right = 1402 * m_dHoriRatio;
	}
	rcTemp.bottom = 76 * m_dVertRatio;
	m_btLoad.SetWindowPos(this,rcTemp.left,rcTemp.top,rcTemp.Width(),rcTemp.Height(),SWP_NOZORDER);
	m_rcManage.AddRectToDelete(rcTemp);

	int iStartY = rcTemp.top + rcTemp.Height() + 30*m_dVertRatio;
	rcTemp.left = 1082 * m_dHoriRatio;
	rcTemp.right = 1322 * m_dHoriRatio;
	if(theApp.GetBeEnglish())
	{
		rcTemp.right = 1402 * m_dHoriRatio;
	}
	rcTemp.bottom = iStartY + rcTemp.Height();
	rcTemp.top = iStartY;
	m_swtBtSegMonitor.SetWindowPos(this,rcTemp.left,rcTemp.top,rcTemp.Width(),rcTemp.Height(),SWP_NOZORDER);
	m_rcManage.AddRectToDelete(rcTemp);

	rcTemp.top = rcTemp.top + rcTemp.Height() + 20*m_dVertRatio;
	rcTemp.bottom = 646 * m_dVertRatio;
	rcTemp.right = rect.right - 20 * m_dHoriRatio;
	m_segDlg.SetWindowPos(this,rcTemp.left,rcTemp.top,rcTemp.Width(),rcTemp.Height(),SWP_NOZORDER);
	m_rcManage.AddRectToDelete(rcTemp);


	m_rcManage.CalcRectResult();

	return;
}

// 函数 CLoadSamDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CLoadSamDlg::ShowCtrl()
{
	m_samPlateDlg.ShowWindow(SW_SHOW);
	m_btLoad.ShowWindow(SW_SHOW);

	m_swtBtSegMonitor.ShowWindow(SW_SHOW);
	m_segDlg.ShowWindow(SW_SHOW);
}

// 函数 CLoadSamDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowText、GetText。
void CLoadSamDlg::SetCtrlText()
{
	m_btLoad.SetWindowText(theApp.m_pLangInfo->GetText(386));
	m_swtBtSegMonitor.SetWindowText(theApp.m_pLangInfo->GetText(465));
	return;
}

// 函数 CLoadSamDlg::RefreshExpEmbody
// 作用：更新或清除RefreshExpEmbody。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAllTubeInfoPtr、SetTubeInfo、ResetCurItemSubCycle、SetSegmentInfo、GetSegment、SetSegmentFullSelectState。
int CLoadSamDlg::RefreshExpEmbody()
{
	if(NULL == m_pExpData)
	{
		return -1;
	}

	vector<CTubeInfo*> vecTubeInfoPtr;
	m_pExpData->GetAllTubeInfoPtr(vecTubeInfoPtr);
	m_samPlateDlg.SetTubeInfo(vecTubeInfoPtr,TRUE);
	m_segDlg.ResetCurItemSubCycle();
	m_segDlg.SetSegmentInfo(m_pExpData->GetSegment(),TRUE);
	m_segDlg.SetSegmentFullSelectState(FALSE,TRUE);
	m_segDlg.CorrectSegmentName();

	return 0;
}

// 函数 CLoadSamDlg::ClearExpEmbody
// 作用：更新或清除ClearExpEmbody。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAllTubeInfo、Clear。
void CLoadSamDlg::ClearExpEmbody()
{
	m_samPlateDlg.DeleteAllTubeInfo();
	m_segDlg.Clear();

	return;
}

// 函数 CLoadSamDlg::ImportId
// 作用：读入ImportId。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAllSampleType、InputSampleSetInfo、GetAllTubeInfoPtr、SetTubeInfo、PopNormalTipInfo、GetText。
int CLoadSamDlg::ImportId()
{
	if(NULL == m_pExpData)
	{
		return -1;
	}

	vector<eSampleType> vecSamType;
	m_samPlateDlg.GetAllSampleType(vecSamType);
	int iRet = m_pExpData->InputSampleSetInfo(&vecSamType);
	if(0 == iRet)
	{
		//导入成功，更新孔板编辑、样本登记页面
		vector<CTubeInfo*> vecTubeInfoPtr;
		m_pExpData->GetAllTubeInfoPtr(vecTubeInfoPtr);
		m_samPlateDlg.SetTubeInfo(vecTubeInfoPtr,TRUE);
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(344));
	}
	else
	{
		if(-5 == iRet)
		{
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(345));
			return -2;
		}
		else if(-6 == iRet || -7 == iRet || -8 == iRet || -9 == iRet || -10 == iRet)
		{
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(346));
			return -3;
		}
		else if(-1 == iRet)
		{
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(347));
			return -2;
		}
	}

	return 0;
}

// 函数 CLoadSamDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 EnableWindow。
int CLoadSamDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	m_eExpEditMode = eExpEditMode;

	if(EEEM_RUNNING == m_eExpEditMode)
	{
		m_btLoad.EnableWindow(FALSE);
	}
	else if(EEEM_END == m_eExpEditMode)
	{
		m_btLoad.EnableWindow(TRUE);
	}

	return 0;
}

// 函数 CLoadSamDlg::SetExpDataPtr
// 作用：设置SetExpDataPtr。
// 参数：pExpData：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 SetSegmentInfo、GetSegment、ResetCurItemSubCycle、SetSegmentFullSelectState。
void CLoadSamDlg::SetExpDataPtr(CExperimentData* pExpData)
{
	m_pExpData = pExpData;
	m_segDlg.SetSegmentInfo(m_pExpData->GetSegment(),TRUE);
	//m_segDlg.ResetCurItemSubCycle();
	//m_segDlg.SetSegmentInfo(m_pExpData->GetSegment(),TRUE);
	//m_segDlg.SetSegmentFullSelectState(FALSE,TRUE);
	return;
}


// 函数 CLoadSamDlg::InitSegment
// 作用：初始化InitSegment。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、SetGradientInfoUseState、SetMyFont、SetBeMonitorFunc、SetScrollArrowWH、SetBeEditable。
void CLoadSamDlg::InitSegment()
{
	int iFontH = 22 * m_dTxRatio;
	if(theApp.m_pLangInfo->GetBeEnglish())
	{
		iFontH = 23 * m_dTxRatio;
	}

	m_segDlg.SetGradientInfoUseState(FALSE);
	m_segDlg.m_fontStepTag.SetMyFont(m_stTxFont,iFontH);
	m_segDlg.m_fontGeneral.SetMyFont(m_stTxFont,iFontH);
	m_segDlg.m_fontSegTag.SetMyFont(m_stTxFont,iFontH);
	m_segDlg.SetBeMonitorFunc(TRUE);

	int iTempInt1 = 34 * m_dVertRatio;
	m_segDlg.m_horiScroll.m_arrowWH = iTempInt1;
	m_segDlg.m_horiScroll.m_scrollH = iTempInt1;
	m_segDlg.m_vertScroll.m_arrowWH = iTempInt1;
	m_segDlg.m_vertScroll.m_scrollW = iTempInt1;
	m_segDlg.SetScrollArrowWH(4 * m_dHoriRatio,8 * m_dVertRatio);

	m_segDlg.SetBeEditable(FALSE);
}

// 函数 CLoadSamDlg::CurrentSegmentStepChangedOnRun
// 作用：执行CurrentSegmentStepChangedOnRun。
// 参数：iCycle：整数；iSeg：整数；iStep：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 UpdateCurSelectStepCycleInfo、SetSegmentSetpShow。
int CLoadSamDlg::CurrentSegmentStepChangedOnRun(int iCycle,int iSeg,int iStep)
{
	if(-1 != m_segDlg.m_priorItem && -1 != m_segDlg.m_priorStep)
	{
		m_segDlg.UpdateCurSelectStepCycleInfo(m_segDlg.m_priorItem,m_segDlg.m_priorStep,iCycle,FALSE);
	}

	m_segDlg.UpdateCurSelectStepCycleInfo(iSeg,iStep,iCycle + 1,TRUE,FALSE);
	m_segDlg.SetSegmentSetpShow(iSeg,iStep,TRUE);	

	m_segDlg.m_priorItem = iSeg;
	m_segDlg.m_priorStep = iStep;

	return 0;
}

