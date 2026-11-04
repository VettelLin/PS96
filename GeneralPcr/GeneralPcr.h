// 【交接】 GeneralPcr\GeneralPcr.h
// 作用：GeneralPcr。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CGeneralPcrApp、InitInstance、ExitInstance、DECLARE_MESSAGE_MAP、InitRatioParam、InitMapSampleTypeToCbIndex、GetSampleTypeCbIndex、ReadParam。

#pragma once

#include "SetInfo.h"

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include "LisSetInfo.h"
#include "LinkList.h"
#include "DeclaresPCR.h"
#include "ExperimentData.h"
#include "ConfigureDBInfo.h"
#include "TemplateFileInfo.h"
#include "PowerOffProtect.h"
#include "Ps96IvdSet.h"
#include "CYInfo.h"
#include "SamInfoExportMode.h"
#include "DeclaresPCR.h"

#include <map>

using namespace std;

class CGeneralPcrApp : public CWinApp
{
public:
	// 函数 CGeneralPcrApp
	// 作用：执行CGeneralPcrApp。
	// 参数：无。
	// 返回：没有返回值。
	CGeneralPcrApp();
	// 函数 ~CGeneralPcrApp
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CGeneralPcrApp();

// Overrides
public:
	// 函数 InitInstance
	// 作用：初始化InitInstance。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL InitInstance();
	// 函数 ExitInstance
	// 作用：执行ExitInstance。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ExitInstance();

// Implementation

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

public:
	// 函数 InitRatioParam
	// 作用：初始化InitRatioParam。
	// 参数：无。
	// 返回：没有返回值。
	void InitRatioParam();

	// 函数 InitMapSampleTypeToCbIndex
	// 作用：初始化InitMapSampleTypeToCbIndex。
	// 参数：无。
	// 返回：没有返回值。
	void InitMapSampleTypeToCbIndex();	//初始化样本类型在下拉选择框中的下标信息
	// 函数 GetSampleTypeCbIndex
	// 作用：读取GetSampleTypeCbIndex。
	// 参数：eType。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetSampleTypeCbIndex(eSampleType eType);	//获取样本类型在下拉选择框中的下标信息

	// 函数 ReadParam
	// 作用：读取ReadParam。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ReadParam();	//从文件中读取参数信息
	// 函数 WriteParam
	// 作用：把WriteParam写入文件、仪器或界面。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int WriteParam();	//保存参数信息到文件中

	// 函数 InitLanguageSet
	// 作用：初始化InitLanguageSet。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int InitLanguageSet();	//从文件中读取语言设置
	// 函数 WriteLanguageSet
	// 作用：把WriteLanguageSet写入文件、仪器或界面。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int WriteLanguageSet();	//保存语言设置到文件中

	// 函数 ReadCYInfo
	// 作用：读取ReadCYInfo。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ReadCYInfo();
	// 函数 WriteCYInfo
	// 作用：把WriteCYInfo写入文件、仪器或界面。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int WriteCYInfo();

	// 函数 ReadPs96IvdSet
	// 作用：读取ReadPs96IvdSet。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ReadPs96IvdSet();	//从文件中读取PS96 IVD模式设置
	// 函数 WritePs96IvdSet
	// 作用：把WritePs96IvdSet写入文件、仪器或界面。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int WritePs96IvdSet();	//保存PS96 IVD模式设置到文件中

	// 函数 ReadSystemAnalyseParam
	// 作用：读取ReadSystemAnalyseParam。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ReadSystemAnalyseParam();	
	// 函数 WriteSystemAnalyseParam
	// 作用：把WriteSystemAnalyseParam写入文件、仪器或界面。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int WriteSystemAnalyseParam();

	// 函数 ReadDefaultGeneName
	// 作用：读取ReadDefaultGeneName。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ReadDefaultGeneName();	
	// 函数 WriteDefaultGeneName
	// 作用：把WriteDefaultGeneName写入文件、仪器或界面。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int WriteDefaultGeneName();

	// 函数 GetBeIVDUser
	// 作用：读取GetBeIVDUser。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeIVDUser();	//判断用户类型是否是IVD用户

	// 函数 GetBeEnglish
	// 作用：读取GetBeEnglish。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeEnglish();	//判断当前软件语言是否为英文

	// 函数 SetLanguage
	// 作用：设置SetLanguage。
	// 参数：eLang；bSaveToFile：是或否。
	// 返回：没有返回值。
	void SetLanguage(eLanguageUI eLang,BOOL bSaveToFile = TRUE);

	// 函数 GetBeAdminPermission
	// 作用：读取GetBeAdminPermission。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeAdminPermission();	//判断当前用户是否是管理员用户
	// 函数 GetBeOrdinaryPermission
	// 作用：读取GetBeOrdinaryPermission。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeOrdinaryPermission();	//判断当前用户是否是普通用户

	// 函数 InitTemplateFileInfo
	// 作用：初始化InitTemplateFileInfo。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int InitTemplateFileInfo();	//初始化模板文件列表信息
	// 函数 ReadDefaultTemplateFileInfo
	// 作用：读取ReadDefaultTemplateFileInfo。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ReadDefaultTemplateFileInfo();	//保存默认的模板文件列表信息
	// 函数 IsTemplateExist
	// 作用：判断IsTemplateExist是否成立。
	// 参数：strTemplateTitle：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int IsTemplateExist(CString strTemplateTitle);	//判断用户新打开的模板文件是否已经存在于模板文件列表中
	// 函数 AddNewTemplate
	// 作用：创建或加入AddNewTemplate。
	// 参数：temFileInfo。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddNewTemplate(CTemplateFileInfo& temFileInfo);	//添加新的模板文件信息

	// 函数 DeleteTemplate
	// 作用：更新或清除DeleteTemplate。
	// 参数：iIndex：整数。
	// 返回：返回是或否。
	BOOL DeleteTemplate(int iIndex);

	// 函数 InitilizePCR
	// 作用：初始化InitilizePCR。
	// 参数：strStartupPath：字符串。
	// 返回：返回是或否。
	BOOL InitilizePCR(CString strStartupPath);
	// 函数 InitilizePCRStartPage
	// 作用：初始化InitilizePCRStartPage。
	// 参数：strStartupPath：字符串。
	// 返回：返回是或否。
	BOOL InitilizePCRStartPage(CString strStartupPath);

	// 函数 ResetTextFont
	// 作用：更新或清除ResetTextFont。
	// 参数：无。
	// 返回：没有返回值。
	void ResetTextFont();

	// 函数 InitChanNum
	// 作用：初始化InitChanNum。
	// 参数：无。
	// 返回：没有返回值。
	void InitChanNum();
	// 函数 InitDefaultDyeName
	// 作用：初始化InitDefaultDyeName。
	// 参数：无。
	// 返回：没有返回值。
	void InitDefaultDyeName();
	// 函数 InitFilterParam
	// 作用：初始化InitFilterParam。
	// 参数：无。
	// 返回：没有返回值。
	void InitFilterParam();
	// 函数 InitAmpCrossSetValue
	// 作用：初始化InitAmpCrossSetValue。
	// 参数：无。
	// 返回：没有返回值。
	void InitAmpCrossSetValue();
	// 函数 InitMeltCrossSetValue
	// 作用：初始化InitMeltCrossSetValue。
	// 参数：无。
	// 返回：没有返回值。
	void InitMeltCrossSetValue();

	// 函数 DeleteSystemAnaParam
	// 作用：更新或清除DeleteSystemAnaParam。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteSystemAnaParam();

	// 函数 AddDefaultGeneName
	// 作用：创建或加入AddDefaultGeneName。
	// 参数：strData：字符串；bSave：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddDefaultGeneName(CString strData,BOOL bSave);
	// 函数 DeleteDefaultGeneName
	// 作用：更新或清除DeleteDefaultGeneName。
	// 参数：iIndex：整数；bSave：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteDefaultGeneName(int iIndex, BOOL bSave=TRUE);

	// 函数 GetChannelDyeInfo
	// 作用：读取GetChannelDyeInfo。
	// 参数：无。
	// 返回：没有返回值。
	void GetChannelDyeInfo();

	// 函数 HasExpNameExist
	// 作用：判断HasExpNameExist是否成立。
	// 参数：strExpName：字符串。
	// 返回：返回是或否。
	BOOL HasExpNameExist(CString strExpName);
	// 函数 HasExpSaveFileUsed
	// 作用：判断HasExpSaveFileUsed是否成立。
	// 参数：strExpSavePath：字符串。
	// 返回：返回是或否。
	BOOL HasExpSaveFileUsed(CString strExpSavePath);
	// 函数 DeleteSavePathName
	// 作用：更新或清除DeleteSavePathName。
	// 参数：strPathName：字符串。
	// 返回：没有返回值。
	void DeleteSavePathName(CString strPathName);
	// 函数 HasExpSaveFileExist
	// 作用：判断HasExpSaveFileExist是否成立。
	// 参数：strExpSavePath：字符串。
	// 返回：返回是或否。
	BOOL HasExpSaveFileExist(CString strExpSavePath);

	// 函数 SaveTempalteOrder
	// 作用：把SaveTempalteOrder写入文件、仪器或界面。
	// 参数：无。
	// 返回：没有返回值。
	void SaveTempalteOrder();

protected:
	// 函数 FindAndInputUser
	// 作用：执行FindAndInputUser。
	// 参数：strStartupPath：字符串。
	// 返回：返回是或否。
	BOOL FindAndInputUser(CString strStartupPath);

	// 函数 DeleteDyeInfo
	// 作用：更新或清除DeleteDyeInfo。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteDyeInfo();

	// 函数 IsTemplateFile
	// 作用：判断IsTemplateFile是否成立。
	// 参数：strFilePath：字符串。
	// 返回：返回是或否。
	BOOL IsTemplateFile(CString strFilePath);
	// 函数 ReadTemplateOrder
	// 作用：读取ReadTemplateOrder。
	// 参数：pArrayOrder：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void ReadTemplateOrder(CStringArray* pArrayOrder);
	// 函数 IsDefaultTemplateExist
	// 作用：判断IsDefaultTemplateExist是否成立。
	// 参数：strTempalteName：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int IsDefaultTemplateExist(CString strTempalteName);

public:
	CRect m_rcWorkArea;	//记录工作区大小
	CRect m_rcScreen;	//记录屏幕大小

	ULONG_PTR m_gdiplusToken;

	HANDLE m_hMutex;	//确保同一台PC同一时间只能有一个实例运行

	CSetInfo m_setInfo;

	CLisSetInfo m_lisSetInfo;

	CPs96IvdSet m_ps96IvdSet; 

	int m_iFileManageDlgH;	//实验文件管理窗口高度

	CDyeInfoList m_listDyeInfo; // 系统定义的染料目标信息

	CDBUserInfo m_curUserInfo;	//记录当前登录用户的信息

	ESAMINFOEXPORTMODE m_eSamExportMode;	//样本信息导出模式,临时使用，最终要放到设置信息类里,20220508

	CLanguageInfo* m_pLangInfo;	//记录CLanguageInfo单例模式的指针，方便使用，20220512，孙文郎

	map<eSampleType,int> m_mapSamTypeToCbIndex;	//记录样本类型再下拉选择中的下标

	CLinkList<CTemplateFileInfo> m_lnkDefTemFileInfo;	//记录软件自带的模板文件信息
	CLinkList<CTemplateFileInfo> m_lnkTotalTemFileInfo;	//记录所有的模板文件信息，默认在前，用户自己以打开方式添加的在后

	BOOL m_bInitNormal;	//记录软件是否已经打开

	CPowerOffProtect m_powerOffProtect;
	CLinkList<int> m_lnkLnkIndex;	//保存需要运行的（被断电保护的）实验流程在m_powerOffProtect中的下标

	Color m_gclrSoftTheme;
	Color m_gclrSoftThemeEnd;
	Color m_gclr2LevelTheme;
	Color m_gclr3LevelTheme;
	COLORREF m_clrSoftTheme;
	COLORREF m_clr2LevelTheme;
	COLORREF m_clr3LevelTheme;
	COLORREF m_clrSoftLight;
	COLORREF m_clrDarkTx;

	LANGID m_pcLangId;	//保存软件启动时本机的语言环境

	int m_iStdDensityDpd;	//标准品浓度的小数点位数

	CCYInfo m_cyInfo;	//康研葆使用的相关信息

	//系统默认的分析参数
	vector<CString> m_vecDefDyeName;
	int m_iDefChanNum;
	float**	m_ppFCrosstalkPara; // 交叉干扰参数，扩增分析使用
	float**	m_ppFMeltCrosstalk; // 交叉干扰参数，熔曲分析使用
	vector<tagFilterItem> m_vecFlt;	//滤波参数
	vector<tagAnaAmplifyPara> m_vecAmplifyPara; //扩增分析参数
	vector<tagAnaMeltCurvePara>	m_vecMeltCurvePara;	//熔曲分析参数

	//默认基因名
	CLinkList<CString> m_lnkDefGN;

protected:
	CStringArray	m_arrayExpInitName;
	CStringArray	m_arrayExpSaveFileUsed;
};

extern CGeneralPcrApp theApp;



