// 【交接】 GeneralPcr\ItemForSelInfo.h
// 作用：ItemForSelInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CItemForSelInfo、GetBeDisabled、GetBeSelected、SetSelectState、GetSelectState、MouseOut、MouseIn。
#pragma once

typedef enum SelectState{
	ESS_NORMAL,ESS_HOVER,ESS_SELECTED,ESS_DISABLE
}ESELECTSTATE;

class CItemForSelInfo
{
public:
	// 函数 CItemForSelInfo
	// 作用：执行CItemForSelInfo。
	// 参数：无。
	// 返回：没有返回值。
	CItemForSelInfo(void);
	// 函数 ~CItemForSelInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CItemForSelInfo(void);

	// 函数 CItemForSelInfo
	// 作用：执行CItemForSelInfo。
	// 参数：info。
	// 返回：没有返回值。
	CItemForSelInfo(const CItemForSelInfo& info);
	void operator=(const CItemForSelInfo& info);

	// 函数 GetBeDisabled
	// 作用：读取GetBeDisabled。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeDisabled();
	// 函数 GetBeSelected
	// 作用：读取GetBeSelected。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeSelected();

	// 函数 SetSelectState
	// 作用：设置SetSelectState。
	// 参数：eSelState。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int SetSelectState(ESELECTSTATE eSelState);
	// 函数 GetSelectState
	// 作用：读取GetSelectState。
	// 参数：无。
	// 返回：返回 ESELECTSTATE。
	ESELECTSTATE GetSelectState();

	// 函数 MouseOut
	// 作用：执行MouseOut。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int MouseOut();
	// 函数 MouseIn
	// 作用：执行MouseIn。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int MouseIn();

public:
	CString m_strText;
	
	COLORREF m_clrNormal;
	COLORREF m_clrHover;
	COLORREF m_clrSelected;
	COLORREF m_clrDisabled;

	int m_iItemH;

	ESELECTSTATE m_eSelState;
};

