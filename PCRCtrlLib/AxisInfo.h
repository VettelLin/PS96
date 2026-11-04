// 【交接】 PCRCtrlLib\AxisInfo.h
// 作用：AxisInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CAxisInfo、CalculateLogValaue。
#pragma once

class AFX_EXT_CLASS CAxisInfo
{
public:
	// 函数 CAxisInfo
	// 作用：执行CAxisInfo。
	// 参数：无。
	// 返回：没有返回值。
	CAxisInfo(void);
	// 函数 ~CAxisInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CAxisInfo(void);

	// 函数 CAxisInfo
	// 作用：执行CAxisInfo。
	// 参数：axisInfo。
	// 返回：没有返回值。
	CAxisInfo(const CAxisInfo& axisInfo);
	void operator=(const CAxisInfo& axisInfo);

	BOOL operator==(const CAxisInfo& axisInfo);

	// 函数 CalculateLogValaue
	// 作用：计算CalculateLogValaue。
	// 参数：无。
	// 返回：返回 CAxisInfo。
	CAxisInfo CalculateLogValaue();

public:
	double m_dXMin;
	double m_dXMax;
	double m_dYMin;
	double m_dYMax;
};

