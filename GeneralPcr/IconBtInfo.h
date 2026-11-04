// 【交接】 GeneralPcr\IconBtInfo.h
// 作用：IconBtInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CIconBtInfo。
#pragma once

#include <GdiPlus.h>

class CIconBtInfo
{
public:
	// 函数 CIconBtInfo
	// 作用：执行CIconBtInfo。
	// 参数：无。
	// 返回：没有返回值。
	CIconBtInfo(void);
	// 函数 ~CIconBtInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CIconBtInfo(void);

	// 函数 CIconBtInfo
	// 作用：执行CIconBtInfo。
	// 参数：info。
	// 返回：没有返回值。
	CIconBtInfo(const CIconBtInfo& info);
	void operator=(const CIconBtInfo& info);

public:
	BOOL m_bUseIcon;
	CString m_strIconPath;
	int m_iSonIconNum;
	BOOL m_bSonIconPosOrder;	//子图标是否按照正序排列

	Rect m_rcIcon;
	CRect m_rcText;

	BOOL m_bRoundRectBk;
	int m_iRoundRadius;
	int m_iBoderLineW;

	Color m_clrFrameNormal;
	Color m_clrFrameHover;
	Color m_clrFrameSelected;
	Color m_clrFrameDisabled;

	Color m_clrNormal;
	Color m_clrHover;
	Color m_clrSelected;
	Color m_clrDisabled;

	BOOL m_bNormalNotFill;	//普通状态下不填充圆角矩形
	BOOL m_bHoverNotFill;	//悬浮状态下不填充圆角矩形
};

