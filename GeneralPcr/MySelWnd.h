// 【交接】 GeneralPcr\MySelWnd.h
// 作用：MySelWnd 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMySelWnd、DECLARE_MESSAGE_MAP、OnPaint、OnEraseBkgnd、OnSize、OnRButtonDown、OnLButtonDown。
#pragma once

#include "FontSet.h"
#include "LinkList.h"
#include "ItemForSelInfo.h"
#include "MyScrollInfo.h"
#include "MySelWndPosInfo.h"

#define WM_ROWSELECTCHANGE	WM_USER + 6023	//列表框选中行改变，通知父窗口

class CMySelWnd : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMySelWnd。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMySelWnd)

public:
	// 函数 CMySelWnd
	// 作用：执行CMySelWnd。
	// 参数：无。
	// 返回：没有返回值。
	CMySelWnd();
	// 函数 ~CMySelWnd
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMySelWnd();

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
	// 函数 OnKillFocus
	// 作用：响应 Windows 或自定义消息 OnKillFocus。
	// 参数：pNewWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	// 函数 OnShowWindow
	// 作用：响应 Windows 或自定义消息 OnShowWindow。
	// 参数：bShow：是或否；nStatus：整数。
	// 返回：没有返回值。
	afx_msg void OnShowWindow(BOOL bShow,UINT nStatus);
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

			// 函数 DrawBody
			// 作用：绘制DrawBody。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawBody(CDC* pDC);
			// 函数 DrawVertScroll
			// 作用：绘制DrawVertScroll。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawVertScroll(CDC* pDC);

			// 函数 CalcScrollPos
			// 作用：计算CalcScrollPos。
			// 参数：无。
			// 返回：没有返回值。
			void CalcScrollPos();
			// 函数 CalcRowToShow
			// 作用：计算CalcRowToShow。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcRowToShow();
			// 函数 CalcRowToShow
			// 作用：计算CalcRowToShow。
			// 参数：newStartRow。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcRowToShow(int newStartRow);
			// 函数 CalcTotalRowHeight
			// 作用：计算CalcTotalRowHeight。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcTotalRowHeight();
			// 函数 GetHeight
			// 作用：读取GetHeight。
			// 参数：rowStart；rowEnd。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetHeight(int rowStart,int rowEnd);
			// 函数 GetRowStartDrawInMemoryVertPixel
			// 作用：读取GetRowStartDrawInMemoryVertPixel。
			// 参数：rowId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowStartDrawInMemoryVertPixel(int rowId);
			// 函数 ProcessVertSrcoll
			// 作用：执行ProcessVertSrcoll。
			// 参数：nFlags：整数；point。
			// 返回：没有返回值。
			void ProcessVertSrcoll(UINT nFlags, CPoint point);
			// 函数 ScrollRow
			// 作用：执行ScrollRow。
			// 参数：pxVertShift。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ScrollRow(int pxVertShift);
			// 函数 ScrollRowToFixPos
			// 作用：执行ScrollRowToFixPos。
			// 参数：pxFixPos。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ScrollRowToFixPos(int pxFixPos);
			// 函数 CalcPtPos
			// 作用：计算CalcPtPos。
			// 参数：pt。
			// 返回：返回 CMySelWndDotPosInfo。
			CMySelWndDotPosInfo CalcPtPos(CPoint pt);

			// 函数 SetRowSingleSelected
			// 作用：设置SetRowSingleSelected。
			// 参数：rowId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRowSingleSelected(int rowId,BOOL bRedraw = FALSE);

			// 函数 GetRowString
			// 作用：读取GetRowString。
			// 参数：rowId；strText：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowString(int rowId,CString& strText);
			// 函数 SetItemText
			// 作用：设置SetItemText。
			// 参数：iIndex：整数；strText：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetItemText(int iIndex,CString strText);
			// 函数 InsertRow
			// 作用：创建或加入InsertRow。
			// 参数：rowId；strText：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertRow(int rowId,CString strText,BOOL bRedraw = TRUE); //在rowId之前插入
			// 函数 InsertRow
			// 作用：创建或加入InsertRow。
			// 参数：strText：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertRow(CString strText,BOOL bRedraw = TRUE);
			// 函数 DeleteRow
			// 作用：更新或清除DeleteRow。
			// 参数：rowId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteRow(int rowId,BOOL bRedraw = TRUE);
			// 函数 DeleteAll
			// 作用：更新或清除DeleteAll。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteAll(BOOL bRedraw = TRUE);

			// 函数 SetSelectedRow
			// 作用：设置SetSelectedRow。
			// 参数：strSelectedRow：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSelectedRow(CString strSelectedRow,BOOL bRedraw = FALSE);	//单选
			// 函数 SetRowSelected
			// 作用：设置SetRowSelected。
			// 参数：strSelectedRow：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRowSelected(CString strSelectedRow,BOOL bRedraw = FALSE);	//不影响其它行选中状态

			// 函数 GetFirstSelectedRow
			// 作用：读取GetFirstSelectedRow。
			// 参数：strSelectedRow：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetFirstSelectedRow(CString strSelectedRow);

			// 函数 SetBeAllowSameItem
			// 作用：设置SetBeAllowSameItem。
			// 参数：bAllowSamItem：是或否。
			// 返回：没有返回值。
			void SetBeAllowSameItem(BOOL bAllowSamItem);
			// 函数 GetBeAllowSameItem
			// 作用：读取GetBeAllowSameItem。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeAllowSameItem();

			// 函数 GetItemCount
			// 作用：读取GetItemCount。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetItemCount();	//获取供选择的所有项的个数

private:
			// 函数 InitVertScroll
			// 作用：初始化InitVertScroll。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InitVertScroll();

public:
	int m_pxFrameW;
	
	CLinkList<CItemForSelInfo> m_lnkItemForSelInfo;
	CLinkList<CMySelWndDotPosInfo> m_lnkHistoryDotPosInfo;

	CMyScrollInfo m_vertScroll;

	CMySelWndDotPosInfo m_curDotPosInfo;
	CMySelWndDotPosInfo m_preDotPosInfo;

	CRect m_rcWnd;
	CRect m_rcBody;

	int m_rowNum;
	int m_cdcH;	//记录显示行的总高度（包括 顶部、底部缩进像素） CDC Height
	int m_totalRowH;	//所d有行的高度之和
	int m_rowIdStartShow;
	int m_rowIdEndShow;
	int m_iRowTopIndent;	//起始显示行顶部缩进
	int m_iRowBottomIndent;	//终止显示列底部缩进

	BOOL m_bTellParentRowSelChange;

	CWnd* m_pParent;

	int m_iLeftIndent;	//输出文字左侧缩进
	int m_iRightIndent;	//输出文字右侧缩进
	int m_iDefRowH;	//默认行高

private:
	BOOL m_bMouseFstInCtrl;	//标识鼠标是否初次在控件中
	BOOL m_bAllowSameItem;	//是否允许选项内容重复
};


