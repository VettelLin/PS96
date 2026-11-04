// 【交接】 GeneralPcr\Algorithm.h
// 作用：Algorithm。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：Sum、MultiSum、RelatePow、RelateMultiXY、EMatrix、CalEquation、F。
#pragma once

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//最小二乘法拟合相关函数定义
double Sum(vector<double> vecData);
double MultiSum(vector<double> vecX,vector<double> vecY);
double RelatePow(vector<double> vecX,int n,int ex);
double RelateMultiXY(vector<double> vecX,vector<double> vecY,int n,int ex);

//计算方程的增广矩阵
void EMatrix(vector<double> vecX,vector<double> vecY,int n,int ex,double coefficient[]);

//求解方程
void CalEquation(int exp,double coefficient[]);
double F(double c[],int l,int m);
