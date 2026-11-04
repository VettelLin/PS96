// 【交接】 GeneralPcr\MySamPlateDlg.h
// 作用：MySamPlateDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CMySamPalteDlg、DECLARE_MESSAGE_MAP、OnPaint、DrawTotalHeader、DrawRowHeader、DrawColHeader、DrawBody。
#pragma once

#include "FontSet.h"
#include "LinkList.h"
#include "TitleInfo.h"
#include "CellInfo.h"
#include "MyScrollInfo.h"
#include "SelfDefType.h"
#include "RowInfo.h"
#include "DotPosInfo.h"
#include "RowColEditInfo.h"
#include "TubeInfo.h"
#include "PlateInfo.h"
#include "MySelWnd.h"
#include "HoleColorInfo.h"
 
#include <GdiPlus.h>
#include <map>

using namespace std;

#define SAMPLATE_DELETEKEY_PRESSED WM_USER + 6034	//通知父窗口Delete按键被按下

class CMySamPalteDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMySamPalteDlg。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMySamPalteDlg)

public:
	// 函数 CMySamPalteDlg
	// 作用：执行CMySamPalteDlg。
	// 参数：无。
	// 返回：没有返回值。
	CMySamPalteDlg();
	// 函数 ~CMySamPalteDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMySamPalteDlg();
	
protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();

public:
			// 函数 DrawTotalHeader
			// 作用：绘制DrawTotalHeader。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawTotalHeader(CDC* pDC);
			// 函数 DrawRowHeader
			// 作用：绘制DrawRowHeader。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawRowHeader(CDC* pDC);
			// 函数 DrawColHeader
			// 作用：绘制DrawColHeader。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawColHeader(CDC* pDC);
			// 函数 DrawBody
			// 作用：绘制DrawBody。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawBody(CDC* pDC);
			// 函数 DrawHoriScroll
			// 作用：绘制DrawHoriScroll。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawHoriScroll(CDC* pDC);
			// 函数 DrawVertScroll
			// 作用：绘制DrawVertScroll。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawVertScroll(CDC* pDC);

	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnRButtonDown
	// 作用：按下鼠标右键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// 函数 OnLButtonDblClk
	// 作用：双击鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
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
	
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL PreTranslateMessage(MSG* pMsg);

	// 函数 OnMsgEditEnterPushed
	// 作用：响应 Windows 或自定义消息 OnMsgEditEnterPushed。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgEditEnterPushed(WPARAM wParam,LPARAM lParam);

			// 函数 ProcessHoriSrcoll
			// 作用：执行ProcessHoriSrcoll。
			// 参数：nFlags：整数；point。
			// 返回：没有返回值。
			void ProcessHoriSrcoll(UINT nFlags, CPoint point);
			// 函数 ProcessVertSrcoll
			// 作用：执行ProcessVertSrcoll。
			// 参数：nFlags：整数；point。
			// 返回：没有返回值。
			void ProcessVertSrcoll(UINT nFlags, CPoint point);

			// 函数 GetColStartDrawInMemoryHoriPixel
			// 作用：读取GetColStartDrawInMemoryHoriPixel。
			// 参数：colId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColStartDrawInMemoryHoriPixel(int colId);
			// 函数 GetRowStartDrawInMemoryVertPixel
			// 作用：读取GetRowStartDrawInMemoryVertPixel。
			// 参数：rowId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowStartDrawInMemoryVertPixel(int rowId);

			// 函数 GetWidth
			// 作用：读取GetWidth。
			// 参数：colStart；colEnd。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetWidth(int colStart,int colEnd);
			// 函数 GetHeight
			// 作用：读取GetHeight。
			// 参数：rowStart；rowEnd。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetHeight(int rowStart,int rowEnd);

			// 函数 CalcPtRowCol
			// 作用：计算CalcPtRowCol。
			// 参数：pt。
			// 返回：返回 CDotPosInfo。
			CDotPosInfo CalcPtRowCol(CPoint pt);
			
			// 函数 InsertColumn
			// 作用：创建或加入InsertColumn。
			// 参数：colId；strColTitle：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertColumn(int colId,CString strColTitle,BOOL bRedraw = TRUE);
			// 函数 InsertRow
			// 作用：创建或加入InsertRow。
			// 参数：rowId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertRow(int rowId,BOOL bRedraw = TRUE);
			
			// 函数 DeleteColumn
			// 作用：更新或清除DeleteColumn。
			// 参数：colId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteColumn(int colId,BOOL bRedraw = TRUE);
			// 函数 DeleteRow
			// 作用：更新或清除DeleteRow。
			// 参数：rowId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteRow(int rowId,BOOL bRedraw = TRUE);

			// 函数 DeleteMultiRow
			// 作用：更新或清除DeleteMultiRow。
			// 参数：vecSelectedRow；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteMultiRow(vector<int> vecSelectedRow,BOOL bRedraw = TRUE);	//存储行信息的是链表结构，删除多项时，倒着删除,vecSelectedRow记录的下标需要是从小到大的顺序

			// 函数 DeleteData
			// 作用：更新或清除DeleteData。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void DeleteData(BOOL bRedraw = FALSE);	//清除列表信息，不包括标题栏
			// 函数 Clear
			// 作用：更新或清除Clear。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void Clear(BOOL bRedraw = FALSE);	//删除所有的行，不包括标题栏

			// 函数 GetSelectedRowId
			// 作用：读取GetSelectedRowId。
			// 参数：无。
			// 返回：返回 vector<int>。
			vector<int> GetSelectedRowId();	//获取选中行的下标，从小到大的顺序

			// 函数 SetColumnTitleInfo
			// 作用：设置SetColumnTitleInfo。
			// 参数：colId；titleInfo；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnTitleInfo(int colId,CTitleInfo titleInfo,BOOL bRedraw = TRUE);
			// 函数 GetColumnTitleInfo
			// 作用：读取GetColumnTitleInfo。
			// 参数：colId；titleInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnTitleInfo(int colId,CTitleInfo& titleInfo);

			// 函数 SetColumnCheckFunc
			// 作用：设置SetColumnCheckFunc。
			// 参数：colId；bHaveCheckFunc：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnCheckFunc(int colId,BOOL bHaveCheckFunc,BOOL bRedraw = FALSE);
			// 函数 GetColumnCheckFunc
			// 作用：读取GetColumnCheckFunc。
			// 参数：colId；bHaveCheckFunc：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnCheckFunc(int colId,BOOL& bHaveCheckFunc);

			// 函数 SetColumnColorFunc
			// 作用：设置SetColumnColorFunc。
			// 参数：colId；bHaveColorFunc：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnColorFunc(int colId,BOOL bHaveColorFunc,BOOL bRedraw = FALSE);
			// 函数 GetColumnColorFunc
			// 作用：读取GetColumnColorFunc。
			// 参数：colId；bHaveColorFunc：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnColorFunc(int colId,BOOL& bHaveColorFunc);

			// 函数 SetColumnWidth
			// 作用：设置SetColumnWidth。
			// 参数：colId；colWidth；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnWidth(int colId,int colWidth,BOOL bRedraw = FALSE);
			// 函数 GetColumnWidth
			// 作用：读取GetColumnWidth。
			// 参数：colId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnWidth(int colId);

			// 函数 SetItemHeight
			// 作用：设置SetItemHeight。
			// 参数：itemH；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetItemHeight(int itemH,BOOL bRedraw = FALSE);
			// 函数 GetItemHeight
			// 作用：读取GetItemHeight。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetItemHeight();

			// 函数 SetFixedRowHeightColumnWidth
			// 作用：设置SetFixedRowHeightColumnWidth。
			// 参数：iRowH：整数；iColW：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetFixedRowHeightColumnWidth(int iRowH,int iColW,BOOL bRedraw = FALSE);
			// 函数 GetFixedRowHeightColumnWidth
			// 作用：读取GetFixedRowHeightColumnWidth。
			// 参数：iRowH：整数；iColW：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetFixedRowHeightColumnWidth(int& iRowH,int& iColW);

			// 函数 SetColumnText
			// 作用：设置SetColumnText。
			// 参数：colId；strColTitle：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnText(int colId,CString strColTitle);
			// 函数 GetColumnText
			// 作用：读取GetColumnText。
			// 参数：colId。
			// 返回：返回一段文字。
			CString GetColumnText(int colId);

			// 函数 SetColumnMaxMinInfo
			// 作用：设置SetColumnMaxMinInfo。
			// 参数：colId；maxMinInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnMaxMinInfo(int colId,CMaxMinInfo maxMinInfo);
			// 函数 GetColumnMaxMinInfo
			// 作用：读取GetColumnMaxMinInfo。
			// 参数：colId；maxMinInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnMaxMinInfo(int colId,CMaxMinInfo& maxMinInfo);

			// 函数 SetItemText
			// 作用：设置SetItemText。
			// 参数：rowId；colId；strText：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetItemText(int rowId,int colId,CString strText,BOOL bRedraw = FALSE);
			// 函数 GetItemText
			// 作用：读取GetItemText。
			// 参数：rowId；colId。
			// 返回：返回一段文字。
			CString GetItemText(int rowId,int colId);

			// 函数 SetRowSelectState
			// 作用：设置SetRowSelectState。
			// 参数：rowId；bSelected：是或否；bSingleSel：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRowSelectState(int rowId,BOOL bSelected,BOOL bSingleSel = FALSE,BOOL bRedraw = FALSE);
			// 函数 GetRowSelectState
			// 作用：读取GetRowSelectState。
			// 参数：rowId；bSelected：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowSelectState(int rowId,BOOL& bSelected);

			// 函数 SetRowDisableState
			// 作用：设置SetRowDisableState。
			// 参数：rowId；bDisabled：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRowDisableState(int rowId,BOOL bDisabled,BOOL bRedraw = FALSE);
			// 函数 GetRowDisableState
			// 作用：读取GetRowDisableState。
			// 参数：rowId；bDisabled：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowDisableState(int rowId,BOOL& bDisabled);

			// 函数 SetCellCheckState
			// 作用：设置SetCellCheckState。
			// 参数：rowId；colId；bChecked：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellCheckState(int rowId,int colId,BOOL bChecked,BOOL bRedraw = FALSE);
			// 函数 GetCellCheckState
			// 作用：读取GetCellCheckState。
			// 参数：rowId；colId；bChecked：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCellCheckState(int rowId,int colId,BOOL& bChecked);

			// 函数 SetCellDisableState
			// 作用：设置SetCellDisableState。
			// 参数：rowId；colId；bDisabled：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellDisableState(int rowId,int colId,BOOL bDisabled,BOOL bRedraw = FALSE);
			// 函数 GetCellDisableState
			// 作用：读取GetCellDisableState。
			// 参数：rowId；colId；bDisabled：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCellDisableState(int rowId,int colId,BOOL& bDisabled);

			// 函数 SetCellSelfCbInfo
			// 作用：设置SetCellSelfCbInfo。
			// 参数：rowId；colId；bCbable：是或否；bUseCellLnkCbStr：是或否；lnkCbStr；bEditableCb：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellSelfCbInfo(int rowId,int colId,BOOL bCbable,BOOL bUseCellLnkCbStr,CLinkList<CString>& lnkCbStr,BOOL bEditableCb,BOOL bRedraw = FALSE);	//设置单元格自定义的下拉框信息
			// 函数 GetCellSelfCbInfo
			// 作用：读取GetCellSelfCbInfo。
			// 参数：rowId；colId；bCbable：是或否；bUseCellLnkCbStr：是或否；lnkCbStr；bEditableCb：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCellSelfCbInfo(int rowId,int colId,BOOL& bCbable,BOOL& bUseCellLnkCbStr,CLinkList<CString>& lnkCbStr,BOOL& bEditableCb);

			// 函数 GetRowNum
			// 作用：读取GetRowNum。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowNum();
			// 函数 GetColNum
			// 作用：读取GetColNum。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColNum();

			// 函数 SetBeGradientHeader
			// 作用：设置SetBeGradientHeader。
			// 参数：bGradientHeader：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeGradientHeader(BOOL bGradientHeader,BOOL bRedraw = FALSE);
			// 函数 GetBeGradientHeader
			// 作用：读取GetBeGradientHeader。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeGradientHeader();

			// 函数 SetBkColor
			// 作用：设置SetBkColor。
			// 参数：bkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBkColor(COLORREF bkClr,BOOL bRedraw = FALSE);
			// 函数 GetBkColor
			// 作用：读取GetBkColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetBkColor();

			// 函数 SetHeaderBkColor
			// 作用：设置SetHeaderBkColor。
			// 参数：headerBkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHeaderBkColor(COLORREF headerBkClr,BOOL bRedraw = FALSE);
			// 函数 GetHeaderBkColor
			// 作用：读取GetHeaderBkColor。
			// 参数：无。
			// 返回：返回 Color。
			Color GetHeaderBkColor();

			// 函数 SetBodyBkColor
			// 作用：设置SetBodyBkColor。
			// 参数：bodyBkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBodyBkColor(COLORREF bodyBkClr,BOOL bRedraw = FALSE);
			// 函数 GetBodyBkColor
			// 作用：读取GetBodyBkColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetBodyBkColor();

			// 函数 SetRowHeaderWidth
			// 作用：设置SetRowHeaderWidth。
			// 参数：iRowW：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRowHeaderWidth(int iRowW,BOOL bRedraw = FALSE);
			// 函数 GetRowHeaderWidth
			// 作用：读取GetRowHeaderWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowHeaderWidth();

			// 函数 SetColumnHeaderHeight
			// 作用：设置SetColumnHeaderHeight。
			// 参数：iColH：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetColumnHeaderHeight(int iColH,BOOL bRedraw = FALSE);
			// 函数 GetColumnHeaderHeight
			// 作用：读取GetColumnHeaderHeight。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnHeaderHeight();

			// 函数 SetFrameLineWidth
			// 作用：设置SetFrameLineWidth。
			// 参数：frameLineWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetFrameLineWidth(int frameLineWidth,BOOL bRedraw = FALSE);
			// 函数 GetFrameLineWidth
			// 作用：读取GetFrameLineWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetFrameLineWidth();

			// 函数 SetFrameLineColor
			// 作用：设置SetFrameLineColor。
			// 参数：frameLineColor：颜色；bRedraw：是或否。
			// 返回：没有返回值。
			void SetFrameLineColor(COLORREF frameLineColor,BOOL bRedraw = FALSE);
			// 函数 GetFrameLineColor
			// 作用：读取GetFrameLineColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetFrameLineColor();

			// 函数 SetRowColLineWidth
			// 作用：设置SetRowColLineWidth。
			// 参数：rowColLineWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRowColLineWidth(int rowColLineWidth,BOOL bRedraw = FALSE);
			// 函数 GetRowColLineWidth
			// 作用：读取GetRowColLineWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowColLineWidth();

			// 函数 SetRowColLineColor
			// 作用：设置SetRowColLineColor。
			// 参数：rowColLineColor：颜色；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRowColLineColor(COLORREF rowColLineColor,BOOL bRedraw = FALSE);
			// 函数 GetRowColLineColor
			// 作用：读取GetRowColLineColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetRowColLineColor();

			// 函数 SetBeShowFrameLine
			// 作用：设置SetBeShowFrameLine。
			// 参数：bShowFrameLine：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeShowFrameLine(int bShowFrameLine,BOOL bRedraw = FALSE);
			// 函数 GetBeShowFrameLine
			// 作用：读取GetBeShowFrameLine。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShowFrameLine();

			// 函数 SetBeShowRowColLine
			// 作用：设置SetBeShowRowColLine。
			// 参数：bShowRowColLine：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeShowRowColLine(int bShowRowColLine,BOOL bRedraw = FALSE);
			// 函数 GetBeShowRowColLine
			// 作用：读取GetBeShowRowColLine。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShowRowColLine();

			// 函数 SetHeaderTextColor
			// 作用：设置SetHeaderTextColor。
			// 参数：headTextColor：颜色；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHeaderTextColor(COLORREF headTextColor,BOOL bRedraw = FALSE);
			// 函数 GetHeaderTextColor
			// 作用：读取GetHeaderTextColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetHeaderTextColor();

			// 函数 SetBeSingleSelect
			// 作用：设置SetBeSingleSelect。
			// 参数：bSingleSelect：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeSingleSelect(BOOL bSingleSelect,BOOL bRedraw = FALSE);
			// 函数 GetBeSingleSelect
			// 作用：读取GetBeSingleSelect。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeSingleSelect();

			// 函数 SetTitle
			// 作用：设置SetTitle。
			// 参数：strTitle：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetTitle(CString strTitle,BOOL bRedraw = FALSE);
			// 函数 GetTitle
			// 作用：读取GetTitle。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetTitle();

			// 函数 SetBeTellParentRowSelChange
			// 作用：设置SetBeTellParentRowSelChange。
			// 参数：beTellParentSiteSelChange。
			// 返回：没有返回值。
			void SetBeTellParentRowSelChange(BOOL beTellParentSiteSelChange);
			// 函数 GetBeTellParentRowSelChange
			// 作用：读取GetBeTellParentRowSelChange。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeTellParentRowSelChange();

			// 函数 InitFontHeader
			// 作用：初始化InitFontHeader。
			// 参数：lfHeight。
			// 返回：没有返回值。
			void InitFontHeader(int lfHeight);
			// 函数 SetMyHeaderFont
			// 作用：设置SetMyHeaderFont。
			// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
			// 返回：没有返回值。
			void SetMyHeaderFont(CString fontName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL); //nHeight单位为 磅，即1/72英寸;
			// 函数 SetMyHeaderFont
			// 作用：设置SetMyHeaderFont。
			// 参数：无。
			// 返回：没有返回值。
			void SetMyHeaderFont();

			// 函数 InitFontTitle
			// 作用：初始化InitFontTitle。
			// 参数：lfHeight。
			// 返回：没有返回值。
			void InitFontTitle(int lfHeight);
			// 函数 SetMyTitleFont
			// 作用：设置SetMyTitleFont。
			// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
			// 返回：没有返回值。
			void SetMyTitleFont(CString fontName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL); //nHeight单位为 磅，即1/72英寸;
			// 函数 SetMyTitleFont
			// 作用：设置SetMyTitleFont。
			// 参数：无。
			// 返回：没有返回值。
			void SetMyTitleFont();

			// 函数 InitFontAbbr
			// 作用：初始化InitFontAbbr。
			// 参数：lfHeight。
			// 返回：没有返回值。
			void InitFontAbbr(int lfHeight);
			// 函数 SetMyFontAbbr
			// 作用：设置SetMyFontAbbr。
			// 参数：fontName；nHeight：整数；nWeight：整数；fontUnitType。
			// 返回：没有返回值。
			void SetMyFontAbbr(CString fontName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL); //nHeight单位为 磅，即1/72英寸;
			// 函数 SetMyFontAbbr
			// 作用：设置SetMyFontAbbr。
			// 参数：无。
			// 返回：没有返回值。
			void SetMyFontAbbr();

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

			// 函数 GetRowTag
			// 作用：读取GetRowTag。
			// 参数：iRowId：整数；strTag：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetRowTag(int iRowId,CString& strTag);
			// 函数 GetColTag
			// 作用：读取GetColTag。
			// 参数：iColId：整数；strTag：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColTag(int iColId,CString& strTag);

			// 函数 GetSiteTag
			// 作用：读取GetSiteTag。
			// 参数：iSiteIndex：整数；strTag：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSiteTag(int iSiteIndex,CString& strTag);
			// 函数 GetSiteTag
			// 作用：读取GetSiteTag。
			// 参数：iRowId：整数；iColId：整数；strTag：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSiteTag(int iRowId,int iColId,CString& strTag);

			// 函数 SetRowColNum
			// 作用：设置SetRowColNum。
			// 参数：iRowNum：整数；iColNum：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRowColNum(int iRowNum,int iColNum,BOOL bRedraw = FALSE);
			// 函数 GetBeValidPlate
			// 作用：读取GetBeValidPlate。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeValidPlate();	//判断孔板是否合法

			// 函数 UpdateRowSelectState
			// 作用：更新或清除UpdateRowSelectState。
			// 参数：iRowId：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UpdateRowSelectState(int iRowId,BOOL bRedraw);
			// 函数 UpdateColSelectState
			// 作用：更新或清除UpdateColSelectState。
			// 参数：iColId：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UpdateColSelectState(int iColId,BOOL bRedraw);

			// 函数 UpdateRowSelectState
			// 作用：更新或清除UpdateRowSelectState。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UpdateRowSelectState(BOOL bRedraw);
			// 函数 UpdateColSelectState
			// 作用：更新或清除UpdateColSelectState。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UpdateColSelectState(BOOL bRedraw);

			// 函数 SetAllSelectState
			// 作用：设置SetAllSelectState。
			// 参数：bSelected：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetAllSelectState(BOOL bSelected,BOOL bRedraw = FALSE);
			// 函数 SetAllSelectStateImmediately
			// 作用：设置SetAllSelectStateImmediately。
			// 参数：bSelected：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetAllSelectStateImmediately(BOOL bSelected,BOOL bRedraw = FALSE);	//让父窗口立即响应
			// 函数 GetBeAllSelected
			// 作用：读取GetBeAllSelected。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeAllSelected();

			// 函数 SetCurSelectSite
			// 作用：设置SetCurSelectSite。
			// 参数：vecSelSite；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCurSelectSite(vector<int>& vecSelSite,BOOL bRedraw = FALSE);
			// 函数 GetCurSelectSite
			// 作用：读取GetCurSelectSite。
			// 参数：vecSelSite。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCurSelectSite(vector<int>& vecSelSite);

			// 函数 GetSamInfo
			// 作用：读取GetSamInfo。
			// 参数：iSiteIndex：整数；samInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSamInfo(int iSiteIndex,CTubeInfo& samInfo);
			// 函数 GetSamInfo
			// 作用：读取GetSamInfo。
			// 参数：iRowId：整数；iColId：整数；samInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSamInfo(int iRowId,int iColId,CTubeInfo& samInfo);

			// 函数 GetTubeInfoPtr
			// 作用：读取GetTubeInfoPtr。
			// 参数：iSiteIndex：整数；ppTubeInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetTubeInfoPtr(int iSiteIndex,CTubeInfo** ppTubeInfo);
			// 函数 GetTubeInfoPtr
			// 作用：读取GetTubeInfoPtr。
			// 参数：无。
			// 返回：返回指针 CTubeInfo*。指针为空表示没有取到对象。
			CTubeInfo* GetTubeInfoPtr();
			// 函数 GetSamInfo
			// 作用：读取GetSamInfo。
			// 参数：vecSamInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSamInfo(vector<CTubeInfo>& vecSamInfo);

			// 函数 SetSamInfo
			// 作用：设置SetSamInfo。
			// 参数：vecSamInfo；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSamInfo(vector<CTubeInfo>& vecSamInfo,BOOL bRedraw = FALSE);
			// 函数 SetTubeInfo
			// 作用：设置SetTubeInfo。
			// 参数：pTubeAryPtr：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetTubeInfo(CPtrArray* pTubeAryPtr,BOOL bRedraw = FALSE);
			// 函数 SetTubeInfo
			// 作用：设置SetTubeInfo。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；iSiteNum：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetTubeInfo(CTubeInfo* pTubeInfo,int iSiteNum,BOOL bRedraw = FALSE);
			// 函数 SetTubeInfo
			// 作用：设置SetTubeInfo。
			// 参数：vecPTubeInfo；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetTubeInfo(vector<CTubeInfo*>& vecPTubeInfo,BOOL bRedraw = FALSE);

			// 函数 SetSamInfo
			// 作用：设置SetSamInfo。
			// 参数：iSiteIndex：整数；samInfo；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSamInfo(int iSiteIndex,CTubeInfo& samInfo,BOOL bRedraw = FALSE);
			// 函数 SetSamInfo
			// 作用：设置SetSamInfo。
			// 参数：iRowId：整数；iColId：整数；samInfo；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSamInfo(int iRowId,int iColId,CTubeInfo& samInfo,BOOL bRedraw = FALSE);

			// 函数 SetSamInfo
			// 作用：设置SetSamInfo。
			// 参数：iSiteIndex：整数；eItemInfoType；strData：字符串；intData；dData：小数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSamInfo(int iSiteIndex,EITEMINFOTYPE eItemInfoType,CString strData,int intData = 0,double dData = 0,BOOL bRedraw = FALSE);
			// 函数 SetSamInfo
			// 作用：设置SetSamInfo。
			// 参数：iRowId：整数；iColId：整数；eItemInfoType；strData：字符串；intData；dData：小数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSamInfo(int iRowId,int iColId,EITEMINFOTYPE eItemInfoType,CString strData,int intData = 0,double dData = 0,BOOL bRedraw = FALSE);

			// 函数 SetRectWidth
			// 作用：设置SetRectWidth。
			// 参数：iRectW：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRectWidth(int iRectW,BOOL bRedraw = FALSE);
			// 函数 SetRectHeight
			// 作用：设置SetRectHeight。
			// 参数：iRectH：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRectHeight(int iRectH,BOOL bRedraw = FALSE);

			// 函数 SetBeShowTopText
			// 作用：设置SetBeShowTopText。
			// 参数：bShowTopTx：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeShowTopText(BOOL bShowTopTx,BOOL bRedraw = FALSE);
			// 函数 GetBeShowTopText
			// 作用：读取GetBeShowTopText。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShowTopText();

			// 函数 SetBeShowBottomText
			// 作用：设置SetBeShowBottomText。
			// 参数：bShowBottomTx：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeShowBottomText(BOOL bShowBottomTx,BOOL bRedraw = FALSE);
			// 函数 GetBeShowBottomText
			// 作用：读取GetBeShowBottomText。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShowBottomText();

			// 函数 GetPlateSelectState
			// 作用：读取GetPlateSelectState。
			// 参数：vecSelState。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetPlateSelectState(vector<BOOL>& vecSelState);
			// 函数 GetPlateSelectedSite
			// 作用：读取GetPlateSelectedSite。
			// 参数：vecSelectedSite。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetPlateSelectedSite(vector<BOOL>& vecSelectedSite);

			// 函数 SetFourAngleBkColor
			// 作用：设置SetFourAngleBkColor。
			// 参数：clrFourAngleBk：颜色；bRedraw：是或否。
			// 返回：没有返回值。
			void SetFourAngleBkColor(COLORREF clrFourAngleBk,BOOL bRedraw = FALSE);
			// 函数 GetFourAngleBkColor
			// 作用：读取GetFourAngleBkColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetFourAngleBkColor();

			// 函数 SetInterval
			// 作用：设置SetInterval。
			// 参数：iHori：整数；iVert：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetInterval(int iHori,int iVert,BOOL bRedraw = FALSE);
			// 函数 GetHoriInterval
			// 作用：读取GetHoriInterval。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetHoriInterval();
			// 函数 GetVertInterval
			// 作用：读取GetVertInterval。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetVertInterval();

			// 函数 SetBeShieldDeleteKey
			// 作用：设置SetBeShieldDeleteKey。
			// 参数：bShieldDeleteKey：是或否。
			// 返回：没有返回值。
			void SetBeShieldDeleteKey(BOOL bShieldDeleteKey);
			// 函数 GetBeShieldDeleteKey
			// 作用：读取GetBeShieldDeleteKey。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShieldDeleteKey();

			// 函数 SetBeParentProcessDeleteKey
			// 作用：设置SetBeParentProcessDeleteKey。
			// 参数：bParentProcessDeleteKey：是或否。
			// 返回：没有返回值。
			void SetBeParentProcessDeleteKey(BOOL bParentProcessDeleteKey);
			// 函数 GetBeParentProcessDeleteKey
			// 作用：读取GetBeParentProcessDeleteKey。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeParentProcessDeleteKey();

			// 函数 SetSiteIdShowState
			// 作用：设置SetSiteIdShowState。
			// 参数：bShow：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetSiteIdShowState(BOOL bShow,BOOL bRedraw = FALSE);
			// 函数 GetSiteIdShowState
			// 作用：读取GetSiteIdShowState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetSiteIdShowState();

			// 函数 SetLastChanBlockShowState
			// 作用：设置SetLastChanBlockShowState。
			// 参数：bShow：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetLastChanBlockShowState(BOOL bShow,BOOL bRedraw = FALSE);
			// 函数 GetLastChanBlockShowState
			// 作用：读取GetLastChanBlockShowState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetLastChanBlockShowState();

			// 函数 DeleteSelectedTubeInfo
			// 作用：更新或清除DeleteSelectedTubeInfo。
			// 参数：bTemplateMode：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteSelectedTubeInfo(BOOL bTemplateMode);	//删除选中的孔位信息
			// 函数 DeleteTubeInfo
			// 作用：更新或清除DeleteTubeInfo。
			// 参数：vecId；bTemplateMode：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteTubeInfo(vector<int> vecId,BOOL bTemplateMode);	//删除选中孔位的所有信息
			// 函数 DeleteTubeInfo
			// 作用：更新或清除DeleteTubeInfo。
			// 参数：vecId；eDeletType；bTemplateMode：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteTubeInfo(vector<int> vecId,EDELETETYPE eDeletType,BOOL bTemplateMode);	//删除选中孔位的所有信息
			// 函数 DeleteAllTubeInfo
			// 作用：更新或清除DeleteAllTubeInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteAllTubeInfo();	//删除所有的孔位信息

			// 函数 GetSameTubeInfo
			// 作用：读取GetSameTubeInfo。
			// 参数：tubeInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSameTubeInfo(CTubeInfo& tubeInfo);	//选中多个孔位时，提取相同的信息项

			// 函数 SetAllTubeChanInfo
			// 作用：设置SetAllTubeChanInfo。
			// 参数：iChanId：整数；bSelected：是或否；strDyeName：字符串；strTargetName：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetAllTubeChanInfo(int iChanId,BOOL bSelected,CString strDyeName,CString strTargetName);

			// 函数 GetOneChannelDyeNameFromTubeInfo
			// 作用：读取GetOneChannelDyeNameFromTubeInfo。
			// 参数：iChanId：整数。
			// 返回：返回一段文字。
			CString GetOneChannelDyeNameFromTubeInfo(int iChanId);

			// 函数 GetAllSampleType
			// 作用：读取GetAllSampleType。
			// 参数：vecSamType。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetAllSampleType(vector<eSampleType>& vecSamType);	//按下标顺序获取孔板的样本类型信息

	 static CString SampleTypeToText(eSampleType eType);
	 static eSampleType TextToSampleType(CString strText);

	 static int InitMapSampleTypeToText();
	 static int InitMapTextToSampleType(); 
	 static int InitMapSamTypeToHoleClrInfo(); 
	 static int InitMapSamTypeToAbbr();
	 static CString GetSampleTypeAbbr(eSampleType eType);

private:
			// 函数 CalcTotalColumnWidth
			// 作用：计算CalcTotalColumnWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcTotalColumnWidth();
			// 函数 CalcTotalRowHeight
			// 作用：计算CalcTotalRowHeight。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcTotalRowHeight();
			// 函数 CalcRowColToShow
			// 作用：计算CalcRowColToShow。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcRowColToShow();	//计算显示的 行列起始、终止序号,上下左右缩进,当增删行、列并且影响到显示行列时调用该函数
			// 函数 CalcRowColToShowOnNoRowData
			// 作用：计算CalcRowColToShowOnNoRowData。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcRowColToShowOnNoRowData();	//没有行数据时，按照固定行高（28）计算显示分割线显示区域
			// 函数 CalcColToShow
			// 作用：计算CalcColToShow。
			// 参数：newStartCol。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcColToShow(int newStartCol);	//删除列时使用
			// 函数 CalcRowToShow
			// 作用：计算CalcRowToShow。
			// 参数：newStartRow。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcRowToShow(int newStartRow);	//删除行时使用
			// 函数 ScrollCol
			// 作用：执行ScrollCol。
			// 参数：pxHoriShift。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ScrollCol(int pxHoriShift);
			// 函数 ScrollRow
			// 作用：执行ScrollRow。
			// 参数：pxVertShift。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ScrollRow(int pxVertShift);
			// 函数 ScrollColToFixPos
			// 作用：执行ScrollColToFixPos。
			// 参数：pxFixPos。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ScrollColToFixPos(int pxFixPos);
			// 函数 ScrollRowToFixPos
			// 作用：执行ScrollRowToFixPos。
			// 参数：pxFixPos。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ScrollRowToFixPos(int pxFixPos);
			// 函数 CalcScrollPos
			// 作用：计算CalcScrollPos。
			// 参数：无。
			// 返回：没有返回值。
			void CalcScrollPos();

			// 函数 CheckMaxMinSet
			// 作用：判断CheckMaxMinSet是否成立。
			// 参数：strTemp：字符串；maxMinInfo。
			// 返回：没有返回值。
			void CheckMaxMinSet(CString& strTemp,CMaxMinInfo& maxMinInfo);	//结束编辑后，验证最大最小值设置是否在正确范围内，不在正确范围内则自动修正

			// 函数 GetHoleColorInfo
			// 作用：读取GetHoleColorInfo。
			// 参数：iRowId：整数；iColId：整数；holeClrInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetHoleColorInfo(int iRowId,int iColId,CHoleColorInfo& holeClrInfo);

public:
	CLinkList<CTitleInfo> m_lnkTitleInfo;	//保存标题信息
	CLinkList<CLinkList<CCellInfo>> m_2LnkCellInfo;	//保存行列内容信息
	CLinkList<CRowInfo> m_lnkRowInfo;	//保存行公共信息

private:
	int m_rowNum;
	int m_colNum;

	int m_colIdStartShow;
	int m_colIdEndShow;
	int m_rowIdStartShow;
	int m_rowIdEndShow;
	int m_ssColLeftIndent;	//起始显示列左侧缩进
	int m_esColRightIndent;	//终止显示列左侧缩进
	int m_ssRowTopIndent;	//起始显示行顶部缩进
	int m_esRowBottomIndent;	//终止显示列底部缩进

	int m_rowIdSeparatorStart;	//分割线显示起始行，不需要垂直滚动时使用
	int m_rowIdSeparatorEnd;	//分割线显示终止行，不需要垂直滚动时使用
	int m_esSeparatorBottomIndent;	//分割线显示底部缩进，不需要垂直滚动时使用

	int m_pxRowH;	//固定行高 
	int m_pxColW;	//固定列宽
	int m_pxColHeaderH;	//列标题标题高度
	int m_pxRowHeaderW; //行标题宽度
	int m_pxFrame;	//边框宽度
	int m_pxRowColLine;	//行列分割线宽度

	BOOL m_bUseFixedHW;	//是否使用固定行高列宽模式
	BOOL m_bGradientHeader;	//标题栏是否使用渐变色背景

	COLORREF m_clrBk;	//主窗口背景色
	Color m_clrHeaderBk;	//标题栏背景颜色
	Color m_clrHeaderSelectedBk;	//标题栏背景颜色
	COLORREF m_clrBodyBk;	//body背景色
	COLORREF m_clrFrame;	//边框颜色
	COLORREF m_clrRowColLine;	//行列分割线颜色
	COLORREF m_clrHeaderText;	//标题栏文字颜色

	Color m_clrGraHeadStart;
	Color m_clrGraHeadEnd;
	BOOL m_bEditable;	//是否可编辑

	COLORREF m_clrHeadBodySepa;	//Header和Body分隔线

	BOOL m_bShowFrameLine;	//是否显示列表框边框线
	BOOL m_bShowRowColLine;	//是否显示水平、垂直分割线
	BOOL m_bSingleSelect;	//标识是否是单选功能

	BOOL m_bTellParentSiteSelChange;	//类表框选中孔位改变是否通知父窗口

	BOOL m_bShowSplitLine;	//是否显示分割线

	CRect m_rcLst;
	CRect m_rcColHeader;	//行标题
	CRect m_rcRowHeader;	//列标题	
	CRect m_rcTotalHeader;	//总标题
	CRect m_rcBody;

	int m_totalColW;	//所有列的宽度之和
	int m_totalRowH;	//所有行的高度之和

	int m_cdcW;	//记录显示列的总宽度（包括 左侧、右侧缩进像素） CDC Width
	int m_cdcH;	//记录显示行的总高度（包括 顶部、底部缩进像素） CDC Height

	CDotPosInfo m_curDotPosInfo;	//记录最近一次点击的行列信息，需要重新梳理
	CDotPosInfo m_preDotPosInfo;	//记录前一个点击的行列信息，需要重新梳理
	CLinkList<CDotPosInfo> m_lnkHistoryDotPosInfo;	//记录最近N个点击的行列信息

	CDotPosInfo m_dotPosLeftBtDown;	//记录鼠标左键按下时位置
	CDotPosInfo m_dotPosLeftBtUp;	//记录鼠标左键弹起时位置

	CFont m_fontSetHeader; 
	CFont m_fontSetTitle;
	CFont m_fontAbbr;	//显示样本类型缩写使用
	LOGFONT m_logFontHeader;
	LOGFONT m_logFontTitle;
	LOGFONT m_logFontAbbr;

	CString m_strTotalTitle;	//总标题

	int m_iRowWidth;

	BOOL m_bDraggableStart;	//标识可以触发拖动鼠标选中区域
	BOOL m_bDragMove;	//标识是否正在拖动鼠标选中区域
	CDotPosInfo m_dragStartDotPosInfo;	//记录拖动鼠标选中区域起点信息
	CPoint m_ptPreOnMove;	//记录鼠标移动时上一个坐标点

	int m_iRectW;	//圆角矩形宽度
	int m_iRectH;	//圆角矩形高度

	BOOL m_bShowTopTx;	//孔位顶端是否显示文本
	BOOL m_bShowBottomTx;	//孔位底端是否显示文本

	BOOL m_bLeftBtDown;	//记录左键按下、弹起是否成对发生在控件内部

	int m_iRoundAngleLT;	//左上角圆角大小
	int m_iRoundAngleRT;	//右上角圆角大小
	int m_iRoundAngleRB;	//右下角圆角大小
	int m_iRoundAngleLB;	//左下角圆角大小

public:
	//水平滚动条
	CMyScrollInfo m_horiScroll;
	CMyScrollInfo m_vertScroll;
	ESCROLLHVCONFLICTMANAGE m_eScrollHVCM;

	int m_iTotalSiteNum;	//总的孔位数
	BOOL m_bAllSelected;	//是否全部选中

	CMySelWnd m_sonWnd;

	//圆角矩形样式参数
	BOOL m_bRoundRectStyle;	//标识是否使用圆角矩形样式
	COLORREF m_clrFourAngleBk;	//圆角矩形以外的背景色
	int m_iRoundAngleSize;	//圆角大小
	Color m_clrIndepent;	//独立第三方颜色，用于支持局部透明

	static map<eSampleType,CString> m_mapSamTypeToTx;	//样本类型--文本映射
	static map<CString,eSampleType> m_mapTxToSamType;	//文本--样本类型映射
	static map<eSampleType,CHoleColorInfo> m_mapSamTypeToHoleClrInfo;	//样本类型--孔位颜色信息映射
	static map<eSampleType,CString> m_mapSamTypeToAbbr;	//样本类型--文本缩写映射

protected:
	CTubeInfo* m_pTubeInfo;	//样本信息
	CPlateInfo* m_pPlateInfo;	//孔板孔位参数信息

	//备用参数
	int m_iLeftIndent;	//左侧缩进	
	int m_iRightIndent;	//右侧缩进
	int m_iTopIndent;	//顶部缩进
	int m_iBottomIndent;	//底部缩进
	
	int m_iHoriInterval;	//孔位间水平间隔
	int m_iVertInterval;	//孔位间垂直间隔

	BOOL m_bShieldDeleteKey;	//是否屏蔽Delete按键删除功能

	BOOL m_bParentProcessDeleteKey;	//标识是否由父窗口处理Delete按键删除功能

	BOOL m_bShowSiteId;	//是否显示孔位序号标识
	BOOL m_bShowLastChanBlock;	//是否显示最后一个通道的颜色块（PS96的校准通道）
};






