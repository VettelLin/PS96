// 【交接】 GeneralPcr\ChanThreInfo.cpp
// 作用：ChanThreInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CChanThreInfo、_T、GetCurSelThreInfo、GetCurSelAssociatedThreInfo。
#include "StdAfx.h"
#include "ChanThreInfo.h"

// 函数 CChanThreInfo::CChanThreInfo
// 作用：执行CChanThreInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CChanThreInfo::CChanThreInfo(void)
{
	m_eLineDataType = ELDT_NORMALIZE;
	m_eLineShowFormat = ELSF_LINEAR;
	m_iChanId = -1;
	m_strChanName = _T("");
	m_strTargetName = _T("");
}

// 函数 CChanThreInfo::~CChanThreInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CChanThreInfo::~CChanThreInfo(void)
{

}

// 函数 CChanThreInfo::CChanThreInfo
// 作用：执行CChanThreInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CChanThreInfo::CChanThreInfo(const CChanThreInfo& info)
{
	m_eLineDataType = info.m_eLineDataType;
	m_eLineShowFormat = info.m_eLineShowFormat; 
	m_iChanId = info.m_iChanId;
	m_strChanName = info.m_strChanName;
	m_strTargetName = info.m_strTargetName;

	m_tliNormolize = info.m_tliNormolize;
	m_tliDeltaRn = info.m_tliDeltaRn;
	m_tliLogNormolize = info.m_tliLogNormolize;
	m_tliLogDeltaRn = info.m_tliLogDeltaRn;
}

void CChanThreInfo::operator=(const CChanThreInfo& info)
{
	m_eLineDataType = info.m_eLineDataType;
	m_eLineShowFormat = info.m_eLineShowFormat; 
	m_iChanId = info.m_iChanId;
	m_strChanName = info.m_strChanName;
	m_strTargetName = info.m_strTargetName;

	m_tliNormolize = info.m_tliNormolize;
	m_tliDeltaRn = info.m_tliDeltaRn;
	m_tliLogNormolize = info.m_tliLogNormolize;
	m_tliLogDeltaRn = info.m_tliLogDeltaRn;
}

void CChanThreInfo::operator=(CChanThreInfo& info)
{
	m_eLineDataType = info.m_eLineDataType;
	m_eLineShowFormat = info.m_eLineShowFormat; 
	m_iChanId = info.m_iChanId;
	m_strChanName = info.m_strChanName;
	m_strTargetName = info.m_strTargetName;

	m_tliNormolize = info.m_tliNormolize;
	m_tliDeltaRn = info.m_tliDeltaRn;
	m_tliLogNormolize = info.m_tliLogNormolize;
	m_tliLogDeltaRn = info.m_tliLogDeltaRn;
}

// 函数 CChanThreInfo::GetCurSelThreInfo
// 作用：读取GetCurSelThreInfo。
// 参数：无。
// 返回：返回指针 CThreLineInfo*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CThreLineInfo* CChanThreInfo::GetCurSelThreInfo()
{ 
	if(ELSF_LINEAR == m_eLineShowFormat)
	{
		if(ELDT_NORMALIZE == m_eLineDataType)
		{
			return &m_tliNormolize; 
		}
		else if(ELDT_DELTARN == m_eLineDataType)
		{
			return &m_tliDeltaRn; 
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		if(ELDT_NORMALIZE == m_eLineDataType)
		{
			return &m_tliLogNormolize; 
		}
		else if(ELDT_DELTARN == m_eLineDataType)
		{
			return &m_tliLogDeltaRn; 
		}
		else
		{
			return NULL;
		}
	}
}

// 函数 CChanThreInfo::GetCurSelAssociatedThreInfo
// 作用：读取GetCurSelAssociatedThreInfo。
// 参数：无。
// 返回：返回指针 CThreLineInfo*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CThreLineInfo* CChanThreInfo::GetCurSelAssociatedThreInfo()
{ 
	if(ELSF_LINEAR == m_eLineShowFormat)
	{
		if(ELDT_NORMALIZE == m_eLineDataType)
		{
			return &m_tliLogNormolize; 
		}
		else if(ELDT_DELTARN == m_eLineDataType)
		{
			return &m_tliLogDeltaRn; 
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		if(ELDT_NORMALIZE == m_eLineDataType)
		{
			return &m_tliNormolize; 
		}
		else if(ELDT_DELTARN == m_eLineDataType)
		{
			return &m_tliDeltaRn; 
		}
		else
		{
			return NULL;
		}
	}
}
//
//void CChanThreInfo::SetBeAutoThre(BOOL bAutoThre)
//{
//	m_tliNormolize.m_bAutoThre = bAutoThre;
//	m_tliNormolize.m_bFstDrawThreLine = TRUE;
//	m_tliDeltaRn.m_bAutoThre = bAutoThre;
//	m_tliDeltaRn.m_bFstDrawThreLine = TRUE;
//	m_tliLogNormolize.m_bAutoThre = bAutoThre;
//	m_tliLogNormolize.m_bFstDrawThreLine = TRUE;
//	m_tliLogDeltaRn.m_bAutoThre = bAutoThre;
//	m_tliLogDeltaRn.m_bFstDrawThreLine = TRUE;
//	return;
//}
//
