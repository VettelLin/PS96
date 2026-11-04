// 【交接】 GeneralPcr\Ps96IvdSet.h
// 作用：Ps96IvdSet。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPs96IvdSet、IsExportResultHorizontal、SetResultExportOrder、GetResultExportOrder、SetHospitalName、GetHospitalName。
#pragma once

typedef enum RstExportOrder{
	EREO_HORI = 1,EREO_VERT
}ERSTEXPORTORDER;

class CPs96IvdSet
{
public:
	// 函数 CPs96IvdSet
	// 作用：执行CPs96IvdSet。
	// 参数：无。
	// 返回：没有返回值。
	CPs96IvdSet(void);
	// 函数 ~CPs96IvdSet
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPs96IvdSet(void);

	// 函数 CPs96IvdSet
	// 作用：执行CPs96IvdSet。
	// 参数：info。
	// 返回：没有返回值。
	CPs96IvdSet(const CPs96IvdSet& info);
	void operator=(const CPs96IvdSet& info);
	BOOL operator==(const CPs96IvdSet& info);
	BOOL operator!=(const CPs96IvdSet& info);

	// 函数 IsExportResultHorizontal
	// 作用：判断IsExportResultHorizontal是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsExportResultHorizontal();
	
	// 函数 SetResultExportOrder
	// 作用：设置SetResultExportOrder。
	// 参数：eData。
	// 返回：没有返回值。
	void SetResultExportOrder(ERSTEXPORTORDER eData);
	// 函数 SetResultExportOrder
	// 作用：设置SetResultExportOrder。
	// 参数：bHori：是或否。
	// 返回：没有返回值。
	void SetResultExportOrder(BOOL bHori);
	// 函数 GetResultExportOrder
	// 作用：读取GetResultExportOrder。
	// 参数：无。
	// 返回：返回 ERSTEXPORTORDER。
	ERSTEXPORTORDER GetResultExportOrder();

	// 函数 SetHospitalName
	// 作用：设置SetHospitalName。
	// 参数：strData：字符串。
	// 返回：没有返回值。
	void SetHospitalName(CString strData);
	// 函数 GetHospitalName
	// 作用：读取GetHospitalName。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetHospitalName();

public:
	ERSTEXPORTORDER m_eRstExportOrder;
	CString m_strHospitalName;
};

