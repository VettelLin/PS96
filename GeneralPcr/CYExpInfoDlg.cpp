// 【交接】 GeneralPcr\CYExpInfoDlg.cpp
// 作用：CYExpInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CCYExpInfoDlg、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、END_MESSAGE_MAP、OnEraseBkgnd、GetInstance、GetClientRect。
#include "StdAfx.h"
#include "CYExpInfoDlg.h"
#include "GeneralPcr.h"

IMPLEMENT_DYNAMIC(CCYExpInfoDlg,CExpeInfoDlg)

// 函数 CCYExpInfoDlg::CCYExpInfoDlg
// 作用：执行CCYExpInfoDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCYExpInfoDlg::CCYExpInfoDlg(void)
{

}

// 函数 CCYExpInfoDlg::~CCYExpInfoDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCYExpInfoDlg::~CCYExpInfoDlg(void)
{

}

BEGIN_MESSAGE_MAP(CCYExpInfoDlg,CExpeInfoDlg)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// 函数 CCYExpInfoDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CCYExpInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bitMap;
	bitMap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmap = memDC.SelectObject(&bitMap);

	memDC.FillSolidRect(0,0,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);
	DrawRoundRectangleNew(&memDC,rect.left,rect.top,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);

	memDC.SetBkMode(TRANSPARENT);
	memDC.FillSolidRect(28 * m_dHoriRatio,33 * m_dVertRatio,12 * m_dHoriRatio,4 * m_dVertRatio,CLR_SOFT_THEME);
	memDC.FillSolidRect(32 * m_dHoriRatio,29 * m_dVertRatio,4 * m_dHoriRatio,12 * m_dVertRatio,CLR_SOFT_THEME);

	CFont* pOldFont = memDC.SelectObject(&m_fontSet);

	memDC.SetTextColor(CLR_SOFT_THEME);

	memDC.DrawText(pLangInfo->GetText(21),CRect(44 * m_dHoriRatio,24 * m_dVertRatio,316 * m_dHoriRatio,46 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDC.SetTextColor(RGB(0X39,0X45,0X65));

	int iEndX = 190 * m_dHoriRatio;
	if(theApp.GetBeEnglish())
	{
		iEndX += 30 * m_dHoriRatio; 
	}

	UINT uiTxFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE;

	memDC.DrawTextW(pLangInfo->GetText(7),CRect(48 * m_dHoriRatio,138 * m_dVertRatio,iEndX,165 * m_dVertRatio),uiTxFormat);
	memDC.DrawText(pLangInfo->GetText(402),CRect(48 * m_dHoriRatio,218 * m_dVertRatio,iEndX,245 * m_dVertRatio),uiTxFormat);
	memDC.DrawText(pLangInfo->GetText(19),CRect(48 * m_dHoriRatio,298 * m_dVertRatio,iEndX,325 * m_dVertRatio),uiTxFormat);
	memDC.DrawText(pLangInfo->GetText(20),CRect(48 * m_dHoriRatio,378 * m_dVertRatio,iEndX,405 * m_dVertRatio),uiTxFormat);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDC,0,0,SRCCOPY);

	Node<CRect>* pNodeRst = m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDC,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}

	memDC.SelectObject(pOldFont);

	memDC.SelectObject(pOldBitmap);
	bitMap.DeleteObject();
	memDC.DeleteDC();

	return TRUE;
}

// 函数 CCYExpInfoDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CCYExpInfoDlg::CreateEd()
{
	CExpeInfoDlg::CreateEd();

	CRect rcCreate(0,0,0,0);
	m_edReportNo.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_CYEXPEINFODLG_ED_REPORTNO);
}

// 函数 CCYExpInfoDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitOneEd。
void CCYExpInfoDlg::InitEd()
{
	CExpeInfoDlg::InitEd();
	InitOneEd(&m_edReportNo);

	return;
}

// 函数 CCYExpInfoDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、GetBeEnglish、SetWindowPos、AddRectToDelete、CalcRectResult。
void CCYExpInfoDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcInit = rect;
	ClearRectToDelete();

	int iStartX = 192 * m_dHoriRatio;
	int iTempInt1 = 688 * m_dHoriRatio;
	int iTempInt2 = 40 * m_dVertRatio;
	int iTempInt3 = 160 * m_dVertRatio;
	int iTempInt4 = 480 * m_dHoriRatio;
	if(theApp.GetBeEnglish())
	{
		iStartX += 30 * m_dHoriRatio;
		iTempInt1 += 30 * m_dHoriRatio;
	}

	m_btSelectDir.SetWindowPos(this,iTempInt1,291 * m_dVertRatio,80 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iTempInt1,291 * m_dVertRatio,80 * m_dHoriRatio,iTempInt2);

	m_edExpeName.SetWindowPos(this,iStartX,131 * m_dVertRatio,iTempInt4,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iStartX,131 * m_dVertRatio,iTempInt4,iTempInt2);

	m_edReportNo.SetWindowPos(this,iStartX,211 * m_dVertRatio,iTempInt4,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iStartX,211 * m_dVertRatio,iTempInt4,iTempInt2);

	m_edSavePath.SetWindowPos(this,iStartX,291 * m_dVertRatio,iTempInt4,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iStartX,291 * m_dVertRatio,iTempInt4,iTempInt2);

	//m_edRemark.SetWindowPos(this,iStartX,371 * m_dVertRatio,iTempInt4,iTempInt3,SWP_NOZORDER);
	//AddRectToDelete(iStartX,371 * m_dVertRatio,iTempInt4,iTempInt3);
	m_edRemark.SetWindowPos(this,iStartX,371 * m_dVertRatio,iTempInt4,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iStartX,371 * m_dVertRatio,iTempInt4,iTempInt2);

	CalcRectResult();

	return;
}

// 函数 CCYExpInfoDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CCYExpInfoDlg::ShowCtrl()
{
	CExpeInfoDlg::ShowCtrl();
	m_edReportNo.ShowWindow(SW_SHOW);

	return;
}

// 函数 CCYExpInfoDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CExpeInfoDlg::SetCtrlText。
void CCYExpInfoDlg::SetCtrlText()
{
	CExpeInfoDlg::SetCtrlText();

	return;
}

// 函数 CCYExpInfoDlg::GetExperiInfo
// 作用：读取GetExperiInfo。
// 参数：experiInfo。
// 返回：没有返回值。
// 过程：函数里会调用 SetCYReportNo、GetText。
void CCYExpInfoDlg::GetExperiInfo(CExperimentInfo& experiInfo)
{
	CExpeInfoDlg::GetExperiInfo(experiInfo);
	experiInfo.SetCYReportNo(m_edReportNo.GetText());

	return;
}

// 函数 CCYExpInfoDlg::SetExperiInfo
// 作用：设置SetExperiInfo。
// 参数：experiInfo。
// 返回：没有返回值。
// 过程：函数里会调用 SetText、GetCYReportNo。
void CCYExpInfoDlg::SetExperiInfo(CExperimentInfo& experiInfo)
{
	CExpeInfoDlg::SetExperiInfo(experiInfo);
	m_edReportNo.SetText(experiInfo.GetCYReportNo(),TRUE,TRUE);

	return;
}

// 函数 CCYExpInfoDlg::SetCtrlEnableState
// 作用：设置SetCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable。
void CCYExpInfoDlg::SetCtrlEnableState(BOOL bEnabled)
{
	CExpeInfoDlg::SetCtrlEnableState(bEnabled);
	m_edReportNo.SetBeEditable(bEnabled);

	return;
}

// 函数 CCYExpInfoDlg::ClearPage
// 作用：更新或清除ClearPage。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetText、_T。
void CCYExpInfoDlg::ClearPage()
{
	CExpeInfoDlg::ClearPage();
	m_edReportNo.SetText(_T(""));

	return;
}

// 函数 CCYExpInfoDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetMyFont、TextParamChanged。
int CCYExpInfoDlg::RefreshLanguageDisplay()
{
	CExpeInfoDlg::RefreshLanguageDisplay();

	m_edReportNo.SetMyFont(m_stTxFont);
	m_edReportNo.TextParamChanged();

	return 0;
}

// 函数 CCYExpInfoDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetBeEditable。
int CCYExpInfoDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	m_eExpEditMode = eExpEditMode;

	CExpeInfoDlg::SetEditMode(eExpEditMode);

	if(EEEM_RUNNING == m_eExpEditMode)
	{
		m_edReportNo.SetBeEditable(FALSE,TRUE);
	}
	else if(EEEM_END == m_eExpEditMode)
	{
		m_edReportNo.SetBeEditable(TRUE,TRUE);
	}

	return 0;
}


