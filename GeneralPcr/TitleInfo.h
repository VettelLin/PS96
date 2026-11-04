// 【交接】 GeneralPcr\TitleInfo.h
// 作用：TitleInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTitleInfo、SetBeEditable、GetBeEditable、SetBeDisabled、GetBeDisabled、SetDataParam、GetDataParam、DataFilter。
#pragma once

#include "MaxMinInfo.h"
#include "LinkList.h"
#include "ArrowInfo.h"
#include "DataParam.h"

class CTitleInfo
{
public:
	// 函数 CTitleInfo
	// 作用：执行CTitleInfo。
	// 参数：无。
	// 返回：没有返回值。
	CTitleInfo(void);
	// 函数 ~CTitleInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CTitleInfo(void);

	// 函数 CTitleInfo
	// 作用：执行CTitleInfo。
	// 参数：info。
	// 返回：没有返回值。
	CTitleInfo(const CTitleInfo& info);
	void operator=(const CTitleInfo& info);

	// 函数 SetBeEditable
	// 作用：设置SetBeEditable。
	// 参数：bEditable：是或否。
	// 返回：没有返回值。
	void SetBeEditable(BOOL bEditable);
	// 函数 GetBeEditable
	// 作用：读取GetBeEditable。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeEditable();

	// 函数 SetBeDisabled
	// 作用：设置SetBeDisabled。
	// 参数：bDisabled：是或否。
	// 返回：没有返回值。
	void SetBeDisabled(BOOL bDisabled);
	// 函数 GetBeDisabled
	// 作用：读取GetBeDisabled。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeDisabled();

	// 函数 SetDataParam
	// 作用：设置SetDataParam。
	// 参数：dtParam。
	// 返回：没有返回值。
	void SetDataParam(CDataParam dtParam);
	// 函数 GetDataParam
	// 作用：读取GetDataParam。
	// 参数：无。
	// 返回：返回 CDataParam。
	CDataParam GetDataParam();	
	// 函数 DataFilter
	// 作用：执行DataFilter。
	// 参数：strData：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DataFilter(CString& strData);

	// 函数 SetMultiDensityState
	// 作用：设置SetMultiDensityState。
	// 参数：bData：是或否。
	// 返回：没有返回值。
	void SetMultiDensityState(BOOL bData);
	// 函数 GetMultiDensityState
	// 作用：读取GetMultiDensityState。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetMultiDensityState();

	// 函数 SetTextAlignFormat2
	// 作用：设置SetTextAlignFormat2。
	// 参数：dwData。
	// 返回：没有返回值。
	void SetTextAlignFormat2(DWORD dwData);
	// 函数 GetTextAlignFormat2
	// 作用：读取GetTextAlignFormat2。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	DWORD GetTextAlignFormat2();

public:
	CString m_strTitle;	//列标题
	BOOL m_bSelected;	//标识是否被选中
	COLORREF m_clrBkSlected;	//选中效果背景色
	COLORREF m_clrBkUnselected;	//未选中效果背景色
	int m_colWidth;	//列宽
	DWORD m_dwTextAlign;	//文本对齐方式
	DWORD m_dwTxAlign2;	//文本对齐方式2

	BOOL m_bCheckFunc;	//标识是否是可勾选列

	BOOL m_bColorFunc;	//标识是否是显示颜色块
	BOOL m_bClrEditale;	//标识颜色块的颜色是否可修改

	BOOL m_bCbtable;	//标识列是否可使用下拉框编辑
	BOOL m_bCbEditable;	//标识下拉框是否可手动输入
	BOOL m_bTellParentCellChanged;	//是否通知父窗口单元格信息改变，CcellInfo暂不保存该信息,20220302

	CMaxMinInfo m_maxMinInfo;	//记录列共有的最大最小值信息

	CArrowInfo m_arrowInfo;	//记录下拉框箭头参数信息
	CLinkList<CString> m_lnkCbStr;	//记录下拉框包含的所有选择项
	int m_iCbTxLeftIndent;	//下拉框文本输出左侧缩进
	int m_iCbTxRightIndent;	//下拉框文本输出右侧缩进

protected:
	BOOL m_bEditable;	//标识列是否可使用编辑框编辑
	BOOL m_bDisabled;	//标识列是否是禁用状态

	CDataParam m_dtParam; 

	BOOL m_bMultiDensity;	//标识“是否在同一列显示多个浓度”
};

