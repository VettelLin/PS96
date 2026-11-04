// 【交接】 GeneralPcr\SegStepRange.cpp
// 作用：SegStepRange。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSegStepRange、BeValidRange、ResetSegStepRange、SetSegmentStart、GetSegmentStart、SetSegmentEnd、GetSegmentEnd、SetStepStart。
#include "StdAfx.h"
#include "SegStepRange.h"


// 函数 CSegStepRange::CSegStepRange
// 作用：执行CSegStepRange。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegStepRange::CSegStepRange(void)
{
	m_segStart = -1;
	m_segEnd = -1;
	m_stepStart = -1;
	m_stepEnd = -1;
}

// 函数 CSegStepRange::~CSegStepRange
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegStepRange::~CSegStepRange(void)
{

}

// 函数 CSegStepRange::CSegStepRange
// 作用：执行CSegStepRange。
// 参数：segStep。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegStepRange::CSegStepRange(const CSegStepRange& segStep)
{
	m_segStart = segStep.m_segStart;
	m_segEnd = segStep.m_segEnd;
	m_stepStart = segStep.m_stepStart;
	m_stepEnd = segStep.m_stepEnd;
}

void CSegStepRange::operator=(const CSegStepRange& segStep)
{
	m_segStart = segStep.m_segStart;
	m_segEnd = segStep.m_segEnd;
	m_stepStart = segStep.m_stepStart;
	m_stepEnd = segStep.m_stepEnd;
}

// 函数 CSegStepRange::BeValidRange
// 作用：判断BeValidRange是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSegStepRange::BeValidRange()
{
	return (-1 != m_segStart) && (-1 != m_segEnd) && (-1 != m_stepStart) && (-1 != m_stepEnd) && (m_segStart <= m_segEnd); 
}

// 函数 CSegStepRange::ResetSegStepRange
// 作用：更新或清除ResetSegStepRange。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSegStepRange::ResetSegStepRange()
{
	m_segStart = -1;
	m_segEnd = -1;
	m_stepStart = -1;
	m_stepEnd = -1;
}

// 函数 CSegStepRange::SetSegmentStart
// 作用：设置SetSegmentStart。
// 参数：segStart。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSegStepRange::SetSegmentStart(int segStart)
{
	m_segStart = segStart;
}

// 函数 CSegStepRange::GetSegmentStart
// 作用：读取GetSegmentStart。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CSegStepRange::GetSegmentStart()
{
	return m_segStart;
}

// 函数 CSegStepRange::SetSegmentEnd
// 作用：设置SetSegmentEnd。
// 参数：segEnd。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSegStepRange::SetSegmentEnd(int segEnd)
{
	m_segEnd = segEnd;
}

// 函数 CSegStepRange::GetSegmentEnd
// 作用：读取GetSegmentEnd。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CSegStepRange::GetSegmentEnd()
{
	return m_segEnd;
}

// 函数 CSegStepRange::SetStepStart
// 作用：设置SetStepStart。
// 参数：stepStart。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSegStepRange::SetStepStart(int stepStart)
{
	m_stepStart = stepStart;
}

// 函数 CSegStepRange::GetStepStart
// 作用：读取GetStepStart。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CSegStepRange::GetStepStart()
{
	return m_stepStart;
}

// 函数 CSegStepRange::SetStepEnd
// 作用：设置SetStepEnd。
// 参数：stepEnd。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSegStepRange::SetStepEnd(int stepEnd)
{
	m_stepEnd = stepEnd;
}

// 函数 CSegStepRange::GetStepEnd
// 作用：读取GetStepEnd。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CSegStepRange::GetStepEnd()
{
	return m_stepEnd;
}


