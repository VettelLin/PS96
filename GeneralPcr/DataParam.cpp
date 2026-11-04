// 【交接】 GeneralPcr\DataParam.cpp
// 作用：DataParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CDataParam、DataFilter、Find、GetLength、_ttof、_T、Format。
#include "StdAfx.h"
#include "DataParam.h"


// 函数 CDataParam::CDataParam
// 作用：执行CDataParam。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDataParam::CDataParam(void)
{
	m_eDataType = EDT2_NONE;
	m_iDpd = 0;
	m_bUseDataFilter = FALSE;
}

// 函数 CDataParam::CDataParam
// 作用：执行CDataParam。
// 参数：eDtType；iDpd：整数；bData：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDataParam::CDataParam(EDATATYPE eDtType,int iDpd,BOOL bData)
{
	m_eDataType = eDtType;
	m_iDpd = iDpd;
	m_bUseDataFilter = bData;
}

// 函数 CDataParam::~CDataParam
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDataParam::~CDataParam(void)
{

}

// 函数 CDataParam::CDataParam
// 作用：执行CDataParam。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDataParam::CDataParam(const CDataParam& info)
{
	m_eDataType = info.m_eDataType;
	m_iDpd = info.m_iDpd;
	m_bUseDataFilter = info.m_bUseDataFilter;
}

void CDataParam::operator=(const CDataParam& info)
{
	m_eDataType = info.m_eDataType;
	m_iDpd = info.m_iDpd;
	m_bUseDataFilter = info.m_bUseDataFilter;
}

// 函数 CDataParam::DataFilter
// 作用：执行DataFilter。
// 参数：strData：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Find、_T、GetLength、_ttof、Format。
int CDataParam::DataFilter(CString& strData)
{
	if(!m_bUseDataFilter)
	{
		return 1;
	}

	if(EDT2_DOUBLE != m_eDataType)
	{
		return -1;
	}

	int iDPd = 0;
	int iDotIndex = strData.Find(_T('.'));
	if(-1 != iDotIndex)
	{
		iDPd = strData.GetLength() - iDotIndex - 1;
	}

	if(iDPd == m_iDpd)
	{
		return 2;
	}

	double dData = _ttof(strData);
	CString strFormat = _T("");
	strFormat.Format(_T("%%.%dlf"),m_iDpd);
	strData.Format(strFormat,dData);

	return 0;
}
