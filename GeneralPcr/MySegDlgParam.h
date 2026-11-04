// 【交接】 GeneralPcr\MySegDlgParam.h
// 作用：MySegDlgParam 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：CMySegDlgParam。
#pragma once

class CMySegDlgParam
{
public:
	// 函数 CMySegDlgParam
	// 作用：执行CMySegDlgParam。
	// 参数：无。
	// 返回：没有返回值。
	CMySegDlgParam(void);
	// 函数 ~CMySegDlgParam
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMySegDlgParam(void);

	// 函数 CMySegDlgParam
	// 作用：执行CMySegDlgParam。
	// 参数：segDlgParam。
	// 返回：没有返回值。
	CMySegDlgParam(const CMySegDlgParam& segDlgParam);
	void operator=(const CMySegDlgParam& segDlgParam);

public:
	COLORREF m_clrGeneral;
	COLORREF m_clrStepTag;
	COLORREF m_clrSegTag;
	COLORREF m_clrRunning;
};

