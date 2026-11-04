// 【交接】 GeneralPcr\InterfaceB.h
// 作用：InterfaceB。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInterfaceB、SetNewPrjBaseInfo。
#pragma once

class CInterfaceB
{
public:
	// 函数 CInterfaceB
	// 作用：执行CInterfaceB。
	// 参数：无。
	// 返回：没有返回值。
	CInterfaceB(void);
	// 函数 ~CInterfaceB
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CInterfaceB(void);

	// 函数 SetNewPrjBaseInfo
	// 作用：设置SetNewPrjBaseInfo。
	// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
	// 返回：没有返回值。
	virtual void SetNewPrjBaseInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/) = 0;
};

