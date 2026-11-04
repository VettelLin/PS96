// 【交接】 GeneralPcr\CaretInfo.h
// 作用：CaretInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCaretInfo。
#pragma once
class CCaretInfo
{
public:
	// 函数 CCaretInfo
	// 作用：执行CCaretInfo。
	// 参数：无。
	// 返回：没有返回值。
	CCaretInfo(void);
	// 函数 ~CCaretInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CCaretInfo(void);

	// 函数 CCaretInfo
	// 作用：执行CCaretInfo。
	// 参数：caretInfo。
	// 返回：没有返回值。
	CCaretInfo(const CCaretInfo& caretInfo);
	void operator=(const CCaretInfo& caretInfo);

public:
	int m_pxXStart;	//插入符水平方向起始位置
	int m_pxYStart;	//插入符垂直方向起始位置
	int m_pxWidth;	//插入符宽度
	int m_pxHeight;	//插入符高度

	int m_iCurCharIndex;	//记录插入符当前处于哪个字符的（紧邻）后面
};

