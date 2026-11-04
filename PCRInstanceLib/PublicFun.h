// 【交接】 PCRInstanceLib\PublicFun.h
// 作用：PublicFun。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPublicFun、MyRound、SplitCombineStringByFlag、GetCurrentDateTime、GetExeFileDirectory、ValidateFileOrDirWChar、CheckAndCreateFileOrDirPath、WriteStringToFile。
#pragma once

#include <string>
#include <tchar.h>
#include <fstream>
#include <vector>

using namespace std;

// 公用函数，一般是Static
class AFX_EXT_CLASS CPublicFun
{
public:
	// 函数 CPublicFun
	// 作用：执行CPublicFun。
	// 参数：无。
	// 返回：没有返回值。
	CPublicFun(void) {}
	// 函数 ~CPublicFun
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPublicFun(void){}

public:
	// 函数 MyRound
	// 作用：执行MyRound。
	// 参数：r。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	static int MyRound(double r);
	// 函数 SplitCombineStringByFlag
	// 作用：执行SplitCombineStringByFlag。
	// 参数：strCombine：字符串；pArray：指针，指向调用方传入的对象；strFlag：字符串。
	// 返回：没有返回值。
	static void SplitCombineStringByFlag(CString strCombine, CStringArray* pArray, CString strFlag=_T(";"));
	// 函数 GetCurrentDateTime
	// 作用：读取GetCurrentDateTime。
	// 参数：bHasMS：是或否。
	// 返回：返回一段文字。
	static CString GetCurrentDateTime(BOOL bHasMS=TRUE);

	// 函数 GetExeFileDirectory
	// 作用：读取GetExeFileDirectory。
	// 参数：无。
	// 返回：返回一段文字。
	static CString GetExeFileDirectory();
	// 函数 ValidateFileOrDirWChar
	// 作用：执行ValidateFileOrDirWChar。
	// 参数：fileDirWChar。
	// 返回：返回是或否。
	static BOOL ValidateFileOrDirWChar(const wchar_t& fileDirWChar);
	// 函数 CheckAndCreateFileOrDirPath
	// 作用：判断CheckAndCreateFileOrDirPath是否成立。
	// 参数：fileDirPath。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	static int CheckAndCreateFileOrDirPath(wstring fileDirPath);

	// 函数 WriteStringToFile
	// 作用：把WriteStringToFile写入文件、仪器或界面。
	// 参数：pFile：指针，指向调用方传入的对象；strInput：字符串。
	// 返回：没有返回值。
	static void WriteStringToFile(CFile* pFile, CString strInput);
	// 函数 ReadStringFromFile
	// 作用：读取ReadStringFromFile。
	// 参数：pFile：指针，指向调用方传入的对象。
	// 返回：返回一段文字。
	static CString ReadStringFromFile(CFile* pFile);

	// 函数 ConverToColor
	// 作用：执行ConverToColor。
	// 参数：strColor：字符串。
	// 返回：返回 COLORREF。
	static COLORREF ConverToColor(CString strColor);

	// 函数 GetDoublePrecision
	// 作用：读取GetDoublePrecision。
	// 参数：dValue：小数；nPres：整数。
	// 返回：返回一个小数。
	static double GetDoublePrecision(double dValue,int nPres=3);
};

