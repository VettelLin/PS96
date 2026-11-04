// 【交接】 GeneralPcr\LinearFitData.h
// 作用：LinearFitData 曲线拟合。给标准曲线或扩增曲线提供数学拟合，不直接判断阴阳性。
// 先看这些函数：CLinearFitData、Clear、SetDataNum、LeastSquare。
#pragma once
class CLinearFitData
{
public:
	// 函数 CLinearFitData
	// 作用：执行CLinearFitData。
	// 参数：无。
	// 返回：没有返回值。
	CLinearFitData(void);
	// 函数 ~CLinearFitData
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLinearFitData(void);

	// 函数 CLinearFitData
	// 作用：执行CLinearFitData。
	// 参数：data。
	// 返回：没有返回值。
	CLinearFitData(const CLinearFitData& data);
	void operator=(const CLinearFitData& data);
	BOOL operator==(const CLinearFitData& data);

	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();
	
	// 函数 SetDataNum
	// 作用：设置SetDataNum。
	// 参数：iDataNum：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int SetDataNum(int iDataNum);

	// 函数 LeastSquare
	// 作用：执行LeastSquare。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int LeastSquare();

public:
	double* m_pDX;
	double* m_pDY;
	
	double m_dSlope;
	double m_dIntercept;
	double m_dSquare;

	int m_iDataNum;
};

