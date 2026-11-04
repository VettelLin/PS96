// 【交接】 PCRCtrlLib\PCRAlgorithmLib\Fitting.cpp
// 作用：Fitting 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CFitting、m_pdXlist、m_pdYlist、m_pCMatrix、m_pAMatrix、m_pdFinalCoef、FormCLEG、FormNormalEquation。
#include "StdAfx.h"
#include <math.h>

#include "Fitting.h"


CFitting::CFitting(void):
    m_pdXlist(NULL),
    m_pdYlist(NULL),
    m_pCMatrix(NULL),
    m_pAMatrix(NULL),
    m_pdFinalCoef(NULL)
{
}

// 函数 CFitting::~CFitting
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CFitting::~CFitting(void)
{
    if (m_pdFinalCoef != NULL)
    {
        delete m_pdFinalCoef;
    }
    if (m_pdXlist != NULL)
    {
        delete m_pdXlist;
    }
    if (m_pdYlist != NULL)
    {
        delete m_pdYlist;
    }
    if (m_pAMatrix != NULL)
    {
        delete m_pAMatrix;
    }
    if (m_pCMatrix != NULL)
    {
        delete m_pCMatrix;
    }
}


/**
 * 生成矛盾方程的系数矩阵m_pCMatrix
 */
// 函数 CFitting::FormCLEG
// 作用：执行FormCLEG。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CFitting::FormCLEG()
{
    int i, j;
    double x, temp;

    if (m_pCMatrix != NULL)
    {
        delete m_pCMatrix;
        m_pCMatrix = NULL;
    }
    m_pCMatrix = new double [m_iListLen * m_iMjie];
    if (NULL == m_pCMatrix)
    {
        return FALSE;
    }
    for (i = 0; i < m_iListLen; i++)
    {
        x = m_pdXlist[i];
        temp = 1;
        for (j = 0; j < m_iMjie; j++)
        {
            m_pCMatrix[i * m_iMjie + j] = temp;
            temp *= x;
        }
    }
    return TRUE;
}

/**
 * 生成正规方程的增广矩阵m_pAMatrix
 */
// 函数 CFitting::FormNormalEquation
// 作用：执行FormNormalEquation。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CFitting::FormNormalEquation()
{
    int i, j, k;
    double temp;

    if (m_pAMatrix != NULL)
    {
        delete m_pAMatrix;
        m_pAMatrix = NULL;
    }
    m_pAMatrix = new double [m_iMjie * (m_iMjie + 1)]; //为增广矩阵分配空间 M*(M+1)
    if (NULL == m_pAMatrix)
    {
        return FALSE;
    }
    ////////////////////////////////////
    for (i = 0; i < m_iMjie; i++)
        for (j = i; j < m_iMjie; j++) //C的转置乘C
        {
            temp = 0;
            for (k = 0; k < m_iListLen; k++)
            {
                temp += m_pCMatrix[k * m_iMjie + i] * m_pCMatrix[k * m_iMjie + j];
            }
            m_pAMatrix[i * (m_iMjie + 1) + j] = temp;
            m_pAMatrix[j * (m_iMjie + 1) + i] = temp;
        }
    for (i = 0; i < m_iMjie; i++) //C的转置乘Y
    {
        temp = 0;
        for (k = 0; k < m_iListLen; k++)
        {
            temp += m_pCMatrix[k * m_iMjie + i] * m_pdYlist[k];
        }
        m_pAMatrix[i * (m_iMjie + 1) + m_iMjie] = temp;
    }
    return TRUE;

}

/**
 *Gauss消元，求线性方程组的解
 * \return 0
 */
// 函数 CFitting::Gauss
// 作用：执行Gauss。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CFitting::Gauss()
{
    int i, j, k;
    double x = 0;
    int MatrixA_ArrNum = m_iMjie + 1;
    for (k = 0; k < m_iMjie; k++)
    {
        x = m_pAMatrix[k * MatrixA_ArrNum + k];
        for (j = k; j < MatrixA_ArrNum; j++)
        {
            m_pAMatrix[k * MatrixA_ArrNum + j] /= x;
        }
        if (k == m_iMjie - 1)
        {
            break;
        }
        for (i = k + 1; i < m_iMjie; i++)
        {
            x = m_pAMatrix[i * MatrixA_ArrNum + k];
            for (j = k; j < MatrixA_ArrNum; j++)
            {
                m_pAMatrix[i * MatrixA_ArrNum + j] -= x * m_pAMatrix[k * MatrixA_ArrNum + j];
            }
        }

    }
    for (k = m_iMjie - 1; k > 0; k--)
    {
        for (i = k - 1; i >= 0; i--)
        {
            m_pAMatrix[i * MatrixA_ArrNum + m_iMjie] -= m_pAMatrix[i * MatrixA_ArrNum + k] * m_pAMatrix[k * MatrixA_ArrNum + m_iMjie];
            m_pAMatrix[i * MatrixA_ArrNum + k] = 0;
        }
    }
    return 0;
}

/**
 *求误差的平方和
 * \return 误差的平方和
 */
//double CFitting::SD()
//{
//  int l,m;
//  double SD = 0, temp = 0;
//  for(l=0; l<m_iListLen; l++)
//  {
//      temp = 0;
//      for(m=0; m<m_iMjie; m++)
//          temp+=m_pdFinalCoef[m]*m_pCMatrix[l*m_iMjie+m];
//      temp-=m_pdYlist[l];
//      SD+=temp*temp;
//  }
//  return SD;
//}

/**
 *求相关系数R^2
 * \return 相关系数R^2
 */
// 函数 CFitting::RelatedCoef
// 作用：执行RelatedCoef。
// 参数：无。
// 返回：返回一个小数。
// 过程：函数里会调用 Sum、Aver、pow。
double CFitting::RelatedCoef()
{
    int l, m;
    double SD = 0, temp = 0, Var = 0, dRelatedCoef = 0;
    for (l = 0; l < m_iListLen; l++) //求标准差SD
    {
        temp = 0;
        for (m = 0; m < m_iMjie; m++)
        {
            temp += m_pdFinalCoef[m] * m_pCMatrix[l * m_iMjie + m];
        }
        temp -= m_pdYlist[l];
        SD += temp * temp;
    }

    temp = 0;
    for (l = 0; l < m_iListLen; l++) //求Var＝Sum(Yi-Aver(Yi))^2
    {
        temp += pow((m_pdYlist[l] - m_dYListAver), (double)2);
    }
    Var = temp;
    if (Var == 0)
    {
        Var = 0.000000001;
    }
    dRelatedCoef = 1 - SD / Var;
    return dRelatedCoef;
}


/**
 *
 * \param *x X列的值
 * \param *y Y列的值
 * \param *dCoef 外部调用的多项式拟和的系数数组
 * \param len X列和Y列的长度
 * \param m 多项式拟和的阶数
 * \return 各点误差的平方和
 */
// 函数 CFitting::SolutionCLEG
// 作用：执行SolutionCLEG。
// 参数：x；y；dCoef：小数；len；m。
// 返回：返回一个小数。失败时返回 FALSE。
// 过程：函数里会调用 FormCLEG、FormNormalEquation、Gauss、RelatedCoef、memcpy。
double CFitting::SolutionCLEG(double *x, double *y, double *dCoef, int len, int m) //求解
{
    int k, ErrCode = 0;
    double dbRelatedCoef = 0;
    double SumX = 0, SumY = 0;

    m_iListLen = len;
    m_iMjie = m;

    if (m_pdXlist != NULL)
    {
        delete m_pdXlist;
        m_pdXlist = NULL;
    }
    m_pdXlist = new double [m_iListLen];
    if (NULL == m_pdXlist)
    {
        return FALSE;
    }

    if (m_pdYlist != NULL)
    {
        delete m_pdYlist;
        m_pdYlist = NULL;
    }
    m_pdYlist = new double [m_iListLen];
    if (NULL == m_pdYlist)
    {
        return FALSE;
    }

    if (m_pdFinalCoef != NULL)
    {
        delete m_pdFinalCoef;
        m_pdFinalCoef = NULL;
    }
    m_pdFinalCoef = new double [m_iMjie];
    if (NULL == m_pdFinalCoef)
    {
        return FALSE;
    }

    for (k = 0; k < m_iListLen; k++)
    {
        m_pdXlist[k] = x[k];
        SumX = SumX + x[k];
        m_pdYlist[k] = y[k];
        SumY = SumY + y[k];
    }
    m_dXListAver = SumX / m_iListLen;
    m_dYListAver = SumY / m_iListLen;

    FormCLEG();
    FormNormalEquation();
    ErrCode = Gauss();
    if (ErrCode > 0)
    {
        return -2;
    }

    for (k = 0; k < m_iMjie; k++)
    {
        m_pdFinalCoef[k] = m_pAMatrix[k * (m_iMjie + 1) + m_iMjie];
    }

    dbRelatedCoef = RelatedCoef();

    memcpy(dCoef, m_pdFinalCoef, m_iMjie * 8);

    return dbRelatedCoef;
}

