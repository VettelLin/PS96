// 【交接】 PCRInstanceLib\InstanceDemo.h
// 作用：InstanceDemo。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInstanceDemo、Initialize、Hello、ReadDeviceParamsFromEPROM、ReadStructureParamsFromEPROM、Home、MotorScanRow、SetStateLED。
#pragma once

#include "InstancePCR.h"

class AFX_EXT_CLASS CInstanceDemo : public CInstancePCR
{
public:
	// 函数 CInstanceDemo
	// 作用：执行CInstanceDemo。
	// 参数：pComPort：指针，指向调用方传入的对象；strVersion：字符串。
	// 返回：没有返回值。
	CInstanceDemo(CSerialPortPCR* pComPort, CString strVersion);
	// 函数 ~CInstanceDemo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CInstanceDemo(void);

// Operations
public:	
	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL Initialize();
	// 函数 Hello
	// 作用：执行Hello。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL Hello();
	// 函数 ReadDeviceParamsFromEPROM
	// 作用：读取ReadDeviceParamsFromEPROM。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ReadDeviceParamsFromEPROM();
	// 函数 ReadStructureParamsFromEPROM
	// 作用：读取ReadStructureParamsFromEPROM。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ReadStructureParamsFromEPROM();
	// 函数 Home
	// 作用：执行Home。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL Home();
	// 函数 MotorScanRow
	// 作用：执行MotorScanRow。
	// 参数：wPulse；cDirection：矩形区域。
	// 返回：返回是或否。
	virtual BOOL MotorScanRow(WORD wPulse, BYTE cDirection); // 默认X电机

	// 函数 SetStateLED
	// 作用：设置SetStateLED。
	// 参数：cMode。
	// 返回：返回是或否。
	virtual BOOL SetStateLED(BYTE cMode);
	// 函数 SetPMTGain
	// 作用：设置SetPMTGain。
	// 参数：wGainPara。
	// 返回：返回是或否。
	virtual BOOL SetPMTGain(WORD wGainPara);
	// 函数 SetTempCtrlMode
	// 作用：设置SetTempCtrlMode。
	// 参数：nCtrlMode：整数。
	// 返回：返回是或否。
	virtual BOOL SetTempCtrlMode(eTempCtrlMode nCtrlMode);// 控温方式？是否控温
	// 函数 SetLidHeaterTemp
	// 作用：设置SetLidHeaterTemp。
	// 参数：fTemp：小数。
	// 返回：返回是或否。
	virtual BOOL SetLidHeaterTemp(float fTemp); // 设置热盖温度
	// 函数 SetMultiTemp
	// 作用：设置SetMultiTemp。
	// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数；fRate：小数；cMode。
	// 返回：返回是或否。
	virtual BOOL SetMultiTemp(float fTemp1, float fTemp2, float fTemp3, float fRate, BYTE cMode);
	// 函数 SetLaserStatus
	// 作用：设置SetLaserStatus。
	// 参数：cType；cStatus：字符串。
	// 返回：返回是或否。
	virtual BOOL SetLaserStatus(BYTE cType, BYTE cStatus);

	// 函数 ScanOnce
	// 作用：执行ScanOnce。
	// 参数：pBeAskTop：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL ScanOnce(BOOL *pBeAskTop);
	// 函数 ReadChannelTemp
	// 作用：读取ReadChannelTemp。
	// 参数：cChannel；fTempCh：小数；bToTarget：是或否。
	// 返回：返回是或否。
	virtual BOOL ReadChannelTemp(BYTE cChannel, float &fTempCh, BOOL& bToTarget); // 读取指定通道温度
	// 函数 ReadPCRTemp
	// 作用：读取ReadPCRTemp。
	// 参数：fTempPCR：小数；bToTarget：是或否。
	// 返回：返回是或否。
	virtual BOOL ReadPCRTemp(float &fTempPCR, BOOL& bToTarget); // 读取PCR仪温度
	// 函数 ReadFLUData
	// 作用：读取ReadFLUData。
	// 参数：arrayData；cChannel；cFrmIndex。
	// 返回：返回是或否。
	virtual BOOL ReadFLUData(CUIntArray& arrayData, BYTE cChannel, BYTE cFrmIndex=1);

	// 函数 ReadDeviceStatus
	// 作用：读取ReadDeviceStatus。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ReadDeviceStatus();

	//添加于20220415，孙文郎
	// 函数 ReadEPROM
	// 作用：读取ReadEPROM。
	// 参数：nAddress：整数；cGetLength；pReceive：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL ReadEPROM(UINT nAddress, BYTE cGetLength,BYTE* pReceive);
	// 函数 WriteEPROM
	// 作用：把WriteEPROM写入文件、仪器或界面。
	// 参数：nAddress：整数；iData：整数；iDataLen：整数。
	// 返回：返回是或否。
	virtual BOOL WriteEPROM(UINT nAddress,int iData,int iDataLen);

	// 函数 GetInitChanDyeName
	// 作用：读取GetInitChanDyeName。
	// 参数：vecChanDyeName。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetInitChanDyeName(vector<CString>& vecChanDyeName);	//新建实验时，初始化每个通道的染料名称标识

	// 函数 IsDemo
	// 作用：判断IsDemo是否成立。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL IsDemo();	//判断是否是Demo

			// 函数 ReadParaFromDemo
			// 作用：读取ReadParaFromDemo。
			// 参数：strIniFile：字符串。
			// 返回：没有返回值。
			void ReadParaFromDemo(CString strIniFile);

protected:
	// 函数 InitStructurePara
	// 作用：初始化InitStructurePara。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitStructurePara();
	// 模拟数据
	// 函数 InitFluData
	// 作用：初始化InitFluData。
	// 参数：无。
	// 返回：没有返回值。
	void InitFluData(); // 初始化各通道荧光数据
	// 函数 InitOneDyeFluData
	// 作用：初始化InitOneDyeFluData。
	// 参数：pArrayFlu：指针，指向调用方传入的对象；strIniFile：字符串。
	// 返回：没有返回值。
	void InitOneDyeFluData(CUIntArray* pArrayFlu, CString strIniFile);
	// 函数 GetFluDataBy
	// 作用：读取GetFluDataBy。
	// 参数：iTubeIndex：整数；pArrayFlu：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	UINT GetFluDataBy(int iTubeIndex, CUIntArray* pArrayFlu);

public:
	// 函数 GetModel
	// 作用：读取GetModel。
	// 参数：无。
	// 返回：返回一段文字。
	virtual CString GetModel();

	// 函数 InitDemoData
	// 作用：初始化InitDemoData。
	// 参数：iTubeCount：整数。
	// 返回：没有返回值。
	void InitDemoData(int iTubeCount);
	// 函数 GetMaxLidHeatSecond
	// 作用：读取GetMaxLidHeatSecond。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetMaxLidHeatSecond(); // 取得热盖加热最长时间

protected:
	CUIntArray	m_arrayTemp; // 温度数据
	int		m_iCurTempIndex; // 当前温度位置

	CUIntArray	m_arrayFluFam; // 通道1
	CUIntArray  m_arrayFluCy5; // 通道2
	CUIntArray	m_arrayFluHex; // 通道3
	CUIntArray	m_arrayFluCy55; // 通道4
	CUIntArray	m_arrayFluRox; // 通道5
	CUIntArray	m_arrayFluCy3; // 通道6

	int		m_iTubeCount; // 孔板管数
	int		m_iCurCycleNo; // 当前循环数
	int		m_iFirstChannelNo;

	int*	m_pCurFluIndex; // 孔板各管位对应荧光数据开始位置
};

