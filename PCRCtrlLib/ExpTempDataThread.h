// 【交接】 PCRCtrlLib\ExpTempDataThread.h
// 作用：ExpTempDataThread 后台线程。实验运行时在界面之外轮询状态，避免卡住窗口。
// 先看这些函数：DECLARE_DYNCREATE、CExpTempDataThread、InitInstance、ExitInstance、Run、InitParameter、SetInstance、SetExperimentData。
#pragma once

#include "InstancePCR.h"
#include "ExperimentData.h"
#include "ExpRunPara.h"


// PCR实验中读取温度数据线程
class AFX_EXT_CLASS CExpTempDataThread : public CWinThread
{
	// 函数 DECLARE_DYNCREATE
	// 作用：执行DECLARE_DYNCREATE。
	// 参数：CExpTempDataThread。
	// 返回：没有返回值。
	DECLARE_DYNCREATE(CExpTempDataThread)

public:
	// 函数 CExpTempDataThread
	// 作用：执行CExpTempDataThread。
	// 参数：无。
	// 返回：没有返回值。
	CExpTempDataThread();
	// 函数 ~CExpTempDataThread
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CExpTempDataThread(void);

// Operations
public:
	// 函数 InitInstance
	// 作用：初始化InitInstance。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL InitInstance();
	// 函数 ExitInstance
	// 作用：执行ExitInstance。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetInstance。
	virtual int ExitInstance();
	// 函数 Run
	// 作用：执行Run。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetInstance。
	virtual int Run();

protected:
	// 函数 InitParameter
	// 作用：初始化InitParameter。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetInstance。
	void InitParameter();

// Attributes
public:
	// 函数 SetInstance
	// 作用：设置SetInstance。
	// 参数：pInstance：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetInstance(CInstancePCR* pInstance) { m_pInstance = pInstance; }
	// 函数 SetExperimentData
	// 作用：设置SetExperimentData。
	// 参数：pExpData：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetExperimentData(CExperimentData* pExpData) { m_pExpData = pExpData; }
	// 函数 SetExpRunPara
	// 作用：设置SetExpRunPara。
	// 参数：pRunPara：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetExpRunPara(CExpRunPara* pRunPara) { m_pRunPara = pRunPara; }
	// 函数 SetMsgWnd
	// 作用：设置SetMsgWnd。
	// 参数：pWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetMsgWnd(CWnd* pWnd) { m_pMsgWnd = pWnd; }
	// 函数 SetAskStop
	// 作用：设置SetAskStop。
	// 参数：bStop：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAskStop(BOOL bStop) { m_bAskStop = bStop; }
	// 函数 SetRunStatus
	// 作用：设置SetRunStatus。
	// 参数：nStatus：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRunStatus(eExpRunStatus nStatus) { m_nRunStatus = nStatus; }

	// 函数 SetStartTime
	// 作用：设置SetStartTime。
	// 参数：dwStartTime。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetStartTime(DWORD dwStartTime) { m_dwStartTime = dwStartTime; }

protected:
	CInstancePCR* m_pInstance;
	
	CExperimentData* m_pExpData;// 保存数据对象指针
	CExpRunPara*	m_pRunPara; // 运行状态参数
	CWnd*	m_pMsgWnd; // 接受消息窗口
	
	eExpRunStatus	m_nRunStatus;
	BOOL			m_bAskStop; // 外部中止
	int				m_nDelay; // 每次取温度间隔，毫秒
	int				m_nTempChannelCount; // 加热模块温度通道数，不包括热盖个数
	BOOL			m_bUseLidHeater; // 使用热盖

	DWORD	m_dwStartTime;
};

