// 【交接】 GeneralPcr\CrossSetDlg.cpp
// 作用：CrossSetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CCrossSetDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_CREATE、ON_WM_LBUTTONDOWN。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "CrossSetDlg.h"
#include "GeneralPcr.h"

// CCrossSetDlg dialog
IMPLEMENT_DYNAMIC(CCrossSetDlg, CDialogEx)

// 函数 CCrossSetDlg::CCrossSetDlg
// 作用：执行CCrossSetDlg。
// 参数：pExpData：指针，指向调用方传入的对象；pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCrossSetDlg::CCrossSetDlg(CExperimentData* pExpData,CWnd* pParent /*=NULL*/)
	: CDialogEx(CCrossSetDlg::IDD, pParent)
{
	m_frameWidth = 1;
	m_roundValue = 10;
	m_iWndWidth = 865;
	m_iWndHeight = 386;
	m_iCaptionHeight = 52;
	m_pExpData = pExpData;
	m_bChanged = FALSE;
}

// 函数 CCrossSetDlg::~CCrossSetDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCrossSetDlg::~CCrossSetDlg()
{

}

// 函数 CCrossSetDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CCrossSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCrossSetDlg, CDialogEx)
	ON_WM_ERASEBKGND() 
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(ID_CROSSSETDLG_BT_SAVE,&CCrossSetDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_CROSSSETDLG_BT_CANCEL,&CCrossSetDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

// 函数 CCrossSetDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetInstance、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
BOOL CCrossSetDlg::OnEraseBkgnd(CDC* pDC)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	double dHoriRatio = m_dHoriRatio;
	double dVertRatio = m_dVertRatio;

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

	memDc.SetBkMode(TRANSPARENT);
	memDc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);
	memDc2.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(0,0,0));

	BLENDFUNCTION blendFunc;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.SourceConstantAlpha = CLRALPHAVALUE;
	blendFunc.AlphaFormat = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	BOOL ret = memDc.AlphaBlend(0,0,rect.Width(),rect.Height(),&memDc2,0,0,rect.Width(),rect.Height(),blendFunc);

	CRect rcUseful;
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2 - m_iWndWidth / 5 * 2.2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;

	CPen pen;
	CPen* pOldPen = NULL;

	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top + m_iCaptionHeight,rcUseful.Width(),rcUseful.Height() - m_iCaptionHeight,0,0,m_roundValue,m_roundValue,FALSE,Color(197,197,197),m_frameWidth,TRUE,Color(255,255,255),1);
	DrawRoundRectangleNew(&memDc,rcUseful.left,rcUseful.top,rcUseful.Width(),m_iCaptionHeight,m_roundValue,m_roundValue,0,0,FALSE,Color(3,91,199),2,TRUE,COLOR_SOFT_THEME,1);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(RGB(255,255,255));
	memDc.DrawText(pLangInfo->GetText(178),CRect(rcUseful.left + 10,rcUseful.top + 5,rcUseful.left + rcUseful.Width() - 10,rcUseful.top + m_iCaptionHeight - 5),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
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

// 函数 CCrossSetDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CCrossSetDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iWndWidth *= m_dHoriRatio;
	m_iWndHeight *= m_dVertRatio;
	m_iCaptionHeight *= m_dVertRatio;
	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CCrossSetDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PostMessage、MAKELPARAM。
void CCrossSetDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
#ifdef POPDLG_USESHADEBK
	CDialogEx::OnLButtonDown(nFlags, point);
#else
	if(point.y < m_iCaptionHeight)
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

// 函数 CCrossSetDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、GetParent、Width、Height、CenterWindow、CreateCtrl。
BOOL CCrossSetDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

#ifdef POPDLG_USESHADEBK
	SetWindowPos(GetParent(),theApp.m_rcWorkArea.left,theApp.m_rcWorkArea.top,theApp.m_rcWorkArea.Width(),theApp.m_rcWorkArea.Height(),SWP_NOZORDER);
#else
	SetWindowPos(GetParent(),0 * m_dHoriRatio,0 * m_dVertRatio,m_iWndWidth * m_dHoriRatio,m_iWndHeight * m_dVertRatio,SWP_NOZORDER);
	CenterWindow(GetParent());
#endif
	
	CreateCtrl();
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	SetCtrlText();
	SetCrossSetParam();

	ShowCtrl();

	return TRUE;
}

// 函数 CCrossSetDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateCkBt、CreateSt、CreateEd、CreateCb、CreateLst。
void CCrossSetDlg::CreateCtrl()
{
	CreateBt();
	CreateCkBt();
	CreateSt();
	CreateEd();
	CreateCb();
	CreateLst();
}

// 函数 CCrossSetDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CCrossSetDlg::CreateBt()
{
	m_btSave.Create(_T("保存"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_CROSSSETDLG_BT_SAVE);
	m_btCancel.Create(_T("取消"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_CROSSSETDLG_BT_CANCEL);
}

// 函数 CCrossSetDlg::CreateCkBt
// 作用：创建或加入CreateCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::CreateCkBt()
{
	
}

// 函数 CCrossSetDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::CreateSt()
{
	
}

// 函数 CCrossSetDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::CreateEd()
{
	
}

// 函数 CCrossSetDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::CreateCb()
{
	
}

// 函数 CCrossSetDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create。
void CCrossSetDlg::CreateLst()
{
	m_lstCrossSet.Create(IDD_MIDDLEDLG,this);
}

// 函数 CCrossSetDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、SetTextClr1、RGB、SetMyFont。
void CCrossSetDlg::InitDlg()
{
	int iFontH = 16 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
	}	

	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CCrossSetDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCkBt、InitSt、InitEd、InitCb、InitLst。
void CCrossSetDlg::InitCtrl()
{
	InitBt();
	InitCkBt();
	InitSt();
	InitEd();
	InitCb();
	InitLst();
}

// 函数 CCrossSetDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetRoundRectParam、RGB、SetBkColor、Color、SetBkColorEnd。
void CCrossSetDlg::InitBt()
{
	int iFontH = 18 * m_dTxRatio;

	m_btSave.SetMyFont(m_stTxFont,iFontH);
#ifndef GRADIENT_SOME_BTBK
	m_btSave.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),FALSE);
	m_btSave.SetBkColor(COLOR_BTBK_NORMAL,COLOR_BTBK_HOVER,COLOR_BTBK_CLICKED,COLOR_BTBK_DISABLED);
#else
	m_btSave.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
	m_btSave.SetBkColor(Color(0X38,0XE0,0XEF),Color(0X3A,0XEF,0XFF),COLOR_SOFT_THEME,Color(0XF1,0XF1,0XF1));
	m_btSave.SetBkColorEnd(COLOR_SOFT_THEME,Color(0X38,0XE0,0XEF),Color(0X02,0X8D,0X99),Color(0XD8,0XD8,0XD8));
#endif
	m_btSave.SetTextColor(RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XFF,0XFF,0XFF),RGB(0XC6,0XC4,0XC4));

	m_btCancel.SetMyFont(m_stTxFont,iFontH);
	m_btCancel.SetRoundRectParam(TRUE,RGB(0XFF,0XFF,0XFF),TRUE);
}

// 函数 CCrossSetDlg::InitCkBt
// 作用：初始化InitCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::InitCkBt()
{
	
}

// 函数 CCrossSetDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::InitSt()
{
	
}

// 函数 CCrossSetDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::InitEd()
{
	
}

// 函数 CCrossSetDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCrossSetDlg::InitCb()
{
	
}

// 函数 CCrossSetDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetBeEnglish、SetHeaderHeight、SetMyHeaderFont、SetHeaderBkColor、RGB、SetHeaderTextColor。
void CCrossSetDlg::InitLst()
{
	int iFontH = 15 * m_dTxRatio;
	int iFontH2 = 16 * m_dTxRatio;
	if(theApp.GetBeEnglish())
	{
		iFontH = 17 * m_dTxRatio;
		iFontH2 = 17 * m_dTxRatio;
	}

	m_lstCrossSet.SetHeaderHeight(28 * m_dVertRatio);
	m_lstCrossSet.SetMyHeaderFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_lstCrossSet.SetHeaderBkColor(RGB(228,231,236));
	m_lstCrossSet.SetHeaderTextColor(RGB(0X59,0X59,0X59));
	m_lstCrossSet.SetMyTitleFont(m_stTxFont,iFontH,FW_BOLD,TYPE_PIXEL);
	m_lstCrossSet.SetItemHeight(30 * m_dVertRatio);
	m_lstCrossSet.SetBeShowRowSelectState(FALSE);

	m_lstCrossSet.m_horiScroll.m_arrowWH = 28 * m_dHoriRatio;
	m_lstCrossSet.m_horiScroll.m_scrollH = 28 * m_dVertRatio;
	m_lstCrossSet.m_vertScroll.m_arrowWH = 28 * m_dHoriRatio;
	m_lstCrossSet.m_vertScroll.m_scrollW = 28 * m_dVertRatio;
	m_lstCrossSet.SetMyFont(m_stTxFont,iFontH2,FW_NORMAL,TYPE_PIXEL);
	m_lstCrossSet.SetTextClr1(RGB(0X39,0X45,0X65));

	m_lstCrossSet.SetFuncEditCtrlFont(m_stTxFont,iFontH2,FW_NORMAL,TYPE_PIXEL);

	return;
}

// 函数 CCrossSetDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、Width、Height、SetWindowPos。
void CCrossSetDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	CRect rcUseful;
#ifdef POPDLG_USESHADEBK
	rcUseful.left = rect.left + (rect.Width() - m_iWndWidth) / 2 - m_iWndWidth / 5 * 2.2;
	rcUseful.top = rect.top + (rect.Height() - m_iWndHeight) / 2;
	rcUseful.right = rcUseful.left + m_iWndWidth;
	rcUseful.bottom = rcUseful.top + m_iWndHeight;
#endif

	m_lstCrossSet.SetWindowPos(this,rcUseful.left + 30 * m_dHoriRatio,rcUseful.top + 90 * m_dVertRatio,809 * m_dHoriRatio,210 * m_dVertRatio,SWP_NOZORDER);
	m_btSave.SetWindowPos(this,rcUseful.left + 617 * m_dHoriRatio,rcUseful.top + 334 * m_dVertRatio,90 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);
	m_btCancel.SetWindowPos(this,rcUseful.left + 731 * m_dHoriRatio,rcUseful.top + 334 * m_dVertRatio,90 * m_dHoriRatio,40 * m_dVertRatio,SWP_NOZORDER);
}

// 函数 CCrossSetDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CCrossSetDlg::ShowCtrl()
{
	m_lstCrossSet.ShowWindow(SW_SHOW);

	m_btSave.ShowWindow(SW_SHOW);
	m_btCancel.ShowWindow(SW_SHOW);

	return;
}

// 函数 CCrossSetDlg::SetCtrlText
// 作用：设置SetCtrlText。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、SetWindowText、GetText。
void CCrossSetDlg::SetCtrlText()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_btSave.SetWindowText(pLangInfo->GetText(148));
	m_btCancel.SetWindowText(pLangInfo->GetText(150));

	return;
}

// 函数 CCrossSetDlg::OnBnClickedSave
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 EndEDit、GetCrossSetParam、OnOK。
void CCrossSetDlg::OnBnClickedSave()
{
	m_lstCrossSet.EndEDit();
	GetCrossSetParam();
	OnOK();
	return;
}

// 函数 CCrossSetDlg::OnBnClickedCancel
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 OnCancel。
void CCrossSetDlg::OnBnClickedCancel()
{
	OnCancel();
	return;
}

// 函数 CCrossSetDlg::SetRoundRect
// 作用：设置SetRoundRect。
// 参数：x；y。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetClientRect、CreateRoundRectRgn、SetWindowRgn。
BOOL CCrossSetDlg::SetRoundRect(int x /*= 5*/,int y /*= 5*/)
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

// 函数 CCrossSetDlg::SetCrossSetParam
// 作用：设置SetCrossSetParam。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCrosstalkPara、GetChannelCount、SetColumnRowNum、strTemp、_T、Format。
int CCrossSetDlg::SetCrossSetParam()
{
	if(NULL == m_pExpData)
	{
		return -1;
	}

	float** ppCrosstalkPara = m_pExpData->GetCrosstalkPara();
	if(NULL == ppCrosstalkPara)
	{
		return -2;
	}

	int iChanCount = m_pExpData->GetChannelCount();

	//PS96不显示校准通道的串扰信息
#ifdef PS96INSTRUMENT
	--iChanCount;
#endif

	if(iChanCount < 1)
	{
		return -3;
	}

	//设置行列数
	SetColumnRowNum(iChanCount);

	CString strTemp(_T(""));
	for(int i = 0;i < iChanCount;++i)
	{
		for(int j = 0;j < iChanCount;++j)
		{
			strTemp.Format(_T("%.3lf"),ppCrosstalkPara[i][j]);
			m_lstCrossSet.SetItemText(i,j + 1,strTemp);
		}
	}

	m_lstCrossSet.BottomBlankSetAutoFitHeight();

	m_lstCrossSet.Invalidate(FALSE);
	
	return 0;
}

// 函数 CCrossSetDlg::GetCrossSetParam
// 作用：读取GetCrossSetParam。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCrosstalkPara、GetRowNum、GetColNum、_ttof、GetItemText。
int CCrossSetDlg::GetCrossSetParam()
{
	float** ppCrosstalkPara = m_pExpData->GetCrosstalkPara();
	if(NULL == ppCrosstalkPara)
	{
		return -1;
	}

	int iChanCount = m_lstCrossSet.GetRowNum();
	if(iChanCount < 1)
	{
		return -2;
	}

	int iColumnNum = m_lstCrossSet.GetColNum();
	if(iChanCount != iColumnNum - 1)
	{
		return -3;
	}

	float* pNewData = new float[iChanCount * iChanCount];
	if(NULL == pNewData)
	{
		return -4;
	}

	for(int i = 0;i < iChanCount;++i)
	{
		for(int j = 0;j < iChanCount;++j)
		{
			pNewData[i * iChanCount + j] = _ttof(m_lstCrossSet.GetItemText(i,j + 1));
		}
	}

	for(int i = 0;i < iChanCount;++i)
	{
		for(int j = 0;j < iChanCount;++j)
		{
			if(pNewData[i * iChanCount + j] != ppCrosstalkPara[i][j])
			{
				m_bChanged = TRUE;
				goto COMPAREEND;
			}
		}
	}
	
COMPAREEND:
	if(m_bChanged)
	{
		for(int i = 0;i < iChanCount;++i)
		{
			for(int j = 0;j < iChanCount;++j)
			{
				ppCrosstalkPara[i][j] = pNewData[i * iChanCount + j];
			}
		}
	}

	delete [] pNewData;

	return 0;
}

// 函数 CCrossSetDlg::SetColumnRowNum
// 作用：设置SetColumnRowNum。
// 参数：iChanNum：整数；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetInstance、strTemp、_T、str1、InsertColumn、GetText。
int CCrossSetDlg::SetColumnRowNum(int iChanNum,BOOL bRedraw /*= FALSE*/)
{
	if(iChanNum < 1)
	{
		return -1;
	}

	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	
	CString strTemp(_T("")),str1(_T("通道"));
	m_lstCrossSet.InsertColumn(0,pLangInfo->GetText(51));

	CMaxMinInfo maxMinInfo;
	maxMinInfo.SetBeOnlyFloatNumber(TRUE);
	maxMinInfo.SetBeSetMinValue(TRUE);
	maxMinInfo.SetMinValue(0);
	maxMinInfo.SetBeSetMaxValue(TRUE);
	maxMinInfo.SetMaxValue(1);
	maxMinInfo.SetBeMaxMinSimultaneousEffect(TRUE);
	
	vector<CString> vecChanDyeName = m_pExpData->GetChannelDyeName();

	str1 = pLangInfo->GetText(51);
	for(int i = 0;i < iChanNum;++i)
	{
		if(i < vecChanDyeName.size())
		{
			strTemp = vecChanDyeName[i];
		}
		else
		{
			strTemp.Format(_T("%s%d"),str1,i + 1);
		}

		m_lstCrossSet.InsertColumn(i + 1,strTemp);
		m_lstCrossSet.SetColumnEditable(i + 1,TRUE);
		m_lstCrossSet.SetColumnMaxMinInfo(i + 1,maxMinInfo);
	}

	for(int i = 0;i < iChanNum;++i)
	{
		m_lstCrossSet.InsertRowSetHeight(i,30 * m_dVertRatio,FALSE);

		if(i < vecChanDyeName.size())
		{
			strTemp = vecChanDyeName[i];
		}
		else
		{
			strTemp.Format(_T("%s%d"),str1,i + 1);
		}

		m_lstCrossSet.SetItemText(i,0,strTemp);
		m_lstCrossSet.SetCellDisableState(i,i + 1,TRUE);
	}

	//设置列宽
	int iWidth = 809 * m_dHoriRatio;
	int iTempInt = 87 * m_dHoriRatio;

	m_lstCrossSet.SetColumnWidth(0,iTempInt);
	iWidth -= iTempInt;

	iTempInt = 120 * m_dHoriRatio;
	if(iChanNum > 0)
	{
		iTempInt = iWidth / iChanNum;
	}

	for(int i = 0;i < iChanNum;++i)
	{
		if(i == iChanNum - 1)
		{
			iWidth -= m_lstCrossSet.GetFrameLineWidth() * 2;
			m_lstCrossSet.SetColumnWidth(i + 1,iWidth);
		}
		else
		{
			m_lstCrossSet.SetColumnWidth(i + 1,iTempInt);
			iWidth -= iTempInt;
		}
	}
	
	if(bRedraw && NULL != m_lstCrossSet.GetSafeHwnd())
	{
		m_lstCrossSet.Invalidate(FALSE);
	}

	return 0;
}

