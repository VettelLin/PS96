// 【交接】 GeneralPcr\SingleLgdInfo.cpp
// 作用：SingleLgdInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSingleLgdInfo、Color、_T。
#include "StdAfx.h"
#include "SingleLgdInfo.h"


// 函数 CSingleLgdInfo::CSingleLgdInfo
// 作用：执行CSingleLgdInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Color、_T。
CSingleLgdInfo::CSingleLgdInfo(void)
{
	m_clrFrame = Color(0XFF,0XFF,0XFF);
	m_clrFill = 0;
	m_pxFrameW = 1;
	m_strTx = _T("");
}

// 函数 CSingleLgdInfo::~CSingleLgdInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSingleLgdInfo::~CSingleLgdInfo(void)
{
}

// 函数 CSingleLgdInfo::CSingleLgdInfo
// 作用：执行CSingleLgdInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSingleLgdInfo::CSingleLgdInfo(const CSingleLgdInfo& info)
{
	m_clrFrame = info.m_clrFrame;
	m_clrFill = info.m_clrFill;
	m_pxFrameW = info.m_pxFrameW;
	m_strTx = info.m_strTx;
}

void CSingleLgdInfo::operator=(const CSingleLgdInfo& info)
{
	m_clrFrame = info.m_clrFrame;
	m_clrFill = info.m_clrFill;
	m_pxFrameW = info.m_pxFrameW;
	m_strTx = info.m_strTx;
}

