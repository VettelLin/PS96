// 【交接】 GeneralPcr\FtSetDensity.cpp
// 作用：FtSetDensity。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CFtSetDensity、InitFontDensity、DeleteObject、_tcscpy、CreateFontIndirect、SetMyDensityFont、double。
#include "StdAfx.h"
#include "FtSetDensity.h"
#include "FontSet.h"

// 函数 CFtSetDensity::CFtSetDensity
// 作用：执行CFtSetDensity。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 InitFontDensity。
CFtSetDensity::CFtSetDensity(void)
{
	InitFontDensity(16);
}

// 函数 CFtSetDensity::~CFtSetDensity
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject。
CFtSetDensity::~CFtSetDensity(void)
{
	m_ftDensity.DeleteObject();
}

// 函数 CFtSetDensity::InitFontDensity
// 作用：初始化InitFontDensity。
// 参数：lfHeight。
// 返回：没有返回值。
// 过程：函数里会调用 _tcscpy、_T、CreateFontIndirect。
void CFtSetDensity::InitFontDensity(int lfHeight)
{
	m_logFtDensity.lfHeight = lfHeight;
	m_logFtDensity.lfWidth = 0;
	m_logFtDensity.lfEscapement = 0;
	m_logFtDensity.lfOrientation = 400;
	m_logFtDensity.lfWeight = FW_NORMAL;
	m_logFtDensity.lfItalic = FALSE;
	m_logFtDensity.lfUnderline = FALSE;
	m_logFtDensity.lfStrikeOut = 0;
	m_logFtDensity.lfCharSet = ANSI_CHARSET;
	m_logFtDensity.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_logFtDensity.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_logFtDensity.lfQuality = PROOF_QUALITY;
	m_logFtDensity.lfPitchAndFamily = VARIABLE_PITCH | FF_SCRIPT;
	_tcscpy(m_logFtDensity.lfFaceName,  _T("微软雅黑"));

	m_ftDensity.CreateFontIndirect(&m_logFtDensity);  
}

// 函数 CFtSetDensity::SetMyDensityFont
// 作用：设置SetMyDensityFont。
// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
// 返回：没有返回值。
// 过程：函数里会调用 double、_tcscpy、DeleteObject、CreateFontIndirect。
void CFtSetDensity::SetMyDensityFont(CString fontName,int nHeight,int nWeight /*= FW_NORMAL*/,FONT_UNIT_TYPE fontUnitType /*= TYPE_PIXEL*/) //nHeight单位为 磅，即1/72英寸
{
	if(TYPE_POUND == fontUnitType)
	{
		m_logFtDensity.lfHeight = (double(nHeight * CFontSet::fontSetDesDpi))/ 72;
	}
	else
	{
		m_logFtDensity.lfHeight = nHeight;
	}

	_tcscpy(m_logFtDensity.lfFaceName, fontName);
	m_logFtDensity.lfWeight = nWeight;
	m_ftDensity.DeleteObject();
	m_ftDensity.CreateFontIndirect(&m_logFtDensity);
}

// 函数 CFtSetDensity::SetMyDensityFont
// 作用：设置SetMyDensityFont。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject、CreateFontIndirect。
void CFtSetDensity::SetMyDensityFont() 
{
	m_ftDensity.DeleteObject();
	m_ftDensity.CreateFontIndirect(&m_logFtDensity);
}

