// 【交接】 GeneralPcr\SingleLgdInfo.h
// 作用：SingleLgdInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSingleLgdInfo。
#pragma once

#include<GdiPlus.h>
using namespace Gdiplus;

class CSingleLgdInfo
{
public:
	// 函数 CSingleLgdInfo
	// 作用：执行CSingleLgdInfo。
	// 参数：无。
	// 返回：没有返回值。
	CSingleLgdInfo(void);
	// 函数 ~CSingleLgdInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSingleLgdInfo(void);

	// 函数 CSingleLgdInfo
	// 作用：执行CSingleLgdInfo。
	// 参数：info。
	// 返回：没有返回值。
	CSingleLgdInfo(const CSingleLgdInfo& info);
	void operator=(const CSingleLgdInfo& info);

public:
	Color m_clrFrame;
	Color m_clrFill;

	int m_pxFrameW;
	CString m_strTx;
};

