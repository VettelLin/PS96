// 【交接】 PCRInstanceLib\InstrumentPCR.h
// 作用：InstrumentPCR。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CInstrumentPCR、tagInstancePara、Empty、GetInstance、CleanUp、Initialize、Uninitialize、GetErrorCode。
#pragma once

#include "InstancePCR.h"
#include "SerialPortPCR.h"

class AFX_EXT_CLASS CInstrumentPCR
{
public:
	// 函数 CInstrumentPCR
	// 作用：执行CInstrumentPCR。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 tagInstancePara、Empty。
	CInstrumentPCR(void);
	// 函数 ~CInstrumentPCR
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 tagInstancePara、Empty。
	~CInstrumentPCR(void);

	struct tagInstancePara
	{
		CString		strPort;
		CInstancePCR*	pInstance; // 设备指针
		CString		strModel; // PCR仪型号
		CString		strSN; // 产品序列号
		CString		strCode; // PCR仪版本(类型)
		CString		strVersion; // 硬件版本
		CString		strSoftware; // 嵌入式软件版本
		tagInstancePara()
		{
			strPort.Empty();
			pInstance = NULL;
			strModel.Empty();
			strSN.Empty();
			strCode.Empty();
			strVersion.Empty();
			strSoftware.Empty();
		}
	};

public:
	// 函数 GetInstance
	// 作用：读取GetInstance。
	// 参数：无。
	// 返回：返回指针 CInstrumentPCR*。指针为空表示没有取到对象。
	// 过程：函数里会调用 GetInstanceCount、GetCount。
	static CInstrumentPCR* GetInstance(void);
	// 函数 CleanUp
	// 作用：执行CleanUp。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetInstanceCount、GetCount。
	static void CleanUp();

	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：strStartPath：字符串；bRecognizeAll：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetInstanceCount、GetCount。
	BOOL Initialize(CString strStartPath, BOOL bRecognizeAll=TRUE);
	// 函数 Uninitialize
	// 作用：执行Uninitialize。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetInstanceCount、GetCount。
	void Uninitialize();
	// 函数 GetErrorCode
	// 作用：读取GetErrorCode。
	// 参数：iErrPara1：整数；iErrPara2：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetInstanceCount、GetCount。
	UINT GetErrorCode(int &iErrPara1, int &iErrPara2);
	// 函数 Reinitialize
	// 作用：执行Reinitialize。
	// 参数：bRecognizeAll：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetInstanceCount、GetCount。
	BOOL Reinitialize(BOOL bRecognizeAll); // 0表示PS96

	// 函数 GetInstanceCount
	// 作用：读取GetInstanceCount。
	// 参数：m_arrayInstancePCR.GetCount(。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetCount。
	int GetInstanceCount() { return m_arrayInstancePCR.GetCount(); }
	// 函数 GetInstancePCR
	// 作用：读取GetInstancePCR。
	// 参数：strModel：字符串；strSN：字符串。
	// 返回：返回指针 CInstancePCR*。指针为空表示没有取到对象。
	// 过程：函数里会调用 SetMsgWnd。
	CInstancePCR* GetInstancePCR(CString strModel=_T(""), CString strSN=_T(""));
	// 函数 GetInstancePCR
	// 作用：读取GetInstancePCR。
	// 参数：iIndex：整数。
	// 返回：返回指针 CInstancePCR*。指针为空表示没有取到对象。
	// 过程：函数里会调用 SetMsgWnd。
	CInstancePCR* GetInstancePCR(int iIndex);
	// 函数 GetAvailableInstance
	// 作用：读取GetAvailableInstance。
	// 参数：无。
	// 返回：返回指针 CInstancePCR*。指针为空表示没有取到对象。
	// 过程：函数里会调用 SetMsgWnd。
	CInstancePCR* GetAvailableInstance();

	// 函数 CreateInstanceDemo
	// 作用：创建或加入CreateInstanceDemo。
	// 参数：strUser：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetMsgWnd。
	BOOL CreateInstanceDemo(CString strUser); // 创建虚拟仪器
	// 函数 SaveInstanceParaForDemo
	// 作用：把SaveInstanceParaForDemo写入文件、仪器或界面。
	// 参数：strIniFile：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetMsgWnd。
	void SaveInstanceParaForDemo(CString strIniFile);

	// 函数 IsExistIdleInstrument
	// 作用：判断IsExistIdleInstrument是否成立。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetMsgWnd。
	BOOL IsExistIdleInstrument();
	// 函数 SetMsgWnd
	// 作用：设置SetMsgWnd。
	// 参数：pWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetMsgWnd(CWnd* pWnd) { m_pMsgWnd = pWnd; }

protected:
	// 函数 GetComPort
	// 作用：读取GetComPort。
	// 参数：ComArray。
	// 返回：没有返回值。
	void GetComPort(CStringArray& ComArray);
	// 函数 InitCommPort_AutoRecognition
	// 作用：初始化InitCommPort_AutoRecognition。
	// 参数：bAppOrSer：是或否。
	// 返回：没有返回值。
	void InitCommPort_AutoRecognition(BOOL bAppOrSer); // 初始化通讯口 自动识别
	// 函数 ReadModelFromEEPROM
	// 作用：读取ReadModelFromEEPROM。
	// 参数：pComPort：指针，指向调用方传入的对象；pInsPara：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL ReadModelFromEEPROM(CSerialPortPCR* pComPort, tagInstancePara* pInsPara);
	// 函数 ReadEPROM
	// 作用：读取ReadEPROM。
	// 参数：pComPort：指针，指向调用方传入的对象；nAddress：整数；cLen；pReceive：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL ReadEPROM(CSerialPortPCR* pComPort, UINT nAddress,BYTE &cLen,BYTE** pReceive);
	// 函数 CreateInstancePCR
	// 作用：创建或加入CreateInstancePCR。
	// 参数：pComPort：指针，指向调用方传入的对象；pInputPara：指针，指向调用方传入的对象。
	// 返回：返回指针 CInstancePCR*。指针为空表示没有取到对象。
	CInstancePCR* CreateInstancePCR(CSerialPortPCR* pComPort, tagInstancePara* pInputPara);
	// 函数 SendHello
	// 作用：执行SendHello。
	// 参数：pComPort：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL SendHello(CSerialPortPCR* pComPort);

	// 函数 SaveCodeToPara
	// 作用：把SaveCodeToPara写入文件、仪器或界面。
	// 参数：pInsPara：指针，指向调用方传入的对象；pReceiveData：指针，指向调用方传入的对象；iFlag：整数。
	// 返回：没有返回值。
	void SaveCodeToPara(tagInstancePara* pInsPara, BYTE* pReceiveData, int iFlag);

	// 函数 PortHasUsed
	// 作用：执行PortHasUsed。
	// 参数：strPort：字符串。
	// 返回：返回是或否。
	BOOL PortHasUsed(CString strPort);

	// 函数 ReadUsedDeviceID
	// 作用：读取ReadUsedDeviceID。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	void ReadUsedDeviceID(CString strStartupPath);
	// 函数 SaveUsedDeviceID
	// 作用：把SaveUsedDeviceID写入文件、仪器或界面。
	// 参数：strStartupPath：字符串。
	// 返回：没有返回值。
	void SaveUsedDeviceID(CString strStartupPath);
	// 函数 SaveDeviceID
	// 作用：把SaveDeviceID写入文件、仪器或界面。
	// 参数：strID：字符串。
	// 返回：返回是或否。
	BOOL SaveDeviceID(CString strID);
	// 函数 ReadStringFromIniFile
	// 作用：读取ReadStringFromIniFile。
	// 参数：strAppName：字符串；strKeyName：字符串；strDefault：字符串；strIniFile：字符串。
	// 返回：返回一段文字。
	CString ReadStringFromIniFile(CString strAppName, CString strKeyName, CString strDefault, CString strIniFile);

protected:
	static CInstrumentPCR*	m_pInstrumentPCR;

	CString m_strStartPath;
	CWnd*	m_pMsgWnd;
	UINT m_uiErrorCode; // 错误码，方便外部判读错误类型
	int	m_iErrorPara1; // 错误参数 1/2 方便表明错误的详细信息
	int m_iErrorPara2;

	int m_iBandRate;
	int m_iResetTime;
	int m_iSTimeOutBase;
	CPtrArray	m_arrayInstancePCR;// 全部链接的PCR仪 CInstancePCR

	CStringArray m_arrayDeviceID;
};

