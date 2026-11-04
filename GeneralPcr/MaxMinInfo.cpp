// 【交接】 GeneralPcr\MaxMinInfo.cpp
// 作用：MaxMinInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMaxMinInfo、SetBeOnlyIntergerNumber、GetBeOnlyIntergerNumber、SetBeOnlyFloatNumber、GetBeOnlyFloatNumber、SetBeSetMaxValue、GetBeSetMaxValue、SetMaxValue。
#include "StdAfx.h"
#include "MaxMinInfo.h"


// 函数 CMaxMinInfo::CMaxMinInfo
// 作用：执行CMaxMinInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMaxMinInfo::CMaxMinInfo(void)
{
	m_bOnlyIntergerNumber = FALSE;	
	m_bOnlyFloatNumber = FALSE;	
	m_bSetMaxValue = FALSE;	
	m_dMaxValue = 1;	
	m_bMaxEqualSignWork = TRUE;	
	m_bSetMinValue = FALSE;	
	m_dMinValue = 0;	
	m_bMinEqualSignWork = TRUE;	
	m_bAllowNegtiveNumber = TRUE;
	m_bMaxMinSimultaneousEffect = FALSE;
	m_bLessThanMinSetMin = TRUE;
}

// 函数 CMaxMinInfo::~CMaxMinInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMaxMinInfo::~CMaxMinInfo(void)
{
}

// 函数 CMaxMinInfo::CMaxMinInfo
// 作用：执行CMaxMinInfo。
// 参数：minMaxInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMaxMinInfo::CMaxMinInfo(const CMaxMinInfo& minMaxInfo)
{
	m_bOnlyIntergerNumber = minMaxInfo.m_bOnlyIntergerNumber;	
	m_bOnlyFloatNumber = minMaxInfo.m_bOnlyFloatNumber;	
	m_bSetMaxValue = minMaxInfo.m_bSetMaxValue;	
	m_dMaxValue = minMaxInfo.m_dMaxValue;	
	m_bMaxEqualSignWork = minMaxInfo.m_bMaxEqualSignWork;	
	m_bSetMinValue = minMaxInfo.m_bSetMinValue;	
	m_dMinValue = minMaxInfo.m_dMinValue;	
	m_bMinEqualSignWork = minMaxInfo.m_bMinEqualSignWork;
	m_bAllowNegtiveNumber = minMaxInfo.m_bAllowNegtiveNumber;
	m_bMaxMinSimultaneousEffect = minMaxInfo.m_bMaxMinSimultaneousEffect;
	m_bLessThanMinSetMin = minMaxInfo.m_bLessThanMinSetMin;
}

void CMaxMinInfo::operator=(const CMaxMinInfo& minMaxInfo)
{
	m_bOnlyIntergerNumber = minMaxInfo.m_bOnlyIntergerNumber;	
	m_bOnlyFloatNumber = minMaxInfo.m_bOnlyFloatNumber;	
	m_bSetMaxValue = minMaxInfo.m_bSetMaxValue;	
	m_dMaxValue = minMaxInfo.m_dMaxValue;	
	m_bMaxEqualSignWork = minMaxInfo.m_bMaxEqualSignWork;	
	m_bSetMinValue = minMaxInfo.m_bSetMinValue;	
	m_dMinValue = minMaxInfo.m_dMinValue;	
	m_bMinEqualSignWork = minMaxInfo.m_bMinEqualSignWork;	
	m_bAllowNegtiveNumber = minMaxInfo.m_bAllowNegtiveNumber;
	m_bMaxMinSimultaneousEffect = minMaxInfo.m_bMaxMinSimultaneousEffect;
	m_bLessThanMinSetMin = minMaxInfo.m_bLessThanMinSetMin;
}

// 函数 CMaxMinInfo::SetBeOnlyIntergerNumber
// 作用：设置SetBeOnlyIntergerNumber。
// 参数：beOnlyIntergerNumber。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeOnlyIntergerNumber(BOOL beOnlyIntergerNumber)
{
	m_bOnlyIntergerNumber = beOnlyIntergerNumber;
}

// 函数 CMaxMinInfo::GetBeOnlyIntergerNumber
// 作用：读取GetBeOnlyIntergerNumber。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeOnlyIntergerNumber()
{
	return m_bOnlyIntergerNumber;
}

// 函数 CMaxMinInfo::SetBeOnlyFloatNumber
// 作用：设置SetBeOnlyFloatNumber。
// 参数：beOnlyFloatNumber。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeOnlyFloatNumber(BOOL beOnlyFloatNumber)
{
	m_bOnlyFloatNumber = beOnlyFloatNumber;
}

// 函数 CMaxMinInfo::GetBeOnlyFloatNumber
// 作用：读取GetBeOnlyFloatNumber。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeOnlyFloatNumber()
{
	return m_bOnlyFloatNumber;
}

// 函数 CMaxMinInfo::SetBeSetMaxValue
// 作用：设置SetBeSetMaxValue。
// 参数：bSetMaxValue：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeSetMaxValue(BOOL bSetMaxValue)
{
	m_bSetMaxValue = bSetMaxValue;
}

// 函数 CMaxMinInfo::GetBeSetMaxValue
// 作用：读取GetBeSetMaxValue。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeSetMaxValue()
{
	return m_bSetMaxValue;
}


// 函数 CMaxMinInfo::SetMaxValue
// 作用：设置SetMaxValue。
// 参数：dMaxValue：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetMaxValue(double dMaxValue)
{
	m_dMaxValue = dMaxValue;
}

// 函数 CMaxMinInfo::GetMaxValue
// 作用：读取GetMaxValue。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CMaxMinInfo::GetMaxValue()
{
	return m_dMaxValue;
}

// 函数 CMaxMinInfo::SetBeMaxEqualSignWork
// 作用：设置SetBeMaxEqualSignWork。
// 参数：bMaxEqualSignWork：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeMaxEqualSignWork(double bMaxEqualSignWork)
{
	m_bMaxEqualSignWork = bMaxEqualSignWork;
}

// 函数 CMaxMinInfo::GetBeMaxEqualSignWork
// 作用：读取GetBeMaxEqualSignWork。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeMaxEqualSignWork()
{
	return m_bMaxEqualSignWork;
}

// 函数 CMaxMinInfo::SetBeSetMinValue
// 作用：设置SetBeSetMinValue。
// 参数：bSetMinValue：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeSetMinValue(BOOL bSetMinValue)
{
	m_bSetMinValue = bSetMinValue;
}

// 函数 CMaxMinInfo::GetBeSetMinValue
// 作用：读取GetBeSetMinValue。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeSetMinValue()
{
	return m_bSetMinValue;
}

// 函数 CMaxMinInfo::SetMinValue
// 作用：设置SetMinValue。
// 参数：dMinValue：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetMinValue(double dMinValue)
{
	m_dMinValue = dMinValue;
}

// 函数 CMaxMinInfo::GetMinValue
// 作用：读取GetMinValue。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CMaxMinInfo::GetMinValue()
{
	return m_dMinValue;
}


// 函数 CMaxMinInfo::SetBeMinEqualSignWork
// 作用：设置SetBeMinEqualSignWork。
// 参数：bMinEqualSignWork：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeMinEqualSignWork(double bMinEqualSignWork)
{
	m_bMinEqualSignWork = bMinEqualSignWork;
}

// 函数 CMaxMinInfo::GetBeMinEqualSignWork
// 作用：读取GetBeMinEqualSignWork。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeMinEqualSignWork()
{
	return m_bMinEqualSignWork;
}

// 函数 CMaxMinInfo::SetBeAllowNegtiveNumber
// 作用：设置SetBeAllowNegtiveNumber。
// 参数：bAllowNegtiveNumber：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeAllowNegtiveNumber(BOOL bAllowNegtiveNumber)
{
	m_bAllowNegtiveNumber = bAllowNegtiveNumber;
}

// 函数 CMaxMinInfo::GetBeAllowNegtiveNumber
// 作用：读取GetBeAllowNegtiveNumber。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeAllowNegtiveNumber()
{
	return m_bAllowNegtiveNumber;
}

// 函数 CMaxMinInfo::SetBeMaxMinSimultaneousEffect
// 作用：设置SetBeMaxMinSimultaneousEffect。
// 参数：bMaxMinSimultaneousEffect：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeMaxMinSimultaneousEffect(BOOL bMaxMinSimultaneousEffect)
{
	m_bMaxMinSimultaneousEffect = bMaxMinSimultaneousEffect;
}

// 函数 CMaxMinInfo::GetBeMaxMinSimultaneousEffect
// 作用：读取GetBeMaxMinSimultaneousEffect。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeMaxMinSimultaneousEffect()
{
	return m_bMaxMinSimultaneousEffect;
}

// 函数 CMaxMinInfo::SetBeLessThanMinSetMin
// 作用：设置SetBeLessThanMinSetMin。
// 参数：bLessThanMinSetMin：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::SetBeLessThanMinSetMin(BOOL bLessThanMinSetMin)
{
	m_bLessThanMinSetMin = bLessThanMinSetMin;
}

// 函数 CMaxMinInfo::GetBeLessThanMinSetMin
// 作用：读取GetBeLessThanMinSetMin。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMaxMinInfo::GetBeLessThanMinSetMin()
{
	return m_bLessThanMinSetMin;
}

// 函数 CMaxMinInfo::ClearMaxMinLimit
// 作用：更新或清除ClearMaxMinLimit。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMaxMinInfo::ClearMaxMinLimit()
{
	m_bSetMaxValue = FALSE;
	m_bSetMinValue = FALSE;
	m_bOnlyFloatNumber = FALSE;
	m_bOnlyIntergerNumber = FALSE;
	m_bMaxMinSimultaneousEffect = FALSE;
	m_bAllowNegtiveNumber = FALSE;
	m_bMinEqualSignWork = FALSE;
	m_bMaxEqualSignWork = FALSE;
}

