// 【交接】 GeneralPcr\ThreLineInfo.h
// 作用：ThreLineInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CThreLineInfo、SetThreLineColor、GetThreLineColor、SetBeShow、GetBeShow、SetBeFirstDrawThreLline、GetBeFirstDrawThreLline、SetThreLineValue。
#pragma once

#include <GdiPlus.h>

using namespace Gdiplus;

class CThreLineInfo
{
public:
	// 函数 CThreLineInfo
	// 作用：执行CThreLineInfo。
	// 参数：无。
	// 返回：没有返回值。
	CThreLineInfo(void);
	// 函数 ~CThreLineInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CThreLineInfo(void);

	// 函数 CThreLineInfo
	// 作用：执行CThreLineInfo。
	// 参数：threLineInfo。
	// 返回：没有返回值。
	CThreLineInfo(const CThreLineInfo& threLineInfo);
	void operator=(const CThreLineInfo& threLineInfo);

	// 函数 SetThreLineColor
	// 作用：设置SetThreLineColor。
	// 参数：clrThreLine：颜色。
	// 返回：没有返回值。
	void SetThreLineColor(Color clrThreLine);
	// 函数 GetThreLineColor
	// 作用：读取GetThreLineColor。
	// 参数：无。
	// 返回：返回 Color。
	Color GetThreLineColor();

	// 函数 SetBeShow
	// 作用：设置SetBeShow。
	// 参数：bShow：是或否。
	// 返回：没有返回值。
	void SetBeShow(BOOL bShow);
	// 函数 GetBeShow
	// 作用：读取GetBeShow。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeShow();

	// 函数 SetBeFirstDrawThreLline
	// 作用：设置SetBeFirstDrawThreLline。
	// 参数：bFstDrawThreLine：是或否。
	// 返回：没有返回值。
	void SetBeFirstDrawThreLline(BOOL bFstDrawThreLine);
	// 函数 GetBeFirstDrawThreLline
	// 作用：读取GetBeFirstDrawThreLline。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeFirstDrawThreLline();

	// 函数 SetThreLineValue
	// 作用：设置SetThreLineValue。
	// 参数：threLineValue。
	// 返回：没有返回值。
	void SetThreLineValue(double threLineValue);
	// 函数 GetThreLineValue
	// 作用：读取GetThreLineValue。
	// 参数：无。
	// 返回：返回一个小数。
	double GetThreLineValue();

public:
	int m_threLinePixelH;	//阈值线对应的像素高度
	int m_threLineNormalWidth;	//阈值线普通状态宽度
	int m_threLineHighLightWidth;	//阈值线高亮状态宽度
	int m_threLineDiscernHalfH;	//阈值线识别（扩展半径，线宽 + 扩展半径 * 2）
	
	Color m_clrThreLine;
	CRect m_rcThreLine;

	BOOL m_bFstDrawThreLine;
	BOOL m_bThreLineSel;
	BOOL m_bAutoThre;
	double m_dThre;	//手动阈值
	double m_dThreAuto;	//自动阈值

protected:
	BOOL m_bShow;
};

