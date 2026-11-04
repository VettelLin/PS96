// 【交接】 dll\header\AlgorithmSet.h
// 作用：AlgorithmSet。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：LinearFitData、ParabolaFitData、__declspec。
#pragma once

//#define in
//#define out

typedef struct LinearFitData
{
	double* pDataX;
	int xLen;
	double* pDataY;
	int yLen;
	double intercept;
	double rSquare;
	double slope;

	// 函数 LinearFitData
	// 作用：执行LinearFitData。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	LinearFitData()
	{
		pDataX = nullptr;
		xLen = 0;
		pDataY = nullptr;
		yLen = 0;
		intercept = 0;
		rSquare = 0;
		slope = 0;
	}

	// 函数 ~LinearFitData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~LinearFitData()
	{
		if(nullptr != pDataX)
		{
			delete pDataX;
		}
		if(nullptr != pDataY)
		{
			delete pDataY;
		}
	}
}LINEARFITDATA;

typedef struct ParabolaFitData
{
	double* pDataX;
	int xLen;
	double* pDataY;
	int yLen;
	double a;
	double b;
	double c;
	double dR;

	// 函数 ParabolaFitData
	// 作用：执行ParabolaFitData。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	ParabolaFitData()
	{
		pDataX = nullptr;
		xLen = 0;
		pDataY = nullptr;
		yLen = 0;
		a = 0;
		b = 0;
		c = 0;
		dR = 0;
	}

	// 函数 ~ParabolaFitData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~ParabolaFitData()
	{
		if(nullptr != pDataX)
		{
			delete pDataX;
		}
		if(nullptr != pDataY)
		{
			delete pDataY;
		}
	}
}PARABOLAFITDATA;

extern "C" __declspec(dllexport) int LinearFit(LINEARFITDATA* pFitData);
