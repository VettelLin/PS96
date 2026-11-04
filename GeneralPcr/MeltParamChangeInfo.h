// 【交接】 GeneralPcr\MeltParamChangeInfo.h
// 作用：MeltParamChangeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMeltParamChangeInfo、GetBeChanged。
#pragma once
class CMeltParamChangeInfo
{
public:
	// 函数 CMeltParamChangeInfo
	// 作用：执行CMeltParamChangeInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMeltParamChangeInfo(void);
	// 函数 ~CMeltParamChangeInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMeltParamChangeInfo(void);

	// 函数 CMeltParamChangeInfo
	// 作用：执行CMeltParamChangeInfo。
	// 参数：info。
	// 返回：没有返回值。
	CMeltParamChangeInfo(const CMeltParamChangeInfo& info);
	void operator=(const CMeltParamChangeInfo& info);

	// 函数 GetBeChanged
	// 作用：读取GetBeChanged。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeChanged();

public:
	BOOL m_bChanged;
	BOOL m_bMeltTemMinChanged;	//熔曲最低温度设置是否改变
	BOOL m_bMeltTemMaxChanged;	//熔曲最高温度设置是否改变
	BOOL m_bPeakHeightThreChanged;	//峰高阈值是否改变

	BOOL m_bCrvMeltPeakNeedRedraw;	//熔解峰值曲线是否需要重绘
	BOOL m_bRstLstNeedRedraw;	//结果列表是否需要重绘
};

