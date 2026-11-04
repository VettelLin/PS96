// 【交接】 PCRCtrlLib\CalibrateParaTurbidity.cpp
// 作用：CalibrateParaTurbidity。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CCalibrateParaTurbidity、DeleteAll、GetCount、GetAt、SAFE_DELETE、ReadPara、GetPrivateProfileString、_ttof。
#include "StdAfx.h"
#include "CalibrateParaTurbidity.h"
#include "PublicFun.h"

// 函数 CCalibrateParaTurbidity::CCalibrateParaTurbidity
// 作用：执行CCalibrateParaTurbidity。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCalibrateParaTurbidity::CCalibrateParaTurbidity(void)
{
	m_fMinRatio = 0.06f;
}

// 函数 CCalibrateParaTurbidity::~CCalibrateParaTurbidity
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteAll。
CCalibrateParaTurbidity::~CCalibrateParaTurbidity(void)
{
	DeleteAll();
}

// 函数 CCalibrateParaTurbidity::DeleteAll
// 作用：更新或清除DeleteAll。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、SAFE_DELETE。
void CCalibrateParaTurbidity::DeleteAll()
{
	int iCount = m_arrayDyePara.GetCount();
	for (int i=0; i<iCount; i++)
	{
		tagTurbidityPara* pAdjust = (tagTurbidityPara*)m_arrayDyePara.GetAt(i);
		SAFE_DELETE(pAdjust);
	}
}

// 函数 CCalibrateParaTurbidity::ReadPara
// 作用：读取ReadPara。
// 参数：strFile：字符串。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、GetPrivateProfileString、_T、_ttof、GetPrivateProfileInt、Format。
BOOL CCalibrateParaTurbidity::ReadPara(CString strFile)
{
	DeleteAll();

	TCHAR c1[250];
	GetPrivateProfileString(_T("TurbidityPara"), _T("MinRatio"), _T("0.05"), c1, sizeof(c1), strFile);
	m_fMinRatio = (float)_ttof(c1);

	CString strFlag;
	tagTurbidityPara* pDyePara = NULL;

	int nDyeCount = ::GetPrivateProfileInt(_T("TurbidityPara"), _T("Count"), 0, strFile);
	for (int i=0; i<nDyeCount; i++)
	{
		pDyePara = new tagTurbidityPara;

		strFlag.Format(_T("TurbidityDye(%d)"), i+1);
		::GetPrivateProfileString(strFlag, _T("DyeName"), _T(""), c1, 250, strFile);
		pDyePara->strDyeName = c1;
		pDyePara->iChannel = ::GetPrivateProfileInt(strFlag, _T("Channel"), -1, strFile);

		pDyePara->bUseMOT = ::GetPrivateProfileInt(strFlag, _T("UseMOT"), 0, strFile);
		pDyePara->iAheadCycle = ::GetPrivateProfileInt(strFlag, _T("AheadCycle"), 5, strFile);
		GetPrivateProfileString(strFlag, _T("Ratio"), _T("0.05"), c1, sizeof(c1), strFile);
		pDyePara->fRatio = (float)_ttof(c1);

		m_arrayDyePara.Add(pDyePara);
	}
	
	return TRUE;
}

// 函数 CCalibrateParaTurbidity::SavePara
// 作用：把SavePara写入文件、仪器或界面。
// 参数：strFile：字符串。
// 返回：返回是或否。
// 过程：函数里会调用 Format、_T、WritePrivateProfileString、GetSize、GetAt、TurbidityDye。
BOOL CCalibrateParaTurbidity::SavePara(CString strFile)
{
	CString strFlag, strValue;

	strValue.Format(_T("%.4f"), m_fMinRatio);
	::WritePrivateProfileString(_T("TurbidityPara"), _T("MinRatio"), strValue, strFile);

	int nCount = (int)m_arrayDyePara.GetSize();
	strValue.Format(_T("%d"), nCount);
	::WritePrivateProfileString(_T("TurbidityPara"), _T("Count"), strValue, strFile);

	tagTurbidityPara* pDyePara = NULL;
	for (int i=0; i<nCount; i++)
	{
		pDyePara = (tagTurbidityPara*)m_arrayDyePara.GetAt(i);
		strFlag.Format(_T("TurbidityDye(%d)"), i+1);
		::WritePrivateProfileString(strFlag, _T("DyeName"), pDyePara->strDyeName, strFile);
		strValue.Format(_T("%d"), pDyePara->iChannel);
		::WritePrivateProfileString(strFlag, _T("Channel"), strValue, strFile);
		strValue.Format(_T("%d"), pDyePara->bUseMOT);
		::WritePrivateProfileString(strFlag, _T("UseMOT"), strValue, strFile);
		strValue.Format(_T("%d"), pDyePara->iAheadCycle);
		::WritePrivateProfileString(strFlag, _T("AheadCycle"), strValue, strFile);
		strValue.Format(_T("%.3f"), pDyePara->fRatio);
		::WritePrivateProfileString(strFlag, _T("Ratio"), strValue, strFile);
	}

	return TRUE;
}

// 写入数据到文件中
// 函数 CCalibrateParaTurbidity::WriteFile
// 作用：把WriteFile写入文件、仪器或界面。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 Write、GetCount、GetAt、WriteStringToFile。
BOOL CCalibrateParaTurbidity::WriteFile(CFile* pFile)
{
	pFile->Write((const char *)&m_iChannelMOT, sizeof(int));
	pFile->Write((const char *)&m_fMinRatio, sizeof(float));

	int nParaCount = m_arrayDyePara.GetCount();
	pFile->Write((const char*)&nParaCount, sizeof(int));
	for (int i=0; i<nParaCount; i++)
	{
		tagTurbidityPara* pAdjust = (tagTurbidityPara*)m_arrayDyePara.GetAt(i);
		CPublicFun::WriteStringToFile(pFile, pAdjust->strDyeName);
		pFile->Write((const char *)&pAdjust->iChannel, sizeof(int));
		pFile->Write((const char *)&pAdjust->bUseMOT, sizeof(BOOL));
		pFile->Write((const char *)&pAdjust->iAheadCycle, sizeof(int));
		pFile->Write((const char *)&pAdjust->fRatio, sizeof(float));
	}

	return TRUE;
}

// 函数 CCalibrateParaTurbidity::ReadFile
// 作用：读取ReadFile。
// 参数：pFile：指针，指向调用方传入的对象；wVersion。
// 返回：返回是或否。
// 过程：函数里会调用 DeleteAll、Read、Add、ReadStringFromFile。
BOOL CCalibrateParaTurbidity::ReadFile(CFile* pFile, WORD wVersion)
{
	DeleteAll();

	pFile->Read((char*)&m_iChannelMOT, sizeof(int));
	pFile->Read((char*)&m_fMinRatio, sizeof(float));

	int nParaCount = 0;
	pFile->Read(&nParaCount, sizeof(int));
	for (int i=0; i<nParaCount; i++)
	{
		tagTurbidityPara* pAdjust = new tagTurbidityPara;
		m_arrayDyePara.Add(pAdjust);
		pAdjust->strDyeName = CPublicFun::ReadStringFromFile(pFile);
		if (wVersion >= wPCRVersion102)
		{
			pFile->Read((char*)&pAdjust->iChannel, sizeof(int));
		}

		pFile->Read((char*)&pAdjust->bUseMOT, sizeof(BOOL));
		pFile->Read((char*)&pAdjust->iAheadCycle, sizeof(int));
		pFile->Read((char*)&pAdjust->fRatio, sizeof(float));
	}

	return TRUE;
}

// 函数 CCalibrateParaTurbidity::GetParaBy
// 作用：读取GetParaBy。
// 参数：strDye：字符串。
// 返回：返回指针 CCalibrateParaTurbidity::tagTurbidityPara*。指针为空表示没有取到对象。
// 过程：函数里会调用 GetCount、GetAt。
CCalibrateParaTurbidity::tagTurbidityPara* CCalibrateParaTurbidity::GetParaBy(CString strDye)
{
	tagTurbidityPara* pAdjust = NULL;
	int iCount = m_arrayDyePara.GetCount();
	for (int i=0; i<iCount; i++)
	{
		tagTurbidityPara* pTemp = (tagTurbidityPara*)m_arrayDyePara.GetAt(i);
		if (strDye == pTemp->strDyeName)
		{
			pAdjust = pTemp;
			break;
		}
	}

	return pAdjust;
}

// 函数 CCalibrateParaTurbidity::GetChannel
// 作用：读取GetChannel。
// 参数：strDye：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetParaBy。
int CCalibrateParaTurbidity::GetChannel(CString strDye)
{
	tagTurbidityPara* pAdjust = GetParaBy(strDye);
	if (pAdjust != NULL)
	{
		return pAdjust->iChannel;
	}

	return -1;
}


// 函数 CCalibrateParaTurbidity::UseCalibrate
// 作用：执行UseCalibrate。
// 参数：strDye：字符串。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetParaBy。
BOOL CCalibrateParaTurbidity::UseCalibrate(CString strDye)
{
	tagTurbidityPara* pAdjust = GetParaBy(strDye);
	if (pAdjust != NULL)
	{
		return pAdjust->bUseMOT;
	}

	return FALSE;
}

// 函数 CCalibrateParaTurbidity::UseCalibrate
// 作用：执行UseCalibrate。
// 参数：iChannel：整数。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetCount、GetAt。
BOOL CCalibrateParaTurbidity::UseCalibrate(int iChannel)
{
	int iCount = m_arrayDyePara.GetCount();
	for (int i=0; i<iCount; i++)
	{
		tagTurbidityPara* pTemp = (tagTurbidityPara*)m_arrayDyePara.GetAt(i);
		if (iChannel == pTemp->iChannel)
		{
			return pTemp->bUseMOT;
		}
	}

	return FALSE;

}

// 函数 CCalibrateParaTurbidity::EnableUseCalibrate
// 作用：改变EnableUseCalibrate的显示或可用状态。
// 参数：strDye：字符串；bEnable：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetParaBy。
void CCalibrateParaTurbidity::EnableUseCalibrate(CString strDye, BOOL bEnable)
{
	tagTurbidityPara* pAdjust = GetParaBy(strDye);
	if (pAdjust != NULL)
	{
		pAdjust->bUseMOT = bEnable;
	}
}


// 函数 CCalibrateParaTurbidity::GetAheadCycle
// 作用：读取GetAheadCycle。
// 参数：strDye：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetParaBy。
int CCalibrateParaTurbidity::GetAheadCycle(CString strDye)
{
	tagTurbidityPara* pAdjust = GetParaBy(strDye);
	if (pAdjust != NULL)
	{
		return pAdjust->iAheadCycle;
	}

	//ASSERT(FALSE);
	return -1;
}

// 函数 CCalibrateParaTurbidity::SetAheadCycle
// 作用：设置SetAheadCycle。
// 参数：strDye：字符串；iCycyle：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetParaBy。
void CCalibrateParaTurbidity::SetAheadCycle(CString strDye, int iCycyle)
{
	tagTurbidityPara* pAdjust = GetParaBy(strDye);
	if (pAdjust != NULL)
	{
		pAdjust->iAheadCycle = iCycyle;
	}
}

// 函数 CCalibrateParaTurbidity::GetAdjustRatio
// 作用：读取GetAdjustRatio。
// 参数：strDye：字符串。
// 返回：返回一个小数。
// 过程：函数里会调用 GetParaBy。
float CCalibrateParaTurbidity::GetAdjustRatio(CString strDye)
{
	tagTurbidityPara* pAdjust = GetParaBy(strDye);
	if (pAdjust != NULL)
	{
		return pAdjust->fRatio;
	}

	//ASSERT(FALSE);
	return 0.1f;
}

// 函数 CCalibrateParaTurbidity::SetAdjustRatio
// 作用：设置SetAdjustRatio。
// 参数：strDye：字符串；fRatio：小数。
// 返回：没有返回值。
// 过程：函数里会调用 GetParaBy。
void CCalibrateParaTurbidity::SetAdjustRatio(CString strDye, float fRatio)
{
	tagTurbidityPara* pAdjust = GetParaBy(strDye);
	if (pAdjust != NULL)
	{
		pAdjust->fRatio = fRatio;
	}
}


// 函数 CCalibrateParaTurbidity::GetDye
// 作用：读取GetDye。
// 参数：iIndex：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 Empty、GetCount、GetAt。
CString CCalibrateParaTurbidity::GetDye(int iIndex)
{
	CString strDye;
	strDye.Empty();

	if (iIndex >=0 && iIndex < m_arrayDyePara.GetCount())
	{
		tagTurbidityPara* pAdjust = (tagTurbidityPara*)m_arrayDyePara.GetAt(iIndex);
		strDye = pAdjust->strDyeName;
	}

	return strDye;
}

// 函数 CCalibrateParaTurbidity::ResetChannel
// 作用：更新或清除ResetChannel。
// 参数：pArrayDyeChannel：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt。
void CCalibrateParaTurbidity::ResetChannel(CPtrArray* pArrayDyeChannel)
{
	for (int i=0; i<m_arrayDyePara.GetCount(); i++)
	{
		tagTurbidityPara* pAdjust = (tagTurbidityPara*)m_arrayDyePara.GetAt(i);
		if (pAdjust == NULL)
			continue;

		for (int j=0; j<pArrayDyeChannel->GetCount(); j++)
		{
			tagDyeChannelInfo* pChannel = (tagDyeChannelInfo*)pArrayDyeChannel->GetAt(j);
			if (pChannel == NULL)
				continue;

			if (pAdjust->strDyeName == pChannel->strDye)
			{
				pAdjust->iChannel = pChannel->iChannel;
				break;
			}
		}

	}
}
