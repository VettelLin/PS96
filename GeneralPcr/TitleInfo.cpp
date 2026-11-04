// 【交接】 GeneralPcr\TitleInfo.cpp
// 作用：TitleInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTitleInfo、_T、RGB、SetBeEditable、GetBeEditable、SetBeDisabled、GetBeDisabled、SetDataParam。
#include "StdAfx.h"
#include "TitleInfo.h"


// 函数 CTitleInfo::CTitleInfo
// 作用：执行CTitleInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T、RGB。
CTitleInfo::CTitleInfo(void)
{
	m_strTitle = _T("");
	m_bSelected = FALSE;
	m_clrBkSlected = RGB(0XF1,0XF4,0XF9);
	m_clrBkUnselected = RGB(0XF1,0XF4,0XF9);
	m_colWidth = 60;
	m_dwTextAlign = DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
	m_dwTxAlign2 = DT_LEFT | DT_VCENTER | DT_END_ELLIPSIS;
	m_bCheckFunc = FALSE;
	m_bColorFunc = FALSE;
	m_bClrEditale = FALSE;
	m_bEditable = FALSE;
	m_bDisabled = FALSE;
	m_bCbtable = FALSE;
	m_bCbEditable = FALSE;
	m_iCbTxLeftIndent = 6; 
	m_iCbTxRightIndent = 28;
	m_bTellParentCellChanged = FALSE;
	m_bMultiDensity = FALSE;
}

// 函数 CTitleInfo::~CTitleInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTitleInfo::~CTitleInfo(void)
{

}

// 函数 CTitleInfo::CTitleInfo
// 作用：执行CTitleInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CTitleInfo::CTitleInfo(const CTitleInfo& info)
{
	m_strTitle = info.m_strTitle;
	m_bSelected = info.m_bSelected;
	m_colWidth = info.m_colWidth;
	m_dwTextAlign = info.m_dwTextAlign;
	m_clrBkSlected = info.m_clrBkSlected;
	m_clrBkUnselected = info.m_clrBkUnselected;
	m_bCheckFunc = info.m_bCheckFunc;
	m_bColorFunc = info.m_bColorFunc;
	m_bClrEditale = info.m_bClrEditale;
	m_bEditable = info.m_bEditable;
	m_bDisabled = info.m_bDisabled;
	m_bCbtable = info.m_bCbtable;
	m_bCbEditable = info.m_bCbEditable;
	m_maxMinInfo = info.m_maxMinInfo;
	m_lnkCbStr = info.m_lnkCbStr;
	m_arrowInfo = info.m_arrowInfo;
	m_iCbTxLeftIndent = info.m_iCbTxLeftIndent;
	m_iCbTxRightIndent = info.m_iCbTxRightIndent;
	m_bTellParentCellChanged = info.m_bTellParentCellChanged;
	return;
}

void CTitleInfo::operator=(const CTitleInfo& info)
{
	m_strTitle = info.m_strTitle;
	m_bSelected = info.m_bSelected;
	m_colWidth = info.m_colWidth;
	m_dwTextAlign = info.m_dwTextAlign;
	m_clrBkSlected = info.m_clrBkSlected;
	m_clrBkUnselected = info.m_clrBkUnselected;
	m_bCheckFunc = info.m_bCheckFunc;
	m_bColorFunc = info.m_bColorFunc;
	m_bClrEditale = info.m_bClrEditale;
	m_bEditable = info.m_bEditable;
	m_bDisabled = info.m_bDisabled;
	m_bCbtable = info.m_bCbtable;
	m_bCbEditable = info.m_bCbEditable;
	m_maxMinInfo = info.m_maxMinInfo;
	m_lnkCbStr = info.m_lnkCbStr;
	m_arrowInfo = info.m_arrowInfo;
	m_iCbTxLeftIndent = info.m_iCbTxLeftIndent;
	m_iCbTxRightIndent = info.m_iCbTxRightIndent;
	m_bTellParentCellChanged = info.m_bTellParentCellChanged;
	return;
}

// 函数 CTitleInfo::SetBeEditable
// 作用：设置SetBeEditable。
// 参数：bEditable：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTitleInfo::SetBeEditable(BOOL bEditable)
{
	m_bEditable = bEditable;
}

// 函数 CTitleInfo::GetBeEditable
// 作用：读取GetBeEditable。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTitleInfo::GetBeEditable()
{
	return m_bEditable;
}

// 函数 CTitleInfo::SetBeDisabled
// 作用：设置SetBeDisabled。
// 参数：bDisabled：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTitleInfo::SetBeDisabled(BOOL bDisabled)
{
	m_bDisabled = bDisabled;
}

// 函数 CTitleInfo::GetBeDisabled
// 作用：读取GetBeDisabled。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTitleInfo::GetBeDisabled()
{
	return m_bDisabled;
}

// 函数 CTitleInfo::SetDataParam
// 作用：设置SetDataParam。
// 参数：dtParam。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTitleInfo::SetDataParam(CDataParam dtParam)
{
	m_dtParam = dtParam;
}

// 函数 CTitleInfo::GetDataParam
// 作用：读取GetDataParam。
// 参数：无。
// 返回：返回 CDataParam。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CDataParam CTitleInfo::GetDataParam()
{
	return m_dtParam;
}

// 函数 CTitleInfo::DataFilter
// 作用：执行DataFilter。
// 参数：strData：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CTitleInfo::DataFilter(CString& strData)
{
	return m_dtParam.DataFilter(strData);
}

// 函数 CTitleInfo::SetMultiDensityState
// 作用：设置SetMultiDensityState。
// 参数：bData：是或否。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTitleInfo::SetMultiDensityState(BOOL bData)
{
	m_bMultiDensity = bData;
	return;
}

// 函数 CTitleInfo::GetMultiDensityState
// 作用：读取GetMultiDensityState。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CTitleInfo::GetMultiDensityState()
{
	return m_bMultiDensity;
}

// 函数 CTitleInfo::SetTextAlignFormat2
// 作用：设置SetTextAlignFormat2。
// 参数：dwData。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CTitleInfo::SetTextAlignFormat2(DWORD dwData)
{
	m_dwTxAlign2 = dwData;
	return;
}

// 函数 CTitleInfo::GetTextAlignFormat2
// 作用：读取GetTextAlignFormat2。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
DWORD CTitleInfo::GetTextAlignFormat2()
{
	return m_dwTxAlign2;
}
