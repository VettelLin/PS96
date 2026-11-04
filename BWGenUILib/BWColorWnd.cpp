// 【交接】 BWGenUILib\BWColorWnd.cpp
// 作用：BWColorWnd 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CBWColorWnd、RegisterWindowClass、RGB、SetColor、BEGIN_MESSAGE_MAP、ON_WM_PAINT、ON_WM_SIZE。
// BWColorWnd.cpp : implementation file
//

#include "stdafx.h"
#include "BWGenUILib.h"
#include "BWColorWnd.h"
#include "math.h"

// CBWColorWnd

IMPLEMENT_DYNAMIC(CBWColorWnd, CWnd)

// 函数 CBWColorWnd::CBWColorWnd
// 作用：执行CBWColorWnd。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 RegisterWindowClass、RGB。
CBWColorWnd::CBWColorWnd()
{
	RegisterWindowClass();
	m_iColorCount = 0;
	m_pArrayColor = NULL;
	m_iColCount = 0;
	m_iRowCount = 0;
	m_bChanged = FALSE;

	m_iRowClicked = -1;
	m_iColClicked = -1;

	m_bPopup = FALSE;
	m_iItem = -1;
	m_iSubItem = -1;
	m_clrInit = RGB(255, 255, 255);
}

// 函数 CBWColorWnd::CBWColorWnd
// 作用：执行CBWColorWnd。
// 参数：iItem：整数；iSubItem：整数；clrInit：颜色；iCount：整数；pArrayColor：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 RegisterWindowClass、SetColor。
CBWColorWnd::CBWColorWnd(int iItem, int iSubItem, COLORREF clrInit, int iCount, COLORREF* pArrayColor)
{
	RegisterWindowClass();
	m_iColorCount = 0;
	m_pArrayColor = NULL;
	m_iColCount = 0;
	m_iRowCount = 0;
	m_bChanged = FALSE;

	m_iRowClicked = -1;
	m_iColClicked = -1;

	m_bPopup = TRUE;
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_clrInit = clrInit;
	SetColor(iCount, pArrayColor);
}


// 函数 CBWColorWnd::~CBWColorWnd
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CBWColorWnd::~CBWColorWnd()
{
	if (m_pArrayColor != NULL)
	{
		delete m_pArrayColor;
		m_pArrayColor = NULL;
	}
}


BEGIN_MESSAGE_MAP(CBWColorWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// 函数 CBWColorWnd::SetColor
// 作用：设置SetColor。
// 参数：iCount：整数；pInputColor：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 CalculateColAndRow、Invalidate。
void CBWColorWnd::SetColor(int iCount, COLORREF* pInputColor)
{
	if (iCount != m_iColorCount)
	{
		if (m_pArrayColor != NULL)
		{
			delete m_pArrayColor;
			m_pArrayColor = NULL;
		}

		m_iColorCount = iCount;
		m_pArrayColor = new COLORREF[iCount];

		CalculateColAndRow(iCount);
	}

	for (int i=0; i<m_iColorCount; i++)
	{
		m_pArrayColor[i] = pInputColor[i];
	}

	m_bChanged = FALSE;
	if (m_hWnd != NULL)
	{
		Invalidate();
	}
}

// 函数 CBWColorWnd::CalculateColAndRow
// 作用：计算CalculateColAndRow。
// 参数：iCount：整数。
// 返回：没有返回值。
// 过程：函数里会调用 sqrt、double。
void CBWColorWnd::CalculateColAndRow(int iCount)
{
	int iTempRow = (int)::sqrt(double(iCount));
	if (iCount % iTempRow == 0)
	{
		m_iRowCount = iTempRow;
		m_iColCount = iCount / m_iRowCount;
	}
	else
	{
		if (iCount % (iTempRow -1) == 0)
		{
			m_iRowCount = iTempRow - 1;
			m_iColCount = iCount / m_iRowCount;
		}
		else
		{
			m_iRowCount = iTempRow - 1;
			m_iColCount = iCount / m_iRowCount + 1;
		}
	}
}


// CBWColorWnd message handlers

// 函数 CBWColorWnd::RegisterWindowClass
// 作用：执行RegisterWindowClass。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 AfxGetInstanceHandle、GetClassInfo、AfxGetApp、LoadStandardCursor、AfxRegisterClass、AfxThrowResourceException。
BOOL CBWColorWnd::RegisterWindowClass()
{
	WNDCLASS wndClass;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, CLASSNAME_BWCOLORWND, &wndClass)))
	{
		// otherwise we need to register a new class
		wndClass.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = ::DefWindowProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = hInst;
		wndClass.hIcon = NULL;
		wndClass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndClass.hbrBackground = NULL;
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = CLASSNAME_BWCOLORWND;

		if (!AfxRegisterClass(&wndClass)) {
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

// 函数 CBWColorWnd::Create
// 作用：创建或加入Create。
// 参数：dwStyle；rect：矩形区域；pParentWnd：指针，指向调用方传入的对象；nID：整数。
// 返回：返回是或否。
// 过程：函数里会调用 SetFocus。
BOOL CBWColorWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL bSuccess = CWnd::Create(CLASSNAME_BWCOLORWND, NULL, dwStyle, rect, pParentWnd, nID);
	if (bSuccess)
		SetFocus();

	return bSuccess;
}

// 函数 CBWColorWnd::OnPaint
// 作用：窗口需要重画时绘制内容。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 dc、GetClientRect、FillSolidRect、RGB、DeflateRect、Width。
void CBWColorWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect(rectClient);

	dc.FillSolidRect(rectClient, RGB(198, 198, 198));

	CRect rectDraw = rectClient;
	rectDraw.DeflateRect(2, 2);
	dc.FillSolidRect(rectDraw, RGB(255, 255, 255));

	float fWidth = rectDraw.Width() / float(m_iColCount);
	float fHeight = rectDraw.Height() / float(m_iRowCount);

	m_arrayCellArea.RemoveAll();
	CRect rectCell;
	for (int i=0; i<m_iRowCount; i++)
	{
		for (int j=0; j<m_iColCount; j++)
		{
			int iIndex = i * m_iColCount + j;
			if (iIndex >= m_iColorCount)
				break;

			rectCell.left = int(j * fWidth + 0.5) + rectDraw.left;
			rectCell.right = int((j+1) * fWidth + 0.5) + rectDraw.left;
			rectCell.top = int(i * fHeight + 0.5) + rectDraw.top;
			rectCell.bottom = int((i+1) * fHeight + 0.5) + rectDraw.top;

			rectCell.DeflateRect(1, 1);
			dc.FillSolidRect(rectCell, m_pArrayColor[iIndex]);
			m_arrayCellArea.Add(rectCell);
		}
	}
}

// 函数 CBWColorWnd::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 CWnd::OnEraseBkgnd。
BOOL CBWColorWnd::OnEraseBkgnd(CDC* pDC)
{
	// return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}

// 函数 CBWColorWnd::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 CWnd::OnSize。
void CBWColorWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

}

// 函数 CBWColorWnd::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 SetFocus、GetAt、PtInRect、SendDisplayInfo、dlg、DoModal。
void CBWColorWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();

	m_iRowClicked = -1;
	m_iColClicked = -1;
	int iIndex = -1;
	for (int i=0; i<m_iColorCount; i++)
	{
		CRect rect = m_arrayCellArea.GetAt(i);
		if (rect.PtInRect(point))
		{
			iIndex = i;
			m_iRowClicked = i / m_iColCount;
			m_iColClicked = i % m_iColCount;
			break;
		}
	}

	if (m_iRowClicked != -1 && m_iColClicked != -1)
	{
		if (m_bPopup)
		{
			SendDisplayInfo(iIndex);
		}
		else
		{
			CColorDialog dlg(m_pArrayColor[iIndex]);
			if (dlg.DoModal() == IDOK)
			{
				COLORREF color = dlg.GetColor();
				if (color != m_pArrayColor[iIndex])
				{
					m_pArrayColor[iIndex] = color;
					InvalidateRect(m_arrayCellArea.GetAt(iIndex));
					m_bChanged = TRUE;
				}
			}
		}
	}

	//CWnd::OnLButtonDown(nFlags, point);
}

// 函数 CBWColorWnd::OnKillFocus
// 作用：响应 Windows 或自定义消息 OnKillFocus。
// 参数：pNewWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 SendDisplayInfo。
void CBWColorWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	SendDisplayInfo();
}


// 函数 CBWColorWnd::SendDisplayInfo
// 作用：执行SendDisplayInfo。
// 参数：iIndex：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetParent、GetDlgCtrlID、LPTSTR、GetLength、SendMessage。
void CBWColorWnd::SendDisplayInfo(int iIndex)
{
	LV_DISPINFO dispinfo;
	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	dispinfo.hdr.code = LVN_ENDLABELEDIT;

	dispinfo.item.mask = LVIF_PARAM;
	dispinfo.item.iItem = m_iItem;
	dispinfo.item.iSubItem = m_iSubItem;
	//dispinfo.item.pszText = m_bEscPressed ? LPTSTR((LPCTSTR)m_strInitText) : LPTSTR((LPCTSTR)strText);
	//dispinfo.item.cchTextMax = m_bEscPressed ? m_strInitText.GetLength() : strText.GetLength();
	if (iIndex == -1)
	{
		dispinfo.item.lParam = m_clrInit;
	}
	else
	{
		dispinfo.item.lParam = m_pArrayColor[iIndex];
	}

	GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo );

}
