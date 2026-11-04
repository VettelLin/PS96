// 【交接】 PCRInstanceLib\InstancePS384.h
// 作用：InstancePS384。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInstancePS384、ReadAllFLUData、InitStructurePara、ReadFLUData384。
#pragma once

#include "InstancePS96.h"

class AFX_EXT_CLASS CInstancePS384 : public CInstancePS96
{
public:
	// 函数 CInstancePS384
	// 作用：执行CInstancePS384。
	// 参数：pComPort：指针，指向调用方传入的对象；strVersion：字符串。
	// 返回：没有返回值。
	CInstancePS384(CSerialPortPCR* pComPort, CString strVersion);
	// 函数 ~CInstancePS384
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CInstancePS384(void);

public:
	// 函数 ReadAllFLUData
	// 作用：读取ReadAllFLUData。
	// 参数：pAryData：指针，指向调用方传入的对象；iChanNum：整数。
	// 返回：返回是或否。
	virtual BOOL ReadAllFLUData(CUIntArray* pAryData,int iChanNum);

protected:
	// 函数 InitStructurePara
	// 作用：初始化InitStructurePara。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitStructurePara();
	// 函数 ReadFLUData384
	// 作用：读取ReadFLUData384。
	// 参数：arrayData；cChannel；cIndex；cFrmIndex。
	// 返回：返回是或否。
	BOOL ReadFLUData384(CUIntArray& arrayData, BYTE cChannel, BYTE cIndex, BYTE cFrmIndex=1);

};

