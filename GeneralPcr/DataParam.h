// 【交接】 GeneralPcr\DataParam.h
// 作用：DataParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CDataParam、DataFilter。
#pragma once

typedef enum DataType{
	EDT2_NONE,EDT2_INT,EDT2_DOUBLE,EDT2_STRING
}EDATATYPE;

class CDataParam
{
public:
	// 函数 CDataParam
	// 作用：执行CDataParam。
	// 参数：无。
	// 返回：没有返回值。
	CDataParam(void);
	// 函数 CDataParam
	// 作用：执行CDataParam。
	// 参数：eDtType；iDpd：整数；bData：是或否。
	// 返回：没有返回值。
	CDataParam(EDATATYPE eDtType,int iDpd,BOOL bData);
	// 函数 ~CDataParam
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CDataParam(void);

	// 函数 CDataParam
	// 作用：执行CDataParam。
	// 参数：info。
	// 返回：没有返回值。
	CDataParam(const CDataParam& info);
	void operator=(const CDataParam& info);

	// 函数 DataFilter
	// 作用：执行DataFilter。
	// 参数：strData：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DataFilter(CString& strData);

public:
	EDATATYPE m_eDataType;
	int m_iDpd;	//小数点位数
	BOOL m_bUseDataFilter;	//是否使用数据过滤功能
};

