// 【交接】 GeneralPcr\RowColEditInfo.h
// 作用：RowColEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CRowColEditInfo、BeValidRowCol、Clear。
#pragma once

//记录正在编辑的行列信息

class CRowColEditInfo
{
public:
	// 函数 CRowColEditInfo
	// 作用：执行CRowColEditInfo。
	// 参数：无。
	// 返回：没有返回值。
	CRowColEditInfo(void);
	// 函数 ~CRowColEditInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CRowColEditInfo(void);

	// 函数 CRowColEditInfo
	// 作用：执行CRowColEditInfo。
	// 参数：rowColEditInfo。
	// 返回：没有返回值。
	CRowColEditInfo(const CRowColEditInfo& rowColEditInfo);
	void operator=(const CRowColEditInfo& rowColEditInfo);
	BOOL operator==(const CRowColEditInfo& rowColEditInfo);

	// 函数 BeValidRowCol
	// 作用：判断BeValidRowCol是否成立。
	// 参数：无。
	// 返回：返回是或否。
	BOOL BeValidRowCol();
	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();

public:
	int m_rowId;
	int m_colId;

	CString m_strText;	//修改之前的文本
	CString m_strNewText;	//修改之后的文本
};

