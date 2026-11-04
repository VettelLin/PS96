// 【交接】 Language\LanguageInfo.h
// 作用：LanguageInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CLanguageInfo、GetInstance、CleanUp、InitLanguageText、GetText、GetCapitalText、GetTextWithColon、GetCapitalTextWithColon。
#pragma once

#include <map>

typedef CArray<int, int> CIntArray;

using namespace std;

enum eLanguageUI
{
	LANGUAGE_CHS = 0, // 中文
	LANGUAGE_ENG, // 英语
};

#define LANGUAGEFILEEXT	_T("xlsx")	//存储各语言文本信息的文件后缀名
#define LANGUAGEFILE_TAG	_T("7760FC7D-893B-46E1-8409-9259B9F9950C")	//存储各语言文本信息的文件标识（excel第一个单元格内容）

// 语言信息数据
class AFX_EXT_CLASS CLanguageInfo
{
public:
	// 函数 CLanguageInfo
	// 作用：执行CLanguageInfo。
	// 参数：无。
	// 返回：没有返回值。
	CLanguageInfo(void);
	// 函数 ~CLanguageInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLanguageInfo(void);

// Operations
public:
	// 函数 GetInstance
	// 作用：读取GetInstance。
	// 参数：无。
	// 返回：返回指针 CLanguageInfo*。指针为空表示没有取到对象。
	static CLanguageInfo* GetInstance(void);
	// 函数 CleanUp
	// 作用：执行CleanUp。
	// 参数：无。
	// 返回：没有返回值。
	static void CleanUp();

	// 函数 InitLanguageText
	// 作用：初始化InitLanguageText。
	// 参数：strPath：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetLanguage。
	int InitLanguageText(CString strPath);	//从文件中读取各语言文本内容 
	// 函数 GetText
	// 作用：读取GetText。
	// 参数：iId：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetLanguage。
	CString GetText(int iId);	//从映射对象中查询文本信息
	// 函数 GetText
	// 作用：读取GetText。
	// 参数：iId：整数；eLanguage。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetLanguage。
	CString GetText(int iId, eLanguageUI eLanguage);
	// 函数 GetCapitalText
	// 作用：读取GetCapitalText。
	// 参数：iId：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetLanguage。
	CString GetCapitalText(int iId); // 读取英文的大写拼写字符串，中文忽略
	// 函数 GetTextWithColon
	// 作用：读取GetTextWithColon。
	// 参数：iID：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetLanguage。
	CString GetTextWithColon(int iID);
	// 函数 GetTextWithColon
	// 作用：读取GetTextWithColon。
	// 参数：iId：整数；eLanguage。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetLanguage。
	CString GetTextWithColon(int iId, eLanguageUI eLanguage);
	// 函数 GetCapitalTextWithColon
	// 作用：读取GetCapitalTextWithColon。
	// 参数：iId：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetLanguage。
	CString GetCapitalTextWithColon(int iId);

	// 函数 SetLanguage
	// 作用：设置SetLanguage。
	// 参数：nLanguage：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLanguage(eLanguageUI nLanguage) { m_nLanguage = nLanguage; }
	// 函数 GetLanguage
	// 作用：读取GetLanguage。
	// 参数：无。
	// 返回：返回 eLanguageUI。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	eLanguageUI GetLanguage(){return m_nLanguage;}

	// 函数 GetBeEnglish
	// 作用：读取GetBeEnglish。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeEnglish();
	// 函数 ConvertTo
	// 作用：执行ConvertTo。
	// 参数：strInput：字符串；eLanguage。
	// 返回：返回一段文字。
	CString ConvertTo(CString strInput, eLanguageUI eLanguage);

protected:
	static CLanguageInfo* m_pInstance;
	CIntArray	m_arrayIndex;
	eLanguageUI	m_nLanguage; // 使用的语言
	map<int,CString> m_mapIdToChinese;	//使用映射保存中文信息
	map<int,CString> m_mapIdToEnglish;	//使用映射保存英文信息
};

