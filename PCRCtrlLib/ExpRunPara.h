// 【交接】 PCRCtrlLib\ExpRunPara.h
// 作用：ExpRunPara。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CExpRunPara、GetStartTime、SetStartTime、GetCurrentStageDelay、SetRunInfo、ExpRun、SetCurSegment、SetCurCycle。
#pragma once

#include "DeclaresPCR.h"
#include "ConfigureDBInfo.h"

// 实验运行过程中的参数，包括配置参数和过程参数
class AFX_EXT_CLASS CExpRunPara
{
public:
	// 函数 CExpRunPara
	// 作用：执行CExpRunPara。
	// 参数：无。
	// 返回：没有返回值。
	CExpRunPara(void);
	// 函数 ~CExpRunPara
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CExpRunPara(void);

// Operations
public:
	unsigned long long GetStartTime(eExpStageType nType);
	// 函数 SetStartTime
	// 作用：设置SetStartTime。
	// 参数：nType：整数；lTime。
	// 返回：没有返回值。
	void SetStartTime(eExpStageType nType, unsigned long long lTime);
	// 函数 GetCurrentStageDelay
	// 作用：读取GetCurrentStageDelay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCurSegment。
	int GetCurrentStageDelay();

	// 函数 SetRunInfo
	// 作用：设置SetRunInfo。
	// 参数：pRunInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSegment。
	void SetRunInfo(CDBRunInfo* pRunInfo);
	// 函数 ExpRun
	// 作用：执行ExpRun。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSegment。
	void ExpRun();
	// 函数 SetCurSegment
	// 作用：设置SetCurSegment。
	// 参数：iSegment：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSegment。
	void SetCurSegment(int iSegment);
	// 函数 SetCurCycle
	// 作用：设置SetCurCycle。
	// 参数：iCycle：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSegment。
	void SetCurCycle(int iCycle);
	// 函数 SetCurStep
	// 作用：设置SetCurStep。
	// 参数：iStep：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSegment。
	void SetCurStep(int iStep);
	// 函数 ExpStop
	// 作用：执行ExpStop。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSegment。
	void ExpStop(CDBRunInfo::eStopFlagType nType);
	// 函数 GetCurSegment
	// 作用：读取GetCurSegment。
	// 参数：m_pDBRunInfo->GetCurSegment(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCurSegment() { return m_pDBRunInfo->GetCurSegment(); }
	// 函数 GetCurCycle
	// 作用：读取GetCurCycle。
	// 参数：m_pDBRunInfo->GetCurCycle(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCurCycle() { return m_pDBRunInfo->GetCurCycle(); }
	// 函数 GetCurStep
	// 作用：读取GetCurStep。
	// 参数：m_pDBRunInfo->GetCurStep(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCurStep() { return m_pDBRunInfo->GetCurStep(); }

	// 函数 LockInstance
	// 作用：执行LockInstance。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetLidLowerTemp。
	void LockInstance();
	// 函数 UnlockInstance
	// 作用：执行UnlockInstance。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetLidLowerTemp。
	void UnlockInstance();

protected:

// Attributes
public:
	// 函数 GetLidLowerTemp
	// 作用：读取GetLidLowerTemp。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	float GetLidLowerTemp() { return m_fLidLowerTemp; }
	// 函数 SetLidLowerTemp
	// 作用：设置SetLidLowerTemp。
	// 参数：fTemp：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLidLowerTemp(float fTemp) { m_fLidLowerTemp = fTemp;}
	// 函数 GetPeltierLowerTemp
	// 作用：读取GetPeltierLowerTemp。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	float GetPeltierLowerTemp() { return m_fPeltierLowerTemp; }
	// 函数 SetPeltierLowerTemp
	// 作用：设置SetPeltierLowerTemp。
	// 参数：fTemp：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPeltierLowerTemp(float fTemp) { m_fPeltierLowerTemp = fTemp; }

	// 函数 GetLidGetTempDelay
	// 作用：读取GetLidGetTempDelay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetLidGetTempDelay() { return m_iLidGetTempDelay; }
 	void SetLidGetTempDelay(int iDelay) { m_iLidGetTempDelay = iDelay; }
	// 函数 GetAmplifyTempDelay
	// 作用：读取GetAmplifyTempDelay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetAmplifyTempDelay() { return m_iAmplifyTempDelay; }
	// 函数 SetAmplifyTempDelay
	// 作用：设置SetAmplifyTempDelay。
	// 参数：iDelay：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAmplifyTempDelay(int iDelay) { m_iAmplifyTempDelay = iDelay; }
	// 函数 GetMeltTempDelay
	// 作用：读取GetMeltTempDelay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetMeltTempDelay() { return m_iMeltTempDelay; }
	// 函数 SetMeltTempDelay
	// 作用：设置SetMeltTempDelay。
	// 参数：iDelay：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetMeltTempDelay(int iDelay) { m_iMeltTempDelay = iDelay; }
	// 函数 GetEndAutoCooling
	// 作用：读取GetEndAutoCooling。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetEndAutoCooling()  { return m_bEndAutoCoolling; }
	// 函数 SetEndAutoCooling
	// 作用：设置SetEndAutoCooling。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetEndAutoCooling(BOOL bEnable) { m_bEndAutoCoolling = bEnable; }

	// 函数 GetCurStage
	// 作用：读取GetCurStage。
	// 参数：无。
	// 返回：返回 eExpStageType。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eExpStageType GetCurStage() { return m_nStageType; }
	// 函数 SetCurStage
	// 作用：设置SetCurStage。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCurStage(eExpStageType nType) { m_nStageType = nType; }

	// 函数 GetCurTemp
	// 作用：读取GetCurTemp。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	float GetCurTemp() { return m_fCurTemp; }
	// 函数 SetCurTemp
	// 作用：设置SetCurTemp。
	// 参数：fTemp：小数；bReach：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCurTemp(float fTemp, BOOL bReach) { m_fCurTemp = fTemp; m_bCurReachTemp = bReach; }
	// 函数 GetCurReachTemp
	// 作用：读取GetCurReachTemp。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetCurReachTemp() { return m_bCurReachTemp; }
	// 函数 GetLidTemp
	// 作用：读取GetLidTemp。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	float GetLidTemp() { return m_fLidTemp; }
	// 函数 SetLidTemp
	// 作用：设置SetLidTemp。
	// 参数：fTemp：小数；bReach：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLidTemp(float fTemp, BOOL bReach) { m_fLidTemp = fTemp; m_bLidReachTemp = bReach; }
	// 函数 GetLidReachTemp
	// 作用：读取GetLidReachTemp。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetLidReachTemp() { return m_bLidReachTemp; }

	// 函数 SetScanGetDataMs
	// 作用：设置SetScanGetDataMs。
	// 参数：ckMs。
	// 返回：没有返回值。
	void SetScanGetDataMs(clock_t ckMs);
	// 函数 GetScanGetDataMs
	// 作用：读取GetScanGetDataMs。
	// 参数：无。
	// 返回：返回 clock_t。
	clock_t GetScanGetDataMs();
	// 函数 GetScanDataSecond
	// 作用：读取GetScanDataSecond。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetScanDataSecond();

	// 函数 SetMeltStepRunningState
	// 作用：设置SetMeltStepRunningState。
	// 参数：bMeltStepRunning：是或否。
	// 返回：没有返回值。
	void SetMeltStepRunningState(BOOL bMeltStepRunning);
	// 函数 IsMeltStepRunning
	// 作用：判断IsMeltStepRunning是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsMeltStepRunning();

	// 函数 SetCommunicationState
	// 作用：设置SetCommunicationState。
	// 参数：bValue：是或否。
	// 返回：没有返回值。
	void SetCommunicationState(BOOL bValue);
	// 函数 GetCommunicationState
	// 作用：读取GetCommunicationState。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetCommunicationState();

protected:
	CRITICAL_SECTION m_csUseInstance; 

	float		m_fLidLowerTemp; // 热盖最低温度
	float		m_fPeltierLowerTemp; // 帕尔贴最低保持温度

	// 控制参数
	int		m_iLidGetTempDelay; // 热盖加热过程中读取温度间隔，单位：毫秒
	int		m_iAmplifyTempDelay; // 扩增过程中读取温度间隔，单位：毫秒
	int		m_iMeltTempDelay; // 熔解过程中读取温度间隔，单位：毫秒
	BOOL	m_bEndAutoCoolling; // 实验结束是否自动降温

	// 过程参数
	eExpStageType	m_nStageType; // 当前实验段类型
	unsigned long long m_lTempStartTime; // 取温度数据开始时间
	unsigned long long m_lAmplifyStartTime; // 扩增段开始时间
	unsigned long long m_lMeltStartTime; // 熔解段开始时间
	unsigned long long m_lSegmentStartTime; // 每个程序段循环开始时间，方便计算整个实验所需时间，可以根据一个循环的时间计算全部循环时间

	CDBRunInfo* m_pDBRunInfo; // 数据库中需要保存的运行信息
	BOOL	m_bExpInterrupt; // 实验是否中断

	float	m_fCurTemp; // 取温度线程得到的最近温度值，表示整个PCR仪温度
	BOOL	m_bCurReachTemp; // 最近取温度时下位机返回，表示温度是否达到
	float	m_fLidTemp; // 热盖温度
	BOOL	m_bLidReachTemp; // 热盖温度是否到达目标值

	clock_t m_ckScanGetDataMs;	//记录扫描以及上传数据占用的时间，单位为毫秒

	BOOL m_bMeltStepRunning;	//判断是否正在运行熔曲步骤

private:
	BOOL m_bCommuNormal;	//标识通信状态是否正常，防止通信异常时，主线程处于延时等待过程中无法及时退出
	HANDLE m_hSyncCommuState;	//同步m_bCommuNormal访问
};

