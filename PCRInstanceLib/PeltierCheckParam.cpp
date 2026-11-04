// 【交接】 PCRInstanceLib\PeltierCheckParam.cpp
// 作用：PeltierCheckParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPeltierCheckParam、IsCheck、GetTemperatureThreshold、GetRiseTemError、GetDropTemError、GetTemRiseDropRange、GetRiseTimeSec、GetDropTimeSec。
#include "StdAfx.h"
#include "PeltierCheckParam.h"


// 函数 CPeltierCheckParam::CPeltierCheckParam
// 作用：执行CPeltierCheckParam。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPeltierCheckParam::CPeltierCheckParam(void)
{
	m_bCheck = TRUE;
	m_dTemThre = 50;
	m_dRiseTemError = 5;
	m_dDropTemError = 5;
	m_dTemRiseDropRange = 20;
	m_fRiseTimeSec = 16;	
	m_fDropTimeSec = 16;	
}

// 函数 CPeltierCheckParam::~CPeltierCheckParam
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPeltierCheckParam::~CPeltierCheckParam(void)
{

}

// 函数 CPeltierCheckParam::CPeltierCheckParam
// 作用：执行CPeltierCheckParam。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPeltierCheckParam::CPeltierCheckParam(const CPeltierCheckParam& info)
{
	m_bCheck = info.m_bCheck;
	m_dTemThre = info.m_dTemThre;
	m_dRiseTemError = info.m_dRiseTemError;
	m_dDropTemError = info.m_dDropTemError;
	m_dTemRiseDropRange = info.m_dTemRiseDropRange;
	m_fRiseTimeSec = info.m_fRiseTimeSec;	
	m_fDropTimeSec = info.m_fDropTimeSec;	
}

void CPeltierCheckParam::operator=(const CPeltierCheckParam& info)
{
	m_bCheck = info.m_bCheck;
	m_dTemThre = info.m_dTemThre;
	m_dRiseTemError = info.m_dRiseTemError;
	m_dDropTemError = info.m_dDropTemError;
	m_dTemRiseDropRange = info.m_dTemRiseDropRange;
	m_fRiseTimeSec = info.m_fRiseTimeSec;	
	m_fDropTimeSec = info.m_fDropTimeSec;	
}

// 函数 CPeltierCheckParam::IsCheck
// 作用：判断IsCheck是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CPeltierCheckParam::IsCheck()
{
	return m_bCheck;
}

// 函数 CPeltierCheckParam::GetTemperatureThreshold
// 作用：读取GetTemperatureThreshold。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CPeltierCheckParam::GetTemperatureThreshold()
{
	return m_dTemThre;
}

// 函数 CPeltierCheckParam::GetRiseTemError
// 作用：读取GetRiseTemError。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CPeltierCheckParam::GetRiseTemError()
{
	return m_dRiseTemError;
}

// 函数 CPeltierCheckParam::GetDropTemError
// 作用：读取GetDropTemError。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CPeltierCheckParam::GetDropTemError()
{
	return m_dDropTemError;
}

// 函数 CPeltierCheckParam::GetTemRiseDropRange
// 作用：读取GetTemRiseDropRange。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CPeltierCheckParam::GetTemRiseDropRange()
{
	return m_dTemRiseDropRange;
}

// 函数 CPeltierCheckParam::GetRiseTimeSec
// 作用：读取GetRiseTimeSec。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CPeltierCheckParam::GetRiseTimeSec()
{
	return m_fRiseTimeSec;
}

// 函数 CPeltierCheckParam::GetDropTimeSec
// 作用：读取GetDropTimeSec。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
float CPeltierCheckParam::GetDropTimeSec()
{
	return m_fDropTimeSec;
}





