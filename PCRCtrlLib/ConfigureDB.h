// 【交接】 PCRCtrlLib\ConfigureDB.h
// 作用：ConfigureDB。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CConfigureDB、GetInstance、DestroyInstance、Open、FindUserRecord、SearchUser、InsertUserRecord、UpdateUserRecord。
#pragma once

#include "ConfigureDBInfo.h"
#include <afxdao.h>
#pragma warning(disable: 4995 311 244)

class AFX_EXT_CLASS CConfigureDB
{
public:
	// 函数 CConfigureDB
	// 作用：执行CConfigureDB。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CConfigureDB(void);
	// 函数 ~CConfigureDB
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CConfigureDB(void);

	enum eTableUserField
	{
		USER_INDEX = 0,
		USER_NAME,
		USER_PASSWORD,
		USER_ROLE_TYPE,
		USER_STATUS,
		USER_MNEMONIC,
		USER_CREATETM
	};

	enum eTableDyeField
	{
		DYE_INDEX = 0,
		DYE_NAME,
		DYE_EXWAVELENGTH,
		DYE_EXCHANNEL,
		DYE_EMWAVELENGTH,
		DYE_EMCHANNEL,
		DYE_TARGET,
		DYE_QUENCHER,
		DYE_COLOR,
		DYE_DEFAULT,
		DYE_INSTRUMENT,
		DYE_USERNAME,
	};

	enum eTableRunField
	{
		RUN_INDEX = 0,
		RUN_INSTRUMENT,
		RUN_FILENAME,
		RUN_USERNAME,
		RUN_BEGIN_DATE,
		RUN_END_DATE,
		RUN_STOP_FLAG,
		RUN_CUR_SEGMENT,
		RUN_CUR_CYCLE,
		RUN_CUR_STEP,
	};

// Operations
public:
	// 函数 GetInstance
	// 作用：读取GetInstance。
	// 参数：无。
	// 返回：返回指针 CConfigureDB*。指针为空表示没有取到对象。
	static CConfigureDB* GetInstance();
	// 函数 DestroyInstance
	// 作用：执行DestroyInstance。
	// 参数：无。
	// 返回：没有返回值。
	static void DestroyInstance();
	// 函数 Open
	// 作用：读入Open。
	// 参数：strPath：字符串。
	// 返回：返回是或否。
	BOOL Open(CString strPath);

	// 操作用户表
	// 函数 FindUserRecord
	// 作用：执行FindUserRecord。
	// 参数：strName：字符串。
	// 返回：返回是或否。
	BOOL FindUserRecord(CString strName);
	// 函数 SearchUser
	// 作用：执行SearchUser。
	// 参数：pList：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL SearchUser(CUserInfoList* pList);
	// 函数 SearchUser
	// 作用：执行SearchUser。
	// 参数：strName：字符串；userInfo。
	// 返回：返回是或否。
	BOOL SearchUser(CString strName,CDBUserInfo& userInfo);
	// 函数 InsertUserRecord
	// 作用：创建或加入InsertUserRecord。
	// 参数：pUser：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL InsertUserRecord(CDBUserInfo* pUser);
	// 函数 UpdateUserRecord
	// 作用：更新或清除UpdateUserRecord。
	// 参数：pUser：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL UpdateUserRecord(CDBUserInfo* pUser);
	// 函数 DeleteUserRecord
	// 作用：更新或清除DeleteUserRecord。
	// 参数：pUser：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL DeleteUserRecord(CDBUserInfo* pUser);

	// 操作染料表
	// 函数 FindDyeRecord
	// 作用：执行FindDyeRecord。
	// 参数：nIndex：整数。
	// 返回：返回是或否。
	BOOL FindDyeRecord(int nIndex);
	// 函数 SearchDye
	// 作用：执行SearchDye。
	// 参数：pList：指针，指向调用方传入的对象；strUser：字符串；strInstrument：字符串。
	// 返回：返回是或否。
	BOOL SearchDye(CDyeInfoList* pList, CString strUser, CString strInstrument=_T(""));
	// 函数 InsertDyeRecord
	// 作用：创建或加入InsertDyeRecord。
	// 参数：pDye：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL InsertDyeRecord(CDBDyeInfo* pDye);
	// 函数 UpdateDyeRecord
	// 作用：更新或清除UpdateDyeRecord。
	// 参数：pDye：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL UpdateDyeRecord(CDBDyeInfo* pDye);
	// 函数 DeleteDyeRecord
	// 作用：更新或清除DeleteDyeRecord。
	// 参数：pDye：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL DeleteDyeRecord(CDBDyeInfo* pDye);

	// 操作运行信息表
	// 函数 FindRunRecord
	// 作用：执行FindRunRecord。
	// 参数：nIndex：整数。
	// 返回：返回是或否。
	BOOL FindRunRecord(int nIndex);
	// 函数 SearchRun
	// 作用：执行SearchRun。
	// 参数：pList：指针，指向调用方传入的对象；strUser：字符串；strInstrument：字符串；iStopFlag：整数。
	// 返回：返回是或否。
	BOOL SearchRun(CRunInfoList* pList, CString strUser, CString strInstrument, int iStopFlag=-1);
	// 函数 InsertRunRecord
	// 作用：创建或加入InsertRunRecord。
	// 参数：pRunInfo：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL InsertRunRecord(CDBRunInfo* pRunInfo);
	// 函数 UpdateRunRecord
	// 作用：更新或清除UpdateRunRecord。
	// 参数：pRunInfo：指针，指向调用方传入的对象；bStop：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetDatabase。
	BOOL UpdateRunRecord(CDBRunInfo* pRunInfo, BOOL bStop=TRUE);
	// 函数 DeleteRunRecord
	// 作用：更新或清除DeleteRunRecord。
	// 参数：pRunInfo：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetDatabase。
	BOOL DeleteRunRecord(CDBRunInfo* pRunInfo);

protected:
	// 函数 Close
	// 作用：执行Close。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetDatabase。
	void Close();

// Attributes
public:
	// 函数 GetDatabase
	// 作用：读取GetDatabase。
	// 参数：无。
	// 返回：返回指针 CDaoDatabase*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CDaoDatabase* GetDatabase(){return m_pDaoDB;}
	// 函数 IsOpen
	// 作用：判断IsOpen是否成立。
	// 参数：m_pDaoDB->IsOpen(。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL IsOpen(){return m_pDaoDB->IsOpen();}

protected:
	static CConfigureDB* m_pInstance;
	CDaoDatabase* m_pDaoDB;
	CString m_strFileName;
	CRITICAL_SECTION m_csUseDB;

	// 用户信息表
	CString m_strUserTableName;
	CStringArray m_arrayUserTableField;

	// 染料信息表，包括所在通道、目标等
	CString m_strDyeTableName;
	CStringArray m_arrayDyeTableField;

	// 运行信息表
	CString m_strRunTableName;
	CStringArray m_arrayRunTableField;
};

