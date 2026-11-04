// 【交接】 BWGenUILib\ResizeContainer.cpp
// 作用：ResizeContainer。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CResizeItem、SetRect、GetPosition、MoveWindow、FindAndSetShow、Invalidate、Width、Height。
// ResizeContainer.cpp : implementation file
//

#include "stdafx.h"
#include "ResizeContainer.h"

// CResizeItem

CResizeContainer::CResizeItem::CResizeItem(CWnd* pWnd, CRect rect, eResizeType nType, int iIndent)
{
	m_pResizeWnd = pWnd;
	m_rect = rect;
	m_nResizeType = nType;
	m_iIndent = iIndent;
	m_bNewRow = TRUE;
	m_bShow = TRUE;
}

CResizeContainer::CResizeItem::~CResizeItem()
{
}

/**
 * 设置窗口位置
 * \param &rect 去除窗口占用的剩余父类窗口位置
 */
void CResizeContainer::CResizeItem::SetRect(CRect rect)
{
	ASSERT(m_pResizeWnd != NULL);	
	CRect rectResize = GetPosition(rect);
	MoveWindow(m_pResizeWnd, rectResize);
	m_rect = rectResize;
}

BOOL CResizeContainer::CResizeItem::FindAndSetShow(CWnd* pInputWnd, BOOL bShow)
{
	ASSERT(m_pResizeWnd != NULL);
	if (m_pResizeWnd == pInputWnd)
	{
		m_bShow = bShow;
		return TRUE;
	}

	return FALSE;
}


// 移动窗口的位置和大小
void CResizeContainer::CResizeItem::MoveWindow(CWnd* pWnd, CRect rect)
{
	CRect rectResize = rect;
	if (pWnd->IsKindOf(RUNTIME_CLASS(CComboBox)))
	{
		rectResize.bottom += 150;
	}

	pWnd->MoveWindow(rectResize);
	pWnd->Invalidate();
}

// 得到当前窗口的位置矩形
CRect CResizeContainer::CResizeItem::GetPosition(CRect rect)
{
	CRect rectResize;

	switch (m_nResizeType)
	{
	case LEFT_SIZE_NO: // 靠左
		rectResize.left = rect.left + m_iIndent;
		rectResize.right = rectResize.left + m_rect.Width();
		rectResize.top = rect.top + (rect.Height() - m_rect.Height()) / 2;
		if (rectResize.top < rect.top)
			rectResize.top = rect.top;
		rectResize.bottom = rectResize.top + m_rect.Height();
		break;
	case LEFT_SIZE_H:
		rectResize.left = rect.left + m_iIndent;
		rectResize.right = rect.right;
		rectResize.top = rect.top + (rect.Height() - m_rect.Height()) / 2;
		if (rectResize.top < rect.top)
			rectResize.top = rect.top;
		rectResize.bottom = rectResize.top + m_rect.Height();
		break;
	case LEFT_SIZE_V:
		rectResize.left = rect.left + (rect.Width() - m_rect.Width()) / 2;
		rectResize.right = rectResize.left + m_rect.Width();
		rectResize.top = rect.top + m_iIndent;
		rectResize.bottom = rect.bottom;
		break;
	case LEFT_SIZE_HV:
		rectResize.left = rect.left + m_iIndent;
		rectResize.right = rect.right;
		rectResize.top = rect.top;
		rectResize.bottom = rect.bottom;
		break;
	case RIGHT_SIZE_NO:
		rectResize.right = rect.right - m_iIndent;
		rectResize.left = rectResize.right - m_rect.Width();
		rectResize.top = rect.top + (rect.Height() - m_rect.Height()) / 2;
		if (rectResize.top < rect.top)
			rectResize.top = rect.top;
		rectResize.bottom = rectResize.top + m_rect.Height();
		break;
	case RIGHT_SIZE_H:
		rectResize.right = rect.right - m_iIndent;
		rectResize.left = rect.left;
		rectResize.top = rect.top + (rect.Height() - m_rect.Height()) / 2;
		if (rectResize.top < rect.top)
			rectResize.top = rect.top;
		rectResize.bottom = rectResize.top + m_rect.Height();
		break;
	case RIGHT_SIZE_V:
		rectResize.left = rect.left + (rect.Width() - m_rect.Width()) / 2;
		rectResize.right = rectResize.left + m_rect.Width();
		rectResize.top = rect.top + m_iIndent;
		rectResize.bottom = rect.bottom;
		break;
	case RIGHT_SIZE_HV:
		rectResize.right = rect.right - m_iIndent;
		rectResize.left = rect.left;
		rectResize.top = rect.top;
		rectResize.bottom = rect.bottom;
		break;
	default:
		ASSERT(FALSE);
		break;
	}

	return rectResize;
}


// CResizeGroup

CResizeContainer::CResizeGroup::CResizeGroup(CRect rect, eResizeType nType, eResizeFillType nFillType, int iIndent)
	: CResizeItem(NULL, rect, nType, iIndent)
{
	m_nFillType = nFillType;
	m_nSeparator = 5;
}

CResizeContainer::CResizeGroup::~CResizeGroup()
{
}

void CResizeContainer::CResizeGroup::SetChildren(CPtrArray* pChildren)
{
	m_arrayChildren.Copy(*pChildren);

	CRect rectChild, rectGroup;
	rectGroup.SetRectEmpty();
	CWnd* pChild = NULL;
	for (int i=0; i<m_arrayChildren.GetSize(); i++)
	{
		pChild = (CWnd*)m_arrayChildren.GetAt(i);
		pChild->GetWindowRect(&rectChild);
		if (rectGroup.IsRectEmpty())
			rectGroup = rectChild;
		else
		{
			if (rectChild.Height() > rectGroup.Height())
				rectGroup.bottom = rectGroup.top + rectChild.Height();

			if (rectGroup.right < rectChild.right)
				rectGroup.right = rectChild.right;
			if (rectGroup.left > rectChild.left)
				rectGroup.left = rectChild.left;
		}
	}

	m_rect = rectGroup;
}

void CResizeContainer::CResizeGroup::SetRect(CRect rect)
{
	CRect rectResize = GetPosition(rect);
	int nChildCount = (int)m_arrayChildren.GetCount();
	CRect rectChild = rectResize;
	CWnd* pChildWnd = NULL;

	if (m_nFillType == FILL_RESIZE_H)
	{
		float fHorz = float(rectResize.Width() - (nChildCount-1)*m_nSeparator) / float(nChildCount);
		for (int i=0; i<nChildCount; i++)
		{
			rectChild.right = rectResize.left + long((i+1) * fHorz + 0.5) + i*m_nSeparator;
			pChildWnd = (CWnd*)m_arrayChildren.GetAt(i);
			MoveWindow(pChildWnd, rectChild );

			rectChild.left = rectChild.right + m_nSeparator;
		}
	}
	else if (m_nFillType == FILL_RESIZE_V)
	{
		float fVert = float(rectResize.Height() - (nChildCount-1)*m_nSeparator) / float(nChildCount);
		for (int i=0; i<nChildCount; i++)
		{
			rectChild.bottom = rectChild.top + long((i+1) * fVert + 0.5) + i*m_nSeparator;
			pChildWnd = (CWnd*)m_arrayChildren.GetAt(i);
			MoveWindow(pChildWnd, rectChild );

			rectChild.top = rectChild.bottom + m_nSeparator;
		}
	}
	else if (m_nFillType == FILL_RESIZE_LEFT)
	{
		int iHoriPos = rect.right;
		for (int i=nChildCount-1; i>0; i--)
		{
			pChildWnd = (CWnd*)m_arrayChildren.GetAt(i);
			CRect rectTemp;
			pChildWnd->GetWindowRect(&rectTemp);
			rectChild.right = iHoriPos;
			rectChild.left = rectChild.right - rectTemp.Width();
			MoveWindow(pChildWnd, rectChild );
			iHoriPos = rectChild.left - m_nSeparator;
		}

		pChildWnd = (CWnd*)m_arrayChildren.GetAt(0);
		rectChild.right = iHoriPos;
		rectChild.left = rect.left + m_iIndent;
		MoveWindow(pChildWnd, rectChild );

	}
}

BOOL CResizeContainer::CResizeGroup::FindAndSetShow(CWnd* pInputWnd, BOOL bShow)
{
	ASSERT(m_pResizeWnd == NULL);
	BOOL bFind = FALSE;
	for (int i=0; i<m_arrayChildren.GetCount(); i++)
	{
		CWnd* pChildWnd = (CWnd*)m_arrayChildren.GetAt(i);
		if (pChildWnd == pInputWnd)
		{
			bFind = TRUE;
			m_bShow = bShow;
			break;
		}
	}

	return bFind;
}

// CResizeContainer

// 函数 CResizeContainer::CResizeContainer
// 作用：执行CResizeContainer。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 RemoveAll、CSize。
CResizeContainer::CResizeContainer()
{
	m_pParentWnd = NULL;
	m_arrayChild.RemoveAll();

	m_nDockType = DOCK_TOP;
	m_sizeMarginLT = CSize(5, 10);
	m_sizeMarginRB = CSize(5, 5);
	m_iRowSpace = 30;
	m_sizeResizeMax = CSize(-1, -1);
}

// 函数 CResizeContainer::~CResizeContainer
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize、GetAt、RemoveAll。
CResizeContainer::~CResizeContainer()
{
	int nChildCount = (int)m_arrayChild.GetSize();
	CResizeItem* pItem = NULL;

	for (int i=0; i<nChildCount; i++)
	{
		pItem = (CResizeItem*)m_arrayChild.GetAt(i);
		if (pItem != NULL)
		{
			delete pItem;
			pItem = NULL;
		}
	}
	m_arrayChild.RemoveAll();
}


// CResizeContainer member functions

// 函数 CResizeContainer::AddChild
// 作用：创建或加入AddChild。
// 参数：pChild：指针，指向调用方传入的对象；nType：整数；iIndent：整数；bNewRow：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetWindowRect、CResizeItem、SetNewRow、Add。
int CResizeContainer::AddChild(CWnd* pChild, eResizeType nType, int iIndent, BOOL bNewRow)
{
	ASSERT(m_pParentWnd != NULL);
	ASSERT(pChild != NULL);

	CRect rect;
	pChild->GetWindowRect(&rect);	
	CResizeItem* pItem = new CResizeItem(pChild, rect, nType, iIndent);
	pItem->SetNewRow(bNewRow);
	int nIndex = (int)m_arrayChild.Add(pItem);
	return nIndex;
}

// 函数 CResizeContainer::AddGroupChild
// 作用：创建或加入AddGroupChild。
// 参数：pChildArray：指针，指向调用方传入的对象；nType：整数；nFillType：整数；iIndent：整数；bNewRow：是或否。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCount、CResizeGroup、CRect、SetNewRow、SetChildren、Add。
int CResizeContainer::AddGroupChild(CPtrArray* pChildArray, eResizeType nType, eResizeFillType nFillType, int iIndent, BOOL bNewRow)
{
	ASSERT(m_pParentWnd != NULL);
	ASSERT(pChildArray->GetCount() > 0);
	CResizeGroup* pItem = new CResizeGroup(CRect(0,0,0,0), nType, nFillType, iIndent);
	pItem->SetNewRow(bNewRow);
	pItem->SetChildren(pChildArray);
	int nIndex = (int)m_arrayChild.Add(pItem);
	return nIndex;
}

// 函数 CResizeContainer::SetRect
// 作用：设置SetRect。
// 参数：rect：矩形区域。
// 返回：没有返回值。
// 过程：函数里会调用 IsRectEmpty、CalculateRowSpace、GetCount、GetAt、GetShow、GetNewRow。
void CResizeContainer::SetRect(CRect rect)
{
	if (rect.IsRectEmpty())
		return;

	CRect rectClient = rect;
	rectClient.left += m_sizeMarginLT.cx;
	rectClient.top += m_sizeMarginLT.cy;
	rectClient.right -= m_sizeMarginRB.cx;
	rectClient.bottom -= m_sizeMarginRB.cy;

	CRect rectRow = rectClient;

	// 根据显示区域高度计算实际的行间距大小
	int iRowSpace = CalculateRowSpace(rectClient);

	int iStartPos = -1;
	for (int i=0; i<m_arrayChild.GetCount(); i++)
	{
		CResizeItem* pItem = (CResizeItem*)m_arrayChild.GetAt(i);
		if (!pItem->GetShow())
			continue;

		if (pItem->GetNewRow())
		{
			rectRow = rectClient;
			CRect rectItem = GetRowRect(i);

			eResizeType nResizeType = pItem->GetResizeType();

			if (m_nDockType == DOCK_TOP)
			{
				if (iStartPos == -1)
					iStartPos = rectClient.top;

				rectRow.top = iStartPos;

				switch(nResizeType)
				{
				case LEFT_SIZE_NO:
				case RIGHT_SIZE_NO:
					rectRow.bottom = rectRow.top + rectItem.Height();
					break;
				case LEFT_SIZE_H:
				case RIGHT_SIZE_H:
					rectRow.bottom = rectRow.top + rectItem.Height();
					if (m_sizeResizeMax.cx != -1)
					{
						rectRow.right = rectRow.left + m_sizeResizeMax.cx;
					}
					break;
				case LEFT_SIZE_V:
				case RIGHT_SIZE_V:
					if (m_sizeResizeMax.cy != -1)
					{
						rectRow.bottom = rectRow.top + m_sizeResizeMax.cy;
					}
					break;
				case LEFT_SIZE_HV:
				case RIGHT_SIZE_HV:
					if (m_sizeResizeMax.cx != -1)
					{
						rectRow.right = rectRow.left + m_sizeResizeMax.cx;
					}
					if (m_sizeResizeMax.cy != -1)
					{
						rectRow.bottom = rectRow.top + m_sizeResizeMax.cy;
					}
					break;
				default:
					ASSERT(FALSE);
					break;
				}

				iStartPos = rectRow.bottom + iRowSpace;
			}
			else
			{
				if (iStartPos == -1)
					iStartPos = rectClient.bottom;

				rectRow.bottom = iStartPos;

				switch(nResizeType)
				{
				case LEFT_SIZE_NO:
				case RIGHT_SIZE_NO:
					rectRow.top = rectRow.bottom - rectItem.Height();
					break;
				case LEFT_SIZE_H:
				case RIGHT_SIZE_H:
					rectRow.top = rectRow.bottom - rectItem.Height();
					if (m_sizeResizeMax.cx != -1)
					{
						rectRow.right = rectRow.left + m_sizeResizeMax.cx;
					}
					break;
				case LEFT_SIZE_V:
				case RIGHT_SIZE_V:
					if (m_sizeResizeMax.cy != -1)
					{
						rectRow.bottom = rectRow.top + m_sizeResizeMax.cy;
					}
					break;
				case LEFT_SIZE_HV:
				case RIGHT_SIZE_HV:
					if (m_sizeResizeMax.cx != -1)
					{
						rectRow.right = rectRow.left + m_sizeResizeMax.cx;
					}
					if (m_sizeResizeMax.cy != -1)
					{
						rectRow.bottom = rectRow.top + m_sizeResizeMax.cy;
					}
					break;
				default:
					ASSERT(FALSE);
					break;
				}

				iStartPos = rectRow.top - iRowSpace;

			}
		}

		pItem->SetRect(rectRow);
	}
}

// 函数 CResizeContainer::GetRowRect
// 作用：读取GetRowRect。
// 参数：iStartIndex：整数。
// 返回：返回 CRect。
// 过程：函数里会调用 SetRectEmpty、GetCount、GetAt、IsRectEmpty、GetRect、GetNewRow。
CRect CResizeContainer::GetRowRect(int iStartIndex)
{
	CRect rectRow;
	rectRow.SetRectEmpty();
	for (int i=iStartIndex; i<m_arrayChild.GetCount(); i++)
	{
		CResizeItem* pItem = (CResizeItem*)m_arrayChild.GetAt(i);
		if (rectRow.IsRectEmpty())
		{
			rectRow = pItem->GetRect();
			continue;
		}
		else
		{
			if (pItem->GetNewRow())
				break;
			CRect rectChild = pItem->GetRect();
			if (rectChild.Height() > rectRow.Height())
				rectRow.bottom = rectRow.top + rectChild.Height();

			if (rectRow.right < rectChild.right)
				rectRow.right = rectChild.right;
			if (rectRow.left > rectChild.left)
				rectRow.left = rectChild.left;
		}
	}

	return rectRow;
}

// 函数 CResizeContainer::SetWndShow
// 作用：设置SetWndShow。
// 参数：pInputWnd：指针，指向调用方传入的对象；bShow：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetCount、GetAt、FindAndSetShow。
void CResizeContainer::SetWndShow(CWnd* pInputWnd, BOOL bShow)
{
	BOOL bFind = FALSE;
	for (int i=0; i<m_arrayChild.GetCount(); i++)
	{
		CResizeItem* pItem = (CResizeItem*)m_arrayChild.GetAt(i);
		if (pItem->FindAndSetShow(pInputWnd, bShow))
		{
			bFind = TRUE;
			break;
		}
	}

	ASSERT(bFind);
}


// 函数 CResizeContainer::CalculateRowSpace
// 作用：计算CalculateRowSpace。
// 参数：rectArea：矩形区域。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 GetCount、GetAt、GetShow、GetNewRow、GetRowRect、Height。
int CResizeContainer::CalculateRowSpace(CRect rectArea)
{
	int iNeedHeight = 0;
	int iRowCount = 0;

	for (int i=0; i<m_arrayChild.GetCount(); i++)
	{
		CResizeItem* pItem = (CResizeItem*)m_arrayChild.GetAt(i);
		if (!pItem->GetShow())
			continue;

		if (pItem->GetNewRow())
		{
			CRect rectItem = GetRowRect(i);
			iNeedHeight += rectItem.Height();
			iRowCount ++;
		}
	}

	int iReturn = m_iRowSpace;
	if (iRowCount > 1)
	{
		if ((rectArea.Height() - iNeedHeight) / (iRowCount-1) < m_iRowSpace)
			iReturn = (rectArea.Height() - iNeedHeight) / (iRowCount-1);
	}

	return iReturn;
}
