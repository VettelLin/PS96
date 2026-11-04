// 【交接】 PCRCtrlLib\TemperatureData.cpp
// 作用：TemperatureData。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CTemperatureData、DeleteAll、SAFE_DELETE、AllocateMemory、AddOneTempData、push_back、UINT、WriteFile。
#include "StdAfx.h"
#include "TemperatureData.h"
#include "DeclaresPCR.h"

// 函数 CTemperatureData::CTemperatureData
// 作用：执行CTemperatureData。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTemperatureData::CTemperatureData(void)
{
	m_bUseLid = FALSE;
	m_iLidChannelCount = 1;
	m_iChannelCount = 0;
	m_pTimeData = NULL;
	m_pTempData = NULL;

	m_iUpDownFlag = -1;
	m_nTargetChannel1 = 45;
	m_nTargetChannel2 = 0;
	m_nTargetChannel3 = 0;
	m_bSteadyPeriod = FALSE;

	m_iChan1PreTem = 0;
	m_iChan2PreTem = 0;
	m_iChan3PreTem = 0;
}

// 函数 CTemperatureData::~CTemperatureData
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CTemperatureData::~CTemperatureData(void)
{
	DeleteAll();
}

// 函数 CTemperatureData::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SAFE_DELETE。
void CTemperatureData::DeleteAll()
{
	m_iChannelCount = 0;
	SAFE_DELETE(m_pTimeData);

	if (m_pTempData != NULL)
	{
		delete [] m_pTempData;
		m_pTempData = NULL;
	}

	m_iUpDownFlag = -1;

	m_nTargetChannel1 = 45;
	m_nTargetChannel2 = 0;
	m_nTargetChannel3 = 0;
	m_bSteadyPeriod = FALSE;

	m_iChan1PreTem = 0;
	m_iChan2PreTem = 0;
	m_iChan3PreTem = 0;
}

// 函数 CTemperatureData::AllocateMemory
// 作用：执行AllocateMemory。
// 参数：iChannelCount：整数；iLidChannelCount：整数。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll。
BOOL CTemperatureData::AllocateMemory(int iChannelCount, int iLidChannelCount /*= 1*/)
{
	DeleteAll();

	m_iChannelCount = iChannelCount;
	m_iLidChannelCount = iLidChannelCount;
	m_pTimeData = new vector<DWORD>;
	m_pTempData = new vector<UINT>[iChannelCount+iLidChannelCount]; // 保证可以保存热盖温度
	return TRUE;
}

// 函数 CTemperatureData::AddOneTempData
// 作用：创建或加入AddOneTempData。
// 参数：dwTime；nTempCount：整数；pInputTemp：指针，指向调用方传入的对象；bMeltStepRunning：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 push_back、UINT。
void CTemperatureData::AddOneTempData(DWORD dwTime,int nTempCount,UINT* pInputTemp,BOOL bMeltStepRunning /*= FALSE*/)
{
	m_pTimeData->push_back(dwTime);
	for (int i = 0;i < nTempCount;++i)
	{
		if(0 == i && m_nTargetChannel1 > 2000 && !bMeltStepRunning) // 值修正温度通道1的显示数据
		{
			UINT nTemp = pInputTemp[i];
			if (m_iUpDownFlag == 0) // 升温
			{
				if (nTemp > m_nTargetChannel1) // 过温
				{
					/*float fHigh = (nTemp - m_nTargetChannel1) * 0.1f;
					nTemp = m_nTargetChannel1 + UINT(fHigh);*/

					nTemp = m_nTargetChannel1;
					m_bSteadyPeriod = TRUE;
				}
				else if(nTemp < m_iChan1PreTem)
				{
					nTemp = m_iChan1PreTem;
				}
				else if (m_bSteadyPeriod)
				{
					float fHigh = (m_nTargetChannel1 - nTemp) * 0.1f;
					nTemp = m_nTargetChannel1 - UINT(fHigh);
				}
			}
			else if (m_iUpDownFlag == 1) // 降温
			{
				if (nTemp < m_nTargetChannel1) // 低温
				{
					/*float fHigh = (m_nTargetChannel1 - nTemp) * 0.1f;
					nTemp = m_nTargetChannel1 - UINT(fHigh);*/

					nTemp = m_nTargetChannel1;
					m_bSteadyPeriod = TRUE;
				}
				else if(nTemp > m_iChan1PreTem)
				{
					nTemp = m_iChan1PreTem;
				}
				else if (m_bSteadyPeriod)
				{
					float fHigh = (nTemp - m_nTargetChannel1) * 0.1f;
					nTemp = m_nTargetChannel1 + UINT(fHigh);
				}
			}

			if(i < m_iChannelCount + m_iLidChannelCount)
			{
				m_pTempData[i].push_back(nTemp);
			}
		}
		else
		{
			if(i < m_iChannelCount + m_iLidChannelCount)
			{
				m_pTempData[i].push_back(pInputTemp[i]);
			}
		}
	}
}

// 函数 CTemperatureData::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 Write、size、data。
BOOL CTemperatureData::WriteFile(CFile* pFile)
{
	pFile->Write((const char*)&m_iChannelCount, sizeof(int));
	pFile->Write((const char*)&m_bUseLid, sizeof(BOOL));
	pFile->Write((const char*)&m_iLidChannelCount, sizeof(int));


	if (m_pTimeData != NULL)
	{
		int iDataCount = m_pTimeData->size();
		pFile->Write((const char*)&iDataCount, sizeof(int));
		pFile->Write((const char*)m_pTimeData->data(), sizeof(DWORD) * iDataCount);
	}

	if (m_pTempData != NULL)
	{
		for (int i=0; i<m_iChannelCount+m_iLidChannelCount; i++)
		{
			int iDataCount = m_pTempData[i].size();
			pFile->Write((const char*)&iDataCount, sizeof(int));
			pFile->Write((const char*)m_pTempData[i].data(), sizeof(UINT) * iDataCount);
		}
	}

	return TRUE;
}

// 函数 CTemperatureData::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、Read、AllocateMemory、push_back、SAFE_DELETE。
BOOL CTemperatureData::ReadFile(CFile* pFile, WORD wVersion)
{
	DeleteAll();

	int iKindCount = 0;
	if (wVersion <= wPCRVersion106)
	{
		pFile->Read(&iKindCount, sizeof(int));
		if (iKindCount == 0)
			return TRUE;

		AllocateMemory(iKindCount - 1);	//20220624之前为iKindCount，此时打开旧有的工程文件，再次运行实验会报错（因为温度通道数不对），改为iKindCount - 1能够保持对旧有工程文件的兼容
	}
	else
	{
		pFile->Read(&m_iChannelCount,sizeof(int));
		pFile->Read(&m_bUseLid,sizeof(BOOL));
		pFile->Read(&m_iLidChannelCount,sizeof(int));
		AllocateMemory(m_iChannelCount,m_iLidChannelCount);
		iKindCount = m_iChannelCount + m_iLidChannelCount;
	}

	int iTimeCount = 0;
	pFile->Read(&iTimeCount, sizeof(int));
	DWORD* pTempTime = new DWORD[iTimeCount];
	pFile->Read(pTempTime, sizeof(DWORD)*iTimeCount);
	for (int i=0; i<iTimeCount; i++)
	{
		m_pTimeData->push_back(pTempTime[i]);
	}

	int iTempCount = 0;
	UINT* pTempData = NULL;
	for (int i=0; i<iKindCount; i++)
	{
		pFile->Read(&iTempCount, sizeof(int));

		if (pTempData == NULL)
		{
			pTempData = new UINT[iTempCount];
		}
		pFile->Read(pTempData, sizeof(UINT)*iTempCount);
		for (int k=0; k<iTempCount; k++)
		{
			m_pTempData[i].push_back(pTempData[k]);
		}
	}

	SAFE_DELETE(pTempTime);
	SAFE_DELETE(pTempData);

	return TRUE;
}

// 函数 CTemperatureData::GetCurTemp
// 作用：读取GetCurTemp。
// 参数：nTempChannel：整数；iChannelNo：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
UINT CTemperatureData::GetCurTemp(eTempChannel nTempChannel,int iChannelNo /*= 0*/)
{
	UINT nTemp = 0;
	int iMaxIndex = m_pTempData[0].size() - 1;
	int iCurChannel = iChannelNo; 

	if (nTempChannel == TEMP_CH_LID) // 热盖
	{
		ASSERT(m_bUseLid);
		iCurChannel = m_iChannelCount + iChannelNo;
	}

	if (iCurChannel < m_iLidChannelCount + m_iChannelCount)
	{
		if(iMaxIndex < m_pTempData[iCurChannel].size())	//防止“仪器温度通道数和实验文件里的通道数不一致导致崩溃”，20220707，孙文郎
		{
			nTemp = m_pTempData[iCurChannel][iMaxIndex];
		}
		else
		{
			if(iCurChannel - 1 >= 0 && iMaxIndex < m_pTempData[iCurChannel - 1].size())
			{
				nTemp = m_pTempData[iCurChannel - 1][iMaxIndex];
			}
		}
	}

	return nTemp;
}

// 函数 CTemperatureData::GetCurTempCollectTime
// 作用：读取GetCurTempCollectTime。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
DWORD CTemperatureData::GetCurTempCollectTime()
{
	int iMaxIndex = m_pTempData[0].size() - 1;
	if(iMaxIndex < 0)
	{
		return 0;
	}
	
	return (*m_pTimeData)[iMaxIndex];
}

// 函数 CTemperatureData::HasData
// 作用：判断HasData是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 size。
BOOL CTemperatureData::HasData() 
{ 
	if (m_pTimeData != NULL)
	{
		if (m_pTimeData->size() > 0)
			return TRUE;
	}
	
	if (m_pTempData != NULL)
	{
		if (m_pTempData->size() > 0)
			return TRUE;
	}

	return FALSE;
} 

// 设置控温过程中的目标温度
// 函数 CTemperatureData::SetChannelTarget
// 作用：设置SetChannelTarget。
// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数。
// 返回：没有返回值。
// 过程：函数里会调用 UINT。
void CTemperatureData::SetChannelTarget(float fTemp1, float fTemp2, float fTemp3)
{
	UINT nChannelTemp1 = UINT(fTemp1 * RESOLUTION_TEMP);

	if (m_iUpDownFlag == -1)
	{
		m_iUpDownFlag = 0; // 升温
	}
	else
	{
		if (nChannelTemp1 > m_nTargetChannel1)
		{
			m_iUpDownFlag = 0; // 升温
		}
		else
		{
			m_iUpDownFlag = 1; // 降温
		}
	}

	m_iChan1PreTem = m_nTargetChannel1;
	m_iChan2PreTem = m_nTargetChannel2;
	m_iChan3PreTem = m_nTargetChannel3;

	m_bSteadyPeriod = FALSE;
	m_nTargetChannel1 = UINT(fTemp1 * RESOLUTION_TEMP);
	m_nTargetChannel2 = UINT(fTemp2 * RESOLUTION_TEMP);
	m_nTargetChannel3 = UINT(fTemp3 * RESOLUTION_TEMP);
}

// 函数 CTemperatureData::GetTemDataPtr
// 作用：读取GetTemDataPtr。
// 参数：无。
// 返回：返回指针 vector<UINT>*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
vector<UINT>* CTemperatureData::GetTemDataPtr()
{
	return m_pTempData;
}


// 函数 CTemperatureData::GetDataCount
// 作用：读取GetDataCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
int CTemperatureData::GetDataCount()
{
	return m_pTempData[0].size();
}


// 函数 CTemperatureData::GetTimeData
// 作用：读取GetTimeData。
// 参数：iDataCount：整数；pdValueTime。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTemperatureData::GetTimeData(int iDataCount, double* pdValueTime)
{
	for (int i=0; i<iDataCount; i++)
	{
		pdValueTime[i] = (*m_pTimeData)[i];
	}
}

// 函数 CTemperatureData::GetChannelData
// 作用：读取GetChannelData。
// 参数：nTempChannel：整数；iChannelNo：整数；iDataCount：整数；pdValueTemp。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTemperatureData::GetChannelData(CTemperatureData::eTempChannel nTempChannel, int iChannelNo, int iDataCount, double* pdValueTemp)
{
	UINT nTemp = 0;
	int iCurChannel = iChannelNo; 

	if (nTempChannel == TEMP_CH_LID) // 热盖
	{
		ASSERT(m_bUseLid);
		iCurChannel = m_iChannelCount + iChannelNo;
	}

	if (iCurChannel < m_iLidChannelCount + m_iChannelCount)
	{
		for (int i=0; i<iDataCount; i++)
		{
			pdValueTemp[i] = m_pTempData[iCurChannel][i] / RESOLUTION_TEMP;
		}
	}
}

// 函数 CTemperatureData::GetOneTimeData
// 作用：读取GetOneTimeData。
// 参数：iIndex：整数。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CTemperatureData::GetOneTimeData(int iIndex)
{
	return (*m_pTimeData)[iIndex] / 1000.0;
}

// 函数 CTemperatureData::GetOneTempData
// 作用：读取GetOneTempData。
// 参数：iChannel：整数；iIndex：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 double。
double CTemperatureData::GetOneTempData(int iChannel, int iIndex)
{
	return double(m_pTempData[iChannel][iIndex]) / RESOLUTION_TEMP;
}
