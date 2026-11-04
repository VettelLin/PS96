// 【交接】 GeneralPcr\CalibAutoSetInfo.h
// 作用：CalibAutoSetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCalibAutoSetInfo。
#pragma once

#include "SelfDefType.h"

typedef enum DilutionDirection{
	EDD_INCREASE,EDD_DECREASE
}EDILUTION_DIRECTION;

class CCalibAutoSetInfo
{
public:
	// 函数 CCalibAutoSetInfo
	// 作用：执行CCalibAutoSetInfo。
	// 参数：无。
	// 返回：没有返回值。
	CCalibAutoSetInfo(void);
	// 函数 ~CCalibAutoSetInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CCalibAutoSetInfo(void);

	// 函数 CCalibAutoSetInfo
	// 作用：执行CCalibAutoSetInfo。
	// 参数：calibAutoSetInfo。
	// 返回：没有返回值。
	CCalibAutoSetInfo(const CCalibAutoSetInfo& calibAutoSetInfo);
	void operator=(const CCalibAutoSetInfo& calibAutoSetInfo);

public:
	int m_selectHoleNum;	//选中孔位个数
	int m_repeatNum;	//复管个数
	double m_dStartDensity;
	EDILUTION_DIRECTION m_eDilutionDirection;
	int m_dilutionMulitiples;	//稀释倍数
	ESAMSORTWAY m_eSamSortWay;
};

