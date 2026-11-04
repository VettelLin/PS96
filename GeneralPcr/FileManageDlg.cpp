// 【交接】 GeneralPcr\FileManageDlg.cpp
// 作用：FileManageDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：IMPLEMENT_DYNAMIC、CFileManageDlg、CDialogEx、GetHead、DoDataExchange、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_SIZE。
// BottomFuncBtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GeneralPcr.h"
#include "GeneralPcrDlg.h"
#include "FileManageDlg.h"
#include "MiddleDlg.h"
#include "WorkDlg.h"
#include "afxdialogex.h"
#include "PublicInfo.h"


IMPLEMENT_DYNAMIC(CFileManageDlg, CDialogEx)

// 函数 CFileManageDlg::CFileManageDlg
// 作用：执行CFileManageDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CFileManageDlg::CFileManageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileManageDlg::IDD, pParent),m_imgLogo(_T(".\\BkPic\\logo.png")),m_imgLogo2(_T(".\\BkPic\\icon2.png"))
{
	m_pWorkDlg = (CWorkDlg*)pParent;
	m_iBtHeight = 38;
	m_pCurSelBt = NULL;
	m_bCtrlCreated = FALSE;
	m_iLeftIndent = 16;

	m_iRightIndent = 188;
	m_iBtRegionW = 1548;
#ifdef XINYI_THEME
	m_iRightIndent += 108;
	m_iBtRegionW -= 108;
#else
	#ifdef PS96INSTRUMENT
		m_iRightIndent += 105;
		m_iBtRegionW -= 105;
	#endif
#endif

	m_iBtDefWidth = 270;
	m_iBtRealWidth = 270;
	m_iBtPreRealW = 270;
}

// 函数 CFileManageDlg::~CFileManageDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetHead。
CFileManageDlg::~CFileManageDlg()
{
	Node<CMyPageSwitchBt*>* pNodePageSwitchBt = m_lnkPageSwitchBtPtr.GetHead();
	while(NULL != pNodePageSwitchBt)
	{
		delete pNodePageSwitchBt->data;
		pNodePageSwitchBt->data = NULL;
		pNodePageSwitchBt = pNodePageSwitchBt->pNext;
	}
}

// 函数 CFileManageDlg::DoDataExchange
// 作用：把对话框控件和成员变量绑在一起。
// 参数：pDX：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CDialogEx::DoDataExchange。
void CFileManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFileManageDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_PAGESWITCHBTSTART,ID_PAGESWITCHBTSTART + 1000,OnPageSelected)
	ON_MESSAGE(WM_CLOSEPAGE,OnMsgClosePage)
END_MESSAGE_MAP()

// 函数 CFileManageDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CFileManageDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect; 
	GetClientRect(&rect);
	
	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),RGB(0XFF,0XFF,0XFF));

	Graphics graphics(memDc.m_hDC);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	Rect destRect;
	destRect.X = 1588 * m_dHoriRatio;
	destRect.Y = 9 * m_dVertRatio;
	destRect.Width = 48 * m_dHoriRatio;
	destRect.Height = 24 * m_dVertRatio;

#ifndef NOLOGO_VERSION

#ifdef XINYI_THEME
	destRect.X -= 108 * m_dHoriRatio;
	destRect.Y = 1 * m_dVertRatio;
	destRect.Width = 79 * m_dHoriRatio;
	destRect.Height = 43 * m_dVertRatio;
	graphics.DrawImage(&m_imgLogo2,destRect,0,0,m_imgLogo2.GetWidth(),m_imgLogo2.GetHeight(),UnitPixel,&ImgAtt);
#else

#ifdef CAN_YOUNG
	destRect.X -= 88 * m_dHoriRatio;
	destRect.Y = 4 * m_dVertRatio;
	destRect.Width = 70 * m_dHoriRatio;
	destRect.Height = 36 * m_dVertRatio;
	graphics.DrawImage(&m_imgLogo2,destRect,0,0,m_imgLogo2.GetWidth(),m_imgLogo2.GetHeight(),UnitPixel,&ImgAtt);
#else
#ifdef PS96INSTRUMENT
	destRect.X -= 105 * m_dHoriRatio;
	destRect.Y = 2 * m_dVertRatio;
	destRect.Width = 76 * m_dHoriRatio;
	destRect.Height = 40 * m_dVertRatio;
	graphics.DrawImage(&m_imgLogo,destRect,0,0,m_imgLogo.GetWidth(),m_imgLogo.GetHeight(),UnitPixel,&ImgAtt);
#else
	graphics.DrawImage(&m_imgLogo,destRect,0,0,m_imgLogo.GetWidth(),m_imgLogo.GetHeight(),UnitPixel,&ImgAtt);
#endif
#endif

#endif

#else
	destRect.X -= 88 * m_dHoriRatio;

#endif

	graphics.ReleaseHDC(memDc.m_hDC);

	//绘制软件版本号，20220513
	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);
	memDc.DrawText(SOFRVERION_STRING,CRect(destRect.GetRight(),0,rect.right,rect.bottom),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	memDc.SelectObject(pOldFont);

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

// 函数 CFileManageDlg::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 SetCtrlPos。
void CFileManageDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	m_iBtRegionW = cx - m_iLeftIndent - m_iRightIndent;

	if(m_bCtrlCreated)
	{
		SetCtrlPos();
	}
	return;
}

// 函数 CFileManageDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CDialogEx::OnCreate。
int CFileManageDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iLeftIndent *= m_dHoriRatio;
	m_iRightIndent *= m_dHoriRatio;
	m_iBtDefWidth *= m_dHoriRatio;
	m_iBtRealWidth *= m_dHoriRatio;
	m_iBtPreRealW *= m_dHoriRatio;
	m_iBtHeight *= m_dVertRatio;

	return CDialogEx::OnCreate(lpCreateStruct);
}

// 函数 CFileManageDlg::OnInitDialog
// 作用：对话框创建后做初始化。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitDlg、SetCtrlPos、ShowCtrl。
BOOL CFileManageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitDlg();
	m_bCtrlCreated = TRUE;
	SetCtrlPos();

	ShowCtrl();

	return TRUE;
}

// 函数 CFileManageDlg::InitDlg
// 作用：初始化InitDlg。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetMyFont、SetTextClr1。
void CFileManageDlg::InitDlg()
{
	SetMyFont(m_stTxFont,16 * m_dTxRatio,FW_MEDIUM,TYPE_PIXEL);

#ifndef BIOWET_BK
	SetTextClr1(CLR_SOFT_THEME);
#else
	SetTextClr1(CLR_2LEVEL_THEME);
#endif
}


// 函数 CFileManageDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、GetSize、SetWindowPos、ClearRectToDelete、AddRectToDelete、CalcRectResult。
void CFileManageDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	int startX = m_iLeftIndent;
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		(*m_lnkPageSwitchBtPtr[i])->SetWindowPos(this,startX,BT_TOP_START,m_iBtDefWidth,m_iBtHeight,SWP_NOZORDER);
		startX += m_iBtDefWidth;
	}

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();
	m_rcManage.AddRectToDelete(startX,BT_TOP_START,m_iBtRealWidth * m_lnkPageSwitchBtPtr.GetSize(),m_iBtHeight);
	m_rcManage.CalcRectResult();
}

// 函数 CFileManageDlg::SetPageSwitchBtPos
// 作用：设置SetPageSwitchBtPos。
// 参数：iStart：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、GetSize、ClearRectToDelete、AddRectToDelete、CalcRectResult、GetSafeHwnd。
void CFileManageDlg::SetPageSwitchBtPos(int iStart)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	int iStartX = m_iLeftIndent;
	int iSwitchBtNum = m_lnkPageSwitchBtPtr.GetSize();
	CMyPageSwitchBt* pPageSwtBt = NULL;

	if(iSwitchBtNum * m_iBtDefWidth > m_iBtRegionW)
	{
		m_iBtRealWidth = m_iBtRegionW / iSwitchBtNum;
	}
	else
	{
		m_iBtRealWidth = m_iBtDefWidth;
	}

	m_rcManage.m_rcInit = rcClient;
	m_rcManage.ClearRectToDelete();
	m_rcManage.AddRectToDelete(m_iLeftIndent,BT_TOP_START,m_iBtRealWidth * iSwitchBtNum,m_iBtHeight);
	m_rcManage.CalcRectResult();

	if(m_iBtPreRealW != m_iBtRealWidth)
	{
		iStart = 0;
	}
	m_iBtPreRealW = m_iBtRealWidth;

	BOOL bProcessed = FALSE;

	iStartX = m_iLeftIndent + iStart * m_iBtRealWidth;
	for(int i = iStart;i < iSwitchBtNum;++i)
	{
		pPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(NULL != pPageSwtBt->GetSafeHwnd())
		{
			pPageSwtBt->MoveWindow(iStartX,BT_TOP_START,m_iBtRealWidth,m_iBtHeight,TRUE);
			iStartX += m_iBtRealWidth;

			bProcessed = TRUE;
		}
	}	

	if(!bProcessed)
	{
		Invalidate();
	}

	return;
}

// 函数 CFileManageDlg::ShowCtrl
// 作用：改变ShowCtrl的显示或可用状态。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、ShowWindow。
void CFileManageDlg::ShowCtrl()
{
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		(*m_lnkPageSwitchBtPtr[i])->ShowWindow(SW_SHOW);
	}
}


// 函数 CFileManageDlg::OnPageSelected
// 作用：响应 Windows 或自定义消息 OnPageSelected。
// 参数：nID：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetDlgItem、GetPageId、SetPageSelected。
void CFileManageDlg::OnPageSelected(UINT nID)
{
	int pageId = ((CMyPageSwitchBt*)GetDlgItem(nID))->GetPageId();
	SetPageSelected(pageId);
}

// 函数 CFileManageDlg::OnMsgClosePage
// 作用：响应 Windows 或自定义消息 OnMsgClosePage。
// 参数：wParam；lParam。
// 返回：返回 LRESULT。
// 过程：函数里会调用 DeletePage。
LRESULT CFileManageDlg::OnMsgClosePage(WPARAM wParam,LPARAM lParam)
{
	return DeletePage(wParam);
}

// 函数 CFileManageDlg::AddPage
// 作用：创建或加入AddPage。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetInstance、strFSPOrigin、_T、GetUserDataSavePath、GetExperimentInfo、SetFilePath。
int CFileManageDlg::AddPage()
{
	CExperimentData* pExpData = new CExperimentData;
	if(NULL == pExpData)
	{
		return -1;
	}

	CPublicInfo* pPublicInfo = CPublicInfo::GetInstance();

	//设置实验默认保存路径
	CString strFSPOrigin(_T(""));
	strFSPOrigin = pPublicInfo->GetUserDataSavePath();
	pExpData->GetExperimentInfo()->SetFilePath(strFSPOrigin);

	pExpData->GetExperimentInfo()->SetOperator(pPublicInfo->GetUserName());
	AddNewPage(pExpData);

	return 0;
}

// 函数 CFileManageDlg::AddNewPage
// 作用：创建或加入AddNewPage。
// 参数：pExpData：指针，指向调用方传入的对象；strFileName：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 PopWarningTipInfo、_T、Create、CRect、GetPageId、InitPageSwitchBt。
int CFileManageDlg::AddNewPage(CExperimentData* pExpData,CString strFileName /*= _T("")*/)
{
	if(NULL == pExpData)
	{
		return -1;
	}

	CMyPageSwitchBt* pPageSwtBt = new CMyPageSwitchBt;
	if(NULL == pPageSwtBt)
	{
		PopWarningTipInfo(_T("AddNewPage failed,memory allocate error!"));
		return -4;
	}	

	pPageSwtBt->Create(_T(""),WS_CHILD | WS_CLIPSIBLINGS | BS_PUSHBUTTON,CRect(0,0,0,0),this,ID_PAGESWITCHBTSTART + pPageSwtBt->GetPageId());
	InitPageSwitchBt(pPageSwtBt);

	m_lnkPageSwitchBtPtr.AddTail(pPageSwtBt);

	SetPageSwitchBtPos(m_lnkPageSwitchBtPtr.GetSize() - 1);

	pPageSwtBt->ShowWindow(SW_SHOW);

	int ret = m_pWorkDlg->AddNewPage(pPageSwtBt->GetPageId());
	if(0 != ret)
	{
		PopWarningTipInfo(_T("页面添加失败1"));
		return -2;
	}

	CMiddleDlg* pMiddleDlg = m_pWorkDlg->GetMiddleDlg(pPageSwtBt->GetPageId());
	if(NULL == pMiddleDlg->GetSafeHwnd())
	{
		PopWarningTipInfo(_T("页面添加失败2"));
		return -3;
	}

	//创建窗口后保存实验数据对象指针到CMiddleDlg中
	pMiddleDlg->SetExpDataPtr(pExpData);
	pMiddleDlg->InitExperimentData(pExpData);
	pMiddleDlg->EmbodyBaseSetInfo();

	if(strFileName.IsEmpty() || pExpData->GetBeTemplateFile())
	{
		strFileName = pExpData->GetExperimentInfo()->GetExpName();
	}
	pPageSwtBt->SetWindowText(strFileName);

	SetPageSelected(pPageSwtBt->GetPageId());

	return 0;
}

// 函数 CFileManageDlg::DeletePage
// 作用：更新或清除DeletePage。
// 参数：pageId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetSafeHwnd、IsExpRunning、PopNormalTipInfo、GetText、GetInstance。
int CFileManageDlg::DeletePage(int pageId)
{
	//只存在一个文档（窗口）时，不允许删除操作
	if(1 == m_lnkPageSwitchBtPtr.GetSize())
	{
		return 1;
	}

	if(pageId < 0)
	{
		return -1;
	}

	if(pageId > CMyPageSwitchBt::PageCount)
	{
		return -2;
	}


	if(NULL == m_pWorkDlg->GetSafeHwnd())
	{
		return -4;
	}
	
	if(NULL == m_pWorkDlg->m_pCurSelPageDlg->GetSafeHwnd())
	{
		return -5;
	}

	if(m_pWorkDlg->m_pCurSelPageDlg->IsExpRunning())
	{
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(289));
		return -3;	
	}

	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	BOOL bChanged = FALSE;//m_pWorkDlg->m_pCurSelPageDlg->m_dataAnaDlg.GetBeChanged();
	if(bChanged)
	{
		if(IDYES == PopQueryTipInfo(pLangInfo->GetText(248)))
		{
			//pMainDlg->SaveAs();
		}
	}
	else
	{
		if(IDYES != PopQueryTipInfo(pLangInfo->GetText(247)))
		{
			return -6;
		}
	}

	CMyPageSwitchBt* pTempPageSwtBt = NULL;
	int iSwtBtNum = m_lnkPageSwitchBtPtr.GetSize();
	for(int i = 0;i < iSwtBtNum;++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(pageId == pTempPageSwtBt->GetPageId())
		{
			BOOL bNeedResetSelPage = FALSE;
			if(NULL != m_pCurSelBt->GetSafeHwnd() &&  pageId == m_pCurSelBt->GetPageId())
			{
				m_pCurSelBt = NULL;
				bNeedResetSelPage = TRUE;
			}
			
			BOOL ret = pTempPageSwtBt->DestroyWindow();
			delete pTempPageSwtBt;
			m_lnkPageSwitchBtPtr.DeleteAt(i);

			m_pWorkDlg->DeletePage(pageId);

			if(bNeedResetSelPage)
			{
				int curSelBtIndex = -1;
				int iNewSwtBtNum = m_lnkPageSwitchBtPtr.GetSize();
				if(iNewSwtBtNum > 0)
				{
					if(i == iNewSwtBtNum)
					{
						curSelBtIndex = i - 1;
					}
					else if(i < iNewSwtBtNum)
					{
						curSelBtIndex = i;
					}
				}
				if(-1 != curSelBtIndex)
				{
					SetPageSelected((*m_lnkPageSwitchBtPtr[curSelBtIndex])->GetPageId());
				}
			}

			SetPageSwitchBtPos(i);

			break;
		}
	}

	return 0;
}

// 函数 CFileManageDlg::SetNewFileSavePath
// 作用：设置SetNewFileSavePath。
// 参数：strNewFileSavePath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd。
void CFileManageDlg::SetNewFileSavePath(CString strNewFileSavePath)
{
	if(NULL != m_pCurSelBt->GetSafeHwnd())
	{
		m_pCurSelBt->m_strFilePath = strNewFileSavePath;
	}
}

// 函数 CFileManageDlg::SetPageFirstColumn
// 作用：设置SetPageFirstColumn。
// 参数：pageId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetPageId、SetBeBtPageRunning、DeleteAt、AddHead、MoveWindow。
int CFileManageDlg::SetPageFirstColumn(int pageId)
{
	if(m_lnkPageSwitchBtPtr.GetSize() < 1)
	{
		return 1;
	}

	CMyPageSwitchBt* pTempPageSwtBt = *m_lnkPageSwitchBtPtr[0];
	if(NULL == pTempPageSwtBt)
	{
		return -1;
	}

	if(1 == m_lnkPageSwitchBtPtr.GetSize() || pageId == pTempPageSwtBt->GetPageId())
	{
		pTempPageSwtBt->SetBeBtPageRunning(TRUE);
		return 2;
	}

 	if(pageId < 0)
	{
		return -2;
	}

	if(pageId > CMyPageSwitchBt::PageCount)
	{
		return -3;
	}

	int iSwtBtNum = m_lnkPageSwitchBtPtr.GetSize();
	for(int i = 0;i < iSwtBtNum;++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(pageId == pTempPageSwtBt->GetPageId())
		{
			m_lnkPageSwitchBtPtr.DeleteAt(i);
			m_lnkPageSwitchBtPtr.AddHead(pTempPageSwtBt);

			int startX = m_iLeftIndent; 
			for(int j = 0;j <= i;++j) 
			{
				pTempPageSwtBt = *m_lnkPageSwitchBtPtr[j];
				if(0 == j)
				{
					pTempPageSwtBt->SetBeBtPageRunning(TRUE);
				}
				pTempPageSwtBt->MoveWindow(startX,BT_TOP_START,m_iBtRealWidth,m_iBtHeight);
				startX += m_iBtRealWidth;
			}

			break;
		}
	}

	return 0;
}

// 函数 CFileManageDlg::SetPageSwitchBtState
// 作用：设置SetPageSwitchBtState。
// 参数：pageId；bRunning：是或否；bRedraw：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetPageId、SetBeBtPageRunning。
int CFileManageDlg::SetPageSwitchBtState(int pageId,BOOL bRunning,BOOL bRedraw /*= TRUE*/)
{
	if(pageId < 0)
	{
		return -1;
	}

	if(pageId > CMyPageSwitchBt::PageCount)
	{
		return -2;
	}

	CMyPageSwitchBt* pTempPageSwtBt = NULL;
	int iSwtBtNum = m_lnkPageSwitchBtPtr.GetSize();
	for(int i = 0;i < iSwtBtNum;++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(pageId == pTempPageSwtBt->GetPageId())
		{
			pTempPageSwtBt->SetBeBtPageRunning(bRunning,bRedraw);
			break;
		}
	}

	return 0;
}

// 函数 CFileManageDlg::SetPageSelected
// 作用：设置SetPageSelected。
// 参数：pageId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、EnableWindow、GetSize、GetPageId。
int CFileManageDlg::SetPageSelected(int pageId)
{
	if(pageId < 0)
	{
		return -1;
	}

	if(pageId > CMyPageSwitchBt::PageCount)
	{
		return -2;
	}

	if(NULL != m_pCurSelBt->GetSafeHwnd())
	{
		m_pCurSelBt->EnableWindow(TRUE);
	}

	CMyPageSwitchBt* pTempPageSwtBt = NULL;
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(pageId == pTempPageSwtBt->GetPageId())
		{
			pTempPageSwtBt->EnableWindow(FALSE);
			m_pCurSelBt = pTempPageSwtBt;
			m_pWorkDlg->SetPageSelected(pageId);
			break;
		}
	}
	
	return 0;
}

// 函数 CFileManageDlg::SetCurrentSelectPageString
// 作用：设置SetCurrentSelectPageString。
// 参数：strFileName：字符串；strFilePath：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSafeHwnd、SetWindowText。
int CFileManageDlg::SetCurrentSelectPageString(CString strFileName,CString strFilePath)
{
	if(NULL != m_pCurSelBt->GetSafeHwnd())
	{
		m_pCurSelBt->SetWindowText(strFileName);
		m_pCurSelBt->m_strFilePath = strFilePath;
	}
	return 0;
}

// 函数 CFileManageDlg::SetExperName
// 作用：设置SetExperName。
// 参数：pageId；strExpeName：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetSafeHwnd、GetPageId、SetWindowText。
void CFileManageDlg::SetExperName(int pageId,CString strExpeName)
{
	CMyPageSwitchBt* pTempPageSwtBt = NULL;
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(NULL != pTempPageSwtBt->GetSafeHwnd() && pageId == pTempPageSwtBt->GetPageId())
		{
			pTempPageSwtBt->SetWindowText(strExpeName);
			break;
		}
	}

	return;
}

// 函数 CFileManageDlg::CheckFileExistOrNot
// 作用：判断CheckFileExistOrNot是否成立。
// 参数：strFilePath：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSize、GetSafeHwnd。
BOOL CFileManageDlg::CheckFileExistOrNot(CString strFilePath)
{
	CMyPageSwitchBt* pTempPageSwtBt = NULL;
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(NULL != pTempPageSwtBt->GetSafeHwnd())
		{
			if(pTempPageSwtBt->m_strFilePath == strFilePath)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

// 函数 CFileManageDlg::SetPageFilePath
// 作用：设置SetPageFilePath。
// 参数：iPageId：整数；strFilePath：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetPageId。
int CFileManageDlg::SetPageFilePath(int iPageId,CString strFilePath)
{
	CMyPageSwitchBt* pTempPageSwtBt = NULL;
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(pTempPageSwtBt->GetPageId() == iPageId)
		{
			pTempPageSwtBt->m_strFilePath = strFilePath;
			return 0;
		}
	}

	return -1;
}

// 函数 CFileManageDlg::CheckFileNameExistOrNot
// 作用：判断CheckFileNameExistOrNot是否成立。
// 参数：strFileName：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 strTemp、_T、GetSize、GetSafeHwnd、GetWindowText。
BOOL CFileManageDlg::CheckFileNameExistOrNot(CString strFileName)
{
	CString strTemp(_T(""));
	CMyPageSwitchBt* pTempPageSwtBt = NULL;
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		pTempPageSwtBt = *m_lnkPageSwitchBtPtr[i];
		if(NULL != pTempPageSwtBt->GetSafeHwnd())
		{
			pTempPageSwtBt->GetWindowText(strTemp);
			if(strTemp == strFileName)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

// 函数 CFileManageDlg::PreTranslateMessage
// 作用：消息送达窗口前先拦截键盘或鼠标。
// 参数：pMsg：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 __super::PreTranslateMessage。
BOOL CFileManageDlg::PreTranslateMessage(MSG* pMsg)
{
	if(WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN:	return TRUE;
			case VK_ESCAPE:	return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

// 函数 CFileManageDlg::InitPageSwitchBt
// 作用：初始化InitPageSwitchBt。
// 参数：pPageSwitchBt：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、SetMyFont、SetPngBkPic、_T。
void CFileManageDlg::InitPageSwitchBt(CMyPageSwitchBt* pPageSwitchBt)
{
	if(NULL == pPageSwitchBt->GetSafeHwnd())
	{
		return;
	}

	pPageSwitchBt->SetMyFont(m_stTxFont,16 * m_dTxRatio,FW_NORMAL,TYPE_PIXEL);
	pPageSwitchBt->SetPngBkPic(_T(".\\BkPic\\experiment.png"),2,24,18 * m_dHoriRatio,10 * m_dHoriRatio);
}

