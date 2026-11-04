// 【交接】 PCRCtrlLib\ReagentItemManager.cpp
// 作用：ReagentItemManager。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CReagentItemManager、Empty、DeleteAll、GetInstance、DestroyInstance、OutputItems、GetCount、GetAt。
#include "StdAfx.h"
#include "ReagentItemManager.h"
#include "PublicFun.h"
#include "LanguageInfo.h"

CReagentItemManager* CReagentItemManager::m_pManager = NULL;

// 函数 CReagentItemManager::CReagentItemManager
// 作用：执行CReagentItemManager。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CReagentItemManager::CReagentItemManager(void)
{
	m_strProjectPath.Empty();
	m_bItemChanged = FALSE;
	m_iNameIndex = 0;
}

// 函数 CReagentItemManager::~CReagentItemManager
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CReagentItemManager::~CReagentItemManager(void)
{
	DeleteAll();
}

// 函数 CReagentItemManager::GetInstance
// 作用：读取GetInstance。
// 参数：无。
// 返回：返回指针 CReagentItemManager*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CReagentItemManager* CReagentItemManager::GetInstance()
{
	if(m_pManager == NULL)
	{
		m_pManager = new CReagentItemManager;
	}

	return m_pManager;
}

// 函数 CReagentItemManager::DestroyInstance
// 作用：执行DestroyInstance。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetItemChanged、OutputItems。
void CReagentItemManager::DestroyInstance()
{
	if(m_pManager != NULL)
	{
		if (m_pManager->GetItemChanged())
		{
			// 提示用户是否需要保存修改过的项目信息
			m_pManager->OutputItems(NULL);
		}
		delete m_pManager;
	}
	m_pManager = NULL;
}

// 函数 CReagentItemManager::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SAFE_DELETE、RemoveAll。
void CReagentItemManager::DeleteAll()
{
	int iCount = m_arrayItems.GetCount();
	for (int i=0; i<iCount; i++)
	{
		CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(i);
		SAFE_DELETE(pItem);
	}
	m_arrayItems.RemoveAll();
}


// 函数 CReagentItemManager::Initialize
// 作用：初始化Initialize。
// 参数：strUserPath：字符串；strStartupPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 _T、FindFile、CreateDirectory、InitializeFromPath、GetCount、FindNameIndex。
void CReagentItemManager::Initialize(CString strUserPath, CString strStartupPath)
{
	m_strProjectPath = strUserPath + _T("\\Project");
	CFileFind finder;
	if (!finder.FindFile(m_strProjectPath)) // 如果没有ExpData路径
	{
		::CreateDirectory(m_strProjectPath, NULL);
	}

	InitializeFromPath(m_strProjectPath);

	if (m_arrayItems.GetCount() == 0)
	{
		// 读取系统安装默认的项目
		CString strPath = strStartupPath + _T("Users\\System\\Project");
		InitializeFromPath(strPath);
	}

	FindNameIndex();
}

// 函数 CReagentItemManager::InitializeFromPath
// 作用：初始化InitializeFromPath。
// 参数：strPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll、FindFile、_T、FindNextFile、GetFileTitle、GetFilePath。
void CReagentItemManager::InitializeFromPath(CString strPath)
{
	DeleteAll();

	CReagentItem* pItem = NULL;
	CFileFind filefind;
	BOOL bFind = filefind.FindFile(strPath + _T("\\*.qprj"));
	while(bFind)
	{
		bFind = filefind.FindNextFile();
		//CString l_strFileTitle = filefind.GetFileTitle();
		CString strFilePath = filefind.GetFilePath();
		if (pItem == NULL)
		{
			pItem = new CReagentItem;
		}
		if (pItem->OpenFile(strFilePath))
		{
			m_arrayItems.Add(pItem);
			pItem = NULL;
		}
	}

	SAFE_DELETE(pItem);

}

// 选择需要导入的项目文件
// 函数 CReagentItemManager::InputItems
// 作用：执行InputItems。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 dlgFile、_T、File、DoModal、GetPathName、GetFileTitle。
void CReagentItemManager::InputItems()
{
	CFileDialog dlgFile(TRUE,_T(".qprj"), NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT ,_T("RtPcr Project File(*.qprj)|*.qprj|All File(*.*)|*.*||"));
	if (dlgFile.DoModal() == IDOK)
	{
		CString strFilename = dlgFile.GetPathName();
		CString strFileTitle = dlgFile.GetFileTitle();

		CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
		WORD wLangId = MAKELANGID(LANG_CHINESE_SIMPLIFIED,SUBLANG_CHINESE_SIMPLIFIED);
		if(pLangInfo->GetBeEnglish())
		{
			wLangId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
		}
		HWND hWnd = NULL;
		CWnd* pMainWnd = AfxGetMainWnd();
		if(NULL != pMainWnd)
		{
			hWnd = pMainWnd->m_hWnd;
		}

		CReagentItem* pItem = FindItemBy(strFileTitle);
		if (pItem != NULL)
		{
			if(IDNO == MessageBoxExW(hWnd,pLangInfo->GetText(265),_T("GeneralPcr"),MB_ICONINFORMATION | MB_YESNO,wLangId))
			{
				return;
			}
		}
		else
		{
			pItem = new CReagentItem;
			m_arrayItems.Add(pItem);
		}

		BOOL bReturn = pItem->OpenFile(strFilename);
		if (bReturn)
		{
			MessageBoxExW(hWnd,pLangInfo->GetText(263),_T("GeneralPcr"),MB_ICONINFORMATION | MB_OK,wLangId);
		}
		else
		{
			MessageBoxExW(hWnd,pLangInfo->GetText(264),_T("GeneralPcr"),MB_ICONINFORMATION | MB_OK,wLangId);
		}
	}

	FindNameIndex();
}

// 保存指定项目信息，如果路径为空，则保存到项目目录下，如果指针为空，则保存全部项目
// 函数 CReagentItemManager::OutputItems
// 作用：执行OutputItems。
// 参数：strSavePath：字符串；pArrayName：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 IsEmpty、GetCount、GetAt、CreateFileNameByName、GetName、SaveFile。
void CReagentItemManager::OutputItems(CString strSavePath, CStringArray* pArrayName)
{
	BOOL bSave = FALSE;
	if (strSavePath.IsEmpty())
	{
		strSavePath = m_strProjectPath;
	}

	if (pArrayName == NULL)
	{
		int iCount = m_arrayItems.GetCount();
		for (int i=0; i<iCount; i++)
		{
			CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(i);
			if (pItem != NULL)
			{
				CString strPathName = CreateFileNameByName(strSavePath, pItem->GetName());
				bSave = pItem->SaveFile(strPathName);
				if (!bSave)
					break;
			}
		}
	}
	else
	{
		int iCount = pArrayName->GetCount();
		for(int i=0; i<iCount; i++)
		{
			CString strProject = pArrayName->GetAt(i);
			CReagentItem* pItem = FindItemBy(strProject);
			if (pItem != NULL)
			{
				CString strPathName = CreateFileNameByName(strSavePath, strProject);
				bSave = pItem->SaveFile(strPathName);
				if (!bSave)
					break;
			}
		}
	}

	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	WORD wLangId = MAKELANGID(LANG_CHINESE_SIMPLIFIED,SUBLANG_CHINESE_SIMPLIFIED);
	if(pLangInfo->GetBeEnglish())
	{
		wLangId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
	}
	HWND hWnd = NULL;
	CWnd* pMainWnd = AfxGetMainWnd();
	if(NULL != pMainWnd)
	{
		hWnd = pMainWnd->m_hWnd;
	}

	if (bSave)
	{
		MessageBoxExW(hWnd,pLangInfo->GetText(261),_T("GeneralPcr"),MB_ICONINFORMATION | MB_OK,wLangId);
	}
	else
	{
		MessageBoxExW(hWnd,pLangInfo->GetText(262),_T("GeneralPcr"),MB_ICONINFORMATION | MB_OK,wLangId);
	}
}

// 函数 CReagentItemManager::FindItemBy
// 作用：执行FindItemBy。
// 参数：strName：字符串。
// 返回：返回指针 CReagentItem*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt、GetName。
CReagentItem* CReagentItemManager::FindItemBy(CString strName)
{
	CReagentItem* pReturn = NULL;
	int iCount = m_arrayItems.GetCount();
	for (int i=0; i<iCount; i++)
	{
		CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(i);
		if (pItem->GetName() == strName)
		{
			pReturn = pItem;
			break;
		}
	}

	return pReturn;
}

// 根据项目名称删除一个项目，同时删除文件
// 函数 CReagentItemManager::DeleteItem
// 作用：更新或清除DeleteItem。
// 参数：strName：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetCount、GetAt、GetName。
BOOL CReagentItemManager::DeleteItem(CString strName)
{
	int iFindIndex = -1;
	int iCount = m_arrayItems.GetCount();
	for (int i=0; i<iCount; i++)
	{
		CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(i);
		if (pItem->GetName() == strName)
		{
			iFindIndex = i;
			break;
		}
	}

	if (iFindIndex != -1)
	{
		return DeleteItem(iFindIndex);
	}
	return FALSE;
}

// 函数 CReagentItemManager::DeleteItem
// 作用：更新或清除DeleteItem。
// 参数：iIndex：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetAt、GetStatus、GetInstance、MAKELANGID、GetBeEnglish、AfxGetMainWnd。
BOOL CReagentItemManager::DeleteItem(int iIndex)
{
	CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(iIndex);

	if (pItem->GetStatus() != CReagentItem::STATUS_NEW)
	{
		CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
		WORD wLangId = MAKELANGID(LANG_CHINESE_SIMPLIFIED,SUBLANG_CHINESE_SIMPLIFIED);
		if(pLangInfo->GetBeEnglish())
		{
			wLangId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
		}
		HWND hWnd = NULL;
		CWnd* pMainWnd = AfxGetMainWnd();
		if(NULL != pMainWnd)
		{
			hWnd = pMainWnd->m_hWnd;
		}

		CString strFilePath = CreateFileNameByName(m_strProjectPath, pItem->GetName());
		BOOL bSuccess = ::DeleteFile(strFilePath);
		if (bSuccess)
		{
			SAFE_DELETE(pItem);
			m_arrayItems.RemoveAt(iIndex);
			FindNameIndex();
			MessageBoxExW(hWnd,pLangInfo->GetText(266),_T("GeneralPcr"),MB_ICONINFORMATION | MB_OK,wLangId);
			return TRUE;
		}
		else
		{
			MessageBoxExW(hWnd,pLangInfo->GetText(267),_T("GeneralPcr"),MB_ICONINFORMATION | MB_OK,wLangId);
			return FALSE;
		}
	}
	else
	{
		SAFE_DELETE(pItem);
		m_arrayItems.RemoveAt(iIndex);
		FindNameIndex();
		return TRUE;
	}
}

// 函数 CReagentItemManager::CanDelete
// 作用：判断CanDelete是否成立。
// 参数：iIndex：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetCount、GetAt、GetStatus。
BOOL CReagentItemManager::CanDelete(int iIndex)
{
	if (iIndex >=0 && iIndex < m_arrayItems.GetCount())
	{
		CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(iIndex);

		return pItem->GetStatus() != CReagentItem::STATUS_USING;
	}

	return FALSE;
}

// 函数 CReagentItemManager::CreateFileNameByName
// 作用：创建或加入CreateFileNameByName。
// 参数：strPath：字符串；strName：字符串。
// 返回：返回一段文字。
// 过程：函数里会调用 Format、_T。
CString CReagentItemManager::CreateFileNameByName(CString strPath, CString strName)
{
	CString strFileName;
	strFileName.Format(_T("%s.qprj"), strName);
	CString strPathName = strPath + _T("\\") + strFileName;
	return strPathName;
}

// 函数 CReagentItemManager::NewOneItem
// 作用：执行NewOneItem。
// 参数：无。
// 返回：返回指针 CReagentItem*。指针为空表示没有取到对象。
// 过程：函数里会调用 Format、_T、SetName。
CReagentItem* CReagentItemManager::NewOneItem()
{
	CReagentItem* pItem = new CReagentItem;
	m_iNameIndex ++;
	CString strName;
	strName.Format(_T("Project%d"), m_iNameIndex);
	pItem->SetName(strName);

	return pItem;
}

// 函数 CReagentItemManager::GetBeNewPrj
// 作用：读取GetBeNewPrj。
// 参数：iIndex：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetCount、GetAt、GetStatus。
BOOL CReagentItemManager::GetBeNewPrj(int iIndex)
{
	if(iIndex < 0 || iIndex >= m_arrayItems.GetCount())
	{
		return FALSE;
	}

	CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(iIndex);
	if(NULL == pItem)
	{
		return TRUE;
	}

	return CReagentItem::STATUS_NEW == pItem->GetStatus();
}

// 函数 CReagentItemManager::FindNameIndex
// 作用：执行FindNameIndex。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、GetName、Find、_T、Right。
void CReagentItemManager::FindNameIndex()
{
	m_iNameIndex = 0;

	int iCount = m_arrayItems.GetCount();
	for (int i=0; i<iCount; i++)
	{
		CReagentItem* pItem = (CReagentItem*)m_arrayItems.GetAt(i);
		if (pItem != NULL)
		{
			CString strName = pItem->GetName();
			int iFind = strName.Find(_T("Project"));
			if (iFind != -1)
			{
				CString strIndex = strName.Right(strName.GetLength() - iFind - 7);
				int iTemp = _ttoi(strIndex);
				if (iTemp > m_iNameIndex)
				{
					m_iNameIndex = iTemp;
				}
			}
		}
	}
}
