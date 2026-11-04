// 【交接】 GeneralPcr\InstrumentInfoDlg.cpp
// 作用：InstrumentInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CInstrumentInfoDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、ON_BN_CLICKED。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"
#include "InstrumentInfoDlg.h"
#include "InstrumentPCR.h"

// CInstrumentInfoDlg dialog
IMPLEMENT_DYNAMIC(CInstrumentInfoDlg, CDialogEx)

// 函数 CInstrumentInfoDlg::CInstrumentInfoDlg
// 作用：执行CInstrumentInfoDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInstrumentInfoDlg::CInstrumentInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInstrumentInfoDlg::IDD, pParent)
{
	m_bCtrlCreated = FALSE; 
}

// 函数 CInstrumentInfoDlg::~CInstrumentInfoDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInstrumentInfoDlg::~CInstrumentInfoDlg()
{

}

// 函数 CInstrumentInfoDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CInstrumentInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInstrumentInfoDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_BN_CLICKED(ID_INSTRUMENTINFODLG_BT_FINDINSTRUMENT,OnBnClickedFindInstrument)
	ON_MESSAGE(WM_TELLPARENTSETNEWTEXT,OnMsgTellParentSetNewText)
END_MESSAGE_MAP()

// 函数 CInstrumentInfoDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、FillSolidRect、Width、Height、DrawRoundRectangleNew。
BOOL CInstrumentInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	CRect rect;
	GetClientRect(&rect);

	pDC->FillSolidRect(0,0,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);
	DrawRoundRectangleNew(pDC,rect.left,rect.top,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);

	pDC->SetBkMode(TRANSPARENT);
	CFont* pOldFont = pDC->SelectObject(&m_fontSet);

	pDC->FillSolidRect(28 * m_dHoriRatio,33 * m_dVertRatio,12 * m_dHoriRatio,4 * m_dVertRatio,CLR_SOFT_THEME);
	pDC->FillSolidRect(32 * m_dHoriRatio,29 * m_dVertRatio,4 * m_dHoriRatio,12 * m_dVertRatio,CLR_SOFT_THEME);
	pDC->SetTextColor(CLR_SOFT_THEME);
	pDC->DrawText(pLangInfo->GetText(22),CRect(44 * m_dHoriRatio,24 * m_dVertRatio,316 * m_dHoriRatio,46 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	pDC->SetTextColor(RGB(0X39,0X45,0X65));

	int iEndX = 238 * m_dHoriRatio;
	int iTempInt1 = 290 * m_dHoriRatio;
	if(theApp.GetBeEnglish())
	{
		iEndX += 30 * m_dHoriRatio; 
		iTempInt1 += 30 * m_dHoriRatio; 
	}
	pDC->DrawText(pLangInfo->GetText(23),CRect(48 * m_dHoriRatio,138 * m_dVertRatio,iEndX,165 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	pDC->DrawText(pLangInfo->GetText(24),CRect(48 * m_dHoriRatio,218 * m_dVertRatio,iEndX,245 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	pDC->DrawText(pLangInfo->GetText(25),CRect(48 * m_dHoriRatio,298 * m_dVertRatio,iEndX,325 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	
	//显示热盖温度
	CGeneralPcrDlg* pMainDlg = (CGeneralPcrDlg*)theApp.m_pMainWnd;
	CMiddleDlg* pMiddleDlg = pMainDlg->m_workDlg.m_pCurSelPageDlg;
	if(NULL != pMiddleDlg->GetSafeHwnd() && NULL != pMiddleDlg->m_pExpData)
	{
		float fLidTopTemp = pMiddleDlg->m_pExpData->GetExperimentInfo()->GetLidTemp();
		CString strTemp(_T(""));
		strTemp.Format(_T("%.2lf℃"),fLidTopTemp);
		pDC->DrawText(strTemp,CRect(iTempInt1,221 * m_dVertRatio,440 * m_dHoriRatio,241 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	}



	return TRUE;
}

// 函数 CInstrumentInfoDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CInstrumentInfoDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}

	return;
}

// 函数 CInstrumentInfoDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetMyFont、CreateCtrl、InitCtrl、SetCtrlPos、SetCtrlText、ShowCtrl。
BOOL CInstrumentInfoDlg::OnInitDialog()
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

// 函数 CInstrumentInfoDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect、_T。
void CInstrumentInfoDlg::CreateCtrl()
{
	m_cbInstrumentType.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,CRect(0,0,0,0),this,ID_INSTRUMENTINFODLG_CB_INSTRUMENTTYPE);
	m_btnFindInstrument.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_INSTRUMENTINFODLG_BT_FINDINSTRUMENT);

	m_ckbtLidSet.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_INSTRUMENTINFODLG_CKBT_LIDSET);
	m_ckbtTempCtrl.Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_INSTRUMENTINFODLG_ST_TEMCTRLFORMAT);
}

// 函数 CInstrumentInfoDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCb。
void CInstrumentInfoDlg::InitCtrl()
{
	InitBt();
	InitCb();
}

// 函数 CInstrumentInfoDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBtChecked、SetPngBkPic、_T。
void CInstrumentInfoDlg::InitBt()
{
	int iFontH = 18 * m_dTxRatio;

	m_btnFindInstrument.SetMyFont(m_stTxFont,iFontH);
	m_btnFindInstrument.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);

	m_ckbtLidSet.SetBtChecked(TRUE);
	m_ckbtLidSet.SetPngBkPic(_T(".\\BkPic\\check.png"),4,40 * m_dHoriRatio);
	m_ckbtLidSet.SetBeNeedRedrawBk(TRUE);
	m_ckbtLidSet.SetMyFont(m_stTxFont,iFontH);
	m_ckbtLidSet.SetMyFontChecked(m_stTxFont,iFontH);
	m_ckbtLidSet.EnableWindow(FALSE);

	m_ckbtTempCtrl.SetBtChecked(TRUE);
	m_ckbtTempCtrl.SetPngBkPic(_T(".\\BkPic\\check.png"),4,40 * m_dHoriRatio);
	m_ckbtTempCtrl.SetBeNeedRedrawBk(TRUE);
	m_ckbtTempCtrl.SetMyFont(m_stTxFont,iFontH);
	m_ckbtTempCtrl.SetMyFontChecked(m_stTxFont,iFontH);
}

// 函数 CInstrumentInfoDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetFrameColor、Color、SetMainWndBkColor、SetSelectedBkColor、RGB、SetTextColor。
void CInstrumentInfoDlg::InitCb()
{
	int iFontH = 18 * m_dTxRatio;

	m_cbInstrumentType.SetFrameColor(Color(0XD8,0XD8,0XD8),COLOR_SOFT_THEME,COLOR_SOFT_THEME,Color(0XD8,0XD8,0XD8));
	m_cbInstrumentType.SetMainWndBkColor(Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XFF,0XFF,0XFF),Color(0XF7,0XF7,0XF7));
	m_cbInstrumentType.SetSelectedBkColor(RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB),RGB(0X7E,0XD3,0XDB));
	m_cbInstrumentType.SetTextColor(RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X39,0X45,0X65),RGB(0X97,0X97,0X97));
	m_cbInstrumentType.SetMyFont(m_stTxFont,iFontH);
	m_cbInstrumentType.m_selWnd.SetMyFont(m_stTxFont,iFontH);
	m_cbInstrumentType.SetWorkState(EWS_READONLY);
	m_cbInstrumentType.SetTellParentSetNewText(TRUE, 1);
	m_cbInstrumentType.m_iRightIndent = 44 * m_dHoriRatio;
	m_cbInstrumentType.m_arrowInfo.m_clrArrow = Color(0X39,0X45,0X65);
	m_cbInstrumentType.m_arrowInfo.m_arrowW = 12 * m_dHoriRatio;
	m_cbInstrumentType.m_arrowInfo.m_arrowH = 8 * m_dVertRatio;


	InitInstrument();

	return;
}

// 函数 CInstrumentInfoDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ResetCtrlPos。
void CInstrumentInfoDlg::SetCtrlPos()
{
	ResetCtrlPos();
}

// 函数 CInstrumentInfoDlg::ResetCtrlPos
// 作用：更新或清除ResetCtrlPos。
// 参数：bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、GetBeEnglish、CRect、int、MoveWindow、GetSafeHwnd。
void CInstrumentInfoDlg::ResetCtrlPos(BOOL bRedraw /*= FALSE*/)
{
	CRect rect;
	GetClientRect(&rect);

	int iStartX = 240 * m_dHoriRatio;
	if(theApp.GetBeEnglish())
	{
		iStartX += 30 * m_dHoriRatio;
	}

	CRect rectItem = CRect(iStartX, int(131 * m_dVertRatio), iStartX+int(450 * m_dHoriRatio), int(171*m_dVertRatio));
	m_cbInstrumentType.MoveWindow(rectItem, FALSE);
	CRect rectBtn = rectItem;
	int iSpace = int(10*m_dHoriRatio);
	rectBtn.left = rectItem.right + iSpace;
	rectBtn.right = rect.right - iSpace;
	m_btnFindInstrument.MoveWindow(rectBtn, FALSE);

	m_ckbtLidSet.MoveWindow(iStartX, int(221 * m_dVertRatio),int(40 * m_dHoriRatio),int(20 * m_dVertRatio),FALSE);
	m_ckbtTempCtrl.MoveWindow(iStartX, int(301 * m_dVertRatio),int(40 * m_dHoriRatio),int(20 * m_dVertRatio),FALSE);

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate();
	}

	return;
}

// 函数 CInstrumentInfoDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CInstrumentInfoDlg::ShowCtrl()
{
	m_cbInstrumentType.ShowWindow(SW_SHOW);
	m_btnFindInstrument.ShowWindow(SW_SHOW);
	m_ckbtLidSet.ShowWindow(SW_SHOW);
	m_ckbtTempCtrl.ShowWindow(SW_SHOW);

	return;
}

// 函数 CInstrumentInfoDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowText、GetText。
void CInstrumentInfoDlg::SetCtrlText()
{
	m_btnFindInstrument.SetWindowText(theApp.m_pLangInfo->GetText(474));
}

// 函数 CInstrumentInfoDlg::GetInstruInfo
// 作用：读取GetInstruInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：函数里会调用 SetInstrument、GetText、SetLidHeader、GetCheckState、SetTempCtrlMode。
void CInstrumentInfoDlg::GetInstruInfo(CExperimentInfo& info)
{
	//info.SetInstrument(m_cbInstrumentType.GetText());

	info.SetLidHeader(m_ckbtLidSet.GetCheckState());

	if (m_ckbtTempCtrl.GetCheckState())
	{
		info.SetTempCtrlMode(TEMP_CTRL_TUBE);
	}
	else
	{
		info.SetTempCtrlMode(TEMP_CTRL_NONE);
	}

	return;
}

// 函数 CInstrumentInfoDlg::SetInstruInfo
// 作用：设置SetInstruInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：函数里会调用 SetBtChecked、GetLidHeader、GetTempCtrlMode。
void CInstrumentInfoDlg::SetInstruInfo(CExperimentInfo& info)
{
	m_ckbtLidSet.SetBtChecked(info.GetLidHeader(),TRUE);
	m_ckbtTempCtrl.SetBtChecked(info.GetTempCtrlMode() != TEMP_CTRL_NONE,TRUE);
}

// 函数 CInstrumentInfoDlg::SetCtrlEnableState
// 作用：设置SetCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable、EnableWindow。
void CInstrumentInfoDlg::SetCtrlEnableState(BOOL bEnabled)
{
	m_cbInstrumentType.SetBeEditable(bEnabled);
	m_ckbtLidSet.EnableWindow(bEnabled);
	m_ckbtTempCtrl.EnableWindow(bEnabled);
}

// 函数 CInstrumentInfoDlg::ClearPage
// 作用：更新或清除ClearPage。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetBtChecked。
void CInstrumentInfoDlg::ClearPage()
{
	m_ckbtLidSet.SetBtChecked(TRUE,TRUE);
	m_ckbtTempCtrl.SetBtChecked(TRUE,TRUE);
}

// 函数 CInstrumentInfoDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetCtrlText、SetMyFont、TextParamChanged、ResetCtrlPos。
int CInstrumentInfoDlg::RefreshLanguageDisplay()
{
	SetCtrlText();

	SetMyFont(m_stTxFont);

	int iFontH = 18 * m_dTxRatio;

	m_cbInstrumentType.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbInstrumentType.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbInstrumentType.TextParamChanged();

	ResetCtrlPos();

	return 0;
}

// 函数 CInstrumentInfoDlg::SetEditMode
// 作用：设置SetEditMode。
// 参数：eExpEditMode。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetBeEditable、EnableWindow。
int CInstrumentInfoDlg::SetEditMode(EEXPEDITMODE eExpEditMode)
{
	if(m_eExpEditMode == eExpEditMode)
	{
		return 1;
	}

	m_eExpEditMode = eExpEditMode;

	if(EEEM_IVD == m_eExpEditMode)
	{
		m_cbInstrumentType.SetBeEditable(FALSE);
		m_btnFindInstrument.EnableWindow(FALSE);
		m_ckbtTempCtrl.EnableWindow(FALSE);
	}
	else if(EEEM_NOLIMIT == m_eExpEditMode)
	{
		m_cbInstrumentType.SetBeEditable(TRUE);
		m_btnFindInstrument.EnableWindow(TRUE);
		m_ckbtTempCtrl.EnableWindow(TRUE);
	}
	else if(EEEM_RUNNING == m_eExpEditMode)
	{
		m_cbInstrumentType.SetBeEditable(FALSE,TRUE);
		m_btnFindInstrument.EnableWindow(FALSE);
		m_ckbtTempCtrl.EnableWindow(FALSE);
	}
	else if(EEEM_END == m_eExpEditMode)
	{
		m_cbInstrumentType.SetBeEditable(TRUE,TRUE);
		m_btnFindInstrument.EnableWindow(TRUE);
		m_ckbtTempCtrl.EnableWindow(TRUE);
	}

	return 0;
}

// 函数 CInstrumentInfoDlg::InitInstrument
// 作用：初始化InitInstrument。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Clear、GetInstance、GetInstanceCount、GetInstancePCR、IsDemo、CombineModelAndSN。
void CInstrumentInfoDlg::InitInstrument()
{
	m_cbInstrumentType.Clear(FALSE);

	CInstrumentPCR* pInstrument = CInstrumentPCR::GetInstance();
	for(int i = 0;i < pInstrument->GetInstanceCount();++i)
	{
		CInstancePCR* pInstance = pInstrument->GetInstancePCR(i);
		if (pInstance->IsDemo())
			continue;

		CString strFlag = CombineModelAndSN(pInstance->GetModel(), pInstance->GetSN());
		m_cbInstrumentType.InsertString(i,strFlag);
	}
}

// 函数 CInstrumentInfoDlg::CombineModelAndSN
// 作用：执行CombineModelAndSN。
// 参数：strModel：字符串；strSN：字符串。
// 返回：返回一段文字。
// 过程：函数里会调用 IsEmpty、Format、_T、s。
CString CInstrumentInfoDlg::CombineModelAndSN(CString strModel,CString strSN)
{
	CString strFlag = strModel;
	if (!strSN.IsEmpty())
	{
		strFlag.Format(_T("%s(%s)"), strModel, strSN);
	}
	
	return strFlag;
}

// 函数 CInstrumentInfoDlg::SetSelectedInstrument
// 作用：设置SetSelectedInstrument。
// 参数：strModel：字符串；strSN：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 CombineModelAndSN、GetItemCount、GetString、GetCurSel、SetCurSel、CanRunExperiment。
void CInstrumentInfoDlg::SetSelectedInstrument(CString strModel, CString strSN)
{
	CString strFlag = CombineModelAndSN(strModel, strSN);

	int iCount = m_cbInstrumentType.GetItemCount();
	int iCurSel = -1;
	CString strItem;
	for (int i=0; i<iCount; i++)
	{
		m_cbInstrumentType.GetString(i, strItem);
		if (strFlag == strItem)
		{
			iCurSel = i;
			break;
		}
	}

	int iOldSel = m_cbInstrumentType.GetCurSel();
	if (iOldSel != iCurSel)
	{
		m_cbInstrumentType.SetCurSel(iCurSel);
		//CanRunExperiment(iCurSel);
	}
}

// 函数 CInstrumentInfoDlg::OnBnClickedFindInstrument
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCurSel、GetString、GetInstance、Reinitialize、InitInstrument、GetItemCount。
void CInstrumentInfoDlg::OnBnClickedFindInstrument()
{
	CString strOldSel;
	int iOldSel = m_cbInstrumentType.GetCurSel();
	if (iOldSel != -1)
	{
		m_cbInstrumentType.GetString(iOldSel, strOldSel);
	}

	CInstrumentPCR* pInstrument = CInstrumentPCR::GetInstance();
	if (pInstrument->Reinitialize(FALSE))
	{
		InitInstrument();

		int iCount = m_cbInstrumentType.GetItemCount();
		int iCurSel = -1;
		CString strItem;
		for (int i=0; i<iCount; i++)
		{
			m_cbInstrumentType.GetString(i, strItem);
			if (strOldSel == strItem)
			{
				iCurSel = i;
				break;
			}
		}
		m_cbInstrumentType.SetCurSel(iCurSel);

		GetParent()->GetParent()->GetParent()->SendMessage(WM_INSTRUMENT_REINITIALIZE);
	}
}


// 函数 CInstrumentInfoDlg::OnMsgTellParentSetNewText
// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 GetCurSel、CanRunExperiment、GetParent、SendMessage、Invalidate。
LRESULT CInstrumentInfoDlg::OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1);
	{
		int iCurSel = m_cbInstrumentType.GetCurSel();
		CanRunExperiment(iCurSel);
		GetParent()->GetParent()->SendMessage(WM_INSTRUMENT_SELECTED, iCurSel);
		Invalidate();
	}

	return 0;
}

// 函数 CInstrumentInfoDlg::ReshowInstrumentList
// 作用：执行ReshowInstrumentList。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCurSel、GetString、InitInstrument、GetItemCount、SetCurSel。
void CInstrumentInfoDlg::ReshowInstrumentList()
{
	CString strOldSel;
	int iOldSel = m_cbInstrumentType.GetCurSel();
	if (iOldSel != -1)
	{
		m_cbInstrumentType.GetString(iOldSel, strOldSel);
	}

	InitInstrument();

	int iCount = m_cbInstrumentType.GetItemCount();
	int iCurSel = -1;
	CString strItem;
	for (int i=0; i<iCount; i++)
	{
		m_cbInstrumentType.GetString(i, strItem);
		if (strOldSel == strItem)
		{
			iCurSel = i;
			break;
		}
	}
	m_cbInstrumentType.SetCurSel(iCurSel);
}

// 函数 CInstrumentInfoDlg::CanRunExperiment
// 作用：判断CanRunExperiment是否成立。
// 参数：iSelDevice：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、GetInstancePCR、GetInstanceStatus、PopNormalTipInfo、GetText。
void CInstrumentInfoDlg::CanRunExperiment(int iSelDevice)
{
	if (iSelDevice < 0)
		return;

	CInstancePCR* pInstance = CInstrumentPCR::GetInstance()->GetInstancePCR(iSelDevice);
	if (pInstance == NULL)
		return;

	if (pInstance->GetInstanceStatus() == INSTANCE_TEMP_HIGH)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(479));
	}
	else if (pInstance->GetInstanceStatus() == INSTANCE_TEMP_LOW)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(480));
	}
	else if (pInstance->GetInstanceStatus() == INSTANCE_FLUO_HIGH)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(482));
	}
	else if (pInstance->GetInstanceStatus() == INSTANCE_FLUO_LOW)
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(483));
	}

}
