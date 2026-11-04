// 【交接】 PCRInstanceLib\InstancePS384.cpp
// 作用：InstancePS384。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInstancePS384、InitStructurePara、ReadAllFLUData、ReadFLUData384、NewSendCommand、GetByteSum、SendCommandRepeatedly、Add。
#include "StdAfx.h"
#include "InstancePS384.h"
#include "ErrorCodeDefine.h"


// 函数 CInstancePS384::CInstancePS384
// 作用：执行CInstancePS384。
// 参数：pComPort：指针，指向调用方传入的对象；CInstancePS96(pComPort；strVersion：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInstancePS384::CInstancePS384(CSerialPortPCR* pComPort, CString strVersion) : CInstancePS96(pComPort, strVersion)
{

}


// 函数 CInstancePS384::~CInstancePS384
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInstancePS384::~CInstancePS384(void)
{
}



// 函数 CInstancePS384::InitStructurePara
// 作用：初始化InitStructurePara。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CInstancePS96::InitStructurePara。
void CInstancePS384::InitStructurePara()
{
	CInstancePS96::InitStructurePara();

	m_sStructurePara.cPlateRowCount = 16;
	m_sStructurePara.cPlateColCount = 24;
}


// 函数 CInstancePS384::ReadAllFLUData
// 作用：读取ReadAllFLUData。
// 参数：pAryData：指针，指向调用方传入的对象；iChanNum：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetScanChannelCount、ReadFLUData384。
BOOL CInstancePS384::ReadAllFLUData(CUIntArray* pAryData,int iChanNum)
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
		for (int i=0; i<4; i++)
		{
			bReturn = ReadFLUData384(pAryData[ichannel - 1],ichannel, i);
			if(!bReturn)
			{
				break;
			}
		}
		if(!bReturn)
		{
			break;
		}
	}

	return bReturn;
}

// 函数 CInstancePS384::ReadFLUData384
// 作用：读取ReadFLUData384。
// 参数：arrayData；cChannel；cIndex；cFrmIndex。
// 返回：返回是或否。
// 过程：函数里会调用 NewSendCommand、GetByteSum、SendCommandRepeatedly、Add。
BOOL CInstancePS384::ReadFLUData384(CUIntArray& arrayData, BYTE cChannel, BYTE cIndex, BYTE cFrmIndex)
{
	BYTE* pCommand = NewSendCommand(CMD_SEND_LEN7, PCR_READ_FLUDATA, cChannel, cFrmIndex);
	pCommand[2] = cIndex;
	pCommand[CMD_SEND_LEN7-1] = m_pComPort->GetByteSum(pCommand, CMD_SEND_LEN7-1);
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
