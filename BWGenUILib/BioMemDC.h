// 【交接】 BWGenUILib\BioMemDC.h
// 作用：BioMemDC 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CBioMemDC、Discard、FromDC、GetBitmap。
#pragma once

#include <afxwin.h>

class AFX_EXT_CLASS CBioMemDC : public CDC
{
    DECLARE_DYNAMIC(CBioMemDC);
public:
	// 函数 CBioMemDC
	// 作用：执行CBioMemDC。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；clrColor：颜色。
	// 返回：没有返回值。
	CBioMemDC(CDC* pDC, const CRect& rect, COLORREF clrColor=::GetSysColor(COLOR_3DFACE));
	// 函数 ~CBioMemDC
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CBioMemDC(void);

	// 函数 Discard
	// 作用：执行Discard。
	// 参数：无。
	// 返回：没有返回值。
	void Discard();

 	void FromDC();
	// 函数 GetBitmap
	// 作用：读取GetBitmap。
	// 参数：无。
	// 返回：返回 CBitmap&。
	CBitmap& GetBitmap();

protected:
	CDC* m_pDC; // Saves the CDC passed in constructor.
	CRect m_rc;  // Rectangle of the drawing area.
	CBitmap m_bitmap;  // Offscreen bitmap.
	HBITMAP m_hOldBitmap; // Original GDI object.
	BOOL m_bValid; // Flag used for autodraw in destructor.
};
