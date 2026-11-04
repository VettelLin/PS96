// 【交接】 PCRCtrlLib\ExpStateInfo.h
// 作用：ExpStateInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CExpStateInfo、GetRemainTimeStr、GetCurrentTemperatureStr、Clear。
#pragma once

/*该类用于记录实验文件的状态信息，切换实验时更新软件主页面相应控件的状态和内容,20220712,孙文郎*/

#include "DeclaresPCR.h"

//运行图标状态（可运行）、停止图标状态、运行图标禁用状态、停止图标禁用状态、隐藏状态
typedef enum RunBtState{
	ERBS_RUN,ERBS_STOP,ERBS_RUNFORBIDDEN,ERBS_STOPFORBIDDEN,ERBS_HIDE
}ERUNBTSTATE;

//进仓图标状态（可进仓）、出仓图标状态、进仓图标禁用状态、出仓图标禁用状态、隐藏状态
typedef enum BinBtState{
	EBBS_IN,EBBS_OUT,EBBS_INFORBIDDEN,EBBS_OUTFORBIDDEN,EBBS_HIDE
}EBINBTSTATE;

class AFX_EXT_CLASS CExpStateInfo
{
public:
	// 函数 CExpStateInfo
	// 作用：执行CExpStateInfo。
	// 参数：无。
	// 返回：没有返回值。
	CExpStateInfo(void);
	// 函数 ~CExpStateInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CExpStateInfo(void);

	// 函数 CExpStateInfo
	// 作用：执行CExpStateInfo。
	// 参数：info。
	// 返回：没有返回值。
	CExpStateInfo(const CExpStateInfo& info);
	void operator=(const CExpStateInfo& info);

	// 函数 GetRemainTimeStr
	// 作用：读取GetRemainTimeStr。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetRemainTimeStr();
	// 函数 GetCurrentTemperatureStr
	// 作用：读取GetCurrentTemperatureStr。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetCurrentTemperatureStr();

	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();

public:
	CString m_strExpName;	//实验名称
	int m_iRemainSec;	//剩余时间
	double m_dCurTem;	//当前温度
	double m_dCurProgress;	//当前进度
	eExperimentType m_eExpType;	//实验类型

	ERUNBTSTATE m_eRunBtState;	//运行按钮状态
	EBINBTSTATE m_eBinBtState;	//进出仓按钮状态
};

