// 【交接】 GeneralPcr\GifProgressBar.cpp
// 作用：GifProgressBar。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：IMPLEMENT_DYNAMIC、CGifProgressBar、_T、SelectObject、DeleteDC、DeleteObject、BEGIN_MESSAGE_MAP、ON_WM_PAINT。
// Gif.cpp : implementation file
//

#include "stdafx.h"
#include "GifProgressBar.h"

// CGifProgressBar

IMPLEMENT_DYNAMIC(CGifProgressBar, CStatic)

// 函数 CGifProgressBar::CGifProgressBar
// 作用：执行CGifProgressBar。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CGifProgressBar::CGifProgressBar()
{
	m_pImg = NULL;
	m_gifFilePath = _T("");
	m_dimenCount = 0;
	m_pDimenIds = NULL;
	m_frameCount = 0;
	m_pPropertyItem = NULL;
	m_curCount = 0;	//当前显示的是哪一帧
	m_bFstPaint = TRUE;
	m_pMemDc = NULL;
	m_hBitmap = NULL;
	m_hGdiObj = NULL;
}

// 函数 CGifProgressBar::~CGifProgressBar
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SelectObject、DeleteDC、DeleteObject。
CGifProgressBar::~CGifProgressBar()
{
	if(NULL != m_pImg)
	{
		delete m_pImg;
		m_pImg = NULL;
	}
	
	if(NULL != m_pPropertyItem)
	{
		delete m_pPropertyItem;
		m_pPropertyItem = NULL;
	}

	if(NULL != m_pMemDc)
	{
		m_pMemDc->SelectObject(m_hGdiObj);
		m_pMemDc->DeleteDC();
		delete m_pMemDc;
		m_pMemDc = NULL;

		if(NULL != m_hBitmap)
		{
			::DeleteObject(m_hBitmap);
		}
	}
}

BEGIN_MESSAGE_MAP(CGifProgressBar, CStatic)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CGifProgressBar message handlers

// 函数 CGifProgressBar::OnPaint
// 作用：窗口需要重画时绘制内容。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 dc、clock、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width。
void CGifProgressBar::OnPaint()
{
	CPaintDC dc(this); 

#ifdef _DEBUG
	clock_t startMs = clock();
#endif

	CRect rcClient;
	GetClientRect(&rcClient);

	if(m_bFstPaint) 
	{
		m_pMemDc = new CDC;
		m_pMemDc->CreateCompatibleDC(&dc);
		m_hBitmap = ::CreateCompatibleBitmap(dc.m_hDC,rcClient.Width(),rcClient.Height()); //创建兼容位图
		HGDIOBJ m_hGdiObj = m_pMemDc->SelectObject(m_hBitmap);
		m_pMemDc->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&dc,0,0,SRCCOPY);

		m_bFstPaint = FALSE;
	}

	CDC memDc;
	memDc.CreateCompatibleDC(&dc);
	HBITMAP hBmp = ::CreateCompatibleBitmap(dc.m_hDC,rcClient.Width(),rcClient.Height()); //创建兼容位图
	HGDIOBJ hOldGdiObject = memDc.SelectObject(hBmp);
	memDc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),m_pMemDc,0,0,SRCCOPY);

	memDc.FillSolidRect(0,0,rcClient.Width(),rcClient.Height(),RGB(255,255,255));

	Graphics gc(memDc.m_hDC);

	m_pImg->SelectActiveFrame(&m_guid,m_curCount);
	RectF destRectF(0,0,rcClient.Width(),rcClient.Height());
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	if(m_pImg->GetWidth() > rcClient.Width() && m_pImg->GetHeight() > rcClient.Height())
	{
		gc.DrawImage(m_pImg,destRectF,(m_pImg->GetWidth() - rcClient.Width()) / 2,(m_pImg->GetHeight() - rcClient.Height()) / 2 - 6,rcClient.Width(),rcClient.Height(),UnitPixel,&ImgAtt);
	}
	else
	{
		gc.DrawImage(m_pImg,destRectF,0,0,m_pImg->GetWidth(),m_pImg->GetHeight(),UnitPixel,&ImgAtt);
	}
	
	dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDc,0,0,SRCCOPY);
	memDc.SelectObject(hOldGdiObject);
	::DeleteObject(hBmp);
	memDc.DeleteDC();

#ifdef _DEBUG
	clock_t endMs = clock();
	if(endMs - startMs > 15)
	{
		int k = 0;
		++k;
	}
#endif
}

// 函数 CGifProgressBar::OnDestroy
// 作用：窗口销毁前做清理。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 CStatic::OnDestroy。
void CGifProgressBar::OnDestroy()
{
	CStatic::OnDestroy();
}

// 函数 CGifProgressBar::SetGifFilePath
// 作用：设置SetGifFilePath。
// 参数：gifFilePath；bRedraw：是或否。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSafeHwnd、FromFile、c_str、GetFrameDimensionsCount、GetFrameDimensionsList、StringFromGUID2。
BOOL CGifProgressBar::SetGifFilePath(wstring gifFilePath,BOOL bRedraw /*= FALSE*/)
{
	if(NULL == GetSafeHwnd())
	{
		return FALSE;
	}

	if(NULL != m_pImg)
	{
		delete m_pImg;
		m_pImg = NULL;
	}
	if(NULL != m_pPropertyItem)
	{
		delete m_pPropertyItem;
		m_pPropertyItem = NULL;
	}

	m_gifFilePath = gifFilePath;
	m_pImg = Image::FromFile(m_gifFilePath.c_str());
	m_dimenCount = m_pImg->GetFrameDimensionsCount();
	GUID* pDimenIds = (GUID*)new GUID[m_dimenCount];
	m_pImg->GetFrameDimensionsList(pDimenIds,m_dimenCount);
	TCHAR strGuid[39] = {0};
	StringFromGUID2(pDimenIds[0],strGuid,39);
	m_frameCount = m_pImg->GetFrameCount(&(pDimenIds[0]));
	delete pDimenIds;
	pDimenIds = NULL;
	int size = m_pImg->GetPropertyItemSize(PropertyTagFrameDelay);
	byte* p = new byte[size];  
	m_pPropertyItem = (PropertyItem*)p;
	m_pImg->GetPropertyItem(PropertyTagFrameDelay,size,m_pPropertyItem);
	m_guid = FrameDimensionTime;

	m_curCount = 0;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate();
	}

	return TRUE;
}

// 函数 CGifProgressBar::GetGifFilePath
// 作用：读取GetGifFilePath。
// 参数：无。
// 返回：返回 wstring。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
wstring CGifProgressBar::GetGifFilePath()
{
	return m_gifFilePath;
}

// 函数 CGifProgressBar::GetDimenCount
// 作用：读取GetDimenCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
UINT CGifProgressBar::GetDimenCount()
{
	return m_dimenCount;
}

// 函数 CGifProgressBar::GetDimenIdsPtr
// 作用：读取GetDimenIdsPtr。
// 参数：无。
// 返回：返回指针 const GUID*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
const GUID* CGifProgressBar::GetDimenIdsPtr()
{
	return m_pDimenIds;
}

// 函数 CGifProgressBar::GetFrameCount
// 作用：读取GetFrameCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
UINT CGifProgressBar::GetFrameCount()
{
	return m_frameCount;
}

// 函数 CGifProgressBar::GetPropertyItemPtr
// 作用：读取GetPropertyItemPtr。
// 参数：无。
// 返回：返回指针 const PropertyItem*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
const PropertyItem* CGifProgressBar::GetPropertyItemPtr()
{
	return m_pPropertyItem;
}

// 函数 CGifProgressBar::GetGifGuid
// 作用：读取GetGifGuid。
// 参数：无。
// 返回：返回 GUID&。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
GUID& CGifProgressBar::GetGifGuid()
{
	return m_guid;
}

// 函数 CGifProgressBar::SetCurFrame
// 作用：设置SetCurFrame。
// 参数：curFrame；bRedraw：是或否。
// 返回：没有返回值。
// 过程：函数里会调用 GetSafeHwnd、Invalidate。
void CGifProgressBar::SetCurFrame(int curFrame,BOOL bRedraw /*= FALSE*/)
{
	if(curFrame < 0)
	{
		return;
	}

	if(curFrame >= m_frameCount)
	{
		curFrame = m_frameCount - 1;
	}

	m_curCount = curFrame;

	if(bRedraw && NULL != GetSafeHwnd())
	{
		Invalidate();
	}

	return;
}
