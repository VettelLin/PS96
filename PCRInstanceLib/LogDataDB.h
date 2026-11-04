// 【交接】 PCRInstanceLib\LogDataDB.h
// 作用：LogDataDB。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CLogDataDB、SetDBPath、Open、InsertRunRecord、SearchRunLog、InsertErrorRecord、SearchErrorLog、FindErrorLogMaxIndex。
#pragma once

#include "LogDataInfo.h"
#include <afxdao.h>
#pragma warning(disable: 4995 311 244)

class AFX_EXT_CLASS CLogDataDB
{
public:
	// 函数 CLogDataDB
	// 作用：执行CLogDataDB。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CLogDataDB(void);
	// 函数 ~CLogDataDB
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CLogDataDB(void);
	enum eTableRunrField
	{
		RUN_INDEX = 0,
		RUN_DATE,
		RUN_CONTENT,
		RUN_USER,
		RUN_INSTRUMENT,
		RUN_LOG_TYPE,
		RUN_ERR_INDEX,
		RUN_STATUS,
	};

	enum eTableErrorField
	{
		ERROR_INDEX = 0,
		ERROR_DATE,
		ERROR_CONTENT,
		ERROR_PARA1,
		ERROR_PARA2,
		ERROR_USER,
		ERROR_INSTRUMENT,
		ERROR_LOG_TYPE,
	};

	enum eTableCommField
	{
		COMM_INDEX = 0,
		COMM_LOG_DATE,
		COMM_INSTRUMENT,
		COMM_COMMENT,
		COMM_TYPE,
		COMM_RESULT,
		COMM_SEND_COUNT,
		COMM_CONTENT,
	};

// Operations
public:
	// 函数 SetDBPath
	// 作用：设置SetDBPath。
	// 参数：strPath：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetDBPath(CString strPath) { m_strFileName = strPath + m_strFileName; }
	// 函数 Open
	// 作用：读入Open。
	// 参数：无。
	// 返回：返回是或否。
	BOOL Open();

	// 函数 InsertRunRecord
	// 作用：创建或加入InsertRunRecord。
	// 参数：pLog：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL InsertRunRecord(CLogRunInfo* pLog);
	// 函数 SearchRunLog
	// 作用：执行SearchRunLog。
	// 参数：pList：指针，指向调用方传入的对象；strUser：字符串；strInstrument：字符串；strDateBegin：字符串；strDateEnd：字符串。
	// 返回：返回是或否。
	BOOL SearchRunLog(CLogRunInfoList* pList, CString strUser, CString strInstrument, CString strDateBegin, CString strDateEnd);

	// 函数 InsertErrorRecord
	// 作用：创建或加入InsertErrorRecord。
	// 参数：pLog：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL InsertErrorRecord(CLogErrorInfo* pLog);
	// 函数 SearchErrorLog
	// 作用：执行SearchErrorLog。
	// 参数：pList：指针，指向调用方传入的对象；strUser：字符串；strInstrument：字符串；strDateBegin：字符串；strDateEnd：字符串。
	// 返回：返回是或否。
	BOOL SearchErrorLog(CLogErrorInfoList* pList, CString strUser, CString strInstrument, CString strDateBegin, CString strDateEnd);
	// 函数 SearchErrorLog
	// 作用：执行SearchErrorLog。
	// 参数：pList：指针，指向调用方传入的对象；strErrIndex：字符串。
	// 返回：返回是或否。
	BOOL SearchErrorLog(CLogErrorInfoList* pList, CString strErrIndex);
	// 函数 FindErrorLogMaxIndex
	// 作用：执行FindErrorLogMaxIndex。
	// 参数：无。
	// 返回：返回 long。
	long FindErrorLogMaxIndex();

	// 函数 InsertCommRecord
	// 作用：创建或加入InsertCommRecord。
	// 参数：pLog：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL InsertCommRecord(CLogCommInfo* pLog);
	// 函数 SearchCommLog
	// 作用：执行SearchCommLog。
	// 参数：pList：指针，指向调用方传入的对象；strInstrument：字符串。
	// 返回：返回是或否。
	BOOL SearchCommLog(CLogCommInfoList* pList, CString strInstrument);

protected:
	// 函数 SearchErrorLogBySQL
	// 作用：执行SearchErrorLogBySQL。
	// 参数：strSQL：字符串；pList：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL SearchErrorLogBySQL(CString strSQL, CLogErrorInfoList* pList);

// Attributes
protected:
	CDaoDatabase* m_pDaoDB;
	CString m_strFileName;

	// 运行日志信息表
	CString m_strRunTableName;
	CStringArray m_arrayRunTableField;

	// 错误日志信息表
	CString m_strErrorTableName;
	CStringArray m_arrayErrorTableField;

	// 通讯日志信息表
	CString m_strCommTableName;
	CStringArray m_arrayCommTableField;
};

