// 【交接】 PCRCtrlLib\ExpStateInfo.cpp
// 作用：ExpStateInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CExpStateInfo、_T、GetRemainTimeStr、strTemp、Format、GetCurrentTemperatureStr、strCurTemp、Clear。
#include "StdAfx.h"
#include "ExpStateInfo.h"


// 函数 CExpStateInfo::CExpStateInfo
// 作用：执行CExpStateInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CExpStateInfo::CExpStateInfo(void)
{
	m_strExpName = _T("");	
	m_iRemainSec = 0;
	m_dCurTem = -1;
	m_dCurProgress = 0;
	m_eExpType = EXP_TYPE_ABSOLUTE;

	m_eRunBtState = ERBS_RUN;
	m_eBinBtState = EBBS_IN;
}


// 函数 CExpStateInfo::~CExpStateInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpStateInfo::~CExpStateInfo(void)
{
}

// 函数 CExpStateInfo::CExpStateInfo
// 作用：执行CExpStateInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpStateInfo::CExpStateInfo(const CExpStateInfo& info)
{
	m_strExpName = info.m_strExpName;	
	m_iRemainSec = info.m_iRemainSec;
	m_dCurTem = info.m_dCurTem;
	m_dCurProgress = info.m_dCurProgress;
	m_eExpType = info.m_eExpType;
	m_eRunBtState = info.m_eRunBtState;
	m_eBinBtState = info.m_eBinBtState;
}

void CExpStateInfo::operator=(const CExpStateInfo& info)
{
	m_strExpName = info.m_strExpName;	
	m_iRemainSec = info.m_iRemainSec;
	m_dCurTem = info.m_dCurTem;
	m_dCurProgress = info.m_dCurProgress;
	m_eExpType = info.m_eExpType;
	m_eRunBtState = info.m_eRunBtState;
	m_eBinBtState = info.m_eBinBtState;
}

// 函数 CExpStateInfo::GetRemainTimeStr
// 作用：读取GetRemainTimeStr。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 strTemp、_T、Format。
CString CExpStateInfo::GetRemainTimeStr()
{
	int iTemp = m_iRemainSec;
	if(iTemp < 0)
	{
		iTemp = 0;
	}
	int iHour = iTemp / 3600;
	iTemp = iTemp % 3600;
	int iMinute = iTemp / 60;
	int iSec = iTemp % 60;
	CString strTemp(_T(""));
	strTemp.Format(_T("%02d:%02d:%02d"),iHour,iMinute,iSec);

	return strTemp;
}

// 函数 CExpStateInfo::GetCurrentTemperatureStr
// 作用：读取GetCurrentTemperatureStr。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 strCurTemp、_T、Format。
CString CExpStateInfo::GetCurrentTemperatureStr()
{
	CString strCurTemp(_T("--℃"));
	if(m_dCurTem < 0)
	{
		return strCurTemp;
	}
	strCurTemp.Format(_T("%.lf℃"),m_dCurTem);
	return strCurTemp;
}

// 函数 CExpStateInfo::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
void CExpStateInfo::Clear()
{
	m_strExpName = _T("");	
	m_iRemainSec = 0;
	m_dCurTem = -1;
	m_dCurProgress = 0;
	m_eExpType = EXP_TYPE_ABSOLUTE;
	m_eRunBtState = ERBS_RUN;
	m_eBinBtState = EBBS_IN;
}
