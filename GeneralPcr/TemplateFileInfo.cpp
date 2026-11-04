// 【交接】 GeneralPcr\TemplateFileInfo.cpp
// 作用：TemplateFileInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTemplateFileInfo、Empty、IsFileExist、FindFile。
#include "StdAfx.h"
#include "TemplateFileInfo.h"

// 函数 CTemplateFileInfo::CTemplateFileInfo
// 作用：执行CTemplateFileInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Empty。
CTemplateFileInfo::CTemplateFileInfo(void)
{
	m_strFilePath.Empty();
	m_strFileName.Empty();
	m_strTitle.Empty();
}

// 函数 CTemplateFileInfo::~CTemplateFileInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTemplateFileInfo::~CTemplateFileInfo(void)
{

}

// 函数 CTemplateFileInfo::CTemplateFileInfo
// 作用：执行CTemplateFileInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTemplateFileInfo::CTemplateFileInfo(const CTemplateFileInfo& info)
{
	m_strFilePath = info.m_strFilePath;
	m_strFileName = info.m_strFileName;
	m_strTitle = info.m_strTitle;
}

void CTemplateFileInfo::operator=(const CTemplateFileInfo& info)
{
	m_strFilePath = info.m_strFilePath;
	m_strFileName = info.m_strFileName;
	m_strTitle = info.m_strTitle;
}

// 函数 CTemplateFileInfo::IsFileExist
// 作用：判断IsFileExist是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 FindFile。
BOOL CTemplateFileInfo::IsFileExist()
{
	CFileFind fileFind;
	return fileFind.FindFile(m_strFilePath);
}




