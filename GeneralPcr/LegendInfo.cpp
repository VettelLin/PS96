// 【交接】 GeneralPcr\LegendInfo.cpp
// 作用：LegendInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CLegendInfo、Color、AddSingleLegendInfo、AddTail、GetSingleLegendCount、GetSize、GetSingleLegendInfo、ResetSegLegendText。
#include "StdAfx.h"
#include "LegendInfo.h"


// 函数 CLegendInfo::CLegendInfo
// 作用：执行CLegendInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Color。
CLegendInfo::CLegendInfo(void)
{
	m_iLeftIndent = 41; 
	m_iRoundRadius = 6;
	m_iInrIconToTx = 8;
	m_iInrTxToIcon = 20;
	m_iOneCharW = 14;
	m_clrFrame = Color(0XD8,0XD8,0XD8);
	m_clrBk = Color(255,0XF7,0XF7,0XF7);
	m_clrBkEnd = Color(255,0XF5,0XF5,0XF5);
}


// 函数 CLegendInfo::~CLegendInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLegendInfo::~CLegendInfo(void)
{
}

// 函数 CLegendInfo::CLegendInfo
// 作用：执行CLegendInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLegendInfo::CLegendInfo(const CLegendInfo& info)
{
	m_iLeftIndent = info.m_iLeftIndent;
	m_iRoundRadius = info.m_iRoundRadius;
	m_iInrIconToTx = info.m_iInrIconToTx;
	m_iInrTxToIcon = info.m_iInrTxToIcon;
	m_iOneCharW = info.m_iOneCharW;
	m_clrFrame = info.m_clrFrame;
	m_clrBk = info.m_clrBk;
	m_clrBkEnd = info.m_clrBkEnd;
	m_lnkSingleLgdInfo = info.m_lnkSingleLgdInfo;
}

void CLegendInfo::operator=(const CLegendInfo& info)
{
	m_iLeftIndent = info.m_iLeftIndent;
	m_iRoundRadius = info.m_iRoundRadius;
	m_iInrIconToTx = info.m_iInrIconToTx;
	m_iInrTxToIcon = info.m_iInrTxToIcon;
	m_iOneCharW = info.m_iOneCharW;
	m_clrFrame = info.m_clrFrame;
	m_clrBk = info.m_clrBk;
	m_clrBkEnd = info.m_clrBkEnd;
	m_lnkSingleLgdInfo = info.m_lnkSingleLgdInfo;
}

// 函数 CLegendInfo::AddSingleLegendInfo
// 作用：创建或加入AddSingleLegendInfo。
// 参数：singleLgdInfo。
// 返回：没有返回值。
// 过程：函数里会调用 AddTail。
void CLegendInfo::AddSingleLegendInfo(CSingleLgdInfo& singleLgdInfo)
{
	m_lnkSingleLgdInfo.AddTail(singleLgdInfo);
}

// 函数 CLegendInfo::GetSingleLegendCount
// 作用：读取GetSingleLegendCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize。
int CLegendInfo::GetSingleLegendCount()
{
	return m_lnkSingleLgdInfo.GetSize();
}

// 函数 CLegendInfo::GetSingleLegendInfo
// 作用：读取GetSingleLegendInfo。
// 参数：iIndex：整数。
// 返回：返回指针 CSingleLgdInfo*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：函数里会调用 GetSize。
CSingleLgdInfo* CLegendInfo::GetSingleLegendInfo(int iIndex)
{
	if(iIndex < 0 || iIndex >= m_lnkSingleLgdInfo.GetSize())
	{
		return NULL;
	}

	return &(*m_lnkSingleLgdInfo[iIndex]);
}

// 函数 CLegendInfo::ResetSegLegendText
// 作用：更新或清除ResetSegLegendText。
// 参数：pLgdInfo：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetInstance、GetText。
void CLegendInfo::ResetSegLegendText(CLegendInfo* pLgdInfo)
{
	if(NULL == pLgdInfo)
	{
		return;
	}

	int iLgdCount = pLgdInfo->m_lnkSingleLgdInfo.GetSize();
	if(iLgdCount < 5)
	{
		return;
	}

	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();

	pLgdInfo->m_lnkSingleLgdInfo[0]->m_strTx = pLangInfo->GetText(211);
	pLgdInfo->m_lnkSingleLgdInfo[1]->m_strTx = pLangInfo->GetText(212);
	pLgdInfo->m_lnkSingleLgdInfo[2]->m_strTx = pLangInfo->GetText(215);
	pLgdInfo->m_lnkSingleLgdInfo[3]->m_strTx = pLangInfo->GetText(214);
	pLgdInfo->m_lnkSingleLgdInfo[4]->m_strTx = pLangInfo->GetText(213);

	return;
}
