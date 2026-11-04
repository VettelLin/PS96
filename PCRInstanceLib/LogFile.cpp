// 【交接】 PCRInstanceLib\LogFile.cpp
// 作用：LogFile。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CLogFile、_T、Empty、CreateLogPath、InitializeCriticalSection、DeleteCriticalSection、CreateDirectory、GetCurrentDate。
#include "StdAfx.h"
#include "LogFile.h"
#include "locale.h"
#include "PublicFun.h"

// 函数 CLogFile::CLogFile
// 作用：执行CLogFile。
// 参数：strStartupPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 _T、Empty、CreateLogPath、InitializeCriticalSection。
CLogFile::CLogFile(CString strStartupPath)
{
	strStartupPath += _T("LogFile");
	m_strFileName.Empty();
	m_strSpace = _T("    ");

	CreateLogPath(strStartupPath);

	InitializeCriticalSection(&m_CriticalSection);
}


// 函数 CLogFile::~CLogFile
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteCriticalSection。
CLogFile::~CLogFile(void)
{
	DeleteCriticalSection(&m_CriticalSection);
}

// 函数 CLogFile::CreateLogPath
// 作用：创建或加入CreateLogPath。
// 参数：strFilePath：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 PathFileExists、CreateDirectory、GetCurrentDate、_T。
BOOL CLogFile::CreateLogPath(CString strFilePath)
{
	if(!PathFileExists(strFilePath))
	{
		BOOL bRtn = -1;
		bRtn = CreateDirectory(strFilePath,NULL);
		if (0 == bRtn)
		{
			return FALSE;
		}
	}

	CString strDate = GetCurrentDate();
	m_strFilePath = strFilePath + _T("\\") + strDate;

	//获取存储路径
	if(!PathFileExists(m_strFilePath))
	{
		BOOL bRtn = -1;
		bRtn = CreateDirectory(m_strFilePath,NULL);
		if (0 == bRtn)
		{
			return FALSE;
		}
	}

	return TRUE;
}

// 函数 CLogFile::CreateLogFile
// 作用：创建或加入CreateLogFile。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 FindFile、CreateFile、MessageBoxA、CloseHandle。
BOOL CLogFile::CreateLogFile()
{
	CFileFind filefind;
	BOOL bFind = filefind.FindFile(m_strFileName);
	if(!bFind)
	{
		HANDLE hcreatefile = CreateFile(m_strFileName, GENERIC_READ|GENERIC_WRITE,NULL, NULL, OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
		if (hcreatefile== INVALID_HANDLE_VALUE)
		{
			hcreatefile = NULL;
			MessageBoxA(NULL, "Can not open the file", "warning", MB_OK);
			return FALSE;
		}
		else
		{
			CloseHandle(hcreatefile);
			return TRUE;
		}
	}

	return TRUE;
}

// 函数 CLogFile::WriteString
// 作用：把WriteString写入文件、仪器或界面。
// 参数：strLog：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 EnterCriticalSection、Open、_strdup、setlocale、SeekToEnd、free。
BOOL CLogFile::WriteString(CString strLog)
{	
	BOOL bReturn = FALSE;
	EnterCriticalSection(&m_CriticalSection);

	CStdioFile recordFile;
	BOOL bSuc = recordFile.Open(m_strFileName, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	if (!bSuc)
	{
		return FALSE;
	}
		
	char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
	setlocale( LC_CTYPE, "chs" );
	recordFile.SeekToEnd();

	strLog += "\n";
	recordFile.WriteString(strLog);

	setlocale( LC_CTYPE,old_locale );
	free(old_locale);

	recordFile.Close();

	OutputDebugString(strLog);

	LeaveCriticalSection(&m_CriticalSection);

	return bReturn;
}


// 函数 CLogFile::GetCurrentDate
// 作用：读取GetCurrentDate。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetLocalTime、Format、_T。
CString CLogFile::GetCurrentDate()
{
	CString strDate;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strDate.Format(_T("%4d-%02d-%02d"),st.wYear, st.wMonth, st.wDay);
	return strDate;
}


// 函数 CLogFile::GetCurrentTime
// 作用：读取GetCurrentTime。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetLocalTime、Format、_T。
CString CLogFile::GetCurrentTime()
{
	CString strTime;
	SYSTEMTIME st;
	GetLocalTime(&st);
	strTime.Format(_T("%4d-%02d-%02d-%02d-%02d-%02d"),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return strTime;
}


//*****************************************************************************************************************
// 运行日志文件

// 函数 CLogRunFile::CLogRunFile
// 作用：执行CLogRunFile。
// 参数：CLogFile(strStartupPath。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CLogRunFile::CLogRunFile(CString strStartupPath) : CLogFile(strStartupPath)
{
	m_strFileName = m_strFilePath + _T("\\PCRRun.log");
}

// 函数 CLogRunFile::WriteLog
// 作用：把WriteLog写入文件、仪器或界面。
// 参数：pLogInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetDate、GetContent、Format、_T、GetLogType、GetUser。
void CLogRunFile::WriteLog(CLogRunInfo* pLogInfo)
{
	CString strLog, strTemp;
	strLog = pLogInfo->GetDate() + m_strSpace + pLogInfo->GetContent();
	strTemp.Format(_T("%d"), pLogInfo->GetLogType());
	strLog += m_strSpace + strTemp;
	strLog += m_strSpace + pLogInfo->GetUser() + m_strSpace + pLogInfo->GetInstrument();

	WriteString(strLog);
}

// 函数 CLogRunFile::ResetFilePathName
// 作用：更新或清除ResetFilePathName。
// 参数：strStartupPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 CreateLogPath、_T。
void CLogRunFile::ResetFilePathName(CString strStartupPath)
{
	CreateLogPath(strStartupPath);
	m_strFileName = m_strFilePath + _T("\\PCRRun.log");
}


//*****************************************************************************************************************
// 错误日志文件

// 函数 CLogErrorFile::CLogErrorFile
// 作用：执行CLogErrorFile。
// 参数：CLogFile(strStartupPath。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CLogErrorFile::CLogErrorFile(CString strStartupPath) : CLogFile(strStartupPath)
{
	m_strFileName = m_strFilePath + _T("\\PCRError.log");
}

// 函数 CLogErrorFile::WriteLog
// 作用：把WriteLog写入文件、仪器或界面。
// 参数：pLogInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetDate、GetError、GetErrPara1、GetErrPara2、Format、_T。
void CLogErrorFile::WriteLog(CLogErrorInfo* pLogInfo)
{
	CString strLog, strTemp;
	strLog = pLogInfo->GetDate() + m_strSpace + pLogInfo->GetError();
	strLog += m_strSpace + pLogInfo->GetErrPara1() + m_strSpace + pLogInfo->GetErrPara2();
	strTemp.Format(_T("%d"), pLogInfo->GetLogType());
	strLog += m_strSpace + strTemp;
	strLog += m_strSpace + pLogInfo->GetUser() + m_strSpace + pLogInfo->GetInstrument();

	WriteString(strLog);
}

// 函数 CLogErrorFile::WriteLog
// 作用：把WriteLog写入文件、仪器或界面。
// 参数：strError：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 WriteString。
void CLogErrorFile::WriteLog(CString strError)
{
	WriteString(strError);
}

// 函数 CLogErrorFile::ResetFilePathName
// 作用：更新或清除ResetFilePathName。
// 参数：strStartupPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 CreateLogPath、_T。
void CLogErrorFile::ResetFilePathName(CString strStartupPath)
{
	CreateLogPath(strStartupPath);
	m_strFileName = m_strFilePath + _T("\\PCRError.log");
}

//*****************************************************************************************************************
// 通讯日志文件

// 函数 CLogCommFile::CLogCommFile
// 作用：执行CLogCommFile。
// 参数：CLogFile(strStartupPath。
// 返回：没有返回值。
// 过程：函数里会调用 _T、GetCurrentTime。
CLogCommFile::CLogCommFile(CString strStartupPath) : CLogFile(strStartupPath)
{
	m_strFileName = m_strFilePath + _T("\\Comm") + GetCurrentTime() + _T(".log");
}

// 函数 CLogCommFile::WriteLog
// 作用：把WriteLog写入文件、仪器或界面。
// 参数：pLogInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetDate、Right、GetLength、GetCommType、_T、GetContent。
void CLogCommFile::WriteLog(CLogCommInfo* pLogInfo)
{
	CString strTemp;
	CString strLog = pLogInfo->GetDate();
	//strLog = strTime.Right(strTime.GetLength()-11);
	if (pLogInfo->GetCommType() == CLogCommInfo::COMM_TYPE_SEND)
	{
		strLog += m_strSpace + _T("Send:    ");
	}
	else
	{
		strLog += m_strSpace + _T("Receive:");
	}

	strLog += m_strSpace + pLogInfo->GetContent();

	strTemp.Format(_T("%d"), pLogInfo->GetResult());
	strLog += m_strSpace + strTemp;

	strTemp.Format(_T("%d"), pLogInfo->GetSendCount());
	strLog += m_strSpace + strTemp;
	strLog += m_strSpace + pLogInfo->GetComment();
	WriteString(strLog);
}


// 函数 CLogCommFile::WriteLog
// 作用：把WriteLog写入文件、仪器或界面。
// 参数：string：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 GetCurrentDateTime、Right、GetLength、WriteString。
void CLogCommFile::WriteLog(CString string)
{
	CString strLog = CPublicFun::GetCurrentDateTime();
	//strLog = strTime.Right(strTime.GetLength()-11);
	strLog += m_strSpace;
	strLog += string;
	WriteString(strLog);
}

// 函数 CLogCommFile::ResetFilePathName
// 作用：更新或清除ResetFilePathName。
// 参数：strStartupPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 CreateLogPath、_T、GetCurrentTime。
void CLogCommFile::ResetFilePathName(CString strStartupPath)
{
	CreateLogPath(strStartupPath);
	m_strFileName = m_strFilePath + _T("\\Comm") + GetCurrentTime() + _T(".log");
}
