// 【交接】 GeneralPcr\RunProgressRecord.cpp
// 作用：RunProgressRecord。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CRunProgressRecord、Empty。
#include "StdAfx.h"
#include "RunProgressRecord.h"

// 函数 CRunProgressRecord::CRunProgressRecord
// 作用：执行CRunProgressRecord。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CRunProgressRecord::CRunProgressRecord(void)
{
	m_iPageId = -1;
	m_iSegId = 0; 
	m_iStepId = 0;
	m_iCycleId = 0;
	m_strFilePath.Empty();
	m_strSN.Empty();

	m_ttStart = 0;
	m_fMeltStartTem = 0;
	m_fMeltEndTem = 0;
	m_fPowerOffTem = 0;
}

// 函数 CRunProgressRecord::~CRunProgressRecord
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CRunProgressRecord::~CRunProgressRecord(void)
{

}

// 函数 CRunProgressRecord::CRunProgressRecord
// 作用：执行CRunProgressRecord。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CRunProgressRecord::CRunProgressRecord(const CRunProgressRecord& info)
{
	m_iPageId = info.m_iPageId;
	m_iSegId = info.m_iSegId; 
	m_iStepId = info.m_iStepId;
	m_iCycleId = info.m_iCycleId;
	m_strFilePath = info.m_strFilePath;
	m_strSN = info.m_strSN;

	m_ttStart = info.m_ttStart;
	m_fMeltStartTem = info.m_fMeltStartTem;
	m_fMeltEndTem = info.m_fMeltEndTem;
	m_fPowerOffTem = info.m_fPowerOffTem;
}

void CRunProgressRecord::operator=(const CRunProgressRecord& info)
{
	m_iPageId = info.m_iPageId;
	m_iSegId = info.m_iSegId; 
	m_iStepId = info.m_iStepId;
	m_iCycleId = info.m_iCycleId;
	m_strFilePath = info.m_strFilePath;
	m_strSN = info.m_strSN;

	m_ttStart = info.m_ttStart;
	m_fMeltStartTem = info.m_fMeltStartTem;
	m_fMeltEndTem = info.m_fMeltEndTem;
	m_fPowerOffTem = info.m_fPowerOffTem;
}




