// 【交接】 GeneralPcr\ExpRunCtrl.cpp
// 作用：实验运行线程。按程序段执行控温、采集荧光、熔解扫描。全部段跑完或中途停止后，才把“实验结束”发给界面。采集循环里不判断阴阳性。
// 先看这些函数：_RunThread、RunProc、CExpRunCtrl、Empty、Run、SetMeltStepRunningState、PostMessage、Initialize。
#include "StdAfx.h"
#include "ExpRunCtrl.h"
#include "LanguageInfo.h"
#include "PopTipInfo.h"
#include "CommInterruptTipDlg.h"
#include "LogManager.h"

// 实验运行主控线程
UINT _RunThread(LPVOID lpParam)
{
	CExpRunCtrl* pRunCtrl = (CExpRunCtrl*) lpParam;
	pRunCtrl->RunProc();
	return 	0;
}
 
// 函数 CExpRunCtrl::CExpRunCtrl
// 作用：执行CExpRunCtrl。
// 参数：pInstance：指针，指向调用方传入的对象；pMsgWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CExpRunCtrl::CExpRunCtrl(CInstancePCR* pInstance, CWnd* pMsgWnd)
{
	m_pInstancePCR = pInstance;
	m_pMsgWnd = pMsgWnd;
	m_pRunThread = NULL;
	m_pTempThread = NULL;
	m_pStatusThread = NULL;
	m_lScanStartTime = -1;

	m_nRunStatus = STATUS_STOP;
	m_bAskStop = FALSE;
	m_strErrorInfo.Empty();

	m_pExpData = NULL;
	m_pRunPara = NULL;

	m_iNotReachTempCount = 0;
	m_bNotReachMeltStartTemp = FALSE;
	m_bFirstAmplifyCycle = FALSE;

	m_dMeltTemBeforeScan = 0;
	m_dMeltTemAfterScan = 0; 

	m_bPowerOffExp = FALSE;
	m_iStartSeg = -1;
	m_iStartStep = -1;
	m_iStartCyle = -1;

	m_bNoStepBeforeMeltStep = FALSE;
	m_fMeltStepStartTem = 60;

	m_bNewSegmentCycle = FALSE;
	m_bFirstTempErr = TRUE;
	m_pLanguage = NULL;
}

// 函数 CExpRunCtrl::~CExpRunCtrl
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpRunCtrl::~CExpRunCtrl(void)
{
	if(NULL != m_pRunPara)
	{
		delete m_pRunPara;
		m_pRunPara = NULL;
	}

	if(NULL != m_pTempThread)
	{
		delete m_pTempThread;
		m_pTempThread = NULL;
	}

	if(NULL != m_pStatusThread)
	{
		delete m_pStatusThread;
		m_pStatusThread = NULL;
	}
}

// 函数 CExpRunCtrl::Run
// 作用：执行Run。
// 参数：pExpData：指针，指向调用方传入的对象；pRunPara：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 SetMeltStepRunningState、PostMessage、Initialize、AfxBeginThread。
BOOL CExpRunCtrl::Run(CExperimentData* pExpData, CExpRunPara* pRunPara)
{
	ASSERT(m_pInstancePCR != NULL);
	ASSERT(m_pMsgWnd != NULL);

	m_pExpData = pExpData;

	if(NULL != m_pRunPara)
	{
		delete m_pRunPara;
		m_pRunPara = NULL;
	}
	m_pRunPara = pRunPara;

	ASSERT(NULL != m_pExpData);
	ASSERT(NULL != m_pRunPara);

	m_pRunPara->SetMeltStepRunningState(FALSE);
	m_pMsgWnd->PostMessage(WM_EXPERIMENT_RUN,0,0);

	// 整个设备初始化
	BOOL bReturn = Initialize();

	if (bReturn)
	{
		// 创建线程,运行控制开始
		m_pRunThread = AfxBeginThread(_RunThread, (LPVOID)this, THREAD_PRIORITY_ABOVE_NORMAL/*THREAD_PRIORITY_NORMAL*/);
	}
	return bReturn;
}

// 子线程初始化
// 函数 CExpRunCtrl::Initialize
// 作用：初始化Initialize。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 RemoveAll、AfxBeginThread、RUNTIME_CLASS、SetInstance、SetExperimentData、SetMsgWnd。
BOOL CExpRunCtrl::Initialize()
{
	BOOL bReturn = TRUE;

	ASSERT(NULL != m_pInstancePCR);

	if(NULL != m_pTempThread)
	{
		delete m_pTempThread;
		m_pTempThread = NULL;
	}
	if(NULL != m_pStatusThread)
	{
		delete m_pStatusThread;
		m_pStatusThread = NULL;
	}
	m_arrayInfo.RemoveAll();
	m_bFirstTempErr = TRUE;

	// 读取温度线程初始化
	m_pTempThread = (CExpTempDataThread*)AfxBeginThread(RUNTIME_CLASS(CExpTempDataThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_pTempThread->m_bAutoDelete = FALSE;
	m_pTempThread->SetInstance(m_pInstancePCR);
	m_pTempThread->SetExperimentData(m_pExpData);
	m_pTempThread->SetMsgWnd(m_pMsgWnd);
	m_pTempThread->SetExpRunPara(m_pRunPara);
	m_pTempThread->SetStartTime(m_pExpData->GetCurTempCollectTime());

	// 设备状态监控线程
	m_pStatusThread = (CExpDeviceStatusThread*)AfxBeginThread(RUNTIME_CLASS(CExpDeviceStatusThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	m_pStatusThread->m_bAutoDelete = FALSE;
	m_pStatusThread->SetInstance(m_pInstancePCR);
	m_pStatusThread->SetExpRunPara(m_pRunPara);

	return bReturn;
}

// 主线程调用程序
// 函数 CExpRunCtrl::RunProc
// 作用：执行RunProc。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Format、_T、GetExperimentInfo、GetFilePath、GetInstance、WriteCommLog。
void CExpRunCtrl::RunProc()
{
	m_nRunStatus = STATUS_RUNNING;
	m_bAskStop = FALSE;

	// 保存文件保存路径的信息到日志中
	if (!m_bPowerOffExp)
	{
		CString strLog;
		strLog.Format(_T("Experiment file save path is %s"), m_pExpData->GetExperimentInfo()->GetFilePath());
		CLogManager::GetInstance()->WriteCommLog(strLog);
	}

	// 记录实验当前状态信息
	m_pRunPara->ExpRun();

	//CExperimentData类温度数据成员设置是否使用热盖
	m_pExpData->SetLidHeater(m_pExpData->GetExperimentInfo()->GetLidHeader());
	m_pInstancePCR->SetInstanceStatus(INSTANCE_USING);

	// 恢复读取温度线程，开始取温度数据
	m_pTempThread->ResumeThread();
	// 恢复读取设备状态监控线程
	m_pStatusThread->ResumeThread();

	BOOL bSuccess = PrepareRunning();
	if (!bSuccess) 
	{
		m_pTempThread->SetRunStatus(STATUS_STOP);
		m_pStatusThread->SetRunStatus(STATUS_STOP);
		return;
	}

	// 热盖预加热
	bSuccess = RunLidHeader();
	if(!bSuccess)
	{
		m_pTempThread->SetRunStatus(STATUS_STOP);
		m_pStatusThread->SetRunStatus(STATUS_STOP);
		return;
	}

	// 处理实验循环数
	int iCurSeg = m_pRunPara->GetCurSegment();
	int iCurCycle = m_pRunPara->GetCurCycle();
	int iCurStep = m_pRunPara->GetCurStep();
	float fPreSegemntTemp = m_pInstancePCR->GetSysTemp(CInstancePCR::SYS_TEMP_CTRL_LOWER); // 前面步骤温度
	float fCurStepTemp = m_pRunPara->GetCurTemp();

	CLinkList<CSegItemInfo>& lnkSegItem = m_pExpData->GetSegment();
	int nSegmentCount = lnkSegItem.GetSize();

	if(m_bAskStop)
	{
		goto ASKSTOP;
	}

	//处理“运行断电保护实验文件”
	if(m_bPowerOffExp)
	{
		iCurSeg = m_iStartSeg;
		iCurStep = m_iStartStep;
		iCurCycle = m_iStartCyle;

		AddInterruptLog(m_iStartSeg+1, m_iStartStep+1, m_iStartCyle+1);

		if(iCurSeg >= 0 && iCurSeg < nSegmentCount)
		{
			//熔曲步骤运行断电时，如果继续运行该程序，从熔曲所在程序段第一个步骤开始运行
			CSegItemInfo* pSetItem = lnkSegItem[iCurSeg];
			if(pSetItem->GetBeMeltSeg() && pSetItem->m_lnkStepItemInfo.GetSize() > 0)
			{
				if(pSetItem->m_lnkStepItemInfo[0]->GetBeCollectAll())
				{
					m_bNoStepBeforeMeltStep = TRUE;
					m_fMeltStepStartTem = 60;
					if(iCurSeg > 0)
					{
						m_fMeltStepStartTem = lnkSegItem[iCurSeg - 1]->m_lnkStepItemInfo.GetTail()->data.m_fAimTem;
					}
				}

				iCurStep = 0;
				iCurCycle = 0;
			}
		}

		ResetPowerOffExpInfo();
	}

	// 设置LED开关
	bSuccess = SetLaserStatus();
	if(!bSuccess)
	{
		m_pTempThread->SetRunStatus(STATUS_STOP);
		m_pStatusThread->SetRunStatus(STATUS_STOP);
		return;
	}

	// 根据系统文件配置参数判断是否执行扫描背景信号值流程
	bSuccess = ChannelSignalCorrection();
	if(!bSuccess)
	{
		m_pTempThread->SetRunStatus(STATUS_STOP);
		m_pStatusThread->SetRunStatus(STATUS_STOP);
		return;
	}

	m_pExpData->SetExpRunning(TRUE);
	for(;iCurSeg < nSegmentCount;++iCurSeg)
	{
		CSegItemInfo segItem = lnkSegItem.GetAt(iCurSeg)->data;
		m_pRunPara->SetCurSegment(iCurSeg);

		if(segItem.GetBeMeltSeg()) // 熔解段
		{
			m_pRunPara->SetCurCycle(0);

			// 熔曲程序段从头开始
			for(iCurStep = 0;iCurStep < segItem.m_lnkStepItemInfo.GetSize();++iCurStep)
			{
				HandleDeviceStatus();

				CStepItemInfo stepItem = segItem.m_lnkStepItemInfo.GetAt(iCurStep)->data;
				m_pRunPara->SetCurStep(iCurStep);
				m_pMsgWnd->SendMessage(WN_EXPERIMENT_STEP_CHANGED);

				switch(stepItem.m_eChkType)
				{
				case CHECK_NONE:
					bSuccess = RunNoneStep(&stepItem,fCurStepTemp);
					break;
				case CHECK_ALL_POINT:
					bSuccess = RunMeltStep(&stepItem,fCurStepTemp,m_pExpData->GetPreStepDelay(iCurSeg,iCurStep));
					break;
				default:
					ASSERT(FALSE);
					break;
				}

				// 处理运行状态
				if(!bSuccess)
				{
					break;
				}

				if(m_bAskStop)
				{
					goto ASKSTOP;
				}

				if(STATUS_RUNNING != m_nRunStatus)
				{
					break;
				}

				fCurStepTemp = stepItem.m_fAimTem;
			}
			iCurStep = 0;
		}
		else // 扩增段或维持段
		{
			m_bNewSegmentCycle = TRUE;

			for (;iCurCycle < segItem.m_iCycleNum;++iCurCycle)
			{	
				m_pRunPara->SetCurCycle(iCurCycle);

				for(;iCurStep < segItem.m_lnkStepItemInfo.GetSize();++iCurStep)
				{
					HandleDeviceStatus();

					CStepItemInfo stepItem = segItem.m_lnkStepItemInfo.GetAt(iCurStep)->data;
					m_pRunPara->SetCurStep(iCurStep);
					m_pMsgWnd->SendMessage(WN_EXPERIMENT_STEP_CHANGED);
					
					switch(stepItem.m_eChkType)
					{
					case CHECK_NONE:
						bSuccess = RunNoneStep(&stepItem, fCurStepTemp);
						break;
					case CHECK_END_POINT:
						m_bFirstAmplifyCycle = iCurCycle == 0;
						bSuccess = RunAmplifyStep(iCurCycle, &stepItem, fCurStepTemp);
						break;
					default:
						ASSERT(FALSE);
						break;
					}

					// 处理运行状态
					if(!bSuccess)
					{
						CTime timeStart = CTime::GetCurrentTime();
						bSuccess = ReconnectDeviceToRun();
						if (!bSuccess)
							break;

						CTime timeEnd = CTime::GetCurrentTime();
						CTimeSpan timeSpan = timeEnd - timeStart;
						long lSeconds = (long)timeSpan.GetTotalSeconds();

						iCurCycle = CalculateCurrentCycle(iCurCycle, &segItem, lSeconds);
						//iCurCycle --;
					}

					if(m_bAskStop)
					{
						goto ASKSTOP;
					}

					if(STATUS_RUNNING != m_nRunStatus)
					{
						break;
					}

					fCurStepTemp = stepItem.m_fAimTem;					
				}

				if(!bSuccess)
				{
					break;
				}

				iCurStep = 0;
			}

			iCurCycle = 0;
		}

		if(!bSuccess)
		{
			break;
		}
	}
	
	if(bSuccess)
	{
		m_pMsgWnd->PostMessage(WM_SEGMENT_OVER,m_nRunStatus);
	}

ASKSTOP:

	m_pExpData->SetExpRunning(FALSE);

	//if(bSuccess)
	//{
	//	bSuccess = m_pInstancePCR->Home();
	//}

	// 热盖释放控温
	if(bSuccess && m_pExpData->GetExperimentInfo()->GetLidHeader())
	{
		bSuccess = m_pInstancePCR->SetLidHeaterTemp(PCR_TEMP_RELEASE);
	}

	//实验结束时，PS96不走降温等待过程
	if(bSuccess && !m_pExpData->GetBePS96ExperFile())
	{
		bSuccess = CoolAtEnd();
	}

	//退出温度监控、系统状态监控线程
	m_pTempThread->SetRunStatus(STATUS_STOP);
	m_pStatusThread->SetRunStatus(STATUS_STOP);

	//停止仪器温度调制
	if(bSuccess)
	{
		bSuccess = SetMultiTemp(PCR_TEMP_RELEASE,PCR_TEMP_RELEASE,PCR_TEMP_RELEASE,0,TEMP_CTRL_NORMAL);
	}

	//设置主线程运行状态
	if(bSuccess)
	{
		if(m_bAskStop)
		{
			m_nRunStatus = STATUS_ASK_STOP;
		}
		else
		{
			m_nRunStatus = STATUS_STOP;
		}
	}
	else
	{
		if (m_bAskStop && m_pExpData->GetConnInterruptCount() > 0)
		{
			m_nRunStatus = STATUS_ASK_STOP;
		}
		else
			m_nRunStatus = STATUS_STOP_ERROR;
	}

	AfterRunning();
	return;
}

// 函数 CExpRunCtrl::SetPowerOffExpInfo
// 作用：设置SetPowerOffExpInfo。
// 参数：bPowerOffExp：是或否；iStartSeg：整数；iStartStep：整数；iStartCyle：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpRunCtrl::SetPowerOffExpInfo(BOOL bPowerOffExp,int iStartSeg,int iStartStep,int iStartCyle)
{
	m_bPowerOffExp = bPowerOffExp;
	m_iStartSeg = iStartSeg;
	m_iStartStep = iStartStep;
	m_iStartCyle = iStartCyle;

	return;
}

// 函数 CExpRunCtrl::ResetPowerOffExpInfo
// 作用：更新或清除ResetPowerOffExpInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CExpRunCtrl::ResetPowerOffExpInfo()
{
	m_bPowerOffExp = FALSE;
	m_iStartSeg = -1;
	m_iStartStep = -1;
	m_iStartCyle = -1;
}

// 实验前准备工作，如设备Home等
// 函数 CExpRunCtrl::PrepareRunning
// 作用：执行PrepareRunning。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 HasBox、IsInBox、GetInstance、MAKELANGID、GetBeEnglish、AfxGetMainWnd。
BOOL CExpRunCtrl::PrepareRunning()
{
	BOOL bReturn = TRUE;

	//如果有进出仓结构则需要判断是否进仓
	if(m_pInstancePCR->HasBox())
	{
		eSysBoxStatus nBoxStatus = BOXSTATE_IN;
		bReturn = m_pInstancePCR->IsInBox(nBoxStatus);
		if(bReturn)
		{
			if(BOXSTATE_OUT == nBoxStatus)
			{
				CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
				WORD wLangId = MAKELANGID(LANG_CHINESE_SIMPLIFIED,SUBLANG_CHINESE_SIMPLIFIED);
				if(pLangInfo->GetBeEnglish())
				{
					wLangId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
				}
				HWND hWnd = NULL;
				CWnd* pMainWnd = AfxGetMainWnd();
				if(NULL != pMainWnd)
				{
					hWnd = pMainWnd->m_hWnd;
				}
				
				if(IDNO == MessageBoxExW(hWnd,pLangInfo->GetText(260),_T("GeneralPcr"),MB_ICONINFORMATION | MB_YESNO,wLangId))
				{
					m_nRunStatus = STATUS_ASK_STOP;	//可重新定义一种状态,20220817,孙文郎
					AfterRunning();
					return FALSE;
				}
				else
				{
					bReturn = m_pInstancePCR->InBox();
				}
			} 
		}
	}
	if(!bReturn)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		AfterRunning();
		return FALSE;
	}

	bReturn = m_pInstancePCR->Home();
	if(!bReturn)
	{
		m_strErrorInfo = _T("");
		m_nRunStatus = STATUS_STOP_ERROR;
		AfterRunning();
		return bReturn;
	}

	// 打开状态灯时下位机同时打开热盖，所有不使用热盖时只能不改变状态灯
	if (m_pExpData->GetExperimentInfo()->GetTempCtrlMode() != TEMP_CTRL_NONE)
	{
		//系统忙时绿灯均速闪烁
		bReturn = m_pInstancePCR->SetStateLED(STALED_GREEN_BUSY);
		if(!bReturn)
		{
			m_strErrorInfo = _T("");
			m_nRunStatus = STATUS_STOP_ERROR;
			AfterRunning();
			return bReturn;
		}
	}

	// 设置控温模式
	bReturn = m_pInstancePCR->SetTempCtrlMode(m_pExpData->GetExperimentInfo()->GetTempCtrlMode());
	if(!bReturn)
	{
		m_strErrorInfo = _T("");
		m_nRunStatus = STATUS_STOP_ERROR;
		AfterRunning();
		return bReturn;
	}

	// 设置PMT控制电压
	WORD wPmtGain = m_pInstancePCR->GetPMTGain(); // 需要修改，当前是PS96模式

	//临时使用，需要通过修改EEPROM实现
	if(NULL != m_pInstancePCR && m_pInstancePCR->GetBe96SiteQPCR())
	{
		wPmtGain = m_pInstancePCR->GetMppcGainMiddle();
	}

	bReturn = m_pInstancePCR->SetPMTGain(wPmtGain);
	if(!bReturn)
	{
		m_strErrorInfo = _T("");
		m_nRunStatus = STATUS_STOP_ERROR;
		AfterRunning();
		return bReturn;
	}

	return bReturn;
}


// 实验完成后设备状态处理
// 函数 CExpRunCtrl::AfterRunning
// 作用：执行AfterRunning。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCurrentTime、GetExperimentInfo、SetEndTime、SaveFile、GetLidHeader、SetStateLED。
void CExpRunCtrl::AfterRunning()
{
	m_pExpData->m_tmEnd = CTime::GetCurrentTime();
	m_pExpData->GetExperimentInfo()->SetEndTime(m_pExpData->m_tmEnd);
	m_pExpData->SaveFile();

	if(STATUS_ASK_STOP == m_nRunStatus || STATUS_STOP == m_nRunStatus)
	{
		//系统空闲时绿灯常亮
		if (m_pExpData->GetExperimentInfo()->GetLidHeader())
		{
			BOOL bSuccess = m_pInstancePCR->SetStateLED(STALED_GREEN_IDLE);
		}
	}

	m_pInstancePCR->SetInstanceStatus(INSTANCE_READY);

	if(NULL != m_pMsgWnd)
	{
		m_pMsgWnd->SendMessage(WM_EXPERIMENT_FINISH,m_nRunStatus);
	}
}

// 函数 CExpRunCtrl::RefreshStatus
// 作用：更新或清除RefreshStatus。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 PostMessage。
void CExpRunCtrl::RefreshStatus()
{
	if (NULL != m_pMsgWnd)
	{
		m_pMsgWnd->PostMessage(WM_EXPERIMENT_REFRESH);
	}
}

// 函数 CExpRunCtrl::RunLidHeader
// 作用：执行RunLidHeader。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetExperimentInfo、GetLidHeader、GetTempCtrlMode、SetCurStage、GetLidTemp、SetLidHeaterTemp。
BOOL CExpRunCtrl::RunLidHeader()
{
	if(!m_pExpData->GetExperimentInfo()->GetLidHeader() || m_pExpData->GetExperimentInfo()->GetTempCtrlMode() == TEMP_CTRL_NONE)
	{
		return TRUE;
	}

	m_pRunPara->SetCurStage(STAGE_LID_HEATER);

	//设置热盖温度
	float fTopTemp = m_pExpData->GetExperimentInfo()->GetLidTemp();
	BOOL bReturn = m_pInstancePCR->SetLidHeaterTemp(fTopTemp);
	if (!bReturn)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		m_strErrorInfo = _T("");
		AfterRunning();
		return FALSE;
	}

	float fLower = m_pInstancePCR->GetSysTemp(CInstancePCR::SYS_TEMP_PELTIER_LOWER);
	bReturn = SetMultiTemp(fLower,fLower,fLower,0,TEMP_CTRL_NORMAL);
	if(!bReturn)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		m_strErrorInfo = _T("");
		AfterRunning();
		return FALSE;
	}

	//判断是否到达目标温度值
	BOOL bSuccess = TRUE;
	float fLidTemp = 0.0f;
	BOOL bToTarget = FALSE;
	int iReadCount = 0;
	float fTempGap = ::fabs(fLidTemp - fTopTemp);
	float fLegalGap = m_pInstancePCR->GetLidTempLegalGap();
	int iSleepTime = 1000;
	int iMaxReadCount = m_pInstancePCR->GetMaxLidHeatSecond() * 1000 / iSleepTime;

#ifdef WEAK_HOTLID_ON_TEMPERATURE
	fLegalGap = 5;
	while(fLidTemp + fLegalGap < fTopTemp || fLidTemp > fTopTemp + fLegalGap)
#else
	while((fTempGap > fLegalGap) /*|| !bToTarget*/)
#endif
	{
		if(m_bAskStop)
			break;

		if (m_pInstancePCR->GetInstanceStatus() == INSTANCE_ERROR)
			break;

		fLidTemp = m_pRunPara->GetLidTemp();
		bToTarget = m_pRunPara->GetLidReachTemp();
		++iReadCount;
		if(iReadCount >= iMaxReadCount)
		{
			bSuccess = FALSE;
			break;
		}

		if(NULL != m_pRunPara && !m_pRunPara->GetCommunicationState())
		{
			bSuccess = FALSE;
			break;
		}

		fTempGap = ::fabs(fLidTemp - fTopTemp);
		::Sleep(iSleepTime);
	}

	if(iReadCount >= iMaxReadCount)
	{
		m_pExpData->SetReachLidTemp(FALSE);

		CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

		WORD wLangId = MAKELANGID(LANG_CHINESE_SIMPLIFIED,SUBLANG_CHINESE_SIMPLIFIED);
		if(pLangInfo->GetBeEnglish())
		{
			wLangId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
		}

		HWND hWnd = NULL;
		CWnd* pMainWnd = AfxGetMainWnd();
		if(NULL != pMainWnd)
		{
			hWnd = pMainWnd->m_hWnd;
		}
		if(IDYES == MessageBoxExW(hWnd,pLangInfo->GetText(246),_T("GeneralPcr"),MB_ICONINFORMATION | MB_YESNO,wLangId))
		{
			bSuccess = TRUE;
		}
	}

	if(m_bAskStop)
	{
		return bSuccess;
	}

	if(!bSuccess)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		m_strErrorInfo = _T("");
		AfterRunning();
	}

	return bSuccess;
}

// 函数 CExpRunCtrl::SetLaserStatus
// 作用：设置SetLaserStatus。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 _T、AfterRunning。
BOOL CExpRunCtrl::SetLaserStatus()
{
	BYTE LaserState = 255;
	BOOL bReturn = m_pInstancePCR->SetLaserStatus(2, LaserState);

	if (!bReturn)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		m_strErrorInfo = _T("");
		AfterRunning();
	}

	return bReturn;
}

// 扫描通道信号值修正，根据设置进行预扫描进行
// 函数 CExpRunCtrl::ChannelSignalCorrection
// 作用：执行ChannelSignalCorrection。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 AfterRunning。
BOOL CExpRunCtrl::ChannelSignalCorrection()
{
	BOOL bReturn = TRUE;

	if(!bReturn)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		AfterRunning();
	}

	return bReturn;
}

// 处理系统状态，如进出仓/开盖等
// 函数 CExpRunCtrl::HandleDeviceStatus
// 作用：执行HandleDeviceStatus。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetDeviceStatus、SetStateLED、_T、GetExperimentInfo、GetLidHeader。
void CExpRunCtrl::HandleDeviceStatus()
{
	tagDeviceStatus* pStatus = m_pInstancePCR->GetDeviceStatus();

	//进出仓按钮是否按下
	if (1 == pStatus->cSysBox)
	{
		//设置状态灯黄色显示
		m_pInstancePCR->SetStateLED(STALED_YELLOW_PCR_BTNDOWN);
		if (IDOK == AfxMessageBox(_T("Please do not open the door during running !"),MB_ICONINFORMATION |MB_OK))
		{
			m_pInstancePCR->SetStateLED(STALED_GREEN_BUSY);
		}
	}

	// 盖子是否被打开
	if (1 == pStatus->cLid)
	{
		//设置状态灯黄色显示
		m_pInstancePCR->SetStateLED(STALED_YELLOW_PCR_BTNDOWN);
		if (IDOK == AfxMessageBox(_T("Please do not open the lid during running !"),MB_ICONINFORMATION |MB_OK))
		{
			if (m_pExpData->GetExperimentInfo()->GetLidHeader())
				m_pInstancePCR->SetStateLED(STALED_GREEN_BUSY);
		}
	}
}

//  运行不进行荧光检测步骤，只控温或等待
// 函数 CExpRunCtrl::RunNoneStep
// 作用：执行RunNoneStep。
// 参数：pStep：指针，指向调用方传入的对象；fPreTemp：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 SetMultiTemp、RunWaitReachTemp、GetStepVolumeDelaySec、RunStepDelay。
BOOL CExpRunCtrl::RunNoneStep(CStepItemInfo* pStep, float fPreTemp)
{
	int nTemChangedSecond = 0;

	//设置目标温度
	BOOL bReturn = SetMultiTemp(pStep->m_fAimTem,pStep->m_fAimTem,pStep->m_fAimTem,pStep->m_fRate,TEMP_CTRL_NORMAL);
	if (!bReturn) 
	{
		return FALSE;
	}
	
	if(m_bAskStop)
	{
		return TRUE;
	}

	// 温度控温，并判断是否到达温度
	int iUseTime = RunWaitReachTemp(pStep);

	if(m_bAskStop)
	{
		return TRUE;
	}

	//处理延时等待，96孔QPCR可能有额外延时（和体积相关）
	int iRealDelay = (int)m_pExpData->GetStepVolumeDelaySec(pStep->m_fAimTem);
	iRealDelay += pStep->m_iDelay;
	RunStepDelay(iRealDelay);

	return TRUE;
}

// 函数 CExpRunCtrl::RunWaitReachTemp
// 作用：执行RunWaitReachTemp。
// 参数：pStep：指针，指向调用方传入的对象。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetExperimentInfo、GetTempCtrlMode、GetTempMode、GetMaxTempCtrlSecond、GetTempLegalGap、GetCurrentTime。
int CExpRunCtrl::RunWaitReachTemp(CStepItemInfo* pStep)
{
	if (m_pExpData->GetExperimentInfo()->GetTempCtrlMode() == TEMP_CTRL_NONE)
		return 0;

	BOOL bIgnoreGap = FALSE;
	if(TEMP_MODE_CONSTANT == m_pInstancePCR->GetTempMode())
	{
		if (!m_bNewSegmentCycle)
		{
			return 0;
		}

		if (m_bFirstAmplifyCycle && CHECK_END_POINT == pStep->m_eChkType)
		{
			bIgnoreGap = TRUE;
		}
	}

	LONGLONG lUseSeconds = 0;
	int iMaxCtrlTime = m_pInstancePCR->GetMaxTempCtrlSecond();
	float fTempLegalGap = m_pInstancePCR->GetTempLegalGap();
	if (bIgnoreGap)
	{
		fTempLegalGap = 0.5;
	}
	CTime timeStart = CTime::GetCurrentTime();
	float fCurTemp = m_pRunPara->GetCurTemp();
	BOOL bCurReachTemp = m_pRunPara->GetCurReachTemp();
	float fTempGap = ::fabs(fCurTemp - pStep->m_fAimTem);
	while(fTempGap > fTempLegalGap)
	{
		if(m_bAskStop)
		{
			break;
		}

		::Sleep(50);
		CTime timeTemp = CTime::GetCurrentTime();
		CTimeSpan timespan = timeTemp - timeStart;
		lUseSeconds = timespan.GetTotalSeconds();
		if (lUseSeconds >= iMaxCtrlTime)
		{
			m_iNotReachTempCount ++;
			break;
		}
		if(STATUS_RUNNING != m_nRunStatus )
		{
			break;
		}

		fCurTemp = m_pRunPara->GetCurTemp();
		bCurReachTemp = m_pRunPara->GetCurReachTemp();
		if (bCurReachTemp)
			break;
		fTempGap = ::fabs(fCurTemp - pStep->m_fAimTem);
	}

	if(TEMP_MODE_CONSTANT == m_pInstancePCR->GetTempMode())
	{
		m_bNewSegmentCycle = FALSE;
	}

	return (int)lUseSeconds;
}

// 函数 CExpRunCtrl::RunWaitReachTemp
// 作用：执行RunWaitReachTemp。
// 参数：fAimTem：小数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetExperimentInfo、GetTempCtrlMode、GetCurrentTime、GetMaxTempCtrlSecond、GetTempLegalGap、GetCurTemp。
int CExpRunCtrl::RunWaitReachTemp(float fAimTem)
{
	if (m_pExpData->GetExperimentInfo()->GetTempCtrlMode() == TEMP_CTRL_NONE)
		return 0;

	if(fAimTem <= 0)
	{
		return 0;
	}

	LONGLONG lUseSeconds = 0;
	CTime timeStart = CTime::GetCurrentTime();
	int iMaxCtrlTime = m_pInstancePCR->GetMaxTempCtrlSecond();

	float fTempLegalGap = m_pInstancePCR->GetTempLegalGap();
	float fCurTemp = m_pRunPara->GetCurTemp();
	float fTempGap = ::fabs(fCurTemp - fAimTem);

	BOOL bCurReachTemp = m_pRunPara->GetCurReachTemp();
	
	while (fTempGap > fTempLegalGap || !bCurReachTemp)
	{
		if(m_bAskStop)
		{
			break;
		}

		::Sleep(50);
		CTime timeTemp = CTime::GetCurrentTime();
		CTimeSpan timespan = timeTemp - timeStart;
		lUseSeconds = timespan.GetTotalSeconds();
		if (lUseSeconds >= iMaxCtrlTime)
		{
			++m_iNotReachTempCount;
			break;
		}
		if(m_nRunStatus != STATUS_RUNNING)
		{
			break;
		}

		fCurTemp = m_pRunPara->GetCurTemp();
		bCurReachTemp = m_pRunPara->GetCurReachTemp();
		fTempGap = ::fabs(fCurTemp - fAimTem);
	}

	return (int)lUseSeconds;
}

// 函数 CExpRunCtrl::CoolAtEnd
// 作用：执行CoolAtEnd。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 ReadPCRTemp、GetEndCoolTemperature、SetMultiTemp、Sleep、GetSleepMsAfterCool。
BOOL CExpRunCtrl::CoolAtEnd()
{
	float fTem = 0;
	BOOL bTarget = FALSE;

	BOOL bReturn = m_pInstancePCR->ReadPCRTemp(fTem,bTarget);
	if (!bReturn)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		return FALSE;
	}

	float fEndCoolTem = m_pInstancePCR->GetEndCoolTemperature();
	if(fTem <= fEndCoolTem)
	{
		return TRUE;
	}

	bReturn = SetMultiTemp(fEndCoolTem,fEndCoolTem,fEndCoolTem,4.0,TEMP_CTRL_NORMAL);
	if (!bReturn)
	{
		m_nRunStatus = STATUS_STOP_ERROR;
		return FALSE;
	}

	float fLegal = fTem - fEndCoolTem;
	while(fLegal > 2.0)
	{
		Sleep(200);
		if(m_bAskStop)
		{
			Sleep(1200);
			return TRUE;
		}

		bReturn = m_pInstancePCR->ReadPCRTemp(fTem,bTarget);
		if (!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			return FALSE;
		}
		fLegal = fTem - fEndCoolTem;
	}

	int iTempInt1 = m_pInstancePCR->GetSleepMsAfterCool() / 100;
	for(int i = 0;i < iTempInt1;++i)
	{
		Sleep(100);
		if(m_bAskStop)
		{
			Sleep(200);
			return TRUE;
		}
	}

	return TRUE;
}

// 运行指定等待时间
// 函数 CExpRunCtrl::RunStepDelay
// 作用：执行RunStepDelay。
// 参数：iWaitSecond：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetCommunicationState、Sleep。
void CExpRunCtrl::RunStepDelay(int iWaitSecond)
{
	for (int i = 0;i < iWaitSecond;++i)
	{
		if(m_bAskStop)
		{
			break;
		}

		if(NULL != m_pRunPara && !m_pRunPara->GetCommunicationState())
		{
			break;
		}

		if(STATUS_RUNNING != m_nRunStatus)
		{
			break;
		}
		::Sleep(1000);
	}

	return;
}

// 函数 CExpRunCtrl::RunMeltStep
// 作用：执行RunMeltStep。
// 参数：pStep：指针，指向调用方传入的对象；fPreTemp：小数；iPreDelay：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 SetMultiTemp、ReadPCRTemp、Sleep、GetPreMeltMinSleepSec、SetMeltStepRunningState、GetBe96SiteQPCR。
BOOL CExpRunCtrl::RunMeltStep(CStepItemInfo* pStep,float fPreTemp,int iPreDelay)
{
	BOOL bReturn = FALSE;
	BOOL bTarget = FALSE;

	if(m_bNoStepBeforeMeltStep)
	{
		bReturn = SetMultiTemp(m_fMeltStepStartTem,m_fMeltStepStartTem,m_fMeltStepStartTem,pStep->m_fRate,TEMP_CTRL_NORMAL);
		if(!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			return FALSE;
		}

		float fRealTem = 0;
		for(int i = 0;i < 60;++i)
		{
			bReturn = m_pInstancePCR->ReadPCRTemp(fRealTem,bTarget);
			if(!bReturn)
			{
				m_nRunStatus = STATUS_STOP_ERROR;
				return FALSE;
			}

			if(bTarget)
			{
				break;
			}
			Sleep(1000);
		}
		
		if(bTarget)
		{
			fPreTemp = m_fMeltStepStartTem;
		}
		else
		{
			fPreTemp = fRealTem;
		}
		iPreDelay =0;
	}
	else
	{
		// 如果当前温度大于熔解段目标温度，则无法进行熔解扫描，返回
		if(fPreTemp >= pStep->m_fAimTem)
		{
			m_bNotReachMeltStartTemp = TRUE;
			return TRUE;
		}
	}
	
	//熔曲步骤上一个步骤的延时时间如果小于30秒，补充延时时间，确保起始温度稳定
	int iPreMeltMinSlpSec = m_pInstancePCR->GetPreMeltMinSleepSec();
	if(iPreDelay < iPreMeltMinSlpSec)
	{
		int iCycles = (iPreMeltMinSlpSec - iPreDelay) * 10;
		for(int i = 0;i < iCycles;++i)
		{
			Sleep(100);
			if(m_bAskStop)
			{
				return TRUE;
			}
		}
	}

	m_pRunPara->SetMeltStepRunningState(TRUE);

	m_dMeltTemBeforeScan = 0;
	m_dMeltTemAfterScan = 0;

	float fStartTem = 0;

	BOOL bPwmMelt = m_pInstancePCR->GetBe96SiteQPCR();
	float fPwmK1 = 1,fPwmB1 = 0,fPwmK2 = 1,fPwmB2 = 0,fPwmK3 = 1,fPwmB3 = 0,fBasePwm1 = 0,fBasePwm2 = 0,fBasePwm3 = 0;
	float fIncrementPwm1 = 0,fIncrementPwm2 = 2,fIncrementPwm3 = 3;  
	if(bPwmMelt)
	{
		//PWM控温时，先稳定初始温度
		fPwmK1 = m_pInstancePCR->GetPwmK1();
		fPwmB1 = m_pInstancePCR->GetPwmB1();
		fPwmK2 = m_pInstancePCR->GetPwmK2();
		fPwmB2 = m_pInstancePCR->GetPwmB2();
		fPwmK3 = m_pInstancePCR->GetPwmK3();
		fPwmB3 = m_pInstancePCR->GetPwmB3();

		fIncrementPwm1 = pStep->m_fIncrement * fPwmK1;
		fIncrementPwm2 = pStep->m_fIncrement * fPwmK2;
		fIncrementPwm3 = pStep->m_fIncrement * fPwmK3;

		if(fPreTemp < 50)
		{
			fPreTemp = 50;
		}

		fBasePwm1 = fPreTemp * fPwmK1 + fPwmB1;
		fBasePwm2= fPreTemp * fPwmK2 + fPwmB2;
		fBasePwm3 = fPreTemp * fPwmK3 + fPwmB3;
		bReturn = m_pInstancePCR->SetPWMTemp(fPreTemp,fPreTemp,fPreTemp,WORD(fBasePwm1),WORD(fBasePwm2),WORD(fBasePwm3));
		if (!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			return FALSE;
		}

		int iTempInt1 = m_pInstancePCR->GetPWMInitWaitMs() / 100;
		for(int i = 0;i < iTempInt1;++i)
		{
			Sleep(100);
			if(m_bAskStop)
			{
				return TRUE;
			}
		}

		bReturn = m_pInstancePCR->ReadPCRTemp(fStartTem,bTarget);
		if (!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			return FALSE;
		}
		float fDiff = fStartTem - fPreTemp;

		//修正PWM温度偏差
		fStartTem = fPreTemp - fDiff;
		if(pStep->m_fIncrement < 0.5)
		{
			fStartTem -= pStep->m_fIncrement * 2;
		}
		else
		{
			fStartTem -= pStep->m_fIncrement;
		}
		
		//下发初始温度
		fBasePwm1 = fStartTem * fPwmK1 + fPwmB1;
		fBasePwm2= fStartTem * fPwmK2 + fPwmB2;
		fBasePwm3 = fStartTem * fPwmK3 + fPwmB3;
		bReturn = m_pInstancePCR->SetPWMTemp(fStartTem,fStartTem,fStartTem,WORD(fBasePwm1),WORD(fBasePwm2),WORD(fBasePwm3));
		if (!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			return FALSE;
		}
		for(int i = 0;i < iTempInt1;++i)
		{
			Sleep(100);
			if(m_bAskStop)
			{
				return TRUE;
			}
		}
	}
	else
	{
		if(fPreTemp < 30)
		{
			fPreTemp = 30;
		}

		fStartTem = fPreTemp;
		bReturn = SetMultiTemp(fStartTem,fStartTem,fStartTem,pStep->m_fRate,TEMP_CTRL_NORMAL);
		if(!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			return FALSE;
		}
	}

	int iUseTime = 0;
	int iDataIndex = 0,iCalcCycles = 6;
	if(0 != pStep->m_fIncrement)
	{
		iCalcCycles = int((pStep->m_fAimTem - fPreTemp) / pStep->m_fIncrement) + 20;
	}
	for(float fTem = fStartTem;(m_dMeltTemBeforeScan + m_dMeltTemAfterScan) / 2 <= pStep->m_fAimTem && iDataIndex < iCalcCycles;fTem += pStep->m_fIncrement)
	{
		if(bPwmMelt)
		{
			bReturn = m_pInstancePCR->SetPWMTemp(fTem,fTem,fTem,WORD(fBasePwm1 + iDataIndex * fIncrementPwm1),WORD(fBasePwm2 + iDataIndex * fIncrementPwm2),WORD(fBasePwm3 + iDataIndex * fIncrementPwm3));
		}
		else
		{
			bReturn = SetMultiTemp(fTem,fTem,fTem,pStep->m_fRate,TEMP_CTRL_NORMAL);
		}
		
		if(!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			return FALSE;
		}

		if(m_bAskStop)
		{
			return TRUE;
		}

		//并判断是否到达温度
		if(bPwmMelt)
		{
			for(int i = 0;i < 60;++i)
			{
				Sleep(100);
				if(m_bAskStop)
				{
					return TRUE;
				}
			}
		}
		else
		{
			iUseTime = RunWaitReachTemp(fTem);
		}

		if(m_bAskStop)
		{
			return TRUE;
		}

		clock_t ckStart = clock();
		
		//检测
		m_pRunPara->LockInstance();
		if(pStep->GetBeCollectAll())
		{
			// 记录扫描开始时间
			unsigned long long startTime = ::GetTickCount64();

			float fCurTemp = 0.0f;
			BOOL bCurToTarget = FALSE;

			//扫描前获取一次温度
			bReturn = m_pInstancePCR->ReadPCRTemp(fCurTemp,bCurToTarget);
			if(!bReturn)
			{
				m_nRunStatus = STATUS_STOP_ERROR;
				m_pRunPara->UnlockInstance();
				return FALSE;
			}
			m_dMeltTemBeforeScan = fCurTemp;

			// 扫描
			bReturn = m_pInstancePCR->ScanOnce(&m_bAskStop);
			if(!bReturn)
			{
				m_nRunStatus = STATUS_STOP_ERROR;
				m_pRunPara->UnlockInstance();
				return FALSE;
			}

			//扫描后获取一次温度
			bReturn = m_pInstancePCR->ReadPCRTemp(fCurTemp,bCurToTarget);
			if(!bReturn)
			{
				m_nRunStatus = STATUS_STOP_ERROR;
				m_pRunPara->UnlockInstance();
				return FALSE;
			}
			m_dMeltTemAfterScan = fCurTemp;

			if(m_bAskStop)
			{
				m_pRunPara->UnlockInstance();
				return TRUE;
			}

			//读取荧光数据
			if(!ReadScanDataOnce(ESDT_MELT))
			{
				m_nRunStatus = STATUS_STOP_ERROR;
				m_pRunPara->UnlockInstance();
				return FALSE;
			}

			m_pMsgWnd->SendMessage(WN_EXPERIMENT_FLU_CHANGED,iDataIndex++,1);
			m_pMsgWnd->PostMessage(WM_MELT_ONETEM_OVER, int(fTem * 100),0);
		}
		m_pRunPara->UnlockInstance();

		clock_t ckExist = clock() - ckStart;
		m_pRunPara->SetScanGetDataMs(ckExist);
	}

	//熔曲步骤执行完毕后，即使后面还有其它流程，也不再进行断电保护，20220824
	m_pMsgWnd->PostMessage(WM_SEGMENT_OVER,m_nRunStatus);

	RunStepDelay(pStep->m_iDelay);

	m_pRunPara->SetMeltStepRunningState(FALSE);

	return TRUE;
}

// 函数 CExpRunCtrl::RunAmplifyStep
// 作用：执行RunAmplifyStep。
// 参数：iCycleC：整数；pStep：指针，指向调用方传入的对象；fPreTemp：小数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetExperimentInfo、GetTempCtrlMode、GetStepGradientInfo、SetMultiTemp、RunWaitReachTemp、GetTempMode。
BOOL CExpRunCtrl::RunAmplifyStep(int iCycleC, CStepItemInfo* pStep, float fPreTemp)
{
	int iUseTime = 0;
	BOOL bReturn = FALSE;

	// 控温
	if(TEMP_CTRL_NONE != m_pExpData->GetExperimentInfo()->GetTempCtrlMode())
	{
		if (pStep->m_bSelGrad)
		{
			//设置梯度模式
			float ColTemp[12] = {0};
			float DeltaT = 0; 
			float fCaliAimT = 0;
			float fCaliDeltaT = 0;
			pStep->GetStepGradientInfo(ColTemp,DeltaT,fCaliAimT,fCaliDeltaT);
			bReturn = SetMultiTemp(fCaliAimT,(fCaliAimT * 2 + fCaliDeltaT) / 2,fCaliAimT+fCaliDeltaT,0,TEMP_CTRL_GRADIENT);
			if(!bReturn)
			{
				m_nRunStatus = STATUS_STOP_ERROR;
				return FALSE;
			}
		}
		else
		{
			//普通模式
			bReturn = SetMultiTemp(pStep->m_fAimTem,pStep->m_fAimTem,pStep->m_fAimTem,pStep->m_fRate,TEMP_CTRL_NORMAL);
			if(!bReturn)
			{
				m_nRunStatus = STATUS_STOP_ERROR;
				return FALSE;
			}
		}
		
		//并判断是否到达温度
		iUseTime = RunWaitReachTemp(pStep);
	}

	if(m_bAskStop)
	{
		return TRUE;
	}

	//延时等待
	if(TEMP_MODE_CONSTANT == m_pInstancePCR->GetTempMode())
	{
		int iWaitSecond = pStep->m_iDelay /*- iUseTime*/;

		if(CHECK_END_POINT == pStep->m_eChkType)
		{
			int ScanGetDataSec = m_pRunPara->GetScanDataSecond();
			if(ScanGetDataSec > 0)
			{
				iWaitSecond -= ScanGetDataSec;
			}
			else
			{
				iWaitSecond -= m_pInstancePCR->GetScanOnceTime();
			}
		}
		RunStepDelay(iWaitSecond);
	}
	else
	{
		//96孔QPCR有额外延时
		int iRealDelay = (int)m_pExpData->GetStepVolumeDelaySec(pStep->m_fAimTem);
		iRealDelay += pStep->m_iDelay;
		RunStepDelay(iRealDelay);
	}

	if(m_bAskStop)
	{
		return TRUE;
	}

	clock_t ckScanStart = clock();

	//检测
	m_pRunPara->LockInstance();
	if(pStep->GetBeCollect())
	{
		// 判断是否到达扫描时的温度，恒温仪如果平均温度偏差超过1度，则认为有问题
		CompareTempAndWriteLog(iCycleC, pStep);

		// 记录扫描开始时间
		unsigned long long startTime = ::GetTickCount64();
		// 扫描
		bReturn = m_pInstancePCR->ScanOnce(&m_bAskStop);
		if(!bReturn)
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			m_pRunPara->UnlockInstance();
			return FALSE;
		}

		if(m_bAskStop)
		{
			m_pRunPara->UnlockInstance();
			return TRUE;
		}

		// 记录扫描结束时间
		unsigned long long currentTime = ::GetTickCount64();
		// 处理传输循环数或时间数据
		CreateAndSendCycle((long)startTime,(long)currentTime,iCycleC);

		//读取荧光数据
		if(!ReadScanDataOnce(ESDT_AMP))
		{
			m_nRunStatus = STATUS_STOP_ERROR;
			m_pRunPara->UnlockInstance();
			return FALSE;
		}

		m_pMsgWnd->SendMessage(WN_EXPERIMENT_FLU_CHANGED,iCycleC+1,0);
	}
	m_pRunPara->UnlockInstance();

	m_pRunPara->SetScanGetDataMs(clock() - ckScanStart);

	return TRUE;
}

// 读取荧光扫描数据
// 函数 CExpRunCtrl::ReadScanDataOnce
// 作用：读取ReadScanDataOnce。
// 参数：eScanDataType。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetChannelCount、ReadAllFLUData、AddAmplifyFluOriginalData、AddMeltFluOriginalData。
BOOL CExpRunCtrl::ReadScanDataOnce(ESCANDATATYPE eScanDataType)
{
	int nChannelCount = m_pExpData->GetChannelCount();
	CUIntArray* pAryFlu = new CUIntArray[nChannelCount];
	if(NULL == pAryFlu)
	{
		return FALSE;
	}

	BOOL bReturn = FALSE;
	bReturn = m_pInstancePCR->ReadAllFLUData(pAryFlu,nChannelCount);
	if(!bReturn)
	{
		delete [] pAryFlu;
		return FALSE;
	}

	// 保存数据
	for(int ichannel = 1;ichannel <= nChannelCount;++ichannel)
	{
		if(ESDT_AMP == eScanDataType)
		{
			m_pExpData->AddAmplifyFluOriginalData(pAryFlu[ichannel - 1],ichannel);
		}
		else if(ESDT_MELT == eScanDataType)
		{
			m_pExpData->AddMeltFluOriginalData(pAryFlu[ichannel - 1],ichannel,(m_dMeltTemBeforeScan + m_dMeltTemAfterScan) / 2);
		}
	}

	delete [] pAryFlu;

	return TRUE;
}

// 处理扩增数据的X轴数据，判断是循环数还是时间
// 函数 CExpRunCtrl::CreateAndSendCycle
// 作用：创建或加入CreateAndSendCycle。
// 参数：lStartTime；lEndTime；iCycleCount：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetPlateInfo、GetTubeCount、RemoveAll、GetTempMode、Add、AddAmplifyCycleX。
void CExpRunCtrl::CreateAndSendCycle(long lStartTime, long lEndTime, int iCycleCount)
{
	int iTubeCount = m_pExpData->GetPlateInfo()->GetTubeCount();
	CUIntArray	arrayCycleX;
	arrayCycleX.RemoveAll();
	if (m_pInstancePCR->GetTempMode() == TEMP_MODE_UPDOWN)
	{
		for (int i=0; i<iTubeCount; i++)
		{
			arrayCycleX.Add(iCycleCount + 1);
		}
	}
	else
	{
		if (m_lScanStartTime == -1)
		{
			m_lScanStartTime = lStartTime;
		}

		long lStart = lStartTime - m_lScanStartTime + 1000;
		long lStep = (lEndTime - lStartTime) / (iTubeCount-1);

		for (int i=0; i<iTubeCount; i++)
		{
			arrayCycleX.Add(lStartTime + lStep * i);
		}
	}

	m_pExpData->AddAmplifyCycleX(&arrayCycleX);
}

// 函数 CExpRunCtrl::SetMultiTemp
// 作用：设置SetMultiTemp。
// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数；fRate：小数；cMode。
// 返回：返回是或否。
// 过程：函数里会调用 GetExperimentInfo、GetTempCtrlMode、SetTempTarget。
BOOL CExpRunCtrl::SetMultiTemp(float fTemp1, float fTemp2, float fTemp3, float fRate, BYTE cMode)
{
	if (m_pExpData->GetExperimentInfo()->GetTempCtrlMode() == TEMP_CTRL_NONE)
		return TRUE;

	BOOL bReturn = m_pInstancePCR->SetMultiTemp(fTemp1, fTemp2, fTemp3, fRate, cMode);
	if (bReturn)
	{
		m_pExpData->SetTempTarget(fTemp1, fTemp2, fTemp3);
	}

	return bReturn;
}

// 判断是否到达扫描时的温度，恒温仪如果平均温度偏差超过1度，则认为有问题
// 函数 CExpRunCtrl::CompareTempAndWriteLog
// 作用：执行CompareTempAndWriteLog。
// 参数：iCycle：整数；pStep：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 fabs、GetCurTemp、Empty、ReadAllTemp、Format、_T。
void CExpRunCtrl::CompareTempAndWriteLog(int iCycle, CStepItemInfo* pStep)
{
	if(::fabs(m_pRunPara->GetCurTemp() - pStep->m_fAimTem) <= 1.0)
		return;

	int iErrChaCount = 0;
	CString strChannel, strTemp;
	strChannel.Empty();
	BOOL bReachTemp = FALSE;
	int iChannelCount = 6;
	float* pChTemp = new float[iChannelCount];
	if (m_pInstancePCR->ReadAllTemp(iChannelCount, pChTemp, bReachTemp))
	{
		for (int i=0; i<iChannelCount; i++)
		{
			if (::fabs(pChTemp[i] - pStep->m_fAimTem) > 3.0)
			{
				iErrChaCount ++;
				strTemp.Format(_T("%d"), i+1);
				if (strChannel.IsEmpty())
				{
					strChannel = strTemp;
				}
				else
				{
					strChannel += _T(", ");
					strChannel += strTemp;
				}
			}
		}
	}

	if (!strChannel.IsEmpty())
	{
		strTemp.Format(_T(" %d"), iCycle+1);
		CString strLog;
		strLog = m_pLanguage->GetText(238);
		strLog += strTemp;
		if (m_pLanguage->GetLanguage() == LANGUAGE_ENG)
			strLog += _T(" ");
		strLog += m_pLanguage->GetText(51);
		strLog += strChannel;
		if (m_pLanguage->GetLanguage() == LANGUAGE_ENG)
			strLog += _T(" ");
		strLog += m_pLanguage->GetText(478);

		if (m_bFirstTempErr)
		{
			m_pExpData->AddLog(strLog);
			if (iErrChaCount >=3)
			{
				m_arrayInfo.Add(strLog);
			}
			m_bFirstTempErr = FALSE;
		}
	}

	delete pChTemp;
}

// 函数 CExpRunCtrl::GetRunLog
// 作用：读取GetRunLog。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 Empty、GetCount、GetAt。
CString CExpRunCtrl::GetRunLog()
{
	CString strLog;
	strLog.Empty();
	if (!m_bFirstTempErr && m_arrayInfo.GetCount() > 0)
	{
		strLog = m_arrayInfo.GetAt(0);
	}

	return strLog;
}

// 函数 CExpRunCtrl::AddInterruptLog
// 作用：创建或加入AddInterruptLog。
// 参数：iSegNo：整数；iStepNo：整数；iCycleNo：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetText、Format、_T、AddLog。
void CExpRunCtrl::AddInterruptLog(int iSegNo, int iStepNo, int iCycleNo)
{
	if (iStepNo == 1 && iStepNo == 1 && iCycleNo == 1)
		return;

	CString strLog, strTemp;
	strLog = m_pLanguage->GetText(484);

	strTemp.Format(_T("%s:%d, %s:%d, %s:%d"), m_pLanguage->GetText(57), iSegNo, m_pLanguage->GetText(58), iStepNo, m_pLanguage->GetText(238), iCycleNo);
	strLog += _T(" ");
	strLog += strTemp;

	m_pExpData->AddLog(strLog);
}

// 函数 CExpRunCtrl::ReconnectDeviceToRun
// 作用：执行ReconnectDeviceToRun。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 SendMessage、SetInstanceStatus、ConnInterruptOnce、GetExperimentInfo、GetRemainSec、DoModal。
BOOL CExpRunCtrl::ReconnectDeviceToRun()
{
	if (m_bAskStop)
		return TRUE;

	m_pMsgWnd->SendMessage(WN_EXPERIMENT_DISCONNECT, 0);
	m_pInstancePCR->SetInstanceStatus(INSTANCE_ERROR);
	m_pExpData->ConnInterruptOnce();

	CCommInterruptTipDlg dlg;
	dlg.m_pInstancePCR = m_pInstancePCR;
	dlg.m_pExpData = m_pExpData;
	dlg.m_iRemainSec = m_pExpData->GetExperimentInfo()->GetRemainSec();
	if (dlg.DoModal() == IDCANCEL)
	{
		if (dlg.m_retCode == 0)
		{
			m_pExpData->SetReconnectState(1);
			m_pRunPara->SetCommunicationState(TRUE);
			m_nRunStatus = STATUS_RUNNING;
			m_pMsgWnd->SendMessage(WN_EXPERIMENT_DISCONNECT, 1);
			return TRUE;
		}
		else if (dlg.m_retCode == 1)
		{
			m_pExpData->SetReconnectState(2);
		}
		else
		{
			m_bAskStop = TRUE;
		}
	}

	return FALSE;
}

// 实验中断时根据中断时间来处理循环数，如果中断时间超过一个循环以上，则自动补充整数倍的循环数，数据为0，同时不能进行Ct计算
// 函数 CExpRunCtrl::CalculateCurrentCycle
// 作用：计算CalculateCurrentCycle。
// 参数：iCycle：整数；pSegment：指针，指向调用方传入的对象；iDelaySecond：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CalculateTotalSeconds、long、GetPlateInfo、GetTubeCount、GetChannelCount、GetCurrentAmplifyCycleX。
int CExpRunCtrl::CalculateCurrentCycle(int iCycle, CSegItemInfo* pSegment, int iDelaySecond)
{
	int iReturnCycle = iCycle;
	long lSegmengTime = pSegment->CalculateTotalSeconds();
	if (lSegmengTime < PS96_SCANSEC)
		lSegmengTime = long(PS96_SCANSEC + 0.5);
	int iAddCycle = iDelaySecond / lSegmengTime + 1;
	if (iCycle + iAddCycle > pSegment->m_iCycleNum)
	{
		iReturnCycle = pSegment->m_iCycleNum + 1;
	}
	else
	{
		int iTubeCount = m_pExpData->GetPlateInfo()->GetTubeCount();
		int nChannelCount = m_pExpData->GetChannelCount();
		CUIntArray	arrayCycleX;
		CUIntArray	arrayFluoValue;
		long lLastScanTime = m_pExpData->GetCurrentAmplifyCycleX(1);
		iReturnCycle = iCycle + iAddCycle;
		for (int i=0; i<iAddCycle; i++)
		{
			arrayCycleX.RemoveAll();
			for (int j=0; j<iTubeCount; j++)
			{
				if (m_pInstancePCR->GetTempMode() == TEMP_MODE_UPDOWN)
				{
					arrayCycleX.Add(lLastScanTime + lSegmengTime*(i+1));
				}
				else
				{
					arrayCycleX.Add(iCycle + i);
				}
			}
			m_pExpData->AddAmplifyCycleX(&arrayCycleX);

			for(int ichannel = 1;ichannel <= nChannelCount;++ichannel)
			{
				arrayFluoValue.RemoveAll();
				for (int j=0; j<iTubeCount; j++)
				{
					arrayFluoValue.Add(0);
				}

				m_pExpData->AddAmplifyFluOriginalData(arrayFluoValue,ichannel);
			}
			m_pMsgWnd->SendMessage(WN_EXPERIMENT_FLU_CHANGED, iCycle+i, 0);
		}

		int iRemainSecond = m_pExpData->GetExperimentInfo()->GetRemainSec();
		iRemainSecond -= lSegmengTime * iAddCycle;
		m_pExpData->GetExperimentInfo()->SetRemainSec(iRemainSecond);
		m_pExpData->SetHasZeroValues(TRUE);
	}

	return iReturnCycle;
}
