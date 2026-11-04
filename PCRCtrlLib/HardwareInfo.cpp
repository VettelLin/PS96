// 【交接】 PCRCtrlLib\HardwareInfo.cpp
// 作用：HardwareInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CHardwareInfo、Empty、WriteFile、WriteStringToFile、ReadFile、ReadStringFromFile、WriteScanChannelInfoToFile、GetSize。
#include "StdAfx.h"
#include "HardwareInfo.h"
#include "PublicFun.h"

// 函数 CHardwareInfo::CHardwareInfo
// 作用：执行CHardwareInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CHardwareInfo::CHardwareInfo(void)
{
	m_strModel.Empty();
	m_strSN.Empty();
	m_strCode.Empty();
	m_strVersion.Empty();
	m_strSoftwareVer.Empty();
}

// 函数 CHardwareInfo::~CHardwareInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHardwareInfo::~CHardwareInfo(void)
{

}

// 函数 CHardwareInfo::CHardwareInfo
// 作用：执行CHardwareInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHardwareInfo::CHardwareInfo(const CHardwareInfo& info)
{
	m_strModel = info.m_strModel;
	m_strSN = info.m_strSN;
	m_strCode = info.m_strCode;
	m_strVersion = info.m_strVersion;
	m_strSoftwareVer = info.m_strSoftwareVer;
	m_lnkScanChanInfo = info.m_lnkScanChanInfo;
}

void CHardwareInfo::operator=(const CHardwareInfo& info)
{
	m_strModel = info.m_strModel;
	m_strSN = info.m_strSN;
	m_strCode = info.m_strCode;
	m_strVersion = info.m_strVersion;
	m_strSoftwareVer = info.m_strSoftwareVer;
	m_lnkScanChanInfo = info.m_lnkScanChanInfo;
}

// 函数 CHardwareInfo::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象；bTemplate：是或否。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 WriteStringToFile、_T。
BOOL CHardwareInfo::WriteFile(CFile* pFile,BOOL bTemplate)
{
	if(NULL == pFile)
	{
		return FALSE;
	}

	if(bTemplate)
	{	
		//模板文件保存的硬件信息设置为空
		CPublicFun::WriteStringToFile(pFile,_T(""));
		CPublicFun::WriteStringToFile(pFile,_T(""));
		CPublicFun::WriteStringToFile(pFile,_T(""));
		CPublicFun::WriteStringToFile(pFile,_T(""));
		CPublicFun::WriteStringToFile(pFile,_T(""));
	}
	else
	{
		CPublicFun::WriteStringToFile(pFile,m_strModel);
		CPublicFun::WriteStringToFile(pFile,m_strSN);
		CPublicFun::WriteStringToFile(pFile,m_strCode);
		CPublicFun::WriteStringToFile(pFile,m_strVersion);
		CPublicFun::WriteStringToFile(pFile,m_strSoftwareVer);
	}
	return TRUE;
}

// 函数 CHardwareInfo::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 ReadStringFromFile。
BOOL CHardwareInfo::ReadFile(CFile* pFile,WORD wVersion)
{
	if(wVersion < 0x0106)
	{
		return TRUE;
	}

	if(NULL == pFile)
	{
		return FALSE;
	}
	m_strModel = CPublicFun::ReadStringFromFile(pFile);
	m_strSN = CPublicFun::ReadStringFromFile(pFile);
	m_strCode = CPublicFun::ReadStringFromFile(pFile);
	m_strVersion = CPublicFun::ReadStringFromFile(pFile);
	m_strSoftwareVer = CPublicFun::ReadStringFromFile(pFile);

	return TRUE;
}

// 函数 CHardwareInfo::WriteScanChannelInfoToFile
// 作用：把WriteScanChannelInfoToFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象；bTemplate：是或否。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSize、Write。
BOOL CHardwareInfo::WriteScanChannelInfoToFile(CFile* pFile,BOOL bTemplate)
{
	if(NULL == pFile)
	{
		return FALSE;
	}

	if(bTemplate)
	{
		return TRUE;
	}

	int iCount = m_lnkScanChanInfo.GetSize();
	pFile->Write((const char *)&iCount,sizeof(int));

	for(int i = 0;i < iCount;++i)
	{
		tagScanChannelInfo& scanChanInfo = *m_lnkScanChanInfo[i];
		pFile->Write((const char *)&scanChanInfo,sizeof(tagScanChannelInfo));
	}

	return TRUE;
}

// 函数 CHardwareInfo::ReadScanChannelInfoFromFile
// 作用：读取ReadScanChannelInfoFromFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion；bTemplate：是或否。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 Clear、Read、AddTail。
BOOL CHardwareInfo::ReadScanChannelInfoFromFile(CFile* pFile,WORD wVersion,BOOL bTemplate)
{
	if(NULL == pFile)
	{
		return FALSE;
	}

	if(bTemplate)
	{
		return TRUE;
	}

	m_lnkScanChanInfo.Clear();

	int iCount = 0;
	pFile->Read((char*)&iCount,sizeof(int));

	tagScanChannelInfo scanChanInfo;
	for(int i = 0;i < iCount;++i)
	{
		pFile->Read((char*)&scanChanInfo,sizeof(tagScanChannelInfo));
		m_lnkScanChanInfo.AddTail(scanChanInfo);
	}

	return TRUE;
}

// 函数 CHardwareInfo::ResetHardwareInfo
// 作用：更新或清除ResetHardwareInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
void CHardwareInfo::ResetHardwareInfo()
{
	m_strModel.Empty();
	m_strSN.Empty();
	m_strCode.Empty();
	m_strVersion.Empty();
	m_strSoftwareVer.Empty();
}

// 函数 CHardwareInfo::GetBeEmptyHardware
// 作用：读取GetBeEmptyHardware。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 IsEmpty。
BOOL CHardwareInfo::GetBeEmptyHardware()
{
	return m_strModel.IsEmpty() &&
	m_strSN.IsEmpty() &&
	m_strCode.IsEmpty() &&
	m_strVersion.IsEmpty() &&
	m_strSoftwareVer.IsEmpty();
}

