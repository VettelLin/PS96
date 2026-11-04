// 【交接】 GeneralPcr\PrjBaseInfoDlg.cpp
// 作用：PrjBaseInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CPrjBaseInfoDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、ON_MESSAGE。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"
#include "PrjBaseInfoDlg.h"

// CPrjBaseInfoDlg dialog
IMPLEMENT_DYNAMIC(CPrjBaseInfoDlg, CDialogEx)

// 函数 CPrjBaseInfoDlg::CPrjBaseInfoDlg
// 作用：执行CPrjBaseInfoDlg。
// 参数：bPrjManage：是或否；pParent：指针，指向调用方传入的对象；pInterfaceB：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPrjBaseInfoDlg::CPrjBaseInfoDlg(BOOL bPrjManage /*= FALSE*/,CWnd* pParent /*=NULL*/,CInterfaceB* pInterfaceB /*= NULL*/)
	: CDialogEx(CPrjBaseInfoDlg::IDD, pParent)
{
	m_bPrjMange = bPrjManage;
	m_bCtrlCreated = FALSE;
	m_pInterfaceB = pInterfaceB;
}

// 函数 CPrjBaseInfoDlg::~CPrjBaseInfoDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPrjBaseInfoDlg::~CPrjBaseInfoDlg()
{

}

// 函数 CPrjBaseInfoDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CPrjBaseInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPrjBaseInfoDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_MESSAGE(WM_TELLPARENTTEXTCHANGED,OnMsgTellParentTextChanged)
	ON_MESSAGE(WM_TELLPARENTSETNEWTEXT,OnMsgTellParentSetNewText)
END_MESSAGE_MAP()

// 函数 CPrjBaseInfoDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、str1、_T、str2、str3、str4。
BOOL CPrjBaseInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	CString str1(_T("项目名称")),str2(_T("项目类型")),str3(_T("反应体系")),str4(_T("单位"));
	str1 = pLangInfo->GetText(30);
	str2 = pLangInfo->GetText(31);
	str3 = pLangInfo->GetText(32);
	str4 = pLangInfo->GetText(34);

	CRect rect; 
	GetClientRect(&rect);
	pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	CFont* pOldFont = pDC->SelectObject(&m_fontSet);
	pDC->SetTextColor(m_txClr1);
	pDC->SetBkMode(TRANSPARENT);

	pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);
	DrawRoundRectangleNew(pDC,0,0,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);

	int iHoriSpace = int(10 * m_dHoriRatio);
	int iStcWidth = int(120 * m_dHoriRatio);
	int iUnitWdith = int(20 * m_dHoriRatio);
	int iUnitStartX = rect.Width()-iHoriSpace-iUnitWdith;

	DWORD dwFormat = DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;

	if(m_bPrjMange)
	{
		pDC->DrawText(str1,CRect(iHoriSpace,int(20 * m_dVertRatio),iStcWidth, int(60 * m_dVertRatio)),dwFormat);
		pDC->DrawText(str2,CRect(iHoriSpace,int(72 * m_dVertRatio),iStcWidth, int(112 * m_dVertRatio)),dwFormat);
		pDC->DrawText(str3,CRect(iHoriSpace,124 * m_dVertRatio,iStcWidth, int(164 * m_dVertRatio)),dwFormat);
		pDC->DrawText(_T("ul"),CRect(iUnitStartX, int(124 * m_dVertRatio), iUnitStartX+iUnitWdith, int(164 * m_dVertRatio)),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		pDC->DrawText(str1,CRect(iHoriSpace,int(30 * m_dVertRatio),iStcWidth,int(54 * m_dVertRatio)),dwFormat);
		pDC->DrawText(str2,CRect(iHoriSpace,int(86 * m_dVertRatio),iStcWidth,int(110 * m_dVertRatio)),dwFormat);
		pDC->DrawText(str3,CRect(iHoriSpace,int(134 * m_dVertRatio),iStcWidth,int(174 * m_dVertRatio)),dwFormat);
		pDC->DrawText(_T("ul"),CRect(iUnitStartX,int(134 * m_dVertRatio),iUnitStartX+iUnitWdith, int(174 * m_dVertRatio)),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}

#ifndef HIDE_PROJECTUNIT

	#ifdef HIDE_PROJECTTYPE
		if(m_bPrjMange)
		{
			pDC->DrawText(str4,CRect(iTempInt1,124 * m_dVertRatio,iTempInt2,164 * m_dVertRatio),dwFormat);
		}
		else
		{
			pDC->DrawText(str4,CRect(iTempInt1,134 * m_dVertRatio,iTempInt2,174 * m_dVertRatio),dwFormat);
		}
	#else
		if(m_bPrjMange)
		{
			pDC->DrawText(str4,CRect(iTempInt1,176 * m_dVertRatio,iTempInt2,216 * m_dVertRatio),dwFormat);
		}
		else
		{
			pDC->DrawText(str4,CRect(iTempInt1,190 * m_dVertRatio,iTempInt2,230 * m_dVertRatio),dwFormat);
		}
	#endif
	
#endif

	return TRUE;
}

// 函数 CPrjBaseInfoDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CPrjBaseInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}
	return;
}

// 函数 CPrjBaseInfoDlg::OnMsgTellParentTextChanged
// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、strTemp、_T、GetText、_ttoi、SetNewPrjBaseInfo。
LRESULT CPrjBaseInfoDlg::OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam)
{	
	CMyNewEdit* pEdit = NULL;;
	EITEMINFOTYPE eItemInfoType = (EITEMINFOTYPE)wParam;
	EITEMINFODATATYPE eItemInfoDataType = EIIDT_NONE;

	switch(eItemInfoType)
	{
		case ITEM_PRJBASE_CBPRJTYPE:	pEdit = &m_cbPrjType;	eItemInfoDataType = EIIDT_STRING;	break;
		case ITEM_PRJBASE_EDPRJNAME:	pEdit = &m_edPrjName;	eItemInfoDataType = EIIDT_STRING;	break;
		default:	break;
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
	default:	break;
	}

	if(NULL != m_pInterfaceB)
	{
		m_pInterfaceB->SetNewPrjBaseInfo(eItemInfoType,strTemp,iData,dData);
		return 0;
	}

	return 2;
}

// 函数 CPrjBaseInfoDlg::OnMsgTellParentSetNewText
// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetSafeHwnd、strTemp、_T、GetText、_ttoi、SetNewPrjBaseInfo。
LRESULT CPrjBaseInfoDlg::OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam)
{
	CMyNewEdit* pEdit = NULL;;
	EITEMINFOTYPE eItemInfoType = (EITEMINFOTYPE)wParam;
	EITEMINFODATATYPE eItemInfoDataType = EIIDT_NONE;

	switch(eItemInfoType)
	{
	case ITEM_PRJBASE_CBPRJTYPE:	pEdit = &m_cbPrjType;	eItemInfoDataType = EIIDT_STRING;	break;
	case ITEM_PRJBASE_EDPRJNAME:	pEdit = &m_edPrjName;	eItemInfoDataType = EIIDT_STRING;	break;
	default:	break;
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
	default:	break;
	}

	if(NULL != m_pInterfaceB)
	{
		m_pInterfaceB->SetNewPrjBaseInfo(eItemInfoType,strTemp,iData,dData);
		return 0;
	}

	return 2;
}

// 函数 CPrjBaseInfoDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitDlg、CreateCtrl、InitCtrl、SetCtrlPos、ShowCtrl。
BOOL CPrjBaseInfoDlg::OnInitDialog()
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

// 函数 CPrjBaseInfoDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateCb、CreateEd。
void CPrjBaseInfoDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateCb();
	CreateEd();
}

// 函数 CPrjBaseInfoDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjBaseInfoDlg::CreateBt()
{
	
}

// 函数 CPrjBaseInfoDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjBaseInfoDlg::CreateSt()
{
	
}

// 函数 CPrjBaseInfoDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CPrjBaseInfoDlg::CreateCb()
{
	CRect rcCreate(0,0,0,0);

	m_cbPrjType.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_PRJBASEINFODLG_CB_PRJTYPE);
}

// 函数 CPrjBaseInfoDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CPrjBaseInfoDlg::CreateEd()
{
	m_edPrjName.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_PRJBASEINFODLG_ED_PRJNAME);
	m_edReactSystem.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_PRJBASEINFODLG_ED_SYSTEM);
	m_edUnit.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0,0,0,0), this,ID_PRJBASEINFODLG_ED_UNIT);
}

// 函数 CPrjBaseInfoDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont、GetBeEnglish。
void CPrjBaseInfoDlg::InitDlg()
{
	int iFontH = 16 * m_dTxRatio;

	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	if(theApp.GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
	}
}

// 函数 CPrjBaseInfoDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitEd、InitCb。
void CPrjBaseInfoDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitEd();
	InitCb();
}

// 函数 CPrjBaseInfoDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjBaseInfoDlg::InitBt()
{
	
}

// 函数 CPrjBaseInfoDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPrjBaseInfoDlg::InitSt()
{
	
}

// 函数 CPrjBaseInfoDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、SetTextColor。
void CPrjBaseInfoDlg::InitCb()
{
	int iFontH = 16 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
	}

	m_cbPrjType.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_cbPrjType.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_cbPrjType.SetSelectedBkColor(CLR_SOFT_THEME,CLR_SOFT_THEME,CLR_SOFT_THEME,CLR_SOFT_THEME);
	m_cbPrjType.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XC6,0XC6,0XC6));
	m_cbPrjType.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbPrjType.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbPrjType.SetWorkState(EWS_READONLY);
	m_cbPrjType.m_iRightIndent = 44;
	m_cbPrjType.m_arrowInfo.m_clrArrow = Color(0X39,0X45,0X65);
	m_cbPrjType.m_arrowInfo.m_arrowW = 12;
	m_cbPrjType.m_arrowInfo.m_arrowH = 8;

	if(m_bPrjMange)
	{
		m_cbPrjType.SetTellParentTxChangedParam(TRUE,ITEM_PRJBASE_CBPRJTYPE);
	}
	m_cbPrjType.SetTellParentSetNewText(TRUE,ITEM_PRJBASE_CBPRJTYPE);

	m_cbPrjType.InsertString(0,theApp.m_pLangInfo->GetText(33));
	m_cbPrjType.InsertString(1,theApp.m_pLangInfo->GetText(219));
	m_cbPrjType.InsertString(2,theApp.m_pLangInfo->GetText(220));
	m_cbPrjType.SetCurSel(1,FALSE,TRUE);

	return;
}

// 函数 CPrjBaseInfoDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB。
void CPrjBaseInfoDlg::InitEd()
{
	int iFontH = 16 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
	}

	m_edPrjName.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edPrjName.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edPrjName.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edPrjName.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edPrjName.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	if(m_bPrjMange)
	{
		m_edPrjName.SetTellParentTxChangedParam(TRUE,ITEM_PRJBASE_EDPRJNAME);
	}

	m_edReactSystem.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edReactSystem.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edReactSystem.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edReactSystem.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edReactSystem.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_edReactSystem.SetText(_T("20"),FALSE,TRUE);	//新建实验时，默认实验体系为20ul

	m_edUnit.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_edUnit.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_edUnit.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_edUnit.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_edUnit.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CPrjBaseInfoDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、int、CRect、Width、MoveWindow、OffsetRect。
void CPrjBaseInfoDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	int iHeight = int(40 * m_dVertRatio);
	int iSpace = int(10 * m_dHoriRatio);
	int iStcWidth = int(120 * m_dHoriRatio);
	int iUnitWdith = int(20 * m_dHoriRatio);

	CRect rectEdit;
	if(m_bPrjMange)
	{
		rectEdit = CRect(iSpace*2+iStcWidth, int(20*m_dVertRatio), rect.Width()-iSpace, int(60*m_dVertRatio));
	}
	else
	{
		rectEdit = CRect(iSpace*2+iStcWidth, int(22*m_dVertRatio), rect.Width()-iSpace, int(62*m_dVertRatio));
	}
	m_edPrjName.MoveWindow(rectEdit);

	if(m_bPrjMange)
	{
		rectEdit.OffsetRect(0, int(52 * m_dVertRatio));
	}
	else
	{
		rectEdit.OffsetRect(0, int(56 * m_dVertRatio));
	}
	m_cbPrjType.MoveWindow(rectEdit);

	if(m_bPrjMange)
	{
		rectEdit.OffsetRect(0, int(52 * m_dVertRatio));
		rectEdit.right = rect.Width()-iSpace*2-iUnitWdith;
	}
	else
	{
		rectEdit.OffsetRect(0, int(56 * m_dVertRatio));
		rectEdit.right = rect.Width()-iSpace*2-iUnitWdith;
	}
	m_edReactSystem.MoveWindow(rectEdit);

	if(m_bPrjMange)
	{
		rectEdit.OffsetRect(0, int(52 * m_dVertRatio));
		rectEdit.right = rect.Width()-iSpace*2;
	}
	else
	{
		rectEdit.OffsetRect(0, int(56 * m_dVertRatio));
		rectEdit.right = rect.Width()-iSpace*2;
	}
	m_edUnit.MoveWindow(rectEdit);

	return;
}

// 函数 CPrjBaseInfoDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CPrjBaseInfoDlg::ShowCtrl()
{
#ifndef HIDE_PROJECTTYPE
	m_cbPrjType.ShowWindow(SW_SHOW);
#endif

	m_edPrjName.ShowWindow(SW_SHOW);
	m_edReactSystem.ShowWindow(SW_SHOW);

#ifndef HIDE_PROJECTUNIT
	m_edUnit.ShowWindow(SW_SHOW);
#endif
}

// 函数 CPrjBaseInfoDlg::SetCtrlEnableState
// 作用：设置SetCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 EnableWindow。
void CPrjBaseInfoDlg::SetCtrlEnableState(BOOL bEnabled)
{
	m_edPrjName.EnableWindow(bEnabled);
	m_cbPrjType.EnableWindow(bEnabled);
	m_edReactSystem.EnableWindow(bEnabled);
	m_edUnit.EnableWindow(bEnabled);
}

// 函数 CPrjBaseInfoDlg::ClearPage
// 作用：更新或清除ClearPage。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetCurSel、SetText、_T。
void CPrjBaseInfoDlg::ClearPage()
{
	m_cbPrjType.SetCurSel(0,TRUE,TRUE);

	m_edPrjName.SetText(_T(""),TRUE,TRUE);
	m_edReactSystem.SetText(_T(""),TRUE,TRUE);
	m_edUnit.SetText(_T(""),TRUE,TRUE);
}

// 函数 CPrjBaseInfoDlg::SetPrjBaseInfo
// 作用：设置SetPrjBaseInfo。
// 参数：pReagentItem：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 strTemp、_T、SetText、GetName、SetCurSel、GetType。
int CPrjBaseInfoDlg::SetPrjBaseInfo(CReagentItem* pReagentItem)
{
	if(NULL == pReagentItem)
	{
		return -1;
	}

	CString strTemp(_T(""));

	m_edPrjName.SetText(pReagentItem->GetName(),TRUE,TRUE);
	m_cbPrjType.SetCurSel(pReagentItem->GetType(),TRUE,TRUE);
	strTemp.Format(_T("%d"),pReagentItem->GetReactVolume());
	m_edReactSystem.SetText(strTemp,TRUE,TRUE);
	m_edUnit.SetText(pReagentItem->GetUnit(),TRUE,TRUE);

	return 0;
}

// 函数 CPrjBaseInfoDlg::GetPrjBaseInfo
// 作用：读取GetPrjBaseInfo。
// 参数：pReagentItem：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 strTemp、_T、SetName、GetText、SetType、GetCurSel。
int CPrjBaseInfoDlg::GetPrjBaseInfo(CReagentItem* pReagentItem)
{
	if(NULL == pReagentItem)
	{
		return -1;
	}

	CString strTemp(_T(""));

	pReagentItem->SetName(m_edPrjName.GetText());
	pReagentItem->SetType((eExperimentType)m_cbPrjType.GetCurSel());
	pReagentItem->SetReactVolume(_ttoi(m_edReactSystem.GetText()));
	pReagentItem->SetUnit(m_edUnit.GetText());

	return 0;
}

// 函数 CPrjBaseInfoDlg::SetEditState
// 作用：设置SetEditState。
// 参数：bEditable：是或否；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable。
void CPrjBaseInfoDlg::SetEditState(BOOL bEditable,BOOL bRedraw /*= FALSE*/)
{
	m_cbPrjType.SetBeEditable(bEditable,bRedraw);
	m_edPrjName.SetBeEditable(bEditable,bRedraw);
	m_edReactSystem.SetBeEditable(bEditable,bRedraw);
	m_edUnit.SetBeEditable(bEditable,bRedraw);
}

// 函数 CPrjBaseInfoDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetMyFont、GetBeEnglish、TextParamChanged、GetCurSel、SetItemText、GetText。
int CPrjBaseInfoDlg::RefreshLanguageDisplay()
{
	SetMyFont(m_stTxFont);

	int iFontH = 16 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
	}

	m_edPrjName.SetMyFont(m_stTxFont,iFontH);
	m_edPrjName.TextParamChanged();

	m_edReactSystem.SetMyFont(m_stTxFont,iFontH);
	m_edPrjName.TextParamChanged();

	m_edUnit.SetMyFont(m_stTxFont,iFontH);
	m_edPrjName.TextParamChanged();

	m_cbPrjType.SetMyFont(m_stTxFont,iFontH);
	m_cbPrjType.m_selWnd.SetMyFont(m_stTxFont,iFontH);
	m_cbPrjType.TextParamChanged();

	int iCurSel = m_cbPrjType.GetCurSel();
	m_cbPrjType.SetItemText(0,theApp.m_pLangInfo->GetText(33));
	m_cbPrjType.SetItemText(1,theApp.m_pLangInfo->GetText(219));
	m_cbPrjType.SetItemText(2,theApp.m_pLangInfo->GetText(220));
	m_cbPrjType.RefreshText(iCurSel);

	SetCtrlPos();

	return 0;
}

// 函数 CPrjBaseInfoDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetBeEditable。
int CPrjBaseInfoDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	m_eExpEditMode = eExpEditMode;

	if(EEEM_IVD == m_eExpEditMode)
	{
		m_edPrjName.SetBeEditable(FALSE,TRUE);
		m_cbPrjType.SetBeEditable(FALSE,TRUE);
		m_edReactSystem.SetBeEditable(FALSE,TRUE);
		m_edUnit.SetBeEditable(FALSE,TRUE);
	}
	else if(EEEM_NOLIMIT == m_eExpEditMode)
	{
		m_edPrjName.SetBeEditable(TRUE,TRUE);
		m_cbPrjType.SetBeEditable(TRUE,TRUE);
		m_edReactSystem.SetBeEditable(TRUE,TRUE);
		m_edUnit.SetBeEditable(TRUE,TRUE);
	}
	else if(EEEM_RUNNING == m_eExpEditMode)
	{
		m_edPrjName.SetBeEditable(FALSE,TRUE);
		m_cbPrjType.SetBeEditable(FALSE,TRUE);
		m_edReactSystem.SetBeEditable(FALSE,TRUE);
		m_edUnit.SetBeEditable(FALSE,TRUE);
	}
	else if(EEEM_END == m_eExpEditMode)
	{
		m_edPrjName.SetBeEditable(TRUE,TRUE);
		m_cbPrjType.SetBeEditable(TRUE,TRUE);
		m_edReactSystem.SetBeEditable(TRUE,TRUE);
		m_edUnit.SetBeEditable(TRUE,TRUE);
	}

	return 0;
}

