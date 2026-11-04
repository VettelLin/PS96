// 【交接】 GeneralPcr\Gif.cpp
// 作用：Gif。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：IMPLEMENT_DYNAMIC、CGif、_T、SelectObject、DeleteDC、DeleteObject、BEGIN_MESSAGE_MAP、ON_WM_PAINT。
// Gif.cpp : implementation file
//

#include "stdafx.h"
#include "Gif.h"

// CGif

IMPLEMENT_DYNAMIC(CGif, CStatic)

// 函数 CGif::CGif
// 作用：执行CGif。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 _T。
CGif::CGif()
{
	m_pImg = NULL;
	m_gifFilePath = _T("");
	m_dimenCount = 0;
	m_pDimenIds = NULL;
	m_frameCount = 0;
	m_pPropertyItem = NULL;
	m_curCount = 0;	//当前显示的是哪一帧
	m_bGifRun = FALSE;
	m_timerId = 1;
	m_bFstPaint = TRUE;
	m_pMemDc = NULL;
	m_hBitmap = NULL;
	m_hGdiObj = NULL;
}

// 函数 CGif::~CGif
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 SelectObject、DeleteDC、DeleteObject。
CGif::~CGif()
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

BEGIN_MESSAGE_MAP(CGif, CStatic)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CGif message handlers

// 函数 CGif::OnPaint
// 作用：窗口需要重画时绘制内容。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 dc、clock、GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width。
void CGif::OnPaint()
{
	CPaintDC dc(this); 
	if(m_bGifRun)
	{
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

		Graphics gc(memDc.m_hDC);
		m_pImg->SelectActiveFrame(&m_guid,m_curCount++);
		RectF destRectF(0,0,rcClient.Width(),rcClient.Height());
		ImageAttributes ImgAtt;
		ImgAtt.SetWrapMode(WrapModeTileFlipXY);
		gc.DrawImage(m_pImg,destRectF,0,0,m_pImg->GetWidth(),m_pImg->GetHeight(),UnitPixel,&ImgAtt);
		dc.BitBlt(0,0,rcClient.Width(),rcClient.Height(),&memDc,0,0,SRCCOPY);
		memDc.SelectObject(hOldGdiObject);
		::DeleteObject(hBmp);
		memDc.DeleteDC();

		if(m_curCount == m_frameCount)
		{
			m_curCount = 0;
		}

#ifdef _DEBUG
		clock_t endMs = clock();
		if(endMs - startMs > 15)
		{
			int k = 0;
			++k;
		}
#endif
	}
}

// 函数 CGif::OnTimer
// 作用：定时器到期时刷新界面或推进状态。
// 参数：nIDEvent：整数。
// 返回：没有返回值。
// 过程：函数里会调用 KillTimer、_T、PopTipInfo、Invalidate、UpdateWindow、SetTimer。
void CGif::OnTimer(UINT_PTR nIDEvent)
{
	if(0 == KillTimer(nIDEvent))
	{
		CMyGeneTipInfo geneTipInfo;
		geneTipInfo.m_strTipInfo = _T("定时器关闭失败");
		PopTipInfo(geneTipInfo);
	}

	if(m_timerId == nIDEvent)
	{
		Invalidate();
		UpdateWindow();
 		if(0 == (m_timerId = SetTimer(nIDEvent,((long*)m_pPropertyItem->value)[m_curCount] * 6,NULL)))
		{
			CMyGeneTipInfo geneTipInfo;
			geneTipInfo.m_strTipInfo = _T("定时器启动失败");
			PopTipInfo(geneTipInfo);
		}
	}
}

// 函数 CGif::OnDestroy
// 作用：窗口销毁前做清理。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 KillTimer、_T。
void CGif::OnDestroy()
{
	if(m_bGifRun)
	{
		if(0 == KillTimer(m_timerId))
		{
			AfxMessageBox(_T("定时器关闭失败！"));
		}
	}

	CStatic::OnDestroy();
}

// 函数 CGif::SetGifFilePath
// 作用：设置SetGifFilePath。
// 参数：gifFilePath；bRedraw：是或否。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSafeHwnd、KillTimer、_T、FromFile、c_str、GetFrameDimensionsCount。
BOOL CGif::SetGifFilePath(wstring gifFilePath,BOOL bRedraw /*= FALSE*/)
{
	if(NULL == GetSafeHwnd())
	{
		return FALSE;
	}

	if(m_bGifRun)
	{
		m_bGifRun = FALSE;
		if(0 == KillTimer(m_timerId))
		{
			AfxMessageBox(_T("SetGifFilePath多次执行时定时器关闭失败"));
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
	}

	m_gifFilePath = gifFilePath;
	m_pImg = Image::FromFile(m_gifFilePath.c_str());
	//if (m_pImg->lastResult != Ok)
	//{

	//}
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

	m_bGifRun = TRUE;
	if(0 == (m_timerId = SetTimer(m_timerId,((long*)m_pPropertyItem->value)[m_curCount],NULL)))
	{
		AfxMessageBox(_T("定时器启动失败"));
	}

	if(bRedraw)
	{
		Invalidate();
	}

	return TRUE;
}

// 函数 CGif::GetGifFilePath
// 作用：读取GetGifFilePath。
// 参数：无。
// 返回：返回 wstring。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
wstring CGif::GetGifFilePath()
{
	return m_gifFilePath;
}

// 函数 CGif::SetTimerID
// 作用：设置SetTimerID。
// 参数：timerId。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CGif::SetTimerID(UINT_PTR timerId)
{
	m_timerId = timerId;
}

// 函数 CGif::GetTimerID
// 作用：读取GetTimerID。
// 参数：无。
// 返回：返回 UINT_PTR。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
UINT_PTR CGif::GetTimerID()
{
	return m_timerId;
}

// 函数 CGif::GetDimenCount
// 作用：读取GetDimenCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
UINT CGif::GetDimenCount()
{
	return m_dimenCount;
}

// 函数 CGif::GetDimenIdsPtr
// 作用：读取GetDimenIdsPtr。
// 参数：无。
// 返回：返回指针 const GUID*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
const GUID* CGif::GetDimenIdsPtr()
{
	return m_pDimenIds;
}

// 函数 CGif::GetFrameCount
// 作用：读取GetFrameCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
UINT CGif::GetFrameCount()
{
	return m_frameCount;
}

// 函数 CGif::GetPropertyItemPtr
// 作用：读取GetPropertyItemPtr。
// 参数：无。
// 返回：返回指针 const PropertyItem*。指针为空表示没有取到对象。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
const PropertyItem* CGif::GetPropertyItemPtr()
{
	return m_pPropertyItem;
}

// 函数 CGif::GetGifGuid
// 作用：读取GetGifGuid。
// 参数：无。
// 返回：返回 GUID&。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
GUID& CGif::GetGifGuid()
{
	return m_guid;
}

// 函数 CGif::Start
// 作用：执行Start。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSafeHwnd、SetTimer、_T。
BOOL CGif::Start()
{
	if(NULL == GetSafeHwnd())
	{
		return FALSE;
	}

	if(!m_bGifRun)
	{
		if(0 == (m_timerId = SetTimer(m_timerId,((long*)m_pPropertyItem->value)[m_curCount],NULL)))
		{
			AfxMessageBox(_T("定时器启动失败"));
			return FALSE;
		}
		m_bGifRun = TRUE;
	}
	return TRUE;
}

// 函数 CGif::Stop
// 作用：执行Stop。
// 参数：无。
// 返回：返回是或否。失败时返回 FALSE。
// 过程：函数里会调用 GetSafeHwnd、KillTimer、_T。
BOOL CGif::Stop()
{
	if(NULL == GetSafeHwnd())
	{
		return FALSE;
	}

	if(m_bGifRun)
	{
		if(0 == KillTimer(m_timerId))
		{
			AfxMessageBox(_T("定时器关闭失败！"));
			return FALSE;
		}
		m_bGifRun = FALSE;
	}
	return TRUE;
}
