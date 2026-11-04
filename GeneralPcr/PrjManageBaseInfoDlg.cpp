// 【交接】 GeneralPcr\PrjManageBaseInfoDlg.cpp
// 作用：PrjManageBaseInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CPrjManageBaseInfoDlg、CDialogEx、Empty、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "PrjManageBaseInfoDlg.h"
#include "DataAnalysisPara.h"
#include "GeneralPcr.h"
#include "PrjManageDlg.h"
#include "PublicFun.h"

// CPrjManageBaseInfoDlg  dialog
IMPLEMENT_DYNAMIC(CPrjManageBaseInfoDlg, CDialogEx)

// 函数 CPrjManageBaseInfoDlg::CPrjManageBaseInfoDlg
// 作用：执行CPrjManageBaseInfoDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CPrjManageBaseInfoDlg::CPrjManageBaseInfoDlg (CWnd* pParent /*=NULL*/)
	: CDialogEx(CPrjManageBaseInfoDlg ::IDD, pParent),m_prjBaseInfoDlg(TRUE,this,this)
{
	m_bEditable = TRUE;
	m_bCtrlCreated = FALSE;
	m_iDyeChangeChanId = -1;
	m_strDyeChangeName.Empty(); 
}

// 函数 CPrjManageBaseInfoDlg::~CPrjManageBaseInfoDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPrjManageBaseInfoDlg::~CPrjManageBaseInfoDlg ()
{

}

// 函数 CPrjManageBaseInfoDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CPrjManageBaseInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrjManageBaseInfoDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_MESSAGE(WM_PRJTYPECHANGED,OnMsgPrjTypeChanged)
	ON_MESSAGE(WM_TELLPARENTCELLCHANGED,OnMsgTellParentLstCellChanged)

	ON_BN_CLICKED(ID_PRJMANAGEBASEINFODLG_BT_INSERTSEGMENT,&CPrjManageBaseInfoDlg::OnBnClickedInsertSegment)
	ON_BN_CLICKED(ID_PRJMANAGEBASEINFODLG_BT_INSERTSTEP,&CPrjManageBaseInfoDlg::OnBnClickedInsertStep)
	ON_BN_CLICKED(ID_PRJMANAGEBASEINFODLG_BT_EDITSTEP,&CPrjManageBaseInfoDlg::OnBnClickedEditStep)
	ON_BN_CLICKED(ID_PRJMANAGEBASEINFODLG_BT_EDITSEGMENT,&CPrjManageBaseInfoDlg::OnBnClickedEditSegment)
	ON_BN_CLICKED(ID_PRJMANAGEBASEINFODLG_BT_DELETE,&CPrjManageBaseInfoDlg::OnBnClickedDelete)

	ON_COMMAND(ID_MENU_INSERTSEGBEFORE2, OnFileMenuSegInsertBefore)
	ON_COMMAND(ID_MENU_INSERTSEGAFTER2, OnFileMenuSegInsertAfter)
	ON_COMMAND(ID_MENU_INSERTSEGLAST2, OnFileMenuSegInsertLast)

	ON_COMMAND(ID_MENU_INSERTSTEPBEFORE2, OnFileMenuStepInsertBefore)
	ON_COMMAND(ID_MENU_INSERTSTEPAFTER2, OnFileMenuStepInsertAfter)
	ON_COMMAND(ID_MENU_INSERTSTEPLAST2, OnFileMenuStepInsertLast)

	ON_BN_CLICKED(ID_PRJMANAGEBASEINFODLG_BT_ADDTARGET, &CPrjManageBaseInfoDlg::OnBnClickedAddTarget)
	ON_BN_CLICKED(ID_PRJMANAGEBASEINFODLG_BT_DELETETARGET, &CPrjManageBaseInfoDlg::OnBnClickedDeleteTarget)
	ON_MESSAGE(WM_ROWSELECTCHANGE,OnMsgRowSelectedChange)
END_MESSAGE_MAP()

// 函数 CPrjManageBaseInfoDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CPrjManageBaseInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	
	CRect rect;
	GetClientRect(&rect);
	
	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(0,0,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);

	DrawRoundRectangleNew(&memDc,836 * m_dHoriRatio,0,716 * m_dHoriRatio,235 * m_dVertRatio,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	DrawRoundRectangleNew(&memDc,836 * m_dHoriRatio,252 * m_dVertRatio,716 * m_dHoriRatio,284 * m_dVertRatio,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	DrawRoundRectangleNew(&memDc,836 * m_dHoriRatio,552 * m_dVertRatio,716 * m_dHoriRatio,282 * m_dVertRatio,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	DrawRoundRectangleNew(&memDc,0,252 * m_dVertRatio,820 * m_dHoriRatio,284 * m_dVertRatio,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	DrawRoundRectangleNew(&memDc,0,552 * m_dVertRatio,820 * m_dHoriRatio,282 * m_dVertRatio,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);

	memDc.FillSolidRect(852 * m_dHoriRatio,21 * m_dVertRatio,12 * m_dHoriRatio,4 * m_dVertRatio,CLR_SOFT_THEME);
	memDc.FillSolidRect(856 * m_dHoriRatio,17 * m_dVertRatio,4 * m_dHoriRatio,12 * m_dVertRatio,CLR_SOFT_THEME);

	memDc.FillSolidRect(852 * m_dHoriRatio,272 * m_dVertRatio,12 * m_dHoriRatio,4 * m_dVertRatio,CLR_SOFT_THEME);
	memDc.FillSolidRect(856 * m_dHoriRatio,268 * m_dVertRatio,4 * m_dHoriRatio,12 * m_dVertRatio,CLR_SOFT_THEME);

	memDc.FillSolidRect(852 * m_dHoriRatio,572 * m_dVertRatio,12 * m_dHoriRatio,4 * m_dVertRatio,CLR_SOFT_THEME);
	memDc.FillSolidRect(856 * m_dHoriRatio,568 * m_dVertRatio,4 * m_dHoriRatio,12 * m_dVertRatio,CLR_SOFT_THEME);

	memDc.FillSolidRect(690 * m_dHoriRatio,564 * m_dVertRatio,4 * m_dHoriRatio,14 * m_dVertRatio,CLR_SOFT_THEME);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	int iStartX = 872 * m_dHoriRatio,iEndX = 1072 * m_dHoriRatio;

	memDc.DrawText(pLangInfo->GetText(125),CRect(iStartX,9 * m_dVertRatio,iEndX,36 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(121),CRect(iStartX,260 * m_dVertRatio,iEndX,287 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(126),CRect(iStartX,560 * m_dVertRatio,iEndX,587 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	
	memDc.SelectObject(&m_fontNormal.m_fontSet);
	memDc.SetTextColor(m_fontNormal.m_txClr1);
	memDc.DrawText(pLangInfo->GetText(448),CRect(16 * m_dHoriRatio,269 * m_dVertRatio,186 * m_dHoriRatio,283 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(35),CRect(710 * m_dHoriRatio,559 * m_dVertRatio,800 * m_dHoriRatio,583 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);

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

// 函数 CPrjManageBaseInfoDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CPrjManageBaseInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType,cx,cy);

	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}
}

// 函数 CPrjManageBaseInfoDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitSonDlg、CreateCtrl、InitDlg、InitCtrl、SetCtrlPos、SetCtrlText。
BOOL CPrjManageBaseInfoDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	InitSonDlg();

	CreateCtrl();
	m_bCtrlCreated = TRUE;
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();

	ShowCtrl();

	return TRUE;
}

// 函数 CPrjManageBaseInfoDlg::InitSonDlg
// 作用：初始化InitSonDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitPrjBaseInfoDlg。
void CPrjManageBaseInfoDlg::InitSonDlg()
{
	InitPrjBaseInfoDlg();
}

// 函数 CPrjManageBaseInfoDlg::InitPrjBaseInfoDlg
// 作用：初始化InitPrjBaseInfoDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CPrjManageBaseInfoDlg::InitPrjBaseInfoDlg()
{
	m_prjBaseInfoDlg.Create(IDD_MIDDLEDLG,this);
}

// 函数 CPrjManageBaseInfoDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateEd、CreateLst、CreateSegment。
void CPrjManageBaseInfoDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateEd();
	CreateLst();
	CreateSegment();
}

// 函数 CPrjManageBaseInfoDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect、EnableWindow。
void CPrjManageBaseInfoDlg::CreateBt()
{
	m_btInsertSegment.Create(_T("插入程序段"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PRJMANAGEBASEINFODLG_BT_INSERTSEGMENT);
	m_btInsertStep.Create(_T("插入步骤"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PRJMANAGEBASEINFODLG_BT_INSERTSTEP);
	m_btEditStep.Create(_T("编辑步骤"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PRJMANAGEBASEINFODLG_BT_EDITSTEP);
	m_btEditSegment.Create(_T("编辑程序段"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PRJMANAGEBASEINFODLG_BT_EDITSEGMENT);
	m_btDelete.Create(_T("删除"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PRJMANAGEBASEINFODLG_BT_DELETE);

	m_btnAddTarget.Create(_T("增加目标"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PRJMANAGEBASEINFODLG_BT_ADDTARGET);
	m_btnDeleteTarget.Create(_T("删除目标"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PRJMANAGEBASEINFODLG_BT_DELETETARGET);
	m_btnDeleteTarget.EnableWindow(FALSE);
}

// 函数 CPrjManageBaseInfoDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjManageBaseInfoDlg::CreateSt()
{
	
}

// 函数 CPrjManageBaseInfoDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjManageBaseInfoDlg::CreateEd()
{
	
}

// 函数 CPrjManageBaseInfoDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CPrjManageBaseInfoDlg::CreateLst()
{
	m_lstAmlBaseParam.Create(IDD_MIDDLEDLG,this);
	m_lstMeltParam.Create(IDD_MIDDLEDLG,this);
	m_lstCrossParam.Create(IDD_MIDDLEDLG,this);
	m_lstChanSet.Create(IDD_MIDDLEDLG,this);
}

// 函数 CPrjManageBaseInfoDlg::CreateSegment
// 作用：创建或加入CreateSegment。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CPrjManageBaseInfoDlg::CreateSegment()
{
	m_segDlg.Create(IDD_MIDDLEDLG,this);
}

// 函数 CPrjManageBaseInfoDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、SetMyFont、RGB。
void CPrjManageBaseInfoDlg::InitDlg()
{
	SetTextClr1(CLR_2LEVEL_THEME);
	SetMyFont(m_stTxFont,18 * m_dTxRatio,FW_BOLD);

	m_fontNormal.SetTextClr1(RGB(0X39,0X45,0X65));
	m_fontNormal.SetMyFont(m_stTxFont,16 * m_dTxRatio);
}

// 函数 CPrjManageBaseInfoDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitEd、InitLst、InitSegment。
void CPrjManageBaseInfoDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitEd();
	InitLst();
	InitSegment();
}

// 函数 CPrjManageBaseInfoDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitInsertBt、SetSplitLineXPos、InitOtherBt。
void CPrjManageBaseInfoDlg::InitBt()
{
	InitInsertBt(&m_btInsertSegment);
	m_btInsertSegment.SetSplitLineXPos(94 * m_dHoriRatio);

	InitInsertBt(&m_btInsertStep);
	m_btInsertStep.SetSplitLineXPos(82 * m_dHoriRatio);

	InitOtherBt(&m_btEditStep);
	InitOtherBt(&m_btEditSegment);
	InitOtherBt(&m_btDelete);

	InitOtherBt(&m_btnAddTarget);
	InitOtherBt(&m_btnDeleteTarget);
}

// 函数 CPrjManageBaseInfoDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjManageBaseInfoDlg::InitSt()
{
	
}

// 函数 CPrjManageBaseInfoDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjManageBaseInfoDlg::InitEd()
{
	
}

// 函数 CPrjManageBaseInfoDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitLstBaseParam、InitLstMeltParam、InitLstCrossParam、InitLstChanSet。
void CPrjManageBaseInfoDlg::InitLst()
{
	InitLstBaseParam();
	InitLstMeltParam();
	InitLstCrossParam();
	InitLstChanSet();
}

// 函数 CPrjManageBaseInfoDlg::InitSegment
// 作用：初始化InitSegment。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetFuncEditCtrlFont、SetFourAngleBkColor、SetScrollArrowWH、SetShieldGradientSetState、SetTemperatureRateShowState。
void CPrjManageBaseInfoDlg::InitSegment()
{
	int iFontH = 14 * m_dTxRatio;

	m_segDlg.m_fontStepTag.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_segDlg.m_fontGeneral.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_segDlg.m_fontSegTag.SetMyFont(m_stTxFont,iFontH,FW_BOLD,TYPE_PIXEL);
	m_segDlg.SetFuncEditCtrlFont(m_stTxFont,iFontH);
	m_segDlg.SetFourAngleBkColor(CLR_SOFT_LIGHT);

	int iTempInt1 = 34 * m_dVertRatio;
	m_segDlg.m_horiScroll.m_arrowWH = iTempInt1;
	m_segDlg.m_horiScroll.m_scrollH = iTempInt1;
	m_segDlg.m_vertScroll.m_arrowWH = iTempInt1;
	m_segDlg.m_vertScroll.m_scrollW = iTempInt1;
	m_segDlg.SetScrollArrowWH(4 * m_dHoriRatio,8 * m_dVertRatio);

	//设置本实验对梯度功能是否支持
#ifdef N96INSTRUMENT
	m_segDlg.SetShieldGradientSetState(FALSE);
#else
	m_segDlg.SetShieldGradientSetState(TRUE);
#endif

	//设置本实验是否显示升降温速率
#ifdef PS96INSTRUMENT
	m_segDlg.SetTemperatureRateShowState(FALSE);
#endif

	return;
}

// 函数 CPrjManageBaseInfoDlg::InitLstBaseParam
// 作用：初始化InitLstBaseParam。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetHeaderHeight、int、SetMyHeaderFont、SetMyFont、SetTextClr1、RGB。
void CPrjManageBaseInfoDlg::InitLstBaseParam()
{
	int iFontH = 14 * m_dTxRatio;
	m_lstAmlBaseParam.SetHeaderHeight(int(24 * m_dVertRatio));
	m_lstAmlBaseParam.SetMyHeaderFont(m_stTxFont,iFontH);
	m_lstAmlBaseParam.SetMyFont(m_stTxFont,iFontH);
	m_lstAmlBaseParam.SetTextClr1(RGB(0X39,0X45,0X65));
	m_lstAmlBaseParam.SetHeaderTextColor(RGB(0X39,0X45,0X65));
	m_lstAmlBaseParam.SetFourAngleBkColor(RGB(0XFF,0XFF,0XFF));
	m_lstAmlBaseParam.SetItemHeight(37 * m_dVertRatio);
	m_lstAmlBaseParam.SetBeSingleSelect(TRUE);
	m_lstAmlBaseParam.SetBeTellParentRowSelChange(TRUE);
	m_lstAmlBaseParam.SetRowBkSelectedColor(RGB(0XE1,0XE1,0XE1));
	//m_lstAmlBaseParam.SetBeShowRowSelectState(FALSE);
	m_lstAmlBaseParam.SetAllRowHeight(int(30 * m_dVertRatio));

	int iTempInt1 = 34 * m_dVertRatio;
	m_lstAmlBaseParam.m_horiScroll.m_arrowWH = iTempInt1;
	m_lstAmlBaseParam.m_horiScroll.m_scrollH = iTempInt1;
	m_lstAmlBaseParam.m_vertScroll.m_arrowWH = iTempInt1;
	m_lstAmlBaseParam.m_vertScroll.m_scrollW = iTempInt1;
	
	m_lstAmlBaseParam.InsertColumn(0,theApp.m_pLangInfo->GetText(111));
	m_lstAmlBaseParam.InsertColumn(1,theApp.m_pLangInfo->GetText(112));
	m_lstAmlBaseParam.InsertColumn(2,theApp.m_pLangInfo->GetText(53));
	m_lstAmlBaseParam.InsertColumn(3,theApp.m_pLangInfo->GetText(294));
	m_lstAmlBaseParam.InsertColumn(4,theApp.m_pLangInfo->GetText(114));
	m_lstAmlBaseParam.InsertColumn(5,theApp.m_pLangInfo->GetText(115));
	m_lstAmlBaseParam.InsertColumn(6,theApp.m_pLangInfo->GetText(117));
	m_lstAmlBaseParam.InsertColumn(7,theApp.m_pLangInfo->GetText(118));
	m_lstAmlBaseParam.InsertColumn(8,theApp.m_pLangInfo->GetText(119));
	m_lstAmlBaseParam.InsertColumn(9,theApp.m_pLangInfo->GetText(279));
	m_lstAmlBaseParam.InsertColumn(10,theApp.m_pLangInfo->GetText(280));

	//m_lstAmlBaseParam.SetColumnEditable(1,TRUE);
	m_lstAmlBaseParam.SetColumnEditable(2,TRUE);
	m_lstAmlBaseParam.SetColumnEditable(4,TRUE);
	m_lstAmlBaseParam.SetColumnEditable(5,TRUE);
	m_lstAmlBaseParam.SetColumnEditable(7,TRUE);
	m_lstAmlBaseParam.SetColumnEditable(8,TRUE);
	m_lstAmlBaseParam.SetColumnEditable(9,TRUE);
	m_lstAmlBaseParam.SetColumnEditable(10,TRUE);

	m_lstAmlBaseParam.SetColumnCheckFunc(3,TRUE);
	m_lstAmlBaseParam.SetColumnCheckFunc(6,TRUE);

	ResetAmlListColumnWidth();

	CLinkList<int> lnkControledIdIndex;
	int idIndex = 4;
	lnkControledIdIndex.AddTail(idIndex);
	idIndex = 5;
	lnkControledIdIndex.AddTail(idIndex);
	m_lstAmlBaseParam.SetMapColumnDisableControl(3,lnkControledIdIndex);

	lnkControledIdIndex.Clear();
	idIndex = 7;
	lnkControledIdIndex.AddTail(idIndex);
	idIndex = 8;
	lnkControledIdIndex.AddTail(idIndex);
	m_lstAmlBaseParam.SetMapColumnDisableControl(6,lnkControledIdIndex);

	lnkControledIdIndex.Clear();
	idIndex = 0;
	lnkControledIdIndex.AddTail(idIndex);
	m_lstAmlBaseParam.SetMapRowOutsideControl(0,lnkControledIdIndex);

	lnkControledIdIndex.Clear();
	idIndex = 1;
	lnkControledIdIndex.AddTail(idIndex);
	m_lstAmlBaseParam.SetMapRowOutsideControl(1,lnkControledIdIndex);

	lnkControledIdIndex.Clear();
	idIndex = 2;
	lnkControledIdIndex.AddTail(idIndex);
	m_lstAmlBaseParam.SetMapRowOutsideControl(2,lnkControledIdIndex);

	m_lstAmlBaseParam.AddPairToMapDisabledStateKeyString(_T("FALSE"),FALSE);
	m_lstAmlBaseParam.AddPairToMapDisabledStateKeyString(_T("TRUE"),TRUE);

	CMaxMinInfo maxMinInfo;
	maxMinInfo.SetBeOnlyIntergerNumber(TRUE);
	maxMinInfo.SetBeSetMinValue(TRUE);
	maxMinInfo.SetMinValue(1);
	maxMinInfo.SetBeSetMaxValue(TRUE);
	maxMinInfo.SetMaxValue(100);
	maxMinInfo.SetBeMaxMinSimultaneousEffect(TRUE);
	m_lstAmlBaseParam.SetColumnMaxMinInfo(4,maxMinInfo);
	m_lstAmlBaseParam.SetColumnMaxMinInfo(5,maxMinInfo);

	maxMinInfo.ClearMaxMinLimit();
	maxMinInfo.SetBeOnlyFloatNumber(TRUE);
	maxMinInfo.SetBeAllowNegtiveNumber(TRUE);
	m_lstAmlBaseParam.SetColumnMaxMinInfo(7,maxMinInfo);
	m_lstAmlBaseParam.SetColumnMaxMinInfo(8,maxMinInfo);

	return;
}

// 函数 CPrjManageBaseInfoDlg::ResetAmlListColumnWidth
// 作用：更新或清除ResetAmlListColumnWidth。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetColumnWidth、GetFrameLineWidth、Width、Invalidate。
void CPrjManageBaseInfoDlg::ResetAmlListColumnWidth()
{
	//int width = 684 * m_dHoriRatio;
	int tempInt = 36 * m_dHoriRatio;

	//BOOL bHasVertScroll = m_lstAmlBaseParam.m_vertScroll.m_bScrollNeedShow;
	//BOOL bHasVertScroll = TRUE;
	//m_lstAmlBaseParam.m_horiScroll.m_bScrollNeedShow = FALSE;

	m_lstAmlBaseParam.SetColumnWidth(0,tempInt);
	//width -= tempInt;
	tempInt = 75 * m_dHoriRatio;
	m_lstAmlBaseParam.SetColumnWidth(1,tempInt); // Dye
	//width -= tempInt;
	//if (bHasVertScroll)
	//	tempInt = 55 * m_dHoriRatio;
	//else
		//tempInt = 65 * m_dHoriRatio;
	m_lstAmlBaseParam.SetColumnWidth(2,tempInt); // Target
	//width -= tempInt;
	//tempInt = 55 * m_dHoriRatio;
	m_lstAmlBaseParam.SetColumnWidth(3,tempInt); // Auto baseline
	//width -= tempInt;
	//tempInt = 60 * m_dHoriRatio;
	m_lstAmlBaseParam.SetColumnWidth(4,tempInt);
	//width -= tempInt;
	//tempInt = 60 * m_dHoriRatio;
	m_lstAmlBaseParam.SetColumnWidth(5,tempInt);
	//width -= tempInt;
	//tempInt = 55 * m_dHoriRatio;
	m_lstAmlBaseParam.SetColumnWidth(6,tempInt);
	//width -= tempInt;
	//if (bHasVertScroll)
	//	tempInt = 65 * m_dHoriRatio;
	//else
		tempInt = 95 * m_dHoriRatio;
	m_lstAmlBaseParam.SetColumnWidth(7,tempInt);
	//width -= tempInt;
	m_lstAmlBaseParam.SetColumnWidth(8,tempInt);
	//width -= tempInt;
	m_lstAmlBaseParam.SetColumnWidth(9,tempInt);
	//width -= tempInt;
	//if (bHasVertScroll)
	//	width -= m_lstAmlBaseParam.GetFrameLineWidth() * 2 + m_lstAmlBaseParam.m_vertScroll.m_rcScroll.Width();
	//else
		//width -= m_lstAmlBaseParam.GetFrameLineWidth() * 2;
	//if (width < tempInt)
	//	width = tempInt;
	//m_lstAmlBaseParam.SetColumnWidth(10,width);
	m_lstAmlBaseParam.SetColumnWidth(10, tempInt);

	m_lstAmlBaseParam.Invalidate();
}


// 函数 CPrjManageBaseInfoDlg::InitLstMeltParam
// 作用：初始化InitLstMeltParam。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetHeaderHeight、SetMyHeaderFont、SetMyFont、SetTextClr1、RGB、SetHeaderTextColor。
void CPrjManageBaseInfoDlg::InitLstMeltParam()
{
	int iFontH = 14 * m_dTxRatio;
	m_lstMeltParam.SetHeaderHeight(24 * m_dVertRatio);
	m_lstMeltParam.SetMyHeaderFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_lstMeltParam.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_lstMeltParam.SetTextClr1(RGB(0X39,0X45,0X65));
	m_lstMeltParam.SetHeaderTextColor(RGB(0X39,0X45,0X65));
	m_lstMeltParam.SetFourAngleBkColor(RGB(0XFF,0XFF,0XFF));
	m_lstMeltParam.SetItemHeight(37 * m_dVertRatio);
	m_lstMeltParam.SetRowBkSelectedColor(RGB(0XF1,0XF1,0XF1));
	m_lstMeltParam.SetBeShowRowSelectState(FALSE);

	int iTempInt1 = 34 * m_dVertRatio;
	m_lstMeltParam.m_horiScroll.m_arrowWH = iTempInt1;
	m_lstMeltParam.m_horiScroll.m_scrollH = iTempInt1;
	m_lstMeltParam.m_vertScroll.m_arrowWH = iTempInt1;
	m_lstMeltParam.m_vertScroll.m_scrollW = iTempInt1;

	m_lstMeltParam.InsertColumn(0,_T("序号"));
	m_lstMeltParam.InsertColumn(1,_T("通道"));
	m_lstMeltParam.InsertColumn(2,_T("目标信息"));
	m_lstMeltParam.InsertColumn(3,_T("最低温度"));
	m_lstMeltParam.InsertColumn(4,_T("最高温度"));
	m_lstMeltParam.InsertColumn(5,_T("峰高阈值"));

	m_lstMeltParam.SetColumnEditable(3,TRUE);
	m_lstMeltParam.SetColumnEditable(4,TRUE);
	m_lstMeltParam.SetColumnEditable(5,TRUE);

	int width = 684 * m_dHoriRatio;
	int tempInt = 36 * m_dHoriRatio;

	m_lstMeltParam.SetColumnWidth(0,tempInt);
	width -= tempInt;
	tempInt = 60 * m_dHoriRatio;
	m_lstMeltParam.SetColumnWidth(1,tempInt);
	width -= tempInt;
	tempInt = 64 * m_dHoriRatio;
	m_lstMeltParam.SetColumnWidth(2,tempInt);
	width -= tempInt;
	tempInt = 172 * m_dHoriRatio;
	m_lstMeltParam.SetColumnWidth(3,tempInt);
	width -= tempInt;
	tempInt = 172 * m_dHoriRatio;
	m_lstMeltParam.SetColumnWidth(4,tempInt);
	width -= tempInt;
	width -= m_lstMeltParam.GetFrameLineWidth() * 2;
	m_lstMeltParam.SetColumnWidth(5,width);

	CMaxMinInfo maxMinInfo;
	maxMinInfo.SetBeOnlyFloatNumber(TRUE);
	maxMinInfo.SetBeSetMinValue(TRUE);
	maxMinInfo.SetMinValue(4);
	maxMinInfo.SetBeSetMaxValue(TRUE);
	maxMinInfo.SetMaxValue(100);
	maxMinInfo.SetBeLessThanMinSetMin(FALSE);
	m_lstMeltParam.SetColumnMaxMinInfo(3,maxMinInfo);
	m_lstMeltParam.SetColumnMaxMinInfo(4,maxMinInfo);

	maxMinInfo.ClearMaxMinLimit();
	maxMinInfo.SetBeOnlyFloatNumber(TRUE);
	maxMinInfo.SetBeSetMinValue(TRUE);
	maxMinInfo.SetMinValue(0);
	maxMinInfo.SetBeMinEqualSignWork(FALSE);
	m_lstMeltParam.SetColumnMaxMinInfo(5,maxMinInfo);

	return;
}

// 函数 CPrjManageBaseInfoDlg::InitLstCrossParam
// 作用：初始化InitLstCrossParam。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetHeaderHeight、SetMyHeaderFont、SetMyFont、SetTextClr1、RGB、SetHeaderTextColor。
void CPrjManageBaseInfoDlg::InitLstCrossParam()
{
	int iFontH = 14 * m_dTxRatio;
	m_lstCrossParam.SetHeaderHeight(24 * m_dVertRatio);
	m_lstCrossParam.SetMyHeaderFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_lstCrossParam.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_lstCrossParam.SetTextClr1(RGB(0X39,0X45,0X65));
	m_lstCrossParam.SetHeaderTextColor(RGB(0X39,0X45,0X65));
	m_lstCrossParam.SetFourAngleBkColor(RGB(0XFF,0XFF,0XFF));
	m_lstCrossParam.SetItemHeight(37 * m_dVertRatio);
	m_lstCrossParam.SetRowBkSelectedColor(RGB(0XF1,0XF1,0XF1));
	m_lstCrossParam.SetBeShowRowSelectState(FALSE);

	int iTempInt1 = 34 * m_dVertRatio;
	m_lstCrossParam.m_horiScroll.m_arrowWH = iTempInt1;
	m_lstCrossParam.m_horiScroll.m_scrollH = iTempInt1;
	m_lstCrossParam.m_vertScroll.m_arrowWH = iTempInt1;
	m_lstCrossParam.m_vertScroll.m_scrollW = iTempInt1;
	
	return;
}

// 函数 CPrjManageBaseInfoDlg::InitLstChanSet
// 作用：初始化InitLstChanSet。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetHeaderHeight、SetMyHeaderFont、SetMyFont、SetTextClr1、RGB、SetHeaderTextColor。
void CPrjManageBaseInfoDlg::InitLstChanSet()
{
	int iFtH = 14 * m_dTxRatio;
	m_lstChanSet.SetHeaderHeight(24 * m_dVertRatio);
	m_lstChanSet.SetMyHeaderFont(m_stTxFont,iFtH);
	m_lstChanSet.SetMyFont(m_stTxFont,iFtH);
	m_lstChanSet.SetTextClr1(RGB(0X39,0X45,0X65));
	m_lstChanSet.SetHeaderTextColor(RGB(0X39,0X45,0X65));
	m_lstChanSet.SetFourAngleBkColor(RGB(0XFF,0XFF,0XFF));
	m_lstChanSet.SetItemHeight(37 * m_dVertRatio);
	m_lstChanSet.SetRowBkSelectedColor(RGB(0XF1,0XF1,0XF1));
	m_lstChanSet.SetBeShowRowSelectState(FALSE);

	int iTempInt1 = 34 * m_dVertRatio;
	m_lstChanSet.m_horiScroll.m_arrowWH = iTempInt1;
	m_lstChanSet.m_horiScroll.m_scrollH = iTempInt1;
	m_lstChanSet.m_vertScroll.m_arrowWH = iTempInt1;
	m_lstChanSet.m_vertScroll.m_scrollW = iTempInt1;
	
	return;
}

// 函数 CPrjManageBaseInfoDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、SetWindowPos、AddRectToDelete、int、CalcRectResult。
void CPrjManageBaseInfoDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	m_prjBaseInfoDlg.SetWindowPos(this,0,0,820 * m_dHoriRatio,236 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(0,0,820 * m_dHoriRatio,236 * m_dVertRatio);

	m_lstChanSet.SetWindowPos(this,16 * m_dHoriRatio,308 * m_dVertRatio,788 * m_dHoriRatio,212 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(16 * m_dHoriRatio,308 * m_dVertRatio,788 * m_dHoriRatio,212 * m_dVertRatio);

	m_segDlg.SetWindowPos(this,0,552 * m_dVertRatio,680 * m_dHoriRatio,280 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(0,552 * m_dVertRatio,680 * m_dHoriRatio,280 * m_dVertRatio);
	
	m_btnDeleteTarget.SetWindowPos(this, int(1426*m_dHoriRatio), int(9*m_dVertRatio), int(110*m_dHoriRatio), int(28*m_dVertRatio),SWP_NOZORDER);
	m_btnAddTarget.SetWindowPos(this, int(1306*m_dHoriRatio), int(9 * m_dVertRatio), int(110*m_dHoriRatio), int(28*m_dVertRatio),SWP_NOZORDER);

	m_lstAmlBaseParam.SetWindowPos(this,852 * m_dHoriRatio,47 * m_dVertRatio,684 * m_dHoriRatio,176 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(852 * m_dHoriRatio,47 * m_dVertRatio,684 * m_dHoriRatio,176 * m_dVertRatio);

	m_lstMeltParam.SetWindowPos(this,852 * m_dHoriRatio,298 * m_dVertRatio,684 * m_dHoriRatio,221 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(852 * m_dHoriRatio,298 * m_dVertRatio,684 * m_dHoriRatio,221 * m_dVertRatio);

	m_lstCrossParam.SetWindowPos(this,852 * m_dHoriRatio,598 * m_dVertRatio,684 * m_dHoriRatio,221 * m_dVertRatio,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(852 * m_dHoriRatio,598 * m_dVertRatio,684 * m_dHoriRatio,221 * m_dVertRatio);
	
	int iTempInt1 = 690 * m_dHoriRatio,iTempInt3 = 28 * m_dVertRatio,iTempInt4 = 110 * m_dHoriRatio;
	m_btInsertSegment.SetWindowPos(this,iTempInt1,604 * m_dVertRatio,121 * m_dHoriRatio,iTempInt3,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt1,604 * m_dVertRatio,121 * m_dHoriRatio,iTempInt3);

	m_btEditSegment.SetWindowPos(this,iTempInt1,644 * m_dVertRatio,iTempInt4,iTempInt3,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt1,644 * m_dVertRatio,iTempInt4,iTempInt3);

	m_btInsertStep.SetWindowPos(this,iTempInt1,684 * m_dVertRatio,iTempInt4,iTempInt3,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt1,684 * m_dVertRatio,iTempInt4,iTempInt3);

	m_btDelete.SetWindowPos(this,iTempInt1,724 * m_dVertRatio,iTempInt4,iTempInt3,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt1,724 * m_dVertRatio,iTempInt4,iTempInt3);

	m_btEditStep.SetWindowPos(this,iTempInt1,764 * m_dVertRatio,iTempInt4,iTempInt3,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt1,764 * m_dVertRatio,iTempInt4,iTempInt3);

	m_rcManage.CalcRectResult();

	return;
}

// 函数 CPrjManageBaseInfoDlg::SetLstChanTargetColumnWidth
// 作用：设置SetLstChanTargetColumnWidth。
// 参数：iChanNum：整数。
// 返回：没有返回值。
// 过程：函数里会调用 SetColumnWidth、GetFrameLineWidth。
void CPrjManageBaseInfoDlg::SetLstChanTargetColumnWidth(int iChanNum)
{
	if(iChanNum < 1)
	{
		return;
	}

	int iWidth = 788 * m_dHoriRatio;
	int iTempInt = 36 * m_dHoriRatio;

	m_lstChanSet.SetColumnWidth(0,iTempInt);
	iWidth -= iTempInt;
	iTempInt = 136 * m_dHoriRatio;
	m_lstChanSet.SetColumnWidth(1,iTempInt);
	iWidth -= iTempInt;

	iTempInt = iWidth / iChanNum;

	for(int i = 0;i < iChanNum;++i)
	{
		if(i == iChanNum - 1)
		{
			iWidth -= m_lstChanSet.GetFrameLineWidth() * 2;
			m_lstChanSet.SetColumnWidth(i + 2,iWidth);
		}
		else
		{
			m_lstChanSet.SetColumnWidth(i + 2,iTempInt);
			iWidth -= iTempInt;
		}
	}

	return;
}

// 函数 CPrjManageBaseInfoDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CPrjManageBaseInfoDlg::ShowCtrl()
{
	m_prjBaseInfoDlg.ShowWindow(SW_SHOW);
	m_lstAmlBaseParam.ShowWindow(SW_SHOW);
	m_lstMeltParam.ShowWindow(SW_SHOW);
	m_lstCrossParam.ShowWindow(SW_SHOW);
	m_lstChanSet.ShowWindow(SW_SHOW);
	m_segDlg.ShowWindow(SW_SHOW);

	m_btInsertSegment.ShowWindow(SW_SHOW);
	m_btInsertStep.ShowWindow(SW_SHOW);
	m_btEditStep.ShowWindow(SW_SHOW);
	m_btEditSegment.ShowWindow(SW_SHOW);
	m_btDelete.ShowWindow(SW_SHOW);

	m_btnAddTarget.ShowWindow(SW_SHOW);
	m_btnDeleteTarget.ShowWindow(SW_SHOW);
}

// 函数 CPrjManageBaseInfoDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetWindowText、GetText、ResetLstAmlColumnText、ResetLstMeltColumnText、SetColumnText。
void CPrjManageBaseInfoDlg::SetCtrlText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_btInsertSegment.SetWindowText(pLangInfo->GetText(36));
	m_btInsertStep.SetWindowText(pLangInfo->GetText(41));
	m_btEditStep.SetWindowText(pLangInfo->GetText(44));
	m_btEditSegment.SetWindowText(pLangInfo->GetText(40));
	m_btDelete.SetWindowText(pLangInfo->GetText(45));

	m_btnAddTarget.SetWindowText(pLangInfo->GetText(522));
	m_btnDeleteTarget.SetWindowText(pLangInfo->GetText(523));

	ResetLstAmlColumnText();
	ResetLstMeltColumnText();

	m_lstChanSet.SetColumnText(0,pLangInfo->GetText(111));
	m_lstChanSet.SetColumnText(1,pLangInfo->GetText(447));

	return;
}

// 函数 CPrjManageBaseInfoDlg::InitInsertBt
// 作用：初始化InitInsertBt。
// 参数：pInsertBt：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、GetBeEnglish、SetMyFont。
void CPrjManageBaseInfoDlg::InitInsertBt(CMyInsertBt *pInsertBt)
{
	if(NULL == pInsertBt->GetSafeHwnd())
	{
		return;
	}

	int iFontH = 13 * m_dTxRatio;
	if(theApp.m_pLangInfo->GetBeEnglish())
	{
		iFontH = 15 * m_dTxRatio;
	}

	pInsertBt->m_arrowInfo.m_eArrowStyle = EAS_LEFTRIGHT;
	pInsertBt->m_arrowInfo.m_arrowW = 8 * m_dHoriRatio;
	pInsertBt->m_arrowInfo.m_arrowH = 4 * m_dVertRatio;
	pInsertBt->SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	return;
}

// 函数 CPrjManageBaseInfoDlg::InitOtherBt
// 作用：初始化InitOtherBt。
// 参数：pBt：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、GetBeEnglish、SetRoundRectParam、RGB、SetBkColor、Color。
void CPrjManageBaseInfoDlg::InitOtherBt(CMyButton *pBt)
{
	if(NULL == pBt->GetSafeHwnd())
	{
		return;
	}

	int iFontH = 13 * m_dTxRatio;
	if(theApp.m_pLangInfo->GetBeEnglish())
	{
		iFontH = 15 * m_dTxRatio;
	}

	pBt->SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),FALSE);
	pBt->SetBkColor(Color(0XF1,0XF4,0XF9),Color(0XFF,0XFF,0XFF),Color(0XE7,0XE7,0XE7),Color(0XF1,0XF4,0XF9));
	pBt->SetEdgeColor(Color(0XD8,0XD8,0XD8),Color(0XD8,0XD8,0XD8),Color(0XD8,0XD8,0XD8),Color(0XD8,0XD8,0XD8));
	pBt->SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	pBt->SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	return;
}

// 函数 CPrjManageBaseInfoDlg::ResetLstChanCross
// 作用：更新或清除ResetLstChanCross。
// 参数：iChanCount：整数；lnkDyeName。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 DeleteAllColumn、Invalidate、SetBeOnlyFloatNumber、SetBeSetMinValue、SetMinValue、SetBeSetMaxValue。
int CPrjManageBaseInfoDlg::ResetLstChanCross(int iChanCount,CLinkList<CString>& lnkDyeName)
{
	m_lstCrossParam.DeleteAllColumn(FALSE);
	if(iChanCount < 1)
	{
		m_lstCrossParam.Invalidate(FALSE);
		return -1;
	}

	CMaxMinInfo maxMinInfo;
	maxMinInfo.SetBeOnlyFloatNumber(TRUE);
	maxMinInfo.SetBeSetMinValue(TRUE);
	maxMinInfo.SetMinValue(0);
	maxMinInfo.SetBeSetMaxValue(TRUE);
	maxMinInfo.SetMaxValue(1);
	maxMinInfo.SetBeMaxMinSimultaneousEffect(TRUE);
	
	int iLnkSize = lnkDyeName.GetSize();

	CString strTemp(_T(""));
	m_lstCrossParam.InsertColumn(0,theApp.m_pLangInfo->GetText(112));
	for(int i = 0;i < iChanCount;++i)
	{
		if(i < iLnkSize)
		{
			strTemp = *lnkDyeName[i];
		}
		else
		{
			strTemp.Format(_T("%d"),i + 1);
		}
		
		m_lstCrossParam.InsertColumn(i + 1,strTemp);
		m_lstCrossParam.SetColumnEditable(i + 1,TRUE);
		m_lstCrossParam.SetColumnMaxMinInfo(i + 1,maxMinInfo);
	}

	int iWidth = 684 * m_dHoriRatio;
	int iTempInt = 136 * m_dHoriRatio;
	if(iChanCount > 0)
	{
		iTempInt = iWidth / (iChanCount + 1);
	}
	for(int i = 0;i < iChanCount + 1;++i)
	{
		if(i == iChanCount)
		{
			iWidth -= m_lstCrossParam.GetFrameLineWidth() * 2;
			m_lstCrossParam.SetColumnWidth(i,iWidth);
		}
		else
		{
			m_lstCrossParam.SetColumnWidth(i,iTempInt);
			iWidth -= iTempInt;
		}
	}

	for(int i = 0;i < iChanCount;++i)
	{
		m_lstCrossParam.InsertRow(i,FALSE);

		if(i < iLnkSize)
		{
			strTemp = *lnkDyeName[i];
		}
		else
		{
			strTemp.Format(_T("%d"),i + 1);
		}
		
		m_lstCrossParam.SetItemText(i,0,strTemp);
		m_lstCrossParam.SetCellDisableState(i,i + 1,TRUE);
	}

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::ResetLstCrossOneChannelName
// 作用：更新或清除ResetLstCrossOneChannelName。
// 参数：iChanId：整数；strDye：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetRowNum、GetColNum、SetItemText、SetColumnText。
int CPrjManageBaseInfoDlg::ResetLstCrossOneChannelName(int iChanId,CString strDye)
{
	int iRowNum = m_lstCrossParam.GetRowNum();
	int iColNum = m_lstCrossParam.GetColNum();
	if(iRowNum < 1)
	{
		return -1;
	}
	if(iColNum < 2)
	{
		return -2;
	}

	if(iRowNum != iColNum - 1)
	{
		return -3;
	}

	if(iChanId < 0)
	{
		return -4;
	}

	if(iChanId >= iRowNum)
	{
		return -5;
	}

	m_lstCrossParam.SetItemText(iChanId,0,strDye);
	m_lstCrossParam.SetColumnText(iChanId + 1,strDye,TRUE);

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetPrjInfoBaseInfo
// 作用：设置SetPrjInfoBaseInfo。
// 参数：reagentItem。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 strTemp、_T、SetText、GetName、SetCurSel、GetType。
int CPrjManageBaseInfoDlg::SetPrjInfoBaseInfo(CReagentItem& reagentItem)
{
	CString strTemp(_T(""));

	m_prjBaseInfoDlg.m_edPrjName.SetText(reagentItem.GetName());
	m_prjBaseInfoDlg.m_cbPrjType.SetCurSel(reagentItem.GetType(),TRUE,TRUE);
	strTemp.Format(_T("%d"),reagentItem.GetReactVolume());
	m_prjBaseInfoDlg.m_edReactSystem.SetText(strTemp);
	m_prjBaseInfoDlg.m_edUnit.SetText(reagentItem.GetUnit());

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::GetPrjInfoBaseInfo
// 作用：读取GetPrjInfoBaseInfo。
// 参数：reagentItem。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 strTemp、_T、SetName、GetText、SetType、GetCurSel。
int CPrjManageBaseInfoDlg::GetPrjInfoBaseInfo(CReagentItem& reagentItem)
{
	CString strTemp(_T(""));
	reagentItem.SetName(m_prjBaseInfoDlg.m_edPrjName.GetText());
	reagentItem.SetType((eExperimentType)(m_prjBaseInfoDlg.m_cbPrjType.GetCurSel()));
	reagentItem.SetReactVolume(_ttoi(m_prjBaseInfoDlg.m_edReactSystem.GetText()));
	reagentItem.SetUnit(m_prjBaseInfoDlg.m_edUnit.GetText());

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetChanTargetInfo
// 作用：设置SetChanTargetInfo。
// 参数：reagentItem。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Clear、GetChannelTargetCount、Invalidate、strTemp、_T、GetColNum。
int CPrjManageBaseInfoDlg::SetChanTargetInfo(CReagentItem& reagentItem)
{
	m_lstChanSet.Clear();

	int iChanTargetCount = reagentItem.GetChannelTargetCount();
	if(iChanTargetCount < 1)
	{
		m_lstChanSet.Invalidate(FALSE);
		return - 1;
	}

	CString strTemp(_T(""));

	if(m_lstChanSet.GetColNum() > 0)
	{
		m_lstChanSet.DeleteAllColumn(FALSE);
	}

	m_lstChanSet.InsertColumn(0,theApp.m_pLangInfo->GetText(111));
	m_lstChanSet.InsertColumn(1,theApp.m_pLangInfo->GetText(447));

	for(int i = 0;i < iChanTargetCount;++i)
	{
		strTemp.Format(_T("%d"),i + 1);
		m_lstChanSet.InsertColumn(i + 2,strTemp);
		m_lstChanSet.SetColumnBeTellParentCellChanged(i + 2,TRUE);
	}

	SetLstChanTargetColumnWidth(iChanTargetCount);

	for(int i = 0;i < 4;++i)
	{
		m_lstChanSet.InsertRowSetHeight(i,37 * m_dVertRatio);
		strTemp.Format(_T("%d"),i + 1);
		m_lstChanSet.SetItemText(i,0,strTemp);
	}

	////新增两行用于输入阴阳性阈值,20220609，孙文郎
	//for(int i = 4;i <= 5;++i)
	//{
	//	m_lstChanSet.InsertRowSetHeight(i,37 * m_dVertRatio);
	//	strTemp.Format(_T("%d"),i + 1);
	//	m_lstChanSet.SetItemText(i,0,strTemp);
	//}
	//m_lstChanSet.SetItemText(4,1,theApp.m_pLangInfo->GetText(279));
	//m_lstChanSet.SetItemText(5,1,theApp.m_pLangInfo->GetText(280));

	CLinkList<CLinkList<CString>> totalLnkCbStr;
	CLinkList<CString> lnkCbStr;
	strTemp = (_T("SYBR"));
	lnkCbStr.AddTail(strTemp);
	strTemp = (_T("FAM"));
	lnkCbStr.AddTail(strTemp);
	totalLnkCbStr.AddTail(lnkCbStr);
	lnkCbStr.Clear();
	strTemp = (_T("Cy5"));
	lnkCbStr.AddTail(strTemp);
	totalLnkCbStr.AddTail(lnkCbStr);
	lnkCbStr.Clear();
	strTemp = (_T("JOE"));
	lnkCbStr.AddTail(strTemp);
	strTemp = (_T("TET"));
	lnkCbStr.AddTail(strTemp);
	strTemp = (_T("HEX"));
	lnkCbStr.AddTail(strTemp);
	strTemp = (_T("VIC"));
	lnkCbStr.AddTail(strTemp);
	totalLnkCbStr.AddTail(lnkCbStr);

#ifdef PS96INSTRUMENT
	lnkCbStr.Clear();
	strTemp = (_T("Cy5.5"));
	lnkCbStr.AddTail(strTemp);
	totalLnkCbStr.AddTail(lnkCbStr);
#endif

	lnkCbStr.Clear();
	strTemp = (_T("ROX"));
	lnkCbStr.AddTail(strTemp);
#ifdef PS96INSTRUMENT
	strTemp = (_T("Texas Red"));
	lnkCbStr.AddTail(strTemp);
#endif
	totalLnkCbStr.AddTail(lnkCbStr);

	for(int i = 0;i < iChanTargetCount;++i)
	{
		if(i < totalLnkCbStr.GetSize())
		{
			m_lstChanSet.SetCellSelfCbInfo(1,i + 2,TRUE,TRUE,*totalLnkCbStr[i],FALSE);
		}
		m_lstChanSet.SetCellCheckFunc(2,i + 2,TRUE);
		m_lstChanSet.SetCellEditable(3,i + 2,TRUE);
		m_lstChanSet.SetCellEditable(4,i + 2,TRUE);
		m_lstChanSet.SetCellEditable(5,i + 2,TRUE);
	}

	m_lstChanSet.SetItemText(0,1,theApp.m_pLangInfo->GetText(106));
	m_lstChanSet.SetItemText(1,1,theApp.m_pLangInfo->GetText(107));
	m_lstChanSet.SetItemText(2,1,theApp.m_pLangInfo->GetText(108));
	m_lstChanSet.SetItemText(3,1,theApp.m_pLangInfo->GetText(53));

	for(int i = 0;i < iChanTargetCount;++i)
	{
		CItemChannelInfo* pItemChanInfo = reagentItem.GetChannelTargetBy(i); 

		strTemp.Format(_T("%d-%d"),pItemChanInfo->GetExWavelength(),pItemChanInfo->GetEmWavelength());
		m_lstChanSet.SetItemText(0,i + 2,strTemp);

		m_lstChanSet.SetItemText(1,i + 2,pItemChanInfo->GetDyeName());
		m_lstChanSet.SetCellCheckState(2,i + 2,pItemChanInfo->GetUse());

		if(pItemChanInfo->GetTargetCount() > 0)
		{
			m_lstChanSet.SetItemText(3,i + 2,pItemChanInfo->GetTargetName(0));
		}

		//strTemp.Format(_T("%.2lf"),pItemChanInfo->GetNegPosDownLimit());
		//m_lstChanSet.SetItemText(4,i + 2,strTemp);
		//strTemp.Format(_T("%.2lf"),pItemChanInfo->GetNegPosUpLimit());
		//m_lstChanSet.SetItemText(5,i + 2,strTemp);
	}

	m_lstChanSet.BottomBlankSetAutoFitHeight();
	m_lstChanSet.Invalidate(FALSE);

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::GetChanTargetInfo
// 作用：读取GetChanTargetInfo。
// 参数：reagentItem。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetRowNum、GetChannelTargetCount、strTemp、_T、GetChannelTargetBy、SetDyeName。
int CPrjManageBaseInfoDlg::GetChanTargetInfo(CReagentItem& reagentItem)
{
	int iRowNum = m_lstChanSet.GetRowNum();

	int iChanTargetCount = reagentItem.GetChannelTargetCount();
	if(iChanTargetCount < 1)
	{
		return -1;
	}

	CString strTemp(_T(""));
	CItemChannelInfo* pItemChanInfo = NULL;
	for(int i = 0;i < iChanTargetCount;++i)
	{
		pItemChanInfo = reagentItem.GetChannelTargetBy(i); 
		if(NULL == pItemChanInfo)
		{
			continue;
		}

		pItemChanInfo->SetDyeName(m_lstChanSet.GetItemText(1,i + 2));
		BOOL bChecked = FALSE;
		m_lstChanSet.GetCellCheckState(2,i + 2,bChecked);
		pItemChanInfo->SetUse(bChecked); 

		strTemp = m_lstChanSet.GetItemText(3,i + 2);
		if(pItemChanInfo->GetTargetCount() > 0)
		{
			pItemChanInfo->SetTargetName(0,strTemp);
		}
		else
		{
			pItemChanInfo->AddTarget(strTemp);
		}

		//pItemChanInfo->SetNegPosDownLimit(_ttof(m_lstChanSet.GetItemText(4,i + 2)));
		//pItemChanInfo->SetNegPosUpLimit(_ttof(m_lstChanSet.GetItemText(5,i + 2)));
	}

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetLstAmlAnaBaseParam
// 作用：设置SetLstAmlAnaBaseParam。
// 参数：pAnalysisPara：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Clear、Invalidate、GetAmplifyParaCount、GetArrayAmplifyParaPtr、GetAt、InsertRow。
int CPrjManageBaseInfoDlg::SetLstAmlAnaBaseParam(CDataAnalysisPara* pAnalysisPara)
{
	m_lstAmlBaseParam.Clear();

	if(NULL == pAnalysisPara)
	{
		m_lstAmlBaseParam.Invalidate(FALSE);
		return -1;
	}

	int iAmpParamCount = pAnalysisPara->GetAmplifyParaCount();
	for(int i = 0;i < iAmpParamCount;++i)
	{
		CPtrArray* pAryAmpParam = pAnalysisPara->GetArrayAmplifyParaPtr();
		tagAnaAmplifyPara* pAnaAmpParam = (tagAnaAmplifyPara*)pAryAmpParam->GetAt(i);
		if(NULL == pAnaAmpParam)
		{
			continue;
		}

		m_lstAmlBaseParam.InsertRow(i);
		SetOneAmlBaseParam(i, pAnaAmpParam);
	}

	m_lstAmlBaseParam.SetAllRowHeight(int(30 * m_dVertRatio));
	//ResetAmlListColumnWidth();
	//m_lstAmlBaseParam.Invalidate(FALSE);
	ResetAmlListChannelArray();
	m_lstAmlBaseParam.Invalidate();

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetOneAmlBaseParam
// 作用：设置SetOneAmlBaseParam。
// 参数：iRowIndex：整数；pInputParam：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 tempStr、_T、Format、SetItemText、SetCellCheckState。
void CPrjManageBaseInfoDlg::SetOneAmlBaseParam(int iRowIndex, tagAnaAmplifyPara* pInputParam)
{
	CString tempStr(_T(""));

	tempStr.Format(_T("%d"),iRowIndex + 1);
	m_lstAmlBaseParam.SetItemText(iRowIndex,0,tempStr);

	m_lstAmlBaseParam.SetItemText(iRowIndex,1,pInputParam->strDye);
	m_lstAmlBaseParam.SetItemText(iRowIndex,2,pInputParam->strTarget);

	m_lstAmlBaseParam.SetCellCheckState(iRowIndex,3,pInputParam->bAutoBaseline);

	tempStr.Format(_T("%d"),pInputParam->iBaselineStart);
	m_lstAmlBaseParam.SetItemText(iRowIndex,4,tempStr);
	tempStr.Format(_T("%d"),pInputParam->iBaselineEnd);
	m_lstAmlBaseParam.SetItemText(iRowIndex,5,tempStr);

	m_lstAmlBaseParam.SetCellCheckState(iRowIndex,6,SPLINE_THRESHOLD_AUTO == pInputParam->nThresholdType);
	tempStr.Format(_T("%.2lf"),pInputParam->dNormalizeThreshold);
	m_lstAmlBaseParam.SetItemText(iRowIndex,7,tempStr);
	tempStr.Format(_T("%.2lf"),pInputParam->dDeltaRnThreshold);
	m_lstAmlBaseParam.SetItemText(iRowIndex,8,tempStr);

	tempStr.Format(_T("%.2lf"), pInputParam->dLowerThreshold);
	m_lstAmlBaseParam.SetItemText(iRowIndex, 9,tempStr);
	tempStr.Format(_T("%.2lf"), pInputParam->dUpperThreshold);
	m_lstAmlBaseParam.SetItemText(iRowIndex, 10,tempStr);
}


// 函数 CPrjManageBaseInfoDlg::GetLstAmlAnaBaseParam
// 作用：读取GetLstAmlAnaBaseParam。
// 参数：pAnalysisPara：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetRowNum、SetAmplifyParaCount、strTemp、_T、GetAmplifyParaBy、GetItemText。
int CPrjManageBaseInfoDlg::GetLstAmlAnaBaseParam(CDataAnalysisPara* pAnalysisPara)
{
	if(NULL == pAnalysisPara)
	{
		return -1;
	}

	int iRowNum = m_lstAmlBaseParam.GetRowNum();
	if(pAnalysisPara->SetAmplifyParaCount(iRowNum) < 0)
	{
		return -2;
	}

	if(iRowNum < 1)
	{
		return 1;
	}

	CString strTemp(_T(""));
	tagAnaAmplifyPara* pAnaAmpParam = NULL;
	for(int i = 0;i < iRowNum;++i)
	{
		pAnaAmpParam = pAnalysisPara->GetAmplifyParaBy(i);

		pAnaAmpParam->strDye = m_lstAmlBaseParam.GetItemText(i,1);
		pAnaAmpParam->strTarget = m_lstAmlBaseParam.GetItemText(i,2);

		m_lstAmlBaseParam.GetCellCheckState(i,3,pAnaAmpParam->bAutoBaseline);
		pAnaAmpParam->iBaselineStart = _ttoi(m_lstAmlBaseParam.GetItemText(i,4));
		pAnaAmpParam->iBaselineEnd = _ttoi(m_lstAmlBaseParam.GetItemText(i,5));

		BOOL bChecked = FALSE;
		m_lstAmlBaseParam.GetCellCheckState(i,6,bChecked);
		if(bChecked)
		{
			pAnaAmpParam->nThresholdType = SPLINE_THRESHOLD_AUTO;
		}
		else
		{
			pAnaAmpParam->nThresholdType = SPLINE_THRESHOLD_NORMALIZE;
		}

		pAnaAmpParam->dNormalizeThreshold = _ttof(m_lstAmlBaseParam.GetItemText(i,7));
		pAnaAmpParam->dDeltaRnThreshold = _ttof(m_lstAmlBaseParam.GetItemText(i,8));

		pAnaAmpParam->dLowerThreshold = _ttof(m_lstAmlBaseParam.GetItemText(i,9));
		pAnaAmpParam->dUpperThreshold = _ttof(m_lstAmlBaseParam.GetItemText(i,10));

	}

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetLstMeltParam
// 作用：设置SetLstMeltParam。
// 参数：pAnalysisPara：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Clear、Invalidate、tempStr、_T、GetMeltCurveParaCount、GetArrayMeltCurveParaPtr。
int CPrjManageBaseInfoDlg::SetLstMeltParam(CDataAnalysisPara* pAnalysisPara)
{
	m_lstMeltParam.Clear();

	if(NULL == pAnalysisPara)
	{
		m_lstMeltParam.Invalidate(FALSE);
		return -1;
	}

	CString tempStr(_T(""));
	int iMeltParamCount = pAnalysisPara->GetMeltCurveParaCount();
	for(int i = 0;i < iMeltParamCount;++i)
	{
		CPtrArray* pAryMeltCrvParam = pAnalysisPara->GetArrayMeltCurveParaPtr();
		tagAnaMeltCurvePara* pAnaMeltCrvParam = (tagAnaMeltCurvePara*)pAryMeltCrvParam->GetAt(i); 
		if(NULL == pAnaMeltCrvParam)
		{
			continue;
		}

		m_lstMeltParam.InsertRow(i);

		tempStr.Format(_T("%d"),i + 1);
		m_lstMeltParam.SetItemText(i,0,tempStr);

		m_lstMeltParam.SetItemText(i,1,pAnaMeltCrvParam->strDye);
		m_lstMeltParam.SetItemText(i,2,pAnaMeltCrvParam->strTarget);

		tempStr.Format(_T("%.2lf"),pAnaMeltCrvParam->dMinTemp);
		m_lstMeltParam.SetItemText(i,3,tempStr);
		tempStr.Format(_T("%.2lf"),pAnaMeltCrvParam->dMaxTemp);
		m_lstMeltParam.SetItemText(i,4,tempStr);
		tempStr.Format(_T("%.2lf"),pAnaMeltCrvParam->dThreshold);
		m_lstMeltParam.SetItemText(i,5,tempStr);
	}

	m_lstMeltParam.BottomBlankSetAutoFitHeight();
	m_lstMeltParam.Invalidate(FALSE);

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::GetLstMeltParam
// 作用：读取GetLstMeltParam。
// 参数：pAnalysisPara：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetRowNum、SetMeltCurveParaCount、strTemp、_T、GetMeltCurveParaBy、GetItemText。
int CPrjManageBaseInfoDlg::GetLstMeltParam(CDataAnalysisPara* pAnalysisPara)
{
	if(NULL == pAnalysisPara)
	{
		return -1;
	}

	int iRowNum = m_lstMeltParam.GetRowNum();
	if(pAnalysisPara->SetMeltCurveParaCount(iRowNum) < 0)
	{
		return -2;
	}

	if(iRowNum < 1)
	{
		return 1;
	}

	CString strTemp(_T(""));
	tagAnaMeltCurvePara* pAnaMeltCrvParam = NULL;
	for(int i = 0;i < iRowNum;++i)
	{
		pAnaMeltCrvParam = pAnalysisPara->GetMeltCurveParaBy(i); 
		if(NULL == pAnaMeltCrvParam)
		{
			continue;
		}

		pAnaMeltCrvParam->strDye = m_lstMeltParam.GetItemText(i,1);
		pAnaMeltCrvParam->strTarget = m_lstMeltParam.GetItemText(i,2);
		
		pAnaMeltCrvParam->dMinTemp = _ttof(m_lstMeltParam.GetItemText(i,3));
		pAnaMeltCrvParam->dMaxTemp = _ttof(m_lstMeltParam.GetItemText(i,4));
		pAnaMeltCrvParam->dThreshold = _ttof(m_lstMeltParam.GetItemText(i,5));
	}
	
	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetChanCrossParam
// 作用：设置SetChanCrossParam。
// 参数：pCrosstalkPara：指针，指向调用方传入的对象；iChanCount：整数；lnkDyeName。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 ResetLstChanCross、tempStr、_T、Format、SetItemText、BottomBlankSetAutoFitHeight。
int CPrjManageBaseInfoDlg::SetChanCrossParam(double* pCrosstalkPara,int iChanCount,CLinkList<CString>& lnkDyeName)
{
	if(0 != ResetLstChanCross(iChanCount,lnkDyeName))
	{
		return -1;
	}

	if(NULL == pCrosstalkPara)
	{
		return -2;
	}

	CString tempStr(_T(""));
	for(int i = 0;i < iChanCount;++i)
	{
		for(int j = 0;j < iChanCount;++j)
		{
			tempStr.Format(_T("%.3lf"),pCrosstalkPara[i * iChanCount + j]);
			m_lstCrossParam.SetItemText(i,j + 1,tempStr);
		}
	}

	m_lstCrossParam.BottomBlankSetAutoFitHeight();
	m_lstCrossParam.Invalidate(FALSE);

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::GetChanCrossParam
// 作用：读取GetChanCrossParam。
// 参数：pCrosstalkPara：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetRowNum、_ttof、GetItemText。
int CPrjManageBaseInfoDlg::GetChanCrossParam(double* pCrosstalkPara)
{
	if(NULL == pCrosstalkPara)
	{
		return -1;
	}

	int iChanNum = m_lstCrossParam.GetRowNum();
	if(iChanNum < 1)
	{
		return -1;
	}

	for(int i = 0;i < iChanNum;++i)
	{
		for(int j = 0;j < iChanNum;++j)
		{
			pCrosstalkPara[i * iChanNum + j] = _ttof(m_lstCrossParam.GetItemText(i,j + 1));
		}
	}

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::OnBnClickedInsertSegment
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCursorPos、GetWindowRect、InsertSegment、CreatePopupMenu、AppendMenu、GetText。
void CPrjManageBaseInfoDlg::OnBnClickedInsertSegment()
{
#ifdef NEW_SEGMENT_INSERTBT
	CPoint pt;
	GetCursorPos(&pt);
	CRect rcBtInsert;
	m_btInsertSegment.GetWindowRect(&rcBtInsert);

	if(pt.x < rcBtInsert.right - RIFHTWIDTH)
	{
		m_segDlg.InsertSegment(EIS_AFTER);
	}
	else
	{
		CMenu menuMain;
		menuMain.CreatePopupMenu();

		menuMain.AppendMenu(MF_STRING,ID_MENU_INSERTSEGBEFORE2,theApp.m_pLangInfo->GetText(254));
		menuMain.AppendMenu(MF_STRING,ID_MENU_INSERTSEGAFTER2,theApp.m_pLangInfo->GetText(255));
		menuMain.AppendMenu(MF_STRING,ID_MENU_INSERTSEGLAST2,theApp.m_pLangInfo->GetText(256));


		//m_bMenuPopUped = TRUE;
		menuMain.TrackPopupMenu(TPM_RIGHTBUTTON,rcBtInsert.left,rcBtInsert.bottom,this);
		menuMain.DestroyMenu();
	}
#else
	m_segDlg.InsertSegment();
#endif
	return;
}

// 函数 CPrjManageBaseInfoDlg::OnBnClickedInsertStep
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCursorPos、GetWindowRect、InsertStep、CreatePopupMenu、AppendMenu、GetText。
void CPrjManageBaseInfoDlg::OnBnClickedInsertStep()
{
#ifdef NEW_SEGMENT_INSERTBT
	CPoint pt;
	GetCursorPos(&pt);
	CRect rcBtStep;
	m_btInsertStep.GetWindowRect(&rcBtStep);
	if(pt.x < rcBtStep.right - RIFHTWIDTH)
	{
		m_segDlg.InsertStep(EIS_AFTER);
	}
	else
	{
		CMenu menuMain;
		menuMain.CreatePopupMenu();

		menuMain.AppendMenu(MF_STRING,ID_MENU_INSERTSTEPBEFORE2,theApp.m_pLangInfo->GetText(257));
		menuMain.AppendMenu(MF_STRING,ID_MENU_INSERTSTEPAFTER2,theApp.m_pLangInfo->GetText(258));
		menuMain.AppendMenu(MF_STRING,ID_MENU_INSERTSTEPLAST2,theApp.m_pLangInfo->GetText(256));

		menuMain.TrackPopupMenu(TPM_RIGHTBUTTON,rcBtStep.left,rcBtStep.bottom,this);
		menuMain.DestroyMenu();
	}
#else
	m_segDlg.InsertStep();
#endif
	return;
}

// 函数 CPrjManageBaseInfoDlg::OnBnClickedEditStep
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、PopNormalTipInfo、GetText、GetHead、EditStep。
void CPrjManageBaseInfoDlg::OnBnClickedEditStep()
{
	CLinkList<CSegItemInfo>& lnkSegItem = m_segDlg.m_lnkSegItemInfo;

	if(lnkSegItem.GetSize() < 1)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(240));
		return;
	}

	Node<CSegItemInfo>* pNodeSegItem = lnkSegItem.GetHead();
	int segIndex = 0;
	while(NULL != pNodeSegItem)
	{
		Node<CStepItemInfo>* pNodeStepItem = pNodeSegItem->data.m_lnkStepItemInfo.GetHead();
		int stepIndex = 0;
		while(NULL != pNodeStepItem)
		{
			if(pNodeStepItem->data.m_bSel)
			{
				m_segDlg.EditStep(segIndex,stepIndex);
				return;
			}
			pNodeStepItem = pNodeStepItem->pNext;
			++stepIndex;
		}
		pNodeSegItem = pNodeSegItem->pNext;
		++segIndex;
	}

	PopNormalTipInfo(theApp.m_pLangInfo->GetText(241));
	return;
}

// 函数 CPrjManageBaseInfoDlg::OnBnClickedEditSegment
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、PopNormalTipInfo、GetText、GetHead、EditSegment。
void CPrjManageBaseInfoDlg::OnBnClickedEditSegment()
{
	CLinkList<CSegItemInfo>& lnkSegItem = m_segDlg.m_lnkSegItemInfo;

	if(lnkSegItem.GetSize() < 1)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(240));
		return;
	}

	Node<CSegItemInfo>* pNodeSegItem = lnkSegItem.GetHead();
	int segIndex = 0;
	while(NULL != pNodeSegItem)
	{
		Node<CStepItemInfo>* pNodeStepItem = pNodeSegItem->data.m_lnkStepItemInfo.GetHead();
		int stepIndex = 0;
		while(NULL != pNodeStepItem)
		{
			if(pNodeStepItem->data.m_bSel)
			{
				m_segDlg.EditSegment(segIndex);
				return;
			}
			pNodeStepItem = pNodeStepItem->pNext;
			++stepIndex;
		}
		pNodeSegItem = pNodeSegItem->pNext;
		++segIndex;
	}

	PopNormalTipInfo(theApp.m_pLangInfo->GetText(242));
	return;
}

// 函数 CPrjManageBaseInfoDlg::OnBnClickedDelete
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteSelectedItem。
void CPrjManageBaseInfoDlg::OnBnClickedDelete()
{
	m_segDlg.DeleteSelectedItem();
	return;
}

// 函数 CPrjManageBaseInfoDlg::OnFileMenuSegInsertBefore
// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertBefore。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InsertSegment。
void CPrjManageBaseInfoDlg::OnFileMenuSegInsertBefore()
{
	m_segDlg.InsertSegment(EIS_BEFORE);
}

// 函数 CPrjManageBaseInfoDlg::OnFileMenuSegInsertAfter
// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertAfter。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InsertSegment。
void CPrjManageBaseInfoDlg::OnFileMenuSegInsertAfter()
{
	m_segDlg.InsertSegment(EIS_AFTER);
}

// 函数 CPrjManageBaseInfoDlg::OnFileMenuSegInsertLast
// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertLast。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InsertSegment。
void CPrjManageBaseInfoDlg::OnFileMenuSegInsertLast()
{
	m_segDlg.InsertSegment(EIS_LAST);
}

// 函数 CPrjManageBaseInfoDlg::OnFileMenuStepInsertBefore
// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertBefore。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InsertStep。
void CPrjManageBaseInfoDlg::OnFileMenuStepInsertBefore()
{
	m_segDlg.InsertStep(EIS_BEFORE);
}

// 函数 CPrjManageBaseInfoDlg::OnFileMenuStepInsertAfter
// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertAfter。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InsertStep。
void CPrjManageBaseInfoDlg::OnFileMenuStepInsertAfter()
{
	m_segDlg.InsertStep(EIS_AFTER);
}

// 函数 CPrjManageBaseInfoDlg::OnFileMenuStepInsertLast
// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertLast。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InsertStep。
void CPrjManageBaseInfoDlg::OnFileMenuStepInsertLast()
{
	m_segDlg.InsertStep(EIS_LAST);
}

// 函数 CPrjManageBaseInfoDlg::OnMsgPrjTypeChanged
// 作用：响应 Windows 或自定义消息 OnMsgPrjTypeChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetParent、PostMessage、SetBeEditable。
LRESULT CPrjManageBaseInfoDlg::OnMsgPrjTypeChanged(WPARAM wParam,LPARAM lParam)
{
	CWnd* pParent = GetParent();
	if(NULL != pParent)
	{
		pParent->PostMessage(WM_PRJTYPECHANGED,wParam,0);
	}

	//更新熔曲分析参数列表框“是否可编辑”状态
	m_lstMeltParam.SetBeEditable(wParam,TRUE);

	return wParam;
}

// 函数 CPrjManageBaseInfoDlg::OnMsgTellParentLstCellChanged
// 作用：响应 Windows 或自定义消息 OnMsgTellParentLstCellChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetItemText、SetItemText、ResetAmlListChannelArray、ResetLstCrossOneChannelName、GetParent、GetSafeHwnd。
LRESULT CPrjManageBaseInfoDlg::OnMsgTellParentLstCellChanged(WPARAM wParam,LPARAM lParam)
{
	int iRowId = wParam;
	int iColId = lParam;

	if(3 == iRowId && iColId > 1)	//基因名改变
	{
		CString strTemp = m_lstChanSet.GetItemText(iRowId,iColId);
		m_lstAmlBaseParam.SetItemText(iColId - 2,2,strTemp,TRUE);
		m_lstMeltParam.SetItemText(iColId - 2,2,strTemp,TRUE);
	}
	else if(1 == iRowId && iColId > 1)	//通道染料名称改变
	{
		CString strTemp = m_lstChanSet.GetItemText(iRowId,iColId);
		m_lstAmlBaseParam.SetItemText(iColId - 2,1,strTemp,TRUE);
		ResetAmlListChannelArray();

		m_lstMeltParam.SetItemText(iColId - 2,1,strTemp,TRUE);

		//更新串扰信息中的染料名称
		ResetLstCrossOneChannelName(iColId - 2,strTemp);

		CWnd* pParent = GetParent();
		if(NULL != pParent->GetSafeHwnd())
		{
			m_iDyeChangeChanId = iColId - 2;
			m_strDyeChangeName = strTemp;
			pParent->PostMessage(WM_PRJ_CHANNEL_DYENAME_CHANGED,0,0);
		}

		/*CReagentItem reagentItem;
		reagentItem.DyeNameChanged(0,_T(""));*/
	}

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetReagentItem
// 作用：设置SetReagentItem。
// 参数：reagentItem。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetPrjInfoBaseInfo、SetChanTargetInfo、SetLstAmlAnaBaseParam、GetAnalysisPara、SetLstMeltParam、SetChanCrossParam。
int CPrjManageBaseInfoDlg::SetReagentItem(CReagentItem& reagentItem)
{
	SetPrjInfoBaseInfo(reagentItem);
	SetChanTargetInfo(reagentItem);

	SetLstAmlAnaBaseParam(reagentItem.GetAnalysisPara());
	SetLstMeltParam(reagentItem.GetAnalysisPara());
	SetChanCrossParam(reagentItem.GetCrosstalkPara(),reagentItem.GetSelChannelCount(),reagentItem.GetLnkDyeName());
	m_segDlg.SetSegmentInfo(reagentItem.GetSegment(),TRUE);

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::GetReagentItem
// 作用：读取GetReagentItem。
// 参数：reagentItem。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetPrjInfoBaseInfo、GetLstAmlAnaBaseParam、GetAnalysisPara、GetLstMeltParam、GetChanCrossParam、GetCrosstalkPara。
int CPrjManageBaseInfoDlg::GetReagentItem(CReagentItem& reagentItem)
{
	GetPrjInfoBaseInfo(reagentItem);
	GetLstAmlAnaBaseParam(reagentItem.GetAnalysisPara());
	GetLstMeltParam(reagentItem.GetAnalysisPara());
	GetChanCrossParam(reagentItem.GetCrosstalkPara());

	CLinkList<CSegItemInfo> lnkSegment;
	m_segDlg.GetSegmentInfo(lnkSegment);
	reagentItem.SetSegment(lnkSegment);

	GetChanTargetInfo(reagentItem);

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::SetEditState
// 作用：设置SetEditState。
// 参数：bEditable：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable。
void CPrjManageBaseInfoDlg::SetEditState(BOOL bEditable,BOOL bRedraw /*= FALSE*/)
{
	if(bEditable == m_bEditable)
	{
		return;
	}

	m_prjBaseInfoDlg.SetEditState(bEditable,bRedraw);
	m_lstAmlBaseParam.SetBeEditable(bEditable,bRedraw);
	m_lstMeltParam.SetBeEditable(bEditable,bRedraw);
	m_lstCrossParam.SetBeEditable(bEditable,bRedraw);
	m_lstChanSet.SetBeEditable(bEditable,bRedraw);
	m_bEditable = bEditable;
	return;
}

// 函数 CPrjManageBaseInfoDlg::SetNewPrjBaseInfo
// 作用：设置SetNewPrjBaseInfo。
// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
// 返回：没有返回值。
// 过程：函数里会调用 GetParent、GetSafeHwnd、GetCurSel、SetDefaultAbsoluteQuantification、SetDefaultStandardMeltingCurve。
void CPrjManageBaseInfoDlg::SetNewPrjBaseInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/)
{
	CPrjManageDlg* pPrjManageDlg = (CPrjManageDlg*)GetParent();
	if(NULL == pPrjManageDlg->GetSafeHwnd())
	{
		return;
	}

	pPrjManageDlg->SetNewPrjBaseInfo(eItemInfoType,strData,intData,dData);

	//项目中实验类型改变时，不改变默认实验流程
	return;


	/*int iIndex = m_prjBaseInfoDlg.m_cbPrjType.GetCurSel();
	if(0 == iIndex || 1 == iIndex)
	{
	m_segDlg.SetDefaultAbsoluteQuantification();
	}
	else if(2 == iIndex)
	{
	m_segDlg.SetDefaultStandardMeltingCurve();
	}

	return;*/
}

// 函数 CPrjManageBaseInfoDlg::SetPrjDyeInfo
// 作用：设置SetPrjDyeInfo。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHeadPosition、GetNext、abs、GetExWavelength、GetEmWavelength、GetExChannel。
int CPrjManageBaseInfoDlg::SetPrjDyeInfo()
{
	/*POSITION pos = theApp.m_listDyeInfo.GetHeadPosition();
	while(NULL != pos)
	{
		CDBDyeInfo* pDyeDB = theApp.m_listDyeInfo.GetNext(pos);

		BOOL bSameEx = ::abs(pDyeDB->GetExWavelength() - pChannel->iExWaveLen) < pChannel->iExRange / 2;
		BOOL bSameEm = ::abs(pDyeDB->GetEmWavelength() - pChannel->iEmWaveLen) < pChannel->iEmRange / 2;
		if(bSameEx || bSameEm)
		{
			tagDyeChannelInfo* pDye = new tagDyeChannelInfo;
			pDye->iChannel = pChannel->iExPosition; pDyeDB->GetExChannel();
			pDye->strTarget = pDyeDB->GetTarget();
			pDye->strDye = pDyeDB->GetDye();
			pDye->strQuencher = pDyeDB->GetQuencher();
			pDye->clrTarget = CPublicFun::ConverToColor(pDyeDB->GetColor());
			pDye->bDefault = pDyeDB->GetDefault();

			
		}
	}*/

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::ResetLstAmlColumnText
// 作用：更新或清除ResetLstAmlColumnText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetColumnText、GetText。
void CPrjManageBaseInfoDlg::ResetLstAmlColumnText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_lstAmlBaseParam.SetColumnText(0,pLangInfo->GetText(111));
	m_lstAmlBaseParam.SetColumnText(1,pLangInfo->GetText(112));
	m_lstAmlBaseParam.SetColumnText(2,pLangInfo->GetText(53));
	m_lstAmlBaseParam.SetColumnText(3,pLangInfo->GetText(294));
	m_lstAmlBaseParam.SetColumnText(4,pLangInfo->GetText(114));
	m_lstAmlBaseParam.SetColumnText(5,pLangInfo->GetText(115));
	m_lstAmlBaseParam.SetColumnText(6,pLangInfo->GetText(117));
	m_lstAmlBaseParam.SetColumnText(7,pLangInfo->GetText(118));
	m_lstAmlBaseParam.SetColumnText(8,pLangInfo->GetText(119));
	m_lstAmlBaseParam.SetColumnText(9,pLangInfo->GetText(279));
	m_lstAmlBaseParam.SetColumnText(10,pLangInfo->GetText(280));

	return;
}

// 函数 CPrjManageBaseInfoDlg::ResetLstMeltColumnText
// 作用：更新或清除ResetLstMeltColumnText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetColumnText、GetText。
void CPrjManageBaseInfoDlg::ResetLstMeltColumnText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_lstMeltParam.SetColumnText(0,pLangInfo->GetText(111));
	m_lstMeltParam.SetColumnText(1,pLangInfo->GetText(112));
	m_lstMeltParam.SetColumnText(2,pLangInfo->GetText(53));
	m_lstMeltParam.SetColumnText(3,pLangInfo->GetText(122));
	m_lstMeltParam.SetColumnText(4,pLangInfo->GetText(123));
	m_lstMeltParam.SetColumnText(5,pLangInfo->GetText(124));

	return;
}

// 函数 CPrjManageBaseInfoDlg::ResetLstChanSetText
// 作用：更新或清除ResetLstChanSetText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetColumnText、GetText、GetRowNum、SetItemText。
void CPrjManageBaseInfoDlg::ResetLstChanSetText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_lstChanSet.SetColumnText(0,theApp.m_pLangInfo->GetText(111));
	m_lstChanSet.SetColumnText(1,theApp.m_pLangInfo->GetText(447));

	if(m_lstChanSet.GetRowNum() >= 6)
	{
		m_lstChanSet.SetItemText(0,1,theApp.m_pLangInfo->GetText(106));
		m_lstChanSet.SetItemText(1,1,theApp.m_pLangInfo->GetText(107));
		m_lstChanSet.SetItemText(2,1,theApp.m_pLangInfo->GetText(108));
		m_lstChanSet.SetItemText(3,1,theApp.m_pLangInfo->GetText(53));
		//m_lstChanSet.SetItemText(4,1,theApp.m_pLangInfo->GetText(279));
		//m_lstChanSet.SetItemText(5,1,theApp.m_pLangInfo->GetText(280));
	}
	
	return;
}

// 函数 CPrjManageBaseInfoDlg::ResetLstCrossText
// 作用：更新或清除ResetLstCrossText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetColNum、SetColumnText、GetText。
void CPrjManageBaseInfoDlg::ResetLstCrossText()
{
	if(m_lstCrossParam.GetColNum() > 0)
	{
		m_lstCrossParam.SetColumnText(0,theApp.m_pLangInfo->GetText(51));
	}
	return;
}

// 函数 CPrjManageBaseInfoDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetMyFont、GetBeEnglish、SetWindowText、GetText、SetFuncEditCtrlFont、CorrectSegmentName。
int CPrjManageBaseInfoDlg::RefreshLanguageDisplay()
{
	SetMyFont(m_stTxFont);
	m_fontNormal.SetMyFont(m_stTxFont);

	int iFontH = 13 * m_dTxRatio;
	if(theApp.m_pLangInfo->GetBeEnglish())
	{
		iFontH = 15 * m_dTxRatio;
	}

	m_btInsertSegment.SetMyFont(m_stTxFont,iFontH);
	m_btInsertSegment.SetWindowText(theApp.m_pLangInfo->GetText(36));

	m_btInsertStep.SetMyFont(m_stTxFont,iFontH);
	m_btInsertStep.SetWindowText(theApp.m_pLangInfo->GetText(41));

	m_btEditStep.SetMyFont(m_stTxFont,iFontH);
	m_btEditStep.SetWindowText(theApp.m_pLangInfo->GetText(44));

	m_btEditSegment.SetMyFont(m_stTxFont,iFontH);
	m_btEditSegment.SetWindowText(theApp.m_pLangInfo->GetText(40));

	m_btDelete.SetMyFont(m_stTxFont,iFontH);
	m_btDelete.SetWindowText(theApp.m_pLangInfo->GetText(45));

	m_btnAddTarget.SetMyFont(m_stTxFont,iFontH);
	m_btnAddTarget.SetWindowText(theApp.m_pLangInfo->GetText(522));
	m_btnDeleteTarget.SetMyFont(m_stTxFont,iFontH);
	m_btnDeleteTarget.SetWindowText(theApp.m_pLangInfo->GetText(523));

	iFontH = 14 * m_dTxRatio;
	m_segDlg.m_fontStepTag.SetMyFont(m_stTxFont);
	m_segDlg.m_fontGeneral.SetMyFont(m_stTxFont);
	m_segDlg.m_fontSegTag.SetMyFont(m_stTxFont,iFontH,FW_BOLD);
	m_segDlg.SetFuncEditCtrlFont(m_stTxFont,iFontH);
	m_segDlg.CorrectSegmentName();
	m_segDlg.SetSegmentString(theApp.m_pLangInfo->GetText(57));
	m_segDlg.SetStepString(theApp.m_pLangInfo->GetText(58));
	m_segDlg.SetGradientString(theApp.m_pLangInfo->GetText(449));
	m_segDlg.SetColumnString(theApp.m_pLangInfo->GetText(450));
	m_segDlg.SetRangeString(theApp.m_pLangInfo->GetText(451));

	//列表框
	iFontH = 14 * m_dTxRatio;
	m_lstAmlBaseParam.SetMyHeaderFont(m_stTxFont,iFontH);
	m_lstAmlBaseParam.SetMyFont(m_stTxFont);
	ResetLstAmlColumnText();

	m_lstMeltParam.SetMyHeaderFont(m_stTxFont,iFontH);
	m_lstMeltParam.SetMyFont(m_stTxFont);
	ResetLstMeltColumnText();

	m_lstCrossParam.SetMyHeaderFont(m_stTxFont,iFontH);
	m_lstCrossParam.SetMyFont(m_stTxFont);
	ResetLstCrossText();

	m_lstChanSet.SetMyHeaderFont(m_stTxFont,iFontH);
	m_lstChanSet.SetMyFont(m_stTxFont);
	ResetLstChanSetText();
	
	m_prjBaseInfoDlg.RefreshLanguageDisplay();

	return 0;
}


// 函数 CPrjManageBaseInfoDlg::OnBnClickedAddTarget
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetRowNum、InsertRow、SetOneAmlBaseParam、BottomBlankSetAutoFitHeight、SetAllRowHeight、int。
void CPrjManageBaseInfoDlg::OnBnClickedAddTarget()
{
	tagAnaAmplifyPara sTargetParam;
	int iRowNum = m_lstAmlBaseParam.GetRowNum();	
	m_lstAmlBaseParam.InsertRow(iRowNum);
	SetOneAmlBaseParam(iRowNum, &sTargetParam);
	//m_lstAmlBaseParam.BottomBlankSetAutoFitHeight();
	m_lstAmlBaseParam.SetAllRowHeight(int(30 * m_dVertRatio));

	// ResetAmlListColumnWidth();
	ResetAmlListChannelArray();
	//m_lstAmlBaseParam.SetAllRowHeight(int(30 * m_dVertRatio));
	//m_lstAmlBaseParam.Invalidate();
}

// 函数 CPrjManageBaseInfoDlg::OnBnClickedDeleteTarget
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetSelectedRowId、size、DeleteMultiRow、GetRowNum、SetRowSelectState、strTemp。
void CPrjManageBaseInfoDlg::OnBnClickedDeleteTarget()
{
	vector<int> vecSelectedRowId = m_lstAmlBaseParam.GetSelectedRowId();
	if(vecSelectedRowId.size() < 1)
		return;

	m_lstAmlBaseParam.DeleteMultiRow(vecSelectedRowId);	//m_lstSelPrj是 行单选类型

	int iRowNum = m_lstAmlBaseParam.GetRowNum();
	if(iRowNum > vecSelectedRowId[0])
	{
		//m_lstAmlBaseParam.SetRowSelectState(vecSelectedRowId[0],TRUE);
		CString strTemp(_T(""));
		for(int i = vecSelectedRowId[0];i < iRowNum;++i)
		{
			strTemp.Format(_T("%d"),i + 1);
			m_lstAmlBaseParam.SetItemText(i,0,strTemp);
		}
	}
	else if (iRowNum > 0)
	{
		//m_lstAmlBaseParam.SetRowSelectState(iRowNum - 1,TRUE);
	}

	//int iChanTargetCount = reagentItem.GetChannelTargetCount();
	m_btnDeleteTarget.EnableWindow(FALSE);

	//ResetAmlListColumnWidth();
	//m_lstAmlBaseParam.Invalidate();
}

// 函数 CPrjManageBaseInfoDlg::OnMsgRowSelectedChange
// 作用：响应 Windows 或自定义消息 OnMsgRowSelectedChange。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSelectedRowId、size、GetColNum、EnableWindow。
LRESULT CPrjManageBaseInfoDlg::OnMsgRowSelectedChange(WPARAM wParam, LPARAM lParam)
{
	vector<int> vecSelectedRowId;
	vecSelectedRowId = m_lstAmlBaseParam.GetSelectedRowId();
	if(vecSelectedRowId.size() < 1)
	{
		return 1;
	}

	int iChanTargetCount = m_lstChanSet.GetColNum();
	m_btnDeleteTarget.EnableWindow(vecSelectedRowId[0] >= iChanTargetCount-2);

	return 0;
}

// 函数 CPrjManageBaseInfoDlg::ResetAmlListChannelArray
// 作用：更新或清除ResetAmlListChannelArray。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetColNum、GetItemText、AddTail、GetRowNum、SetCellSelfCbInfo。
void CPrjManageBaseInfoDlg::ResetAmlListChannelArray()
{
	CLinkList<CString> lnkCbStr;
	CString strTemp;

	int iChanTargetCount = m_lstChanSet.GetColNum();
	for (int i=2; i<iChanTargetCount; i++)
	{
		strTemp = m_lstChanSet.GetItemText(1, i);
		lnkCbStr.AddTail(strTemp);
	}

	int iAmlRowCount = m_lstAmlBaseParam.GetRowNum();
	for (int i=iChanTargetCount-2; i<iAmlRowCount; i++)
	{
		m_lstAmlBaseParam.SetCellSelfCbInfo(i, 1, TRUE, TRUE, lnkCbStr, FALSE);
	}
}

// 函数 CPrjManageBaseInfoDlg::IsAmlBaseParamLegal
// 作用：判断IsAmlBaseParamLegal是否成立。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetRowNum、GetItemText、IsEmpty。
int CPrjManageBaseInfoDlg::IsAmlBaseParamLegal()
{
	int iRowNum = m_lstAmlBaseParam.GetRowNum();
	for (int i=0; i<iRowNum; i++)
	{
		CString strChannel = m_lstAmlBaseParam.GetItemText(i, 1);
		if (strChannel.IsEmpty())
			return 1;

		CString strTarget = m_lstAmlBaseParam.GetItemText(i, 2);

		for (int j=i+1; j<iRowNum; j++)
		{
			CString strChannel2 = m_lstAmlBaseParam.GetItemText(j, 1);
			CString strTarget2 = m_lstAmlBaseParam.GetItemText(j, 2);

			if (strChannel == strChannel2 && strTarget == strTarget2)
				return 2;
		}
	}


	return 0;
}
