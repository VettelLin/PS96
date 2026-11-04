// 【交接】 PCRCtrlLib\TubeInfo.cpp
// 作用：单孔样本。在通道阴阳性已经写好之后，按内标、阳性对照、阴性对照汇总整孔结论。
// 先看这些函数：CTubeInfo、Empty、RGB、DeleteAllDyeTargetInfo、GetCount、GetAt、SAFE_DELETE、RemoveAll。
#include "StdAfx.h"
#include "TubeInfo.h"
#include "PublicFun.h"
#include "Define.h"

// 函数 CTubeInfo::CTubeInfo
// 作用：执行CTubeInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty、RGB。
CTubeInfo::CTubeInfo()
{
	m_iTubeID = 1;
	m_strTubeLabel.Empty();
	m_strTubeFlag.Empty();
	m_strSampleID.Empty();
	m_strSampleName.Empty();
	m_clrSample = RGB(255, 0, 0);
	m_nSampleType = SAMPLE_TYPE_UNKNOWN;
	m_bRepeatTube = FALSE;
	m_iRepeatNo = -1;
	m_strComments.Empty();

	m_iCalibrateChannel = -1;
	m_iCycleOfMaxMOTRatio = -1;
}

// 函数 CTubeInfo::CTubeInfo
// 作用：执行CTubeInfo。
// 参数：nID：整数。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CTubeInfo::CTubeInfo(int nID)
{
	m_iTubeID = nID;
	m_strTubeLabel.Empty();
	m_strTubeFlag.Empty();
	m_strSampleID.Empty();
	m_strSampleName.Empty();
	m_nSampleType = SAMPLE_TYPE_UNKNOWN;
	m_bRepeatTube = FALSE;
	m_iRepeatNo = -1;
	m_strComments.Empty();

	m_iCalibrateChannel = -1;
	m_iCycleOfMaxMOTRatio = -1;
}

// 函数 CTubeInfo::~CTubeInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAllDyeTargetInfo。
CTubeInfo::~CTubeInfo(void)
{
	DeleteAllDyeTargetInfo();
}

// 函数 CTubeInfo::DeleteAllDyeTargetInfo
// 作用：更新或清除DeleteAllDyeTargetInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SAFE_DELETE、RemoveAll。
void CTubeInfo::DeleteAllDyeTargetInfo()
{
	int nDyeCount = m_arrayDyeTarget.GetCount();
	for(int i=0; i<nDyeCount; i++)
	{
		CDyeTargetInfo* pTarget = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		SAFE_DELETE(pTarget);
	}
	m_arrayDyeTarget.RemoveAll();
}

// 函数 CTubeInfo::CTubeInfo
// 作用：执行CTubeInfo。
// 参数：tubeInfo):CSampleInfo(tubeInfo。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAllDyeTargetInfo、GetCount、CDyeTargetInfo、GetAt、Add。
CTubeInfo::CTubeInfo(const CTubeInfo& tubeInfo):CSampleInfo(tubeInfo)
{
	m_iTubeID = tubeInfo.m_iTubeID;
	m_strTubeLabel = tubeInfo.m_strTubeLabel;
	m_strTubeFlag = tubeInfo.m_strTubeFlag;
	m_strSampleID = tubeInfo.m_strSampleID;
	m_strSampleName = tubeInfo.m_strSampleName;
	m_nSampleType = tubeInfo.m_nSampleType;
	m_bRepeatTube = tubeInfo.m_bRepeatTube;
	m_iRepeatNo = tubeInfo.m_iRepeatNo;
	m_strComments = tubeInfo.m_strComments;
	m_iCalibrateChannel = tubeInfo.m_iCalibrateChannel;

	DeleteAllDyeTargetInfo();
	int nTargetCount = tubeInfo.m_arrayDyeTarget.GetCount();
	CDyeTargetInfo *pTargetSource = NULL,*pTargetDest = NULL;
	for (int i = 0;i < nTargetCount;++i)
	{
		pTargetDest = new CDyeTargetInfo();
		pTargetSource = (CDyeTargetInfo*)tubeInfo.m_arrayDyeTarget.GetAt(i);
		*pTargetDest = *pTargetSource;
		m_arrayDyeTarget.Add(pTargetDest);
		pTargetDest = NULL;
	}

	return;
}

void CTubeInfo::operator=(const CTubeInfo& tubeInfo)
{
	CSampleInfo::operator=(tubeInfo);
	m_iTubeID = tubeInfo.m_iTubeID;
	m_strTubeLabel = tubeInfo.m_strTubeLabel;
	m_strTubeFlag = tubeInfo.m_strTubeFlag;
	m_strSampleID = tubeInfo.m_strSampleID;
	m_strSampleName = tubeInfo.m_strSampleName;
	m_nSampleType = tubeInfo.m_nSampleType;
	m_bRepeatTube = tubeInfo.m_bRepeatTube;
	m_iRepeatNo = tubeInfo.m_iRepeatNo;
	m_strComments = tubeInfo.m_strComments;
	m_iCalibrateChannel = tubeInfo.m_iCalibrateChannel;

	DeleteAllDyeTargetInfo();
	int nTargetCount = tubeInfo.m_arrayDyeTarget.GetCount();
	CDyeTargetInfo *pTargetSource = NULL,*pTargetDest = NULL;
	for (int i = 0;i < nTargetCount;++i)
	{
		pTargetDest = new CDyeTargetInfo();
		pTargetSource = (CDyeTargetInfo*)tubeInfo.m_arrayDyeTarget.GetAt(i);
		*pTargetDest = *pTargetSource;
		m_arrayDyeTarget.Add(pTargetDest);
		pTargetDest = NULL;
	}

	return;
}

// 函数 CTubeInfo::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 Write、WriteStringToFile、GetCount、GetAt。
BOOL CTubeInfo::WriteFile(CFile* pFile,WORD wVersion)
{
	pFile->Write((const char *)&m_iTubeID, sizeof(int));

	CPublicFun::WriteStringToFile(pFile, m_strTubeLabel);
	CPublicFun::WriteStringToFile(pFile, m_strTubeFlag);
	CPublicFun::WriteStringToFile(pFile, m_strSampleID);
	CPublicFun::WriteStringToFile(pFile, m_strSampleName);
	pFile->Write((const char *)&m_clrSample, sizeof(COLORREF));

	int nTempInt = m_nSampleType;
	pFile->Write((const char *)&nTempInt, sizeof(int));
	pFile->Write((const char *)&m_bRepeatTube, sizeof(BOOL));
	pFile->Write((const char *)&m_iRepeatNo, sizeof(int));
	CPublicFun::WriteStringToFile(pFile, m_strComments);

	int nTargetCount = m_arrayDyeTarget.GetCount();
	pFile->Write((const char *)&nTargetCount, sizeof(int));
	for (int i=0; i<nTargetCount; i++)
	{
		CDyeTargetInfo* pTarget = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		pTarget->WriteFile(pFile,wVersion);
	}

	if(wVersion >= wPCRVersion104)
	{
		CPublicFun::WriteStringToFile(pFile, m_strPatientID);
		CPublicFun::WriteStringToFile(pFile, m_strClinicID);
		CPublicFun::WriteStringToFile(pFile, m_strCaseID);
		CPublicFun::WriteStringToFile(pFile, m_strPatientName);
		CPublicFun::WriteStringToFile(pFile, m_strAreaNo);
		CPublicFun::WriteStringToFile(pFile, m_strRoomNo);
		CPublicFun::WriteStringToFile(pFile, m_strBedNo);
		CPublicFun::WriteStringToFile(pFile, m_strProposer);
		CPublicFun::WriteStringToFile(pFile, m_strDepartment);
		CPublicFun::WriteStringToFile(pFile, m_strHospital);
		CPublicFun::WriteStringToFile(pFile, m_strCollectDate);
		CPublicFun::WriteStringToFile(pFile, m_strApplyDate);

		pFile->Write((const char *)&m_nPatientSex,sizeof(ePatientSexuality));
		pFile->Write((const char *)&m_nPatientAge,sizeof(int));
		pFile->Write((const char *)&m_nAgeUnit,sizeof(ePatientAgeUnit));
	}

	return TRUE;
}

// 函数 CTubeInfo::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAllDyeTargetInfo、Read、ReadStringFromFile、Add。
BOOL CTubeInfo::ReadFile(CFile* pFile, WORD wVersion)
{
	DeleteAllDyeTargetInfo();

	pFile->Read(&m_iTubeID, sizeof(int));

	m_strTubeLabel = CPublicFun::ReadStringFromFile(pFile);
	m_strTubeFlag = CPublicFun::ReadStringFromFile(pFile);
	m_strSampleID = CPublicFun::ReadStringFromFile(pFile);
	m_strSampleName = CPublicFun::ReadStringFromFile(pFile);
	if (wVersion >= wPCRVersion101)
	{
		pFile->Read((char *)&m_clrSample, sizeof(COLORREF));
	}

	int tempInt = 0;
	pFile->Read(&tempInt, sizeof(int));
	m_nSampleType = (eSampleType)tempInt;
	pFile->Read(&m_bRepeatTube, sizeof(BOOL));
	pFile->Read(&m_iRepeatNo, sizeof(int));
	m_strComments = CPublicFun::ReadStringFromFile(pFile);

	int nTargetCount = 0;
	pFile->Read(&nTargetCount, sizeof(int));
	for (int i=0; i<nTargetCount; i++)
	{
		CDyeTargetInfo* pTarget = new CDyeTargetInfo;
		pTarget->ReadFile(pFile, wVersion);
		m_arrayDyeTarget.Add(pTarget);
	}

	if(wVersion >= wPCRVersion104)
	{
		m_strPatientID = CPublicFun::ReadStringFromFile(pFile);
		m_strClinicID = CPublicFun::ReadStringFromFile(pFile);
		m_strCaseID = CPublicFun::ReadStringFromFile(pFile);
		m_strPatientName = CPublicFun::ReadStringFromFile(pFile);
		m_strAreaNo = CPublicFun::ReadStringFromFile(pFile);
		m_strRoomNo = CPublicFun::ReadStringFromFile(pFile);
		m_strBedNo = CPublicFun::ReadStringFromFile(pFile);
		m_strProposer = CPublicFun::ReadStringFromFile(pFile);
		m_strDepartment = CPublicFun::ReadStringFromFile(pFile);
		m_strHospital = CPublicFun::ReadStringFromFile(pFile);
		m_strCollectDate = CPublicFun::ReadStringFromFile(pFile);
		m_strApplyDate = CPublicFun::ReadStringFromFile(pFile);

		pFile->Read(&m_nPatientSex,sizeof(ePatientSexuality));
		pFile->Read(&m_nPatientAge,sizeof(int));
		pFile->Read(&m_nAgeUnit,sizeof(ePatientAgeUnit));
	}

	return TRUE;
}

// 函数 CTubeInfo::SetTmCount
// 作用：设置SetTmCount。
// 参数：nCount：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt。
void CTubeInfo::SetTmCount(int nCount)
{
	int nTargetCount = m_arrayDyeTarget.GetCount();
	for (int i=0; i<nTargetCount; i++)
	{
		CDyeTargetInfo* pTarget = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		pTarget->SetTmCount(nCount);
	}
}

// 函数 CTubeInfo::GetTargetInfo
// 作用：读取GetTargetInfo。
// 参数：iIndex：整数。
// 返回：返回指针 CDyeTargetInfo*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt。
CDyeTargetInfo* CTubeInfo::GetTargetInfo(int iIndex)
{
	CDyeTargetInfo* pDyeInfo = NULL;
	if (iIndex < m_arrayDyeTarget.GetCount())
	{
		pDyeInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iIndex);
	}

	return pDyeInfo;
}

// 函数 CTubeInfo::GetRepeatNoString
// 作用：读取GetRepeatNoString。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 _T、strTemp、Format。
CString CTubeInfo::GetRepeatNoString()
{
	if(-1 == m_iRepeatNo)
	{
		return _T("");
	}

	CString strTemp(_T(""));
	strTemp.Format(_T("%d"),m_iRepeatNo);
	return strTemp;
}

// 函数 CTubeInfo::FindTargetInfoByTarget
// 作用：执行FindTargetInfoByTarget。
// 参数：strTarget：字符串。
// 返回：返回指针 CDyeTargetInfo*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt、GetTargetName。
CDyeTargetInfo* CTubeInfo::FindTargetInfoByTarget(CString strTarget)
{
	CDyeTargetInfo* pDyeInfo = NULL;
	int iCount = m_arrayDyeTarget.GetCount();
	for (int i=0; i<iCount; i++)
	{
		CDyeTargetInfo* pTemp = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if (pTemp->GetTargetName() == strTarget)
		{
			pDyeInfo = pTemp;
			break;
		}
	}
	return pDyeInfo;
}

// 函数 CTubeInfo::FindTargetInfoByChannel
// 作用：执行FindTargetInfoByChannel。
// 参数：iChannel：整数。
// 返回：返回指针 CDyeTargetInfo*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt、GetChannel。
CDyeTargetInfo* CTubeInfo::FindTargetInfoByChannel(int iChannel)
{
	CDyeTargetInfo* pDyeInfo = NULL;
	int iCount = m_arrayDyeTarget.GetCount();
	for (int i=0; i<iCount; i++)
	{
		CDyeTargetInfo* pTemp = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if (pTemp->GetChannel() == iChannel)
		{
			pDyeInfo = pTemp;
			break;
		}
	}
	return pDyeInfo;
}

// 函数 CTubeInfo::ResetDyeInfo
// 作用：更新或清除ResetDyeInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SetBeSelected、SetDyeName、_T、SetTargetName。
void CTubeInfo::ResetDyeInfo()
{
	CDyeTargetInfo* pDyeInfo = NULL;
	int iCount = m_arrayDyeTarget.GetCount();
	for (int i = 0;i < iCount;++i)
	{
		pDyeInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if(NULL != pDyeInfo)
		{
			pDyeInfo->SetBeSelected(FALSE);
			pDyeInfo->SetDyeName(_T(""));
			pDyeInfo->SetTargetName(_T(""));
			pDyeInfo->SetQuantity(0,4);
		}
	}
	return;
}

// 函数 CTubeInfo::ResetDyeTargetInfoExceptDyeNameAndColor
// 作用：更新或清除ResetDyeTargetInfoExceptDyeNameAndColor。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SetBeSelected、SetQuantity。
void CTubeInfo::ResetDyeTargetInfoExceptDyeNameAndColor()
{
	CDyeTargetInfo* pDyeInfo = NULL;
	int iCount = m_arrayDyeTarget.GetCount();
	for (int i = 0;i < iCount;++i)
	{
		pDyeInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if(NULL != pDyeInfo)
		{
			pDyeInfo->SetBeSelected(FALSE);
			pDyeInfo->SetQuantity(0,4);
		}
	}
	return;
}

// 函数 CTubeInfo::GetDyeName
// 作用：读取GetDyeName。
// 参数：iIndex：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetSize、_T、GetAt。
CString CTubeInfo::GetDyeName(int iIndex)
{
	if(iIndex < 0 || iIndex >= m_arrayDyeTarget.GetSize())
	{
		return _T("");
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iIndex);
	if(NULL == pDyeTargetInfo)
	{
		return _T("");
	}

	return pDyeTargetInfo->GetDyeName();
}

// 函数 CTubeInfo::SetDyeName
// 作用：设置SetDyeName。
// 参数：iIndex：整数；strDyeName：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt。
void CTubeInfo::SetDyeName(int iIndex,CString strDyeName)
{
	if(iIndex < 0 || iIndex >= m_arrayDyeTarget.GetSize())
	{
		return;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iIndex);
	if(NULL == pDyeTargetInfo)
	{
		return;
	}

	pDyeTargetInfo->SetDyeName(strDyeName);
	return; 
}

// 函数 CTubeInfo::GetTargetName
// 作用：读取GetTargetName。
// 参数：iIndex：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetSize、_T、GetAt。
CString CTubeInfo::GetTargetName(int iIndex)
{
	if(iIndex < 0 || iIndex >= m_arrayDyeTarget.GetSize())
	{
		return _T("");
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iIndex);
	if(NULL == pDyeTargetInfo)
	{
		return _T("");
	}

	return pDyeTargetInfo->GetTargetName();
}

// 函数 CTubeInfo::SetTargetName
// 作用：设置SetTargetName。
// 参数：iIndex：整数；strTarget：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt。
void CTubeInfo::SetTargetName(int iIndex,CString strTarget)
{
	if(iIndex < 0 || iIndex >= m_arrayDyeTarget.GetSize())
	{
		return;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iIndex);
	if(NULL == pDyeTargetInfo)
	{
		return;
	}

	pDyeTargetInfo->SetTargetName(strTarget);
	return;
}

// 函数 CTubeInfo::GetDyeTargetInfo
// 作用：读取GetDyeTargetInfo。
// 参数：iIndex：整数；strDyeName：字符串；strTargetName：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 _T、GetSize、GetAt、GetDyeName、GetTargetName。
int CTubeInfo::GetDyeTargetInfo(int iIndex,CString& strDyeName,CString strTargetName)
{
	strDyeName = _T("");
	strTargetName = _T("");

	if(iIndex < 0 || iIndex >= m_arrayDyeTarget.GetSize())
	{
		return -1;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iIndex);
	if(NULL == pDyeTargetInfo)
	{
		return -2;
	}

	strDyeName = pDyeTargetInfo->GetDyeName();
	strTargetName = pDyeTargetInfo->GetTargetName();

	return 0;
}

// 函数 CTubeInfo::GetTubeLabel
// 作用：读取GetTubeLabel。
// 参数：iColNum：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 _T、Format。
CString CTubeInfo::GetTubeLabel(int iColNum) 
{ 
	if(iColNum < 1)
	{
		m_strTubeLabel = _T("");
		return _T("");
	}

	char cLabel = 'A';

	int Quotient = (m_iTubeID - 1) / iColNum;
	int Remainder = m_iTubeID % iColNum;

	if (0 == Remainder)
	{
		Remainder = iColNum;
	}

	m_strTubeLabel.Format(_T("%c%d"),cLabel + Quotient,Remainder);

	return m_strTubeLabel; 
}

// 函数 CTubeInfo::InitDyeChannel
// 作用：初始化InitDyeChannel。
// 参数：iChannelCount：整数。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAllDyeTargetInfo、CDyeTargetInfo、SetChannel、Add、GetCount。
void CTubeInfo::InitDyeChannel(int iChannelCount)
{
	DeleteAllDyeTargetInfo();

	for(int i=0; i<iChannelCount; ++i)
	{
		CDyeTargetInfo* pDyeTargetInfo = new CDyeTargetInfo();
		if (pDyeTargetInfo != NULL)
		{
			pDyeTargetInfo->SetChannel(i+1); 
			m_arrayDyeTarget.Add(pDyeTargetInfo);
		}
	}

	ASSERT(m_arrayDyeTarget.GetCount() == iChannelCount);
}

// 复制项目中定义的染料信息
// 函数 CTubeInfo::PasteTargetInfoFromItem
// 作用：执行PasteTargetInfoFromItem。
// 参数：pItem：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetChannelTargetCount、GetTargetCount、GetTargetInfo、GetChannelTargetBy、GetChannel、SetDyeName。
void CTubeInfo::PasteTargetInfoFromItem(CReagentItem* pItem)
{
	int iChannelCount = pItem->GetChannelTargetCount();
	int iTargetCount = GetTargetCount();
	for (int i=0; i<iTargetCount; i++)
	{
		CDyeTargetInfo* pTarget = GetTargetInfo(i);
		if (pTarget == NULL)
			continue;

		BOOL bFind = FALSE;
		for (int j=0; j<iChannelCount; j++)
		{
			CItemChannelInfo* pChannel = (CItemChannelInfo*)pItem->GetChannelTargetBy(j);
			if (pTarget->GetChannel() == pChannel->GetChannel()) // 找到
			{
				pTarget->SetDyeName(pChannel->GetDyeName());
				pTarget->SetBeSelected(pChannel->GetUse());
				if (pChannel->GetUse())
				{
					pTarget->SetTargetName(pChannel->GetTargetName(m_strTubeFlag));
					pTarget->SetTargetColor(pChannel->GetTargetColor(m_strTubeFlag));
				}

				bFind = TRUE;
				break;
			}
		}

		if (!bFind)
		{
			pTarget->SetBeSelected(FALSE);
		}
	}
}



// 函数 CTubeInfo::Reset
// 作用：更新或清除Reset。
// 参数：bTemplateMode：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 Empty、ResetDyeInfo。
void CTubeInfo::Reset(BOOL bTemplateMode)
{
	m_strSampleID.Empty();
	m_strSampleName.Empty();
	m_nSampleType = SAMPLE_TYPE_NONE;
	m_bRepeatTube = FALSE;
	m_iRepeatNo = -1;
	m_strComments.Empty();

	m_iCalibrateChannel = -1;
	if(!bTemplateMode)
	{
		ResetDyeInfo();
	}

	CSampleInfo::Reset();
}

// 函数 CTubeInfo::ResetInfo1
// 作用：更新或清除ResetInfo1。
// 参数：bTemplateMode：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 Empty、ResetDyeTargetInfoExceptDyeNameAndColor、Reset。
void CTubeInfo::ResetInfo1(BOOL bTemplateMode)
{
	m_strSampleID.Empty();
	m_nSampleType = SAMPLE_TYPE_NONE;
	m_bRepeatTube = FALSE;
	m_iRepeatNo = -1;

	if(!bTemplateMode)
	{
		ResetDyeTargetInfoExceptDyeNameAndColor();
	}

	CSampleInfo::Reset();
}

// 函数 CTubeInfo::ResetInfo2
// 作用：更新或清除ResetInfo2。
// 参数：bTemplateMode：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 Empty、Reset。
void CTubeInfo::ResetInfo2(BOOL bTemplateMode)
{
	m_strSampleID.Empty();
	m_strSampleName.Empty();
	m_nSampleType = SAMPLE_TYPE_NONE;
	m_strComments.Empty();

	CSampleInfo::Reset();
}

// 函数 CTubeInfo::GetChannelNum
// 作用：读取GetChannelNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCount。
int CTubeInfo::GetChannelNum()
{
	return m_arrayDyeTarget.GetCount();
}

// 阳性对照孔使用。选中的通道里，只要有一个不是阳性，整孔就不算通过。
// 未处理的通道跳过。浊度校正通道不参与。一个可比较的通道都没有，返回失败。
// 函数 CTubeInfo::IsAllSelectedChannelPositive
// 作用：判断IsAllSelectedChannelPositive是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetChannelNum、GetTargetInfo、GetBeSelected、GetBeUnhandledAnaResult、GetBePositiveAnaResult。
BOOL CTubeInfo::IsAllSelectedChannelPositive()
{
	int iChanNum = GetChannelNum();
	if(iChanNum < 1)
	{
		return FALSE;
	}

	BOOL bCompared = FALSE;
	CDyeTargetInfo* pDyeTargetInfo = NULL;

#ifdef PS96INSTRUMENT
	iChanNum -= 1;
#endif

	for(int i = 0;i < iChanNum;++i)
	{
		pDyeTargetInfo = GetTargetInfo(i);
		if(NULL == pDyeTargetInfo || !pDyeTargetInfo->GetBeSelected())
		{
			continue;
		}

		if (pDyeTargetInfo->GetBeUnhandledAnaResult())
			continue;

		bCompared = TRUE;
		if(!pDyeTargetInfo->GetBePositiveAnaResult())
		{
			return FALSE;
		}
	}

	return bCompared;
}

// 阴性对照孔使用。普通通道必须是阴性。
// 目标名是 SPC 的内标反过来：它是阴性时，整孔不算通过。
// 未处理通道跳过，浊度校正通道不参与。
// 函数 CTubeInfo::IsAllSelectedChannelNegative
// 作用：判断IsAllSelectedChannelNegative是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetChannelNum、GetTargetInfo、GetBeSelected、GetBeUnhandledAnaResult、IsInternalControlSPC、GetTargetName。
BOOL CTubeInfo::IsAllSelectedChannelNegative()
{
	int iChanNum = GetChannelNum();
	if(iChanNum < 1)
	{
		return FALSE;
	}

	BOOL bCompared = FALSE;
	CDyeTargetInfo* pDyeTargetInfo = NULL;

#ifdef PS96INSTRUMENT
	iChanNum -= 1;
#endif

	for(int i = 0;i < iChanNum;++i)
	{
		pDyeTargetInfo = GetTargetInfo(i);
		if(NULL == pDyeTargetInfo || !pDyeTargetInfo->GetBeSelected())
		{
			continue;
		}
		if (pDyeTargetInfo->GetBeUnhandledAnaResult())
			continue;

		bCompared = TRUE;

		if (IsInternalControlSPC(pDyeTargetInfo->GetTargetName()))
		{
			if (pDyeTargetInfo->GetBeNegativeAnaResult())
				return FALSE;
		}
		else if(!pDyeTargetInfo->GetBeNegativeAnaResult())
		{
			return FALSE;
		}
	}

	return bCompared;
}

// 按内标汇总一孔的结论，不重新计算 Ct。
// 没有内标，返回普通结果，由调用方继续处理。
// 内标阳性且其他通道没有阳性：阴性。
// 内标阳性且其他通道有阳性：普通结果。
// 内标不是阳性且其他通道有阳性：普通结果。
// 内标不是阳性且其他通道也没有阳性：无效。
ESAMPLETOTALRESULT CTubeInfo::GetSampleTotalResultIfIncludeIC()
{
	BOOL bExistIC = FALSE,bICPositve = FALSE,bOtherChanExistPositive = FALSE;
	int iChanNum = GetChannelNum(),iIndex = 0;
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < iChanNum;++i)
	{
		pDyeTargetInfo = GetTargetInfo(i);
		if(NULL == pDyeTargetInfo || !pDyeTargetInfo->GetBeSelected())
		{
			continue;
		}

		if(IsInternalControl(pDyeTargetInfo->GetTargetName()))
		{
			bExistIC = TRUE;
			iIndex = i;
			bICPositve = pDyeTargetInfo->GetBePositiveAnaResult();
		}
		else
		{
			if(pDyeTargetInfo->GetBePositiveAnaResult())
			{
				bOtherChanExistPositive = TRUE;
			}
		}
	}

	if(!bExistIC)
	{
		return ESTR_NORMAL;
	}

	if(bICPositve)
	{
		if(bOtherChanExistPositive)
		{
			return ESTR_NORMAL;
		}
		else
		{
			return ESTR_NEGATIVE;
		}
	}
	else
	{
		if(bOtherChanExistPositive)
		{
			return ESTR_NORMAL;
		}
		else
		{
			return ESTR_INVALID;
		}
	}
}

// 函数 CTubeInfo::IsExistInternalControl
// 作用：判断IsExistInternalControl是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetChannelNum、GetTargetInfo、GetBeSelected、IsInternalControl、GetTargetName。
BOOL CTubeInfo::IsExistInternalControl()
{
	int iChanNum = GetChannelNum();
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < iChanNum;++i)
	{
		pDyeTargetInfo = GetTargetInfo(i);
		if(NULL == pDyeTargetInfo || !pDyeTargetInfo->GetBeSelected())
		{
			continue;
		}

		if(IsInternalControl(pDyeTargetInfo->GetTargetName()))
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 函数 CTubeInfo::IsExistInternalControl
// 作用：判断IsExistInternalControl是否成立。
// 参数：bICPositive：是或否。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetChannelNum、GetTargetInfo、GetBeSelected、IsInternalControl、GetTargetName、GetBePositiveAnaResult。
BOOL CTubeInfo::IsExistInternalControl(BOOL& bICPositive)
{
	int iChanNum = GetChannelNum();
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < iChanNum;++i)
	{
		pDyeTargetInfo = GetTargetInfo(i);
		if(NULL == pDyeTargetInfo || !pDyeTargetInfo->GetBeSelected())
		{
			continue;
		}

		if(IsInternalControl(pDyeTargetInfo->GetTargetName()))
		{
			bICPositive = pDyeTargetInfo->GetBePositiveAnaResult();
			return TRUE;
		}
	}

	return FALSE;
}

// 函数 CTubeInfo::IsExistPositiveExceptICGene
// 作用：判断IsExistPositiveExceptICGene是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetChannelNum、GetTargetInfo、GetBeSelected、IsInternalControl、GetTargetName、GetBePositiveAnaResult。
BOOL CTubeInfo::IsExistPositiveExceptICGene()
{
	int iChanNum = GetChannelNum();
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < iChanNum;++i)
	{
		pDyeTargetInfo = GetTargetInfo(i);
		if(NULL == pDyeTargetInfo || !pDyeTargetInfo->GetBeSelected())
		{
			continue;
		}

		if(!IsInternalControl(pDyeTargetInfo->GetTargetName()) && pDyeTargetInfo->GetBePositiveAnaResult())
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 内标名字：IC、SPC，以及名字中包含 IC- 或 -IC。大小写都认。
// 内标阳性不写入报告里的阳性基因名单。
// 函数 CTubeInfo::IsInternalControl
// 作用：判断IsInternalControl是否成立。
// 参数：str：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 TrimLeft、TrimRight、_T、IsInternalControlSPC、Find。
BOOL CTubeInfo::IsInternalControl(CString& str)
{
	str.TrimLeft();
	str.TrimRight();
	if(_T("IC") == str || _T("ic") == str || _T("Ic") == str || _T("iC") == str || IsInternalControlSPC(str))
	{
		return TRUE;
	}
	else if (str.Find(_T("-IC")) != -1 || str.Find(_T("IC-")) != -1 || str.Find(_T("-ic")) != -1 || str.Find(_T("-Ic")) != -1
		|| str.Find(_T("-iC")) != -1 || str.Find(_T("ic-")) != -1 || str.Find(_T("Ic-")) != -1 || str.Find(_T("iC-")) != -1)
	{
		return TRUE;
	}

	return FALSE;
}

// 函数 CTubeInfo::IsInternalControlSPC
// 作用：判断IsInternalControlSPC是否成立。
// 参数：strSPC：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 _T。
BOOL CTubeInfo::IsInternalControlSPC(CString strSPC)
{
	if(_T("SPC") == strSPC || _T("spc") == strSPC || _T("Spc") == strSPC)
	{
		return TRUE;
	}
	return FALSE;
}


// 将选择通道中没有设置完善的染料和目标信息补充完整
// 函数 CTubeInfo::PerfectTargetDyeInfo
// 作用：执行PerfectTargetDyeInfo。
// 参数：pArrayChannel：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、GetDyeName、IsEmpty、GetChannel、SetDyeName。
void CTubeInfo::PerfectTargetDyeInfo(CPtrArray* pArrayChannel)
{
	int iTargetCount = m_arrayDyeTarget.GetCount();
	for (int i=0; i<iTargetCount; i++)
	{
		CDyeTargetInfo* pTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if (pTargetInfo == NULL)
			continue;

		if (pTargetInfo->GetDyeName().IsEmpty())
		{
			int iDyeCount = pArrayChannel->GetCount();
			tagDyeChannelInfo* pFindChannel = NULL;
			for (int j=0; j<iDyeCount; j++)
			{
				tagDyeChannelInfo* pChannel = (tagDyeChannelInfo*)pArrayChannel->GetAt(j);
				if (pChannel == NULL)
					continue;

				if (pChannel->iChannel == pTargetInfo->GetChannel())
				{
					if (pFindChannel == NULL)
					{
						pFindChannel = pChannel;			
					}
					if (pChannel->bDefault)
					{
						pFindChannel = pChannel;
						break;
					}
				}
			}

			if (pFindChannel == NULL)
				continue;

			pTargetInfo->SetDyeName(pFindChannel->strDye);
			if (pTargetInfo->GetTargetName().IsEmpty())
			{
				pTargetInfo->SetTargetName(pFindChannel->strTarget);
			}
		}
		else if (pTargetInfo->GetTargetName().IsEmpty())
		{
			pTargetInfo->SetTargetName(pTargetInfo->GetDyeName());
		}
	}
}

// 函数 CTubeInfo::GetBeNeedDensity
// 作用：读取GetBeNeedDensity。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeInfo::GetBeNeedDensity()
{
	return SAMPLE_TYPE_STANDARD == m_nSampleType || SAMPLE_TYPE_CALIBRATOR == m_nSampleType;
}

// 函数 CTubeInfo::GetBeNoneSampleType
// 作用：读取GetBeNoneSampleType。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeInfo::GetBeNoneSampleType()
{
	return SAMPLE_TYPE_NONE == m_nSampleType;
}

// 函数 CTubeInfo::GetBeUnknown
// 作用：读取GetBeUnknown。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeInfo::GetBeUnknown()
{
	return SAMPLE_TYPE_UNKNOWN == m_nSampleType;
}

// 函数 CTubeInfo::GetBePositive
// 作用：读取GetBePositive。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeInfo::GetBePositive()
{
	return SAMPLE_TYPE_POSITIVE == m_nSampleType;
}

// 函数 CTubeInfo::GetBeNegtive
// 作用：读取GetBeNegtive。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeInfo::GetBeNegtive()
{
	return SAMPLE_TYPE_NEGATIVE == m_nSampleType;
}

// 函数 CTubeInfo::GetSampleDyeTargetColor
// 作用：读取GetSampleDyeTargetColor。
// 参数：iChanIndex：整数。
// 返回：返回 COLORREF。
// 过程：函数里会调用 GetSize、RGB、GetAt、GetTargetColor。
COLORREF CTubeInfo::GetSampleDyeTargetColor(int iChanIndex)
{
	if(iChanIndex < 0 || iChanIndex >= m_arrayDyeTarget.GetSize())
	{
		return RGB(0,0,0);
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return RGB(0,0,0);
	}
	
	return pDyeTargetInfo->GetTargetColor();
}

// 函数 CTubeInfo::SetSampleDyeTargetColor
// 作用：设置SetSampleDyeTargetColor。
// 参数：iChanIndex：整数；clrDyeTarget：颜色。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt、SetTargetColor。
void CTubeInfo::SetSampleDyeTargetColor(int iChanIndex,COLORREF clrDyeTarget)
{
	if(iChanIndex < 0 || iChanIndex >= m_arrayDyeTarget.GetSize())
	{
		return;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return;
	}

	pDyeTargetInfo->SetTargetColor(clrDyeTarget);
	return;
}

// 函数 CTubeInfo::GetSampleChannelSelectState
// 作用：读取GetSampleChannelSelectState。
// 参数：iChanIndex：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSize、GetAt、GetBeSelected。
BOOL CTubeInfo::GetSampleChannelSelectState(int iChanIndex)
{
	if(iChanIndex < 0 || iChanIndex >= m_arrayDyeTarget.GetSize())
	{
		return FALSE;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return FALSE;
	}

	return pDyeTargetInfo->GetBeSelected();
}

// 函数 CTubeInfo::SetSampleChannelSelectState
// 作用：设置SetSampleChannelSelectState。
// 参数：iChanIndex：整数；bSelectState：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt、SetBeSelected。
void CTubeInfo::SetSampleChannelSelectState(int iChanIndex,BOOL bSelectState)
{
	if(iChanIndex < 0 || iChanIndex >= m_arrayDyeTarget.GetSize())
	{
		return;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return;
	}

	pDyeTargetInfo->SetBeSelected(bSelectState);
	return;
}

// 函数 CTubeInfo::GetFirstNonZeroDensity
// 作用：读取GetFirstNonZeroDensity。
// 参数：无。
// 返回：返回一个小数。
// 过程：函数里会调用 GetCount、GetAt、GetQuantity。
double CTubeInfo::GetFirstNonZeroDensity()
{
	double dTemp = 0.0;
	int iDyeNum = m_arrayDyeTarget.GetCount();
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < iDyeNum;++i)
	{
		pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if(NULL == pDyeTargetInfo)
		{
			continue;
		}

		dTemp = pDyeTargetInfo->GetQuantity();
		if(0 != dTemp)
		{
			break;
		}
	}

	return dTemp;
}

// 函数 CTubeInfo::GetFirstNonZeroDensityString
// 作用：读取GetFirstNonZeroDensityString。
// 参数：iDPd：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetCount、GetAt、GetQuantity、strTemp、_T、strFormat。
CString CTubeInfo::GetFirstNonZeroDensityString(int iDPd /*= 4*/)
{
	double dTemp = 0.0;
	int iDyeNum = m_arrayDyeTarget.GetCount();
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	for(int i = 0;i < iDyeNum;++i)
	{
		pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if(NULL == pDyeTargetInfo)
		{
			continue;
		}

		dTemp = pDyeTargetInfo->GetQuantity();
		if(0 != dTemp)
		{
			break;
		}
	}

	CString strTemp(_T(""));
	if(dTemp > 0)
	{
		 CString strFormat(_T(""));
		 strFormat.Format(_T("%%.%dlf"),pDyeTargetInfo->GetQuanIDPD());
		strTemp.Format(strFormat,dTemp);
	}

	return strTemp;
}

// 函数 CTubeInfo::GetAllChannelDensityString
// 作用：读取GetAllChannelDensityString。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetCount、strData、_T、GetAt、GetQuantity、strFormat。
CString CTubeInfo::GetAllChannelDensityString()
{
	double dTemp = 0.0;
	int iDyeNum = m_arrayDyeTarget.GetCount();
	CDyeTargetInfo* pDyeTargetInfo = NULL;
	CString strData(_T(""));

	for(int i = 0;i < iDyeNum;++i)
	{
		pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(i);
		if(NULL == pDyeTargetInfo)
		{
			strData += _T("\n");
			continue;
		}

		dTemp = pDyeTargetInfo->GetQuantity();
		if(dTemp > 0)
		{
			CString strFormat(_T(""));
			strFormat.Format(_T("%%.%dlf"),pDyeTargetInfo->GetQuanIDPD());
			strData.AppendFormat(strFormat,dTemp);
		}
		strData += _T("\n");
	}

	return strData;
}

// 函数 CTubeInfo::GetDensity
// 作用：读取GetDensity。
// 参数：iChanIndex：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 GetCount、GetAt、GetQuantity。
double CTubeInfo::GetDensity(int iChanIndex)
{
	int iDyeNum = m_arrayDyeTarget.GetCount();
	if(iChanIndex < 0 || iChanIndex >= iDyeNum)
	{
		return 0;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return 0;
	}

	return pDyeTargetInfo->GetQuantity();
}

// 函数 CTubeInfo::GetDensityString
// 作用：读取GetDensityString。
// 参数：iChanIndex：整数；iDPd：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetCount、GetAt、GetQuantity、strTemp、_T、strFormat。
CString CTubeInfo::GetDensityString(int iChanIndex,int iDPd /*= 4*/)
{
	int iDyeNum = m_arrayDyeTarget.GetCount();
	if(iChanIndex < 0 || iChanIndex >= iDyeNum)
	{
		return 0;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return 0;
	}

	double dTemp = pDyeTargetInfo->GetQuantity();
	CString strTemp(_T(""));
	if(dTemp > 0)
	{
		CString strFormat(_T(""));
		strFormat.Format(_T("%%.%dlf"),pDyeTargetInfo->GetQuanIDPD());
		strTemp.Format(strFormat,dTemp);
	}

	return strTemp;
}

// 函数 CTubeInfo::GetCalculatedDensity
// 作用：读取GetCalculatedDensity。
// 参数：iChanIndex：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 GetCount、GetAt、GetCalcValue。
double CTubeInfo::GetCalculatedDensity(int iChanIndex)
{
	int iDyeNum = m_arrayDyeTarget.GetCount();
	if(iChanIndex < 0 || iChanIndex >= iDyeNum)
	{
		return -1;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return -1;
	}

	return pDyeTargetInfo->GetCalcValue(CDyeTargetInfo::VALUE_CALC_QUANTITY);
}

// 函数 CTubeInfo::GetCalculatedDensityString
// 作用：读取GetCalculatedDensityString。
// 参数：iChanIndex：整数；iDPd：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 strTemp、_T、GetCount、GetAt、GetCalcValue、strFormat。
CString CTubeInfo::GetCalculatedDensityString(int iChanIndex,int iDPd /*= 4*/)
{
	CString strTemp(_T(""));
	int iDyeNum = m_arrayDyeTarget.GetCount();
	if(iChanIndex < 0 || iChanIndex >= iDyeNum)
	{
		return strTemp;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return strTemp;
	}

	double dTemp = pDyeTargetInfo->GetCalcValue(CDyeTargetInfo::VALUE_CALC_QUANTITY);
	if(dTemp > 0) //-1是否用于判断，待定，20220614，孙文郎
	{
		CString strFormat(_T(""));
		strFormat.Format(_T("%%.%dlf"),iDPd);
		strTemp.Format(strFormat,dTemp);
		int iIndex = strTemp.Find(_T('.')),iLen = strTemp.GetLength(),iZeroNum = 0;
		for(int i = iLen - 1;i > iIndex;--i)
		{
			if(_T('0') != strTemp[i])
			{
				break;
			}
			++iZeroNum;
		}
		strTemp = strTemp.Left(iLen - iZeroNum);
	}

	return strTemp;
}

// 函数 CTubeInfo::ResetChannelCalculatedDensity
// 作用：更新或清除ResetChannelCalculatedDensity。
// 参数：iChanIndex：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetCount、GetAt、SetCalcValue。
BOOL CTubeInfo::ResetChannelCalculatedDensity(int iChanIndex)
{
	int iDyeNum = m_arrayDyeTarget.GetCount();
	if(iChanIndex < 0 || iChanIndex >= iDyeNum)
	{
		return FALSE;
	}

	CDyeTargetInfo* pDyeTargetInfo = (CDyeTargetInfo*)m_arrayDyeTarget.GetAt(iChanIndex);
	if(NULL == pDyeTargetInfo)
	{
		return FALSE;
	}

	pDyeTargetInfo->SetCalcValue(CDyeTargetInfo::VALUE_CALC_QUANTITY,-1);
	return TRUE;
}



