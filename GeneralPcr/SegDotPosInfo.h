// 【交接】 GeneralPcr\SegDotPosInfo.h
// 作用：SegDotPosInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CSegDotPosInfo、BeValidStepEmptyPos、BeValidSegmentEmptyPos。
#pragma once

typedef enum DotPosType{
	EDP_CYCLE = 1,EDP_TEM,EDP_TIME,EDP_COLLECTFLU,EDP_NONE,EDP_LINE,EDP_SEGNAME,EDP_HORISCROLL,EDP_VERTSCROLL,EDP_SEGEMPTY
}EDOTPOSTYPE;

class CSegDotPosInfo
{
public:
	// 函数 CSegDotPosInfo
	// 作用：执行CSegDotPosInfo。
	// 参数：无。
	// 返回：没有返回值。
	CSegDotPosInfo(void);
	// 函数 ~CSegDotPosInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSegDotPosInfo(void);

	// 函数 CSegDotPosInfo
	// 作用：执行CSegDotPosInfo。
	// 参数：segDotPosInfo。
	// 返回：没有返回值。
	CSegDotPosInfo(const CSegDotPosInfo& segDotPosInfo);
	void operator=(const CSegDotPosInfo& segDotPosInfo);

	// 函数 BeValidStepEmptyPos
	// 作用：判断BeValidStepEmptyPos是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL BeValidStepEmptyPos();	//是否是Step空白区域，相对于空白区域、标题区域和Step可编辑区域
	// 函数 BeValidSegmentEmptyPos
	// 作用：判断BeValidSegmentEmptyPos是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL BeValidSegmentEmptyPos();	//是否是Segment空白区域，相对于Segment名称和循环数区域

public:
	int m_seg;
	int m_step;
	EDOTPOSTYPE m_eDotPosType;

	CRect m_rcItem;
	CPoint m_pt;
};

