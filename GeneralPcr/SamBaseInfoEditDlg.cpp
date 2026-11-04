// 【交接】 GeneralPcr\SamBaseInfoEditDlg.cpp
// 作用：SamBaseInfoEditDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CSamBaseInfoEditDlg、CDialogEx、_T、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE。
#include "StdAfx.h"
#include "SamBaseInfoEditDlg.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"
//#include "ProcSetDlg.h"
//#include "MiddleDlg.h"
//#include "TubeChanEditInfo.h"

IMPLEMENT_DYNAMIC(CSamBaseInfoEditDlg,CDialogEx)

// 函数 CSamBaseInfoEditDlg::CSamBaseInfoEditDlg
// 作用：执行CSamBaseInfoEditDlg。
// 参数：pParent：指针，指向调用方传入的对象；pInterfaceA：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CSamBaseInfoEditDlg::CSamBaseInfoEditDlg(CWnd* pParent /*= NULL*/,CInterfaceA* pInterfaceA /*= NULL*/)
	: CDialogEx(CSamBaseInfoEditDlg::IDD, pParent)
{
	m_strTitle = _T("");
	m_iWidth = 330;
	m_iHeight = 230;
	m_frameWidth = 1;
	m_roundValue = 10;
	m_iHeaderH = 40;
	m_bEditabe = TRUE;

	m_pInterfaceA = pInterfaceA;
	m_bDensityEditable = FALSE;
	m_bCtrlCreated = FALSE;
}

// 函数 CSamBaseInfoEditDlg::~CSamBaseInfoEditDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSamBaseInfoEditDlg::~CSamBaseInfoEditDlg(void)
{

}

// 函数 CSamBaseInfoEditDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CSamBaseInfoEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSamBaseInfoEditDlg,CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_TELLPARENTTEXTCHANGED,OnMsgTellParentTextChanged)
	ON_MESSAGE(WM_TELLPARENTSETNEWTEXT,OnMsgTellParentSetNewText)
	ON_MESSAGE(WM_TELLPARENTCELLCHANGED,OnMsgTellParentLstCellChanged)
	ON_MESSAGE(WM_DELETE_COMBO_ROW_STRING,OnMsgListDeleteComboRowString)
END_MESSAGE_MAP()

// 函数 CSamBaseInfoEditDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CSamBaseInfoEditDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	memDc.FillSolidRect(0,0,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);
	DrawRoundRectangleNew(&memDc,0,0,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);
	
	memDc.DrawText(pLangInfo->GetText(47),CRect(20 * m_dHoriRatio,32 * m_dVertRatio,114 * m_dHoriRatio,56 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(64),CRect(20 * m_dHoriRatio,80 * m_dVertRatio,114 * m_dHoriRatio,104 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	
	memDc.SelectObject(pOldFont);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	Node<CRect>* pNodeRst = m_rcManage.m_lnkRcRst.GetHead();
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

// 函数 CSamBaseInfoEditDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CSamBaseInfoEditDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}
	return;
}

// 函数 CSamBaseInfoEditDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PostMessage、MAKELPARAM。
void CSamBaseInfoEditDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
#ifdef POPDLG_USESHADEBK
	CDialogEx::OnLButtonDown(nFlags, point);
#else
	if(point.y < m_iHeaderH)
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

// 函数 CSamBaseInfoEditDlg::OnMsgTellParentTextChanged
// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、strTemp、_T、GetText、_ttoi、SetPlateSelectedSiteSamInfo。
LRESULT CSamBaseInfoEditDlg::OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam)
{	
	CMyNewCb* pCb = NULL;
	CMyNewEdit* pEd = NULL;
	EITEMINFOTYPE eItemInfoType = (EITEMINFOTYPE)wParam;
	EITEMINFODATATYPE eItemInfoDataType = EIIDT_NONE;

	switch(eItemInfoType)
	{
	case ITEMSAMTYPE:	pCb = &m_cbSamType;	eItemInfoDataType = EIIDT_STRING;	break;
	case ITEM_REPETITIVETUBETAG:	pCb = &m_cbRepeatTubeNumber;	eItemInfoDataType = EIIDT_INT;	break;
	case ITEMSAMID: pEd = &m_edSamId; eItemInfoDataType = EIIDT_STRING;	break;

	default:	break;
	}

	if(NULL == pCb->GetSafeHwnd() && NULL == pEd->GetSafeHwnd())
	{
		return 1;
	}

	CString strTemp(_T(""));
	if(NULL != pCb->GetSafeHwnd())
	{
		strTemp = pCb->GetText();
	}
	else if(NULL != pEd->GetSafeHwnd())
	{
		strTemp = pEd->GetText();
	}

	int iData = 0;
	double dData = 0;

	switch(eItemInfoDataType)
	{
	case EIIDT_INT:	iData = _ttoi(strTemp);	break;
	default:	break;
	}

	if(NULL != m_pInterfaceA)
	{
		m_pInterfaceA->SetPlateSelectedSiteSamInfo(eItemInfoType,strTemp,iData,dData);
		return 0;
	}

	return 2;
}

// 函数 CSamBaseInfoEditDlg::OnMsgTellParentSetNewText
// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、strTemp、_T、GetText、_ttoi、TextToSampleType。
LRESULT CSamBaseInfoEditDlg::OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam)
{
	CMyNewCb* pCb = NULL;
	CMyNewEdit* pEd = NULL;
	EITEMINFOTYPE eItemInfoType = (EITEMINFOTYPE)wParam;
	EITEMINFODATATYPE eItemInfoDataType = EIIDT_NONE;

	switch(eItemInfoType)
	{
	case ITEMSAMTYPE:	
		pCb = &m_cbSamType;	
		eItemInfoDataType = EIIDT_STRING;	
		break;
	case ITEMSAMID:	
		pEd = &m_edSamId;	
		eItemInfoDataType = EIIDT_STRING;	
		break;
	case ITEM_REPETITIVETUBETAG:	
		pCb = &m_cbRepeatTubeNumber;	
		eItemInfoDataType = EIIDT_INT;	
		break;

	default:	
		break;
	}

	if(NULL == pCb->GetSafeHwnd() && NULL == pEd->GetSafeHwnd())
	{
		return 1;
	}

	CString strTemp(_T(""));
	if(NULL != pCb->GetSafeHwnd())
	{
		strTemp = pCb->GetText();
	}
	else if(NULL != pEd->GetSafeHwnd())
	{
		strTemp = pEd->GetText();
	}

	int iData = 0;
	double dData = 0;

	switch(eItemInfoDataType)
	{
	case EIIDT_INT:	
		iData = _ttoi(strTemp);	
		break;
	default:	
		break;
	}

	//标准品、校准品样本可设置浓度信息，其它类型样本不可设置浓度信息
	if(ITEMSAMTYPE == eItemInfoType)
	{
		eSampleType eTempType = CMySamPalteDlg::TextToSampleType(strTemp);
		BOOL bDensityEditable = FALSE;
		if(SAMPLE_TYPE_STANDARD == eTempType || SAMPLE_TYPE_CALIBRATOR == eTempType)
		{
			bDensityEditable = TRUE;
		}
		if(m_bDensityEditable != bDensityEditable)
		{
			m_bDensityEditable = bDensityEditable; 
			int iRownNum = m_lstSamBaseInfo.GetRowNum();
			for(int i = 0;i < iRownNum;++i)
			{
				m_lstSamBaseInfo.SetCellDisableState(i,5,!m_bDensityEditable);
			}
			m_lstSamBaseInfo.Invalidate(FALSE);
		}
	}

	if(NULL != m_pInterfaceA)
	{
		m_pInterfaceA->SetPlateSelectedSiteSamInfo(eItemInfoType,strTemp,iData,dData);
		return 0;
	}

	return 2;
}

// 函数 CSamBaseInfoEditDlg::OnMsgTellParentLstCellChanged
// 作用：响应 Windows 或自定义消息 OnMsgTellParentLstCellChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetCellCheckState、GetItemText、GetItemColor、_ttof、GetIDPD、SetPlateSelectedSiteSamInfo。
LRESULT CSamBaseInfoEditDlg::OnMsgTellParentLstCellChanged(WPARAM wParam, LPARAM lParam)
{
	if(NULL == m_pInterfaceA)
	{
		return 1;
	}

	CTubeChanEditInfo tubeChanEditInfo;
	tubeChanEditInfo.m_iRowId = wParam;
	tubeChanEditInfo.m_iColId = lParam;

	if(0 == lParam)
	{
		m_lstSamBaseInfo.GetCellCheckState(wParam,lParam,tubeChanEditInfo.m_bChecked);
	}
	else if(2 == lParam || 3 == lParam)
	{
		tubeChanEditInfo.m_strData = m_lstSamBaseInfo.GetItemText(wParam,lParam);
	}
	else if(4 == lParam)
	{
		m_lstSamBaseInfo.GetItemColor(wParam,lParam,tubeChanEditInfo.m_clrData);
	}
	else if(5 == lParam)
	{
		CString strTemp = m_lstSamBaseInfo.GetItemText(wParam,lParam);
		tubeChanEditInfo.m_dData = _ttof(strTemp);
		tubeChanEditInfo.m_iDpd = GetIDPD(strTemp);
	}

	m_pInterfaceA->SetPlateSelectedSiteSamInfo(tubeChanEditInfo);
	
	//记录用户输入的历史基因名
	if(3 == lParam && m_lstSamBaseInfo.IsCbEndEdit())
	{
		m_lstSamBaseInfo.SetCbEndEditState(FALSE);
		int iRet = theApp.AddDefaultGeneName(tubeChanEditInfo.m_strData,TRUE);
		if(0 == iRet)
		{
			CGeneralPcrDlg* pMainDlg = (CGeneralPcrDlg*)theApp.m_pMainWnd;
			if(NULL != pMainDlg->GetSafeHwnd())
			{
				pMainDlg->SetDefaultGeneName();
			}
		}
	}

	return 0;
}

// 函数 CSamBaseInfoEditDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitDlg、CreateCtrl、InitCtrl、SetCtrlPos、ShowCtrl。
BOOL CSamBaseInfoEditDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();
	  
	InitDlg();

	CreateCtrl();
	m_bCtrlCreated = TRUE;
	InitCtrl();
	SetCtrlPos();
	ShowCtrl();

	return TRUE;
}

// 函数 CSamBaseInfoEditDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetTextClr1、RGB。
void CSamBaseInfoEditDlg::InitDlg()
{
	SetMyFont(m_stTxFont,16 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
	SetTextClr1(RGB(0X39,0X45,0X65));
}

// 函数 CSamBaseInfoEditDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateCb、CreateEd、CreateLst。
void CSamBaseInfoEditDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateCb();
	CreateEd();
	CreateLst();
}

// 函数 CSamBaseInfoEditDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSamBaseInfoEditDlg::CreateBt()
{

}

// 函数 CSamBaseInfoEditDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSamBaseInfoEditDlg::CreateSt()
{

}

// 函数 CSamBaseInfoEditDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CSamBaseInfoEditDlg::CreateCb()
{
	CRect rcCreate(0,0,0,0);

	m_cbSamType.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_SAMBASEINFODLG_CB_SAMTYPE);
	m_cbRepeatTubeNumber.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_SAMBASEINFODLG_CB_REPEATTUBENUMBER);
}

// 函数 CSamBaseInfoEditDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CSamBaseInfoEditDlg::CreateEd()
{
	m_edSamId.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_SAMBASEINFODLG_ED_SAMID);
}

// 函数 CSamBaseInfoEditDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CSamBaseInfoEditDlg::CreateLst()
{
	m_lstSamBaseInfo.Create(IDD_MIDDLEDLG,this);
}

// 函数 CSamBaseInfoEditDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitCb、InitEd、InitLst。
void CSamBaseInfoEditDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitCb();
	InitEd();
	InitLst();
}

// 函数 CSamBaseInfoEditDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSamBaseInfoEditDlg::InitBt()
{

}

// 函数 CSamBaseInfoEditDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSamBaseInfoEditDlg::InitSt()
{

}

// 函数 CSamBaseInfoEditDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
void CSamBaseInfoEditDlg::InitCb()
{
	int iFontH = 16 * m_dTxRatio;

	m_cbSamType.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_cbSamType.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_cbSamType.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_cbSamType.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_cbSamType.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbSamType.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbSamType.SetWorkState(EWS_READONLY);
	m_cbSamType.m_iRightIndent = 44 * m_dHoriRatio;
	m_cbSamType.m_arrowInfo.m_clrArrow = Color(0X39,0X45,0X65);
	m_cbSamType.m_arrowInfo.m_arrowW = 12 * m_dHoriRatio;
	m_cbSamType.m_arrowInfo.m_arrowH = 8 * m_dVertRatio;
	m_cbSamType.SetTellParentSetNewText(TRUE,ITEMSAMTYPE);

#ifdef N16USENEWSAMPLETYPE
	m_cbSamType.InsertString(0,theApp.m_pLangInfo->GetText(211));
	m_cbSamType.InsertString(1,theApp.m_pLangInfo->GetText(212));
	m_cbSamType.InsertString(2,theApp.m_pLangInfo->GetText(215));
	m_cbSamType.InsertString(3,theApp.m_pLangInfo->GetText(214));
	m_cbSamType.InsertString(4,theApp.m_pLangInfo->GetText(213));
	#ifdef CAN_YOUNG
	m_cbSamType.InsertString(5,theApp.m_pLangInfo->GetText(457));
	m_cbSamType.InsertString(6,theApp.m_pLangInfo->GetText(292));
    #else
	m_cbSamType.InsertString(5,theApp.m_pLangInfo->GetText(292));
	#endif
#else
	m_cbSamType.InsertString(0,theApp.m_pLangInfo->GetText(211));
	m_cbSamType.InsertString(1,theApp.m_pLangInfo->GetText(212));
	m_cbSamType.InsertString(2,theApp.m_pLangInfo->GetText(213));
	m_cbSamType.InsertString(3,theApp.m_pLangInfo->GetText(214));
	m_cbSamType.InsertString(4,theApp.m_pLangInfo->GetText(215));
	m_cbSamType.InsertString(5,theApp.m_pLangInfo->GetText(216));
	m_cbSamType.InsertString(6,theApp.m_pLangInfo->GetText(217));
	m_cbSamType.InsertString(7,theApp.m_pLangInfo->GetText(218));
#endif

	m_cbRepeatTubeNumber.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_cbRepeatTubeNumber.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_cbRepeatTubeNumber.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_cbRepeatTubeNumber.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_cbRepeatTubeNumber.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbRepeatTubeNumber.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbRepeatTubeNumber.m_iRightIndent = 44 * m_dHoriRatio;
	m_cbRepeatTubeNumber.m_arrowInfo.m_clrArrow = Color(0X39,0X45,0X65);
	m_cbRepeatTubeNumber.m_arrowInfo.m_arrowW = 12 * m_dHoriRatio;
	m_cbRepeatTubeNumber.m_arrowInfo.m_arrowH = 8 * m_dVertRatio;
	m_cbRepeatTubeNumber.SetTellParentTxChangedParam(TRUE,ITEM_REPETITIVETUBETAG);
	m_cbRepeatTubeNumber.SetTellParentSetNewText(TRUE,ITEM_REPETITIVETUBETAG);

	return;
}

// 函数 CSamBaseInfoEditDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
void CSamBaseInfoEditDlg::InitEd()
{
	int iFontH = 16 * m_dTxRatio;

	m_edSamId.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edSamId.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edSamId.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edSamId.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XC6,0XC6,0XC6));
	m_edSamId.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edSamId.SetTellParentTxChangedParam(TRUE,ITEMSAMID);
}

// 函数 CSamBaseInfoEditDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitLstSamBaseInfo。
void CSamBaseInfoEditDlg::InitLst()
{
	InitLstSamBaseInfo();
}

// 函数 CSamBaseInfoEditDlg::InitLstSamBaseInfo
// 作用：初始化InitLstSamBaseInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、SetHeaderHeight、SetMyHeaderFont、SetHeaderTextColor、RGB、SetMyTitleFont。
void CSamBaseInfoEditDlg::InitLstSamBaseInfo()
{
	int iFtH = 14 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		iFtH = 15 * m_dTxRatio;
	}

	m_lstSamBaseInfo.SetHeaderHeight(24 * m_dVertRatio);
	m_lstSamBaseInfo.SetMyHeaderFont(m_stTxFont,iFtH);
	m_lstSamBaseInfo.SetHeaderTextColor(RGB(0X39,0X45,0X65));
	m_lstSamBaseInfo.SetMyTitleFont(m_stTxFont,iFtH,FW_BOLD);
	m_lstSamBaseInfo.SetItemHeight(44 * m_dVertRatio);

	int iTempInt1 = 34 * m_dVertRatio;
	m_lstSamBaseInfo.m_horiScroll.m_arrowWH = iTempInt1;
	m_lstSamBaseInfo.m_horiScroll.m_scrollH = iTempInt1;
	m_lstSamBaseInfo.m_vertScroll.m_arrowWH = iTempInt1;
	m_lstSamBaseInfo.m_vertScroll.m_scrollW = iTempInt1;
	m_lstSamBaseInfo.SetMyFont(m_stTxFont,iFtH);
	m_lstSamBaseInfo.SetTextClr1(RGB(0X39,0X45,0X65));
	m_lstSamBaseInfo.SetBeShowRowSelectState(FALSE);

	m_lstSamBaseInfo.SetFuncEditCtrlFont(m_stTxFont,iFtH);

	m_lstSamBaseInfo.InsertColumn(0,theApp.m_pLangInfo->GetText(50));
	m_lstSamBaseInfo.InsertColumn(1,theApp.m_pLangInfo->GetText(51));
	m_lstSamBaseInfo.InsertColumn(2,theApp.m_pLangInfo->GetText(52));
	m_lstSamBaseInfo.InsertColumn(3,theApp.m_pLangInfo->GetText(53));
	m_lstSamBaseInfo.InsertColumn(4,theApp.m_pLangInfo->GetText(54));
	m_lstSamBaseInfo.InsertColumn(5,theApp.m_pLangInfo->GetText(55));

	m_lstSamBaseInfo.SetColumnCheckFunc(0,TRUE);
	m_lstSamBaseInfo.SetColumnCbtable(2,TRUE);
	m_lstSamBaseInfo.SetColumnCbtable(3,TRUE,TRUE);
	m_lstSamBaseInfo.SetColumnColorFunc(4,TRUE);
	m_lstSamBaseInfo.SetColumnColorEditable(4,TRUE);
	m_lstSamBaseInfo.SetColumnEditable(5,TRUE);
	CDataParam dtParam(EDT2_DOUBLE,theApp.m_iStdDensityDpd,TRUE);
	m_lstSamBaseInfo.SetColumnDataParam(5,dtParam);

	m_lstSamBaseInfo.SetColumnBeTellParentCellChanged(0,TRUE);
	m_lstSamBaseInfo.SetColumnBeTellParentCellChanged(2,TRUE);
	m_lstSamBaseInfo.SetColumnBeTellParentCellChanged(3,TRUE);
	m_lstSamBaseInfo.SetColumnBeTellParentCellChanged(4,TRUE);
	m_lstSamBaseInfo.SetColumnBeTellParentCellChanged(5,TRUE);

	int width = 499 * m_dHoriRatio;
	int tempInt = 60 * m_dHoriRatio;

	m_lstSamBaseInfo.SetColumnWidth(0,tempInt);
	width -= tempInt;
	tempInt = 68 * m_dHoriRatio;
	m_lstSamBaseInfo.SetColumnWidth(1,tempInt);
	width -= tempInt;
	tempInt = 88 * m_dHoriRatio;
	m_lstSamBaseInfo.SetColumnWidth(2,tempInt);
	width -= tempInt;
	tempInt = 96 * m_dHoriRatio;
	m_lstSamBaseInfo.SetColumnWidth(3,tempInt);
	width -= tempInt;
	tempInt = 76 * m_dHoriRatio;
	m_lstSamBaseInfo.SetColumnWidth(4,tempInt);
	width -= tempInt;
	width -= m_lstSamBaseInfo.GetFrameLineWidth() * 2;
	m_lstSamBaseInfo.SetColumnWidth(5,width);

	return;
}

// 函数 CSamBaseInfoEditDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、AddRectToDelete、SetWindowPos、CalcRectResult。
void CSamBaseInfoEditDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	m_rcManage.AddRectToDelete(120 * m_dHoriRatio,24 * m_dVertRatio,383 * m_dHoriRatio,40 * m_dVertRatio);
	m_cbSamType.SetWindowPos(this,120 * m_dHoriRatio,24 * m_dVertRatio,383 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);

	m_rcManage.AddRectToDelete(120 * m_dHoriRatio,72 * m_dVertRatio,383 * m_dHoriRatio,40 * m_dVertRatio);
	m_edSamId.SetWindowPos(this,120 * m_dHoriRatio,72 * m_dVertRatio,383 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);

	m_cbRepeatTubeNumber.SetWindowPos(this,120 * m_dHoriRatio,120 * m_dVertRatio,383 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);

	m_rcManage.AddRectToDelete(16 * m_dHoriRatio,136 * m_dVertRatio,499 * m_dHoriRatio,362 * m_dVertRatio);
	m_lstSamBaseInfo.SetWindowPos(this,16 * m_dHoriRatio,136 * m_dVertRatio,499 * m_dHoriRatio,362 * m_dVertRatio,SWP_NOZORDER);

	m_rcManage.CalcRectResult();
}

// 函数 CSamBaseInfoEditDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CSamBaseInfoEditDlg::ShowCtrl()
{
	m_cbSamType.ShowWindow(SW_SHOW);
	m_edSamId.ShowWindow(SW_SHOW);
	//m_cbRepeatTubeNumber.ShowWindow(SW_SHOW);
	m_lstSamBaseInfo.ShowWindow(SW_SHOW);
}

// 函数 CSamBaseInfoEditDlg::AddChannel
// 作用：创建或加入AddChannel。
// 参数：pDyeChanInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 strTemp、_T、GetRowNum、GetItemText、_ttoi、InsertRowSetHeight。
void CSamBaseInfoEditDlg::AddChannel(tagDyeChannelInfo* pDyeChanInfo)
{
	if(NULL == pDyeChanInfo)
	{
		return;
	}

	CString strTemp(_T(""));
	BOOL bFind = FALSE;
	int iChanId = -1,iTempRowId = -1;

	int iRowNum = m_lstSamBaseInfo.GetRowNum();
	iTempRowId = iRowNum;

	for(int i = 0;i < iRowNum;++i)
	{
		strTemp = m_lstSamBaseInfo.GetItemText(i,1);
		iChanId = _ttoi(strTemp);
		if(pDyeChanInfo->iChannel == iChanId)
		{
			bFind = TRUE;
			iTempRowId = i;
			break;
		}
	}

	if(!bFind)
	{
		m_lstSamBaseInfo.InsertRowSetHeight(iRowNum,57 * m_dVertRatio,FALSE);
		strTemp.Format(_T("%d"),pDyeChanInfo->iChannel);
		m_lstSamBaseInfo.SetItemText(iRowNum,1,strTemp);

		m_lstSamBaseInfo.SetCellSelfCbInfo(iRowNum,2,TRUE,TRUE,FALSE);
		m_lstSamBaseInfo.SetCellSelfCbInfo(iRowNum,3,TRUE,TRUE,TRUE);
		m_lstSamBaseInfo.SetCellSelCbRowDelete(iRowNum,3,TRUE);

		m_lstSamBaseInfo.SetCellDisableState(iRowNum,5,TRUE);
	}

	bFind = FALSE;
	CLinkList<CString> lnkCbStr;
	m_lstSamBaseInfo.GetCellSelfCbInfo(iTempRowId,2,lnkCbStr);
	for(int i = 0;i < lnkCbStr.GetSize();++i)
	{
		if(*lnkCbStr[i] == pDyeChanInfo->strDye)
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		lnkCbStr.AddTail(pDyeChanInfo->strDye);
		m_lstSamBaseInfo.SetCellSelfCbInfo(iTempRowId,2,lnkCbStr);
	}

	if(pDyeChanInfo->strTarget.IsEmpty())
	{
		return;
	}

	bFind = FALSE;
	m_lstSamBaseInfo.GetCellSelfCbInfo(iTempRowId,3,lnkCbStr);
	for(int i = 0;i < lnkCbStr.GetSize();++i)
	{
		if(*lnkCbStr[i] == pDyeChanInfo->strTarget)
		{
			bFind = TRUE;
			break;
		}
	}
	if(!bFind)
	{
		lnkCbStr.AddTail(pDyeChanInfo->strTarget);
		m_lstSamBaseInfo.SetCellSelfCbInfo(iTempRowId,3,lnkCbStr);
	}

	return;
}

// 函数 CSamBaseInfoEditDlg::SetDefaultGeneName
// 作用：设置SetDefaultGeneName。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 IsEmpty、strTemp、_T、AddTail、SetCellSelfCbInfo。
void CSamBaseInfoEditDlg::SetDefaultGeneName()
{
	if(theApp.m_lnkDefGN.IsEmpty())
	{
		CString strTemp(_T(""));
		CLinkList<CString> lnkCbStr;
		strTemp = _T("Actin");
		theApp.m_lnkDefGN.AddTail(strTemp);
		strTemp = _T("GAPDH");
		theApp.m_lnkDefGN.AddTail(strTemp);
	}

	m_lstSamBaseInfo.SetCellSelfCbInfo(0,3,theApp.m_lnkDefGN);
	m_lstSamBaseInfo.SetCellSelfCbInfo(1,3,theApp.m_lnkDefGN);
	m_lstSamBaseInfo.SetCellSelfCbInfo(2,3,theApp.m_lnkDefGN);
	m_lstSamBaseInfo.SetCellSelfCbInfo(3,3,theApp.m_lnkDefGN);
	m_lstSamBaseInfo.SetCellSelfCbInfo(4,3,theApp.m_lnkDefGN);

	return;
}

// 函数 CSamBaseInfoEditDlg::SetDefaultColor
// 作用：设置SetDefaultColor。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 strTemp、_T、GetRowNum、SetItemColor。
void CSamBaseInfoEditDlg::SetDefaultColor()
{
	CString strTemp(_T(""));
	COLORREF clrTemp = 0;
	int iRowNum = m_lstSamBaseInfo.GetRowNum();
	for(int i = 0;i < iRowNum;++i)
	{
		if(0 == i)
		{
			clrTemp = CHANNEL1COLOR;
		}
		else if(1 == i)
		{
			clrTemp = CHANNEL2COLOR;
		}
		else if(2 == i)
		{
			clrTemp = CHANNEL3COLOR;
		}
		else if(3 == i)
		{
			clrTemp = CHANNEL4COLOR;
		}
		else if(4 == i)
		{
			clrTemp = CHANNEL5COLOR;
		}
		m_lstSamBaseInfo.SetItemColor(i,4,clrTemp);
	}

	return;
}

// 函数 CSamBaseInfoEditDlg::SetDefaultDyeName
// 作用：设置SetDefaultDyeName。
// 参数：vecDyeName。
// 返回：没有返回值。
// 过程：函数里会调用 size、strTemp、_T、GetRowNum、SetItemText。
void CSamBaseInfoEditDlg::SetDefaultDyeName(vector<CString>& vecDyeName)
{
	int iVecSize = vecDyeName.size();
	if(iVecSize < 1)
	{
		return;
	}

	CString strTemp(_T(""));
	int iRowNum = m_lstSamBaseInfo.GetRowNum();
	for(int i = 0;i < iRowNum;++i)
	{
		if(i < iVecSize)
		{
			strTemp = vecDyeName[i];
		}
		else
		{
			strTemp = _T("");
		}

		m_lstSamBaseInfo.SetItemText(i,2,strTemp);
	}

	return;
}

// 函数 CSamBaseInfoEditDlg::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetText、_T、DeleteData。
void CSamBaseInfoEditDlg::Clear()
{
	m_cbSamType.SetText(_T(""),TRUE,TRUE);
	m_edSamId.SetText(_T(""),TRUE,TRUE);
	m_cbRepeatTubeNumber.SetText(_T(""),TRUE,TRUE);
	//m_lstSamBaseInfo.DeleteData(TRUE); 
	return; 
}

// 函数 CSamBaseInfoEditDlg::SetEditableState
// 作用：设置SetEditableState。
// 参数：bEditable：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable、SetColumnDisableState。
void CSamBaseInfoEditDlg::SetEditableState(BOOL bEditable)
{
	if(EEEM_IVD == m_eExpEditMode)
	{
#ifdef IVDALLOWCHANGECOLOR
		m_lstSamBaseInfo.SetBeEditable(bEditable);
		m_lstSamBaseInfo.SetColumnDisableState(0,TRUE);
		m_lstSamBaseInfo.SetColumnDisableState(1,TRUE);
		m_lstSamBaseInfo.SetColumnDisableState(2,TRUE);
		m_lstSamBaseInfo.SetColumnDisableState(3,TRUE);
		m_lstSamBaseInfo.SetColumnDisableState(4,!bEditable);
		m_lstSamBaseInfo.SetColumnDisableState(5,FALSE,TRUE);
#else
		m_lstSamBaseInfo.SetBeEditable(FALSE,TRUE);
#endif
	}
	else
	{
#ifdef DYE_COLOR_NEVER_DISABLE
		m_lstSamBaseInfo.SetColumnDisableState(0,!bEditable);
		m_lstSamBaseInfo.SetColumnDisableState(1,FALSE);
		m_lstSamBaseInfo.SetColumnDisableState(2,FALSE);
		m_lstSamBaseInfo.SetColumnDisableState(3,!bEditable);
		m_lstSamBaseInfo.SetColumnDisableState(4,FALSE);
		m_lstSamBaseInfo.SetColumnDisableState(5,FALSE,TRUE);
#else
		m_lstSamBaseInfo.SetBeEditable(bEditable,TRUE);
#endif
	}

	m_cbSamType.SetBeEditable(bEditable,TRUE);
	m_edSamId.SetBeEditable(bEditable,TRUE);
	m_cbRepeatTubeNumber.SetBeEditable(bEditable,TRUE);

	m_bEditabe = bEditable;
	return;
}

// 函数 CSamBaseInfoEditDlg::GetEditableState
// 作用：读取GetEditableState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSamBaseInfoEditDlg::GetEditableState()
{
	return m_bEditabe;
}

// 函数 CSamBaseInfoEditDlg::SetTubeInfo
// 作用：设置SetTubeInfo。
// 参数：info；bSetDensityEditState：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 strTemp、_T、SetCurSel、GetSampleTypeCbIndex、GetSampleType、SetText。
void CSamBaseInfoEditDlg::SetTubeInfo(CTubeInfo& info,BOOL bSetDensityEditState)
{
	CString strTemp(_T(""));
	m_cbSamType.SetCurSel(theApp.GetSampleTypeCbIndex(info.GetSampleType()),TRUE,TRUE);

	m_edSamId.SetText(info.GetSampleID(),TRUE,TRUE);
	m_cbRepeatTubeNumber.SetText(info.GetRepeatNoString(),TRUE,TRUE);

	//标准品、校准品样本可设置浓度信息，其它类型样本不可设置浓度信息
	BOOL bDensityEditable = FALSE;
	if(SAMPLE_TYPE_STANDARD == info.GetSampleType() || SAMPLE_TYPE_CALIBRATOR == info.GetSampleType())
	{
		bDensityEditable = TRUE;
	}

	//设置标准品浓度显示的小数位数
	CString strFormat(_T(""));

	int iDyeNum = info.GetTargetCount();
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < iDyeNum;++i)
	{
		pDyeTargetInfo = info.GetTargetInfo(i);
		strTemp.Format(_T("%d"),i + 1);
		m_lstSamBaseInfo.SetItemText(i,1,strTemp);
		m_lstSamBaseInfo.SetCellCheckState(i,0,pDyeTargetInfo->GetBeSelected());
		m_lstSamBaseInfo.SetItemText(i,2,pDyeTargetInfo->GetDyeName());
		m_lstSamBaseInfo.SetItemText(i,3,pDyeTargetInfo->GetTargetName());
		m_lstSamBaseInfo.SetItemColor(i,4,pDyeTargetInfo->GetTargetColor());
		strFormat.Format(_T("%%.%dlf"),pDyeTargetInfo->GetQuanIDPD());
		strTemp.Format(strFormat,pDyeTargetInfo->GetQuantity());
		m_lstSamBaseInfo.SetItemText(i,5,strTemp);
	}

	//选中多个孔位时，临时定义的CTubeInfo没有通道信息
	if(iDyeNum < 1)
	{
		int iRowNum = m_lstSamBaseInfo.GetRowNum();
		for(int i = 0;i < iRowNum;++i)
		{
			m_lstSamBaseInfo.SetCellCheckState(i,0,FALSE);
			m_lstSamBaseInfo.SetItemText(i,2,_T(""));
			m_lstSamBaseInfo.SetItemText(i,3,_T(""));
			m_lstSamBaseInfo.SetItemColor(i,4,RGB(0,0,0));
			m_lstSamBaseInfo.SetItemText(i,5,_T("0.0000"));
		}
	}

	if(bSetDensityEditState)
	{
		if(m_bDensityEditable != bDensityEditable)
		{
			m_bDensityEditable = bDensityEditable;
			for(int i = 0;i < iDyeNum;++i)
			{
				m_lstSamBaseInfo.SetCellDisableState(i,5,!m_bDensityEditable);
			}
		}
	}
	
	m_lstSamBaseInfo.Invalidate(FALSE);

	return;
}

// 函数 CSamBaseInfoEditDlg::SetDensityEditableState
// 作用：设置SetDensityEditableState。
// 参数：bEditable：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetParent、GetSafeHwnd、GetChannelCount、SetCellDisableState。
void CSamBaseInfoEditDlg::SetDensityEditableState(BOOL bEditable)
{
	if(m_bDensityEditable == bEditable)
	{
		return;
	}

	CProcSetDlg* pParent = (CProcSetDlg*)GetParent();
	if(NULL == pParent->GetSafeHwnd())
	{
		return;
	}

	if(NULL == pParent->m_pParent->GetSafeHwnd())
	{
		return;
	}
	if(NULL == pParent->m_pParent->m_pExpData)
	{
		return;
	}

	int iChanCount = pParent->m_pParent->m_pExpData->GetChannelCount();

	m_bDensityEditable = bEditable;
	for(int i = 0;i < iChanCount;++i)
	{
		m_lstSamBaseInfo.SetCellDisableState(i,5,!m_bDensityEditable);
	}
	return;
}

// 函数 CSamBaseInfoEditDlg::LstRowHeightAutoFit
// 作用：执行LstRowHeightAutoFit。
// 参数：iChanCount：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 BottomBlankSetAutoFitHeight。
int CSamBaseInfoEditDlg::LstRowHeightAutoFit(int iChanCount)
{
	if(iChanCount < 2)
	{
		return -1;
	}

	if(0 != m_lstSamBaseInfo.BottomBlankSetAutoFitHeight())
	{
		return -2;
	}

	return 0;
}

// 函数 CSamBaseInfoEditDlg::ResetLstTitle
// 作用：更新或清除ResetLstTitle。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetColumnText、GetText。
void CSamBaseInfoEditDlg::ResetLstTitle()
{
	m_lstSamBaseInfo.SetColumnText(0,theApp.m_pLangInfo->GetText(50));
	m_lstSamBaseInfo.SetColumnText(1,theApp.m_pLangInfo->GetText(51));
	m_lstSamBaseInfo.SetColumnText(2,theApp.m_pLangInfo->GetText(52));
	m_lstSamBaseInfo.SetColumnText(3,theApp.m_pLangInfo->GetText(53));
	m_lstSamBaseInfo.SetColumnText(4,theApp.m_pLangInfo->GetText(54));
	m_lstSamBaseInfo.SetColumnText(5,theApp.m_pLangInfo->GetText(55));
}

// 函数 CSamBaseInfoEditDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetMyFont、GetBeEnglish、ResetLstTitle、SetMyHeaderFont、SetMyTitleFont、SetFuncEditCtrlFont。
int CSamBaseInfoEditDlg::RefreshLanguageDisplay()
{
	SetMyFont(m_stTxFont);

	int iFontH = 14 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		iFontH = 15 * m_dTxRatio;
	}

	ResetLstTitle();
	m_lstSamBaseInfo.SetMyHeaderFont(m_stTxFont,iFontH);
	m_lstSamBaseInfo.SetMyTitleFont(m_stTxFont,iFontH);
	m_lstSamBaseInfo.SetMyFont(m_stTxFont,iFontH);
	m_lstSamBaseInfo.SetFuncEditCtrlFont(m_stTxFont,iFontH);

	m_edSamId.SetMyFont(m_stTxFont);
	m_edSamId.TextParamChanged();

	m_cbSamType.SetMyFont(m_stTxFont);
	m_cbSamType.m_selWnd.SetMyFont(m_stTxFont);
	m_cbSamType.TextParamChanged();

	int iCurSel = m_cbSamType.GetCurSel();
#ifdef N16USENEWSAMPLETYPE
	m_cbSamType.SetItemText(0,theApp.m_pLangInfo->GetText(211));
	m_cbSamType.SetItemText(1,theApp.m_pLangInfo->GetText(212));
	m_cbSamType.SetItemText(2,theApp.m_pLangInfo->GetText(215));
	m_cbSamType.SetItemText(3,theApp.m_pLangInfo->GetText(214));
	m_cbSamType.SetItemText(4,theApp.m_pLangInfo->GetText(213));
	#ifdef CAN_YOUNG
		m_cbSamType.SetItemText(5,theApp.m_pLangInfo->GetText(457));
		m_cbSamType.SetItemText(6,theApp.m_pLangInfo->GetText(292));
	#else
		m_cbSamType.SetItemText(5,theApp.m_pLangInfo->GetText(292));
	#endif
#else
	m_cbSamType.SetItemText(0,theApp.m_pLangInfo->GetText(211));
	m_cbSamType.SetItemText(1,theApp.m_pLangInfo->GetText(212));
	m_cbSamType.SetItemText(2,theApp.m_pLangInfo->GetText(213));
	m_cbSamType.SetItemText(3,theApp.m_pLangInfo->GetText(214));
	m_cbSamType.SetItemText(4,theApp.m_pLangInfo->GetText(215));
	m_cbSamType.SetItemText(5,theApp.m_pLangInfo->GetText(216));
	m_cbSamType.SetItemText(6,theApp.m_pLangInfo->GetText(217));
	m_cbSamType.SetItemText(7,theApp.m_pLangInfo->GetText(218));
#endif
	m_cbSamType.RefreshText(iCurSel);

	return 0;
}

// 函数 CSamBaseInfoEditDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetBeEditable。
int CSamBaseInfoEditDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	m_eExpEditMode = eExpEditMode;

	if(EEEM_IVD == m_eExpEditMode)
	{
		m_lstSamBaseInfo.SetBeEditable(FALSE,TRUE);
	}
	else if(EEEM_NOLIMIT == m_eExpEditMode)
	{
		m_lstSamBaseInfo.SetBeEditable(m_bEditabe,TRUE);
	}

	return 0;
}


// 函数 CSamBaseInfoEditDlg::OnMsgListDeleteComboRowString
// 作用：响应 Windows 或自定义消息 OnMsgListDeleteComboRowString。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 _T、DeleteDefaultGeneName、GetSafeHwnd、SetDefaultGeneName。
LRESULT CSamBaseInfoEditDlg::OnMsgListDeleteComboRowString(WPARAM wParam, LPARAM lParam)
{
	//AfxMessageBox(_T("删除目标项！"));
	if (2 == wParam)
	{
		ASSERT(FALSE);
	}
	else if(3 == wParam) // 删除基因名
	{
		int iRet = theApp.DeleteDefaultGeneName(lParam);
		if(0 == iRet)
		{
			CGeneralPcrDlg* pMainDlg = (CGeneralPcrDlg*)theApp.m_pMainWnd;
			if(NULL != pMainDlg->GetSafeHwnd())
			{
				pMainDlg->SetDefaultGeneName();
			}
		}
	}


	return 0;
}
