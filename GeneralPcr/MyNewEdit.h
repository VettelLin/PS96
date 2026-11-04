// 【交接】 GeneralPcr\MyNewEdit.h
// 作用：MyNewEdit 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyNewEdit、DoDataExchange、DECLARE_MESSAGE_MAP、OnPaint、OnEraseBkgnd、OnSize、OnRButtonDown。
#pragma once

#include "Resource.h"
#include "CaretInfo.h"
#include "LinkList.h"
#include "FontSet.h"
#include "MaxMinInfo.h"
#include "SelfDefType.h"

#define WM_EDITENTERPUSHED	WM_USER + 6025	//编辑框Enter按键被按下

typedef enum SelectMoveType{
	ESMT_NONE,ESMT_OUTLEFT,ESMT_OUTRIGHT,ESMT_NORMAL
}ESELECTMOVETYPE;

//正常模式、只读模式
typedef enum WorkState{
	EWS_NORMAL,EWS_READONLY
}EWORKSTATE;

typedef enum RegionType{
	ERT_FRAME,ERT_LEFTINDENT,ERT_EDIT,ERT_RIGHTINDENT,ERT_TOPINDENT,ERT_BOTTOMINDENT,ERT_EMPTY,ERT_OUTSIDE
}EREGIONTYPE;

//边框样式，矩形边框、圆角边框
typedef enum FrameStyle{
	EFS_RECTANGLE,EFS_ROUNDRECT
}EFRAMESTYLE;

typedef enum TextMode{
	ETM_NORMAL,ETM_PASSWORDDOT
}ETEXTMODE;

#define WM_TELLPARENTTEXTCHANGED	WM_USER + 6029	//手动编辑字符导致编辑框文本改变，通知父窗口
#define WM_TELLPARENTSETNEWTEXT	WM_USER + 6030	//SetText导致编辑框文本改变，通知父窗口

class CMyNewEdit : public CEdit,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyNewEdit。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CMyNewEdit)

public:
	// 函数 CMyNewEdit
	// 作用：执行CMyNewEdit。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CMyNewEdit(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CMyNewEdit
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CMyNewEdit();

	enum { IDD = IDD_MYNEWEDIT};

protected:
	// 函数 DoDataExchange
	// 作用：把对话框控件和成员变量绑在一起。
	// 参数：pDX：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

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
	virtual afx_msg void OnPaint();
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 OnRButtonDown
	// 作用：按下鼠标右键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
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
	// 函数 OnMouseMove
	// 作用：鼠标在窗口上移动。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 函数 OnMouseWheel
	// 作用：转动鼠标滚轮。
	// 参数：nFlags：整数；zDelta；pt。
	// 返回：返回是或否。
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnSetFocus
	// 作用：响应 Windows 或自定义消息 OnSetFocus。
	// 参数：pOldWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	// 函数 OnKillFocus
	// 作用：响应 Windows 或自定义消息 OnKillFocus。
	// 参数：pNewWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	// 函数 OnChar
	// 作用：响应 Windows 或自定义消息 OnChar。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 OnKeyDown
	// 作用：响应 Windows 或自定义消息 OnKeyDown。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 OnKeyUp
	// 作用：响应 Windows 或自定义消息 OnKeyUp。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL PreTranslateMessage(MSG* pMsg);

			// 函数 SetCharFullShow
			// 作用：设置SetCharFullShow。
			// 参数：iIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCharFullShow(int iIndex);
			// 函数 CalcCaretPos
			// 作用：计算CalcCaretPos。
			// 参数：iIndex：整数；iCaretXPos：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcCaretPos(int iIndex,int& iCaretXPos);

			// 函数 ClearSelectInfo
			// 作用：更新或清除ClearSelectInfo。
			// 参数：无。
			// 返回：没有返回值。
			void ClearSelectInfo();

			// 函数 SetBeEditable
			// 作用：设置SetBeEditable。
			// 参数：bEditable：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeEditable(BOOL bEditable,BOOL bRedraw = FALSE);
			// 函数 GetBeEditable
			// 作用：读取GetBeEditable。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeEditable();

			// 函数 SetAllSelected
			// 作用：设置SetAllSelected。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetAllSelected();
			// 函数 DeleteAll
			// 作用：更新或清除DeleteAll。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteAll(BOOL bRedraw = TRUE);

			// 函数 SetFrameColor
			// 作用：设置SetFrameColor。
			// 参数：clrNormal：颜色；clrHover：颜色；clrSelected：颜色；clrDisabled：颜色；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetFrameColor(Color clrNormal,Color clrHover,Color clrSelected,Color clrDisabled,BOOL bRedraw = FALSE);
			// 函数 SetMainWndBkColor
			// 作用：设置SetMainWndBkColor。
			// 参数：clrNormal：颜色；clrHover：颜色；clrSelected：颜色；clrDisabled：颜色；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetMainWndBkColor(Color clrNormal,Color clrHover,Color clrSelected,Color clrDisabled,BOOL bRedraw = FALSE);
			// 函数 SetTextColor
			// 作用：设置SetTextColor。
			// 参数：clrNormal：颜色；clrHover：颜色；clrSelected：颜色；clrDisabled：颜色；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetTextColor(COLORREF clrNormal,COLORREF clrHover,COLORREF clrSelected,COLORREF clrDisabled,BOOL bRedraw = FALSE);
			// 函数 SetSelectedTextColor
			// 作用：设置SetSelectedTextColor。
			// 参数：clrNormal：颜色；clrHover：颜色；clrSelected：颜色；clrDisabled：颜色；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSelectedTextColor(COLORREF clrNormal,COLORREF clrHover,COLORREF clrSelected,COLORREF clrDisabled,BOOL bRedraw = FALSE);
			// 函数 SetSelectedBkColor
			// 作用：设置SetSelectedBkColor。
			// 参数：clrNormal：颜色；clrHover：颜色；clrSelected：颜色；clrDisabled：颜色；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSelectedBkColor(COLORREF clrNormal,COLORREF clrHover,COLORREF clrSelected,COLORREF clrDisabled,BOOL bRedraw = FALSE);

	// 函数 SetText
	// 作用：设置SetText。
	// 参数：strText：字符串；bRedraw：是或否；bForbidTellParent：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SetText(CString strText,BOOL bRedraw = TRUE,BOOL bForbidTellParent = FALSE);
			// 函数 SetText
			// 作用：设置SetText。
			// 参数：dData：小数；bRedraw：是或否；bForbidTellParent：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetText(double dData,BOOL bRedraw = TRUE,BOOL bForbidTellParent = FALSE);
			// 函数 GetText
			// 作用：读取GetText。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetText();
			
			// 函数 ClearMaxMinLimit
			// 作用：更新或清除ClearMaxMinLimit。
			// 参数：无。
			// 返回：没有返回值。
			void ClearMaxMinLimit();

			// 函数 SetMaxMinInfo
			// 作用：设置SetMaxMinInfo。
			// 参数：maxMinInfo；bRedraw：是或否。
			// 返回：没有返回值。
			void SetMaxMinInfo(CMaxMinInfo maxMinInfo,BOOL bRedraw = FALSE);
			// 函数 GetMaxMinInfo
			// 作用：读取GetMaxMinInfo。
			// 参数：无。
			// 返回：返回 CMaxMinInfo。
			CMaxMinInfo GetMaxMinInfo();

			// 函数 SetBeEnterTellParent
			// 作用：设置SetBeEnterTellParent。
			// 参数：bEnterTellParent：是或否。
			// 返回：没有返回值。
			void SetBeEnterTellParent(BOOL bEnterTellParent);
			// 函数 GetBeEnterTellParent
			// 作用：读取GetBeEnterTellParent。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeEnterTellParent();

			// 函数 SetTellParentTxChangedParam
			// 作用：设置SetTellParentTxChangedParam。
			// 参数：bTellParentTxChanged：是或否；iTextTypeTag：整数。
			// 返回：没有返回值。
			void SetTellParentTxChangedParam(BOOL bTellParentTxChanged,int iTextTypeTag);
			// 函数 GetTellParentTxChangedParam
			// 作用：读取GetTellParentTxChangedParam。
			// 参数：bTellParentTxChanged：是或否；iTextTypeTag：整数。
			// 返回：没有返回值。
			void GetTellParentTxChangedParam(BOOL& bTellParentTxChanged,int& iTextTypeTag);

			// 函数 SetTellParentSetNewText
			// 作用：设置SetTellParentSetNewText。
			// 参数：bTellParentSetNewText：是或否；iTextTypeTag：整数。
			// 返回：没有返回值。
			void SetTellParentSetNewText(BOOL bTellParentSetNewText,int iTextTypeTag);
			// 函数 GetTellParentSetNewText
			// 作用：读取GetTellParentSetNewText。
			// 参数：bTellParentSetNewText：是或否；iTextTypeTag：整数。
			// 返回：没有返回值。
			void GetTellParentSetNewText(BOOL& bTellParentSetNewText,int& iTextTypeTag);

			// 函数 SetWorkState
			// 作用：设置SetWorkState。
			// 参数：eWorkState。
			// 返回：没有返回值。
			void SetWorkState(EWORKSTATE eWorkState);
			// 函数 GetWorkState
			// 作用：读取GetWorkState。
			// 参数：无。
			// 返回：返回 EWORKSTATE。
			EWORKSTATE GetWorkState();
			
			// 函数 SetFrameStyle
			// 作用：设置SetFrameStyle。
			// 参数：eFrameStyle；bRedraw：是或否。
			// 返回：没有返回值。
			void SetFrameStyle(EFRAMESTYLE eFrameStyle,BOOL bRedraw = FALSE);
			// 函数 GetFrameStyle
			// 作用：读取GetFrameStyle。
			// 参数：无。
			// 返回：返回 EFRAMESTYLE。
			EFRAMESTYLE GetFrameStyle();
			 
			// 函数 SetFrameRoundAngle
			// 作用：设置SetFrameRoundAngle。
			// 参数：iFrameRoundAngle：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetFrameRoundAngle(int iFrameRoundAngle,BOOL bRedraw = FALSE);
			// 函数 GetFrameRoundAngle
			// 作用：读取GetFrameRoundAngle。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetFrameRoundAngle();

			// 函数 SetLeftImageParam
			// 作用：设置SetLeftImageParam。
			// 参数：bShowImg：是或否；iSonPicNum：整数；strFilePath：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetLeftImageParam(BOOL bShowImg,int iSonPicNum,CString strFilePath,BOOL bRedraw = FALSE);
			// 函数 GetBeShowLeftImage
			// 作用：读取GetBeShowLeftImage。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShowLeftImage();
			// 函数 GetLeftImageSonPicNum
			// 作用：读取GetLeftImageSonPicNum。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetLeftImageSonPicNum();
			// 函数 GetLeftImagePath
			// 作用：读取GetLeftImagePath。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetLeftImagePath();

			// 函数 SetPasswordParam
			// 作用：设置SetPasswordParam。
			// 参数：eData；iDotRadius：整数；iDotInterval：整数。
			// 返回：没有返回值。
			void SetPasswordParam(ETEXTMODE eData,int iDotRadius,int iDotInterval);

			// 函数 TextParamChanged
			// 作用：执行TextParamChanged。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int TextParamChanged(BOOL bRedraw = FALSE);	//字体属性（字体名称、大小）改变了

	// 函数 LBtDownSpecialProc
	// 作用：执行LBtDownSpecialProc。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int LBtDownSpecialProc();
			
public:
	// 函数 CalcCharStartEndShowIndex
	// 作用：计算CalcCharStartEndShowIndex。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalcCharStartEndShowIndex();	//正序计算
	// 函数 CalcCharStartEndShowIndex
	// 作用：计算CalcCharStartEndShowIndex。
	// 参数：iStartIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalcCharStartEndShowIndex(int iStartIndex);	//正序计算
	// 函数 CalcCharEndStartShowIndex
	// 作用：计算CalcCharEndStartShowIndex。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalcCharEndStartShowIndex();	//倒序计算
	// 函数 CalcCharEndStartShowIndex
	// 作用：计算CalcCharEndStartShowIndex。
	// 参数：iEndIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalcCharEndStartShowIndex(int iEndIndex);	//倒序计算
	// 函数 HoriScrollPixel
	// 作用：执行HoriScrollPixel。
	// 参数：iPxShift：整数；bRedraw：是或否；bSetCaretPos：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int HoriScrollPixel(int iPxShift,BOOL bRedraw = FALSE,BOOL bSetCaretPos = FALSE);
	// 函数 HoriScrollChar
	// 作用：执行HoriScrollChar。
	// 参数：iCharShift：整数；bRedraw：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int HoriScrollChar(int iCharShift,BOOL bRedraw = FALSE);
	// 函数 TransformXPosToCharInex
	// 作用：执行TransformXPosToCharInex。
	// 参数：pxX。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int TransformXPosToCharInex(int pxX);	//把横坐标转换为字符串下标位置，改变m_caretInfo
	// 函数 TransformXPosToCharInex
	// 作用：执行TransformXPosToCharInex。
	// 参数：pxX；iIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int TransformXPosToCharInex(int pxX,int& iIndex);	//把横坐标转换为字符串下标位置并单独输出，不改变m_caretInfo
	// 函数 GetLeftUnShowCharPixelLength
	// 作用：读取GetLeftUnShowCharPixelLength。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetLeftUnShowCharPixelLength();	//计算左侧未显示字符的总宽度
	// 函数 GetRightUnShowCharPixelLength
	// 作用：读取GetRightUnShowCharPixelLength。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetRightUnShowCharPixelLength();	//计算右侧未显示字符的总宽度
	
	// 函数 GetWidth
	// 作用：读取GetWidth。
	// 参数：iStart：整数；iEnd：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetWidth(int iStart,int iEnd);

	// 函数 ArrowKeyProcess
	// 作用：执行ArrowKeyProcess。
	// 参数：nChar：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ArrowKeyProcess(UINT nChar);
	// 函数 DeleteKeyProcess
	// 作用：更新或清除DeleteKeyProcess。
	// 参数：nChar：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteKeyProcess(UINT nChar);
	// 函数 MouseLeftBtPushedMoveProcess
	// 作用：执行MouseLeftBtPushedMoveProcess。
	// 参数：pt。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int MouseLeftBtPushedMoveProcess(CPoint pt);

	// 函数 DeleteSelectedChar
	// 作用：更新或清除DeleteSelectedChar。
	// 参数：bRedraw：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteSelectedChar(BOOL bRedraw = TRUE);
	// 函数 DeleteChar
	// 作用：更新或清除DeleteChar。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteChar();	//以下标作为参考标准
	// 函数 DeleteCharAfter
	// 作用：更新或清除DeleteCharAfter。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteCharAfter(); 	//以下标作为参考标准
	// 函数 DeleteChar
	// 作用：更新或清除DeleteChar。
	// 参数：iIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteChar(int iIndex);
	// 函数 DeleteCharAfter
	// 作用：更新或清除DeleteCharAfter。
	// 参数：iIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteCharAfter(int iIndex); 

	// 函数 CharFilter
	// 作用：执行CharFilter。
	// 参数：nChar：整数；nFlags：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CharFilter(UINT nChar,UINT nFlags);
	// 函数 MsgFilter
	// 作用：执行MsgFilter。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int MsgFilter(MSG* pMsg);

	// 函数 CopySelectedTextToClipBoard
	// 作用：复制CopySelectedTextToClipBoard。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CopySelectedTextToClipBoard();
	// 函数 CtrlAndVProcess
	// 作用：执行CtrlAndVProcess。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CtrlAndVProcess();
	
	// 函数 CheckLnkCharWidth
	// 作用：判断CheckLnkCharWidth是否成立。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CheckLnkCharWidth();

	// 函数 GetRegionType
	// 作用：读取GetRegionType。
	// 参数：pt。
	// 返回：返回 EREGIONTYPE。
	EREGIONTYPE GetRegionType(CPoint pt);

	// 函数 TellParentTxChangedProcess
	// 作用：执行TellParentTxChangedProcess。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int TellParentTxChangedProcess();	//文字变更后，处理“是否通知父窗口”
	// 函数 TellParentSetNewTextProcess
	// 作用：执行TellParentSetNewTextProcess。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int TellParentSetNewTextProcess();	//SetText导致文字变更后，处理“是否通知父窗口”
	
	// 函数 SetBeFuncEdit
	// 作用：设置SetBeFuncEdit。
	// 参数：bFuncEdit：是或否。
	// 返回：没有返回值。
	void SetBeFuncEdit(BOOL bFuncEdit);
	// 函数 GetBeFuncEdit
	// 作用：读取GetBeFuncEdit。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeFuncEdit();

	// 函数 SetDefaultIndent
	// 作用：设置SetDefaultIndent。
	// 参数：无。
	// 返回：没有返回值。
	void SetDefaultIndent();

	// 函数 SetCtrlTag
	// 作用：设置SetCtrlTag。
	// 参数：iCtrlTag：整数。
	// 返回：没有返回值。
	void SetCtrlTag(int iCtrlTag);
	// 函数 GetCtrlTag
	// 作用：读取GetCtrlTag。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetCtrlTag();

public:
	CCaretInfo m_caretInfo;
	CString m_strText;

	CLinkList<int> m_lnkCharW;	//记录每个字符宽度

	int m_iLeftIndent;	//文字显示区域左侧空白区域宽度
	int m_iRightIndent;	//文字显示区域右侧空白区域宽度
	int m_iTopIndent;	//文字显示区域顶部空白区域高度
	int m_iBottomIndent;	//文字显示区域底部空白区域高度
	int m_iCharShowLI;	//绘制文字时左侧缩进
	int m_iCharShowRI;	//绘制文字时右侧缩进
	int m_iCharShowW;	//文字显示区域宽度

	int m_pxFrameW;	//边框宽度
	
	int m_iCharStartShowIndex;	//显示的第一个字符在总体字符串中的下标
	int m_iCharEndShowIndex;	//显示的最后一个字符在总体字符串中的下标

public:
	int m_iCdcW;	//m_iCharStartShowIndex与m_iCharEndShowIndex之间的字符内存宽度
	int m_iSelDrawCDcW;	//选中区域需绘制字符的宽度

	int m_iSelStart;	//选中区域起始下标
	int m_iSelEnd;	//选中区域终止下标
	int m_iSelCharNum;	//选中字符数

	BOOL m_bLBtPushedMove;	//标识是否是左键按下移动
	BOOL m_bSelMoveCaretHid;	//标识选中滑动时插入符是否已隐藏
	ESELECTMOVETYPE m_eCurSMT;	//标识选中滑动时鼠标位置类型
	ESELECTMOVETYPE m_ePreSMT;	//标识选中滑动时上一次的鼠标位置类型
	CPoint m_ptPreSelMove;	//记录选中滑动时鼠标的上一个位置

	CRect m_rcCtrl;	//控件显示区域
	CRect m_rcText;	//文本显示区域
	CRect m_rcLeftIndent;	//左侧缩进区域
	CRect m_rcRightIndent;	//右侧缩进区域
	CRect m_rcTopIndent;	//顶部缩进区域
	CRect m_rcBottomIndent;	//底部缩进区域

	BOOL m_bEidtable;	//标识是否可编辑

	BOOL m_bMouseFstInCtrl;	//标识鼠标是否初次在控件中
	BOOL m_bEnterTellParent;	//Enter按键按下时是否通知父窗口

	ECTRLSTATE m_eCtrlState;
	ECTRLSTATE m_ePreCtrlState;

	Color m_clrFrameNormal;		//边框颜色
	Color m_clrFrameHover;
	Color m_clrFrameSelected;
	Color m_clrFrameDisabled;

	Color m_clrMainWndNormal;	//主窗口背景色
	Color m_clrMainWndHover;
	Color m_clrMainWndSelected;
	Color m_clrMainWndDisabled;

	COLORREF m_clrTxNormal;		//正常文字颜色
	COLORREF m_clrTxHover;
	COLORREF m_clrTxSelected;
	COLORREF m_clrTxDisabled;

	COLORREF m_clrTxSelNormal;	//选中文字颜色
	COLORREF m_clrTxSelHover;
	COLORREF m_clrTxSelSelected;
	COLORREF m_clrTxSelDisabled;

	COLORREF m_clrBkSelNormal;	//选中区域背景色
	COLORREF m_clrBkSelHover;
	COLORREF m_clrBkSelSelected;
	COLORREF m_clrBkSelDisabled;

	CMaxMinInfo m_maxMinInfo;

	EWORKSTATE m_eWorkState;
	EREGIONTYPE m_eRgnType;

protected:
	EFRAMESTYLE m_eFrameStyle;	//边框样式
	int m_iFrameRoundAngle;	//圆角边框的圆角大小

	BOOL m_bFuncEdit;	//是否是功能控件，用于列表框或者特别控件的内容编辑,失去焦点时自动隐藏
	int m_iCtrlTag;	//用于单一标识功能控件，失去焦点时发送给父窗口，让父窗口能够识别到是哪一个控件

	BOOL m_bShowLeftImg;	//左侧缩进区域是否显示图标
	int m_iLeftImgSonPicNum;	//左侧缩进区域显示图形的子图个数
	CString m_strLeftImgPath;	//左侧缩进图形路径

	int m_iTxH;	//记录字体文字的高度

private:
	BOOL m_bTellParentTxChanged;	//通知父窗口文本已变更，由鼠标按键操作触发
	int m_iTextTypeTag;	//文本功能标识（标识当前编辑框用于编辑哪种类型的信息）

	BOOL m_bTellParentSetNewText;	//通知父窗口文本已变更，由SetText触发
	
	//密码圆点字符格式参数
	int m_iPWDotRadius;	//密码字符圆点半径
	int m_iPWDotDiam;	//密码字符圆点直径
	int m_iPWDotInterval;	//密码字符圆点间隔
	int m_iPWCharW;
	ETEXTMODE m_eTxMode;
};
