// 【交接】 CurveFit\PowerFitting.h
// 作用：PowerFitting 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CPowerFitting、Ln、PowSolution。
#pragma once

#include "Fitting.h"


class AFX_EXT_CLASS CPowerFitting :
    public CFitting
{
public:
    CPowerFitting(void);
    ~CPowerFitting(void);
private:
    double *m_pdXList;
    double *m_pdYList;
    double *m_pdCoeffExpon;
    int m_iListLength;
    BOOL Ln(double *pdData, int iDataLen);
public:
    double PowSolution(double *x, double *y, double *Result, int iListLen);
};

