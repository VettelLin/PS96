// 【交接】 PCRInstanceLib\InstancePS96.cpp
// 作用：InstancePS96。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInstancePS96、InitStructurePara、Initialize、FluoSelfcheck、Home、GetInitChanDyeName、clear、GetScanChannelCount。
#include "StdAfx.h"
#include "InstancePS96.h"
#include "ErrorCodeDefine.h"

// 函数 CInstancePS96::CInstancePS96
// 作用：执行CInstancePS96。
// 参数：pComPort：指针，指向调用方传入的对象；CInstancePCR(pComPort；strVersion：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInstancePS96::CInstancePS96(CSerialPortPCR* pComPort, CString strVersion) : CInstancePCR(pComPort, strVersion)
{
	
}

// 函数 CInstancePS96::~CInstancePS96
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInstancePS96::~CInstancePS96(void)
{

}

// 初始化仪器结构参数
// 函数 CInstancePS96::InitStructurePara
// 作用：初始化InitStructurePara。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CInstancePCR::InitStructurePara。
void CInstancePS96::InitStructurePara()
{
	CInstancePCR::InitStructurePara();

	m_sStructurePara.cTempMode = TEMP_MODE_CONSTANT; // 恒温
	m_sStructurePara.cScanOrigin = 1; // 从右上开始扫描
	m_sStructurePara.cSupportMelt = 0; // 不支持熔曲
	m_sStructurePara.wScanOnceTime = 1200;
	m_sStructurePara.cCalibratePara = 1; // 使用浊度校准

	m_sStructurePara.cTempCtrlMaxTime = 120;	//PS96升温20℃（非热盖）用时大约75秒
	m_sStructurePara.cTempLegalGap = 20;	//PS96下位机返回的到温范围为正负1℃，这里默认值设置为正负2℃

	m_sStructurePara.cLidTempTop = 90;
}
  
// 函数 CInstancePS96::Initialize
// 作用：初始化Initialize。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 ReadAllTemp、FluoSelfcheck、Home。
BOOL CInstancePS96::Initialize()
{
	BOOL bReturn = CInstancePCR::Initialize();
	if (bReturn)
	{
		int iHigherCount = 0;
		int iLowerCount = 0;
		BOOL bReachTemp = FALSE;
		int iChannelCount = 6;
		float* pChTemp = new float[iChannelCount];
		if (ReadAllTemp(iChannelCount, pChTemp, bReachTemp))
		{
			for (int i=0; i<iChannelCount; i++)
			{
				if (pChTemp[i] > 85)
					iHigherCount ++;
				else if (pChTemp[i] < 5)
					iLowerCount ++;
			}
		}

		if (iHigherCount >= 2)
			m_eInstanceStatus = INSTANCE_TEMP_HIGH;
		else if(iLowerCount >= 2)
			m_eInstanceStatus = INSTANCE_TEMP_LOW;

		delete pChTemp;

		bReturn = FluoSelfcheck();
		if(bReturn)
		{
			bReturn = Home();
		}
	}

	return bReturn;
}

// 函数 CInstancePS96::GetInitChanDyeName
// 作用：读取GetInitChanDyeName。
// 参数：vecChanDyeName。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、GetScanChannelCount、push_back、_T、strTemp、Format。
int CInstancePS96::GetInitChanDyeName(vector<CString>& vecChanDyeName)
{
	vecChanDyeName.clear();
	int iChanCount = GetScanChannelCount();
	if(iChanCount < 1)
	{
		return -1;
	}
	
	for(int i = 0;i < iChanCount;++i)
	{
		if(0 == i)
		{
			vecChanDyeName.push_back(_T("FAM"));
		}
		else if(1 == i)
		{
			vecChanDyeName.push_back(_T("Cy5")); 
		}
		else if(2 == i)
		{
			vecChanDyeName.push_back(_T("VIC"));
		}
		else if(3 == i)
		{
			vecChanDyeName.push_back(_T("Cy5.5"));
		}
		else if(4 == i)
		{
			vecChanDyeName.push_back(_T("ROX")); 
		}
		else if(5 == i)
		{
			vecChanDyeName.push_back(_T("MOT")); 
		}
		else
		{
			CString strTemp(_T(""));
			strTemp.Format(_T("%d"),i + 1);
			vecChanDyeName.push_back(strTemp);
		}
	}

	return 0;
}

// 函数 CInstancePS96::CalculateExperimentTotalTimeSec
// 作用：计算CalculateExperimentTotalTimeSec。
// 参数：lnkSegItem；bUseLid：是或否；iVolume：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHead、GetTail。
int CInstancePS96::CalculateExperimentTotalTimeSec(CLinkList<CSegItemInfo>& lnkSegItem,BOOL bUseLid,int iVolume)
{
	//使用临时的 整板扫描时间,96孔QPCR默认扫描时间是10.5秒
	double dScanTimeSec = PS96_SCANSEC;
	int iExpTotalSec = 0;

	//计算热盖升温时间
	if(bUseLid)
	{
		iExpTotalSec += PS96_LIDHEATSEC;
	}

	//PS96只有升温，升温速率默认为0.4℃/S，96孔QPCR升降温速率使用2.5℃/S，N16使用5.5℃/S
	float iUpRate = 0.4f;
	float iDownRate = 0.4f;
	float fPreTem = 0,fPreTem2 = 0,fTemMinus = 0,fTemMinus2 = 0,fExistSec = 0,fExistSec2 = 0;

	Node<CSegItemInfo>* pSegNode = lnkSegItem.GetHead();
	Node<CStepItemInfo>* pStepNode = NULL;
	int iSegIdnex = 0,iStepIndex = 0;

	while(NULL != pSegNode)
	{
		CSegItemInfo& segItem = pSegNode->data;
		pStepNode = pSegNode->data.m_lnkStepItemInfo.GetHead();
		iStepIndex = 0;

		while(NULL != pStepNode)
		{
			CStepItemInfo& stepItem = pStepNode->data;

			if(CHECK_ALL_POINT == stepItem.m_eChkType)
			{
				if(0 == iStepIndex)
				{
					if(0 == iSegIdnex)
					{
						fPreTem = 36;
					}
					else
					{
						fPreTem = pSegNode->pPrevious->data.m_lnkStepItemInfo.GetTail()->data.m_fAimTem;
					}
				}
				else
				{
					fPreTem = pStepNode->pPrevious->data.m_fAimTem;
				}

				fTemMinus = stepItem.m_fAimTem - fPreTem;
				if(fTemMinus > 0)
				{
					fExistSec = (WORD)((stepItem.m_fAimTem - fPreTem) / stepItem.m_fIncrement * (6 + dScanTimeSec) + 0.5);
				}

				float fRate = stepItem.m_fRate / 0.1f + 0.05f;
				float ctrlSec = fExistSec * 1.3f + stepItem.m_uiWaitTimeBelowStartTem * 2;

				iExpTotalSec += ctrlSec; 
				iExpTotalSec += stepItem.m_iDelay;
			}
			else
			{
				if(0 == iStepIndex)
				{
					if(0 == iSegIdnex)
					{
						fPreTem = 36;
					}
					else
					{
						fPreTem = pSegNode->pPrevious->data.m_lnkStepItemInfo.GetTail()->data.m_fAimTem;
					}
					fPreTem2 = segItem.m_lnkStepItemInfo.GetTail()->data.m_fAimTem;

					fTemMinus = stepItem.m_fAimTem - fPreTem;
					fTemMinus2 = stepItem.m_fAimTem - fPreTem2;
					if(fTemMinus > 0)
					{
						fExistSec = fTemMinus / iUpRate;
					}
					else
					{
						fExistSec = -fTemMinus / iDownRate;
					}
					if(fTemMinus2 > 0)
					{
						fExistSec2 = fTemMinus2 / iUpRate;
					}
					else
					{
						fExistSec2 = -fTemMinus2 / iDownRate;
					}
					iExpTotalSec += (fExistSec + (segItem.m_iCycleNum - 1) * fExistSec2 + stepItem.m_iDelay * segItem.m_iCycleNum);
				}
				else
				{
					fPreTem = pStepNode->pPrevious->data.m_fAimTem;
					fTemMinus = stepItem.m_fAimTem - fPreTem;
					if(fTemMinus > 0)
					{
						fExistSec = fTemMinus / iUpRate;
					}
					else
					{
						fExistSec = -fTemMinus / iDownRate;
					}
					iExpTotalSec += ((fExistSec + stepItem.m_iDelay) * segItem.m_iCycleNum);
				}
			}

			++iStepIndex;
			pStepNode = pStepNode->pNext;
		}

		++iSegIdnex;
		pSegNode = pSegNode->pNext;
	}

	iExpTotalSec += 20;	//20200609，ps96计算出的总时间偏低

	return iExpTotalSec;
}

// 函数 CInstancePS96::GetLidHeatNormalSecond
// 作用：读取GetLidHeatNormalSecond。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePS96::GetLidHeatNormalSecond()
{
	return PS96_LIDHEATSEC;
}

// 函数 CInstancePS96::GetLidState
// 作用：读取GetLidState。
// 参数：iStatus：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
int CInstancePS96::GetLidState(int& iStatus)
{
	WORD wParam = 0X0D;
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN6,PCR_LID_STATUS, wParam);
	int iReceiveFrameLen = 0,iRet = 0;
	BYTE* pStatus = NULL;

	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand,CMD_SEND_LEN6,&pStatus,iReceiveFrameLen);
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		iStatus = pStatus[4];
	}
	else
	{
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_LED_SET_FAIL;
			iRet = -1;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_LED_SET_TIMEOUT;
			iRet = -2;
		}
		else
		{
			iRet = -3;
		}
		m_iErrorPara1 = UINT_STATE_LED;
	}

	delete [] pCommand;
	delete [] pStatus;

	return iRet;
}


// 函数 CInstancePS96::WriteLidPreheatTemperaturePLCUsed
// 作用：把WriteLidPreheatTemperaturePLCUsed写入文件、仪器或界面。
// 参数：fLidTem：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 WriteEPROM。
BOOL CInstancePS96::WriteLidPreheatTemperaturePLCUsed(float fLidTem)
{
	int iLidTem = fLidTem;

	if(iLidTem <= 0)
	{
		return FALSE;
	}

	if(!WriteEPROM(0X540,iLidTem,2))
	{
		return FALSE;
	}

	if(!WriteEPROM(0X544,iLidTem,2))
	{
		return FALSE;
	}

	return TRUE;
}

// 函数 CInstancePS96::ReadLidPreheatTemperaturePLCUsed
// 作用：读取ReadLidPreheatTemperaturePLCUsed。
// 参数：fLidPreheatTem：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 memset、ReadEPROM。
BOOL CInstancePS96::ReadLidPreheatTemperaturePLCUsed(float& fLidPreheatTem)
{
	BYTE* pReceive = new BYTE[2];
	if(NULL == pReceive)
	{
		return FALSE;
	}
	memset(pReceive,0,sizeof(BYTE) * 2);

	if(!ReadEPROM(0X540,2,pReceive))
	{
		delete [] pReceive;
		return FALSE;
	}

	fLidPreheatTem = *((USHORT*)pReceive);

	delete [] pReceive;

	return TRUE;
}

// 荧光值自检
// 函数 CInstancePS96::FluoSelfcheck
// 作用：执行FluoSelfcheck。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 SetPMTGain、GetPMTGain、SetLaserStatus、ScanOnce、ReadAllFLUData、GetCount。
BOOL CInstancePS96::FluoSelfcheck()
{
	int iScanChannelCount = 5;
	BOOL bReturn = SetPMTGain(GetPMTGain());
	if (!bReturn)
		goto END;

	bReturn = SetLaserStatus(2, 255);
	if (!bReturn)
		goto END;



	bReturn = ScanOnce();
	if (bReturn)
	{
		CUIntArray* pAryFlu = new CUIntArray[iScanChannelCount+1];

		bReturn = ReadAllFLUData(pAryFlu, iScanChannelCount+1);
		if(!bReturn)
		{
			delete [] pAryFlu;
			goto END;
		}

		int iMaxCount = 0;
		int iMinCount = 0;
		// 保存数据
		for(int i=0; i<iScanChannelCount; i++)
		{
			int iDataCount = pAryFlu[i].GetCount();
			iMaxCount = 0;
			iMinCount = 0;
			for (int j=0; j<iDataCount; j++)
			{
				UINT iFluoValue = pAryFlu[i].GetAt(j);
				if (pAryFlu[i].GetAt(j) > 55000)
					iMaxCount ++;
				//if (pAryFlu[i].GetAt(j) < pChannelFluo[i])
				if (pAryFlu[i].GetAt(j) < 100) // 待定，与常江波讨论暂定100,2025-07-18
					iMinCount ++;
			}

			if (iMaxCount > iDataCount/2)
			{
				m_eInstanceStatus = INSTANCE_FLUO_HIGH;
				break;
			}
			if (iMinCount > iDataCount/2)
			{
				m_eInstanceStatus = INSTANCE_FLUO_LOW;
				break;
			}
		}

		delete [] pAryFlu;
	}

END:
	//delete pChannelFluo;
	return bReturn;
}

// 运输锁上锁
// 函数 CInstancePS96::TransportLock
// 作用：执行TransportLock。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 memset、ReadEPROM、MotorMove。
BOOL CInstancePS96::TransportLock()
{
	BYTE* pReceive = new BYTE[2];
	if(NULL == pReceive)
		return FALSE;
	memset(pReceive, 0, sizeof(BYTE)*2);

	if(!ReadEPROM(0X230,2,pReceive))
	{
		delete [] pReceive;
		return FALSE;
	}	
	USHORT nPulseX = *((USHORT*)pReceive); // 7900

	if(!ReadEPROM(0X232,2,pReceive))
	{
		delete [] pReceive;
		return FALSE;
	}	
	USHORT nPulseY = *((USHORT*)pReceive); // 2500
	delete [] pReceive;

	BOOL bReturn = MotorMove(PCR_XMOT_FORWARD, nPulseX, m_sDevicePara.wXMotorScanFreq, 0X01);
	if (bReturn)
	{
		bReturn = MotorMove(PCR_YMOT_FORWARD, nPulseY, m_sDevicePara.wYMotorScanFreq, 0X00);
	}

	return bReturn;
}


// 函数 CInstancePS96::MotorMove
// 作用：执行MotorMove。
// 参数：cMotorFlag；wPulse；wSpeed；cDirection：矩形区域。
// 返回：返回是或否。
// 过程：函数里会调用 NewMySendCommand、SetLongReceiveTime、SendCommandRepeatedly。
BOOL CInstancePS96::MotorMove(BYTE cMotorFlag, WORD wPulse, WORD wSpeed, BYTE cDirection)
{
	BYTE* pCommand = NewMySendCommand(CMD_SEND_LEN11, PCR_MOTOR, cMotorFlag, wPulse, cDirection, wSpeed);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	m_pComPort->SetLongReceiveTime(TRUE);
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN11, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_MOTOR_MOVE_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_MOTOR_MOVE_TIMEOUT;
		}

		m_iErrorPara1 = cMotorFlag;
		m_iErrorPara2 = wPulse;
	}
	m_pComPort->SetLongReceiveTime(FALSE);

	if(NULL != pCommand)
	{
		delete [] pCommand;
	}
	if(NULL != pStatus)
	{
		delete [] pStatus;
	}

	return bReturn;
}


// 函数 CInstancePS96::NewMySendCommand
// 作用：执行NewMySendCommand。
// 参数：iCmdLength：整数；cCommand；cFlag；wPulse；cDirection：矩形区域；wSpeed。
// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
// 过程：函数里会调用 memset、GetByteSum。
BYTE* CInstancePS96::NewMySendCommand(int iCmdLength, BYTE cCommand, BYTE cFlag, WORD wPulse, BYTE cDirection, WORD wSpeed)
{
	BYTE* pCmd = new BYTE[iCmdLength];
	memset(pCmd, 0, iCmdLength);
	pCmd[0] = PCR_DNSEND;//帧头
	pCmd[1] = cCommand; //命令字
	pCmd[3] = iCmdLength; //长度
	pCmd[4] = cFlag;
	pCmd[5] = (BYTE)((wPulse & 0xFF00)>> 8);
	pCmd[6] = (BYTE)(wPulse & 0xFF);
	pCmd[7] = cDirection;
	pCmd[8] = (BYTE)((wSpeed & 0xFF00)>> 8);
	pCmd[9] = (BYTE)(wSpeed & 0xFF);
	pCmd[iCmdLength-1] = m_pComPort->GetByteSum(pCmd, iCmdLength-1);//校验和
	return pCmd;
}
