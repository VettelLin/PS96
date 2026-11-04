// 【交接】 GeneralPcr\EditModeAbs.h
// 作用：EditModeAbs。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CEditModeAbs、SetEditMode。
#pragma once

#include "EditModeType.h"

class CEditModeAbs
{
public:
	// 函数 CEditModeAbs
	// 作用：执行CEditModeAbs。
	// 参数：无。
	// 返回：没有返回值。
	CEditModeAbs(void);
	// 函数 ~CEditModeAbs
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CEditModeAbs(void);

	// 函数 CEditModeAbs
	// 作用：执行CEditModeAbs。
	// 参数：editMode。
	// 返回：没有返回值。
	CEditModeAbs(const CEditModeAbs& editMode);
	void operator=(const CEditModeAbs& editMode);

	// 函数 SetEditMode
	// 作用：设置SetEditMode。
	// 参数：eExpEditMode。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SetEditMode(EEXPEDITMODE eExpEditMode) = 0;

public:
	EEXPEDITMODE m_eExpEditMode;
};

