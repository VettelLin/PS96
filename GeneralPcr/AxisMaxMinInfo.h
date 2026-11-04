// 【交接】 GeneralPcr\AxisMaxMinInfo.h
// 作用：AxisMaxMinInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CAxisMaxMinInfo。
#pragma once
class CAxisMaxMinInfo
{
public:
	// 函数 CAxisMaxMinInfo
	// 作用：执行CAxisMaxMinInfo。
	// 参数：无。
	// 返回：没有返回值。
	CAxisMaxMinInfo(void);
	// 函数 ~CAxisMaxMinInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CAxisMaxMinInfo(void);

	// 函数 CAxisMaxMinInfo
	// 作用：执行CAxisMaxMinInfo。
	// 参数：axisMaxMinInfo。
	// 返回：没有返回值。
	CAxisMaxMinInfo(const CAxisMaxMinInfo& axisMaxMinInfo);
	void operator=(const CAxisMaxMinInfo& axisMaxMinInfo);

public:
	double m_dXMax;
	double m_dXMin;
	double m_dYMax;
	double m_dYMin;
};

