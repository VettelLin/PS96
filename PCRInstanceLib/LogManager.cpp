// 【交接】 PCRInstanceLib\LogManager.cpp
// 作用：LogManager。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CLogManager、RemoveAll、InitializeCriticalSection、SAFE_DELETE、GetAt、DeleteCriticalSection、GetInstance、DestroyInstance。
#include "StdAfx.h"
#include "LogManager.h"
#include "PublicFun.h"

CLogManager* CLogManager::m_pInstance = NULL;

// 函数 CLogManager::CLogManager
// 作用：执行CLogManager。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 RemoveAll、InitializeCriticalSection。
CLogManager::CLogManager(void)
{
	m_iSaveMode = 0;
	m_pLogDB = NULL;
	m_pLogRunFile = NULL;
	m_pLogErrorFile = NULL;
	m_pLogCommFile = NULL;

	m_arrayInstrument.RemoveAll();
	m_arrayErrorIndex.RemoveAll();
	m_arrayWarmIndex.RemoveAll();

	InitializeCriticalSection(&m_csUseDB);
}

// 函数 CLogManager::~CLogManager
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SAFE_DELETE、RemoveAll、GetCount、GetAt、DeleteCriticalSection。
CLogManager::~CLogManager(void)
{
	SAFE_DELETE(m_pLogDB);

	SAFE_DELETE(m_pLogRunFile);
	SAFE_DELETE(m_pLogErrorFile);
	SAFE_DELETE(m_pLogCommFile);

	m_arrayInstrument.RemoveAll();
	m_arrayErrorIndex.RemoveAll();

	for (int i=0; i<m_arrayWarmIndex.GetCount(); i++)
	{
		CLongArray* pArrayLong = (CLongArray*)m_arrayWarmIndex.GetAt(i);
		SAFE_DELETE(pArrayLong);
	}
	m_arrayWarmIndex.RemoveAll();

	DeleteCriticalSection(&m_csUseDB);
}

// 函数 CLogManager::GetInstance
// 作用：读取GetInstance。
// 参数：无。
// 返回：返回指针 CLogManager*。指针为空表示没有取到对象。
// 过程：函数里会调用 CLogManager。
CLogManager* CLogManager::GetInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CLogManager();
	}
	return m_pInstance;
}

// 函数 CLogManager::DestroyInstance
// 作用：执行DestroyInstance。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLogManager::DestroyInstance()
{
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

// 函数 CLogManager::Initialize
// 作用：初始化Initialize。
// 参数：strStartupPath：字符串。
// 返回：返回是或否。
// 过程：函数里会调用 CLogRunFile、CLogErrorFile、CLogCommFile、SetDBPath、Open。
BOOL CLogManager::Initialize(CString strStartupPath)
{
	BOOL bReturn = FALSE;

	if (m_iSaveMode == 0)
	{
		m_pLogRunFile = new CLogRunFile(strStartupPath);
		m_pLogErrorFile = new CLogErrorFile(strStartupPath);
		m_pLogCommFile = new CLogCommFile(strStartupPath);
	}
	else
	{
		m_pLogDB = new CLogDataDB;
		if (m_pLogDB != NULL)
		{
			m_pLogDB->SetDBPath(strStartupPath);
			bReturn = m_pLogDB->Open();
		}
	}

	return bReturn;
}

// 函数 CLogManager::ResetLogFileName
// 作用：更新或清除ResetLogFileName。
// 参数：strStartupPath：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 ResetFilePathName。
void CLogManager::ResetLogFileName(CString strStartupPath)
{
	if (m_pLogRunFile != NULL)
	{
		m_pLogRunFile->ResetFilePathName(strStartupPath);
	}
	if (m_pLogErrorFile != NULL)
	{
		m_pLogErrorFile->ResetFilePathName(strStartupPath);
	}
	if (m_pLogCommFile != NULL)
	{
		m_pLogCommFile->ResetFilePathName(strStartupPath);
	}
}


// 保存运行日志，是否需要错误日志中的序号
// 函数 CLogManager::WriteRunLog
// 作用：把WriteRunLog写入文件、仪器或界面。
// 参数：pLogRun：指针，指向调用方传入的对象；nUseErrIndex：整数。
// 返回：返回是或否。
// 过程：函数里会调用 FindInstruemntIndexOfArray、GetInstrument、Empty、GetAt、GetCount、Format。
BOOL CLogManager::WriteRunLog(CLogRunInfo* pLogRun, int nUseErrIndex)
{
	BOOL bReturn = TRUE;

	if (nUseErrIndex == 1) // 使用警告日志序号
	{
		int nInstrumentNo = FindInstruemntIndexOfArray(pLogRun->GetInstrument());
		ASSERT(nInstrumentNo != -1);

		CString strIndex;
		strIndex.Empty();
		CLongArray* pWarmLog = (CLongArray*)m_arrayWarmIndex.GetAt(nInstrumentNo);
		CString strTemp;
		for (int i=0; i<pWarmLog->GetCount(); i++)
		{
			strTemp.Format(_T("%ld"), pWarmLog->GetAt(i));
			strIndex += strTemp;
			if(i < pWarmLog->GetCount() -1)
			{
				strIndex += _T(";");
			}
		}
		pWarmLog->RemoveAll();

		pLogRun->SetErrorIndex(strIndex);
	}
	else if (nUseErrIndex == 2) // 使用错误日志序号
	{
		int nInstrumentNo = FindInstruemntIndexOfArray(pLogRun->GetInstrument());
		ASSERT(nInstrumentNo != -1);

		CString strIndex;
		strIndex.Format(_T("%ld"), m_arrayErrorIndex.GetAt(nInstrumentNo));
		m_arrayErrorIndex.SetAt(nInstrumentNo, 0);
		pLogRun->SetErrorIndex(strIndex);
	}
	
	if (pLogRun->GetDate().IsEmpty())
	{
		pLogRun->SetDate(CPublicFun::GetCurrentDateTime(FALSE));
	}

	// 保存文件或数据库中
	if (m_iSaveMode == 0)
	{
		m_pLogRunFile->WriteLog(pLogRun);
	}
	else
	{
		EnterCriticalSection(&m_csUseDB);
		bReturn = m_pLogDB->InsertRunRecord(pLogRun);
		LeaveCriticalSection(&m_csUseDB);
	}

	return bReturn;
}

// 保存错误日志，是否需要记录插入日志的序号，方便在运行日志中记录原因
// 函数 CLogManager::WriteErrorLog
// 作用：把WriteErrorLog写入文件、仪器或界面。
// 参数：pLogError：指针，指向调用方传入的对象；bRecordIndex：是或否。
// 返回：返回是或否。
// 过程：函数里会调用 WriteLog、FindInstruemntIndexOfArray、GetInstrument、Add、GetLogType、GetAt。
BOOL CLogManager::WriteErrorLog(CLogErrorInfo* pLogError, BOOL bRecordIndex)
{
	BOOL bReturn = TRUE;
	if (m_iSaveMode == 0)
	{
		m_pLogErrorFile->WriteLog(pLogError);

		int nInstrumentNo = FindInstruemntIndexOfArray(pLogError->GetInstrument());
		if (nInstrumentNo == -1)
		{
			nInstrumentNo = m_arrayInstrument.Add(pLogError->GetInstrument());
			m_arrayErrorIndex.Add(0);
			CLongArray* pWarmLog = new CLongArray;
			m_arrayWarmIndex.Add(pWarmLog);
		}

		ASSERT(nInstrumentNo != -1);
		if (pLogError->GetLogType() == LOG_TYPE_WARM)
		{
			CLongArray* pWarmLog = (CLongArray*)m_arrayWarmIndex.GetAt(nInstrumentNo);
			pWarmLog->Add(0);

			// 如果警告超出规定数则增加一条运行记录
			if (pWarmLog->GetCount() > 4)
			{
				CLogRunInfo* pLogRun = new CLogRunInfo;

				pLogRun->SetDate(CPublicFun::GetCurrentDateTime(FALSE));
				pLogRun->SetUser(pLogError->GetUser());
				pLogRun->SetInstrument(pLogError->GetInstrument());
				pLogRun->SetLogType(LOG_TYPE_WARM);

				CString strTemp;
				strTemp.Format(_T("The command sent to the %s had more than %d failures"), pLogError->GetInstrument(), pWarmLog->GetCount());
				pLogRun->SetContent(strTemp);
				bReturn = WriteRunLog(pLogRun, 1);
				SAFE_DELETE(pLogRun);
			}
		}
		else if (pLogError->GetLogType() == LOG_TYPE_ERROR)
		{
			m_arrayErrorIndex.SetAt(nInstrumentNo, 0);
		}
	}
	else
	{
		EnterCriticalSection(&m_csUseDB);

		bReturn = m_pLogDB->InsertErrorRecord(pLogError);
		if (bRecordIndex)
		{
			long lIndex = m_pLogDB->FindErrorLogMaxIndex();

			int nInstrumentNo = FindInstruemntIndexOfArray(pLogError->GetInstrument());
			if (nInstrumentNo == -1)
			{
				nInstrumentNo = m_arrayInstrument.Add(pLogError->GetInstrument());
				m_arrayErrorIndex.Add(0);
				CLongArray* pWarmLog = new CLongArray;
				m_arrayWarmIndex.Add(pWarmLog);
			}

			ASSERT(nInstrumentNo != -1);
			if (pLogError->GetLogType() == LOG_TYPE_WARM)
			{
				CLongArray* pWarmLog = (CLongArray*)m_arrayWarmIndex.GetAt(nInstrumentNo);
				pWarmLog->Add(lIndex);

				// 如果警告超出规定数则增加一条运行记录
				if (pWarmLog->GetCount() > 4)
				{
					CLogRunInfo* pLogRun = new CLogRunInfo;

					pLogRun->SetDate(CPublicFun::GetCurrentDateTime(FALSE));
					pLogRun->SetUser(pLogError->GetUser());
					pLogRun->SetInstrument(pLogError->GetInstrument());
					pLogRun->SetLogType(LOG_TYPE_WARM);

					CString strTemp;
					strTemp.Format(_T("The command sent to the %s had more than %d failures"), pLogError->GetInstrument(), pWarmLog->GetCount());
					pLogRun->SetContent(strTemp);
					bReturn = WriteRunLog(pLogRun, 1);
					SAFE_DELETE(pLogRun);
				}
			}
			else if (pLogError->GetLogType() == LOG_TYPE_ERROR)
			{
				m_arrayErrorIndex.SetAt(nInstrumentNo, lIndex);
			}
		}

		LeaveCriticalSection(&m_csUseDB);
	}

	return bReturn;
}

// 函数 CLogManager::WriteErrorLog
// 作用：把WriteErrorLog写入文件、仪器或界面。
// 参数：strError：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 WriteLog。
BOOL CLogManager::WriteErrorLog(CString strError)
{
	if (m_iSaveMode == 0)
	{
		m_pLogErrorFile->WriteLog(strError);
		return TRUE;
	}
	else
	{
		ASSERT(FALSE);
		return FALSE;
	}
}

// 函数 CLogManager::WriteCommLog
// 作用：把WriteCommLog写入文件、仪器或界面。
// 参数：pLogComm：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 WriteLog、EnterCriticalSection、InsertCommRecord、LeaveCriticalSection。
BOOL CLogManager::WriteCommLog(CLogCommInfo* pLogComm)
{
	BOOL bReturn = TRUE;
	if (m_iSaveMode == 0)
	{
		m_pLogCommFile->WriteLog(pLogComm);
	}
	else
	{
		EnterCriticalSection(&m_csUseDB);
		bReturn = m_pLogDB->InsertCommRecord(pLogComm);
		LeaveCriticalSection(&m_csUseDB);
	}
	return bReturn;
}

// 函数 CLogManager::WriteCommLog
// 作用：把WriteCommLog写入文件、仪器或界面。
// 参数：string：字符串。
// 返回：返回是或否。
// 过程：函数里会调用 WriteLog。
BOOL CLogManager::WriteCommLog(CString string)
{
	BOOL bReturn = TRUE;
	if (m_iSaveMode == 0)
	{
		m_pLogCommFile->WriteLog(string);
	}
	return bReturn;
}


// 函数 CLogManager::FindInstruemntIndexOfArray
// 作用：执行FindInstruemntIndexOfArray。
// 参数：strInstrument：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCount、GetAt。
int CLogManager::FindInstruemntIndexOfArray(CString strInstrument)
{
	int nInstrumentNo = -1;
	for (int x=0; x<m_arrayInstrument.GetCount(); x++)
	{
		if (m_arrayInstrument.GetAt(x) == strInstrument)
		{
			nInstrumentNo = x;
			break;
		}
	}

	return nInstrumentNo;
}
