// 【交接】 PCRInstanceLib\PublicFun.cpp
// 作用：PublicFun。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：MyRound、int、SplitCombineStringByFlag、RemoveAll、Find、Left、Right、Add。
#include "StdAfx.h"
#include "PublicFun.h"
#include "math.h"

// 函数 CPublicFun::MyRound
// 作用：执行MyRound。
// 参数：r。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 int、floor、ceil。
int CPublicFun::MyRound(double r)
{
	return int((r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5));
}


// 函数 CPublicFun::SplitCombineStringByFlag
// 作用：执行SplitCombineStringByFlag。
// 参数：strCombine：字符串；pArray：指针，指向调用方传入的对象；strFlag：字符串。
// 返回：没有返回值。
// 过程：函数里会调用 RemoveAll、IsEmpty、Find、Left、Right、GetLength。
void CPublicFun::SplitCombineStringByFlag(CString strCombine, CStringArray* pArray, CString strFlag)
{
	pArray->RemoveAll();

	while (!strCombine.IsEmpty())
	{
		int nPosition = strCombine.Find(strFlag);
		if (nPosition > 0)
		{
			CString stCol = strCombine.Left(nPosition);
			strCombine = strCombine.Right(strCombine.GetLength() - nPosition -1);
			pArray->Add(stCol.Trim());
		}
		else
		{
			break;
		}
	}

	if (!strCombine.IsEmpty())
	{
		pArray->Add(strCombine.Trim());
	}
}

// 函数 CPublicFun::GetCurrentDateTime
// 作用：读取GetCurrentDateTime。
// 参数：bHasMS：是或否。
// 返回：返回一段文字。
// 过程：函数里会调用 GetLocalTime、Format、_T。
CString CPublicFun::GetCurrentDateTime(BOOL bHasMS)
{
	CString strTime;
	SYSTEMTIME st;
	GetLocalTime(&st);
	if (bHasMS)
	{
		strTime.Format(_T("%4d-%02d-%02d %02d:%02d:%02d:%03d"),st.wYear, st.wMonth, st.wDay, st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
	}
	else
	{
		strTime.Format(_T("%4d-%02d-%02d %02d:%02d:%02d"),st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	}

	return strTime;
}


// 函数 CPublicFun::GetExeFileDirectory
// 作用：读取GetExeFileDirectory。
// 参数：无。
// 返回：返回一段文字。
// 过程：函数里会调用 fileDirectory、_T、memset、GetModuleFileName、_tcsrchr。
CString CPublicFun::GetExeFileDirectory()
{
	TCHAR filePath[MAX_PATH];
	CString fileDirectory(_T(""));
	memset(filePath,0,MAX_PATH);
	::GetModuleFileName(NULL,filePath,MAX_PATH);
	(_tcsrchr(filePath,_T('\\')))[1] = 0;
	fileDirectory += filePath;
	return fileDirectory;  
}

BOOL CPublicFun::ValidateFileOrDirWChar(const wchar_t& fileDirWChar)
{
	if(L'*' == fileDirWChar || L'\?' == fileDirWChar || L'\"' == fileDirWChar || L'<' == fileDirWChar || L'>' == fileDirWChar || L'|' == fileDirWChar)
	{
		return FALSE;
	}
	return TRUE;
}

int CPublicFun::CheckAndCreateFileOrDirPath(wstring fileDirPath)
{
	if(_T("") == fileDirPath)
	{
		return -1;
	}

	vector<int> slashIndex,dotIndex,iterantSlashIndex;
	slashIndex.clear();
	dotIndex.clear();
	const wchar_t* pCWPathData = fileDirPath.c_str();

	if(!ValidateFileOrDirWChar(*pCWPathData))
	{
		return -2;		
	}

	if(L'\\' == *pCWPathData || L'/' == *pCWPathData)
	{
		return -3;
	}

	int index = 0;
	while(0 != *(++pCWPathData))
	{
		++index;
		if(!ValidateFileOrDirWChar(*pCWPathData))
		{
			return -2;		
		}

		if(L'\\' == *pCWPathData || L'/' == *pCWPathData)
		{
			if(slashIndex.size() > 0)
			{
				if(index - 1 == slashIndex[slashIndex.size() - 1])
				{
					iterantSlashIndex.push_back(index);
					continue;
				}
			}
			slashIndex.push_back(index);
		}
		else if(L'.' == *pCWPathData)
		{
			dotIndex.push_back(index);
		}
	}

	wstring subWStr = _T("");

	if(0 == slashIndex.size())
	{
		wstring defaultWStr = GetExeFileDirectory().GetBuffer();
		defaultWStr += (_T("\\") + fileDirPath);
		ifstream ifs(defaultWStr);
		if(!ifs)
		{
			ofstream ofs(defaultWStr);
			ofs.close();
		}
		else
		{
			ifs.close();
		}
		return 1;
	}
	else if(0 == dotIndex.size())
	{
		for(UINT i = 0;i < slashIndex.size();++i)
		{
			subWStr = fileDirPath.substr(0,slashIndex[i] + 1);

			if(!PathIsDirectoryW(subWStr.c_str()))
			{
				if(!CreateDirectoryW(subWStr.c_str(),NULL))
				{
					return -4;
				}
			} 
		}
		if(fileDirPath.size() - 1 != slashIndex[slashIndex.size() - 1])
		{
			if(!PathIsDirectoryW(fileDirPath.c_str()))
			{
				if(!CreateDirectoryW(fileDirPath.c_str(),NULL))
				{
					return -5;
				}
			} 
		}
		return 2;
	}
	else
	{
		for(UINT i = 0;i < slashIndex.size();++i)
		{
			subWStr = fileDirPath.substr(0,slashIndex[i] + 1);

			if(!PathIsDirectoryW(subWStr.c_str()))
			{
				if(!CreateDirectoryW(subWStr.c_str(),NULL))
				{
					return -6;
				}
			} 
		}

		if(dotIndex[dotIndex.size() - 1] > slashIndex[slashIndex.size() - 1])
		{
			ifstream ifs(fileDirPath);
			if(!ifs)
			{
				ofstream ofs(fileDirPath);
				ofs.close();
			}
			else
			{
				ifs.close();
			}
			return 3;
		}
		else
		{
			if(fileDirPath.size() - 1 != slashIndex[slashIndex.size() - 1])
			{
				if(!PathIsDirectoryW(fileDirPath.c_str()))
				{
					if(!CreateDirectoryW(fileDirPath.c_str(),NULL))
					{
						return -7;
					}
				} 
			}
			return 4;
		}
	}
}

void CPublicFun::WriteStringToFile(CFile* pFile, CString strInput)
{
	int nStrLength = strInput.GetLength();
	pFile->Write((const char *)&nStrLength, sizeof(int));
	if(nStrLength > 0)
	{
		pFile->Write((const char*)(strInput.GetBuffer()), sizeof(TCHAR)*nStrLength);
	}
}

// 函数 CPublicFun::ReadStringFromFile
// 作用：读取ReadStringFromFile。
// 参数：pFile：指针，指向调用方传入的对象。
// 返回：返回一段文字。
// 过程：函数里会调用 Empty、Read。
CString CPublicFun::ReadStringFromFile(CFile* pFile)
{
	CString strRead;
	strRead.Empty();
	int nStrLength = 0;
	pFile->Read((char*)&nStrLength, sizeof(int));
	if(nStrLength > 0)
	{
		TCHAR lpTStr[1024] = {0};
		pFile->Read((char*)lpTStr, sizeof(TCHAR) * nStrLength);
		lpTStr[nStrLength] = 0; 
		strRead = lpTStr;
	}

	return strRead;
}

// 函数 CPublicFun::ConverToColor
// 作用：执行ConverToColor。
// 参数：strColor：字符串。
// 返回：返回 COLORREF。
// 过程：函数里会调用 RGB、SplitCombineStringByFlag、_T、GetCount、_ttoi、GetAt。
COLORREF CPublicFun::ConverToColor(CString strColor)
{
	COLORREF clrReturn = RGB(0, 0, 0);
	CStringArray arrayColor;
	SplitCombineStringByFlag(strColor, &arrayColor, _T(","));
	ASSERT(arrayColor.GetCount() == 3);
	int r = _ttoi(arrayColor.GetAt(0));
	int g = _ttoi(arrayColor.GetAt(1));
	int b = _ttoi(arrayColor.GetAt(2));

	clrReturn = RGB(r, g, b);

	return clrReturn;
}

// 函数 CPublicFun::GetDoublePrecision
// 作用：读取GetDoublePrecision。
// 参数：dValue：小数；nPres：整数。
// 返回：返回一个小数。
// 过程：函数里会调用 pow。
double CPublicFun::GetDoublePrecision(double dValue,int nPres)
{
	double factor = pow(10.0,nPres);
	dValue = (double)((/*int*/__int64)(dValue*factor)/factor);
	return dValue;
}
