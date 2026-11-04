// 【交接】 GeneralPcr\Ps96AddTemplateDlg.cpp
// 作用：Ps96AddTemplateDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CPs96AddTemplateDlg、CDialogEx、Empty、DoDataExchange、DDX_Control、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "Ps96AddTemplateDlg.h"
#include "GeneralPcr.h"

// CPs96AddTemplateDlg dialog
IMPLEMENT_DYNAMIC(CPs96AddTemplateDlg, CDialogEx)

// 函数 CPs96AddTemplateDlg::CPs96AddTemplateDlg
// 作用：执行CPs96AddTemplateDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CPs96AddTemplateDlg::CPs96AddTemplateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPs96AddTemplateDlg::IDD, pParent)
{
	m_iAngleRadius = 20;
	m_iFrameWidth = 1;
	m_iWndWidth = 900;
	m_iWndHeight = 900;
	m_iCapHeight = 90;

	m_strName.Empty();
	m_strLabName.Empty();
	m_strLogoFile.Empty();
	m_strLabAdress.Empty();
	m_strContactUrl.Empty();
	m_strContactEmail.Empty();
	m_strContactPhone.Empty();
	m_strTestName.Empty();
	m_strDisclaimer.Empty();

	m_bAddTemplage = TRUE;
	m_bChanged = FALSE;

	m_pReportData = NULL;
}

// 函数 CPs96AddTemplateDlg::~CPs96AddTemplateDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPs96AddTemplateDlg::~CPs96AddTemplateDlg()
{

}

// 函数 CPs96AddTemplateDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 DDX_Control。
void CPs96AddTemplateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DISCLAIMER, m_edDisclaimer);
}

BEGIN_MESSAGE_MAP(CPs96AddTemplateDlg, CDialogEx)
	ON_WM_ERASEBKGND() 
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_PS96ADDTEMPLATE_BT_LOGOFILE,OnBnClickedLogoFile)
	ON_BN_CLICKED(ID_PS96SIMPLESETDLG_BT_SAVE,OnBnClickedSave)
	ON_BN_CLICKED(ID_PS96SIMPLESETDLG_BT_CANCEL,OnBnClickedCancel)
END_MESSAGE_MAP()

// 函数 CPs96AddTemplateDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CPs96AddTemplateDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDc,memDc2;
	memDc.CreateCompatibleDC(pDC);
	memDc2.CreateCompatibleDC(pDC);

	CBitmap bitMapCB,bitMapCB2;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);
	bitMapCB2.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB2 = memDc2.SelectObject(&bitMapCB2);

	memDc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	memDc2.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(0,0,0));

	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = CLRALPHAVALUE;
	blendFunc.AlphaFormat = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	BOOL ret = memDc.AlphaBlend(0,0,rect.Width(),rect.Height(),&memDc2,0,0,rect.Width(),rect.Height(),blendFunc);

	CRect rcUseful;
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;

	DrawRoundRectangleNew(&memDc,rcUseful.left, rcUseful.top + m_iCapHeight,rcUseful.Width(),rcUseful.Height() - m_iCapHeight,0,0,m_iAngleRadius,m_iAngleRadius,FALSE,Color(197,197,197),m_iFrameWidth,TRUE,Color(255,255,255),1);
	DrawRoundRectangleNew(&memDc,rcUseful.left, rcUseful.top,rcUseful.Width(),m_iCapHeight,m_iAngleRadius,m_iAngleRadius,0,0,FALSE,COLOR_SOFT_THEME,m_iFrameWidth,TRUE,COLOR_SOFT_THEME,1);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	DWORD dwTxStyle = DT_LEFT | DT_VCENTER | DT_SINGLELINE;
	
	int iStartX = rcUseful.left + int(20 * m_dHoriRatio);
	int iStartY = rcUseful.top + int(110 * m_dVertRatio);
	int iSpace = int(10 * m_dVertRatio);
	int iWidth = int(230 * m_dHoriRatio);
	int iHeight = int(45 * m_dHoriRatio);

	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(504),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle); // 模版名臣
	iStartY += iHeight + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(505),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle); // 机构名称
	iStartY += iHeight + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(530),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle); // 机构Logo

	iStartY += iHeight + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(506),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle); // 地址

	iStartY += iHeight*2 + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(507),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle); // 联系网站
	iStartY += iHeight + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(508),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle);
	iStartY += iHeight + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(509),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle);
	iStartY += iHeight + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(510),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle);

	iStartY += iHeight + iSpace;
	memDc.DrawText(theApp.m_pLangInfo->GetTextWithColon(511),CRect(iStartX, iStartY, iStartX+iWidth, iStartY+iHeight), dwTxStyle); // 免责声明

	memDc.SetTextColor(RGB(255,255,255));
	if (m_bAddTemplage)
		memDc.DrawText(theApp.m_pLangInfo->GetText(501),CRect(rcUseful.left + 10,rcUseful.top + 5,rcUseful.left + rcUseful.Width() - 10,rcUseful.top + m_iCapHeight - 5),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	else
		memDc.DrawText(theApp.m_pLangInfo->GetText(502),CRect(rcUseful.left + 10,rcUseful.top + 5,rcUseful.left + rcUseful.Width() - 10,rcUseful.top + m_iCapHeight - 5),DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	memDc.SelectObject(pOldFont);

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	memDc2.SelectObject(&pOldBitmapCB2);
	bitMapCB2.DeleteObject();
	memDc2.DeleteDC();

	return TRUE;
}

// 函数 CPs96AddTemplateDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CPs96AddTemplateDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iWndWidth *= m_dHoriRatio;
	m_iWndHeight *= m_dVertRatio;
	m_iCapHeight *= m_dVertRatio;
	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CPs96AddTemplateDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PostMessage、MAKELPARAM。
void CPs96AddTemplateDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
#ifdef POPDLG_USESHADEBK
	CDialogEx::OnLButtonDown(nFlags, point);
#else
	if(point.y < m_iCapHeight)
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

// 函数 CPs96AddTemplateDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、GetParent、Width、Height、SetRoundRect、CenterWindow。
BOOL CPs96AddTemplateDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

#ifdef POPDLG_USESHADEBK
	SetWindowPos(GetParent(),theApp.m_rcWorkArea.left,theApp.m_rcWorkArea.top,theApp.m_rcWorkArea.Width(),theApp.m_rcWorkArea.Height(),SWP_NOZORDER);
#else
	SetWindowPos(GetParent(),0,0,m_iWndWidth,m_iWndHeight,SWP_NOZORDER);
	SetRoundRect(m_iAngleRadius,m_iAngleRadius);
	CenterWindow(GetParent());
#endif

	CreateCtrl();
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();

	ShowCtrl();

	return TRUE;
}

// 函数 CPs96AddTemplateDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateEd。
void CPs96AddTemplateDlg::CreateCtrl()
{
	CreateBt();
	CreateEd();
}

// 函数 CPs96AddTemplateDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CPs96AddTemplateDlg::CreateBt()
{
	m_btnLogoFile.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_BT_LOGOFILE);

	m_btSave.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PS96SIMPLESETDLG_BT_SAVE);
	m_btCancel.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PS96SIMPLESETDLG_BT_CANCEL);
}

// 函数 CPs96AddTemplateDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CPs96AddTemplateDlg::CreateEd()
{
	m_edTemplateName.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_NAME);
	m_edLabName.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_LAB_NAME);
	m_edLogoFile.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_LOGOFILE);
	m_edLabAddress.Create(WS_CHILD | WS_BORDER | WS_TABSTOP | ES_MULTILINE | ES_AUTOVSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_ADDRESS);
	m_edContactUrl.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_UML);
	m_edContactEmail.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_EMAIL);
	m_edContactPhone.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_PHONE);
	m_edTestName.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_PS96ADDTEMPLATE_ED_TEST);
}

// 函数 CPs96AddTemplateDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CPs96AddTemplateDlg::InitDlg()
{
	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,30 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CPs96AddTemplateDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitEd。
void CPs96AddTemplateDlg::InitCtrl()
{
	InitBt();
	InitEd();
}

// 函数 CPs96AddTemplateDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBkColor、Color、SetBkColorEnd。
void CPs96AddTemplateDlg::InitBt()
{
	int iFontH = 26 * m_dTxRatio;

	m_btSave.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btSave.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
	m_btSave.SetBkColor(Color(0X38,0XE0,0XEF),Color(0X3A,0XEF,0XFF),COLOR_SOFT_THEME,Color(0XF1,0XF1,0XF1));
	m_btSave.SetBkColorEnd(COLOR_SOFT_THEME,Color(0X38,0XE0,0XEF),Color(0X02,0X8D,0X99),Color(0XD8,0XD8,0XD8));
	m_btSave.SetTextColor(RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XC6,0XC4,0XC4));

	m_btCancel.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btCancel.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);

	m_btnLogoFile.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_btnLogoFile.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
}

// 函数 CPs96AddTemplateDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitEditCtrlParam、SetFont、SetText、SetWindowText。
void CPs96AddTemplateDlg::InitEd()
{
	InitEditCtrlParam(&m_edTemplateName);
	InitEditCtrlParam(&m_edLabName);
	InitEditCtrlParam(&m_edLogoFile);

	m_edLabAddress.SetFont(&m_edLabName.m_fontSet);

	InitEditCtrlParam(&m_edContactUrl);
	InitEditCtrlParam(&m_edContactEmail);
	InitEditCtrlParam(&m_edContactPhone);
	InitEditCtrlParam(&m_edTestName);

	m_edDisclaimer.SetFont(&m_edLabName.m_fontSet);

	m_edTemplateName.SetText(m_strName,FALSE,TRUE);
	m_edLabName.SetText(m_strLabName,FALSE,TRUE);
	m_edLogoFile.SetText(m_strLogoFile,FALSE,TRUE);

	m_edLabAddress.SetWindowText(m_strLabAdress);
	m_edContactUrl.SetText(m_strContactUrl,FALSE,TRUE);
	m_edContactEmail.SetText(m_strContactEmail,FALSE,TRUE);
	m_edContactPhone.SetText(m_strContactPhone,FALSE,TRUE);
	m_edTestName.SetText(m_strTestName,FALSE,TRUE);
	//m_edDisclaimer.SetText(m_strDisclaimer,FALSE,TRUE);
	m_edDisclaimer.SetWindowText(m_strDisclaimer);
}

// 函数 CPs96AddTemplateDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、Width、Height、int、SetWindowPos。
void CPs96AddTemplateDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	CRect rcUseful;
#ifdef POPDLG_USESHADEBK
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;
#endif

	int iStartX = rcUseful.left + int(270 * m_dHoriRatio);
	int iStartY = rcUseful.top + int(110 * m_dVertRatio);
	int iSpace = int(10 * m_dVertRatio);
	int iWidth = int(600 * m_dHoriRatio);
	int iHeight = int(45 * m_dHoriRatio);

	m_edTemplateName.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight,SWP_NOZORDER);
	iStartY += iHeight + iSpace;
	m_edLabName.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight,SWP_NOZORDER);

	iStartY += iHeight + iSpace;
	int iBtnWidth = int(80 * m_dHoriRatio);
	m_edLogoFile.SetWindowPos(this, iStartX, iStartY, iWidth-iBtnWidth-iSpace, iHeight,SWP_NOZORDER);
	m_btnLogoFile.SetWindowPos(this, iStartX+iWidth-iBtnWidth, iStartY, iBtnWidth, iHeight,SWP_NOZORDER);

	iStartY += iHeight + iSpace;
	m_edLabAddress.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight*2,SWP_NOZORDER);

	iStartY += iHeight*2 + iSpace;
	m_edContactUrl.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight,SWP_NOZORDER);
	iStartY += iHeight + iSpace;
	m_edContactEmail.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight,SWP_NOZORDER);
	iStartY += iHeight + iSpace;
	m_edContactPhone.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight,SWP_NOZORDER);
	iStartY += iHeight + iSpace;
	m_edTestName.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight,SWP_NOZORDER);
	iStartY += iHeight + iSpace;
	m_edDisclaimer.SetWindowPos(this, iStartX, iStartY, iWidth, iHeight*5,SWP_NOZORDER);
	
	iStartY += iHeight*5 + iSpace*2;

	iBtnWidth = int(140 * m_dHoriRatio);
	int iBtnHeight = int(70 * m_dVertRatio);
	m_btSave.SetWindowPos(this, rcUseful.left + int(540 * m_dHoriRatio), iStartY, iBtnWidth, iBtnHeight,SWP_NOZORDER);
	m_btCancel.SetWindowPos(this, rcUseful.left + int(720 * m_dHoriRatio), iStartY, iBtnWidth, iBtnHeight,SWP_NOZORDER);

	return;
}

// 函数 CPs96AddTemplateDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CPs96AddTemplateDlg::ShowCtrl()
{
	m_btSave.ShowWindow(SW_SHOW);
	m_btCancel.ShowWindow(SW_SHOW);

	m_edTemplateName.ShowWindow(SW_SHOW);
	m_edLabName.ShowWindow(SW_SHOW);
	m_edLogoFile.ShowWindow(SW_SHOW);
	m_btnLogoFile.ShowWindow(SW_SHOW);

	m_edLabAddress.ShowWindow(SW_SHOW);
	m_edContactUrl.ShowWindow(SW_SHOW);
	m_edContactEmail.ShowWindow(SW_SHOW);
	m_edContactPhone.ShowWindow(SW_SHOW);
	m_edTestName.ShowWindow(SW_SHOW);
	m_edDisclaimer.ShowWindow(SW_SHOW);

	return;
}

// 函数 CPs96AddTemplateDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowText、GetText。
void CPs96AddTemplateDlg::SetCtrlText()
{
	m_btnLogoFile.SetWindowText(theApp.m_pLangInfo->GetText(28));

	m_btSave.SetWindowText(theApp.m_pLangInfo->GetText(148));
	m_btCancel.SetWindowText(theApp.m_pLangInfo->GetText(150));

	return;
}

// 函数 CPs96AddTemplateDlg::OnBnClickedSave
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetText、IsEmpty、PopNormalTipInfo、FindSameName、FindFile、PopWarningTipInfo。
void CPs96AddTemplateDlg::OnBnClickedSave()
{
	CString strTemp;
	strTemp = m_edTemplateName.GetText();
	if (strTemp.IsEmpty())
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(512));
		return;
	}
	if (m_bAddTemplage)
	{
		if (m_pReportData->FindSameName(strTemp))
		{
			PopNormalTipInfo(theApp.m_pLangInfo->GetText(513));
			return;
		}
	}
	else
	{
		if (strTemp != m_strName)
		{
			if (m_pReportData->FindSameName(strTemp))
			{
				PopNormalTipInfo(theApp.m_pLangInfo->GetText(513));
				return;
			}
		}
	}

	if (strTemp != m_strName)
	{
		m_strName = strTemp;
		m_bChanged = TRUE;
	}

	strTemp = m_edLabName.GetText();
	if (strTemp != m_strLabName)
	{
		m_strLabName = strTemp;
		m_bChanged = TRUE;
	}

	strTemp = m_edLogoFile.GetText();
	if (strTemp != m_strLogoFile)
	{
		CFileFind fileFind;
		BOOL bFind = fileFind.FindFile(strTemp); 
		if(!bFind)
		{
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(531));
			return;
		}

		m_strLogoFile = strTemp;
		m_bChanged = TRUE;
	}

	m_edLabAddress.GetWindowText(strTemp);
	if (strTemp != m_strLabAdress)
	{
		m_strLabAdress = strTemp;
		m_bChanged = TRUE;
	}

	strTemp = m_edContactUrl.GetText();
	if (strTemp != m_strContactUrl)
	{
		m_strContactUrl = strTemp;
		m_bChanged = TRUE;
	}


	strTemp = m_edContactEmail.GetText();
	if (strTemp != m_strContactEmail)
	{
		m_strContactEmail = strTemp;
		m_bChanged = TRUE;
	}


	strTemp = m_edContactPhone.GetText();
	if (strTemp != m_strContactPhone)
	{
		m_strContactPhone = strTemp;
		m_bChanged = TRUE;
	}

	strTemp = m_edTestName.GetText();
	if (strTemp != m_strTestName)
	{
		m_strTestName = strTemp;
		m_bChanged = TRUE;
	}

	m_edDisclaimer.GetWindowText(strTemp);
	if (strTemp != m_strDisclaimer)
	{
		m_strDisclaimer = strTemp;
		m_bChanged = TRUE;
	}

	OnOK();
	return;
}

// 函数 CPs96AddTemplateDlg::OnBnClickedCancel
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 OnCancel。
void CPs96AddTemplateDlg::OnBnClickedCancel()
{
	OnCancel();
	return;
}

// 函数 CPs96AddTemplateDlg::SetRoundRect
// 作用：设置SetRoundRect。
// 参数：x；y。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetClientRect、CreateRoundRectRgn、SetWindowRgn。
BOOL CPs96AddTemplateDlg::SetRoundRect(int x /*= 5*/,int y /*= 5*/)
{
	CRgn rgnWnd;
	CRect rcWnd;
	GetClientRect(&rcWnd);
	rgnWnd.CreateRoundRectRgn(rcWnd.left,rcWnd.top,rcWnd.right,rcWnd.bottom,x,y);
	if(!SetWindowRgn(rgnWnd,TRUE))
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

// 函数 CPs96AddTemplateDlg::InitEditCtrlParam
// 作用：初始化InitEditCtrlParam。
// 参数：pEdit：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
void CPs96AddTemplateDlg::InitEditCtrlParam(CMyNewEdit* pEdit)
{
	if(NULL == pEdit)
	{
		return;
	}

	pEdit->SetFrameColor(Color(0,0,0),Color(0,0,0),Color(0,0,0),Color(0,0,0));
	pEdit->SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	pEdit->SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	pEdit->SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0XC6,0XC6,0XC6));
	pEdit->SetMyFont(m_stTxFont,26 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
	pEdit->SetTextClr1(RGB(0X56,0X56,0X56));

	return;
}



// 函数 CPs96AddTemplateDlg::OnBnClickedLogoFile
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 cf、_T、File、DoModal、GetPathName、SetText。
void CPs96AddTemplateDlg::OnBnClickedLogoFile()
{
	CFileDialog cf(TRUE,_T(".jpeg"), NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,_T("Logo File(*.jpeg);(*.png);(*.gif)|*.jepg;*.png;*.gif|"),this);
	if(IDOK == cf.DoModal())
	{
		CString strFilePath = cf.GetPathName();
		m_edLogoFile.SetText(strFilePath, TRUE, TRUE);
	}
}

