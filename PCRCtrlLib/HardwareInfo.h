// 【交接】 PCRCtrlLib\HardwareInfo.h
// 作用：HardwareInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CHardwareInfo、WriteFile、ReadFile、WriteScanChannelInfoToFile、ReadScanChannelInfoFromFile、ResetHardwareInfo、GetBeEmptyHardware。
#pragma once

#include "LinkList.h"
#include "DeclaresPCR.h"

class AFX_EXT_CLASS CHardwareInfo
{
public:
	// 函数 CHardwareInfo
	// 作用：执行CHardwareInfo。
	// 参数：无。
	// 返回：没有返回值。
	CHardwareInfo(void);
	// 函数 ~CHardwareInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CHardwareInfo(void);

	// 函数 CHardwareInfo
	// 作用：执行CHardwareInfo。
	// 参数：info。
	// 返回：没有返回值。
	CHardwareInfo(const CHardwareInfo& info);
	void operator=(const CHardwareInfo& info);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；bTemplate：是或否。
	// 返回：返回是或否。
	BOOL WriteFile(CFile* pFile,BOOL bTemplate);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL ReadFile(CFile* pFile,WORD wVersion);

	// 函数 WriteScanChannelInfoToFile
	// 作用：把WriteScanChannelInfoToFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；bTemplate：是或否。
	// 返回：返回是或否。
	BOOL WriteScanChannelInfoToFile(CFile* pFile,BOOL bTemplate);
	// 函数 ReadScanChannelInfoFromFile
	// 作用：读取ReadScanChannelInfoFromFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bTemplate：是或否。
	// 返回：返回是或否。
	BOOL ReadScanChannelInfoFromFile(CFile* pFile,WORD wVersion,BOOL bTemplate);

	// 函数 ResetHardwareInfo
	// 作用：更新或清除ResetHardwareInfo。
	// 参数：无。
	// 返回：没有返回值。
	void ResetHardwareInfo();	//重置（清空）硬件信息

	// 函数 GetBeEmptyHardware
	// 作用：读取GetBeEmptyHardware。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeEmptyHardware();	//判断是否是空的硬件信息，一般Demo模式会导致空的硬件信息

public:
	CString	m_strModel; // PCR仪型号
	CString	m_strSN; // 产品序列号
	CString	m_strCode; // PCR仪版本(类型)
	CString	m_strVersion; // 硬件版本
	CString	m_strSoftwareVer; // 嵌入式软件版本

	CLinkList<tagScanChannelInfo> m_lnkScanChanInfo;
};

