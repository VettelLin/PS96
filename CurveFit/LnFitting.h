// 【交接】 CurveFit\LnFitting.h
// 作用：LnFitting 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：LnX、CLnFitting、LnSolution。
#pragma once

#include "Fitting.h"


class AFX_EXT_CLASS CLnFitting :
    public CFitting
{
    double *m_pdXList, *m_pdYList, *m_pdCoeffExpon;
    int m_iListLength;
    BOOL LnX();// 对x列取对数
public:
    CLnFitting(void);
    ~CLnFitting(void);
    double LnSolution(double *x, double *y, double *Result, int iListLen); //计算结果
};

