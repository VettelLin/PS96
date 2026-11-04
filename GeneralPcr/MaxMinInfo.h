// 【交接】 GeneralPcr\MaxMinInfo.h
// 作用：MaxMinInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMaxMinInfo、SetBeOnlyIntergerNumber、GetBeOnlyIntergerNumber、SetBeOnlyFloatNumber、GetBeOnlyFloatNumber、SetBeSetMaxValue、GetBeSetMaxValue、SetMaxValue。
#pragma once
class CMaxMinInfo
{
public:
	// 函数 CMaxMinInfo
	// 作用：执行CMaxMinInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMaxMinInfo(void);
	// 函数 ~CMaxMinInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMaxMinInfo(void);

	// 函数 CMaxMinInfo
	// 作用：执行CMaxMinInfo。
	// 参数：minMaxInfo。
	// 返回：没有返回值。
	CMaxMinInfo(const CMaxMinInfo& minMaxInfo);
	void operator=(const CMaxMinInfo& minMaxInfo);

	// 函数 SetBeOnlyIntergerNumber
	// 作用：设置SetBeOnlyIntergerNumber。
	// 参数：beOnlyIntergerNumber。
	// 返回：没有返回值。
	void SetBeOnlyIntergerNumber(BOOL beOnlyIntergerNumber);
	// 函数 GetBeOnlyIntergerNumber
	// 作用：读取GetBeOnlyIntergerNumber。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeOnlyIntergerNumber();

	// 函数 SetBeOnlyFloatNumber
	// 作用：设置SetBeOnlyFloatNumber。
	// 参数：beOnlyFloatNumber。
	// 返回：没有返回值。
	void SetBeOnlyFloatNumber(BOOL beOnlyFloatNumber);
	// 函数 GetBeOnlyFloatNumber
	// 作用：读取GetBeOnlyFloatNumber。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeOnlyFloatNumber();

	// 函数 SetBeSetMaxValue
	// 作用：设置SetBeSetMaxValue。
	// 参数：bSetMaxValue：是或否。
	// 返回：没有返回值。
	void SetBeSetMaxValue(BOOL bSetMaxValue);
	// 函数 GetBeSetMaxValue
	// 作用：读取GetBeSetMaxValue。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeSetMaxValue();

	// 函数 SetMaxValue
	// 作用：设置SetMaxValue。
	// 参数：dMaxValue：小数。
	// 返回：没有返回值。
	void SetMaxValue(double dMaxValue);
	// 函数 GetMaxValue
	// 作用：读取GetMaxValue。
	// 参数：无。
	// 返回：返回一个小数。
	double GetMaxValue();

	// 函数 SetBeMaxEqualSignWork
	// 作用：设置SetBeMaxEqualSignWork。
	// 参数：bMaxEqualSignWork：是或否。
	// 返回：没有返回值。
	void SetBeMaxEqualSignWork(double bMaxEqualSignWork);
	// 函数 GetBeMaxEqualSignWork
	// 作用：读取GetBeMaxEqualSignWork。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeMaxEqualSignWork();

	// 函数 SetBeSetMinValue
	// 作用：设置SetBeSetMinValue。
	// 参数：bSetMinValue：是或否。
	// 返回：没有返回值。
	void SetBeSetMinValue(BOOL bSetMinValue);
	// 函数 GetBeSetMinValue
	// 作用：读取GetBeSetMinValue。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeSetMinValue();

	// 函数 SetMinValue
	// 作用：设置SetMinValue。
	// 参数：dMinValue：小数。
	// 返回：没有返回值。
	void SetMinValue(double dMinValue);
	// 函数 GetMinValue
	// 作用：读取GetMinValue。
	// 参数：无。
	// 返回：返回一个小数。
	double GetMinValue();

	// 函数 SetBeMinEqualSignWork
	// 作用：设置SetBeMinEqualSignWork。
	// 参数：bMinEqualSignWork：是或否。
	// 返回：没有返回值。
	void SetBeMinEqualSignWork(double bMinEqualSignWork);
	// 函数 GetBeMinEqualSignWork
	// 作用：读取GetBeMinEqualSignWork。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeMinEqualSignWork();

	// 函数 SetBeAllowNegtiveNumber
	// 作用：设置SetBeAllowNegtiveNumber。
	// 参数：bAllowNegtiveNumber：是或否。
	// 返回：没有返回值。
	void SetBeAllowNegtiveNumber(BOOL bAllowNegtiveNumber);
	// 函数 GetBeAllowNegtiveNumber
	// 作用：读取GetBeAllowNegtiveNumber。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeAllowNegtiveNumber();

	// 函数 SetBeMaxMinSimultaneousEffect
	// 作用：设置SetBeMaxMinSimultaneousEffect。
	// 参数：bMaxMinSimultaneousEffect：是或否。
	// 返回：没有返回值。
	void SetBeMaxMinSimultaneousEffect(BOOL bMaxMinSimultaneousEffect);
	// 函数 GetBeMaxMinSimultaneousEffect
	// 作用：读取GetBeMaxMinSimultaneousEffect。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeMaxMinSimultaneousEffect();

	// 函数 SetBeLessThanMinSetMin
	// 作用：设置SetBeLessThanMinSetMin。
	// 参数：bLessThanMinSetMin：是或否。
	// 返回：没有返回值。
	void SetBeLessThanMinSetMin(BOOL bLessThanMinSetMin);
	// 函数 GetBeLessThanMinSetMin
	// 作用：读取GetBeLessThanMinSetMin。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeLessThanMinSetMin();

	// 函数 ClearMaxMinLimit
	// 作用：更新或清除ClearMaxMinLimit。
	// 参数：无。
	// 返回：没有返回值。
	void ClearMaxMinLimit();

private:
	BOOL   m_bOnlyIntergerNumber;	//是否只能输入整数数字
	BOOL   m_bOnlyFloatNumber;	//是否只能输入浮点数（兼容double类型）
	BOOL   m_bSetMaxValue;	//是否设置最大值
	double m_dMaxValue;	//最大值，结合m_bSetMaxValue使用
	BOOL   m_bMaxEqualSignWork;	//标识“<= 中的 = 是否起作用”
	BOOL   m_bSetMinValue;	//是否设置最小值
	double m_dMinValue;	//最小值，结合m_bSetMinValue使用
	BOOL   m_bAllowNegtiveNumber;	//标识“是否允许负数输入"
	BOOL   m_bMinEqualSignWork;	//标识“>= 中的 = 是否起作用”

	BOOL m_bMaxMinSimultaneousEffect;	//标识“最大最小值限制是否同时起作用（最大最小值限制同时存在时，默认最大值生效）”

	BOOL m_bLessThanMinSetMin;	//有最小值限制的项，如果用户输入的数值小于最小值 或者 输入内容为空，软件直接设置为最小值
};

