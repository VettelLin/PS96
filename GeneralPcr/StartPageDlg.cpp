// 【交接】 GeneralPcr\StartPageDlg.cpp
// 作用：开机首页。连接仪器后从仪器存储器读出序列号并显示。首页不能编辑序列号。
// 先看这些函数：IMPLEMENT_DYNAMIC、CStartPageDlg、CDialogEx、Empty、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_LBUTTONDOWN。
#include "StdAfx.h"
#include "StartPageDlg.h"
#include "GeneralPcr.h"
#include "InstrumentPCR.h"
#include "InstancePCR.h"

IMPLEMENT_DYNAMIC(CStartPageDlg,CDialogEx)

#define WM_DISCERNINSTRUMENT_RESULT	WM_USER + 6035	//通知仪器识别结果
																							
// 函数 CStartPageDlg::CStartPageDlg
// 作用：执行CStartPageDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CStartPageDlg::CStartPageDlg(CWnd* pParent /*= NULL*/)
	: CDialogEx(CStartPageDlg::IDD, pParent),m_stTipInfo(TRUE)
{
	m_iWidth = 800;
	m_iHeight = 600;
	m_iFrameW = 1;
	m_iRoundAngle = 10;
	m_iHeaderH = 40;
	m_strStartPath.Empty();
	m_strWarningTip.Empty();
}

// 函数 CStartPageDlg::~CStartPageDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStartPageDlg::~CStartPageDlg(void)
{

}

// 函数 CStartPageDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CStartPageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStartPageDlg,CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_MESSAGE(WM_DISCERNINSTRUMENT_RESULT,OnMsgDiscernInstrumentRst)  
	ON_MESSAGE(WN_DEVICE_FIRST_CONNECT,OnMsgDeviceFirstConnect)  
END_MESSAGE_MAP()

// 函数 CStartPageDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CStartPageDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	int iTempInt1 = 150 * m_dHoriRatio;
	int iTempInt2 = 146 * m_dHoriRatio;

	Graphics graphics(memDc.m_hDC);
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);

	Image image(_T(".\\BkPic\\StartBk.png"));
	Rect rcDest(0,0,rect.Width(),rect.Height());
	graphics.DrawImage(&image,rcDest,0,0,image.GetWidth(),image.GetHeight(),UnitPixel,&ImgAtt);
//
//#ifndef NOLOGO_STARTUP_VERSION
//
//	Image image2(_T(".\\BkPic\\StartPagelogo.png"));
//#ifdef ODREI
//	Rect rcDest2(iTempInt1,122 * m_dVertRatio,175 * m_dHoriRatio,87 * m_dVertRatio);
//#else
//	Rect rcDest2(iTempInt1,122 * m_dVertRatio,image2.GetWidth(),image2.GetHeight());
//#endif
//	graphics.DrawImage(&image2,rcDest2,0,0,image2.GetWidth(),image2.GetHeight(),UnitPixel,&ImgAtt);
//
//	Image image3(_T(".\\BkPic\\Welcome.png"));
//	Rect rcDest3(iTempInt2,413 * m_dVertRatio,image3.GetWidth(),image3.GetHeight());
//	graphics.DrawImage(&image3,rcDest3,0,0,image3.GetWidth(),image3.GetHeight(),UnitPixel,&ImgAtt);
//
//#ifndef XINYI_THEME
//	Image image4(_T(".\\BkPic\\right.png"));
//	Rect rcDest4(iTempInt1,987 * m_dVertRatio,image4.GetWidth(),image4.GetHeight());
//	graphics.DrawImage(&image4,rcDest4,0,0,image4.GetWidth(),image4.GetHeight(),UnitPixel,&ImgAtt);
//	int iTxStartX = iTempInt1 + image4.GetWidth() + 2;
//
//	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
//	memDc.SetBkMode(TRANSPARENT);
//	memDc.SetTextColor(CLR_STARTPAGE_TX);
//	memDc.DrawText(RIGHT_STRING,CRect(iTxStartX,980 * m_dVertRatio,600 * m_dHoriRatio,1010 * m_dVertRatio),DT_LEFT | DT_VCENTER | DT_SINGLELINE);
//	memDc.SelectObject(pOldFont);
//#else
//	Image image5(_T(".\\BkPic\\RightInfo.png"));
//	Rect rcDest5(iTempInt1,987 * m_dVertRatio,image5.GetWidth(),image5.GetHeight());
//	graphics.DrawImage(&image5,rcDest5,0,0,image5.GetWidth(),image5.GetHeight(),UnitPixel,&ImgAtt);
//#endif
//
//#endif

	graphics.ReleaseHDC(memDc.m_hDC);

	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CStartPageDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::OnLButtonDown。
void CStartPageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);

	return;
}

// 函数 CStartPageDlg::OnTimer
// 作用：定时器到期时刷新界面或推进状态。
// 参数：nIDEvent：整数。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::OnTimer。
void CStartPageDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
}

// 函数 CStartPageDlg::OnMsgDiscernInstrumentRst
// 作用：响应 Windows 或自定义消息 OnMsgDiscernInstrumentRst。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 strTemp、_T、GetInstance、GetText、size、GetWindowText。
LRESULT CStartPageDlg::OnMsgDiscernInstrumentRst(WPARAM wParam,LPARAM lParam)
{
	if(MSGTEXTTAG_INT == wParam)
	{
		int iTempInt1 = 0;
		CString strTemp(_T(""));
		CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
		if(0 == lParam)	//未识别到仪器
		{
			strTemp = pLangInfo->GetText(340);
		}
		else if(1 == lParam)	//未识别到仪器
		{
			strTemp = pLangInfo->GetText(331);
		}
		else if(2 == lParam)	//仪器已正常识别
		{
			strTemp = pLangInfo->GetText(332);
			for(int i = 0;i < m_vecInstruSerial.size();++i)
			{
				strTemp += m_vecInstruSerial[i];
				if(i + 1 < m_vecInstruSerial.size())
				{
					strTemp += ",";
				}
			}
			strTemp += pLangInfo->GetText(341);
		}
		else if(3 == lParam)	//运动模块自检中
		{
			m_stTipInfo.GetWindowText(strTemp);
			strTemp += _T("\n");
			strTemp += pLangInfo->GetText(333);
			strTemp += pLangInfo->GetText(334);
			m_stTipInfo.SetWindowText(strTemp);
		}
		else if(4 == lParam)	//运动模块自检失败
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(335); 
		}
		else if(5 == lParam)	//运动模块自检成功
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(336); 
		}
		else if(6 == lParam)	//传感器模块自检中
		{
			m_stTipInfo.GetWindowText(strTemp);
			strTemp += _T("\n");
			strTemp += pLangInfo->GetText(337);
			strTemp += pLangInfo->GetText(334);
			m_stTipInfo.SetWindowText(strTemp);
		}
		else if(7 == lParam)	//传感器模块自检失败
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(335); 
		}
		else if(8 == lParam)	//传感器模块自检成功
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(336); 
		}
		else if(9 == lParam)	//加热模块自检中
		{
			m_stTipInfo.GetWindowText(strTemp);
			strTemp += _T("\n");
			strTemp += pLangInfo->GetText(338);
			strTemp += pLangInfo->GetText(334);
			m_stTipInfo.SetWindowText(strTemp);
		}
		else if(10 == lParam)	//加热模块自检失败
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(335); 
		}
		else if(11 == lParam)	//加热模块自检成功
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(336); 
		}
		else if(12 == lParam)	//光学模块自检中
		{
			m_stTipInfo.GetWindowText(strTemp);
			strTemp += _T("\n");
			strTemp += pLangInfo->GetText(339);
			strTemp += pLangInfo->GetText(334);
			m_stTipInfo.SetWindowText(strTemp);
		}
		else if(13 == lParam)	//光学模块自检失败
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(335); 
		}
		else if(14 == lParam)	//光学模块自检成功
		{
			m_stTipInfo.GetWindowText(strTemp);
			iTempInt1 = strTemp.Find(pLangInfo->GetText(334));
			if(-1 != iTempInt1)
			{
				strTemp = strTemp.Left(iTempInt1);
			}
			strTemp += pLangInfo->GetText(336); 
		}
		m_stTipInfo.SetWindowText(strTemp);
	}
	else 
	{
		if(0 == wParam)
		{
			if(0 == lParam)	//自检成功
			{

			}
			else if(1 == lParam)	//自检成功，有警告信息
			{
				PopWarningTipInfo(m_strWarningTip);
			}
		}
		else if(1 == wParam)	//自检失败（通信失败）
		{
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(342));
		}
		else if(2 == wParam)	//不自检（仪器未连接或者用户选择不自检，可通过lParam判断）
		{

		}
		else if(3 == wParam)	//仪器屏蔽自检
		{

		}
		else if(4 == wParam)	//运行上一个未完成的实验（断电保护）
		{
			int iLnkIndex = lParam;
			theApp.m_lnkLnkIndex.AddTail(iLnkIndex);
		}
		else if(5 == wParam)	//不自检（仪器未连接或者用户选择不自检，可通过lParam判断）
		{
			m_gifHanding.Stop();
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(436));
		}

		if(5 != wParam)
		{
			m_gifHanding.Stop();
		}
		
		OnOK();
	}

	return 0;
}

// 函数 CStartPageDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetWindowPos、Width、Height、InitDlg、CreateCtrl、InitCtrl。
BOOL CStartPageDlg::OnInitDialog()
{ 
	CDialogEx::OnInitDialog();

	SetWindowPos(NULL,theApp.m_rcWorkArea.left,theApp.m_rcWorkArea.top,theApp.m_rcWorkArea.Width(),theApp.m_rcWorkArea.Height(),SWP_NOZORDER);
	m_iWidth = theApp.m_rcWorkArea.Width();
	m_iHeight = theApp.m_rcWorkArea.Height();

	InitDlg();

	CreateCtrl();
	InitCtrl();
	SetCtrlPos();
	ShowCtrl();

	AfxBeginThread(DiscernInstrumentTd,this);

	return TRUE;
}

// 函数 CStartPageDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont。
void CStartPageDlg::InitDlg()
{
	SetMyFont(m_stTxFont,30 * m_dTxRatio);
	return;
}

// 函数 CStartPageDlg::CreateCtrl
// 作用：创建或加入CreateCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateBt、CreateSt、CreateCb、CreateEd、CreateLst。
void CStartPageDlg::CreateCtrl()
{
	CreateBt();
	CreateSt();
	CreateCb();
	CreateEd();
	CreateLst();
}

// 函数 CStartPageDlg::CreateBt
// 作用：创建或加入CreateBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::CreateBt()
{

}

// 函数 CStartPageDlg::CreateSt
// 作用：创建或加入CreateSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Create、_T、CRect。
void CStartPageDlg::CreateSt()
{
	m_stTipInfo.Create(_T(""),WS_CHILD,CRect(0,0,0,0),this,ID_STARTPAGEDLG_ST_TIPINFO);
	m_gifHanding.Create(_T(""),WS_CHILD,CRect(0,0,0,0),this,ID_STARTPAGEDLG_GIF_HANDING);
}

// 函数 CStartPageDlg::CreateCb
// 作用：创建或加入CreateCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::CreateCb()
{

}

// 函数 CStartPageDlg::CreateEd
// 作用：创建或加入CreateEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::CreateEd()
{

}

// 函数 CStartPageDlg::CreateLst
// 作用：创建或加入CreateLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::CreateLst()
{

}

// 函数 CStartPageDlg::InitCtrl
// 作用：初始化InitCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitBt、InitSt、InitCb、InitEd、InitLst。
void CStartPageDlg::InitCtrl()
{
	InitBt();
	InitSt();
	InitCb();
	InitEd();
	InitLst();
}

// 函数 CStartPageDlg::InitBt
// 作用：初始化InitBt。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::InitBt()
{

}

// 函数 CStartPageDlg::InitSt
// 作用：初始化InitSt。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetTextColor、SetMyFont、SetWordStyle、SetSingleLineState、SetGifFilePath、_T。
void CStartPageDlg::InitSt()
{
	int iFontH = 36 * m_dTxRatio;
	
	m_stTipInfo.SetTextColor(CLR_STARTPAGE_TX);
	m_stTipInfo.SetMyFont(m_stTxFont,iFontH,FW_NORMAL,TYPE_PIXEL);
	m_stTipInfo.SetWordStyle(DT_LEFT | DT_END_ELLIPSIS);
	m_stTipInfo.SetSingleLineState(FALSE);

	m_gifHanding.SetGifFilePath(_T(".\\BkPic\\Loading.gif"));
}

// 函数 CStartPageDlg::InitCb
// 作用：初始化InitCb。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::InitCb()
{

}

// 函数 CStartPageDlg::InitEd
// 作用：初始化InitEd。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::InitEd()
{

}

// 函数 CStartPageDlg::InitLst
// 作用：初始化InitLst。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStartPageDlg::InitLst()
{

}

// 函数 CStartPageDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetWindowPos。
void CStartPageDlg::SetCtrlPos()
{
	m_stTipInfo.SetWindowPos(this,159 * m_dHoriRatio,378 * m_dVertRatio,420 * m_dHoriRatio,200 * m_dVertRatio,SWP_NOZORDER);
	m_gifHanding.SetWindowPos(this,429 * m_dHoriRatio,719 * m_dVertRatio,80 * m_dHoriRatio,80 * m_dHoriRatio,SWP_NOZORDER);
}

// 函数 CStartPageDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 ShowWindow、Start。
void CStartPageDlg::ShowCtrl()
{
	m_stTipInfo.ShowWindow(SW_SHOW);
	m_gifHanding.ShowWindow(SW_SHOW);
	m_gifHanding.Start();
}

// 函数 CStartPageDlg::DiscernInstrumentTd
// 作用：执行DiscernInstrumentTd。
// 参数：pParam：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 PostMessageW、Sleep、GetInstance、SetMsgWnd、InitilizePCRStartPage、GetAvailableInstance。
UINT CStartPageDlg::DiscernInstrumentTd(LPVOID pParam)
{
	int iErrCode = 0,iTempInt1 = 0,iRet1 = 0,iRet2 = 0,iRet3 = 0,iRet4 = 0;
	
	CStartPageDlg* pStartPageDlg = (CStartPageDlg*)pParam;
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,0);
	//Sleep(1000);

	CInstrumentPCR* pInstrument = CInstrumentPCR::GetInstance();
	if(NULL == pInstrument)
	{
		iErrCode = 2;
		goto NOTSELFCHECK;
	}
	pInstrument->SetMsgWnd(pStartPageDlg);

	BOOL bConnected = theApp.InitilizePCRStartPage(pStartPageDlg->m_strStartPath);
	if(!bConnected)
	{
		pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,1);
		iErrCode = 1;
		goto INSTRUNOTCONNECTED;
	}

	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	
	CInstancePCR* pInstance = pInstrument->GetAvailableInstance();
	if(NULL == pInstance)
	{
		iErrCode = 3;
		goto NOTSELFCHECK;
	}
	else
	{
		pStartPageDlg->m_vecInstruSerial.push_back(pInstance->GetSN());
		pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,2);
	}

	int iLnkIndex = theApp.m_powerOffProtect.SearchPowerOffProtect(pInstance->GetSN());
	if(-1 != iLnkIndex)
	{
		//goto CONTINUE_OLD_EXP;
		CString strTip(_T(""));
		strTip.Format(pLangInfo->GetText(343),pInstance->GetSN());
		if(IDYES == PopQueryTipInfo(strTip))
		{
			//用户选择继续运行上一次实验，不再处理开机自检相关信息
			goto CONTINUE_OLD_EXP;
		}
		else
		{
			theApp.m_powerOffProtect.DeleteOldProgress(iLnkIndex);
		}
	}

	//N96才自检
#ifndef N96INSTRUMENT
	goto SHIELD_SELFCHECK;
#endif

	if(IDYES != PopQueryTipInfo(pLangInfo->GetText(330)))
	{
		iErrCode = 4;
		goto NOTSELFCHECK;
	}

	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,3);
	iRet1 = pInstance->SportModuleCheck();
	if(iRet1 < 0)
	{
		iTempInt1 = 4;
	}
	else 
	{
		iTempInt1 = 5;
	}
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,iTempInt1);
	if(4 == iTempInt1)
	{
		goto COMMU_FAILED;
	}

	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,6);
	iRet2 = pInstance->SensorModuleCheck();
	if(iRet2 < 0)
	{
		iTempInt1 = 7;
	}
	else
	{
		iTempInt1 = 8;
	}
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,iTempInt1);
	if(7 == iTempInt1)
	{
		goto COMMU_FAILED;
	}

	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,9);
	iRet3 = pInstance->HeatModeduleCheck();
	if(iRet3 < 0)
	{
		iTempInt1 = 10;
	}
	else
	{
		iTempInt1 = 11;
	}
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,iTempInt1);
	if(10 == iTempInt1)
	{
		goto COMMU_FAILED;
	}

	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,12);
	iRet4 = pInstance->OpticsModuleCheck();
	if(iRet4 < 0)
	{
		iTempInt1 = 13;
	}
	else
	{
		iTempInt1 = 14;
	}
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,MSGTEXTTAG_INT,iTempInt1);
	if(13 == iTempInt1)
	{
		goto COMMU_FAILED;
	}

	//自检结束，通信正常，如果有警告，则弹窗提示
	pStartPageDlg->m_strWarningTip = pInstance->GetCheckResultString();
	if(pStartPageDlg->m_strWarningTip.IsEmpty())
	{
		Sleep(1200);
		pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,0,0);
	}
	else
	{
		pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,0,1);
	}
	
	return 0;

COMMU_FAILED:
	//Sleep(16000);
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,1,0);
	return iErrCode;

INSTRUNOTCONNECTED:
	Sleep(600);
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,5,iErrCode);
	return iErrCode;

NOTSELFCHECK:
	if(4 != iErrCode)
	{
		//Sleep(16000);
	}
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,2,iErrCode);
	return iErrCode;

SHIELD_SELFCHECK:
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,3,0);
	return 0;

CONTINUE_OLD_EXP:
	pStartPageDlg->PostMessageW(WM_DISCERNINSTRUMENT_RESULT,4,iLnkIndex);
	return 0;
}



// 函数 CStartPageDlg::OnMsgDeviceFirstConnect
// 作用：响应 Windows 或自定义消息 OnMsgDeviceFirstConnect。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 PopNormalTipInfo、GetText。
LRESULT CStartPageDlg::OnMsgDeviceFirstConnect(WPARAM wParam,LPARAM lParam)
{
	PopNormalTipInfo(theApp.m_pLangInfo->GetText(541));
	return 0;
}
