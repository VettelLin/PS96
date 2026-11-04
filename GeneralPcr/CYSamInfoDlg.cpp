// 【交接】 GeneralPcr\CYSamInfoDlg.cpp
// 作用：CYSamInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CCYSamInfoDlg、DoDataExchange、DDX_DateTimeCtrl、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_MESSAGE、END_MESSAGE_MAP。
#include "StdAfx.h"
#include "CYSamInfoDlg.h"
#include "GeneralPcr.h"

IMPLEMENT_DYNAMIC(CCYSamInfoDlg,CSamInfoDlg)

// 函数 CCYSamInfoDlg::CCYSamInfoDlg
// 作用：执行CCYSamInfoDlg。
// 参数：pParent：指针，指向调用方传入的对象；CSamInfoDlg(pParent：字符串；pIfC：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCYSamInfoDlg::CCYSamInfoDlg(CWnd* pParent /*= NULL*/,CInterfaceC* pIfC /*= NULL*/): CSamInfoDlg(pParent,pIfC)
{

}

// 函数 CCYSamInfoDlg::~CCYSamInfoDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCYSamInfoDlg::~CCYSamInfoDlg(void)
{

}

// 函数 CCYSamInfoDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 DDX_DateTimeCtrl。
void CCYSamInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CSamInfoDlg::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX,ID_CYSAMINFODLG_DT_COLLECT_DATE,m_oleCYDt);
}

BEGIN_MESSAGE_MAP(CCYSamInfoDlg,CSamInfoDlg)
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_DATECTRLCHANGED,OnMsgDateCtrlChanged) 
	ON_MESSAGE(WM_TELLPARENTTEXTCHANGED,OnMsgTellParentTextChanged) 
	ON_MESSAGE(WM_TELLPARENTSETNEWTEXT,OnMsgTellParentSetNewText)
END_MESSAGE_MAP()

// 函数 CCYSamInfoDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CCYSamInfoDlg::OnEraseBkgnd(CDC* pDC)
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

	DrawRoundRectangleNew(&memDc,rect.left,rect.top,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	int iTempInt1 = 16 * m_dHoriRatio,iTempInt2 = 122 * m_dHoriRatio;
	int iStartY = 20 * m_dVertRatio,iTempInt4 = 56 * m_dVertRatio,iTempInt5 = 40 * m_dVertRatio,iEndY = iStartY + iTempInt5;

	UINT uiTxFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;

	memDc.DrawText(pLangInfo->GetText(47),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(48),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(64),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(69),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	//康研葆专属内容
	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(403),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(404),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(405),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(406),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(407),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	iStartY += iTempInt4;
	iEndY = iStartY + iTempInt5;
	memDc.DrawText(pLangInfo->GetText(20),CRect(iTempInt1,iStartY,iTempInt2,iEndY),uiTxFormat);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	Node<CRect>* pNodeRst = m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDc,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}

	memDc.SelectObject(pOldFont);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CCYSamInfoDlg::OnMsgDateCtrlChanged
// 作用：响应 Windows 或自定义消息 OnMsgDateCtrlChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、UpdateData、strTemp、_T、Format、Left。
LRESULT CCYSamInfoDlg::OnMsgDateCtrlChanged(WPARAM wParam,LPARAM lParam)
{
	int iRet = CSamInfoDlg::OnMsgDateCtrlChanged(wParam,lParam);
	if(0 != iRet)
	{
		return iRet;
	}

	if(m_bClear)
	{
		return 1;
	}

	CMyDateTimeCtrl* pDt = NULL;
	COleDateTime* pOleDt = NULL;
	EITEMINFOTYPE eItemInfoType = (EITEMINFOTYPE)wParam;

	switch(eItemInfoType)
	{
	case ITEM_CYSAMINFO_DT_COLLECTDATE: pDt = &m_dtCYCollectDate; pOleDt = &m_oleCYDt;break;
	default: return 0;
	}

	if(NULL == pDt->GetSafeHwnd())
	{
		return 2;
	}
	if(NULL == pOleDt)
	{
		return 3;
	}

	UpdateData(TRUE);
	CString strTemp(_T(""));
	strTemp = pOleDt->Format(_T("%Y-%m-%d %H:%M:%S"));

	CString strYMD = strTemp.Left(10);
	CString strCurTime(_T(""));
	GetCurrentTmTime(strCurTime,2,_T("-"));
	if(strYMD != strCurTime)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(396));
	}

	if(NULL != m_pIfC)
	{
		m_pIfC->SetPlateSelectedSiteSamInfo(eItemInfoType,strTemp);
	}

	return 2;
}

// 函数 CCYSamInfoDlg::OnMsgTellParentTextChanged
// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、strTemp、_T、GetText、_ttoi、_ttof。
LRESULT CCYSamInfoDlg::OnMsgTellParentTextChanged(WPARAM wParam,LPARAM lParam)
{
	int iRet = CSamInfoDlg::OnMsgTellParentTextChanged(wParam,lParam);
	if(0 != iRet)
	{
		return iRet;
	}

	CMyNewEdit* pEdit = NULL;
	EITEMINFOTYPE eItemInfoType = (EITEMINFOTYPE)wParam;
	EITEMINFODATATYPE eItemInfoDataType = EIIDT_NONE;

	switch(eItemInfoType)
	{
	case ITEM_CYSAMINFO_CB_SAMCATEGORY: pEdit = &m_cbSamCategory;	eItemInfoDataType = EIIDT_STRING;	break;
	case ITEM_CYSAMINFO_ED_PRODUCTBN:	pEdit = &m_edProductBN;	eItemInfoDataType = EIIDT_STRING;	break;
	case ITEM_CYSAMINFO_ED_SAMCOUNT:	pEdit = &m_edSamCount;	eItemInfoDataType = EIIDT_STRING;	break;
	case ITEM_CYSAMINFO_ED_SAMSTATE:	pEdit = &m_edSamState;	eItemInfoDataType = EIIDT_STRING;	break;
	case ITEM_CYSAMINFO_ED_COMMENT:	pEdit = &m_edComment;	eItemInfoDataType = EIIDT_INT;	break;
	case ITEM_CYSAMINFO_ED_TESTITEM:	pEdit = &m_edTestItem;	eItemInfoDataType = EIIDT_STRING;	break;
	
	default: break;
	}

	if(NULL == pEdit->GetSafeHwnd())
	{
		return 1;
	}

	CString strTemp(_T(""));
	strTemp = pEdit->GetText();

	int iData = 0;
	double dData = 0;

	switch(eItemInfoDataType)
	{
	case EIIDT_INT:	iData = _ttoi(strTemp);	break;
	case EIIDT_DOUBLE:	dData = _ttof(strTemp);	break;
	default:	break;
	}

	if(NULL != m_pIfC)
	{
		m_pIfC->SetPlateSelectedSiteSamInfo(eItemInfoType,strTemp,iData,dData);
		return 0;
	}

	return 2;
}

// 函数 CCYSamInfoDlg::OnMsgTellParentSetNewText
// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、strTemp、_T、GetText、_ttoi、SetPlateSelectedSiteSamInfo。
LRESULT CCYSamInfoDlg::OnMsgTellParentSetNewText(WPARAM wParam,LPARAM lParam)
{
	int iRet = CSamInfoDlg::OnMsgTellParentSetNewText(wParam,lParam);
	if(0 != iRet)
	{
		return iRet;
	}

	CMyNewCb* pCb = NULL;
	EITEMINFOTYPE eItemInfoType = (EITEMINFOTYPE)wParam;
	EITEMINFODATATYPE eItemInfoDataType = EIIDT_NONE;

	switch(eItemInfoType)
	{
	case ITEM_CYSAMINFO_CB_SAMCATEGORY:	pCb = &m_cbSamCategory;	eItemInfoDataType = EIIDT_STRING;	break;

	default:	break;
	}

	if(NULL == pCb->GetSafeHwnd())
	{
		return 1;
	}

	CString strTemp(_T(""));
	strTemp = pCb->GetText();

	int iData = 0;
	double dData = 0;

	switch(eItemInfoDataType)
	{
	case EIIDT_INT:	iData = _ttoi(strTemp);	break;
	default:	break;
	}

	if(NULL != m_pIfC)
	{
		m_pIfC->SetPlateSelectedSiteSamInfo(eItemInfoType,strTemp,iData,dData);
		return 0;
	}

	return 2;
}

// 函数 CCYSamInfoDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CCYSamInfoDlg::CreateCb()
{
	CSamInfoDlg::CreateCb();

	CRect rcCreate(0,0,0,0);

	m_cbSamCategory.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_CYSAMINFODLG_CB_SAMCATEGORY);

	return;
}

// 函数 CCYSamInfoDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcTemp、Create。
void CCYSamInfoDlg::CreateEd()
{
	CSamInfoDlg::CreateEd();

	CRect rcTemp(0,0,0,0);

	m_edProductBN.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcTemp,this,ID_CYSAMINFODLG_ED_PRODUCTBN);
	m_edSamCount.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcTemp,this,ID_CYSAMINFODLG_ED_SAMCOUNT);
	m_edSamState.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcTemp,this,ID_CYSAMINFODLG_ED_SAMSTATE);

	m_edComment.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcTemp,this,ID_CYSAMINFODLG_ED_COMMENT);
	m_edTestItem.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcTemp,this,ID_CYSAMINFODLG_ED_TESTITEM);

	return;
}

// 函数 CCYSamInfoDlg::CreateDt
// 作用：创建或加入CreateDt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CCYSamInfoDlg::CreateDt()
{
	CSamInfoDlg::CreateDt();
	m_dtCYCollectDate.Create(WS_CHILD | WS_TABSTOP | DTS_SHOWNONE | DTS_SHORTDATEFORMAT,CRect(0,0,0,0),this,ID_CYSAMINFODLG_DT_COLLECT_DATE);

	return;
}

// 函数 CCYSamInfoDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitOneCb、SetTellParentSetNewText、SetTellParentTxChangedParam。
void CCYSamInfoDlg::InitCb()
{
	CSamInfoDlg::InitCb();

	InitOneCb(&m_cbSamCategory);
	m_cbSamCategory.SetTellParentSetNewText(TRUE,ITEM_CYSAMINFO_CB_SAMCATEGORY);
	m_cbSamCategory.SetTellParentTxChangedParam(TRUE,ITEM_CYSAMINFO_CB_SAMCATEGORY);

	return;
}

// 函数 CCYSamInfoDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitOneEd、SetTellParentTxChangedParam。
void CCYSamInfoDlg::InitEd()
{
	CSamInfoDlg::InitEd();

	InitOneEd(&m_edProductBN);
	m_edProductBN.SetTellParentTxChangedParam(TRUE,ITEM_CYSAMINFO_ED_PRODUCTBN);

	InitOneEd(&m_edSamCount);
	m_edSamCount.SetTellParentTxChangedParam(TRUE,ITEM_CYSAMINFO_ED_SAMCOUNT);

	InitOneEd(&m_edSamState);
	m_edSamState.SetTellParentTxChangedParam(TRUE,ITEM_CYSAMINFO_ED_SAMSTATE);

	InitOneEd(&m_edComment);
	m_edComment.SetTellParentTxChangedParam(TRUE,ITEM_CYSAMINFO_ED_COMMENT);

	InitOneEd(&m_edTestItem);
	m_edTestItem.SetTellParentTxChangedParam(TRUE,ITEM_CYSAMINFO_ED_TESTITEM);

	return;
}

// 函数 CCYSamInfoDlg::InitDt
// 作用：初始化InitDt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCurrentTime、UpdateData、SetMyFont、SetTellParentDtChangedParam。
void CCYSamInfoDlg::InitDt()
{
	CSamInfoDlg::InitDt();

	m_oleCYDt = COleDateTime::GetCurrentTime();
	UpdateData(FALSE);

	m_dtCYCollectDate.SetMyFont(m_stTxFont,16 * m_dTxRatio);
	m_dtCYCollectDate.SetTellParentDtChangedParam(TRUE,ITEM_CYSAMINFO_DT_COLLECTDATE);

	return;
}

// 函数 CCYSamInfoDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、MoveWindow、AddRectToDelete、CalcRectResult。
void CCYSamInfoDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcInit = rect;
	ClearRectToDelete();

	int iTempInt1 = 124 * m_dHoriRatio,iTempInt2 = 220 * m_dHoriRatio,iTempInt3 = 40 * m_dVertRatio;
	int iStartY = 20 * m_dVertRatio,iTempInt4 = 56 * m_dVertRatio;

	m_cbSamType.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_edSamName.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_edNewId.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_dtCYCollectDate.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_cbSamCategory.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_edSamCount.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_edSamState.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_edProductBN.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_edTestItem.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	iStartY += iTempInt4;
	m_edComment.MoveWindow(iTempInt1,iStartY,iTempInt2,iTempInt3,FALSE);
	AddRectToDelete(iTempInt1,iStartY,iTempInt2,iTempInt3);

	CalcRectResult();

	return;
}

// 函数 CCYSamInfoDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CCYSamInfoDlg::ShowCtrl()
{
	m_cbSamType.ShowWindow(SW_SHOW);
	m_edSamName.ShowWindow(SW_SHOW);
	m_edNewId.ShowWindow(SW_SHOW);

	m_dtCYCollectDate.ShowWindow(SW_SHOW);

	m_cbSamCategory.ShowWindow(SW_SHOW);
	m_edProductBN.ShowWindow(SW_SHOW);
	m_edSamCount.ShowWindow(SW_SHOW);
	m_edSamState.ShowWindow(SW_SHOW);
	m_edComment.ShowWindow(SW_SHOW);
	m_edTestItem.ShowWindow(SW_SHOW);

	return;
}

// 函数 CCYSamInfoDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CSamInfoDlg::SetCtrlText。
void CCYSamInfoDlg::SetCtrlText()
{
	CSamInfoDlg::SetCtrlText();

	return;
}

// 函数 CCYSamInfoDlg::ClearSamInfo
// 作用：更新或清除ClearSamInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CSamInfoDlg::ClearSamInfo。
void CCYSamInfoDlg::ClearSamInfo()
{
	CSamInfoDlg::ClearSamInfo();

	return;
}

// 函数 CCYSamInfoDlg::SetSamInfo
// 作用：设置SetSamInfo。
// 参数：tubeInfo。
// 返回：没有返回值。
// 过程：函数里会调用 CSamInfoDlg::SetSamInfo。
void CCYSamInfoDlg::SetSamInfo(CTubeInfo& tubeInfo)
{
	CSamInfoDlg::SetSamInfo(tubeInfo);

	return;
}

// 函数 CCYSamInfoDlg::SetEditable
// 作用：设置SetEditable。
// 参数：bEditable：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 CSamInfoDlg::SetEditable。
void CCYSamInfoDlg::SetEditable(BOOL bEditable)
{
	CSamInfoDlg::SetEditable(bEditable);

	return;
}

// 函数 CCYSamInfoDlg::GetEditable
// 作用：读取GetEditable。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CCYSamInfoDlg::GetEditable()
{
	return m_bEditable;
}

// 函数 CCYSamInfoDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetMyFont、TextParamChanged。
int CCYSamInfoDlg::RefreshLanguageDisplay()
{
	CSamInfoDlg::RefreshLanguageDisplay();

	m_cbSamCategory.SetMyFont(m_stTxFont);
	m_cbSamCategory.m_selWnd.SetMyFont(m_stTxFont);
	m_cbSamCategory.TextParamChanged();

	m_edSamCount.SetMyFont(m_stTxFont);
	m_edSamCount.TextParamChanged();

	m_edSamState.SetMyFont(m_stTxFont);
	m_edSamState.TextParamChanged();

	m_edProductBN.SetMyFont(m_stTxFont);
	m_edProductBN.TextParamChanged();

	m_edTestItem.SetMyFont(m_stTxFont);
	m_edTestItem.TextParamChanged();

	m_edComment.SetMyFont(m_stTxFont);
	m_edComment.TextParamChanged();

	m_dtCYCollectDate.SetMyFont(m_stTxFont);

	return 0;
}

// 函数 CCYSamInfoDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CSamInfoDlg::SetEditMode。
int CCYSamInfoDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	CSamInfoDlg::SetEditMode(eExpEditMode);

	m_eExpEditMode = eExpEditMode;

	return 0;
}

// 函数 CCYSamInfoDlg::SetCYSamInfo
// 作用：设置SetCYSamInfo。
// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetText、GetCYSampleCategory、GetCYSampleCount、GetCYSampleState、GetCYProductBatchNumber、GetCYTestItem。
int CCYSamInfoDlg::SetCYSamInfo(CExperimentData* pExpData,BOOL bRedraw /*= FALSE*/)
{
	if(NULL == pExpData)
	{
		return -1;
	}

	m_cbSamCategory.SetText(pExpData->GetCYSampleCategory(),bRedraw,TRUE);

	m_edSamCount.SetText(pExpData->GetCYSampleCount(),bRedraw,TRUE);
	m_edSamState.SetText(pExpData->GetCYSampleState(),bRedraw,TRUE);
	m_edProductBN.SetText(pExpData->GetCYProductBatchNumber(),bRedraw,TRUE);
	m_edTestItem.SetText(pExpData->GetCYTestItem(),bRedraw,TRUE);
	m_edComment.SetText(pExpData->GetCYComment(),bRedraw,TRUE);

	CString strDate = pExpData->GetCYCollectDate();
	if(strDate.IsEmpty())
	{
		m_oleCYDt = COleDateTime::GetCurrentTime();
	}
	else
	{
		m_oleCYDt.ParseDateTime(strDate);
	}
	UpdateData(FALSE);

	return 0;
}



