// 【交接】 PCRCtrlLib\PlateTubeInfo.cpp
// 作用：PlateTubeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CPlateTubeInfo、CTubeInfo、Add、DeleteAll、SAFE_DELETE、DeleteAllTubes、GetCount、GetAt。
#include "StdAfx.h"
#include "PlateTubeInfo.h"
#include "Define.h"

// 函数 CPlateTubeInfo::CPlateTubeInfo
// 作用：执行CPlateTubeInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CTubeInfo、Add。
CPlateTubeInfo::CPlateTubeInfo(void)
{
	m_pPlateInfo = new tagPlateModeInfo;

#ifdef PS384INSTRUMENT
	m_pPlateInfo->iHoriCount = 24;
	m_pPlateInfo->iVertCount = 16;
#endif

	if(NULL != m_pPlateInfo)
	{
		int iTubeCount = m_pPlateInfo->iHoriCount * m_pPlateInfo->iVertCount;
		for(int i = 0;i < iTubeCount;++i)
		{
			CTubeInfo* pTubeInfo = new CTubeInfo(i + 1);
			m_arrayTube.Add(pTubeInfo);
		}
	}
}


// 函数 CPlateTubeInfo::~CPlateTubeInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CPlateTubeInfo::~CPlateTubeInfo(void)
{
	DeleteAll();
}

// 函数 CPlateTubeInfo::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：bOnlyTube：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 SAFE_DELETE、DeleteAllTubes。
void CPlateTubeInfo::DeleteAll(BOOL bOnlyTube)
{
	if (!bOnlyTube)
	{
		SAFE_DELETE(m_pPlateInfo);
	}

	DeleteAllTubes();
}

// 函数 CPlateTubeInfo::DeleteAllTubes
// 作用：更新或清除DeleteAllTubes。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SAFE_DELETE、RemoveAll。
void CPlateTubeInfo::DeleteAllTubes()
{
	int iTubeCount = m_arrayTube.GetCount();
	for (int i=0; i<iTubeCount; i++)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		SAFE_DELETE(pTubeInfo);
	}
	m_arrayTube.RemoveAll();
}

// 打开指定文件并读取孔板数据
// 函数 CPlateTubeInfo::OpenFile
// 作用：读入OpenFile。
// 参数：strFilePath：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 Open、Read、ReadFile、Close。
BOOL CPlateTubeInfo::OpenFile(CString strFilePath)
{
	CFile file;       
	if (!file.Open(strFilePath,CFile::modeRead | CFile::shareDenyNone))
	{
		return FALSE;
	}

	// 读取文件标识和版本
	WORD wFileMark = 0;
	file.Read(&wFileMark, sizeof(WORD));
	if (wFileMark != wFileMarkPCRPlate)
	{
		return FALSE;
	}

	WORD wVersion = 0;
	file.Read(&wVersion, sizeof(WORD));

	ReadFile(&file, wVersion);

	file.Close();

	return TRUE;
}

// 写入数据到文件中
// 函数 CPlateTubeInfo::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 Write、GetCount、GetAt。
BOOL CPlateTubeInfo::WriteFile(CFile* pFile,WORD wVersion)
{
	int iTempInt = m_pPlateInfo->nPlateType;
	pFile->Write((const char*)&iTempInt, sizeof(int));
	iTempInt = m_pPlateInfo->iPlateCount;
	pFile->Write((const char*)&iTempInt, sizeof(int));
	iTempInt = m_pPlateInfo->nSortMode;
	pFile->Write((const char*)&iTempInt, sizeof(int));
	iTempInt = m_pPlateInfo->iHoriCount;
	pFile->Write((const char*)&iTempInt, sizeof(int));
	iTempInt = m_pPlateInfo->iVertCount;
	pFile->Write((const char*)&iTempInt, sizeof(int));

	int nTubeCount = m_arrayTube.GetCount();
	pFile->Write((const char*)&nTubeCount,sizeof(int));
	for (int i=0; i<nTubeCount; i++)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		pTubeInfo->WriteFile(pFile,wVersion);
	}

	return TRUE;
}

// 函数 CPlateTubeInfo::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、Read、CTubeInfo、Add。
BOOL CPlateTubeInfo::ReadFile(CFile* pFile, WORD wVersion)
{
	DeleteAll(TRUE);

	int iTempInt = 0;
	pFile->Read(&iTempInt, sizeof(int));
	m_pPlateInfo->nPlateType = (ePlateModeType)iTempInt;
	pFile->Read(&iTempInt, sizeof(int));
	m_pPlateInfo->iPlateCount = iTempInt;
	pFile->Read(&iTempInt, sizeof(int));
	m_pPlateInfo->nSortMode = (ePlateSortMode)iTempInt;
	pFile->Read(&iTempInt, sizeof(int));
	m_pPlateInfo->iHoriCount = iTempInt;
	pFile->Read(&iTempInt, sizeof(int));
	m_pPlateInfo->iVertCount = iTempInt;

	int nTubeCount = 0;
	pFile->Read(&nTubeCount, sizeof(int));
	for (int i=0; i<nTubeCount; i++)
	{
		CTubeInfo* pTubeInfo = new CTubeInfo(i+1);
		pTubeInfo->ReadFile(pFile, wVersion);
		m_arrayTube.Add(pTubeInfo);
	}

	return TRUE;
}

// 函数 CPlateTubeInfo::SetMeltTmCount
// 作用：设置SetMeltTmCount。
// 参数：nCount：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SetTmCount。
void CPlateTubeInfo::SetMeltTmCount(int nCount)
{
	int nTubeCount = m_arrayTube.GetCount();
	for (int i=0; i<nTubeCount; i++)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		pTubeInfo->SetTmCount(nCount);
	}
}

// 设置孔板参数，初始化孔板信息
// 函数 CPlateTubeInfo::SetPlateInfo
// 作用：设置SetPlateInfo。
// 参数：pInputPara：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAllTubes、CalculateTubeCount、CTubeInfo、CreateTubeLabel、SetTubeLabel、Add。
void CPlateTubeInfo::SetPlateInfo(tagPlateModeInfo* pInputPara)
{
	DeleteAllTubes();

	m_pPlateInfo->nPlateType = pInputPara->nPlateType;
	m_pPlateInfo->iPlateCount = pInputPara->iPlateCount;
	m_pPlateInfo->nSortMode = pInputPara->nSortMode;
	m_pPlateInfo->iHoriCount = pInputPara->iHoriCount;
	m_pPlateInfo->iVertCount = pInputPara->iVertCount;
	int iTubeCount = CalculateTubeCount(m_pPlateInfo);

	for (int i=0; i<iTubeCount; i++)
	{
		CTubeInfo* pTubeInfo = new CTubeInfo(i+1);
		CString strTubeID = CreateTubeLabel(i+1);
		pTubeInfo->SetTubeLabel(strTubeID);

		m_arrayTube.Add(pTubeInfo);
	}
}

// 根据序号取得指定管信息指针
// 函数 CPlateTubeInfo::GetTubeInfo
// 作用：读取GetTubeInfo。
// 参数：iIndex：整数。
// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt。
CTubeInfo* CPlateTubeInfo::GetTubeInfo(int iIndex)
{
	CTubeInfo* pTubeInfo = NULL;
	if (iIndex >= 0 && iIndex < m_arrayTube.GetCount())
	{
		pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(iIndex);
	}
	return pTubeInfo;
}

// 函数 CPlateTubeInfo::GetAllTubeInfoPtr
// 作用：读取GetAllTubeInfoPtr。
// 参数：vecPTubeInfo。
// 返回：没有返回值。
// 过程：函数里会调用 clear、GetSize、push_back、GetAt。
void CPlateTubeInfo::GetAllTubeInfoPtr(vector<CTubeInfo*>& vecPTubeInfo)
{
	vecPTubeInfo.clear();
	int iTubeNum = m_arrayTube.GetSize();
	for(int i = 0;i < iTubeNum;++i)
	{
		vecPTubeInfo.push_back((CTubeInfo*)m_arrayTube.GetAt(i));
	}
	return;
}

// 函数 CPlateTubeInfo::GetTubeInfoArrayPtr
// 作用：读取GetTubeInfoArrayPtr。
// 参数：无。
// 返回：返回指针 CPtrArray*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPtrArray* CPlateTubeInfo::GetTubeInfoArrayPtr()
{
	return &m_arrayTube;
}

// 函数 CPlateTubeInfo::GetTubeInfoByID
// 作用：读取GetTubeInfoByID。
// 参数：iTubeID：整数。
// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt、GetTubeID。
CTubeInfo* CPlateTubeInfo::GetTubeInfoByID(int iTubeID)
{
	CTubeInfo* pTube = NULL;

	for (int i=0; i<m_arrayTube.GetCount(); i++)
	{
		CTubeInfo* pTemp = (CTubeInfo*)m_arrayTube.GetAt(i);
		if (pTemp->GetTubeID() == iTubeID)
		{
			pTube = pTemp;
			break;
		}
	}

	return pTube;
}

// 根据管标签得到管信息指针
// 函数 CPlateTubeInfo::GetTubeInfoByLabel
// 作用：读取GetTubeInfoByLabel。
// 参数：strLabel：字符串。
// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt、GetTubeLabel。
CTubeInfo* CPlateTubeInfo::GetTubeInfoByLabel(CString strLabel)
{
	int iColNum = 12;
	if(NULL != m_pPlateInfo)
	{
		iColNum = m_pPlateInfo->iHoriCount;
	}
	CTubeInfo* pTube = NULL;
	for (int i=0; i<m_arrayTube.GetCount(); i++)
	{
		CTubeInfo* pTemp = (CTubeInfo*)m_arrayTube.GetAt(i);
		
		if (pTemp->GetTubeLabel(iColNum) == strLabel)
		{
			pTube = pTemp;
			break;
		}
	}

	return pTube;
}

// 函数 CPlateTubeInfo::CalculateTubeCount
// 作用：计算CalculateTubeCount。
// 参数：pInputInfo：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CPlateTubeInfo::CalculateTubeCount(tagPlateModeInfo* pInputInfo)
{
	int nCount = pInputInfo->iPlateCount * pInputInfo->iHoriCount * pInputInfo->iVertCount;
	return nCount;
}

// 函数 CPlateTubeInfo::CreateTubeLabel
// 作用：创建或加入CreateTubeLabel。
// 参数：iIndex：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 _T、Format。
CString CPlateTubeInfo::CreateTubeLabel(int iIndex)
{
	CString strLable = _T("");
	char cLabel = 'A';

	int Quotient = (iIndex - 1) / 12;
	int Remainder = iIndex % 12;

	if (0 == Remainder)
	{
		Remainder = 12;
	}

	strLable.Format(_T("%c%d"),cLabel+Quotient, Remainder);

	return strLable;
}

// 根据项目定义初始化通道使用情况
// 函数 CPlateTubeInfo::InitDyeTargetInfo
// 作用：初始化InitDyeTargetInfo。
// 参数：iTubeID：整数；pReagentItem：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetTubeInfoByID、PasteTargetInfoFromItem。
void CPlateTubeInfo::InitDyeTargetInfo(int iTubeID, CReagentItem* pReagentItem)
{
	CTubeInfo* pTubeInfo = GetTubeInfoByID(iTubeID);
	if (pTubeInfo == NULL)
	{
		ASSERT(FALSE);
		return;
	}
	pTubeInfo->PasteTargetInfoFromItem(pReagentItem);
}

// 函数 CPlateTubeInfo::SetTubeInfo
// 作用：设置SetTubeInfo。
// 参数：vecTubeInfo。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、size、DeleteAll、Add、GetAt。
void CPlateTubeInfo::SetTubeInfo(vector<CTubeInfo>& vecTubeInfo)
{
	if(m_arrayTube.GetSize() != vecTubeInfo.size())
	{
		DeleteAll(TRUE);

		for(int i = 0;i < vecTubeInfo.size();++i)
		{
			CTubeInfo* pTubeInfo = new CTubeInfo;
			m_arrayTube.Add(pTubeInfo);
		}
	}

	for(int i = 0;i < vecTubeInfo.size();++i)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		*pTubeInfo = vecTubeInfo[i];
	}

	return;
}

// 函数 CPlateTubeInfo::SetTubeInfo
// 作用：设置SetTubeInfo。
// 参数：vecPTubeInfo。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、size、DeleteAll、Add、GetAt。
void CPlateTubeInfo::SetTubeInfo(vector<CTubeInfo*>& vecPTubeInfo)
{
	if(m_arrayTube.GetSize() != vecPTubeInfo.size())
	{
		DeleteAll(TRUE);

		for(int i = 0;i < vecPTubeInfo.size();++i)
		{
			CTubeInfo* pTubeInfo = new CTubeInfo;
			m_arrayTube.Add(pTubeInfo);
		}
	}

	for(int i = 0;i < vecPTubeInfo.size();++i)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		*pTubeInfo = *vecPTubeInfo[i];
	}

	return;
}

// 函数 CPlateTubeInfo::SetTubeInfo
// 作用：设置SetTubeInfo。
// 参数：pTotalTubeInfo：指针，指向调用方传入的对象；iTubeNum：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、DeleteAll、Add、GetAt。
int CPlateTubeInfo::SetTubeInfo(CTubeInfo* pTotalTubeInfo,int iTubeNum)
{
	if(NULL == pTotalTubeInfo)
	{
		return -1;
	}
	if(iTubeNum < 1)
	{
		return -2;
	}

	if(m_arrayTube.GetSize() != iTubeNum)
	{
		DeleteAll(TRUE);

		for(int i = 0;i < iTubeNum;++i)
		{
			CTubeInfo* pTubeInfo = new CTubeInfo;
			m_arrayTube.Add(pTubeInfo);
		}
	}

	for(int i = 0;i < iTubeNum;++i)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		*pTubeInfo = pTotalTubeInfo[i];
	}

	return 0;
}

// 函数 CPlateTubeInfo::GetTubeInfo
// 作用：读取GetTubeInfo。
// 参数：vecTubeInfo。
// 返回：没有返回值。
// 过程：函数里会调用 clear、GetSize、GetAt、push_back。
void CPlateTubeInfo::GetTubeInfo(vector<CTubeInfo>& vecTubeInfo)
{
	vecTubeInfo.clear();

	for(int i = 0;i < m_arrayTube.GetSize();++i)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		vecTubeInfo.push_back(*pTubeInfo);
	}

	return;
}

// 函数 CPlateTubeInfo::GetUsedDyeChannel
// 作用：读取GetUsedDyeChannel。
// 参数：pArrayDye：指针，指向调用方传入的对象；pArrayChannel：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt、GetTargetCount、GetTargetInfo、GetBeSelected、GetCount。
void CPlateTubeInfo::GetUsedDyeChannel(CStringArray* pArrayDye, CIntArray* pArrayChannel)
{
	for(int i = 0;i < m_arrayTube.GetSize();++i)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);		
		int iTargetCount = pTubeInfo->GetTargetCount();
		for (int j=0; j<iTargetCount; j++)
		{
			CDyeTargetInfo* pTarget = pTubeInfo->GetTargetInfo(j);
			if (!pTarget->GetBeSelected())
				continue;

			BOOL bFind = FALSE;
			for (int x=0; x<pArrayDye->GetCount(); x++)
			{
				if (pTarget->GetDyeName() == pArrayDye->GetAt(x))
				{
					bFind = TRUE;
					break;
				}
			}

			if (!bFind)
			{
				pArrayDye->Add(pTarget->GetDyeName());
				pArrayChannel->Add(pTarget->GetChannel());
			}
		}
	}
}

// 找出全部设置的染料指标通道
// 函数 CPlateTubeInfo::GetUsedTarget
// 作用：读取GetUsedTarget。
// 参数：pArrrayTarget：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt、GetTargetCount、GetTargetInfo、GetBeSelected、GetCount。
void CPlateTubeInfo::GetUsedTarget(CPtrArray* pArrrayTarget)
{
	for(int i = 0;i < m_arrayTube.GetSize();++i)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);		
		int iTargetCount = pTubeInfo->GetTargetCount();
		for (int j=0; j<iTargetCount; j++)
		{
			CDyeTargetInfo* pTarget = pTubeInfo->GetTargetInfo(j);
			if (!pTarget->GetBeSelected())
				continue;

			BOOL bFind = FALSE;
			for (int x=0; x<pArrrayTarget->GetCount(); x++)
			{
				tagAnaAmplifyPara* pTempPara = (tagAnaAmplifyPara*)pArrrayTarget->GetAt(x);
				if (pTempPara->strTarget == pTarget->GetTargetName() && pTempPara->strDye == pTarget->GetDyeName())
				{
					bFind = TRUE;
					break;
				}
			}

			if (!bFind)
			{
				tagAnaAmplifyPara* pTemp = new tagAnaAmplifyPara;
				pTemp->strDye = pTarget->GetDyeName();
				pTemp->strTarget = pTarget->GetTargetName();
				pTemp->iChannelNo = pTarget->GetChannel();
				pArrrayTarget->Add(pTemp);
			}
		}
	}
}

// 得到行列标签
// 函数 CPlateTubeInfo::GetTubeRowAndColLabel
// 作用：读取GetTubeRowAndColLabel。
// 参数：pArrayRow：指针，指向调用方传入的对象；pArrayCol：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 RemoveAll、CreateLetterLabel、CreateNumberLabel、Format、_T。
void CPlateTubeInfo::GetTubeRowAndColLabel(CStringArray* pArrayRow, CStringArray* pArrayCol)
{
	pArrayRow->RemoveAll();
	pArrayCol->RemoveAll();

	if (m_pPlateInfo->iPlateCount == 1)
	{
		if (m_pPlateInfo->nSortMode == PLATE_SORT_HORZ)
		{
			CreateLetterLabel(pArrayRow, m_pPlateInfo->iVertCount);
			CreateNumberLabel(pArrayCol, m_pPlateInfo->iHoriCount);
		}
		else
		{
			CreateNumberLabel(pArrayRow, m_pPlateInfo->iVertCount);
			CreateLetterLabel(pArrayCol, m_pPlateInfo->iHoriCount);
		}
	}
	else
	{
		CString strPlateIndex;
		for (int i=0; i<m_pPlateInfo->iPlateCount; i++)
		{
			strPlateIndex.Format(_T("%d"), i+1);

			if (m_pPlateInfo->nSortMode == PLATE_SORT_HORZ)
			{
				CreateLetterLabel(pArrayRow, m_pPlateInfo->iVertCount, strPlateIndex);
				CreateNumberLabel(pArrayCol, m_pPlateInfo->iHoriCount, strPlateIndex);
			}
			else
			{
				CreateNumberLabel(pArrayRow, m_pPlateInfo->iVertCount, strPlateIndex);
				CreateLetterLabel(pArrayCol, m_pPlateInfo->iHoriCount, strPlateIndex);
			}
		}
	}
}

// 函数 CPlateTubeInfo::CreateLetterLabel
// 作用：创建或加入CreateLetterLabel。
// 参数：pArray：指针，指向调用方传入的对象；iCount：整数；strIndex：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 Format、_T、Add。
void CPlateTubeInfo::CreateLetterLabel(CStringArray* pArray, int iCount, CString strIndex)
{
	char cLabel = 'A';
	CString strTemp;
	for (int i=0; i<iCount; i++)
	{
		strTemp.Format(_T("%c"), cLabel+i);
		pArray->Add(strTemp);
	}
}

// 函数 CPlateTubeInfo::CreateNumberLabel
// 作用：创建或加入CreateNumberLabel。
// 参数：pArray：指针，指向调用方传入的对象；iCount：整数；strIndex：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 Format、_T、Add。
void CPlateTubeInfo::CreateNumberLabel(CStringArray* pArray, int iCount, CString strIndex)
{
	CString strTemp;
	for (int i=0; i<iCount; i++)
	{
		strTemp.Format(_T("%d"), i+1);
		pArray->Add(strTemp);
	}
}


// 函数 CPlateTubeInfo::HasTargetUsed
// 作用：判断HasTargetUsed是否成立。
// 参数：strTarget：字符串；strDye：字符串。
// 返回：返回是或否。
// 过程：函数里会调用 GetSize、GetAt、GetTargetCount、GetTargetInfo、GetTargetName、GetDyeName。
BOOL CPlateTubeInfo::HasTargetUsed(CString strTarget, CString strDye)
{
	BOOL bFind = FALSE;
	for(int i = 0;i < m_arrayTube.GetSize();++i)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);		
		int iTargetCount = pTubeInfo->GetTargetCount();
		for (int j=0; j<iTargetCount; j++)
		{
			CDyeTargetInfo* pTarget = pTubeInfo->GetTargetInfo(j);
			if (pTarget == NULL)
				continue;
			if (pTarget->GetTargetName() == strTarget && pTarget->GetDyeName() == strDye)
			{
				bFind = TRUE;
				break;
			}
		}

		if (bFind)
			break;
	}

	return bFind;
}

	
// 函数 CPlateTubeInfo::RecalculateSplineThreshold
// 作用：执行RecalculateSplineThreshold。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt、GetTargetCount、GetTargetInfo、SetCalcSplineThresholdUsed。
void CPlateTubeInfo::RecalculateSplineThreshold()
{
	for(int i=0; i<m_arrayTube.GetSize(); i++)
	{
		CTubeInfo* pTubeInfo = (CTubeInfo*)m_arrayTube.GetAt(i);
		if (pTubeInfo == NULL)
			continue;

		int iTargetCount = pTubeInfo->GetTargetCount();
		for (int j=0; j<iTargetCount; j++)
		{
			CDyeTargetInfo* pTarget = pTubeInfo->GetTargetInfo(j);
			if (pTarget == NULL)
				continue;
			pTarget->SetCalcSplineThresholdUsed(FALSE);
		}
	}
}
