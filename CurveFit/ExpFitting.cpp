// 【交接】 CurveFit\ExpFitting.cpp
// 作用：ExpFitting 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CExpFitting、m_pdXList、m_pdYList、m_pdCoeffExpon、LnY、log、ExpSolution、SolutionCLEG。
#include "StdAfx.h"
#include <math.h>

#include "ExpFitting.h"



CExpFitting::CExpFitting(void):
    m_pdXList(NULL),
    m_pdYList(NULL),
    m_pdCoeffExpon(NULL)
{
}

// 函数 CExpFitting::~CExpFitting
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CExpFitting::~CExpFitting(void)
{
}

/**
 * 求Y列的ln，m_dYList的数值变为其ln值。
 */
// 函数 CExpFitting::LnY
// 作用：执行LnY。
// 参数：无。
// 返回：返回是或否。
// 过程：函数里会调用 log。
BOOL CExpFitting::LnY()
{
    int i;
    for (i = 0; i < m_iListLength; i++)
    {
        m_pdYList[i] = log(m_pdYList[i]);
    }
    return TRUE;
}

/**
 *求指数拟和的系数和指数
 * \param *x   x列数据，double型
 * \param *y   y列数据，double型
 * \param *Result   外部获得的计算结果，Result[0]为拟和得到的系数，Result[1]为指数。
 * \param iListLen  x列和y列的长度
 * \return  各点误差的平方和
 */
// 函数 CExpFitting::ExpSolution
// 作用：执行ExpSolution。
// 参数：x；y；Result；iListLen：整数。
// 返回：返回一个小数。失败时返回 FALSE。
// 过程：函数里会调用 LnY、SolutionCLEG、exp、memcpy。
double CExpFitting::ExpSolution(double *x, double *y, double *Result, int iListLen)
{
    double fSD;
    int k;
    m_iListLength = iListLen;
    m_pdXList = new double[m_iListLength];
    if (NULL == m_pdXList)
    {
        return FALSE;
    }

    m_pdYList = new double[m_iListLength];
    if (NULL == m_pdYList)
    {
        return FALSE;
    }

    m_pdCoeffExpon = new double[2];
    if (NULL == m_pdCoeffExpon)
    {
        return FALSE;
    }

    for (k = 0; k < m_iListLength; k++)
    {
        m_pdXList[k] = x[k];
        m_pdYList[k] = y[k];
    }
    CExpFitting::LnY();
    fSD = CFitting::SolutionCLEG(m_pdXList, m_pdYList, m_pdCoeffExpon, m_iListLength, 2);
    m_pdCoeffExpon[0] = exp(m_pdCoeffExpon[0]);
    memcpy(Result, m_pdCoeffExpon, 16);

    delete m_pdXList;
    delete m_pdYList;
    delete m_pdCoeffExpon;

    return fSD;
}

