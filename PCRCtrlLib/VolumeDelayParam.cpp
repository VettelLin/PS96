// 【交接】 PCRCtrlLib\VolumeDelayParam.cpp
// 作用：VolumeDelayParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CVolumeDelayParam。
#include "StdAfx.h"
#include "VolumeDelayParam.h"

// 函数 CVolumeDelayParam::CVolumeDelayParam
// 作用：执行CVolumeDelayParam。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CVolumeDelayParam::CVolumeDelayParam(void)
{
	m_dUpTemThre = 90;
	m_dDownTemThre = 70;
	m_dUpK = 0.1;
	m_dDownK = 0.2;
	m_dBaseVolume = 20;
}

// 函数 CVolumeDelayParam::~CVolumeDelayParam
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CVolumeDelayParam::~CVolumeDelayParam(void)
{

}

// 函数 CVolumeDelayParam::CVolumeDelayParam
// 作用：执行CVolumeDelayParam。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CVolumeDelayParam::CVolumeDelayParam(const CVolumeDelayParam& info)
{
	m_dUpTemThre = info.m_dUpTemThre;
	m_dDownTemThre = info.m_dDownTemThre;
	m_dUpK = info.m_dUpK;
	m_dDownK = info.m_dDownK;
	m_dBaseVolume = info.m_dBaseVolume;
}

void CVolumeDelayParam::operator=(const CVolumeDelayParam& info)
{
	m_dUpTemThre = info.m_dUpTemThre;
	m_dDownTemThre = info.m_dDownTemThre;
	m_dUpK = info.m_dUpK;
	m_dDownK = info.m_dDownK;
	m_dBaseVolume = info.m_dBaseVolume;
}



