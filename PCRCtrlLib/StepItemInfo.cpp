// 【交接】 PCRCtrlLib\StepItemInfo.cpp
// 作用：StepItemInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CStepItemInfo、_T、GetStepGradientInfo、powf、GetBeCollectAll、GetBeCollect、GetBeNoneCollect、SetCollectAll。
#include "StdAfx.h"
#include "StepItemInfo.h"
#include "PublicFun.h"

// 函数 CStepItemInfo::CStepItemInfo
// 作用：执行CStepItemInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CStepItemInfo::CStepItemInfo(void)
{
	m_bSel = FALSE;
	m_bSelGrad = FALSE;
	m_fAimTem = 50;   
	m_fGradUpTem = 50;
	m_iDelay = 5;
	m_fRate = 4; 
	m_eChkType = CHECK_NONE;
	m_fIncrement = 0.5;
	m_uiHoldTimeSec = 6;
	m_fRangeBelowStartTem = 1; 
	m_uiWaitTimeBelowStartTem = 60; 
	m_stepW = 160;
	m_strStepName = _T("");
}

// 函数 CStepItemInfo::~CStepItemInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStepItemInfo::~CStepItemInfo(void)
{

}

// 函数 CStepItemInfo::CStepItemInfo
// 作用：执行CStepItemInfo。
// 参数：stepItemInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStepItemInfo::CStepItemInfo(const CStepItemInfo& stepItemInfo)
{
	m_bSel = stepItemInfo.m_bSel;
	m_bSelGrad = stepItemInfo.m_bSelGrad;
	m_fAimTem = stepItemInfo.m_fAimTem;   
	m_fGradUpTem = stepItemInfo.m_fGradUpTem;
	m_iDelay = stepItemInfo.m_iDelay;
	m_fRate = stepItemInfo.m_fRate; 
	m_eChkType = stepItemInfo.m_eChkType;
	m_fIncrement = stepItemInfo.m_fIncrement;
	m_uiHoldTimeSec = stepItemInfo.m_uiHoldTimeSec;
	m_fRangeBelowStartTem = stepItemInfo.m_fRangeBelowStartTem; 
	m_uiWaitTimeBelowStartTem = stepItemInfo.m_uiWaitTimeBelowStartTem; 
	m_rcTem = stepItemInfo.m_rcTem;
	m_rcLine = stepItemInfo.m_rcLine;
	m_rcMinSec = stepItemInfo.m_rcMinSec;
	m_rcCkbtCollectFlu = stepItemInfo.m_rcCkbtCollectFlu;
	m_strStepName = stepItemInfo.m_strStepName;
	m_stepW = stepItemInfo.m_stepW;
}

void CStepItemInfo::operator=(const CStepItemInfo& stepItemInfo)
{
	m_bSel = stepItemInfo.m_bSel;
	m_bSelGrad = stepItemInfo.m_bSelGrad;
	m_fAimTem = stepItemInfo.m_fAimTem;   
	m_fGradUpTem = stepItemInfo.m_fGradUpTem;
	m_iDelay = stepItemInfo.m_iDelay;
	m_fRate = stepItemInfo.m_fRate; 
	m_eChkType = stepItemInfo.m_eChkType;
	m_fIncrement = stepItemInfo.m_fIncrement;
	m_uiHoldTimeSec = stepItemInfo.m_uiHoldTimeSec;
	m_fRangeBelowStartTem = stepItemInfo.m_fRangeBelowStartTem; 
	m_uiWaitTimeBelowStartTem = stepItemInfo.m_uiWaitTimeBelowStartTem;
	m_rcTem = stepItemInfo.m_rcTem;
	m_rcLine = stepItemInfo.m_rcLine;
	m_rcMinSec = stepItemInfo.m_rcMinSec;
	m_rcCkbtCollectFlu = stepItemInfo.m_rcCkbtCollectFlu;
	m_strStepName = stepItemInfo.m_strStepName;
	m_stepW = stepItemInfo.m_stepW;
}

//获取梯度信息,计算各列温度分布
// 函数 CStepItemInfo::GetStepGradientInfo
// 作用：读取GetStepGradientInfo。
// 参数：ColTemp；DeltaT；fbackcali_AimT；fbackcali_DeltaT。
// 返回：没有返回值。
// 过程：函数里会调用 powf。
void CStepItemInfo::GetStepGradientInfo(float *ColTemp,float &DeltaT,float &fbackcali_AimT,float &fbackcali_DeltaT)
{
	//四参数系数,反算ColTemp
	float a = 0,b = 0,c = 0,d = 0;
	float a_k = 1.5503;
	float a_b = 0.226;
	float d_k = -0.1143;
	float d_b = -0.308;
	DeltaT = m_fGradUpTem - m_fAimTem;
	a = a_k * DeltaT + m_fAimTem + a_b;
	b = -2.34;
	c = 8;
	d = d_k * DeltaT + m_fAimTem + d_b;

	//根据m_fAimT、m_fUpT反算a、d系数
	float C1 = 1 + powf((1 / c),b);
	float C2 = 1 + powf((12 / c),b);
	float d_backcali = (m_fAimTem * C1 - m_fGradUpTem * C2) / (C1 - C2);
	float a_backcali = (m_fAimTem - d_backcali) * C1 + d_backcali;

	//计算每列的温度值
	for (int iCol = 1;iCol <= 12;++iCol)
	{
		ColTemp[iCol - 1] = (a_backcali - d_backcali) / (1 + powf(iCol / c,b)) + d_backcali;
	}

	//计算实际下发给仪器的3路温度值
	fbackcali_DeltaT = ((a_backcali - d_backcali) - (a_b - d_b)) / (a_k - d_k);
	fbackcali_AimT = d_backcali - d_k * fbackcali_DeltaT - d_b;

	return;
}

// 函数 CStepItemInfo::GetBeCollectAll
// 作用：读取GetBeCollectAll。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CStepItemInfo::GetBeCollectAll()
{
	return CHECK_ALL_POINT == m_eChkType;
}

// 函数 CStepItemInfo::GetBeCollect
// 作用：读取GetBeCollect。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CStepItemInfo::GetBeCollect()
{
	return CHECK_END_POINT == m_eChkType;
}

// 函数 CStepItemInfo::GetBeNoneCollect
// 作用：读取GetBeNoneCollect。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CStepItemInfo::GetBeNoneCollect()
{
	return CHECK_NONE == m_eChkType;
}

// 函数 CStepItemInfo::SetCollectAll
// 作用：设置SetCollectAll。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStepItemInfo::SetCollectAll()
{
	m_eChkType = CHECK_ALL_POINT;
}

// 函数 CStepItemInfo::SetCollect
// 作用：设置SetCollect。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStepItemInfo::SetCollect()
{
	m_eChkType = CHECK_END_POINT;
}

// 函数 CStepItemInfo::SetNoneCollect
// 作用：设置SetNoneCollect。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CStepItemInfo::SetNoneCollect()
{
	m_eChkType = CHECK_NONE;
}

// 函数 CStepItemInfo::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 WriteStringToFile、Write。
BOOL CStepItemInfo::WriteFile(CFile* pFile)
{
	if(NULL == pFile)
	{
		return FALSE;
	}

	CPublicFun::WriteStringToFile(pFile,m_strStepName);
	pFile->Write((const char *)&m_bSel, sizeof(BOOL));
	pFile->Write((const char *)&m_bSelGrad, sizeof(BOOL));

	pFile->Write((const char *)&m_fAimTem, sizeof(float));
	pFile->Write((const char *)&m_fGradUpTem, sizeof(float));
	pFile->Write((const char *)&m_fRate, sizeof(float));
	pFile->Write((const char *)&m_fIncrement, sizeof(float));
	pFile->Write((const char *)&m_fRangeBelowStartTem, sizeof(float));

	pFile->Write((const char *)&m_iDelay, sizeof(int));
	pFile->Write((const char *)&m_stepW, sizeof(int));

	pFile->Write((const char *)&m_uiHoldTimeSec, sizeof(unsigned int));
	pFile->Write((const char *)&m_uiWaitTimeBelowStartTem, sizeof(unsigned int));

	pFile->Write((const char *)&m_eChkType, sizeof(eStepCheckType));

	return TRUE;
}

// 函数 CStepItemInfo::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 ReadStringFromFile、Read。
BOOL CStepItemInfo::ReadFile(CFile* pFile, WORD wVersion)
{
	if(NULL == pFile)
	{
		return FALSE;
	}

	m_strStepName = CPublicFun::ReadStringFromFile(pFile);
	pFile->Read((char*)&m_bSel, sizeof(BOOL));
	pFile->Read((char*)&m_bSelGrad, sizeof(BOOL));

	pFile->Read((char*)&m_fAimTem, sizeof(float));
	pFile->Read((char*)&m_fGradUpTem, sizeof(float));
	pFile->Read((char*)&m_fRate, sizeof(float));
	pFile->Read((char*)&m_fIncrement, sizeof(float));
	pFile->Read((char*)&m_fRangeBelowStartTem, sizeof(float));

	pFile->Read((char*)&m_iDelay, sizeof(int));
	pFile->Read((char*)&m_stepW, sizeof(int));

	pFile->Read((char*)&m_uiHoldTimeSec, sizeof(unsigned int));
	pFile->Read((char*)&m_uiWaitTimeBelowStartTem, sizeof(unsigned int));

	pFile->Read((char*)&m_eChkType, sizeof(eStepCheckType));

	return TRUE;
}

