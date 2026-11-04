// 【交接】 PCRInstanceLib\LogManager.h
// 作用：LogManager。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CLogManager、GetInstance、DestroyInstance、Initialize、ResetLogFileName、WriteRunLog、WriteErrorLog、WriteCommLog。
#pragma once

#include "LogDataDB.h"
#include "DeclaresPCR.h"
#include "LogFile.h"

class AFX_EXT_CLASS CLogManager
{
private:
	// 函数 CLogManager
	// 作用：执行CLogManager。
	// 参数：无。
	// 返回：没有返回值。
	CLogManager(void);
	// 函数 ~CLogManager
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CLogManager(void);

public:
	// 函数 GetInstance
	// 作用：读取GetInstance。
	// 参数：无。
	// 返回：返回指针 CLogManager*。指针为空表示没有取到对象。
	static CLogManager* GetInstance();
	// 函数 DestroyInstance
	// 作用：执行DestroyInstance。
	// 参数：无。
	// 返回：没有返回值。
	static void DestroyInstance();
	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：strStartupPath：字符串。
	// 返回：返回是或否。
	BOOL Initialize(CString strStartupPath);
	// 函数 ResetLogFileName
	// 作用：更新或清除ResetLogFileName。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	void ResetLogFileName(CString strStartupPath);

	// 函数 WriteRunLog
	// 作用：把WriteRunLog写入文件、仪器或界面。
	// 参数：pLogRun：指针，指向调用方传入的对象；nUseErrIndex：整数。
	// 返回：返回是或否。
	BOOL WriteRunLog(CLogRunInfo* pLogRun, int nUseErrIndex=0);
	// 函数 WriteErrorLog
	// 作用：把WriteErrorLog写入文件、仪器或界面。
	// 参数：pLogError：指针，指向调用方传入的对象；bRecordIndex：是或否。
	// 返回：返回是或否。
	BOOL WriteErrorLog(CLogErrorInfo* pLogError, BOOL bRecordIndex=FALSE);
	// 函数 WriteErrorLog
	// 作用：把WriteErrorLog写入文件、仪器或界面。
	// 参数：strError：字符串。
	// 返回：返回是或否。
	BOOL WriteErrorLog(CString strError);
	// 函数 WriteCommLog
	// 作用：把WriteCommLog写入文件、仪器或界面。
	// 参数：pLogComm：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteCommLog(CLogCommInfo* pLogComm);
	// 函数 WriteCommLog
	// 作用：把WriteCommLog写入文件、仪器或界面。
	// 参数：string：字符串。
	// 返回：返回是或否。
	BOOL WriteCommLog(CString string);

protected:
	// 函数 FindInstruemntIndexOfArray
	// 作用：执行FindInstruemntIndexOfArray。
	// 参数：strInstrument：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int FindInstruemntIndexOfArray(CString strInstrument);

private:
	static CLogManager* m_pInstance;

	int	m_iSaveMode; // 保存模式，0：保存到文本文件 1：保存到数据库
	CLogDataDB*		m_pLogDB;

	CLogRunFile*	m_pLogRunFile; // 运行文件日志
	CLogErrorFile*	m_pLogErrorFile; // 错误文件日志
	CLogCommFile*	m_pLogCommFile; // 通讯文件日志

	CRITICAL_SECTION m_csUseDB;

	CStringArray	m_arrayInstrument; // 仪器序号
	CLongArray		m_arrayErrorIndex; // 错误日志序号，有则在运行日志中发出错误提示，外部反馈提示
	CPtrArray		m_arrayWarmIndex; // 记录通讯警告日志序号，如果超过5次则在运行日志中发出警告
};

