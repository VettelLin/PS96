// 【交接】 GeneralPcr\FontSet.cpp
// 作用：FontSet。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CRect、CFontSet、RGB、InitFont、DeleteObject、SetMyFont、CreateFontIndirect、double。

#include "stdafx.h"
#include "FontSet.h"

int CFontSet::fontSetDesDpi = 96;

int CFontSet::GeneDpi = 96;
CRect CFontSet::GeneCRDlg = CRect(0,0,1920,1080);
int CFontSet::m_uiGeneDesDpi = 96;
int CFontSet::m_uiGeneDesWidth = 1920;
int CFontSet::m_uiGeneDesHeight = 1030;
int CFontSet::GeneScreenXWidth = 1920;
int CFontSet::GeneScreenYHeight = 1080;

double CFontSet::m_dHoriRatio = 1;
double CFontSet::m_dVertRatio = 1;
double CFontSet::m_dTxRatio = 1;
CString CFontSet::m_stTxFont = TEXTFONT_CHINESE;

// 函数 CFontSet::CFontSet
// 作用：执行CFontSet。
// 参数：bCkBt：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 RGB、InitFont。
CFontSet::CFontSet(BOOL bCkBt /*= FALSE*/)
{
	m_bCkBt = bCkBt;
	m_cfsTxClr = RGB(0,0,0);
	m_txClr1 = RGB(0,0,0);
	InitFont(16);
}

// 函数 CFontSet::~CFontSet
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject。
CFontSet::~CFontSet()
{
	m_fontSet.DeleteObject();
	if(m_bCkBt)
	{
		m_fontSetChecked.DeleteObject();
	}
}

// 函数 CFontSet::SetMyFont
// 作用：设置SetMyFont。
// 参数：logFont。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、CreateFontIndirect。
void CFontSet::SetMyFont(LOGFONT& logFont)
{
	m_fontSet.DeleteObject();
	m_fontSet.CreateFontIndirect(&logFont);
}

// 函数 CFontSet::SetMyFont
// 作用：设置SetMyFont。
// 参数：nHeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double。
void CFontSet::SetMyFont(int nHeight,FONT_UNIT_TYPE fontUnitType /*= TYPE_PIXEL*/)  //nHeight单位为 磅，即1/72英寸
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFont.lfHeight = (double(nHeight * fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFont.lfHeight = nHeight;
	}
	SetMyFont();
	m_fontOriginalHeight = m_logFont.lfHeight;
}

// 函数 CFontSet::SetMyFont
// 作用：设置SetMyFont。
// 参数：fontName。
// 返回：没有返回值。
// 过程：函数里会调用 _tcscpy。
void CFontSet::SetMyFont(CString fontName)
{
	_tcscpy(m_logFont.lfFaceName, fontName);
	SetMyFont();
}

// 函数 CFontSet::SetMyFont
// 作用：设置SetMyFont。
// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double、_tcscpy。
void CFontSet::SetMyFont(CString fontName,int nHeight,int nWeight /*= FW_NORMAL*/,FONT_UNIT_TYPE fontUnitType /*= TYPE_PIXEL*/) //nHeight单位为 磅，即1/72英寸
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFont.lfHeight = (double(nHeight * fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFont.lfHeight = nHeight;
	}
	
	_tcscpy(m_logFont.lfFaceName, fontName);
	m_logFont.lfWeight = nWeight;
	SetMyFont();
	m_fontOriginalHeight = m_logFont.lfHeight;
}

// 函数 CFontSet::SetMyFont
// 作用：设置SetMyFont。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、CreateFontIndirect。
void CFontSet::SetMyFont()
{
	m_fontSet.DeleteObject();
	m_fontSet.CreateFontIndirect(&m_logFont);
}

// 函数 CFontSet::SetMyFontChecked
// 作用：设置SetMyFontChecked。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、CreateFontIndirect。
void CFontSet::SetMyFontChecked()
{
	m_fontSetChecked.DeleteObject();
	m_fontSetChecked.CreateFontIndirect(&m_logFontChecked);
}

// 函数 CFontSet::SetMyFontChecked
// 作用：设置SetMyFontChecked。
// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double、_tcscpy。
void CFontSet::SetMyFontChecked(CString fontName,int nHeight,int nWeight /*= FW_NORMAL*/,FONT_UNIT_TYPE fontUnitType /*= TYPE_PIXEL*/)
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFontChecked.lfHeight = (double(nHeight * fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFontChecked.lfHeight = nHeight;
	}
	
	_tcscpy(m_logFontChecked.lfFaceName,fontName);
	m_logFontChecked.lfWeight = nWeight;
	SetMyFontChecked();
	m_fontOriginHChecked = m_logFontChecked.lfHeight;
}

// 函数 CFontSet::InitFont
// 作用：初始化InitFont。
// 参数：lfHeight。
// 返回：没有返回值。
// 过程：函数里会调用 _tcscpy、_T、CreateFontIndirect。
void CFontSet::InitFont(int lfHeight)
{
	m_logFont.lfHeight = lfHeight;
	m_logFont.lfWidth = 0;
	m_logFont.lfEscapement = 0;
	m_logFont.lfOrientation = 400;
	m_logFont.lfWeight = FW_NORMAL;
	m_logFont.lfItalic = FALSE;
	m_logFont.lfUnderline = FALSE;
	m_logFont.lfStrikeOut = 0;
	m_logFont.lfCharSet = /*GB2312_CHARSET*/ANSI_CHARSET;
	m_logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logFont.lfQuality = PROOF_QUALITY;
	m_logFont.lfPitchAndFamily = VARIABLE_PITCH | FF_SCRIPT;
	_tcscpy(m_logFont.lfFaceName,  _T("微软雅黑"));

	m_fontSet.CreateFontIndirect(&m_logFont);  
	m_fontOriginalHeight = 17;

	if(m_bCkBt)
	{
		m_logFontChecked.lfHeight = lfHeight;
		m_logFontChecked.lfWidth = 0;
		m_logFontChecked.lfEscapement = 0;
		m_logFontChecked.lfOrientation = 400;
		m_logFontChecked.lfWeight = FW_NORMAL;
		m_logFontChecked.lfItalic = FALSE;
		m_logFontChecked.lfUnderline = FALSE;
		m_logFontChecked.lfStrikeOut = 0;
		m_logFontChecked.lfCharSet = ANSI_CHARSET;
		m_logFontChecked.lfOutPrecision = OUT_DEFAULT_PRECIS;
		m_logFontChecked.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		m_logFontChecked.lfQuality = PROOF_QUALITY;
		m_logFontChecked.lfPitchAndFamily = VARIABLE_PITCH | FF_SCRIPT;
		_tcscpy(m_logFontChecked.lfFaceName,  _T("微软雅黑"));

		m_fontSetChecked.CreateFontIndirect(&m_logFont);  
		m_fontOriginHChecked = 17;
	}
}

// 函数 CFontSet::GetLogFont
// 作用：读取GetLogFont。
// 参数：无。
// 返回：返回 LOGFONT&。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
LOGFONT& CFontSet::GetLogFont()
{
	return m_logFont;
}

// 函数 CFontSet::GetLogFontChecked
// 作用：读取GetLogFontChecked。
// 参数：无。
// 返回：返回 LOGFONT&。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
LOGFONT& CFontSet::GetLogFontChecked()
{
	return m_logFontChecked;
}

// 函数 CFontSet::SetCfsTextClr
// 作用：设置SetCfsTextClr。
// 参数：txClr。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFontSet::SetCfsTextClr(COLORREF txClr)
{
	m_cfsTxClr = txClr;
}

// 函数 CFontSet::GetCfsTextClr
// 作用：读取GetCfsTextClr。
// 参数：无。
// 返回：返回 COLORREF&。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF& CFontSet::GetCfsTextClr()
{
	return m_cfsTxClr;
}

// 函数 CFontSet::SetTextClr1
// 作用：设置SetTextClr1。
// 参数：txClr。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CFontSet::SetTextClr1(COLORREF txClr)
{
	m_txClr1 = txClr;
}

// 函数 CFontSet::GetTextClr1
// 作用：读取GetTextClr1。
// 参数：无。
// 返回：返回 COLORREF&。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF& CFontSet::GetTextClr1()
{
	return m_txClr1;
}

// 函数 CFontSet::SetMultiDpiAdaptive
// 作用：设置SetMultiDpiAdaptive。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 double、GetLogFont、Width、Height、SetMyFont。
void CFontSet::SetMultiDpiAdaptive()
{
	double horiFontRatio = (double(m_fontOriginalHeight * GeneDpi)) / m_uiGeneDesDpi / GeneScreenXWidth;
	double verFontRatio = (double(m_fontOriginalHeight * GeneDpi)) / m_uiGeneDesDpi / GeneScreenYHeight;
	GetLogFont().lfHeight = GeneCRDlg.Width() * horiFontRatio * 0.5 + GeneCRDlg.Height() * verFontRatio * 0.5;
	SetMyFont();
}
