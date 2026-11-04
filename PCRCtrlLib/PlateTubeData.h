// 【交接】 PCRCtrlLib\PlateTubeData.h
// 作用：PlateTubeData。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPlateTubeData、AllocateMemory、DeleteAll、AddCycleX、AddOriginalData、GetCycleX、GetCurrentCycleX、GetChannelFluY。
#pragma once

#include "TubeData.h"


// 所有反应管数据

class AFX_EXT_CLASS CPlateTubeData
{
public:
	// 函数 CPlateTubeData
	// 作用：执行CPlateTubeData。
	// 参数：无。
	// 返回：没有返回值。
	CPlateTubeData(void);
	// 函数 ~CPlateTubeData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPlateTubeData(void);

// Operations
public:
	// 函数 AllocateMemory
	// 作用：执行AllocateMemory。
	// 参数：iTubeCount：整数；iChannelCount：整数。
	// 返回：返回是或否。
	virtual BOOL AllocateMemory(int iTubeCount, int iChannelCount) = 0;
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteAll();
	// 函数 AddCycleX
	// 作用：创建或加入AddCycleX。
	// 参数：pArrayCycle：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void AddCycleX(CUIntArray* pArrayCycle); // 增加全部管的当前循环数或时间
	// 函数 AddOriginalData
	// 作用：创建或加入AddOriginalData。
	// 参数：aryOriData；iChannelID：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddOriginalData(CUIntArray& aryOriData,int iChannelID);

	// 函数 GetCycleX
	// 作用：读取GetCycleX。
	// 参数：iTubeID：整数；iCycleCount：整数；pdValueX；bConstantPCR：是或否。
	// 返回：没有返回值。
	void GetCycleX(int iTubeID, int iCycleCount, double* pdValueX, BOOL bConstantPCR);
	// 函数 GetCycleX
	// 作用：读取GetCycleX。
	// 参数：iTubeID：整数；iCycleId：整数；bConstantPCR：是或否。
	// 返回：返回一个小数。
	double GetCycleX(int iTubeID, int iCycleId, BOOL bConstantPCR);
	// 函数 GetCurrentCycleX
	// 作用：读取GetCurrentCycleX。
	// 参数：iTubeID：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	UINT GetCurrentCycleX(int iTubeID);

	// 函数 GetChannelFluY
	// 作用：读取GetChannelFluY。
	// 参数：iTubeID：整数；nType：整数；iChannel：整数；iCycleCount：整数；pdYValue。
	// 返回：没有返回值。
	void GetChannelFluY(int iTubeID, eDataType nType, int iChannel, int iCycleCount, double* pdYValue);
	// 函数 GetChannelCycleFluY
	// 作用：读取GetChannelCycleFluY。
	// 参数：iTubeID：整数；nType：整数；iChannel：整数；iCycleId：整数。
	// 返回：返回一个小数。
	double GetChannelCycleFluY(int iTubeID, eDataType nType, int iChannel, int iCycleId);	//获取特定通道单个孔位在某个循环的荧光信号值
	// 函数 SetChannelFluY
	// 作用：设置SetChannelFluY。
	// 参数：iTubeID：整数；nType：整数；iChannel：整数；iCycleCount：整数；pdYValue。
	// 返回：没有返回值。
	void SetChannelFluY(int iTubeID, eDataType nType, int iChannel, int iCycleCount, double* pdYValue);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteFile(CFile* pFile);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL ReadFile(CFile* pFile, WORD wVersion);

	// 数据处理
	// 函数 FluChannelCrosstalkAdjust
	// 作用：执行FluChannelCrosstalkAdjust。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pCrosstalkMatrix：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetScanStartPos。
	void FluChannelCrosstalkAdjust(CTubeInfo* pTubeInfo, float** pCrosstalkMatrix);

	//获取数据点个数
	// 函数 GetDataNum
	// 作用：读取GetDataNum。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetScanStartPos。
	int GetDataNum();
	// 函数 GetChannelMaxValueY
	// 作用：读取GetChannelMaxValueY。
	// 参数：nDataType：整数；iTubeID：整数；iChannel：整数。
	// 返回：返回一个小数。
	// 过程：函数里会调用 SetScanStartPos。
	double GetChannelMaxValueY(eDataType nDataType,int iTubeID,int iChannel);

// Attributes
public:
	// 函数 SetScanStartPos
	// 作用：设置SetScanStartPos。
	// 参数：nPos：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetScanStartPos(eScanStartPos nPos) { m_nStartPos = nPos; }
	// 函数 SetColCount
	// 作用：设置SetColCount。
	// 参数：iCount：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetColCount(int iCount) { m_iColCount = iCount; }
	// 函数 GetChannelCount
	// 作用：读取GetChannelCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetChannelCount() { return m_iChannelCount; }
	// 函数 HasData
	// 作用：判断HasData是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL HasData();

protected:
	eScanStartPos m_nStartPos; // 扫描开始位置
	int		m_iColCount;
	int		m_iTubeCount;	//仪器总的试管个数
	int		m_iChannelCount; //仪器总的检测光路通道个数
	CPtrArray	m_arrayTubeData; // 所有数据
};

// 所有反应管扩增数据
class AFX_EXT_CLASS CPlateAmplifyTubeData : public CPlateTubeData
{
public:
	// 函数 CPlateAmplifyTubeData
	// 作用：执行CPlateAmplifyTubeData。
	// 参数：无。
	// 返回：没有返回值。
	CPlateAmplifyTubeData(void) {}
	// 函数 ~CPlateAmplifyTubeData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPlateAmplifyTubeData(void) {}

public:
	// 函数 AllocateMemory
	// 作用：执行AllocateMemory。
	// 参数：iTubeCount：整数；iChannelCount：整数。
	// 返回：返回是或否。
	virtual BOOL AllocateMemory(int iTubeCount, int iChannelCount);

	// 函数 FluDigitalFilter
	// 作用：执行FluDigitalFilter。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iFlag：整数。
	// 返回：没有返回值。
	void FluDigitalFilter(CTubeInfo* pTubeInfo, CPtrArray* pFilterItem, CDataAnalysisPCR* pAlgorithm, int iFlag=0);
	// 函数 FluoAdjustBaseline
	// 作用：执行FluoAdjustBaseline。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void FluoAdjustBaseline(CTubeInfo* pTubeInfo, CDataAnalysisPara* pAnalysisPara, CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity);
	// 函数 FluTurbidityAdjust
	// 作用：执行FluTurbidityAdjust。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void FluTurbidityAdjust(CTubeInfo* pTubeInfo, CCalibrateParaTurbidity* pTurbidity, CDataAnalysisPCR* pAlgorithm);
	// 函数 FluNormalizeAndDeltaRn
	// 作用：执行FluNormalizeAndDeltaRn。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pAnalysisPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；pTurbidity：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void FluNormalizeAndDeltaRn(CTubeInfo* pTubeInfo, CDataAnalysisPara* pAnalysisPara, CDataAnalysisPCR* pAlgorithm, CCalibrateParaTurbidity* pTurbidity);

	// 函数 GenerateCtByTubeID
	// 作用：计算GenerateCtByTubeID。
	// 参数：nDataType：整数；iTubeID：整数；nMethod：整数；pAmplifyPara：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象。
	// 返回：返回一个小数。
	double GenerateCtByTubeID(eDataType nDataType, int iTubeID, eMethodCalculateCt nMethod, tagAnaAmplifyPara* pAmplifyPara, CDataAnalysisPCR* pAlgorithm);
	// 函数 GenerateAutoSplineThreshold
	// 作用：计算GenerateAutoSplineThreshold。
	// 参数：nDataType：整数；iTubeID：整数；iChannel：整数；pAlgorithm：指针，指向调用方传入的对象。
	// 返回：返回一个小数。
	double GenerateAutoSplineThreshold(eDataType nDataType,int iTubeID,int iChannel,CDataAnalysisPCR* pAlgorithm);

	// 函数 SetTubeData
	// 作用：设置SetTubeData。
	// 参数：pVecData：指针，指向调用方传入的对象；iTubeNum：整数；iChanNum：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 CPlateMeltTubeData、AllocateMemory、FluDigitalFilter、AddOriginalData。
	int SetTubeData(vector<double>* pVecData,int iTubeNum,int iChanNum);	//设置样本数据，iTubeNum 和 iChanNum是数据源对应的样本管数和通道数

protected:
	// 滤波参数
};

// 所有反应管熔解数据
class AFX_EXT_CLASS CPlateMeltTubeData : public CPlateTubeData
{
public:
	// 函数 CPlateMeltTubeData
	// 作用：执行CPlateMeltTubeData。
	// 参数：无。
	// 返回：没有返回值。
	CPlateMeltTubeData(void) {}
	// 函数 ~CPlateMeltTubeData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPlateMeltTubeData(void) {}

public:
	// 函数 AllocateMemory
	// 作用：执行AllocateMemory。
	// 参数：iTubeCount：整数；iChannelCount：整数。
	// 返回：返回是或否。
	virtual BOOL AllocateMemory(int iTubeCount, int iChannelCount);

	// 函数 FluDigitalFilter
	// 作用：执行FluDigitalFilter。
	// 参数：pTubeInfo：指针，指向调用方传入的对象；pFilterItem：指针，指向调用方传入的对象；pAlgorithm：指针，指向调用方传入的对象；iFlag：整数。
	// 返回：没有返回值。
	void FluDigitalFilter(CTubeInfo* pTubeInfo, CPtrArray* pFilterItem, CDataAnalysisPCR* pAlgorithm, int iFlag=0);

	// 函数 AddOriginalData
	// 作用：创建或加入AddOriginalData。
	// 参数：aryOriData；iChannelID：整数；dTem：小数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddOriginalData(CUIntArray& aryOriData,int iChannelID,double dTem);
};

