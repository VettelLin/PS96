// 【交接】 GeneralPcr\CYInfo.h
// 作用：CYInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCYInfo。
#pragma once

//康研葆使用的相关信息

class CCYInfo
{
public:
	// 函数 CCYInfo
	// 作用：执行CCYInfo。
	// 参数：无。
	// 返回：没有返回值。
	CCYInfo(void);
	// 函数 ~CCYInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CCYInfo(void);

	// 函数 CCYInfo
	// 作用：执行CCYInfo。
	// 参数：info。
	// 返回：没有返回值。
	CCYInfo(const CCYInfo& info);
	void operator=(const CCYInfo& info);

public:
	CString m_strClient;	//委托单位
	CString m_strCpAdr;	//委托单位地址
	CString m_strRptSoftDir;	//报告生成程序目录
};

