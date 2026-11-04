// 【交接】 PCRCtrlLib\ReagentItem.h
// 作用：ReagentItem。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CItemChannelInfo、WriteFile、ReadFile、CopyFrom、DeleteAll、GetUse、SetUse、GetChannel。
#pragma once

#include "DeclaresPCR.h"
#include <fstream>
#include "SegItemInfo.h"
#include "LinkList.h"
#include "DataAnalysisPara.h"
#include "ConfigureDBInfo.h"


using namespace std;

// 通道染料目标设置
class AFX_EXT_CLASS CItemChannelInfo
{
public:
	// 函数 CItemChannelInfo
	// 作用：执行CItemChannelInfo。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CItemChannelInfo(void);
	// 函数 ~CItemChannelInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CItemChannelInfo(void);

	struct tagItemTargetInfo
	{
		CString strTubeFlag; // 管标记
		CString strTarget; // 指标名称
		COLORREF clrTarget; //  颜色
	};

public:
	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteFile(CFile* pFile);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	BOOL ReadFile(CFile* pFile, WORD wVersion,BOOL bProject);

	// 函数 CopyFrom
	// 作用：复制CopyFrom。
	// 参数：pInputInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetUse。
	void CopyFrom(CItemChannelInfo* pInputInfo);

protected:
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetUse。
	void DeleteAll();

// Attributes
public:
	// 函数 GetUse
	// 作用：读取GetUse。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetUse() { return m_bUse; }
	// 函数 SetUse
	// 作用：设置SetUse。
	// 参数：bUse：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetUse(BOOL bUse) { m_bUse = bUse; }
	// 函数 GetChannel
	// 作用：读取GetChannel。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetChannel() { return m_nChannel; }
	// 函数 SetChannel
	// 作用：设置SetChannel。
	// 参数：nChannel：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetChannel(int nChannel) { m_nChannel = nChannel; }
	// 函数 GetDyeName
	// 作用：读取GetDyeName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetDyeName() { return m_strDye; }
	// 函数 SetDyeName
	// 作用：设置SetDyeName。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetDyeName(CString string) { m_strDye = string; }
	// 函数 GetExWavelength
	// 作用：读取GetExWavelength。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetExWavelength() { return m_nExWavelength; }
	// 函数 SetExWavelength
	// 作用：设置SetExWavelength。
	// 参数：iLength：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetExWavelength(int iLength) { m_nExWavelength = iLength; }
	// 函数 GetEmWavelength
	// 作用：读取GetEmWavelength。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetEmWavelength() { return m_nEmWavelength; }
	// 函数 SetEmWavelength
	// 作用：设置SetEmWavelength。
	// 参数：iLength：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetEmWavelength(int iLength) { m_nEmWavelength = iLength; }

	// 函数 AddTarget
	// 作用：创建或加入AddTarget。
	// 参数：strTubeFlag：字符串；strName：字符串；color：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTargetCount、GetCount。
	void AddTarget(CString strTubeFlag, CString strName, COLORREF color);
	// 函数 AddTarget
	// 作用：创建或加入AddTarget。
	// 参数：strTargetName：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTargetCount、GetCount。
	void AddTarget(CString strTargetName);
	// 函数 GetTargetCount
	// 作用：读取GetTargetCount。
	// 参数：m_arrayTarget.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetTargetCount() { return m_arrayTarget.GetCount(); }
	// 函数 GetTubeFlag
	// 作用：读取GetTubeFlag。
	// 参数：iIndex：整数。
	// 返回：返回一段文字。
	CString GetTubeFlag(int iIndex);
	// 函数 SetTubeFlag
	// 作用：设置SetTubeFlag。
	// 参数：iIndex：整数；strFlag：字符串。
	// 返回：没有返回值。
	void SetTubeFlag(int iIndex, CString strFlag);
	// 函数 GetTargetName
	// 作用：读取GetTargetName。
	// 参数：iIndex：整数。
	// 返回：返回一段文字。
	CString GetTargetName(int iIndex);
	// 函数 GetTargetName
	// 作用：读取GetTargetName。
	// 参数：strTubeFlag：字符串。
	// 返回：返回一段文字。
	CString GetTargetName(CString strTubeFlag);
	// 函数 SetTargetName
	// 作用：设置SetTargetName。
	// 参数：iIndex：整数；string：字符串。
	// 返回：没有返回值。
	void SetTargetName(int iIndex, CString string);
	// 函数 GetTargetColor
	// 作用：读取GetTargetColor。
	// 参数：iIndex：整数。
	// 返回：返回 COLORREF。
	COLORREF GetTargetColor(int iIndex);
	// 函数 GetTargetColor
	// 作用：读取GetTargetColor。
	// 参数：strTubeFlag：字符串。
	// 返回：返回 COLORREF。
	COLORREF GetTargetColor(CString strTubeFlag);
	// 函数 SetTargetColor
	// 作用：设置SetTargetColor。
	// 参数：iIndex：整数；color：颜色。
	// 返回：没有返回值。
	void SetTargetColor(int iIndex, COLORREF color);

	//double GetNegPosUpLimit();
	//double GetNegPosDownLimit();
	//void SetNegPosUpLimit(double dValue);
	//void SetNegPosDownLimit(double dValue);

protected:
	BOOL m_bUse; // 通道是否使用
	int	 m_nChannel; // 通道
	CString m_strDye; // 染料名称
	int m_nExWavelength; // 激发波长
	int m_nEmWavelength; // 发射波长
	CPtrArray m_arrayTarget; // 指标和对应的颜色，tagItemTargetInfo
	
	double m_dNegPosUpLimit;	//阴阳性判定阈值上限，20220609，孙文郎，临时使用(需要永远保存在文件中，即使后续不再使用该参数)，最终要使用用户自定义的判定规则
	double m_dNegPosDownLimit;	//阴阳性判定阈值下限，20220609，孙文郎，临时使用(需要永远保存在文件中，即使后续不再使用该参数)，最终要使用用户自定义的判定规则
};

// 试剂检测项目
class AFX_EXT_CLASS CReagentItem
{
public:
	// 函数 CReagentItem
	// 作用：执行CReagentItem。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CReagentItem(void);
	// 函数 ~CReagentItem
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CReagentItem(void);

	// 相同样本的试管排列方式
	enum eTubeSortMode
	{
		SORT_MODE_VERT = 0, // 竖排
		SORT_MODE_HORI, // 横排
	};

	enum eSaveStatus
	{
		STATUS_NEW = 0, // 新建
		STATUS_SAVE, // 保存
		STATUS_CHANGE, // 修改
		STATUS_USING, // 正在使用
	};

public:
	// 函数 SaveFile
	// 作用：把SaveFile写入文件、仪器或界面。
	// 参数：strFileName：字符串。
	// 返回：返回是或否。
	BOOL SaveFile(CString strFileName);
	// 函数 OpenFile
	// 作用：读入OpenFile。
	// 参数：strFileName：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetPreStepDelay。
	BOOL OpenFile(CString strFileName);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetPreStepDelay。
	BOOL WriteFile(CFile* pFile,WORD wVersion,BOOL bProject);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetPreStepDelay。
	BOOL ReadFile(CFile* pFile, WORD wVersion,BOOL bProject);

	// 函数 CopyFrom
	// 作用：复制CopyFrom。
	// 参数：pInputItem：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPreStepDelay。
	void CopyFrom(CReagentItem* pInputItem);
	// 函数 CopyChanTargetInfo
	// 作用：复制CopyChanTargetInfo。
	// 参数：pInputItem：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPreStepDelay。
	void CopyChanTargetInfo(CReagentItem* pInputItem);

	// 函数 GetPreStepDelay
	// 作用：读取GetPreStepDelay。
	// 参数：iCurSegment：整数；iCurStep：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetPreStepDelay(int iCurSegment, int iCurStep) { return 60; } // 取得指定程序段和步骤的前面一步的等待时间

	// 函数 InitChannelInfo
	// 作用：初始化InitChannelInfo。
	// 参数：pListDye：指针，指向调用方传入的对象；pArrayChannel：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void InitChannelInfo(CDyeInfoList* pListDye, CPtrArray* pArrayChannel); // 初始化可用光路
	// 函数 InitReagentItem
	// 作用：初始化InitReagentItem。
	// 参数：pListDye：指针，指向调用方传入的对象；pArrayChannel：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void InitReagentItem(CDyeInfoList* pListDye, CPtrArray* pArrayChannel);

	// 函数 IsLegal
	// 作用：判断IsLegal是否成立。
	// 参数：iOutTip：整数。
	// 返回：返回是或否。
	BOOL IsLegal(int &iOutTip); // 判断编辑是否合法

	// 函数 GetBeEditable
	// 作用：读取GetBeEditable。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeEditable();	//获取“项目信息是否可编辑”

	// 函数 GetLnkDyeName
	// 作用：读取GetLnkDyeName。
	// 参数：无。
	// 返回：返回 CLinkList<CString>&。
	CLinkList<CString>& GetLnkDyeName();	//获取所有的通道（染料）名称
	// 函数 DyeNameChanged
	// 作用：执行DyeNameChanged。
	// 参数：iChanId：整数；strDye：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DyeNameChanged(int iChanId,CString strDye);	//项目的某个通道染料名称改变了

protected:
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	virtual void DeleteAll();
	// 函数 DeleteAllChannelTarget
	// 作用：更新或清除DeleteAllChannelTarget。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteAllChannelTarget();

	// 函数 WriteBasicInfo
	// 作用：把WriteBasicInfo写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL WriteBasicInfo(CFile* pFile);
	// 函数 WriteChannelTarget
	// 作用：把WriteChannelTarget写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetName。
	BOOL WriteChannelTarget(CFile* pFile,WORD wVersion,BOOL bProject);
	// 函数 WriteSegment
	// 作用：把WriteSegment写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetName。
	BOOL WriteSegment(CFile* pFile);

	// 函数 ReadBasicInfo
	// 作用：读取ReadBasicInfo。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetName。
	BOOL ReadBasicInfo(CFile* pFile, WORD wVersion);
	// 函数 ReadChannelTarget
	// 作用：读取ReadChannelTarget。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion；bProject：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetName。
	BOOL ReadChannelTarget(CFile* pFile, WORD wVersion,BOOL bProject);
	// 函数 ReadSegment
	// 作用：读取ReadSegment。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetName。
	BOOL ReadSegment(CFile* pFile, WORD wVersion);

public:
	// 函数 GetName
	// 作用：读取GetName。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetName() { return m_strName; }
	// 函数 SetName
	// 作用：设置SetName。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetName(CString string) { m_strName = string; }
	// 函数 GetType
	// 作用：读取GetType。
	// 参数：无。
	// 返回：返回 eExperimentType。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eExperimentType GetType() { return m_nType; }
	// 函数 SetType
	// 作用：设置SetType。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetType(eExperimentType nType) { m_nType = nType; }
	// 函数 GetBarcode
	// 作用：读取GetBarcode。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetBarcode() { return m_strBarcode; }
	// 函数 SetBarcode
	// 作用：设置SetBarcode。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBarcode(CString string) { m_strBarcode = string; }
	// 函数 GetReagent
	// 作用：读取GetReagent。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetReagent() { return m_strReagent; }
	// 函数 SetReagent
	// 作用：设置SetReagent。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetReagent(CString string) { m_strReagent = string; }

	// 函数 GetReactVolume
	// 作用：读取GetReactVolume。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetReactVolume() { return m_iReactVolume; }
	// 函数 SetReactVolume
	// 作用：设置SetReactVolume。
	// 参数：nVolume：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetReactVolume(int nVolume) { m_iReactVolume = nVolume; }
	// 函数 GetUnit
	// 作用：读取GetUnit。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetUnit() { return m_strUnit; }
	// 函数 SetUnit
	// 作用：设置SetUnit。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetUnit(CString string) { m_strUnit = string; }
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
	// 函数 GetUser
	// 作用：读取GetUser。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetUser() { return m_strUser; }
	// 函数 SetUser
	// 作用：设置SetUser。
	// 参数：string：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetUser(CString string) { m_strUser = string; }
	// 函数 GetDate
	// 作用：读取GetDate。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetDate() { return m_strDate; }

	// 函数 GetTubeNumPerSample
	// 作用：读取GetTubeNumPerSample。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetTubeNumPerSample() { return m_iTubeNumPerSample; }
	// 函数 SetTubeNumPerSample
	// 作用：设置SetTubeNumPerSample。
	// 参数：nCount：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTubeNumPerSample(int nCount) { m_iTubeNumPerSample = nCount; }
	// 函数 GetTubeSortMode
	// 作用：读取GetTubeSortMode。
	// 参数：无。
	// 返回：返回 eTubeSortMode。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eTubeSortMode GetTubeSortMode() { return m_nSortMode; }
	// 函数 SetTubeSortMode
	// 作用：设置SetTubeSortMode。
	// 参数：nMode：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTubeSortMode(eTubeSortMode nMode) { m_nSortMode = nMode; }

	// 通道染料目标
	// 函数 GetChannelTargetCount
	// 作用：读取GetChannelTargetCount。
	// 参数：m_arrayTarget.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetChannelTargetCount() { return m_arrayTarget.GetCount(); }
	// 函数 AddChannelTarget
	// 作用：创建或加入AddChannelTarget。
	// 参数：m_arrayTarget.Add(pChannel。
	// 返回：没有返回值。
	// 过程：函数里会调用 Add。
	void AddChannelTarget(CItemChannelInfo* pChannel) { m_arrayTarget.Add(pChannel); } // 增加一种指标参数，需要先申请指针
	// 函数 GetChannelTargetBy
	// 作用：读取GetChannelTargetBy。
	// 参数：nIndex：整数。
	// 返回：返回指针 CItemChannelInfo*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetSelChannelCount。
	CItemChannelInfo* GetChannelTargetBy(int nIndex); 
	// 函数 SetChannelTargetAt
	// 作用：设置SetChannelTargetAt。
	// 参数：nIndex：整数；pChannel：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetSelChannelCount。
	void SetChannelTargetAt(int nIndex, CItemChannelInfo* pChannel); // 修改参数，不需要申请指针
	// 函数 GetChannelTargetBy
	// 作用：读取GetChannelTargetBy。
	// 参数：strName：字符串。
	// 返回：返回指针 CItemChannelInfo*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetSelChannelCount。
	CItemChannelInfo* GetChannelTargetBy(CString strName); 


	// 交叉干扰相关函数
	// 函数 GetSelChannelCount
	// 作用：读取GetSelChannelCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetSelChannelCount() { return m_nSelChanCount; }
	// 函数 SetSelChannelCount
	// 作用：设置SetSelChannelCount。
	// 参数：nCount：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCrosstalkPara。
	void SetSelChannelCount(int nCount);
	// 函数 GetCrosstalkPara
	// 作用：读取GetCrosstalkPara。
	// 参数：无。
	// 返回：返回指针 double*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	double* GetCrosstalkPara() { return m_pCrosstalkPara; }
	// 函数 GetUsedChannel
	// 作用：读取GetUsedChannel。
	// 参数：pArrayChanel：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetSegementCount、GetSize。
	void GetUsedChannel(CIntArray* pArrayChanel);

	// 实验流程相关参数
	// 函数 GetSegementCount
	// 作用：读取GetSegementCount。
	// 参数：m_lnkSegment.GetSize(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetSize。
	int GetSegementCount() { return m_lnkSegment.GetSize(); }
	// 函数 AddSegment
	// 作用：创建或加入AddSegment。
	// 参数：m_lnkSegment.AddTail(segItem。
	// 返回：没有返回值。
	// 过程：函数里会调用 AddTail。
	void AddSegment(CSegItemInfo segItem) { m_lnkSegment.AddTail(segItem); } // 增加一种指标参数，需要先申请指针
	// 函数 GetSegmentBy
	// 作用：读取GetSegmentBy。
	// 参数：nIndex：整数。
	// 返回：返回 CSegItemInfo。
	// 过程：函数里会调用 GetSegment。
	CSegItemInfo GetSegmentBy(int nIndex); 
	// 函数 SetSegment
	// 作用：设置SetSegment。
	// 参数：lnkSegItem。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetSegment。
	void SetSegment(CLinkList<CSegItemInfo>& lnkSegItem);
	// 函数 SetSegmentAt
	// 作用：设置SetSegmentAt。
	// 参数：nIndex：整数；segItem。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetSegment。
	void SetSegmentAt(int nIndex, CSegItemInfo segItem); // 修改参数，不需要申请指针
	// 函数 DeleteSegmentAt
	// 作用：更新或清除DeleteSegmentAt。
	// 参数：nIndex：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetSegment。
	void DeleteSegmentAt(int nIndex);
	// 函数 DeleteAllSegement
	// 作用：更新或清除DeleteAllSegement。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetSegment。
	void DeleteAllSegement();
	// 函数 GetSegment
	// 作用：读取GetSegment。
	// 参数：无。
	// 返回：返回 CLinkList<CSegItemInfo>&。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CLinkList<CSegItemInfo>& GetSegment() { return m_lnkSegment; }
	// 函数 SetSegmentInfo
	// 作用：设置SetSegmentInfo。
	// 参数：lnkSegItemInfo。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSegmentInfo(CLinkList<CSegItemInfo>& lnkSegItemInfo) { m_lnkSegment = lnkSegItemInfo; }

	// 函数 GetAnalysisPara
	// 作用：读取GetAnalysisPara。
	// 参数：无。
	// 返回：返回指针 CDataAnalysisPara*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CDataAnalysisPara* GetAnalysisPara() { return m_pAnalysisPara; }

	// 函数 GetStatus
	// 作用：读取GetStatus。
	// 参数：无。
	// 返回：返回 eSaveStatus。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eSaveStatus GetStatus() { return m_nStatus; }
	// 函数 SetStatus
	// 作用：设置SetStatus。
	// 参数：nStatus：整数。
	// 返回：没有返回值。
	void SetStatus(eSaveStatus nStatus);

protected:
	CString		m_strName; // 项目名称
	eExperimentType	m_nType; // 项目类型
	CString		m_strBarcode; // 试剂条码
	CString		m_strReagent; // Chemistry/试剂
	int			m_iReactVolume; // 反应体系
	CString		m_strUnit; // 单位
	CString		m_strComments; // 注释
	CString		m_strUser; // 用户
	CString		m_strDate; // 编辑时间

	// 检测目标
	int				m_iTubeNumPerSample; // 每个样本所含试管数
	eTubeSortMode	m_nSortMode;  // 试管排列方式
	CPtrArray		m_arrayTarget; // 通道染料目标信息, CItemChannelInfo

	int			m_nSelChanCount; // 选择使用的通道数
	double*		m_pCrosstalkPara; // 通道交叉干扰参数
	CLinkList<CString> m_lnkDyeName;	//记录所有的通道（染料）名称

	CLinkList<CSegItemInfo> m_lnkSegment;	//实验步骤信息

	CDataAnalysisPara* m_pAnalysisPara; // 分析参数

	eSaveStatus 	m_nStatus; // 项目文件状态
};



