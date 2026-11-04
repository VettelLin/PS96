// 【交接】 PCRCtrlLib\CalibrateParaTurbidity.h
// 作用：CalibrateParaTurbidity。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CCalibrateParaTurbidity、tagTurbidityPara、Empty、ReadPara、SavePara、WriteFile、ReadFile、GetParaCount。
#pragma once

#include "DeclaresPCR.h"

// 校准参数：浊度校准
class AFX_EXT_CLASS CCalibrateParaTurbidity
{
public:
	// 函数 CCalibrateParaTurbidity
	// 作用：执行CCalibrateParaTurbidity。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 tagTurbidityPara、Empty。
	CCalibrateParaTurbidity(void);
	// 函数 ~CCalibrateParaTurbidity
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 tagTurbidityPara、Empty。
	~CCalibrateParaTurbidity(void);


	struct tagTurbidityPara
	{
		CString strDyeName; // 染料名称
		int		iChannel; // 通道
		BOOL bUseMOT; // 是否使用修正通道数据
		int iAheadCycle; // 前移多少循环开始
		float fRatio;  // 作为显示调整系数使用

		tagTurbidityPara()
		{
			strDyeName.Empty();
			iChannel = -1;
			bUseMOT = FALSE;
			iAheadCycle = 5;
			fRatio = 0;
		}
	};

public:
	// 函数 ReadPara
	// 作用：读取ReadPara。
	// 参数：strFile：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetParaCount、GetCount。
	BOOL ReadPara(CString strFile);
	// 函数 SavePara
	// 作用：把SavePara写入文件、仪器或界面。
	// 参数：strFile：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetParaCount、GetCount。
	BOOL SavePara(CString strFile);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetParaCount、GetCount。
	BOOL WriteFile(CFile* pFile);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetParaCount、GetCount。
	BOOL ReadFile(CFile* pFile, WORD wVersion);

	// 函数 GetParaCount
	// 作用：读取GetParaCount。
	// 参数：m_arrayDyePara.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetParaCount() { return m_arrayDyePara.GetCount(); }
	// 函数 GetDye
	// 作用：读取GetDye。
	// 参数：iIndex：整数。
	// 返回：返回一段文字。
	CString GetDye(int iIndex);

	// 函数 ResetChannel
	// 作用：更新或清除ResetChannel。
	// 参数：pArrayDyeChannel：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetChannelMOT。
	void ResetChannel(CPtrArray* pArrayDyeChannel);

protected:
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetChannelMOT。
	void DeleteAll();
	// 函数 GetParaBy
	// 作用：读取GetParaBy。
	// 参数：strDye：字符串。
	// 返回：返回指针 tagTurbidityPara*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetChannelMOT。
	tagTurbidityPara* GetParaBy(CString strDye);

// Attributes
public:
	// 函数 GetChannelMOT
	// 作用：读取GetChannelMOT。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetChannelMOT() { return m_iChannelMOT; }
	// 函数 SetChannelMOT
	// 作用：设置SetChannelMOT。
	// 参数：iChannel：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetChannelMOT(int iChannel) { m_iChannelMOT = iChannel; }

	// 函数 GetMinRatio
	// 作用：读取GetMinRatio。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	float GetMinRatio() { return m_fMinRatio; }
	// 函数 SetMinRatio
	// 作用：设置SetMinRatio。
	// 参数：fRatio：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetMinRatio(float fRatio) { m_fMinRatio = fRatio; }

	// 函数 GetChannel
	// 作用：读取GetChannel。
	// 参数：strDye：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetChannel(CString strDye);

	// 函数 UseCalibrate
	// 作用：执行UseCalibrate。
	// 参数：strDye：字符串。
	// 返回：返回是或否。
	BOOL UseCalibrate(CString strDye);
	// 函数 UseCalibrate
	// 作用：执行UseCalibrate。
	// 参数：iChannel：整数。
	// 返回：返回是或否。
	BOOL UseCalibrate(int iChannel);
	// 函数 EnableUseCalibrate
	// 作用：改变EnableUseCalibrate的显示或可用状态。
	// 参数：strDye：字符串；bEnable：是或否。
	// 返回：没有返回值。
	void EnableUseCalibrate(CString strDye, BOOL bEnable);
	// 函数 GetAheadCycle
	// 作用：读取GetAheadCycle。
	// 参数：strDye：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetAheadCycle(CString strDye);
	// 函数 SetAheadCycle
	// 作用：设置SetAheadCycle。
	// 参数：strDye：字符串；iCycyle：整数。
	// 返回：没有返回值。
	void SetAheadCycle(CString strDye, int iCycyle);
	// 函数 GetAdjustRatio
	// 作用：读取GetAdjustRatio。
	// 参数：strDye：字符串。
	// 返回：返回一个小数。
	float GetAdjustRatio(CString strDye);
	// 函数 SetAdjustRatio
	// 作用：设置SetAdjustRatio。
	// 参数：strDye：字符串；fRatio：小数。
	// 返回：没有返回值。
	void SetAdjustRatio(CString strDye, float fRatio);

protected:
	int		m_iChannelMOT; // 浊度校准通道
	float	m_fMinRatio; //MOT通道荧光数据归一化后一阶导数认为是出现浊度变化的最小值
	CPtrArray	m_arrayDyePara; // 染料调整参数
};

