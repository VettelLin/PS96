// 【交接】 GeneralPcr\StdProc.cpp
// 作用：StdProc。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CStdLineTag、CStdLine、clear、size、push_back、LinearFit、CalculateAverageDot、Clear。
#include "StdAfx.h"
#include "StdProc.h"

// 函数 CStdLineTag::CStdLineTag
// 作用：执行CStdLineTag。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStdLineTag::CStdLineTag()
{
	m_iChanId = 1;
}

// 函数 CStdLineTag::~CStdLineTag
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStdLineTag::~CStdLineTag()
{

}

// 函数 CStdLineTag::CStdLineTag
// 作用：执行CStdLineTag。
// 参数：stdLineTag。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStdLineTag::CStdLineTag(const CStdLineTag& stdLineTag)
{
	m_iChanId = stdLineTag.m_iChanId;
}

void CStdLineTag::operator=(const CStdLineTag& stdLineTag)
{
	m_iChanId = stdLineTag.m_iChanId;
}

BOOL CStdLineTag::operator==(const CStdLineTag& stdLineTag)
{
	return m_iChanId == stdLineTag.m_iChanId;
}

// 函数 CStdLine::CStdLine
// 作用：执行CStdLine。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStdLine::CStdLine()
{
	m_dEfficiency = 0; 
}

// 函数 CStdLine::~CStdLine
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStdLine::~CStdLine()
{

}

// 函数 CStdLine::CStdLine
// 作用：执行CStdLine。
// 参数：stdLine。
// 返回：没有返回值。
// 过程：函数里会调用 clear、size、push_back。
CStdLine::CStdLine(const CStdLine& stdLine)
{
	m_vecDensity.clear();
	m_2vecCt.clear();

	m_stdLineTag = stdLine.m_stdLineTag;
	int densityNum = stdLine.m_vecDensity.size();
	if(densityNum > 0)
	{
		for(int i = 0;i < densityNum;++i)
		{
			m_vecDensity.push_back(stdLine.m_vecDensity[i]);
			m_2vecCt.push_back(stdLine.m_2vecCt[i]);
		}
	}

	m_linearFitData = stdLine.m_linearFitData;
	m_dEfficiency = stdLine.m_dEfficiency;
}

void CStdLine::operator=(CStdLine& stdLine)
{
	m_vecDensity.clear();
	m_2vecCt.clear();

	m_stdLineTag = stdLine.m_stdLineTag;
	int densityNum = stdLine.m_vecDensity.size();
	if(densityNum > 0)
	{
		for(int i = 0;i < densityNum;++i)
		{
			m_vecDensity.push_back(stdLine.m_vecDensity[i]);
			m_2vecCt.push_back(stdLine.m_2vecCt[i]);
		}
	}

	m_linearFitData = stdLine.m_linearFitData;
	m_dEfficiency = stdLine.m_dEfficiency;
}

// 函数 CStdLine::LinearFit
// 作用：执行LinearFit。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CalculateAverageDot、LeastSquare。
int CStdLine::LinearFit()
{
	if(0 != CalculateAverageDot())
	{
		return -1;
	}

	if(0 != m_linearFitData.LeastSquare())
	{
		return -2;
	}
	return 0;
}

// 函数 CStdLine::CalculateAverageDot
// 作用：计算CalculateAverageDot。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size、SetDataNum。
int CStdLine::CalculateAverageDot()
{
	int iDensityNum = m_vecDensity.size();
	if(iDensityNum < 1)
	{
		return -1;
	}

	if(iDensityNum != m_2vecCt.size())
	{
		return -2;
	}

	if(0 != m_linearFitData.SetDataNum(iDensityNum))
	{
		return -3;
	}

	double dSum = 0;
	int iCtNum = 0;
	
	for(int i = 0;i < iDensityNum;++i)
	{
		dSum = 0;
		m_linearFitData.m_pDX[i] = m_vecDensity[i];
		iCtNum = m_2vecCt[i].size();
		for(int j = 0;j < iCtNum;++j)
		{
			dSum += m_2vecCt[i][j];
		}
		if(0 != iCtNum)
		{
			m_linearFitData.m_pDY[i] = dSum / iCtNum;
		}
		else
		{
			m_linearFitData.m_pDY[i] = 0;
		}
	}

	return 0;
}

// 函数 CStdLine::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 clear。
void CStdLine::Clear()
{
	m_vecDensity.clear();
	m_2vecCt.clear();
}

// 函数 CStdProc::CStdProc
// 作用：执行CStdProc。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStdProc::CStdProc(void)
{
}


// 函数 CStdProc::~CStdProc
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CStdProc::~CStdProc(void)
{
}

// 函数 CStdProc::AddPoint
// 作用：创建或加入AddPoint。
// 参数：stdLineTag；dX：小数；dY：小数。
// 返回：没有返回值。
// 过程：函数里会调用 size、push_back。
void CStdProc::AddPoint(CStdLineTag stdLineTag,double dX,double dY)
{
	int iStdLineNum = m_vecStdLine.size();
	int iStadLineIndex = 0;
	BOOL bFindStdLine = FALSE;
	if(iStdLineNum > 0)
	{
		for(int k = 0;k < iStdLineNum;++k)
		{
			if(stdLineTag == m_vecStdLine[k].m_stdLineTag)
			{
				iStadLineIndex = k;
				bFindStdLine = TRUE;
				break;
			}
		}
	}

	if(bFindStdLine)
	{
		int iDensityNum = m_vecStdLine[iStadLineIndex].m_vecDensity.size();
		BOOL bFind = FALSE;
		int iDotIndex = 0;
		for(int i = 0;i < iDensityNum;++i)
		{
			if(dX == m_vecStdLine[iStadLineIndex].m_vecDensity[i])
			{
				bFind = TRUE;
				iDotIndex = i;
				break;
			}
		}

		if(bFind)
		{
			m_vecStdLine[iStadLineIndex].m_2vecCt[iDotIndex].push_back(dY);
		}
		else
		{
			m_vecStdLine[iStadLineIndex].m_vecDensity.push_back(dX);
			vector<double> vecCt;
			vecCt.push_back(dY);
			m_vecStdLine[iStadLineIndex].m_2vecCt.push_back(vecCt);
		}
	}
	else
	{
		CStdLine stdLine;
		stdLine.m_stdLineTag = stdLineTag;
		stdLine.m_vecDensity.push_back(dX);
		vector<double> vecCt;
		vecCt.push_back(dY);
		stdLine.m_2vecCt.push_back(vecCt);
		m_vecStdLine.push_back(stdLine);
	}

	return;
}

// 函数 CStdProc::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 clear。
void CStdProc::Clear()
{
	m_vecStdLine.clear();
}

// 函数 CStdProc::DeleteOneStdLine
// 作用：更新或清除DeleteOneStdLine。
// 参数：stdLineTag。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 begin、end、erase。
int CStdProc::DeleteOneStdLine(CStdLineTag stdLineTag)
{
	for(vector<CStdLine>::iterator it = m_vecStdLine.begin();it != m_vecStdLine.end();++it)
	{
		if(stdLineTag == it->m_stdLineTag)
		{
			m_vecStdLine.erase(it);
			return 0;
		}
	}

	return 1;
}

// 函数 CStdProc::GetStdLinePtr
// 作用：读取GetStdLinePtr。
// 参数：stdLineTag。
// 返回：返回指针 CStdLine*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：函数里会调用 size。
CStdLine* CStdProc::GetStdLinePtr(CStdLineTag stdLineTag)
{
	for(int i = 0;i < m_vecStdLine.size();++i)
	{
		if(stdLineTag == m_vecStdLine[i].m_stdLineTag)
		{
			return &(m_vecStdLine[i]);
		}
	}
	return NULL;
}

// 函数 CStdProc::GetStdLinePtr
// 作用：读取GetStdLinePtr。
// 参数：iIndex：整数。
// 返回：返回指针 CStdLine*。指针为空表示没有取到对象。取不到时返回空指针。
// 过程：函数里会调用 size。
CStdLine* CStdProc::GetStdLinePtr(int iIndex)
{
	if(iIndex < 0 || iIndex >= m_vecStdLine.size())
	{
		return NULL;
	}
	return &(m_vecStdLine[iIndex]);
}

// 函数 CStdProc::GetStdLineNum
// 作用：读取GetStdLineNum。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
int CStdProc::GetStdLineNum()
{
	return m_vecStdLine.size();
}

// 函数 CStdProc::Fit
// 作用：执行Fit。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 size、LinearFit。
void CStdProc::Fit()
{
	for(int i = 0;i < m_vecStdLine.size();++i)
	{
		m_vecStdLine[i].LinearFit();
	}
	return;
}





