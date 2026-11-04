// 【交接】 GeneralPcr\IconBtInfo.cpp
// 作用：IconBtInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CIconBtInfo、_T、Color。
#include "StdAfx.h"
#include "IconBtInfo.h"


// 函数 CIconBtInfo::CIconBtInfo
// 作用：执行CIconBtInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T、Color。
CIconBtInfo::CIconBtInfo(void)
{
	m_bUseIcon = TRUE;
	m_strIconPath = _T("");
	m_iSonIconNum = 1;
	m_bSonIconPosOrder = TRUE;

	m_bRoundRectBk = TRUE;
	m_iRoundRadius = 8;
	m_iBoderLineW = 1;

	int iAlpha = 255 * 0.2;
	m_clrFrameNormal = Color(iAlpha,0XFF,0XFF,0XFF);
	m_clrFrameHover = Color(iAlpha,0XFF,0XFF,0XFF);
	m_clrFrameSelected = Color(iAlpha,0X0,0X57,0X5F);
	m_clrFrameDisabled = Color(iAlpha,0X0,0X57,0X5F);
	m_clrNormal = COLOR_SOFT_THEME;
	m_clrHover = COLOR_SOFT_THEME;

	m_clrSelected = COLOR_2LEVEL_THEME;
	m_clrDisabled = COLOR_2LEVEL_THEME;

	m_bNormalNotFill = FALSE;
	m_bHoverNotFill = FALSE;
}

// 函数 CIconBtInfo::~CIconBtInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CIconBtInfo::~CIconBtInfo(void)
{

}

// 函数 CIconBtInfo::CIconBtInfo
// 作用：执行CIconBtInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CIconBtInfo::CIconBtInfo(const CIconBtInfo& info)
{
	m_bUseIcon = info.m_bUseIcon;
	m_strIconPath = info.m_strIconPath;
	m_iSonIconNum = info.m_iSonIconNum;
	m_bSonIconPosOrder = info.m_bSonIconPosOrder;

	m_bRoundRectBk = info.m_bRoundRectBk;
	m_iRoundRadius = info.m_iRoundRadius;
	m_iBoderLineW = info.m_iBoderLineW;

	m_rcIcon = info.m_rcIcon;
	m_rcText = info.m_rcText;

	m_clrFrameNormal = info.m_clrFrameNormal;
	m_clrFrameHover = info.m_clrFrameHover;
	m_clrFrameSelected = info.m_clrFrameSelected;
	m_clrFrameDisabled = info.m_clrFrameDisabled;

	m_clrNormal = info.m_clrNormal;
	m_clrHover = info.m_clrHover;
	m_clrSelected = info.m_clrSelected;
	m_clrDisabled = info.m_clrDisabled;

	m_bNormalNotFill = info.m_bNormalNotFill;
	m_bHoverNotFill = info.m_bHoverNotFill;
}

void CIconBtInfo::operator=(const CIconBtInfo& info)
{
	m_bUseIcon = info.m_bUseIcon;
	m_strIconPath = info.m_strIconPath;
	m_iSonIconNum = info.m_iSonIconNum;
	m_bSonIconPosOrder = info.m_bSonIconPosOrder;

	m_bRoundRectBk = info.m_bRoundRectBk;
	m_iRoundRadius = info.m_iRoundRadius;
	m_iBoderLineW = info.m_iBoderLineW;

	m_rcIcon = info.m_rcIcon;
	m_rcText = info.m_rcText;

	m_clrFrameNormal = info.m_clrFrameNormal;
	m_clrFrameHover = info.m_clrFrameHover;
	m_clrFrameSelected = info.m_clrFrameSelected;
	m_clrFrameDisabled = info.m_clrFrameDisabled;

	m_clrNormal = info.m_clrNormal;
	m_clrHover = info.m_clrHover;
	m_clrSelected = info.m_clrSelected;
	m_clrDisabled = info.m_clrDisabled;

	m_bNormalNotFill = info.m_bNormalNotFill;
	m_bHoverNotFill = info.m_bHoverNotFill;
}

