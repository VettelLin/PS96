// 【交接】 PCRInstanceLib\SerialPortPCR.h
// 作用：SerialPortPCR。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSerialPortPCR、GetByteSum、SendCommandRepeatedly、SetUserName、SetInstrumentSN、SetSendComment、GetComPort、OpenCom。
#pragma once
#include "LogDataInfo.h"

const int FRAMELENPARAM_INDEX = 3; ///帧长参数序号(从0开始)
const int  MAX_BLOCK = 1024; //缓冲区长度
const int  SENDTIMEOUT = 1000; //超时时间 
const int  RECEIVETIMEOUT = 3000; //接收超时

const BYTE PCR_UPSEND = 0x5e;
const BYTE PCR_DNSEND = 0x5e;
const BYTE PCR_0X80   = 0x80;

class AFX_EXT_CLASS CSerialPortPCR
{
public:
	// 函数 CSerialPortPCR
	// 作用：执行CSerialPortPCR。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CSerialPortPCR(void);
	// 函数 ~CSerialPortPCR
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CSerialPortPCR(void);

	enum eCmdReturn{
		RETURN_OK = 0,       // 应答OK
		RETURN_FAIL = 1,     // 应答失败
		RETURN_TIMEOUT = 2, // 超时
		RETURN_REPEAT_OUT = 3, // 超出规定次数失败
		RETURN_CKERROR = 4, // 收到数据校验错误
		RETURN_SEND_FAIL = 5, // 发送失败
	};

public:
	// 函数 GetByteSum
	// 作用：读取GetByteSum。
	// 参数：buf；length。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetComPort。
	BYTE GetByteSum(BYTE* buf, int length);

	// 函数 SendCommandRepeatedly
	// 作用：执行SendCommandRepeatedly。
	// 参数：pCommand：指针，指向调用方传入的对象；nCmdLength：整数；ppStatus；iStatusLength：整数；iFaultToleranceCount：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetComPort。
	int SendCommandRepeatedly(BYTE* pCommand,int nCmdLength,BYTE** ppStatus,int &iStatusLength,int iFaultToleranceCount = 3);

	// 函数 SetUserName
	// 作用：设置SetUserName。
	// 参数：strName：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetComPort。
	void SetUserName(CString strName);
	// 函数 SetInstrumentSN
	// 作用：设置SetInstrumentSN。
	// 参数：strSN：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetComPort。
	void SetInstrumentSN(CString strSN);
	// 函数 SetSendComment
	// 作用：设置SetSendComment。
	// 参数：strSend：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetComPort。
	void SetSendComment(CString strSend);

	// 函数 GetComPort
	// 作用：读取GetComPort。
	// 参数：无。
	// 返回：返回一段文字。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CString GetComPort() { return m_strPort;}

	// 函数 OpenCom
	// 作用：读入OpenCom。
	// 参数：nPort：整数。
	// 返回：返回是或否。
	BOOL OpenCom(int nPort);        
	// 函数 OpenCom
	// 作用：读入OpenCom。
	// 参数：strPort：字符串。
	// 返回：返回是或否。
	BOOL OpenCom(CString strPort);    
	// 函数 CloseCom
	// 作用：执行CloseCom。
	// 参数：无。
	// 返回：没有返回值。
	void CloseCom();      
	// 函数 SettingCom
	// 作用：设置SettingCom。
	// 参数：nBaudRate：整数。
	// 返回：返回是或否。
	BOOL SettingCom(int nBaudRate);	///< 设置串口参数 
	// 函数 ReadCommFixed
	// 作用：读取ReadCommFixed。
	// 参数：buf；dwLength。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	DWORD ReadCommFixed(BYTE* buf,DWORD dwLength);	///< 读取固定长度数据
	// 函数 SendCommand
	// 作用：执行SendCommand。
	// 参数：pchBuf；iLen：整数；iTime：整数。
	// 返回：返回是或否。
	BOOL SendCommand(BYTE* pchBuf,int iLen,int iTime);	///< 下发数据
	// 函数 ReadCom
	// 作用：读取ReadCom。
	// 参数：ppBuf；iFrameLen：整数；iTimeOut：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ReadCom(BYTE** ppBuf,int& iFrameLen,int iTimeOut); ///< 读取变长数据

	// 函数 Reset
	// 作用：更新或清除Reset。
	// 参数：无。
	// 返回：返回是或否。
	BOOL Reset();

protected:
	// 函数 SaveSendCommandLog
	// 作用：把SaveSendCommandLog写入文件、仪器或界面。
	// 参数：pCommand：指针，指向调用方传入的对象；nCmdLength：整数；iResult：整数；SendCount。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetSendTimeout。
	void SaveSendCommandLog(BYTE* pCommand, int nCmdLength, int iResult, int SendCount);
	// 函数 SaveReceiveCommandLog
	// 作用：把SaveReceiveCommandLog写入文件、仪器或界面。
	// 参数：pReceive：指针，指向调用方传入的对象；nLength：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetSendTimeout。
	void SaveReceiveCommandLog(BYTE* pReceive,int nLength);
	// 函数 HandleCommandReturn
	// 作用：执行HandleCommandReturn。
	// 参数：nReturn：整数；pCommand：指针，指向调用方传入的对象；nCmdLength：整数；nSendCount：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetSendTimeout。
	void HandleCommandReturn(int nReturn, BYTE* pCommand, int nCmdLength, int nSendCount);

private:
	// 函数 ConvertToString
	// 作用：执行ConvertToString。
	// 参数：pCommand：指针，指向调用方传入的对象；nCmdLength：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 SetSendTimeout。
	CString ConvertToString(BYTE* pCommand, int nCmdLength);
	
public:
	// 函数 SetSendTimeout
	// 作用：设置SetSendTimeout。
	// 参数：iTimeout：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSendTimeout(int iTimeout) { m_iSendTimeout = iTimeout; }
	// 函数 SetReceiveTimeout
	// 作用：设置SetReceiveTimeout。
	// 参数：iTimeout：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetReceiveTimeout(int iTimeout) { m_iReceiveTimeout = iTimeout; }
	// 函数 SetLongSendTime
	// 作用：设置SetLongSendTime。
	// 参数：bLong：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLongSendTime(BOOL bLong) { m_bLongSendTime = bLong; }
	// 函数 SetLongReceiveTime
	// 作用：设置SetLongReceiveTime。
	// 参数：bLong：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetLongReceiveTime(BOOL bLong) { m_bLongReceiveTime = bLong; }

protected:
	CRITICAL_SECTION m_csProtocol;
	int m_iSendTimeout; // 发送命令超时时间
	int m_iReceiveTimeout; // 结束数据超时时间
	BOOL m_bLongSendTime; // 是否使用长时间发送
	BOOL m_bLongReceiveTime; // 是否使用长时间接受

	CLogErrorInfo*	m_pLogError; // 错误或警告日志
	CLogCommInfo*	m_pLogComm; // 串口通讯记录日志

	CString m_strPort; //设备端口号 “COM N”
	HANDLE   m_hCommDev;	       ///< 设备句柄
	HANDLE   m_hWriteEvent;	       ///< 写事件句柄
	HANDLE   m_hReadEvent;         ///< 读事件句柄

	OVERLAPPED  m_CommWrite;	   ///<写重叠区
	OVERLAPPED  m_CommRead;	       ///<读重叠区

	unsigned char m_ucToleranceMaxVal;
	int m_nBaudRate;
	

private:
	BOOL m_bNormalCom;	//标识端口是否正常工作，20220822，孙文郎
};

