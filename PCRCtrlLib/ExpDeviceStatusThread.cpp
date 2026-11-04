// 【交接】 PCRCtrlLib\ExpDeviceStatusThread.cpp
// 作用：ExpDeviceStatusThread 后台线程。实验运行时在界面之外轮询状态，避免卡住窗口。
// 先看这些函数：IMPLEMENT_DYNCREATE、CExpDeviceStatusThread、InitInstance、ExitInstance、InitParameter、Run、LockInstance、ReadDeviceStatus。
#include "StdAfx.h"
#include "ExpDeviceStatusThread.h"

IMPLEMENT_DYNCREATE(CExpDeviceStatusThread, CWinThread)

// 函数 CExpDeviceStatusThread::CExpDeviceStatusThread
// 作用：执行CExpDeviceStatusThread。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpDeviceStatusThread::CExpDeviceStatusThread()
{
	m_pInstance = NULL;
	m_pRunPara = NULL;
	m_nRunStatus = STATUS_RUNNING;
	m_nDelay = 2000; //  20260508 从200改为2000
	m_bAskStop = FALSE;
}


// 函数 CExpDeviceStatusThread::~CExpDeviceStatusThread
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpDeviceStatusThread::~CExpDeviceStatusThread(void)
{
}


// 函数 CExpDeviceStatusThread::InitInstance
// 作用：初始化InitInstance。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CExpDeviceStatusThread::InitInstance()
{
	return TRUE;
}

// 函数 CExpDeviceStatusThread::ExitInstance
// 作用：执行ExitInstance。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CWinThread::ExitInstance。
int CExpDeviceStatusThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

// 函数 CExpDeviceStatusThread::InitParameter
// 作用：初始化InitParameter。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpDeviceStatusThread::InitParameter()
{
	ASSERT(m_pInstance != NULL);
	ASSERT(m_pRunPara != NULL);
}

// 函数 CExpDeviceStatusThread::Run
// 作用：执行Run。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 InitParameter、LockInstance、GetInstanceStatus、ReadDeviceStatus、UnlockInstance、Sleep。
int CExpDeviceStatusThread::Run()
{
	InitParameter();

	int iErrTimes = 0;
	while(STATUS_RUNNING == m_nRunStatus)
	{
		if(m_bAskStop)
		{
			m_nRunStatus = STATUS_ASK_STOP;
			break;
		}

		m_pRunPara->LockInstance();

		if (m_pInstance->GetInstanceStatus() != INSTANCE_ERROR)
		{
			BOOL bReturn = m_pInstance->ReadDeviceStatus();
			if(bReturn)
			{
				iErrTimes = 0;
			}
			else
			{
				++iErrTimes;
				//if(iErrTimes >= 3)
				//{
				//	m_pRunPara->UnlockInstance();
				//	m_nRunStatus = STATUS_STOP_ERROR;
				//	break;
				//}
			}
		}
		m_pRunPara->UnlockInstance();

		::Sleep(m_nDelay);
	}

	if(STATUS_STOP_ERROR == m_nRunStatus)
	{
		m_pRunPara->SetCommunicationState(FALSE);

		// 写日志
	}

	return 0;
}
