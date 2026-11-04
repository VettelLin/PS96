// 【交接】 PCRCtrlLib\PCRAlgorithmLib\DataAlgorithmPCR.h
// 作用：DataAlgorithmPCR。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：structNormalizeParaminfo、tagFunAbleToCalcuParamInfo、tagFunAmpNormalizedAnaParamInfo、CDataAlgorithmPCR、FindCrestWithParabola、CalDerivative、NewCalDerivative、LinearFit。
#pragma once
#include <afxtempl.h>
#include <vector>
#include "DataAlgorithm.h"


//归一化分析参数结构(熔曲)
typedef struct structNormalizeParaminfo
{
	bool	bAble;			//可否进行归一化
	int		nMinPos;		//归一化最小值位置
	int     nMaxPos;        //归一化最大值位置 
	float   fMinTemp;
	float   fMaxTemp;
	// 函数 structNormalizeParaminfo
	// 作用：执行structNormalizeParaminfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	structNormalizeParaminfo()
	{
		bAble = false;
		nMinPos = -1;
		nMaxPos = -1;
		fMinTemp = 0;
		fMaxTemp = 0;
	}

}NORMAPARAMINFO, *PNORMAPARAMINFO;

typedef struct tagFunAbleToCalcuParamInfo
{
	 bool bNormalization;
	 int  nCurveType;
	 double  dAmpNoNormalizeStd;
	 double  dAmpNoNormalizeRatio;
	 double  dAmpNormalizeStd;
	 double  dAmpNormalizeRatio;

	 double  dFDNoNormalizeVal;
	 double  dFDNoNormalizeRatio;
	 double  dFDNormalizeVal;
	 double  dFDNormalizeRatio;

	 double  dMeltNoNormalizeStd;
	 double  dMeltNoNormalizeRatio;
	 double  dMeltNormalizeStd;
	 double  dMeltNormalizeRatio;

	 int bkCalcDotNum;
	 double dCrestBkRatio;

	 tagFunAbleToCalcuParamInfo()
	 {
		 bNormalization = false;
		 nCurveType = 0;//0，扩增曲线；1，普通熔解曲线；2，蛋白熔曲
		 dAmpNoNormalizeStd = 45;
		 dAmpNoNormalizeRatio = 1.1;
		 dAmpNormalizeStd = 0.007;
		 dAmpNormalizeRatio = 1.1;

		 dFDNoNormalizeVal = 40;
		 dFDNoNormalizeRatio = 2;
		 dFDNormalizeVal  = 0.01;
		 dFDNormalizeRatio = 2;

		 dMeltNoNormalizeStd = 45;
		 dMeltNoNormalizeRatio = 1.1;
		 dMeltNormalizeStd = 0.01;
		 dMeltNormalizeRatio = 1.1;

		 bkCalcDotNum = 3;
		 dCrestBkRatio = 0.001;		//原值：0.002，修改于20200608，和IsPeakAml保持一致,孙文郎
	 }
}FUNABLETOCALCUPARAMINFO, *PFUNABLETOCALCUPARAMINFO;

typedef struct tagFunAmpNormalizedAnaParamInfo
{
	bool bAbleToCalcu;
	int nAvgNum;  
	int nNormalizeStartPreXPos;
	int nFiltNum;       

	bool bBaseCorrection; 
	double  dBCK;
	double  dBCR2;    
	int     nBCXPosThre;
	int     nBCStart;     
	int     nBCEndPreXPos; 
	int     nBCEndPreNumPos;

	bool bMinus1;  

	bool bBaseSuppression;
	double  dBSRatioAllData;  
	double  dBSRatioBaseLine;

	// 函数 tagFunAmpNormalizedAnaParamInfo
	// 作用：执行tagFunAmpNormalizedAnaParamInfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	tagFunAmpNormalizedAnaParamInfo()
	{
		bAbleToCalcu = false;
		nAvgNum = 3;  
		nNormalizeStartPreXPos = 5;
		nFiltNum = 4;       
		bBaseCorrection = true; 
		dBCK = 0xFFFF;
		dBCR2 = 0.5;    
		nBCXPosThre = 10;
		nBCStart = 1;     
		nBCEndPreXPos = 3; 
		nBCEndPreNumPos = 0;
		bMinus1 = false;  
		bBaseSuppression = true;
		dBSRatioAllData =0.5;  
		dBSRatioBaseLine=0.5;
	}
}FUNAMPNORMALIZEDANAPARAMINFO,*PFUNAMPNORMALIZEDANAPARAMINFO;


class AFX_EXT_CLASS CDataAlgorithmPCR : public CDataAlgorithm
{
public:
	// 函数 CDataAlgorithmPCR
	// 作用：执行CDataAlgorithmPCR。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CDataAlgorithmPCR(void);
	// 函数 ~CDataAlgorithmPCR
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CDataAlgorithmPCR(void);

	// 滤波类型
	enum eDigitalFilterType
	{
		FILTERTYPE_CFMEAN3 = 0,            ///< 中点滑动平均3点
		FILTERTYPE_CFMEAN5 = 1,			   ///< 中点滑动平均5点	
		FILTERTYPE_CFMEAN7 = 2,			   ///< 中点滑动平均7点
		FILTERTYPE_CFMEAN9 = 14,
		FILTERTYPE_CFMEAN11 = 15,          
		FILTERTYPE_CFMEAN13 = 16,
		FILTERTYPE_CFMEAN15 = 17,
		FILTERTYPE_CFMEAN17 = 18,
		FILTERTYPE_CFMEAN19 = 19,
		FILTERTYPE_CFMEAN21 = 20,
		FILTERTYPE_CFMEAN23 = 21,
		FILTERTYPE_CFMEAN25 = 22,
		FILTERTYPE_CFMEAN27 = 23,
		FILTERTYPE_CFMEAN29 = 24,
		FILTERTYPE_CFMEAN31 = 25,

		FILTERTYPE_MEDIAN = 26,

		FILTERTYPE_QuadraticSmooth_5 = 3,	///< 五点两次
		FILTERTYPE_CubicSmooth_5 = 4,		///< 五点三次
		FILTERTYPE_QuadraticSmooth_7 = 5,	///< 七点两次
		FILTERTYPE_CubicSmooth_7 = 6,		///< 七点三次

		FILTERTYPE_DTMEAN3 = 7,				///< 前置滑动平均3点
		FILTERTYPE_DTMEAN4 = 8,				///< 前置滑动平均4点
		FILTERTYPE_DTMEAN5 = 9,				///< 前置滑动平均5点
		FILTERTYPE_DTMEAN6 = 10,				///< 前置滑动平均6点
		FILTERTYPE_DTMEAN7 = 11,				///< 前置滑动平均7点

		FILTERTYPE_TriangularSmooths_29 = 12,///< 29点三角滤波
		FILTERTYPE_GaussianSmooths_31 = 13  ///< 31点伪高斯
	};


public:
	// 函数 FindCrestWithParabola
	// 作用：执行FindCrestWithParabola。
	// 参数：x；y；nNum：整数；nWndWidth：整数。
	// 返回：返回一个小数。
	double FindCrestWithParabola(double *x, double *y, int nNum, int nWndWidth);

	//计算一阶/二阶导数	
	// 函数 CalDerivative
	// 作用：执行CalDerivative。
	// 参数：x；y；nNum：整数；nDev：整数；dReturn：小数。
	// 返回：没有返回值。
	void CalDerivative(double *x, double *y, int nNum,int nDev,double *dReturn);
	// 函数 NewCalDerivative
	// 作用：执行NewCalDerivative。
	// 参数：x；y；nNum：整数；nDev：整数；dReturn：小数。
	// 返回：没有返回值。
	void NewCalDerivative(double *x, double *y, int nNum,int nDev,double *dReturn);

	//线性拟合
	// 函数 LinearFit
	// 作用：执行LinearFit。
	// 参数：x；y；nNum：整数；dReturn：小数。
	// 返回：没有返回值。
	void LinearFit(double *x, double *y,int nNum, double *dReturn);

	//数字滤波	
	// 函数 DigitalFilter
	// 作用：执行DigitalFilter。
	// 参数：x；dReturn：小数；nNum：整数；eType；nWnd：整数。
	// 返回：没有返回值。
	void DigitalFilter(double *x, double *dReturn, int nNum, eDigitalFilterType eType = FILTERTYPE_CubicSmooth_5,int nWnd = 3);

	//插值计算某一点值
	// 函数 Spline
	// 作用：执行Spline。
	// 参数：x；y；nNum：整数；xCur；yCur。
	// 返回：没有返回值。
	void Spline(double *x, double *y, int nNum, double xCur,double &yCur);
	// 函数 SplineEx
	// 作用：执行SplineEx。
	// 参数：x；y；nNum：整数；xCur；yCur。
	// 返回：没有返回值。
	void SplineEx(double *x, double *y, int nNum, double xCur,double &yCur);

	//数组中的元素头尾两端依次对调
	// 函数 Reverse_array
	// 作用：执行Reverse_array。
	// 参数：x；nNum：整数；dReturn：小数。
	// 返回：没有返回值。
	void Reverse_array(double *x,int nNum, double *dReturn);
	// 函数 findPeak
	// 作用：执行findPeak。
	// 参数：v；peakPositions。
	// 返回：没有返回值。
	void findPeak(const std::vector<int>& v, std::vector<int>& peakPositions);
	// 函数 GetDoublePrecision
	// 作用：读取GetDoublePrecision。
	// 参数：dValue：小数；nPres：整数。
	// 返回：返回一个小数。
	double GetDoublePrecision(double dValue,int nPres);

/*----------------------用户调用的函数--------------------------------------------------*/
	// 函数 KdsptForwardMBackN
	// 作用：执行KdsptForwardMBackN。
	// 参数：n；pY：指针，指向调用方传入的对象；pReturn：指针，指向调用方传入的对象；forwardM；backwardN。
	// 返回：没有返回值。
	void KdsptForwardMBackN(int n, double *pY, double *pReturn,int forwardM,int backwardN);	//数字滤波，前M点后N点,共M + N + 1点,五点中心滤波尾端使用特殊不收缩算法

	// 函数 KdsptForwardMBackN_New
	// 作用：执行KdsptForwardMBackN_New。
	// 参数：n；pY：指针，指向调用方传入的对象；pReturn：指针，指向调用方传入的对象；forwardM；backwardN。
	// 返回：没有返回值。
	void KdsptForwardMBackN_New(int n, double *pY, double *pReturn,int forwardM,int backwardN);	//数字滤波，前M点后N点,共M + N + 1点,五点中心滤波尾端使用逐渐收缩算法

	// 函数 KdsptForwardMBackN_NoShrink
	// 作用：执行KdsptForwardMBackN_NoShrink。
	// 参数：n；pY：指针，指向调用方传入的对象；pReturn：指针，指向调用方传入的对象；forwardM；backwardN。
	// 返回：没有返回值。
	void KdsptForwardMBackN_NoShrink(int n, double *pY, double *pReturn,int forwardM,int backwardN);	//数字滤波，前M点后N点,共M + N + 1点，首尾不收缩

	// 函数 GenStdCurveByStd
	// 作用：执行GenStdCurveByStd。
	// 参数：nCurveNum：整数；nPtNum：整数；nStar：整数；nEnd：整数；nMultiple：整数；dX：小数；dY：小数；dCt：小数；dLinePara：小数；bStdCurve：是或否；bBaseLine：是或否。
	// 返回：没有返回值。
	void GenStdCurveByStd(int nCurveNum,int nPtNum, int nStar, int nEnd, int nMultiple,double *dX, double *dY,double *dCt,double *dLinePara,bool bStdCurve,bool bBaseLine);
	// 函数 FirstNegDerivative
	// 作用：执行FirstNegDerivative。
	// 参数：nCurveNum：整数；nPtNum：整数；dX：小数；dY：小数；dXReturn：小数；dYReturn：小数。
	// 返回：没有返回值。
	void FirstNegDerivative(int nCurveNum, int nPtNum, double *dX, double *dY, double *dXReturn, double *dYReturn);
	// 函数 DataDigitalFilter
	// 作用：执行DataDigitalFilter。
	// 参数：nCurveNum：整数；nPtNum：整数；dX：小数；dY：小数；dYReturn：小数。
	// 返回：没有返回值。
	void DataDigitalFilter(int nCurveNum, int nPtNum, double *dX, double *dY, double *dYReturn);
	// 函数 DataSmooth
	// 作用：执行DataSmooth。
	// 参数：nCurveNum：整数；nPtNum：整数；nWidth：整数；dY：小数；dYReturn：小数。
	// 返回：没有返回值。
	void DataSmooth(int nCurveNum, int nPtNum, int nWidth, double *dY, double *dYReturn);
	// 函数 AdjustBaseLine
	// 作用：执行AdjustBaseLine。
	// 参数：nNum：整数；nAvgNum：整数；pInput：指针，指向调用方传入的对象；pOutput：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void AdjustBaseLine(int nNum, int nAvgNum, double *pInput, double *pOutput);
	// 函数 NewAdjustBaseLine
	// 作用：执行NewAdjustBaseLine。
	// 参数：nNum：整数；start；end；pInput：指针，指向调用方传入的对象；pOutput：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void NewAdjustBaseLine(int nNum, int start,int end, double *pInput, double *pOutput);
	// 函数 AdjustBaseLine
	// 作用：执行AdjustBaseLine。
	// 参数：nNum：整数；nAvgNum：整数；pdx；pdyInput；pdyOutput；bNormalization：是或否。
	// 返回：没有返回值。
	void AdjustBaseLine(int nNum, int nAvgNum, double *pdx,double *pdyInput, double *pdyOutput,bool bNormalization = false);
	// 函数 NewAdjustBaseLine
	// 作用：执行NewAdjustBaseLine。
	// 参数：nNum：整数；forewardNum；calcDotNum；pdx；pdyInput；pdyOutput；bNormalization：是或否。
	// 返回：没有返回值。
	void NewAdjustBaseLine(int nNum,int forewardNum,int calcDotNum,double *pdx,double *pdyInput, double *pdyOutput,bool bNormalization  = false );
	// 函数 CalculatedDeltaRn
	// 作用：计算CalculatedDeltaRn。
	// 参数：nNum：整数；nStart：整数；nEnd：整数；pInput：指针，指向调用方传入的对象；pOutput：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void CalculatedDeltaRn(int nNum, int nStart,int nEnd, double *pInput, double *pOutput);
	// 函数 SortDouble
	// 作用：执行SortDouble。
	// 参数：nNum：整数；pInput：指针，指向调用方传入的对象；pOutput：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void SortDouble(int nNum, double *pInput, double *pOutput);
	// 函数 SortInt
	// 作用：执行SortInt。
	// 参数：nNum：整数；pInput：指针，指向调用方传入的对象；pOutput：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void SortInt(int nNum, int *pInput, int *pOutput);
    void AutoFindCrest(int nCrestNum,int nPtNum, double *dXValue, double *dYValue, double *dReturn,double dThrePercent = 0.2);
	// 函数 AbleToCalculate
	// 作用：执行AbleToCalculate。
	// 参数：dx；dy；nNum：整数；bNormalization：是或否；bCt：是或否。
	// 返回：返回是或否。
	BOOL AbleToCalculate(double *dx, double *dy, int nNum,bool bNormalization = false,bool bCt = true);
	// 函数 AbleToCalculateEx
	// 作用：执行AbleToCalculateEx。
	// 参数：dx；dy；nNum：整数；bNormalization：是或否；bCt：是或否。
	// 返回：返回是或否。
	BOOL AbleToCalculateEx(double *dx, double *dy, int nNum,bool bNormalization = false,bool bCt = true);
	// 函数 AbleToCalculate
	// 作用：执行AbleToCalculate。
	// 参数：dx；dy；nNum：整数；paraminfo。
	// 返回：返回是或否。
	BOOL AbleToCalculate(double *dx, double *dy, int nNum,tagFunAbleToCalcuParamInfo paraminfo);

	// 函数 NewAbleToCalculate
	// 作用：执行NewAbleToCalculate。
	// 参数：dx；dy；nNum：整数；paraminfo；newStart；newForwardNum；newStdNum。
	// 返回：返回是或否。
	BOOL NewAbleToCalculate(double *dx, double *dy, int nNum,tagFunAbleToCalcuParamInfo paraminfo,int newStart = 1,int newForwardNum = 3,float newStdNum = 3);

	// 函数 NormalizedAnalysis
	// 作用：执行NormalizedAnalysis。
	// 参数：nNum：整数；nAvgNum：整数；nNormType：整数；bMinus1：是或否；pInput：指针，指向调用方传入的对象；pOutput：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void NormalizedAnalysis(int nNum,int nAvgNum,int nNormType,bool bMinus1, double *pInput, double *pOutput);
	// 函数 NormalizedAnalysisBySndDerivative
	// 作用：执行NormalizedAnalysisBySndDerivative。
	// 参数：nNum：整数；nAvgNum：整数；pdx；pdyInput；pdyOutput；nFiltNum：整数；bMinus1：是或否；bkSuppression；baseCorrection：矩形区域。
	// 返回：没有返回值。
	void NormalizedAnalysisBySndDerivative(int nNum, int nAvgNum, double *pdx,double *pdyInput, double *pdyOutput,int nFiltNum = 4,bool bMinus1 = false,bool bkSuppression = false,bool baseCorrection = false);
	// 函数 NormalizedAnalysisBySndDerivative
	// 作用：执行NormalizedAnalysisBySndDerivative。
	// 参数：nNum：整数；pdx；pdyInput；pdyOutput；paraminfo。
	// 返回：没有返回值。
	void NormalizedAnalysisBySndDerivative(int nNum, double *pdx,double *pdyInput, double *pdyOutput,tagFunAmpNormalizedAnaParamInfo paraminfo);

	// 函数 NormalizedAnalysisFrom0To1BySndDerivative
	// 作用：执行NormalizedAnalysisFrom0To1BySndDerivative。
	// 参数：nNum：整数；nmaxpos；nminpos；dminTemp；dmaxTemp；pdx；pdyInput；pdyOutput。
	// 返回：没有返回值。
	void NormalizedAnalysisFrom0To1BySndDerivative(int nNum,int nmaxpos,int nminpos,double dminTemp,double dmaxTemp,double *pdx,double *pdyInput, double *pdyOutput);
	// 函数 FindMinPosAndMaxPosByNormalizeFrom0To1ByFirstDerivative
	// 作用：执行FindMinPosAndMaxPosByNormalizeFrom0To1ByFirstDerivative。
	// 参数：nNum：整数；pdx；pdyInput；nMin：整数；nMax：整数；nFiltNum：整数；dThrePercent：小数。
	// 返回：没有返回值。
	void FindMinPosAndMaxPosByNormalizeFrom0To1ByFirstDerivative(int nNum,double *pdx,double *pdyInput,int &nMin,int &nMax,int nFiltNum = 4, double dThrePercent = 0.2);
	// 函数 DeltaRnAnalysisBySndDerivative
	// 作用：执行DeltaRnAnalysisBySndDerivative。
	// 参数：nNum：整数；pdx；pdyInput；pdyOutput；paraminfo。
	// 返回：没有返回值。
	void DeltaRnAnalysisBySndDerivative(int nNum, double *pdx,double *pdyInput, double *pdyOutput,tagFunAmpNormalizedAnaParamInfo paraminfo);
	// 函数 Median
	// 作用：执行Median。
	// 参数：x；nNum：整数。
	// 返回：返回一个小数。
	double Median(double* x,int nNum);

	// 函数 CalcCycleOfMaxMOTRatioBy
	// 作用：计算CalcCycleOfMaxMOTRatioBy。
	// 参数：nCycleCount：整数；pdXValue；pdYValueMOT；dMinRatio：小数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalcCycleOfMaxMOTRatioBy(int nCycleCount, double* pdXValue, double* pdYValueMOT, double dMinRatio);
	// 函数 CalMeltFirstDerivative
	// 作用：执行CalMeltFirstDerivative。
	// 参数：x；y；nNum：整数；bBackMinusFront：是或否；stepNum；dReturn：小数。
	// 返回：没有返回值。
	void CalMeltFirstDerivative(double *x, double *y, int nNum,BOOL bBackMinusFront,int stepNum,double *dReturn);

	// 函数 CalcAutoBaselineByMinStd
	// 作用：计算CalcAutoBaselineByMinStd。
	// 参数：nPtCount：整数；pInputY：指针，指向调用方传入的对象；iOutStart：整数；iOutEnd：整数。
	// 返回：没有返回值。
	void CalcAutoBaselineByMinStd(int nPtCount, double *pInputY, int &iOutStart, int &iOutEnd);
	// 函数 CalcAutoBaselinePos
	// 作用：计算CalcAutoBaselinePos。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iOutStart：整数；iOutEnd：整数。
	// 返回：返回一个小数。
	double CalcAutoBaselinePos(int nPtCount, double *pInputX, double *pInputY, int &iOutStart, int &iOutEnd);
	// 函数 CalcBaselinePosByCt
	// 作用：计算CalcBaselinePosByCt。
	// 参数：nPosMax：整数；iOutStart：整数；iOutEnd：整数。
	// 返回：没有返回值。
	void CalcBaselinePosByCt(int nPosMax, int &iOutStart, int &iOutEnd);
	// 函数 CalcAutoBaselinePosBySndDrvCt
	// 作用：计算CalcAutoBaselinePosBySndDrvCt。
	// 参数：dSndDrvCt：小数；nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iOutStart：整数；iOutEnd：整数。
	// 返回：没有返回值。
	void CalcAutoBaselinePosBySndDrvCt(double dSndDrvCt, int nPtCount, double *pInputX, double *pInputY, int &iOutStart, int &iOutEnd);
	// 函数 CalcBaselineAverage
	// 作用：计算CalcBaselineAverage。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iStart：整数；iEnd：整数。
	// 返回：返回一个小数。
	double CalcBaselineAverage(int nPtCount, double *pInputX, double *pInputY, int iStart, int iEnd);

	// 函数 CalcFirstDerivative
	// 作用：计算CalcFirstDerivative。
	// 参数：iPtCount：整数；pdInputY；pdOutputY。
	// 返回：没有返回值。
	void CalcFirstDerivative(int iPtCount, double *pdInputY, double* pdOutputY);
	// 函数 CalcSecondDerivative
	// 作用：计算CalcSecondDerivative。
	// 参数：iPtCount：整数；pdInputY；pdOutputY。
	// 返回：没有返回值。
	void CalcSecondDerivative(int iPtCount, double *pdInputY, double* pdOutputY);
	// 函数 FindCtPosWithParabola
	// 作用：执行FindCtPosWithParabola。
	// 参数：iPtCount：整数；pdInputX；pdInputY；pdFirstDer；pdSecondDer。
	// 返回：返回一个小数。
	double FindCtPosWithParabola(int iPtCount, double* pdInputX, double *pdInputY, double* pdFirstDer, double* pdSecondDer);
	// 函数 CalcCtPosBySndDerivative
	// 作用：计算CalcCtPosBySndDerivative。
	// 参数：iPtCount：整数；pdInputX；pdInputY。
	// 返回：返回一个小数。
	double CalcCtPosBySndDerivative(int iPtCount, double* pdInputX, double* pdInputY);

	// 函数 GenerateCtOfSndDerivative
	// 作用：计算GenerateCtOfSndDerivative。
	// 参数：iCycleCount：整数；pdInputX；pdInputY；iFilterCount：整数。
	// 返回：返回一个小数。
	double GenerateCtOfSndDerivative(int iCycleCount, double *pdInputX, double *pdInputY, int iFilterCount=4);
	// 函数 GenerateCtOfSpline
	// 作用：计算GenerateCtOfSpline。
	// 参数：iCycleCount：整数；pdInputX；pdInputY；dThreshold：小数。
	// 返回：返回一个小数。
	double GenerateCtOfSpline(int iCycleCount, double *pdInputX, double *pdInputY, double dThreshold);

	// 函数 CalcBaselinePosByLineFit
	// 作用：计算CalcBaselinePosByLineFit。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iEndPos：整数；dMinR：小数；iOutStart：整数；iOutEnd：整数。
	// 返回：没有返回值。
	void CalcBaselinePosByLineFit(int nPtCount, double *pInputX, double *pInputY, int iEndPos, double dMinR, int &iOutStart, int &iOutEnd);
	// 函数 CalcBaselinePosByDeviations
	// 作用：计算CalcBaselinePosByDeviations。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iEndPos：整数；dMinR：小数；iOutStart：整数；iOutEnd：整数。
	// 返回：没有返回值。
	void CalcBaselinePosByDeviations(int nPtCount, double *pInputX, double *pInputY, int iEndPos, double dMinR, int &iOutStart, int &iOutEnd);

	// 函数 FindCtPosBySlope
	// 作用：执行FindCtPosBySlope。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iWndWidth：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int FindCtPosBySlope(int nPtCount, double *pInputX, double *pInputY, int iWndWidth=5);
	// 函数 IsLegalCtByFluo
	// 作用：判断IsLegalCtByFluo是否成立。
	// 参数：nPtCount：整数；pInputX：指针，指向调用方传入的对象；pInputY：指针，指向调用方传入的对象；iCtPos：整数。
	// 返回：返回是或否。
	BOOL IsLegalCtByFluo(int nPtCount, double *pInputX, double *pInputY, int iCtPos);
	// 函数 CalcCtPos
	// 作用：计算CalcCtPos。
	// 参数：iPtCount：整数；pdInputX；pdInputY。
	// 返回：返回一个小数。
	double CalcCtPos(int iPtCount, double* pdInputX, double* pdInputY);

	// 函数 OutputPointerData
	// 作用：执行OutputPointerData。
	// 参数：iDataCount：整数；pOutData：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void OutputPointerData(int iDataCount, double* pOutData);

protected:
	float m_dd2MaxXThre;	//二阶导最大值对应X轴位置小于dd2MaxXThreshold * 循环数(默认值为35)时，比较二阶导最大值是否大于某个数，如果大于，则认为是扩增，反之认为不是扩增
	float m_dd2MaxYThre;	//二阶导最大值阈值

};
