// 【交接】 PCRCtrlLib\PCRAlgorithmLib\PeakAmlCheckParam.h
// 作用：PeakAmlCheckParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：__declspec、CPeakAmlCheckParam。
#pragma once
class __declspec(dllexport) CPeakAmlCheckParam
{
public:
	// 函数 CPeakAmlCheckParam
	// 作用：执行CPeakAmlCheckParam。
	// 参数：无。
	// 返回：没有返回值。
	CPeakAmlCheckParam(void);
	// 函数 ~CPeakAmlCheckParam
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPeakAmlCheckParam(void);

	// 函数 CPeakAmlCheckParam
	// 作用：执行CPeakAmlCheckParam。
	// 参数：param。
	// 返回：没有返回值。
	CPeakAmlCheckParam(const CPeakAmlCheckParam& param);
	void operator=(const CPeakAmlCheckParam& param);
	BOOL operator==(const CPeakAmlCheckParam& param);

public:
	double m_dStdThreshold;	/*!< 曲线标准差阈值 */
	double m_dRatioThreshold;	/*!< 曲线尾端信号值除以首端信号值 阈值 */

	double m_dCrestBkRatio;	/*!< 曲线二阶导数最大值除以基线值计算出比值系数R,该参数为R的阈值 */
	int m_bkCalcDotNum;	/*!< 曲线二阶导数最大值除以基线值计算出比值系数R,选取前bkCalcDotNum个数据点的Y值均值作为基线值 */

	int m_start;	/*!<比较二阶导数最大值和基线段二阶倒数数值，基线段起点 */
	int m_forwardNum;	/*!<比较二阶导数最大值和基线段二阶倒数数值，二阶导数最大值位置前移newForwardNum个点作为基线段终点 */
	float m_sdMultiples;	/*!<比较二阶导数最大值和基线段二阶倒数数值，前者是否达到后者均值加上newStdNum倍SD */
	int m_iForeAvgMax; // 前端均值的最大值限制
};

