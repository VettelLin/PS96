// 【交接】 PCRCtrlLib\PCRAlgorithmLib\PowerFitting.cpp
// 作用：PowerFitting 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CPowerFitting、m_pdXList、m_pdYList、m_pdCoeffExpon、m_iListLength、Ln、log、PowSolution。
#include "StdAfx.h"
#include <math.h>

#include "PowerFitting.h"


CPowerFitting::CPowerFitting(void)
    : m_pdXList(NULL)
    , m_pdYList(NULL)
    , m_pdCoeffExpon(NULL)
    , m_iListLength(0)
{
}

// 函数 CPowerFitting::~CPowerFitting
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPowerFitting::~CPowerFitting(void)
{
}

// 函数 CPowerFitting::Ln
// 作用：执行Ln。
// 参数：pdData；iDataLen：整数。
// 返回：返回是或否。
// 过程：函数里会调用 log。
BOOL CPowerFitting::Ln(double *pdData, int iDataLen)
{
    for (int i = 0 ; i < iDataLen ; i++)
    {
        pdData[i] = log(pdData[i]);
    }

    return TRUE;
}

// 函数 CPowerFitting::PowSolution
// 作用：执行PowSolution。
// 参数：x；y；Result；iListLen：整数。
// 返回：返回一个小数。失败时返回 FALSE。
// 过程：函数里会调用 Ln、SolutionCLEG、exp、memcpy。
double CPowerFitting::PowSolution(double *x, double *y, double *Result, int iListLen)
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
    Ln(m_pdXList, m_iListLength);
    Ln(m_pdYList, m_iListLength);
    fSD = CFitting::SolutionCLEG(m_pdXList, m_pdYList, m_pdCoeffExpon, m_iListLength, 2);
    m_pdCoeffExpon[0] = exp(m_pdCoeffExpon[0]);
    memcpy(Result, m_pdCoeffExpon, 16);

    delete m_pdXList;
    delete m_pdYList;
    delete m_pdCoeffExpon;

    return fSD;
}

