// 【交接】 GeneralPcr\MyPageSwitchBt.h
// 作用：MyPageSwitchBt 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyPageSwitchBt、DECLARE_MESSAGE_MAP、PreSubclassWindow、SetPngBkPic、SetBkColor、GetBkColor、SetTextColor。
#pragma once

#include "FontSet.h"
#include <GdiPlus.h>

using namespace Gdiplus;

// CMyPageSwitchBt

//按钮状态参数
#define CTRL_BUTTON_NOFOCUS 1
#define CTRL_BUTTON_FOCUS 2
#define CTRL_BUTTON_SELECTED 3
#define CTRL_BUTTON_DISABLE 4

class CMyPageSwitchBt : public CButton,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyPageSwitchBt。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyPageSwitchBt)

public:
	// 函数 CMyPageSwitchBt
	// 作用：执行CMyPageSwitchBt。
	// 参数：bAutoDynamic：是或否；bUseFourthState：是或否。
	// 返回：没有返回值。
	CMyPageSwitchBt(BOOL bAutoDynamic = FALSE,BOOL bUseFourthState = TRUE);
	// 函数 ~CMyPageSwitchBt
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyPageSwitchBt();

protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

protected:
	int	   m_srcWidth;
	int    m_srcHeight;
	int    m_ctrlState;

private:
	BOOL m_bTracking;

	BOOL m_bHasBkPic;
	BOOL m_bHasPathBkPic;
	BOOL m_bHasPngBkPic;
	int  m_sonPicNums;
	int  m_iconW;

	int m_iconLeftIndent;
	int m_iconRightIndent;
	int m_rightEnd;

	COLORREF m_bkClrNormal;
	COLORREF m_bkClrFocused;
	COLORREF m_bkClrClicked;
	COLORREF m_bkClrDisabled;
	COLORREF m_txClrNormal;
	COLORREF m_txClrFocused;
	COLORREF m_txClrClicked;
	COLORREF m_txClrDisabled;
	COLORREF m_edgeClrNormal;
	COLORREF m_edgeClrFocused;
	COLORREF m_edgeClrClicked;
	COLORREF m_edgeClrDisabled; 

	BOOL	m_bDrawFrame;	//是否绘制边框

	CString m_strPngPicPath;

	BOOL m_bInMiddle;	//是否居中
	BOOL m_bAmoySwtStyle;	//是否是艾德页面切换按钮
	COLORREF m_AmoySwtBkClr;	//艾德页面切换按钮背景色

	BOOL m_bGradientBk;	//是否是渐变色背景
	Color m_glrStart;
	Color m_glrEnd;
	LinearGradientMode m_gradientMode;

	BOOL m_bFstPaint;
	CDC* m_pMemDc;
	BOOL m_bAutoDynamic;	//20200903添加，适用于大小固定、内容可变或者大小随着父窗口同比例变化的情况，第一次绘制时保存背景信息到m_pMemDc中，为了兼容之前的CStatic控件，保留m_bDynamic选项
	int  m_fstPaintWidth;
	int  m_fstPaintHeight;
	HBITMAP m_hBitmap;

	UINT m_txFormat;

	BOOL m_bUseFourthState;	//禁用状态是否使用背景图片中的第四种状态，为否的话，禁用状态使用背景图片中的第三种状态

	BOOL m_bCkbtFunc;	//是否是“运行、停止”使用同一张背景图（背景图包含两个小图）
	BOOL m_bAddPageIcon;	//是否包含“+”图标

	int m_curStateId;	//从0开始

	int m_iCloseIconW;	//标识关闭按钮的宽度
	int m_iCloseIconH;	//标识关闭按钮的高度
	int m_iCloseIconRightIndent;	//标识关闭按钮距离按钮右侧的距离
	CRect m_rcCloseBt;	//记录关闭按钮区域

	BOOL m_bMouseInColseBtRect;	//记录鼠标是否在关闭按钮内

public:
	BOOL m_bBtPageRunning;	//标识按钮标识的页面是否正在运行中
	
	int m_pageId;
	static int PageCount;

	CString m_strFilePath;

public:
	// 函数 PreSubclassWindow
	// 作用：执行PreSubclassWindow。
	// 参数：无。
	// 返回：没有返回值。
	virtual void PreSubclassWindow();
			// 函数 SetPngBkPic
			// 作用：设置SetPngBkPic。
			// 参数：strPicPath：字符串；sonPicNums；iconWidth；iconLeftStart；iconRightStart；bRedraw：是或否。
			// 返回：没有返回值。
			void SetPngBkPic(CString strPicPath,int sonPicNums,int iconWidth = 0,int iconLeftStart = 0,int iconRightStart = 0,BOOL bRedraw = FALSE);
			// 函数 SetBkColor
			// 作用：设置SetBkColor。
			// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBkColor(COLORREF bkClrNormal,COLORREF bkClrFocused,COLORREF bkClrClicked,COLORREF bkClrDisabled,BOOL bRedraw = FALSE);
			// 函数 GetBkColor
			// 作用：读取GetBkColor。
			// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled。
			// 返回：没有返回值。
			void GetBkColor(COLORREF& bkClrNormal,COLORREF& bkClrFocused,COLORREF& bkClrClicked,COLORREF& bkClrDisabled);
			// 函数 SetTextColor
			// 作用：设置SetTextColor。
			// 参数：txClrNormal；txClrFocused；txClrClicked；txClrDisabled；bRedraw：是或否。
			// 返回：没有返回值。
			void SetTextColor(COLORREF txClrNormal,COLORREF txClrFocused,COLORREF txClrClicked,COLORREF txClrDisabled,BOOL bRedraw = FALSE);
			// 函数 GetTextColor
			// 作用：读取GetTextColor。
			// 参数：txClrNormal；txClrFocused；txClrClicked；txClrDisabled。
			// 返回：没有返回值。
			void GetTextColor(COLORREF& txClrNormal,COLORREF& txClrFocused,COLORREF& txClrClicked,COLORREF& txClrDisabled);
			// 函数 SetEdgeColor
			// 作用：设置SetEdgeColor。
			// 参数：edgeClrNormal；edgeClrFocused；edgeClrClicked；edgeClrDisabled；bRedraw：是或否。
			// 返回：没有返回值。
			void SetEdgeColor(COLORREF edgeClrNormal,COLORREF edgeClrFocused,COLORREF edgeClrClicked,COLORREF edgeClrDisabled,BOOL bRedraw = FALSE);
			// 函数 GetEdgeColor
			// 作用：读取GetEdgeColor。
			// 参数：edgeClrNormal；edgeClrFocused；edgeClrClicked；edgeClrDisabled。
			// 返回：没有返回值。
			void GetEdgeColor(COLORREF& edgeClrNormal,COLORREF& edgeClrFocused,COLORREF& edgeClrClicked,COLORREF& edgeClrDisabled);
			
			// 函数 SetDrawFrame
			// 作用：设置SetDrawFrame。
			// 参数：bDrawFrame：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetDrawFrame(BOOL bDrawFrame,BOOL bRedraw = FALSE);
			// 函数 GetDrawFrame
			// 作用：读取GetDrawFrame。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetDrawFrame();
			// 函数 SetBeInMiddle
			// 作用：设置SetBeInMiddle。
			// 参数：bInMiddle：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeInMiddle(BOOL bInMiddle,BOOL bRedraw = FALSE);
			// 函数 GetBeInMiddle
			// 作用：读取GetBeInMiddle。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeInMiddle();
			// 函数 SetTextFormat
			// 作用：设置SetTextFormat。
			// 参数：txFormat；bRedraw：是或否。
			// 返回：没有返回值。
			void SetTextFormat(UINT txFormat,BOOL bRedraw = FALSE);
			// 函数 GetTextFormat
			// 作用：读取GetTextFormat。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetTextFormat();
			// 函数 SetAmoySwtParam
			// 作用：设置SetAmoySwtParam。
			// 参数：bAmoySwtStyle：是或否；bkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetAmoySwtParam(BOOL bAmoySwtStyle,COLORREF bkClr,BOOL bRedraw = FALSE);
			// 函数 GetAmoySwtParam
			// 作用：读取GetAmoySwtParam。
			// 参数：bAmoySwtStyle：是或否；bkClr。
			// 返回：没有返回值。
			void GetAmoySwtParam(BOOL& bAmoySwtStyle,COLORREF& bkClr);
			// 函数 SetBeAmoySwtStyle
			// 作用：设置SetBeAmoySwtStyle。
			// 参数：bAmoySwtStyle：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeAmoySwtStyle(BOOL bAmoySwtStyle,BOOL bRedraw = FALSE);
			// 函数 GetBeAmoySwtStyle
			// 作用：读取GetBeAmoySwtStyle。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeAmoySwtStyle();
			// 函数 SetAmoySwtBkClr
			// 作用：设置SetAmoySwtBkClr。
			// 参数：bkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetAmoySwtBkClr(COLORREF bkClr,BOOL bRedraw = FALSE);
			// 函数 GetAmoySwtBkClr
			// 作用：读取GetAmoySwtBkClr。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetAmoySwtBkClr();

			// 函数 SetGradientParam
			// 作用：设置SetGradientParam。
			// 参数：bGradientBk：是或否；glrStart；glrEnd；gradientMode；bRedraw：是或否。
			// 返回：没有返回值。
			void SetGradientParam(BOOL bGradientBk,Color glrStart,Color glrEnd,LinearGradientMode gradientMode,BOOL bRedraw = FALSE);
			// 函数 GetGradientParam
			// 作用：读取GetGradientParam。
			// 参数：bGradientBk：是或否；glrStart；glrEnd；gradientMode。
			// 返回：没有返回值。
			void GetGradientParam(BOOL& bGradientBk,Color& glrStart,Color& glrEnd,LinearGradientMode& gradientMode);

			// 函数 SetCkbtFuncParam
			// 作用：设置SetCkbtFuncParam。
			// 参数：bCkbtFunc：是或否；curState；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCkbtFuncParam(BOOL bCkbtFunc,int curState,BOOL bRedraw = FALSE);
			// 函数 GetCkbtFuncParam
			// 作用：读取GetCkbtFuncParam。
			// 参数：bCkbtFunc：是或否；curState。
			// 返回：没有返回值。
			void GetCkbtFuncParam(BOOL& bCkbtFunc,int& curState);
			// 函数 SetBeCkbtFunc
			// 作用：设置SetBeCkbtFunc。
			// 参数：bCkbtFunc：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeCkbtFunc(BOOL bCkbtFunc,BOOL bRedraw = FALSE);
			// 函数 GetBeCkbtFunc
			// 作用：读取GetBeCkbtFunc。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeCkbtFunc();
			// 函数 SetCkbtFuncCurState
			// 作用：设置SetCkbtFuncCurState。
			// 参数：curState；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCkbtFuncCurState(int curState,BOOL bRedraw = FALSE);
			// 函数 GetCkbtFuncCurState
			// 作用：读取GetCkbtFuncCurState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetCkbtFuncCurState();

			// 函数 SetBeAddPageIcon
			// 作用：设置SetBeAddPageIcon。
			// 参数：bAddPageIcon：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeAddPageIcon(BOOL bAddPageIcon,BOOL bRedraw = FALSE);
			// 函数 GetBeAddPageIcon
			// 作用：读取GetBeAddPageIcon。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeAddPageIcon();

			// 函数 SetBeBtPageRunning
			// 作用：设置SetBeBtPageRunning。
			// 参数：bBtPageRunning：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeBtPageRunning(BOOL bBtPageRunning,BOOL bRedraw = FALSE);
			// 函数 GetBeBtPageRunning
			// 作用：读取GetBeBtPageRunning。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeBtPageRunning();

			// 函数 SetPageId
			// 作用：设置SetPageId。
			// 参数：pageId。
			// 返回：没有返回值。
			void SetPageId(int pageId);
			// 函数 GetPageId
			// 作用：读取GetPageId。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetPageId();

			// 函数 EnableWindow
			// 作用：改变EnableWindow的显示或可用状态。
			// 参数：bEnabled：是或否。
			// 返回：没有返回值。
			void EnableWindow(BOOL bEnabled);

public:
	// 函数 DrawItem
	// 作用：绘制DrawItem。
	// 参数：lpDrawItemStruct。
	// 返回：没有返回值。
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	// 函数 OnMouseMove
	// 作用：鼠标在窗口上移动。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 函数 OnMouseLeave
	// 作用：响应 Windows 或自定义消息 OnMouseLeave。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMouseLeave(WPARAM wParam,LPARAM lParam);
	// 函数 OnMouseHover
	// 作用：响应 Windows 或自定义消息 OnMouseHover。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMouseHover(WPARAM wParam,LPARAM lParam);
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnLButtonUp
	// 作用：松开鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);  
	// 函数 OnCaptureChanged
	// 作用：响应 Windows 或自定义消息 OnCaptureChanged。
	// 参数：pNewWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnCaptureChanged(CWnd* pNewWnd);
};


