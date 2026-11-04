// 【交接】 CurveFit\LogisticFit.h
// 作用：LogisticFit 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：InputXY、LnXLogistY、FunctionValue、PartialYmin、PartialYmax、PartialXo、PartialP、FormCYMatrix。
#pragma once

#include "LeastSquare.h"


class AFX_EXT_CLASS CLogisticFit :
    public CLeastSquare
{
protected:
    double *m_pdXList, *m_pdYList;
    double *m_pdLogisticY, *m_pdLnX, *m_pdPartialMatrix, *m_pdYMatrix, *m_pdMinMaxXoP;
    double *m_pdWeight;
    double m_dYmin, m_dYmax, m_dXmin, m_dYMean, m_dSqrtR;
    int m_iListLength, m_iEffectPoint;

    virtual BOOL InputXY(double *x, double *y);
    virtual BOOL LnXLogistY();
    virtual double FunctionValue(double x);
    virtual double PartialYmin(double x);
    virtual double PartialYmax(double x);
    virtual double PartialXo(double x);
    virtual double PartialP(double x);
    virtual BOOL FormCYMatrix();
    virtual double Residual(double *Index);
    virtual double RelativeIndex(double *Index);
    virtual int IterParam(double Factor, double *DeltaParam);

public:
    CLogisticFit(void);
    ~CLogisticFit(void);
    virtual double LogisticFitSol(double *x, double *y, double *MinMaxXoP, int iListLen, int InputIterNum);
private:
    double m_dZero;
};

