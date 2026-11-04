// 【交接】 PCRCtrlLib\PublicInfo.h
// 作用：PublicInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CPublicInfo、GetInstance、CleanUp、Initialize、ReadParameters、SaveParameters、GetIniFilePath、ReadAndCreateUserPath。
#pragma once

#include "DeclaresPCR.h"
#include "ReportTemplateData.h"

// 界面相关公共信息
class AFX_EXT_CLASS CPublicInfo
{
public:
	// 函数 CPublicInfo
	// 作用：执行CPublicInfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPublicInfo(void);
	// 函数 ~CPublicInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CPublicInfo(void);

	enum eIniFileType
	{
		INI_FILE_SYSTEM = 0, // System.ini 
		INI_FILE_ALGORITHM, // AlgorithmPara.ini
		INI_FILE_CALIBRATE, // CalibratePara.ini
		INI_FILE_CROSSTALK, // CrosstalkPara.ini
		INI_FILE_FILTER, // FilterPara.ini
	};

// Operations
public:
	// 函数 GetInstance
	// 作用：读取GetInstance。
	// 参数：无。
	// 返回：返回指针 CPublicInfo*。指针为空表示没有取到对象。
	static CPublicInfo* GetInstance(void);
	// 函数 CleanUp
	// 作用：执行CleanUp。
	// 参数：无。
	// 返回：没有返回值。
	static void CleanUp();
	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：strStartupPath：字符串；strUserName：字符串。
	// 返回：没有返回值。
	void Initialize(CString strStartupPath, CString strUserName);

	// 函数 ReadParameters
	// 作用：读取ReadParameters。
	// 参数：无。
	// 返回：没有返回值。
	void ReadParameters();
	// 函数 SaveParameters
	// 作用：把SaveParameters写入文件、仪器或界面。
	// 参数：无。
	// 返回：没有返回值。
	void SaveParameters();

	// 函数 GetIniFilePath
	// 作用：读取GetIniFilePath。
	// 参数：nIniType：整数；bRead：是或否。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetAnalysisDataType。
	CString GetIniFilePath(eIniFileType nIniType , BOOL bRead=TRUE); // 根据类型得到配置文件全路径

protected:
	// 函数 ReadAndCreateUserPath
	// 作用：读取ReadAndCreateUserPath。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetAnalysisDataType。
	BOOL ReadAndCreateUserPath();
	// 函数 ReadStringFromIniFile
	// 作用：读取ReadStringFromIniFile。
	// 参数：strAppName：字符串；strKeyName：字符串；strDefault：字符串；strIniFile：字符串。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetAnalysisDataType。
	CString ReadStringFromIniFile(CString strAppName, CString strKeyName, CString strDefault, CString strIniFile);

// Attributes
public:
	// 函数 SetAnalysisDataType
	// 作用：设置SetAnalysisDataType。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetAnalysisDataType(eAnalysisDataType nType) { m_nAnaDataType = nType; }
	// 函数 GetAnalysisDataType
	// 作用：读取GetAnalysisDataType。
	// 参数：无。
	// 返回：返回 eAnalysisDataType。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eAnalysisDataType GetAnalysisDataType() { return m_nAnaDataType; }

	//vector<COLORREF> GetChannelColor() { return m_vecChannelColor; }

	// 函数 GetStartupPath
	// 作用：读取GetStartupPath。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetStartupPath() { return m_strStartupPath; }
	// 函数 GetUserPath
	// 作用：读取GetUserPath。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetUserPath() { return m_strUserPath; } // 得到用户路径
	// 函数 GetUserSystemPath
	// 作用：读取GetUserSystemPath。
	// 参数：_T("\\System"。
	// 返回：返回一段文字。
	// 过程：函数里会调用 _T。
	CString GetUserSystemPath() { return m_strUserPath + _T("\\System"); }
	// 函数 SetUserDataSavePath
	// 作用：设置SetUserDataSavePath。
	// 参数：strPath：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetUserDataSavePath。
	void SetUserDataSavePath(CString strPath); // 设置用户数据保存路径
	// 函数 GetUserDataSavePath
	// 作用：读取GetUserDataSavePath。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetUserDataSavePath() { return m_strUserDataPath; } // 取得用户数据保存路径

	// 函数 GetUserName
	// 作用：读取GetUserName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetUserName() { return m_strUserName; }
	// 函数 GetUserRole
	// 作用：读取GetUserRole。
	// 参数：无。
	// 返回：返回 EPERMISSIONTYPE。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	EPERMISSIONTYPE GetUserRole() { return m_ePermissionType; }
	// 函数 SetUserRole
	// 作用：设置SetUserRole。
	// 参数：eType。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetUserRole(EPERMISSIONTYPE eType) { m_ePermissionType = eType; }

	// 函数 SampleTypeToText
	// 作用：执行SampleTypeToText。
	// 参数：eType。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetReportTemplateData。
	CString SampleTypeToText(eSampleType eType);
	// 函数 GetSampleTypeAbbrText
	// 作用：读取GetSampleTypeAbbrText。
	// 参数：eType。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetReportTemplateData。
	CString GetSampleTypeAbbrText(eSampleType eType);

	// 函数 TextToSampleType
	// 作用：执行TextToSampleType。
	// 参数：strText：字符串。
	// 返回：返回 eSampleType。
	// 过程：函数里会调用 GetReportTemplateData。
	eSampleType TextToSampleType(CString strText);

	// 函数 GetReportTemplateData
	// 作用：读取GetReportTemplateData。
	// 参数：无。
	// 返回：返回指针 CReportTemplateData*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CReportTemplateData* GetReportTemplateData() { return m_pReportData; }

	// 函数 GetFluoDataAutoAdjust
	// 作用：读取GetFluoDataAutoAdjust。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetFluoDataAutoAdjust() { return m_bFluoDataAutoAdjust; }
	// 函数 GetFluoDataMaxLimited
	// 作用：读取GetFluoDataMaxLimited。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetFluoDataMaxLimited() { return m_iFluoDataMaxLimited; } 
	// 函数 GetFluoDataAdjustLimited
	// 作用：读取GetFluoDataAdjustLimited。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetFluoDataAdjustLimited() { return m_iFluoDataAdjustLimited; }

protected:
	static CPublicInfo* m_pInstance;

	CString		m_strStartupPath;
	CString		m_strUserPath; // 用户路径
	CString		m_strUserDataPath; // 用户数据保存路径

	CString		m_strUserName; // 用户名

	eAnalysisDataType	m_nAnaDataType; // 扩增分析默认使用的数据类型
	EPERMISSIONTYPE m_ePermissionType;

	CReportTemplateData* m_pReportData; // 报告模板数据

	BOOL		m_bFluoDataAutoAdjust; // 检测荧光值过限自动调整
	int			m_iFluoDataMaxLimited; // 检测荧光值最大限制值
	int			m_iFluoDataAdjustLimited; // 需要补偿限制最大值
};

