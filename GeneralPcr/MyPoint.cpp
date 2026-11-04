// 【交接】 GeneralPcr\MyPoint.cpp
// 作用：MyPoint 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：CMyPoint。
#include "StdAfx.h"
#include "MyPoint.h"


// 函数 CMyPoint::CMyPoint
// 作用：执行CMyPoint。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyPoint::CMyPoint(void)
{
	m_X = 0;
	m_Y = 0;
	m_xPixel = 0;
	m_yPixel = 0;
}


// 函数 CMyPoint::~CMyPoint
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyPoint::~CMyPoint(void)
{

}

// 函数 CMyPoint::CMyPoint
// 作用：执行CMyPoint。
// 参数：pt。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyPoint::CMyPoint(const CMyPoint& pt)
{
	m_X = pt.m_X;
	m_Y = pt.m_Y;
	m_xPixel = pt.m_X;
	m_yPixel = pt.m_Y;
}

void CMyPoint::operator=(const CMyPoint& pt)
{
	m_X = pt.m_X;
	m_Y = pt.m_Y;
	m_xPixel = pt.m_X;
	m_yPixel = pt.m_Y;
}

BOOL CMyPoint::operator==(const CMyPoint& pt)
{
	return (m_X == pt.m_X && m_Y == pt.m_Y);
}

BOOL CMyPoint::operator<(const CMyPoint& pt)
{
	return m_X < pt.m_X;
}

BOOL CMyPoint::operator>(const CMyPoint& pt)
{
	return m_X > pt.m_X;
}

BOOL CMyPoint::operator<=(const CMyPoint& pt)
{
	return m_X <= pt.m_X;
}

BOOL CMyPoint::operator>=(const CMyPoint& pt)
{
	return m_X >= pt.m_X;
}
