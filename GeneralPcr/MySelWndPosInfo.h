// 【交接】 GeneralPcr\MySelWndPosInfo.h
// 作用：MySelWndPosInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMySelWndDotPosInfo、BeSameRow、Clear。
#pragma once

typedef enum MySelWndDotPosType{
	EMSWDPT_FRAME,EMSWDPT_BODY,EMSWDPT_VERTSCROLL,EMSWDPT_NONE
}EMYSELWNDDOTPOSTYPE;

class CMySelWndDotPosInfo
{
public:
	// 函数 CMySelWndDotPosInfo
	// 作用：执行CMySelWndDotPosInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMySelWndDotPosInfo(void);
	// 函数 ~CMySelWndDotPosInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMySelWndDotPosInfo(void);

	// 函数 CMySelWndDotPosInfo
	// 作用：执行CMySelWndDotPosInfo。
	// 参数：dotPosInfo。
	// 返回：没有返回值。
	CMySelWndDotPosInfo(const CMySelWndDotPosInfo& dotPosInfo);
	void operator=(const CMySelWndDotPosInfo& dotPosInfo);
	BOOL operator==(const CMySelWndDotPosInfo& dotPosInfo);

	// 函数 BeSameRow
	// 作用：判断BeSameRow是否成立。
	// 参数：dotPosInfo。
	// 返回：返回是或否。
	BOOL BeSameRow(CMySelWndDotPosInfo& dotPosInfo);
	
	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();

public:
	EMYSELWNDDOTPOSTYPE m_eDotPosType;
	int m_rowId;
	CPoint m_pt;
};

