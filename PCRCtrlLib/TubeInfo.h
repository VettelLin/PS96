// 【交接】 PCRCtrlLib\TubeInfo.h
// 作用：TubeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTubeInfo、WriteFile、ReadFile、HasUsed、InitDyeChannel、PasteTargetInfoFromItem、PerfectTargetDyeInfo、DeleteAllDyeTargetInfo。
#pragma once
#include "SampleInfo.h"
#include "DeclaresPCR.h"
#include "DyeTargetInfo.h"

//删除样本信息时的删除类型（删除所有、删除孔板编辑页面内容（染料名称和颜色除外、删除病人信息（包括样本类型）））
typedef enum DeleteType{
	EDT_DELETEALL,EDT_DELETE1,EDT_DELETE2
}EDELETETYPE;

//样本ID相同的孔位视为同一个样本，报结果时多个孔位只报一个结果
typedef enum SampleTotalResult{
	ESTR_NEGATIVE,ESTR_INVALID,ESTR_NORMAL
}ESAMPLETOTALRESULT;

class AFX_EXT_CLASS CTubeInfo : public CSampleInfo
{
public:
	// 函数 CTubeInfo
	// 作用：执行CTubeInfo。
	// 参数：无。
	// 返回：没有返回值。
	CTubeInfo();
	// 函数 CTubeInfo
	// 作用：执行CTubeInfo。
	// 参数：nID：整数。
	// 返回：没有返回值。
	CTubeInfo(int nID);
	// 函数 ~CTubeInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 HasUsed。
	~CTubeInfo(void);

	// 函数 CTubeInfo
	// 作用：执行CTubeInfo。
	// 参数：tubeInfo。
	// 返回：没有返回值。
	// 过程：函数里会调用 HasUsed。
	CTubeInfo(const CTubeInfo& tubeInfo);
	void operator=(const CTubeInfo& tubeInfo);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	// 过程：函数里会调用 HasUsed。
	BOOL WriteFile(CFile* pFile,WORD wVersion);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	// 过程：函数里会调用 HasUsed。
	BOOL ReadFile(CFile* pFile,WORD wVersion);

	// 函数 HasUsed
	// 作用：判断HasUsed是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL HasUsed() { return m_nSampleType != SAMPLE_TYPE_NONE; }
	// 函数 InitDyeChannel
	// 作用：初始化InitDyeChannel。
	// 参数：iChannelCount：整数。
	// 返回：没有返回值。
	void InitDyeChannel(int iChannelCount); // 初始化染料通道
	// 函数 PasteTargetInfoFromItem
	// 作用：执行PasteTargetInfoFromItem。
	// 参数：pItem：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTubeID。
	void PasteTargetInfoFromItem(CReagentItem* pItem); // 复制项目中定义的染料信息
	// 函数 PerfectTargetDyeInfo
	// 作用：执行PerfectTargetDyeInfo。
	// 参数：pArrayChannel：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTubeID。
	void PerfectTargetDyeInfo(CPtrArray* pArrayChannel);

protected:
	// 函数 DeleteAllDyeTargetInfo
	// 作用：更新或清除DeleteAllDyeTargetInfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTubeID。
	void DeleteAllDyeTargetInfo();

public:
	// 函数 SetTmCount
	// 作用：设置SetTmCount。
	// 参数：nCount：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTubeID。
	void SetTmCount(int nCount);
	// 函数 GetTubeID
	// 作用：读取GetTubeID。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetTubeID() { return m_iTubeID; }
	// 函数 GetTubeLabel
	// 作用：读取GetTubeLabel。
	// 参数：iColNum：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetTubeLabel。
	CString GetTubeLabel(int iColNum);
	// 函数 SetTubeLabel
	// 作用：设置SetTubeLabel。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTubeLabel(CString string) { m_strTubeLabel = string; }
	// 函数 GetTubeFlag
	// 作用：读取GetTubeFlag。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetTubeFlag() { return m_strTubeFlag; }
	// 函数 SetTubeFlag
	// 作用：设置SetTubeFlag。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTubeFlag(CString string) { m_strTubeFlag = string; }
	// 函数 GetSampleID
	// 作用：读取GetSampleID。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetSampleID() { return m_strSampleID; }
	// 函数 SetSampleID
	// 作用：设置SetSampleID。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSampleID(CString string) { m_strSampleID = string; }
	// 函数 GetSampleName
	// 作用：读取GetSampleName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetSampleName() { return m_strSampleName; }
	// 函数 SetSampleName
	// 作用：设置SetSampleName。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSampleName(CString string) { m_strSampleName = string; }
	// 函数 GetSampleColor
	// 作用：读取GetSampleColor。
	// 参数：无。
	// 返回：返回 COLORREF。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	COLORREF GetSampleColor() { return m_clrSample; }
	// 函数 SetSampleColor
	// 作用：设置SetSampleColor。
	// 参数：color：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSampleColor(COLORREF color) { m_clrSample = color; }

	// 函数 GetSampleType
	// 作用：读取GetSampleType。
	// 参数：无。
	// 返回：返回 eSampleType。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eSampleType GetSampleType() { return m_nSampleType; }
	// 函数 SetSampleType
	// 作用：设置SetSampleType。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSampleType(eSampleType nType) { m_nSampleType = nType; }
	// 函数 GetIsRepeatTube
	// 作用：读取GetIsRepeatTube。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetIsRepeatTube() { return m_bRepeatTube; }
	// 函数 SetIsRepeatTube
	// 作用：设置SetIsRepeatTube。
	// 参数：bSet：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetIsRepeatTube(BOOL bSet) { m_bRepeatTube = bSet; }
	
	// 函数 GetRepeatNo
	// 作用：读取GetRepeatNo。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetRepeatNo() { return m_iRepeatNo; }
	// 函数 GetRepeatNoString
	// 作用：读取GetRepeatNoString。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetRepeatNo。
	CString GetRepeatNoString();

	// 函数 SetRepeatNo
	// 作用：设置SetRepeatNo。
	// 参数：iNo：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRepeatNo(int iNo) { m_iRepeatNo = iNo; }
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
	void SetComments(CString string) { m_strComments = string;}

	// 函数 GetTargetCount
	// 作用：读取GetTargetCount。
	// 参数：m_arrayDyeTarget.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetTargetCount() { return m_arrayDyeTarget.GetCount(); }
	// 函数 GetTargetInfo
	// 作用：读取GetTargetInfo。
	// 参数：iIndex：整数。
	// 返回：返回指针 CDyeTargetInfo*。指针为空表示没有取到对象。
	// 过程：函数里会调用 AddDyeTargetInfo、Add。
	CDyeTargetInfo* GetTargetInfo(int iIndex);

	// 函数 AddDyeTargetInfo
	// 作用：创建或加入AddDyeTargetInfo。
	// 参数：m_arrayDyeTarget.Add(pDyeInfo。
	// 返回：没有返回值。
	// 过程：函数里会调用 Add。
	void AddDyeTargetInfo(CDyeTargetInfo* pDyeInfo) { m_arrayDyeTarget.Add(pDyeInfo); }
	// 函数 FindTargetInfoByTarget
	// 作用：执行FindTargetInfoByTarget。
	// 参数：strTarget：字符串。
	// 返回：返回指针 CDyeTargetInfo*。指针为空表示没有取到对象。
	CDyeTargetInfo* FindTargetInfoByTarget(CString strTarget);
	// 函数 FindTargetInfoByChannel
	// 作用：执行FindTargetInfoByChannel。
	// 参数：iChannel：整数。
	// 返回：返回指针 CDyeTargetInfo*。指针为空表示没有取到对象。
	CDyeTargetInfo* FindTargetInfoByChannel(int iChannel);

	// 函数 ResetDyeInfo
	// 作用：更新或清除ResetDyeInfo。
	// 参数：无。
	// 返回：没有返回值。
	void ResetDyeInfo();	//重置（清空）染料信息，不会释放指针
	// 函数 ResetDyeTargetInfoExceptDyeNameAndColor
	// 作用：更新或清除ResetDyeTargetInfoExceptDyeNameAndColor。
	// 参数：无。
	// 返回：没有返回值。
	void ResetDyeTargetInfoExceptDyeNameAndColor();	//重置（清空）染料信息，除了染料名和颜色，

	// 函数 GetDyeName
	// 作用：读取GetDyeName。
	// 参数：iIndex：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetCalibrateChannel。
	CString GetDyeName(int iIndex);
	// 函数 SetDyeName
	// 作用：设置SetDyeName。
	// 参数：iIndex：整数；strDyeName：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetCalibrateChannel。
	void SetDyeName(int iIndex,CString strDyeName);

	// 函数 GetTargetName
	// 作用：读取GetTargetName。
	// 参数：iIndex：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetCalibrateChannel。
	CString GetTargetName(int iIndex);
	// 函数 SetTargetName
	// 作用：设置SetTargetName。
	// 参数：iIndex：整数；strTarget：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetCalibrateChannel。
	void SetTargetName(int iIndex,CString strTarget);

	// 函数 GetDyeTargetInfo
	// 作用：读取GetDyeTargetInfo。
	// 参数：iIndex：整数；strDyeName：字符串；strTargetName：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetCalibrateChannel。
	int GetDyeTargetInfo(int iIndex,CString& strDyeName,CString strTargetName);

	// 函数 SetCalibrateChannel
	// 作用：设置SetCalibrateChannel。
	// 参数：iChannel：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCalibrateChannel(int iChannel) { m_iCalibrateChannel = iChannel; }
	// 函数 GetCalibrateChannel
	// 作用：读取GetCalibrateChannel。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCalibrateChannel()  { return m_iCalibrateChannel; }

	// 函数 GetBeNeedDensity
	// 作用：读取GetBeNeedDensity。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeNeedDensity();	//获取是否需要设置样本浓度值（非反算浓度值）
	// 函数 GetBeNoneSampleType
	// 作用：读取GetBeNoneSampleType。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeNoneSampleType();	//判断样本类型是否为空
	// 函数 GetBeUnknown
	// 作用：读取GetBeUnknown。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeUnknown();	//判断是否是待测样本
	// 函数 GetBePositive
	// 作用：读取GetBePositive。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBePositive();	//判断样本类型是否是阳性对照
	// 函数 GetBeNegtive
	// 作用：读取GetBeNegtive。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeNegtive();	//判断样本类型是否是阴性对照

	// 函数 GetSampleDyeTargetColor
	// 作用：读取GetSampleDyeTargetColor。
	// 参数：iChanIndex：整数。
	// 返回：返回 COLORREF。
	COLORREF GetSampleDyeTargetColor(int iChanIndex);
	// 函数 SetSampleDyeTargetColor
	// 作用：设置SetSampleDyeTargetColor。
	// 参数：iChanIndex：整数；clrDyeTarget：颜色。
	// 返回：没有返回值。
	void SetSampleDyeTargetColor(int iChanIndex,COLORREF clrDyeTarget);

	// 函数 GetSampleChannelSelectState
	// 作用：读取GetSampleChannelSelectState。
	// 参数：iChanIndex：整数。
	// 返回：返回是或否。
	BOOL GetSampleChannelSelectState(int iChanIndex);
	// 函数 SetSampleChannelSelectState
	// 作用：设置SetSampleChannelSelectState。
	// 参数：iChanIndex：整数；bSelectState：是或否。
	// 返回：没有返回值。
	void SetSampleChannelSelectState(int iChanIndex,BOOL bSelectState);

	// 函数 GetFirstNonZeroDensity
	// 作用：读取GetFirstNonZeroDensity。
	// 参数：无。
	// 返回：返回一个小数。
	double GetFirstNonZeroDensity();	//获取第一个非零（标准品、校准品）浓度值
	// 函数 GetFirstNonZeroDensityString
	// 作用：读取GetFirstNonZeroDensityString。
	// 参数：iDPd：整数。
	// 返回：返回一段文字。
	CString GetFirstNonZeroDensityString(int iDPd = 4);	//iDPd--小数点位数
	// 函数 GetAllChannelDensityString
	// 作用：读取GetAllChannelDensityString。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetAllChannelDensityString();	//获取所有通道的浓度字符串，用换行符分隔

	// 函数 GetDensity
	// 作用：读取GetDensity。
	// 参数：iChanIndex：整数。
	// 返回：返回一个小数。
	double GetDensity(int iChanIndex);	//获取特定通道（标准品、校准品）浓度值
	// 函数 GetDensityString
	// 作用：读取GetDensityString。
	// 参数：iChanIndex：整数；iDPd：整数。
	// 返回：返回一段文字。
	CString GetDensityString(int iChanIndex,int iDPd = 4);	//iDPd--小数点位数

	// 函数 GetCalculatedDensity
	// 作用：读取GetCalculatedDensity。
	// 参数：iChanIndex：整数。
	// 返回：返回一个小数。
	double GetCalculatedDensity(int iChanIndex);	//获取特定通道的反算浓度值
	// 函数 GetCalculatedDensityString
	// 作用：读取GetCalculatedDensityString。
	// 参数：iChanIndex：整数；iDPd：整数。
	// 返回：返回一段文字。
	CString GetCalculatedDensityString(int iChanIndex,int iDPd = 4);	//iDPd--小数点位数

	// 函数 ResetChannelCalculatedDensity
	// 作用：更新或清除ResetChannelCalculatedDensity。
	// 参数：iChanIndex：整数。
	// 返回：返回是或否。
	BOOL ResetChannelCalculatedDensity(int iChanIndex);	//重置通道反算的浓度值，设置为-1

	// 函数 Reset
	// 作用：更新或清除Reset。
	// 参数：bTemplateMode：是或否。
	// 返回：没有返回值。
	virtual void Reset(BOOL bTemplateMode);

	// 函数 ResetInfo1
	// 作用：更新或清除ResetInfo1。
	// 参数：bTemplateMode：是或否。
	// 返回：没有返回值。
	void ResetInfo1(BOOL bTemplateMode);	//重置孔板编辑-通道编辑页面可编辑的样本信息
	// 函数 ResetInfo2
	// 作用：更新或清除ResetInfo2。
	// 参数：bTemplateMode：是或否。
	// 返回：没有返回值。
	void ResetInfo2(BOOL bTemplateMode);	//重置样本登记页面可编辑的样本信息

	// 函数 GetChannelNum
	// 作用：读取GetChannelNum。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetChannelNum();
	
	// 函数 IsAllSelectedChannelPositive
	// 作用：判断IsAllSelectedChannelPositive是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsAllSelectedChannelPositive();	//判断所有选中的通道是否都是阳性（正常起峰）
	// 函数 IsAllSelectedChannelNegative
	// 作用：判断IsAllSelectedChannelNegative是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsAllSelectedChannelNegative();	//判断所有选中的通道是否都是阴性（未起峰）

	// 函数 GetSampleTotalResultIfIncludeIC
	// 作用：读取GetSampleTotalResultIfIncludeIC。
	// 参数：无。
	// 返回：返回 ESAMPLETOTALRESULT。
	ESAMPLETOTALRESULT GetSampleTotalResultIfIncludeIC();	//如果样本孔位包含IC基因，返回该样本多通道组合判定结果

	// 函数 IsExistInternalControl
	// 作用：判断IsExistInternalControl是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetCycleOfMaxMOTRatio。
	BOOL IsExistInternalControl();	//判断管内是否存在内标基因
	// 函数 IsExistInternalControl
	// 作用：判断IsExistInternalControl是否成立。
	// 参数：bICPositive：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetCycleOfMaxMOTRatio。
	BOOL IsExistInternalControl(BOOL& bICPositive);

	// 函数 IsExistPositiveExceptICGene
	// 作用：判断IsExistPositiveExceptICGene是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetCycleOfMaxMOTRatio。
	BOOL IsExistPositiveExceptICGene();	//判断除了内标基因，是否包含其它阳性基因

	// 函数 IsInternalControl
	// 作用：判断IsInternalControl是否成立。
	// 参数：str：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetCycleOfMaxMOTRatio。
	static BOOL IsInternalControl(CString& str);	//判断是否是内标基因
	// 函数 IsInternalControlSPC
	// 作用：判断IsInternalControlSPC是否成立。
	// 参数：strSPC：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetCycleOfMaxMOTRatio。
	static BOOL IsInternalControlSPC(CString strSPC);

	// 函数 SetCycleOfMaxMOTRatio
	// 作用：设置SetCycleOfMaxMOTRatio。
	// 参数：iCycle：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCycleOfMaxMOTRatio(int iCycle) { m_iCycleOfMaxMOTRatio = iCycle; }
	// 函数 GetCycleOfMaxMOTRatio
	// 作用：读取GetCycleOfMaxMOTRatio。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCycleOfMaxMOTRatio() { return m_iCycleOfMaxMOTRatio; }

protected:
	int			m_iTubeID; // 管序号，从1开始，与按行或按列排列有关  
	CString		m_strTubeLabel; // 孔位标志，如A1,B1
	CString		m_strTubeFlag; // 管名，与Target相对应，单人份所含试管数
	CString		m_strSampleID;  // 样本ID
	CString		m_strSampleName; // 样本名称
	COLORREF	m_clrSample; // 样本颜色

	eSampleType m_nSampleType; // 样本类型
	BOOL		m_bRepeatTube; // 是否为复管
	int			m_iRepeatNo; // 复管编号
	CString		m_strComments; // 注释

	CPtrArray	m_arrayDyeTarget; // 类CDyeTargetInfo 指针，染料通道、浓度、计算结果Ct、Tm等

	// 传递校准通道，不需要保存
	int		m_iCalibrateChannel;

	int		m_iCycleOfMaxMOTRatio; // 浊度调整时最大下降比率时的循环数，方便调整荧光数据，-1表示没有找到
};















