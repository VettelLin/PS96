// 【交接】 GeneralPcr\Ps96WorkDlg.cpp
// 作用：Ps96WorkDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：CPs96WorkDlg、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、END_MESSAGE_MAP、OnEraseBkgnd、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap。
#include "StdAfx.h"
#include "Ps96WorkDlg.h"
#include "GeneralPcr.h"
#include "PublicInfo.h"

CPs96WorkDlg::CPs96WorkDlg(void): m_ps96FileManagerDlg(this)
{

}

CPs96WorkDlg::~CPs96WorkDlg(void)
{

}

BEGIN_MESSAGE_MAP(CPs96WorkDlg,CWorkDlg)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CPs96WorkDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect; 
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(0,rect.bottom - theApp.m_iFileManageDlgH,rect.Width(),theApp.m_iFileManageDlgH,CLR_SOFT_LIGHT);

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

int CPs96WorkDlg::SetPageSelected(int iPageId)
{
	if(iPageId < 0)
	{
		return -1;
	}

	if(iPageId > CMyPageSwitchBt::PageCount)
	{
		return -2;
	}

	if(NULL != m_pCurSelPageDlg->GetSafeHwnd())
	{
		m_pCurSelPageDlg->ShowWindow(FALSE);
	}

	CMiddleDlg* pPageDlg = NULL;
	for(int i = 0;i < m_lnkPageDlgPtr.GetSize();++i)
	{
		pPageDlg = *m_lnkPageDlgPtr[i];
		if(iPageId == pPageDlg->GetPageId())
		{
			pPageDlg->ShowWindow(SW_SHOW);
			m_pCurSelPageDlg = pPageDlg;
			break;
		}
	}

	return 0;
}

void CPs96WorkDlg::InitFileManageDlg()
{
	m_ps96FileManagerDlg.Create(IDD_MIDDLEDLG,this);
	m_ps96FileManagerDlg.ShowWindow(SW_SHOW);
}

int CPs96WorkDlg::OpenFile(int iFileFormat)
{
	CString strTemp(_T(""));

	if(m_ps96FileManagerDlg.m_lnkPageSwitchBtPtr.GetSize() >= MAX_FILEOPEN_NUM)
	{
		CString strFormat = theApp.m_pLangInfo->GetText(159);
		strTemp.Format(strFormat,MAX_FILEOPEN_NUM);
		PopNormalTipInfo(strTemp);
		return -1;
	}

	CString strOpenFormat(_T("")), strSuffix(_T(""));
	strSuffix = PCR_DATA_FILE_SUFFIX;

	if(1 == iFileFormat)
	{
		strOpenFormat.Format(_T("QPCR File(*.%s)|*.%s||"), PCR_DATA_FILE_SUFFIX,PCR_DATA_FILE_SUFFIX);
	}
	else if(2 == iFileFormat)
	{
		strOpenFormat.Format(_T("QPCR File(*.%s)|*.%s||"), PCR_TEMPLATE_FILE_SUFFIX,PCR_TEMPLATE_FILE_SUFFIX);
		strSuffix = PCR_TEMPLATE_FILE_SUFFIX;;
	}
	else
	{
		strOpenFormat.Format(_T("QPCR File(*.%s);(*.%s)|*.%s;*.%s|All File(*.*)|*.*||"), PCR_DATA_FILE_SUFFIX,PCR_TEMPLATE_FILE_SUFFIX,PCR_DATA_FILE_SUFFIX,PCR_TEMPLATE_FILE_SUFFIX);
	}
	
	CFileDialog cf(TRUE,strSuffix,NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,strOpenFormat, this);
	if(IDOK != cf.DoModal())
	{
		return 1;
	}

	//?????????????????????????
	if(m_ps96FileManagerDlg.CheckFileExistOrNot(cf.GetPathName()))
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(160));
		return -2;
	}

	if(m_ps96FileManagerDlg.CheckFileNameExistOrNot(cf.GetFileTitle()))
	{
		strTemp = theApp.m_pLangInfo->GetText(161);
		PopWarningTipInfo(strTemp);
		return -3;
	}

	CExperimentData* pExperimentData = new CExperimentData;
	if (NULL == pExperimentData)
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(251));
		return -3;
	}

	int iRet = pExperimentData->OpenFile(cf.GetPathName());
	if(0 != iRet)
	{
		if(-3 == iRet)
		{
			strTemp = theApp.m_pLangInfo->GetText(252);
		}
		else
		{
			strTemp = theApp.m_pLangInfo->GetText(253);
		}

		PopWarningTipInfo(strTemp);
		delete pExperimentData;

		return -4;
	}
	pExperimentData->SetFileName(cf.GetFileTitle());
	if(cf.GetFileExt() == PCR_TEMPLATE_FILE_SUFFIX)
	{
		pExperimentData->SetTemplateNane(cf.GetFileTitle());
	}
	pExperimentData->ApplyAssayMeanFilterParam();

#ifdef ORDINARY_USER_CHECK_FILEUSERNAME
	//?????????????????????????????????????????????????????????????????
	CString strFileUserName = pExperimentData->GetUserName();
	if(!strFileUserName.IsEmpty() && theApp.GetBeOrdinaryPermission() && strFileUserName != theApp.m_curUserInfo.GetName())
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(377));
		delete pExperimentData;

		return -5;
	}
#endif

	//?????????????????????????????????????????????????????20220511????????
	if(cf.GetFileExt() == PCR_TEMPLATE_FILE_SUFFIX)
	{
		pExperimentData->SetExpFileSaveDirectory(cf.GetFolderPath());
		pExperimentData->SetBeTemplateFile(TRUE);
	}

	m_ps96FileManagerDlg.AddNewPage(pExperimentData,cf.GetFileTitle());	//????????????????SetBaseInfo
	m_ps96FileManagerDlg.SetCurrentSelectPageString(cf.GetFileTitle(),cf.GetPathName());

	m_pCurSelPageDlg->RefreshExpEmbody();

	return 0;
}

int CPs96WorkDlg::OpenPowerOffProtectFile(CString strFilePath)
{
	CString strTemp(_T(""));

	//????????????????????????????????????????????????????????

	CExperimentData* pExperimentData = new CExperimentData;
	if (NULL == pExperimentData)
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(251));
		return -3;
	}

	int iRet = pExperimentData->OpenFile(strFilePath);
	if(0 != iRet)
	{
		if(-3 == iRet)
		{
			strTemp = theApp.m_pLangInfo->GetText(252);
		}
		else
		{
			strTemp = theApp.m_pLangInfo->GetText(253);
		}

		PopWarningTipInfo(strTemp);
		delete pExperimentData;

		return -4;
	}

	//??????????????????????????????????????????????????????????????
	pExperimentData->DeleteMeltData();

	CString strFileTile = GetFileNameFromPath(strFilePath);
	pExperimentData->SetFileName(strFileTile);

	m_ps96FileManagerDlg.AddNewPage(pExperimentData,strFileTile);	//????????????????SetBaseInfo
	m_ps96FileManagerDlg.SetCurrentSelectPageString(strFileTile,strFilePath);

	m_pCurSelPageDlg->RefreshExpEmbody();

	return 0;
}


void CPs96WorkDlg::SetCtrlPos()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	m_rcManage.m_rcInit = rcClient;
	m_rcManage.ClearRectToDelete();

	int iStartX = 60 * m_dHoriRatio;
	CRect rect;
	rect.left = iStartX;
	rect.right = rcClient.right;
	rect.bottom = rcClient.bottom;
	rect.top = rect.bottom - theApp.m_iFileManageDlgH;

	if(NULL != m_ps96FileManagerDlg.GetSafeHwnd())
	{
		m_ps96FileManagerDlg.SetWindowPos(this,rect.left,rect.top,rect.Width(),rect.Height(),SWP_NOZORDER);
	}
	m_rcManage.AddRectToDelete(rect);

	CMiddleDlg* pPageDlg = NULL;
	for(int i = 0;i < m_lnkPageDlgPtr.GetSize();++i)
	{
		pPageDlg = *m_lnkPageDlgPtr[i];
		if(NULL != pPageDlg->GetSafeHwnd())
		{
			pPageDlg->SetWindowPos(this,0,0,rcClient.Width(),rcClient.Height() - rect.Height(),SWP_NOZORDER);
		}
	}
	m_rcManage.AddRectToDelete(0,0,rcClient.Width(),rcClient.Height() - rect.Height());

	m_rcManage.CalcRectResult();

	return;
}

BOOL CPs96WorkDlg::AddTemplate()
{
	CString strOpenFormat;
	strOpenFormat.Format(_T("QPCR File(*.%s)|*.%s||"), PCR_TEMPLATE_FILE_SUFFIX,PCR_TEMPLATE_FILE_SUFFIX);
	CString strSuffix = PCR_TEMPLATE_FILE_SUFFIX;	
	CFileDialog cf(TRUE,strSuffix,NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT,strOpenFormat, this);
	if(IDOK == cf.DoModal())
	{
		CString strFileName = cf.GetFileName();
		CString strTargetFile = CPublicInfo::GetInstance()->GetStartupPath() + _T("Template\\") + strFileName;
		CFileFind	findfile;
		BOOL bFind = findfile.FindFile(strTargetFile);
		if (bFind)
		{ // ???????????????????????
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(532));
			return FALSE;
		}

		CString strFilePath = cf.GetPathName();
		BOOL bCopy = CopyFile(strFilePath, strTargetFile, FALSE);
		if (bCopy)
		{
			CTemplateFileInfo temFileInfo;
			temFileInfo.m_strFileName = strFileName;
			temFileInfo.m_strFilePath = strTargetFile;
			temFileInfo.m_strTitle = cf.GetFileTitle();
			int iAdIndex = theApp.AddNewTemplate(temFileInfo);
			NewTemplateAdded(iAdIndex);
			PopNormalTipInfo(theApp.m_pLangInfo->GetText(534));
		}
		else
		{ // ??????????????
			PopWarningTipInfo(theApp.m_pLangInfo->GetText(533));
			return FALSE;
		}
	}

	return TRUE;
}


int CPs96WorkDlg::DeleteTemplate(int iIndex)
{
	BOOL bDelete = theApp.DeleteTemplate(iIndex);
	if (bDelete)
	{
		CMiddleDlg* pPageDlg = NULL;
		for(int i = 0;i < m_lnkPageDlgPtr.GetSize();++i)
		{
			pPageDlg = *m_lnkPageDlgPtr[i];
			pPageDlg->DeleteTemplateListRow(iIndex);
		}
			
		PopNormalTipInfo(theApp.m_pLangInfo->GetText(536));
		return 0;
	}
	else
	{
		PopWarningTipInfo(theApp.m_pLangInfo->GetText(535));
		return -1;
	}
}

int CPs96WorkDlg::RefreshExpDlgRunState(int iPageId,BOOL bOccupy)
{
	CMiddleDlg* pPageDlg = NULL;
	for(int i = 0;i < m_lnkPageDlgPtr.GetSize();++i)
	{
		pPageDlg = *m_lnkPageDlgPtr[i];
		if(NULL == pPageDlg->GetSafeHwnd())
		{
			continue;
		}
		
		if(iPageId == pPageDlg->GetPageId())
		{
			pPageDlg->RefreshExpDlgRunState(bOccupy);
		}
		else
		{
			pPageDlg->RefreshExpDlgRunState(FALSE);
		}
	}

	return 0;
}

