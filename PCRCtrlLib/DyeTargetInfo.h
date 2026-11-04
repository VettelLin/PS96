// 【交接】 PCRCtrlLib\DyeTargetInfo.h
// 作用：DyeTargetInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CDyeTargetInfo、WriteFile、ReadFile、SetTm、DeleteAll、GetDyeName、SetDyeName、GetTargetName。
#pragma once

#include "DeclaresPCR.h"
#include "ReagentItem.h"

class AFX_EXT_CLASS CDyeTargetInfo
{
public:
	// 函数 CDyeTargetInfo
	// 作用：执行CDyeTargetInfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CDyeTargetInfo(void);
	// 函数 ~CDyeTargetInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CDyeTargetInfo(void);

	enum eCalculateValueType
	{
		VALUE_CT = 0, // 插值法Ct
		VALUE_REPEAT_CT, // 复管Ct
		VALUE_SET_QUANTITY, // 设置浓度
		VALUE_CALC_QUANTITY, // 计算浓度拷贝数
		VALUE_REPEAT_QUANTITY, // 复管浓度
		VALUE_MEAN_CT, // 平均Ct
		VALUE_CT_SD, // Ct平均方差
		VALUE_TM	//Tm值
	};

	// 函数 CDyeTargetInfo
	// 作用：执行CDyeTargetInfo。
	// 参数：dyeTargetInfo。
	// 返回：没有返回值。
	CDyeTargetInfo(const CDyeTargetInfo& dyeTargetInfo);
	void operator=(const CDyeTargetInfo& dyeTargetInfo);

// Operations
public:
	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL WriteFile(CFile* pFile,WORD wVersion);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetDyeName。
	BOOL ReadFile(CFile* pFile,WORD wVersion);
	// 函数 SetTm
	// 作用：设置SetTm。
	// 参数：nCount：整数；pdTm；pdRm。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetDyeName。
	void SetTm(int nCount, double* pdTm, double* pdRm);
	
protected:
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetDyeName。
	void DeleteAll();

// Attributes
public:
	// 函数 GetDyeName
	// 作用：读取GetDyeName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetDyeName() { return m_strDye; }
	// 函数 SetDyeName
	// 作用：设置SetDyeName。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetDyeName(CString string) { m_strDye = string; }
	// 函数 GetTargetName
	// 作用：读取GetTargetName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetTargetName() { return m_strTarget; }
	// 函数 SetTargetName
	// 作用：设置SetTargetName。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTargetName(CString string) { m_strTarget = string; }
	// 函数 GetQuencher
	// 作用：读取GetQuencher。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetQuencher() { return m_strQuencher; }
	// 函数 SetQuencher
	// 作用：设置SetQuencher。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetQuencher(CString string) { m_strQuencher = string; }
	// 函数 GetChannel
	// 作用：读取GetChannel。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetChannel() { return m_iChannel; }
	// 函数 SetChannel
	// 作用：设置SetChannel。
	// 参数：iChannel：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetChannel(int iChannel) { m_iChannel = iChannel; }
	// 函数 GetTargetColor
	// 作用：读取GetTargetColor。
	// 参数：无。
	// 返回：返回 COLORREF。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	COLORREF GetTargetColor() {return m_clrTarget; }
	// 函数 SetTargetColor
	// 作用：设置SetTargetColor。
	// 参数：color：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTargetColor(COLORREF color) { m_clrTarget = color; }

	// 函数 GetAutoBaseline
	// 作用：读取GetAutoBaseline。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetAutoBaseline() { return m_bAutoBaseline; }
	// 函数 SetAutoBaseline
	// 作用：设置SetAutoBaseline。
	// 参数：bAuto：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAutoBaseline(BOOL bAuto) { m_bAutoBaseline = bAuto; }
	// 函数 GetBaselineStart
	// 作用：读取GetBaselineStart。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetBaselineStart() { return m_iBaselineStart; }
	// 函数 SetBaselineStart
	// 作用：设置SetBaselineStart。
	// 参数：iStart：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBaselineStart(int iStart) { m_iBaselineStart = iStart; }
	// 函数 GetBaselineEnd
	// 作用：读取GetBaselineEnd。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetBaselineEnd() { return m_iBaselineEnd; }
	// 函数 SetBaselineEnd
	// 作用：设置SetBaselineEnd。
	// 参数：iEnd：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBaselineEnd(int iEnd) { m_iBaselineEnd = iEnd; }
	// 函数 GetAutoThreshold
	// 作用：读取GetAutoThreshold。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetAutoThreshold() { return m_bAutoThreshold; }
	// 函数 SetAutoThreshold
	// 作用：设置SetAutoThreshold。
	// 参数：bAuto：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAutoThreshold(BOOL bAuto) { m_bAutoThreshold = bAuto; }
	// 函数 GetThresholdValue
	// 作用：读取GetThresholdValue。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	double GetThresholdValue() { return m_dThreshold; }
	// 函数 SetThresholdValue
	// 作用：设置SetThresholdValue。
	// 参数：dValue：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetThresholdValue(double dValue) { m_dThreshold = dValue; }

	// 函数 GetCalcValue
	// 作用：读取GetCalcValue。
	// 参数：nType：整数。
	// 返回：返回一个小数。
	// 过程：函数里会调用 GetTmCount。
	double GetCalcValue(eCalculateValueType nType);
	// 函数 SetCalcValue
	// 作用：设置SetCalcValue。
	// 参数：nType：整数；dValue：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTmCount。
	void SetCalcValue(eCalculateValueType nType, double dValue);

	// 函数 SetTmCount
	// 作用：设置SetTmCount。
	// 参数：nCount：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTmCount。
	void SetTmCount(int nCount);
	// 函数 GetTmCount
	// 作用：读取GetTmCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetTmCount() { return m_iTmCount; }

	// 函数 SetBeSelected
	// 作用：设置SetBeSelected。
	// 参数：bSelected：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBaselineAverage。
	void SetBeSelected(BOOL bSelected);
	// 函数 GetBeSelected
	// 作用：读取GetBeSelected。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetBaselineAverage。
	BOOL GetBeSelected();

	// 函数 SetQuantity
	// 作用：设置SetQuantity。
	// 参数：dQuantity：小数；iDpd：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetBaselineAverage。
	void SetQuantity(double dQuantity,int iDpd);
	// 函数 GetQuantity
	// 作用：读取GetQuantity。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：函数里会调用 SetBaselineAverage。
	double GetQuantity();
	// 函数 GetQuanIDPD
	// 作用：读取GetQuanIDPD。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetBaselineAverage。
	int GetQuanIDPD();

	// 函数 SetBaselineAverage
	// 作用：设置SetBaselineAverage。
	// 参数：dAverage：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBaselineAverage(double dAverage) { m_dBaselineAverage = dAverage; }
	// 函数 GetBaselineAverage
	// 作用：读取GetBaselineAverage。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	double GetBaselineAverage() { return m_dBaselineAverage; }
	// 函数 HasSndDrvCt
	// 作用：判断HasSndDrvCt是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL HasSndDrvCt() { return m_bHasSndDrvCt; }
	// 函数 SetHasSndDrvCt
	// 作用：设置SetHasSndDrvCt。
	// 参数：bHas：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetHasSndDrvCt(BOOL bHas) { m_bHasSndDrvCt = bHas; }
	// 函数 GetSndDrvCt
	// 作用：读取GetSndDrvCt。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	double GetSndDrvCt() { return m_dSndDrvCt; }
	// 函数 SetSndDrvCt
	// 作用：设置SetSndDrvCt。
	// 参数：dCt：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSndDrvCt(double dCt) { m_dSndDrvCt = dCt; }

	// 函数 GetCt
	// 作用：读取GetCt。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	double GetCt(){return m_dCt;}
	// 函数 GetTm1
	// 作用：读取GetTm1。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：函数里会调用 SetAnalyseResult。
	double GetTm1();
	// 函数 GetTm1String
	// 作用：读取GetTm1String。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetAnalyseResult。
	CString GetTm1String();

	// 函数 SetAnalyseResult
	// 作用：设置SetAnalyseResult。
	// 参数：eAnaRst。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAnalyseResult(EANALYSERESULT eAnaRst){ m_eAnaRst = eAnaRst; }
	// 函数 GetAnalyseResult
	// 作用：读取GetAnalyseResult。
	// 参数：无。
	// 返回：返回 EANALYSERESULT。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	EANALYSERESULT GetAnalyseResult(){ return m_eAnaRst; }

	// 函数 GetBePositiveAnaResult
	// 作用：读取GetBePositiveAnaResult。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetBePositiveAnaResult() { return EAR_POSITVE == m_eAnaRst; }
	// 函数 GetBeNegativeAnaResult
	// 作用：读取GetBeNegativeAnaResult。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetBeNegativeAnaResult() { return EAR_NEGATIVE == m_eAnaRst; }
	// 函数 GetBeUnhandledAnaResult
	// 作用：读取GetBeUnhandledAnaResult。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetBeUnhandledAnaResult() { return EAR_UNHANDLED == m_eAnaRst; }

	// 函数 SetCycleOfPlateau
	// 作用：设置SetCycleOfPlateau。
	// 参数：iCycle：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCycleOfPlateau(int iCycle) { m_iCycleOfPlateau = iCycle; }
	// 函数 GetCycleOfPlateau
	// 作用：读取GetCycleOfPlateau。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCycleOfPlateau() { return m_iCycleOfPlateau;}

	// 函数 SetCalcSplineThresholdUsed
	// 作用：设置SetCalcSplineThresholdUsed。
	// 参数：bUsed：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCalcSplineThresholdUsed(BOOL bUsed) {m_bCalcSplineUsed=bUsed;}
	// 函数 GetCalcSplineThresholdUsed
	// 作用：读取GetCalcSplineThresholdUsed。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetCalcSplineThresholdUsed() { return m_bCalcSplineUsed; }

protected:
	BOOL		m_bSelected;	//标识染料是否选中
	CString		m_strDye; // 染料名称，即Reporter
	CString		m_strTarget; // 目标
	CString		m_strQuencher; // 淬灭者
	int			m_iChannel; // 通道，从1开始
	double		m_dQuantity; // 浓度
	int			m_iQuanIdpd;	//设定浓度的小数点位数
	COLORREF	m_clrTarget; // 指标曲线颜色

	BOOL	m_bAutoBaseline;	//是否选择自动基线
	int		m_iBaselineStart;	//基线起点
	int		m_iBaselineEnd;	//基线终点
	BOOL	m_bAutoThreshold;	//是否选择自动阈值
	double	m_dThreshold; // 手动阈值

	// 扩增曲线Ct及相关结果
	double	m_dBaselineAverage; // 基线范围内荧光值均值
	BOOL	m_bHasSndDrvCt; // 是否存在二阶导数Ct
	double	m_dSndDrvCt; // 最大二阶导数计算Ct

	double	m_dCt; // Ct
	double	m_dCalcQuantity; // 重新计算后的拷贝数
	double	m_dRepeatCt; // 复管Ct
	double	m_dRepeatQuantity; // 复管浓度数

	// 熔解段参数
	int			m_iTmCount; // 熔解段Tm数量
	double*		m_pMeltTm; // 熔解段Tm值
	double*		m_pMeltRm; // 熔解段最高峰Rm值

	EANALYSERESULT m_eAnaRst;	//阴阳性判定结果

	int	m_iCycleOfPlateau; // 平台期开始的循环

	BOOL m_bCalcSplineUsed; // 计算基线时是否被使用
};

