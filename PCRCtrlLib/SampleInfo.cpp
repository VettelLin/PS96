// 【交接】 PCRCtrlLib\SampleInfo.cpp
// 作用：SampleInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSampleInfo、Empty、time、localtime、Format、GetCollectYMD、Find、Left。
#include "StdAfx.h"
#include "SampleInfo.h"
#include "LanguageInfo.h"

// 函数 CSampleInfo::CSampleInfo
// 作用：执行CSampleInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty、time、localtime、Format、_T。
CSampleInfo::CSampleInfo(void)
{
	m_strPatientID.Empty();
	m_strClinicID.Empty();
	m_strCaseID.Empty();
	m_strPatientName.Empty();
	m_nPatientSex = SEXUALITY_NONE;
	m_nPatientAge = -1;
	m_nAgeUnit = AGE_UNIT_YEAR;
	m_strAreaNo.Empty();
	m_strRoomNo.Empty();
	m_strBedNo.Empty();
	m_strProposer.Empty();
	m_strDepartment.Empty();
	m_strHospital.Empty();
	m_strApplyDate.Empty();

	time_t timer = time(NULL);	struct tm* localTime = localtime(&timer);	m_strCollectDate.Format(_T("%d%s%02d%s%02d%s%02d%s%02d%s%02d"),localTime->tm_year + 1900,_T("-"),localTime->tm_mon + 1,_T("-"),localTime->tm_mday,_T(" "),localTime->tm_hour,_T(":"),localTime->tm_min,_T(":"),localTime->tm_sec);
}

// 函数 CSampleInfo::~CSampleInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSampleInfo::~CSampleInfo(void)
{
}

// 函数 CSampleInfo::CSampleInfo
// 作用：执行CSampleInfo。
// 参数：samInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSampleInfo::CSampleInfo(const CSampleInfo& samInfo)
{
	m_strPatientID = samInfo.m_strPatientID;
	m_strClinicID = samInfo.m_strClinicID;
	m_strCaseID = samInfo.m_strCaseID;
	m_strPatientName = samInfo.m_strPatientName;
	m_nPatientSex = samInfo.m_nPatientSex;
	m_nPatientAge = samInfo.m_nPatientAge;
	m_nAgeUnit = samInfo.m_nAgeUnit;
	m_strAreaNo = samInfo.m_strAreaNo;
	m_strRoomNo = samInfo.m_strRoomNo;
	m_strBedNo = samInfo.m_strBedNo;
	m_strProposer = samInfo.m_strProposer;
	m_strDepartment = samInfo.m_strDepartment;
	m_strHospital = samInfo.m_strHospital;
	m_strCollectDate = samInfo.m_strCollectDate;
	m_strApplyDate = samInfo.m_strApplyDate;
}

void CSampleInfo::operator=(const CSampleInfo& samInfo)
{
	m_strPatientID = samInfo.m_strPatientID;
	m_strClinicID = samInfo.m_strClinicID;
	m_strCaseID = samInfo.m_strCaseID;
	m_strPatientName = samInfo.m_strPatientName;
	m_nPatientSex = samInfo.m_nPatientSex;
	m_nPatientAge = samInfo.m_nPatientAge;
	m_nAgeUnit = samInfo.m_nAgeUnit;
	m_strAreaNo = samInfo.m_strAreaNo;
	m_strRoomNo = samInfo.m_strRoomNo;
	m_strBedNo = samInfo.m_strBedNo;
	m_strProposer = samInfo.m_strProposer;
	m_strDepartment = samInfo.m_strDepartment;
	m_strHospital = samInfo.m_strHospital;
	m_strCollectDate = samInfo.m_strCollectDate;
	m_strApplyDate = samInfo.m_strApplyDate;
}

BOOL CSampleInfo::operator==(const CSampleInfo& samInfo)
{
	return m_strPatientID == samInfo.m_strPatientID && 
	m_strClinicID == samInfo.m_strClinicID && 
	m_strCaseID == samInfo.m_strCaseID && 
	m_strPatientName == samInfo.m_strPatientName && 
	m_nPatientSex == samInfo.m_nPatientSex && 
	m_nPatientAge == samInfo.m_nPatientAge && 
	m_nAgeUnit == samInfo.m_nAgeUnit && 
	m_strAreaNo == samInfo.m_strAreaNo && 
	m_strRoomNo == samInfo.m_strRoomNo && 
	m_strBedNo == samInfo.m_strBedNo && 
	m_strProposer == samInfo.m_strProposer && 
	m_strDepartment == samInfo.m_strDepartment && 
	m_strHospital == samInfo.m_strHospital && 
	m_strCollectDate == samInfo.m_strCollectDate && 
	m_strApplyDate == samInfo.m_strApplyDate;
}

// 函数 CSampleInfo::GetCollectYMD
// 作用：读取GetCollectYMD。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 Find、_T、Left。
CString CSampleInfo::GetCollectYMD()
{
	int iIndex = m_strCollectDate.Find(_T(' '));
	if(-1 != iIndex)
	{
		return m_strCollectDate.Left(iIndex);
	}

	return _T("");
}

// 函数 CSampleInfo::SetCollectDateYMD
// 作用：设置SetCollectDateYMD。
// 参数：strDate：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 IsEmpty、Find、_T。
void CSampleInfo::SetCollectDateYMD(CString strDate)
{
	if(strDate.IsEmpty())
	{
		return;
	}

	int iIndex = strDate.Find(_T(' '));
	if(-1 == iIndex)
	{
		strDate += _T(" 00:00:00");
	}
	
	m_strCollectDate = strDate;

	return;
}

// 函数 CSampleInfo::SetSQMCollectDateYMD
// 作用：设置SetSQMCollectDateYMD。
// 参数：strDate：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 IsEmpty、Find、_T、GetLength、Left。
void CSampleInfo::SetSQMCollectDateYMD(CString strDate)
{
	if(strDate.IsEmpty())
	{
		return;
	}

	int iIndex = strDate.Find(_T('\''));
	if(strDate.GetLength() - 1 != iIndex)
	{
		if(strDate.GetLength() >= 10)
		{
			strDate = strDate.Left(10);
		}
		else
		{
			return;
		}
	}
	else
	{
		strDate = strDate.Left(strDate.GetLength() - 1);
	}

	
	if(strDate.IsEmpty())
	{
		return;
	}

	m_strCollectDate = strDate;
	iIndex = m_strCollectDate.Find(_T(' '));
	if(-1 == iIndex && m_strCollectDate.GetLength() <= 10)
	{
		m_strCollectDate += _T(" 00:00:00");
	}

	return;
}

// 函数 CSampleInfo::Reset
// 作用：更新或清除Reset。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
void CSampleInfo::Reset()
{
	m_strPatientID.Empty();
	m_strClinicID.Empty();
	m_strCaseID.Empty();
	m_strPatientName.Empty();
	m_nPatientSex = SEXUALITY_NONE;
	m_nPatientAge = -1;
	m_nAgeUnit = AGE_UNIT_YEAR;
	m_strAreaNo.Empty();
	m_strRoomNo.Empty();
	m_strBedNo.Empty();
	m_strProposer.Empty();
	m_strDepartment.Empty();
	m_strHospital.Empty();
	m_strCollectDate.Empty();
	m_strApplyDate.Empty();
}

// 函数 CSampleInfo::SetSexuality
// 作用：设置SetSexuality。
// 参数：strData：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 GetInstance、GetText。
void CSampleInfo::SetSexuality(CString strData)
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	if(pLangInfo->GetText(182,LANGUAGE_CHS) == strData || pLangInfo->GetText(182,LANGUAGE_ENG) == strData)
	{
		m_nPatientSex = SEXUALITY_MALE;
	}
	else if(pLangInfo->GetText(183,LANGUAGE_CHS) == strData || pLangInfo->GetText(183,LANGUAGE_ENG) == strData)
	{
		m_nPatientSex = SEXUALITY_FEMALE;
	}
	else
	{
		m_nPatientSex = SEXUALITY_NONE;
	}

	return;
}

// 函数 CSampleInfo::GetSexualityString
// 作用：读取GetSexualityString。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 GetInstance、GetText、_T。
CString CSampleInfo::GetSexualityString()
{
	CLanguageInfo* pLangInfo = CLanguageInfo::GetInstance();
	if(SEXUALITY_MALE == m_nPatientSex)
	{
		return pLangInfo->GetText(182);
	}
	else if(SEXUALITY_FEMALE == m_nPatientSex)
	{
		return pLangInfo->GetText(183);
	}
	else
	{
		 return _T("");
	}
}

// 函数 CSampleInfo::GetAgeString
// 作用：读取GetAgeString。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 strTemp、_T、Format。
CString CSampleInfo::GetAgeString()
{
	CString strTemp(_T(""));
	if(m_nPatientAge > 0)
	{
		strTemp.Format(_T("%d"),m_nPatientAge); 
	}
	
	return strTemp; 
}


