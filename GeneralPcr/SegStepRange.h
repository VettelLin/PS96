// 【交接】 GeneralPcr\SegStepRange.h
// 作用：SegStepRange。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSegStepRange、BeValidRange、ResetSegStepRange、SetSegmentStart、GetSegmentStart、SetSegmentEnd、GetSegmentEnd、SetStepStart。
#pragma once
class CSegStepRange
{
public:
	// 函数 CSegStepRange
	// 作用：执行CSegStepRange。
	// 参数：无。
	// 返回：没有返回值。
	CSegStepRange(void);
	// 函数 ~CSegStepRange
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSegStepRange(void);

	// 函数 CSegStepRange
	// 作用：执行CSegStepRange。
	// 参数：segStep。
	// 返回：没有返回值。
	CSegStepRange(const CSegStepRange& segStep);
	void operator=(const CSegStepRange& segStep);

	// 函数 BeValidRange
	// 作用：判断BeValidRange是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL BeValidRange();
	// 函数 ResetSegStepRange
	// 作用：更新或清除ResetSegStepRange。
	// 参数：无。
	// 返回：没有返回值。
	void ResetSegStepRange();

	// 函数 SetSegmentStart
	// 作用：设置SetSegmentStart。
	// 参数：segStart。
	// 返回：没有返回值。
	void SetSegmentStart(int segStart);
	// 函数 GetSegmentStart
	// 作用：读取GetSegmentStart。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetSegmentStart();
	// 函数 SetSegmentEnd
	// 作用：设置SetSegmentEnd。
	// 参数：segEnd。
	// 返回：没有返回值。
	void SetSegmentEnd(int segEnd);
	// 函数 GetSegmentEnd
	// 作用：读取GetSegmentEnd。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetSegmentEnd();

	// 函数 SetStepStart
	// 作用：设置SetStepStart。
	// 参数：stepStart。
	// 返回：没有返回值。
	void SetStepStart(int stepStart);
	// 函数 GetStepStart
	// 作用：读取GetStepStart。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetStepStart();
	// 函数 SetStepEnd
	// 作用：设置SetStepEnd。
	// 参数：stepEnd。
	// 返回：没有返回值。
	void SetStepEnd(int stepEnd);
	// 函数 GetStepEnd
	// 作用：读取GetStepEnd。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetStepEnd();

private:
	int m_segStart;
	int m_segEnd;
	int m_stepStart;
	int m_stepEnd;
};

