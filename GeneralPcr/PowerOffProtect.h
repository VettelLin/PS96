// 【交接】 GeneralPcr\PowerOffProtect.h
// 作用：PowerOffProtect。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPowerOffProtect、InitPowerOffProtect、SetRunProgress、AddRunProgress、DeleteRunProgress、DeleteOldProgress、SearchPowerOffProtect、GetRunProgressRecord。
#pragma once

#include "LinkList.h"
#include "RunProgressRecord.h"
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

class CPowerOffProtect
{
public:
	// 函数 CPowerOffProtect
	// 作用：执行CPowerOffProtect。
	// 参数：无。
	// 返回：没有返回值。
	CPowerOffProtect(void);
	// 函数 ~CPowerOffProtect
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPowerOffProtect(void);

			// 函数 InitPowerOffProtect
			// 作用：初始化InitPowerOffProtect。
			// 参数：strPath：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InitPowerOffProtect(CString strPath);
			// 函数 SetRunProgress
			// 作用：设置SetRunProgress。
			// 参数：iPageId：整数；iSegId：整数；iStepId：整数；iCycleId：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRunProgress(int iPageId,int iSegId,int iStepId,int iCycleId);
			// 函数 SetRunProgress
			// 作用：设置SetRunProgress。
			// 参数：iPageId：整数；fMeltTem：小数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRunProgress(int iPageId,float fMeltTem);
			// 函数 AddRunProgress
			// 作用：创建或加入AddRunProgress。
			// 参数：runPrgRcd。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AddRunProgress(CRunProgressRecord& runPrgRcd);
			// 函数 DeleteRunProgress
			// 作用：更新或清除DeleteRunProgress。
			// 参数：iPageId：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteRunProgress(int iPageId);
			// 函数 DeleteOldProgress
			// 作用：更新或清除DeleteOldProgress。
			// 参数：iLnkIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteOldProgress(int iLnkIndex);

			// 函数 SearchPowerOffProtect
			// 作用：执行SearchPowerOffProtect。
			// 参数：strSN：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SearchPowerOffProtect(CString strSN);

			// 函数 GetRunProgressRecord
			// 作用：读取GetRunProgressRecord。
			// 参数：iIndex：整数；runPrjRcd。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRunProgressRecord(int iIndex,CRunProgressRecord& runPrjRcd);

private:
			// 函数 ReadFile
			// 作用：读取ReadFile。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadFile();
			// 函数 SaveFile
			// 作用：把SaveFile写入文件、仪器或界面。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SaveFile();

			// 函数 WriteString
			// 作用：把WriteString写入文件、仪器或界面。
			// 参数：strText：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int WriteString(CString& strText);
			// 函数 ReadString
			// 作用：读取ReadString。
			// 参数：ifs；strText：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadString(ifstream& ifs,CString& strText);

public:
	CLinkList<CRunProgressRecord> m_lnkRunPrgRcd;
	ofstream m_fs;

private:
	HANDLE m_hSyncLnk;	//同步m_lnkRunPrgRcd访问
	BOOL m_bProtectWork;	//标识断电保护功能是否可用

	CString m_strFileDir;	//未完成实验记录文件所在的文件夹
	CString m_strFileName;	//未完成实验记录文件的文件名（包含后缀名）
	CString m_strFilePath;	//未完成实验记录文件的完整路径名

	int m_iFileTag;	//文件标识
};

