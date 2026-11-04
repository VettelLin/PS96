// 【交接】 GeneralPcr\ArrowInfo.h
// 作用：ArrowInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CArrowInfo、CalcPtData。
#pragma once

#include <GdiPlus.h>

using namespace Gdiplus;

//箭头样式：填充、左右两边
typedef enum ArrowStyle{
	EAS_FILL,EAS_LEFTRIGHT
}EARROWSTYLE;

class CArrowInfo
{
public:
	// 函数 CArrowInfo
	// 作用：执行CArrowInfo。
	// 参数：无。
	// 返回：没有返回值。
	CArrowInfo(void);
	// 函数 ~CArrowInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CArrowInfo(void);

	// 函数 CArrowInfo
	// 作用：执行CArrowInfo。
	// 参数：arrowInfo。
	// 返回：没有返回值。
	CArrowInfo(const CArrowInfo& arrowInfo);
	void operator=(const CArrowInfo& arrowInfo);

	// 函数 CalcPtData
	// 作用：计算CalcPtData。
	// 参数：rect：矩形区域。
	// 返回：没有返回值。
	void CalcPtData(CRect rect);

public:
	int m_arrowW; //右侧箭头的宽度
	int m_arrowH; //右侧箭头的高度
	int m_arrowRightIndent;	//箭头右侧缩进

	int m_iLineW;	//线条宽度

	Color m_clrArrow;	//箭头填充颜色
	Color m_clrLineNormal;	//普通状态箭头线条颜色，向下
	Color m_clrLineDropDown;	//下拉状态箭头线条颜色，向上

	Point m_aryPtTriangle[3];	//填充模式-三角形的三个点，线条模式-普通状态两条线对应的三个点,向下
	Point m_aryPtTriangleDropDown[3];	//填充模式-三角形的三个点，线条模式-下拉状态两条线对应的三个点，向上

	Point m_aryPtTriangleLeft[3];	//填充模式-三角形的三个点，线条模式-普通状态两条线对应的三个点，向左
	Point m_aryPtTriangleRight[3];	//填充模式-三角形的三个点，线条模式-下拉状态两条线对应的三个点，向右

	EARROWSTYLE m_eArrowStyle;
};

