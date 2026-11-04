// 【交接】 PCRCtrlLib\ExpRunPara.cpp
// 作用：ExpRunPara。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CExpRunPara、InitializeCriticalSection、CreateEvent、DeleteCriticalSection、SAFE_DELETE、CloseHandle、LockInstance、EnterCriticalSection。
#include "StdAfx.h"
#include "ExpRunPara.h"
#include "PublicFun.h"
#include "ConfigureDB.h"

// 函数 CExpRunPara::CExpRunPara
// 作用：执行CExpRunPara。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitializeCriticalSection、CreateEvent。
CExpRunPara::CExpRunPara(void)
{
	m_fLidLowerTemp = 30.0f;
	m_fPeltierLowerTemp = 15.0f;

	m_iLidGetTempDelay = 500;
	m_iAmplifyTempDelay = 800;
	m_iMeltTempDelay = 800;
	m_bEndAutoCoolling = TRUE;

	m_nStageType = STAGE_LID_HEATER;
	m_lTempStartTime = 0;
	m_lAmplifyStartTime = 0;
	m_lMeltStartTime = 0;
	m_lSegmentStartTime = 0;

	m_bExpInterrupt = FALSE;
	m_pDBRunInfo = new CDBRunInfo;

	m_fCurTemp = 15.0f;
	m_bCurReachTemp = FALSE;
	m_fLidTemp = 30.0f;
	m_bLidReachTemp = FALSE;

	m_ckScanGetDataMs = 0;
	m_bMeltStepRunning = FALSE;

	InitializeCriticalSection(&m_csUseInstance);

	m_bCommuNormal = TRUE;
	m_hSyncCommuState = CreateEvent(NULL,FALSE,TRUE,NULL);
}

// 函数 CExpRunPara::~CExpRunPara
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteCriticalSection、SAFE_DELETE、CloseHandle。
CExpRunPara::~CExpRunPara(void)
{
	DeleteCriticalSection(&m_csUseInstance);
	SAFE_DELETE(m_pDBRunInfo);

	if(NULL != m_hSyncCommuState)
	{
		CloseHandle(m_hSyncCommuState);
		m_hSyncCommuState = NULL;
	}
}

// 函数 CExpRunPara::LockInstance
// 作用：执行LockInstance。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 EnterCriticalSection。
void CExpRunPara::LockInstance()
{
	EnterCriticalSection(&m_csUseInstance);
}

// 函数 CExpRunPara::UnlockInstance
// 作用：执行UnlockInstance。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 LeaveCriticalSection。
void CExpRunPara::UnlockInstance()
{
	LeaveCriticalSection(&m_csUseInstance);
}

// 函数 CExpRunPara::SetRunInfo
// 作用：设置SetRunInfo。
// 参数：pRunInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetStopFlag、SetIndex、GetIndex、SetInstrument、GetInstruemnt、SetFileName。
void CExpRunPara::SetRunInfo(CDBRunInfo* pRunInfo)
{
	if (pRunInfo->GetStopFlag() == 1) // 非法中止过
	{
		m_bExpInterrupt = TRUE;
		m_pDBRunInfo->SetIndex(pRunInfo->GetIndex());
		m_pDBRunInfo->SetInstrument(pRunInfo->GetInstruemnt());
		m_pDBRunInfo->SetFileName(pRunInfo->GetFileName());
		m_pDBRunInfo->SetUser(pRunInfo->GetUser());
		m_pDBRunInfo->SetBeginTime(pRunInfo->GetBeginTime());
		m_pDBRunInfo->SetEndTime(pRunInfo->GetEndTime());
		m_pDBRunInfo->SetStopFlag(pRunInfo->GetStopFlag());
		m_pDBRunInfo->SetCurSegment(pRunInfo->GetCurSegment());
		m_pDBRunInfo->SetCurCycle(pRunInfo->GetCurCycle());
		m_pDBRunInfo->SetCurStep(pRunInfo->GetCurStep());
	}
}

// 实验运行，新实验插入一条记录到数据库中
// 函数 CExpRunPara::ExpRun
// 作用：执行ExpRun。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SetBeginTime、GetCurrentDateTime、GetInstance、InsertRunRecord。
void CExpRunPara::ExpRun()
{
	ASSERT(m_pDBRunInfo != NULL);
	if (!m_bExpInterrupt)
	{
		m_pDBRunInfo->SetBeginTime(CPublicFun::GetCurrentDateTime(FALSE));
		CConfigureDB::GetInstance()->InsertRunRecord(m_pDBRunInfo);
	}
}

// 函数 CExpRunPara::SetCurSegment
// 作用：设置SetCurSegment。
// 参数：iSegment：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetTickCount64。
void CExpRunPara::SetCurSegment(int iSegment)
{
	m_lSegmentStartTime = GetTickCount64();
	m_pDBRunInfo->SetCurSegment(iSegment);
}

// 函数 CExpRunPara::SetCurCycle
// 作用：设置SetCurCycle。
// 参数：iCycle：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpRunPara::SetCurCycle(int iCycle)
{
	m_pDBRunInfo->SetCurCycle(iCycle);
}

// 函数 CExpRunPara::SetCurStep
// 作用：设置SetCurStep。
// 参数：iStep：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、UpdateRunRecord。
void CExpRunPara::SetCurStep(int iStep)
{
	m_pDBRunInfo->SetCurStep(iStep);
	// 保存到数据库中
	CConfigureDB::GetInstance()->UpdateRunRecord(m_pDBRunInfo, FALSE);
}

// 函数 CExpRunPara::ExpStop
// 作用：执行ExpStop。
// 参数：nType：整数。
// 返回：没有返回值。
// 过程：函数里会调用 SetEndTime、GetCurrentDateTime、SetStopFlag、GetInstance、UpdateRunRecord。
void CExpRunPara::ExpStop(CDBRunInfo::eStopFlagType nType)
{
	m_pDBRunInfo->SetEndTime(CPublicFun::GetCurrentDateTime(FALSE));
	m_pDBRunInfo->SetStopFlag(nType);
	CConfigureDB::GetInstance()->UpdateRunRecord(m_pDBRunInfo, TRUE);
}

// 函数 CExpRunPara::GetStartTime
// 作用：读取GetStartTime。
// 参数：nType：整数。
// 返回：返回 unsigned long long。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
unsigned long long CExpRunPara::GetStartTime(eExpStageType nType)
{
	unsigned long long lTemp = 0;
	switch (nType)
	{
	case STAGE_LID_HEATER:
	case STAGE_HOLD:
		lTemp = m_lTempStartTime;
		break;
	case STAGE_AMPLIFY:
		lTemp = m_lAmplifyStartTime;
		break;
	case STAGE_MELT:
		lTemp = m_lMeltStartTime;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return lTemp;
}

// 函数 CExpRunPara::SetStartTime
// 作用：设置SetStartTime。
// 参数：nType：整数；lTime。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpRunPara::SetStartTime(eExpStageType nType, unsigned long long lTime)
{
	switch (nType)
	{
	case STAGE_LID_HEATER: // 如果已经设置开始时间，则不修改
	case STAGE_HOLD: 
		if (m_lTempStartTime == 0)
		{
			m_lTempStartTime = lTime;
		}
		break;
	case STAGE_AMPLIFY:
		m_lAmplifyStartTime = lTime;
		break;
	case STAGE_MELT:
		m_lMeltStartTime = lTime;
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

// 函数 CExpRunPara::GetCurrentStageDelay
// 作用：读取GetCurrentStageDelay。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CExpRunPara::GetCurrentStageDelay()
{
	int iDelay = 0;
	switch(m_nStageType)
	{
	case STAGE_HOLD:
	case STAGE_LID_HEATER:
		iDelay = m_iLidGetTempDelay;
		break;
	case STAGE_AMPLIFY:
		iDelay = m_iAmplifyTempDelay;
		break;
	case STAGE_MELT:
		iDelay = m_iMeltTempDelay;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return iDelay;
}

// 函数 CExpRunPara::SetScanGetDataMs
// 作用：设置SetScanGetDataMs。
// 参数：ckMs。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpRunPara::SetScanGetDataMs(clock_t ckMs)
{
	m_ckScanGetDataMs = ckMs;
}

// 函数 CExpRunPara::GetScanGetDataMs
// 作用：读取GetScanGetDataMs。
// 参数：无。
// 返回：返回 clock_t。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
clock_t CExpRunPara::GetScanGetDataMs()
{
	return m_ckScanGetDataMs;
}

// 函数 CExpRunPara::GetScanDataSecond
// 作用：读取GetScanDataSecond。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CExpRunPara::GetScanDataSecond()
{
	return m_ckScanGetDataMs / 1000.0;
}

// 函数 CExpRunPara::SetMeltStepRunningState
// 作用：设置SetMeltStepRunningState。
// 参数：bMeltStepRunning：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpRunPara::SetMeltStepRunningState(BOOL bMeltStepRunning)
{
	m_bMeltStepRunning = bMeltStepRunning;
	return;
}

// 函数 CExpRunPara::IsMeltStepRunning
// 作用：判断IsMeltStepRunning是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CExpRunPara::IsMeltStepRunning()
{
	return m_bMeltStepRunning;
}

// 函数 CExpRunPara::SetCommunicationState
// 作用：设置SetCommunicationState。
// 参数：bValue：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 WaitForSingleObject、SetEvent。
void CExpRunPara::SetCommunicationState(BOOL bValue)
{
	//慎用INFINITE
	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncCommuState,200000))
	{
		return;
	}
	m_bCommuNormal = bValue;
	SetEvent(m_hSyncCommuState);
	return;
}

// 函数 CExpRunPara::GetCommunicationState
// 作用：读取GetCommunicationState。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 WaitForSingleObject、SetEvent。
BOOL CExpRunPara::GetCommunicationState()
{
	//慎用INFINITE
	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncCommuState,200000))
	{
		return TRUE;
	}
	SetEvent(m_hSyncCommuState);
	return m_bCommuNormal;
}


