// 【交接】 PCRCtrlLib\ExperimentInfo.cpp
// 作用：ExperimentInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CExperimentInfo、CreateExperimentName、Empty、GetCurrentTime、CopyExperiment、WriteFile、WriteStringToFile、Write。
#include "StdAfx.h"
#include "ExperimentInfo.h"
#include "PublicFun.h"

// 函数 CExperimentInfo::CExperimentInfo
// 作用：执行CExperimentInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateExperimentName、Empty、GetCurrentTime。
CExperimentInfo::CExperimentInfo()
{
	m_strExpName = CreateExperimentName(); 
	m_strFilePath.Empty(); 

	m_nExpType = EXP_TYPE_ABSOLUTE;
	m_strOperator.Empty(); 
	m_strVerifier.Empty(); 
	m_strComments.Empty();
	m_strStartTime.Empty();
	m_strEndTime.Empty();

	m_strInstrument.Empty();
	m_strInstrumentSN.Empty();
	m_nTubeType = TUBE_TRANSPARENT;

	m_bLidHeater = TRUE;
	m_fLidTopTemp = 90;
	m_nTempMode = TEMP_MODE_CONSTANT;
	m_nTempCtrlMode = TEMP_CTRL_TUBE;
	m_nBlockHeater = 0;
	m_ScanMode = CHANNEL_SCAN_ALL;
	m_nMeltScanMode = MELT_SCAN_STANDARD;
	m_nPMTGear = MPPC_VOLGEAR_MIDDLE;

	m_strCYReportNo.Empty();

	m_iTotalSec = 0;
	m_iRemainSec = 0;
	m_iHasRunSec = 0;
	m_timeStart = CTime::GetCurrentTime();
}

// 函数 CExperimentInfo::CopyExperiment
// 作用：复制CopyExperiment。
// 参数：expInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExperimentInfo::CopyExperiment(CExperimentInfo& expInfo)
{
	if(NULL == this)
	{
		return;
	}

	m_strExpName = expInfo.m_strExpName;
	m_strFilePath = expInfo.m_strFilePath;

	m_nExpType = expInfo.m_nExpType;
	m_strOperator = expInfo.m_strOperator;
	m_strVerifier = expInfo.m_strVerifier;
	m_strComments = expInfo.m_strComments;
	m_strStartTime = expInfo.m_strStartTime;
	m_strEndTime = expInfo.m_strEndTime;
	m_strRunDuration = expInfo.m_strRunDuration;

	m_strInstrument = expInfo.m_strInstrument;
	m_strInstrumentSN = expInfo.m_strInstrumentSN;
	m_strFirmwareVersion = expInfo.m_strFirmwareVersion;
	m_strSoftwareVersion = expInfo.m_strSoftwareVersion;

	m_nTubeType = expInfo.m_nTubeType;
	m_bLidHeater = expInfo.m_bLidHeater;
	m_fLidTopTemp = expInfo.m_fLidTopTemp;
	m_nTempMode = expInfo.m_nTempMode;
	m_nTempCtrlMode = expInfo.m_nTempCtrlMode;
	m_nBlockHeater = expInfo.m_nBlockHeater;
	m_ScanMode = expInfo.m_ScanMode;
	m_nMeltScanMode = expInfo.m_nMeltScanMode;
	m_nPMTGear = expInfo.m_nPMTGear;

	m_strCYReportNo = expInfo.m_strCYReportNo;

	m_iTotalSec = expInfo.m_iTotalSec;
	m_iRemainSec = expInfo.m_iRemainSec;
	m_iHasRunSec = expInfo.m_iHasRunSec;
	m_timeStart = expInfo.m_timeStart;

	return;
}

// 函数 CExperimentInfo::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象；bTemplate：是或否。
// 返回：返回是或否。
// 过程：函数里会调用 WriteStringToFile、Write、_T。
BOOL CExperimentInfo::WriteFile(CFile* pFile,BOOL bTemplate)
{
	CPublicFun::WriteStringToFile(pFile, m_strExpName);
	CPublicFun::WriteStringToFile(pFile, m_strFilePath);

	int nTempInt = m_nExpType;
	pFile->Write((const char *)&nTempInt, sizeof(int));
	CPublicFun::WriteStringToFile(pFile, m_strOperator);
	CPublicFun::WriteStringToFile(pFile, m_strVerifier);
	CPublicFun::WriteStringToFile(pFile, m_strComments);

	//保存模板文件时，不保留相关状态信息
	if(bTemplate)
	{
		CPublicFun::WriteStringToFile(pFile,_T(""));
		CPublicFun::WriteStringToFile(pFile,_T(""));
		CPublicFun::WriteStringToFile(pFile,_T(""));
	}
	else
	{
		CPublicFun::WriteStringToFile(pFile, m_strStartTime);
		CPublicFun::WriteStringToFile(pFile, m_strEndTime);
		CPublicFun::WriteStringToFile(pFile, m_strRunDuration);
	}

	CPublicFun::WriteStringToFile(pFile, m_strInstrument);
	CPublicFun::WriteStringToFile(pFile, m_strInstrumentSN);
	CPublicFun::WriteStringToFile(pFile, m_strFirmwareVersion);
	CPublicFun::WriteStringToFile(pFile, m_strSoftwareVersion);

	nTempInt = m_nTubeType;
	pFile->Write((const char *)&nTempInt, sizeof(int));
	pFile->Write((const char *)&m_bLidHeater, sizeof(BOOL));
	pFile->Write((const char *)&m_fLidTopTemp, sizeof(float));
	nTempInt = m_nTempMode;
	pFile->Write((const char *)&nTempInt, sizeof(int));
	nTempInt = m_nTempCtrlMode;
	pFile->Write((const char *)&nTempInt, sizeof(int));
	pFile->Write((const char *)&m_nBlockHeater, sizeof(UINT));
	nTempInt = m_ScanMode;
	pFile->Write((const char *)&nTempInt, sizeof(int));
	nTempInt = m_nMeltScanMode;
	pFile->Write((const char *)&nTempInt, sizeof(int));
	nTempInt = m_nPMTGear;
	pFile->Write((const char *)&nTempInt, sizeof(int));

	if(bTemplate)
	{
		int iTotalSec = 0,iRemainSec = 0;
		pFile->Write((const char *)&iTotalSec,sizeof(int));
		pFile->Write((const char *)&iRemainSec,sizeof(int));
	}
	else
	{
		pFile->Write((const char *)&m_iTotalSec, sizeof(int));
		pFile->Write((const char *)&m_iRemainSec, sizeof(int));
	}

	return TRUE;
}

// 函数 CExperimentInfo::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 ReadStringFromFile、Read。
BOOL CExperimentInfo::ReadFile(CFile* pFile, WORD wVersion)
{
	m_strExpName = CPublicFun::ReadStringFromFile(pFile);
	m_strFilePath = CPublicFun::ReadStringFromFile(pFile);

	int tempInt = 0;
	pFile->Read(&tempInt, sizeof(int));
	m_nExpType = (eExperimentType)tempInt;
	m_strOperator = CPublicFun::ReadStringFromFile(pFile);
	m_strVerifier = CPublicFun::ReadStringFromFile(pFile);
	m_strComments = CPublicFun::ReadStringFromFile(pFile);
	m_strStartTime = CPublicFun::ReadStringFromFile(pFile);
	m_strEndTime = CPublicFun::ReadStringFromFile(pFile);
	m_strRunDuration = CPublicFun::ReadStringFromFile(pFile);

	m_strInstrument = CPublicFun::ReadStringFromFile(pFile);
	m_strInstrumentSN = CPublicFun::ReadStringFromFile(pFile);
	m_strFirmwareVersion = CPublicFun::ReadStringFromFile(pFile);
	m_strSoftwareVersion = CPublicFun::ReadStringFromFile(pFile);

	pFile->Read(&tempInt, sizeof(int));
	m_nTubeType = (eTubeType)tempInt;
	pFile->Read(&m_bLidHeater, sizeof(BOOL));
	pFile->Read(&m_fLidTopTemp, sizeof(float));
	pFile->Read(&tempInt, sizeof(int));
	m_nTempMode = (ePCRTempMode)tempInt;
	pFile->Read(&tempInt, sizeof(int));
	m_nTempCtrlMode = (eTempCtrlMode)tempInt;
	pFile->Read(&m_nBlockHeater, sizeof(UINT));
	pFile->Read(&tempInt, sizeof(int));
	m_ScanMode = (eChannelScanlMode)tempInt;
	pFile->Read(&tempInt, sizeof(int));
	m_nMeltScanMode = (eMeltScanMode)tempInt;
	pFile->Read(&tempInt, sizeof(int));
	m_nPMTGear = (eMPPCVoltageGear)tempInt;

	pFile->Read(&m_iTotalSec, sizeof(int));
	pFile->Read(&m_iRemainSec, sizeof(int));

	m_iHasRunSec = m_iTotalSec - m_iRemainSec;	//添加于20220823，孙文郎
	if(m_iHasRunSec > m_iTotalSec)
	{
		m_iHasRunSec = m_iTotalSec;
		m_iRemainSec = 0;
	}

	return TRUE;
}

// 函数 CExperimentInfo::CreateExperimentName
// 作用：创建或加入CreateExperimentName。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetLocalTime、Format、_T。
CString CExperimentInfo::CreateExperimentName()
{
	CString strDate;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strDate.Format(_T("%4d-%02d-%02d_%02d-%02d-%02d"),st.wYear, st.wMonth, st.wDay, st.wHour,st.wMinute,st.wSecond);
	return strDate;
}

// 函数 CExperimentInfo::GetBePS96ExperimentFile
// 作用：读取GetBePS96ExperimentFile。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 _T、Left。
BOOL CExperimentInfo::GetBePS96ExperimentFile()
{
	return _T("iAMP-PS96") == m_strInstrument.Left(9);
}

// 函数 CExperimentInfo::GetSaveDataFileName
// 作用：读取GetSaveDataFileName。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetFilePath、_T、GetExpName。
CString CExperimentInfo::GetSaveDataFileName()
{
	CString strName;

	strName = GetFilePath() + _T("\\") + GetExpName();

	return strName;
}

// 函数 CExperimentInfo::SetCYReportNo
// 作用：设置SetCYReportNo。
// 参数：strData：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExperimentInfo::SetCYReportNo(CString strData)
{
	m_strCYReportNo = strData;
	return;
}

// 函数 CExperimentInfo::GetCYReportNo
// 作用：读取GetCYReportNo。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CExperimentInfo::GetCYReportNo()
{
	return m_strCYReportNo;
}

// 函数 CExperimentInfo::SetTotalSec
// 作用：设置SetTotalSec。
// 参数：iTotalSec：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExperimentInfo::SetTotalSec(int iTotalSec)
{
	m_iTotalSec = iTotalSec;
	return;
}

// 函数 CExperimentInfo::GetTotalSec
// 作用：读取GetTotalSec。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CExperimentInfo::GetTotalSec()
{
	return m_iTotalSec;
}

// 函数 CExperimentInfo::GetTotalTimeString
// 作用：读取GetTotalTimeString。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 strTemp、_T、Format。
CString CExperimentInfo::GetTotalTimeString()
{
	int iHour = m_iTotalSec / 3600;
	int iTotalSec = m_iTotalSec % 3600;
	int iMinute = iTotalSec / 60;
	int iSec = iTotalSec % 60;
	CString strTemp(_T(""));

	strTemp.Format(_T("%02d:%02d:%02d"),iHour,iMinute,iSec);

	return strTemp;
}

// 函数 CExperimentInfo::SetHasRunSec
// 作用：设置SetHasRunSec。
// 参数：iHasRunSec：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExperimentInfo::SetHasRunSec(int iHasRunSec)
{
	m_iHasRunSec = iHasRunSec;
	if(m_iHasRunSec < 0)
	{
		m_iHasRunSec = 0;
	}
}

// 函数 CExperimentInfo::GetHasRunSec
// 作用：读取GetHasRunSec。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CExperimentInfo::GetHasRunSec()
{
	return m_iHasRunSec;
}

// 函数 CExperimentInfo::SetRemainSec
// 作用：设置SetRemainSec。
// 参数：iRemainSec：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExperimentInfo::SetRemainSec(int iRemainSec)
{
	m_iRemainSec = iRemainSec;
	return;
}

// 函数 CExperimentInfo::GetRemainSec
// 作用：读取GetRemainSec。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CExperimentInfo::GetRemainSec()
{
	return m_iRemainSec;
}

// 函数 CExperimentInfo::SetStartTime
// 作用：设置SetStartTime。
// 参数：time。
// 返回：没有返回值。
// 过程：函数里会调用 Format、_T。
void CExperimentInfo::SetStartTime(CTime time)
{
	m_timeStart = time;
	m_strStartTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
}

// 函数 CExperimentInfo::SetEndTime
// 作用：设置SetEndTime。
// 参数：time。
// 返回：没有返回值。
// 过程：函数里会调用 Format、_T、GetMinutes、GetSeconds。
void CExperimentInfo::SetEndTime(CTime time)
{
	m_strEndTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	CTimeSpan timeSpan = time - m_timeStart;
	m_strRunDuration.Format(_T("%d minutes %d seconds"), timeSpan.GetMinutes(), timeSpan.GetSeconds());
}
