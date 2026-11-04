// 【交接】 GeneralPcr\ExpRunCtrl.h
// 作用：实验运行控制类声明。保存当前段、步、循环，以及停止、重连、读荧光的接口。
// 先看这些函数：CExpRunCtrl、Run、RunProc、GetCurCycle、GetCurSegment、GetCurStep、SetPowerOffExpInfo、ResetPowerOffExpInfo。
#pragma once

#include "InstancePCR.h"
#include "ExperimentData.h"
#include "ExpRunPara.h"
#include "ExpTempDataThread.h"
#include "ExpDeviceStatusThread.h"
#include "LanguageInfo.h"

// 实验过程控制线程
class CExpRunCtrl
{
public:
	// 函数 CExpRunCtrl
	// 作用：执行CExpRunCtrl。
	// 参数：pInstance：指针，指向调用方传入的对象；pMsgWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurCycle。
	CExpRunCtrl(CInstancePCR* pInstance, CWnd* pMsgWnd);
	// 函数 ~CExpRunCtrl
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurCycle。
	~CExpRunCtrl(void);

// Operations
public:
	// 函数 Run
	// 作用：执行Run。
	// 参数：pExpData：指针，指向调用方传入的对象；pRunPara：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetCurCycle。
	BOOL Run(CExperimentData* pExpData, CExpRunPara* pRunPara);
	// 函数 RunProc
	// 作用：执行RunProc。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurCycle。
	void RunProc();

	// 函数 GetCurCycle
	// 作用：读取GetCurCycle。
	// 参数：m_pRunPara->GetCurCycle(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCurCycle(){return m_pRunPara->GetCurCycle();}
	// 函数 GetCurSegment
	// 作用：读取GetCurSegment。
	// 参数：m_pRunPara->GetCurSegment(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCurSegment(){return m_pRunPara->GetCurSegment();}
	// 函数 GetCurStep
	// 作用：读取GetCurStep。
	// 参数：m_pRunPara->GetCurStep(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCurStep(){return m_pRunPara->GetCurStep();}

	// 函数 SetPowerOffExpInfo
	// 作用：设置SetPowerOffExpInfo。
	// 参数：bPowerOffExp：是或否；iStartSeg：整数；iStartStep：整数；iStartCyle：整数。
	// 返回：没有返回值。
	void SetPowerOffExpInfo(BOOL bPowerOffExp,int iStartSeg,int iStartStep,int iStartCyle);
	// 函数 ResetPowerOffExpInfo
	// 作用：更新或清除ResetPowerOffExpInfo。
	// 参数：无。
	// 返回：没有返回值。
	void ResetPowerOffExpInfo();

protected:
	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL Initialize();
	// 函数 AfterRunning
	// 作用：执行AfterRunning。
	// 参数：无。
	// 返回：没有返回值。
	virtual void AfterRunning();
	// 函数 PrepareRunning
	// 作用：执行PrepareRunning。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL PrepareRunning();
	// 函数 RefreshStatus
	// 作用：更新或清除RefreshStatus。
	// 参数：无。
	// 返回：没有返回值。
	virtual void RefreshStatus();
	// 函数 RunLidHeader
	// 作用：执行RunLidHeader。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL RunLidHeader();
	// 函数 SetLaserStatus
	// 作用：设置SetLaserStatus。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL SetLaserStatus();
	// 函数 ChannelSignalCorrection
	// 作用：执行ChannelSignalCorrection。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ChannelSignalCorrection();
	// 函数 HandleDeviceStatus
	// 作用：执行HandleDeviceStatus。
	// 参数：无。
	// 返回：没有返回值。
	virtual void HandleDeviceStatus();

	// 函数 CreateAndSendCycle
	// 作用：创建或加入CreateAndSendCycle。
	// 参数：lStartTime；lEndTime；iCycleCount：整数。
	// 返回：没有返回值。
	void CreateAndSendCycle(long lStartTime, long lEndTime, int iCycleCount);
	// 函数 RunNoneStep
	// 作用：执行RunNoneStep。
	// 参数：pStep：指针，指向调用方传入的对象；fPreTemp：小数。
	// 返回：返回是或否。
	BOOL RunNoneStep(CStepItemInfo* pStep, float fPreTemp);
	// 函数 RunMeltStep
	// 作用：执行RunMeltStep。
	// 参数：pStep：指针，指向调用方传入的对象；fPreTemp：小数；iPreDelay：整数。
	// 返回：返回是或否。
	BOOL RunMeltStep(CStepItemInfo* pStep,float fPreTemp,int iPreDelay);
	// 函数 RunAmplifyStep
	// 作用：执行RunAmplifyStep。
	// 参数：iCycleC：整数；pStep：指针，指向调用方传入的对象；fPreTemp：小数。
	// 返回：返回是或否。
	BOOL RunAmplifyStep(int iCycleC, CStepItemInfo* pStep, float fPreTemp);
	// 函数 ReadScanDataOnce
	// 作用：读取ReadScanDataOnce。
	// 参数：eScanDataType。
	// 返回：返回是或否。
	BOOL ReadScanDataOnce(ESCANDATATYPE eScanDataType);

	// 函数 SetMultiTemp
	// 作用：设置SetMultiTemp。
	// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数；fRate：小数；cMode。
	// 返回：返回是或否。
	BOOL SetMultiTemp(float fTemp1, float fTemp2, float fTemp3, float fRate, BYTE cMode);
	// 函数 CompareTempAndWriteLog
	// 作用：执行CompareTempAndWriteLog。
	// 参数：iCycle：整数；pStep：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void CompareTempAndWriteLog(int iCycle, CStepItemInfo* pStep);
	// 函数 AddInterruptLog
	// 作用：创建或加入AddInterruptLog。
	// 参数：iSegNo：整数；iStepNo：整数；iCycleNo：整数。
	// 返回：没有返回值。
	void AddInterruptLog(int iSegNo, int iStepNo, int iCycleNo);

	// 函数 ReconnectDeviceToRun
	// 作用：执行ReconnectDeviceToRun。
	// 参数：无。
	// 返回：返回是或否。
	BOOL ReconnectDeviceToRun();
	// 函数 CalculateCurrentCycle
	// 作用：计算CalculateCurrentCycle。
	// 参数：iCycle：整数；pSegment：指针，指向调用方传入的对象；iDelaySecond：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalculateCurrentCycle(int iCycle, CSegItemInfo* pSegment, int iDelaySecond);

private:
	// 函数 RunStepDelay
	// 作用：执行RunStepDelay。
	// 参数：iWaitSecond：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetInstancePCR。
	void RunStepDelay(int iWaitSecond);
	// 函数 RunWaitReachTemp
	// 作用：执行RunWaitReachTemp。
	// 参数：pStep：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetInstancePCR。
	int RunWaitReachTemp(CStepItemInfo* pStep);
	// 函数 RunWaitReachTemp
	// 作用：执行RunWaitReachTemp。
	// 参数：fAimTem：小数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetInstancePCR。
	int RunWaitReachTemp(float fAimTem);
	// 函数 CoolAtEnd
	// 作用：执行CoolAtEnd。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetInstancePCR。
	BOOL CoolAtEnd();	//实验结束后，自动进行冷却降温

// Attributes
public:
	// 函数 SetInstancePCR
	// 作用：设置SetInstancePCR。
	// 参数：pInstance：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetInstancePCR(CInstancePCR* pInstance) { m_pInstancePCR = pInstance; }
	// 函数 GetInstancePCR
	// 作用：读取GetInstancePCR。
	// 参数：无。
	// 返回：返回指针 CInstancePCR*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CInstancePCR* GetInstancePCR() {return m_pInstancePCR;}
	// 函数 AskStop
	// 作用：执行AskStop。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void AskStop() { m_bAskStop = TRUE; }
	// 函数 SetLanguage
	// 作用：设置SetLanguage。
	// 参数：pInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLanguage(CLanguageInfo* pInfo) { m_pLanguage = pInfo; }
	// 函数 GetRunLog
	// 作用：读取GetRunLog。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetRunLog();

protected:
	CInstancePCR*	m_pInstancePCR; // PCR实例

	CExperimentData* m_pExpData; // 实验数据
	CExpRunPara*	m_pRunPara; // 运行参数

	CWnd*		m_pMsgWnd; // 接受消息窗口
	CWinThread* m_pRunThread; // 运行主线程指针
	CExpTempDataThread* m_pTempThread; // 读取温度线程指针
	CExpDeviceStatusThread* m_pStatusThread; // 设备状态监控线程

	eExpRunStatus	m_nRunStatus; // 运行状态
	BOOL			m_bAskStop; // 要求结束
	CString			m_strErrorInfo; // 错误信息描述，保存到日志中
	long			m_lScanStartTime; // 开始扫描时的时刻，恒温PCR使用

	int				m_iNotReachTempCount; // 控温没有达到次数，超过规定控温时间（如60秒）
	BOOL			m_bNotReachMeltStartTemp; // 没有达到熔解段开始温度
	BOOL	m_bFirstAmplifyCycle; // 扩增循环第1个循环

	double m_dMeltTemBeforeScan;	//保存熔曲数据扫描前的温度
	double m_dMeltTemAfterScan;	//保存熔曲数据扫描前的温度

	BOOL m_bPowerOffExp;	//标识是否是断电保护后重新运行的实验
	int m_iStartSeg;	//断电保护实验 断电时运行的程序段ID
	int m_iStartStep;	//断电保护实验 断电时运行的步骤ID
	int m_iStartCyle;	//断电保护实验 断电时运行的循环数ID

	CStringArray m_arrayInfo; 
	BOOL	m_bNewSegmentCycle; // 是否是新的程序段开始，方便恒温仪控温使用
	BOOL	m_bFirstTempErr;
	CLanguageInfo* m_pLanguage;

private:
	BOOL m_bNoStepBeforeMeltStep;	//运行断电保护流程时，如果熔曲步骤是该程序段的第一个步骤，则 运行该步骤前需要稳定初始温度
	float m_fMeltStepStartTem;	//记录熔曲步骤运行前的初始温度（运行断电保护流程时使用）
};

