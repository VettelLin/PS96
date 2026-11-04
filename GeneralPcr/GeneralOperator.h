// 【交接】 GeneralPcr\GeneralOperator.h
// 作用：GeneralOperator。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CGeneralOperator、ExtractSubString、Find、push_back、GetAppHome、GetModuleFileName、CString、ReverseFind。
#pragma once
#include <vector>
#include "shlwapi.h"
#import "msxml3.dll"

class CGeneralOperator
{
public:
	// 函数 CGeneralOperator
	// 作用：执行CGeneralOperator。
	// 参数：无。
	// 返回：没有返回值。
	CGeneralOperator(void){};
	// 函数 ~CGeneralOperator
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CGeneralOperator(void){};

	// 函数 ExtractSubString
	// 作用：执行ExtractSubString。
	// 参数：strSource：字符串；ch；vString。
	// 返回：没有返回值。
	// 过程：函数里会调用 Find、push_back、Mid、GetLength、Right。
	static void ExtractSubString(CString strSource, char ch, std::vector<CString>& vString)
	{
		int nBegin = 0;
		int nEnd = 0;

		nEnd = strSource.Find(ch, nBegin);

		while (nEnd != -1)
		{
			vString.push_back(strSource.Mid(nBegin, nEnd - nBegin));
			nBegin = nEnd + 1;
			nEnd = strSource.Find(ch, nBegin);
		}

		if (nBegin < strSource.GetLength())
		{
			vString.push_back(strSource.Right(strSource.GetLength() - nBegin));
		}		
	}

	///////////////////////////////////////////////////////////////////////
	/**	
	*	得到可执行程序的目录名
	*
	*	@return  可执行程序的目录名
	*	@author thh		@date 20050830
	*/
	// 函数 GetAppHome
	// 作用：读取GetAppHome。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetModuleFileName、CString、ReverseFind、_T、Left。
	static CString GetAppHome()
	{
		TCHAR pFileName[256]; 
		GetModuleFileName(NULL,pFileName,255);
		CString appHome;
		appHome = CString(pFileName);
		int nPos = appHome.ReverseFind( _T('\\') ); 
		if( nPos < 0 ) 
			appHome = CString(""); 
		else 
			appHome = appHome.Left(nPos);
		return appHome;
	}

	///////////////////////////////////////////////////////////////////////
	/**	
	*	数据转换为字符串
	*
	*	@param	 Type value			--  要转换的数据
	*	@param	 CString strFormat  --  要转换的格式字符串
	*	@return  转换后的字符串
	*	@author thh		@date 20050830
	*/
	template<class Type>
	// 函数 ExchangeValueToStr
	// 作用：执行ExchangeValueToStr。
	// 参数：value；strFormat：字符串。
	// 返回：返回一段文字。
	// 过程：函数里会调用 Format。
	static CString ExchangeValueToStr(Type value, CString strFormat)
	{
		CString strResult;
		strResult.Format(strFormat, value);
		return strResult;
	}

	template<class Type>
	// 函数 DeleteVectorItem
	// 作用：更新或清除DeleteVectorItem。
	// 参数：strVect：字符串；nIndex：整数。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 size、pop_back。
	static BOOL DeleteVectorItem(std::vector<Type> &strVect, int nIndex)
	{
		if(nIndex < 0 || strVect.size()-1 < static_cast<unsigned>(nIndex))
		{
			return FALSE;
		}
		for(unsigned int i = nIndex; i < strVect.size()-1; i++)
		{
			strVect[i] = strVect[i+1];
		}
		strVect.pop_back();
		return TRUE;
	}

	// 函数 ShowBrowseDlg
	// 作用：改变ShowBrowseDlg的显示或可用状态。
	// 参数：wnd；strTitle：字符串。
	// 返回：返回一段文字。
	// 过程：函数里会调用 Empty、ZeroMemory、SHBrowseForFolder、SHGetPathFromIDList、GetBuffer、ReleaseBuffer。
	static CString ShowBrowseDlg(HWND wnd, CString strTitle)
	{
		CString str;
		str.Empty();
		BROWSEINFO bi;
		TCHAR name[MAX_PATH];
		ZeroMemory(&bi,sizeof(BROWSEINFO));
		bi.hwndOwner = wnd;
		bi.pszDisplayName = name;
		bi.lpszTitle = strTitle;
		bi.ulFlags = BIF_DONTGOBELOWDOMAIN |BIF_RETURNONLYFSDIRS ;
		LPITEMIDLIST idl=SHBrowseForFolder(&bi);
		if(idl==NULL)
			return str;
		SHGetPathFromIDList(idl,str.GetBuffer(MAX_PATH));
		str.ReleaseBuffer();
		return str;
	}

	// 函数 IsNumString
	// 作用：判断IsNumString是否成立。
	// 参数：str：字符串。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 GetLength、isdigit、GetAt。
	static BOOL IsNumString(CString str)
	{
		for(int i = 0; i < str.GetLength(); i++)
		{
			if(!::isdigit(str.GetAt(i)))
				return FALSE;
		}
		return TRUE;
	}

	// 函数 GetPathLastName
	// 作用：读取GetPathLastName。
	// 参数：strPath：字符串；bContainExt：是或否。
	// 返回：返回一段文字。
	// 过程：函数里会调用 ExtractSubString、_T、at、size、Find、Left。
	static CString GetPathLastName(CString strPath, BOOL bContainExt = FALSE)
	{
		std::vector<CString> vStr;
		CGeneralOperator::ExtractSubString(strPath, _T('\\'), vStr);
		CString strLastName = vStr.at(vStr.size() - 1);

		if(!bContainExt)
		{
			int nPos = -1;
			while( strLastName.Find(_T('.'), nPos + 1) != -1 )
			{
				nPos = strLastName.Find(_T('.'), nPos + 1);
			}
			strLastName = strLastName.Left(nPos);
		}
		return strLastName;
	}

	// 函数 IsFileExist
	// 作用：判断IsFileExist是否成立。
	// 参数：strFile：字符串。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 FindFile、GetAppHome、_T。
	static BOOL IsFileExist(CString& strFile)
	{
		CFileFind ff;
		if(!ff.FindFile(strFile))
		{
			strFile = GetAppHome() + _T("\\") + strFile;
			if(!ff.FindFile(strFile))
				return FALSE;
		}
		return TRUE;
	}

	// 函数 CreateFolder
	// 作用：创建或加入CreateFolder。
	// 参数：strFolder：字符串。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 ReverseFind、_T、Left、PathFileExists、SHCreateDirectory、CStringW。
	static BOOL CreateFolder(CString& strFolder)
	{
		int nPos = strFolder.ReverseFind(_T('\\'));
		strFolder = strFolder.Left(nPos);
		if(!PathFileExists(strFolder))
		{
			if(ERROR_SUCCESS != ::SHCreateDirectory(NULL, CStringW(strFolder)))
			{
				strFolder = GetAppHome() + _T("\\") + strFolder;
				if(!PathFileExists(strFolder))
				{
					if(ERROR_SUCCESS != ::SHCreateDirectory(NULL, CStringW(strFolder)))
						return FALSE;
				}
			}
		}
		return TRUE;
	}

	// 函数 LoadString
	// 作用：读入LoadString。
	// 参数：idText。
	// 返回：返回一段文字。
	// 过程：函数里会调用 _T。
	static CString LoadString(int idText)
	{
		CString str;
		if(str.LoadString(idText))
			return str;
		return _T("");
	}
};

#define ValueToStr(value, strformat) ( CGeneralOperator::ExchangeValueToStr(value, strformat) )
