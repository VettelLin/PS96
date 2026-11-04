// 【交接】 GeneralPcr\ChanThreInfo.h
// 作用：ChanThreInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CChanThreInfo、GetCurSelThreInfo、GetCurSelAssociatedThreInfo。
#pragma once

#include "ThreLineInfo.h"

//曲线显示类型（线性曲线，对数曲线）
typedef enum LineShowFormat
{
	ELSF_LINEAR,ELSF_LOG
}ELINESHOWFORMAT;

//曲线数据类型（原始曲线、归一化曲线、DeltaRn曲线）
typedef enum LineDataType{
	ELDT_NORMALIZE,ELDT_DELTARN
}ELINEDATATYPE;

class AFX_EXT_CLASS CChanThreInfo
{
public:
	// 函数 CChanThreInfo
	// 作用：执行CChanThreInfo。
	// 参数：无。
	// 返回：没有返回值。
	CChanThreInfo(void);
	// 函数 ~CChanThreInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CChanThreInfo(void);

	// 函数 CChanThreInfo
	// 作用：执行CChanThreInfo。
	// 参数：info。
	// 返回：没有返回值。
	CChanThreInfo(const CChanThreInfo& info);
	void operator=(const CChanThreInfo& info);
	void operator=(CChanThreInfo& info);

	// 函数 GetCurSelThreInfo
	// 作用：读取GetCurSelThreInfo。
	// 参数：无。
	// 返回：返回指针 CThreLineInfo*。指针为空表示没有取到对象。
	CThreLineInfo* GetCurSelThreInfo();
	// 函数 GetCurSelAssociatedThreInfo
	// 作用：读取GetCurSelAssociatedThreInfo。
	// 参数：无。
	// 返回：返回指针 CThreLineInfo*。指针为空表示没有取到对象。
	CThreLineInfo* GetCurSelAssociatedThreInfo();	//获取当前选中阈值线关联阈值信息（线性阈值线和对数阈值线互为关联）

	//void SetBeAutoThre(BOOL bAutoThre);
	
public:
	CThreLineInfo m_tliNormolize;
	CThreLineInfo m_tliDeltaRn;
	CThreLineInfo m_tliLogNormolize;
	CThreLineInfo m_tliLogDeltaRn;
	
	ELINEDATATYPE m_eLineDataType;
	ELINESHOWFORMAT m_eLineShowFormat;

	int m_iChanId;
	CString m_strChanName;
	CString m_strTargetName;
};

