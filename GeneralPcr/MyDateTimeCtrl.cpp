// 【交接】 GeneralPcr\MyDateTimeCtrl.cpp
// 作用：MyDateTimeCtrl 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CMyDateTimeCtrl、BEGIN_MESSAGE_MAP、ON_WM_SIZE、ON_WM_NCPAINT、ON_WM_PAINT、ON_WM_LBUTTONDOWN、ON_WM_ERASEBKGND。
// MyDateTimeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyDateTimeCtrl.h"

// CMyDateTimeCtrl

IMPLEMENT_DYNAMIC(CMyDateTimeCtrl, CDateTimeCtrl)

// 函数 CMyDateTimeCtrl::CMyDateTimeCtrl
// 作用：执行CMyDateTimeCtrl。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyDateTimeCtrl::CMyDateTimeCtrl()
{
	m_bTellParentDtChanged = FALSE;
	m_iDtTypeTag = TRUE;
}

// 函数 CMyDateTimeCtrl::~CMyDateTimeCtrl
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CMyDateTimeCtrl::~CMyDateTimeCtrl()
{

}

BEGIN_MESSAGE_MAP(CMyDateTimeCtrl, CDateTimeCtrl)
	ON_WM_SIZE()
	ON_WM_NCPAINT()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_NOTIFY_REFLECT(DTN_DATETIMECHANGE,OnDtnDatetimechange)
END_MESSAGE_MAP()

// 函数 CMyDateTimeCtrl::OnSize
// 作用：窗口大小变化时重新摆放控件。
// 参数：nType：整数；cx；cy。
// 返回：没有返回值。
// 过程：函数里会调用 __super::OnSize。
void CMyDateTimeCtrl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
}

// 函数 CMyDateTimeCtrl::OnNcPaint
// 作用：绘制标题栏等非客户区。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyDateTimeCtrl::OnNcPaint()
{
	
}

// 函数 CMyDateTimeCtrl::OnPaint
// 作用：窗口需要重画时绘制内容。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 dc、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height。
void CMyDateTimeCtrl::OnPaint()
{
	CPaintDC dc(this); 

	CRect rect;
	GetClientRect(&rect);
	
	int iIconW = 40 * m_dHoriRatio;
	int iIconH = iIconW;

	CDC memDc;
	memDc.CreateCompatibleDC(&dc);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(&rect,RGB(255,255,255));

	CBrush brush;
	brush.CreateSolidBrush(RGB(197,197,197));
	memDc.FrameRect(&rect,&brush);
	brush.DeleteObject();

	Graphics graphics(memDc.m_hDC);
	Image image(_T(".\\BkPic\\date.png"));

	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);

	Rect destRect;
	destRect.X = rect.Width() - image.GetWidth() - 10;
	destRect.Y = (rect.Height() - image.GetHeight()) / 2;
	destRect.Width = image.GetWidth();
	destRect.Height = image.GetHeight();

	graphics.DrawImage(&image,destRect,0,0,image.GetWidth(),image.GetHeight(),UnitPixel,&ImgAtt);
	graphics.ReleaseHDC(memDc.m_hDC);
	
	COleDateTime curOleDateTime;
	GetTime(curOleDateTime);

	CString strText(curOleDateTime.Format(_T("%Y/%m/%d")));
	if(!strText.IsEmpty())
	{
		CRect rcText = rect;
		rcText.left += 5 * m_dHoriRatio;
		rcText.right -= (iIconW + 10 * m_dHoriRatio);

		int nOldBkMode = memDc.SetBkMode(TRANSPARENT);
		CFont* pOldFont = memDc.SelectObject(&m_fontSet);
		memDc.SetTextColor(RGB(86,86,86));
		memDc.DrawText(strText,&rcText,DT_LEFT | DT_SINGLELINE | DT_VCENTER);
		memDc.SelectObject(&pOldFont);
		memDc.SetBkMode(nOldBkMode);
	}	

	dc.BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);
	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return;
}

// 函数 CMyDateTimeCtrl::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 __super::OnLButtonDown。
void CMyDateTimeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	__super::OnLButtonDown(nFlags, point);
}


// 函数 CMyDateTimeCtrl::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyDateTimeCtrl::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

// 函数 CMyDateTimeCtrl::OnDtnDatetimechange
// 作用：响应 Windows 或自定义消息 OnDtnDatetimechange。
// 参数：pNMHDR：指针，指向调用方传入的对象；pResult：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 Invalidate、GetParent、GetSafeHwnd、PostMessage。
void CMyDateTimeCtrl::OnDtnDatetimechange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);

	*pResult = 0;
	Invalidate(FALSE);

	CWnd* pParent = GetParent();
	if(m_bTellParentDtChanged && NULL != pParent->GetSafeHwnd())
	{
		pParent->PostMessage(WM_DATECTRLCHANGED,m_iDtTypeTag,0);
	}

	return;
}

// 函数 CMyDateTimeCtrl::SetTellParentDtChangedParam
// 作用：设置SetTellParentDtChangedParam。
// 参数：bTell：是或否；iDtTypeTag：整数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CMyDateTimeCtrl::SetTellParentDtChangedParam(BOOL bTell,int iDtTypeTag)
{
	m_bTellParentDtChanged = bTell;
	m_iDtTypeTag = iDtTypeTag;

	return;
}

// 函数 CMyDateTimeCtrl::IsTllParentDtChanged
// 作用：判断IsTllParentDtChanged是否成立。
// 参数：无。
// 返回：返回是或否。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
BOOL CMyDateTimeCtrl::IsTllParentDtChanged()
{
	return m_bTellParentDtChanged;
}

// 函数 CMyDateTimeCtrl::GetDtTypeTag
// 作用：读取GetDtTypeTag。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
int CMyDateTimeCtrl::GetDtTypeTag()
{
	return m_iDtTypeTag;
}

