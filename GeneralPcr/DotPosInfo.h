// 【交接】 GeneralPcr\DotPosInfo.h
// 作用：DotPosInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CDotPosInfo、BeSameRowCol、BeSameRow、BeSameCol、BeValidCellPos。
#pragma once

typedef enum MyLstDotPosType{
	EDT_FRAME,EDT_HEADER,EDT_TOTALHEADER,EDT_ROWHEADER,EDT_COLHEADER,EDT_BODY,EDT_HORISCROLL,EDT_VERTSCROLL,EDT_NONE
}EMYLSTDOTPOSTYPE;

class CDotPosInfo
{
public:
	// 函数 CDotPosInfo
	// 作用：执行CDotPosInfo。
	// 参数：无。
	// 返回：没有返回值。
	CDotPosInfo(void);
	// 函数 ~CDotPosInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CDotPosInfo(void);

	// 函数 CDotPosInfo
	// 作用：执行CDotPosInfo。
	// 参数：dotPosInfo。
	// 返回：没有返回值。
	CDotPosInfo(const CDotPosInfo& dotPosInfo);
	void operator=(const CDotPosInfo& dotPosInfo);
	BOOL operator==(const CDotPosInfo& dotPosInfo);

	// 函数 BeSameRowCol
	// 作用：判断BeSameRowCol是否成立。
	// 参数：dotPosInfo。
	// 返回：返回是或否。
	BOOL BeSameRowCol(CDotPosInfo& dotPosInfo);
	// 函数 BeSameRow
	// 作用：判断BeSameRow是否成立。
	// 参数：dotPosInfo。
	// 返回：返回是或否。
	BOOL BeSameRow(CDotPosInfo& dotPosInfo);
	// 函数 BeSameCol
	// 作用：判断BeSameCol是否成立。
	// 参数：dotPosInfo。
	// 返回：返回是或否。
	BOOL BeSameCol(CDotPosInfo& dotPosInfo);

	// 函数 BeValidCellPos
	// 作用：判断BeValidCellPos是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL BeValidCellPos();	//标识是否在EDT_BODY已经存在的单元格中

public:
	EMYLSTDOTPOSTYPE m_eDotPosType;
	int m_rowId;
	int m_colId;
	CPoint m_pt;
};

