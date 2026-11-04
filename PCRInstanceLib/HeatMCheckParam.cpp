// 【交接】 PCRInstanceLib\HeatMCheckParam.cpp
// 作用：HeatMCheckParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CHeatMCheckParam、_T、GetPeltierCheckParam、IsNeedCheck、IsCheck、ResetCheckResult、Empty、AddCheckResult。
#include "StdAfx.h"
#include "HeatMCheckParam.h"


// 函数 CHeatMCheckParam::CHeatMCheckParam
// 作用：执行CHeatMCheckParam。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CHeatMCheckParam::CHeatMCheckParam(void)
{
	m_strChkRst = _T("");
}

// 函数 CHeatMCheckParam::~CHeatMCheckParam
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHeatMCheckParam::~CHeatMCheckParam(void)
{

}

// 函数 CHeatMCheckParam::CHeatMCheckParam
// 作用：执行CHeatMCheckParam。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CHeatMCheckParam::CHeatMCheckParam(const CHeatMCheckParam& info)
{
	m_peltier1ChkParam = info.m_peltier1ChkParam;
	m_peltier2ChkParam = info.m_peltier2ChkParam;
	m_peltier3ChkParam = info.m_peltier3ChkParam;
	m_strChkRst = info.m_strChkRst;
}

void CHeatMCheckParam::operator=(const CHeatMCheckParam& info)
{
	m_peltier1ChkParam = info.m_peltier1ChkParam;
	m_peltier2ChkParam = info.m_peltier2ChkParam;
	m_peltier3ChkParam = info.m_peltier3ChkParam;
	m_strChkRst = info.m_strChkRst;
}

// 函数 CHeatMCheckParam::GetPeltierCheckParam
// 作用：读取GetPeltierCheckParam。
// 参数：iPeltierId：整数。
// 返回：返回指针 CPeltierCheckParam*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPeltierCheckParam* CHeatMCheckParam::GetPeltierCheckParam(int iPeltierId)
{
	if(iPeltierId < 0 || iPeltierId > 2)
	{
		return NULL;
	}
	
	if(0 == iPeltierId)
	{
		return &m_peltier1ChkParam;
	}
	else if(1 == iPeltierId)
	{
		return &m_peltier2ChkParam;
	}
	else if(2 == iPeltierId)
	{
		return &m_peltier3ChkParam;
	}
}

// 函数 CHeatMCheckParam::IsNeedCheck
// 作用：判断IsNeedCheck是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 IsCheck。
BOOL CHeatMCheckParam::IsNeedCheck()
{
	return m_peltier1ChkParam.IsCheck() || m_peltier2ChkParam.IsCheck() || m_peltier3ChkParam.IsCheck();
}

// 函数 CHeatMCheckParam::ResetCheckResult
// 作用：更新或清除ResetCheckResult。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
void CHeatMCheckParam::ResetCheckResult()
{
	m_strChkRst.Empty();
}

// 函数 CHeatMCheckParam::AddCheckResult
// 作用：创建或加入AddCheckResult。
// 参数：strData：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
void CHeatMCheckParam::AddCheckResult(CString strData)
{
	m_strChkRst += _T("\r\n");
	m_strChkRst += strData;
	return;
}

// 函数 CHeatMCheckParam::GetCheckResult
// 作用：读取GetCheckResult。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CHeatMCheckParam::GetCheckResult()
{
	return m_strChkRst;
}

// 函数 CHeatMCheckParam::IsSuccessful
// 作用：判断IsSuccessful是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 IsEmpty。
BOOL CHeatMCheckParam::IsSuccessful()
{
	return m_strChkRst.IsEmpty();
}




