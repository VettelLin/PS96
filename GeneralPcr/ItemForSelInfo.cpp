// 【交接】 GeneralPcr\ItemForSelInfo.cpp
// 作用：ItemForSelInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CItemForSelInfo、_T、RGB、GetBeDisabled、GetBeSelected、SetSelectState、GetSelectState、MouseOut。
#include "StdAfx.h"
#include "ItemForSelInfo.h"


// 函数 CItemForSelInfo::CItemForSelInfo
// 作用：执行CItemForSelInfo。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T、RGB。
CItemForSelInfo::CItemForSelInfo(void)
{
	m_strText = _T("");

	m_clrNormal = RGB(255,255,255);
	m_clrHover = RGB(255,255,255);
	m_clrSelected = RGB(229,242,255);
	m_clrDisabled = RGB(246,246,246);

	m_iItemH = 28;
	m_eSelState = ESS_NORMAL;
}

// 函数 CItemForSelInfo::~CItemForSelInfo
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CItemForSelInfo::~CItemForSelInfo(void)
{

}

// 函数 CItemForSelInfo::CItemForSelInfo
// 作用：执行CItemForSelInfo。
// 参数：info。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CItemForSelInfo::CItemForSelInfo(const CItemForSelInfo& info)
{
	m_strText = info.m_strText;
	m_clrNormal = info.m_clrNormal;
	m_clrHover = info.m_clrHover;
	m_clrSelected = info.m_clrSelected;
	m_clrDisabled = info.m_clrDisabled;
	m_iItemH = info.m_iItemH;
	m_eSelState = info.m_eSelState;
}

void CItemForSelInfo::operator=(const CItemForSelInfo& info)
{
	m_strText = info.m_strText;
	m_clrNormal = info.m_clrNormal;
	m_clrHover = info.m_clrHover;
	m_clrSelected = info.m_clrSelected;
	m_clrDisabled = info.m_clrDisabled;
	m_iItemH = info.m_iItemH;
	m_eSelState = info.m_eSelState;
}

// 函数 CItemForSelInfo::GetBeDisabled
// 作用：读取GetBeDisabled。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CItemForSelInfo::GetBeDisabled()
{
	return ESS_DISABLE == m_eSelState;
}

// 函数 CItemForSelInfo::GetBeSelected
// 作用：读取GetBeSelected。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CItemForSelInfo::GetBeSelected()
{
	return ESS_SELECTED == m_eSelState;
}

// 函数 CItemForSelInfo::SetSelectState
// 作用：设置SetSelectState。
// 参数：eSelState。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CItemForSelInfo::SetSelectState(ESELECTSTATE eSelState)
{
	m_eSelState = eSelState;
	return 0;
}

// 函数 CItemForSelInfo::GetSelectState
// 作用：读取GetSelectState。
// 参数：无。
// 返回：返回 ESELECTSTATE。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
ESELECTSTATE CItemForSelInfo::GetSelectState()
{
	return m_eSelState;
}

// 函数 CItemForSelInfo::MouseOut
// 作用：执行MouseOut。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CItemForSelInfo::MouseOut()
{
	if(ESS_DISABLE == m_eSelState)
	{
		return 1;
	}

	if(ESS_SELECTED == m_eSelState)
	{
		return 2 ;
	}

	if(ESS_HOVER == m_eSelState)
	{
		m_eSelState = ESS_NORMAL;
		return 3;
	}
	
	if(ESS_NORMAL == m_eSelState)
	{
		return 4;
	}

	return 0;
}

// 函数 CItemForSelInfo::MouseIn
// 作用：执行MouseIn。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CItemForSelInfo::MouseIn()
{
	if(ESS_DISABLE == m_eSelState)
	{
		return 1;
	}

	if(ESS_SELECTED == m_eSelState)
	{
		return 2 ;
	}

	if(ESS_HOVER == m_eSelState)
	{
		return 3;
	}

	if(ESS_NORMAL == m_eSelState)
	{
		m_eSelState = ESS_HOVER;
		return 4;
	}

	return 0;
}
