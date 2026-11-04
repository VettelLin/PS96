// 【交接】 GeneralPcr\MonitorBaseInfoDlg.cpp
// 作用：MonitorBaseInfoDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMonitorBaseInfoDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE、END_MESSAGE_MAP。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"
#include "MonitorBaseInfoDlg.h"

// CMonitorBaseInfoDlg dialog
IMPLEMENT_DYNAMIC(CMonitorBaseInfoDlg, CDialogEx)

// 函数 CMonitorBaseInfoDlg::CMonitorBaseInfoDlg
// 作用：执行CMonitorBaseInfoDlg。
// 参数：bPrjManage：是或否；pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMonitorBaseInfoDlg::CMonitorBaseInfoDlg(BOOL bPrjManage /*= FALSE*/,CWnd* pParent /*=NULL*/)
: CDialogEx(CMonitorBaseInfoDlg::IDD, pParent)
{
	m_bCtrlCreated = FALSE;
}

// 函数 CMonitorBaseInfoDlg::~CMonitorBaseInfoDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMonitorBaseInfoDlg::~CMonitorBaseInfoDlg()
{
}

// 函数 CMonitorBaseInfoDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CMonitorBaseInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMonitorBaseInfoDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// 函数 CMonitorBaseInfoDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CMonitorBaseInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	
	CRect rect; 
	GetClientRect(&rect);
	
	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	memDc.FillSolidRect(0,0,rect.Width(),rect.Height(),CLR_SOFT_LIGHT);
	DrawRoundRectangleNew(&memDc,0,0,rect.Width() - 1,rect.Height() - 1,8,8,8,8,TRUE,Color(0XD8,0XD8,0XD8),1,TRUE,Color(0XFF,0XFF,0XFF),1);

	//绘制图标
	Graphics graphics(memDc.m_hDC);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);

	Image image(_T(".\\BkPic\\timeicon.png"));

	Rect destRect;
	destRect.X = 36 * m_dHoriRatio;
	destRect.Y = 59 * m_dVertRatio;
	destRect.Width = 16 * m_dHoriRatio;
	destRect.Height = destRect.Width;
	graphics.DrawImage(&image,destRect,0,0,image.GetWidth(),image.GetHeight(),UnitPixel,&ImgAtt);

	destRect.Y = 90 * m_dVertRatio;
	graphics.DrawImage(&image,destRect,0,0,image.GetWidth(),image.GetHeight(),UnitPixel,&ImgAtt);

	destRect.Y = 254 * m_dVertRatio;
	graphics.DrawImage(&image,destRect,0,0,image.GetWidth(),image.GetHeight(),UnitPixel,&ImgAtt);

	destRect.Y = 284 * m_dVertRatio;
	graphics.DrawImage(&image,destRect,0,0,image.GetWidth(),image.GetHeight(),UnitPixel,&ImgAtt);

	Image image2(_T(".\\BkPic\\temperatureicon.png"));
	destRect.X = 40 * m_dHoriRatio;
	destRect.Y = 156 * m_dVertRatio;
	destRect.Width = 8 * m_dHoriRatio;
	destRect.Height = 16 * m_dVertRatio;
	graphics.DrawImage(&image2,destRect,0,0,image2.GetWidth(),image2.GetHeight(),UnitPixel,&ImgAtt);

	destRect.Y = 187 * m_dVertRatio;
	graphics.DrawImage(&image2,destRect,0,0,image2.GetWidth(),image2.GetHeight(),UnitPixel,&ImgAtt);

	graphics.ReleaseHDC(memDc.m_hDC);
	
	int iTempInt1 = 66 * m_dHoriRatio,iTempInt2 = 163 * m_dHoriRatio,iTempInt3 = 176 * m_dHoriRatio,iTempInt4 = 176 * m_dHoriRatio,iTempInt5 = 163 * m_dHoriRatio;
	if(theApp.GetBeEnglish())
	{
		iTempInt2 = 192 * m_dHoriRatio;
		iTempInt3 = 280 * m_dHoriRatio;
		iTempInt4 = 182 * m_dHoriRatio;
		iTempInt5 = 240 * m_dHoriRatio;
	}

	memDc.DrawText(pLangInfo->GetText(83),CRect(iTempInt1,55 * m_dVertRatio,iTempInt2,79 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(84),CRect(iTempInt1,86 * m_dVertRatio,iTempInt2,110 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(85),CRect(iTempInt1,152 * m_dVertRatio,iTempInt5,176 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(86),CRect(iTempInt1,183 * m_dVertRatio,iTempInt3,207 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(87),CRect(iTempInt1,249 * m_dVertRatio,iTempInt4,273 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	memDc.DrawText(pLangInfo->GetText(88),CRect(iTempInt1,280 * m_dVertRatio,iTempInt4,304 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	clock_t ckStart = clock();	
	Node<CRect>* pNodeRst = m_rcManage.m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDc,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}
	ckStart = clock() - ckStart;

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CMonitorBaseInfoDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CMonitorBaseInfoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}
	return;
}

// 函数 CMonitorBaseInfoDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitDlg、CreateCtrl、InitCtrl、SetCtrlPos、SetCtrlText、ShowCtrl。
BOOL CMonitorBaseInfoDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	InitDlg();
	CreateCtrl();
	m_bCtrlCreated = TRUE;
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();

	ShowCtrl();

	return TRUE;
}

// 函数 CMonitorBaseInfoDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateCb、CreateEd、Create、_T。
void CMonitorBaseInfoDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateCb();
	CreateEd();

	//m_progressBar.Create(_T(""),WS_CHILD,CRect(0,0,0,0),this,ID_GENERALPCRDLG_PROGRESS_EXPER);
}

// 函数 CMonitorBaseInfoDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMonitorBaseInfoDlg::CreateBt()
{
	
}

// 函数 CMonitorBaseInfoDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCtrl、Create、_T。
void CMonitorBaseInfoDlg::CreateSt()
{
	CRect rcCtrl(0,0,0,0);

	m_stStartTm.Create(_T(""),WS_CHILD,rcCtrl,this,ID_MONITORBASEINFODLG_ST_STARTTM);
	m_stEndTm.Create(_T(""),WS_CHILD,rcCtrl,this,ID_MONITORBASEINFODLG_ST_ENDTM);
	m_stTemLid.Create(_T("--℃"),WS_CHILD,rcCtrl,this,ID_MONITORBASEINFODLG_ST_TEMLID);
	m_stTemTube.Create(_T("--℃"),WS_CHILD,rcCtrl,this,ID_MONITORBASEINFODLG_ST_TEMTUBE);
	m_stTotalSec.Create(_T(""),WS_CHILD,rcCtrl,this,ID_MONITORBASEINFODLG_ST_TOTALSEC);
	m_stRemainSec.Create(_T(""),WS_CHILD,rcCtrl,this,ID_MONITORBASEINFODLG_ST_REMAINSEC);
}

// 函数 CMonitorBaseInfoDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMonitorBaseInfoDlg::CreateCb()
{
	
}

// 函数 CMonitorBaseInfoDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMonitorBaseInfoDlg::CreateEd()
{
	
}

// 函数 CMonitorBaseInfoDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、SetTextClr1、RGB、SetMyFont。
void CMonitorBaseInfoDlg::InitDlg()
{
	int iFontH = 16 * m_dTxRatio;
	if(theApp.m_pLangInfo->GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
	}

	SetTextClr1(RGB(0X66,0X66,0X66));
	SetMyFont(m_stTxFont,iFontH);
}

// 函数 CMonitorBaseInfoDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitEd、InitCb、SetTextColor、RGB。
void CMonitorBaseInfoDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitEd();
	InitCb();

	//m_progressBar.SetTextColor(RGB(206,206,206));
	//m_progressBar.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CMonitorBaseInfoDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMonitorBaseInfoDlg::InitBt()
{
	
}

// 函数 CMonitorBaseInfoDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、RGB、SetTextColor、SetMyFont、SetBkColor、SetBDynamic。
void CMonitorBaseInfoDlg::InitSt()
{
	int iFontH = 16 * m_dTxRatio;
	if(theApp.m_pLangInfo->GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
	}

	DWORD clrTx = RGB(0X66,0X66,0X66);

	m_stStartTm.SetTextColor(clrTx);
	m_stStartTm.SetMyFont(m_stTxFont,iFontH);
	m_stStartTm.SetBkColor(RGB(0XFF,0XFF,0XFF));
	m_stStartTm.SetBDynamic(TRUE);

	m_stEndTm.SetTextColor(clrTx);
	m_stEndTm.SetMyFont(m_stTxFont,iFontH);
	m_stEndTm.SetBkColor(RGB(0XFF,0XFF,0XFF));
	m_stEndTm.SetBDynamic(TRUE);

	m_stTemLid.SetTextColor(clrTx);
	m_stTemLid.SetMyFont(m_stTxFont,iFontH);
	m_stTemLid.SetBkColor(RGB(0XFF,0XFF,0XFF));
	m_stTemLid.SetBDynamic(TRUE);

	m_stTemTube.SetTextColor(clrTx);
	m_stTemTube.SetMyFont(m_stTxFont,iFontH);
	m_stTemTube.SetBkColor(RGB(0XFF,0XFF,0XFF));
	m_stTemTube.SetBDynamic(TRUE);

	m_stTotalSec.SetTextColor(clrTx);
	m_stTotalSec.SetMyFont(m_stTxFont,iFontH);
	m_stTotalSec.SetBkColor(RGB(0XFF,0XFF,0XFF));
	m_stTotalSec.SetBDynamic(TRUE);

	m_stRemainSec.SetTextColor(clrTx);
	m_stRemainSec.SetMyFont(m_stTxFont,iFontH);
	m_stRemainSec.SetBkColor(RGB(0XFF,0XFF,0XFF));
	m_stRemainSec.SetBDynamic(TRUE);
}

// 函数 CMonitorBaseInfoDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMonitorBaseInfoDlg::InitCb()
{
	return;
}

// 函数 CMonitorBaseInfoDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMonitorBaseInfoDlg::InitEd()
{

}

// 函数 CMonitorBaseInfoDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、GetBeEnglish、AddRectToDelete、SetWindowPos、CalcRectResult。
void CMonitorBaseInfoDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	int iTempInt1 = 169 * m_dHoriRatio,iTempInt2 = 24 * m_dVertRatio,iTempInt3 = 182 * m_dHoriRatio,iTempInt4 = 169 * m_dHoriRatio,iTempInt5 = 169 * m_dHoriRatio;
	
	if(theApp.GetBeEnglish())
	{
		iTempInt3 = 186 * m_dHoriRatio;
		iTempInt4 = 284 * m_dHoriRatio;
		iTempInt5 = 244 * m_dHoriRatio;
	}

	m_rcManage.AddRectToDelete(iTempInt1,55 * m_dVertRatio,iTempInt1,iTempInt2);
	m_stStartTm.SetWindowPos(this,iTempInt1,55 * m_dVertRatio,iTempInt1,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt1,86 * m_dVertRatio,iTempInt1,iTempInt2);
	m_stEndTm.SetWindowPos(this,iTempInt1,86 * m_dVertRatio,iTempInt1,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt5,152 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2);
	m_stTemLid.SetWindowPos(this,iTempInt5,152 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt4,183 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2);
	m_stTemTube.SetWindowPos(this,iTempInt4,183 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt3,249 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2);
	m_stTotalSec.SetWindowPos(this,iTempInt3,249 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt3,280 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2);
	m_stRemainSec.SetWindowPos(this,iTempInt3,280 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);

	m_rcManage.CalcRectResult();

	return;
}

// 函数 CMonitorBaseInfoDlg::ResetCtrlPos
// 作用：更新或清除ResetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、ClearRectToDelete、GetBeEnglish、AddRectToDelete、SetWindowPos、CalcRectResult。
void CMonitorBaseInfoDlg::ResetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();

	int iTempInt1 = 169 * m_dHoriRatio,iTempInt2 = 24 * m_dVertRatio,iTempInt3 = 182 * m_dHoriRatio,iTempInt4 = 169 * m_dHoriRatio,iTempInt5 = 169 * m_dHoriRatio;

	if(theApp.GetBeEnglish())
	{
		iTempInt3 = 186 * m_dHoriRatio;
		iTempInt4 = 284 * m_dHoriRatio;
		iTempInt5 = 244 * m_dHoriRatio;
	}

	m_rcManage.AddRectToDelete(iTempInt1,55 * m_dVertRatio,iTempInt1,iTempInt2);
	m_stStartTm.SetWindowPos(this,iTempInt1,55 * m_dVertRatio,iTempInt1,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt1,86 * m_dVertRatio,iTempInt1,iTempInt2);
	m_stEndTm.SetWindowPos(this,iTempInt1,86 * m_dVertRatio,iTempInt1,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt5,152 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2);
	m_stTemLid.SetWindowPos(this,iTempInt5,152 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt4,183 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2);
	m_stTemTube.SetWindowPos(this,iTempInt4,183 * m_dVertRatio,60 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt3,249 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2);
	m_stTotalSec.SetWindowPos(this,iTempInt3,249 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);
	m_rcManage.AddRectToDelete(iTempInt3,280 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2);
	m_stRemainSec.SetWindowPos(this,iTempInt3,280 * m_dVertRatio,90 * m_dHoriRatio,iTempInt2,SWP_NOZORDER);

	m_rcManage.CalcRectResult();

	return;
}

// 函数 CMonitorBaseInfoDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CMonitorBaseInfoDlg::ShowCtrl()
{
	m_stStartTm.ShowWindow(SW_SHOW);
	m_stEndTm.ShowWindow(SW_SHOW);
	m_stTemLid.ShowWindow(SW_SHOW);
	m_stTemTube.ShowWindow(SW_SHOW);
	m_stTotalSec.ShowWindow(SW_SHOW);
	m_stRemainSec.ShowWindow(SW_SHOW);
}

// 函数 CMonitorBaseInfoDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance。
void CMonitorBaseInfoDlg::SetCtrlText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	if(NULL == pLangInfo)
	{
		return;
	}

	return;
}

// 函数 CMonitorBaseInfoDlg::SetCtrlEnableState
// 作用：设置SetCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMonitorBaseInfoDlg::SetCtrlEnableState(BOOL bEnabled)
{
	
}

// 函数 CMonitorBaseInfoDlg::ClearPage
// 作用：更新或清除ClearPage。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowText、_T。
void CMonitorBaseInfoDlg::ClearPage()
{
	m_stStartTm.SetWindowText(_T(""));
	m_stEndTm.SetWindowText(_T("")); 
	m_stTemLid.SetWindowText(_T("--℃")); 
	m_stTemTube.SetWindowText(_T("--℃")); 
	m_stTotalSec.SetWindowText(_T("")); 
	m_stRemainSec.SetWindowText(_T("")); 
}

// 函数 CMonitorBaseInfoDlg::SetMonitorBaseInfo
// 作用：设置SetMonitorBaseInfo。
// 参数：pExpInfo：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetWindowText、GetStartTime、GetEndTime、SecondToHourMinuteSecond、GetTotalSec、GetRemainSec。
int CMonitorBaseInfoDlg::SetMonitorBaseInfo(CExperimentInfo* pExpInfo)
{
	if(NULL == pExpInfo)
	{
		return -1;
	}

	m_stStartTm.SetWindowText(pExpInfo->GetStartTime());
	m_stEndTm.SetWindowText(pExpInfo->GetEndTime());
	m_stTotalSec.SetWindowText(SecondToHourMinuteSecond(pExpInfo->GetTotalSec()));
	m_stRemainSec.SetWindowText(SecondToHourMinuteSecond(pExpInfo->GetRemainSec()));
}

// 函数 CMonitorBaseInfoDlg::RefreshLanguageDisplay
// 作用：更新或清除RefreshLanguageDisplay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetBeEnglish、SetMyFont、ResetCtrlPos。
int CMonitorBaseInfoDlg::RefreshLanguageDisplay()
{
	BOOL bEnglish = theApp.m_pLangInfo->GetBeEnglish();

	int iFontH = 16 * m_dTxRatio;
	if(bEnglish)
	{
		iFontH = 17 * m_dTxRatio;
	}

	SetMyFont(m_stTxFont,iFontH);

	iFontH = 16 * m_dTxRatio;
	if(bEnglish)
	{
		iFontH = 17 * m_dTxRatio;
	}
	m_stStartTm.SetMyFont(m_stTxFont,iFontH);
	m_stEndTm.SetMyFont(m_stTxFont,iFontH);
	m_stTemLid.SetMyFont(m_stTxFont,iFontH);
	m_stTemTube.SetMyFont(m_stTxFont,iFontH);
	m_stTotalSec.SetMyFont(m_stTxFont,iFontH);
	m_stRemainSec.SetMyFont(m_stTxFont,iFontH);

	ResetCtrlPos();

	return 0;
}


