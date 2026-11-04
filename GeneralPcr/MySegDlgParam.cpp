// 【交接】 GeneralPcr\MySegDlgParam.cpp
// 作用：MySegDlgParam 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：CMySegDlgParam、RGB。
#include "StdAfx.h"
#include "MySegDlgParam.h"


// 函数 CMySegDlgParam::CMySegDlgParam
// 作用：执行CMySegDlgParam。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 RGB。
CMySegDlgParam::CMySegDlgParam(void)
{
	m_clrGeneral = CLR_2LEVEL_THEME;
	m_clrStepTag = RGB(0X66,0X66,0X66);
	m_clrSegTag = RGB(0X39,0X45,0X65);
	m_clrRunning = RGB(0XFF,0XFF,0XFF);
}

// 函数 CMySegDlgParam::~CMySegDlgParam
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMySegDlgParam::~CMySegDlgParam(void)
{

}

// 函数 CMySegDlgParam::CMySegDlgParam
// 作用：执行CMySegDlgParam。
// 参数：segDlgParam。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMySegDlgParam::CMySegDlgParam(const CMySegDlgParam& segDlgParam)
{
	m_clrGeneral = segDlgParam.m_clrGeneral;
	m_clrStepTag = segDlgParam.m_clrStepTag;
	m_clrSegTag = segDlgParam.m_clrSegTag;
	m_clrRunning = segDlgParam.m_clrRunning;
}

void CMySegDlgParam::operator=(const CMySegDlgParam& segDlgParam)
{
	m_clrGeneral = segDlgParam.m_clrGeneral;
	m_clrStepTag = segDlgParam.m_clrStepTag;
	m_clrSegTag = segDlgParam.m_clrSegTag;
	m_clrRunning = segDlgParam.m_clrRunning;
}
