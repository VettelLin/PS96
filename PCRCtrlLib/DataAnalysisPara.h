// 【交接】 PCRCtrlLib\DataAnalysisPara.h
// 作用：DataAnalysisPara。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CDataAnalysisPara、WriteFile、ReadFile、CopyFrom、SetChannelSplineThreshold、Clear、DeleteAll、DeleteAmplifyPara。
#pragma once

#include "DeclaresPCR.h"

// 数据分析参数类，包括扩增参数、熔解参数、结果分析参数、结果判定参数等
class AFX_EXT_CLASS CDataAnalysisPara
{
public:
	// 函数 CDataAnalysisPara
	// 作用：执行CDataAnalysisPara。
	// 参数：无。
	// 返回：没有返回值。
	CDataAnalysisPara(void);
	// 函数 ~CDataAnalysisPara
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CDataAnalysisPara(void);

public:
	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	BOOL WriteFile(CFile* pFile,WORD wVersion,BOOL bProject);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	BOOL ReadFile(CFile* pFile, WORD wVersion,BOOL bProject);
	// 函数 CopyFrom
	// 作用：复制CopyFrom。
	// 参数：pAnalysis：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void CopyFrom(CDataAnalysisPara* pAnalysis);
	// 函数 SetChannelSplineThreshold
	// 作用：设置SetChannelSplineThreshold。
	// 参数：strTarget：字符串；strDye：字符串；nDataType：整数；dThreshold：小数。
	// 返回：没有返回值。
	void SetChannelSplineThreshold(CString strTarget, CString strDye, eAnalysisDataType nDataType, double dThreshold);

	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();

protected:
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteAll();
	// 函数 DeleteAmplifyPara
	// 作用：更新或清除DeleteAmplifyPara。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteAmplifyPara();
	// 函数 DeleteMeltCurvePara
	// 作用：更新或清除DeleteMeltCurvePara。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteMeltCurvePara();
	// 函数 DeleteInspectScope
	// 作用：更新或清除DeleteInspectScope。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteInspectScope();
	// 函数 DeleteBasicRule
	// 作用：更新或清除DeleteBasicRule。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteBasicRule();

	// 函数 WriteAmplifyPara
	// 作用：把WriteAmplifyPara写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	BOOL WriteAmplifyPara(CFile* pFile,WORD wVersion,BOOL bProject);
	// 函数 WriteMeltCurvePara
	// 作用：把WriteMeltCurvePara写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteMeltCurvePara(CFile* pFile);
	// 函数 WriteInspectScope
	// 作用：把WriteInspectScope写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteInspectScope(CFile* pFile);
	// 函数 WriteResultRule
	// 作用：把WriteResultRule写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteResultRule(CFile* pFile);

	// 函数 ReadAmplifyPara
	// 作用：读取ReadAmplifyPara。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	BOOL ReadAmplifyPara(CFile* pFile, WORD wVersion,BOOL bProject);
	// 函数 ReadMeltCurvePara
	// 作用：读取ReadMeltCurvePara。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL ReadMeltCurvePara(CFile* pFile, WORD wVersion);
	// 函数 ReadInspectScope
	// 作用：读取ReadInspectScope。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL ReadInspectScope(CFile* pFile, WORD wVersion);
	// 函数 ReadResultRule
	// 作用：读取ReadResultRule。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL ReadResultRule(CFile* pFile, WORD wVersion);

// Attributes
public:
	// 函数 GetAmplifyParaBy
	// 作用：读取GetAmplifyParaBy。
	// 参数：strTarget：字符串；strDye：字符串；iChannel：整数。
	// 返回：返回指针 tagAnaAmplifyPara*。指针为空表示没有取到对象。
	tagAnaAmplifyPara* GetAmplifyParaBy(CString strTarget, CString strDye, int iChannel); 
	// 函数 GetMeltCurveParaBy
	// 作用：读取GetMeltCurveParaBy。
	// 参数：strTarget：字符串。
	// 返回：返回指针 tagAnaMeltCurvePara*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetAmplifyParaCount、GetCount。
	tagAnaMeltCurvePara* GetMeltCurveParaBy(CString strTarget); 
	// 函数 GetInspectScopeBy
	// 作用：读取GetInspectScopeBy。
	// 参数：strTarget：字符串。
	// 返回：返回指针 tagAnaInspectScope*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetAmplifyParaCount、GetCount。
	tagAnaInspectScope* GetInspectScopeBy(CString strTarget); 
	// 函数 GetBasicRuleBy
	// 作用：读取GetBasicRuleBy。
	// 参数：strTarget：字符串。
	// 返回：返回指针 tagAnaBasicRule*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetAmplifyParaCount、GetCount。
	tagAnaBasicRule* GetBasicRuleBy(CString strTarget); 

	// 函数 GetAmplifyParaBy
	// 作用：读取GetAmplifyParaBy。
	// 参数：nIndex：整数。
	// 返回：返回指针 tagAnaAmplifyPara*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetAmplifyParaCount、GetCount。
	tagAnaAmplifyPara* GetAmplifyParaBy(int nIndex); 

	// 指标分析参数相关参数
	// 函数 SetAmplifyParaCount
	// 作用：设置SetAmplifyParaCount。
	// 参数：iCount：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetAmplifyParaCount、GetCount。
	int SetAmplifyParaCount(int iCount);
	// 函数 GetAmplifyParaCount
	// 作用：读取GetAmplifyParaCount。
	// 参数：m_arrayAmplifyPara.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetAmplifyParaCount() { return m_arrayAmplifyPara.GetCount(); }
	// 函数 AddAmplifyPara
	// 作用：创建或加入AddAmplifyPara。
	// 参数：m_arrayAmplifyPara.Add(pAnalysis。
	// 返回：没有返回值。
	// 过程：函数里会调用 Add。
	void AddAmplifyPara(tagAnaAmplifyPara* pAnalysis) { m_arrayAmplifyPara.Add(pAnalysis); } // 增加一种指标参数，需要先申请指针
	// 函数 SetAmplifyParaAt
	// 作用：设置SetAmplifyParaAt。
	// 参数：nIndex：整数；pAnalysis：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetMeltCurveParaCount、GetCount。
	void SetAmplifyParaAt(int nIndex, tagAnaAmplifyPara* pAnalysis); // 修改参数，不需要申请指针
	// 函数 GetAmplifyParaByTarget
	// 作用：读取GetAmplifyParaByTarget。
	// 参数：strTarget：字符串；strDye：字符串。
	// 返回：返回指针 tagAnaAmplifyPara*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetMeltCurveParaCount、GetCount。
	tagAnaAmplifyPara* GetAmplifyParaByTarget(CString strTarget, CString strDye); 
	// 函数 GetAmplifyParaByDye
	// 作用：读取GetAmplifyParaByDye。
	// 参数：strDye：字符串。
	// 返回：返回指针 tagAnaAmplifyPara*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetMeltCurveParaCount、GetCount。
	tagAnaAmplifyPara* GetAmplifyParaByDye(CString strDye);
	// 函数 DeleteOneAmplifyPara
	// 作用：更新或清除DeleteOneAmplifyPara。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetMeltCurveParaCount、GetCount。
	void DeleteOneAmplifyPara(int iIndex);

	// 熔解曲线相关参数
	// 函数 SetMeltCurveParaCount
	// 作用：设置SetMeltCurveParaCount。
	// 参数：iCount：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetMeltCurveParaCount、GetCount。
	int SetMeltCurveParaCount(int iCount);
	// 函数 GetMeltCurveParaCount
	// 作用：读取GetMeltCurveParaCount。
	// 参数：m_arrayMeltCurvePara.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetMeltCurveParaCount() { return m_arrayMeltCurvePara.GetCount(); }
	// 函数 AddMeltCurvePara
	// 作用：创建或加入AddMeltCurvePara。
	// 参数：m_arrayMeltCurvePara.Add(pMeltCurve。
	// 返回：没有返回值。
	// 过程：函数里会调用 Add。
	void AddMeltCurvePara(tagAnaMeltCurvePara* pMeltCurve) { m_arrayMeltCurvePara.Add(pMeltCurve); } // 增加一种指标参数，需要先申请指针
	// 函数 GetMeltCurveParaBy
	// 作用：读取GetMeltCurveParaBy。
	// 参数：nIndex：整数。
	// 返回：返回指针 tagAnaMeltCurvePara*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetInspectScopeCount、GetCount。
	tagAnaMeltCurvePara* GetMeltCurveParaBy(int nIndex); 
	// 函数 SetMeltCurveParaAt
	// 作用：设置SetMeltCurveParaAt。
	// 参数：nIndex：整数；pMeltCurve：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetInspectScopeCount、GetCount。
	void SetMeltCurveParaAt(int nIndex, tagAnaMeltCurvePara* pMeltCurve); // 修改参数，不需要申请指针

	// 目标定量检测范围参数相关
	// 函数 GetInspectScopeCount
	// 作用：读取GetInspectScopeCount。
	// 参数：m_arrayInspectScope.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetInspectScopeCount() { return m_arrayInspectScope.GetCount(); }
	// 函数 AddInspectScope
	// 作用：创建或加入AddInspectScope。
	// 参数：m_arrayInspectScope.Add(pInspectScope。
	// 返回：没有返回值。
	// 过程：函数里会调用 Add。
	void AddInspectScope(tagAnaInspectScope* pInspectScope) { m_arrayInspectScope.Add(pInspectScope); } // 增加一种指标参数，需要先申请指针
	// 函数 GetInspectScopeBy
	// 作用：读取GetInspectScopeBy。
	// 参数：nIndex：整数。
	// 返回：返回指针 tagAnaInspectScope*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetUseRule。
	tagAnaInspectScope* GetInspectScopeBy(int nIndex); 
	// 函数 SetInspectScopeAt
	// 作用：设置SetInspectScopeAt。
	// 参数：nIndex：整数；pInspectScope：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetUseRule。
	void SetInspectScopeAt(int nIndex, tagAnaInspectScope* pInspectScope); // 修改参数，不需要申请指针

	// 结果判定规则参数相关
	// 函数 GetUseRule
	// 作用：读取GetUseRule。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetUseRule() { return m_bUseRule; }
	// 函数 SetUseRule
	// 作用：设置SetUseRule。
	// 参数：bUse：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetUseRule(BOOL bUse) { m_bUseRule = bUse; }
	// 函数 GetBasicRuleCount
	// 作用：读取GetBasicRuleCount。
	// 参数：m_arrayBasicRule.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetBasicRuleCount() { return m_arrayBasicRule.GetCount(); }
	// 函数 AddBasicRule
	// 作用：创建或加入AddBasicRule。
	// 参数：m_arrayBasicRule.Add(pBasicRule。
	// 返回：没有返回值。
	// 过程：函数里会调用 Add。
	void AddBasicRule(tagAnaBasicRule* pBasicRule) { m_arrayBasicRule.Add(pBasicRule); } // 增加一种指标参数，需要先申请指针
	// 函数 GetBasicRuleBy
	// 作用：读取GetBasicRuleBy。
	// 参数：nIndex：整数。
	// 返回：返回指针 tagAnaBasicRule*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetArrayAmplifyParaPtr。
	tagAnaBasicRule* GetBasicRuleBy(int nIndex); 
	// 函数 SetBasicRule
	// 作用：设置SetBasicRule。
	// 参数：nIndex：整数；pBasicRule：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetArrayAmplifyParaPtr。
	void SetBasicRule(int nIndex, tagAnaBasicRule* pBasicRule); // 修改参数，不需要申请指针
	
	// 函数 GetArrayAmplifyParaPtr
	// 作用：读取GetArrayAmplifyParaPtr。
	// 参数：无。
	// 返回：返回指针 CPtrArray*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPtrArray* GetArrayAmplifyParaPtr(){return &m_arrayAmplifyPara;}
	// 函数 GetArrayMeltCurveParaPtr
	// 作用：读取GetArrayMeltCurveParaPtr。
	// 参数：无。
	// 返回：返回指针 CPtrArray*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPtrArray* GetArrayMeltCurveParaPtr(){return &m_arrayMeltCurvePara;}

protected:
	CPtrArray	m_arrayAmplifyPara; // 目标分析参数 tagAnaAmplifyPara
	CPtrArray	m_arrayMeltCurvePara; // 熔解曲线参数 tagAnaMeltCurvePara
	CPtrArray	m_arrayInspectScope; // 目标定量检测范围 tagAnaInspectScope
	BOOL		m_bUseRule; // 是否使用判定规则
	CPtrArray	m_arrayBasicRule; // 基本判定规则 tagAnaBasicRule
};

