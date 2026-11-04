// 【交接】 GeneralPcr\LisSetDlg.cpp
// 作用：LisSetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CLisSetDlg、CDialogEx、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_BN_CLICKED、END_MESSAGE_MAP。
// SkipDlg.cpp : implementation file
//

#include "stdafx.h"

#include "LisSetDlg.h"
#include "GeneralPcrDlg.h"
#include "GeneralPcr.h"

// CLisSetDlg dialog
IMPLEMENT_DYNAMIC(CLisSetDlg, CDialogEx)

// 函数 CLisSetDlg::CLisSetDlg
// 作用：执行CLisSetDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLisSetDlg::CLisSetDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLisSetDlg::IDD, pParent)
{
	
}

// 函数 CLisSetDlg::~CLisSetDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLisSetDlg::~CLisSetDlg()
{
}

// 函数 CLisSetDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CLisSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLisSetDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(ID_LISSETDLG_CKBT_LISCONNECT,&CLisSetDlg::OnBnClickedLisConnect)
	ON_BN_CLICKED(ID_LISSETDLG_CKBT_COM,&CLisSetDlg::OnBnClickedComMode)
	ON_BN_CLICKED(ID_LISSETDLG_CKBT_TCPIP,&CLisSetDlg::OnBnClickedTcpIpMode)
END_MESSAGE_MAP()

// 函数 CLisSetDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CLisSetDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(0,0,rect.Width(),rect.Height(),RGB(255,255,255));

	double dHoriRatio = m_dHoriRatio;
	double dVertRatio = m_dVertRatio;

	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(164,164,164));
	CPen* pOldPen = memDc.SelectObject(&pen);
	memDc.Rectangle(CRect(0,0,rect.Width(),rect.Height()));
	memDc.SelectObject(pOldPen);
	pen.DeleteObject();

	CBrush brush;
	brush.CreateSolidBrush(RGB(164,164,164));
	CRect rc2(36 * dHoriRatio,209 * dVertRatio,442 * dHoriRatio,626 * dVertRatio);
	memDc.FrameRect(&rc2,&brush);

	CRect rc3(506 * dHoriRatio,209 * dVertRatio,912 * dHoriRatio,626 * dVertRatio);
	memDc.FrameRect(&rc3,&brush);

	brush.DeleteObject();

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CLisSetDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 CreateCtrl、InitDlg、InitCtrl、SetCtrlPos、SetComCtrlEnableState、SetTcpCtrlEnableState。
BOOL CLisSetDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	CreateCtrl();
	InitDlg();
	InitCtrl();
	SetCtrlPos();

	if(theApp.m_lisSetInfo.m_bOpenLis)
	{
		if(theApp.m_lisSetInfo.m_bUseCom)
		{
			SetComCtrlEnableState(TRUE);
			SetTcpCtrlEnableState(FALSE);
		}
		else
		{
			SetComCtrlEnableState(FALSE);
			SetTcpCtrlEnableState(TRUE);
		}
	}
	else
	{
		EnableCtrl(FALSE);
	}

	ShowCtrl();

	return TRUE;
}

// 函数 CLisSetDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateCkbt、CreateSt、CreateEd、CreateCb。
void CLisSetDlg::CreateCtrl()
{
	CreateBt();
	CreateCkbt();
	CreateSt();
	CreateEd();
	CreateCb();
}

// 函数 CLisSetDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLisSetDlg::CreateBt()
{
	
}

// 函数 CLisSetDlg::CreateCkbt
// 作用：创建或加入CreateCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CLisSetDlg::CreateCkbt()
{
	m_ckbtLisConnect.Create(_T("LIS通讯(单向)"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_LISSETDLG_CKBT_LISCONNECT);
	m_ckbtAutoUploadRst.Create(_T("自动上传结果"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_LISSETDLG_CKBT_AUTOPULOADRESULT);
	m_ckbtRecvSamData.Create(_T("接收样本信息"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_LISSETDLG_CKBT_RECVSAMDATA);

	m_ckbtCom.Create(_T("串口"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_LISSETDLG_CKBT_COM);
	m_ckbtTcpIp.Create(_T("TCP/IP"),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_LISSETDLG_CKBT_TCPIP);
}

// 函数 CLisSetDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CLisSetDlg::CreateSt()
{
	m_stRecvWaitSec.Create(_T("接收等待时间"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_RECVWAITSEC);
	m_stRecvWaitSecUnit.Create(_T("秒"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_WAITSECUNIT);
	m_stMaxTransTimes.Create(_T("最大传输次数"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_TARNSTIMES);

	m_stComId.Create(_T("端口号"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_COMID);
	m_stDataByteLen.Create(_T("数据位"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_DATABYTELEN);
	m_stStopByteLen.Create(_T("停止位"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_STOPBYTELEN);
	m_stPaud.Create(_T("波特率"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_PAUD);
	m_stCheckWay.Create(_T("奇偶位"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_CHECKWAY);

	m_stServerIp.Create(_T("服务器IP"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_SERVERIP);
	m_stServerPort.Create(_T("端  口"), WS_CHILD, CRect(10, 10, 120, 30), this,ID_LISSETDLG_ST_SERVERPORT);
}

// 函数 CLisSetDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、CRect。
void CLisSetDlg::CreateEd()
{
	m_edRecvWaitSec.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_LISSETDLG_ED_WAITSEC);
	m_edMaxSendTimes.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_LISSETDLG_ED_MAXSENDTIMES);
	m_edServerIp.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_LISSETDLG_ED_SERVERIP);
	m_edServerPort.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL, CRect(0, 0, 0, 0), this,ID_LISSETDLG_ED_SERVERPORT);
}

// 函数 CLisSetDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 rcCreate、Create。
void CLisSetDlg::CreateCb()
{
	CRect rcCreate(0,0,0,0);

	m_cbComId.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_LISSETDLG_CB_COMID);
	m_cbDataByteLen.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_LISSETDLG_CB_DATABYTELEN);
	m_cbStopByteLen.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_LISSETDLG_CB_STOPBYTELEN);
	m_cbPaud.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_LISSETDLG_CB_PUAD);
	m_cbCheckWay.Create(WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,rcCreate,this,ID_LISSETDLG_CB_CHECKWAY);
	return;
}

// 函数 CLisSetDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextClr1、RGB、SetMyFont。
void CLisSetDlg::InitDlg()
{
	SetTextClr1(RGB(86,86,86));
	SetMyFont(m_stTxFont,14,FW_BOLD,TYPE_PIXEL);
}

// 函数 CLisSetDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitCkbt、InitSt、InitEd、InitCb。
void CLisSetDlg::InitCtrl()
{
	InitBt();
	InitCkbt();
	InitSt();
	InitEd();
	InitCb();
}

// 函数 CLisSetDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLisSetDlg::InitBt()
{
	
}

// 函数 CLisSetDlg::InitCkbt
// 作用：初始化InitCkbt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetPngBkPic、_T、SetBeNeedRedrawBk、SetMyFont、SetMyFontChecked、SetBeParentProcessMouseClick。
void CLisSetDlg::InitCkbt()
{
	int fontH = 14 * m_dTxRatio;

	m_ckbtLisConnect.SetPngBkPic(_T("..\\BkPic\\开关.png"),4,30);
	m_ckbtLisConnect.SetBeNeedRedrawBk(TRUE);
	m_ckbtLisConnect.SetMyFont(m_stTxFont,14,FW_NORMAL,TYPE_PIXEL);
	m_ckbtLisConnect.SetMyFontChecked(m_stTxFont,14,FW_NORMAL,TYPE_PIXEL);
	m_ckbtLisConnect.SetBeParentProcessMouseClick(TRUE);
	m_ckbtLisConnect.SetTextColor(RGB(0x54,0x54,0x54),RGB(0x54,0x54,0x54));
	m_ckbtLisConnect.SetBtChecked(theApp.m_lisSetInfo.m_bOpenLis);

	m_ckbtAutoUploadRst.SetPngBkPic(_T("..\\BkPic\\开关.png"),4,30);
	m_ckbtAutoUploadRst.SetBeNeedRedrawBk(TRUE);
	m_ckbtAutoUploadRst.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtAutoUploadRst.SetMyFontChecked(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtAutoUploadRst.SetTextColor(RGB(0x54,0x54,0x54),RGB(0x54,0x54,0x54));

	m_ckbtRecvSamData.SetPngBkPic(_T("..\\BkPic\\开关.png"),4,30);
	m_ckbtRecvSamData.SetBeNeedRedrawBk(TRUE);
	m_ckbtRecvSamData.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtRecvSamData.SetMyFontChecked(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtRecvSamData.SetTextColor(RGB(0x54,0x54,0x54),RGB(0x54,0x54,0x54));
	
	m_ckbtCom.SetPngBkPic(_T("..\\BkPic\\单选-1.png"),2,16);
	m_ckbtCom.SetTextColor(RGB(86,86,86),RGB(86,86,86));
	m_ckbtCom.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtCom.SetBeNeedRedrawBk(TRUE);
	m_ckbtCom.SetBeParentProcessMouseClick(TRUE);
	m_ckbtCom.SetMyFontChecked(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtCom.SetTextColor(RGB(0x54,0x54,0x54),RGB(0x54,0x54,0x54));
	m_ckbtCom.SetBtChecked(theApp.m_lisSetInfo.m_bUseCom);
	m_ckbtCom.EnableWindow(!theApp.m_lisSetInfo.m_bUseCom);

	m_ckbtTcpIp.SetPngBkPic(_T("..\\BkPic\\单选-1.png"),2,16);
	m_ckbtTcpIp.SetTextColor(RGB(86,86,86),RGB(86,86,86));
	m_ckbtTcpIp.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtTcpIp.SetBeNeedRedrawBk(TRUE);
	m_ckbtTcpIp.SetBeParentProcessMouseClick(TRUE);
	m_ckbtTcpIp.SetBtChecked(!theApp.m_lisSetInfo.m_bUseCom);
	m_ckbtTcpIp.EnableWindow(theApp.m_lisSetInfo.m_bUseCom);
	m_ckbtTcpIp.SetMyFontChecked(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_ckbtTcpIp.SetTextColor(RGB(0x54,0x54,0x54),RGB(0x54,0x54,0x54));
}

// 函数 CLisSetDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextColor、RGB、SetWordStyle、SetMyFont。
void CLisSetDlg::InitSt()
{
	int fontH = 14 * m_dTxRatio;

	m_stRecvWaitSec.SetTextColor(RGB(0x54,0x54,0x54));
	m_stRecvWaitSec.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stRecvWaitSec.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stRecvWaitSecUnit.SetTextColor(RGB(0x54,0x54,0x54));
	m_stRecvWaitSecUnit.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stRecvWaitSecUnit.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stMaxTransTimes.SetTextColor(RGB(0x54,0x54,0x54));
	m_stMaxTransTimes.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stMaxTransTimes.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stComId.SetTextColor(RGB(0x54,0x54,0x54));
	m_stComId.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stComId.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stDataByteLen.SetTextColor(RGB(0x54,0x54,0x54));
	m_stDataByteLen.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stDataByteLen.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stStopByteLen.SetTextColor(RGB(0x54,0x54,0x54));
	m_stStopByteLen.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stStopByteLen.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stPaud.SetTextColor(RGB(0x54,0x54,0x54));
	m_stPaud.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stPaud.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stCheckWay.SetTextColor(RGB(0x54,0x54,0x54));
	m_stCheckWay.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stCheckWay.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stServerIp.SetTextColor(RGB(0x54,0x54,0x54));
	m_stServerIp.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stServerIp.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	
	m_stServerPort.SetTextColor(RGB(0x54,0x54,0x54));
	m_stServerPort.SetWordStyle(DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	m_stServerPort.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
}

// 函数 CLisSetDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 tempStr、_T、Format、SetMyFont、SetCfsTextClr、RGB。
void CLisSetDlg::InitEd()
{
	int fontH = 14 * m_dTxRatio;

	CString tempStr(_T(""));

	tempStr.Format(_T("%.1lf"),theApp.m_lisSetInfo.m_dRecvWaitMaxSec);
	m_edRecvWaitSec.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_edRecvWaitSec.SetCfsTextClr(RGB(0x54,0x54,0x54));
	m_edRecvWaitSec.SetMainWndBkColor(RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(246,246,246));
	m_edRecvWaitSec.SetText(tempStr);
	
	tempStr.Format(_T("%d"),theApp.m_lisSetInfo.m_maxTransferTimes);
	m_edMaxSendTimes.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_edMaxSendTimes.SetCfsTextClr(RGB(0x54,0x54,0x54));
	m_edMaxSendTimes.SetMainWndBkColor(RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(246,246,246));
	m_edMaxSendTimes.SetText(tempStr);
	
	m_edServerIp.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_edServerIp.SetCfsTextClr(RGB(0x54,0x54,0x54));
	m_edServerIp.SetMainWndBkColor(RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(246,246,246));
	m_edServerIp.SetText(theApp.m_lisSetInfo.m_strIpAddress);

	m_edServerPort.SetMyFont(m_stTxFont,fontH,FW_NORMAL,TYPE_PIXEL);
	m_edServerPort.SetCfsTextClr(RGB(0x54,0x54,0x54));
	m_edServerPort.SetMainWndBkColor(RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),RGB(246,246,246));
	m_edServerPort.SetText(theApp.m_lisSetInfo.m_strPort);
}

// 函数 CLisSetDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetWorkState、GetSystemComNames、size、InsertString、SetCurSel。
void CLisSetDlg::InitCb()
{
	int iFontH = 14 * CFontSet::m_dTxRatio;

	m_cbComId.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbComId.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbComId.SetWorkState(EWS_READONLY);
	m_cbComId.m_iLeftIndent = 10;
	m_cbComId.m_iRightIndent = 28;

	vector<CString> vecComName;
	GetSystemComNames(vecComName);
	for(int i = 0;i < vecComName.size();++i)
	{
		m_cbComId.InsertString(i,vecComName[i]);
	}
	if(vecComName.size() > 0)
	{
		int index = 0;
		BOOL bFind = FALSE;
		for(int i = 0;i < vecComName.size();++i)
		{
			if(vecComName[i] == theApp.m_lisSetInfo.m_strComId)
			{
				index = i;
				bFind = TRUE;
				break;
			}
		}

		if(bFind)
		{
			m_cbComId.SetCurSel(index);
		}
		else
		{
			m_cbComId.SetText(theApp.m_lisSetInfo.m_strComId);
		}
	}
	else
	{
		m_cbComId.SetText(theApp.m_lisSetInfo.m_strComId);
	}


	m_cbDataByteLen.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbDataByteLen.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbDataByteLen.SetWorkState(EWS_READONLY);
	m_cbDataByteLen.m_iLeftIndent = 10;
	m_cbDataByteLen.m_iRightIndent = 28;
	m_cbDataByteLen.InsertString(0,_T("8"));
	m_cbDataByteLen.SetCurSel(0);

	m_cbStopByteLen.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbStopByteLen.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbStopByteLen.SetWorkState(EWS_READONLY);
	m_cbStopByteLen.m_iLeftIndent = 10;
	m_cbStopByteLen.m_iRightIndent = 28;
	m_cbStopByteLen.InsertString(0,_T("0"));
	m_cbStopByteLen.InsertString(1,_T("1"));
	if(0 == theApp.m_lisSetInfo.m_dStopBit)
	{
		m_cbStopByteLen.SetCurSel(0);
	}
	else
	{
		m_cbStopByteLen.SetCurSel(1);
	}
	
	m_cbPaud.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbPaud.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbPaud.SetWorkState(EWS_READONLY);
	m_cbPaud.m_iLeftIndent = 10;
	m_cbPaud.m_iRightIndent = 28;
	m_cbPaud.InsertString(0,_T("4800"));
	m_cbPaud.InsertString(1,_T("9600"));
	m_cbPaud.InsertString(2,_T("19200"));
	m_cbPaud.InsertString(3,_T("38400"));
	m_cbPaud.InsertString(4,_T("115200"));
	if(4800 == theApp.m_lisSetInfo.m_baudRate)
	{
		m_cbPaud.SetCurSel(0);
	}
	else if(9600 == theApp.m_lisSetInfo.m_baudRate)
	{
		m_cbPaud.SetCurSel(1);
	}
	else if(19200 == theApp.m_lisSetInfo.m_baudRate)
	{
		m_cbPaud.SetCurSel(2);
	}
	else if(38400 == theApp.m_lisSetInfo.m_baudRate)
	{
		m_cbPaud.SetCurSel(3);
	}
	else if(115200 == theApp.m_lisSetInfo.m_baudRate)
	{
		m_cbPaud.SetCurSel(4);
	}

	m_cbCheckWay.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbCheckWay.m_selWnd.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_cbCheckWay.SetWorkState(EWS_READONLY);
	m_cbCheckWay.m_iLeftIndent = 10;
	m_cbCheckWay.m_iRightIndent = 28;
	m_cbCheckWay.InsertString(0,_T("NONE"));
	m_cbCheckWay.SetCurSel(0);

	return;
}

// 函数 CLisSetDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowPos。
void CLisSetDlg::SetCtrlPos()
{
	double dHoriRatio = m_dHoriRatio;
	double dVertRatio = m_dVertRatio;

	m_ckbtLisConnect.SetWindowPos(this,40 * dHoriRatio,32 * dVertRatio,165 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);

	m_ckbtAutoUploadRst.SetWindowPos(this,30 * dHoriRatio,108 * dVertRatio,200 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_ckbtRecvSamData.SetWindowPos(this,270 * dHoriRatio,108 * dVertRatio,200 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);

	m_ckbtCom.SetWindowPos(this,40 * dHoriRatio,177 * dVertRatio,100 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_ckbtTcpIp.SetWindowPos(this,502 * dHoriRatio,177 * dVertRatio,100 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);

	m_stRecvWaitSec.SetWindowPos(this,40 * dHoriRatio,77 * dVertRatio,105 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_stRecvWaitSecUnit.SetWindowPos(this,417 * dHoriRatio,77 * dVertRatio,20 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_stMaxTransTimes.SetWindowPos(this,40 * dHoriRatio,124 * dVertRatio,105 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);

	m_stComId.SetWindowPos(this,70 * dHoriRatio,239 * dVertRatio,76 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_stDataByteLen.SetWindowPos(this,70 * dHoriRatio,287 * dVertRatio,76 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_stStopByteLen.SetWindowPos(this,70 * dHoriRatio,336 * dVertRatio,76 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_stPaud.SetWindowPos(this,70 * dHoriRatio,384 * dVertRatio,76 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_stCheckWay.SetWindowPos(this,70 * dHoriRatio,432 * dVertRatio,76 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);

	m_stServerIp.SetWindowPos(this,536 * dHoriRatio,239 * dVertRatio,76 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_stServerPort.SetWindowPos(this,536 * dHoriRatio,287 * dVertRatio,76 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);

	m_edRecvWaitSec.SetWindowPos(this,147 * dHoriRatio,77 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_edMaxSendTimes.SetWindowPos(this,147 * dHoriRatio,124 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_edServerIp.SetWindowPos(this,615 * dHoriRatio,239 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_edServerPort.SetWindowPos(this,615 * dHoriRatio,287 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);

	m_cbComId.SetWindowPos(this,147 * dHoriRatio,239 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_cbDataByteLen.SetWindowPos(this,147 * dHoriRatio,287 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_cbStopByteLen.SetWindowPos(this,147 * dHoriRatio,336 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_cbPaud.SetWindowPos(this,147 * dHoriRatio,384 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
	m_cbCheckWay.SetWindowPos(this,147 * dHoriRatio,432 * dVertRatio,260 * dHoriRatio,28 * dVertRatio,SWP_NOZORDER);
}

// 函数 CLisSetDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow。
void CLisSetDlg::ShowCtrl()
{
	m_ckbtLisConnect.ShowWindow(SW_SHOW);

	m_ckbtCom.ShowWindow(SW_SHOW);
	m_ckbtTcpIp.ShowWindow(SW_SHOW);

	m_stComId.ShowWindow(SW_SHOW);
	m_stDataByteLen.ShowWindow(SW_SHOW);
	m_stStopByteLen.ShowWindow(SW_SHOW);
	m_stPaud.ShowWindow(SW_SHOW);
	m_stCheckWay.ShowWindow(SW_SHOW);

	m_stServerIp.ShowWindow(SW_SHOW);
	m_stServerPort.ShowWindow(SW_SHOW);

	m_edServerIp.ShowWindow(SW_SHOW);
	m_edServerPort.ShowWindow(SW_SHOW);

	m_cbComId.ShowWindow(SW_SHOW);
	m_cbDataByteLen.ShowWindow(SW_SHOW);
	m_cbStopByteLen.ShowWindow(SW_SHOW);
	m_cbPaud.ShowWindow(SW_SHOW);
	m_cbCheckWay.ShowWindow(SW_SHOW);
}

// 函数 CLisSetDlg::OnBnClickedLisConnect
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCheckState、SetBtChecked、EnableCtrl。
void CLisSetDlg::OnBnClickedLisConnect()
{
	BOOL bCkbtState = m_ckbtLisConnect.GetCheckState();
	m_ckbtLisConnect.SetBtChecked(!bCkbtState,TRUE);
	
	EnableCtrl(!bCkbtState);
	return;
}

// 函数 CLisSetDlg::OnBnClickedComMode
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCheckState、SetBtChecked、EnableWindow、SetComCtrlEnableState、SetTcpCtrlEnableState。
void CLisSetDlg::OnBnClickedComMode()
{
	BOOL bCkbtState = m_ckbtCom.GetCheckState();
	m_ckbtCom.SetBtChecked(!bCkbtState,TRUE);
	m_ckbtCom.EnableWindow(FALSE);

	m_ckbtTcpIp.SetBtChecked(bCkbtState,TRUE);
	m_ckbtTcpIp.EnableWindow(TRUE);

	SetComCtrlEnableState(TRUE);
	SetTcpCtrlEnableState(FALSE);
}

// 函数 CLisSetDlg::OnBnClickedTcpIpMode
// 作用：响应按钮点击。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCheckState、SetBtChecked、EnableWindow、SetComCtrlEnableState、SetTcpCtrlEnableState。
void CLisSetDlg::OnBnClickedTcpIpMode()
{
	BOOL bCkbtState = m_ckbtTcpIp.GetCheckState();
	m_ckbtTcpIp.SetBtChecked(!bCkbtState,TRUE);
	m_ckbtTcpIp.EnableWindow(FALSE);

	m_ckbtCom.SetBtChecked(bCkbtState,TRUE);
	m_ckbtCom.EnableWindow(TRUE);

	SetComCtrlEnableState(FALSE);
	SetTcpCtrlEnableState(TRUE);
}

// 函数 CLisSetDlg::SaveLisSet
// 作用：把SaveLisSet写入文件、仪器或界面。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 tempStr、_T、GetCheckState、GetText、_ttoi、GetWindowText。
void CLisSetDlg::SaveLisSet()
{
	CString tempStr(_T(""));

	theApp.m_lisSetInfo.m_bOpenLis = m_ckbtLisConnect.GetCheckState();

	tempStr = m_edRecvWaitSec.GetText();
	theApp.m_lisSetInfo.m_dRecvWaitMaxSec = _ttoi(tempStr); 

	tempStr = m_edMaxSendTimes.GetText();
	theApp.m_lisSetInfo.m_maxTransferTimes = _ttoi(tempStr); 

	theApp.m_lisSetInfo.m_bUseCom = m_ckbtCom.GetCheckState();

	m_cbComId.GetWindowText(theApp.m_lisSetInfo.m_strComId);

	m_cbDataByteLen.GetWindowText(tempStr);
	theApp.m_lisSetInfo.m_dataNum = _ttoi(tempStr);

	m_cbStopByteLen.GetWindowText(tempStr);
	theApp.m_lisSetInfo.m_dStopBit = _ttof(tempStr);

	m_cbPaud.GetWindowText(tempStr);
	theApp.m_lisSetInfo.m_baudRate = _ttof(tempStr);

	int curSel = m_cbCheckWay.GetCurSel();
	if(-1 == curSel)
	{
		curSel = 0;
	}
	theApp.m_lisSetInfo.m_eCheckWay = (ECHEKCWAY)curSel;

	theApp.m_lisSetInfo.m_strIpAddress = m_edServerIp.GetText();
	theApp.m_lisSetInfo.m_strPort = m_edServerPort.GetText();

	//theApp.SaveLisSetInfo();
}

// 函数 CLisSetDlg::EnableCtrl
// 作用：改变EnableCtrl的显示或可用状态。
// 参数：bEnable：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable、EnableWindow、SetComCtrlEnableState、SetTcpCtrlEnableState。
void CLisSetDlg::EnableCtrl(BOOL bEnable)
{
	m_edRecvWaitSec.SetBeEditable(bEnable,TRUE);
	m_edMaxSendTimes.SetBeEditable(bEnable,TRUE);

	if(bEnable)
	{
		m_ckbtCom.EnableWindow(TRUE);
		m_ckbtTcpIp.EnableWindow(TRUE);

		if(theApp.m_lisSetInfo.m_bUseCom)
		{
			SetComCtrlEnableState(TRUE);
			SetTcpCtrlEnableState(FALSE);
		}
		else
		{
			SetComCtrlEnableState(FALSE);
			SetTcpCtrlEnableState(TRUE);
		}
	}
	else
	{
		m_ckbtCom.EnableWindow(FALSE);
		m_ckbtTcpIp.EnableWindow(FALSE);

		m_edServerIp.SetBeEditable(FALSE,TRUE);
		m_edServerPort.SetBeEditable(FALSE,TRUE);
		m_cbComId.SetBeEditable(FALSE,TRUE);
		m_cbDataByteLen.SetBeEditable(FALSE,TRUE);
		m_cbStopByteLen.SetBeEditable(FALSE,TRUE);
		m_cbPaud.SetBeEditable(FALSE,TRUE);
		m_cbCheckWay.SetBeEditable(FALSE,TRUE);
	}
}

// 函数 CLisSetDlg::SetComCtrlEnableState
// 作用：设置SetComCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable。
void CLisSetDlg::SetComCtrlEnableState(BOOL bEnabled)
{
	m_cbComId.SetBeEditable(bEnabled,TRUE);
	m_cbDataByteLen.SetBeEditable(bEnabled,TRUE);
	m_cbStopByteLen.SetBeEditable(bEnabled,TRUE);
	m_cbPaud.SetBeEditable(bEnabled,TRUE);
	m_cbCheckWay.SetBeEditable(bEnabled,TRUE);
}

// 函数 CLisSetDlg::SetTcpCtrlEnableState
// 作用：设置SetTcpCtrlEnableState。
// 参数：bEnabled：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeEditable。
void CLisSetDlg::SetTcpCtrlEnableState(BOOL bEnabled)
{
	m_edServerIp.SetBeEditable(bEnabled,TRUE);
	m_edServerPort.SetBeEditable(bEnabled,TRUE);
}

