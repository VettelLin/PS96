// 【交接】 GeneralPcr\ChanMeltAnaParamChangeInfo.h
// 作用：ChanMeltAnaParamChangeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CChanMeltAnaParamChangeInfo、IsAnaParamChanged。
#pragma once
class CChanMeltAnaParamChangeInfo
{
public:
	// 函数 CChanMeltAnaParamChangeInfo
	// 作用：执行CChanMeltAnaParamChangeInfo。
	// 参数：无。
	// 返回：没有返回值。
	CChanMeltAnaParamChangeInfo(void);
	// 函数 ~CChanMeltAnaParamChangeInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CChanMeltAnaParamChangeInfo(void);

	// 函数 CChanMeltAnaParamChangeInfo
	// 作用：执行CChanMeltAnaParamChangeInfo。
	// 参数：info。
	// 返回：没有返回值。
	CChanMeltAnaParamChangeInfo(const CChanMeltAnaParamChangeInfo& info);
	void operator=(const CChanMeltAnaParamChangeInfo& info);

	// 函数 IsAnaParamChanged
	// 作用：判断IsAnaParamChanged是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsAnaParamChanged();

public:
	BOOL m_bMinTemChanged;
	BOOL m_bMaxTemChanged;
	BOOL m_bPeakThreChanged;
};

