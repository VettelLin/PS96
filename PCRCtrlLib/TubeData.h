// 【交接】 PCRCtrlLib\TubeData.h
// 作用：TubeData。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CTubeData、AllocateMemory、DeleteAll、AddCycleX、AddOriginalData、HasData、GetPointCout、GetCycleX。
#pragma once

#include <vector>
#include "TubeInfo.h"
#include "DataAnalysisPCR.h"
#include "CalibrateParaTurbidity.h"
#include "DataAnalysisPara.h"

using namespace std;

//一个反应管的数据，只有原始数据和处理后数据
class AFX_EXT_CLASS CTubeData
{
public:
	// 函数 CTubeData
	// 作用：执行CTubeData。
	// 参数：无。
	// 返回：没有返回值。
	CTubeData(void);
	// 函数 ~CTubeData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CTubeData(void);

	// 函数 AllocateMemory
	// 作用：执行AllocateMemory。
	// 参数：nChannelCount：整数。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetPointCout、size。
	virtual BOOL AllocateMemory(int nChannelCount);
			// 函数 DeleteAll
			// 作用：更新或清除DeleteAll。
			// 参数：无。
			// 返回：没有返回值。
			// 过程：函数里会调用 GetPointCout、size。
			void DeleteAll();
			// 函数 AddCycleX
			// 作用：创建或加入AddCycleX。
			// 参数：nCycle：整数。
			// 返回：没有返回值。
			// 过程：函数里会调用 GetPointCout、size。
			void AddCycleX(UINT nCycle);
	// 函数 AddOriginalData
	// 作用：创建或加入AddOriginalData。
	// 参数：nChannelNo：整数；nYValue：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPointCout、size。
	virtual void AddOriginalData(int nChannelNo, UINT nYValue);
	// 函数 AddOriginalData
	// 作用：创建或加入AddOriginalData。
	// 参数：nChannelNo：整数；nYValue：整数；dTem：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPointCout、size。
	virtual void AddOriginalData(int nChannelNo, UINT nYValue,double dTem) = 0;
			// 函数 HasData
			// 作用：判断HasData是否成立。
			// 参数：无。
			// 返回：返回是或否。
			// 过程：函数里会调用 GetPointCout、size。
			BOOL HasData();

			// 函数 GetPointCout
			// 作用：读取GetPointCout。
			// 参数：m_pFluOriginal[0].size(。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			// 过程：函数里会调用 size。
			int GetPointCout(){	return m_pFluOriginal[0].size(); }
	// 函数 GetCycleX
	// 作用：读取GetCycleX。
	// 参数：nCycleCount：整数；pdValueX；bConstantPCR：是或否。
	// 返回：没有返回值。
	virtual void GetCycleX(int nCycleCount, double* pdValueX, BOOL bConstantPCR);
	// 函数 GetCycleX
	// 作用：读取GetCycleX。
	// 参数：iCycleId：整数；bConstantPCR：是或否。
	// 返回：返回一个小数。
	virtual double GetCycleX(int iCycleId, BOOL bConstantPCR);
			// 函数 GetCurrentCycleX
			// 作用：读取GetCurrentCycleX。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetCurrentCycleX();
			// 函数 GetChannelFluY
			// 作用：读取GetChannelFluY。
			// 参数：nType：整数；nChannel：整数；nCycleCount：整数；pdYValue。
			// 返回：没有返回值。
			void GetChannelFluY(eDataType nType, int nChannel, int nCycleCount, double* pdYValue);
			// 函数 SetChannelFluY
			// 作用：设置SetChannelFluY。
			// 参数：nType：整数；nChannel：整数；nCycleCount：整数；pdYValue。
			// 返回：没有返回值。
			void SetChannelFluY(eDataType nType, int nChannel, int nCycleCount, double* pdYValue);

			//获取孔位特定通道某个循环的信号值
			// 函数 GetChannelCycleFluY
			// 作用：读取GetChannelCycleFluY。
			// 参数：nType：整数；nChannel：整数；nCycleId：整数。
			// 返回：返回一个小数。
			double GetChannelCycleFluY(eDataType nType, int nChannel, int nCycleId );

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual	BOOL WriteFile(CFile* pFile);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	virtual BOOL ReadFile(CFile* pFile,WORD wVersion);

	// 数据处理
	// 函数 FluChannelCrosstalkAdjust
	// 作用：执行FluChannelCrosstalkAdjust。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pCrosstalkMatrix：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void FluChannelCrosstalkAdjust(CTubeInfo* pTubeInfo, float** pCrosstalkMatrix);

	//获取数据点个数
	// 函数 GetDataNum
	// 作用：读取GetDataNum。
	// 参数：iChannelNo：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetDataNum(int iChannelNo=0);
	// 函数 GetMaxValueY
	// 作用：读取GetMaxValueY。
	// 参数：nDataType：整数；iChannel：整数。
	// 返回：返回一个小数。
	double GetMaxValueY(eDataType nDataType, int iChannel);
	// 函数 CorrectFluoZeroValue
	// 作用：执行CorrectFluoZeroValue。
	// 参数：pTubeInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void CorrectFluoZeroValue(CTubeInfo* pTubeInfo);

protected:
	// 函数 BeAllAllocated
	// 作用：判断BeAllAllocated是否成立。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL BeAllAllocated();	//是否都成功申请了内存空间
	// 函数 GetFluYValueBy
	// 作用：读取GetFluYValueBy。
	// 参数：nType：整数；nChannelNo：整数；nPointNo：整数。
	// 返回：返回一个小数。
	virtual double GetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo);
	// 函数 SetFluYValueBy
	// 作用：设置SetFluYValueBy。
	// 参数：nType：整数；nChannelNo：整数；nPointNo：整数；dYValue：小数。
	// 返回：没有返回值。
	virtual void SetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo, double dYValue);

	// 函数 FluCopyTo
	// 作用：执行FluCopyTo。
	// 参数：nChannelCount：整数；nCycleCount：整数；pBase：指针，指向调用方传入的对象；pTarget：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void FluCopyTo(int nChannelCount, int nCycleCount, vector<UINT>* pBase, vector<double>* pTarget);
	// 函数 FluCopyTo
	// 作用：执行FluCopyTo。
	// 参数：nChannelCount：整数；nCycleCount：整数；pBase：指针，指向调用方传入的对象；pTarget：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void FluCopyTo(int nChannelCount, int nCycleCount, vector<double>* pBase, vector<double>* pTarget);
	// 函数 GetChannelFlu
	// 作用：读取GetChannelFlu。
	// 参数：Type；nChannel：整数；nCycleCount：整数；pdXValue；pdYValue。
	// 返回：没有返回值。
	void GetChannelFlu(eDataType Type, int nChannel, int nCycleCount, double* pdXValue, double* pdYValue);
	// 函数 SetChannelFlu
	// 作用：设置SetChannelFlu。
	// 参数：Type；nChannel：整数；nCycleCount：整数；pdYValue。
	// 返回：没有返回值。
	void SetChannelFlu(eDataType Type, int nChannel, int nCycleCount, double* pdYValue);
	// 函数 FluDigitalFilterBy
	// 作用：执行FluDigitalFilterBy。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；iFlag：整数；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
	// 返回：没有返回值。
	void FluDigitalFilterBy(CTubeInfo* pTubeInfo,CPtrArray* pFilterItem,int iFlag,CDataAnalysisPCR* pAlgorithm, int iDivideFlag);
	// 函数 FluDigitalFilterByChannel
	// 作用：执行FluDigitalFilterByChannel。
	// 参数：iChannelNo：整数；pFilterItem：指针，指向调用方传入的对象；iFlag：整数；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
	// 返回：没有返回值。
	void FluDigitalFilterByChannel(int iChannelNo,CPtrArray* pFilterItem,int iFlag,CDataAnalysisPCR* pAlgorithm, int iDivideFlag);

	// 函数 ConvertToLog10
	// 作用：执行ConvertToLog10。
	// 参数：dInput：小数。
	// 返回：返回一个小数。
	double ConvertToLog10(double dInput);

protected:
	int		m_nChannelCount;
	vector<UINT>	m_viValueX; // 对应循环数或者时间等，如果时间则按照毫秒保存
	vector<UINT>*	m_pFluOriginal;
	vector<double>* m_pFluCrossTalk;
	vector<double>* m_pFluFilterMedian;
	vector<double>* m_pFluBaselineAdjust;
	vector<double>* m_pFluFilter;
	vector<double>* m_pFluTuibitidy; // 使用浊度调整

	CArray<BOOL, BOOL> m_arrayAutoAdjust; // 自动调整荧光数据

};

//扩增段数据，包括原始数据和处理后数据
class AFX_EXT_CLASS CTubeAmplifyData : public CTubeData
{
public:
	// 函数 CTubeAmplifyData
	// 作用：执行CTubeAmplifyData。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 AddOriginalData。
	CTubeAmplifyData(void);
	// 函数 ~CTubeAmplifyData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 AddOriginalData。
	~CTubeAmplifyData(void);

public:
	// 函数 AllocateMemory
	// 作用：执行AllocateMemory。
	// 参数：nChannelCount：整数。
	// 返回：返回是或否。
	// 过程：函数里会调用 AddOriginalData。
	virtual BOOL AllocateMemory(int nChannelCount);
			// 函数 DeleteAll
			// 作用：更新或清除DeleteAll。
			// 参数：无。
			// 返回：没有返回值。
			// 过程：函数里会调用 AddOriginalData。
			void DeleteAll();
	// 函数 AddOriginalData
	// 作用：创建或加入AddOriginalData。
	// 参数：nChannelNo：整数；nYValue：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual void AddOriginalData(int nChannelNo, UINT nYValue);
	// 函数 AddOriginalData
	// 作用：创建或加入AddOriginalData。
	// 参数：nChannelNo：整数；nYValue：整数；ASSERT(FALSE。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual	void AddOriginalData(int nChannelNo,UINT nYValue,double dTem) { ASSERT(FALSE); }

			// 函数 FluDigitalFilter
			// 作用：执行FluDigitalFilter。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
			// 返回：没有返回值。
			void FluDigitalFilter(CTubeInfo* pTubeInfo,CPtrArray* pFilterItem,CDataAnalysisPCR* pAlgorithm, int iDivideFlag);
			// 函数 FluoAdjustBaseline
			// 作用：执行FluoAdjustBaseline。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void FluoAdjustBaseline(CTubeInfo* pTubeInfo, CDataAnalysisPara* pAnalysisPara,CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity);

			// 函数 FluTurbidityAdjust
			// 作用：执行FluTurbidityAdjust。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void FluTurbidityAdjust(CTubeInfo* pTubeInfo, CCalibrateParaTurbidity* pTurbidity,CDataAnalysisPCR* pAlgorithm);

			// 函数 FluNormalizeAndDeltaRn
			// 作用：执行FluNormalizeAndDeltaRn。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void FluNormalizeAndDeltaRn(CTubeInfo* pTubeInfo,CDataAnalysisPara* pAnalysisPara,CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity);

			// 函数 GenerateCt
			// 作用：计算GenerateCt。
			// 参数：nType：整数；nMethod：整数；pAmplifyPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
			// 返回：返回一个小数。
			double GenerateCt(eDataType nType, eMethodCalculateCt nMethod, tagAnaAmplifyPara* pAmplifyPara, CDataAnalysisPCR* pAlgorithm);
			// 函数 GenerateAutoSplineThreshold
			// 作用：计算GenerateAutoSplineThreshold。
			// 参数：nType：整数；iChannel：整数；pAlgorithm：指针，指向调用方传入的对象。
			// 返回：返回一个小数。
			double GenerateAutoSplineThreshold(eDataType nType,int iChannel,CDataAnalysisPCR* pAlgorithm);

protected:
	// 函数 BeAllAllocated
	// 作用：判断BeAllAllocated是否成立。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL BeAllAllocated();
	// 函数 GetFluYValueBy
	// 作用：读取GetFluYValueBy。
	// 参数：nType：整数；nChannelNo：整数；nPointNo：整数。
	// 返回：返回一个小数。
	virtual double GetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo);
	// 函数 SetFluYValueBy
	// 作用：设置SetFluYValueBy。
	// 参数：nType：整数；nChannelNo：整数；nPointNo：整数；dYValue：小数。
	// 返回：没有返回值。
	virtual void SetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo, double dYValue);
			// 函数 CalcFluDataByCtAndMOT
			// 作用：计算CalcFluDataByCtAndMOT。
			// 参数：nChannelNo：整数；nStartNo：整数；nCycleCount：整数；pdYValue；dChangedRatio：小数。
			// 返回：没有返回值。
			void CalcFluDataByCtAndMOT(int nChannelNo, int nStartNo, int nCycleCount, double* pdYValue, double dChangedRatio);
			// 函数 CalcAllCtPosBySndDerivative
			// 作用：计算CalcAllCtPosBySndDerivative。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；iChannelMOT：整数；pAlgorithm：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void CalcAllCtPosBySndDerivative(CTubeInfo* pTubeInfo, int iChannelMOT, CDataAnalysisPCR* pAlgorithm);
			// 函数 CalcFluoDescendPosByCtAndMOT
			// 作用：计算CalcFluoDescendPosByCtAndMOT。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；iCycleOfMOT：整数；pAlgorithm：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcFluoDescendPosByCtAndMOT(CTubeInfo* pTubeInfo, int iCycleOfMOT, CDataAnalysisPCR* pAlgorithm);

			// 函数 GenerateCtOfSpline
			// 作用：计算GenerateCtOfSpline。
			// 参数：iCycleCount：整数；pdInputX；pdInputY；pAmplifyPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；nType：整数。
			// 返回：返回一个小数。
			double GenerateCtOfSpline(int iCycleCount, double *pdInputX, double *pdInputY, tagAnaAmplifyPara* pAmplifyPara, CDataAnalysisPCR* pAlgorithm,eDataType nType);
			// 函数 CalcCycleOfMaxMOTRatio
			// 作用：计算CalcCycleOfMaxMOTRatio。
			// 参数：iCycleCount：整数；pTurbidity：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcCycleOfMaxMOTRatio(int iCycleCount, CCalibrateParaTurbidity* pTurbidity, CDataAnalysisPCR* pAlgorithm);


protected:
	vector<double>* m_pFluNormalize;
	vector<double>* m_pFluDeltaRn;
};

// 熔解段数据，包括原始数据和处理后数据
class AFX_EXT_CLASS CTubeMeltData : public CTubeData
{
public:
	// 函数 CTubeMeltData
	// 作用：执行CTubeMeltData。
	// 参数：无。
	// 返回：没有返回值。
	CTubeMeltData(void);
	// 函数 ~CTubeMeltData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CTubeMeltData(void);

public:
	// 函数 AllocateMemory
	// 作用：执行AllocateMemory。
	// 参数：nChannelCount：整数。
	// 返回：返回是或否。
	virtual BOOL AllocateMemory(int nChannelCount);
	// 函数 BeAllAllocated
	// 作用：判断BeAllAllocated是否成立。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL BeAllAllocated();
			// 函数 DeleteAll
			// 作用：更新或清除DeleteAll。
			// 参数：无。
			// 返回：没有返回值。
			void DeleteAll();
	// 函数 GetFluYValueBy
	// 作用：读取GetFluYValueBy。
	// 参数：nType：整数；nChannelNo：整数；nPointNo：整数。
	// 返回：返回一个小数。
	virtual double GetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo);
	// 函数 SetFluYValueBy
	// 作用：设置SetFluYValueBy。
	// 参数：nType：整数；nChannelNo：整数；nPointNo：整数；dYValue：小数。
	// 返回：没有返回值。
	virtual void SetFluYValueBy(eDataType nType, int nChannelNo, int nPointNo, double dYValue);
	// 函数 GetCycleX
	// 作用：读取GetCycleX。
	// 参数：nCycleCount：整数；pdValueX；bConstantPCR：是或否。
	// 返回：没有返回值。
	virtual void GetCycleX(int nCycleCount,double* pdValueX,BOOL bConstantPCR);
	// 函数 GetCycleX
	// 作用：读取GetCycleX。
	// 参数：iCycleId：整数；bConstantPCR：是或否。
	// 返回：返回一个小数。
	virtual double GetCycleX(int iCycleId,BOOL bConstantPCR);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual	BOOL WriteFile(CFile* pFile);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	virtual BOOL ReadFile(CFile* pFile,WORD wVersion);

			// 函数 AddOriginalData
			// 作用：创建或加入AddOriginalData。
			// 参数：nChannelNo：整数；nYValue：整数；dTem：小数。
			// 返回：没有返回值。
			void AddOriginalData(int nChannelNo,UINT nYValue,double dTem);

			// 函数 FluDigitalFilter
			// 作用：执行FluDigitalFilter。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iDivideFlag：整数。
			// 返回：没有返回值。
			void FluDigitalFilter(CTubeInfo* pTubeInfo, CPtrArray* pFilterItem, CDataAnalysisPCR* pAlgorithm, int iDivideFlag);

protected:
	vector<double>* m_pTem;
	vector<double>* m_pNormalize;	//归一化处理之后的数据，预留
	vector<double>* m_pFstNegReciprocal;	//计算一阶负倒数之后的数据
	vector<double>* m_pGainData;	//增益处理之后的数据,预留
};
