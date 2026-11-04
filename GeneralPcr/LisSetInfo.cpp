// 【交接】 GeneralPcr\LisSetInfo.cpp
// 作用：LisSetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CLisSetInfo、_T。
#include "StdAfx.h"
#include "LisSetInfo.h"


// 函数 CLisSetInfo::CLisSetInfo
// 作用：执行CLisSetInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CLisSetInfo::CLisSetInfo(void)
{
	m_bOpenLis = FALSE;
	m_dRecvWaitMaxSec = 5;
	m_maxTransferTimes = 3;

	m_bUseCom = TRUE;
	m_strComId = _T("COM1");
	m_dataNum = 8;
	m_dStopBit = 1;
	m_baudRate = 9600;
	m_strIpAddress = _T("127.0.0.1");
	m_strPort = _T("21110");
}

// 函数 CLisSetInfo::~CLisSetInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLisSetInfo::~CLisSetInfo(void)
{

}

// 函数 CLisSetInfo::CLisSetInfo
// 作用：执行CLisSetInfo。
// 参数：lisSetInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLisSetInfo::CLisSetInfo(const CLisSetInfo& lisSetInfo)
{
	m_bOpenLis = lisSetInfo.m_bOpenLis;
	m_dRecvWaitMaxSec = lisSetInfo.m_dRecvWaitMaxSec;
	m_maxTransferTimes = lisSetInfo.m_maxTransferTimes;
	m_bUseCom = lisSetInfo.m_bUseCom;
	m_strComId = lisSetInfo.m_strComId;
	m_dataNum = lisSetInfo.m_dataNum;
	m_dStopBit = lisSetInfo.m_dStopBit;
	m_baudRate = lisSetInfo.m_baudRate;
	m_strIpAddress = lisSetInfo.m_strIpAddress;
	m_strPort = lisSetInfo.m_strPort;
}

void CLisSetInfo::operator=(const CLisSetInfo& lisSetInfo)
{
	m_bOpenLis = lisSetInfo.m_bOpenLis;
	m_dRecvWaitMaxSec = lisSetInfo.m_dRecvWaitMaxSec;
	m_maxTransferTimes = lisSetInfo.m_maxTransferTimes;
	m_bUseCom = lisSetInfo.m_bUseCom;
	m_strComId = lisSetInfo.m_strComId;
	m_dataNum = lisSetInfo.m_dataNum;
	m_dStopBit = lisSetInfo.m_dStopBit;
	m_baudRate = lisSetInfo.m_baudRate;
	m_strIpAddress = lisSetInfo.m_strIpAddress;
	m_strPort = lisSetInfo.m_strPort;
}



