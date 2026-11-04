// 【交接】 PCRCtrlLib\PCRAlgorithmLib\PeakAmlCheckParam.cpp
// 作用：起峰判断使用的固定门槛：标准差 45、前后段倍数 1.1、尖峰背景比 0.001、基线倍数 1.5。
// 先看这些函数：CPeakAmlCheckParam。
#include "StdAfx.h"
#include "PeakAmlCheckParam.h"


// 起峰判断的全部门槛。IsPeakAml 直接使用这些默认值，界面上不能改。
// 标准差 45：整条原始曲线的样本标准差小于或等于 45，不算起峰。
// 前后段倍数 1.1：后段平均值必须大于前段平均值的 1.1 倍。
// 尖峰背景比 0.001：尖峰处二阶导绝对值 / 原始曲线前 3 点平均值，必须大于 0.001。
// 背景点数 3：上面这个比值的分母取原始曲线最前面 3 个点。
// 基线起点 1、尖峰前移 3：二阶导基线段从第 1 个点算到尖峰前第 3 个点。
// 标准差倍数 1.5：尖峰处二阶导必须大于基线段均值 + 1.5 倍基线段标准差。
// m_iForeAvgMax 初始值 45。第一次前后段比较前会被改成当前点数，补判时改成尖峰序号减 2。
CPeakAmlCheckParam::CPeakAmlCheckParam(void)
{
	m_dStdThreshold = 45;
	m_dRatioThreshold = 1.1;

	m_dCrestBkRatio = 0.001; 
	m_bkCalcDotNum = 3;

	m_start = 1;
	m_forwardNum = 3;
	m_sdMultiples = 1.5;
	m_iForeAvgMax = 45;
}


// 函数 CPeakAmlCheckParam::~CPeakAmlCheckParam
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPeakAmlCheckParam::~CPeakAmlCheckParam(void)
{
}

// 函数 CPeakAmlCheckParam::CPeakAmlCheckParam
// 作用：执行CPeakAmlCheckParam。
// 参数：param。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPeakAmlCheckParam::CPeakAmlCheckParam(const CPeakAmlCheckParam& param)
{
	m_dStdThreshold = param.m_dStdThreshold;
	m_dRatioThreshold = param.m_dRatioThreshold;

	m_dCrestBkRatio = param.m_dCrestBkRatio; 
	m_bkCalcDotNum = param.m_bkCalcDotNum;

	m_start = param.m_start;
	m_forwardNum = param.m_forwardNum;
	m_sdMultiples = param.m_sdMultiples;
}

void CPeakAmlCheckParam::operator=(const CPeakAmlCheckParam& param)
{
	m_dStdThreshold = param.m_dStdThreshold;
	m_dRatioThreshold = param.m_dRatioThreshold;

	m_dCrestBkRatio = param.m_dCrestBkRatio; 
	m_bkCalcDotNum = param.m_bkCalcDotNum;

	m_start = param.m_start;
	m_forwardNum = param.m_forwardNum;
	m_sdMultiples = param.m_sdMultiples;
}

BOOL CPeakAmlCheckParam::operator==(const CPeakAmlCheckParam& param)
{
	return m_dStdThreshold == param.m_dStdThreshold && 
	m_dRatioThreshold == param.m_dRatioThreshold && 
	m_dCrestBkRatio == param.m_dCrestBkRatio &&  
	m_bkCalcDotNum == param.m_bkCalcDotNum && 
	m_start == param.m_start && 
	m_forwardNum == param.m_forwardNum && 
	m_sdMultiples == param.m_sdMultiples;
}

