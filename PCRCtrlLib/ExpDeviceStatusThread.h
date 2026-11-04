// 【交接】 PCRCtrlLib\ExpDeviceStatusThread.h
// 作用：ExpDeviceStatusThread 后台线程。实验运行时在界面之外轮询状态，避免卡住窗口。
// 先看这些函数：DECLARE_DYNCREATE、CExpDeviceStatusThread、InitInstance、ExitInstance、Run、InitParameter、SetInstance、SetAskStop。
#pragma once

#include "InstancePCR.h"
#include "ExpRunPara.h"

class AFX_EXT_CLASS CExpDeviceStatusThread :	public CWinThread
{
	// 函数 DECLARE_DYNCREATE
	// 作用：执行DECLARE_DYNCREATE。
	// 参数：CExpDeviceStatusThread。
	// 返回：没有返回值。
	DECLARE_DYNCREATE(CExpDeviceStatusThread)

public:
	// 函数 CExpDeviceStatusThread
	// 作用：执行CExpDeviceStatusThread。
	// 参数：无。
	// 返回：没有返回值。
	CExpDeviceStatusThread();
	// 函数 ~CExpDeviceStatusThread
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CExpDeviceStatusThread(void);

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
	// 函数 SetAskStop
	// 作用：设置SetAskStop。
	// 参数：bStop：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAskStop(BOOL bStop) { m_bAskStop = bStop; }
	// 函数 SetExpRunPara
	// 作用：设置SetExpRunPara。
	// 参数：pRunPara：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetExpRunPara(CExpRunPara* pRunPara) { m_pRunPara = pRunPara; }
	// 函数 SetRunStatus
	// 作用：设置SetRunStatus。
	// 参数：nStatus：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRunStatus(eExpRunStatus nStatus) { m_nRunStatus = nStatus; }

protected:
	CInstancePCR* m_pInstance;
	CExpRunPara* m_pRunPara; // 运行状态参数
	eExpRunStatus m_nRunStatus;

	BOOL m_bAskStop; // 外部中止
	int m_nDelay; // 每次取温度间隔，毫秒
};

