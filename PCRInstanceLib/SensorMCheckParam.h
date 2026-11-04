// 【交接】 PCRInstanceLib\SensorMCheckParam.h
// 作用：SensorMCheckParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSensorMCheckParam、IsCheckEnvirTsm、IsCheckHeatSinkTsm、IsCheckLidTsm、IsCheckPelt1Tsm、IsCheckPelt2Tsm、IsCheckPelt3Tsm、IsCheckPowerTsm。
#pragma once
class AFX_EXT_CLASS CSensorMCheckParam
{
public:
	// 函数 CSensorMCheckParam
	// 作用：执行CSensorMCheckParam。
	// 参数：无。
	// 返回：没有返回值。
	CSensorMCheckParam(void);
	// 函数 ~CSensorMCheckParam
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSensorMCheckParam(void);

	// 函数 CSensorMCheckParam
	// 作用：执行CSensorMCheckParam。
	// 参数：info。
	// 返回：没有返回值。
	CSensorMCheckParam(const CSensorMCheckParam& info);
	void operator=(const CSensorMCheckParam& info);

	// 函数 IsCheckEnvirTsm
	// 作用：判断IsCheckEnvirTsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckEnvirTsm();
	// 函数 IsCheckHeatSinkTsm
	// 作用：判断IsCheckHeatSinkTsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckHeatSinkTsm();
	// 函数 IsCheckLidTsm
	// 作用：判断IsCheckLidTsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckLidTsm();
	// 函数 IsCheckPelt1Tsm
	// 作用：判断IsCheckPelt1Tsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckPelt1Tsm();
	// 函数 IsCheckPelt2Tsm
	// 作用：判断IsCheckPelt2Tsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckPelt2Tsm();
	// 函数 IsCheckPelt3Tsm
	// 作用：判断IsCheckPelt3Tsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckPelt3Tsm();
	// 函数 IsCheckPowerTsm
	// 作用：判断IsCheckPowerTsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckPowerTsm();
	// 函数 IsCheckScanTsm
	// 作用：判断IsCheckScanTsm是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsCheckScanTsm();

	// 函数 GetEnvirTsmRefH
	// 作用：读取GetEnvirTsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetEnvirTsmRefH();
	// 函数 GetEnvirTsmRefL
	// 作用：读取GetEnvirTsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetEnvirTsmRefL();

	// 函数 GetHeatSinkTsmRefH
	// 作用：读取GetHeatSinkTsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetHeatSinkTsmRefH();
	// 函数 GetHeatSinkTsmRefL
	// 作用：读取GetHeatSinkTsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetHeatSinkTsmRefL();

	// 函数 GetLidTsmRefH
	// 作用：读取GetLidTsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetLidTsmRefH();
	// 函数 GetLidTsmRefL
	// 作用：读取GetLidTsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetLidTsmRefL();

	// 函数 GetPelt1TsmRefH
	// 作用：读取GetPelt1TsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPelt1TsmRefH();
	// 函数 GetPelt1TsmRefL
	// 作用：读取GetPelt1TsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPelt1TsmRefL();

	// 函数 GetPelt2TsmRefH
	// 作用：读取GetPelt2TsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPelt2TsmRefH();
	// 函数 GetPelt2TsmRefL
	// 作用：读取GetPelt2TsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPelt2TsmRefL();

	// 函数 GetPelt3TsmRefH
	// 作用：读取GetPelt3TsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPelt3TsmRefH();
	// 函数 GetPelt3TsmRefL
	// 作用：读取GetPelt3TsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPelt3TsmRefL();

	// 函数 GetPowerTsmRefH
	// 作用：读取GetPowerTsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPowerTsmRefH();
	// 函数 GetPowerTsmRefL
	// 作用：读取GetPowerTsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetPowerTsmRefL();

	// 函数 GetScanTsmRefH
	// 作用：读取GetScanTsmRefH。
	// 参数：无。
	// 返回：返回一个小数。
	double GetScanTsmRefH();
	// 函数 GetScanTsmRefL
	// 作用：读取GetScanTsmRefL。
	// 参数：无。
	// 返回：返回一个小数。
	double GetScanTsmRefL();

	// 函数 SetEnvirTsmRefH
	// 作用：设置SetEnvirTsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetEnvirTsmRefH(double dData);
	// 函数 SetEnvirTsmRefL
	// 作用：设置SetEnvirTsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetEnvirTsmRefL(double dData);

	// 函数 SetHeatSinkTsmRefH
	// 作用：设置SetHeatSinkTsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetHeatSinkTsmRefH(double dData);
	// 函数 SetHeatSinkTsmRefL
	// 作用：设置SetHeatSinkTsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetHeatSinkTsmRefL(double dData);

	// 函数 SetLidTsmRefH
	// 作用：设置SetLidTsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetLidTsmRefH(double dData);
	// 函数 SetLidTsmRefL
	// 作用：设置SetLidTsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetLidTsmRefL(double dData);

	// 函数 SetPelt1TsmRefH
	// 作用：设置SetPelt1TsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPelt1TsmRefH(double dData);
	// 函数 SetPelt1TsmRefL
	// 作用：设置SetPelt1TsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPelt1TsmRefL(double dData);

	// 函数 SetPelt2TsmRefH
	// 作用：设置SetPelt2TsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPelt2TsmRefH(double dData);
	// 函数 SetPelt2TsmRefL
	// 作用：设置SetPelt2TsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPelt2TsmRefL(double dData);

	// 函数 SetPelt3TsmRefH
	// 作用：设置SetPelt3TsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPelt3TsmRefH(double dData);
	// 函数 SetPelt3TsmRefL
	// 作用：设置SetPelt3TsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPelt3TsmRefL(double dData);

	// 函数 SetPowerTsmRefH
	// 作用：设置SetPowerTsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPowerTsmRefH(double dData);
	// 函数 SetPowerTsmRefL
	// 作用：设置SetPowerTsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetPowerTsmRefL(double dData);

	// 函数 SetScanTsmRefH
	// 作用：设置SetScanTsmRefH。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetScanTsmRefH(double dData);
	// 函数 SetScanTsmRefL
	// 作用：设置SetScanTsmRefL。
	// 参数：dData：小数。
	// 返回：没有返回值。
	void SetScanTsmRefL(double dData);

	// 函数 ResetCheckResult
	// 作用：更新或清除ResetCheckResult。
	// 参数：无。
	// 返回：没有返回值。
	void ResetCheckResult();
	// 函数 AddCheckResult
	// 作用：创建或加入AddCheckResult。
	// 参数：strData：字符串。
	// 返回：没有返回值。
	void AddCheckResult(CString strData);
	// 函数 GetCheckResult
	// 作用：读取GetCheckResult。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetCheckResult();
	// 函数 IsSuccessful
	// 作用：判断IsSuccessful是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsSuccessful();

protected:
	BOOL m_bCheckEnvirTsm;
	BOOL m_bCheckHeatSinkTsm;
	BOOL m_bCheckLidTsm;
	BOOL m_bCheckPelt1Tsm;
	BOOL m_bCheckPelt2Tsm;
	BOOL m_bCheckPelt3Tsm;
	BOOL m_bCheckPowerTsm;
	BOOL m_bCheckScanTsm;

	double m_dEnvirTsmRefH;
	double m_dEnvirTsmRefL;

	double m_dHeatSinkTsmRefH;
	double m_dHeatSinkTsmRefL;

	double m_dLidTsmRefH;
	double m_dLidTsmRefL;

	double m_dPelt1TsmRefH;
	double m_dPelt1TsmRefL;

	double m_dPelt2TsmRefH;
	double m_dPelt2TsmRefL;

	double m_dPelt3TsmRefH;
	double m_dPelt3TsmRefL;

	double m_dPowerTsmRefH;
	double m_dPowerTsmRefL;

	double m_dScanTsmRefH;
	double m_dScanTsmRefL;

	CString m_strChkRst;
};

