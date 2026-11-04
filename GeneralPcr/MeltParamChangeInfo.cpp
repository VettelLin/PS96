// 【交接】 GeneralPcr\MeltParamChangeInfo.cpp
// 作用：MeltParamChangeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMeltParamChangeInfo、GetBeChanged。
#include "StdAfx.h"
#include "MeltParamChangeInfo.h"

// 函数 CMeltParamChangeInfo::CMeltParamChangeInfo
// 作用：执行CMeltParamChangeInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltParamChangeInfo::CMeltParamChangeInfo(void)
{
	m_bChanged = FALSE;
	m_bMeltTemMinChanged = FALSE;
	m_bMeltTemMaxChanged = FALSE;
	m_bPeakHeightThreChanged = FALSE;
	m_bCrvMeltPeakNeedRedraw = FALSE;
	m_bRstLstNeedRedraw = FALSE;
}

// 函数 CMeltParamChangeInfo::~CMeltParamChangeInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltParamChangeInfo::~CMeltParamChangeInfo(void)
{

}

// 函数 CMeltParamChangeInfo::CMeltParamChangeInfo
// 作用：执行CMeltParamChangeInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltParamChangeInfo::CMeltParamChangeInfo(const CMeltParamChangeInfo& info)
{
	m_bChanged = info.m_bChanged;
	m_bMeltTemMinChanged = info.m_bMeltTemMinChanged;
	m_bMeltTemMaxChanged = info.m_bMeltTemMaxChanged;
	m_bPeakHeightThreChanged = info.m_bPeakHeightThreChanged;
	m_bCrvMeltPeakNeedRedraw = info.m_bCrvMeltPeakNeedRedraw;
	m_bRstLstNeedRedraw = info.m_bRstLstNeedRedraw;
}

void CMeltParamChangeInfo::operator=(const CMeltParamChangeInfo& info)
{
	m_bChanged = info.m_bChanged;
	m_bMeltTemMinChanged = info.m_bMeltTemMinChanged;
	m_bMeltTemMaxChanged = info.m_bMeltTemMaxChanged;
	m_bPeakHeightThreChanged = info.m_bPeakHeightThreChanged;
	m_bCrvMeltPeakNeedRedraw = info.m_bCrvMeltPeakNeedRedraw;
	m_bRstLstNeedRedraw = info.m_bRstLstNeedRedraw;
}

// 函数 CMeltParamChangeInfo::GetBeChanged
// 作用：读取GetBeChanged。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMeltParamChangeInfo::GetBeChanged()
{
	m_bChanged = m_bMeltTemMinChanged || m_bMeltTemMaxChanged || m_bPeakHeightThreChanged;
	return m_bChanged;
}

