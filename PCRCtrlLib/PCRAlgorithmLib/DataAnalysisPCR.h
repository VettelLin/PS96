// 【交接】 PCRCtrlLib\PCRAlgorithmLib\DataAnalysisPCR.h
// 作用：DataAnalysisPCR。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CDataAnalysisPCR、InitPara、CanNormalize、IsPeakAml、AdjustFluValueByBaseline、CalcNormalize、CalcDeltaRn、CalcFluTurbidityAdjust。
#pragma once

#include "DataAlgorithmPCR.h"
#include "PeakAmlCheckParam.h"

class AFX_EXT_CLASS CDataAnalysisPCR : public CDataAlgorithmPCR
{
public:
	// 函数 CDataAnalysisPCR
	// 作用：执行CDataAnalysisPCR。
	// 参数：无。
	// 返回：没有返回值。
	CDataAnalysisPCR(void);
	// 函数 ~CDataAnalysisPCR
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CDataAnalysisPCR(void);

// 保存与分析相关的参数
public:
	// 函数 InitPara
	// 作用：初始化InitPara。
	// 参数：strStartPath：字符串。
	// 返回：没有返回值。
	void InitPara(CString strStartPath);
	// 函数 CanNormalize
	// 作用：判断CanNormalize是否成立。
	// 参数：iCycleCount：整数。
	// 返回：返回是或否。
	BOOL CanNormalize(int iCycleCount);

	// 函数 IsPeakAml
	// 作用：判断IsPeakAml是否成立。
	// 参数：pDX：指针，指向调用方传入的对象；pDY：指针，指向调用方传入的对象；nDataNum：整数；peakAmlChkParam；dOutCt：小数。
	// 返回：返回是或否。
	BOOL IsPeakAml(double *pDX,double *pDY,int nDataNum,CPeakAmlCheckParam& peakAmlChkParam, double &dOutCt);

	// 函数 AdjustFluValueByBaseline
	// 作用：执行AdjustFluValueByBaseline。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iStart：整数；iEnd：整数。
	// 返回：没有返回值。
	void AdjustFluValueByBaseline(int nPtCount, double *pInputX, double *pInputY, int iStart, int iEnd);
	// 函数 CalcNormalize
	// 作用：计算CalcNormalize。
	// 参数：nPtCount：整数；pInputY：指针，指向调用方传入的对象；pOutputY：指针，指向调用方传入的对象；dAverage：小数。
	// 返回：没有返回值。
	void CalcNormalize(int nPtCount, double *pInputY, double *pOutputY, double dAverage);
	// 函数 CalcDeltaRn
	// 作用：计算CalcDeltaRn。
	// 参数：nPtCount：整数；pInputY：指针，指向调用方传入的对象；pOutputY：指针，指向调用方传入的对象；dAverage：小数。
	// 返回：没有返回值。
	void CalcDeltaRn(int nPtCount, double *pInputY, double *pOutputY, double dAverage);
	// 函数 CalcFluTurbidityAdjust
	// 作用：计算CalcFluTurbidityAdjust。
	// 参数：iCtMOT：整数；iCtPos：整数；dAdjustRatio：小数；nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；pOutputY：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void CalcFluTurbidityAdjust(int iCtMOT, int iCtPos, double dAdjustRatio, int nPtCount, double* pInputX, double *pInputY, double *pOutputY);
	// 函数 AbleToCalculateCt
	// 作用：执行AbleToCalculateCt。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；bNormalized：是或否。
	// 返回：返回是或否。
	BOOL AbleToCalculateCt(int nPtCount, double *pInputX, double *pInputY, BOOL bNormalized);
	// 函数 NewAutoFindCrest
	// 作用：执行NewAutoFindCrest。
	// 参数：nCrestNum：整数；nPtNum：整数；dXValue：小数；dYValue：小数；dReturn：小数；pDCrestIndex：指针，指向调用方传入的对象；dThrePercent：小数；dHandSetThre：小数；bPosFstDerivative：是或否。
	// 返回：没有返回值。
	void NewAutoFindCrest(int nCrestNum,int nPtNum,double *dXValue,double *dYValue,double *dReturn,int* pDCrestIndex,double dThrePercent = 0.2,double dHandSetThre = 0,BOOL bPosFstDerivative = FALSE);

	// 函数 FindStartPlateauCycle
	// 作用：执行FindStartPlateauCycle。
	// 参数：iCycleCount：整数；pdInputX；pdInputY；dCt：小数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int FindStartPlateauCycle(int iCycleCount, double *pdInputX, double *pdInputY, double dCt);

	// 函数 CalcBaselinePosOfNoCt
	// 作用：计算CalcBaselinePosOfNoCt。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iStart：整数；iEnd：整数。
	// 返回：没有返回值。
	void CalcBaselinePosOfNoCt(int nPtCount, double *pInputX, double *pInputY, int &iStart, int &iEnd);
	// 函数 CalcLegalLineFitParam
	// 作用：计算CalcLegalLineFitParam。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；dReturn：小数；iMinPtCount：整数；dMinR：小数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalcLegalLineFitParam(int nPtCount, double *pInputX, double *pInputY, double *dReturn, int &iMinPtCount, double dMinR);
	// 函数 FindPeakAmlBySlope
	// 作用：执行FindPeakAmlBySlope。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iWndWidth：整数。
	// 返回：返回是或否。
	BOOL FindPeakAmlBySlope(int nPtCount, double *pInputX, double *pInputY, int iWndWidth=5);
	// 函数 AbleToCalculateCtBySndDerivative
	// 作用：执行AbleToCalculateCtBySndDerivative。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；dMinValue：小数；iValueCount：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AbleToCalculateCtBySndDerivative(int nPtCount, double *pInputX, double *pInputY, double dMinValue, int iValueCount=3);

protected:
	// 函数 CalcFluDataByCtAndMOT
	// 作用：计算CalcFluDataByCtAndMOT。
	// 参数：nStartNo：整数；nCycleCount：整数；pdValueY；dChangedRatio：小数；pdOutputY。
	// 返回：没有返回值。
	void CalcFluDataByCtAndMOT(int nStartNo, int nCycleCount, double* pdValueY, double dChangedRatio, double* pdOutputY);
	// 函数 CalculateSD
	// 作用：计算CalculateSD。
	// 参数：iDataCount：整数；pInputData：指针，指向调用方传入的对象。
	// 返回：返回一个小数。
	double CalculateSD(int iDataCount, double* pInputData);
	// 函数 MeetForeAvgAndEndAvgCondition
	// 作用：执行MeetForeAvgAndEndAvgCondition。
	// 参数：iDataCount：整数；pInputData：指针，指向调用方传入的对象；peakAmlChkParam。
	// 返回：返回是或否。
	BOOL MeetForeAvgAndEndAvgCondition(int iDataCount, double* pInputData, CPeakAmlCheckParam& peakAmlChkParam);

protected:
	tagFunAbleToCalcuParamInfo m_tagAbleToCalcuParam; ///< 判定曲线是否满足计算的相关参数信息 
	tagFunAmpNormalizedAnaParamInfo m_tagAmpNormalizedAnaParam; ///< 扩增曲线归一化处理相关参数信息
};

