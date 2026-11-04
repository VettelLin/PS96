// 【交接】 GeneralPcr\SamLst.h
// 作用：SamLst。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSamLst、DrawBody。
#pragma once

#include "FtSetDensity.h"
#include "MyLstCtrl.h"

class CSamLst: public CMyLstCtrl,public CFtSetDensity
{
public:
	// 函数 CSamLst
	// 作用：执行CSamLst。
	// 参数：无。
	// 返回：没有返回值。
	CSamLst(void);
	// 函数 ~CSamLst
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSamLst(void);

	// 函数 DrawBody
	// 作用：绘制DrawBody。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int DrawBody(CDC* pDC);

};

