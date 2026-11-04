// 【交接】 GeneralPcr\MyCheckButton.h
// 作用：MyCheckButton 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyCheckButton、DECLARE_MESSAGE_MAP、PreSubclassWindow、SetBkPicture、SetPngBkPic、SetBtChecked、GetCheckState。
#pragma once

#include "FontSet.h"

class CMyCheckButton : public CButton,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyCheckButton。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyCheckButton)

public:
	// 函数 CMyCheckButton
	// 作用：执行CMyCheckButton。
	// 参数：无。
	// 返回：没有返回值。
	CMyCheckButton();
	// 函数 ~CMyCheckButton
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyCheckButton();

protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()
	// 函数 PreSubclassWindow
	// 作用：执行PreSubclassWindow。
	// 参数：无。
	// 返回：没有返回值。
	virtual void PreSubclassWindow();

public:
			// 函数 SetBkPicture
			// 作用：设置SetBkPicture。
			// 参数：idChecked；idUnChecked；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBkPicture(UINT idChecked,UINT idUnChecked,BOOL bRedraw = FALSE);
			// 函数 SetBkPicture
			// 作用：设置SetBkPicture。
			// 参数：idPicture；sonPicNums；iconW。
			// 返回：没有返回值。
			void SetBkPicture(UINT idPicture,int sonPicNums = 2,int iconW = 0);
			// 函数 SetPngBkPic
			// 作用：设置SetPngBkPic。
			// 参数：picPath；sonPicNums；iconW；pngBkClr；bInvalidate：是或否。
			// 返回：没有返回值。
			void SetPngBkPic(wstring picPath,int sonPicNums = 2,int iconW = 0,COLORREF pngBkClr = RGB(255,255,255),BOOL bInvalidate = FALSE);
			// 函数 SetBtChecked
			// 作用：设置SetBtChecked。
			// 参数：btState；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBtChecked(BOOL btState,BOOL bRedraw = FALSE);
			// 函数 GetCheckState
			// 作用：读取GetCheckState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetCheckState();
			// 函数 SetShieldClickMsgState
			// 作用：设置SetShieldClickMsgState。
			// 参数：bShieldClickMsg：是或否。
			// 返回：没有返回值。
			void SetShieldClickMsgState(BOOL bShieldClickMsg);
			// 函数 GetShieldClickMsgState
			// 作用：读取GetShieldClickMsgState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShieldClickMsgState();
			// 函数 SetBkColor
			// 作用：设置SetBkColor。
			// 参数：bkClrUnchked；bkClrChked；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBkColor(COLORREF bkClrUnchked,COLORREF bkClrChked,BOOL bRedraw = FALSE);
			// 函数 GetBkColor
			// 作用：读取GetBkColor。
			// 参数：bkClrUnchked；bkClrChked。
			// 返回：没有返回值。
			void GetBkColor(COLORREF& bkClrUnchked,COLORREF& bkClrChked);
			// 函数 SetRoundStyle
			// 作用：设置SetRoundStyle。
			// 参数：bRoundSytle：是或否；roundStyleBkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRoundStyle(BOOL bRoundSytle,COLORREF roundStyleBkClr,BOOL bRedraw = FALSE);
			// 函数 GetRoundStyle
			// 作用：读取GetRoundStyle。
			// 参数：pRoundStyleBkClr：指针，指向调用方传入的对象。
			// 返回：返回是或否。
			BOOL GetRoundStyle(COLORREF* pRoundStyleBkClr = NULL);

			// 函数 SetTickStyle
			// 作用：设置SetTickStyle。
			// 参数：bTickSytle：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetTickStyle(BOOL bTickSytle,BOOL bRedraw = FALSE);
			// 函数 GetTickStyle
			// 作用：读取GetTickStyle。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetTickStyle();

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

			// 函数 SetFrameColor
			// 作用：设置SetFrameColor。
			// 参数：clrFrame：颜色；bRedraw：是或否。
			// 返回：没有返回值。
			void SetFrameColor(COLORREF clrFrame,BOOL bRedraw = FALSE);
			// 函数 GetFrameColor
			// 作用：读取GetFrameColor。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetFrameColor();

			// 函数 SetSelectStateSerail
			// 作用：设置SetSelectStateSerail。
			// 参数：selStateSerial；bRedraw：是或否。
			// 返回：没有返回值。
			void SetSelectStateSerail(int selStateSerial,BOOL bRedraw = FALSE);
			// 函数 GetSelectStateSerail
			// 作用：读取GetSelectStateSerail。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSelectStateSerail();

			// 函数 SetTextColor
			// 作用：设置SetTextColor。
			// 参数：txClrUnchecked；txClrChecked；bRedraw：是或否。
			// 返回：没有返回值。
			void SetTextColor(COLORREF txClrUnchecked,COLORREF txClrChecked = RGB(0,0,0),BOOL bRedraw = FALSE);
			// 函数 GetTextColor
			// 作用：读取GetTextColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetTextColor();

			// 函数 SetBeNeedRedrawBk
			// 作用：设置SetBeNeedRedrawBk。
			// 参数：bNeedRedrawBk：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeNeedRedrawBk(BOOL bNeedRedrawBk,BOOL bRedraw = FALSE);
			// 函数 GetBeNeedRedrawBk
			// 作用：读取GetBeNeedRedrawBk。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeNeedRedrawBk();

			// 函数 SetPngBkColor
			// 作用：设置SetPngBkColor。
			// 参数：pngBkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetPngBkColor(COLORREF pngBkClr,BOOL bRedraw = FALSE);
			// 函数 GetPngBkColor
			// 作用：读取GetPngBkColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetPngBkColor();  

			// 函数 SetBeParentProcessMouseClick
			// 作用：设置SetBeParentProcessMouseClick。
			// 参数：bParentProcMouseClick：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeParentProcessMouseClick(BOOL bParentProcMouseClick,BOOL bRedraw = FALSE);
			// 函数 GetBeParentProcessMouseClick
			// 作用：读取GetBeParentProcessMouseClick。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetBeParentProcessMouseClick();
			
			// 函数 SetIconTextInterval
			// 作用：设置SetIconTextInterval。
			// 参数：iLeftIndent：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetIconTextInterval(int iLeftIndent,BOOL bRedraw = FALSE);	//设置左侧缩进（图标和文本之间的间隔）
			// 函数 GetIconTextInterval
			// 作用：读取GetIconTextInterval。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetIconTextInterval();

	// 函数 DrawItem
	// 作用：绘制DrawItem。
	// 参数：lpDrawItemStruct。
	// 返回：没有返回值。
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
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
	// 函数 OnLButtonDblClk
	// 作用：双击鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 OnCtlColor
	// 作用：给子控件设置文字色和背景色。
	// 参数：pDC：指针，指向调用方传入的对象；pWnd：指针，指向调用方传入的对象；nCtlColor：整数。
	// 返回：返回 HBRUSH。
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	COLORREF m_bkClrUnchked;
	COLORREF m_bkClrChked;

	BOOL m_isBtChecked;

	UINT   m_idChecked;
	UINT   m_idUnChecked;
	BOOL   m_bHasBkPic;
	BOOL   m_bHasPngBkPic;

	wstring m_picPath;

	int m_sonPicNums;
	COLORREF m_txClrUnchecked;
	COLORREF m_txClrChecked;

	COLORREF m_pngBkClr;

	BOOL m_bShieldClickMsg;

	int  m_iconW;
	int m_iLeftIndent;
	int m_rightEnd;

	double m_cheBtHoriFontRatio;
	double m_cheBtVerFontRatio;

	BOOL m_bNeedRedrawBk;	//是否需要重新填充背景
	BOOL m_bParentProcMouseClick;	//是否由父窗口处理点击事件

	BOOL m_bRoundStyle;
	BOOL m_bTickStyle;

	COLORREF m_roundStyleBkClr;	//圆形外部背景色

	DWORD m_dwWordStyle;

	COLORREF m_clrFrame;

	int m_selStateSerail;	//选中状态在背景图中的序列号
};


