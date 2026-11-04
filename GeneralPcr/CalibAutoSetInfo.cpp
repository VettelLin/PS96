// 【交接】 GeneralPcr\CalibAutoSetInfo.cpp
// 作用：CalibAutoSetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCalibAutoSetInfo。
#include "StdAfx.h"
#include "CalibAutoSetInfo.h"


// 函数 CCalibAutoSetInfo::CCalibAutoSetInfo
// 作用：执行CCalibAutoSetInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCalibAutoSetInfo::CCalibAutoSetInfo(void)
{
	m_repeatNum = 1;
	m_dStartDensity = 10000;
	m_eDilutionDirection = EDD_INCREASE;
	m_dilutionMulitiples = 10;
	m_eSamSortWay = ESSW_HORI;
	m_selectHoleNum = 0;
}


// 函数 CCalibAutoSetInfo::~CCalibAutoSetInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCalibAutoSetInfo::~CCalibAutoSetInfo(void)
{
	
}

// 函数 CCalibAutoSetInfo::CCalibAutoSetInfo
// 作用：执行CCalibAutoSetInfo。
// 参数：calibAutoSetInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCalibAutoSetInfo::CCalibAutoSetInfo(const CCalibAutoSetInfo& calibAutoSetInfo)
{
	m_repeatNum = calibAutoSetInfo.m_repeatNum;
	m_dStartDensity = calibAutoSetInfo.m_dStartDensity;
	m_eDilutionDirection = calibAutoSetInfo.m_eDilutionDirection;
	m_dilutionMulitiples = calibAutoSetInfo.m_dilutionMulitiples;
	m_eSamSortWay = calibAutoSetInfo.m_eSamSortWay;
	m_selectHoleNum = calibAutoSetInfo.m_selectHoleNum;
}

void CCalibAutoSetInfo::operator=(const CCalibAutoSetInfo& calibAutoSetInfo)
{
	m_repeatNum = calibAutoSetInfo.m_repeatNum;
	m_dStartDensity = calibAutoSetInfo.m_dStartDensity;
	m_eDilutionDirection = calibAutoSetInfo.m_eDilutionDirection;
	m_dilutionMulitiples = calibAutoSetInfo.m_dilutionMulitiples;
	m_eSamSortWay = calibAutoSetInfo.m_eSamSortWay;
	m_selectHoleNum = calibAutoSetInfo.m_selectHoleNum;
}

