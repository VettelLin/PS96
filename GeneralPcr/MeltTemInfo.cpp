// 【交接】 GeneralPcr\MeltTemInfo.cpp
// 作用：MeltTemInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMeltTemInfo。
#include "StdAfx.h"
#include "MeltTemInfo.h"

// 函数 CMeltTemInfo::CMeltTemInfo
// 作用：执行CMeltTemInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltTemInfo::CMeltTemInfo(void)
{
	m_dTargetTem = 0;
	m_dPeltier1Tem = 0;   
	m_dPeltier2Tem = 0;	
	m_dPeltier3Tem = 0;	

	m_dPeltier1StartTem = 0; 
	m_dPeltier1EndTem = 0;   
	m_dPeltier2StartTem = 0; 
	m_dPeltier2EndTem = 0;   
	m_dPeltier3StartTem = 0; 
	m_dPeltier3EndTem = 0;
}


// 函数 CMeltTemInfo::~CMeltTemInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltTemInfo::~CMeltTemInfo(void)
{
}

// 函数 CMeltTemInfo::CMeltTemInfo
// 作用：执行CMeltTemInfo。
// 参数：meltTemInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltTemInfo::CMeltTemInfo(const CMeltTemInfo& meltTemInfo)
{
	m_dTargetTem = meltTemInfo.m_dTargetTem;
	m_dPeltier1Tem = meltTemInfo.m_dPeltier1Tem;   
	m_dPeltier2Tem = meltTemInfo.m_dPeltier2Tem;	
	m_dPeltier3Tem = meltTemInfo.m_dPeltier3Tem;	

	m_dPeltier1StartTem = meltTemInfo.m_dPeltier1StartTem; 
	m_dPeltier1EndTem = meltTemInfo.m_dPeltier1EndTem;   
	m_dPeltier2StartTem = meltTemInfo.m_dPeltier2StartTem; 
	m_dPeltier2EndTem = meltTemInfo.m_dPeltier2EndTem;   
	m_dPeltier3StartTem = meltTemInfo.m_dPeltier3StartTem; 
	m_dPeltier3EndTem = meltTemInfo.m_dPeltier3EndTem;
}

void CMeltTemInfo::operator=(const CMeltTemInfo& meltTemInfo)
{
	m_dTargetTem = meltTemInfo.m_dTargetTem;
	m_dPeltier1Tem = meltTemInfo.m_dPeltier1Tem;   
	m_dPeltier2Tem = meltTemInfo.m_dPeltier2Tem;	
	m_dPeltier3Tem = meltTemInfo.m_dPeltier3Tem;	

	m_dPeltier1StartTem = meltTemInfo.m_dPeltier1StartTem; 
	m_dPeltier1EndTem = meltTemInfo.m_dPeltier1EndTem;   
	m_dPeltier2StartTem = meltTemInfo.m_dPeltier2StartTem; 
	m_dPeltier2EndTem = meltTemInfo.m_dPeltier2EndTem;   
	m_dPeltier3StartTem = meltTemInfo.m_dPeltier3StartTem; 
	m_dPeltier3EndTem = meltTemInfo.m_dPeltier3EndTem;
}



