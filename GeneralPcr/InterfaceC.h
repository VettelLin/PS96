// 【交接】 GeneralPcr\InterfaceC.h
// 作用：InterfaceC。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInterfaceC、SetPlateSelectedSiteSamInfo。
#pragma once

#include "SelfDefType.h"

class CInterfaceC
{
public:
	// 函数 CInterfaceC
	// 作用：执行CInterfaceC。
	// 参数：无。
	// 返回：没有返回值。
	CInterfaceC(void);
	// 函数 ~CInterfaceC
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CInterfaceC(void);

	// 函数 SetPlateSelectedSiteSamInfo
	// 作用：设置SetPlateSelectedSiteSamInfo。
	// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
	// 返回：没有返回值。
	virtual void SetPlateSelectedSiteSamInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData = 0,double dData = 0) = 0;
};

