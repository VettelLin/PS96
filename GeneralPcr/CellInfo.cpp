// 【交接】 GeneralPcr\CellInfo.cpp
// 作用：CellInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CCellInfo、_T、RGB、SetItemText、GetItemText、SetItemHeight、GetItemHeight、SetItemCheckState。
#include "StdAfx.h"
#include "CellInfo.h"


// 函数 CCellInfo::CCellInfo
// 作用：执行CCellInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T、RGB。
CCellInfo::CCellInfo(void)
{
	m_strText = _T("");
	m_rowId = -1;
	m_colId = -1;
	m_rowH = 30;
	m_dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
	m_bChecked = FALSE;
	m_clr = RGB(0,0,0);
	m_clrW = 20;
	m_clrH = 20;
	m_iClrBlockRoundAngle = 4;

	m_bEditable = FALSE;
	m_bRowColEqualUneditable = FALSE;
	m_bCbAble = FALSE;
	m_bCbEditable = FALSE;
	m_bDisabled = FALSE;
	m_bCbDeleteRow = FALSE;

	m_clrDisabled = RGB(0XF7,0XF7,0XF7);
	m_bUseCellLnkCbStr = FALSE;
	m_bEditableCb = FALSE;
	m_iTxLeftIndent = 0;
	m_iTxRightIndent = 0;
	m_bCheckable = FALSE;
}

// 函数 CCellInfo::~CCellInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCellInfo::~CCellInfo(void)
{

}

// 函数 CCellInfo::CCellInfo
// 作用：执行CCellInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CCellInfo::CCellInfo(const CCellInfo& info)
{
	m_rowId = info.m_rowId;
	m_colId = info.m_colId;
	m_strText = info.m_strText;
	m_rowH = info.m_rowH;
	m_dwTextAlign = info.m_dwTextAlign;
	m_bChecked = info.m_bChecked;
	m_clr = info.m_clr;
	m_clrW = info.m_clrW;
	m_clrH = info.m_clrH;

	m_bEditable = info.m_bEditable;
	m_bRowColEqualUneditable = info.m_bRowColEqualUneditable;
	m_bCbAble = info.m_bCbAble;
	m_bCbEditable = info.m_bCbEditable;
	m_bDisabled = info.m_bDisabled;
	m_clrDisabled = info.m_clrDisabled;
	m_arrowInfo = info.m_arrowInfo;
	m_lnkCbStr = info.m_lnkCbStr;
	m_bUseCellLnkCbStr = info.m_bUseCellLnkCbStr;
	m_bEditableCb = info.m_bEditableCb;
	m_iTxLeftIndent = info.m_iTxLeftIndent;
	m_iTxRightIndent = info.m_iTxRightIndent;
	m_bCheckable = info.m_bCheckable;
	m_rcClrBlock = info.m_rcClrBlock;
}

void CCellInfo::operator=(const CCellInfo& info)
{
	m_rowId = info.m_rowId;
	m_colId = info.m_colId;
	m_strText = info.m_strText;
	m_rowH = info.m_rowH;
	m_dwTextAlign = info.m_dwTextAlign;
	m_bChecked = info.m_bChecked;
	m_clr = info.m_clr;
	m_clrW = info.m_clrW;
	m_clrH = info.m_clrH;
	m_bEditable = info.m_bEditable;
	m_bRowColEqualUneditable = info.m_bRowColEqualUneditable;
	m_bCbAble = info.m_bCbAble;
	m_bCbEditable = info.m_bCbEditable;
	m_bDisabled = info.m_bDisabled;
	m_clrDisabled = info.m_clrDisabled;
	m_arrowInfo = info.m_arrowInfo;
	m_lnkCbStr = info.m_lnkCbStr;
	m_bUseCellLnkCbStr = info.m_bUseCellLnkCbStr;
	m_bEditableCb = info.m_bEditableCb;
	m_iTxLeftIndent = info.m_iTxLeftIndent;
	m_iTxRightIndent = info.m_iTxRightIndent;
	m_bCheckable = info.m_bCheckable;
	m_rcClrBlock = info.m_rcClrBlock;
}

// 函数 CCellInfo::SetItemText
// 作用：设置SetItemText。
// 参数：strText：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetItemText(CString strText)
{
	m_strText = strText;
}

// 函数 CCellInfo::GetItemText
// 作用：读取GetItemText。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CCellInfo::GetItemText()
{
	return m_strText;
}

// 函数 CCellInfo::SetItemHeight
// 作用：设置SetItemHeight。
// 参数：itemH。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetItemHeight(int itemH)
{
	m_rowH = itemH;
	return;
}

// 函数 CCellInfo::GetItemHeight
// 作用：读取GetItemHeight。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CCellInfo::GetItemHeight()
{
	return m_rowH;
}

// 函数 CCellInfo::SetItemCheckState
// 作用：设置SetItemCheckState。
// 参数：bChecked：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetItemCheckState(BOOL bChecked)
{
	m_bChecked = bChecked;
	return;
}

// 函数 CCellInfo::GetItemCheckState
// 作用：读取GetItemCheckState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CCellInfo::GetItemCheckState()
{
	return m_bChecked;
}

// 函数 CCellInfo::SetItemColorParam
// 作用：设置SetItemColorParam。
// 参数：clr：颜色；clrW：颜色；clrH：颜色；iRoundAngle：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetItemColorParam(COLORREF clr,int clrW,int clrH,int iRoundAngle)
{
	m_clr = clr;
	m_clrW = clrW;
	m_clrH = clrH;
	m_iClrBlockRoundAngle = iRoundAngle;
	return;
}

// 函数 CCellInfo::GetItemColorParam
// 作用：读取GetItemColorParam。
// 参数：clr：颜色；clrW：颜色；clrH：颜色；iRoundAngle：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::GetItemColorParam(COLORREF& clr,int& clrW,int& clrH,int& iRoundAngle)
{
	clr = m_clr;
	clrW = m_clrW;
	clrH = m_clrH;
	iRoundAngle = m_iClrBlockRoundAngle;
	return;
}

// 函数 CCellInfo::SetItemColor
// 作用：设置SetItemColor。
// 参数：clr：颜色。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetItemColor(COLORREF clr)
{
	m_clr = clr;
	return;
}

// 函数 CCellInfo::GetItemColor
// 作用：读取GetItemColor。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CCellInfo::GetItemColor()
{
	return m_clr;
}

// 函数 CCellInfo::SetColorDisabled
// 作用：设置SetColorDisabled。
// 参数：clr：颜色。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetColorDisabled(COLORREF clr)
{
	m_clrDisabled = clr;
	return;
}

// 函数 CCellInfo::GetColorDisabled
// 作用：读取GetColorDisabled。
// 参数：无。
// 返回：返回 COLORREF。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
COLORREF CCellInfo::GetColorDisabled()
{
	return m_clrDisabled;
}

// 函数 CCellInfo::DeleteData
// 作用：更新或清除DeleteData。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T、RGB、ClearMaxMinLimit、Clear。
void CCellInfo::DeleteData()
{
	m_strText = _T("");
	m_bChecked = FALSE;
	m_clr = RGB(0,0,0);
	m_clrW = 12;
	m_clrH = 12;

	m_bEditable = FALSE;
	m_bRowColEqualUneditable = FALSE;
	m_bCbAble = FALSE;
	
	m_bDisabled = FALSE;
	m_clrDisabled = RGB(241,243,245);

	m_maxMinInfo.ClearMaxMinLimit();

	m_lnkCbStr.Clear();
	m_bUseCellLnkCbStr = FALSE;
	m_bEditableCb = FALSE;
	m_bCheckable = FALSE;

	return;
}

// 函数 CCellInfo::GetStringFormatData
// 作用：读取GetStringFormatData。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CCellInfo::GetStringFormatData()
{
	return m_strText;
}

// 函数 CCellInfo::SetStringFormatData
// 作用：设置SetStringFormatData。
// 参数：strFormatData：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetStringFormatData(CString strFormatData)
{
	m_strText = strFormatData;
}

// 函数 CCellInfo::SetCheckable
// 作用：设置SetCheckable。
// 参数：bCheckable：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CCellInfo::SetCheckable(BOOL bCheckable)
{
	m_bCheckable = bCheckable;
}

// 函数 CCellInfo::GetCheckable
// 作用：读取GetCheckable。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CCellInfo::GetCheckable()
{
	return m_bCheckable;
}

