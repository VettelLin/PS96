// 【交接】 BWGenUILib\BioMemDC.cpp
// 作用：BioMemDC 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CBioMemDC、GetClipBox、CopyRect、SetMapMode、CreateCompatibleBitmap、SelectObject、rc。
#include "StdAfx.h"
#include "BioMemDC.h"

IMPLEMENT_DYNAMIC(CBioMemDC, CDC)

// 函数 CBioMemDC::CBioMemDC
// 作用：执行CBioMemDC。
// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；clrColor：颜色。
// 返回：没有返回值。
// 过程：函数里会调用 IsRectEmpty、GetClipBox、CopyRect、CreateCompatibleDC、SetMapMode、GetMapMode。
CBioMemDC::CBioMemDC(CDC* pDC, const CRect& rect, COLORREF clrColor)
{
	ASSERT(pDC != NULL);
	m_pDC = pDC;
	
	// If rect is NULL, use the device context's clip box.
	if (rect.IsRectEmpty())
		m_pDC->GetClipBox(&m_rc);
	else
		m_rc.CopyRect(&rect);

    // Create the memory DC, set Map Mode
	if (CreateCompatibleDC(m_pDC))
	{
		SetMapMode(m_pDC->GetMapMode());
		
		// Create a bitmap big enough to hold the window's image
		m_bitmap.CreateCompatibleBitmap(m_pDC, m_rc.Width(), m_rc.Height());
		
		// Select the bitmap into the memory DC
		m_hOldBitmap = (HBITMAP)SelectObject(&m_bitmap)->GetSafeHandle();
		
		// Repaint the background, this takes the place of WM_ERASEBKGND.
		if (clrColor != -1)
		{
			//P.Baranov
			CRect rc( m_rc );

			rc.left    = 0;
			rc.right  -= m_rc.left;
			rc.top     = 0;
			rc.bottom -= m_rc.top;

			FillSolidRect(rc, clrColor);
		}
		
		m_bValid = TRUE;
	}

	// Something bad happened, could be GDI leak, didn't create device context.
	else
	{
		m_bValid = FALSE;
		m_hOldBitmap = NULL;
	}
}

// 函数 CBioMemDC::~CBioMemDC
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 BitBlt、Width、Height、SelectObject、DeleteObject、DeleteDC。
CBioMemDC::~CBioMemDC(void)
{
	if (m_bValid)
	{
		// Blt it
		m_pDC->BitBlt(m_rc.left, m_rc.top, m_rc.Width(), m_rc.Height(), this, 0, 0, SRCCOPY);
	}

	// Select the original bitmap back in
	if (m_hOldBitmap != NULL)
	{
		SelectObject(m_hOldBitmap);
		m_bitmap.DeleteObject();
	}

	DeleteDC();
}
