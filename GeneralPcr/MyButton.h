// 【交接】 GeneralPcr\MyButton.h
// 作用：MyButton 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyButton、DECLARE_MESSAGE_MAP、PreSubclassWindow、SetBmpBkPic、SetPngBkPic、SetNewBmpBkPic、SetTextColor。
#pragma once

#include "FontSet.h"
#include <GdiPlus.h>
#include "IconBtInfo.h"
// CMyButton

//按钮状态参数
#define CTRL_BUTTON_NOFOCUS 1
#define CTRL_BUTTON_FOCUS 2
#define CTRL_BUTTON_SELECTED 3
#define CTRL_BUTTON_DISABLE 4

//最小化、缩放、关闭按钮
typedef enum DlgSizeBtType{
	EDSBT_MINIMUM = 1,EDSBT_ZOOM,EDSBT_CLOSE
}EDLGSIZEBTTYPE;

class CMyButton : public CButton,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyButton。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyButton)

public:
	// 函数 CMyButton
	// 作用：执行CMyButton。
	// 参数：bAutoDynamic：是或否。
	// 返回：没有返回值。
	CMyButton(BOOL bAutoDynamic = FALSE);
	// 函数 ~CMyButton
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyButton();

protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

protected:
	UINT   m_idNormal;
	UINT   m_idFocus;
	UINT   m_idSelected;
	UINT   m_idDisabled;

	int	   m_srcWidth;
	int    m_srcHeight;
	int    m_ctrlState;

private:
	COLORREF m_textColor;
	BOOL m_bTracking;

	BOOL m_bHasBkPic;
	BOOL m_bHasPathBkPic;
	BOOL m_bHasPngBkPic;
	int  m_sonPicNums;
	int  m_iconW;

	int m_iLeftIndent;	//图片显示位置左侧缩进
	int m_iRightIndent;	//图片显示位置右侧缩进

	int m_rightEnd;

	Color m_bkClrNormal;	//背景色
	Color m_bkClrFocused;
	Color m_bkClrClicked;
	Color m_bkClrDisabled;

	Color m_bkClrNormalEnd;	//渐变色终点背景颜色
	Color m_bkClrFocusedEnd;
	Color m_bkClrClickedEnd;
	Color m_bkClrDisabledEnd;
	
	Color m_edgeClrNormal;	//边框颜色
	Color m_edgeClrFocused;
	Color m_edgeClrClicked;
	Color m_edgeClrDisabled;

	COLORREF m_txClrNormal;
	COLORREF m_txClrFocused;
	COLORREF m_txClrClicked;
	COLORREF m_txClrDisabled;

	BOOL	m_bDrawFrame;	//是否绘制边框

	CString m_strPngPicPath;

	BOOL m_bInMiddle;	//是否居中

	BOOL m_bDlgSizeBt;	//标识是否是关闭、最小化、缩放按钮
	EDLGSIZEBTTYPE m_eDlgSizeBtType;

	BOOL m_bTwinkle;	//是否包含闪烁功能
	BOOL m_bTwinkleShow;	//闪烁是否处于显示状态，闪烁包含显示、不显示两种状态，结合m_bHasPngBkPic使用
	int m_curState;	//当前图标类型
	int m_curState2;	//和m_curState对立的闪烁类型

	BOOL m_bTextDown;	//标识文字在图片下方

	CIconBtInfo m_iConBtInfo;
	BOOL m_bIconBt;	//标识是否是图标型按钮

	BOOL m_bHaveTxPushedFormat;	//标识是否包含文字被按下样式

	DWORD m_dWordStyle;

	BOOL m_bFstPaint;
	CDC* m_pMemDc;
	BOOL m_bAutoDynamic;	//20190525添加，适用于大小固定、内容可变或者大小随着父窗口同比例变化的情况，第一次绘制时保存背景信息到m_pMemDc中，为了兼容之前的CStatic控件，保留m_bDynamic选项
	int  m_fstPaintWidth;
	int  m_fstPaintHeight;
	HBITMAP m_hBitmap;

protected:
	BOOL m_bRoundRectBk;
	COLORREF m_clrRoundRectBk;	//标识四个圆角外部背景色
	BOOL m_bGradientBk;	//标识是否是渐变色背景

public:
	// 函数 PreSubclassWindow
	// 作用：执行PreSubclassWindow。
	// 参数：无。
	// 返回：没有返回值。
	virtual void PreSubclassWindow();
			// 函数 SetBmpBkPic
			// 作用：设置SetBmpBkPic。
			// 参数：idPic；sonPicNums；btIconW；leftStart；rightEnd；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBmpBkPic(UINT idPic,int sonPicNums = 2,int btIconW = 0,int leftStart = 0,int rightEnd = 0,BOOL bRedraw = FALSE);
			// 函数 SetPngBkPic
			// 作用：设置SetPngBkPic。
			// 参数：strPicPath：字符串；sonPicNums；iIconWidth：整数；iLeftIndent：整数；iRightIndent：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetPngBkPic(CString strPicPath,int sonPicNums,int iIconWidth = 0,int iLeftIndent = 0,int iRightIndent = 0,BOOL bRedraw = FALSE);
			// 函数 SetNewBmpBkPic
			// 作用：设置SetNewBmpBkPic。
			// 参数：idPic；sonPicNums；bInvalidate：是或否。
			// 返回：没有返回值。
			void SetNewBmpBkPic(UINT idPic,int sonPicNums,BOOL bInvalidate);
			// 函数 SetBmpBkPic
			// 作用：设置SetBmpBkPic。
			// 参数：idNormal；idFocus；idSelected；idDisabled；btIconW；leftStart；rightEnd。
			// 返回：没有返回值。
			void SetBmpBkPic(UINT idNormal,UINT idFocus,UINT idSelected,UINT idDisabled,int btIconW,int leftStart = 0,int rightEnd = 0);
			// 函数 SetTextColor
			// 作用：设置SetTextColor。
			// 参数：textColor：颜色。
			// 返回：没有返回值。
			void SetTextColor(COLORREF textColor);
			// 函数 GetTextColor
			// 作用：读取GetTextColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetTextColor();
			// 函数 SetBkColor
			// 作用：设置SetBkColor。
			// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBkColor(Color bkClrNormal,Color bkClrFocused,Color bkClrClicked,Color bkClrDisabled,BOOL bRedraw = FALSE);
			// 函数 GetBkColor
			// 作用：读取GetBkColor。
			// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled。
			// 返回：没有返回值。
			void GetBkColor(Color& bkClrNormal,Color& bkClrFocused,Color& bkClrClicked,Color& bkClrDisabled);
			// 函数 SetBkColorEnd
			// 作用：设置SetBkColorEnd。
			// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBkColorEnd(Color bkClrNormal,Color bkClrFocused,Color bkClrClicked,Color bkClrDisabled,BOOL bRedraw = FALSE);
			// 函数 GetBkColorEnd
			// 作用：读取GetBkColorEnd。
			// 参数：bkClrNormal；bkClrFocused；bkClrClicked；bkClrDisabled。
			// 返回：没有返回值。
			void GetBkColorEnd(Color& bkClrNormal,Color& bkClrFocused,Color& bkClrClicked,Color& bkClrDisabled);
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
			void SetEdgeColor(Color edgeClrNormal,Color edgeClrFocused,Color edgeClrClicked,Color edgeClrDisabled,BOOL bRedraw = FALSE);
			// 函数 GetEdgeColor
			// 作用：读取GetEdgeColor。
			// 参数：edgeClrNormal；edgeClrFocused；edgeClrClicked；edgeClrDisabled。
			// 返回：没有返回值。
			void GetEdgeColor(Color& edgeClrNormal,Color& edgeClrFocused,Color& edgeClrClicked,Color& edgeClrDisabled);
			// 函数 SetRoundRectParam
			// 作用：设置SetRoundRectParam。
			// 参数：bRoundRect：是或否；clrRoundRectBk：矩形区域；bGradientBk：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRoundRectParam(BOOL bRoundRect,COLORREF clrRoundRectBk,BOOL bGradientBk,BOOL bRedraw = FALSE);
			// 函数 GetRoundRectParam
			// 作用：读取GetRoundRectParam。
			// 参数：bRoundRect：是或否；clrRoundRectBk：矩形区域；bGradientBk：是或否。
			// 返回：没有返回值。
			void GetRoundRectParam(BOOL& bRoundRect,COLORREF& clrRoundRectBk,BOOL& bGradientBk);
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
			// 函数 SetDlgSizeBtParam
			// 作用：设置SetDlgSizeBtParam。
			// 参数：bDlgSizeBt：是或否；eDlgSizeBtType；bRedraw：是或否。
			// 返回：没有返回值。
			void SetDlgSizeBtParam(BOOL bDlgSizeBt,EDLGSIZEBTTYPE eDlgSizeBtType,BOOL bRedraw = FALSE);
			// 函数 GetBeDlgSizeBt
			// 作用：读取GetBeDlgSizeBt。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeDlgSizeBt();
			// 函数 GetDlgSizeBtType
			// 作用：读取GetDlgSizeBtType。
			// 参数：无。
			// 返回：返回 EDLGSIZEBTTYPE。
			EDLGSIZEBTTYPE GetDlgSizeBtType();
			// 函数 SetBeTextDown
			// 作用：设置SetBeTextDown。
			// 参数：bTextDown：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeTextDown(BOOL bTextDown,BOOL bRedraw = FALSE);
			// 函数 GetBeTextDown
			// 作用：读取GetBeTextDown。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeTextDown();

			// 函数 SetWordStyle
			// 作用：设置SetWordStyle。
			// 参数：dwWordStyle；bRedraw：是或否。
			// 返回：没有返回值。
			void SetWordStyle(DWORD dwWordStyle,BOOL bRedraw = FALSE);
			// 函数 GetWordStyle
			// 作用：读取GetWordStyle。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			DWORD GetWordStyle();

			// 函数 SetCurState
			// 作用：设置SetCurState。
			// 参数：curState；curState2；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCurState(int curState,int curState2,BOOL bRedraw = FALSE);
			// 函数 GetCurState
			// 作用：读取GetCurState。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCurState();
			// 函数 GetCurState2
			// 作用：读取GetCurState2。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCurState2();

			// 函数 GetBeTwinkle
			// 作用：读取GetBeTwinkle。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeTwinkle();

			// 函数 EnableWindow
			// 作用：改变EnableWindow的显示或可用状态。
			// 参数：bEnabled：是或否。
			// 返回：没有返回值。
			void EnableWindow(BOOL bEnabled);
			
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
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT_PTR nIDEvent);

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

			// 函数 SetIconBtInfo
			// 作用：设置SetIconBtInfo。
			// 参数：info；bRedraw：是或否。
			// 返回：没有返回值。
			void SetIconBtInfo(CIconBtInfo info,BOOL bRedraw = FALSE);
			// 函数 SetIconBtPath
			// 作用：设置SetIconBtPath。
			// 参数：strPath：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetIconBtPath(CString strPath,BOOL bRedraw = FALSE);
			// 函数 GetIconBtInfo
			// 作用：读取GetIconBtInfo。
			// 参数：无。
			// 返回：返回 CIconBtInfo。
			CIconBtInfo GetIconBtInfo();
			// 函数 SetIconBtTxRectEndX
			// 作用：设置SetIconBtTxRectEndX。
			// 参数：iEndX：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetIconBtTxRectEndX(int iEndX,BOOL bRedraw = FALSE);
			// 函数 SetIconBtIconRect
			// 作用：设置SetIconBtIconRect。
			// 参数：rc；bRedraw：是或否。
			// 返回：没有返回值。
			void SetIconBtIconRect(Rect rc,BOOL bRedraw = FALSE);

			// 函数 SetBeHaveTxPushedFormat
			// 作用：设置SetBeHaveTxPushedFormat。
			// 参数：bHaveTxPushedFormat：是或否。
			// 返回：没有返回值。
			void SetBeHaveTxPushedFormat(BOOL bHaveTxPushedFormat);
			// 函数 GetBeHaveTxPushedFormat
			// 作用：读取GetBeHaveTxPushedFormat。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeHaveTxPushedFormat();
};


