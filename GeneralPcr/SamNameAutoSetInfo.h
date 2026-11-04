// 【交接】 GeneralPcr\SamNameAutoSetInfo.h
// 作用：SamNameAutoSetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSamNameAutoSetInfo。
#pragma once

#include "SelfDefType.h"

class CSamNameAutoSetInfo
{
public:
	// 函数 CSamNameAutoSetInfo
	// 作用：执行CSamNameAutoSetInfo。
	// 参数：无。
	// 返回：没有返回值。
	CSamNameAutoSetInfo(void);
	// 函数 ~CSamNameAutoSetInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSamNameAutoSetInfo(void);

	// 函数 CSamNameAutoSetInfo
	// 作用：执行CSamNameAutoSetInfo。
	// 参数：samIdAutoSetInfo。
	// 返回：没有返回值。
	CSamNameAutoSetInfo(const CSamNameAutoSetInfo& samIdAutoSetInfo);
	void operator=(const CSamNameAutoSetInfo& samIdAutoSetInfo);

public:
	CString m_strPrjName;
	CString m_strSamIdPrefix;
	int m_startValue;
	int m_interval;
	int m_bitNum;
	ESAMSORTWAY m_eSamSortWay;
};

