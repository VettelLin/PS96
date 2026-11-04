// 【交接】 PCRCtrlLib\VolumeDelayParam.h
// 作用：VolumeDelayParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CVolumeDelayParam。
#pragma once
class CVolumeDelayParam
{
public:
	// 函数 CVolumeDelayParam
	// 作用：执行CVolumeDelayParam。
	// 参数：无。
	// 返回：没有返回值。
	CVolumeDelayParam(void);
	// 函数 ~CVolumeDelayParam
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CVolumeDelayParam(void);

	// 函数 CVolumeDelayParam
	// 作用：执行CVolumeDelayParam。
	// 参数：info。
	// 返回：没有返回值。
	CVolumeDelayParam(const CVolumeDelayParam& info);
	void operator=(const CVolumeDelayParam& info);

public:
	double m_dUpTemThre;
	double m_dDownTemThre;
	double m_dUpK;
	double m_dDownK;
	double m_dBaseVolume;
};

