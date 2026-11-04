// 【交接】 PCRInstanceLib\InstancePS96.h
// 作用：InstancePS96。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInstancePS96、Initialize、GetInitChanDyeName、CalculateExperimentTotalTimeSec、GetLidHeatNormalSecond、GetLidState、WriteLidPreheatTemperaturePLCUsed、ReadLidPreheatTemperaturePLCUsed。
#pragma once
#include "InstancePCR.h"

class AFX_EXT_CLASS CInstancePS96 : public CInstancePCR
{
public:
	// 函数 CInstancePS96
	// 作用：执行CInstancePS96。
	// 参数：pComPort：指针，指向调用方传入的对象；strVersion：字符串。
	// 返回：没有返回值。
	CInstancePS96(CSerialPortPCR* pComPort, CString strVersion);
	// 函数 ~CInstancePS96
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CInstancePS96(void);

// Operations
public:
	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL Initialize();
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

	// 函数 GetLidHeatNormalSecond
	// 作用：读取GetLidHeatNormalSecond。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetLidHeatNormalSecond();
	// 函数 GetLidState
	// 作用：读取GetLidState。
	// 参数：iStatus：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetLidState(int& iStatus);
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

protected:
	// 函数 InitStructurePara
	// 作用：初始化InitStructurePara。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitStructurePara();
	// 函数 MotorMove
	// 作用：执行MotorMove。
	// 参数：cMotorFlag；wPulse；wSpeed；cDirection：矩形区域。
	// 返回：返回是或否。
	BOOL MotorMove(BYTE cMotorFlag, WORD wPulse, WORD wSpeed, BYTE cDirection);
	// 函数 NewMySendCommand
	// 作用：执行NewMySendCommand。
	// 参数：iCmdLength：整数；cCommand；cFlag；wPulse；cDirection：矩形区域；wSpeed。
	// 返回：返回指针 BYTE*。指针为空表示没有取到对象。
	BYTE* NewMySendCommand(int iCmdLength, BYTE cCommand, BYTE cFlag, WORD wPulse, BYTE cDirection, WORD wSpeed);

	// 函数 FluoSelfcheck
	// 作用：执行FluoSelfcheck。
	// 参数：无。
	// 返回：返回是或否。
	BOOL FluoSelfcheck();
};

