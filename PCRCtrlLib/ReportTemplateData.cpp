// 【交接】 PCRCtrlLib\ReportTemplateData.cpp
// 作用：ReportTemplateData。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CReportTemplateData、Empty、DeleteAll、GetAt、SAFE_DELETE、RemoveAll、SetStartupPath、_T。
#include "StdAfx.h"
#include "ReportTemplateData.h"
#include "PublicFun.h"
#include "DeclaresPCR.h"

// 函数 CReportTemplateData::CReportTemplateData
// 作用：执行CReportTemplateData。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CReportTemplateData::CReportTemplateData(void)
{
	m_wFileFlag = wFileReportTemplateMarkPCR;
	m_wFileVersion = wPCRVersion101;

	m_strFilePath.Empty();
	m_iUsedIndex = -1;
	m_bChanged = FALSE;
}


// 函数 CReportTemplateData::~CReportTemplateData
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CReportTemplateData::~CReportTemplateData(void)
{
	DeleteAll();
}

// 函数 CReportTemplateData::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SAFE_DELETE、RemoveAll。
void CReportTemplateData::DeleteAll()
{
	for (int i=0; i<m_arrayTemplate.GetCount(); i++)
	{
		tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(i);
		SAFE_DELETE(pTemplate);
	}

	m_arrayTemplate.RemoveAll();
	m_iUsedIndex = -1;
}



// 函数 CReportTemplateData::SetStartupPath
// 作用：设置SetStartupPath。
// 参数：strPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
void CReportTemplateData::SetStartupPath(CString strPath)
{
	m_strFilePath = strPath + _T("AtilaReportTemplate") + PCR_REPORT_TEMPLATE_FILE_SUFFIX_DOT;
}

// 函数 CReportTemplateData::SaveFile
// 作用：把SaveFile写入文件、仪器或界面。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CReportTemplateData::SaveFile()
{
	return SaveFile(m_strFilePath);
}

// 函数 CReportTemplateData::OpenFile
// 作用：读入OpenFile。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CReportTemplateData::OpenFile()
{
	return OpenFile(m_strFilePath);
}

// 函数 CReportTemplateData::SaveFile
// 作用：把SaveFile写入文件、仪器或界面。
// 参数：strFilePath：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 Open、Write、GetCount、GetAt、WriteStringToFile。
BOOL CReportTemplateData::SaveFile(CString strFilePath)
{
	CFile file;       
	CFileException e;
	if (!file.Open(strFilePath,CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone, &e))
	{
		return FALSE;
	}

	// 写入文件标识和版本
	file.Write((const char*)&m_wFileFlag, sizeof(WORD));
	file.Write((const char*)&m_wFileVersion, sizeof(WORD));

	file.Write((const char*)&m_iUsedIndex, sizeof(int));

	int iTemplateCount = m_arrayTemplate.GetCount();
	file.Write((const char*)&iTemplateCount, sizeof(int));
	for(int i=0; i<iTemplateCount; i++)
	{
		tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(i);
		CPublicFun::WriteStringToFile(&file, pTemplate->strName);
		CPublicFun::WriteStringToFile(&file, pTemplate->strLabName);
		CPublicFun::WriteStringToFile(&file, pTemplate->strLabAddress);
		CPublicFun::WriteStringToFile(&file, pTemplate->strContactUrl);
		CPublicFun::WriteStringToFile(&file, pTemplate->strContactEmail);
		CPublicFun::WriteStringToFile(&file, pTemplate->strContactPhone);
		CPublicFun::WriteStringToFile(&file, pTemplate->strTestName);
		CPublicFun::WriteStringToFile(&file, pTemplate->strDisclaimer);
		CPublicFun::WriteStringToFile(&file, pTemplate->strLogoFile);
	}

	return TRUE;
}


// 函数 CReportTemplateData::OpenFile
// 作用：读入OpenFile。
// 参数：strFilePath：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 Open、Read、Close、ReadStringFromFile、Add。
BOOL CReportTemplateData::OpenFile(CString strFilePath)
{
	CFile file;       
	if (!file.Open(strFilePath,CFile::modeRead | CFile::shareDenyNone))
	{
		return FALSE;
	}

	// 读取文件标识和版本
	WORD wFileMark = 0;
	file.Read(&wFileMark, sizeof(WORD));
	if (wFileMark != wFileReportTemplateMarkPCR)
	{
		file.Close();
		return FALSE;
	}

	WORD wFileVersion = 0;
	file.Read(&wFileVersion, sizeof(WORD));

	file.Read(&m_iUsedIndex, sizeof(int));

	int iTemplateCount = 0;
	file.Read(&iTemplateCount, sizeof(int));
	for(int i=0; i<iTemplateCount; i++)
	{
		tagTemplate* pTemplate = new tagTemplate;
		pTemplate->strName = CPublicFun::ReadStringFromFile(&file);
		pTemplate->strLabName = CPublicFun::ReadStringFromFile(&file);
		pTemplate->strLabAddress = CPublicFun::ReadStringFromFile(&file);
		pTemplate->strContactUrl = CPublicFun::ReadStringFromFile(&file);
		pTemplate->strContactEmail = CPublicFun::ReadStringFromFile(&file);
		pTemplate->strContactPhone = CPublicFun::ReadStringFromFile(&file);
		pTemplate->strTestName = CPublicFun::ReadStringFromFile(&file);
		pTemplate->strDisclaimer = CPublicFun::ReadStringFromFile(&file);
		if (wFileVersion >= wPCRVersion101)
		{
			pTemplate->strLogoFile = CPublicFun::ReadStringFromFile(&file);
		}

		m_arrayTemplate.Add(pTemplate);
	}

	file.Close();
	return TRUE;
}

// 函数 CReportTemplateData::AddTemplate
// 作用：创建或加入AddTemplate。
// 参数：nFlag：整数；string：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetStringTo、Add。
int CReportTemplateData::AddTemplate(eDataFlag nFlag, CString string)
{
	tagTemplate* pTemplate = new tagTemplate;
	SetStringTo(pTemplate, nFlag, string);
	return m_arrayTemplate.Add(pTemplate);
}

// 函数 CReportTemplateData::DeleteTemplate
// 作用：更新或清除DeleteTemplate。
// 参数：iIndex：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt、SAFE_DELETE、RemoveAt、GetCount。
void CReportTemplateData::DeleteTemplate(int iIndex)
{
	if (iIndex == m_iUsedIndex)
	{
		tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(iIndex);
		SAFE_DELETE(pTemplate);
		m_arrayTemplate.RemoveAt(iIndex);
		if (m_iUsedIndex >= m_arrayTemplate.GetCount())
			m_iUsedIndex --;
	}
	else if (iIndex < m_iUsedIndex)
	{
		tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(iIndex);
		SAFE_DELETE(pTemplate);
		m_arrayTemplate.RemoveAt(iIndex);
		m_iUsedIndex --;
	}
	else
	{
		tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(iIndex);
		SAFE_DELETE(pTemplate);
		m_arrayTemplate.RemoveAt(iIndex);
	}
}

// 函数 CReportTemplateData::GetStringBy
// 作用：读取GetStringBy。
// 参数：nFlag：整数；iIndex：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetAt。
CString CReportTemplateData::GetStringBy(eDataFlag nFlag, int iIndex)
{
	int iCurIndex = iIndex;
	if (iCurIndex == -1)
	{
		iCurIndex = m_iUsedIndex;
		if (iCurIndex < 0)
			iCurIndex = 0;
	}
	tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(iCurIndex);
	return GetStringBy(pTemplate, nFlag);
}

// 函数 CReportTemplateData::SetStringTo
// 作用：设置SetStringTo。
// 参数：nFlag：整数；string：字符串；iIndex：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt。
void CReportTemplateData::SetStringTo(eDataFlag nFlag, CString string, int iIndex)
{
	int iCurIndex = iIndex;
	if (iCurIndex == -1)
	{
		iCurIndex = m_iUsedIndex;
		if (iCurIndex < 0)
			iCurIndex = 0;
	}
	tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(iCurIndex);
	SetStringTo(pTemplate, nFlag, string);
}

// 函数 CReportTemplateData::GetStringBy
// 作用：读取GetStringBy。
// 参数：pTemplate：指针，指向调用方传入的对象；nFlag：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 Empty。
CString CReportTemplateData::GetStringBy(tagTemplate* pTemplate, eDataFlag nFlag)
{
	CString strReturn;
	strReturn.Empty();

	switch(nFlag)
	{
	case DATA_NAME:
		strReturn = pTemplate->strName;
		break;
	case DATA_LAB_NAME:
		strReturn = pTemplate->strLabName;
		break;
	case DATA_ADDRESS:
		strReturn = pTemplate->strLabAddress;
		break;
	case DATA_CONTACT_URL:
		strReturn = pTemplate->strContactUrl;
		break;
	case DATA_CONTACT_EMAIL:
		strReturn = pTemplate->strContactEmail;
		break;
	case DATA_CONTACT_PHONE:
		strReturn = pTemplate->strContactPhone;
		break;
	case DATA_TEST_NAME:
		strReturn = pTemplate->strTestName;
		break;
	case DATA_DISCLAIMER:
		strReturn = pTemplate->strDisclaimer;
		break;
	case DATA_LOGO_FILE:
		strReturn = pTemplate->strLogoFile;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return strReturn;
}

// 函数 CReportTemplateData::SetStringTo
// 作用：设置SetStringTo。
// 参数：pTemplate：指针，指向调用方传入的对象；nFlag：整数；string：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CReportTemplateData::SetStringTo(tagTemplate* pTemplate, eDataFlag nFlag, CString string)
{
	switch(nFlag)
	{
	case DATA_NAME:
		pTemplate->strName = string;
		break;
	case DATA_LAB_NAME:
		pTemplate->strLabName = string;
		break;
	case DATA_ADDRESS:
		pTemplate->strLabAddress = string;
		break;
	case DATA_CONTACT_URL:
		pTemplate->strContactUrl = string;
		break;
	case DATA_CONTACT_EMAIL:
		pTemplate->strContactEmail = string;
		break;
	case DATA_CONTACT_PHONE:
		pTemplate->strContactPhone = string;
		break;
	case DATA_TEST_NAME:
		pTemplate->strTestName = string;
		break;
	case DATA_DISCLAIMER:
		pTemplate->strDisclaimer = string;
		break;
	case DATA_LOGO_FILE:
		pTemplate->strLogoFile = string;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

// 函数 CReportTemplateData::CopyTo
// 作用：复制CopyTo。
// 参数：pTargetData：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll、GetCount、GetAt、AddTemplate、SetStringTo。
void CReportTemplateData::CopyTo(CReportTemplateData* pTargetData)
{
	pTargetData->DeleteAll();

	for (int i=0; i<m_arrayTemplate.GetCount(); i++)
	{
		tagTemplate* pTemplate = (tagTemplate*)m_arrayTemplate.GetAt(i);
		int iIndex = pTargetData->AddTemplate(DATA_NAME, pTemplate->strName);
		pTargetData->SetStringTo(DATA_LAB_NAME, pTemplate->strLabName, iIndex);
		pTargetData->SetStringTo(DATA_ADDRESS, pTemplate->strLabAddress, iIndex);
		pTargetData->SetStringTo(DATA_CONTACT_URL, pTemplate->strContactUrl, iIndex);
		pTargetData->SetStringTo(DATA_CONTACT_EMAIL, pTemplate->strContactEmail, iIndex);
		pTargetData->SetStringTo(DATA_CONTACT_PHONE, pTemplate->strContactPhone, iIndex);
		pTargetData->SetStringTo(DATA_TEST_NAME, pTemplate->strTestName, iIndex);
		pTargetData->SetStringTo(DATA_DISCLAIMER, pTemplate->strDisclaimer, iIndex);
		pTargetData->SetStringTo(DATA_LOGO_FILE, pTemplate->strLogoFile, iIndex);
	}
}

// 函数 CReportTemplateData::CopyFrom
// 作用：复制CopyFrom。
// 参数：pSourceData：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll、GetTemplateCount、AddTemplate、GetStringBy、SetStringTo、GetCount。
void CReportTemplateData::CopyFrom(CReportTemplateData* pSourceData)
{
	int iOldSel = m_iUsedIndex;
	DeleteAll();

	for (int i=0; i<pSourceData->GetTemplateCount(); i++)
	{
		int iIndex = AddTemplate(DATA_NAME, pSourceData->GetStringBy(DATA_NAME, i));
		SetStringTo(DATA_LAB_NAME, pSourceData->GetStringBy(DATA_LAB_NAME, i), iIndex);
		SetStringTo(DATA_ADDRESS, pSourceData->GetStringBy(DATA_ADDRESS, i), iIndex);
		SetStringTo(DATA_CONTACT_URL, pSourceData->GetStringBy(DATA_CONTACT_URL, i), iIndex);
		SetStringTo(DATA_CONTACT_EMAIL, pSourceData->GetStringBy(DATA_CONTACT_EMAIL, i), iIndex);
		SetStringTo(DATA_CONTACT_PHONE, pSourceData->GetStringBy(DATA_CONTACT_PHONE, i), iIndex);
		SetStringTo(DATA_TEST_NAME, pSourceData->GetStringBy(DATA_TEST_NAME, i), iIndex);
		SetStringTo(DATA_DISCLAIMER, pSourceData->GetStringBy(DATA_DISCLAIMER, i), iIndex);
		SetStringTo(DATA_LOGO_FILE, pSourceData->GetStringBy(DATA_LOGO_FILE, i), iIndex);
	}

	if (iOldSel >= m_arrayTemplate.GetCount())
		m_iUsedIndex = m_arrayTemplate.GetCount()-1;
	else
		m_iUsedIndex = iOldSel;
}


// 函数 CReportTemplateData::SetCurSel
// 作用：设置SetCurSel。
// 参数：strName：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetStringBy。
void CReportTemplateData::SetCurSel(CString strName)
{
	int iSelected = -1;
	for (int i=0; i<m_arrayTemplate.GetCount(); i++)
	{
		if (strName == GetStringBy(DATA_NAME, i))
		{
			iSelected = i;
			break;
		}
	}
	if (iSelected != -1)
	{
		m_iUsedIndex = iSelected;
	}
}



// 函数 CReportTemplateData::FindSameName
// 作用：执行FindSameName。
// 参数：strName：字符串。
// 返回：返回是或否。
// 过程：函数里会调用 GetTemplateCount、GetStringBy。
BOOL CReportTemplateData::FindSameName(CString strName)
{
	BOOL bFind = FALSE;
	for (int i=0; i<GetTemplateCount(); i++)
	{
		if (strName == GetStringBy(DATA_NAME, i))
		{
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}

// 函数 CReportTemplateData::AddTemplate
// 作用：创建或加入AddTemplate。
// 参数：pInputTemplate：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Add。
int CReportTemplateData::AddTemplate(tagTemplate* pInputTemplate)
{
	tagTemplate* pTemplate = new tagTemplate;
	*pTemplate = *pInputTemplate;
	return m_arrayTemplate.Add(pTemplate);
}

// 函数 CReportTemplateData::GetTemplate
// 作用：读取GetTemplate。
// 参数：iIndex：整数。
// 返回：返回指针 CReportTemplateData::tagTemplate*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：函数里会调用 GetCount、GetAt。
CReportTemplateData::tagTemplate* CReportTemplateData::GetTemplate(int iIndex)
{
	if (iIndex < 0 || iIndex >= m_arrayTemplate.GetCount())
		return NULL;
	return (tagTemplate*)m_arrayTemplate.GetAt(iIndex);
}
