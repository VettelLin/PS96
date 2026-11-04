// 【交接】 GeneralPcr\MeltAnaParamChangeInfo.cpp
// 作用：MeltAnaParamChangeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMeltAnaParamChangeInfo、SetChannelNum、clear、push_back、IsAnaParamChanged、IsChannelAnaParamChanged。
#include "StdAfx.h"
#include "MeltAnaParamChangeInfo.h"

// 函数 CMeltAnaParamChangeInfo::CMeltAnaParamChangeInfo
// 作用：执行CMeltAnaParamChangeInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltAnaParamChangeInfo::CMeltAnaParamChangeInfo(void)
{
	m_iChanNum = 0;
}

// 函数 CMeltAnaParamChangeInfo::~CMeltAnaParamChangeInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltAnaParamChangeInfo::~CMeltAnaParamChangeInfo(void)
{

}

// 函数 CMeltAnaParamChangeInfo::CMeltAnaParamChangeInfo
// 作用：执行CMeltAnaParamChangeInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMeltAnaParamChangeInfo::CMeltAnaParamChangeInfo(const CMeltAnaParamChangeInfo& info)
{
	m_iChanNum = info.m_iChanNum;
	m_vecChanMeltChangeInfo = info.m_vecChanMeltChangeInfo;
}

void CMeltAnaParamChangeInfo::operator=(const CMeltAnaParamChangeInfo& info)
{
	m_iChanNum = info.m_iChanNum;
	m_vecChanMeltChangeInfo = info.m_vecChanMeltChangeInfo;
}

// 函数 CMeltAnaParamChangeInfo::SetChannelNum
// 作用：设置SetChannelNum。
// 参数：iChanNum：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 clear、push_back。
int CMeltAnaParamChangeInfo::SetChannelNum(int iChanNum)
{ 
	if(iChanNum < 0)
	{
		return -1;
	}

	if(m_iChanNum == iChanNum)
	{
		return 1;
	}

	m_iChanNum = iChanNum;
	m_vecChanMeltChangeInfo.clear();

	for(int i = 0;i < m_iChanNum;++i)
	{
		CChanMeltAnaParamChangeInfo temp;
		m_vecChanMeltChangeInfo.push_back(temp);
	}

	return 0;
}

// 函数 CMeltAnaParamChangeInfo::IsAnaParamChanged
// 作用：判断IsAnaParamChanged是否成立。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMeltAnaParamChangeInfo::IsAnaParamChanged()
{
	if(m_iChanNum < 1)
	{
		return FALSE;
	}

	for(int i = 0;i < m_iChanNum;++i)
	{
		if(m_vecChanMeltChangeInfo[i].IsAnaParamChanged())
		{
			return TRUE;
		}
	}

	return FALSE;
}

// 函数 CMeltAnaParamChangeInfo::IsChannelAnaParamChanged
// 作用：判断IsChannelAnaParamChanged是否成立。
// 参数：iChanId：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 IsAnaParamChanged。
BOOL CMeltAnaParamChangeInfo::IsChannelAnaParamChanged(int iChanId)
{
	if(iChanId >= m_iChanNum || iChanId < 0)
	{
		return FALSE;
	}

	return m_vecChanMeltChangeInfo[iChanId].IsAnaParamChanged();
}

