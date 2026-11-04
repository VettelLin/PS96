// 【交接】 GeneralPcr\MyStatic.h
// 作用：MyStatic 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyStatic、DECLARE_MESSAGE_MAP、SetSingleLineState、GetSingleLineState、SetWordStyle、GetWordStyle、DrawItem。
#pragma once

#include "FontSet.h"
// CMyStatic

class CMyStatic : public CStatic,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyStatic。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyStatic)

public:
	// 函数 CMyStatic
	// 作用：执行CMyStatic。
	// 参数：bAutoDynamic：是或否。
	// 返回：没有返回值。
	CMyStatic(BOOL bAutoDynamic = FALSE);
	// 函数 ~CMyStatic
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyStatic();

private:
	COLORREF m_bkColor;
	COLORREF m_textColor;

	BOOL m_bSingleLine; //设置是否单行显示文字
	UINT m_nFormat;//定义文字显示格式
	BOOL m_bHasBkPic;
	BOOL m_bHasPngBkPic;
	BOOL m_bTwinkle;	//是否包含闪烁功能
	BOOL m_bTwinkleShow;	//闪烁是否处于显示状态，闪烁包含显示、不显示两种状态，结合m_bHasPngBkPic使用
	int  m_bkPicID;
	CString m_pngPicPath;
	int m_iconWidth;
	int m_sonPicNums;
	int m_curState;	//当前图标类型

	int m_iconLeftIndent;	//图标左侧缩进
	int m_iconRightIndent;	//图片右侧缩进

	BOOL m_bDynamic; 

	BOOL m_bFstPaint;
	CDC* m_pMemDc;
	BOOL m_bAutoDynamic;	//20190525添加，适用于大小固定、内容可变或者大小随着父窗口同比例变化的情况，第一次绘制时保存背景信息到m_pMemDc中，为了兼容之前的CStatic控件，保留m_bDynamic选项
	int  m_fstPaintWidth;
	int  m_fstPaintHeight;

	BOOL m_bHaveRoundRectBk;	//标识是否使用圆角背景样式
	COLORREF m_clrFourAngleBk;	//四角背景
	Color m_clrRoundRectBk;	//圆角背景
	int m_iArcRadius;	//圆角大小

public:
	HBITMAP m_hBitmap;

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

			// 函数 SetCurState
			// 作用：设置SetCurState。
			// 参数：curState；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCurState(int curState,BOOL bRedraw = FALSE);
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
			// 参数：textColor：颜色；bRedraw：是或否。
			// 返回：没有返回值。
			void SetTextColor(COLORREF textColor,BOOL bRedraw = FALSE);
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
			// 参数：picPath；sonPicNums；iconWidth；iconLeftIndent；iconRightIndent；bInvalidate：是或否。
			// 返回：没有返回值。
			void SetPngBkPic(CString picPath,int sonPicNums = 1,int iconWidth = 0,int iconLeftIndent = 0,int iconRightIndent = 0,BOOL bInvalidate = FALSE);

			// 函数 SetRoundRectBkParam
			// 作用：设置SetRoundRectBkParam。
			// 参数：bHaveRoundRectBk：是或否；clrFourAngle：颜色；clrRoundRectBk：矩形区域；iArcRadius：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRoundRectBkParam(BOOL bHaveRoundRectBk,COLORREF clrFourAngle,Color clrRoundRectBk,int iArcRadius,BOOL bRedraw = FALSE);
			// 函数 GetRoundRectBkColor
			// 作用：读取GetRoundRectBkColor。
			// 参数：无。
			// 返回：返回 Color。
			Color GetRoundRectBkColor();
			// 函数 GetRoundRectArcSize
			// 作用：读取GetRoundRectArcSize。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRoundRectArcSize();

			// 函数 SetBDynamic
			// 作用：设置SetBDynamic。
			// 参数：bDyNaminc：是或否。
			// 返回：没有返回值。
			void SetBDynamic(BOOL bDyNaminc);
			// 函数 GetBDynamic
			// 作用：读取GetBDynamic。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBDynamic();
		
			// 函数 StartTwinkle
			// 作用：执行StartTwinkle。
			// 参数：无。
			// 返回：没有返回值。
			void StartTwinkle();
			// 函数 StopTwinkle
			// 作用：执行StopTwinkle。
			// 参数：无。
			// 返回：没有返回值。
			void StopTwinkle();
		
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
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


