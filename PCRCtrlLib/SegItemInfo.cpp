// 【交接】 PCRCtrlLib\SegItemInfo.cpp
// 作用：SegItemInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSegItemInfo、_T、WriteFile、WriteStringToFile、Write、GetSize、ReadFile、Clear。
#include "StdAfx.h"
#include "SegItemInfo.h"
#include "PublicFun.h"

// 函数 CSegItemInfo::CSegItemInfo
// 作用：执行CSegItemInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CSegItemInfo::CSegItemInfo(void)
{
	m_iStepNum = 0;
	m_iSegType = 1;
	m_iCycleNum = 1;
	m_strSegName = _T("程序段");
	m_fMeltRate = 1.0;
	m_nSegType = SEGMENT_NONE;
	m_bSelected = FALSE;
}

// 函数 CSegItemInfo::~CSegItemInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegItemInfo::~CSegItemInfo(void)
{

}

// 函数 CSegItemInfo::CSegItemInfo
// 作用：执行CSegItemInfo。
// 参数：segItemInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSegItemInfo::CSegItemInfo(const CSegItemInfo& segItemInfo)
{
	m_iStepNum = segItemInfo.m_iStepNum;
	m_iSegType = segItemInfo.m_iSegType;
	m_iCycleNum = segItemInfo.m_iCycleNum;
	m_strSegName = segItemInfo.m_strSegName;
	m_lnkStepItemInfo = segItemInfo.m_lnkStepItemInfo;
	m_rcCycleNum = segItemInfo.m_rcCycleNum;
	m_rcSegName = segItemInfo.m_rcSegName;
	m_fMeltRate = segItemInfo.m_fMeltRate;
	m_nSegType = segItemInfo.m_nSegType;
	m_rcSeg = segItemInfo.m_rcSeg;
	m_bSelected = segItemInfo.m_bSelected;
}

void CSegItemInfo::operator=(const CSegItemInfo& segItemInfo)
{
	m_iStepNum = segItemInfo.m_iStepNum;
	m_iSegType = segItemInfo.m_iSegType;
	m_iCycleNum = segItemInfo.m_iCycleNum;
	m_strSegName = segItemInfo.m_strSegName;
	m_lnkStepItemInfo = segItemInfo.m_lnkStepItemInfo;
	m_rcCycleNum = segItemInfo.m_rcCycleNum;
	m_rcSegName = segItemInfo.m_rcSegName;
	m_fMeltRate = segItemInfo.m_fMeltRate;
	m_nSegType = segItemInfo.m_nSegType;
	m_rcSeg = segItemInfo.m_rcSeg;
	m_bSelected = segItemInfo.m_bSelected;
}

// 函数 CSegItemInfo::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 WriteStringToFile、Write、GetSize。
BOOL CSegItemInfo::WriteFile(CFile* pFile)
{
	if(NULL == pFile)
	{
		return FALSE;
	}

	CPublicFun::WriteStringToFile(pFile, m_strSegName);
	pFile->Write((const char *)&m_iSegType, sizeof(int));
	pFile->Write((const char*)&m_iCycleNum, sizeof(int));
	pFile->Write((const char*)&m_fMeltRate, sizeof(float));
	pFile->Write((const char*)&m_nSegType, sizeof(eSegmentType));

	m_iStepNum = m_lnkStepItemInfo.GetSize();
	pFile->Write((const char*)&m_iStepNum, sizeof(int));

	for(int i = 0;i < m_iStepNum;++i)
	{
		m_lnkStepItemInfo[i]->WriteFile(pFile);
	}

	return TRUE;
}

// 函数 CSegItemInfo::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 Clear、ReadStringFromFile、Read、AddTail、GetTail。
BOOL CSegItemInfo::ReadFile(CFile* pFile, WORD wVersion)
{
	if(NULL == pFile)
	{
		return FALSE;
	}

	m_lnkStepItemInfo.Clear();

	m_strSegName = CPublicFun::ReadStringFromFile(pFile);
	pFile->Read((char*)&m_iSegType, sizeof(int));
	pFile->Read((char*)&m_iCycleNum, sizeof(int));
	pFile->Read((char*)&m_fMeltRate, sizeof(float));
	pFile->Read((char*)&m_nSegType, sizeof(eSegmentType));
	pFile->Read((char*)&m_iStepNum, sizeof(int));

	CStepItemInfo stepItem;
	for(int i = 0;i < m_iStepNum;++i)
	{
		m_lnkStepItemInfo.AddTail(stepItem);
		m_lnkStepItemInfo.GetTail()->data.ReadFile(pFile,wVersion);
	}

	return TRUE;
}

// 函数 CSegItemInfo::GetSegWidth
// 作用：读取GetSegWidth。
// 参数：stepId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHead、GetSize。
int CSegItemInfo::GetSegWidth(int stepId /*= -2*/)
{
	if((stepId < 0 && -2 != stepId) || -1 == stepId)
	{
		return 0;
	}

	int segWidth = 0;
	Node<CStepItemInfo>* pNode = m_lnkStepItemInfo.GetHead();
	int index = 0;
	int stepNum = stepId;
	if(-2 == stepId)
	{
		stepNum = m_lnkStepItemInfo.GetSize();
	}
	while(NULL != pNode && index++ <= stepNum)
	{
		segWidth += pNode->data.m_stepW;
		pNode = pNode->pNext;
	}
	
	return segWidth;
}

// 函数 CSegItemInfo::GetBeMeltSeg
// 作用：读取GetBeMeltSeg。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetHead。
BOOL CSegItemInfo::GetBeMeltSeg()
{
	Node<CStepItemInfo>* pNode = m_lnkStepItemInfo.GetHead();
	while(NULL != pNode)
	{
		if(3 == pNode->data.m_eChkType)
		{
			m_fMeltRate = pNode->data.m_fRate;
			return TRUE;
		}
		pNode = pNode->pNext;
	}
	return FALSE;
}

// 函数 CSegItemInfo::GetMeltIncrement
// 作用：读取GetMeltIncrement。
// 参数：dMeltIncrement：小数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetHead。
int CSegItemInfo::GetMeltIncrement(double& dMeltIncrement)
{
	Node<CStepItemInfo>* pNode = m_lnkStepItemInfo.GetHead();
	while(NULL != pNode)
	{
		if(3 == pNode->data.m_eChkType)
		{
			dMeltIncrement = pNode->data.m_fIncrement;
			return 0;
		}
		pNode = pNode->pNext;
	}
	return -1;
}

// 函数 CSegItemInfo::GetBeAmlSeg
// 作用：读取GetBeAmlSeg。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetHead。
BOOL CSegItemInfo::GetBeAmlSeg()
{
	Node<CStepItemInfo>* pNode = m_lnkStepItemInfo.GetHead();
	BOOL bHaveAml = FALSE;
	while(NULL != pNode)
	{
		if(3 == pNode->data.m_eChkType)
		{
			return FALSE;
		}
		if(2 == pNode->data.m_eChkType)
		{
			bHaveAml = TRUE;
		}
		pNode = pNode->pNext;
	}
	return bHaveAml;
}

// 函数 CSegItemInfo::GetBeAllStepSelected
// 作用：读取GetBeAllStepSelected。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetHead。
BOOL CSegItemInfo::GetBeAllStepSelected()
{
	Node<CStepItemInfo>* pStepNode = m_lnkStepItemInfo.GetHead();
	while(NULL != pStepNode)
	{
		if(!pStepNode->data.m_bSel)
		{
			return FALSE;
		}
		pStepNode = pStepNode->pNext;
	}
	return TRUE;
}

// 函数 CSegItemInfo::GetBeHaveSelectedStep
// 作用：读取GetBeHaveSelectedStep。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetHead。
BOOL CSegItemInfo::GetBeHaveSelectedStep()
{
	Node<CStepItemInfo>* pStepNode = m_lnkStepItemInfo.GetHead();
	while(NULL != pStepNode)
	{
		if(pStepNode->data.m_bSel)
		{
			return TRUE;
		}
		pStepNode = pStepNode->pNext;
	}
	return FALSE;
}

// 函数 CSegItemInfo::GetFirstStepTemperature
// 作用：读取GetFirstStepTemperature。
// 参数：无。
// 返回：返回一个小数。
// 过程：函数里会调用 GetSize、GetHead。
float CSegItemInfo::GetFirstStepTemperature()
{
	float ret = 4;

	if(m_lnkStepItemInfo.GetSize() > 0)
	{
		ret = m_lnkStepItemInfo.GetHead()->data.m_fAimTem;
	}

	return ret;
}

// 函数 CSegItemInfo::GetLastStepTemperatre
// 作用：读取GetLastStepTemperatre。
// 参数：无。
// 返回：返回一个小数。
// 过程：函数里会调用 GetSize、GetAt。
float CSegItemInfo::GetLastStepTemperatre()
{
	float ret = 4;
	int size = m_lnkStepItemInfo.GetSize();
	if(size > 0)
	{
		ret = m_lnkStepItemInfo.GetAt(size - 1)->data.m_fAimTem;
	}

	return ret;
}

// 函数 CSegItemInfo::GetStepNum
// 作用：读取GetStepNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize。
int CSegItemInfo::GetStepNum()
{
	return m_lnkStepItemInfo.GetSize();
}

// 函数 CSegItemInfo::CorrectNameLanguage
// 作用：执行CorrectNameLanguage。
// 参数：strSource：字符串；strTarget：字符串；strStepSource：字符串；strStepTarget：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 Replace、GetHead。
void CSegItemInfo::CorrectNameLanguage(CString strSource, CString strTarget, CString strStepSource, CString strStepTarget)
{
	m_strSegName.Replace(strSource, strTarget);

	Node<CStepItemInfo>* pStepNode = m_lnkStepItemInfo.GetHead();
	while(NULL != pStepNode)
	{
		pStepNode->data.m_strStepName.Replace(strStepSource, strStepTarget);
		pStepNode = pStepNode->pNext;
	}
}

// 函数 CSegItemInfo::CorrectIndex
// 作用：执行CorrectIndex。
// 参数：iIndex：整数。
// 返回：没有返回值。
// 过程：函数里会调用 Format、_T、Find。
void CSegItemInfo::CorrectIndex(int iIndex)
{
	CString strIndex;
	strIndex.Format(_T("%d"), iIndex);

	if (m_strSegName.Find(strIndex) == -1)
	{
		m_strSegName += _T(" ") + strIndex;
	}
}

// 函数 CSegItemInfo::CalculateTotalSeconds
// 作用：计算CalculateTotalSeconds。
// 参数：无。
// 返回：返回 long。
// 过程：函数里会调用 GetHead。
long CSegItemInfo::CalculateTotalSeconds()
{
	long iTime = 0;
	Node<CStepItemInfo>* pStepNode = m_lnkStepItemInfo.GetHead();
	while(NULL != pStepNode)
	{
		iTime += pStepNode->data.m_iDelay;
		pStepNode = pStepNode->pNext;
	}

	return iTime;
}
