// 【交接】 GeneralPcr\Gif.h
// 作用：Gif。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：DECLARE_DYNAMIC、CGif、DECLARE_MESSAGE_MAP、OnPaint、OnTimer、OnDestroy、SetGifFilePath、GetGifFilePath。
#pragma once

#include<GdiPlus.h>
#include <xstring>

using namespace Gdiplus;
using namespace std;
// CGif

class CGif : public CStatic
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CGif。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CGif)

public:
	// 函数 CGif
	// 作用：执行CGif。
	// 参数：无。
	// 返回：没有返回值。
	CGif();
	// 函数 ~CGif
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CGif();

protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

public:
	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 函数 OnDestroy
	// 作用：窗口销毁前做清理。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnDestroy();
			// 函数 SetGifFilePath
			// 作用：设置SetGifFilePath。
			// 参数：gifFilePath；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetGifFilePath(wstring gifFilePath,BOOL bRedraw = FALSE);	//窗口创建后该函数才有效
			// 函数 GetGifFilePath
			// 作用：读取GetGifFilePath。
			// 参数：无。
			// 返回：返回 wstring。
			wstring GetGifFilePath();
			// 函数 SetTimerID
			// 作用：设置SetTimerID。
			// 参数：timerId。
			// 返回：没有返回值。
			void SetTimerID(UINT_PTR timerId);
			// 函数 GetTimerID
			// 作用：读取GetTimerID。
			// 参数：无。
			// 返回：返回 UINT_PTR。
			UINT_PTR GetTimerID();
			// 函数 GetDimenCount
			// 作用：读取GetDimenCount。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetDimenCount();
	const GUID* GetDimenIdsPtr();
			// 函数 GetFrameCount
			// 作用：读取GetFrameCount。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetFrameCount();
	const PropertyItem* GetPropertyItemPtr();
			// 函数 GetGifGuid
			// 作用：读取GetGifGuid。
			// 参数：无。
			// 返回：返回 GUID&。
			GUID& GetGifGuid();
			// 函数 Start
			// 作用：执行Start。
			// 参数：无。
			// 返回：返回是或否。
			BOOL Start();
			// 函数 Stop
			// 作用：执行Stop。
			// 参数：无。
			// 返回：返回是或否。
			BOOL Stop();

private:
	wstring m_gifFilePath;
	UINT m_dimenCount;
	GUID* m_pDimenIds;
	UINT m_frameCount;
	PropertyItem* m_pPropertyItem;
	GUID m_guid;

	Image* m_pImg;

	int m_curCount;	//当前显示的是哪一帧

	BOOL m_bGifRun;

	UINT_PTR m_timerId;
	BOOL m_bFstPaint;
	CDC* m_pMemDc;

public:
	HBITMAP m_hBitmap;	//第一次绘制之前的背景图
	HGDIOBJ m_hGdiObj;
};


