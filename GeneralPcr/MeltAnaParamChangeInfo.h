// 【交接】 GeneralPcr\MeltAnaParamChangeInfo.h
// 作用：MeltAnaParamChangeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMeltAnaParamChangeInfo、SetChannelNum、IsAnaParamChanged、IsChannelAnaParamChanged。
#pragma once

#include<vector>
#include "ChanMeltAnaParamChangeInfo.h"

using namespace std;

class CMeltAnaParamChangeInfo
{
public:
	// 函数 CMeltAnaParamChangeInfo
	// 作用：执行CMeltAnaParamChangeInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMeltAnaParamChangeInfo(void);
	// 函数 ~CMeltAnaParamChangeInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMeltAnaParamChangeInfo(void);

	// 函数 CMeltAnaParamChangeInfo
	// 作用：执行CMeltAnaParamChangeInfo。
	// 参数：info。
	// 返回：没有返回值。
	CMeltAnaParamChangeInfo(const CMeltAnaParamChangeInfo& info);
	void operator=(const CMeltAnaParamChangeInfo& info);

	// 函数 SetChannelNum
	// 作用：设置SetChannelNum。
	// 参数：iChanNum：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int SetChannelNum(int iChanNum);

	// 函数 IsAnaParamChanged
	// 作用：判断IsAnaParamChanged是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsAnaParamChanged();
	// 函数 IsChannelAnaParamChanged
	// 作用：判断IsChannelAnaParamChanged是否成立。
	// 参数：iChanId：整数。
	// 返回：返回是或否。
	BOOL IsChannelAnaParamChanged(int iChanId);

public:
	int m_iChanNum;
	vector<CChanMeltAnaParamChangeInfo> m_vecChanMeltChangeInfo; 
};

