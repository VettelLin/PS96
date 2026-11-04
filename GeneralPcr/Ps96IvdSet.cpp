// 【交接】 GeneralPcr\Ps96IvdSet.cpp
// 作用：Ps96IvdSet。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPs96IvdSet、Empty、IsExportResultHorizontal、SetResultExportOrder、GetResultExportOrder、SetHospitalName、GetHospitalName。
#include "StdAfx.h"
#include "Ps96IvdSet.h"

// 函数 CPs96IvdSet::CPs96IvdSet
// 作用：执行CPs96IvdSet。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CPs96IvdSet::CPs96IvdSet(void)
{
	m_eRstExportOrder = EREO_VERT;
	m_strHospitalName.Empty();
}

// 函数 CPs96IvdSet::~CPs96IvdSet
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPs96IvdSet::~CPs96IvdSet(void)
{

}

// 函数 CPs96IvdSet::CPs96IvdSet
// 作用：执行CPs96IvdSet。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPs96IvdSet::CPs96IvdSet(const CPs96IvdSet& info)
{
	m_eRstExportOrder = info.m_eRstExportOrder;
	m_strHospitalName = info.m_strHospitalName;

	return;
}

void CPs96IvdSet::operator=(const CPs96IvdSet& info)
{
	m_eRstExportOrder = info.m_eRstExportOrder;
	m_strHospitalName = info.m_strHospitalName;

	return;
}

BOOL CPs96IvdSet::operator==(const CPs96IvdSet& info)
{
	return m_eRstExportOrder == info.m_eRstExportOrder && 
	m_strHospitalName == info.m_strHospitalName;
}

BOOL CPs96IvdSet::operator!=(const CPs96IvdSet& info)
{
	return m_eRstExportOrder != info.m_eRstExportOrder || 
		   m_strHospitalName != info.m_strHospitalName;
}

// 函数 CPs96IvdSet::IsExportResultHorizontal
// 作用：判断IsExportResultHorizontal是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CPs96IvdSet::IsExportResultHorizontal()
{
	return EREO_HORI == m_eRstExportOrder;
}

// 函数 CPs96IvdSet::SetResultExportOrder
// 作用：设置SetResultExportOrder。
// 参数：eData。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPs96IvdSet::SetResultExportOrder(ERSTEXPORTORDER eData)
{
	m_eRstExportOrder = eData;
	return;
}

// 函数 CPs96IvdSet::SetResultExportOrder
// 作用：设置SetResultExportOrder。
// 参数：bHori：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPs96IvdSet::SetResultExportOrder(BOOL bHori)
{
	if(bHori)
	{
		m_eRstExportOrder = EREO_HORI;
	}
	else
	{
		m_eRstExportOrder = EREO_VERT;
	}
	return;
}

// 函数 CPs96IvdSet::GetResultExportOrder
// 作用：读取GetResultExportOrder。
// 参数：无。
// 返回：返回 ERSTEXPORTORDER。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
ERSTEXPORTORDER CPs96IvdSet::GetResultExportOrder()
{
	return m_eRstExportOrder;
}

// 函数 CPs96IvdSet::SetHospitalName
// 作用：设置SetHospitalName。
// 参数：strData：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CPs96IvdSet::SetHospitalName(CString strData)
{
	m_strHospitalName = strData;
	return;
}

// 函数 CPs96IvdSet::GetHospitalName
// 作用：读取GetHospitalName。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CPs96IvdSet::GetHospitalName()
{
	return m_strHospitalName;
}
