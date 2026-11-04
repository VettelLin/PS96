// 【交接】 GeneralPcr\LinearFitData.cpp
// 作用：LinearFitData 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CLinearFitData、Clear、SetDataNum、LeastSquare、abs、sqrt。
#include "StdAfx.h"
#include "LinearFitData.h"


// 函数 CLinearFitData::CLinearFitData
// 作用：执行CLinearFitData。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLinearFitData::CLinearFitData(void)
{
	m_pDX = NULL;
	m_pDY = NULL;
	m_dSlope = 0;
	m_dIntercept = 0;
	m_dSquare = 0;
	m_iDataNum = 0;
}

// 函数 CLinearFitData::~CLinearFitData
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Clear。
CLinearFitData::~CLinearFitData(void)
{
	Clear();
}

// 函数 CLinearFitData::CLinearFitData
// 作用：执行CLinearFitData。
// 参数：data。
// 返回：没有返回值。
// 过程：函数里会调用 Clear。
CLinearFitData::CLinearFitData(const CLinearFitData& data)
{
	if(data.m_iDataNum < 1)
	{
		Clear();
		return;
	}

	if(m_iDataNum != data.m_iDataNum)
	{
		Clear();
		m_iDataNum = data.m_iDataNum;
		m_pDX = new double[m_iDataNum];
		if(NULL == m_pDX)
		{
			return;
		}
		m_pDY = new double[m_iDataNum];
		if(NULL == m_pDY)
		{
			delete [] m_pDX;
			return;
		}
	}

	for(int i = 0;i < m_iDataNum;++i)
	{
		m_pDX[i] = data.m_pDX[i];
		m_pDY[i] = data.m_pDY[i]; 
	}

	m_dSlope = data.m_dSlope;
	m_dIntercept = data.m_dIntercept;
	m_dSquare = data.m_dSquare;
}

void CLinearFitData::operator=(const CLinearFitData& data)
{
	if(data.m_iDataNum < 1)
	{
		Clear();
		return;
	}

	if(m_iDataNum != data.m_iDataNum)
	{
		Clear();
		m_iDataNum = data.m_iDataNum;
		m_pDX = new double[m_iDataNum];
		if(NULL == m_pDX)
		{
			return;
		}
		m_pDY = new double[m_iDataNum];
		if(NULL == m_pDY)
		{
			delete [] m_pDX;
			return;
		}
	}
	
	for(int i = 0;i < m_iDataNum;++i)
	{
		m_pDX[i] = data.m_pDX[i];
		m_pDY[i] = data.m_pDY[i]; 
	}

	m_dSlope = data.m_dSlope;
	m_dIntercept = data.m_dIntercept;
	m_dSquare = data.m_dSquare;
}

BOOL CLinearFitData::operator==(const CLinearFitData& data)
{
	if(m_iDataNum != data.m_iDataNum)
	{
		return FALSE;
	}
	if(0 == m_iDataNum)
	{
		return TRUE;
	}

	for(int i = 0;i < m_iDataNum;++i)
	{
		if(m_pDX[i] != data.m_pDX[i])
		{
			return FALSE;
		}
		if(m_pDY[i] != data.m_pDY[i])
		{
			return FALSE;
		}
	}

	return m_dSlope == data.m_dSlope &&
	m_dIntercept == data.m_dIntercept &&
	m_dSquare == data.m_dSquare;
}

// 函数 CLinearFitData::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CLinearFitData::Clear()
{
	if(NULL != m_pDX)
	{
		delete [] m_pDX;
		m_pDX = NULL;
	}
	if(NULL != m_pDY)
	{
		delete [] m_pDY;
		m_pDY = NULL;
	}
	m_dSlope = 0;
	m_dIntercept = 0;
	m_dSquare = 0;
	m_iDataNum = 0;
	return;
}

// 函数 CLinearFitData::SetDataNum
// 作用：设置SetDataNum。
// 参数：iDataNum：整数。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Clear。
int CLinearFitData::SetDataNum(int iDataNum)
{
	if(iDataNum < 1)
	{
		return -1;
	}

	if(m_iDataNum > 0)
	{
		if(m_iDataNum != iDataNum)
		{
			Clear();
		}
	}
	else
	{
		m_iDataNum = iDataNum;
		m_pDX = new double[m_iDataNum];
		if(NULL == m_pDX)
		{
			return -2;
		}
		m_pDY = new double[m_iDataNum];
		if(NULL == m_pDY)
		{
			delete [] m_pDX;
			return -3;
		}
	}

	return 0;
}

// 函数 CLinearFitData::LeastSquare
// 作用：执行LeastSquare。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 abs、sqrt。
int CLinearFitData::LeastSquare()
{
	if(NULL == m_pDX)
	{
		return -1;
	}
	if(NULL == m_pDY)
	{
		return -2;
	}

	if(m_iDataNum < 2)
	{
		return -3;
	}

	double s0 = m_iDataNum, s1 = 0, s2 = 0, t0 = 0, t1 = 0;
	for(int i = 0;i < m_iDataNum;++i)
	{
		s1 += m_pDX[i];
		s2 += (m_pDX[i] * m_pDX[i]);
		t0 += m_pDY[i];
		t1 += (m_pDX[i] * m_pDY[i]);
	}
	double d = s0 * s2 - s1 * s1;

	if(0 == d)
	{
		return -4;
	}

	m_dIntercept = (s2 * t0 - s1 * t1) / d;
	m_dSlope = (s0 * t1 - s1 * t0) / d;

	//计算相关系数R2
	double dXMean = 0,dYMean = 0;
	for(int i=0; i<m_iDataNum; i++)
	{
		dXMean += m_pDX[i];
		dYMean += m_pDY[i];
	} 

	dXMean /= m_iDataNum;
	dYMean /= m_iDataNum;

	double dAUp = 0,dBDown = 0,dCDown = 0;
	for(int i = 0;i <m_iDataNum;++i)
	{
		dAUp += abs((m_pDX[i] - dXMean) * (m_pDY[i] - dYMean));
		dBDown += (m_pDX[i] - dXMean) * (m_pDX[i] - dXMean);
		dCDown += (m_pDY[i] - dYMean) * (m_pDY[i] - dYMean);
	} 

	double dSumXY = 0,dSumX = 0, dSumY = 0, dSumX2 = 0, dSumY2 = 0;
	for(int i = 0;i < m_iDataNum;++i)
	{
		dSumXY += m_pDX[i] * m_pDY[i];
		dSumX += m_pDX[i];
		dSumY += m_pDY[i];
		dSumX2 += m_pDX[i] * m_pDX[i];
		dSumY2 += m_pDY[i] * m_pDY[i];
	}
	double dUp = m_iDataNum*dSumXY - dSumX * dSumY;
	double dDown = sqrt(m_iDataNum * dSumX2 - dSumX * dSumX) * sqrt(m_iDataNum * dSumY2 - dSumY * dSumY);

	if(0 != dDown)
	{
		m_dSquare = dUp /dDown;
	}
	else
	{
		m_dSquare = 0;
	}
	return 0;
}

