// 【交接】 PCRCtrlLib\SegItemInfo.h
// 作用：SegItemInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSegItemInfo、WriteFile、ReadFile、GetSegWidth、GetBeMeltSeg、GetMeltIncrement、GetBeAmlSeg、GetBeAllStepSelected。
#pragma once

#include "StepItemInfo.h"
#include "LinkList.h"

class AFX_EXT_CLASS CSegItemInfo
{
	enum eSegmentType
	{
		SEGMENT_NONE = 0,
		SEGMENT_CYCLE, // 循环扩增
		SEGMENT_MELT, // 熔曲
		SEGMENT_HOLD, // 保持，ABI
	};

public:
	// 函数 CSegItemInfo
	// 作用：执行CSegItemInfo。
	// 参数：无。
	// 返回：没有返回值。
	CSegItemInfo(void);
	// 函数 ~CSegItemInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSegItemInfo(void);

	// 函数 CSegItemInfo
	// 作用：执行CSegItemInfo。
	// 参数：segItemInfo。
	// 返回：没有返回值。
	CSegItemInfo(const CSegItemInfo& segItemInfo);
	void operator=(const CSegItemInfo& segItemInfo);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteFile(CFile* pFile);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL ReadFile(CFile* pFile, WORD wVersion);

	// 函数 GetSegWidth
	// 作用：读取GetSegWidth。
	// 参数：stepId。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetSegWidth(int stepId = -2);	//stepId默认值不能是-1，因为0 - 1 = -1；
	// 函数 GetBeMeltSeg
	// 作用：读取GetBeMeltSeg。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeMeltSeg();
	// 函数 GetMeltIncrement
	// 作用：读取GetMeltIncrement。
	// 参数：dMeltIncrement：小数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetMeltIncrement(double& dMeltIncrement);
	// 函数 GetBeAmlSeg
	// 作用：读取GetBeAmlSeg。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeAmlSeg();

	// 函数 GetBeAllStepSelected
	// 作用：读取GetBeAllStepSelected。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeAllStepSelected();
	// 函数 GetBeHaveSelectedStep
	// 作用：读取GetBeHaveSelectedStep。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeHaveSelectedStep();

	// 函数 GetFirstStepTemperature
	// 作用：读取GetFirstStepTemperature。
	// 参数：无。
	// 返回：返回一个小数。
	float GetFirstStepTemperature();
	// 函数 GetLastStepTemperatre
	// 作用：读取GetLastStepTemperatre。
	// 参数：无。
	// 返回：返回一个小数。
	float GetLastStepTemperatre();

	// 函数 GetStepNum
	// 作用：读取GetStepNum。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetStepNum();

	// 函数 CorrectNameLanguage
	// 作用：执行CorrectNameLanguage。
	// 参数：strSource：字符串；strTarget：字符串；strStepSource：字符串；strStepTarget：字符串。
	// 返回：没有返回值。
	void CorrectNameLanguage(CString strSource, CString strTarget, CString strStepSource, CString strStepTarget);
	// 函数 CorrectIndex
	// 作用：执行CorrectIndex。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	void CorrectIndex(int iIndex);

	// 函数 CalculateTotalSeconds
	// 作用：计算CalculateTotalSeconds。
	// 参数：无。
	// 返回：返回 long。
	long CalculateTotalSeconds();

//数据属性
public:
	int m_iStepNum;       ///< 步骤中子项的个数
	int	m_iSegType;        ///< 步骤类型 1--none,2--扩增,3--熔曲
	int m_iCycleNum;     ///< 循环次数
	CString m_strSegName;    ///< 步骤名称
	float m_fMeltRate;			//记录融解段升降温速率

	BOOL m_bSelected;	//标识程序段是否被选中

	eSegmentType m_nSegType; // 步骤类型

	CRect m_rcCycleNum;	//记录循环数区域（窗口区域，非内存区域）
	CRect m_rcSegName;	//记录程序段名称区域（窗口区域，非内存区域）
	CRect m_rcSeg;	//记录程序段区域（窗口区域，非内存区域）

	CLinkList<CStepItemInfo> m_lnkStepItemInfo;	///<保存step信息
};

