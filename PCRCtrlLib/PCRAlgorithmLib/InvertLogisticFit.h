// 【交接】 PCRCtrlLib\PCRAlgorithmLib\InvertLogisticFit.h
// 作用：InvertLogisticFit 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CInvertLogisticFit、LnXLogistY、FunctionValue、PartialYmin、PartialYmax、PartialXo、PartialP、Residual。
#pragma once

#include "LogisticFit.h"


class AFX_EXT_CLASS CInvertLogisticFit : public CLogisticFit
{
public:
    CInvertLogisticFit(void);
    virtual ~CInvertLogisticFit(void);
protected:
    virtual BOOL LnXLogistY(void);
    virtual double FunctionValue(double x);
    virtual double PartialYmin(double x);
    virtual double PartialYmax(double x);
    virtual double PartialXo(double x);
    virtual double PartialP(double x);
    virtual double Residual(double *pdIndex);
public:
    virtual double LogisticFitSol(double *x, double *y, double *MinMaxXoP, int iListLen, int InputIterNum);
protected:
    virtual BOOL FormCYMatrix(void);
    virtual double RelativeIndex(double *pdIndex);
};

