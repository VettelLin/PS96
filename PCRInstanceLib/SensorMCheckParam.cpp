// 【交接】 PCRInstanceLib\SensorMCheckParam.cpp
// 作用：SensorMCheckParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSensorMCheckParam、Empty、IsCheckEnvirTsm、IsCheckHeatSinkTsm、IsCheckLidTsm、IsCheckPelt1Tsm、IsCheckPelt2Tsm、IsCheckPelt3Tsm。
#include "StdAfx.h"
#include "SensorMCheckParam.h"


// 函数 CSensorMCheckParam::CSensorMCheckParam
// 作用：执行CSensorMCheckParam。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CSensorMCheckParam::CSensorMCheckParam(void)
{
	m_bCheckEnvirTsm = TRUE;
	m_bCheckHeatSinkTsm = TRUE;
	m_bCheckLidTsm = TRUE;
	m_bCheckPelt1Tsm = TRUE;
	m_bCheckPelt2Tsm = TRUE;
	m_bCheckPelt3Tsm = TRUE;
	m_bCheckPowerTsm = FALSE;
	m_bCheckScanTsm = TRUE;

	m_dEnvirTsmRefH = 40;
	m_dEnvirTsmRefL = 10;

	m_dHeatSinkTsmRefH = 75;
	m_dHeatSinkTsmRefL = 10;

	m_dLidTsmRefH = 110;
	m_dLidTsmRefL = 10;

	m_dPelt1TsmRefH = 95;
	m_dPelt1TsmRefL = 5;

	m_dPelt2TsmRefH = 95;
	m_dPelt2TsmRefL = 5;

	m_dPelt3TsmRefH = 95;
	m_dPelt3TsmRefL = 5;

	m_dPowerTsmRefH = 5;
	m_dPowerTsmRefL = 100;

	m_dScanTsmRefH = 40;
	m_dScanTsmRefL = 10;

	m_strChkRst.Empty();
}

// 函数 CSensorMCheckParam::~CSensorMCheckParam
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSensorMCheckParam::~CSensorMCheckParam(void)
{
	
}

// 函数 CSensorMCheckParam::CSensorMCheckParam
// 作用：执行CSensorMCheckParam。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSensorMCheckParam::CSensorMCheckParam(const CSensorMCheckParam& info)
{
	m_bCheckEnvirTsm = info.m_bCheckEnvirTsm;
	m_bCheckHeatSinkTsm = info.m_bCheckHeatSinkTsm;
	m_bCheckLidTsm = info.m_bCheckLidTsm;
	m_bCheckPelt1Tsm = info.m_bCheckPelt1Tsm;
	m_bCheckPelt2Tsm = info.m_bCheckPelt2Tsm;
	m_bCheckPelt3Tsm = info.m_bCheckPelt3Tsm;
	m_bCheckPowerTsm = info.m_bCheckPowerTsm;
	m_bCheckScanTsm = info.m_bCheckScanTsm;

	m_dEnvirTsmRefH = info.m_dEnvirTsmRefH;
	m_dEnvirTsmRefL = info.m_dEnvirTsmRefL;
	m_dHeatSinkTsmRefH = info.m_dHeatSinkTsmRefH;
	m_dHeatSinkTsmRefL = info.m_dHeatSinkTsmRefL;
	m_dLidTsmRefH = info.m_dLidTsmRefH;
	m_dLidTsmRefL = info.m_dLidTsmRefL;
	m_dPelt1TsmRefH = info.m_dPelt1TsmRefH;
	m_dPelt1TsmRefL = info.m_dPelt1TsmRefL;
	m_dPelt2TsmRefH = info.m_dPelt2TsmRefH;
	m_dPelt2TsmRefL = info.m_dPelt2TsmRefL;
	m_dPelt3TsmRefH = info.m_dPelt3TsmRefH;
	m_dPelt3TsmRefL = info.m_dPelt3TsmRefL;
	m_dPowerTsmRefH = info.m_dPowerTsmRefH;
	m_dPowerTsmRefL = info.m_dPowerTsmRefL;
	m_dScanTsmRefH = info.m_dScanTsmRefH;
	m_dScanTsmRefL = info.m_dScanTsmRefL;
	m_strChkRst = info.m_strChkRst;
}

void CSensorMCheckParam::operator=(const CSensorMCheckParam& info)
{
	m_dEnvirTsmRefH = info.m_dEnvirTsmRefH;
	m_dEnvirTsmRefL = info.m_dEnvirTsmRefL;
	m_dHeatSinkTsmRefH = info.m_dHeatSinkTsmRefH;
	m_dHeatSinkTsmRefL = info.m_dHeatSinkTsmRefL;
	m_dLidTsmRefH = info.m_dLidTsmRefH;
	m_dLidTsmRefL = info.m_dLidTsmRefL;
	m_dPelt1TsmRefH = info.m_dPelt1TsmRefH;
	m_dPelt1TsmRefL = info.m_dPelt1TsmRefL;
	m_dPelt2TsmRefH = info.m_dPelt2TsmRefH;
	m_dPelt2TsmRefL = info.m_dPelt2TsmRefL;
	m_dPelt3TsmRefH = info.m_dPelt3TsmRefH;
	m_dPelt3TsmRefL = info.m_dPelt3TsmRefL;
	m_dPowerTsmRefH = info.m_dPowerTsmRefH;
	m_dPowerTsmRefL = info.m_dPowerTsmRefL;
	m_dScanTsmRefH = info.m_dScanTsmRefH;
	m_dScanTsmRefL = info.m_dScanTsmRefL;
	m_strChkRst = info.m_strChkRst;
}

// 函数 CSensorMCheckParam::IsCheckEnvirTsm
// 作用：判断IsCheckEnvirTsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckEnvirTsm()
{
	return m_bCheckEnvirTsm;
}

// 函数 CSensorMCheckParam::IsCheckHeatSinkTsm
// 作用：判断IsCheckHeatSinkTsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckHeatSinkTsm()
{
	return m_bCheckHeatSinkTsm;
}

// 函数 CSensorMCheckParam::IsCheckLidTsm
// 作用：判断IsCheckLidTsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckLidTsm()
{
	return m_bCheckLidTsm;
}

// 函数 CSensorMCheckParam::IsCheckPelt1Tsm
// 作用：判断IsCheckPelt1Tsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckPelt1Tsm()
{
	return m_bCheckPelt1Tsm;
}

// 函数 CSensorMCheckParam::IsCheckPelt2Tsm
// 作用：判断IsCheckPelt2Tsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckPelt2Tsm()
{
	return m_bCheckPelt2Tsm;
}

// 函数 CSensorMCheckParam::IsCheckPelt3Tsm
// 作用：判断IsCheckPelt3Tsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckPelt3Tsm()
{
	return m_bCheckPelt3Tsm;
}

// 函数 CSensorMCheckParam::IsCheckPowerTsm
// 作用：判断IsCheckPowerTsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckPowerTsm()
{
	return m_bCheckPowerTsm;
}

// 函数 CSensorMCheckParam::IsCheckScanTsm
// 作用：判断IsCheckScanTsm是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CSensorMCheckParam::IsCheckScanTsm()
{
	return m_bCheckScanTsm;
}

// 函数 CSensorMCheckParam::GetEnvirTsmRefH
// 作用：读取GetEnvirTsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetEnvirTsmRefH()
{
	return m_dEnvirTsmRefH;
}

// 函数 CSensorMCheckParam::GetEnvirTsmRefL
// 作用：读取GetEnvirTsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetEnvirTsmRefL()
{
	return m_dEnvirTsmRefL;
}

// 函数 CSensorMCheckParam::GetHeatSinkTsmRefH
// 作用：读取GetHeatSinkTsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetHeatSinkTsmRefH()
{
	return m_dHeatSinkTsmRefH;
}

// 函数 CSensorMCheckParam::GetHeatSinkTsmRefL
// 作用：读取GetHeatSinkTsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetHeatSinkTsmRefL()
{
	return m_dHeatSinkTsmRefL;
}

// 函数 CSensorMCheckParam::GetLidTsmRefH
// 作用：读取GetLidTsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetLidTsmRefH()
{
	return m_dLidTsmRefH;
}

// 函数 CSensorMCheckParam::GetLidTsmRefL
// 作用：读取GetLidTsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetLidTsmRefL()
{
	return m_dLidTsmRefL;
}

// 函数 CSensorMCheckParam::GetPelt1TsmRefH
// 作用：读取GetPelt1TsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPelt1TsmRefH()
{
	return m_dPelt1TsmRefH;
}

// 函数 CSensorMCheckParam::GetPelt1TsmRefL
// 作用：读取GetPelt1TsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPelt1TsmRefL()
{
	return m_dPelt1TsmRefL;
}

// 函数 CSensorMCheckParam::GetPelt2TsmRefH
// 作用：读取GetPelt2TsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPelt2TsmRefH()
{
	return m_dPelt2TsmRefH;
}

// 函数 CSensorMCheckParam::GetPelt2TsmRefL
// 作用：读取GetPelt2TsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPelt2TsmRefL()
{
	return m_dPelt2TsmRefL;
}

// 函数 CSensorMCheckParam::GetPelt3TsmRefH
// 作用：读取GetPelt3TsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPelt3TsmRefH()
{
	return m_dPelt3TsmRefH;
}

// 函数 CSensorMCheckParam::GetPelt3TsmRefL
// 作用：读取GetPelt3TsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPelt3TsmRefL()
{
	return m_dPelt3TsmRefL;
}

// 函数 CSensorMCheckParam::GetPowerTsmRefH
// 作用：读取GetPowerTsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPowerTsmRefH()
{
	return m_dPowerTsmRefH;
}

// 函数 CSensorMCheckParam::GetPowerTsmRefL
// 作用：读取GetPowerTsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetPowerTsmRefL()
{
	return m_dPowerTsmRefL;
}

// 函数 CSensorMCheckParam::GetScanTsmRefH
// 作用：读取GetScanTsmRefH。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetScanTsmRefH()
{
	return m_dScanTsmRefH;
}

// 函数 CSensorMCheckParam::GetScanTsmRefL
// 作用：读取GetScanTsmRefL。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CSensorMCheckParam::GetScanTsmRefL()
{
	return m_dScanTsmRefL;
}

// 函数 CSensorMCheckParam::SetEnvirTsmRefH
// 作用：设置SetEnvirTsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetEnvirTsmRefH(double dData)
{
	m_dEnvirTsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetEnvirTsmRefL
// 作用：设置SetEnvirTsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetEnvirTsmRefL(double dData)
{
	m_dEnvirTsmRefL = dData;
}

// 函数 CSensorMCheckParam::SetHeatSinkTsmRefH
// 作用：设置SetHeatSinkTsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetHeatSinkTsmRefH(double dData)
{
	m_dHeatSinkTsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetHeatSinkTsmRefL
// 作用：设置SetHeatSinkTsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetHeatSinkTsmRefL(double dData)
{
	m_dHeatSinkTsmRefL = dData;
}

// 函数 CSensorMCheckParam::SetLidTsmRefH
// 作用：设置SetLidTsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetLidTsmRefH(double dData)
{
	m_dLidTsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetLidTsmRefL
// 作用：设置SetLidTsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetLidTsmRefL(double dData)
{
	m_dLidTsmRefL = dData;
}

// 函数 CSensorMCheckParam::SetPelt1TsmRefH
// 作用：设置SetPelt1TsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPelt1TsmRefH(double dData)
{
	m_dPelt1TsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetPelt1TsmRefL
// 作用：设置SetPelt1TsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPelt1TsmRefL(double dData)
{
	m_dPelt1TsmRefL = dData;
}

// 函数 CSensorMCheckParam::SetPelt2TsmRefH
// 作用：设置SetPelt2TsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPelt2TsmRefH(double dData)
{
	m_dPelt2TsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetPelt2TsmRefL
// 作用：设置SetPelt2TsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPelt2TsmRefL(double dData)
{
	m_dPelt2TsmRefL = dData;
}

// 函数 CSensorMCheckParam::SetPelt3TsmRefH
// 作用：设置SetPelt3TsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPelt3TsmRefH(double dData)
{
	m_dPelt3TsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetPelt3TsmRefL
// 作用：设置SetPelt3TsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPelt3TsmRefL(double dData)
{
	m_dPelt3TsmRefL = dData;
}

// 函数 CSensorMCheckParam::SetPowerTsmRefH
// 作用：设置SetPowerTsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPowerTsmRefH(double dData)
{
	m_dPowerTsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetPowerTsmRefL
// 作用：设置SetPowerTsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetPowerTsmRefL(double dData)
{
	m_dPowerTsmRefL = dData;
}

// 函数 CSensorMCheckParam::SetScanTsmRefH
// 作用：设置SetScanTsmRefH。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetScanTsmRefH(double dData)
{
	m_dScanTsmRefH = dData;
}

// 函数 CSensorMCheckParam::SetScanTsmRefL
// 作用：设置SetScanTsmRefL。
// 参数：dData：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CSensorMCheckParam::SetScanTsmRefL(double dData)
{
	m_dScanTsmRefL = dData;
}

// 函数 CSensorMCheckParam::ResetCheckResult
// 作用：更新或清除ResetCheckResult。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
void CSensorMCheckParam::ResetCheckResult()
{
	m_strChkRst.Empty();
}

// 函数 CSensorMCheckParam::AddCheckResult
// 作用：创建或加入AddCheckResult。
// 参数：strData：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
void CSensorMCheckParam::AddCheckResult(CString strData)
{
	m_strChkRst += _T("\r\n");
	m_strChkRst += strData;
	return;
}

// 函数 CSensorMCheckParam::GetCheckResult
// 作用：读取GetCheckResult。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CSensorMCheckParam::GetCheckResult()
{
	return m_strChkRst;
}

// 函数 CSensorMCheckParam::IsSuccessful
// 作用：判断IsSuccessful是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 IsEmpty。
BOOL CSensorMCheckParam::IsSuccessful()
{
	return m_strChkRst.IsEmpty();
}



