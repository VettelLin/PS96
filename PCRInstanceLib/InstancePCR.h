// 【交接】 PCRInstanceLib\InstancePCR.h
// 作用：InstancePCR。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInstancePCR、Reinitialize、Initialize、Hello、InitDevicePara、ReadEPROM、WriteEPROM、Home。
#pragma once

#include "SerialPortPCR.h"
#include "DeclaresPCR.h"
#include "LinkList.h"
#include "SegItemInfo.h"
#include "SensorMCheckParam.h"
#include "HeatMCheckParam.h"

#include <vector>

using namespace std;

class AFX_EXT_CLASS CInstancePCR
{
public:
	// 函数 CInstancePCR
	// 作用：执行CInstancePCR。
	// 参数：pComPort：指针，指向调用方传入的对象；strVersion：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CInstancePCR(CSerialPortPCR* pComPort, CString strVersion);
	// 函数 ~CInstancePCR
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CInstancePCR(void);

public:
	// 仪器模块说明，外部调用使用
	enum eUnitPCR{
		UNIT_MOTOR_X = 0, // X轴电机
		UNIT_MOTOR_Y, // Y轴电机
		UNIT_MOTOR_Z, // Z轴压紧电机
		UNIT_MOTOR_U, // U轴进出仓电机

		UINT_STATE_LED, // 状态灯
	};
	// 电机移动类型
	enum eMotorMoveFlag{
		MOTOR_MOVE_TO = 0, // 移动到
		MOTOR_FORWARD, // 正向移动
		MOTOR_REVERSE, // 反向移动
	};
	// 系统设置温度参数类型
	enum eSysTempType
	{
		SYS_TEMP_CTRL_TOP = 0, // 系统控温最高温度
		SYS_TEMP_CTRL_LOWER, // 系统控温最低温度
		SYS_TEMP_LID_TOP, // 热盖最高温度
		SYS_TEMP_LID_LOWER, // 热盖最低温度
		SYS_TEMP_PELTIER_LOWER, // 帕尔贴最低保持温度
	};

// Operations
public:
	// 函数 Reinitialize
	// 作用：执行Reinitialize。
	// 参数：无。
	// 返回：返回是或否。
	BOOL Reinitialize();
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
			// 函数 InitDevicePara
			// 作用：初始化InitDevicePara。
			// 参数：strFilename：字符串。
			// 返回：没有返回值。
			void InitDevicePara(CString strFilename);
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

	// 函数 Home
	// 作用：执行Home。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL Home();
	// 函数 IsInBox
	// 作用：判断IsInBox是否成立。
	// 参数：outStatus。
	// 返回：返回是或否。
	virtual BOOL IsInBox(eSysBoxStatus &outStatus); // 是否进仓
	// 函数 InBox
	// 作用：执行InBox。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL InBox();
	// 函数 OutBox
	// 作用：执行OutBox。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OutBox();
	// 函数 MotorReset
	// 作用：执行MotorReset。
	// 参数：nMotorFlag：整数。
	// 返回：返回是或否。
	virtual BOOL MotorReset(eUnitPCR nMotorFlag);
	// 函数 MotorMove
	// 作用：执行MotorMove。
	// 参数：nMotorFlag：整数；wPulse；nMoveFlag：整数。
	// 返回：返回是或否。
	virtual BOOL MotorMove(eUnitPCR nMotorFlag, WORD wPulse, eMotorMoveFlag nMoveFlag);
	// 函数 MotorScanRow
	// 作用：执行MotorScanRow。
	// 参数：wPulse；cDirection：矩形区域。
	// 返回：返回是或否。
	virtual BOOL MotorScanRow(WORD wPulse, BYTE cDirection); // 默认X电机
	// 函数 ScanOnce
	// 作用：执行ScanOnce。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ScanOnce();
	// 函数 ScanOnce
	// 作用：执行ScanOnce。
	// 参数：pBeAskTop：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL ScanOnce(BOOL *pBeAskTop);	// 完成一次扫描全部扫描动作，支持快速停止扫描，20220330，孙文郎

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
	virtual BOOL SetLidHeaterTemp(float fTemp); // 设置热盖温度，实验运行时给下位机下发热盖温度
	// 函数 SetMultiTemp
	// 作用：设置SetMultiTemp。
	// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数；fRate：小数；cMode；bSelfCheck：是或否。
	// 返回：返回是或否。
	virtual BOOL SetMultiTemp(float fTemp1, float fTemp2, float fTemp3, float fRate, BYTE cMode,BOOL bSelfCheck = FALSE);	//设置温度，PID模式
	// 函数 SetPWMTemp
	// 作用：设置SetPWMTemp。
	// 参数：fTemp1：小数；fTemp2：小数；fTemp3：小数；Pwm1；Pwm2；Pwm3。
	// 返回：返回是或否。
	virtual BOOL SetPWMTemp(float fTemp1,float fTemp2,float fTemp3,WORD Pwm1,WORD Pwm2,WORD Pwm3);	//设置温度，PID模式
	// 函数 SetLaserStatus
	// 作用：设置SetLaserStatus。
	// 参数：cType；cStatus：字符串。
	// 返回：返回是或否。
	virtual BOOL SetLaserStatus(BYTE cType, BYTE cStatus);

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
	// 函数 ReadAllTemp
	// 作用：读取ReadAllTemp。
	// 参数：iTempCount：整数；pTemp：指针，指向调用方传入的对象；bToTarget：是或否。
	// 返回：返回是或否。
	virtual BOOL ReadAllTemp(int iTempCount, float* pTemp, BOOL& bToTarget); //读取仪器Block模块所有温度

	// 函数 ReadFLUData
	// 作用：读取ReadFLUData。
	// 参数：arrayData；cChannel；cFrmIndex。
	// 返回：返回是或否。
	virtual BOOL ReadFLUData(CUIntArray& arrayData, BYTE cChannel, BYTE cFrmIndex=1);
	// 函数 ReadAllFLUData
	// 作用：读取ReadAllFLUData。
	// 参数：pAryData：指针，指向调用方传入的对象；iChanNum：整数。
	// 返回：返回是或否。
	virtual BOOL ReadAllFLUData(CUIntArray* pAryData,int iChanNum);	//封装了多通道数据读取过程

	// 函数 ReadDeviceStatus
	// 作用：读取ReadDeviceStatus。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ReadDeviceStatus(); // 读取设备状态，在实验过程中使用
	// 函数 ReadHardwareStatus
	// 作用：读取ReadHardwareStatus。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ReadHardwareStatus(); // 读取全部硬件状态，查找错误是使用

			// 函数 SaveParaForDemo
			// 作用：把SaveParaForDemo写入文件、仪器或界面。
			// 参数：strIniFile：字符串。
			// 返回：没有返回值。
			void SaveParaForDemo(CString strIniFile); // 虚拟演示程序使用
			// 函数 OutputHardwareStatusToErrorLog
			// 作用：执行OutputHardwareStatusToErrorLog。
			// 参数：无。
			// 返回：没有返回值。
			void OutputHardwareStatusToErrorLog(); // 输出硬件状态信息到错误日志中

	// 函数 ReadLidTemperatureFromEEPROMPLCUsed
	// 作用：读取ReadLidTemperatureFromEEPROMPLCUsed。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL ReadLidTemperatureFromEEPROMPLCUsed();	
	// 函数 ReadLidTemperatureFromEEPROMPLCUsed
	// 作用：读取ReadLidTemperatureFromEEPROMPLCUsed。
	// 参数：dLidTem：小数。
	// 返回：返回是或否。
	virtual BOOL ReadLidTemperatureFromEEPROMPLCUsed(double& dLidTem);
	// 函数 WriteLidTemperaturePLCUsed
	// 作用：把WriteLidTemperaturePLCUsed写入文件、仪器或界面。
	// 参数：fLidTem：小数。
	// 返回：返回是或否。
	virtual BOOL WriteLidTemperaturePLCUsed(float fLidTem);
	// 函数 WriteLidPreheatTemperaturePLCUsed
	// 作用：把WriteLidPreheatTemperaturePLCUsed写入文件、仪器或界面。
	// 参数：fLidTem：小数。
	// 返回：返回是或否。
	virtual BOOL WriteLidPreheatTemperaturePLCUsed(float fLidTem);
	// 函数 ReadLidPreheatTemperaturePLCUsed
	// 作用：读取ReadLidPreheatTemperaturePLCUsed。
	// 参数：fLidPreheatTem：小数。
	// 返回：返回是或否。
	virtual BOOL ReadLidPreheatTemperaturePLCUsed(float& fLidPreheatTem);
	// 函数 TransportLock
	// 作用：执行TransportLock。
	// 参数：无。
	// 返回：返回是或否。
	virtual	BOOL TransportLock();

	// 函数 GetInitChanDyeName
	// 作用：读取GetInitChanDyeName。
	// 参数：vecChanDyeName。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetInitChanDyeName(vector<CString>& vecChanDyeName);	//新建实验时，初始化每个通道的染料名称标识

	// 函数 CalculateExperimentTotalTimeSec
	// 作用：计算CalculateExperimentTotalTimeSec。
	// 参数：lnkSegItem；bUseLid：是或否；iVolume：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int CalculateExperimentTotalTimeSec(CLinkList<CSegItemInfo>& lnkSegItem,BOOL bUseLid,int iVolume);	//估算实验总时间

	// 函数 IsDemo
	// 作用：判断IsDemo是否成立。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL IsDemo();	//判断是否是Demo

			// 函数 GetMppcGainHigh
			// 作用：读取GetMppcGainHigh。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetMppcGainHigh();
			// 函数 GetMppcGainMiddle
			// 作用：读取GetMppcGainMiddle。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetMppcGainMiddle();
			// 函数 GetMppcGainLow
			// 作用：读取GetMppcGainLow。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetMppcGainLow();

			// 函数 SetInstanceStatus
			// 作用：设置SetInstanceStatus。
			// 参数：eStatus。
			// 返回：没有返回值。
			void SetInstanceStatus(eInstanceStatus eStatus);
			// 函数 GetInstanceStatus
			// 作用：读取GetInstanceStatus。
			// 参数：无。
			// 返回：返回 eInstanceStatus。
			eInstanceStatus GetInstanceStatus();
			// 函数 IsInstanceIdle
			// 作用：判断IsInstanceIdle是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsInstanceIdle();

			// 函数 GetPwmK1
			// 作用：读取GetPwmK1。
			// 参数：无。
			// 返回：返回一个小数。
			float GetPwmK1();
			// 函数 GetPwmB1
			// 作用：读取GetPwmB1。
			// 参数：无。
			// 返回：返回一个小数。
			float GetPwmB1();
			// 函数 GetPwmK2
			// 作用：读取GetPwmK2。
			// 参数：无。
			// 返回：返回一个小数。
			float GetPwmK2();
			// 函数 GetPwmB2
			// 作用：读取GetPwmB2。
			// 参数：无。
			// 返回：返回一个小数。
			float GetPwmB2();
			// 函数 GetPwmK3
			// 作用：读取GetPwmK3。
			// 参数：无。
			// 返回：返回一个小数。
			float GetPwmK3();
			// 函数 GetPwmB3
			// 作用：读取GetPwmB3。
			// 参数：无。
			// 返回：返回一个小数。
			float GetPwmB3();

			// 函数 SetEndCoolTemperature
			// 作用：设置SetEndCoolTemperature。
			// 参数：fTem：小数。
			// 返回：没有返回值。
			void SetEndCoolTemperature(float fTem);
			// 函数 GetEndCoolTemperature
			// 作用：读取GetEndCoolTemperature。
			// 参数：无。
			// 返回：返回一个小数。
			float GetEndCoolTemperature();
			// 函数 SetSleepMsAfterCool
			// 作用：设置SetSleepMsAfterCool。
			// 参数：iMs：整数。
			// 返回：没有返回值。
			void SetSleepMsAfterCool(int iMs);
			// 函数 GetSleepMsAfterCool
			// 作用：读取GetSleepMsAfterCool。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSleepMsAfterCool();

			// 函数 SetPWMInitWaitMs
			// 作用：设置SetPWMInitWaitMs。
			// 参数：iMs：整数。
			// 返回：没有返回值。
			void SetPWMInitWaitMs(int iMs);
			// 函数 GetPWMInitWaitMs
			// 作用：读取GetPWMInitWaitMs。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetPWMInitWaitMs();

protected:
			// 函数 DeleteAll
			// 作用：更新或清除DeleteAll。
			// 参数：无。
			// 返回：没有返回值。
			void DeleteAll();
	// 函数 InitDevicePara
	// 作用：初始化InitDevicePara。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitDevicePara();
			// 函数 InitDeviceStatus
			// 作用：初始化InitDeviceStatus。
			// 参数：无。
			// 返回：没有返回值。
			void InitDeviceStatus();
	// 函数 InitStructurePara
	// 作用：初始化InitStructurePara。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitStructurePara();
			// 函数 InitOneChannelFilter
			// 作用：初始化InitOneChannelFilter。
			// 参数：iChannel：整数；iByte：整数。
			// 返回：没有返回值。
			void InitOneChannelFilter(int iChannel, int iByte);
			// 函数 InitFilterPara
			// 作用：初始化InitFilterPara。
			// 参数：无。
			// 返回：没有返回值。
			void InitFilterPara();
			// 函数 DeleteFilterPara
			// 作用：更新或清除DeleteFilterPara。
			// 参数：无。
			// 返回：没有返回值。
			void DeleteFilterPara();

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
	
			// 函数 ReadLongEPROM
			// 作用：读取ReadLongEPROM。
			// 参数：nAddress：整数；nGetLength：整数；pReceive：指针，指向调用方传入的对象。
			// 返回：返回是或否。
			BOOL ReadLongEPROM(UINT nAddress, UINT nGetLength,BYTE* pReceive);

			// 函数 SetDeviceStatusBy
			// 作用：设置SetDeviceStatusBy。
			// 参数：iLength：整数；pStatus：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void SetDeviceStatusBy(int iLength, BYTE* pStatus);
			// 函数 SetHardwareStatus
			// 作用：设置SetHardwareStatus。
			// 参数：state。
			// 返回：没有返回值。
			void SetHardwareStatus(BYTE* state);

			// 函数 NewSendCommand
			// 作用：执行NewSendCommand。
			// 参数：iCmdLength：整数；cCommand；wPara。
			// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
			BYTE* NewSendCommand(int iCmdLength, BYTE cCommand, WORD wPara);
			// 函数 NewSendCommand
			// 作用：执行NewSendCommand。
			// 参数：iCmdLength：整数；cCommand；cPara1；cPara2。
			// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
			BYTE* NewSendCommand(int iCmdLength, BYTE cCommand, BYTE cPara1, BYTE cPara2);
			// 函数 NewSendCommand
			// 作用：执行NewSendCommand。
			// 参数：iCmdLength：整数；cCommand；nAddress：整数；cGReceiveLen。
			// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
			BYTE* NewSendCommand(int iCmdLength, BYTE cCommand, UINT nAddress, BYTE cGReceiveLen);
			// 函数 NewSendCommand
			// 作用：执行NewSendCommand。
			// 参数：iCmdLength：整数；cCommand；cFlag；wPulse；wSpeed。
			// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
			BYTE* NewSendCommand(int iCmdLength, BYTE cCommand, BYTE cFlag, WORD wPulse, WORD wSpeed);
			// 函数 NewSendCommand
			// 作用：执行NewSendCommand。
			// 参数：iCmdLength：整数；cCommand；wPara1；wPara2；wPara3；wPara4；cMode。
			// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
			BYTE* NewSendCommand(int iCmdLength, BYTE cCommand, WORD wPara1, WORD wPara2, WORD wPara3, WORD wPara4, BYTE cMode);

			// 函数 MotorReset
			// 作用：执行MotorReset。
			// 参数：cMotorFlag。
			// 返回：返回是或否。
			// 过程：函数里会调用 SetModel。
			BOOL MotorReset(BYTE cMotorFlag);
			// 函数 MotorMove
			// 作用：执行MotorMove。
			// 参数：cMotorFlag；wPulse；wSpeed。
			// 返回：返回是或否。
			// 过程：函数里会调用 SetModel。
			BOOL MotorMove(BYTE  cMotorFlag, WORD wPulse, WORD wSpeed);

			// 函数 SetDeviceParams
			// 作用：设置SetDeviceParams。
			// 参数：pPara：指针，指向调用方传入的对象；iLen：整数。
			// 返回：没有返回值。
			// 过程：函数里会调用 SetModel。
			void SetDeviceParams(BYTE* pPara,int iLen);

// Attributes
public:
	// 函数 SetModel
	// 作用：设置SetModel。
	// 参数：strModel：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetModel(CString strModel) { m_strModel = strModel; }
	// 函数 GetModel
	// 作用：读取GetModel。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual CString GetModel() { return m_strModel; }

	// 函数 SetSN
	// 作用：设置SetSN。
	// 参数：strSN：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSN(CString strSN) { m_strSN=strSN; }
	// 函数 GetSN
	// 作用：读取GetSN。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetSN() { return m_strSN; }

	// 函数 GetVersion
	// 作用：读取GetVersion。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetVersion() { return m_strVersion; }

	// 函数 SetCode
	// 作用：设置SetCode。
	// 参数：strCode：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCode(CString strCode) { m_strCode = strCode; } 
	// 函数 GetCode
	// 作用：读取GetCode。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetCode() { return m_strCode; }

	// 函数 SetSoftwareVersion
	// 作用：设置SetSoftwareVersion。
	// 参数：strSoftwareVer：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSoftwareVersion(CString strSoftwareVer) { m_strSoftwareVer = strSoftwareVer; }
	// 函数 GetSoftwareVersion
	// 作用：读取GetSoftwareVersion。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetSoftwareVersion(){ return m_strSoftwareVer; }

	// 函数 GetBe96SiteQPCR
	// 作用：读取GetBe96SiteQPCR。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetBe96SiteQPCR() { return PCR_CODE_QPCR_STANDARD == m_strCode; }	
	// 函数 GetBePS96PCR
	// 作用：读取GetBePS96PCR。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetBePS96PCR() { return PCR_CODE_IAMP_PS96 == m_strCode; }
	// 函数 GetBeN96PCR
	// 作用：读取GetBeN96PCR。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetBeN96PCR() { return PCR_CODE_QPCR_STANDARD == m_strCode; }

	// 函数 SetStartPath
	// 作用：设置SetStartPath。
	// 参数：strPath：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetStartPath(CString strPath) { m_strStartPath = strPath; }
	// 函数 GetErrorCode
	// 作用：读取GetErrorCode。
	// 参数：iErrPara1：整数；iErrPara2：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	UINT GetErrorCode(int &iErrPara1, int &iErrPara2);

	// 函数 GetPlateInfo
	// 作用：读取GetPlateInfo。
	// 参数：pInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void GetPlateInfo(tagPlateModeInfo* pInfo);
	// 函数 GetTempMode
	// 作用：读取GetTempMode。
	// 参数：无。
	// 返回：返回 ePCRTempMode。
	ePCRTempMode GetTempMode(); // 控温模式
	// 函数 GetTempCtrlMode
	// 作用：读取GetTempCtrlMode。
	// 参数：无。
	// 返回：返回 eTempCtrlMode。
	eTempCtrlMode GetTempCtrlMode(); // 控温方式

	// 函数 GetPMTGain
	// 作用：读取GetPMTGain。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	WORD GetPMTGain();

	// 函数 GetTempLegalGap
	// 作用：读取GetTempLegalGap。
	// 参数：无。
	// 返回：返回一个小数。
	float GetTempLegalGap(); // 取得默认到达温度的偏差范围
	// 函数 GetLidTempLegalGap
	// 作用：读取GetLidTempLegalGap。
	// 参数：无。
	// 返回：返回一个小数。
	float GetLidTempLegalGap();	//获取热盖温度的 到温偏差范围

	// 函数 GetMaxLidHeatSecond
	// 作用：读取GetMaxLidHeatSecond。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetMaxLidHeatSecond(); // 取得热盖加热最长时间
			// 函数 GetMaxTempCtrlSecond
			// 作用：读取GetMaxTempCtrlSecond。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetMaxTempCtrlSecond(); // 取得加热模块最长控温时间

	// 函数 GetLidHeatNormalSecond
	// 作用：读取GetLidHeatNormalSecond。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetLidHeatNormalSecond();	//获取热盖正常工作时的升温时间

	// 函数 GetLidState
	// 作用：读取GetLidState。
	// 参数：iStatus：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetLidState(int& iStatus);	//获取PS96热盖状态

	// 函数 GetSysTemp
	// 作用：读取GetSysTemp。
	// 参数：eType。
	// 返回：返回一个小数。
	// 过程：函数里会调用 GetCalibrateMethod。
	float GetSysTemp(eSysTempType eType); // 取得指定类型的温度
	// 函数 GetTempChannelCount
	// 作用：读取GetTempChannelCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCalibrateMethod。
	int GetTempChannelCount(); // 取得温度通道数
	
	// 函数 GetMeltPreDelay
	// 作用：读取GetMeltPreDelay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCalibrateMethod。
	int GetMeltPreDelay(); // 熔解荧光扫描开始前等待时间
	// 函数 GetMeltMinIncrement
	// 作用：读取GetMeltMinIncrement。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：函数里会调用 GetCalibrateMethod。
	float GetMeltMinIncrement(); // 熔解单步最小增量
	// 函数 GetMeltStepDelay
	// 作用：读取GetMeltStepDelay。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCalibrateMethod。
	int GetMeltStepDelay(); // 熔解单步等待时间
	// 函数 GetScanOnceTime
	// 作用：读取GetScanOnceTime。
	// 参数：bIsSecond：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCalibrateMethod。
	int GetScanOnceTime(BOOL bIsSecond=TRUE); // 扫描指定通道一次需要时间
	// 函数 GetScanRowCount
	// 作用：读取GetScanRowCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCalibrateMethod。
	int GetScanRowCount(); // 扫描行数即X电机移动次数
	// 函数 GetCalibrateMethod
	// 作用：读取GetCalibrateMethod。
	// 参数：(eCalibrateMethod。
	// 返回：返回 eCalibrateMethod。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eCalibrateMethod GetCalibrateMethod() { return (eCalibrateMethod)m_sStructurePara.cCalibratePara; }

	// 函数 GetDeviceStatus
	// 作用：读取GetDeviceStatus。
	// 参数：无。
	// 返回：返回指针 tagDeviceStatus*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	tagDeviceStatus* GetDeviceStatus() { return &m_sDeviceStatus; }

	// 函数 GetCalibrateChannel
	// 作用：读取GetCalibrateChannel。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetScanChannelInfoArray。
	int GetCalibrateChannel();
	// 函数 GetScanChannelCount
	// 作用：读取GetScanChannelCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetScanChannelInfoArray。
	int GetScanChannelCount(); // 只返回扫描光路通道数
	// 函数 GetScanChannelInfo
	// 作用：读取GetScanChannelInfo。
	// 参数：iIndex：整数。
	// 返回：返回指针 tagScanChannelInfo*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetScanChannelInfoArray。
	tagScanChannelInfo* GetScanChannelInfo(int iIndex); // 所有光路
	// 函数 GetScanChannelInfo
	// 作用：读取GetScanChannelInfo。
	// 参数：lnkScanChanInfo。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetScanChannelInfoArray。
	int GetScanChannelInfo(CLinkList<tagScanChannelInfo>& lnkScanChanInfo);
	// 函数 GetScanChannelInfoArray
	// 作用：读取GetScanChannelInfoArray。
	// 参数：无。
	// 返回：返回指针 CPtrArray*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPtrArray* GetScanChannelInfoArray() { return & m_arrayFilter; }
	// 函数 GetScanStartPos
	// 作用：读取GetScanStartPos。
	// 参数：无。
	// 返回：返回 eScanStartPos。
	eScanStartPos GetScanStartPos();
	// 函数 GetScanColCount
	// 作用：读取GetScanColCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetScanColCount();

	// 函数 GetLidTem
	// 作用：读取GetLidTem。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetLidTem();
	// 函数 SetLidTem
	// 作用：设置SetLidTem。
	// 参数：iLidTem：整数。
	// 返回：返回是或否。
	BOOL SetLidTem(int iLidTem);
	
	// 函数 HasBox
	// 作用：判断HasBox是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL HasBox();// 是否有进出仓
	// 函数 HasLid
	// 作用：判断HasLid是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL HasLid(); // 是否有热盖

    int GetPreMeltMinSleepSec();

	// 函数 SportModuleCheck
	// 作用：执行SportModuleCheck。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SportModuleCheck();
	// 函数 SensorModuleCheck
	// 作用：执行SensorModuleCheck。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SensorModuleCheck();
	// 函数 HeatModeduleCheck
	// 作用：执行HeatModeduleCheck。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int HeatModeduleCheck();
	// 函数 OpticsModuleCheck
	// 作用：执行OpticsModuleCheck。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int OpticsModuleCheck();

	// 函数 GetCheckResultString
	// 作用：读取GetCheckResultString。
	// 参数：无。
	// 返回：返回一段文字。
	virtual CString GetCheckResultString();

	// 函数 CanRunExp
	// 作用：判断CanRunExp是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL CanRunExp();

protected:
	CSerialPortPCR*	m_pComPort;
	CString		m_strModel; // PCR仪型号
	CString		m_strSN; // PCR序列号
	CString		m_strCode;	//PCR仪类型
	CString		m_strVersion; // 硬件版本
	CString		m_strSoftwareVer; // 嵌入式软件版本

	CString m_strStartPath;
	UINT m_uiErrorCode; // 错误码，方便外部判读错误类型
	int	m_iErrorPara1; // 错误参数 1/2 方便表明错误的详细信息
	int m_iErrorPara2;

	CPtrArray		m_arrayFilter; // 通道滤色片信息 tagScanChannelInfo
	tagDeviceParams		m_sDevicePara;  // 全部设备参数信息，按一个字节排列
	tagStructureParams	m_sStructurePara;  // PCR仪结构参数
	tagDeviceStatus		m_sDeviceStatus; // 设备状态，监控状态
	tagHardwareStatus	m_sHardwareStatus; // 硬件设备状态

	int m_iMppcGainH;	//MPPC增益高值，仪器各通道统一的增益高值，默认值为4742，EEPROM地址:0X850,2Byte，主要用于96孔QPCR
	int m_iMppcGainM;	//MPPC增益中值，仪器各通道统一的增益中值，默认值为4125，EEPROM地址:0X852,2Byte，主要用于96孔QPCR
	int m_iMppcGainL;	//MPPC增益低值，仪器各通道统一的增益低值，默认值为3637，EEPROM地址:0X854,2Byte，主要用于96孔QPCR

	eInstanceStatus m_eInstanceStatus;	//记录仪器的工作状态

	float m_fPwmK1;	//PWM K B 值
	float m_fPwmB1;
	float m_fPwmK2;
	float m_fPwmB2;
	float m_fPwmK3;
	float m_fPwmB3;

	float m_fEndCoolTem;	//实验结束时，仪器需要自动到达的温度(低于该温度时，不做处理，防止开仓时爆管)
	int m_iMsSlpAfterCool;	//实验结束时，仪器自动到达冷却温度后，延时时间，单位为毫秒

	int m_iMsPwmInitWait;	//PWM设置初始温度时，需等待（PWM稳定）的毫秒数

	int m_iPreMeltMinSlpSec;	//熔曲开始前，起始温度需要保持的最小时间，N16熔曲使用

	CSensorMCheckParam m_sensorMChkParam;
	CHeatMCheckParam m_heatModuleChkParam;
};


