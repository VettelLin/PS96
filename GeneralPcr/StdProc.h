// 【交接】 GeneralPcr\StdProc.h
// 作用：StdProc。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CStdLineTag、CStdLine、LinearFit、CalculateAverageDot、Clear、CStdProc、AddPoint、DeleteOneStdLine。
#pragma once

#include<vector>
#include "MyPoint.h"
#include "LinkList.h"
#include "LinearFitData.h"

using namespace std;

class CStdLineTag
{
public:
	// 函数 CStdLineTag
	// 作用：执行CStdLineTag。
	// 参数：无。
	// 返回：没有返回值。
	CStdLineTag();
	// 函数 ~CStdLineTag
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CStdLineTag();

	// 函数 CStdLineTag
	// 作用：执行CStdLineTag。
	// 参数：stdLineTag。
	// 返回：没有返回值。
	CStdLineTag(const CStdLineTag& stdLineTag);
	void operator=(const CStdLineTag& stdLineTag);
	BOOL operator==(const CStdLineTag& stdLineTag);

public:
	int m_iChanId;
};

class CStdLine
{
public:
	// 函数 CStdLine
	// 作用：执行CStdLine。
	// 参数：无。
	// 返回：没有返回值。
	CStdLine();
	// 函数 ~CStdLine
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CStdLine();

	// 函数 CStdLine
	// 作用：执行CStdLine。
	// 参数：stdLine。
	// 返回：没有返回值。
	CStdLine(const CStdLine& stdLine);

	void operator=(CStdLine& stdLine);

	// 函数 LinearFit
	// 作用：执行LinearFit。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int LinearFit();
	// 函数 CalculateAverageDot
	// 作用：计算CalculateAverageDot。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalculateAverageDot();

	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();

public:
	CStdLineTag m_stdLineTag;

	vector<double> m_vecDensity;
	vector<vector<double>> m_2vecCt;

	CLinearFitData m_linearFitData;
	double m_dEfficiency;	//扩增效率
};

class CStdProc
{
public:
	// 函数 CStdProc
	// 作用：执行CStdProc。
	// 参数：无。
	// 返回：没有返回值。
	CStdProc(void);
	// 函数 ~CStdProc
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CStdProc(void);

	// 函数 AddPoint
	// 作用：创建或加入AddPoint。
	// 参数：stdLineTag；dX：小数；dY：小数。
	// 返回：没有返回值。
	void AddPoint(CStdLineTag stdLineTag,double dX,double dY);
	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();
	// 函数 DeleteOneStdLine
	// 作用：更新或清除DeleteOneStdLine。
	// 参数：stdLineTag。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteOneStdLine(CStdLineTag stdLineTag);

	// 函数 GetStdLinePtr
	// 作用：读取GetStdLinePtr。
	// 参数：stdLineTag。
	// 返回：返回指针 CStdLine*。指针为空表示没有取到对象。
	CStdLine* GetStdLinePtr(CStdLineTag stdLineTag);
	// 函数 GetStdLinePtr
	// 作用：读取GetStdLinePtr。
	// 参数：iIndex：整数。
	// 返回：返回指针 CStdLine*。指针为空表示没有取到对象。
	CStdLine* GetStdLinePtr(int iIndex);

	// 函数 GetStdLineNum
	// 作用：读取GetStdLineNum。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetStdLineNum();

	// 函数 Fit
	// 作用：执行Fit。
	// 参数：无。
	// 返回：没有返回值。
	void Fit();	//拟合所有曲线

public:
	vector<CStdLine> m_vecStdLine;
};

