// 【交接】 GeneralPcr\LineInfo.h
// 作用：LineInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CLineInfo、AddDot、SetLinearFitData、SetExpressionShowState、GetExpressionShowState、BeHaveFitData、GetDotXYMinMax、GetLineXYMinMax。
#pragma once

#include <vector>
#include "MyPoint.h"
#include "LinkList.h"
#include "AlgorithmSet.h"
#include "LinearFitData.h"

using namespace std;

class CLineInfo
{
public:
	// 函数 CLineInfo
	// 作用：执行CLineInfo。
	// 参数：无。
	// 返回：没有返回值。
	CLineInfo(void);
	// 函数 ~CLineInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLineInfo(void);

	// 函数 CLineInfo
	// 作用：执行CLineInfo。
	// 参数：lineInfo。
	// 返回：没有返回值。
	CLineInfo(const CLineInfo& lineInfo);
	void operator=(const CLineInfo& lineInfo);

	// 函数 AddDot
	// 作用：创建或加入AddDot。
	// 参数：pt。
	// 返回：没有返回值。
	void AddDot(CMyPoint& pt);

	// 函数 SetLinearFitData
	// 作用：设置SetLinearFitData。
	// 参数：pLinearFitData：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int SetLinearFitData(LINEARFITDATA* pLinearFitData);
	// 函数 SetLinearFitData
	// 作用：设置SetLinearFitData。
	// 参数：pLinearFitData：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int SetLinearFitData(CLinearFitData* pLinearFitData);

	// 函数 SetExpressionShowState
	// 作用：设置SetExpressionShowState。
	// 参数：bShowExpression：是或否。
	// 返回：没有返回值。
	void SetExpressionShowState(BOOL bShowExpression);
	// 函数 GetExpressionShowState
	// 作用：读取GetExpressionShowState。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetExpressionShowState();
	// 函数 BeHaveFitData
	// 作用：判断BeHaveFitData是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL BeHaveFitData();
	// 函数 GetDotXYMinMax
	// 作用：读取GetDotXYMinMax。
	// 参数：minX；maxX；minY；maxY。
	// 返回：返回是或否。
	BOOL GetDotXYMinMax(double& minX,double& maxX,double& minY,double& maxY);	//获取表达式拟合前数据点最大值最小值
	// 函数 GetLineXYMinMax
	// 作用：读取GetLineXYMinMax。
	// 参数：minX；maxX；minY；maxY。
	// 返回：返回是或否。
	BOOL GetLineXYMinMax(double& minX,double& maxX,double& minY,double& maxY);	//获取表达式拟合后线段数据点最大值最小值

	// 函数 SetChanId
	// 作用：设置SetChanId。
	// 参数：iChanId：整数。
	// 返回：没有返回值。
	void SetChanId(int iChanId);
	// 函数 GetChanId
	// 作用：读取GetChanId。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetChanId();

	// 函数 SetDyeName
	// 作用：设置SetDyeName。
	// 参数：strData：字符串。
	// 返回：没有返回值。
	void SetDyeName(CString strData);
	// 函数 GetDyeName
	// 作用：读取GetDyeName。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetDyeName();

	// 函数 GetGeneralDotMinMax
	// 作用：读取GetGeneralDotMinMax。
	// 参数：minX；maxX；minY；maxY。
	// 返回：返回是或否。
	BOOL GetGeneralDotMinMax(double& minX,double& maxX,double& minY,double& maxY);

	// 函数 GetLineClr
	// 作用：读取GetLineClr。
	// 参数：eGetLineClr。
	// 返回：返回 COLORREF。
	COLORREF GetLineClr(ELINECLRMODE eGetLineClr);

	// 函数 SetBeXAxisMillisecondTime
	// 作用：设置SetBeXAxisMillisecondTime。
	// 参数：bXAxisMsTime：是或否。
	// 返回：没有返回值。
	void SetBeXAxisMillisecondTime(BOOL bXAxisMsTime);
	// 函数 GetBeXAxisMillisecondTime
	// 作用：读取GetBeXAxisMillisecondTime。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeXAxisMillisecondTime();

	// 函数 GetEfficiencyString
	// 作用：读取GetEfficiencyString。
	// 参数：//获取字符串形式的扩增效率(默认按照百分比格式输出，保留两位小数。
	// 返回：返回一段文字。
	CString GetEfficiencyString();	//获取字符串形式的扩增效率(默认按照百分比格式输出，保留两位小数)

	// 函数 GetExpressionString
	// 作用：读取GetExpressionString。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetExpressionString();	//获取表达式信息

	// 函数 IsExpressionVisible
	// 作用：判断IsExpressionVisible是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL IsExpressionVisible();	//获取“关系式是否可视”
	// 函数 HasLineData
	// 作用：判断HasLineData是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL HasLineData();

public:
	int m_tubeId;
	int m_rowId;
	int m_colId;
	int m_chanId;
	BOOL m_bShow;
	CString m_strDyeName;	//染料名称
	CString m_strTaget;	//基因名称
	CString m_strHoleTag;	//孔位标识"A1"

	CLinkList<CMyPoint> m_lnkDots;
	COLORREF m_lineClr;

	static COLORREF m_staChanClr[6];	//通道默认颜色

	//记录标曲
	LINEARFITDATA m_linearFitData;
	CMyPoint m_linearMinPt;
	CMyPoint m_linearMaxPt;
	BOOL m_bShowExpression;	//是否显示曲线关系式

	double m_dEfficiency;	//扩增效率

protected:
	BOOL m_bXAxisMsTime;	//横坐标是否是毫秒时间
};

