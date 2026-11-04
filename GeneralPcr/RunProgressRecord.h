// 【交接】 GeneralPcr\RunProgressRecord.h
// 作用：RunProgressRecord。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CRunProgressRecord。
#pragma once

class CRunProgressRecord
{
public:
	// 函数 CRunProgressRecord
	// 作用：执行CRunProgressRecord。
	// 参数：无。
	// 返回：没有返回值。
	CRunProgressRecord(void);
	// 函数 ~CRunProgressRecord
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CRunProgressRecord(void);

	// 函数 CRunProgressRecord
	// 作用：执行CRunProgressRecord。
	// 参数：info。
	// 返回：没有返回值。
	CRunProgressRecord(const CRunProgressRecord& info);
	void operator=(const CRunProgressRecord& info);

public:
	int m_iPageId;	//页面ID
	int m_iSegId;
	int m_iStepId;
	int m_iCycleId;
	CString m_strFilePath;	//实验文件保存路径
	CString m_strSN;	//仪器序列号

	time_t m_ttStart;	//实验开始时间
	float m_fMeltStartTem;	//熔曲步骤起始温度
	float m_fMeltEndTem;	//熔曲步骤目标温度
	float m_fPowerOffTem;	//记录已经完成数据保存的熔曲温度点
};

