// 【交接】 GeneralPcr\LisSetInfo.h
// 作用：LisSetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CLisSetInfo。
#pragma once

typedef enum CheckWay{
	ECK_NONE,ECK_PARITYCHECK
}ECHEKCWAY;

class CLisSetInfo
{
public:
	// 函数 CLisSetInfo
	// 作用：执行CLisSetInfo。
	// 参数：无。
	// 返回：没有返回值。
	CLisSetInfo(void);
	// 函数 ~CLisSetInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLisSetInfo(void);

	// 函数 CLisSetInfo
	// 作用：执行CLisSetInfo。
	// 参数：lisSetInfo。
	// 返回：没有返回值。
	CLisSetInfo(const CLisSetInfo& lisSetInfo);
	void operator=(const CLisSetInfo& lisSetInfo);

public:
	BOOL m_bOpenLis;
	double m_dRecvWaitMaxSec;
	int m_maxTransferTimes;

	BOOL m_bUseCom;
	CString m_strComId;
	int m_dataNum;
	double m_dStopBit;
	int m_baudRate;

	CString m_strIpAddress;
	CString m_strPort;

	ECHEKCWAY m_eCheckWay;
};

