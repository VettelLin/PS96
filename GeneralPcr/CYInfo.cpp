// 【交接】 GeneralPcr\CYInfo.cpp
// 作用：CYInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCYInfo、Empty。
#include "StdAfx.h"
#include "CYInfo.h"


// 函数 CCYInfo::CCYInfo
// 作用：执行CCYInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CCYInfo::CCYInfo(void)
{
	m_strClient.Empty();
	m_strCpAdr.Empty();
	m_strRptSoftDir.Empty();
}

// 函数 CCYInfo::~CCYInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCYInfo::~CCYInfo(void)
{

}

// 函数 CCYInfo::CCYInfo
// 作用：执行CCYInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCYInfo::CCYInfo(const CCYInfo& info)
{
	m_strClient = info.m_strClient;
	m_strCpAdr = info.m_strCpAdr;
	m_strRptSoftDir = info.m_strRptSoftDir;
}

void CCYInfo::operator=(const CCYInfo& info)
{
	m_strClient = info.m_strClient;
	m_strCpAdr = m_strCpAdr;
	m_strRptSoftDir = info.m_strRptSoftDir;
}



