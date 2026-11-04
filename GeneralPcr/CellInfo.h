// 【交接】 GeneralPcr\CellInfo.h
// 作用：CellInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCellInfo、SetItemText、GetItemText、SetItemHeight、GetItemHeight、SetItemCheckState、GetItemCheckState、SetItemColorParam。
#pragma once

#include "MaxMinInfo.h"
#include "LinkList.h"
#include "ArrowInfo.h"

typedef enum CellDataType{
		ECDT_INT,ECDT_DOUBLE,ECDT_BYTE,ECDT_CHAR,ECDT_PCHAR,ECDT_WCHAR,ECDT_PWCHAR,
	}ECELLDATATYPE;

class CCellInfo
{
public:
	// 函数 CCellInfo
	// 作用：执行CCellInfo。
	// 参数：无。
	// 返回：没有返回值。
	CCellInfo(void);
	// 函数 ~CCellInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CCellInfo(void);

	// 函数 CCellInfo
	// 作用：执行CCellInfo。
	// 参数：info。
	// 返回：没有返回值。
	CCellInfo(const CCellInfo& info);
	void operator=(const CCellInfo& info);

	// 函数 SetItemText
	// 作用：设置SetItemText。
	// 参数：strText：字符串。
	// 返回：没有返回值。
	void SetItemText(CString strText);
	// 函数 GetItemText
	// 作用：读取GetItemText。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetItemText();

	// 函数 SetItemHeight
	// 作用：设置SetItemHeight。
	// 参数：itemH。
	// 返回：没有返回值。
	void SetItemHeight(int itemH);
	// 函数 GetItemHeight
	// 作用：读取GetItemHeight。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetItemHeight();

	// 函数 SetItemCheckState
	// 作用：设置SetItemCheckState。
	// 参数：bChecked：是或否。
	// 返回：没有返回值。
	void SetItemCheckState(BOOL bChecked);
	// 函数 GetItemCheckState
	// 作用：读取GetItemCheckState。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetItemCheckState();

	// 函数 SetItemColorParam
	// 作用：设置SetItemColorParam。
	// 参数：clr：颜色；clrW：颜色；clrH：颜色；iRoundAngle：整数。
	// 返回：没有返回值。
	void SetItemColorParam(COLORREF clr,int clrW,int clrH,int iRoundAngle);	//颜色块参数编辑
	// 函数 GetItemColorParam
	// 作用：读取GetItemColorParam。
	// 参数：clr：颜色；clrW：颜色；clrH：颜色；iRoundAngle：整数。
	// 返回：没有返回值。
	void GetItemColorParam(COLORREF& clr,int& clrW,int& clrH,int& iRoundAngle);

	// 函数 SetItemColor
	// 作用：设置SetItemColor。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	void SetItemColor(COLORREF clr);	//颜色块颜色编辑
	// 函数 GetItemColor
	// 作用：读取GetItemColor。
	// 参数：无。
	// 返回：返回 COLORREF。
	COLORREF GetItemColor();

	// 函数 SetColorDisabled
	// 作用：设置SetColorDisabled。
	// 参数：clr：颜色。
	// 返回：没有返回值。
	void SetColorDisabled(COLORREF clr);
	// 函数 GetColorDisabled
	// 作用：读取GetColorDisabled。
	// 参数：无。
	// 返回：返回 COLORREF。
	COLORREF GetColorDisabled();

	// 函数 DeleteData
	// 作用：更新或清除DeleteData。
	// 参数：无。
	// 返回：没有返回值。
	void DeleteData();

	// 函数 GetStringFormatData
	// 作用：读取GetStringFormatData。
	// 参数：无。
	// 返回：返回一段文字。
	CString GetStringFormatData();
	// 函数 SetStringFormatData
	// 作用：设置SetStringFormatData。
	// 参数：strFormatData：字符串。
	// 返回：没有返回值。
	void SetStringFormatData(CString strFormatData);

	// 函数 SetCheckable
	// 作用：设置SetCheckable。
	// 参数：bCheckable：是或否。
	// 返回：没有返回值。
	void SetCheckable(BOOL bCheckable);
	// 函数 GetCheckable
	// 作用：读取GetCheckable。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetCheckable();

public:
	int m_rowId;
	int m_colId;
	DWORD m_dwTextAlign;	//文本对齐方式

	BOOL m_bEditable;	//标识单元格是否可使用编辑框编辑
	BOOL m_bRowColEqualUneditable;	//单元格行列相等时是否可编辑
	BOOL m_bCbAble;	//标识单元格是否可使用下拉框编辑
	BOOL m_bCbEditable;	//标识下拉框是否可手动输入
	BOOL m_bCbDeleteRow; // 标识下拉框是否可行删除

	CMaxMinInfo m_maxMinInfo;	//记录单元格的最大最小值信息

	BOOL m_bDisabled;	//标识单元格是否处于禁用状态

	CRect m_rcInCDc;	//单元格在内存CDC中的位置（此内存CDC宽度>=rcbody宽度）,已去除行列分割线的像素

	CArrowInfo m_arrowInfo;	//记录下拉框箭头参数信息
	CLinkList<CString> m_lnkCbStr;	//记录下拉框包含的所有选择项

	BOOL m_bUseCellLnkCbStr;	//标识“是否使用单元格自身的下拉选项信息”
	BOOL m_bEditableCb;	//标识“下拉框是否可输入信息”

	int m_iTxLeftIndent;	//显示文本时，左侧缩进
	int m_iTxRightIndent;	//显示文本时，右侧缩进

	CRect m_rcClrBlock;	//记录颜色块的位置

private:
	CString m_strText;
	int m_rowH;	//行高
	BOOL m_bChecked;	//是否是选中状态

	COLORREF m_clr;	//显示颜色块
	COLORREF m_clrDisabled;	//单元格禁用状态颜色
	int m_clrW;	//颜色块高度
	int m_clrH;	//颜色块高度
	int m_iClrBlockRoundAngle;	//颜色块圆角大小

	BOOL m_bCheckable;	//标识单元格是否是可选中状态
};

