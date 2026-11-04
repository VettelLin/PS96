// 【交接】 GeneralPcr\FtSetDensity.h
// 作用：FtSetDensity。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CFtSetDensity、InitFontDensity、SetMyDensityFont。
#pragma once

#include "EnumFtUnitType.h"

class CFtSetDensity
{
public:
	// 函数 CFtSetDensity
	// 作用：执行CFtSetDensity。
	// 参数：无。
	// 返回：没有返回值。
	CFtSetDensity(void);
	// 函数 ~CFtSetDensity
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CFtSetDensity(void);

	// 函数 InitFontDensity
	// 作用：初始化InitFontDensity。
	// 参数：lfHeight。
	// 返回：没有返回值。
	void InitFontDensity(int lfHeight);
	// 函数 SetMyDensityFont
	// 作用：设置SetMyDensityFont。
	// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
	// 返回：没有返回值。
	void SetMyDensityFont(CString fontName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL); //磅，即1/72英寸;
	// 函数 SetMyDensityFont
	// 作用：设置SetMyDensityFont。
	// 参数：无。
	// 返回：没有返回值。
	void SetMyDensityFont();

public:
	CFont m_ftDensity;
	LOGFONT m_logFtDensity;
};

