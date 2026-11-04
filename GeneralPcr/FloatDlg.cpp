// 【交接】 GeneralPcr\FloatDlg.cpp
// 作用：FloatDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CFloatDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_CREATE、ON_WM_LBUTTONDOWN。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "FloatDlg.h"
#include "GeneralPcr.h"

// CFloatDlg dialog
IMPLEMENT_DYNAMIC(CFloatDlg, CDialogEx)

// 函数 CFloatDlg::CFloatDlg
// 作用：执行CFloatDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CFloatDlg::CFloatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFloatDlg::IDD, pParent)
{
	m_frameWidth = 2;
	m_roundValue = 4;
	m_iWndWidth = 136;
	m_iWndHeight = 136;
	m_iCaptionHeight = 20;
	m_pParent = pParent;
	m_iHoriDotNum = 0;
	m_iVertDotNum = 2;
}

// 函数 CFloatDlg::~CFloatDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CFloatDlg::~CFloatDlg()
{

}

// 函数 CFloatDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CFloatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFloatDlg, CDialogEx)
	ON_WM_ERASEBKGND() 
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_SHOWWINDOW()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// 函数 CFloatDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CFloatDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.BitBlt(0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);

	CPen pen;
	CPen* pOldPen = NULL;
	DrawRoundRectangleNew(&memDc,2 + m_frameWidth,2 + m_frameWidth,rect.Width() - m_frameWidth * 2 - 2,rect.Height() - m_frameWidth * 2 - 2,m_roundValue,m_roundValue,m_roundValue,m_roundValue,TRUE,Color(233,233,233),m_frameWidth,TRUE,Color(0XFF,0XFF,0XFF),1);

	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);

	DrawTipText(&memDc);

	memDc.SelectObject(pOldFont);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);
	
	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CFloatDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CFloatDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iWndWidth *= m_dHoriRatio;
	m_iWndHeight *= m_dVertRatio;
	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CFloatDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::OnLButtonDown。
void CFloatDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags,point); 
}

// 函数 CFloatDlg::OnLButtonUp
// 作用：松开鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::OnLButtonUp。
void CFloatDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags,point); 
}

// 函数 CFloatDlg::OnSetFocus
// 作用：响应 Windows 或自定义消息 OnSetFocus。
// 参数：pOldWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::OnSetFocus(CWnd* pOldWnd)
{
	return;
}

// 函数 CFloatDlg::OnKillFocus
// 作用：响应 Windows 或自定义消息 OnKillFocus。
// 参数：pNewWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 ReleaseCapture、ShowWindow。
void CFloatDlg::OnKillFocus(CWnd* pNewWnd)
{
	ReleaseCapture();
	ShowWindow(SW_HIDE);

	return;
}

// 函数 CFloatDlg::OnShowWindow
// 作用：响应 Windows 或自定义消息 OnShowWindow。
// 参数：bShow：是或否；nStatus：整数。
// 返回：没有返回值。
// 过程：函数里会调用 SetCapture。
void CFloatDlg::OnShowWindow(BOOL bShow,UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow,nStatus);

	if(bShow)
	{
		SetCapture();
	}
	return;
}

// 函数 CFloatDlg::OnMouseMove
// 作用：鼠标在窗口上移动。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、PtInRect、ReleaseCapture、ShowWindow。
void CFloatDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	if(!rect.PtInRect(point))
	{
		ReleaseCapture();
		ShowWindow(SW_HIDE);
	}
	return;
}

// 函数 CFloatDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、GetParent、CreateCtrl、InitDlg、InitCtrl、SetCtrlPos。
BOOL CFloatDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	SetWindowPos(GetParent(),0,0,m_iWndWidth,m_iWndHeight,SWP_NOZORDER);

	CreateCtrl();
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	ShowCtrl();

	return TRUE;
}

// 函数 CFloatDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateCkBt、CreateSt、CreateEd、CreateCb、CreateLst。
void CFloatDlg::CreateCtrl()
{
	CreateBt();
	CreateCkBt();
	CreateSt();
	CreateEd();
	CreateCb();
	CreateLst();
}

// 函数 CFloatDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::CreateBt()
{
	
}

// 函数 CFloatDlg::CreateCkBt
// 作用：创建或加入CreateCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::CreateCkBt()
{
	
}

// 函数 CFloatDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::CreateSt()
{
	
}

// 函数 CFloatDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::CreateEd()
{
	
}

// 函数 CFloatDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::CreateCb()
{
	
}

// 函数 CFloatDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::CreateLst()
{
	
}

// 函数 CFloatDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CFloatDlg::InitDlg()
{
	SetTextClr1(RGB(0X39,0X45,0X65));
	SetMyFont(m_stTxFont,16 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CFloatDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCkBt、InitSt、InitEd、InitCb、InitLst。
void CFloatDlg::InitCtrl()
{
	InitBt();
	InitCkBt();
	InitSt();
	InitEd();
	InitCb();
	InitLst();
}

// 函数 CFloatDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::InitBt()
{
	
}

// 函数 CFloatDlg::InitCkBt
// 作用：初始化InitCkBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::InitCkBt()
{
	
}

// 函数 CFloatDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::InitSt()
{
	
}

// 函数 CFloatDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::InitEd()
{
	
}

// 函数 CFloatDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::InitCb()
{
	
}

// 函数 CFloatDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::InitLst()
{
	return;
}

// 函数 CFloatDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::SetCtrlPos()
{
	
}

// 函数 CFloatDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::ShowCtrl()
{
	return;
}

// 函数 CFloatDlg::SetRoundRect
// 作用：设置SetRoundRect。
// 参数：x；y。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetClientRect、CreateRoundRectRgn、SetWindowRgn。
BOOL CFloatDlg::SetRoundRect(int x /*= 5*/,int y /*= 5*/)
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

// 函数 CFloatDlg::DrawTipText
// 作用：绘制DrawTipText。
// 参数：pDc：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 strTemp、_T、strFormat、GetBeXAxisMillisecondTime、strTime、int。
int CFloatDlg::DrawTipText(CDC* pDc)
{
	if(NULL == pDc)
	{
		return -1;
	}

	CString strTemp(_T("")),strFormat(_T(""));

	if(m_lineInfo.GetBeXAxisMillisecondTime())
	{
		CString strTime(_T(""));
		int curSecond = int(m_ptDotInfo.m_X) / 1000;
		strTime.Format(_T("%01d:%02d:%02d"),curSecond / 3600,(curSecond % 3600) / 60,curSecond % 60);

		strFormat.Format(_T("(%%s,%%.%dlf)"),m_iVertDotNum);
		strTemp.Format(strFormat,strTime,m_ptDotInfo.m_Y);
	}
	else
	{
		strFormat.Format(_T("(%%.%dlf,%%.%dlf)"),m_iHoriDotNum,m_iVertDotNum);
		strTemp.Format(strFormat,m_ptDotInfo.m_X,m_ptDotInfo.m_Y);
	}

	CRect rect;
	GetClientRect(&rect);

	pDc->DrawText(m_lineInfo.m_strHoleTag,CRect(12 * m_dHoriRatio,12 * m_dVertRatio,rect.Width() - 12 * m_dHoriRatio,34 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	pDc->DrawText(m_lineInfo.m_strDyeName,CRect(12 * m_dHoriRatio,42 * m_dVertRatio,rect.Width() - 12 * m_dHoriRatio,64 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	pDc->DrawText(m_lineInfo.m_strTaget,CRect(12 * m_dHoriRatio,72 * m_dVertRatio,rect.Width() - 12 * m_dHoriRatio,94 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE );
	pDc->DrawText(strTemp,CRect(12 * m_dHoriRatio,102 * m_dVertRatio,rect.Width() - 12 * m_dHoriRatio,124 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE );
}

// 函数 CFloatDlg::SetHoriDotNum
// 作用：设置SetHoriDotNum。
// 参数：iData：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::SetHoriDotNum(int iData)
{
	if(iData < 0)
	{
		return;
	}
	m_iHoriDotNum = iData;
}

// 函数 CFloatDlg::GetHoriDotNum
// 作用：读取GetHoriDotNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CFloatDlg::GetHoriDotNum()
{
	return m_iHoriDotNum;
}

// 函数 CFloatDlg::SetVertDotNum
// 作用：设置SetVertDotNum。
// 参数：iData：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFloatDlg::SetVertDotNum(int iData)
{
	if(iData < 0)
	{
		return;
	}
	m_iVertDotNum = iData;
}

// 函数 CFloatDlg::GetVertDotNum
// 作用：读取GetVertDotNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CFloatDlg::GetVertDotNum()
{
	return m_iVertDotNum;
}





