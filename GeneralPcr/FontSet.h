// 【交接】 GeneralPcr\FontSet.h
// 作用：FontSet。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CFontSet、SetMyFont、SetMyFontChecked、InitFont、GetLogFont、GetLogFontChecked、SetCfsTextClr、GetCfsTextClr。

#pragma once

#include <string>
#include "EnumFtUnitType.h"

using namespace std;

class CFontSet
{
public:
	// 函数 CFontSet
	// 作用：执行CFontSet。
	// 参数：bCkBt：是或否。
	// 返回：没有返回值。
	CFontSet(BOOL bCkBt = FALSE);
	// 函数 ~CFontSet
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CFontSet();

public:
	CFont m_fontSet;
	LOGFONT m_logFont;
	CFont m_fontSetChecked;
	LOGFONT m_logFontChecked;

	COLORREF m_cfsTxClr;
	COLORREF m_txClr1;

	int m_fontOriginalHeight;
	int m_fontOriginHChecked;

	static int fontSetDesDpi;
	static int GeneDpi;
	static CRect GeneCRDlg;
	static int m_uiGeneDesDpi;
	static int m_uiGeneDesWidth;
	static int m_uiGeneDesHeight;
	static int GeneScreenXWidth;
	static int GeneScreenYHeight;

	static double m_dHoriRatio;
	static double m_dVertRatio;
	static double m_dTxRatio;	//文字大小自动适配比率值，用于缩放
	static CString m_stTxFont;	//记录字体名称

private:
	BOOL m_bCkBt;

public:
	// 函数 SetMyFont
	// 作用：设置SetMyFont。
	// 参数：无。
	// 返回：没有返回值。
	void SetMyFont();
	// 函数 SetMyFontChecked
	// 作用：设置SetMyFontChecked。
	// 参数：无。
	// 返回：没有返回值。
	void SetMyFontChecked();
	// 函数 SetMyFont
	// 作用：设置SetMyFont。
	// 参数：logFont。
	// 返回：没有返回值。
	void SetMyFont(LOGFONT& logFont);
	// 函数 SetMyFont
	// 作用：设置SetMyFont。
	// 参数：nHeight：整数；fontUnitType。
	// 返回：没有返回值。
	void SetMyFont(int nHeight,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL);  //nHeight单位为 磅，即1/72英寸
	// 函数 SetMyFont
	// 作用：设置SetMyFont。
	// 参数：fontName。
	// 返回：没有返回值。
	void SetMyFont(CString fontName);
	// 函数 SetMyFont
	// 作用：设置SetMyFont。
	// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
	// 返回：没有返回值。
	void SetMyFont(CString fontName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL); //nHeight单位为 磅，即1/72英寸
	// 函数 SetMyFontChecked
	// 作用：设置SetMyFontChecked。
	// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
	// 返回：没有返回值。
	void SetMyFontChecked(CString fontName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL); //nHeight单位为 磅，即1/72英寸
	// 函数 InitFont
	// 作用：初始化InitFont。
	// 参数：lfHeight。
	// 返回：没有返回值。
	void InitFont(int lfHeight);  //默认字体为“微软雅黑”，高度为17像素值
	// 函数 GetLogFont
	// 作用：读取GetLogFont。
	// 参数：无。
	// 返回：返回 LOGFONT&。
	LOGFONT& GetLogFont();
	// 函数 GetLogFontChecked
	// 作用：读取GetLogFontChecked。
	// 参数：无。
	// 返回：返回 LOGFONT&。
	LOGFONT& GetLogFontChecked();

	// 函数 SetCfsTextClr
	// 作用：设置SetCfsTextClr。
	// 参数：txClr。
	// 返回：没有返回值。
	void SetCfsTextClr(COLORREF txClr);
	// 函数 GetCfsTextClr
	// 作用：读取GetCfsTextClr。
	// 参数：无。
	// 返回：返回 COLORREF&。
	COLORREF& GetCfsTextClr();

	// 函数 SetTextClr1
	// 作用：设置SetTextClr1。
	// 参数：txClr。
	// 返回：没有返回值。
	void SetTextClr1(COLORREF txClr);
	// 函数 GetTextClr1
	// 作用：读取GetTextClr1。
	// 参数：无。
	// 返回：返回 COLORREF&。
	COLORREF& GetTextClr1();

	// 函数 SetMultiDpiAdaptive
	// 作用：设置SetMultiDpiAdaptive。
	// 参数：无。
	// 返回：没有返回值。
	void SetMultiDpiAdaptive();	//窗口中直接输出文字时，需使用此函数适配字体大小
};

