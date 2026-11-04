// 【交接】 PCRCtrlLib\PCRAlgorithmLib\DataAlgorithm.h
// 作用：DataAlgorithm。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CDataAlgorithm、Alspl、Amspl、Jbsqt、Kdspt、Kdspt7_3、Kdspt5_2、Kdspt7_2。
#pragma once

// 基础数据算法类

class AFX_EXT_CLASS CDataAlgorithm 
{
public:
	// 函数 CDataAlgorithm
	// 作用：执行CDataAlgorithm。
	// 参数：无。
	// 返回：没有返回值。
	CDataAlgorithm(void);
	// 函数 ~CDataAlgorithm
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CDataAlgorithm(void);
/*-----------------基本函数----------------------------------------------*/
//样条插值求一阶微分——1
	// 函数 Alspl
	// 作用：执行Alspl。
	// 参数：x0；h；n；y；k；t；s。
	// 返回：没有返回值。
	void Alspl(double x0,double h,int n,double *y,int k,double t, double *s);
//样条插值求一阶微分——2
	// 函数 Amspl
	// 作用：执行Amspl。
	// 参数：x；y；n；dy；ddy。
	// 返回：没有返回值。
	void Amspl(double *x,double *y,int n,double *dy,double *ddy);
//最小二乘拟合
	// 函数 Jbsqt
	// 作用：执行Jbsqt。
	// 参数：x；y；n；a；dt。
	// 返回：没有返回值。
	void Jbsqt(double *x,double *y,int n,double *a,double *dt);
//数字滤波器
	// 函数 Kdspt
	// 作用：执行Kdspt。
	// 参数：n；y；yy。
	// 返回：没有返回值。
	void Kdspt(int n, double *y, double *yy);
	// 函数 Kdspt7_3
	// 作用：执行Kdspt7_3。
	// 参数：n；y；yy。
	// 返回：没有返回值。
	void Kdspt7_3(int n,double *y,double *yy);
	// 函数 Kdspt5_2
	// 作用：执行Kdspt5_2。
	// 参数：n；y；yy。
	// 返回：没有返回值。
	void Kdspt5_2(int n,double *y,double *yy);
	// 函数 Kdspt7_2
	// 作用：执行Kdspt7_2。
	// 参数：n；y；yy。
	// 返回：没有返回值。
	void Kdspt7_2(int n,double *y,double *yy);
	// 函数 Kdspt_dtmean
	// 作用：执行Kdspt_dtmean。
	// 参数：n；dtnum；y；yy。
	// 返回：没有返回值。
	void Kdspt_dtmean(int n,int dtnum,double *y,double *yy);
	// 函数 Kdspt_cfmean
	// 作用：执行Kdspt_cfmean。
	// 参数：n；cfnum；y；yy。
	// 返回：没有返回值。
	void Kdspt_cfmean(int n,int cfnum,double *y,double *yy);//中心滑动滤波，dtnum 为奇数
	// 函数 Kdspt_TriangularSmooths_29
	// 作用：执行Kdspt_TriangularSmooths_29。
	// 参数：n；y；yy。
	// 返回：没有返回值。
	void Kdspt_TriangularSmooths_29(int n,double *y,double *yy);//29点三角平滑
	// 函数 Kdspt_GaussianSmooths_31
	// 作用：执行Kdspt_GaussianSmooths_31。
	// 参数：n；y；yy。
	// 返回：没有返回值。
	void Kdspt_GaussianSmooths_31(int n,double *y,double *yy);//31点伪高斯平滑
	// 函数 Kdspt_Median
	// 作用：执行Kdspt_Median。
	// 参数：n；cfnum；y；yy。
	// 返回：没有返回值。
	void Kdspt_Median(int n,int cfnum,double *y,double *yy); //中位数滤波
	// 函数 SortDouble
	// 作用：执行SortDouble。
	// 参数：nNum：整数；pInput：指针，指向调用方传入的对象；pOutput：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void SortDouble(int nNum, double *pInput, double *pOutput);
//样条插值
	// 函数 Akspl
	// 作用：执行Akspl。
	// 参数：x；y；n；k；t；s；bSpline：是或否。
	// 返回：没有返回值。
	void Akspl(double *x,double *y,int n,int k,double t,double *s,bool bSpline);
	// 函数 AksplEx
	// 作用：执行AksplEx。
	// 参数：x；y；n；k；t；s；bSpline：是或否。
	// 返回：没有返回值。
	void AksplEx(double *x,double *y,int n,int k,double t,double *s,bool bSpline);
//非方阵求逆，用于多项式拟合
	// 函数 Dginv
	// 作用：执行Dginv。
	// 参数：a；m；n；aa；eps；u；v；ka。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int Dginv(double *a,int m,int n,double *aa,double eps,double *u,double *v,int ka);
//Dluav, Sss, Ppp矩阵分解，用于求逆函数
	// 函数 Dluav
	// 作用：执行Dluav。
	// 参数：a；m；n；u；v；eps；ka。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int  Dluav(double *a,int m,int n,double *u,double *v,double eps,int ka);
	// 函数 Sss
	// 作用：执行Sss。
	// 参数：fg；cs：字符串。
	// 返回：没有返回值。
	void Sss(double *fg,double *cs);
	// 函数 Ppp
	// 作用：执行Ppp。
	// 参数：a；e；s；v；m；n。
	// 返回：没有返回值。
	void Ppp(double *a,double *e,double *s,double *v,int m,int n);
//矩阵乘法
	// 函数 Damul
	// 作用：执行Damul。
	// 参数：a；b；m；n；k；c。
	// 返回：没有返回值。
	void Damul(double *a,double *b,int m,int n,int k,double *c);

	
};
