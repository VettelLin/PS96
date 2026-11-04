// 【交接】 PCRInstanceLib\LogFile.h
// 作用：LogFile。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CLogFile、CreateLogPath、CreateLogFile、WriteString、GetCurrentDate、GetCurrentTime、CLogRunFile、WriteLog。
#pragma once

#include "LogDataInfo.h"

class CLogFile
{
public:
	// 函数 CLogFile
	// 作用：执行CLogFile。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	CLogFile(CString strStartupPath);
	// 函数 ~CLogFile
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLogFile(void);

protected:
	// 函数 CreateLogPath
	// 作用：创建或加入CreateLogPath。
	// 参数：strFilePath：字符串。
	// 返回：返回是或否。
	BOOL CreateLogPath(CString strFilePath);
	// 函数 CreateLogFile
	// 作用：创建或加入CreateLogFile。
	// 参数：无。
	// 返回：返回是或否。
	BOOL CreateLogFile();
	// 函数 WriteString
	// 作用：把WriteString写入文件、仪器或界面。
	// 参数：strLog：字符串。
	// 返回：返回是或否。
	BOOL WriteString(CString strLog);
	// 函数 GetCurrentDate
	// 作用：读取GetCurrentDate。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetCurrentDate();
	// 函数 GetCurrentTime
	// 作用：读取GetCurrentTime。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetCurrentTime();

protected:
	CRITICAL_SECTION m_CriticalSection;

	CString m_strFilePath;
	CString m_strFileName;
	CString m_strSpace;
};

class CLogRunFile : public CLogFile
{
public:
	// 函数 CLogRunFile
	// 作用：执行CLogRunFile。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CLogRunFile(CString strStartupPath);
	// 函数 ~CLogRunFile
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLogRunFile(void) {}

public:
	// 函数 WriteLog
	// 作用：把WriteLog写入文件、仪器或界面。
	// 参数：pLogInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 CLogErrorFile、ResetFilePathName。
	void WriteLog(CLogRunInfo* pLogInfo);
	// 函数 ResetFilePathName
	// 作用：更新或清除ResetFilePathName。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 CLogErrorFile、WriteLog。
	void ResetFilePathName(CString strStartupPath);
};

class CLogErrorFile : public CLogFile
{
public:
	// 函数 CLogErrorFile
	// 作用：执行CLogErrorFile。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CLogErrorFile(CString strStartupPath);
	// 函数 ~CLogErrorFile
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLogErrorFile(void) {}

public:
	// 函数 WriteLog
	// 作用：把WriteLog写入文件、仪器或界面。
	// 参数：pLogInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 CLogCommFile、ResetFilePathName。
	void WriteLog(CLogErrorInfo* pLogInfo);
	// 函数 WriteLog
	// 作用：把WriteLog写入文件、仪器或界面。
	// 参数：strError：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 CLogCommFile、ResetFilePathName。
	void WriteLog(CString strError);
	// 函数 ResetFilePathName
	// 作用：更新或清除ResetFilePathName。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 CLogCommFile、WriteLog。
	void ResetFilePathName(CString strStartupPath);
};

class CLogCommFile : public CLogFile
{
public:
	// 函数 CLogCommFile
	// 作用：执行CLogCommFile。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CLogCommFile(CString strStartupPath);
	// 函数 ~CLogCommFile
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLogCommFile(void) {}

public:
	// 函数 WriteLog
	// 作用：把WriteLog写入文件、仪器或界面。
	// 参数：pLogInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void WriteLog(CLogCommInfo* pLogInfo);
	// 函数 WriteLog
	// 作用：把WriteLog写入文件、仪器或界面。
	// 参数：string：字符串。
	// 返回：没有返回值。
	void WriteLog(CString string);
	// 函数 ResetFilePathName
	// 作用：更新或清除ResetFilePathName。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	void ResetFilePathName(CString strStartupPath);
};
