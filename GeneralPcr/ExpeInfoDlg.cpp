// 【交接】 GeneralPcr\ExpeInfoDlg.cpp
// 作用：ExpeInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CExpeInfoDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、ON_BN_CLICKED。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"
#include "ExpeInfoDlg.h"
#include "PublicInfo.h"

// CExpeInfoDlg dialog
IMPLEMENT_DYNAMIC(CExpeInfoDlg, CDialogEx)

// 函数 CExpeInfoDlg::CExpeInfoDlg
// 作用：执行CExpeInfoDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpeInfoDlg::CExpeInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExpeInfoDlg::IDD, pParent)
{
	m_bCtrlCreated = FALSE;
}

// 函数 CExpeInfoDlg::~CExpeInfoDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpeInfoDlg::~CExpeInfoDlg()
{

}

// 函数 CExpeInfoDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CExpeInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExpeInfoDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_EXPEINFODLG_BT_SELECTDIRECTORY,OnBnClickedSelectPath)
	ON_MESSAGE(WM_TELLPARENTTEXTCHANGED,OnMsgTellParentTextChanged)
END_MESSAGE_MAP()

// 函数 CExpeInfoDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CExpeInfoDlg::OnEraseBkgnd(CDC* pDC)
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
	memDC.DrawText(pLangInfo->GetText(19),CRect(48 * m_dHoriRatio,218 * m_dVertRatio,iEndX,245 * m_dVertRatio),uiTxFormat);
	memDC.DrawText(pLangInfo->GetText(20),CRect(48 * m_dHoriRatio,298 * m_dVertRatio,iEndX,325 * m_dVertRatio),uiTxFormat);

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

// 函数 CExpeInfoDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CExpeInfoDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}

	return;
}

// 函数 CExpeInfoDlg::OnBnClickedSelectPath
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、folderDlg、GetUserDataSavePath、DoModal、GetPathName、SetText。
void CExpeInfoDlg::OnBnClickedSelectPath()
{
	CPublicInfo* pInfo = CPublicInfo::GetInstance();
	CFolderPickerDialog folderDlg(pInfo->GetUserDataSavePath(),0,this,0);

	if(IDOK == folderDlg.DoModal())
	{
		CString selPath = folderDlg.GetPathName();
		m_edSavePath.SetText(selPath);
	}

	return;
}

// 函数 CExpeInfoDlg::OnMsgTellParentTextChanged
// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、strTemp、_T、GetText、GetStatus、SetExperName。
LRESULT CExpeInfoDlg::OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam)
{
	CGeneralPcrDlg* pMainDlg = (CGeneralPcrDlg*)theApp.m_pMainWnd;
	if(NULL == pMainDlg->m_workDlg.GetSafeHwnd())
	{
		return 1;
	}

	CString strTemp(_T(""));
	strTemp = m_edExpeName.GetText();

	CMiddleDlg* pMiddlgDlg = pMainDlg->m_workDlg.m_pCurSelPageDlg;
	if(NULL != pMiddlgDlg->GetSafeHwnd() && NULL != pMiddlgDlg->m_pExpData)
	{
		if(CExperimentData::STATUS_NEW == pMiddlgDlg->m_pExpData->GetStatus())
		{
			//新建的实验 实验名称和文件名称 保持一致
			pMainDlg->m_workDlg.m_fileManageDlg.SetExperName(pMainDlg->m_workDlg.m_pCurSelPageDlg->GetPageId(),strTemp);
		}
	}

	return 2;
}

// 函数 CExpeInfoDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetMyFont、CreateCtrl、InitCtrl、SetCtrlPos、SetCtrlText、ShowCtrl。
BOOL CExpeInfoDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	SetMyFont(m_stTxFont,18 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);

	CreateCtrl();
	m_bCtrlCreated = TRUE;
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();

	ShowCtrl();

	return TRUE;
}

// 函数 CExpeInfoDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateCb、CreateEd。
void CExpeInfoDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateCb();
	CreateEd();
}

// 函数 CExpeInfoDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CExpeInfoDlg::CreateBt()
{
	m_btSelectDir.Create(_T("浏览"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_EXPEINFODLG_BT_SELECTDIRECTORY);
}

// 函数 CExpeInfoDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpeInfoDlg::CreateSt()
{
	
}

// 函数 CExpeInfoDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpeInfoDlg::CreateCb()
{
	
}

// 函数 CExpeInfoDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CExpeInfoDlg::CreateEd()
{
	CRect rcCreate(0,0,0,0);

	m_edExpeName.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, rcCreate, this,ID_EXPEINFODLG_ED_EXPENAME);
	m_edSavePath.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, rcCreate, this,ID_EXPEINFODLG_ED_SAVEPATH);
	m_edRemark.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate, this,ID_EXPEINFODLG_ST_REMARK);
}

// 函数 CExpeInfoDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitCb、InitEd。
void CExpeInfoDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitCb();
	InitEd();
}

// 函数 CExpeInfoDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB。
void CExpeInfoDlg::InitBt()
{
	int iFontH = 18 * m_dTxRatio;

	m_btSelectDir.SetMyFont(m_stTxFont,iFontH);
	m_btSelectDir.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
}

// 函数 CExpeInfoDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpeInfoDlg::InitSt()
{
	
}

// 函数 CExpeInfoDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpeInfoDlg::InitCb()
{
	
}

// 函数 CExpeInfoDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitOneEd。
void CExpeInfoDlg::InitEd()
{
	int iFontH = 18 * m_dTxRatio;

	InitOneEd(&m_edExpeName);
	InitOneEd(&m_edSavePath);
	InitOneEd(&m_edRemark);

	return;
}

// 函数 CExpeInfoDlg::InitOneEd
// 作用：初始化InitOneEd。
// 参数：pEdit：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
int CExpeInfoDlg::InitOneEd(CMyNewEdit* pEdit)
{
	if(NULL == pEdit)
	{
		return -1;
	}

	int iFontH = 18 * m_dTxRatio;

	pEdit->SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	pEdit->SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	pEdit->SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	pEdit->SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	pEdit->SetMyFont(m_stTxFont,iFontH);
	pEdit->SetTellParentTxChangedParam(TRUE,0);

	return 0;
}

// 函数 CExpeInfoDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、GetBeEnglish、SetWindowPos、AddRectToDelete、CalcRectResult。
void CExpeInfoDlg::SetCtrlPos()
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

	m_btSelectDir.SetWindowPos(this,iTempInt1,211 * m_dVertRatio,80 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iTempInt1,211 * m_dVertRatio,80 * m_dHoriRatio,iTempInt2);

	m_edExpeName.SetWindowPos(this,iStartX,131 * m_dVertRatio,iTempInt4,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iStartX,131 * m_dVertRatio,iTempInt4,iTempInt2);

	m_edSavePath.SetWindowPos(this,iStartX,211 * m_dVertRatio,iTempInt4,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iStartX,211 * m_dVertRatio,iTempInt4,iTempInt2);

	m_edRemark.SetWindowPos(this,iStartX,291 * m_dVertRatio,iTempInt4,iTempInt2,SWP_NOZORDER);
	AddRectToDelete(iStartX,291 * m_dVertRatio,iTempInt4,iTempInt2);

	CalcRectResult();

	return;
}

// 函数 CExpeInfoDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CExpeInfoDlg::ShowCtrl()
{
	m_btSelectDir.ShowWindow(SW_SHOW);
	m_edExpeName.ShowWindow(SW_SHOW);
	m_edSavePath.ShowWindow(SW_SHOW);
	m_edRemark.ShowWindow(SW_SHOW);
}

// 函数 CExpeInfoDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowText、GetText。
void CExpeInfoDlg::SetCtrlText()
{
	m_btSelectDir.SetWindowText(theApp.m_pLangInfo->GetText(181));

	return;
}

// 函数 CExpeInfoDlg::GetExperiInfo
// 作用：读取GetExperiInfo。
// 参数：experiInfo。
// 返回：没有返回值。
// 过程：函数里会调用 SetExpName、GetText、SetFilePath、SetComments。
void CExpeInfoDlg::GetExperiInfo(CExperimentInfo& experiInfo)
{
	experiInfo.SetExpName(m_edExpeName.GetText());
	experiInfo.SetFilePath(m_edSavePath.GetText());
	experiInfo.SetComments(m_edRemark.GetText()) ;
}

// 函数 CExpeInfoDlg::SetExperiInfo
// 作用：设置SetExperiInfo。
// 参数：experiInfo。
// 返回：没有返回值。
// 过程：函数里会调用 SetText、GetExpName、GetFilePath、GetComments。
void CExpeInfoDlg::SetExperiInfo(CExperimentInfo& experiInfo)
{
	m_edExpeName.SetText(experiInfo.GetExpName());
	m_edSavePath.SetText(experiInfo.GetFilePath());
	m_edRemark.SetText(experiInfo.GetComments());

	return;
}

// 函数 CExpeInfoDlg::SetCtrlEnableState
// 作用：设置SetCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 EnableWindow、SetBeEditable。
void CExpeInfoDlg::SetCtrlEnableState(BOOL bEnabled)
{
	m_btSelectDir.EnableWindow(bEnabled);
	m_edExpeName.SetBeEditable(bEnabled);
	m_edSavePath.SetBeEditable(bEnabled);
	m_edRemark.SetBeEditable(bEnabled);
}

// 函数 CExpeInfoDlg::ClearPage
// 作用：更新或清除ClearPage。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetText、_T。
void CExpeInfoDlg::ClearPage()
{
	m_edExpeName.SetText(_T(""));
	m_edSavePath.SetText(_T(""));
	m_edRemark.SetText(_T(""));
}

// 函数 CExpeInfoDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetMyFont、SetWindowText、GetText、TextParamChanged。
int CExpeInfoDlg::RefreshLanguageDisplay()
{
	int iFontH = 18 * m_dTxRatio;

	SetMyFont(m_stTxFont);

	m_btSelectDir.SetMyFont(m_stTxFont,iFontH);
	m_btSelectDir.SetWindowText(theApp.m_pLangInfo->GetText(181));

	m_edExpeName.SetMyFont(m_stTxFont,iFontH);
	m_edExpeName.TextParamChanged();

	m_edSavePath.SetMyFont(m_stTxFont,iFontH);
	m_edSavePath.TextParamChanged();

	m_edRemark.SetMyFont(m_stTxFont,iFontH);
	m_edRemark.TextParamChanged();

	return 0;
}

// 函数 CExpeInfoDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetBeEditable、EnableWindow。
int CExpeInfoDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	m_eExpEditMode = eExpEditMode;

	if(EEEM_RUNNING == m_eExpEditMode)
	{
		m_edExpeName.SetBeEditable(FALSE,TRUE);
		m_edSavePath.SetBeEditable(FALSE,TRUE);
		m_edRemark.SetBeEditable(FALSE,TRUE);
		m_btSelectDir.EnableWindow(FALSE);
	}
	else if(EEEM_END == m_eExpEditMode)
	{
		m_edExpeName.SetBeEditable(TRUE,TRUE);
		m_edSavePath.SetBeEditable(TRUE,TRUE);
		m_edRemark.SetBeEditable(TRUE,TRUE);
		m_btSelectDir.EnableWindow(TRUE);
	}

	return 0;
}

// 函数 CExpeInfoDlg::GetExpName
// 作用：读取GetExpName。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetText。
CString CExpeInfoDlg::GetExpName()
{
	return m_edExpeName.GetText();
}
