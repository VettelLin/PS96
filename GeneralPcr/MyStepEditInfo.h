// 【交接】 GeneralPcr\MyStepEditInfo.h
// 作用：MyStepEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMyStepEditInfo。
#pragma once
class CMyStepEditInfo
{
public:
	// 函数 CMyStepEditInfo
	// 作用：执行CMyStepEditInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMyStepEditInfo(void);
	// 函数 ~CMyStepEditInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMyStepEditInfo(void);

	// 函数 CMyStepEditInfo
	// 作用：执行CMyStepEditInfo。
	// 参数：stepEditInfo。
	// 返回：没有返回值。
	CMyStepEditInfo(const CMyStepEditInfo& stepEditInfo);
	void operator=(const CMyStepEditInfo& stepEditInfo);

public:
	CString m_strSegName;
	CString m_strStepName;
	float m_fAimTem;
	BOOL m_bSelGradient;
	float m_fGradientMaxTem;
	int m_holdSec;
	int m_iCollect;	//是否采集荧光
	float m_fRate;	//升降温速率
	float m_fIncrement;	//熔曲荧光采集温度间隔

	BOOL m_bCollectExistExceptThisStep;	//步骤之外是否已经存在采集步骤（扩增）
	BOOL m_bCollectAllExistExceptThisStep;	//步骤之外是否已经存在全点采集步骤（熔曲）

	BOOL m_bMeltSeg;	//标识步骤所在的程序段是否是熔曲程序段
};

