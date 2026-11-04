// 【交接】 CurveFit\ExpFitting.h
// 作用：ExpFitting 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：LnY、CExpFitting、ExpSolution。
#pragma once

#include "Fitting.h"

class AFX_EXT_CLASS CExpFitting :
    public CFitting
{
    double *m_pdXList, *m_pdYList, *m_pdCoeffExpon;
    int m_iListLength;
    BOOL LnY();//对Y列取对数
public:
    CExpFitting(void);
    ~CExpFitting(void);
    double ExpSolution(double *x, double *y, double *Result, int iListLen);//计算结果
};

