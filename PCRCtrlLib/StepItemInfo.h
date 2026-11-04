// 【交接】 PCRCtrlLib\StepItemInfo.h
// 作用：StepItemInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CStepItemInfo、GetStepGradientInfo、GetBeCollectAll、GetBeCollect、GetBeNoneCollect、SetCollectAll、SetCollect、SetNoneCollect。
#pragma once

#include "DeclaresPCR.h"

class AFX_EXT_CLASS CStepItemInfo
{
public:
	// 函数 CStepItemInfo
	// 作用：执行CStepItemInfo。
	// 参数：无。
	// 返回：没有返回值。
	CStepItemInfo(void);
	// 函数 ~CStepItemInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CStepItemInfo(void);

	// 函数 CStepItemInfo
	// 作用：执行CStepItemInfo。
	// 参数：stepItemInfo。
	// 返回：没有返回值。
	CStepItemInfo(const CStepItemInfo& stepItemInfo);
	void operator=(const CStepItemInfo& stepItemInfo);
	
	// 函数 GetStepGradientInfo
	// 作用：读取GetStepGradientInfo。
	// 参数：ColTemp；DeltaT；fbackcali_AimT；fbackcali_DeltaT。
	// 返回：没有返回值。
	void GetStepGradientInfo(float *ColTemp,float &DeltaT,float &fbackcali_AimT,float &fbackcali_DeltaT);

	// 函数 GetBeCollectAll
	// 作用：读取GetBeCollectAll。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeCollectAll();	//判断是否是 熔曲采集 步骤
	// 函数 GetBeCollect
	// 作用：读取GetBeCollect。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeCollect();	//判断是否是 扩增采集 步骤
	// 函数 GetBeNoneCollect
	// 作用：读取GetBeNoneCollect。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeNoneCollect();	//判断是否是 不采集 步骤

	// 函数 SetCollectAll
	// 作用：设置SetCollectAll。
	// 参数：无。
	// 返回：没有返回值。
	void SetCollectAll();	//设置是否是 熔曲采集 步骤
	// 函数 SetCollect
	// 作用：设置SetCollect。
	// 参数：无。
	// 返回：没有返回值。
	void SetCollect();	//设置是否是 扩增采集 步骤
	// 函数 SetNoneCollect
	// 作用：设置SetNoneCollect。
	// 参数：无。
	// 返回：没有返回值。
	void SetNoneCollect();	//设置是否是 不采集 步骤

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

public:
	BOOL    m_bSel;  ///< 表示当前是否处于选中状态
	BOOL    m_bSelGrad; ///< 表示是否选中梯度模式
	float   m_fAimTem;   ///< 表示目标温度
	float   m_fGradUpTem;    ///< 表示梯度温度上限	
	int     m_iDelay;  ///< 表示延迟时间
	float   m_fRate;   ///< 表示温度上升的速度
	eStepCheckType m_eChkType;  ///< 数据检测的方式,1--不检测，2--末点检测，3--全点检测
	float   m_fIncrement; ///< Melt温度增量
	unsigned int     m_uiHoldTimeSec; ///< Melt温度增量对应的Hold时间
	float   m_fRangeBelowStartTem; ///< Melt 控制流程，初始降温范围
	unsigned int	m_uiWaitTimeBelowStartTem; ///< Melt 控制流程，低于起始温度的等待时间 单位（s）

	int m_stepW;	//步骤项宽度

	CRect m_rcTem;
	CRect m_rcLine;
	CRect m_rcMinSec;
	CRect m_rcCkbtCollectFlu;

	CString m_strStepName;
};

