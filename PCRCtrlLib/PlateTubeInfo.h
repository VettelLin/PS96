// 【交接】 PCRCtrlLib\PlateTubeInfo.h
// 作用：PlateTubeInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CPlateTubeInfo、OpenFile、WriteFile、ReadFile、SetMeltTmCount、SetPlateInfo、InitDyeTargetInfo、SetTubeInfo。
#pragma once

#include  "TubeInfo.h"
#include <vector>

using namespace std;

const WORD wFileMarkPCRPlate = 0x6363;   // PCR孔板数据文件标识
const WORD wPCRPlateVersion100 =  0x0100;    // PCR孔板数据文件版本

class AFX_EXT_CLASS CPlateTubeInfo
{
public:
	// 函数 CPlateTubeInfo
	// 作用：执行CPlateTubeInfo。
	// 参数：无。
	// 返回：没有返回值。
	CPlateTubeInfo(void);
	// 函数 ~CPlateTubeInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPlateTubeInfo(void);

// Operations
public:
	// 函数 OpenFile
	// 作用：读入OpenFile。
	// 参数：strFilePath：字符串。
	// 返回：返回是或否。
	BOOL OpenFile(CString strFilePath);

	// 函数 WriteFile
	// 作用：把WriteFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL WriteFile(CFile* pFile,WORD wVersion);
	// 函数 ReadFile
	// 作用：读取ReadFile。
	// 参数：pFile：指针，指向调用方传入的对象；wVersion。
	// 返回：返回是或否。
	BOOL ReadFile(CFile* pFile,WORD wVersion);

	// 函数 SetMeltTmCount
	// 作用：设置SetMeltTmCount。
	// 参数：nCount：整数。
	// 返回：没有返回值。
	void SetMeltTmCount(int nCount);
	// 函数 SetPlateInfo
	// 作用：设置SetPlateInfo。
	// 参数：pInputPara：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void SetPlateInfo(tagPlateModeInfo* pInputPara);
	// 函数 InitDyeTargetInfo
	// 作用：初始化InitDyeTargetInfo。
	// 参数：iTubeID：整数；pReagentItem：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void InitDyeTargetInfo(int iTubeID, CReagentItem* pReagentItem);

	// 函数 SetTubeInfo
	// 作用：设置SetTubeInfo。
	// 参数：vecTubeInfo。
	// 返回：没有返回值。
	void SetTubeInfo(vector<CTubeInfo>& vecTubeInfo);
	// 函数 SetTubeInfo
	// 作用：设置SetTubeInfo。
	// 参数：vecPTubeInfo。
	// 返回：没有返回值。
	void SetTubeInfo(vector<CTubeInfo*>& vecPTubeInfo);
	// 函数 SetTubeInfo
	// 作用：设置SetTubeInfo。
	// 参数：pTotalTubeInfo：指针，指向调用方传入的对象；iTubeNum：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int SetTubeInfo(CTubeInfo* pTotalTubeInfo,int iTubeNum);

	// 函数 GetTubeInfo
	// 作用：读取GetTubeInfo。
	// 参数：vecTubeInfo。
	// 返回：没有返回值。
	void GetTubeInfo(vector<CTubeInfo>& vecTubeInfo);

	// 函数 GetUsedDyeChannel
	// 作用：读取GetUsedDyeChannel。
	// 参数：pArrayDye：指针，指向调用方传入的对象；pArrayChannel：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void GetUsedDyeChannel(CStringArray* pArrayDye, CIntArray* pArrayChannel);
	// 函数 GetUsedTarget
	// 作用：读取GetUsedTarget。
	// 参数：pArrrayTarget：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void GetUsedTarget(CPtrArray* pArrrayTarget);

	// 孔板列标行号标签
	// 函数 GetTubeRowAndColLabel
	// 作用：读取GetTubeRowAndColLabel。
	// 参数：pArrayRow：指针，指向调用方传入的对象；pArrayCol：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void GetTubeRowAndColLabel(CStringArray* pArrayRow, CStringArray* pArrayCol);

	// 函数 HasTargetUsed
	// 作用：判断HasTargetUsed是否成立。
	// 参数：strTarget：字符串；strDye：字符串。
	// 返回：返回是或否。
	BOOL HasTargetUsed(CString strTarget, CString strDye);
	// 函数 RecalculateSplineThreshold
	// 作用：执行RecalculateSplineThreshold。
	// 参数：无。
	// 返回：没有返回值。
	void RecalculateSplineThreshold();

protected:
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：bOnlyTube：是或否。
	// 返回：没有返回值。
	void DeleteAll(BOOL bOnlyTube=FALSE);
	// 函数 DeleteAllTubes
	// 作用：更新或清除DeleteAllTubes。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteAllTubes();
	// 函数 CalculateTubeCount
	// 作用：计算CalculateTubeCount。
	// 参数：pInputInfo：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetPlateInfo。
	int CalculateTubeCount(tagPlateModeInfo* pInputInfo);
	// 函数 CreateTubeLabel
	// 作用：创建或加入CreateTubeLabel。
	// 参数：iIndex：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetPlateInfo。
	CString CreateTubeLabel(int iIndex);

	// 函数 CreateLetterLabel
	// 作用：创建或加入CreateLetterLabel。
	// 参数：pArray：指针，指向调用方传入的对象；iCount：整数；strIndex：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPlateInfo。
	void CreateLetterLabel(CStringArray* pArray, int iCount, CString strIndex=_T(""));
	// 函数 CreateNumberLabel
	// 作用：创建或加入CreateNumberLabel。
	// 参数：pArray：指针，指向调用方传入的对象；iCount：整数；strIndex：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetPlateInfo。
	void CreateNumberLabel(CStringArray* pArray, int iCount, CString strIndex=_T(""));

// Attributes 
public:
	// 函数 GetPlateInfo
	// 作用：读取GetPlateInfo。
	// 参数：无。
	// 返回：返回指针 tagPlateModeInfo*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	tagPlateModeInfo* GetPlateInfo() { return m_pPlateInfo; }
	// 函数 GetTubeCount
	// 作用：读取GetTubeCount。
	// 参数：m_arrayTube.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetTubeCount() { return m_arrayTube.GetCount(); }
	// 函数 GetTubeInfo
	// 作用：读取GetTubeInfo。
	// 参数：iIndex：整数。
	// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
	CTubeInfo* GetTubeInfo(int iIndex);
	// 函数 GetAllTubeInfoPtr
	// 作用：读取GetAllTubeInfoPtr。
	// 参数：vecPTubeInfo。
	// 返回：没有返回值。
	void GetAllTubeInfoPtr(vector<CTubeInfo*>& vecPTubeInfo);
	// 函数 GetTubeInfoArrayPtr
	// 作用：读取GetTubeInfoArrayPtr。
	// 参数：无。
	// 返回：返回指针 CPtrArray*。指针为空表示没有取到对象。
	CPtrArray* GetTubeInfoArrayPtr();
	// 函数 GetTubeInfoByID
	// 作用：读取GetTubeInfoByID。
	// 参数：iTubeID：整数。
	// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
	CTubeInfo* GetTubeInfoByID(int iTubeID);
	// 函数 GetTubeInfoByLabel
	// 作用：读取GetTubeInfoByLabel。
	// 参数：strLabel：字符串。
	// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
	CTubeInfo* GetTubeInfoByLabel(CString strLabel);

protected:
	tagPlateModeInfo* m_pPlateInfo; // 孔板信息
	CPtrArray	m_arrayTube; // 孔板信息指针数组
};

