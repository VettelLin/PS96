// 【交接】 GeneralPcr\ChanMeltAnaParamChangeInfo.cpp
// 作用：ChanMeltAnaParamChangeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CChanMeltAnaParamChangeInfo、IsAnaParamChanged。
#include "StdAfx.h"
#include "ChanMeltAnaParamChangeInfo.h"

// 函数 CChanMeltAnaParamChangeInfo::CChanMeltAnaParamChangeInfo
// 作用：执行CChanMeltAnaParamChangeInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CChanMeltAnaParamChangeInfo::CChanMeltAnaParamChangeInfo(void)
{
	m_bMinTemChanged = FALSE;
	m_bMaxTemChanged = FALSE;
	m_bPeakThreChanged = FALSE;
}

// 函数 CChanMeltAnaParamChangeInfo::~CChanMeltAnaParamChangeInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CChanMeltAnaParamChangeInfo::~CChanMeltAnaParamChangeInfo(void)
{

}

// 函数 CChanMeltAnaParamChangeInfo::CChanMeltAnaParamChangeInfo
// 作用：执行CChanMeltAnaParamChangeInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CChanMeltAnaParamChangeInfo::CChanMeltAnaParamChangeInfo(const CChanMeltAnaParamChangeInfo& info)
{
	m_bMinTemChanged = info.m_bMinTemChanged;
	m_bMaxTemChanged = info.m_bMaxTemChanged;
	m_bPeakThreChanged = info.m_bPeakThreChanged;
}

void CChanMeltAnaParamChangeInfo::operator=(const CChanMeltAnaParamChangeInfo& info)
{
	m_bMinTemChanged = info.m_bMinTemChanged;
	m_bMaxTemChanged = info.m_bMaxTemChanged;
	m_bPeakThreChanged = info.m_bPeakThreChanged;
}

// 函数 CChanMeltAnaParamChangeInfo::IsAnaParamChanged
// 作用：判断IsAnaParamChanged是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CChanMeltAnaParamChangeInfo::IsAnaParamChanged()
{
	return m_bMinTemChanged || m_bMaxTemChanged || m_bPeakThreChanged;
}

