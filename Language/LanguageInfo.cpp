// 【交接】 Language\LanguageInfo.cpp
// 作用：LanguageInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CLanguageInfo、GetInstance、CleanUp、InitLanguageText、ReverseFind、Mid、xlCreateXMLBook、setKey。
#include "StdAfx.h"
#include "LanguageInfo.h"
#include "libxl.h"

using namespace libxl;

CLanguageInfo* CLanguageInfo::m_pInstance = NULL;

// 函数 CLanguageInfo::CLanguageInfo
// 作用：执行CLanguageInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLanguageInfo::CLanguageInfo(void)
{
	m_nLanguage = LANGUAGE_CHS;
}

// 函数 CLanguageInfo::~CLanguageInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLanguageInfo::~CLanguageInfo(void)
{
}

// 函数 CLanguageInfo::GetInstance
// 作用：读取GetInstance。
// 参数：无。
// 返回：返回指针 CLanguageInfo*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLanguageInfo* CLanguageInfo::GetInstance(void)
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CLanguageInfo;
	}
	return m_pInstance;
}

// 函数 CLanguageInfo::CleanUp
// 作用：执行CleanUp。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLanguageInfo::CleanUp()
{
	if(NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

// 函数 CLanguageInfo::InitLanguageText
// 作用：初始化InitLanguageText。
// 参数：strPath：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 IsEmpty、PathFileExists、ReverseFind、Mid、xlCreateXMLBook、setKey。
int CLanguageInfo::InitLanguageText(CString strPath)
{
	if(strPath.IsEmpty())
	{
		return -1;
	}

	if(!PathFileExists(strPath))
	{
		return -2;
	}

	int iDotIndex = strPath.ReverseFind('.');
	if(-1 == iDotIndex)
	{
		return -3;
	}

	CString strExt = strPath.Mid(iDotIndex + 1);
	if(LANGUAGEFILEEXT != strExt)
	{
		return -4;
	}

	Book* pBook = xlCreateXMLBook();
	if(NULL == pBook)
	{
		return -5;
	}

	pBook->setKey(_T("Halil Kural"), _T("windows-2723210a07c4e90162b26966a8jcdboe"));
	if (!pBook->load(strPath))
	{
		return -6;
	}

	m_arrayIndex.RemoveAll();
	CLanguageInfo* pLanguageInfo = CLanguageInfo::GetInstance();

	double dData = 0;
	int iErrCode = -10,iRow = -1,iCol = -1,iTextNum = 0;;
	CString strTemp(_T("")),strChinese(_T("")),strEnglish(_T(""));

	Sheet* pSheet = pBook->getSheet(0);
	if (NULL == pSheet)
	{
		iErrCode = -7;
		goto READFAILED;
	}
	
	strTemp = pSheet->readStr(0,0);
	if(LANGUAGEFILE_TAG != strTemp)
	{
		iErrCode = -8;
		goto READFAILED;
	}

	//文件版本号
	strTemp = pSheet->readStr(0,1);

	//中文标识
	strTemp = pSheet->readStr(0,2);
	if(_T("中文") != strTemp)
	{
		iErrCode = -9;
		goto READFAILED;
	}

	//英文标识
	strTemp = pSheet->readStr(0,3);
	if(_T("英文") != strTemp)
	{
		iErrCode = -10;
		goto READFAILED;
	}

	iRow = 1;
	iCol = 0;
	dData = pSheet->readNum(iRow,++iCol);
	while(dData > 0)
	{
		m_arrayIndex.Add((int)dData);
		strChinese = pSheet->readStr(iRow,++iCol);
		strEnglish = pSheet->readStr(iRow,++iCol);
		m_mapIdToChinese[dData] = strChinese;
		m_mapIdToEnglish[dData] = strEnglish;
		++iRow;
		iCol = 0;
		dData = pSheet->readNum(iRow,++iCol);

		if(++iTextNum > 10000)	//防止陷入死循环
		{
			iErrCode = -11;
			goto READFAILED;
		}
	}

	pBook->release();
	return 0;

READFAILED:
	pBook->release();
	return iErrCode;
}

// 函数 CLanguageInfo::GetText
// 作用：读取GetText。
// 参数：iId：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 _T、find、end、strTemp、Format。
CString CLanguageInfo::GetText(int iId)
{
	if(NULL == this)
	{
		return _T("NULL address");
	}

	map<int,CString>::iterator it;
	map<int,CString>* pMap = NULL;
	if(LANGUAGE_CHS == m_nLanguage)
	{
		pMap = &m_mapIdToChinese;
	}
	else
	{
		pMap = &m_mapIdToEnglish;
	}

	if(NULL != pMap)
	{
		it = pMap->find(iId);
		if(it != pMap->end())
		{
			return it->second;
		}
	}

	CString strTemp(_T(""));
	strTemp.Format(_T("%d"),iId);
	return strTemp;
}

// 函数 CLanguageInfo::GetText
// 作用：读取GetText。
// 参数：iId：整数；eLanguage。
// 返回：返回一段文字。
// 过程：函数里会调用 _T、find、end、strTemp、Format。
CString CLanguageInfo::GetText(int iId, eLanguageUI eLanguage)
{
	if(NULL == this)
	{
		return _T("NULL address");
	}

	map<int,CString>::iterator it;
	map<int,CString>* pMap = NULL;
	if(LANGUAGE_CHS == eLanguage)
	{
		pMap = &m_mapIdToChinese;
	}
	else
	{
		pMap = &m_mapIdToEnglish;
	}

	if(NULL != pMap)
	{
		it = pMap->find(iId);
		if(it != pMap->end())
		{
			return it->second;
		}
	}

	CString strTemp(_T(""));
	strTemp.Format(_T("%d"),iId);


	return strTemp;
}

// 函数 CLanguageInfo::GetBeEnglish
// 作用：读取GetBeEnglish。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CLanguageInfo::GetBeEnglish()
{
	if(NULL == this)
	{
		return FALSE;
	}
	return LANGUAGE_ENG == m_nLanguage;
}

// 函数 CLanguageInfo::ConvertTo
// 作用：执行ConvertTo。
// 参数：strInput：字符串；eLanguage。
// 返回：返回一段文字。
// 过程：函数里会调用 Empty、GetCount、GetText、GetAt、IsEmpty。
CString CLanguageInfo::ConvertTo(CString strInput, eLanguageUI eLanguage)
{
	if (eLanguage == m_nLanguage)
	{
		return strInput;
	}

	CString strReturn;
	strReturn.Empty();
	for (int i=0; i<m_arrayIndex.GetCount(); i++)
	{
		if (GetText(m_arrayIndex.GetAt(i)) == strInput)
		{
			strReturn = GetText(m_arrayIndex.GetAt(i), eLanguage);
			break;
		}
	}
	if (strReturn.IsEmpty())
	{
		strReturn = strInput;
	}

	return strReturn;
}

// 读取英文的大写拼写字符串，中文忽略
// 函数 CLanguageInfo::GetCapitalText
// 作用：读取GetCapitalText。
// 参数：iId：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetText、Replace、_T。
CString CLanguageInfo::GetCapitalText(int iId)
{
	CString strText = GetText(iId);
	if (m_nLanguage == LANGUAGE_ENG)
	{
		strText.Replace(_T("a"), _T("A")); //1
		strText.Replace(_T("b"), _T("B"));
		strText.Replace(_T("c"), _T("C"));
		strText.Replace(_T("d"), _T("D"));
		strText.Replace(_T("e"), _T("E"));
		strText.Replace(_T("f"), _T("F"));
		strText.Replace(_T("g"), _T("G"));
		strText.Replace(_T("h"), _T("H"));
		strText.Replace(_T("i"), _T("I"));
		strText.Replace(_T("j"), _T("J"));
		strText.Replace(_T("k"), _T("K")); // 11
		strText.Replace(_T("l"), _T("L"));
		strText.Replace(_T("m"), _T("M"));
		strText.Replace(_T("n"), _T("N"));
		strText.Replace(_T("o"), _T("O"));
		strText.Replace(_T("p"), _T("P"));
		strText.Replace(_T("q"), _T("Q"));
		strText.Replace(_T("r"), _T("R"));
		strText.Replace(_T("s"), _T("S"));
		strText.Replace(_T("t"), _T("T"));
		strText.Replace(_T("u"), _T("U")); // 21
		strText.Replace(_T("v"), _T("V"));
		strText.Replace(_T("w"), _T("W"));
		strText.Replace(_T("x"), _T("X"));
		strText.Replace(_T("y"), _T("Y"));
		strText.Replace(_T("z"), _T("Z"));
	}
	return  strText;
}

// 函数 CLanguageInfo::GetTextWithColon
// 作用：读取GetTextWithColon。
// 参数：iID：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetText、_T。
CString CLanguageInfo::GetTextWithColon(int iID)
{
	if (m_nLanguage == LANGUAGE_ENG)
		return GetText(iID) + _T(":");
	else
		return GetText(iID) + _T("：");
}

// 函数 CLanguageInfo::GetTextWithColon
// 作用：读取GetTextWithColon。
// 参数：iId：整数；eLanguage。
// 返回：返回一段文字。
// 过程：函数里会调用 GetText、_T。
CString CLanguageInfo::GetTextWithColon(int iId, eLanguageUI eLanguage)
{
	if (eLanguage == LANGUAGE_ENG)
		return GetText(iId, eLanguage) + _T(":");
	else
		return GetText(iId, eLanguage) + _T("：");
}

// 函数 CLanguageInfo::GetCapitalTextWithColon
// 作用：读取GetCapitalTextWithColon。
// 参数：iId：整数。
// 返回：返回一段文字。
// 过程：函数里会调用 GetCapitalText、_T。
CString CLanguageInfo::GetCapitalTextWithColon(int iId)
{
	if (m_nLanguage == LANGUAGE_ENG)
		return GetCapitalText(iId) + _T(":");
	else
		return GetCapitalText(iId) + _T("：");
}
