// 【交接】 GeneralPcr\MyInsertBt.h
// 作用：MyInsertBt 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyInsertBt、DECLARE_MESSAGE_MAP、PreSubclassWindow、SetBmpBkPic、SetPngBkPic、SetNewBmpBkPic、SetBkColor。
#pragma once

#include "FontSet.h"
#include "ArrowInfo.h"

// CMyInsertBt

//按钮状态参数
#define CTRL_INSERTBT_NOFOCUS 1
#define CTRL_INSERTBT_FOCUS 2
#define CTRL_INSERTBT_SELECTED 3
#define CTRL_INSERTBT_DISABLE 4

#define RIFHTWIDTH 28	//右侧图标区域宽度

class CMyInsertBt : public CButton,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyInsertBt。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyInsertBt)

public:
	// 函数 CMyInsertBt
	// 作用：执行CMyInsertBt。
	// 参数：无。
	// 返回：没有返回值。
	CMyInsertBt();
	// 函数 ~CMyInsertBt
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyInsertBt();

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
	BOOL m_bTracking;

	BOOL m_bHasBkPic;
	BOOL m_bHasPathBkPic;
	BOOL m_bHasPngBkPic;
	int  m_sonPicNums;
	int  m_iconW;

	int m_leftIndent;
	int m_rightEnd;

	Color m_bkClrNormal;	//背景色，如果是圆角样式，指的是圆角填充背景色
	Color m_bkClrFocused;
	Color m_bkClrClicked;
	Color m_bkClrDisabled;

	Color m_clrArrowNormal;	//右侧箭头色
	Color m_clrArrowFocused;
	Color m_clrArrowClicked;
	Color m_clrArrowDisabled;

	Color m_clrSplitLineNormal;	//中间分隔线颜色
	Color m_clrSplitLineFocused;
	Color m_clrSplitLineClicked;
	Color m_clrSplitLineDisabled;

	COLORREF m_txClrNormal;
	COLORREF m_txClrFocused;
	COLORREF m_txClrClicked;
	COLORREF m_txClrDisabled;

	Color m_edgeClrNormal;
	Color m_edgeClrFocused;
	Color m_edgeClrClicked;
	Color m_edgeClrDisabled;

	BOOL	m_bDrawFrame;	//是否绘制边框

	wstring m_pngPicPath;

	BOOL m_bInMiddle;	//是否居中

	BOOL m_bCloseBt;	//标识是否是关闭按钮

	BOOL m_bTwinkle;	//是否包含闪烁功能
	BOOL m_bTwinkleShow;	//闪烁是否处于显示状态，闪烁包含显示、不显示两种状态，结合m_bHasPngBkPic使用
	int m_curState;	//当前图标类型
	int m_curState2;	//和m_curState对立的闪烁类型

	BOOL m_bTextDown;	//标识文字在图片下方

	int m_iSplitLineXPos;	//记录分割线横坐标位置

public:
	BOOL m_bRoundRectBk;	//标识是否使用圆角边框样式
	Color m_clrRoundRectBk;		//四个圆角外部颜色
	int m_iRoundAngle;	//圆角大小

	CArrowInfo m_arrowInfo;	//箭头信息

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
			// 参数：picPath；sonPicNums；iconWidth；leftIndent；bRedraw：是或否。
			// 返回：没有返回值。
			void SetPngBkPic(wstring picPath,int sonPicNums,int iconWidth = 0,int leftIndent = 0,BOOL bRedraw = FALSE);
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
			// 参数：bRoundRect：是或否；clrRoundRectBk：矩形区域；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRoundRectParam(BOOL bRoundRect,Color clrRoundRectBk,BOOL bRedraw = FALSE);
			// 函数 GetRoundRectParam
			// 作用：读取GetRoundRectParam。
			// 参数：bRoundRect：是或否；clrRoundRectBk：矩形区域。
			// 返回：没有返回值。
			void GetRoundRectParam(BOOL& bRoundRect,Color& clrRoundRectBk);
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
			// 函数 SetBeCloseBt
			// 作用：设置SetBeCloseBt。
			// 参数：bCloseBt：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeCloseBt(BOOL bCloseBt,BOOL bRedraw = FALSE);
			// 函数 GetBeCloseBt
			// 作用：读取GetBeCloseBt。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeCloseBt();
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

			// 函数 SetSplitLineXPos
			// 作用：设置SetSplitLineXPos。
			// 参数：iSplitLineXPos：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetSplitLineXPos(int iSplitLineXPos,BOOL bRedraw = FALSE);
			// 函数 GetSplitLineXPos
			// 作用：读取GetSplitLineXPos。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSplitLineXPos();
};


