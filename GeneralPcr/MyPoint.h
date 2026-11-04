// 【交接】 GeneralPcr\MyPoint.h
// 作用：MyPoint 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：CMyPoint。
#pragma once
class CMyPoint
{
public:
	// 函数 CMyPoint
	// 作用：执行CMyPoint。
	// 参数：无。
	// 返回：没有返回值。
	CMyPoint(void);
	// 函数 ~CMyPoint
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMyPoint(void);
	// 函数 CMyPoint
	// 作用：执行CMyPoint。
	// 参数：pt。
	// 返回：没有返回值。
	CMyPoint(const CMyPoint& pt);

	void operator=(const CMyPoint& pt);
	BOOL operator==(const CMyPoint& pt);
	BOOL operator<(const CMyPoint& pt);
	BOOL operator>(const CMyPoint& pt);
	BOOL operator<=(const CMyPoint& pt);
	BOOL operator>=(const CMyPoint& pt);

public:
	double m_X;
	double m_Y;

	int m_xPixel;	//点在坐标轴中的水平位置
	int m_yPixel;	//点在坐标轴中的垂直位置
};

