// 【交接】 GeneralPcr\HoleColorInfo.h
// 作用：HoleColorInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CHoleColorInfo。
#pragma once

#include <GdiPlus.h>
using namespace Gdiplus;

class CHoleColorInfo
{
public:
	// 函数 CHoleColorInfo
	// 作用：执行CHoleColorInfo。
	// 参数：无。
	// 返回：没有返回值。
	CHoleColorInfo(void);
	// 函数 ~CHoleColorInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CHoleColorInfo(void);

	// 函数 CHoleColorInfo
	// 作用：执行CHoleColorInfo。
	// 参数：info。
	// 返回：没有返回值。
	CHoleColorInfo(const CHoleColorInfo& info);
	void operator=(const CHoleColorInfo& info);

public:
	Color m_clrFrame;	//边框颜色
	Color m_clrFill;	//填充颜色
	COLORREF m_clrTxUnSelected;	//未选中状态文字颜色
	COLORREF m_clrTxSelected;	//选中状态文字颜色
};

