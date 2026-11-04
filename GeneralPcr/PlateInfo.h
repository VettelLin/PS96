// 【交接】 GeneralPcr\PlateInfo.h
// 作用：PlateInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CPlateInfo。
#pragma once

//保存孔板孔位绘制参数

class CPlateInfo
{
public:
	// 函数 CPlateInfo
	// 作用：执行CPlateInfo。
	// 参数：无。
	// 返回：没有返回值。
	CPlateInfo(void);
	// 函数 ~CPlateInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPlateInfo(void);

	// 函数 CPlateInfo
	// 作用：执行CPlateInfo。
	// 参数：info。
	// 返回：没有返回值。
	CPlateInfo(const CPlateInfo& info);
	void operator=(const CPlateInfo& info);

public:
	BOOL m_bSelected;	//孔位是否选中
};

