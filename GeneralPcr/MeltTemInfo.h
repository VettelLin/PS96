// 【交接】 GeneralPcr\MeltTemInfo.h
// 作用：MeltTemInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMeltTemInfo。
#pragma once
class AFX_EXT_CLASS CMeltTemInfo
{
public:
	// 函数 CMeltTemInfo
	// 作用：执行CMeltTemInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMeltTemInfo(void);
	// 函数 ~CMeltTemInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMeltTemInfo(void);

	// 函数 CMeltTemInfo
	// 作用：执行CMeltTemInfo。
	// 参数：meltTemInfo。
	// 返回：没有返回值。
	CMeltTemInfo(const CMeltTemInfo& meltTemInfo);
	void operator=(const CMeltTemInfo& meltTemInfo);

public:
	double m_dTargetTem;///< 目标温度值
	double m_dPeltier1Tem;    ///< 第1路温度数据
	double m_dPeltier2Tem;	 ///< 第2路温度数据
	double m_dPeltier3Tem;	 ///< 第3路温度数据

	double m_dPeltier1StartTem; ///< 第1路温度整板扫描起点温度值
	double m_dPeltier1EndTem;   ///< 第1路温度整板扫描终点温度值
	double m_dPeltier2StartTem; ///< 第2路温度整板扫描起点温度值
	double m_dPeltier2EndTem;   ///< 第2路温度整板扫描终点温度值
	double m_dPeltier3StartTem; ///< 第3路温度整板扫描起点温度值
	double m_dPeltier3EndTem;   ///< 第3路温度整板扫描终点温度值
};

