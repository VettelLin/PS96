// 【交接】 GeneralPcr\TemplateFileInfo.h
// 作用：TemplateFileInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTemplateFileInfo、IsFileExist。
#pragma once
class CTemplateFileInfo
{
public:
	// 函数 CTemplateFileInfo
	// 作用：执行CTemplateFileInfo。
	// 参数：无。
	// 返回：没有返回值。
	CTemplateFileInfo(void);
	// 函数 ~CTemplateFileInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CTemplateFileInfo(void);

	// 函数 CTemplateFileInfo
	// 作用：执行CTemplateFileInfo。
	// 参数：info。
	// 返回：没有返回值。
	CTemplateFileInfo(const CTemplateFileInfo& info);
	void operator=(const CTemplateFileInfo& info);

	// 函数 IsFileExist
	// 作用：判断IsFileExist是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsFileExist();

public:
	CString m_strFilePath;
	CString m_strFileName;
	CString m_strTitle;
};

