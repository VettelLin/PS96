// 【交接】 PCRCtrlLib\TubeData.cpp
// 作用：单孔荧光曲线。基线校正前调用起峰判断；没有起峰时把 DeltaRn 整段写成 0；再用荧光阈值计算 Ct。
// 先看这些函数：CTubeData、DeleteAll、AllocateMemory、clear、RemoveAll、Add、BeAllAllocated、AddCycleX。
#include "StdAfx.h"
#include "TubeData.h"
#include "DeclaresPCR.h"
#include <cmath>
#include "PublicInfo.h"

// 函数 CTubeData::CTubeData
// 作用：执行CTubeData。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTubeData::CTubeData(void)
{
	m_nChannelCount = 0;
	m_pFluOriginal = NULL;
	m_pFluCrossTalk = NULL;
	m_pFluFilterMedian = NULL;
	m_pFluBaselineAdjust = NULL;
	m_pFluFilter = NULL;
	m_pFluTuibitidy = NULL;
}

// 函数 CTubeData::~CTubeData
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CTubeData::~CTubeData(void)
{
	DeleteAll();
}

// 函数 CTubeData::AllocateMemory
// 作用：执行AllocateMemory。
// 参数：nChannelCount：整数。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、clear、RemoveAll、Add、BeAllAllocated。
BOOL CTubeData::AllocateMemory(int nChannelCount)
{
	DeleteAll();

	m_nChannelCount = nChannelCount;
	m_viValueX.clear();
	m_pFluOriginal = new vector<UINT>[m_nChannelCount];
	m_pFluCrossTalk = new vector<double>[m_nChannelCount];
	m_pFluFilterMedian = new vector<double>[m_nChannelCount];
	m_pFluBaselineAdjust = new vector<double>[m_nChannelCount];
	m_pFluFilter = new vector<double>[m_nChannelCount];
	m_pFluTuibitidy = new vector<double>[m_nChannelCount];

	m_arrayAutoAdjust.RemoveAll();
	for (int i=0; i<nChannelCount; i++)
	{
		m_arrayAutoAdjust.Add(FALSE);
	}

	return BeAllAllocated();
}

// 函数 CTubeData::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 clear。
void CTubeData::DeleteAll()
{
	m_nChannelCount = 0;
	m_viValueX.clear();
	if(NULL != m_pFluOriginal)
	{
		delete [] m_pFluOriginal;
		m_pFluOriginal = NULL;
	}
	if(NULL != m_pFluCrossTalk)
	{
		delete [] m_pFluCrossTalk;
		m_pFluCrossTalk = NULL;
	}
	if(NULL != m_pFluFilterMedian)
	{
		delete [] m_pFluFilterMedian;
		m_pFluFilterMedian = NULL;
	}
	if(NULL != m_pFluBaselineAdjust)
	{
		delete [] m_pFluBaselineAdjust;
		m_pFluBaselineAdjust = NULL;
	}
	if(NULL != m_pFluFilter)
	{
		delete [] m_pFluFilter;
		m_pFluFilter = NULL;
	}
	if(NULL != m_pFluTuibitidy)
	{
		delete [] m_pFluTuibitidy;
		m_pFluTuibitidy = NULL;
	}

	return;
}

// 函数 CTubeData::BeAllAllocated
// 作用：判断BeAllAllocated是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTubeData::BeAllAllocated()
{
	if(NULL == m_pFluOriginal)
	{
		return FALSE;
	}
	if(NULL == m_pFluCrossTalk)
	{
		return FALSE;
	}
	if(NULL == m_pFluFilterMedian)
	{
		return FALSE;
	}
	if(NULL == m_pFluBaselineAdjust)
	{
		return FALSE;
	}
	if(NULL == m_pFluFilter)
	{
		return FALSE;
	}
	if(NULL == m_pFluTuibitidy)
	{
		return FALSE;
	}

	return TRUE;
}

// 函数 CTubeData::AddCycleX
// 作用：创建或加入AddCycleX。
// 参数：nCycle：整数。
// 返回：没有返回值。
// 过程：函数里会调用 push_back。
void CTubeData::AddCycleX(UINT nCycle)
{
	m_viValueX.push_back(nCycle);
}

// 函数 CTubeData::AddOriginalData
// 作用：创建或加入AddOriginalData。
// 参数：nChannelNo：整数；nYValue：整数。
// 返回：没有返回值。
// 过程：函数里会调用 push_back。
void CTubeData::AddOriginalData(int nChannelNo, UINT nYValue)
{
	m_pFluOriginal[nChannelNo].push_back(nYValue);
	m_pFluCrossTalk[nChannelNo].push_back(nYValue);
	m_pFluFilterMedian[nChannelNo].push_back(nYValue);
	m_pFluBaselineAdjust[nChannelNo].push_back(nYValue);
	m_pFluFilter[nChannelNo].push_back(nYValue);
	m_pFluTuibitidy[nChannelNo].push_back(nYValue);
}

// 函数 CTubeData::GetFluYValueBy
// 作用：读取GetFluYValueBy。
// 参数：nType：整数；nChannelNo：整数；nPointNo：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 ConvertToLog10。
double CTubeData::GetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo)
{
	double dReturn = 0;
	switch(nType)
	{
	case FLU_ORIGINAL:
		dReturn = m_pFluOriginal[nChannelNo][nPointNo];
		break;
	case FLU_CROSSTALK:
		dReturn = m_pFluCrossTalk[nChannelNo][nPointNo];
		break;
	case FLU_FILTER_MEDIAN:
		dReturn = m_pFluFilterMedian[nChannelNo][nPointNo];
		break;
	case FLU_BASELINE_ADJUST:
		dReturn = m_pFluBaselineAdjust[nChannelNo][nPointNo];
		break;
	case FLU_FILTER:
		dReturn = m_pFluFilter[nChannelNo][nPointNo];
		break;
	case FLU_TURBIDITY:
		dReturn = m_pFluTuibitidy[nChannelNo][nPointNo];
		break;
	case LOG_FLU_TURBIDITY:
		dReturn = m_pFluTuibitidy[nChannelNo][nPointNo];
		dReturn = ConvertToLog10(dReturn);
		break;

	default:
		break;
	}

	return dReturn;
}

// 函数 CTubeData::SetFluYValueBy
// 作用：设置SetFluYValueBy。
// 参数：nType：整数；nChannelNo：整数；nPointNo：整数；dYValue：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTubeData::SetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo, double dYValue)
{
	switch(nType)
	{
	case FLU_ORIGINAL:
		m_pFluOriginal[nChannelNo][nPointNo] = (UINT)dYValue; 
		break;
	case FLU_CROSSTALK:
		m_pFluCrossTalk[nChannelNo][nPointNo] = dYValue; 
		break;
	case FLU_FILTER_MEDIAN:
		m_pFluFilterMedian[nChannelNo][nPointNo] = dYValue; 
		break;
	case FLU_BASELINE_ADJUST:
		m_pFluBaselineAdjust[nChannelNo][nPointNo] = dYValue; 
		break;
	case FLU_FILTER:
		m_pFluFilter[nChannelNo][nPointNo] = dYValue; 
		break;
	case FLU_TURBIDITY:
		m_pFluTuibitidy[nChannelNo][nPointNo] = dYValue; 
		break;
	default:
		break;
	}
}

// 函数 CTubeData::GetCycleX
// 作用：读取GetCycleX。
// 参数：nCycleCount：整数；pdValueX；bConstantPCR：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTubeData::GetCycleX(int nCycleCount, double* pdValueX, BOOL bConstantPCR)
{
	for(int i=0; i<nCycleCount; i++)
	{
		if (bConstantPCR)
		{
			pdValueX[i] = m_viValueX[i] / 1000.0; // 默认按秒显示
		}
		else
		{
			pdValueX[i] = m_viValueX[i];
		}
	}
}

// 函数 CTubeData::GetCycleX
// 作用：读取GetCycleX。
// 参数：iCycleId：整数；bConstantPCR：是或否。
// 返回：返回一个小数。
// 过程：函数里会调用 size。
double CTubeData::GetCycleX(int iCycleId, BOOL bConstantPCR)
{
	double dValueX = 0;
	if(iCycleId >= m_viValueX.size())
	{
		return dValueX;
	}

	if (bConstantPCR)
	{
		dValueX = m_viValueX[iCycleId] / 1000.0; // 默认按秒显示
	}
	else
	{
		dValueX = m_viValueX[iCycleId];
	}
	return dValueX;
}

// 函数 CTubeData::GetCurrentCycleX
// 作用：读取GetCurrentCycleX。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
UINT CTubeData::GetCurrentCycleX()
{
	int iCycle = m_viValueX.size() -1;
	return m_viValueX[iCycle];
}


// 函数 CTubeData::GetChannelFluY
// 作用：读取GetChannelFluY。
// 参数：nType：整数；nChannel：整数；nCycleCount：整数；pdYValue。
// 返回：没有返回值。
// 过程：函数里会调用 GetFluYValueBy。
void CTubeData::GetChannelFluY(eDataType nType, int nChannel, int nCycleCount, double* pdYValue)
{
	for(int i=0; i<nCycleCount; i++)
	{
		pdYValue[i] = GetFluYValueBy(nType, nChannel, i);
	}
}

// 函数 CTubeData::SetChannelFluY
// 作用：设置SetChannelFluY。
// 参数：nType：整数；nChannel：整数；nCycleCount：整数；pdYValue。
// 返回：没有返回值。
// 过程：函数里会调用 SetFluYValueBy。
void CTubeData::SetChannelFluY(eDataType nType, int nChannel, int nCycleCount, double* pdYValue)
{
	for(int i=0; i<nCycleCount; i++)
	{
		SetFluYValueBy(nType, nChannel, i, pdYValue[i]);
	}
}

// 函数 CTubeData::GetChannelCycleFluY
// 作用：读取GetChannelCycleFluY。
// 参数：nType：整数；nChannel：整数；nCycleId：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 GetFluYValueBy。
double CTubeData::GetChannelCycleFluY(eDataType nType, int nChannel, int nCycleId)
{
	return GetFluYValueBy(nType, nChannel,nCycleId);
}

// 函数 CTubeData::FluCopyTo
// 作用：执行FluCopyTo。
// 参数：nChannelCount：整数；nCycleCount：整数；pBase：指针，指向调用方传入的对象；pTarget：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTubeData::FluCopyTo(int nChannelCount, int nCycleCount, vector<UINT>* pBase, vector<double>* pTarget)
{
	for (int i=0; i<nChannelCount; i++)
	{
		for (int j=0; j<nCycleCount; j++)
		{
			pTarget[i][j] = pBase[i][j];
		}
	}
}

// 函数 CTubeData::FluCopyTo
// 作用：执行FluCopyTo。
// 参数：nChannelCount：整数；nCycleCount：整数；pBase：指针，指向调用方传入的对象；pTarget：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTubeData::FluCopyTo(int nChannelCount, int nCycleCount, vector<double>* pBase, vector<double>* pTarget)
{
	for (int i=0; i<nChannelCount; i++)
	{
		for (int j=0; j<nCycleCount; j++)
		{
			pTarget[i][j] = pBase[i][j];
		}
	}
}

// 函数 CTubeData::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 size、Write、data。
BOOL CTubeData::WriteFile(CFile* pFile)
{
	int nCount = m_viValueX.size();
	pFile->Write((const char*)&nCount, sizeof(int));
	pFile->Write((const char*)m_viValueX.data(), sizeof(UINT)*nCount);

	for(int i=0; i<m_nChannelCount; i++)
	{
		nCount = m_pFluOriginal[i].size();
		pFile->Write((const char*)&nCount, sizeof(int));
		pFile->Write((const char*)m_pFluOriginal[i].data(), sizeof(UINT)*nCount);
	}

	return TRUE;
}

// 函数 CTubeData::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 Read、push_back、AddOriginalData、SAFE_DELETE。
BOOL CTubeData::ReadFile(CFile* pFile,WORD wVersion)
{
	int nCount = 0;
	pFile->Read(&nCount, sizeof(int));
	UINT* pValueX = new UINT[nCount];
	pFile->Read(pValueX, sizeof(UINT)*nCount);
	for (int i=0; i<nCount; i++)
	{
		m_viValueX.push_back(pValueX[i]);
	}

	UINT* pOrigData = NULL;
	for (int k=0; k<m_nChannelCount; k++)
	{
		pFile->Read(&nCount, sizeof(int));
		if (pOrigData == NULL)
		{
			pOrigData = new UINT[nCount];
		}
		pFile->Read(pOrigData, sizeof(UINT)*nCount);
		for (int x=0; x<nCount; x++)
		{
			AddOriginalData(k, pOrigData[x]);
		}
	}

	SAFE_DELETE(pValueX);
	SAFE_DELETE(pOrigData);

	return TRUE;
}

// 进行各通道串扰数据处理
// 函数 CTubeData::FluChannelCrosstalkAdjust
// 作用：执行FluChannelCrosstalkAdjust。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pCrosstalkMatrix：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CorrectFluoZeroValue、GetPointCout、GetTargetCount、GetTargetInfo、GetBeSelected、GetChannel。
void CTubeData::FluChannelCrosstalkAdjust(CTubeInfo* pTubeInfo, float** pCrosstalkMatrix)
{
	// 进行断点续传时0点修正
	CorrectFluoZeroValue(pTubeInfo);

	int nCycleCount = GetPointCout();
	for (int i=0; i<nCycleCount; i++)
	{
		int iTargetCount = pTubeInfo->GetTargetCount();
		for(int j=0; j<iTargetCount; j++)
		{
			CDyeTargetInfo* pTargetCol = pTubeInfo->GetTargetInfo(j);
			if (!pTargetCol->GetBeSelected())
				continue;

			int nCol = pTargetCol->GetChannel() -1;
			m_pFluCrossTalk[nCol][i] = m_pFluOriginal[nCol][i];

			for (int x=0; x<iTargetCount; x++)
			{
				CDyeTargetInfo* pTargetRow = pTubeInfo->GetTargetInfo(x);
				if (!pTargetCol->GetBeSelected())
					continue;

				int nRow = pTargetRow->GetChannel() -1;
				if (nCol == nRow)
					continue;

				float fRatio = pCrosstalkMatrix[nRow][nCol];
				double value1 = m_pFluCrossTalk[nCol][i];
				double value2 = m_pFluOriginal[nRow][i];
				double value3 = m_pFluCrossTalk[nCol][i] - m_pFluOriginal[nRow][i] * fRatio;
				m_pFluCrossTalk[nCol][i] -= m_pFluOriginal[nRow][i] * fRatio;

				//防止串扰系数较大，导致产生负数，添加于20220413，孙文郎
				if(m_pFluCrossTalk[nCol][i] < 0)
				{
					m_pFluCrossTalk[nCol][i] = 10;
				}
			}
		}
	}
}

// 函数 CTubeData::GetDataNum
// 作用：读取GetDataNum。
// 参数：iChannelNo：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
int CTubeData::GetDataNum(int iChannelNo)
{
	if(m_nChannelCount < 1)
	{
		return 0;
	}

	if(NULL == m_pFluOriginal)
	{
		return 0;
	}

	return m_pFluOriginal[iChannelNo].size();
}

// 函数 CTubeData::GetMaxValueY
// 作用：读取GetMaxValueY。
// 参数：nDataType：整数；iChannel：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 GetPointCout、GetChannelFlu。
double CTubeData::GetMaxValueY(eDataType nDataType, int iChannel)
{
	int nCycleCount = GetPointCout();
	if(nCycleCount < 1)
		return 0;

	CPeakAmlCheckParam peakAmlChkParam;

	double *pdTempX = new double[nCycleCount];
	double *pdTempY = new double[nCycleCount];
	if(NULL == pdTempX || NULL == pdTempY)
		goto GAST_END;

	GetChannelFlu(nDataType, iChannel - 1,nCycleCount, pdTempX,pdTempY);

	double dReturn = -1000;
	for(int k = 2;k < nCycleCount-1;++k)
	{
		if(pdTempY[k] > dReturn)
		{
			dReturn = pdTempY[k];
		}
	}

GAST_END:
	if(NULL != pdTempX)
	{
		delete [] pdTempX;
	}
	if(NULL != pdTempY)
	{
		delete [] pdTempY;
	}
	return dReturn;
}

// 根据滤波参数进行数据滤波
// 函数 CTubeData::FluDigitalFilterBy
// 作用：执行FluDigitalFilterBy。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；iFlag：整数；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetCalibrateChannel、GetTargetCount、GetTargetInfo、GetBeSelected、GetChannel、FluDigitalFilterByChannel。
void CTubeData::FluDigitalFilterBy(CTubeInfo* pTubeInfo,CPtrArray* pFilterItem,int iFlag,CDataAnalysisPCR* pAlgorithm, int iDivideFlag)
{
	int iCalibrateChannel = pTubeInfo->GetCalibrateChannel();
	int iTargetCount = pTubeInfo->GetTargetCount();
	for(int i = 0;i < iTargetCount;++i)
	{
		CDyeTargetInfo* pTarget = pTubeInfo->GetTargetInfo(i);
		if (pTarget->GetBeSelected() && pTarget->GetChannel() != iCalibrateChannel)
		{
			int nChannelNo = pTarget->GetChannel() -1;
			FluDigitalFilterByChannel(nChannelNo,pFilterItem,iFlag,pAlgorithm, iDivideFlag);
		}
	}

	//旧版的PS96软件，IVD模式下，默认校准通道未选中，可能存在第6通道多滤波一次的情况
	if(iCalibrateChannel > 0)
	{
		FluDigitalFilterByChannel(iCalibrateChannel-1,pFilterItem,iFlag,pAlgorithm, iDivideFlag);
	}

	return;
}

// 指定通道滤波
// 函数 CTubeData::FluDigitalFilterByChannel
// 作用：执行FluDigitalFilterByChannel。
// 参数：iChannelNo：整数；pFilterItem：指针，指向调用方传入的对象；iFlag：整数；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetPointCout、GetCount、GetChannelFlu、memcpy、GetAt、DigitalFilter。
void CTubeData::FluDigitalFilterByChannel(int iChannelNo,CPtrArray* pFilterItem,int iFlag,CDataAnalysisPCR* pAlgorithm, int iDivideFlag)
{
	int nCycleCount = GetPointCout();
	if(nCycleCount < 2)
	{
		return;
	}

	int iFilterCount = pFilterItem->GetCount();
	int iByteNum = sizeof(double) * nCycleCount;

	double *pDTemp = new double[nCycleCount];
	if(NULL == pDTemp)
	{
		goto FDFBC_END;
	}
	double *pDReturn = new double[nCycleCount];
	if(NULL == pDReturn)
	{
		goto FDFBC_END;
	}

	if (iDivideFlag == 2)
	{
		GetChannelFlu(FLU_TURBIDITY,iChannelNo,nCycleCount,NULL,pDReturn);
	}
	else
		GetChannelFlu(FLU_CROSSTALK,iChannelNo,nCycleCount,NULL,pDReturn);

	memcpy(pDTemp,pDReturn,iByteNum);

	BOOL bFiltering = FALSE;
	for(int j = 0;j < iFilterCount;++j)
	{
		tagFilterItem* pItem = (tagFilterItem*)pFilterItem->GetAt(j);
		if(FILTER_NONE == pItem->nType)
		{
			continue;
		}

		if(pItem->iFilterUser == iFlag)
		{
			for(int m = 0;m < pItem->iTimes;++m)
			{
				switch(pItem->nType)
				{
				case FILTER_MEDIAN://中位值滤波
					if (iDivideFlag != 2)
					{
						bFiltering = TRUE;
						pAlgorithm->DigitalFilter(pDTemp,pDReturn,nCycleCount,CDataAlgorithmPCR::FILTERTYPE_MEDIAN, pItem->iPara1);
					}
					break;
				case FILTER_FM_BN: // 均值滤波
					if (iDivideFlag != 1)
						pAlgorithm->KdsptForwardMBackN_New(nCycleCount,pDTemp,pDReturn,pItem->iPara1,pItem->iPara2);
					break;
				default:
					ASSERT(FALSE);
					break;
				}
				memcpy(pDTemp,pDReturn,iByteNum); 
			}
		}
	}


	// 处理开始两点的数据，保证偏差较小
	if (bFiltering)
	{
		if (nCycleCount > 3)
		{
			pDReturn[0] = pDReturn[2] + (pDReturn[0]-pDReturn[2]) * 0.1;
			pDReturn[1] = pDReturn[2] + (pDReturn[1]-pDReturn[2]) * 0.1;
		}
	}

	if (iDivideFlag == 1)
	{
		SetChannelFlu(FLU_FILTER_MEDIAN,iChannelNo,nCycleCount,pDReturn);
		SetChannelFlu(FLU_FILTER,iChannelNo,nCycleCount,pDReturn);
		SetChannelFlu(FLU_TURBIDITY,iChannelNo,nCycleCount,pDReturn);
		SetChannelFlu(FLU_BASELINE_ADJUST,iChannelNo,nCycleCount,pDReturn);
	}
	else
	{
		SetChannelFlu(FLU_FILTER,iChannelNo,nCycleCount,pDReturn);
	}

FDFBC_END:
	if(NULL != pDTemp)
	{
		delete [] pDTemp;
	}
	if(NULL != pDReturn)
	{
		delete [] pDReturn;
	}

	return;
}

// 函数 CTubeData::GetChannelFlu
// 作用：读取GetChannelFlu。
// 参数：Type；nChannel：整数；nCycleCount：整数；pdXValue；pdYValue。
// 返回：没有返回值。
// 过程：函数里会调用 GetFluYValueBy。
void CTubeData::GetChannelFlu(eDataType Type, int nChannel, int nCycleCount, double* pdXValue, double* pdYValue)
{
	for(int i=0; i<nCycleCount; i++)
	{
		if (pdXValue != NULL)
		{
			pdXValue[i] = i + 1;
		}
		pdYValue[i] = GetFluYValueBy(Type, nChannel, i);
	}
}

// 函数 CTubeData::SetChannelFlu
// 作用：设置SetChannelFlu。
// 参数：Type；nChannel：整数；nCycleCount：整数；pdYValue。
// 返回：没有返回值。
// 过程：函数里会调用 SetFluYValueBy。
void CTubeData::SetChannelFlu(eDataType Type, int nChannel, int nCycleCount, double* pdYValue)
{
	for(int i=0; i<nCycleCount; i++)
	{
		SetFluYValueBy(Type, nChannel, i, pdYValue[i]);
	}
}

// 函数 CTubeData::HasData
// 作用：判断HasData是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 size。
BOOL CTubeData::HasData()
{
	if (m_pFluOriginal != NULL)
	{
		if (m_pFluOriginal[0].size() > 0)
			return TRUE;
	}

	return FALSE;
}

// 函数 CTubeData::ConvertToLog10
// 作用：执行ConvertToLog10。
// 参数：dInput：小数。
// 返回：返回一个小数。
// 过程：函数里会调用 log10。
double CTubeData::ConvertToLog10(double dInput)
{
	if(dInput < 0)
	{
		return log10(-dInput);
	}
	else if(dInput > 0)
	{
		return log10(dInput);
	}
	else 
		return 0;
}

// 函数 CTubeData::CorrectFluoZeroValue
// 作用：执行CorrectFluoZeroValue。
// 参数：pTubeInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetPointCout、GetTargetCount、GetTargetInfo、GetBeSelected、UINT、GetDyeName。
void CTubeData::CorrectFluoZeroValue(CTubeInfo* pTubeInfo)
{
	int nCycleCount = GetPointCout();
	int iTargetCount = pTubeInfo->GetTargetCount();
	for (int i=0; i<iTargetCount; i++)
	{
		CDyeTargetInfo* pTarget = pTubeInfo->GetTargetInfo(i);
		if (!pTarget->GetBeSelected())
			continue;

		int iStartValue = m_pFluOriginal[i][0];
		int iEndValue = 0;
		int iStartIndex = -1;
		int iZeroCount = 0;
		for(int j=1; j<nCycleCount; j++)
		{
			if (iStartValue == 0)
			{
				iStartValue = m_pFluOriginal[i][j];
				continue;
			}

			if (m_pFluOriginal[i][j] == 0)
			{
				iZeroCount ++;
				if (iStartIndex == -1)
				{
					iStartIndex = j;
				}
			}
			else if (iZeroCount > 0)
			{
				iEndValue = m_pFluOriginal[i][j];
				double dGradientValue = (iEndValue - iStartValue) / (iZeroCount+1);
				for (int xx=0; xx<iZeroCount; xx++)
				{
					m_pFluOriginal[i][iStartIndex+xx] = UINT(iStartValue + dGradientValue * (xx + 1)+0.5);
					if (pTarget->GetDyeName() == _T("MOT"))
					{
						SetFluYValueBy(FLU_NORMALIZATE, i, iStartIndex+xx, m_pFluOriginal[i][iStartIndex+xx]);
						SetFluYValueBy(FLU_DELTARN, i, iStartIndex+xx, m_pFluOriginal[i][iStartIndex+xx]);
					}
				}

				iStartValue = iEndValue;
				iStartIndex = -1;
				iZeroCount = 0;
			}
			else
			{
				iStartValue = m_pFluOriginal[i][j];
			}
		}
	}
}


//*****************************************************************************************************************
// 扩增段荧光数据
// 函数 CTubeAmplifyData::CTubeAmplifyData
// 作用：执行CTubeAmplifyData。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTubeAmplifyData::CTubeAmplifyData(void)
{
	m_pFluNormalize = NULL;
	m_pFluDeltaRn = NULL;
}

// 函数 CTubeAmplifyData::~CTubeAmplifyData
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CTubeAmplifyData::~CTubeAmplifyData(void)
{
	DeleteAll();
}

// 函数 CTubeAmplifyData::AllocateMemory
// 作用：执行AllocateMemory。
// 参数：nChannelCount：整数。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、BeAllAllocated。
BOOL CTubeAmplifyData::AllocateMemory(int nChannelCount)
{
	CTubeData::AllocateMemory(nChannelCount);

	DeleteAll();
	m_nChannelCount = nChannelCount;

	m_pFluNormalize = new vector<double>[m_nChannelCount];
	m_pFluDeltaRn = new vector<double>[m_nChannelCount];

	return BeAllAllocated();
}

// 函数 CTubeAmplifyData::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTubeAmplifyData::DeleteAll()
{
	m_nChannelCount = 0;

	if(NULL != m_pFluNormalize)
	{
		delete [] m_pFluNormalize;
		m_pFluNormalize = NULL;
	}

	if(NULL != m_pFluDeltaRn)
	{
		delete [] m_pFluDeltaRn;
		m_pFluDeltaRn = NULL;
	}

	return;
}

// 函数 CTubeAmplifyData::AddOriginalData
// 作用：创建或加入AddOriginalData。
// 参数：nChannelNo：整数；nYValue：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、GetFluoDataAutoAdjust、GetAt、GetFluoDataMaxLimited、GetFluoDataAdjustLimited、GetDataNum。
void CTubeAmplifyData::AddOriginalData(int nChannelNo, UINT nYValue)
{
	CPublicInfo* pInfo = CPublicInfo::GetInstance();
	if (pInfo->GetFluoDataAutoAdjust())
	{
		BOOL bAutoAdjust = m_arrayAutoAdjust.GetAt(nChannelNo);
		if (bAutoAdjust)
		{
			nYValue = pInfo->GetFluoDataMaxLimited();
			//if (nYValue < pInfo->GetFluoDataAdjustLimited())
			//{
			//	nYValue += pInfo->GetFluoDataMaxLimited();
			//}
		}
		else
		{
			int iDafaCount = GetDataNum(nChannelNo);
			if (nYValue == pInfo->GetFluoDataMaxLimited())
			{
				m_arrayAutoAdjust.SetAt(nChannelNo, TRUE);
			}
			else if (iDafaCount > 0)
			{
				UINT nLastValue = GetFluYValueBy(FLU_ORIGINAL, nChannelNo, iDafaCount-1);
				if (nYValue+40000 < nLastValue)
				{
					m_arrayAutoAdjust.SetAt(nChannelNo, TRUE);
					//nYValue += pInfo->GetFluoDataMaxLimited();
					nYValue = pInfo->GetFluoDataMaxLimited();
				}
			}
		}
	}

	CTubeData::AddOriginalData(nChannelNo, nYValue);
	m_pFluNormalize[nChannelNo].push_back(nYValue);
	m_pFluDeltaRn[nChannelNo].push_back(nYValue);

	return;
}

// 函数 CTubeAmplifyData::GetFluYValueBy
// 作用：读取GetFluYValueBy。
// 参数：nType：整数；nChannelNo：整数；nPointNo：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 ConvertToLog10。
double CTubeAmplifyData::GetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo)
{
	double dReturn = 0;
	switch(nType)
	{
	case FLU_NORMALIZATE:
		dReturn = m_pFluNormalize[nChannelNo][nPointNo];
		break;
	case FLU_DELTARN:
		dReturn = m_pFluDeltaRn[nChannelNo][nPointNo];
		break;

	case LOG_FLU_TURBIDITY:
		dReturn = m_pFluTuibitidy[nChannelNo][nPointNo];
		dReturn = ConvertToLog10(dReturn);
		break;
	case LOG_FLU_NORMALIZATE:
		dReturn = m_pFluNormalize[nChannelNo][nPointNo];
		dReturn = ConvertToLog10(dReturn);
		break;
	case LOG_FLU_DELTARN:
		dReturn = m_pFluDeltaRn[nChannelNo][nPointNo];
		dReturn = ConvertToLog10(dReturn);
		break;
	default:
		dReturn = CTubeData::GetFluYValueBy(nType, nChannelNo, nPointNo);
		break;
	}
	return dReturn;
}

// 函数 CTubeAmplifyData::SetFluYValueBy
// 作用：设置SetFluYValueBy。
// 参数：nType：整数；nChannelNo：整数；nPointNo：整数；dYValue：小数。
// 返回：没有返回值。
// 过程：函数里会调用 CTubeData::SetFluYValueBy。
void CTubeAmplifyData::SetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo, double dYValue)
{
	switch(nType)
	{
	case FLU_NORMALIZATE:
		m_pFluNormalize[nChannelNo][nPointNo] = dYValue; 
		break;
	case FLU_DELTARN:
		m_pFluDeltaRn[nChannelNo][nPointNo] = dYValue; 
		break;
	default:
		CTubeData::SetFluYValueBy(nType, nChannelNo, nPointNo, dYValue);
		break;
	}
}

// 函数 CTubeAmplifyData::FluDigitalFilter
// 作用：执行FluDigitalFilter。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
// 返回：没有返回值。
// 过程：函数里会调用 FluDigitalFilterBy。
void CTubeAmplifyData::FluDigitalFilter(CTubeInfo* pTubeInfo,CPtrArray* pFilterItem,CDataAnalysisPCR* pAlgorithm, int iDivideFlag)
{
	FluDigitalFilterBy(pTubeInfo,pFilterItem,1,pAlgorithm, iDivideFlag);
}

// 进行斜率和基线数据调整
// 函数 CTubeAmplifyData::FluoAdjustBaseline
// 作用：执行FluoAdjustBaseline。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetPointCout、FluCopyTo、CalcCycleOfMaxMOTRatio、GetTargetCount、GetTargetInfo、GetChannel。
void CTubeAmplifyData::FluoAdjustBaseline(CTubeInfo* pTubeInfo, CDataAnalysisPara* pAnalysisPara,CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity)
{
	int nCycleCount = GetPointCout();
	// 起峰检查的入口。输入是中值滤波后的荧光，不是最终的 DeltaRn。
	// 已经收集的点数少于 8 时直接返回，不会调用 IsPeakAml。
	// 这时起峰标志保持默认值“没有起峰”。点数如果仍大于 3，后面会把 DeltaRn 整段写成 0。
	FluCopyTo(m_nChannelCount, nCycleCount, m_pFluFilterMedian, m_pFluBaselineAdjust);
	if(nCycleCount < 8)
	{
		return;
	}

	double *pDTempX = new double[nCycleCount];
	if(NULL == pDTempX)
	{
		goto FNAD_END;
	}
	double *pDTempY = new double[nCycleCount];
	if(NULL == pDTempY)
	{
		goto FNAD_END;
	}
	double *pDReturn = new double[nCycleCount];
	if(NULL == pDReturn)
	{
		goto FNAD_END;
	}

	int iCycleOfMaxMOTRatio = CalcCycleOfMaxMOTRatio(nCycleCount, pTurbidity, pAlgorithm);
	if (iCycleOfMaxMOTRatio < 5)
		iCycleOfMaxMOTRatio = nCycleCount;

	int iDyeCount = pTubeInfo->GetTargetCount();
	for(int i = 0;i < iDyeCount;++i)
	{
		CDyeTargetInfo* pDyeInfo = pTubeInfo->GetTargetInfo(i);
		if(NULL == pDyeInfo || pDyeInfo->GetChannel() == pTurbidity->GetChannelMOT() || !pDyeInfo->GetBeSelected())
			continue;

		int iChannelNo = pDyeInfo->GetChannel() - 1;
		GetChannelFlu(FLU_FILTER_MEDIAN, iChannelNo, nCycleCount, pDTempX, pDTempY);

		//if(pTurbidity->UseCalibrate(pDyeInfo->GetChannel()))
		{
			int iCurStart = 3;
			int iCurEnd = 8;
			BOOL bHasCt = FALSE;
			BOOL bChangeBase = FALSE;

			tagAnaAmplifyPara* pAmplifyPara = pAnalysisPara->GetAmplifyParaBy(pDyeInfo->GetTargetName(),pDyeInfo->GetDyeName(),pDyeInfo->GetChannel());
			if(NULL == pAmplifyPara)
			{
				pAmplifyPara = pAnalysisPara->GetAmplifyParaBy(iChannelNo);
			}
			if(NULL != pAmplifyPara)
			{
				CPeakAmlCheckParam peakAmlChkParam;
				double dSndDrvCt = 0;
				// 这里只记录有没有起峰，以及尖峰位置。不在这里写阳性或阴性。
				// 有起峰时，用尖峰位置确定自动基线。没有起峰时，改用“无 Ct”的基线区间。
				// 浊度校正通道本身跳过，不参与起峰判断。
				bHasCt = pAlgorithm->IsPeakAml(pDTempX,pDTempY,nCycleCount, peakAmlChkParam, dSndDrvCt);
				pDyeInfo->SetHasSndDrvCt(bHasCt);
				pDyeInfo->SetSndDrvCt(dSndDrvCt);

				if(pAmplifyPara->bAutoBaseline)
				{
					bChangeBase = TRUE;
					// 需要进行数据滤波
					pAlgorithm->DigitalFilter(pDTempY, pDReturn, nCycleCount,CDataAlgorithmPCR::FILTERTYPE_MEDIAN, 5);
					memcpy(pDTempY, pDReturn, sizeof(double) * nCycleCount);
					for (int i=0; i<3; ++i)
					{
						pAlgorithm->KdsptForwardMBackN_New(nCycleCount, pDTempY, pDReturn, 2, 2);
						memcpy(pDTempY, pDReturn,sizeof(double) * nCycleCount);
					}

					if(bHasCt)
					{
						pAlgorithm->CalcAutoBaselinePosBySndDrvCt(dSndDrvCt, nCycleCount,pDTempX,pDTempY,iCurStart,iCurEnd);
						if (iCurEnd - iCurStart < dSndDrvCt / 2)
						{
							iCurStart = iCurEnd - int(dSndDrvCt / 2);
							if (iCurStart < 1)
							{
								iCurStart = 1;
							}
						}

						if (iCurEnd > iCycleOfMaxMOTRatio)
							iCurEnd = iCycleOfMaxMOTRatio;
					}
					else
					{
						iCurStart = 1;
						iCurEnd = nCycleCount;
						pAlgorithm->CalcBaselinePosOfNoCt(nCycleCount, pDTempX, pDTempY, iCurStart, iCurEnd);
						if (nCycleCount > 20 && iCurEnd - iCurStart > nCycleCount*2/3)
						{
							iCurStart = iCurEnd - nCycleCount*2/3;
						}
					}
				}
				else
				{
					iCurStart = pAmplifyPara->iBaselineStart;
					iCurEnd = pAmplifyPara->iBaselineEnd;
				}
			}

			// 根据基线区间进行曲线矫正
			if (bChangeBase)
			{
				GetChannelFlu(FLU_FILTER_MEDIAN, iChannelNo, nCycleCount, pDTempX, pDTempY);
			}
			pAlgorithm->AdjustFluValueByBaseline(nCycleCount,pDTempX,pDTempY,iCurStart,iCurEnd);
			pDyeInfo->SetBaselineStart(iCurStart);
			pDyeInfo->SetBaselineEnd(iCurEnd);
		}

		SetChannelFlu(FLU_BASELINE_ADJUST,iChannelNo,nCycleCount,pDTempY);
		SetChannelFlu(FLU_FILTER,iChannelNo,nCycleCount,pDTempY);
	}

FNAD_END:
	if(NULL != pDTempX)
	{
		delete [] pDTempX;
	}
	if(NULL != pDTempY)
	{
		delete [] pDTempY;
	}
	if(NULL != pDReturn)
	{
		delete [] pDReturn;
	}

	return;

}

// 函数 CTubeAmplifyData::CalcCycleOfMaxMOTRatio
// 作用：计算CalcCycleOfMaxMOTRatio。
// 参数：iCycleCount：整数；pTurbidity：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetChannelFlu、GetChannelMOT、CalcCycleOfMaxMOTRatioBy、GetMinRatio。
int CTubeAmplifyData::CalcCycleOfMaxMOTRatio(int iCycleCount, CCalibrateParaTurbidity* pTurbidity, CDataAnalysisPCR* pAlgorithm)
{
	double *pdXValue = new double[iCycleCount];
	double* pdYValue = new double[iCycleCount];
	GetChannelFlu(FLU_TURBIDITY, pTurbidity->GetChannelMOT() - 1, iCycleCount, pdXValue, pdYValue);
	int iCycleMOT = pAlgorithm->CalcCycleOfMaxMOTRatioBy(iCycleCount, pdXValue, pdYValue, pTurbidity->GetMinRatio());

	delete pdXValue;
	delete pdYValue;

	return iCycleMOT;
}


// 函数 CTubeAmplifyData::FluTurbidityAdjust
// 作用：执行FluTurbidityAdjust。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetPointCout、GetChannelMOT、CalcAllCtPosBySndDerivative、CalcFluoDescendPosByCtAndMOT、GetTargetCount、GetTargetInfo。
void CTubeAmplifyData::FluTurbidityAdjust(CTubeInfo* pTubeInfo,CCalibrateParaTurbidity* pTurbidity,CDataAnalysisPCR* pAlgorithm)
{
	int nCycleCount = GetPointCout();
	if(NULL == pTurbidity || nCycleCount < 8)
	{
		return;
	}

	int nChannelMOT = pTurbidity->GetChannelMOT() - 1;
	if(nChannelMOT >= m_nChannelCount || nChannelMOT < 0)
	{
		return;
	}

	double *pdXValue = new double[nCycleCount];
	if(NULL == pdXValue)
	{
		goto FTA_END;
	}
	double *pdYValue = new double[nCycleCount];
	if(NULL == pdYValue)
	{
		goto FTA_END;
	}

	// 计算滤波后的全部通道Ct值，并找出扩增后平台期开始位置
	CalcAllCtPosBySndDerivative(pTubeInfo, pTurbidity->GetChannelMOT(), pAlgorithm);
	int iStartDescendPos = CalcFluoDescendPosByCtAndMOT(pTubeInfo, nCycleCount, pAlgorithm);

	double *pdReturnY = new double[nCycleCount];
	if(NULL == pdReturnY)
	{
		goto FTA_END;
	}

	int iDyeCount = pTubeInfo->GetTargetCount();
	for(int i = 0;i < iDyeCount;++i)
	{
		CDyeTargetInfo* pDyeInfo = pTubeInfo->GetTargetInfo(i);
		if(!pDyeInfo->GetBeSelected())
		{
			continue;
		}
		if(!pTurbidity->UseCalibrate(pDyeInfo->GetChannel()))
		{
			continue;
		}

		int iChannelNo = pDyeInfo->GetChannel() - 1;
		GetChannelFlu(FLU_BASELINE_ADJUST,iChannelNo,nCycleCount,pdXValue,pdYValue);

		//计算浊度调整值1
		double dAjustRatio = pTurbidity->GetAdjustRatio(pDyeInfo->GetDyeName());
		pAlgorithm->CalcFluTurbidityAdjust(iStartDescendPos, int(pDyeInfo->GetSndDrvCt()), dAjustRatio,nCycleCount,pdXValue,pdYValue,pdReturnY);
		SetChannelFlu(FLU_TURBIDITY,iChannelNo,nCycleCount,pdReturnY);
	}


	if(NULL != pdReturnY)
	{
		delete [] pdReturnY;
	}

FTA_END:
	if(NULL != pdXValue)
	{
		delete [] pdXValue;
	}
	if(NULL != pdYValue)
	{
		delete [] pdYValue;
	}
}

// 函数 CTubeAmplifyData::CalcAllCtPosBySndDerivative
// 作用：计算CalcAllCtPosBySndDerivative。
// 参数：pTubeInfo：指针，指向调用方传入的对象；iChannelMOT：整数；pAlgorithm：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetPointCout、SAFE_DELETE、GetTargetCount、GetTargetInfo、GetBeSelected、GetChannel。
void CTubeAmplifyData::CalcAllCtPosBySndDerivative(CTubeInfo* pTubeInfo, int iChannelMOT, CDataAnalysisPCR* pAlgorithm)
{
	int nCycleCount = GetPointCout();
	double *pdXValue = new double[nCycleCount];
	double* pdYValue = new double[nCycleCount];
	if(NULL == pdXValue || pdYValue == NULL)
	{
		SAFE_DELETE(pdXValue);
		SAFE_DELETE(pdYValue);
		return;
	}

	int iDyeCount = pTubeInfo->GetTargetCount();
	for(int i = 0;i < iDyeCount;++i)
	{
		CDyeTargetInfo* pDyeInfo = pTubeInfo->GetTargetInfo(i);
		if(!pDyeInfo->GetBeSelected())
			continue;
		if(pDyeInfo->GetChannel() == iChannelMOT)
			continue;

		int iChannelNo = pDyeInfo->GetChannel() - 1;
		GetChannelFlu(FLU_BASELINE_ADJUST, iChannelNo, nCycleCount, pdXValue, pdYValue);

		//double dCt = pAlgorithm->CalcCtPos(nCycleCount, pdXValue, pdYValue);
		//pDyeInfo->SetSndDrvCt(dCt);
		double dCt = pDyeInfo->GetSndDrvCt();

		int iCycleStart = -1;
		if (dCt > 0)
		{
			iCycleStart = pAlgorithm->FindStartPlateauCycle(nCycleCount, pdXValue, pdYValue, dCt);
		}
		pDyeInfo->SetCycleOfPlateau(iCycleStart);
	}

	delete pdXValue;
	delete pdYValue;
}

// 函数 CTubeAmplifyData::CalcFluoDescendPosByCtAndMOT
// 作用：计算CalcFluoDescendPosByCtAndMOT。
// 参数：pTubeInfo：指针，指向调用方传入的对象；iCycleOfMOT：整数；pAlgorithm：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetTargetCount、GetTargetInfo、GetCycleOfPlateau。
int CTubeAmplifyData::CalcFluoDescendPosByCtAndMOT(CTubeInfo* pTubeInfo, int iCycleOfMOT, CDataAnalysisPCR* pAlgorithm)
{
	int iStartDecend = iCycleOfMOT;

	int iDyeCount = pTubeInfo->GetTargetCount();
	for(int i = 0;i < iDyeCount;++i)
	{
		CDyeTargetInfo* pDyeInfo = pTubeInfo->GetTargetInfo(i);
		if (pDyeInfo->GetCycleOfPlateau() <= 0)
			continue;

		if (iStartDecend > pDyeInfo->GetCycleOfPlateau())
			iStartDecend = pDyeInfo->GetCycleOfPlateau();
	}

	return iStartDecend;
}


// 函数 CTubeAmplifyData::FluNormalizeAndDeltaRn
// 作用：执行FluNormalizeAndDeltaRn。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetPointCout、GetTargetCount、GetTargetInfo、GetBeSelected、GetChannel、GetChannelFlu。
void CTubeAmplifyData::FluNormalizeAndDeltaRn(CTubeInfo* pTubeInfo,CDataAnalysisPara* pAnalysisPara,CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity)
{
	int nCycleCount = GetPointCout();
	if(nCycleCount < 1)
	{
		return;
	}

	int iDyeCount = pTubeInfo->GetTargetCount();
	double *pDTempX = new double[nCycleCount];
	if(NULL == pDTempX)
	{
		goto FNAD_END;
	}
	double *pDTempY = new double[nCycleCount];
	if(NULL == pDTempY)
	{
		goto FNAD_END;
	}
	double *pDReturn = new double[nCycleCount];
	if(NULL == pDReturn)
	{
		goto FNAD_END;
	}

	for(int i = 0;i < iDyeCount;++i)
	{
		CDyeTargetInfo* pDyeInfo = pTubeInfo->GetTargetInfo(i);
		if(NULL == pDyeInfo || !pDyeInfo->GetBeSelected() || pDyeInfo->GetChannel() == 6)
		{
			continue;
		}

		int iChannelNo = pDyeInfo->GetChannel() - 1;
		GetChannelFlu(FLU_FILTER,iChannelNo,nCycleCount,pDTempX,pDTempY);

		if(nCycleCount > 3 && pAlgorithm->CanNormalize(nCycleCount))
		{
			int iCurStart = 3;
			int iCurEnd = 8;
			BOOL bHasCt = FALSE;

			tagAnaAmplifyPara* pAmplifyPara = pAnalysisPara->GetAmplifyParaBy(pDyeInfo->GetTargetName(),pDyeInfo->GetDyeName(),pDyeInfo->GetChannel());
			if(NULL == pAmplifyPara)
			{
				pAmplifyPara = pAnalysisPara->GetAmplifyParaBy(iChannelNo);
			}
			if(NULL != pAmplifyPara)
			{
				if(pAmplifyPara->bAutoBaseline)
				{
					double dSndDrvCt = pDyeInfo->GetSndDrvCt();
					bHasCt = pDyeInfo->HasSndDrvCt();
					if (bHasCt)
					{
						pAlgorithm->CalcAutoBaselinePosBySndDrvCt(dSndDrvCt, nCycleCount,pDTempX,pDTempY,iCurStart,iCurEnd);
					}
					else
					{
						iCurStart = 1;
						iCurEnd = nCycleCount;
						pAlgorithm->CalcBaselinePosOfNoCt(nCycleCount, pDTempX, pDTempY, iCurStart, iCurEnd);
						if (nCycleCount > 20 && iCurEnd - iCurStart > nCycleCount*2/3)
						{
							iCurStart = iCurEnd - nCycleCount*2/3;
						}
					}
				}
				else
				{
					iCurStart = pAmplifyPara->iBaselineStart;
					iCurEnd = pAmplifyPara->iBaselineEnd;
				}

			}

			if (pTurbidity->UseCalibrate(pDyeInfo->GetChannel()))
			{
				// 处理基线及基线前的数据
				for (int x=iCurEnd; x>0; x--)
				{
					if (x>= nCycleCount)
					{
						continue;
					}
					pDTempY[x-1] = pDTempY[iCurEnd-1] + (pDTempY[x-1]-pDTempY[iCurEnd-1]) * 0.1;
				}

				if (!bHasCt)
				{
					for (int x=iCurEnd; x<nCycleCount; x++)
					{
						pDTempY[x] = pDTempY[iCurEnd-1] + (pDTempY[x]-pDTempY[iCurEnd-1]) * 0.1;
					}
				}
			}
			SetChannelFlu(FLU_FILTER,iChannelNo,nCycleCount,pDTempY);

			//pAlgorithm->AdjustFluValueByBaseline(nCycleCount,pDTempX,pDTempY,iCurStart,iCurEnd);
			double dAverage = pAlgorithm->CalcBaselineAverage(nCycleCount,pDTempX,pDTempY,iCurStart,iCurEnd);

			//归一化处理1
			pAlgorithm->CalcNormalize(nCycleCount,pDTempY,pDReturn,dAverage);
			SetChannelFlu(FLU_NORMALIZATE,iChannelNo,nCycleCount,pDReturn);

			//DeltaRn处理1
			// DeltaRn 算完后按起峰标志改写，这一步决定后面能不能找到 Ct。
			// 有起峰：基线结束之前的点写成 0，只保留起峰之后的上升段。
			// 没有起峰：整段 DeltaRn 写成 0。荧光阈值找不到交点，Ct 失败，通道记阴性。
			// 点数不大于 3，或者不能做归一化时，不进入这里，DeltaRn 先保留滤波曲线。
			pAlgorithm->CalcDeltaRn(nCycleCount, pDTempY, pDReturn, dAverage);
			
			if (bHasCt)
			{
				for (int i=0; i<iCurEnd; i++)// 根据Atila李佳薇要求，将平台期的数据都置零
				{
					pDReturn[i] = 0;
				}
			}
			else // 2026-7-9 根据客户要求将无Ct的DeltaRn数据Y值都设置为0
			{
				for (int i=0; i<nCycleCount; i++)
				{
					pDReturn[i] = 0;
				}
			}
			SetChannelFlu(FLU_DELTARN, iChannelNo, nCycleCount, pDReturn);
		}
		else
		{
			//保存归一化数据
			SetChannelFlu(FLU_NORMALIZATE,iChannelNo,nCycleCount,pDTempY);
			//保存DeltaRn数据
			SetChannelFlu(FLU_DELTARN,iChannelNo,nCycleCount,pDTempY);
		}
	}

FNAD_END:
	if(NULL != pDTempX)
	{
		delete [] pDTempX;
	}
	if(NULL != pDTempY)
	{
		delete [] pDTempY;
	}
	if(NULL != pDReturn)
	{
		delete [] pDReturn;
	}

	return;
}

// 函数 CTubeAmplifyData::CalcFluDataByCtAndMOT
// 作用：计算CalcFluDataByCtAndMOT。
// 参数：nChannelNo：整数；nStartNo：整数；nCycleCount：整数；pdYValue；dChangedRatio：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTubeAmplifyData::CalcFluDataByCtAndMOT(int nChannelNo, int nStartNo, int nCycleCount, double* pdYValue, double dChangedRatio)
{
	double dStartBase = pdYValue[nStartNo];
	double dCalcValue;

	for (int j=nStartNo+1; j<nCycleCount; j++)
	{
		if (pdYValue[j] > dStartBase)
		{
			dStartBase = pdYValue[j];
		}
		else
		{
			dCalcValue = dStartBase + (pdYValue[j] - dStartBase) * dChangedRatio;
			m_pFluTuibitidy[nChannelNo][j] = dCalcValue;
		}
	}
}

// 生成某个指标的Ct
// 计算一个通道的 Ct。只用已经收集到的点数，不要求凑满计划循环数。
// 当前分析固定走插值法。插值失败、结果不是数字、小于 1 或大于当前点数时，Ct 改成当前点数。
// 改成当前点数的含义是“没有有效 Ct”。阴阳性判断看到 Ct 大于或等于点数，就记阴性。
double CTubeAmplifyData::GenerateCt(eDataType nType, eMethodCalculateCt nMethod, tagAnaAmplifyPara* pAmplifyPara, CDataAnalysisPCR* pAlgorithm)
{
	double dReturn = 0.0;
	eMethodCalculateCt nCurMethod = nMethod;
	if (nCurMethod == METHOD_CT_USER)
	{
		nCurMethod = pAmplifyPara->nMethodCt;
	}

	int nCycleCount = GetPointCout();
	double *pdTempX = new double[nCycleCount];
	double *pdTempY = new double[nCycleCount];
	GetChannelFlu(nType, pAmplifyPara->iChannelNo-1, nCycleCount, pdTempX, pdTempY);

	if(METHOD_CT_SNDDEV == nCurMethod)	// 二阶导数法
	{
		BOOL bAble = pAlgorithm->AbleToCalculateCt(nCycleCount, pdTempX, pdTempY, nType == FLU_NORMALIZATE);
		if(bAble)
		{
			dReturn = pAlgorithm->GenerateCtOfSndDerivative(nCycleCount, pdTempX, pdTempY);
		}
	}
	else if(METHOD_CT_SPLINE == nCurMethod)	// 插值法
	{
		dReturn = GenerateCtOfSpline(nCycleCount, pdTempX, pdTempY, pAmplifyPara, pAlgorithm,nType);
	}
	else
	{
		ASSERT(FALSE);
	}

	delete [] pdTempX;
	delete [] pdTempY;

	if(_isnan(dReturn))
	{
		dReturn = nCycleCount;
	}

	// 没有有效交点时不要保留 0。统一改成当前点数，让上层用“Ct >= 点数”识别失败。
	//如果是异常值，Ct值设置为数据点数
	if(dReturn < 1 || dReturn > nCycleCount)
	{
		dReturn = nCycleCount;
	}

	return dReturn;
}

// 插值法使用的荧光阈值。DeltaRn 曲线用 dCalcDeltaRnThreshold，归一化曲线用 dCalcNormalizeThreshold。
// 这个阈值只负责找交点，不直接决定阳性或阴性。
// 交点不在 1 到当前点数之间时，返回当前点数，表示 Ct 失败。
// 函数 CTubeAmplifyData::GenerateCtOfSpline
// 作用：计算GenerateCtOfSpline。
// 参数：iCycleCount：整数；pdInputX；pdInputY；pAmplifyPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；nType：整数。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CTubeAmplifyData::GenerateCtOfSpline(int iCycleCount, double *pdInputX, double *pdInputY, tagAnaAmplifyPara* pAmplifyPara, CDataAnalysisPCR* pAlgorithm,eDataType nType)
{
	//使用插值法，如果 阈值在数据点纵坐标上限、下限之外，则输出的Ct值为 数据点个数（N/A）
	double dThreshold = pAmplifyPara->dCalcNormalizeThreshold;
	if(FLU_DELTARN == nType)
	{
		dThreshold = pAmplifyPara->dCalcDeltaRnThreshold;
	}

	double dReturn = iCycleCount;
	dReturn = pAlgorithm->GenerateCtOfSpline(iCycleCount, pdInputX, pdInputY, dThreshold);
	if(dReturn > iCycleCount || dReturn < 1)
	{
		dReturn = iCycleCount;
	}

	return dReturn;
}

// 为自动基线生成Ct
// 函数 CTubeAmplifyData::GenerateAutoSplineThreshold
// 作用：计算GenerateAutoSplineThreshold。
// 参数：nType：整数；iChannel：整数；pAlgorithm：指针，指向调用方传入的对象。
// 返回：返回一个小数。
// 过程：函数里会调用 GetPointCout、GetChannelFlu、IsPeakAml、GenerateCtOfSndDerivative、Spline。
double CTubeAmplifyData::GenerateAutoSplineThreshold(eDataType nType,int iChannel,CDataAnalysisPCR* pAlgorithm)
{
	double dReturn = 0;

	int nCycleCount = GetPointCout();
	if(nCycleCount < 1)
	{
		return dReturn;
	}

	CPeakAmlCheckParam peakAmlChkParam;

	double *pdTempX = new double[nCycleCount];
	if(NULL == pdTempX)
	{
		goto GAST_END;
	}
	double *pdTempY = new double[nCycleCount];
	if(NULL == pdTempY)
	{
		goto GAST_END;
	}

	//GetChannelFlu(nType,iChannel - 1,nCycleCount,pdTempX,pdTempY);
	GetChannelFlu(FLU_TURBIDITY,iChannel - 1,nCycleCount,pdTempX,pdTempY);
	double dOrgCt = 0;
	if(pAlgorithm->IsPeakAml(pdTempX,pdTempY,nCycleCount,peakAmlChkParam, dOrgCt))
	{
		double dReturnCt = pAlgorithm->GenerateCtOfSndDerivative(nCycleCount,pdTempX,pdTempY);
		if (dReturnCt > 1 && dReturnCt <= nCycleCount) // 找到Ct
		{
			GetChannelFlu(nType,iChannel-1, nCycleCount, pdTempX, pdTempY);
			pAlgorithm->Spline(pdTempX,pdTempY,nCycleCount,dReturnCt,dReturn);
		}
	}

GAST_END:
	if(NULL != pdTempX)
	{
		delete [] pdTempX;
	}
	if(NULL != pdTempY)
	{
		delete [] pdTempY;
	}
	return dReturn;
}

// 函数 CTubeAmplifyData::BeAllAllocated
// 作用：判断BeAllAllocated是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 CTubeData::BeAllAllocated。
BOOL CTubeAmplifyData::BeAllAllocated()
{
	BOOL bReturn = CTubeData::BeAllAllocated();
	if (!bReturn)
	{
		return FALSE;
	}
	if(NULL == m_pFluNormalize)
	{
		return FALSE;
	}
	if(NULL == m_pFluDeltaRn)
	{
		return FALSE;
	}

	//if(NULL == m_pLogFluNormalize)
	//{
	//	return FALSE;
	//}
	//if(NULL == m_pLogFluDeltaRn)
	//{
	//	return FALSE;
	//}

	//if(NULL == m_pFluAfterCorrect)
	//{
	//	return FALSE;
	//}

	//if(NULL == m_pFluNormNoCP)
	//{
	//	return FALSE;
	//}
	//if(NULL == m_pFluRnNoCP)
	//{
	//	return FALSE;
	//}

	return TRUE;
}

//*****************************************************************************************************************
// 熔解段荧光数据
// 函数 CTubeMeltData::CTubeMeltData
// 作用：执行CTubeMeltData。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTubeMeltData::CTubeMeltData(void)
{
	m_pTem = NULL;
	m_pNormalize = NULL;
	m_pFstNegReciprocal = NULL;
	m_pGainData = NULL;
}

// 函数 CTubeMeltData::~CTubeMeltData
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CTubeMeltData::~CTubeMeltData(void)
{
	DeleteAll();
}

// 函数 CTubeMeltData::AllocateMemory
// 作用：执行AllocateMemory。
// 参数：nChannelCount：整数。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、BeAllAllocated。
BOOL CTubeMeltData::AllocateMemory(int nChannelCount)
{
	CTubeData::AllocateMemory(nChannelCount);

	DeleteAll();
	m_nChannelCount = nChannelCount;
	
	m_pTem = new vector<double>;
	m_pNormalize = new vector<double>[m_nChannelCount];

	m_pFstNegReciprocal = new vector<double>[m_nChannelCount];
	m_pGainData = new vector<double>[m_nChannelCount];

	return BeAllAllocated();
}

// 函数 CTubeMeltData::BeAllAllocated
// 作用：判断BeAllAllocated是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 CTubeData::BeAllAllocated。
BOOL CTubeMeltData::BeAllAllocated()
{
	BOOL bReturn = CTubeData::BeAllAllocated();
	if (!bReturn)
	{
		return FALSE;
	}
	if(NULL == m_pTem)
	{
		return FALSE;
	}
	if(NULL == m_pNormalize)
	{
		return FALSE;
	}

	if(NULL == m_pFstNegReciprocal)
	{
		return FALSE;
	}
	if(NULL == m_pGainData)
	{
		return FALSE;
	}

	return TRUE;
}

// 函数 CTubeMeltData::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTubeMeltData::DeleteAll()
{
	m_nChannelCount = 0; 

	if(NULL != m_pTem)
	{
		delete m_pTem;
		m_pTem = NULL;
	}

	if(NULL != m_pNormalize)
	{
		delete [] m_pNormalize;
		m_pNormalize = NULL;
	}

	if(NULL != m_pFstNegReciprocal)
	{
		delete [] m_pFstNegReciprocal;
		m_pFstNegReciprocal = NULL;
	}

	if(NULL != m_pGainData)
	{
		delete [] m_pGainData;
		m_pGainData = NULL;
	}
	return;
}


// 函数 CTubeMeltData::AddOriginalData
// 作用：创建或加入AddOriginalData。
// 参数：nChannelNo：整数；nYValue：整数；dTem：小数。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、GetFluoDataAutoAdjust、GetAt、GetFluoDataMaxLimited、GetFluoDataAdjustLimited、GetDataNum。
void CTubeMeltData::AddOriginalData(int nChannelNo,UINT nYValue,double dTem)
{
	if(nChannelNo < 0 || nChannelNo >= m_nChannelCount)
	{
		return;
	}

	CPublicInfo* pInfo = CPublicInfo::GetInstance();
	if (pInfo->GetFluoDataAutoAdjust())
	{
		BOOL bAutoAdjust = m_arrayAutoAdjust.GetAt(nChannelNo);
		if (bAutoAdjust)
		{
			nYValue = pInfo->GetFluoDataMaxLimited(); // 2025072 按常江波要求荧光饱和后的数据改为最大值60000
			//if (nYValue < pInfo->GetFluoDataAdjustLimited())
			//{
			//}
		}
		else
		{
			int iDafaCount = GetDataNum(nChannelNo);
			if (nYValue == pInfo->GetFluoDataMaxLimited())
			{
				m_arrayAutoAdjust.SetAt(nChannelNo, TRUE);
			}
			else if (iDafaCount > 0)
			{
				UINT nLastValue = GetFluYValueBy(FLU_ORIGINAL, nChannelNo, iDafaCount-1);
				if (nYValue+40000 < nLastValue)
				{
					m_arrayAutoAdjust.SetAt(nChannelNo, TRUE);
					nYValue = pInfo->GetFluoDataMaxLimited();
					//nYValue += pInfo->GetFluoDataMaxLimited();
				}
			}
		}
	}

	CTubeData::AddOriginalData(nChannelNo, nYValue);
	if(0 == nChannelNo)	//防止温度数据保存多次
	{
		(*m_pTem).push_back(dTem);
	}
	
	m_pNormalize[nChannelNo].push_back(nYValue);
	m_pFstNegReciprocal[nChannelNo].push_back(nYValue);
	m_pGainData[nChannelNo].push_back(nYValue);

	return;
}

// 函数 CTubeMeltData::GetFluYValueBy
// 作用：读取GetFluYValueBy。
// 参数：nType：整数；nChannelNo：整数；nPointNo：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 CTubeData::GetFluYValueBy。
double CTubeMeltData::GetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo)
{
	double dReturn = 0;
	switch(nType)
	{
	case MELT_NORMALIZE:
		dReturn = m_pNormalize[nChannelNo][nPointNo];
		break;
	case MELT_FSTNEGRECIPROCAL:
		dReturn = m_pFstNegReciprocal[nChannelNo][nPointNo];
		break;
	case MELT_GAINDATA:
		dReturn = m_pGainData[nChannelNo][nPointNo];
		break;
	default:
		dReturn = CTubeData::GetFluYValueBy(nType, nChannelNo, nPointNo);
		break;
	}
	return dReturn;
}

// 函数 CTubeMeltData::SetFluYValueBy
// 作用：设置SetFluYValueBy。
// 参数：nType：整数；nChannelNo：整数；nPointNo：整数；dYValue：小数。
// 返回：没有返回值。
// 过程：函数里会调用 CTubeData::SetFluYValueBy。
void CTubeMeltData::SetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo, double dYValue)
{
	switch(nType)
	{
	case MELT_NORMALIZE:
		m_pNormalize[nChannelNo][nPointNo] = dYValue;
		break;
	case MELT_FSTNEGRECIPROCAL:
		m_pFstNegReciprocal[nChannelNo][nPointNo] = dYValue;
		break;
	case MELT_GAINDATA:
		m_pGainData[nChannelNo][nPointNo] = dYValue;
		break;
	default:
		CTubeData::SetFluYValueBy(nType, nChannelNo, nPointNo, dYValue);
		break;
	}
}

// 函数 CTubeMeltData::GetCycleX
// 作用：读取GetCycleX。
// 参数：nCycleCount：整数；pdValueX；bConstantPCR：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 size。
void CTubeMeltData::GetCycleX(int nCycleCount,double* pdValueX,BOOL bConstantPCR)
{
	if(NULL == pdValueX || NULL == m_pTem)
	{
		return;
	}
	if(nCycleCount < 1 || nCycleCount > (*m_pTem).size())
	{
		return;
	}

	for(int i = 0;i < nCycleCount;++i)
	{
		pdValueX[i] = (*m_pTem)[i];
	}
	return;
}

// 函数 CTubeMeltData::GetCycleX
// 作用：读取GetCycleX。
// 参数：iCycleId：整数；bConstantPCR：是或否。
// 返回：返回一个小数。
// 过程：函数里会调用 size。
double CTubeMeltData::GetCycleX(int iCycleId, BOOL bConstantPCR)
{
	if(NULL == m_pTem)
	{
		return 0;
	}
	if(iCycleId < 0 || iCycleId >= (*m_pTem).size())
	{
		return 0;
	}

	return (*m_pTem)[iCycleId];
}

// 函数 CTubeMeltData::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 size、Write、data。
BOOL CTubeMeltData::WriteFile(CFile* pFile)
{
	if(NULL == pFile || NULL == m_pTem)
	{
		return FALSE;
	}

	CTubeData::WriteFile(pFile);

	int iCount = (*m_pTem).size();
	pFile->Write((const char*)&iCount,sizeof(int));
	pFile->Write((const char*)(*m_pTem).data(),sizeof(double) * iCount);

	return TRUE;
}

// 函数 CTubeMeltData::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 size、push_back、Read。
BOOL CTubeMeltData::ReadFile(CFile* pFile,WORD wVersion)
{
	if(NULL == pFile|| NULL == m_pTem)
	{
		return FALSE;
	}

	if(!CTubeData::ReadFile(pFile,wVersion))
	{
		return FALSE;
	}

	if(wVersion >= wPCRVersion109)
	{
		for(int i = 0;i < m_nChannelCount;++i)
		{
			for(int j = 0;j < m_pFluOriginal[i].size();++j)
			{
				m_pNormalize[i].push_back(m_pFluOriginal[i][j]);
				m_pFstNegReciprocal[i].push_back(m_pFluOriginal[i][j]);
				m_pGainData[i].push_back(m_pFluOriginal[i][j]);
			}
		}

		int iCount = 0;
		pFile->Read(&iCount,sizeof(int));
		if(iCount > 0)
		{
			double* pDTem = new double[iCount];
			if(NULL == pDTem)
			{
				return FALSE;
			}
			pFile->Read(pDTem,sizeof(double) * iCount);

			for (int i = 0;i < iCount;++i)
			{
				(*m_pTem).push_back(pDTem[i]);
			}

			delete [] pDTem;
			pDTem = NULL;
		}
	}

	return TRUE;
}

// 函数 CTubeMeltData::FluDigitalFilter
// 作用：执行FluDigitalFilter。
// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
// 返回：没有返回值。
// 过程：函数里会调用 FluDigitalFilterBy。
void CTubeMeltData::FluDigitalFilter(CTubeInfo* pTubeInfo, CPtrArray* pFilterItem, CDataAnalysisPCR* pAlgorithm, int iDivideFlag)
{
	FluDigitalFilterBy(pTubeInfo, pFilterItem, 2, pAlgorithm, iDivideFlag);
}


