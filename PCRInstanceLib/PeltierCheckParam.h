// 【交接】 PCRInstanceLib\PeltierCheckParam.h
// 作用：PeltierCheckParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPeltierCheckParam、IsCheck、GetTemperatureThreshold、GetRiseTemError、GetDropTemError、GetTemRiseDropRange、GetRiseTimeSec、GetDropTimeSec。
#pragma once
class AFX_EXT_CLASS CPeltierCheckParam
{
public:
	// 函数 CPeltierCheckParam
	// 作用：执行CPeltierCheckParam。
	// 参数：无。
	// 返回：没有返回值。
	CPeltierCheckParam(void);
	// 函数 ~CPeltierCheckParam
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPeltierCheckParam(void);

	// 函数 CPeltierCheckParam
	// 作用：执行CPeltierCheckParam。
	// 参数：info。
	// 返回：没有返回值。
	CPeltierCheckParam(const CPeltierCheckParam& info);
	void operator=(const CPeltierCheckParam& info);

	// 函数 IsCheck
	// 作用：判断IsCheck是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheck();
	// 函数 GetTemperatureThreshold
	// 作用：读取GetTemperatureThreshold。
	// 参数：无。
	// 返回：返回一个小数。
	double GetTemperatureThreshold();
	// 函数 GetRiseTemError
	// 作用：读取GetRiseTemError。
	// 参数：无。
	// 返回：返回一个小数。
	double GetRiseTemError();
	// 函数 GetDropTemError
	// 作用：读取GetDropTemError。
	// 参数：无。
	// 返回：返回一个小数。
	double GetDropTemError();
	// 函数 GetTemRiseDropRange
	// 作用：读取GetTemRiseDropRange。
	// 参数：无。
	// 返回：返回一个小数。
	double GetTemRiseDropRange();
	// 函数 GetRiseTimeSec
	// 作用：读取GetRiseTimeSec。
	// 参数：无。
	// 返回：返回一个小数。
	float  GetRiseTimeSec();
	// 函数 GetDropTimeSec
	// 作用：读取GetDropTimeSec。
	// 参数：无。
	// 返回：返回一个小数。
	float  GetDropTimeSec();

protected:
	BOOL m_bCheck;
	double m_dTemThre;
	double m_dRiseTemError;	//升温温度误差
	double m_dDropTemError;	//降温温度误差
	double m_dTemRiseDropRange;	//升降温幅度
	float m_fRiseTimeSec;	//升温时间
	float m_fDropTimeSec;	//降温时间
};

