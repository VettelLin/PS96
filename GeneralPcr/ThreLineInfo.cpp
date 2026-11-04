// 【交接】 GeneralPcr\ThreLineInfo.cpp
// 作用：ThreLineInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CThreLineInfo、Color、SetThreLineColor、GetThreLineColor、SetBeShow、GetBeShow、SetBeFirstDrawThreLline、GetBeFirstDrawThreLline。
#include "StdAfx.h"
#include "ThreLineInfo.h"

// 函数 CThreLineInfo::CThreLineInfo
// 作用：执行CThreLineInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 Color。
CThreLineInfo::CThreLineInfo(void)
{
	m_threLinePixelH = 1;
	m_threLineNormalWidth = 2;
	m_threLineHighLightWidth = 4;
	m_threLineDiscernHalfH = 2;
	m_clrThreLine = Color(0,0,0);
	m_bThreLineSel = FALSE;
	m_dThre = 1;
	m_dThreAuto = 0.1;
	m_bAutoThre = TRUE;
	m_bShow = TRUE;
	m_bFstDrawThreLine = TRUE;
}

// 函数 CThreLineInfo::~CThreLineInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CThreLineInfo::~CThreLineInfo(void)
{

}

// 函数 CThreLineInfo::CThreLineInfo
// 作用：执行CThreLineInfo。
// 参数：threLineInfo。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CThreLineInfo::CThreLineInfo(const CThreLineInfo& threLineInfo)
{
	m_threLinePixelH = threLineInfo.m_threLinePixelH;
	m_threLineNormalWidth = threLineInfo.m_threLineNormalWidth;
	m_threLineHighLightWidth = threLineInfo.m_threLineHighLightWidth;
	m_threLineDiscernHalfH = threLineInfo.m_threLineDiscernHalfH;
	m_clrThreLine = threLineInfo.m_clrThreLine;
	m_rcThreLine = threLineInfo.m_rcThreLine;
	m_bThreLineSel = threLineInfo.m_bThreLineSel;
	m_bShow = threLineInfo.m_bShow;
	m_bFstDrawThreLine = threLineInfo.m_bFstDrawThreLine;
	m_dThre = threLineInfo.m_dThre;
	m_dThreAuto = threLineInfo.m_dThreAuto;
	m_bAutoThre = threLineInfo.m_bAutoThre;
}

void CThreLineInfo::operator=(const CThreLineInfo& threLineInfo)
{
	m_threLinePixelH = threLineInfo.m_threLinePixelH;
	m_threLineNormalWidth = threLineInfo.m_threLineNormalWidth;
	m_threLineHighLightWidth = threLineInfo.m_threLineHighLightWidth;
	m_threLineDiscernHalfH = threLineInfo.m_threLineDiscernHalfH;
	m_clrThreLine = threLineInfo.m_clrThreLine;
	m_rcThreLine = threLineInfo.m_rcThreLine;
	m_bThreLineSel = threLineInfo.m_bThreLineSel;
	m_bShow = threLineInfo.m_bShow;
	m_bFstDrawThreLine = threLineInfo.m_bFstDrawThreLine;
	m_dThre = threLineInfo.m_dThre;
	m_dThreAuto = threLineInfo.m_dThreAuto;
	m_bAutoThre = threLineInfo.m_bAutoThre;
}

// 函数 CThreLineInfo::SetThreLineColor
// 作用：设置SetThreLineColor。
// 参数：clrThreLine：颜色。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CThreLineInfo::SetThreLineColor(Color clrThreLine)
{
	m_clrThreLine = clrThreLine;
	return;
}

// 函数 CThreLineInfo::GetThreLineColor
// 作用：读取GetThreLineColor。
// 参数：无。
// 返回：返回 Color。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
Color CThreLineInfo::GetThreLineColor()
{
	return m_clrThreLine;
}

// 函数 CThreLineInfo::SetBeShow
// 作用：设置SetBeShow。
// 参数：bShow：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CThreLineInfo::SetBeShow(BOOL bShow)
{
	m_bShow = bShow;
	return;
}

// 函数 CThreLineInfo::GetBeShow
// 作用：读取GetBeShow。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CThreLineInfo::GetBeShow()
{
	return m_bShow;
}

// 函数 CThreLineInfo::SetBeFirstDrawThreLline
// 作用：设置SetBeFirstDrawThreLline。
// 参数：bFstDrawThreLine：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CThreLineInfo::SetBeFirstDrawThreLline(BOOL bFstDrawThreLine)
{
	m_bFstDrawThreLine = bFstDrawThreLine;
	return;
}

// 函数 CThreLineInfo::GetBeFirstDrawThreLline
// 作用：读取GetBeFirstDrawThreLline。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CThreLineInfo::GetBeFirstDrawThreLline()
{
	return m_bFstDrawThreLine;
}

// 函数 CThreLineInfo::SetThreLineValue
// 作用：设置SetThreLineValue。
// 参数：threLineValue。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CThreLineInfo::SetThreLineValue(double threLineValue)
{
	m_dThre = threLineValue;
	return;
}

// 函数 CThreLineInfo::GetThreLineValue
// 作用：读取GetThreLineValue。
// 参数：无。
// 返回：返回一个小数。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
double CThreLineInfo::GetThreLineValue()
{
	//if(m_bAutoThre)
	//{
	//	return m_dThreAuto;
	//}
	//else
	{
		return m_dThre;
	}
}







