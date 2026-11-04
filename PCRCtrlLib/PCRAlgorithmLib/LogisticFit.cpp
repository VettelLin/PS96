// 【交接】 PCRCtrlLib\PCRAlgorithmLib\LogisticFit.cpp
// 作用：LogisticFit 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CLogisticFit、m_pdXList、m_pdYList、m_pdLogisticY、m_pdLnX、m_pdPartialMatrix、m_pdYMatrix、m_pdMinMaxXoP。
#include "StdAfx.h"
#include <math.h>

#include "LogisticFit.h"


CLogisticFit::CLogisticFit(void):
    m_pdXList(NULL),
    m_pdYList(NULL),
    m_pdLogisticY(NULL),
    m_pdLnX(NULL),
    m_pdPartialMatrix(NULL),
    m_pdYMatrix(NULL),
    m_pdMinMaxXoP(NULL),
    m_pdWeight(NULL)
    , m_dZero(0.0000000001)
{
    m_dYmin = m_dYmax = m_dXmin = 0;
    m_dSqrtR = 0;
    m_iListLength = 2;
}

// 函数 CLogisticFit::~CLogisticFit
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CLogisticFit::~CLogisticFit(void)
{
    if (m_pdXList != NULL)
    {
        delete m_pdXList;
    }

    if (m_pdYList != NULL)
    {
        delete m_pdYList;
    }

    if (m_pdLogisticY != NULL)
    {
        delete m_pdLogisticY;
    }

    if (m_pdLnX != NULL)
    {
        delete m_pdLnX;
    }

    if (m_pdPartialMatrix != NULL)
    {
        delete m_pdPartialMatrix;
    }

    if (m_pdYMatrix != NULL)
    {
        delete m_pdYMatrix;
    }

    if (m_pdMinMaxXoP != NULL)
    {
        delete m_pdMinMaxXoP;
    }

    if (m_pdWeight != NULL)
    {
        delete m_pdWeight;
    }
}

/**
 * ????x?��?y???????m_pdXList??m_pdYList????????y?��??????��???????
 * \param *x ?????x?????????
 * \param *y ?????y?????????
 * \return
 */
// 函数 CLogisticFit::InputXY
// 作用：执行InputXY。
// 参数：x；y。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CLogisticFit::InputXY(double *x, double *y)
{
    int k = 0;
    int CountLen = 0;
    double SumY, maxtemp, mintemp, Xmintemp;
    maxtemp = y[0];
    mintemp = y[0];
    Xmintemp = 9999999999;
    SumY = 0;

    for (k = 0; k < m_iListLength; k++) //????x??y?��?��?????0??????0.00000001??
    {
        //???????��???????maxtemp,mintemp
        m_pdXList[k] = x[k];
        m_pdYList[k] = y[k];
        /*  if(m_pdXList[k] <= 0)
            {
                CountLen++;
                m_pdXList[k] = 0.0001;
            }*/

        SumY = m_pdYList[k] + SumY;
        if (maxtemp < m_pdYList[k])
        {
            maxtemp = m_pdYList[k];
        }
        if (mintemp > m_pdYList[k])
        {
            mintemp = m_pdYList[k];
        }
        if ((Xmintemp > m_pdXList[k]) && (m_pdXList[k] > 0))
        {
            Xmintemp = m_pdXList[k];
        }
    }
    m_dYmax = maxtemp;
    m_dYmin = mintemp;
    m_dYMean = SumY / m_iListLength;

    m_dXmin = Xmintemp;

    //m_iEffectPoint = m_iListLength - CountLen;
    m_iEffectPoint = m_iListLength;
    return TRUE;
}

/**
 * ??x???ln????y???logistic????A0?????Ymin*0.5??A1?????Ymax*1.1
 * \return
 */
// 函数 CLogisticFit::LnXLogistY
// 作用：执行LnXLogistY。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 log。
BOOL CLogisticFit::LnXLogistY()
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
        temp = (m_pdYList[j] - min) / (max - m_pdYList[j]);

        m_pdLogisticY[i] = log(temp);

        if (m_pdXList[j] <= 0)
            //j++;
            //m_pdLnX[i] = log(m_dXmin/2);
            //m_pdLnX[i] = log (0.001);
        {
            m_pdLnX[i] = log(m_dZero);
        }
        else
        {
            m_pdLnX[i] = log(m_pdXList[j]);
        }

        j++;
    }
    return TRUE;
}

// 函数 CLogisticFit::FunctionValue
// 作用：执行FunctionValue。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 pow。
double CLogisticFit::FunctionValue(double x)
{
    double temp;
    temp = m_pdMinMaxXoP[0] + (m_pdMinMaxXoP[1] - m_pdMinMaxXoP[0]) / (1 + pow((x / m_pdMinMaxXoP[2]), m_pdMinMaxXoP[3]));
    return temp;
}

// 函数 CLogisticFit::PartialYmin
// 作用：执行PartialYmin。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 pow。
double CLogisticFit::PartialYmin(double x)
{
    double temp;
    temp = 1 - 1 / (1 + pow((x / m_pdMinMaxXoP[2]), m_pdMinMaxXoP[3]));
    return temp;
}

// 函数 CLogisticFit::PartialYmax
// 作用：执行PartialYmax。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 pow。
double CLogisticFit::PartialYmax(double x)
{
    double temp;
    temp = 1 / (1 + pow((x / m_pdMinMaxXoP[2]), m_pdMinMaxXoP[3]));
    return temp;
}

// 函数 CLogisticFit::PartialXo
// 作用：执行PartialXo。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 pow。
double CLogisticFit::PartialXo(double x)
{
    double zero, temp;
    zero = x;
    if (zero <= 0)
    {
        zero = m_dZero;
    }

    temp = pow((zero / m_pdMinMaxXoP[2]), m_pdMinMaxXoP[3]);
    temp = m_pdMinMaxXoP[3] * temp * (m_pdMinMaxXoP[1] - m_pdMinMaxXoP[0]) / (1 + temp) / (1 + temp) / m_pdMinMaxXoP[2];
    return temp;
}

// 函数 CLogisticFit::PartialP
// 作用：执行PartialP。
// 参数：x。
// 返回：返回一个小数。
// 过程：函数里会调用 pow、log。
double CLogisticFit::PartialP(double x)
{
    double zero, temp;
    zero = x;
    if (zero <= 0)
    {
        zero = m_dZero;
    }

    temp = pow((zero / m_pdMinMaxXoP[2]), m_pdMinMaxXoP[3]);
    temp =  temp = log(zero / m_pdMinMaxXoP[2]) * temp * (m_pdMinMaxXoP[0] - m_pdMinMaxXoP[1]) / (1 + temp) / (1 + temp);

    return temp;
}

/**
 * ?????????????m_pdPartialMatrix???��????m_pdYMatrix ?? Y??Y^
 * \return
 */
// 函数 CLogisticFit::FormCYMatrix
// 作用：执行FormCYMatrix。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 PartialYmin、PartialYmax、PartialXo、PartialP、FunctionValue。
BOOL CLogisticFit::FormCYMatrix()
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

/**
 * ??��???????????????????????????????????????Y???????Y???????????
 * \param *Index ????????????
 * \return ?��?
 */
// 函数 CLogisticFit::Residual
// 作用：执行Residual。
// 参数：Index。
// 返回：返回一个小数。
// 过程：函数里会调用 pow、fabs、floor、abs。
double CLogisticFit::Residual(double *Index)
{
    double Ymin, Ymax, Xo, P, temp, SD;
    double ErrMedian, Threshold, TempMax;
    double *ErrSequence;
    int i, j;

    Ymin = Index[0];
    Ymax = Index[1];
    Xo = Index[2];
    P = Index[3];

    ErrMedian = 0;
    SD = 0;
    TempMax = 0;

    ErrSequence = new double [m_iListLength];

    for (i = 0; i < m_iListLength; i++)
    {
        temp = Ymin + (Ymax - Ymin) / (1 + pow((m_pdXList[i] / Xo), P));
        temp -= m_pdYList[i];
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

        temp = Ymin + (Ymax - Ymin) / (1 + pow((m_pdXList[i] / Xo), P));
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

/**
 * ??????????????Residual??��???????????????????
 * \param *Index ????????????
 * \return ??????
 */
// 函数 CLogisticFit::RelativeIndex
// 作用：执行RelativeIndex。
// 参数：Index。
// 返回：返回一个小数。
// 过程：函数里会调用 Residual、Sum、Aver、pow。
double CLogisticFit::RelativeIndex(double *Index)
{
    int l;
    double SD = 0, temp = 0, Var = 0, dRelatedCoef = 0;
    SD = Residual(Index);

    temp = 0;
    for (l = 0; l < m_iListLength; l++) //??Var??Sum(Yi-Aver(Yi))^2
    {
        temp += pow((m_pdYList[l] - m_dYMean), (double)2);
    }

    Var = temp;
    if (Var == 0)
    {
        Var = m_dZero;
    }
    dRelatedCoef = 1 - SD / Var;

    return dRelatedCoef;
}

/**
 * Gauss-Newton???????????????????A=(P'WP)^(-1)P'WY???????????????m_pdMinMaxXoP???????????????????????????????????
 * \param
 * \return 1????????<0???????k+1?????��???????????????????��?k?��??��???????��??ZERO???
 */
// 函数 CLogisticFit::IterParam
// 作用：执行IterParam。
// 参数：Factor；DeltaParam。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。失败时返回 FALSE。
// 过程：函数里会调用 FormCYMatrix、MatrixTranspose、MatrixMultiply、MatrixInversion。
int CLogisticFit::IterParam(double Factor, double *DeltaParam)
{
    int i, Err = 0;
    double *TempMatrix1, *TempMatrix2, *TempMatrix3, *TempMatrix4, *TempMatrix5;

    TempMatrix1 = new double [m_iListLength * 4]; //4*n
    if (NULL == TempMatrix1)
    {
        return FALSE;
    }

    TempMatrix2 = new double [16];//4*4
    if (NULL == TempMatrix2)
    {
        return FALSE;
    }

    TempMatrix3 = new double [16];//4*4
    if (NULL == TempMatrix3)
    {
        return FALSE;
    }

    TempMatrix4 = new double [m_iListLength * 4]; //4*n
    if (NULL == TempMatrix4)
    {
        return FALSE;
    }

    TempMatrix5 = new double [4]; //4*1
    if (NULL == TempMatrix5)
    {
        return FALSE;
    }

    Err = FormCYMatrix();
    if (Err == FALSE)
    {
        return Err;
    }

    //??????????????TempMatrix1 = P';
    Err = CLeastSquare::MatrixTranspose(m_pdPartialMatrix, TempMatrix1, m_iListLength, 4);
    if (Err == FALSE)
    {
        return Err;
    }
    //P'W = TempMatrix1;
    Err = CLeastSquare::MatrixMultiply(TempMatrix1, m_pdWeight, TempMatrix1, 4, m_iListLength, m_iListLength);
    if (Err == FALSE)
    {
        return Err;
    }
    //P'WP = TempMatrix2;
    Err = CLeastSquare::MatrixMultiply(TempMatrix1, m_pdPartialMatrix, TempMatrix2, 4, m_iListLength, 4);
    if (Err == FALSE)
    {
        return Err;
    }
    //(P'WP)^-1 = TempMatrix3;
    Err = CLeastSquare::MatrixInversion(TempMatrix2, TempMatrix3, 4);
    if (Err == FALSE)
    {
        return Err;
    }
    //(P'WP)^-1*P'W = TempMatrix4;
    Err = CLeastSquare::MatrixMultiply(TempMatrix3, TempMatrix1, TempMatrix4, 4, 4, m_iListLength);
    if (Err == FALSE)
    {
        return Err;
    }
    //(P'WP)^-1*P'WY
    Err = CLeastSquare::MatrixMultiply(TempMatrix4, m_pdYMatrix, TempMatrix5, 4, m_iListLength, 1);
    if (Err == FALSE)
    {
        return Err;
    }

    /*for (i = 0; i<4; i++)
        m_pdMinMaxXoP[i] += Factor * TempMatrix5[i];*/

    for (i = 0; i < 4; i++)
    {
        TempMatrix5[i] =  Factor * TempMatrix5[i];
    }

    memcpy(DeltaParam, TempMatrix5, 32);

    delete TempMatrix1;
    delete TempMatrix2;
    delete TempMatrix3;
    delete TempMatrix4;
    delete TempMatrix5;

    return 1;
}

// 函数 CLogisticFit::LogisticFitSol
// 作用：执行LogisticFitSol。
// 参数：x；y；MinMaxXoP；iListLen：整数；InputIterNum。
// 返回：返回一个小数。失败时返回 FALSE。
// 过程：函数里会调用 InputXY、LnXLogistY、LeastSquareSolution。
double CLogisticFit::LogisticFitSol(double *x, double *y, double *MinMaxXoP, int iListLen, int InputIterNum)
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
        dbResidual = CLeastSquare::LeastSquareSolution(pdTempCMatrix, m_pdLogisticY, m_pdInterceptSlope, m_iEffectPoint, 2);
        m_pdMinMaxXoP[0] = m_dYmin - 0.1;
        m_pdMinMaxXoP[1] = m_dYmax + 1;
        m_pdMinMaxXoP[3] = -1 * m_pdInterceptSlope[1]; //????��????????????????x0??p
        m_pdMinMaxXoP[2] = exp(-1 * m_pdInterceptSlope[0] / m_pdInterceptSlope[1]);

        m_dSqrtR = RelativeIndex(m_pdMinMaxXoP);//????????????????????????????????

        if (pdTempCMatrix != NULL)
        {
            delete pdTempCMatrix;
        }

    }

    else
    {
        memcpy(m_pdMinMaxXoP, MinMaxXoP, 32);
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

