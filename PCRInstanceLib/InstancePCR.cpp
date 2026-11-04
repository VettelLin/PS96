// 【交接】 PCRInstanceLib\InstancePCR.cpp
// 作用：仪器通信基类。WriteEPROM 现有实现按整数写入，用于热盖温度等参数，不用于写入序列号字符串。
// 先看这些函数：CInstancePCR、Empty、memset、DeleteAll、CloseCom、SAFE_DELETE、DeleteFilterPara、GetErrorCode。
#include "StdAfx.h"
#include "InstancePCR.h"
#include "ErrorCodeDefine.h"
#include "LogManager.h"
#include "LanguageInfo.h"

// 函数 CInstancePCR::CInstancePCR
// 作用：执行CInstancePCR。
// 参数：pComPort：指针，指向调用方传入的对象；strVersion：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 Empty、memset。
CInstancePCR::CInstancePCR(CSerialPortPCR* pComPort, CString strVersion)
{
	m_pComPort = (CSerialPortPCR*)pComPort;
	m_strModel.Empty();
	m_strSN.Empty();
	m_strVersion = strVersion;
	m_strCode.Empty();
	m_strSoftwareVer.Empty();

	m_uiErrorCode = 0;
	m_iErrorPara1 = -1;
	m_iErrorPara2 = -1;

	memset(&m_sHardwareStatus, 0 ,sizeof(tagHardwareStatus));

	m_iMppcGainH = 4742;
	m_iMppcGainM = 4125;
	m_iMppcGainL = 3637;

	m_eInstanceStatus = INSTANCE_READY;

	m_fPwmK1 = 1;
	m_fPwmB1 = 0;
	m_fPwmK2 = 1;
	m_fPwmB2 = 0;
	m_fPwmK3 = 1;
	m_fPwmB3 = 0;

	m_fEndCoolTem = 40;
	m_iMsSlpAfterCool = 10000;

	m_iMsPwmInitWait = 80000;
	m_iPreMeltMinSlpSec = 30;
}

// 函数 CInstancePCR::~CInstancePCR
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CInstancePCR::~CInstancePCR(void)
{
	DeleteAll();
}

// 函数 CInstancePCR::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CloseCom、SAFE_DELETE、DeleteFilterPara。
void CInstancePCR::DeleteAll()
{
	if (m_pComPort != NULL)
	{
		m_pComPort->CloseCom();
	}
	SAFE_DELETE(m_pComPort);

	DeleteFilterPara();
}

// 函数 CInstancePCR::GetErrorCode
// 作用：读取GetErrorCode。
// 参数：iErrPara1：整数；iErrPara2：整数。
// 返回：返回 unsigned int。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
unsigned int CInstancePCR::GetErrorCode(int &iErrPara1, int &iErrPara2)
{
	iErrPara1 = m_iErrorPara1;
	iErrPara2 = m_iErrorPara2;
	return m_uiErrorCode;
}

// 函数 CInstancePCR::Initialize
// 作用：初始化Initialize。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 InitDevicePara、InitDeviceStatus、InitStructurePara、Hello、Home、ReadDeviceParamsFromEPROM。
BOOL CInstancePCR::Initialize()
{
	InitDevicePara();
	InitDeviceStatus();
	InitStructurePara();

	BOOL bReturn = Hello();
	if (!bReturn)
		return bReturn;

	bReturn = Home();
	if (!bReturn)
		return bReturn;

	// 读取设备参数
	bReturn = ReadDeviceParamsFromEPROM();

	if(bReturn)
	{
		bReturn = ReadStructureParamsFromEPROM();
	}

	InitFilterPara();
	
	return bReturn;
}

// 函数 CInstancePCR::InitDevicePara
// 作用：初始化InitDevicePara。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 memset、memcpy、strlen。
void CInstancePCR::InitDevicePara()
{
	memset(m_sDevicePara.cDeviceModel, 0, 16);
	memset(m_sDevicePara.cDeviceSN, 0, 16);
	memset(m_sDevicePara.cDeviceVersion, 0, 16);
	memset(m_sDevicePara.cFirmware, 0, 16);
	memset(m_sDevicePara.cReserved1, 0, 160);

	char* pChannel1 = "T505,ET470/10,ET520/10";
	memset(m_sDevicePara.cKeyFilter1, 0, 32);
	memcpy(m_sDevicePara.cKeyFilter1, pChannel1, strlen(pChannel1));
	pChannel1 = "T650,ET630/16,ET670/20";
	memset(m_sDevicePara.cKeyFilter2, 0, 32);
	memcpy(m_sDevicePara.cKeyFilter2, pChannel1, strlen(pChannel1));
	pChannel1 = "T550,ET520/20,ET560/20";
	memset(m_sDevicePara.cKeyFilter3, 0, 32);
	memcpy(m_sDevicePara.cKeyFilter3, pChannel1, strlen(pChannel1));
	pChannel1 = "T700,ET670/20,ET740/20";
	memset(m_sDevicePara.cKeyFilter4, 0, 32);
	memcpy(m_sDevicePara.cKeyFilter4, pChannel1, strlen(pChannel1));
	pChannel1 = "T585,ET570/20,ET610/20";
	memset(m_sDevicePara.cKeyFilter5, 0, 32);
	memcpy(m_sDevicePara.cKeyFilter5, pChannel1, strlen(pChannel1));
	
	memset(m_sDevicePara.cKeyFilter6, 0, 32);
	memset(m_sDevicePara.cKeyFilter7, 0, 32);
	memset(m_sDevicePara.cKeyFilter8, 0, 32);

	pChannel1 = "11111400";
	memset(m_sDevicePara.cFilterConfig, 0, 8);
	memcpy(m_sDevicePara.cFilterConfig, pChannel1, strlen(pChannel1));

	memset(m_sDevicePara.cReserved2, 0, 24);

	m_sDevicePara.wXMotorBackPulse = 0;
	m_sDevicePara.wXMotorMaxFreq = 33000;
	m_sDevicePara.wXMotorFreq0 = 2000;
	m_sDevicePara.wXMotorScanFreq = 11000;
	m_sDevicePara.wXMotorHomeFreq = 10000;
	m_sDevicePara.wXMotorAccPulse = 400;
	m_sDevicePara.wXMotorMaxPls = 10000;
	m_sDevicePara.wXMotorScanPulse = 9500;
	m_sDevicePara.wXMotorOutDir = 0;
	m_sDevicePara.wXMotorBackFreq = 1200;

	m_sDevicePara.wYMotorBackPulse = 4600;
	m_sDevicePara.wYMotorMaxFreq = 33000;
	m_sDevicePara.wYMotorFreq0 = 2000;
	m_sDevicePara.wYMotorScanFreq = 16000;
	m_sDevicePara.wYMotorHomeFreq = 20000;
	m_sDevicePara.wYMotorAccPulse = 2000;
	m_sDevicePara.wYMotorMaxPls = 50000;
	m_sDevicePara.wYMotorScanPulse = 5905;
	m_sDevicePara.wYMotorOutDir = 0;
	m_sDevicePara.wYMotorBackFreq = 3000;
	m_sDevicePara.wYMotorMoveToFreq = 16000;

	memset(m_sDevicePara.cReserved3, 0, 214);
	memset(m_sDevicePara.cReserved4, 0, 512);
	memset(m_sDevicePara.cReserved5, 0, 256);
	memset(m_sDevicePara.cReserved6, 0, 256);

	m_sDevicePara.wPMTGainCh1 = 2300;
	memset(m_sDevicePara.cReserved7, 0, 94);

	m_sDevicePara.wCrtCoef1To1 = 0;
	m_sDevicePara.wCrtCoef2To1 = 0;
	m_sDevicePara.wCrtCoef3To1 = 0;
	m_sDevicePara.wCrtCoef4To1 = 0;
	m_sDevicePara.wCrtCoef5To1 = 0;
	m_sDevicePara.wCrtCoef6To1 = 0;
	m_sDevicePara.wCrtCoef7To1 = 0;
	m_sDevicePara.wCrtCoef8To1 = 0;

	m_sDevicePara.wCrtCoef1To2 = 0;
	m_sDevicePara.wCrtCoef2To2 = 0;
	m_sDevicePara.wCrtCoef3To2 = 0;
	m_sDevicePara.wCrtCoef4To2 = 0;
	m_sDevicePara.wCrtCoef5To2 = 0;
	m_sDevicePara.wCrtCoef6To2 = 0;
	m_sDevicePara.wCrtCoef7To2 = 0;
	m_sDevicePara.wCrtCoef8To2 = 0;

	m_sDevicePara.wCrtCoef1To3 = 0;
	m_sDevicePara.wCrtCoef2To3 = 0;
	m_sDevicePara.wCrtCoef3To3 = 0;
	m_sDevicePara.wCrtCoef4To3 = 0;
	m_sDevicePara.wCrtCoef5To3 = 0;
	m_sDevicePara.wCrtCoef6To3 = 0;
	m_sDevicePara.wCrtCoef7To3 = 0;
	m_sDevicePara.wCrtCoef8To3 = 0;

	m_sDevicePara.wCrtCoef1To4 = 0;
	m_sDevicePara.wCrtCoef2To4 = 0;
	m_sDevicePara.wCrtCoef3To4 = 0;
	m_sDevicePara.wCrtCoef4To4 = 0;
	m_sDevicePara.wCrtCoef5To4 = 0;
	m_sDevicePara.wCrtCoef6To4 = 0;
	m_sDevicePara.wCrtCoef7To4 = 0;
	m_sDevicePara.wCrtCoef8To4 = 0;

	m_sDevicePara.wCrtCoef1To5 = 0;
	m_sDevicePara.wCrtCoef2To5 = 0;
	m_sDevicePara.wCrtCoef3To5 = 0;
	m_sDevicePara.wCrtCoef4To5 = 0;
	m_sDevicePara.wCrtCoef5To5 = 0;
	m_sDevicePara.wCrtCoef6To5 = 0;
	m_sDevicePara.wCrtCoef7To5 = 0;
	m_sDevicePara.wCrtCoef8To5 = 0;

	m_sDevicePara.wCrtCoef1To6 = 0;
	m_sDevicePara.wCrtCoef2To6 = 0;
	m_sDevicePara.wCrtCoef3To6 = 0;
	m_sDevicePara.wCrtCoef4To6 = 0;
	m_sDevicePara.wCrtCoef5To6 = 0;
	m_sDevicePara.wCrtCoef6To6 = 0;
	m_sDevicePara.wCrtCoef7To6 = 0;
	m_sDevicePara.wCrtCoef8To6 = 0;

	memset(m_sDevicePara.cReserved8, 0, 64);
	memset(m_sDevicePara.cReserved9, 0, 512);
}

// 函数 CInstancePCR::InitDeviceStatus
// 作用：初始化InitDeviceStatus。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::InitDeviceStatus()
{
	m_sDeviceStatus.cXMot = 0; // X轴状态，0-正常；1-错误；
	m_sDeviceStatus.cYMot = 0; // Y轴状态，0-正常；1-错误；
	m_sDeviceStatus.cZMot = 0 ;		// Z轴状态，0-正常；1-错误；
	m_sDeviceStatus.cUMot = 0 ;		// U轴状态，0-正常；1-错误；
	m_sDeviceStatus.cMotSense = 0;	// 光电开关，0-正常；1-错误；
	m_sDeviceStatus.cEeprom = 0;	// EEPROM状态，0-正常；1-错误；
	m_sDeviceStatus.cPMT = 0;		// PMT状态，0-正常；1-错误；

	m_sDeviceStatus.cPETUnit1 = 0;	// 帕尔贴1状态，0-正常；1-错误；
	m_sDeviceStatus.cPETUnit2 = 0;	// 帕尔贴2状态，0-正常；1-错误；
	m_sDeviceStatus.cPETUnit3 = 0;	// 帕尔贴3状态，0-正常；1-错误；
	m_sDeviceStatus.cCap = 0;		// 热盖状态，0-正常；1-错误；
	m_sDeviceStatus.cFanState = 0;	// 散热器风扇状态，0-正常；1-错误；
	m_sDeviceStatus.cAuxerState = 0; // 辅助加热状态，0-正常；1-错误	
	m_sDeviceStatus.cA4940Rst = 0;	// 功率板状态，0-正常；1-错误；
	m_sDeviceStatus.cSysBox = 0;	// 进出仓按钮状态，0-正常；1-有按下

	m_sDeviceStatus.cLid = 0; // 盖子状态 0：关闭 1：打开
}

// 初始化仪器结构参数
// 函数 CInstancePCR::InitStructurePara
// 作用：初始化InitStructurePara。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 memset。
void CInstancePCR::InitStructurePara()
{
	m_sStructurePara.cFrameLength = 1;
	m_sStructurePara.cUseBox = 0;
	m_sStructurePara.wReserved1 = 0;
	m_sStructurePara.wReserved2 = 0;

	m_sStructurePara.cTempMode = TEMP_MODE_UPDOWN;
	m_sStructurePara.cTempCtrl = TEMP_CTRL_TUBE;
	m_sStructurePara.cTempModuleCount = 1;
	m_sStructurePara.cAutoCooling = 0;
	m_sStructurePara.cReserved3 = 0;

	m_sStructurePara.cPlateType = 0;
	m_sStructurePara.cPlateCount = 1;
	m_sStructurePara.cPlateSortType = 0;
	m_sStructurePara.cPlateRowCount = 8;
	m_sStructurePara.cPlateColCount = 12;
	m_sStructurePara.cReserved4 = 0;

	m_sStructurePara.cScanMode = 0;
	m_sStructurePara.cScanOrigin = 0;
	m_sStructurePara.cScanPathCount = 1;
	m_sStructurePara.cReserved5 = 0;

	m_sStructurePara.cSupportMelt = 1;
	m_sStructurePara.cSupportMultiMelt = 0;
	m_sStructurePara.cMeltPreDelay = 60;
	m_sStructurePara.cMeltBeginTemp = 60;
	m_sStructurePara.cMeltBeginPreTemp = 3;
	m_sStructurePara.cMeltMinIncrement = 50;
	m_sStructurePara.cMeltStepDelay = 60;
	m_sStructurePara.cReserved6 = 0;
	
	m_sStructurePara.cTempChannelCount = 3;
	m_sStructurePara.wTempChannelFlag = 0;
	m_sStructurePara.cTempCtrlTop = 90;
	m_sStructurePara.cTempCtrlLower = 30;
	m_sStructurePara.cTempCtrlMaxTime = 60;
	m_sStructurePara.cTempLegalGap = 50;
	m_sStructurePara.cTempPeltierLower = 15;
	m_sStructurePara.cLidHeader = 1;
	m_sStructurePara.cLidTempTop = 100;
	m_sStructurePara.cLidTempLower = 30;
	m_sStructurePara.cLidTempMaxTime = 10;
	m_sStructurePara.cLidTempLegalGap = 50;
	m_sStructurePara.wReserved7 = 0;

	m_sStructurePara.wScanOnceTime = 1000;
	m_sStructurePara.cScanChangeRowTime = 0;
	m_sStructurePara.cUseCrosstailk = 2;
	m_sStructurePara.cCalibratePara = 0;
	m_sStructurePara.cReserved8 = 0;
	m_sStructurePara.wReserved9 = 0;

	m_sStructurePara.cUseFilter = 0;
	m_sStructurePara.cFilterAmplifyMethod = 1;
	m_sStructurePara.cFilterAmplifyShowMethod = 1;
	m_sStructurePara.cFilterMeltMethod = 2;

	memset(m_sStructurePara.cReserved10, 0, 454);
}

// 函数 CInstancePCR::InitFilterPara
// 作用：初始化InitFilterPara。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteFilterPara、memset、InitOneChannelFilter、atoi。
void CInstancePCR::InitFilterPara()
{
	DeleteFilterPara();

	char* pFilterConfig = m_sDevicePara.cFilterConfig;
	int iLength = 8;
	for (int i=0; i<iLength; i++)
	{
		char cType[2];
		memset(cType, 0, 2);
		cType[0] = pFilterConfig[i];
		InitOneChannelFilter(i+1, ::atoi(cType));
	}
}

// 函数 CInstancePCR::InitOneChannelFilter
// 作用：初始化InitOneChannelFilter。
// 参数：iChannel：整数；iByte：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::InitOneChannelFilter(int iChannel, int iByte)
{
	char* pChannelFlag = NULL;

	switch(iChannel)
	{
	case 1:
		pChannelFlag = m_sDevicePara.cKeyFilter1;
		break;
	case 2:
		pChannelFlag = m_sDevicePara.cKeyFilter2;
		break;
	case 3:
		pChannelFlag = m_sDevicePara.cKeyFilter3;
		break;
	case 4:
		pChannelFlag = m_sDevicePara.cKeyFilter4;
		break;
	case 5:
		pChannelFlag = m_sDevicePara.cKeyFilter5;
		break;
	case 6:
		pChannelFlag = m_sDevicePara.cKeyFilter6;
		break;
	case 7:
		pChannelFlag = m_sDevicePara.cKeyFilter7;
		break;
	case 8:
		pChannelFlag = m_sDevicePara.cKeyFilter8;
		break;
	default:
		break;
	}

	if (pChannelFlag == NULL)
		return;

	if (iByte == 1) // MPPC
	{
		BOOL bFstLine = TRUE;

		int iComma1 = -1;
		int iComma2 = -1;
		int iLine1 = -1;
		int iLine2 = -1;
		for (int i=0; i<32; i++)
		{
			if (pChannelFlag[i] == ',' || '，' == pChannelFlag[i])
			{
				if (iComma1 == -1)
				{
					iComma1 = i;
				}
				else if (iComma2 == -1)
				{
					iComma2 = i;
				}
			}
			else if (pChannelFlag[i] == '/')
			{
				if (iLine1 == -1)
				{
					iLine1 = i;
				}
				else if (iLine2 == -1)
				{
					iLine2 = i;
				}

				/*if(!bFstLine)
				{
				if (iLine1 == -1)
				{
				iLine1 = i;
				}
				else if (iLine2 == -1)
				{
				iLine2 = i;
				}
				}
				else
				{
				bFstLine = FALSE;
				}*/
			}
		}

		if (iComma1 == -1 || iComma2 == -1 || iLine1 == -1 || iLine2 == -1)
		{
			ASSERT(FALSE);
			return;
		}

		char cExWavelength[8];
		memset(cExWavelength, 0, 8);
		memcpy(cExWavelength, pChannelFlag+iComma1+1, iLine1-iComma1-1);
		char cExWaveRange[5];
		memset(cExWaveRange, 0, 5);
		memcpy(cExWaveRange, pChannelFlag+iLine1+1, iComma2-iLine1-1);
		char cEmWavelength[8];
		memset(cEmWavelength, 0, 8);
		memcpy(cEmWavelength, pChannelFlag+iComma2+1, iLine2-iComma2-1);
		char cEmWaveRange[5];
		memset(cEmWaveRange, 0, 5);
		memcpy(cEmWaveRange, pChannelFlag+iLine2+1, 2);

		int iExFirst = -1;
		int iEmFirst = -1;
		for (int j=0; j<8; j++)
		{
			if (cExWavelength[j] >= '0' && cExWavelength[j] <= '9')
			{
				if (iExFirst == -1)
					iExFirst = j;
			}

			if (cEmWavelength[j] >= '0' && cEmWavelength[j] <= '9')
			{
				if (iEmFirst == -1)
					iEmFirst = j;
			}
		}

		if (iExFirst != -1)
		{
			memcpy(cExWavelength, cExWavelength+iExFirst, 8-iExFirst);
		}
		if (iEmFirst != -1)
		{
			memcpy(cEmWavelength, cEmWavelength+iEmFirst, 8-iEmFirst);
		}

		tagScanChannelInfo* pFilter = new tagScanChannelInfo;
		pFilter->iType = iByte;
		pFilter->iExPosition = iChannel;
		pFilter->iExWaveLen = ::atoi(cExWavelength);
		pFilter->iExRange = ::atoi(cExWaveRange);
		pFilter->iEmPosition = iChannel;
		pFilter->iEmWaveLen = ::atoi(cEmWavelength);
		pFilter->iEmRange = ::atoi(cEmWaveRange);
		m_arrayFilter.Add(pFilter);
	}
	else if (iByte == 4) // MOT校准
	{
		tagScanChannelInfo* pFilter = new tagScanChannelInfo;
		pFilter->iType = iByte;
		pFilter->iExPosition = iChannel;
		pFilter->iExWaveLen = 0;
		pFilter->iExRange = 0;
		pFilter->iEmPosition = iChannel;
		pFilter->iEmWaveLen = 0;
		pFilter->iEmRange = 0;
		m_arrayFilter.Add(pFilter);
	}
}

// 函数 CInstancePCR::DeleteFilterPara
// 作用：更新或清除DeleteFilterPara。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SAFE_DELETE、RemoveAll。
void CInstancePCR::DeleteFilterPara()
{
	int iCount = m_arrayFilter.GetCount();
	for (int i=0; i<iCount; i++)
	{
		tagScanChannelInfo* pFilter = (tagScanChannelInfo*)m_arrayFilter.GetAt(i);
		SAFE_DELETE(pFilter);
	}
	m_arrayFilter.RemoveAll();
}


// 生成发送命令，处理指令长度5/6/7的情况，没有参数或只有一个参数
// 函数 CInstancePCR::NewSendCommand
// 作用：执行NewSendCommand。
// 参数：iCmdLength：整数；cCommand；wPara。
// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
// 过程：函数里会调用 memset、GetByteSum。
BYTE* CInstancePCR::NewSendCommand(int iCmdLength, BYTE cCommand, WORD wPara)
{
	BYTE* pCmd = new BYTE[iCmdLength];
	memset(pCmd, 0, iCmdLength);
	pCmd[0] = PCR_DNSEND;//帧头
	pCmd[1] = cCommand; //命令字
	pCmd[3] = iCmdLength; //长度
	if (iCmdLength == CMD_SEND_LEN7)
	{
		pCmd[4] = (BYTE)((wPara & 0xFF00)>> 8);
		pCmd[5] = (BYTE)(wPara & 0xFF);
	}
	else if (iCmdLength == CMD_SEND_LEN6)
	{
		pCmd[4] = (BYTE)(wPara & 0xFF);;
	}
	pCmd[iCmdLength-1] = m_pComPort->GetByteSum(pCmd, iCmdLength-1);
	return pCmd;
}

// 生成发送命令，处理指令长度5/6/7的情况，有两个单字节参数
// 函数 CInstancePCR::NewSendCommand
// 作用：执行NewSendCommand。
// 参数：iCmdLength：整数；cCommand；cPara1；cPara2。
// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
// 过程：函数里会调用 memset、GetByteSum。
BYTE* CInstancePCR::NewSendCommand(int iCmdLength, BYTE cCommand, BYTE cPara1, BYTE cPara2)
{
	BYTE* pCmd = new BYTE[iCmdLength];
	memset(pCmd, 0, iCmdLength);
	pCmd[0] = PCR_DNSEND;//帧头
	pCmd[1] = cCommand; //命令字
	pCmd[3] = iCmdLength; //长度
	pCmd[4] = cPara1;
	pCmd[5] = cPara2;
	pCmd[iCmdLength-1] = m_pComPort->GetByteSum(pCmd, iCmdLength-1);
	return pCmd;
}

// 生成发送命令，处理指令长度9的情况，当前使用在取EEPROM参数时，包括地址和取数据长度（字节数）
// 函数 CInstancePCR::NewSendCommand
// 作用：执行NewSendCommand。
// 参数：iCmdLength：整数；cCommand；nAddress：整数；cGReceiveLen。
// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
// 过程：函数里会调用 memset、GetByteSum。
BYTE* CInstancePCR::NewSendCommand(int iCmdLength, BYTE cCommand, UINT nAddress, BYTE cGReceiveLen)
{
	BYTE* pCmd = new BYTE[iCmdLength];
	memset(pCmd, 0, iCmdLength);
	pCmd[0] = PCR_DNSEND;//帧头
	pCmd[1] = cCommand; //命令字
	pCmd[3] = iCmdLength; //长度
	pCmd[4] = (BYTE)((nAddress & 0xFF0000)>> 16);
	pCmd[5] = (BYTE)((nAddress & 0xFF00)>> 8);
	pCmd[6] = (BYTE)(nAddress & 0xFF);
	pCmd[7] =  cGReceiveLen;
	pCmd[iCmdLength-1] = m_pComPort->GetByteSum(pCmd, iCmdLength-1);//校验和
	return pCmd;
}

// 生成发送命令，处理指令长度10的情况，当前使用在电机运行指令上，包括辅助指令、脉冲和速度
// 函数 CInstancePCR::NewSendCommand
// 作用：执行NewSendCommand。
// 参数：iCmdLength：整数；cCommand；cFlag；wPulse；wSpeed。
// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
// 过程：函数里会调用 memset、GetByteSum。
BYTE* CInstancePCR::NewSendCommand(int iCmdLength, BYTE cCommand, BYTE cFlag, WORD wPulse, WORD wSpeed)
{
	BYTE* pCmd = new BYTE[iCmdLength];
	memset(pCmd, 0, iCmdLength);
	pCmd[0] = PCR_DNSEND;//帧头
	pCmd[1] = cCommand; //命令字
	pCmd[3] = iCmdLength; //长度
	pCmd[4] = cFlag;
	pCmd[5] = (BYTE)((wPulse & 0xFF00)>> 8);
	pCmd[6] = (BYTE)(wPulse & 0xFF);
	pCmd[7] = (BYTE)((wSpeed & 0xFF00)>> 8);
	pCmd[8] = (BYTE)(wSpeed & 0xFF);
	pCmd[iCmdLength-1] = m_pComPort->GetByteSum(pCmd, iCmdLength-1);//校验和
	return pCmd;
}

// 函数 CInstancePCR::NewSendCommand
// 作用：执行NewSendCommand。
// 参数：iCmdLength：整数；cCommand；wPara1；wPara2；wPara3；wPara4；cMode。
// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
// 过程：函数里会调用 memset、GetByteSum。
BYTE* CInstancePCR::NewSendCommand(int iCmdLength, BYTE cCommand, WORD wPara1, WORD wPara2, WORD wPara3, WORD wPara4, BYTE cMode)
{
	BYTE* pCmd = new BYTE[iCmdLength];
	memset(pCmd, 0, iCmdLength);
	pCmd[0] = PCR_DNSEND;//帧头
	pCmd[1] = cCommand; //命令字
	pCmd[3] = iCmdLength; //长度
	pCmd[4] = (BYTE)((wPara1 & 0xFF00)>> 8);
	pCmd[5] = (BYTE)(wPara1 & 0xFF);
	pCmd[6] = (BYTE)((wPara2 & 0xFF00)>> 8);
	pCmd[7] = (BYTE)(wPara2 & 0xFF);
	pCmd[8] = (BYTE)((wPara3 & 0xFF00)>> 8);
	pCmd[9] = (BYTE)(wPara3 & 0xFF);
	pCmd[10] = (BYTE)((wPara4 & 0xFF00)>> 8);
	pCmd[11] = (BYTE)(wPara4 & 0xFF);
	pCmd[12] = cMode;
	pCmd[iCmdLength-1] = m_pComPort->GetByteSum(pCmd, iCmdLength-1);//校验和
	return pCmd;
}

// 发送Hello命令
// 函数 CInstancePCR::Hello
// 作用：执行Hello。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::Hello()
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN5, PCR_HELLO, 0);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN5, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 0;
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_HELLO_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_REPEAT_OUT)
		{
			m_uiErrorCode = ERR_HELLO_TIMEOUTL;
		}
	}

	delete pCommand;
	delete pStatus;

	return bReturn;
}
	
//仪器复位
// 函数 CInstancePCR::Home
// 作用：执行Home。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 MotorReset。
BOOL CInstancePCR::Home()
{
	BOOL bReturn = MotorReset(PCR_XMOT_RESET);
	if (!bReturn)
	{
		return bReturn;
	}

	bReturn = MotorReset(PCR_YMOT_RESET);
	return bReturn;
}

// 是否进仓
// 函数 CInstancePCR::IsInBox
// 作用：判断IsInBox是否成立。
// 参数：outStatus。
// 返回：返回是或否。
// 过程：函数里会调用 ReadHardwareStatus。
BOOL CInstancePCR::IsInBox(eSysBoxStatus &outStatus)
{
	outStatus = BOXSTATE_UNKNOW;
	// 先读取硬件设备状态
	BOOL bReturn = ReadHardwareStatus();
	if (bReturn)
	{
		outStatus = (eSysBoxStatus)(m_sHardwareStatus.nSysBox);
	}

	return bReturn;
}

// 发送进仓命令
// 函数 CInstancePCR::InBox
// 作用：执行InBox。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SetLongReceiveTime、SendCommandRepeatedly。
BOOL CInstancePCR::InBox()
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN5, PCR_IN_BOX, 0);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	m_pComPort->SetLongReceiveTime(TRUE);
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN5, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 0;
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_BOX_IN_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_REPEAT_OUT)
		{
			m_uiErrorCode = ERR_BOX_IN_TIMEOUT;
		}
	}

	delete pCommand;
	delete pStatus;
	return bReturn;
}

// 发送出仓命令
// 函数 CInstancePCR::OutBox
// 作用：执行OutBox。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SetLongReceiveTime、SendCommandRepeatedly。
BOOL CInstancePCR::OutBox()
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN5, PCR_OUT_BOX, 0);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	m_pComPort->SetLongReceiveTime(TRUE);
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN5, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 0;
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_BOX_OUT_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_REPEAT_OUT)
		{
			m_uiErrorCode = ERR_BOX_OUT_FAIL;
		}
	}

	delete pCommand;
	delete pStatus;
	return bReturn;
}

// 函数 CInstancePCR::MotorReset
// 作用：执行MotorReset。
// 参数：nMotorFlag：整数。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::MotorReset(eUnitPCR nMotorFlag)
{
	int iMoveFlag = -1;
	switch(nMotorFlag)
	{
	case UNIT_MOTOR_X:
		iMoveFlag = PCR_XMOT_RESET;
		break;
	case UNIT_MOTOR_Y:
		iMoveFlag = PCR_YMOT_RESET;
		break;
	case UNIT_MOTOR_Z:
		iMoveFlag = PCR_ZMOT_RESET;
		break;
	case UNIT_MOTOR_U:
		iMoveFlag = PCR_UMOT_RESET;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return MotorReset(iMoveFlag);
}
// 函数 CInstancePCR::MotorMove
// 作用：执行MotorMove。
// 参数：nMotorFlag：整数；nPulse：整数；nMoveFlag：整数。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::MotorMove(eUnitPCR nMotorFlag, WORD nPulse, eMotorMoveFlag nMoveFlag)
{
	int iMoveFlag = -1;
	WORD nSpeed = 0;
	switch(nMotorFlag)
	{
	case UNIT_MOTOR_X:
		nSpeed = m_sDevicePara.wXMotorScanFreq;
		if (nMoveFlag == MOTOR_MOVE_TO)
		{
			iMoveFlag = PCR_XMOT_MOVETO;
		}
		else if (nMoveFlag == MOTOR_FORWARD)
		{
			iMoveFlag = PCR_XMOT_FORWARD;
		}
		else if (nMoveFlag == MOTOR_REVERSE)
		{
			iMoveFlag = PCR_XMOT_REVERSE;
		}
		else
		{
			ASSERT(FALSE);
		}
		break;
	case UNIT_MOTOR_Y:
		nSpeed = m_sDevicePara.wYMotorScanFreq;
		if (nMoveFlag == MOTOR_MOVE_TO)
		{
			iMoveFlag = PCR_YMOT_MOVETO;
		}
		else if (nMoveFlag == MOTOR_FORWARD)
		{
			iMoveFlag = PCR_YMOT_FORWARD;
		}
		else if (nMoveFlag == MOTOR_REVERSE)
		{
			iMoveFlag = PCR_YMOT_REVERSE;
		}
		else
		{
			ASSERT(FALSE);
		}
		break;
	case UNIT_MOTOR_Z:
		ASSERT(FALSE);
		break;
	case UNIT_MOTOR_U:
		ASSERT(FALSE);
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return MotorMove(iMoveFlag, nPulse, nSpeed);
}

// 函数 CInstancePCR::MotorReset
// 作用：执行MotorReset。
// 参数：cMotorFlag。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SetLongReceiveTime、SendCommandRepeatedly。
BOOL CInstancePCR::MotorReset(BYTE cMotorFlag)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN6, PCR_MOTOR, cMotorFlag);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	m_pComPort->SetLongReceiveTime(TRUE);
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN6, &pStatus, iReceiveFrameLen);
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
			m_uiErrorCode = ERR_MOTOR_RESET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_MOTOR_RESET_TIMEOUT;
		}

		m_iErrorPara1 = cMotorFlag;
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

// 函数 CInstancePCR::MotorMove
// 作用：执行MotorMove。
// 参数：cMotorFlag；wPulse；wSpeed。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SetLongReceiveTime、SendCommandRepeatedly。
BOOL CInstancePCR::MotorMove(BYTE cMotorFlag, WORD wPulse, WORD wSpeed)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN10, PCR_MOTOR, cMotorFlag, wPulse, wSpeed);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	m_pComPort->SetLongReceiveTime(TRUE);
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN10, &pStatus, iReceiveFrameLen);
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

// 默认X电机，扫描一行
// 函数 CInstancePCR::MotorScanRow
// 作用：执行MotorScanRow。
// 参数：wPulse；cDirection：矩形区域。
// 返回：返回是或否。
// 过程：函数里会调用 memset、GetByteSum、SendCommandRepeatedly。
BOOL CInstancePCR::MotorScanRow(WORD wPulse, BYTE cDirection)
{
	int iCmdLength = CMD_SEND_LEN11;
	WORD wSpeed = m_sDevicePara.wXMotorScanFreq;

	BYTE* pCommand = new BYTE[iCmdLength];
	memset(pCommand, 0, iCmdLength);
	pCommand[0] = PCR_DNSEND;//帧头
	pCommand[1] = PCR_MOTOR; //命令字
	pCommand[3] = iCmdLength; //长度
	pCommand[4] = PCR_XMOT_SCAN;
	pCommand[5] = (BYTE)((wPulse & 0xFF00)>> 8);
	pCommand[6] = (BYTE)(wPulse & 0xFF);
	pCommand[7] = cDirection;
	pCommand[8] = (BYTE)((wSpeed & 0xFF00)>> 8);
	pCommand[9] = (BYTE)(wSpeed & 0xFF);
	pCommand[iCmdLength-1] = m_pComPort->GetByteSum(pCommand, iCmdLength-1);//校验和

	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, iCmdLength, &pStatus, iReceiveFrameLen, 1);
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

		m_iErrorPara1 = PCR_XMOT_SCAN;
		m_iErrorPara2 = wPulse;
	}

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

// 完成一次扫描全部扫描动作
// 函数 CInstancePCR::ScanOnce
// 作用：执行ScanOnce。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 GetScanRowCount、MotorMove、MotorScanRow、MotorReset。
BOOL CInstancePCR::ScanOnce()
{
	BOOL bReturn = FALSE;
	BYTE cDirection = 1;
	int iLineDistance = m_sDevicePara.wYMotorScanPulse;
	int iXMotScanDistance = m_sDevicePara.wXMotorScanPulse;

	int iScanRow = GetScanRowCount();
	for (int i=0; i<iScanRow; i++)
	{
		//Y轴运动到待扫描行位置
		bReturn = MotorMove(CInstancePCR::UNIT_MOTOR_Y, iLineDistance*i, CInstancePCR::MOTOR_MOVE_TO);
		if (!bReturn)
			break;

		//发送采样一行指令
		bReturn = MotorScanRow(iXMotScanDistance, cDirection);
		if (!bReturn)
		{
			//执行容错,缺省2次
			int iFoleNum = 0;
			do 
			{
				bReturn = MotorReset(CInstancePCR::UNIT_MOTOR_X);
				if (!bReturn) 
					break;

				if (0 == cDirection)
				{
					bReturn = MotorMove(CInstancePCR::UNIT_MOTOR_X, iXMotScanDistance, CInstancePCR::MOTOR_MOVE_TO);
					if (!bReturn) 
						break;
				}

				bReturn = MotorScanRow(iXMotScanDistance, cDirection);
				if (bReturn)
				{
					break;
				}
				else
				{
					iFoleNum++;
				}
			} while (iFoleNum < 2);

			//若容错失败退出循环，终止当前扫描
			if (!bReturn) 
				break;
		}
		//更改X电机扫描方向，继续下一次扫描
		(cDirection > 0)? (cDirection =0):(cDirection =1);
	}

	return  bReturn;
}

// 完成一次扫描全部扫描动作，支持快速停止扫描，20220330，孙文郎
// 函数 CInstancePCR::ScanOnce
// 作用：执行ScanOnce。
// 参数：pBeAskTop：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 clock、GetScanRowCount、MotorMove、MotorScanRow、MotorReset。
BOOL CInstancePCR::ScanOnce(BOOL *pBeAskTop)
{
#ifdef _DEBUG
	clock_t ckStart = clock();
#endif

	BOOL bReturn = FALSE;
	BYTE cDirection = 1;
	int iLineDistance = m_sDevicePara.wYMotorScanPulse;
	int iXMotScanDistance = m_sDevicePara.wXMotorScanPulse;

	int iScanRow = GetScanRowCount();
	for (int i=0; i<iScanRow; i++)
	{
		//判断用户是否点击了停止扫描
		if(NULL != pBeAskTop && *pBeAskTop)
		{
			return TRUE;
		}

		//Y轴运动到待扫描行位置
		bReturn = MotorMove(CInstancePCR::UNIT_MOTOR_Y, iLineDistance*i, CInstancePCR::MOTOR_MOVE_TO);
		if (!bReturn)
			break;

		//判断用户是否点击了停止扫描
		if(NULL != pBeAskTop && *pBeAskTop)
		{
			return TRUE;
		}

		//发送采样一行指令
		bReturn = MotorScanRow(iXMotScanDistance, cDirection);
		if (!bReturn)
		{
			//执行容错,缺省2次
			int iFoleNum = 0;
			do 
			{
				bReturn = MotorReset(CInstancePCR::UNIT_MOTOR_X);
				if (!bReturn) 
					break;

				if (0 == cDirection)
				{
					bReturn = MotorMove(CInstancePCR::UNIT_MOTOR_X, iXMotScanDistance, CInstancePCR::MOTOR_MOVE_TO);
					if (!bReturn) 
						break;
				}

				bReturn = MotorScanRow(iXMotScanDistance, cDirection);
				if (bReturn)
				{
					break;
				}
				else
				{
					iFoleNum++;
				}
			} while (iFoleNum < 2);

			//若容错失败退出循环，终止当前扫描
			if (!bReturn) 
				break;
		}
		//更改X电机扫描方向，继续下一次扫描
		(cDirection > 0)? (cDirection =0):(cDirection =1);
	}

	//扫描电机复位
	if(bReturn)
	{
		bReturn = MotorMove(CInstancePCR::UNIT_MOTOR_X,0,CInstancePCR::MOTOR_MOVE_TO);
		if(bReturn)
		{
			bReturn = MotorMove(CInstancePCR::UNIT_MOTOR_Y,0,CInstancePCR::MOTOR_MOVE_TO);
		}
	}

#ifdef _DEBUG
	clock_t ckEnd = clock() - ckStart;
#endif

	return  bReturn;
}

// 函数 CInstancePCR::SetStateLED
// 作用：设置SetStateLED。
// 参数：cMode。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SetLongReceiveTime、SendCommandRepeatedly。
BOOL CInstancePCR::SetStateLED(BYTE cMode)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN6, PCR_STALED, cMode);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	m_pComPort->SetLongReceiveTime(TRUE);
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN6, &pStatus, iReceiveFrameLen);
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
			m_uiErrorCode = ERR_LED_SET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_LED_SET_TIMEOUT;
		}
		m_iErrorPara1 = UINT_STATE_LED;
	}
	m_pComPort->SetLongReceiveTime(FALSE);

	delete pCommand;
	delete pStatus;

	return bReturn;
}

// 发送设置PMT控制电压命令
// 函数 CInstancePCR::SetPMTGain
// 作用：设置SetPMTGain。
// 参数：wGainPara。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::SetPMTGain(WORD wGainPara)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN7, PCR_PMT_GAIN, wGainPara);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN7, &pStatus, iReceiveFrameLen);
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
			m_uiErrorCode = ERR_LED_SET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_LED_SET_TIMEOUT;
		}

		m_iErrorPara1 = UINT_STATE_LED;
	}

	delete pCommand;
	delete pStatus;

	return bReturn;
}

// PCR 控温模式
// 函数 CInstancePCR::SetTempCtrlMode
// 作用：设置SetTempCtrlMode。
// 参数：nCtrlMode：整数。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::SetTempCtrlMode(eTempCtrlMode nCtrlMode)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN6, PCR_TEMP_MODE, nCtrlMode);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;

	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN6, &pStatus, iReceiveFrameLen);
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
			m_uiErrorCode = ERR_GAIN_SET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_GAIN_SET_TIMEOUT;
		}
	}

	delete pCommand;
	delete pStatus;

	return bReturn;
}

// 函数 CInstancePCR::SetDeviceParams
// 作用：设置SetDeviceParams。
// 参数：pPara：指针，指向调用方传入的对象；Len。
// 返回：没有返回值。
// 过程：函数里会调用 memcpy。
void CInstancePCR::SetDeviceParams(BYTE* pPara,int Len)
{
	memcpy(&m_sDevicePara, pPara, Len);
}

// 函数 CInstancePCR::GetPMTGain
// 作用：读取GetPMTGain。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
WORD CInstancePCR::GetPMTGain()
{
	WORD wPMTGain = m_sDevicePara.wPMTGainCh1;
	if (wPMTGain == 0)
	{
		//ASSERT(FALSE);
		wPMTGain = 2300;
	}
	
	return wPMTGain;
}

// 取得系统定义的预设温度参数
// 函数 CInstancePCR::GetSysTemp
// 作用：读取GetSysTemp。
// 参数：nType：整数。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetSysTemp(eSysTempType nType)
{
	float fTemp = 0.0f;
	switch(nType)
	{
	case SYS_TEMP_CTRL_TOP:
		fTemp = m_sStructurePara.cTempCtrlTop;
		break;
	case SYS_TEMP_CTRL_LOWER:
		fTemp = m_sStructurePara.cTempCtrlLower;
		break;
	case SYS_TEMP_LID_TOP:
		fTemp = m_sStructurePara.cLidTempTop;
		break;
	case SYS_TEMP_LID_LOWER:
		fTemp = m_sStructurePara.cLidTempLower;
		break;
	case SYS_TEMP_PELTIER_LOWER:
		fTemp = m_sStructurePara.cTempPeltierLower;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return fTemp;
}


// 设置热盖温度
// 函数 CInstancePCR::SetLidHeaterTemp
// 作用：设置SetLidHeaterTemp。
// 参数：fTemp：小数。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::SetLidHeaterTemp(float fTemp)
{
	WORD wTemp = (WORD)(fTemp * RESOLUTION_TEMP + 0.5);
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN7, PCR_LID_TEMP, wTemp);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN7, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = TEMP_CHANNEL_LID; // 表示热盖
		m_iErrorPara2 = wTemp; // 温度
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_LASER_SET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_TEMP_SET_TIMEOUT;
		}
	}

	delete pCommand;
	delete pStatus;

	return bReturn;
}

// 取得仪器控温时到达目标温度的合理偏差
// 下位机反馈“温度到标识位”置1时， 实际温度值与目标温度值之间所允许的合理偏差范围
// 函数 CInstancePCR::GetTempLegalGap
// 作用：读取GetTempLegalGap。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetTempLegalGap()
{
	float fReturn = m_sStructurePara.cTempLegalGap;
	fReturn /= 10;
	return fReturn;
}

// 函数 CInstancePCR::GetLidTempLegalGap
// 作用：读取GetLidTempLegalGap。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetLidTempLegalGap()
{
	float fReturn = m_sStructurePara.cLidTempLegalGap;
	fReturn /= 10;
	return fReturn;
}

// 热盖升温最长时间，单位：秒，默认15分钟
// 函数 CInstancePCR::GetMaxLidHeatSecond
// 作用：读取GetMaxLidHeatSecond。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetMaxLidHeatSecond()
{ 
	int iMaxTime = m_sStructurePara.cLidTempMaxTime * 60;
	return iMaxTime;
}

// 取得最长控温时间，默认60秒
// 函数 CInstancePCR::GetMaxTempCtrlSecond
// 作用：读取GetMaxTempCtrlSecond。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetMaxTempCtrlSecond()
{
	int iMaxTime = m_sStructurePara.cTempCtrlMaxTime;
	return iMaxTime;
}

// 函数 CInstancePCR::GetLidHeatNormalSecond
// 作用：读取GetLidHeatNormalSecond。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetLidHeatNormalSecond()
{
	if(0 == m_sStructurePara.cLidHeader)
	{
		return 0;
	}
	return 0;
}

// 函数 CInstancePCR::GetLidState
// 作用：读取GetLidState。
// 参数：iStatus：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetLidState(int& iStatus)
{
	return -1;
}

// 取得有几个加热通道，不包括热盖
// 函数 CInstancePCR::GetTempChannelCount
// 作用：读取GetTempChannelCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetTempChannelCount()
{
	int iCount = m_sStructurePara.cTempChannelCount;
	if (m_sStructurePara.cLidHeader == 1)
	{
		iCount --;
	}
	return iCount;
}

// 函数 CInstancePCR::GetMeltPreDelay
// 作用：读取GetMeltPreDelay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetMeltPreDelay()
{
	int iMaxTime = m_sStructurePara.cMeltPreDelay;
	return iMaxTime;
}

// 熔解单步最小增量
// 函数 CInstancePCR::GetMeltMinIncrement
// 作用：读取GetMeltMinIncrement。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetMeltMinIncrement()
{
	float fIncrement = m_sStructurePara.cMeltMinIncrement;
	fIncrement /= 100;
	return fIncrement;
}

// 熔解单步等待时间
// 函数 CInstancePCR::GetMeltStepDelay
// 作用：读取GetMeltStepDelay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetMeltStepDelay()
{
	int iDelay = m_sStructurePara.cMeltStepDelay;
	iDelay = (iDelay + 9) / 10;
	return iDelay;
}

// 扫描指定通道一次需要时间，单位
// 函数 CInstancePCR::GetScanOnceTime
// 作用：读取GetScanOnceTime。
// 参数：bIsSecond：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetScanOnceTime(BOOL bIsSecond)
{
	int iMaxTime = m_sStructurePara.wScanOnceTime; 
	if (bIsSecond)
	{
		iMaxTime /= 100;
	}
	return iMaxTime;
}

// 完成一次扫描X轴运行次数
// 函数 CInstancePCR::GetScanRowCount
// 作用：读取GetScanRowCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetScanRowCount()
{
	int iCount = 0;

	if (m_sStructurePara.cScanPathCount == 1)
	{
		iCount = m_sStructurePara.cPlateRowCount;
	}
	else if (m_sStructurePara.cScanPathCount == 2)
	{
		iCount = m_sStructurePara.cPlateRowCount + 2;
	}
	else
	{
		ASSERT(FALSE);
	}

	return iCount;
}

// 取得校准通道
// 函数 CInstancePCR::GetCalibrateChannel
// 作用：读取GetCalibrateChannel。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCount、GetAt。
int CInstancePCR::GetCalibrateChannel()
{
	int iChannel = -1;
	for (int i=0; i<m_arrayFilter.GetCount(); i++)
	{
		tagScanChannelInfo* pChannel = (tagScanChannelInfo*)m_arrayFilter.GetAt(i);
		if (pChannel->iType == 4)
		{
			iChannel = pChannel->iEmPosition;
			break;
		}
	}

	return iChannel;
}

// 只返回扫描光路通道数，返回存在的通道总数，中间不用通道也是存在
// 函数 CInstancePCR::GetScanChannelCount
// 作用：读取GetScanChannelCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCount、GetAt。
int CInstancePCR::GetScanChannelCount()
{ 
	int iMaxChannel = -1;
	for (int i=0; i<m_arrayFilter.GetCount(); i++)
	{
		tagScanChannelInfo* pChannel = (tagScanChannelInfo*)m_arrayFilter.GetAt(i);
		if (pChannel->iType != 4)
		{
			if (pChannel->iExPosition > iMaxChannel)
			{
				iMaxChannel = pChannel->iExPosition;
			}
		}
	}

	if (m_arrayFilter.GetCount() > iMaxChannel)
	{
		return m_arrayFilter.GetCount();
	}
	else
	{
		return iMaxChannel;
	}
} 

// 函数 CInstancePCR::SetMultiTemp
// 作用：设置SetMultiTemp。
// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数；fRate：小数；cMode；bSelfCheck：是或否。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::SetMultiTemp(float fTemp1, float fTemp2, float fTemp3, float fRate, BYTE cMode,BOOL bSelfCheck /*= FALSE*/)
{
	WORD wTemp1 = (int)(fTemp1 * RESOLUTION_TEMP + 0.5);
	WORD wTemp2 = (int)(fTemp2 * RESOLUTION_TEMP + 0.5);
	WORD wTemp3 = (int)(fTemp3 * RESOLUTION_TEMP + 0.5);
	WORD wRate = (int)(fRate * RESOLUTION_TEMP + 0.5);

	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN14, PCR_SET_TEMP, wTemp1, wTemp2, wTemp3, wRate, cMode);

	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand,CMD_SEND_LEN14, &pStatus,iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else if(bSelfCheck && NULL != pStatus && iReceiveFrameLen > 2 && (0x01 == pStatus[iReceiveFrameLen -2]))
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 7; // 表示3个温度通道
		m_iErrorPara2 = wTemp1; // 温度
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_LASER_SET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_TEMP_SET_TIMEOUT;
		}
	}

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

// 函数 CInstancePCR::SetPWMTemp
// 作用：设置SetPWMTemp。
// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数；Pwm1；Pwm2；Pwm3。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 memset、SendCommandRepeatedly。
BOOL CInstancePCR::SetPWMTemp(float fTemp1,float fTemp2,float fTemp3,WORD Pwm1,WORD Pwm2,WORD Pwm3)
{
	WORD wTemp1 = (int)(fTemp1 * RESOLUTION_TEMP + 0.5);
	WORD wTemp2 = (int)(fTemp2 * RESOLUTION_TEMP + 0.5);
	WORD wTemp3 = (int)(fTemp3 * RESOLUTION_TEMP + 0.5);

	BYTE* pCmd = new BYTE[17];
	if(NULL == pCmd)
	{
		return FALSE;
	}
	memset(pCmd,0,17);

	pCmd[0] = PCR_DNSEND;
	pCmd[1] = PCR_SETPWM;
	pCmd[3] = 17;

	//温度值
	pCmd[4] = (BYTE)(wTemp1 >> 8);
	pCmd[5] = (BYTE)(wTemp1 & 0xFF);
	pCmd[6] = (BYTE)(wTemp2 >> 8);
	pCmd[7] = (BYTE)(wTemp2 & 0xFF);
	pCmd[8] = (BYTE)(wTemp3 >> 8);
	pCmd[9] = (BYTE)(wTemp3 & 0xFF);

	//PWM值
	pCmd[10] = (BYTE)(Pwm1 >> 8);
	pCmd[11] = (BYTE)(Pwm1 & 0xFF);
	pCmd[12] = (BYTE)(Pwm2 >> 8);
	pCmd[13] = (BYTE)(Pwm2 & 0xFF);
	pCmd[14] = (BYTE)(Pwm3 >> 8);
	pCmd[15] = (BYTE)(Pwm3 & 0xFF);

	//校验和
	for(int i = 0;i < 16;++i)
	{
		pCmd[16] += pCmd[i];
	}

	int iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCmd,17, &pStatus,iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 7; // 表示3个温度通道
		m_iErrorPara2 = wTemp1; // 温度
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_LASER_SET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_TEMP_SET_TIMEOUT;
		}
	}

	delete [] pCmd;
	if(NULL != pStatus)
	{
		delete pStatus;
	}

	return bReturn;
}

// 函数 CInstancePCR::SetLaserStatus
// 作用：设置SetLaserStatus。
// 参数：cType；cStatus：字符串。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::SetLaserStatus(BYTE cType, BYTE cStatus)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN7, PCR_LASER_CTRL, cType, cStatus);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN7, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = cType; 
		m_iErrorPara2 = cStatus; 
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_LASER_SET_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_LASER_SET_TIMEOUT;
		}
	}

	delete pCommand;
	delete pStatus;

	return bReturn;
}

// 读取指定通道温度
// 函数 CInstancePCR::ReadChannelTemp
// 作用：读取ReadChannelTemp。
// 参数：cChannel；fTempCh：小数；bToTarget：是或否。
// 返回：返回是或否。
// 过程：函数里会调用 SetLongSendTime、NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::ReadChannelTemp(BYTE cChannel, float &fTempCh, BOOL& bToTarget)
{
	if (cChannel == TEMP_CHANNEL_ENVIRONMENT)
	{
		m_pComPort->SetLongSendTime(TRUE);
	}

	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN6, PCR_READ_TEMP, cChannel);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN6, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		ASSERT(iReceiveFrameLen == 9);

		int iTemp = 0;
		iTemp = pStatus[iReceiveFrameLen -5];
		iTemp = iTemp<< 8;
		iTemp &= 0xFF00;
		iTemp |= pStatus[iReceiveFrameLen -4];
		fTempCh = ((float)iTemp) / RESOLUTION_TEMP;
		bToTarget = (BOOL)pStatus[iReceiveFrameLen -3];

		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = cChannel; // 表示通道
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_TEMP_READ_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_TEMP_READ_TIMEOUT;
		}
	}

	if(NULL != pCommand)
	{
		delete [] pCommand;
	}
	if(NULL != pStatus)
	{
		delete [] pStatus;
	}

	if(cChannel == TEMP_CHANNEL_ENVIRONMENT)
	{
		m_pComPort->SetLongSendTime(FALSE);
	}

	return bReturn;
}

// 读取PCR仪温度
// 函数 CInstancePCR::ReadPCRTemp
// 作用：读取ReadPCRTemp。
// 参数：fTempPCR：小数；bToTarget：是或否。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::ReadPCRTemp(float &fTempPCR, BOOL& bToTarget)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN6, PCR_READ_PCRTEMP, 0);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN6, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		ASSERT(iReceiveFrameLen == 9);

		int iTemp = 0;
		iTemp = pStatus[iReceiveFrameLen -5];
		iTemp = iTemp<< 8;
		iTemp &= 0xFF00;
		iTemp |= pStatus[iReceiveFrameLen -4];
		fTempPCR = ((float)iTemp) / RESOLUTION_TEMP;
		bToTarget = (BOOL)pStatus[iReceiveFrameLen -3];

		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 0; // 无效值
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_PCR_TEMP_READ_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_PCR_TEMP_READ_TIMEOUT;
		}
	}

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

// 函数 CInstancePCR::ReadFLUData
// 作用：读取ReadFLUData。
// 参数：arrayData；cChannel；cFrmIndex。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly、Add。
BOOL CInstancePCR::ReadFLUData(CUIntArray& arrayData, BYTE cChannel, BYTE cFrmIndex)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN7, PCR_READ_FLUDATA, cChannel, cFrmIndex);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN7, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		for (int i=4; i+1<iReceiveFrameLen-2; i+=2)
		{
			UINT nFludata = 0;
			nFludata = pStatus[i+1];
			nFludata = nFludata<< 8;
			nFludata &= 0xFF00;
			nFludata |= pStatus[i];
			arrayData.Add(nFludata);
		}
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = cChannel;
		m_iErrorPara2 = cFrmIndex;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_PCR_FLU_READ_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_PCR_FLU_READ_TIMEOUT;
		}
	}

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

// 函数 CInstancePCR::ReadAllFLUData
// 作用：读取ReadAllFLUData。
// 参数：pAryData：指针，指向调用方传入的对象；iChanNum：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetScanChannelCount、ReadFLUData。
BOOL CInstancePCR::ReadAllFLUData(CUIntArray* pAryData,int iChanNum)
{
	if(NULL == pAryData)
	{
		return FALSE;
	}
	if(iChanNum != GetScanChannelCount())
	{
		return FALSE;
	}

	BOOL bReturn = FALSE;

	for (int ichannel = 1;ichannel <= iChanNum;++ichannel)
	{
		bReturn = ReadFLUData(pAryData[ichannel - 1],ichannel);
		if(!bReturn)
		{
			break;
		}
	}

	return bReturn;
}

// 读取设备状态，在实验过程中使用
// 函数 CInstancePCR::ReadDeviceStatus
// 作用：读取ReadDeviceStatus。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly、SetDeviceStatusBy。
BOOL CInstancePCR::ReadDeviceStatus()
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN5, PCR_DEVICE_STATUS, 0);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN5, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		SetDeviceStatusBy(iReceiveFrameLen - 6,pStatus + 4);
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 0; // 无效值
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_PCR_STATUS_READ_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_PCR_STATUS_READ_TIMEOUT;
		}


	}

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

// 根据返回参数对仪器状态进行保存
// 函数 CInstancePCR::SetDeviceStatusBy
// 作用：设置SetDeviceStatusBy。
// 参数：iLength：整数；pStatus：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::SetDeviceStatusBy(int iLength, BYTE* pStatus)
{
	m_sDeviceStatus.cXMot = (pStatus[0] & (1<<1)) >> 1;
	m_sDeviceStatus.cYMot =  (pStatus[0] & (1<<2)) >> 2;
	m_sDeviceStatus.cZMot = (pStatus[0] & (1<<3)) >> 3; 
	m_sDeviceStatus.cUMot = (pStatus[0] & (1<<4)) >> 4; 
	m_sDeviceStatus.cMotSense = (pStatus[0] & (1<<5)) >> 5; 
	m_sDeviceStatus.cEeprom = (pStatus[0] & (1<<6)) >> 6; 
	m_sDeviceStatus.cPMT =  (pStatus[0] & (1<<7)) >> 7;

	m_sDeviceStatus.cPETUnit1 = (pStatus[1] & (1)) ;
	m_sDeviceStatus.cPETUnit2 = (pStatus[1] & (1<<1)) >> 1; 
	m_sDeviceStatus.cPETUnit3 =  (pStatus[1] & (1<<2)) >> 2;
	m_sDeviceStatus.cCap =  (pStatus[1] & (1<<3)) >> 3; 
	m_sDeviceStatus.cFanState = (pStatus[1] & (1<<4)) >> 4;
	m_sDeviceStatus.cAuxerState = (pStatus[1] & (1<<5)) >> 5;
	m_sDeviceStatus.cA4940Rst =  (pStatus[1] & (1<<6)) >> 6;
	m_sDeviceStatus.cSysBox = (pStatus[1] & (1<<7)) >> 7;

	// 协议修改增加了2个字节作为返回参数
	if (iLength > 2)
	{
		m_sDeviceStatus.cLid = (pStatus[2] & (1)) ;
	}
}


// 读取设备状态（读取下位机运行的状态，包括各个硬件设备的标志、错误等，仪器运行状态69字节）
// 该命令在指令交互过程中参数解析异常时调用 
// 函数 CInstancePCR::ReadHardwareStatus
// 作用：读取ReadHardwareStatus。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly、SetHardwareStatus。
BOOL CInstancePCR::ReadHardwareStatus()
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN5, PCR_HARDWARE_STATUS, 0);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN5, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		SetHardwareStatus(pStatus+4);
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 0; // 无效值
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_PCR_STATUS_READ_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_PCR_STATUS_READ_TIMEOUT;
		}
	}

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

// 函数 CInstancePCR::SetHardwareStatus
// 作用：设置SetHardwareStatus。
// 参数：state。
// 返回：没有返回值。
// 过程：函数里会调用 WORD。
void CInstancePCR::SetHardwareStatus(BYTE* state)
{
	m_sHardwareStatus.nDevRun = state[0];    ///< 
	m_sHardwareStatus.nXMotState = state[1];  ///< 
	m_sHardwareStatus.wXMotPos = state[2]; ///< 
	m_sHardwareStatus.wXMotPos = WORD(m_sHardwareStatus.wXMotPos << 8) + state[3];
	m_sHardwareStatus.nXMotDirection = state[4]; ///< 

	m_sHardwareStatus.nYMotState = state[5];  ///< 
	m_sHardwareStatus.wYMotPos = state[6]; ///< 
	m_sHardwareStatus.wYMotPos = WORD(m_sHardwareStatus.wXMotPos << 8) + state[7];
	m_sHardwareStatus.nYMotDirection = state[8]; ///< 

	m_sHardwareStatus.nZMotState = state[9];  ///< 
	m_sHardwareStatus.wZMotPos = state[10]; ///< 
	m_sHardwareStatus.wZMotPos = WORD(m_sHardwareStatus.wXMotPos << 8) + state[11];
	m_sHardwareStatus.nZMotDirection = state[12]; ///< 

	m_sHardwareStatus.nUMotState = state[13];  ///< 
	m_sHardwareStatus.wUMotPos = state[14]; ///< 
	m_sHardwareStatus.wUMotPos = WORD(m_sHardwareStatus.wXMotPos << 8) + state[15];
	m_sHardwareStatus.nUMotDirection = state[16]; ///< 

	m_sHardwareStatus.nMotSensor = state[17];  ///< 
	m_sHardwareStatus.nLED = state[18];        ///< 
	m_sHardwareStatus.nPmtAnalogState =  state[19];      ///< 
	m_sHardwareStatus.nEeprom = state[20];       ///< 
	m_sHardwareStatus.nSMBUart = state[21];       ///< 

	m_sHardwareStatus.wPMT7512Out = state[22];   ///< 
	m_sHardwareStatus.wPMT7512Out = WORD(m_sHardwareStatus.wPMT7512Out << 8) + state[23];   ///< 

	m_sHardwareStatus.wSMBBackground = state[24];         ///<
	m_sHardwareStatus.wSMBBackground = WORD(m_sHardwareStatus.wSMBBackground << 8) + state[25];         ///<

	m_sHardwareStatus.nSysBox = state[26];///< 

	m_sHardwareStatus.wScannertTemp = state[27];    ///< 
	m_sHardwareStatus.wScannertTemp = WORD(m_sHardwareStatus.wScannertTemp << 8) + state[28];    ///< 

	m_sHardwareStatus.nSMBParameterInit = state[29];    ///< 
	m_sHardwareStatus.nWKBParaInit = state[30];    ///<
	m_sHardwareStatus.nSysStateLed = state[31]; ///< 
	m_sHardwareStatus.nCurtTempCtrlMode_TubeBlockMode = state[32];   ///< 

	m_sHardwareStatus.nPETUnit1State =  state[33];     ///< 

	m_sHardwareStatus.wPETUnit1Set = state[34];  ///< 
	m_sHardwareStatus.wPETUnit1Set = WORD(m_sHardwareStatus.wPETUnit1Set << 8) + state[35];  ///< 

	m_sHardwareStatus.wPETUnit1tTemp = state[36];  ///<
	m_sHardwareStatus.wPETUnit1tTemp = WORD(m_sHardwareStatus.wPETUnit1tTemp << 8) + state[37];  ///<

	m_sHardwareStatus.nPETUnit2State =  state[38];     ///< 

	m_sHardwareStatus.wPETUnit2Set = state[39];  ///< 
	m_sHardwareStatus.wPETUnit2Set = WORD(m_sHardwareStatus.wPETUnit2Set << 8) + state[40];  ///<

	m_sHardwareStatus.wPETUnit2tTemp = state[41];  ///<
	m_sHardwareStatus.wPETUnit2tTemp = WORD(m_sHardwareStatus.wPETUnit2tTemp << 8) + state[42];  ///<

	m_sHardwareStatus.nPETUnit3State =  state[43];     ///< 

	m_sHardwareStatus.wPETUnit3Set = state[44];  ///< 
	m_sHardwareStatus.wPETUnit3Set = WORD(m_sHardwareStatus.wPETUnit3Set << 8) + state[45];  ///< 

	m_sHardwareStatus.wPETUnit3tTemp = state[46];  ///<
	m_sHardwareStatus.wPETUnit3tTemp = WORD(m_sHardwareStatus.wPETUnit3tTemp << 8) + state[47];  ///<

	m_sHardwareStatus.nCapState = state[48];  ///<

	m_sHardwareStatus.wCapSet = state[49];  ///<
	m_sHardwareStatus.wCapSet = WORD(m_sHardwareStatus.wCapSet << 8) + state[50];  ///<

	m_sHardwareStatus.wCaptTemp = state[51];  ///<
	m_sHardwareStatus.wCaptTemp = WORD(m_sHardwareStatus.wCaptTemp << 8) + state[52];  ///<

	m_sHardwareStatus.nAuxerState = state[53];  ///<

	m_sHardwareStatus.wAuxerSet = state[54];  ///<
	m_sHardwareStatus.wAuxerSet = WORD(m_sHardwareStatus.wAuxerSet << 8) + state[55];  ///<

	m_sHardwareStatus.wFanTemp = state[56];  ///<
	m_sHardwareStatus.wFanTemp = WORD(m_sHardwareStatus.wFanTemp << 8) + state[57];  ///<

	m_sHardwareStatus.nFanState = state[58];  ///<

	m_sHardwareStatus.wFanSet = state[59];  ///<
	m_sHardwareStatus.wFanSet = WORD(m_sHardwareStatus.wFanSet << 8) + state[60];  ///<

	m_sHardwareStatus.wSysFanSet = state[61];  ///<
	m_sHardwareStatus.wSysFanSet = WORD(m_sHardwareStatus.wSysFanSet << 8) + state[62];  ///<

	m_sHardwareStatus.wSysFantTemp = state[63];  ///<
	m_sHardwareStatus.wSysFantTemp = WORD(m_sHardwareStatus.wSysFantTemp << 8) + state[64];  ///<

	m_sHardwareStatus.nA4940Rst = state[65];  ///<

	m_sHardwareStatus.wWKBBackground = state[66];  ///<
	m_sHardwareStatus.wWKBBackground = WORD(m_sHardwareStatus.wWKBBackground << 8) + state[67];  ///<

	m_sHardwareStatus.nAuxerHState = state[68];  ///<

	m_sHardwareStatus.wAuxerHSet = state[69];  ///<
	m_sHardwareStatus.wAuxerHSet = WORD(m_sHardwareStatus.wAuxerHSet << 8) + state[70];  ///<

	m_sHardwareStatus.nTransportlockState = state[71];  ///<

	m_sHardwareStatus.wPET1PWMOut = state[72];  ///<
	m_sHardwareStatus.wPET1PWMOut = WORD(m_sHardwareStatus.wPET1PWMOut << 8) + state[73];  ///<

	m_sHardwareStatus.wPET2PWMOut = state[74];  ///<
	m_sHardwareStatus.wPET2PWMOut = WORD(m_sHardwareStatus.wPET2PWMOut << 8) + state[75];  ///<

	m_sHardwareStatus.wPET3PWMOut = state[76];  ///<
	m_sHardwareStatus.wPET3PWMOut = WORD(m_sHardwareStatus.wPET3PWMOut << 8) + state[77];  ///<
}

// 输出硬件状态信息到错误日志中
// 函数 CInstancePCR::OutputHardwareStatusToErrorLog
// 作用：执行OutputHardwareStatusToErrorLog。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Format、_T、ErrorCode、GetInstance、WriteErrorLog。
void CInstancePCR::OutputHardwareStatusToErrorLog()
{
	CString str;
	str.Format(_T("ErrorCode(Hex) :%02X,\r\n%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,\r\n%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,\r\n%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,\r\n%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,\r\n%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,"),
	m_sHardwareStatus.nDevRun, m_sHardwareStatus.nXMotState, m_sHardwareStatus.wXMotPos,
	m_sHardwareStatus.nXMotDirection, m_sHardwareStatus.nYMotState, m_sHardwareStatus.wYMotPos, m_sHardwareStatus.nYMotDirection, m_sHardwareStatus.nZMotState,
	m_sHardwareStatus.wZMotPos, m_sHardwareStatus.nZMotDirection, m_sHardwareStatus.nUMotState, m_sHardwareStatus.wUMotPos, m_sHardwareStatus.nUMotDirection,
	m_sHardwareStatus.nMotSensor, m_sHardwareStatus.nLED, m_sHardwareStatus.nPmtAnalogState, m_sHardwareStatus.nEeprom, m_sHardwareStatus.nSMBUart,
	m_sHardwareStatus.wPMT7512Out, m_sHardwareStatus.wSMBBackground, m_sHardwareStatus.nSysBox, m_sHardwareStatus.wScannertTemp, m_sHardwareStatus.nSMBParameterInit,
	m_sHardwareStatus.nWKBParaInit, m_sHardwareStatus.nSysStateLed, m_sHardwareStatus.nCurtTempCtrlMode_TubeBlockMode, m_sHardwareStatus.nPETUnit1State, m_sHardwareStatus.wPETUnit1Set,
	m_sHardwareStatus.wPETUnit1tTemp, m_sHardwareStatus.nPETUnit2State, m_sHardwareStatus.wPETUnit2Set, m_sHardwareStatus.wPETUnit2tTemp, m_sHardwareStatus.nPETUnit3State,
	m_sHardwareStatus.wPETUnit3Set, m_sHardwareStatus.wPETUnit3tTemp,m_sHardwareStatus.nCapState, m_sHardwareStatus.wCapSet,m_sHardwareStatus.wCaptTemp,
	m_sHardwareStatus.nAuxerState, m_sHardwareStatus.wAuxerSet, m_sHardwareStatus.wFanTemp,m_sHardwareStatus.nFanState,m_sHardwareStatus.wFanSet,
	m_sHardwareStatus.wSysFanSet,m_sHardwareStatus.wSysFantTemp,m_sHardwareStatus.nA4940Rst,m_sHardwareStatus.wWKBBackground,m_sHardwareStatus.nAuxerHState,
	m_sHardwareStatus.wAuxerSet,m_sHardwareStatus.nTransportlockState,m_sHardwareStatus.wPET1PWMOut,m_sHardwareStatus.wPET2PWMOut,m_sHardwareStatus.wPET3PWMOut);

	CLogManager* pLogManager = CLogManager::GetInstance();
	pLogManager->WriteErrorLog(str);
}

// 函数 CInstancePCR::ReadLidTemperatureFromEEPROMPLCUsed
// 作用：读取ReadLidTemperatureFromEEPROMPLCUsed。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 memset、ReadEPROM、SetLidTem。
BOOL CInstancePCR::ReadLidTemperatureFromEEPROMPLCUsed()
{
	BYTE* pReceive = new BYTE[2];
	if(NULL == pReceive)
	{
		return FALSE;
	}
	memset(pReceive,0,sizeof(BYTE) * 2);
	if(ReadEPROM(0X550,2,pReceive))
	{
		SetLidTem(*((USHORT*)pReceive));
	}
	else
	{
		delete [] pReceive;
		return FALSE;
	}

	delete [] pReceive;

	return TRUE;
}

// 函数 CInstancePCR::ReadLidTemperatureFromEEPROMPLCUsed
// 作用：读取ReadLidTemperatureFromEEPROMPLCUsed。
// 参数：dLidTem：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 memset、ReadEPROM、SetLidTem。
BOOL CInstancePCR::ReadLidTemperatureFromEEPROMPLCUsed(double& dLidTem)
{
	BYTE* pReceive = new BYTE[2];
	if(NULL == pReceive)
	{
		return FALSE;
	}
	memset(pReceive,0,sizeof(BYTE) * 2);
	if(ReadEPROM(0X550,2,pReceive))
	{
		SetLidTem(*((USHORT*)pReceive));
	}
	else
	{
		delete [] pReceive;
		return FALSE;
	}

	dLidTem = *((USHORT*)pReceive);

	delete [] pReceive;

	return TRUE;
}

// 函数 CInstancePCR::WriteLidTemperaturePLCUsed
// 作用：把WriteLidTemperaturePLCUsed写入文件、仪器或界面。
// 参数：fLidTem：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 WriteEPROM、SetLidTem。
BOOL CInstancePCR::WriteLidTemperaturePLCUsed(float fLidTem)
{
	int iLidTem = fLidTem;

	if(iLidTem <= 0)
	{
		return FALSE;
	}

	if(!WriteEPROM(0X550,iLidTem,2))
	{
		return FALSE;
	}

	if(!SetLidTem(iLidTem))
	{
		return FALSE;
	}

	return TRUE;
}

// 函数 CInstancePCR::WriteLidPreheatTemperaturePLCUsed
// 作用：把WriteLidPreheatTemperaturePLCUsed写入文件、仪器或界面。
// 参数：fLidTem：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::WriteLidPreheatTemperaturePLCUsed(float fLidTem)
{
	return FALSE;
}

// 函数 CInstancePCR::ReadLidPreheatTemperaturePLCUsed
// 作用：读取ReadLidPreheatTemperaturePLCUsed。
// 参数：fLidPreheatTem：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::ReadLidPreheatTemperaturePLCUsed(float& fLidPreheatTem)
{
	return FALSE;
}

// 函数 CInstancePCR::GetInitChanDyeName
// 作用：读取GetInitChanDyeName。
// 参数：vecChanDyeName。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、GetScanChannelCount、push_back、_T、strTemp、Format。
int CInstancePCR::GetInitChanDyeName(vector<CString>& vecChanDyeName)
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
			vecChanDyeName.push_back(_T("ROX")); 
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

// 函数 CInstancePCR::CalculateExperimentTotalTimeSec
// 作用：计算CalculateExperimentTotalTimeSec。
// 参数：lnkSegItem；bUseLid：是或否；iVolume：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::CalculateExperimentTotalTimeSec(CLinkList<CSegItemInfo>& lnkSegItem,BOOL bUseLid,int iVolume)
{
	return 0;
}

// 函数 CInstancePCR::IsDemo
// 作用：判断IsDemo是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::IsDemo()
{
	return FALSE;
}

// 函数 CInstancePCR::GetMppcGainHigh
// 作用：读取GetMppcGainHigh。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetMppcGainHigh()
{
	return m_iMppcGainH;
}

// 函数 CInstancePCR::GetMppcGainMiddle
// 作用：读取GetMppcGainMiddle。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetMppcGainMiddle()
{
	return m_iMppcGainM;
}

// 函数 CInstancePCR::GetMppcGainLow
// 作用：读取GetMppcGainLow。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetMppcGainLow()
{
	return m_iMppcGainL;
}

// 函数 CInstancePCR::SetInstanceStatus
// 作用：设置SetInstanceStatus。
// 参数：eStatus。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::SetInstanceStatus(eInstanceStatus eStatus)
{
	m_eInstanceStatus = eStatus;
}

// 函数 CInstancePCR::GetInstanceStatus
// 作用：读取GetInstanceStatus。
// 参数：无。
// 返回：返回 eInstanceStatus。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
eInstanceStatus CInstancePCR::GetInstanceStatus()
{
	return m_eInstanceStatus;
}

// 函数 CInstancePCR::IsInstanceIdle
// 作用：判断IsInstanceIdle是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::IsInstanceIdle()
{
	return INSTANCE_READY == m_eInstanceStatus;
}

// 函数 CInstancePCR::GetPwmK1
// 作用：读取GetPwmK1。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetPwmK1()
{
	return m_fPwmK1;
}

// 函数 CInstancePCR::GetPwmB1
// 作用：读取GetPwmB1。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetPwmB1()
{
	return m_fPwmB1;
}

// 函数 CInstancePCR::GetPwmK2
// 作用：读取GetPwmK2。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetPwmK2()
{
	return m_fPwmK2;
}

// 函数 CInstancePCR::GetPwmB2
// 作用：读取GetPwmB2。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetPwmB2()
{
	return m_fPwmB2;
}

// 函数 CInstancePCR::GetPwmK3
// 作用：读取GetPwmK3。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetPwmK3()
{
	return m_fPwmK3;
}

// 函数 CInstancePCR::GetPwmB3
// 作用：读取GetPwmB3。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetPwmB3()
{
	return m_fPwmB3;
}

// 函数 CInstancePCR::SetEndCoolTemperature
// 作用：设置SetEndCoolTemperature。
// 参数：fTem：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::SetEndCoolTemperature(float fTem)
{
	m_fEndCoolTem = fTem;
}

// 函数 CInstancePCR::GetEndCoolTemperature
// 作用：读取GetEndCoolTemperature。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CInstancePCR::GetEndCoolTemperature()
{
	return m_fEndCoolTem;
}

// 函数 CInstancePCR::SetSleepMsAfterCool
// 作用：设置SetSleepMsAfterCool。
// 参数：iMs：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::SetSleepMsAfterCool(int iMs)
{
	if(iMs < 0)
	{
		iMs = 0;
	}
	m_iMsSlpAfterCool = iMs;
}

// 函数 CInstancePCR::GetSleepMsAfterCool
// 作用：读取GetSleepMsAfterCool。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetSleepMsAfterCool()
{
	return m_iMsSlpAfterCool;
}

// 函数 CInstancePCR::SetPWMInitWaitMs
// 作用：设置SetPWMInitWaitMs。
// 参数：iMs：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::SetPWMInitWaitMs(int iMs)
{
	if(iMs < 0)
	{
		iMs = 0;
	}
	m_iMsPwmInitWait = iMs;
}

// 函数 CInstancePCR::GetPWMInitWaitMs
// 作用：读取GetPWMInitWaitMs。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetPWMInitWaitMs()
{
	return m_iMsPwmInitWait;
}

// 函数 CInstancePCR::SaveParaForDemo
// 作用：把SaveParaForDemo写入文件、仪器或界面。
// 参数：strIniFile：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 _T、WritePrivateProfileString、Format。
void CInstancePCR::SaveParaForDemo(CString strIniFile)
{
	CString strValue;
	CString strAppName = _T("Instrument");

	::WritePrivateProfileString(strAppName, _T("PCRModel"), m_strModel, strIniFile);
	::WritePrivateProfileString(strAppName, _T("PCRVersion"), m_strVersion, strIniFile);

	strValue.Format(_T("%d"), m_sStructurePara.cTempMode);
	::WritePrivateProfileString(strAppName, _T("TempMode"), strValue, strIniFile);
	strValue.Format(_T("%d"), m_sStructurePara.cTempCtrl);
	::WritePrivateProfileString(strAppName, _T("TempCtrlMode"), strValue, strIniFile);
	strValue.Format(_T("%d"), m_sStructurePara.cLidHeader);
	::WritePrivateProfileString(strAppName, _T("HasLid"), strValue, strIniFile);

	strValue.Format(_T("%d"), m_sStructurePara.cPlateType);
	::WritePrivateProfileString(strAppName, _T("PlateType"), strValue, strIniFile);
	strValue.Format(_T("%d"), m_sStructurePara.cPlateCount);
	::WritePrivateProfileString(strAppName, _T("PlateCount"), strValue, strIniFile);
	strValue.Format(_T("%d"), m_sStructurePara.cPlateSortType);
	::WritePrivateProfileString(strAppName, _T("SortType"), strValue, strIniFile);
	strValue.Format(_T("%d"), m_sStructurePara.cPlateRowCount);
	::WritePrivateProfileString(strAppName, _T("RowCount"), strValue, strIniFile);
	strValue.Format(_T("%d"), m_sStructurePara.cPlateColCount);
	::WritePrivateProfileString(strAppName, _T("ColCount"), strValue, strIniFile);

}

// 函数 CInstancePCR::GetScanChannelInfo
// 作用：读取GetScanChannelInfo。
// 参数：iIndex：整数。
// 返回：返回指针 tagScanChannelInfo*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：函数里会调用 GetCount、GetAt。
tagScanChannelInfo* CInstancePCR::GetScanChannelInfo(int iIndex)
{
	if (iIndex >= 0 && iIndex < m_arrayFilter.GetCount())
	{
		tagScanChannelInfo* pChannel =  (tagScanChannelInfo*)m_arrayFilter.GetAt(iIndex);
		return pChannel;
	}
	return NULL; 
}

// 函数 CInstancePCR::GetScanChannelInfo
// 作用：读取GetScanChannelInfo。
// 参数：lnkScanChanInfo。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Clear、GetSize、GetAt、AddTail。
int CInstancePCR::GetScanChannelInfo(CLinkList<tagScanChannelInfo>& lnkScanChanInfo)
{
	lnkScanChanInfo.Clear();
	int iFltNum = m_arrayFilter.GetSize();
	tagScanChannelInfo *pScanChanInfo = NULL;
	for(int i = 0;i < iFltNum;++i)
	{
		pScanChanInfo = (tagScanChannelInfo*)m_arrayFilter.GetAt(i);
		if(NULL == pScanChanInfo)
		{
			continue;
		}

		lnkScanChanInfo.AddTail(*pScanChanInfo);
	}

	return 0;
}

// 函数 CInstancePCR::GetScanStartPos
// 作用：读取GetScanStartPos。
// 参数：无。
// 返回：返回 eScanStartPos。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
eScanStartPos CInstancePCR::GetScanStartPos()
{
	eScanStartPos	nScanStartPos = SCAN_START_LT;
	if (m_sStructurePara.cScanOrigin == 1)
	{
		nScanStartPos = SCAN_START_RT;
	}

	return nScanStartPos;
}

// 函数 CInstancePCR::GetScanColCount
// 作用：读取GetScanColCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetScanColCount()
{
	return m_sStructurePara.cPlateColCount;
}

// 函数 CInstancePCR::GetPlateInfo
// 作用：读取GetPlateInfo。
// 参数：pInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CInstancePCR::GetPlateInfo(tagPlateModeInfo* pInfo)
{
	pInfo->nPlateType = (ePlateModeType)m_sStructurePara.cPlateType;
	pInfo->iPlateCount = m_sStructurePara.cPlateCount;
	pInfo->nSortMode = (ePlateSortMode)m_sStructurePara.cPlateSortType;
	pInfo->iHoriCount = m_sStructurePara.cPlateColCount;
	pInfo->iVertCount = m_sStructurePara.cPlateRowCount;
}

// 函数 CInstancePCR::GetTempMode
// 作用：读取GetTempMode。
// 参数：无。
// 返回：返回 ePCRTempMode。
// 过程：函数里会调用 ePCRTempMode。
ePCRTempMode CInstancePCR::GetTempMode()
{
	return ePCRTempMode(m_sStructurePara.cTempMode);
}

// 函数 CInstancePCR::GetTempCtrlMode
// 作用：读取GetTempCtrlMode。
// 参数：无。
// 返回：返回 eTempCtrlMode。
// 过程：函数里会调用 eTempCtrlMode。
eTempCtrlMode CInstancePCR::GetTempCtrlMode()
{
	return eTempCtrlMode(m_sStructurePara.cTempCtrl);
}

// 是否有进出仓
// 函数 CInstancePCR::HasBox
// 作用：判断HasBox是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 BOOL。
BOOL CInstancePCR::HasBox()
{
	return BOOL(m_sStructurePara.cUseBox);
}

// 是否有热盖
// 函数 CInstancePCR::HasLid
// 作用：判断HasLid是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 BOOL。
BOOL CInstancePCR::HasLid()
{
	return BOOL(m_sStructurePara.cLidHeader);
}

// 函数 CInstancePCR::GetPreMeltMinSleepSec
// 作用：读取GetPreMeltMinSleepSec。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetPreMeltMinSleepSec()
{
	return m_iPreMeltMinSlpSec;
}

// 函数 CInstancePCR::SportModuleCheck
// 作用：执行SportModuleCheck。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 MotorReset、SetInstanceStatus。
int CInstancePCR::SportModuleCheck()
{
	int iErrId = 0;

	BOOL bReturn = MotorReset(PCR_XMOT_RESET);
	if(!bReturn)
	{
		iErrId = -1;
		goto COMMU_FAILED;
	}

	bReturn = MotorReset(PCR_YMOT_RESET);
	if (!bReturn)
	{
		iErrId = -2;
		goto COMMU_FAILED;
	}

	return 0;

COMMU_FAILED:
	SetInstanceStatus(INSTANCE_SELFCHECK_FAIL);
	return iErrId;
}

// 函数 CInstancePCR::SensorModuleCheck
// 作用：执行SensorModuleCheck。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetInstance、strTemp、_T、strTemFormat、strUnit、GetText。
int CInstancePCR::SensorModuleCheck()
{
	int iErrId = 0;
	float fTem = 0;
	BOOL bRet = FALSE,bTarget = FALSE;
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	CString strTemp(_T("")),strTemFormat(_T("%.2lf")),strUnit(_T(""));
	strUnit = pLangInfo->GetText(327);
	
	m_sensorMChkParam.ResetCheckResult();

	//环境温度传感器
	if(m_sensorMChkParam.IsCheckEnvirTsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_ENVIRONMENT,fTem,bTarget))
		{
			iErrId = -1;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetEnvirTsmRefH())
		{
			strTemp = pLangInfo->GetText(319); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetEnvirTsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetEnvirTsmRefL())
		{
			strTemp = pLangInfo->GetText(319); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetEnvirTsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}

	//热沉温度传感器
	if(m_sensorMChkParam.IsCheckHeatSinkTsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_HEATSINK,fTem,bTarget))
		{
			iErrId = -2;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetHeatSinkTsmRefH())
		{
			strTemp = pLangInfo->GetText(320); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetHeatSinkTsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetHeatSinkTsmRefL())
		{
			strTemp = pLangInfo->GetText(320); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetHeatSinkTsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}

	//热盖温度传感器
	if(m_sensorMChkParam.IsCheckLidTsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_LID,fTem,bTarget))
		{
			iErrId = -3;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetHeatSinkTsmRefH())
		{
			strTemp = pLangInfo->GetText(321); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetLidTsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetHeatSinkTsmRefL())
		{
			strTemp = pLangInfo->GetText(321); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetLidTsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}

	//帕尔贴1温度传感器
	if(m_sensorMChkParam.IsCheckPelt1Tsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_PET1,fTem,bTarget))
		{
			iErrId = -4;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetPelt1TsmRefH())
		{
			strTemp = pLangInfo->GetText(322); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPelt1TsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetPelt1TsmRefL())
		{
			strTemp = pLangInfo->GetText(322); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPelt1TsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}

	//帕尔贴2温度传感器
	if(m_sensorMChkParam.IsCheckPelt2Tsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_PET2,fTem,bTarget))
		{
			iErrId = -5;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetPelt2TsmRefH())
		{
			strTemp = pLangInfo->GetText(323); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPelt2TsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetPelt2TsmRefL())
		{
			strTemp = pLangInfo->GetText(323); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPelt2TsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}

	//帕尔贴3温度传感器
	if(m_sensorMChkParam.IsCheckPelt3Tsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_PET3,fTem,bTarget))
		{
			iErrId = -6;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetPelt3TsmRefH())
		{
			strTemp = pLangInfo->GetText(324); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPelt3TsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetPelt3TsmRefL())
		{
			strTemp = pLangInfo->GetText(324); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPelt3TsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}

	//电源温度传感器
	if(m_sensorMChkParam.IsCheckPowerTsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_POWER,fTem,bTarget))
		{
			iErrId = -7;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetPowerTsmRefH())
		{
			strTemp = pLangInfo->GetText(325); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPowerTsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetPowerTsmRefL())
		{
			strTemp = pLangInfo->GetText(325); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetPowerTsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}

	//扫描温度传感器
	if(m_sensorMChkParam.IsCheckScanTsm())
	{
		if(!ReadChannelTemp(TEMP_CHANNEL_SCAN,fTem,bTarget))
		{
			iErrId = -8;
			goto COMMU_FAILED;
		}
		if(fTem > m_sensorMChkParam.GetScanTsmRefH())
		{
			strTemp = pLangInfo->GetText(326); 
			strTemp += pLangInfo->GetText(317); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetScanTsmRefH());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
		else if(fTem < m_sensorMChkParam.GetScanTsmRefL())
		{
			strTemp = pLangInfo->GetText(326); 
			strTemp += pLangInfo->GetText(318); 
			strTemp.AppendFormat(strTemFormat,m_sensorMChkParam.GetScanTsmRefL());
			m_sensorMChkParam.AddCheckResult(strTemp);
		}
	}
	
	if(!m_sensorMChkParam.IsSuccessful())
	{
		return 1;
	}

	return 0;

COMMU_FAILED:
	SetInstanceStatus(INSTANCE_SELFCHECK_FAIL);
	return iErrId;
}

// 函数 CInstancePCR::HeatModeduleCheck
// 作用：执行HeatModeduleCheck。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 IsNeedCheck、strFormat、_T、strTemp、GetInstance、ResetCheckResult。
int CInstancePCR::HeatModeduleCheck()
{
	if(!m_heatModuleChkParam.IsNeedCheck())
	{
		return 1;
	}

	int iErrId = 0;
	BYTE byChanId = 5;
	BOOL bTarget = FALSE;
	int iSlpSec = 0,iSlpSec2 = 0;
	double dTemError = 0,dTemError2 = 0;
	float fTem = 0,fSetTem = 0,fOriginTem = 0,fLastTem = 0,fTemPeltierNotWork = 200,fTemPeltier1 = 0,fTemPeltier2 = 0,fTemPeltier3 = 0,fTemPublic = 0;
	CString strFormat(_T(",%.2lf-%.2lf,")),strTemp(_T(""));
	CPeltierCheckParam* pPeltierChkParam = NULL;
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	m_heatModuleChkParam.ResetCheckResult();

	//帕尔贴升降温检测
	for(int i = 0;i < 3;++i)
	{
		pPeltierChkParam = m_heatModuleChkParam.GetPeltierCheckParam(0);
		if(NULL != pPeltierChkParam && pPeltierChkParam->IsCheck())
		{
			//获取当前温度
			if(!ReadChannelTemp(++byChanId,fTem,bTarget))
			{
				iErrId = -1;
				goto COMMU_FAILED;
			}
			fOriginTem = fTem;

			//获取升温和降温参数
			if(fTem > pPeltierChkParam->GetTemperatureThreshold())
			{
				iSlpSec = pPeltierChkParam->GetDropTimeSec();
				dTemError = pPeltierChkParam->GetDropTemError();
				fSetTem = fTem - pPeltierChkParam->GetTemRiseDropRange();
				iSlpSec2 = pPeltierChkParam->GetRiseTimeSec();
				dTemError2 = pPeltierChkParam->GetRiseTemError();
			}
			else
			{
				iSlpSec = pPeltierChkParam->GetRiseTimeSec();
				dTemError = pPeltierChkParam->GetRiseTemError();
				fSetTem = fTem + pPeltierChkParam->GetTemRiseDropRange();
				iSlpSec2 = pPeltierChkParam->GetDropTimeSec();
				dTemError2 = pPeltierChkParam->GetDropTemError();
			}

			if(0 == i)
			{
				fTemPeltier1 = fSetTem;
				fTemPeltier2 = fTemPeltierNotWork;
				fTemPeltier3 = fTemPeltierNotWork;
			}
			else if(1 == i)
			{
				fTemPeltier1 = fTemPeltierNotWork;
				fTemPeltier2 = fSetTem;
				fTemPeltier3 = fTemPeltierNotWork;
			}
			else if(2 == i)
			{
				fTemPeltier1 = fTemPeltierNotWork;
				fTemPeltier2 = fTemPeltierNotWork;
				fTemPeltier3 = fSetTem;
			}

			//设置目标温度，降温或者升温
			if(!SetMultiTemp(fTemPeltier1,fTemPeltier2,fTemPeltier3,0,TEMP_CTRL_NORMAL,TRUE))
			{
				iErrId = -2;
				goto COMMU_FAILED;
			}

			//延时等待
			for(int j = 0;j < iSlpSec;++j)
			{
				if(!ReadChannelTemp(byChanId,fTemPublic,bTarget))
				{
					iErrId = -10;
					goto COMMU_FAILED;
				}

				if(abs(fTemPublic - fSetTem) <= dTemError)
				{
					break;
				}

				Sleep(1000);
			}

			//再次获取当前温度
			if(!ReadChannelTemp(byChanId,fTem,bTarget))
			{
				iErrId = -3;
				goto COMMU_FAILED;
			}
			fLastTem = fTem;

			/*if(!SetMultiTemp(655.35,655.35,655.35,0,TEMP_CTRL_NORMAL))
			{
			iErrId = -2;
			goto COMMU_FAILED;
			}*/

			//判断特定时间内是否到达目标温度特定范围内
			if(abs(fTem - fSetTem) > dTemError)
			{
				if(0 == i)
				{
					strTemp = pLangInfo->GetText(322);
				}
				else if(1 == i)
				{
					strTemp = pLangInfo->GetText(323);
				}
				else if(2 == i)
				{
					strTemp = pLangInfo->GetText(324);
				}
				strTemp.AppendFormat(strFormat,fOriginTem,fSetTem);
				strTemp += pLangInfo->GetText(329);
				m_heatModuleChkParam.AddCheckResult(strTemp);
			}


			if(0 == i)
			{
				fTemPeltier1 = fOriginTem;
				fTemPeltier2 = fTemPeltierNotWork;
				fTemPeltier3 = fTemPeltierNotWork;
			}
			else if(1 == i)
			{
				fTemPeltier1 = fTemPeltierNotWork;
				fTemPeltier2 = fOriginTem;
				fTemPeltier3 = fTemPeltierNotWork;
			}
			else if(2 == i)
			{
				fTemPeltier1 = fTemPeltierNotWork;
				fTemPeltier2 = fTemPeltierNotWork;
				fTemPeltier3 = fOriginTem;
			}

			//再次设置目标温度，升温或者降温
			if(!SetMultiTemp(fTemPeltier1,fTemPeltier2,fTemPeltier3,0,TEMP_CTRL_NORMAL,TRUE))
			{
				iErrId = -4;
				goto COMMU_FAILED;
			}

			//延时等待
			for(int j = 0;j < iSlpSec2;++j)
			{
				if(!ReadChannelTemp(byChanId,fTemPublic,bTarget))
				{
					iErrId = -11;
					goto COMMU_FAILED;
				}

				if(abs(fTemPublic - fOriginTem) <= dTemError)
				{
					break;
				}

				Sleep(1000);
			}

			//再次获取当前温度
			if(!ReadChannelTemp(byChanId,fTem,bTarget))
			{
				iErrId = -5;
				goto COMMU_FAILED;
			}

			//判断特定时间内是否到达目标温度特定范围内
			if(abs(fTem - fOriginTem) > dTemError2)
			{
				if(0 == i)
				{
					strTemp = pLangInfo->GetText(322);
				}
				else if(1 == i)
				{
					strTemp = pLangInfo->GetText(323);
				}
				else if(2 == i)
				{
					strTemp = pLangInfo->GetText(324);
				}
				strTemp.AppendFormat(strFormat,fLastTem,fOriginTem);
				strTemp += pLangInfo->GetText(329);
				m_heatModuleChkParam.AddCheckResult(strTemp);
			}
		}
	}
	
	//自检结束时，获取当前温度判断需不需要降温
	if(!ReadPCRTemp(fTem,bTarget))
	{
		iErrId = -6;
		goto COMMU_FAILED;
	}
	if(fTem > 45)
	{
		if(!SetMultiTemp(40,40,40,4,0))
		{
			iErrId = -7;
			goto COMMU_FAILED;
		}
		Sleep(10000);
	}
	
	//释放帕尔贴温控
	if(!SetMultiTemp(PCR_TEMP_RELEASE,PCR_TEMP_RELEASE,PCR_TEMP_RELEASE,0,TEMP_CTRL_NORMAL))
	{
		iErrId = -8;
		goto COMMU_FAILED;
	}

#ifdef _DEBUG
	/*if(!ReadHardwareStatus())
	{
	iErrId = -9;
	goto COMMU_FAILED;
	}*/
#endif

	if(!m_heatModuleChkParam.IsSuccessful())
	{
		return 2;
	}

	return 0;

COMMU_FAILED:
	SetInstanceStatus(INSTANCE_SELFCHECK_FAIL);
	return iErrId;
}

// 函数 CInstancePCR::OpticsModuleCheck
// 作用：执行OpticsModuleCheck。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetLaserStatus、Sleep、SetInstanceStatus。
int CInstancePCR::OpticsModuleCheck()
{
	int iErrId = 0;

	//打开所有LED灯
	if(!SetLaserStatus(2,0XFF))
	{
		iErrId = -1;
		goto COMMU_FAILED;
	}

	Sleep(3000);

	//关闭所有LED灯
	if(!SetLaserStatus(2,0))
	{
		iErrId = -2;
		goto COMMU_FAILED;
	}

	return 0;

COMMU_FAILED:
	SetInstanceStatus(INSTANCE_SELFCHECK_FAIL);
	return iErrId;
}

// 函数 CInstancePCR::GetCheckResultString
// 作用：读取GetCheckResultString。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 strTemp、_T、IsSuccessful、GetCheckResult。
CString CInstancePCR::GetCheckResultString()
{
	CString strTemp(_T(""));

	if(!m_sensorMChkParam.IsSuccessful())
	{
		strTemp += m_sensorMChkParam.GetCheckResult();
		strTemp += _T("\n");
	}

	if(!m_heatModuleChkParam.IsSuccessful())
	{
		strTemp += m_heatModuleChkParam.GetCheckResult();
		strTemp += _T("\n");
	}

	return strTemp;
}

// 函数 CInstancePCR::ReadDeviceParamsFromEPROM
// 作用：读取ReadDeviceParamsFromEPROM。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 memset、clock、ReadLongEPROM、memcpy。
BOOL CInstancePCR::ReadDeviceParamsFromEPROM()
{
	BYTE* pReceive = new BYTE[SIZE_DEVICE_PARAM];
	memset(pReceive, 0, sizeof(BYTE)*SIZE_DEVICE_PARAM);

	UINT nAddress = 0;

#ifdef _DEBUG
	clock_t ckStart = clock();
#endif

	BOOL bReturn = ReadLongEPROM(nAddress, SIZE_DEVICE_PARAM, pReceive);

#ifdef _DEBUG
	clock_t ckEnd = clock() - ckStart;
#endif

	if(bReturn)
	{
		memcpy(&m_sDevicePara, pReceive, SIZE_DEVICE_PARAM);
	}

	delete [] pReceive;
	pReceive = nullptr;
	return bReturn;
}

// 函数 CInstancePCR::ReadStructureParamsFromEPROM
// 作用：读取ReadStructureParamsFromEPROM。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 memset、ReadLongEPROM、BOOL、memcpy、ReadEPROM、ReadLidTemperatureFromEEPROMPLCUsed。
BOOL CInstancePCR::ReadStructureParamsFromEPROM()
{
	UINT nLength = 0x200;
	UINT nAddress = 0x2000;
	BYTE* pReceive = new BYTE[nLength];
	memset(pReceive, 0, sizeof(BYTE)*nLength);

	BOOL bReturn = ReadLongEPROM(nAddress, nLength, pReceive);
	if (bReturn)
	{
		BYTE cUsePara = BOOL(*pReceive);
		if (cUsePara == 1)
		{
			memcpy(&m_sStructurePara, pReceive+1, nLength-1);
		}
		else
		{
			//读取热盖温度
			nAddress = 0X2027;
			if(ReadEPROM(nAddress, 1, pReceive)) // 0X550
			{
				m_sStructurePara.cLidTempTop = *pReceive;
				if (m_sStructurePara.cLidTempTop == 255 || m_sStructurePara.cLidTempTop == 0)
				{
					m_sStructurePara.cLidTempTop = 90;
				}
				bReturn = TRUE; 
			}
		}
	}

	//读取仪器实际使用到的热盖温度（EEPROM），并写入到0X2027地址
	if(bReturn)
	{
		bReturn = ReadLidTemperatureFromEEPROMPLCUsed();
	}

	delete [] pReceive;
	pReceive = NULL;

	return bReturn;
}

// 读取指定地址和长度的EEPROM参数
// 函数 CInstancePCR::ReadEPROM
// 作用：读取ReadEPROM。
// 参数：nAddress：整数；cGetLength；pReceive：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly、memcpy。
BOOL CInstancePCR::ReadEPROM(UINT nAddress, BYTE cGetLength, BYTE* pReceive)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN9, PCR_RDEE, nAddress, cGetLength);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN9, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		memcpy(pReceive,&pStatus[4], iReceiveFrameLen - 6);
		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_READ_EEPROM_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_READ_EEPROM_TIMEOUT;
		}

		m_iErrorPara1 = nAddress;
		m_iErrorPara1 = cGetLength;
	}

	delete pCommand;
	delete pStatus;

	return bReturn;
}

// 函数 CInstancePCR::WriteEPROM
// 作用：把WriteEPROM写入文件、仪器或界面。
// 参数：nAddress：整数；iData：整数；iDataLen：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 memset、BYTE、GetByteSum、SendCommandRepeatedly。
BOOL CInstancePCR::WriteEPROM(UINT nAddress,int iData,int iDataLen)
{
	if(iDataLen < 1)
	{
		return FALSE;
	}

	int iCmdLen = 8 + iDataLen;
	BYTE* pCommand = new BYTE[iCmdLen];
	if(NULL == pCommand)
	{
		return FALSE;
	}
	memset(pCommand,0,iCmdLen);

	pCommand[0] = PCR_DNSEND;//帧头
	pCommand[1] = PCR_WDEE; //命令字
	pCommand[3] = iCmdLen; //长度
	pCommand[4] = (BYTE)((nAddress & 0xFF0000) >> 16);
	pCommand[5] = (BYTE)((nAddress & 0xFF00) >> 8);
	pCommand[6] = (BYTE)(nAddress & 0xFF);

	for(int i = 0;i < iDataLen;++i)
	{
		pCommand[7 + i] = BYTE((iData >> (i * 8)) & 0XFF); 
	}
	pCommand[iCmdLen - 1] = m_pComPort->GetByteSum(pCommand,iCmdLen - 1);//校验和

	int iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand,iCmdLen, &pStatus,iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if (iReturn == CSerialPortPCR::RETURN_OK)
	{
		bReturn = TRUE;
	}
	else
	{
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_READ_EEPROM_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_READ_EEPROM_TIMEOUT;
		}

		m_iErrorPara1 = nAddress;
		m_iErrorPara1 = iDataLen;
	}

	delete [] pCommand;
	delete [] pStatus;

	return bReturn;
}

// 函数 CInstancePCR::GetLidTem
// 作用：读取GetLidTem。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CInstancePCR::GetLidTem()
{
	return m_sStructurePara.cLidTempTop;
}

// 函数 CInstancePCR::SetLidTem
// 作用：设置SetLidTem。
// 参数：iLidTem：整数。
// 返回：返回是或否。
// 过程：函数里会调用 BYTE、WriteEPROM。
BOOL CInstancePCR::SetLidTem(int iLidTem)
{
	m_sStructurePara.cLidTempTop = BYTE(iLidTem);
	BOOL bReturn = WriteEPROM(0X2027, BYTE(iLidTem), 1);

	return bReturn;
}

// 读取超过一次传输长度的数据
// 函数 CInstancePCR::ReadLongEPROM
// 作用：读取ReadLongEPROM。
// 参数：nAddress：整数；nGetLength：整数；pReceive：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 ReadEPROM。
BOOL CInstancePCR::ReadLongEPROM(UINT nAddress, UINT nGetLength,BYTE* pReceive)
{
	BOOL bReturn = FALSE;
	UINT nEachLen = 249;
	int  iReadNum = nGetLength / nEachLen;
	UINT nRemain = nGetLength % nEachLen;

	for (int i=0; i<iReadNum; i++)
	{
		bReturn = ReadEPROM(nAddress, nEachLen, &pReceive[i*nEachLen]);
		if (!bReturn) 
		{
			delete [] pReceive;
			pReceive = nullptr;
			return bReturn;
		}
		nAddress += nEachLen;
	}

	if (nRemain > 0)
	{
		bReturn = ReadEPROM(nAddress, nRemain, &pReceive[nEachLen*iReadNum]);
	}

	return bReturn;
}

// 函数 CInstancePCR::Reinitialize
// 作用：执行Reinitialize。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 Reset、Hello、Initialize。
BOOL CInstancePCR::Reinitialize()
{
	BOOL bReturn = m_pComPort->Reset();
	if(bReturn)
	{
		bReturn = Hello();
		//bReturn = Initialize();
	}
	return bReturn;
}


// 函数 CInstancePCR::ReadAllTemp
// 作用：读取ReadAllTemp。
// 参数：iTempCount：整数；pTemp：指针，指向调用方传入的对象；bToTarget：是或否。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、SendCommandRepeatedly。
BOOL CInstancePCR::ReadAllTemp(int iTempCount, float* pTemp, BOOL& bToTarget)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN5, PCR_READ_SIX_TEMP, 0);
	int   iReceiveFrameLen = 0;
	BYTE* pStatus = NULL;
	int iReturn = m_pComPort->SendCommandRepeatedly(pCommand, CMD_SEND_LEN5, &pStatus, iReceiveFrameLen);
	BOOL bReturn = FALSE;
	if(CSerialPortPCR::RETURN_OK == iReturn)
	{
		ASSERT(19 == iReceiveFrameLen);

		int Temp = 0;
		BOOL bTargetVal = FALSE;

		Temp = pStatus[iReceiveFrameLen - 15];
		Temp = Temp<< 8;
		Temp &= 0xFF00;
		Temp |= pStatus[iReceiveFrameLen - 14];
		pTemp[0] = (float)(Temp / RESOLUTION_TEMP);

		Temp = pStatus[iReceiveFrameLen - 13];
		Temp = Temp<< 8;
		Temp &= 0xFF00;
		Temp |= pStatus[iReceiveFrameLen - 12];
		pTemp[1] = (float)(Temp / RESOLUTION_TEMP);

		Temp = pStatus[iReceiveFrameLen - 11];
		Temp = Temp<< 8;
		Temp &= 0xFF00;
		Temp |= pStatus[iReceiveFrameLen - 10];
		pTemp[2] = (float)(Temp / RESOLUTION_TEMP);

		Temp = pStatus[iReceiveFrameLen - 9];
		Temp = Temp<< 8;
		Temp &= 0xFF00;
		Temp |= pStatus[iReceiveFrameLen - 8];
		pTemp[3] = (float)(Temp / RESOLUTION_TEMP);

		Temp = pStatus[iReceiveFrameLen - 7];
		Temp = Temp<< 8;
		Temp &= 0xFF00;
		Temp |= pStatus[iReceiveFrameLen - 6];
		pTemp[4] = (float)(Temp / RESOLUTION_TEMP);

		Temp = pStatus[iReceiveFrameLen - 5];
		Temp = Temp<< 8;
		Temp &= 0xFF00;
		Temp |= pStatus[iReceiveFrameLen - 4];
		pTemp[5] = (float)(Temp / RESOLUTION_TEMP);

		bTargetVal = pStatus[iReceiveFrameLen - 3];

		bReturn = TRUE;
	}
	else
	{
		m_eInstanceStatus = INSTANCE_ERROR;
		m_iErrorPara1 = 0; // 无效值
		m_iErrorPara2 = 0;
		if (iReturn == CSerialPortPCR::RETURN_FAIL)
		{
			m_uiErrorCode = ERR_PCR_TEMP_READ_FAIL;
		}
		else if (iReturn == CSerialPortPCR::RETURN_TIMEOUT)
		{
			m_uiErrorCode = ERR_PCR_TEMP_READ_TIMEOUT;
		}
	}

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

// 函数 CInstancePCR::CanRunExp
// 作用：判断CanRunExp是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::CanRunExp()
{
	return m_eInstanceStatus != INSTANCE_TEMP_LOW && m_eInstanceStatus != INSTANCE_TEMP_HIGH
		&& m_eInstanceStatus != INSTANCE_FLUO_LOW && m_eInstanceStatus != INSTANCE_FLUO_HIGH;
}

// 运输锁上锁
// 函数 CInstancePCR::TransportLock
// 作用：执行TransportLock。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CInstancePCR::TransportLock()
{
	return FALSE;
}
