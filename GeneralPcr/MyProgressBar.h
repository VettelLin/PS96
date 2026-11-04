// 【交接】 GeneralPcr\MyProgressBar.h
// 作用：MyProgressBar 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyProgressBar、DECLARE_MESSAGE_MAP、SetSingleLineState、GetSingleLineState、SetWordStyle、GetWordStyle、DrawItem。
#pragma once

#include "FontSet.h"
#include <GdiPlus.h>

// CMyProgressBar

class CMyProgressBar : public CStatic,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyProgressBar。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyProgressBar)

public:
	// 函数 CMyProgressBar
	// 作用：执行CMyProgressBar。
	// 参数：bAutoDynamic：是或否。
	// 返回：没有返回值。
	CMyProgressBar(BOOL bAutoDynamic = FALSE);
	// 函数 ~CMyProgressBar
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyProgressBar();

private:
	COLORREF m_bkColor;
	COLORREF m_textColor;

	BOOL m_bSingleLine; //设置是否单行显示文字
	UINT m_nFormat;//定义文字显示格式
	int  m_bkPicID;
	wstring m_pngPicPath;
	int m_iconWidth;

	BOOL m_bFstPaint;
	CDC* m_pMemDc;
	BOOL m_bAutoDynamic;	//20190525添加，适用于大小固定、内容可变或者大小随着父窗口同比例变化的情况，第一次绘制时保存背景信息到m_pMemDc中，为了兼容之前的CStatic控件，保留m_bDynamic选项
	int  m_fstPaintWidth;
	int  m_fstPaintHeight;
	HBITMAP m_hBitmap;

protected:
	Gdiplus::Color m_clrBk;	//主背景（非进度部分）颜色
	Gdiplus::Color m_clrFrame;	//主背景边框颜色
	Gdiplus::Color m_clrRopBk;	//进度背景颜色
	Gdiplus::Color m_clrRopFrame;	//进度背景边框颜色

public:
	double m_dProgress;

protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

public:
			// 函数 SetSingleLineState
			// 作用：设置SetSingleLineState。
			// 参数：bSingleLine：是或否。
			// 返回：没有返回值。
			void SetSingleLineState(BOOL bSingleLine = TRUE);
			// 函数 GetSingleLineState
			// 作用：读取GetSingleLineState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetSingleLineState();
			// 函数 SetWordStyle
			// 作用：设置SetWordStyle。
			// 参数：nFormat：整数；bInvalidate：是或否。
			// 返回：没有返回值。
			void SetWordStyle(UINT nFormat,BOOL bInvalidate = FALSE);
			// 函数 GetWordStyle
			// 作用：读取GetWordStyle。
			// 参数：nFormat：整数。
			// 返回：没有返回值。
			void GetWordStyle(UINT& nFormat);

	// 函数 DrawItem
	// 作用：绘制DrawItem。
	// 参数：lpDrawItemStruct。
	// 返回：没有返回值。
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// 函数 PreSubclassWindow
	// 作用：执行PreSubclassWindow。
	// 参数：无。
	// 返回：没有返回值。
	virtual void PreSubclassWindow();

			// 函数 SetBkColor
			// 作用：设置SetBkColor。
			// 参数：bkColor：颜色。
			// 返回：没有返回值。
			void SetBkColor(COLORREF bkColor);
			// 函数 GetBkColor
			// 作用：读取GetBkColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetBkColor();
			// 函数 SetTextColor
			// 作用：设置SetTextColor。
			// 参数：textColor：颜色；bInvalidate：是或否。
			// 返回：没有返回值。
			void SetTextColor(COLORREF textColor,BOOL bInvalidate = FALSE);
			// 函数 GetTextColor
			// 作用：读取GetTextColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetTextColor();
			// 函数 SetBmpBkPic
			// 作用：设置SetBmpBkPic。
			// 参数：bkPicId；iconWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBmpBkPic(int bkPicId,int iconWidth = 0,BOOL bRedraw = FALSE);
			// 函数 SetPngBkPic
			// 作用：设置SetPngBkPic。
			// 参数：picPath；bInvalidate：是或否。
			// 返回：没有返回值。
			void SetPngBkPic(wstring picPath,BOOL bInvalidate = FALSE);
			
			// 函数 SetCurProgress
			// 作用：设置SetCurProgress。
			// 参数：dProgress：小数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCurProgress(double dProgress,BOOL bRedraw = FALSE);
			// 函数 SetZero
			// 作用：设置SetZero。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void SetZero(BOOL bRedraw = FALSE);
			// 函数 SetOneHundred
			// 作用：设置SetOneHundred。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void SetOneHundred(BOOL bRedraw = FALSE);

			// 函数 GetProgress
			// 作用：读取GetProgress。
			// 参数：无。
			// 返回：返回一个小数。
			double GetProgress();

	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 WindowProc
	// 作用：执行WindowProc。
	// 参数：message；wParam；lParam。
	// 返回：返回 LRESULT。
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	// 函数 OnVScroll
	// 作用：垂直滚动条移动。
	// 参数：nSBCode：整数；nPos：整数；pScrollBar：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


