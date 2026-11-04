// 【交接】 GeneralPcr\RowInfo.h
// 作用：RowInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CRowInfo。
#pragma once
class CRowInfo
{
public:
	// 函数 CRowInfo
	// 作用：执行CRowInfo。
	// 参数：无。
	// 返回：没有返回值。
	CRowInfo(void);
	// 函数 ~CRowInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CRowInfo(void);

	// 函数 CRowInfo
	// 作用：执行CRowInfo。
	// 参数：info。
	// 返回：没有返回值。
	CRowInfo(const CRowInfo& info);
	void operator=(const CRowInfo& info);

public:
	int m_rowH;	//行高，不同于CCellInfo中的单元格高度
	BOOL m_bSelected;	//行是否选中
	BOOL m_bDisabled;	//是否禁用整行
};

