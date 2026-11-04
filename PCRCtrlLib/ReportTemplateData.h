// 【交接】 PCRCtrlLib\ReportTemplateData.h
// 作用：ReportTemplateData。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CReportTemplateData、tagTemplate、Empty、SetStartupPath、DeleteAll、SaveFile、OpenFile、GetTemplateCount。
#pragma once


class AFX_EXT_CLASS CReportTemplateData
{
public:
	// 函数 CReportTemplateData
	// 作用：执行CReportTemplateData。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CReportTemplateData(void);
	// 函数 ~CReportTemplateData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CReportTemplateData(void);

	enum eDataFlag
	{
		DATA_NAME = 0,
		DATA_LAB_NAME,
		DATA_ADDRESS,
		DATA_CONTACT_URL,
		DATA_CONTACT_EMAIL,
		DATA_CONTACT_PHONE,
		DATA_TEST_NAME,
		DATA_DISCLAIMER,
		DATA_LOGO_FILE,
	};

	struct tagTemplate
	{
		CString		strName;
		CString		strLabName;
		CString		strLabAddress;
		CString		strContactUrl;
		CString		strContactEmail;
		CString		strContactPhone;
		CString		strTestName; //
		CString		strDisclaimer; // 免责声明
		CString		strLogoFile; // 机构LOGO
		tagTemplate()
		{
			strName.Empty();
			strLabName.Empty();
			strLabAddress.Empty();
			strContactUrl.Empty();
			strContactEmail.Empty();
			strContactPhone.Empty();
			strTestName.Empty();
			strDisclaimer.Empty();
			strLogoFile.Empty();
		}
	};

public:
	// 函数 SetStartupPath
	// 作用：设置SetStartupPath。
	// 参数：strPath：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTemplateCount、GetCount。
	void SetStartupPath(CString strPath);
	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetTemplateCount、GetCount。
	void DeleteAll();

	// 函数 SaveFile
	// 作用：把SaveFile写入文件、仪器或界面。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetTemplateCount、GetCount。
	BOOL SaveFile();
	// 函数 OpenFile
	// 作用：读入OpenFile。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetTemplateCount、GetCount。
	BOOL OpenFile();
	// 函数 SaveFile
	// 作用：把SaveFile写入文件、仪器或界面。
	// 参数：strFilePath：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetTemplateCount、GetCount。
	BOOL SaveFile(CString strFilePath);
	// 函数 OpenFile
	// 作用：读入OpenFile。
	// 参数：strFilePath：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetTemplateCount、GetCount。
	BOOL OpenFile(CString strFilePath);

	// 函数 GetTemplateCount
	// 作用：读取GetTemplateCount。
	// 参数：m_arrayTemplate.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetTemplateCount() { return m_arrayTemplate.GetCount(); }

	// 函数 AddTemplate
	// 作用：创建或加入AddTemplate。
	// 参数：nFlag：整数；string：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCurSel。
	int AddTemplate(eDataFlag nFlag, CString string);
	// 函数 DeleteTemplate
	// 作用：更新或清除DeleteTemplate。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSel。
	void DeleteTemplate(int iIndex);
	// 函数 AddTemplate
	// 作用：创建或加入AddTemplate。
	// 参数：pInputTemplate：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCurSel。
	int AddTemplate(tagTemplate* pInputTemplate);
	// 函数 GetTemplate
	// 作用：读取GetTemplate。
	// 参数：iIndex：整数。
	// 返回：返回指针 tagTemplate*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetCurSel。
	tagTemplate* GetTemplate(int iIndex);

	// 函数 GetStringBy
	// 作用：读取GetStringBy。
	// 参数：nFlag：整数；iIndex：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 GetCurSel。
	CString GetStringBy(eDataFlag nFlag, int iIndex=-1);
	// 函数 SetStringTo
	// 作用：设置SetStringTo。
	// 参数：nFlag：整数；string：字符串；iIndex：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCurSel。
	void SetStringTo(eDataFlag nFlag, CString string, int iIndex=-1);

	// 函数 GetCurSel
	// 作用：读取GetCurSel。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCurSel() { return m_iUsedIndex; }
	// 函数 SetCurSel
	// 作用：设置SetCurSel。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetCurSel(int iIndex) { m_iUsedIndex = iIndex; }
	// 函数 SetCurSel
	// 作用：设置SetCurSel。
	// 参数：strName：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetChanged。
	void SetCurSel(CString strName);

	// 函数 SetChanged
	// 作用：设置SetChanged。
	// 参数：bChanged：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetChanged(BOOL bChanged) { m_bChanged = bChanged; }
	// 函数 GetChanged
	// 作用：读取GetChanged。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetChanged() { return m_bChanged;}

	// 函数 CopyTo
	// 作用：复制CopyTo。
	// 参数：pTargetData：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void CopyTo(CReportTemplateData* pTargetData);
	// 函数 CopyFrom
	// 作用：复制CopyFrom。
	// 参数：pSourceData：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void CopyFrom(CReportTemplateData* pSourceData);

	// 函数 FindSameName
	// 作用：执行FindSameName。
	// 参数：strName：字符串。
	// 返回：返回是或否。
	BOOL FindSameName(CString strName);

protected:
	// 函数 GetStringBy
	// 作用：读取GetStringBy。
	// 参数：pTemplate：指针，指向调用方传入的对象；nFlag：整数。
	// 返回：返回一段文字。
	CString GetStringBy(tagTemplate* pTemplate, eDataFlag nFlag);
	// 函数 SetStringTo
	// 作用：设置SetStringTo。
	// 参数：pTemplate：指针，指向调用方传入的对象；nFlag：整数；string：字符串。
	// 返回：没有返回值。
	void SetStringTo(tagTemplate* pTemplate, eDataFlag nFlag, CString string);

protected:
	WORD	m_wFileFlag; // 文件标识码
	WORD	m_wFileVersion; // 文件版本

	CString m_strFilePath;

	int	m_iUsedIndex;
	CPtrArray	m_arrayTemplate;

	BOOL m_bChanged;
};

