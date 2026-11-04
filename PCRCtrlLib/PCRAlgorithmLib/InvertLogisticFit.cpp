// 【交接】 PCRCtrlLib\PCRAlgorithmLib\InvertLogisticFit.cpp
// 作用：InvertLogisticFit 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CInvertLogisticFit、LnXLogistY、log、FunctionValue、exp、PartialYmin、PartialYmax、PartialXo。
#include "StdAfx.h"
#include <math.h>

#include "InvertLogisticFit.h"
#include "Fitting.h"



// 函数 CInvertLogisticFit::CInvertLogisticFit
// 作用：执行CInvertLogisticFit。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInvertLogisticFit::CInvertLogisticFit(void)
{
}

// 函数 CInvertLogisticFit::~CInvertLogisticFit
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CInvertLogisticFit::~CInvertLogisticFit(void)
{
}

// 函数 CInvertLogisticFit::LnXLogistY
// 作用：执行LnXLogistY。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 log。
BOOL CInvertLogisticFit::LnXLogistY(void)
{
    int i, j;
    double min, max;
    double temp;

    min = m_dYmin - 0.1;
    max = m_dYmax + 1;

    if (m_pdLogisticY != NULL)
    {
        delete m_pdLogisticY;
        m_pdLogisticY = NULL;
    }
    m_pdLogisticY = new double [m_iEffectPoint];
    if (NULL == m_pdLogisticY)
    {
        return FALSE;
    }

    if (m_pdLnX != NULL)
    {
        delete m_pdLnX;
        m_pdLnX = NULL;
    }
    m_pdLnX = new double [m_iEffectPoint];
    if (NULL == m_pdLnX)
    {
        return FALSE;
    }

    j = 0;
    for (i = 0; i < m_iEffectPoint; i++)
    {
        temp = (max - m_pdYList[j]) / (m_pdYList[j] - min);

        m_pdLogisticY[i] = log(temp);

        if (m_pdXList[j] <= 0)
            //j++;
            //m_pdLnX[i] = log(m_dXmin/2);
        {
            m_pdLnX[i] = log(0.001);
        }
        else
        {
            m_pdLnX[i] = log(m_pdXList[j]);
        }

        j++;
    }
    return TRUE;
}

// 函数 CInvertLogisticFit::FunctionValue
// 作用：执行FunctionValue。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 exp、log。
double CInvertLogisticFit::FunctionValue(double x)
{
    double temp;
    if (x <= 0)
    {
        temp = m_pdMinMaxXoP[0] + (m_pdMinMaxXoP[1] - m_pdMinMaxXoP[0]) / (1 + exp(-(m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(0.000001))));
    }
    else
    {
        temp = m_pdMinMaxXoP[0] + (m_pdMinMaxXoP[1] - m_pdMinMaxXoP[0]) / (1 + exp(-(m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(x))));
    }
    return temp;
}

// 函数 CInvertLogisticFit::PartialYmin
// 作用：执行PartialYmin。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 exp、log。
double CInvertLogisticFit::PartialYmin(double x)
{
    double zero, temp;
    zero = x;
    if (zero <= 0)
    {
        zero = 0.000001;
    }
    temp = 1 - 1 / (1 + exp(-(m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(zero))));
    //temp = 1/(1+exp(-(m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(x))));
    return temp;
}

// 函数 CInvertLogisticFit::PartialYmax
// 作用：执行PartialYmax。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 exp、log。
double CInvertLogisticFit::PartialYmax(double x)
{
    double zero, temp;
    zero = x;
    if (zero <= 0)
    {
        zero = 0.000001;
    }
    //temp = 1 - 1/(1+exp(-(m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(x))));
    temp = 1 / (1 + exp(-(m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(zero))));
    return temp;
}

// 函数 CInvertLogisticFit::PartialXo
// 作用：执行PartialXo。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 exp、log、pow。
double CInvertLogisticFit::PartialXo(double x)
{
    double zero, temp;
    zero = x;
    if (zero <= 0)
    {
        zero = 0.000001;
    }

    temp = exp(-1 * (m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(zero)));
    temp = (m_pdMinMaxXoP[1] - m_pdMinMaxXoP[0]) * temp / pow((1 + temp), 2);
    return temp;
}

// 函数 CInvertLogisticFit::PartialP
// 作用：执行PartialP。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 exp、log、pow。
double CInvertLogisticFit::PartialP(double x)
{
    double zero, temp;
    zero = x;
    if (zero <= 0)
    {
        zero = 0.000001;
    }

    temp = exp(-1 * (m_pdMinMaxXoP[2] + m_pdMinMaxXoP[3] * log(zero)));
    temp = (m_pdMinMaxXoP[1] - m_pdMinMaxXoP[0]) * temp * log(zero) / pow((1 + temp), 2);
    return temp;
}

// 函数 CInvertLogisticFit::Residual
// 作用：执行Residual。
// 参数：pdIndex。
// 返回：返回一个小数。
// 过程：函数里会调用 exp、log、fabs、floor。
double CInvertLogisticFit::Residual(double *pdIndex)
{
    double Ymin, Ymax, Xo, P, temp, SD;
    double ErrMedian, Threshold, TempMax;
    double *ErrSequence;
    int i, j;

    Ymin = pdIndex[0];
    Ymax = pdIndex[1];
    Xo = pdIndex[2];
    P = pdIndex[3];

    ErrMedian = 0;
    SD = 0;
    TempMax = 0;

    ErrSequence = new double [m_iListLength];

    for (i = 0; i < m_iListLength; i++)
    {
        if (m_pdXList[i] <= 0)
        {
            temp = Ymin + (Ymax - Ymin) / (1 + exp(-(Xo + P * log(0.000001))));
        }
        else
        {
            temp = Ymin + (Ymax - Ymin) / (1 + exp(-(Xo + P * log(m_pdXList[i]))));
        }
        temp -= m_pdYList[i];
        //if(i == m_iListLength - 2)
        //{
        //  temp *= 1;
        //}
        //else if(i == m_iListLength - 1)
        //{
        //  temp *= 8;
        //}
        ErrSequence[i] = fabs(temp);
        SD += temp * temp;
    }

    for (i = 0; i < m_iListLength; i++)
    {
        TempMax = ErrSequence[i];
        for (j = i; j < m_iListLength; j++)
        {
            if (ErrSequence[j] > TempMax)
            {
                TempMax = ErrSequence[j];
                ErrSequence[j] = ErrSequence[i];
                ErrSequence[i] = TempMax;
            }
        }
    }

    double temp2, l;
    l = (double)m_iListLength;
    temp2 = floor(l / 2);

    i = (int)temp2;

    if (i == (l / 2))
    {
        ErrMedian = (ErrSequence[i] + ErrSequence[i - 1]) / 2;
    }
    else
    {
        ErrMedian = ErrSequence[i];
    }

    Threshold = 1.345 * 1.4826 * ErrMedian;

    //Threshold = 0.00001*ErrMedian;
    for (i = 0; i < m_iListLength; i++)
    {
        if (m_pdXList[i] <= 0)
        {
            temp = Ymin + (Ymax - Ymin) / (1 + exp(-(Xo + P * log(0.000001))));
        }
        else
        {
            temp = Ymin + (Ymax - Ymin) / (1 + exp(-(Xo + P * log(m_pdXList[i]))));
        }
        temp -= m_pdYList[i];

        for (j = 0; j < m_iListLength; j++)
        {
            if (j == i)
            {
                if (fabs(temp) <= Threshold)
                {
                    m_pdWeight[i * m_iListLength + j] = 1;
                }
                else
                {
                    m_pdWeight[i * m_iListLength + j] = 1;    //Threshold/abs(temp);
                }
            }
            else
            {
                m_pdWeight[i * m_iListLength + j] = 0;
            }
        }
    }
    delete ErrSequence;
    return SD;
}

// 函数 CInvertLogisticFit::LogisticFitSol
// 作用：执行LogisticFitSol。
// 参数：x；y；MinMaxXoP；iListLen：整数；InputIterNum。
// 返回：返回一个小数。失败时返回 FALSE。
// 过程：函数里会调用 InputXY、LnXLogistY。
double CInvertLogisticFit::LogisticFitSol(double *x, double *y, double *MinMaxXoP, int iListLen, int InputIterNum)
{
    int Err, iIterNum;
    int i, j, k;
    double *m_pdInterceptSlope, *pdTempCMatrix, *m_pdTempIndex, dbResidual, temp;

    m_iListLength = iListLen;

    if (m_pdXList != NULL)
    {
        delete m_pdXList;
        m_pdXList = NULL;
    }
    m_pdXList = new double[m_iListLength];
    if (NULL == m_pdXList)
    {
        return FALSE;
    }

    if (m_pdYList != NULL)
    {
        delete m_pdYList;
        m_pdYList = NULL;
    }
    m_pdYList = new double[m_iListLength];
    if (NULL == m_pdYList)
    {
        return FALSE;
    }

    if (m_pdWeight != NULL)
    {
        delete m_pdWeight;
        m_pdWeight = NULL;
    }
    m_pdWeight = new double[m_iListLength * m_iListLength];
    if (NULL == m_pdWeight)
    {
        return FALSE;
    }

    if (m_pdMinMaxXoP != NULL)
    {
        delete m_pdMinMaxXoP;
        m_pdMinMaxXoP = NULL;
    }
    m_pdMinMaxXoP = new double[4];
    if (NULL == m_pdMinMaxXoP)
    {
        return FALSE;
    }

    m_pdInterceptSlope = new double[2];
    if (NULL == m_pdInterceptSlope)
    {
        return FALSE;
    }

    m_pdTempIndex = new double [4];
    if (NULL == m_pdTempIndex)
    {
        return FALSE;
    }

    InputXY(x, y);
    LnXLogistY();


    //////////////////////////////////////////////////////////////////////
    ///////////               ???????????                //////////////
    //////////////////////////////////////////////////////////////////////
    if ((MinMaxXoP[0] == 0) && (MinMaxXoP[1] == 0) && (MinMaxXoP[2] == 0) && (MinMaxXoP[3] == 0))
    {
        pdTempCMatrix = new double [m_iEffectPoint * 2];
        for (i = 0; i < m_iEffectPoint; i++)
        {
            pdTempCMatrix [i * 2] = 1;
            pdTempCMatrix [i * 2 + 1] = m_pdLnX[i];
        }
        //????????Xo,p
        //CFitting fit;
        //dbResidual = fit.SolutionCLEG(pdTempCMatrix, m_pdLogisticY, m_pdInterceptSlope, m_iEffectPoint, 2);
        dbResidual = CLeastSquare::LeastSquareSolution(pdTempCMatrix, m_pdLogisticY, m_pdInterceptSlope, m_iEffectPoint, 2);
        m_pdMinMaxXoP[0] = m_dYmin - 0.1;
        m_pdMinMaxXoP[1] = m_dYmax + 1;
        m_pdMinMaxXoP[3] = -1 * m_pdInterceptSlope[1]; //????��????????????????x0??p
        m_pdMinMaxXoP[2] = -1 * m_pdInterceptSlope[0];

        m_dSqrtR = RelativeIndex(m_pdMinMaxXoP);//????????????????????????????????

        if (pdTempCMatrix != NULL)
        {
            delete pdTempCMatrix;
        }

    }

    else
    {
        memcpy(m_pdMinMaxXoP, MinMaxXoP, sizeof(double) * 4);
    }

    /*m_pdMinMaxXoP[0] = -57726;
    m_pdMinMaxXoP[1] = 553359;
    m_pdMinMaxXoP[3] = 1.08; //????��????????????????x0??p
    m_pdMinMaxXoP[2] = 1.5;*/

    ////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    ///////////////           ???????                ////////////
    //////////////////////////////////////////////////////////////
    double NewtonFactor, MaxSqrtR1, MaxSqrtR, MaxSqrtR2, BestNewtonFactor, BestNewtonFactor1, BestNewtonFactor2;
    double Lamda = 1;
    double *TempMinMaxXoP;
    temp = MaxSqrtR = 0;

    TempMinMaxXoP = new double [4];
    if (NULL == m_pdTempIndex)
    {
        return FALSE;
    }

    if (InputIterNum == 0)
    {
        iIterNum = 10000;
    }
    else
    {
        iIterNum = InputIterNum;
    }

    m_dSqrtR = RelativeIndex(m_pdMinMaxXoP);

    int m;

    NewtonFactor = 1;
    MaxSqrtR = 0;
    for (m = 0; m < iIterNum; m++)
    {
        //////???Newton??
        MaxSqrtR = MaxSqrtR1 = MaxSqrtR2 = m_dSqrtR;
        BestNewtonFactor = BestNewtonFactor1 = BestNewtonFactor2 = 2;

        Err = FormCYMatrix();
        if (Err == FALSE)
        {
            return Err;
        }

        //CFitting fit;
        //dbResidual = fit.SolutionCLEG(m_pdPartialMatrix, m_pdYMatrix, m_pdTempIndex, m_iListLength, 4);
        dbResidual = CLeastSquare::LeastSquareSolution(m_pdPartialMatrix, m_pdYMatrix, m_pdTempIndex, m_iListLength, 4);

        NewtonFactor = 2;
        for (k = 0; k < 10; k++)
        {
            for (j = 0; j < 4; j++)
            {
                TempMinMaxXoP[j] = m_pdMinMaxXoP[j] + m_pdTempIndex[j] * NewtonFactor;
            }

            temp = RelativeIndex(TempMinMaxXoP);

            if (temp > MaxSqrtR1)
            {
                MaxSqrtR1 = temp;
                BestNewtonFactor1 = NewtonFactor;
            }

            NewtonFactor = NewtonFactor / 2;
        }

        NewtonFactor = 2;
        for (k = 0; k < 10; k++)
        {
            for (j = 0; j < 4; j++)
            {
                TempMinMaxXoP[j] = m_pdMinMaxXoP[j] + m_pdTempIndex[j] * NewtonFactor;
            }

            temp = RelativeIndex(TempMinMaxXoP);

            if (temp > MaxSqrtR2)
            {
                MaxSqrtR2 = temp;
                BestNewtonFactor2 = NewtonFactor;
            }

            NewtonFactor = NewtonFactor * 2;
        }

        if (MaxSqrtR2 > MaxSqrtR1)
        {
            MaxSqrtR = MaxSqrtR2;
            BestNewtonFactor = BestNewtonFactor2;
        }
        else
        {
            MaxSqrtR = MaxSqrtR1;
            BestNewtonFactor = BestNewtonFactor1;
        }

        if ((m != 0) && (MaxSqrtR <= m_dSqrtR))
        {
            break;
        }

        else
        {
            m_dSqrtR = MaxSqrtR;

            for (j = 0; j < 4; j++)
            {
                m_pdMinMaxXoP[j] = m_pdMinMaxXoP[j] + m_pdTempIndex[j] * BestNewtonFactor;
            }
        }

    }

    memcpy(MinMaxXoP, m_pdMinMaxXoP, 32);

    if (m_pdTempIndex != NULL)
    {
        delete m_pdTempIndex;
    }


    if (m_pdInterceptSlope != NULL)
    {
        delete m_pdInterceptSlope;
    }

    if (TempMinMaxXoP != NULL)
    {
        delete TempMinMaxXoP;
    }

    //return m_dSqrtR;
    return MaxSqrtR;
}

// 函数 CInvertLogisticFit::FormCYMatrix
// 作用：执行FormCYMatrix。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 PartialYmin、PartialYmax、PartialXo、PartialP、FunctionValue。
BOOL CInvertLogisticFit::FormCYMatrix(void)
{
    int i;
    double temp;

    if (m_pdPartialMatrix != NULL)
    {
        delete m_pdPartialMatrix;
        m_pdPartialMatrix = NULL;
    }

    m_pdPartialMatrix = new double [m_iListLength * 4];
    if (NULL == m_pdPartialMatrix)
    {
        return FALSE;
    }

    if (m_pdYMatrix != NULL)
    {
        delete m_pdYMatrix;
        m_pdYMatrix = NULL;
    }

    m_pdYMatrix = new double [m_iListLength * 4];
    if (NULL == m_pdYMatrix)
    {
        return FALSE;
    }

    for (i = 0; i < m_iListLength; i++)
    {
        temp = m_pdXList[i];
        m_pdPartialMatrix[i * 4] = PartialYmin(temp) * m_pdWeight[i * m_iListLength + i]; //?????????
        m_pdPartialMatrix[i * 4 + 1] = PartialYmax(temp) * m_pdWeight[i * m_iListLength + i];
        m_pdPartialMatrix[i * 4 + 2] = PartialXo(temp) * m_pdWeight[i * m_iListLength + i];
        m_pdPartialMatrix[i * 4 + 3] = PartialP(temp) * m_pdWeight[i * m_iListLength + i];
    }

    for (i = 0; i < m_iListLength; i++)
    {
        temp = m_pdXList[i];
        temp = FunctionValue(temp);
        m_pdYMatrix[i] = m_pdYList[i] - temp;
    }

    return TRUE;
}

// 函数 CInvertLogisticFit::RelativeIndex
// 作用：执行RelativeIndex。
// 参数：pdIndex。
// 返回：返回一个小数。
// 过程：函数里会调用 Residual、Sum、Aver、pow。
double CInvertLogisticFit::RelativeIndex(double *pdIndex)
{
    int l;
    double SD = 0, temp = 0, Var = 0, dRelatedCoef = 0;
    SD = Residual(pdIndex);

    temp = 0;
    for (l = 0; l < m_iListLength; l++) //??Var??Sum(Yi-Aver(Yi))^2
    {
        temp += pow((m_pdYList[l] - m_dYMean), (double)2);
    }

    Var = temp;
    if (Var == 0)
    {
        Var = 0.0000001;
    }
    dRelatedCoef = 1 - SD / Var;

    return dRelatedCoef;
}

