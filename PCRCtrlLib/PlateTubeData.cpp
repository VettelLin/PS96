// 【交接】 PCRCtrlLib\PlateTubeData.cpp
// 作用：PlateTubeData。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPlateTubeData、RemoveAll、DeleteAll、GetCount、GetAt、SAFE_DELETE、HasData、AddCycleX。
#include "StdAfx.h"
#include "PlateTubeData.h"
#include "DeclaresPCR.h"
#include "ErrorCodeDefine.h"

// 函数 CPlateTubeData::CPlateTubeData
// 作用：执行CPlateTubeData。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 RemoveAll。
CPlateTubeData::CPlateTubeData(void)
{
	m_nStartPos = SCAN_START_LT;
	m_iColCount = 12;
	m_iTubeCount = 0;
	m_iChannelCount = 0;
	m_arrayTubeData.RemoveAll();
}

// 函数 CPlateTubeData::~CPlateTubeData
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CPlateTubeData::~CPlateTubeData(void)
{
	DeleteAll();
}

// 函数 CPlateTubeData::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SAFE_DELETE、RemoveAll。
void CPlateTubeData::DeleteAll()
{
	m_iTubeCount = 0;
	m_iChannelCount = 0;

	int nTubeCount = m_arrayTubeData.GetCount();
	for (int i=0; i<nTubeCount; i++)
	{
		CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(i);
		SAFE_DELETE(pTubeData);
	}

	m_arrayTubeData.RemoveAll();
}

// 函数 CPlateTubeData::HasData
// 作用：判断HasData是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetCount、GetAt。
BOOL CPlateTubeData::HasData()
{
	if (m_arrayTubeData.GetCount() > 0)
	{
		CTubeData* pData = (CTubeData*)m_arrayTubeData.GetAt(0);
		if (pData->HasData())
			return TRUE;

	}
	return FALSE;
}


// 增加全部管的当前循环数或时间
// 函数 CPlateTubeData::AddCycleX
// 作用：创建或加入AddCycleX。
// 参数：pArrayCycle：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt。
void CPlateTubeData::AddCycleX(CUIntArray* pArrayCycle)
{
	int usefulDataNum = (m_iTubeCount > pArrayCycle->GetSize() ? pArrayCycle->GetSize() : m_iTubeCount);

	for(int i=0; i<usefulDataNum; i++)
	{
		int nTubeNo = i;
		if (m_nStartPos == SCAN_START_RT)
		{
			int nRow = i / m_iColCount;
			int nCol = i % m_iColCount;
			nTubeNo = (nRow+1)*m_iColCount - nCol -1;
		}
		CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(nTubeNo);
		pTubeData->AddCycleX(pArrayCycle->GetAt(i));
	}
}

// 函数 CPlateTubeData::AddOriginalData
// 作用：创建或加入AddOriginalData。
// 参数：aryOriData；iChannelID：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetAt。
int CPlateTubeData::AddOriginalData(CUIntArray& aryOriData, int iChannelID)
{
	int usefulDataNum = (m_iTubeCount > aryOriData.GetSize() ? aryOriData.GetSize() : m_iTubeCount);

	for(int i=0; i<usefulDataNum; i++)
	{
		int nTubeNo = i;
		if (m_nStartPos == SCAN_START_RT)
		{
			int nRow = i / m_iColCount;
			int nCol = i % m_iColCount;
			nTubeNo = (nRow+1)*m_iColCount - nCol -1;
		}

		CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(nTubeNo);
		pTubeData->AddOriginalData(iChannelID-1, aryOriData.GetAt(i));
	}

	return 0;
}

// 函数 CPlateTubeData::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetCount、Write、GetAt。
BOOL CPlateTubeData::WriteFile(CFile* pFile)
{
	BOOL bHaveData = m_arrayTubeData.GetCount() > 0;
	pFile->Write((const char*)&bHaveData, sizeof(BOOL));

	if(bHaveData)
	{
		pFile->Write((const char*)&m_iTubeCount, sizeof(int));
		pFile->Write((const char*)&m_iChannelCount, sizeof(int));
		for(int i=0; i<m_iTubeCount; i++)
		{
			CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(i);
			pTubeData->WriteFile(pFile);
		}
	}

	return TRUE;
}

// 函数 CPlateTubeData::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、Read、AllocateMemory、GetAt。
BOOL CPlateTubeData::ReadFile(CFile* pFile, WORD wVersion)
{
	DeleteAll();

	BOOL bHaveData = FALSE;
	pFile->Read(&bHaveData, sizeof(BOOL));

	if (bHaveData)
	{
		int nTubeCount = 0;
		int nChannelCount = 0;
		pFile->Read(&nTubeCount, sizeof(int));
		pFile->Read(&nChannelCount, sizeof(int));
		AllocateMemory(nTubeCount, nChannelCount);

		for (int i=0; i<nTubeCount; i++)
		{
			CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(i);
			pTubeData->ReadFile(pFile,wVersion);
		}
	}

	return TRUE;
}

// 函数 CPlateTubeData::GetCycleX
// 作用：读取GetCycleX。
// 参数：iTubeID：整数；iCycleCount：整数；pdValueX；bConstantPCR：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt。
void CPlateTubeData::GetCycleX(int iTubeID, int iCycleCount, double* pdValueX, BOOL bConstantPCR)
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(iTubeID-1);
	ASSERT(pTubeData != NULL);
	pTubeData->GetCycleX(iCycleCount, pdValueX, bConstantPCR);
}

// 函数 CPlateTubeData::GetCycleX
// 作用：读取GetCycleX。
// 参数：iTubeID：整数；iCycleId：整数；bConstantPCR：是或否。
// 返回：返回一个小数。
// 过程：函数里会调用 GetAt。
double CPlateTubeData::GetCycleX(int iTubeID, int iCycleId, BOOL bConstantPCR)
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(iTubeID-1);
	ASSERT(pTubeData != NULL);
	return pTubeData->GetCycleX(iCycleId, bConstantPCR);
}

// 函数 CPlateTubeData::GetCurrentCycleX
// 作用：读取GetCurrentCycleX。
// 参数：iTubeID：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt。
UINT CPlateTubeData::GetCurrentCycleX(int iTubeID)
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(iTubeID-1);
	ASSERT(pTubeData != NULL);
	return pTubeData->GetCurrentCycleX();
}

// 函数 CPlateTubeData::GetChannelFluY
// 作用：读取GetChannelFluY。
// 参数：iTubeID：整数；nType：整数；iChannel：整数；iCycleCount：整数；pdYValue。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt。
void CPlateTubeData::GetChannelFluY(int iTubeID, eDataType nType, int iChannel, int iCycleCount, double* pdYValue)
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(iTubeID-1);
	ASSERT(pTubeData != NULL);
	pTubeData->GetChannelFluY(nType, iChannel, iCycleCount, pdYValue);
}

// 函数 CPlateTubeData::GetChannelCycleFluY
// 作用：读取GetChannelCycleFluY。
// 参数：iTubeID：整数；nType：整数；iChannel：整数；iCycleId：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 GetAt。
double CPlateTubeData::GetChannelCycleFluY(int iTubeID, eDataType nType, int iChannel, int iCycleId)
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(iTubeID - 1);
	ASSERT(pTubeData != NULL);
	return pTubeData->GetChannelCycleFluY(nType, iChannel, iCycleId);
}

// 函数 CPlateTubeData::SetChannelFluY
// 作用：设置SetChannelFluY。
// 参数：iTubeID：整数；nType：整数；iChannel：整数；iCycleCount：整数；pdYValue。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt。
void CPlateTubeData::SetChannelFluY(int iTubeID, eDataType nType, int iChannel, int iCycleCount, double* pdYValue)
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(iTubeID-1);
	ASSERT(pTubeData != NULL);
	pTubeData->SetChannelFluY(nType, iChannel, iCycleCount, pdYValue);
}

// 函数 CPlateTubeData::FluChannelCrosstalkAdjust
// 作用：执行FluChannelCrosstalkAdjust。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pCrosstalkMatrix：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt、GetTubeID。
void CPlateTubeData::FluChannelCrosstalkAdjust(CTubeInfo* pTubeInfo, float** pCrosstalkMatrix)
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(pTubeInfo->GetTubeID()-1);
	pTubeData->FluChannelCrosstalkAdjust(pTubeInfo, pCrosstalkMatrix);
}

// 函数 CPlateTubeData::GetDataNum
// 作用：读取GetDataNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt。
int CPlateTubeData::GetDataNum()
{
	CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(0);
	ASSERT(pTubeData != NULL);
	return pTubeData->GetDataNum();
}

// 函数 CPlateTubeData::GetChannelMaxValueY
// 作用：读取GetChannelMaxValueY。
// 参数：nDataType：整数；iTubeID：整数；iChannel：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 GetAt、GetMaxValueY。
double CPlateTubeData::GetChannelMaxValueY(eDataType nDataType,int iTubeID,int iChannel)
{
	CTubeAmplifyData* pTubeData = (CTubeAmplifyData*)m_arrayTubeData.GetAt(iTubeID - 1);
	double dReturn = pTubeData->GetMaxValueY(nDataType, iChannel);
	return dReturn;
}

//*****************************************************************************************************************
// 孔板扩增段荧光数据
// 函数 CPlateAmplifyTubeData::AllocateMemory
// 作用：执行AllocateMemory。
// 参数：iTubeCount：整数；iChannelCount：整数。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、Add。
BOOL CPlateAmplifyTubeData::AllocateMemory(int iTubeCount, int iChannelCount)
{
	DeleteAll();
	ASSERT(iTubeCount > 0);
	ASSERT(iChannelCount > 0);

	m_iTubeCount = iTubeCount;
	m_iChannelCount = iChannelCount;

	for(int i=0; i<m_iTubeCount; i++)
	{
		CTubeAmplifyData* pTubeData = new CTubeAmplifyData;
		pTubeData->AllocateMemory(m_iChannelCount);
		m_arrayTubeData.Add(pTubeData);
	}

	return TRUE;
}

// 函数 CPlateAmplifyTubeData::FluDigitalFilter
// 作用：执行FluDigitalFilter。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iFlag：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt、GetTubeID。
void CPlateAmplifyTubeData::FluDigitalFilter(CTubeInfo* pTubeInfo, CPtrArray* pFilterItem, CDataAnalysisPCR* pAlgorithm, int iFlag)
{
	CTubeAmplifyData* pTubeData = (CTubeAmplifyData*)m_arrayTubeData.GetAt(pTubeInfo->GetTubeID()-1);
	pTubeData->FluDigitalFilter(pTubeInfo, pFilterItem, pAlgorithm, iFlag);
}

// 函数 CPlateAmplifyTubeData::FluoAdjustBaseline
// 作用：执行FluoAdjustBaseline。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt、GetTubeID。
void CPlateAmplifyTubeData::FluoAdjustBaseline(CTubeInfo* pTubeInfo, CDataAnalysisPara* pAnalysisPara, CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity)
{
	CTubeAmplifyData* pTubeData = (CTubeAmplifyData*)m_arrayTubeData.GetAt(pTubeInfo->GetTubeID()-1);
	pTubeData->FluoAdjustBaseline(pTubeInfo, pAnalysisPara, pAlgorithm, pTurbidity);
}

// 函数 CPlateAmplifyTubeData::FluTurbidityAdjust
// 作用：执行FluTurbidityAdjust。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt、GetTubeID。
void CPlateAmplifyTubeData::FluTurbidityAdjust(CTubeInfo* pTubeInfo, CCalibrateParaTurbidity* pTurbidity, CDataAnalysisPCR* pAlgorithm)
{
	CTubeAmplifyData* pTubeData = (CTubeAmplifyData*)m_arrayTubeData.GetAt(pTubeInfo->GetTubeID()-1);
	pTubeData->FluTurbidityAdjust(pTubeInfo, pTurbidity, pAlgorithm);
}

// 函数 CPlateAmplifyTubeData::FluNormalizeAndDeltaRn
// 作用：执行FluNormalizeAndDeltaRn。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt、GetTubeID。
void CPlateAmplifyTubeData::FluNormalizeAndDeltaRn(CTubeInfo* pTubeInfo, CDataAnalysisPara* pAnalysisPara, CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity)
{
	CTubeAmplifyData* pTubeData = (CTubeAmplifyData*)m_arrayTubeData.GetAt(pTubeInfo->GetTubeID()-1);
	pTubeData->FluNormalizeAndDeltaRn(pTubeInfo, pAnalysisPara, pAlgorithm, pTurbidity);
}

// 生成Ct等相关参数
// 函数 CPlateAmplifyTubeData::GenerateCtByTubeID
// 作用：计算GenerateCtByTubeID。
// 参数：nDataType：整数；iTubeID：整数；nMethod：整数；pAmplifyPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
// 返回：返回一个小数。
// 过程：函数里会调用 GetAt、GenerateCt。
double CPlateAmplifyTubeData::GenerateCtByTubeID(eDataType nDataType, int iTubeID, eMethodCalculateCt nMethod, tagAnaAmplifyPara* pAmplifyPara, CDataAnalysisPCR* pAlgorithm)
{
	CTubeAmplifyData* pTubeData = (CTubeAmplifyData*)m_arrayTubeData.GetAt(iTubeID - 1);
	double dReturn = pTubeData->GenerateCt(nDataType, nMethod, pAmplifyPara, pAlgorithm);
	return dReturn;
}

// 函数 CPlateAmplifyTubeData::GenerateAutoSplineThreshold
// 作用：计算GenerateAutoSplineThreshold。
// 参数：nDataType：整数；iTubeID：整数；iChannel：整数；pAlgorithm：指针，指向调用方传入的对象。
// 返回：返回一个小数。
// 过程：函数里会调用 GetAt。
double CPlateAmplifyTubeData::GenerateAutoSplineThreshold(eDataType nDataType,int iTubeID,int iChannel,CDataAnalysisPCR* pAlgorithm)
{
	CTubeAmplifyData* pTubeData = (CTubeAmplifyData*)m_arrayTubeData.GetAt(iTubeID - 1);
	double dReturn = pTubeData->GenerateAutoSplineThreshold(nDataType,iChannel,pAlgorithm);
	return dReturn;
}

// 函数 CPlateAmplifyTubeData::SetTubeData
// 作用：设置SetTubeData。
// 参数：pVecData：指针，指向调用方传入的对象；iTubeNum：整数；iChanNum：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetAt、size、AddOriginalData。
int CPlateAmplifyTubeData::SetTubeData(vector<double>* pVecData,int iTubeNum,int iChanNum)
{
	if(NULL == pVecData)
	{
		return -1;
	}
	if(iTubeNum < 1)
	{
		return -2;
	}
	if(iChanNum < 1)
	{
		return -3;
	}
	if(m_iChannelCount < 1)
	{
		return -4;
	}
	if(m_iTubeCount < 1)
	{
		return -5;
	}

	int iUsedChanNum = m_iChannelCount;
	if(m_iChannelCount > iChanNum)
	{
		iUsedChanNum = iChanNum;
	}

	int iUsedTubeNum = m_iTubeCount;
	if(m_iTubeCount > iTubeNum)
	{
		iUsedTubeNum = iTubeNum;
	}

	CTubeData* pTubeData = NULL;
	for(int i = 0;i < iUsedTubeNum;++i)
	{
		pTubeData = (CTubeData*)m_arrayTubeData.GetAt(i);
		if(NULL == pTubeData)
		{
			continue;
		}
		for(int j = 0;j < iUsedChanNum;++j)
		{
			vector<double>& vecData = pVecData[j * iUsedTubeNum + i];
			for(int k = 0;k < vecData.size();++k)
			{
				pTubeData->AddOriginalData(j,vecData[k]);
			}
		}
	}

	return 0;
}


//*****************************************************************************************************************
// 孔板熔解段荧光数据
// 函数 CPlateMeltTubeData::AllocateMemory
// 作用：执行AllocateMemory。
// 参数：iTubeCount：整数；iChannelCount：整数。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、Add。
BOOL CPlateMeltTubeData::AllocateMemory(int iTubeCount, int iChannelCount)
{
	DeleteAll();
	ASSERT(iTubeCount > 0);
	ASSERT(iChannelCount > 0);

	m_iTubeCount = iTubeCount;
	m_iChannelCount = iChannelCount;

	for(int i=0; i<m_iTubeCount; i++)
	{
		CTubeMeltData* pTubeData = new CTubeMeltData;
		pTubeData->AllocateMemory(m_iChannelCount);
		m_arrayTubeData.Add(pTubeData);
	}

	return TRUE;
}

// 函数 CPlateMeltTubeData::FluDigitalFilter
// 作用：执行FluDigitalFilter。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iFlag：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetAt、GetTubeID。
void CPlateMeltTubeData::FluDigitalFilter(CTubeInfo* pTubeInfo, CPtrArray* pFilterItem, CDataAnalysisPCR* pAlgorithm, int iFlag)
{
	CTubeMeltData* pTubeData = (CTubeMeltData*)m_arrayTubeData.GetAt(pTubeInfo->GetTubeID()-1);
	pTubeData->FluDigitalFilter(pTubeInfo, pFilterItem, pAlgorithm, iFlag);
}

// 函数 CPlateMeltTubeData::AddOriginalData
// 作用：创建或加入AddOriginalData。
// 参数：aryOriData；iChannelID：整数；dTem：小数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、GetAt。
int CPlateMeltTubeData::AddOriginalData(CUIntArray& aryOriData,int iChannelID,double dTem)
{
	int iUsefulDataNum = (m_iTubeCount > aryOriData.GetSize() ? aryOriData.GetSize() : m_iTubeCount);

	for(int i = 0;i < iUsefulDataNum;++i)
	{
		int nTubeNo = i;
		if (m_nStartPos == SCAN_START_RT)
		{
			int nRow = i / m_iColCount;
			int nCol = i % m_iColCount;
			nTubeNo = (nRow+1)*m_iColCount - nCol -1;
		}

		CTubeData* pTubeData = (CTubeData*)m_arrayTubeData.GetAt(nTubeNo);
		if(NULL == pTubeData)
		{
			continue;
		}
		pTubeData->AddOriginalData(iChannelID - 1,aryOriData.GetAt(i),dTem);
	}

	return 0;
}
