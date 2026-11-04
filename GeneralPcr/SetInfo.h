// 【交接】 GeneralPcr\SetInfo.h
// 作用：SetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSetInfo。
#pragma once

#include "SelfDefType.h"

class CSetInfo
{
public:
	// 函数 CSetInfo
	// 作用：执行CSetInfo。
	// 参数：无。
	// 返回：没有返回值。
	CSetInfo(void);
	// 函数 ~CSetInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSetInfo(void);

	// 函数 CSetInfo
	// 作用：执行CSetInfo。
	// 参数：setInfo。
	// 返回：没有返回值。
	CSetInfo(const CSetInfo& setInfo);
	void operator=(const CSetInfo& setInfo);

public:
	ESAMSORTWAY m_eSamSortWay;
	ESAMSORTDIRECTION m_eSamSortDirection;
};

