// 【交接】 BWGenUILib\ColorComboBox.cpp
// 作用：ColorComboBox。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：IMPLEMENT_DYNAMIC、CColorComboBox、RGB、CSize、BEGIN_MESSAGE_MAP、END_MESSAGE_MAP、DrawItem、FromHandle。
// ColorComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "ColorComboBox.h"


// CColorComboBox

IMPLEMENT_DYNAMIC(CColorComboBox, CComboBox)

// 函数 CColorComboBox::CColorComboBox
// 作用：执行CColorComboBox。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 RGB、CSize。
CColorComboBox::CColorComboBox()
{
	m_bShowText = FALSE;
	m_iMaxItem = 256;
	m_pItemColor = new COLORREF[m_iMaxItem];
	for (int i=0; i<m_iMaxItem; i++)
	{
		m_pItemColor[i] = RGB(255, 0, 0);
	}

	m_sizeColorArea = CSize(16, 16);
	m_iColorBorder = 2;
	m_bIsDropList = FALSE;
	m_iEditHeight = 0;
}

// 函数 CColorComboBox::~CColorComboBox
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CColorComboBox::~CColorComboBox()
{
	delete []m_pItemColor;
}


BEGIN_MESSAGE_MAP(CColorComboBox, CComboBox)
END_MESSAGE_MAP()



// CColorComboBox message handlers

// 函数 CColorComboBox::DrawItem
// 作用：绘制DrawItem。
// 参数：lpDrawItemStruct。
// 返回：没有返回值。
// 过程：函数里会调用 FromHandle、SetBkMode、GetLBText、rectItem、GetBkColor、FillSolidRect。
void CColorComboBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (lpDrawItemStruct->itemID == -1)
	{
		return;
	}

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	pDC->SetBkMode(TRANSPARENT);
	RECT& rcItem = lpDrawItemStruct->rcItem;

	CString strText;
	CComboBox::GetLBText(lpDrawItemStruct->itemID, strText);

	// 是否处于选中状态
	BOOL bIsSelected = (lpDrawItemStruct->itemAction | ODA_SELECT) && (lpDrawItemStruct->itemState & ODS_SELECTED);
	// 是否处于焦点状态
	BOOL bIsFocused = (lpDrawItemStruct->itemAction | ODA_FOCUS) && (lpDrawItemStruct->itemState & ODS_FOCUS);

	CRect rectItem(rcItem);
	// 绘制背景
	if (bIsSelected)
	{
		COLORREF oldColor = pDC->GetBkColor();
		pDC->FillSolidRect(rectItem, ::GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetBkColor(oldColor);
	}
	else
	{
		//pDC->FillSolidRect(rectItem, pDC->GetBkColor());
		pDC->FillSolidRect(rectItem, RGB(255, 255,255));
	}

	CRect rectColor = rectItem;
	rectColor.right = rectColor.left + rectItem.Height();

	rectColor.left = rectColor.left + (rectColor.Width() - m_sizeColorArea.cx) / 2;
	rectColor.right = rectColor.left + m_sizeColorArea.cx;
	rectColor.top = rectColor.top + (rectColor.Height() - m_sizeColorArea.cy) / 2;
	rectColor.bottom = rectColor.top + m_sizeColorArea.cy;
	pDC->FillSolidRect(rectColor, m_pItemColor[lpDrawItemStruct->itemID]);

	if (m_bShowText && !strText.IsEmpty())
	{
		if (bIsSelected)
		{
			pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		}
		else
		{
			pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
		}

		CRect rectText = rectItem;
		rectText.left = rectColor.right + 5;
		pDC->DrawText(strText, rectText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORDBREAK);
	}
}

// 函数 CColorComboBox::MeasureItem
// 作用：执行MeasureItem。
// 参数：lpMeasureItemStruct。
// 返回：没有返回值。
// 过程：函数里会调用 GetDC、GetTextExtent、ReleaseDC、GetStyle、DWORD、UINT。
void CColorComboBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC *pDC = GetDC();
	LPCTSTR lpszText = (LPCTSTR)lpMeasureItemStruct->itemData;
	CSize szText = pDC->GetTextExtent(lpszText);
	ReleaseDC(pDC);

	lpMeasureItemStruct->itemHeight = szText.cy > m_sizeColorArea.cy + 2 * m_iColorBorder ? szText.cy :  m_sizeColorArea.cy + 2 * m_iColorBorder;

	// 检测是否是DropList
	if (!m_bIsDropList)
	{
		DWORD dwStyle = GetStyle();
		if (DWORD(CBS_DROPDOWNLIST & dwStyle) == (DWORD)CBS_DROPDOWNLIST)
		{
			m_bIsDropList = TRUE;
		}
	}

	// 设置EditCtrl的高度
	if (m_bIsDropList && lpMeasureItemStruct->itemHeight > UINT(m_iEditHeight))
	{
		m_iEditHeight = lpMeasureItemStruct->itemHeight;
		SetItemHeight(-1, m_iEditHeight);
	}
}


// 函数 CColorComboBox::AddString
// 作用：创建或加入AddString。
// 参数：lpszString；clrItem：颜色。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 DeleteString、Format、_T。
int CColorComboBox::AddString(LPCTSTR lpszString, COLORREF clrItem)
{
	int iIndex = CComboBox::AddString(lpszString);
	if (iIndex >= m_iMaxItem)
	{
		DeleteString(iIndex);
		CString strTip;
		strTip.Format(_T("The max sum of strings is %d!"), m_iMaxItem);
		AfxMessageBox(strTip);
		return -1;
	}

	if (iIndex != CB_ERR && iIndex != CB_ERRSPACE)
	{
		m_pItemColor[iIndex] = clrItem;
	}

	return iIndex;

}

// 函数 CColorComboBox::GetColor
// 作用：读取GetColor。
// 参数：iIndex：整数。
// 返回：返回 COLORREF。
// 过程：函数里会调用 RGB。
COLORREF CColorComboBox::GetColor(int iIndex)
{
	if (iIndex >= 0 && iIndex < m_iMaxItem)
		return m_pItemColor[iIndex];
	else
		return RGB(255, 255, 255);
}
