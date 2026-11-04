// 【交接】 GeneralPcr\PowerOffProtect.cpp
// 作用：断电保护。按仪器序列号记录未完成实验，再次开机时提示是否续跑。
// 先看这些函数：CPowerOffProtect、CreateEvent、Empty、_T、CloseHandle、close、InitPowerOffProtect、SetRunProgress。
#include "StdAfx.h"
#include "PowerOffProtect.h"

// 函数 CPowerOffProtect::CPowerOffProtect
// 作用：执行CPowerOffProtect。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CreateEvent、Empty、_T。
CPowerOffProtect::CPowerOffProtect(void)
{
	m_bProtectWork = FALSE;
	m_iFileTag = 0X6969;
	m_hSyncLnk = CreateEvent(NULL,FALSE,TRUE,NULL);
	if(NULL != m_hSyncLnk)
	{
		m_bProtectWork = TRUE;
	}
	m_strFileDir.Empty();
	m_strFileName = _T("POPROTECT.po");
	m_strFilePath.Empty();
}

// 函数 CPowerOffProtect::~CPowerOffProtect
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CloseHandle、is_open、close。
CPowerOffProtect::~CPowerOffProtect(void)
{
	if(NULL != m_hSyncLnk)
	{
		CloseHandle(m_hSyncLnk);
		m_hSyncLnk = NULL;
	}

	if(m_fs.is_open())
	{
		m_fs.close();
	}
}

// 函数 CPowerOffProtect::InitPowerOffProtect
// 作用：初始化InitPowerOffProtect。
// 参数：strPath：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 IsEmpty、ReadFile。
int CPowerOffProtect::InitPowerOffProtect(CString strPath)
{
	if(strPath.IsEmpty())
	{
		return -1;
	}

	m_strFileDir = strPath;
	m_strFilePath = m_strFileDir + m_strFileName;

	if(ReadFile() < 0)
	{
		return -3;
	}

	return 0;
}

// 函数 CPowerOffProtect::SetRunProgress
// 作用：设置SetRunProgress。
// 参数：iPageId：整数；iSegId：整数；iStepId：整数；iCycleId：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 WaitForSingleObject、GetHead、SaveFile、SetEvent。
int CPowerOffProtect::SetRunProgress(int iPageId,int iSegId,int iStepId,int iCycleId)
{
	if(!m_bProtectWork)
	{
		return -1;
	}

	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncLnk,INFINITE))
	{
		return -2;
	}

	BOOL bFind = FALSE;
	Node<CRunProgressRecord>* pNode = m_lnkRunPrgRcd.GetHead();
	while(NULL != pNode)
	{
		if(iPageId == pNode->data.m_iPageId)
		{
			pNode->data.m_iSegId = iSegId;
			pNode->data.m_iStepId = iStepId;
			pNode->data.m_iCycleId = iCycleId;
			SaveFile();
			bFind = TRUE;
			break;
		}
		pNode = pNode->pNext;
	}

	SetEvent(m_hSyncLnk);

	if(!bFind)
	{
		return -3;	
	}
	
	return 0;
}

// 函数 CPowerOffProtect::SetRunProgress
// 作用：设置SetRunProgress。
// 参数：iPageId：整数；fMeltTem：小数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 WaitForSingleObject、GetHead、SaveFile、SetEvent。
int CPowerOffProtect::SetRunProgress(int iPageId,float fMeltTem)
{
	if(!m_bProtectWork)
	{
		return -1;
	}

	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncLnk,INFINITE))
	{
		return -2;
	}

	BOOL bFind = FALSE;
	Node<CRunProgressRecord>* pNode = m_lnkRunPrgRcd.GetHead();
	while(NULL != pNode)
	{
		if(iPageId == pNode->data.m_iPageId)
		{
			pNode->data.m_fPowerOffTem = fMeltTem;
			SaveFile();
			bFind = TRUE;
			break;
		}
		pNode = pNode->pNext;
	}

	SetEvent(m_hSyncLnk);

	if(!bFind)
	{
		return -3;	
	}

	return 0;
}

// 函数 CPowerOffProtect::AddRunProgress
// 作用：创建或加入AddRunProgress。
// 参数：runPrgRcd。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 WaitForSingleObject、AddTail、SaveFile、SetEvent。
int CPowerOffProtect::AddRunProgress(CRunProgressRecord& runPrgRcd)
{
	if(!m_bProtectWork)
	{
		return -1;
	}

	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncLnk,INFINITE))
	{
		return -2;
	}

	m_lnkRunPrgRcd.AddTail(runPrgRcd);
	SaveFile();

	SetEvent(m_hSyncLnk);

	return 0;
}

// 函数 CPowerOffProtect::DeleteRunProgress
// 作用：更新或清除DeleteRunProgress。
// 参数：iPageId：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 WaitForSingleObject、GetHead、DeleteNode、SaveFile、SetEvent。
int CPowerOffProtect::DeleteRunProgress(int iPageId)
{
	if(!m_bProtectWork)
	{
		return -1;
	}

	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncLnk,INFINITE))
	{
		return -2;
	}

	BOOL bFind = FALSE;
	Node<CRunProgressRecord>* pNode = m_lnkRunPrgRcd.GetHead();
	while(NULL != pNode)
	{
		if(iPageId == pNode->data.m_iPageId)
		{
			m_lnkRunPrgRcd.DeleteNode(pNode);
			SaveFile();
			bFind = TRUE;
			break;
		}
		pNode = pNode->pNext;
	}

	SetEvent(m_hSyncLnk);

	if(!bFind)
	{
		return 1;	
	}

	return 0;
}

// 函数 CPowerOffProtect::DeleteOldProgress
// 作用：更新或清除DeleteOldProgress。
// 参数：iLnkIndex：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize、WaitForSingleObject、GetAt、DeleteNode、SaveFile、SetEvent。
int CPowerOffProtect::DeleteOldProgress(int iLnkIndex)
{
	if(!m_bProtectWork)
	{
		return -1;
	}

	if(iLnkIndex < 0)
	{
		return -2;
	}

	if(iLnkIndex >= m_lnkRunPrgRcd.GetSize())
	{
		return -3;
	}

	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncLnk,INFINITE))
	{
		return -4;
	}

	Node<CRunProgressRecord>* pNode = m_lnkRunPrgRcd.GetAt(iLnkIndex);
	if(NULL != pNode)
	{
		m_lnkRunPrgRcd.DeleteNode(pNode);
		SaveFile();
	}

	SetEvent(m_hSyncLnk);

	return 0;
}

// 函数 CPowerOffProtect::SearchPowerOffProtect
// 作用：执行SearchPowerOffProtect。
// 参数：strSN：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 WaitForSingleObject、GetHead、SetEvent。
int CPowerOffProtect::SearchPowerOffProtect(CString strSN)
{
	int iIndex = -1;
	if(WAIT_OBJECT_0 != WaitForSingleObject(m_hSyncLnk,INFINITE))
	{
		return iIndex;
	}

	Node<CRunProgressRecord>* pNode = m_lnkRunPrgRcd.GetHead();
	while(NULL != pNode)
	{
		++iIndex;
		if(strSN == pNode->data.m_strSN)
		{
			goto END;
		}
		pNode = pNode->pNext;
	}

END:
	SetEvent(m_hSyncLnk);

	return iIndex;
}

// 函数 CPowerOffProtect::GetRunProgressRecord
// 作用：读取GetRunProgressRecord。
// 参数：iIndex：整数；runPrjRcd。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetSize。
int CPowerOffProtect::GetRunProgressRecord(int iIndex,CRunProgressRecord& runPrjRcd)
{
	if(iIndex < 0)
	{
		return -1;
	}
	if(iIndex >= m_lnkRunPrgRcd.GetSize())
	{
		return -2;
	}
	runPrjRcd = *m_lnkRunPrgRcd[iIndex];

	return 0;
}

// 函数 CPowerOffProtect::ReadFile
// 作用：读取ReadFile。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 ifs、is_open、read、Clear、ReadString、AddTail。
int CPowerOffProtect::ReadFile()
{
	ifstream ifs(m_strFilePath);
	if(!ifs.is_open())
	{
		return -1;
	}

	int iRet = 0;

	int iFileTag = 0;
	ifs.read((char*)&iFileTag,sizeof(int));
	if(iFileTag != m_iFileTag)
	{
		iRet = -2;
		goto END;
	}

	m_lnkRunPrgRcd.Clear();

	int iRcdNum = 0;
	ifs.read((char*)&iRcdNum,sizeof(int));
	if(iRcdNum < 1)
	{
		iRet = 1;
		goto END;
	}

	for(int i = 0;i < iRcdNum;++i)
	{
		CRunProgressRecord runPrgRcd;
		ifs.read((char*)&runPrgRcd.m_iSegId,sizeof(int));
		ifs.read((char*)&runPrgRcd.m_iStepId,sizeof(int));
		ifs.read((char*)&runPrgRcd.m_iCycleId,sizeof(int));

		ifs.read((char*)&runPrgRcd.m_ttStart,sizeof(time_t));
		ifs.read((char*)&runPrgRcd.m_fMeltStartTem,sizeof(float));
		ifs.read((char*)&runPrgRcd.m_fMeltEndTem,sizeof(float));
		ifs.read((char*)&runPrgRcd.m_fPowerOffTem,sizeof(float));

		ReadString(ifs,runPrgRcd.m_strFilePath);
		ReadString(ifs,runPrgRcd.m_strSN);

		m_lnkRunPrgRcd.AddTail(runPrgRcd);
	}

END:
	ifs.close();
	return iRet;
}

// 函数 CPowerOffProtect::SaveFile
// 作用：把SaveFile写入文件、仪器或界面。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 open、is_open、write、GetSize、GetHead、WriteString。
int CPowerOffProtect::SaveFile()
{
	if(!m_bProtectWork)
	{
		return -1;
	}

	m_fs.open(m_strFilePath,ios::out | ios::trunc | ios::binary);
	if(!m_fs.is_open())
	{
		return -2;
	}

	m_fs.write((const char*)&m_iFileTag,sizeof(int));

	int iRcdNum = m_lnkRunPrgRcd.GetSize();
	m_fs.write((const char*)&iRcdNum,sizeof(int));
	
	int iStrLen = 0;
	Node<CRunProgressRecord>* pNode = m_lnkRunPrgRcd.GetHead();
	while(NULL != pNode)
	{
		m_fs.write((const char*)&pNode->data.m_iSegId,sizeof(int));
		m_fs.write((const char*)&pNode->data.m_iStepId,sizeof(int));
		m_fs.write((const char*)&pNode->data.m_iCycleId,sizeof(int));
		
		m_fs.write((const char*)&pNode->data.m_ttStart,sizeof(time_t));
		m_fs.write((const char*)&pNode->data.m_fMeltStartTem,sizeof(float));
		m_fs.write((const char*)&pNode->data.m_fMeltEndTem,sizeof(float));
		m_fs.write((const char*)&pNode->data.m_fPowerOffTem,sizeof(float));

		WriteString(pNode->data.m_strFilePath);
		WriteString(pNode->data.m_strSN);

		pNode = pNode->pNext;
	}

	m_fs.close();

	return 0;
}

// 函数 CPowerOffProtect::WriteString
// 作用：把WriteString写入文件、仪器或界面。
// 参数：strText：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 is_open、GetLength、write、GetBuffer。
int CPowerOffProtect::WriteString(CString& strText)
{
	if(!m_fs.is_open())
	{
		return -1;
	}

	int iStrLen = 0;
	iStrLen = strText.GetLength();
	m_fs.write((const char *)&iStrLen,sizeof(int));
	if(iStrLen > 0)
	{
		m_fs.write((const char *)(strText.GetBuffer()),sizeof(TCHAR) * iStrLen);
	}

	return 0;
}

// 函数 CPowerOffProtect::ReadString
// 作用：读取ReadString。
// 参数：ifs；strText：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 is_open、read。
int CPowerOffProtect::ReadString(ifstream& ifs,CString& strText)
{
	if(!ifs.is_open())
	{
		return -1;
	}

	int iStrLen = 0;
	TCHAR lpTStr[1024] = {0};

	ifs.read((char *)&iStrLen,sizeof(int));
	if(iStrLen > 0)
	{
		ifs.read((char*)lpTStr,sizeof(TCHAR) * iStrLen);
		lpTStr[iStrLen] = 0;
		strText = lpTStr;
	}

	return 0;
}


