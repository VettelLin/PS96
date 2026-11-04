// 【交接】 GeneralPcr\MySegEditInfo.h
// 作用：MySegEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMySegEditInfo。
#pragma once
class CMySegEditInfo
{
public:
	// 函数 CMySegEditInfo
	// 作用：执行CMySegEditInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMySegEditInfo(void);
	// 函数 ~CMySegEditInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMySegEditInfo(void);

	// 函数 CMySegEditInfo
	// 作用：执行CMySegEditInfo。
	// 参数：segEditInfo。
	// 返回：没有返回值。
	CMySegEditInfo(const CMySegEditInfo& segEditInfo);
	void operator=(const CMySegEditInfo& segEditInfo);

public:
	CString m_strSegName;	//程序段名称
	int m_cycleNum;	//循环数
	BOOL m_bMeltSeg;	//标识Segment是否包含熔解步骤
};

