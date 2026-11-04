// 【交接】 PCRCtrlLib\ExperimentInfo.h
// 作用：ExperimentInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CExperimentInfo、CopyExperiment、WriteFile、ReadFile、GetSaveDataFileName、CreateExperimentName、GetExpName、SetExpName。
#pragma once

#include "DeclaresPCR.h"

//  实验数据文件基本信息
class AFX_EXT_CLASS CExperimentInfo
{
public:
	// 函数 CExperimentInfo
	// 作用：执行CExperimentInfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CExperimentInfo();
	// 函数 ~CExperimentInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CExperimentInfo(){}

	// 函数 CopyExperiment
	// 作用：复制CopyExperiment。
	// 参数：expInfo。
	// 返回：没有返回值。
	void CopyExperiment(CExperimentInfo& expInfo);

// Operations
public:
	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；bTemplate：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetExpName。
	BOOL WriteFile(CFile* pFile,BOOL bTemplate);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetExpName。
	BOOL ReadFile(CFile* pFile, WORD wVersion);

	// 函数 GetSaveDataFileName
	// 作用：读取GetSaveDataFileName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetExpName。
	CString GetSaveDataFileName();
	// 函数 CreateExperimentName
	// 作用：创建或加入CreateExperimentName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetExpName。
	CString CreateExperimentName();

// Attributes
public:
	// 函数 GetExpName
	// 作用：读取GetExpName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetExpName() { return m_strExpName; }
	// 函数 SetExpName
	// 作用：设置SetExpName。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetExpName(CString string) { m_strExpName = string; }
	// 函数 GetFilePath
	// 作用：读取GetFilePath。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetFilePath() { return m_strFilePath; }
	// 函数 SetFilePath
	// 作用：设置SetFilePath。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetFilePath(CString string) { m_strFilePath = string; }

	// 函数 GetExpType
	// 作用：读取GetExpType。
	// 参数：无。
	// 返回：返回 eExperimentType。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eExperimentType GetExpType() { return m_nExpType; }
	// 函数 SetExpType
	// 作用：设置SetExpType。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetExpType(eExperimentType nType) { m_nExpType = nType; }
	// 函数 GetOperator
	// 作用：读取GetOperator。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetOperator() { return m_strOperator; }
	// 函数 SetOperator
	// 作用：设置SetOperator。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetOperator(CString string) { m_strOperator = string; }
	// 函数 GetVerifier
	// 作用：读取GetVerifier。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetVerifier() { return m_strVerifier; }
	// 函数 SetVerifier
	// 作用：设置SetVerifier。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetVerifier(CString string) { m_strVerifier = string; }
	// 函数 GetComments
	// 作用：读取GetComments。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetComments() { return m_strComments; }
	// 函数 SetComments
	// 作用：设置SetComments。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetComments(CString string) { m_strComments = string; }

	// 函数 GetStartTime
	// 作用：读取GetStartTime。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetStartTime() { return m_strStartTime;}
	// 函数 SetStartTime
	// 作用：设置SetStartTime。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetStartTime(CString string) { m_strStartTime = string; }
	// 函数 SetStartTime
	// 作用：设置SetStartTime。
	// 参数：time。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetEndTime。
	void SetStartTime(CTime time);
	// 函数 GetEndTime
	// 作用：读取GetEndTime。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetEndTime() { return m_strEndTime;}
	// 函数 SetEndTime
	// 作用：设置SetEndTime。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetEndTime(CString string) { m_strEndTime = string; }
	// 函数 SetEndTime
	// 作用：设置SetEndTime。
	// 参数：time。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetRunDuration。
	void SetEndTime(CTime time);
	// 函数 GetRunDuration
	// 作用：读取GetRunDuration。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetRunDuration() { return m_strRunDuration;}
	// 函数 SetRunDuration
	// 作用：设置SetRunDuration。
	// 参数：strDuration：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRunDuration(CString strDuration) { m_strRunDuration = strDuration; }

	// 函数 GetInstrument
	// 作用：读取GetInstrument。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetInstrument() { return m_strInstrument; }
	// 函数 SetInstrument
	// 作用：设置SetInstrument。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetInstrument(CString string) { m_strInstrument = string; }
	// 函数 GetInstrumentSN
	// 作用：读取GetInstrumentSN。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetInstrumentSN() { return m_strInstrumentSN; }
	// 函数 SetInstrumentSN
	// 作用：设置SetInstrumentSN。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetInstrumentSN(CString string) { m_strInstrumentSN = string;}
	// 函数 GetFirmwareVersion
	// 作用：读取GetFirmwareVersion。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetFirmwareVersion() { return m_strFirmwareVersion; }
	// 函数 SetFirmwareVersion
	// 作用：设置SetFirmwareVersion。
	// 参数：strVersion：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetFirmwareVersion(CString strVersion) { m_strFirmwareVersion = strVersion; }
	// 函数 GetSoftwareVersion
	// 作用：读取GetSoftwareVersion。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetSoftwareVersion() { return m_strSoftwareVersion; }
	// 函数 SetSoftwareVersion
	// 作用：设置SetSoftwareVersion。
	// 参数：strVersion：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSoftwareVersion(CString strVersion) { m_strSoftwareVersion = strVersion; }

	// 函数 GetBePS96ExperimentFile
	// 作用：读取GetBePS96ExperimentFile。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetTubeType。
	BOOL GetBePS96ExperimentFile();	//判断是否是PS96实验文件，添加这个函数是为了兼容PS96早期实验文件的识别,20220624

	// 函数 GetTubeType
	// 作用：读取GetTubeType。
	// 参数：无。
	// 返回：返回 eTubeType。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eTubeType GetTubeType() { return m_nTubeType; }
	// 函数 SetTubeType
	// 作用：设置SetTubeType。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTubeType(eTubeType nType) { m_nTubeType = nType; }
	// 函数 GetLidHeader
	// 作用：读取GetLidHeader。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetLidHeader() { return m_bLidHeater; }
	// 函数 SetLidHeader
	// 作用：设置SetLidHeader。
	// 参数：bUse：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLidHeader(BOOL bUse) { m_bLidHeater = bUse; }
	// 函数 GetLidTemp
	// 作用：读取GetLidTemp。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	float GetLidTemp() { return m_fLidTopTemp; }
	// 函数 SetLidTemp
	// 作用：设置SetLidTemp。
	// 参数：fValue：小数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLidTemp(float fValue) { m_fLidTopTemp = fValue; }

	// 函数 GetTempMode
	// 作用：读取GetTempMode。
	// 参数：无。
	// 返回：返回 ePCRTempMode。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	ePCRTempMode GetTempMode() { return m_nTempMode; }
	// 函数 SetTempMode
	// 作用：设置SetTempMode。
	// 参数：nMode：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTempMode(ePCRTempMode nMode) { m_nTempMode = nMode; }
	// 函数 GetTempCtrlMode
	// 作用：读取GetTempCtrlMode。
	// 参数：无。
	// 返回：返回 eTempCtrlMode。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eTempCtrlMode GetTempCtrlMode() { return m_nTempCtrlMode; }
	// 函数 SetTempCtrlMode
	// 作用：设置SetTempCtrlMode。
	// 参数：nMode：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTempCtrlMode(eTempCtrlMode nMode) { m_nTempCtrlMode = nMode; }
	// 函数 GetBlockHeater
	// 作用：读取GetBlockHeater。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	UINT GetBlockHeater() { return m_nBlockHeater; }
	// 函数 SetBlockHeader
	// 作用：设置SetBlockHeader。
	// 参数：nBlock：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBlockHeader(UINT nBlock) { m_nBlockHeater = nBlock; }
	// 函数 GetChannelScanMode
	// 作用：读取GetChannelScanMode。
	// 参数：无。
	// 返回：返回 eChannelScanlMode。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eChannelScanlMode GetChannelScanMode() { return m_ScanMode; }
	// 函数 SetChannelScanMode
	// 作用：设置SetChannelScanMode。
	// 参数：nMode：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetChannelScanMode(eChannelScanlMode nMode) { m_ScanMode = nMode; }
	// 函数 GetMeltScanMode
	// 作用：读取GetMeltScanMode。
	// 参数：无。
	// 返回：返回 eMeltScanMode。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eMeltScanMode GetMeltScanMode() { return m_nMeltScanMode; }
	// 函数 SetMeltScanMode
	// 作用：设置SetMeltScanMode。
	// 参数：nMode：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetMeltScanMode(eMeltScanMode nMode) { m_nMeltScanMode = nMode; }
	// 函数 GetPMTVoltageGear
	// 作用：读取GetPMTVoltageGear。
	// 参数：无。
	// 返回：返回 eMPPCVoltageGear。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eMPPCVoltageGear GetPMTVoltageGear() { return m_nPMTGear; }
	// 函数 SetPMTVoltageGear
	// 作用：设置SetPMTVoltageGear。
	// 参数：nGear：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetPMTVoltageGear(eMPPCVoltageGear nGear) { m_nPMTGear = nGear; }

	// 函数 SetCYReportNo
	// 作用：设置SetCYReportNo。
	// 参数：strData：字符串。
	// 返回：没有返回值。
	void SetCYReportNo(CString strData);
	// 函数 GetCYReportNo
	// 作用：读取GetCYReportNo。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetCYReportNo();

	// 函数 SetTotalSec
	// 作用：设置SetTotalSec。
	// 参数：iTotalSec：整数。
	// 返回：没有返回值。
	void SetTotalSec(int iTotalSec);
	// 函数 GetTotalSec
	// 作用：读取GetTotalSec。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetTotalSec();
	// 函数 GetTotalTimeString
	// 作用：读取GetTotalTimeString。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetTotalTimeString();

	// 函数 SetHasRunSec
	// 作用：设置SetHasRunSec。
	// 参数：iHasRunSec：整数。
	// 返回：没有返回值。
	void SetHasRunSec(int iHasRunSec);
	// 函数 GetHasRunSec
	// 作用：读取GetHasRunSec。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetHasRunSec();

	// 函数 SetRemainSec
	// 作用：设置SetRemainSec。
	// 参数：iRemainSec：整数。
	// 返回：没有返回值。
	void SetRemainSec(int iRemainSec);
	// 函数 GetRemainSec
	// 作用：读取GetRemainSec。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetRemainSec();

protected:
	CString		m_strExpName; // 实验名称，文件名
	CString		m_strFilePath; // 文件保存路径
	
	eExperimentType m_nExpType; // 实验类型
	CString		m_strOperator; // 操作者
	CString		m_strVerifier; // 审核者
	CString		m_strComments; // 备注
	CString		m_strStartTime; // 实验开始时间
	CString		m_strEndTime; // 实验结束时间
	CString		m_strRunDuration; // 时间耗时

	CString		m_strInstrument; // 仪器型号
	CString		m_strInstrumentSN; // 仪器编码SN
	CString		m_strFirmwareVersion; // 硬件版本
	CString		m_strSoftwareVersion; // 软件版本

	eTubeType	m_nTubeType; // 反应管类型
	BOOL		m_bLidHeater; // 是否使用热盖
	float		m_fLidTopTemp; // 热盖最高温度
	ePCRTempMode  	m_nTempMode; // 加热模式，升降温/恒温
	eTempCtrlMode	m_nTempCtrlMode; // 控温模式 模块控温/试管控温
	UINT			m_nBlockHeater; // 在模块加热时选择的反应模块，使用位操作
	eChannelScanlMode m_ScanMode; // 扫描方式 全通道/选择通道
	eMeltScanMode m_nMeltScanMode; // 熔曲扫描方式
	eMPPCVoltageGear m_nPMTGear; // 扫描模块控制电压

	CString m_strCYReportNo;	//报告编号，康研葆使用

	//实验时间参数，添加于20220320，孙文郎
	int m_iTotalSec;	//实验总时间
	int m_iRemainSec;	//实验剩余时间
	int m_iHasRunSec;	//实验已经运行的时间
	CTime	m_timeStart; // 开始时间，为了计算实验耗时使用，不保存
};

