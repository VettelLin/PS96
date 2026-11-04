// 【交接】 PCRCtrlLib\TemperatureData.h
// 作用：TemperatureData。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CTemperatureData、AllocateMemory、AddOneTempData、WriteFile、ReadFile、GetCurTemp、GetCurTempCollectTime、HasData。
#pragma once

#include <vector>
using namespace std;

// 实验过程采集到的温度数据
class AFX_EXT_CLASS CTemperatureData
{
public:
	// 函数 CTemperatureData
	// 作用：执行CTemperatureData。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CTemperatureData(void);
	// 函数 ~CTemperatureData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CTemperatureData(void);

	enum eTempChannel
	{
		TEMP_CH_PET = 0, // 帕尔贴第1个通道
		TEMP_CH_LID, //热盖
	};
	// 函数 AllocateMemory
	// 作用：执行AllocateMemory。
	// 参数：iChannelCount：整数；iLidChannelCount：整数。
	// 返回：返回是或否。
	BOOL AllocateMemory(int iChannelCount,int iLidChannelCount = 1);
	// 函数 AddOneTempData
	// 作用：创建或加入AddOneTempData。
	// 参数：dwTime；nTempCount：整数；pInputTemp：指针，指向调用方传入的对象；bMeltStepRunning：是或否。
	// 返回：没有返回值。
	void AddOneTempData(DWORD dwTime,int nTempCount,UINT* pInputTemp,BOOL bMeltStepRunning = FALSE);

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

	// 函数 GetCurTemp
	// 作用：读取GetCurTemp。
	// 参数：nTempChannel：整数；iChannelNo：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	UINT GetCurTemp(eTempChannel nTempChannel,int iChannelNo = 0);
	// 函数 GetCurTempCollectTime
	// 作用：读取GetCurTempCollectTime。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	DWORD GetCurTempCollectTime();
	// 函数 HasData
	// 作用：判断HasData是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL HasData();

	// 函数 SetChannelTarget
	// 作用：设置SetChannelTarget。
	// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数。
	// 返回：没有返回值。
	void SetChannelTarget(float fTemp1, float fTemp2, float fTemp3);

	// 函数 GetTemDataPtr
	// 作用：读取GetTemDataPtr。
	// 参数：无。
	// 返回：返回指针 vector<UINT>*。指针为空表示没有取到对象。
	vector<UINT>* GetTemDataPtr();

	// 函数 GetDataCount
	// 作用：读取GetDataCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetDataCount();
	// 函数 GetTimeData
	// 作用：读取GetTimeData。
	// 参数：iDataCount：整数；pdValueTime。
	// 返回：没有返回值。
	void GetTimeData(int iDataCount, double* pdValueTime);
	// 函数 GetChannelData
	// 作用：读取GetChannelData。
	// 参数：nTempChannel：整数；iChannelNo：整数；iDataCount：整数；pdValueTemp。
	// 返回：没有返回值。
	void GetChannelData(CTemperatureData::eTempChannel nTempChannel, int iChannelNo, int iDataCount, double* pdValueTemp);

	// 函数 GetOneTimeData
	// 作用：读取GetOneTimeData。
	// 参数：iIndex：整数。
	// 返回：返回一个小数。
	// 过程：函数里会调用 SetUseLidHeater。
	double GetOneTimeData(int iIndex);
	// 函数 GetOneTempData
	// 作用：读取GetOneTempData。
	// 参数：iChannel：整数；iIndex：整数。
	// 返回：返回一个小数。
	// 过程：函数里会调用 SetUseLidHeater。
	double GetOneTempData(int iChannel, int iIndex);

protected:
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetUseLidHeater。
	void DeleteAll();

// Attributes
public:
	// 函数 SetUseLidHeater
	// 作用：设置SetUseLidHeater。
	// 参数：bUseLid：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetUseLidHeater(BOOL bUseLid) { m_bUseLid = bUseLid; }
	// 函数 SetLidChannelCount
	// 作用：设置SetLidChannelCount。
	// 参数：iCount：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLidChannelCount(int iCount) { m_iLidChannelCount = iCount; }
	// 函数 GetLidChannelCount
	// 作用：读取GetLidChannelCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetLidChannelCount() { return m_iLidChannelCount; } 
	// 函数 SetChannelCount
	// 作用：设置SetChannelCount。
	// 参数：iCount：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetChannelCount(int iCount) { m_iChannelCount = iCount; }
	// 函数 GetChannelCount
	// 作用：读取GetChannelCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetChannelCount() { return m_iChannelCount; }

protected:
	BOOL	m_bUseLid; // 是否使用热盖
	int		m_iLidChannelCount; // 热盖通道数
	int		m_iChannelCount; // 温度有几种
	vector<DWORD>*	m_pTimeData; // 采集温度时的时间
	vector<UINT>*	m_pTempData; // 采集温度，是种类阵列数组，单位0.01度

	// 温度数据修正参数
	int		m_iUpDownFlag;
	UINT	m_nTargetChannel1; // 通道1目标值
	UINT	m_nTargetChannel2; // 通道2目标值
	UINT	m_nTargetChannel3; // 通道3目标值
	BOOL	m_bSteadyPeriod; // 是否稳定期

	UINT	m_iChan1PreTem; // 通道1上一个目标值
	UINT	m_iChan2PreTem; // 通道2上一个目标值
	UINT	m_iChan3PreTem; // 通道3上一个目标值
};

