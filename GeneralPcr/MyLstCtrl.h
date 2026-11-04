// 【交接】 GeneralPcr\MyLstCtrl.h
// 作用：MyLstCtrl 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：DECLARE_DYNAMIC、CMyLstCtrl、DECLARE_MESSAGE_MAP、OnPaint、OnInitDialog、DrawHeader、DrawBody、DrawHoriScroll。
#pragma once

#include "FontSet.h"
#include "MyNewEdit.h"
#include "LinkList.h"
#include "TitleInfo.h"
#include "CellInfo.h"
#include "MyScrollInfo.h"
#include "SelfDefType.h"
#include "RowInfo.h"
#include "DotPosInfo.h"
#include "RowColEditInfo.h"
#include "MyInputCb.h"
#include "ColorSelectDlg.h"

#include <GdiPlus.h>
#include <map>

using namespace std;

#define WM_TELLPARENTCELLCHANGED	WM_USER + 6031	//编辑框单元格信息改变，通知父窗口

class CMyLstCtrl : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyLstCtrl。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMyLstCtrl)

public:
	// 函数 CMyLstCtrl
	// 作用：执行CMyLstCtrl。
	// 参数：无。
	// 返回：没有返回值。
	CMyLstCtrl();
	// 函数 ~CMyLstCtrl
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMyLstCtrl();
	
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
	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();

public:
			// 函数 DrawHeader
			// 作用：绘制DrawHeader。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawHeader(CDC* pDC);
	// 函数 DrawBody
	// 作用：绘制DrawBody。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int DrawBody(CDC* pDC);
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
			// 函数 DrawHoriScrollStyle2
			// 作用：绘制DrawHoriScrollStyle2。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawHoriScrollStyle2(CDC* pDC);	//绘制水平滚动条样式2，圆角边框模式使用
			// 函数 DrawVertScrollStyle2
			// 作用：绘制DrawVertScrollStyle2。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawVertScrollStyle2(CDC* pDC);	//绘制垂直滚动条样式2，圆角边框模式使用

	//virtual BOOL PreTranslateMessage(MSG* pMsg);

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
	// 函数 OnMsgFuncEditKillFocus
	// 作用：响应 Windows 或自定义消息 OnMsgFuncEditKillFocus。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgFuncEditKillFocus(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgEditEnterPushed
	// 作用：响应 Windows 或自定义消息 OnMsgEditEnterPushed。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgEditEnterPushed(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTouch
	// 作用：响应 Windows 或自定义消息 OnMsgTouch。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTouch(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgGesture
	// 作用：响应 Windows 或自定义消息 OnMsgGesture。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgGesture(WPARAM wParam,LPARAM lParam);

	// 函数 OnMsgHorizonScroll
	// 作用：响应 Windows 或自定义消息 OnMsgHorizonScroll。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgHorizonScroll(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgVerticalScroll
	// 作用：响应 Windows 或自定义消息 OnMsgVerticalScroll。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgVerticalScroll(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgSelectNewColor
	// 作用：响应 Windows 或自定义消息 OnMsgSelectNewColor。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgSelectNewColor(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgDeleteComboRowString
	// 作用：响应 Windows 或自定义消息 OnMsgDeleteComboRowString。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgDeleteComboRowString(WPARAM wParam,LPARAM lParam);

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

			// 函数 SetScrollArrowWH
			// 作用：设置SetScrollArrowWH。
			// 参数：iWidth：整数；iHeight：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetScrollArrowWH(int iWidth,int iHeight,BOOL bRedraw = FALSE);

			// 函数 CalcPtRowCol
			// 作用：计算CalcPtRowCol。
			// 参数：pt。
			// 返回：返回 CDotPosInfo。
			CDotPosInfo CalcPtRowCol(CPoint pt);

			// 函数 InsertColumn
			// 作用：创建或加入InsertColumn。
			// 参数：colId；strColTitle：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertColumn(int colId,CString strColTitle,BOOL bRedraw = FALSE);
			// 函数 InsertRow
			// 作用：创建或加入InsertRow。
			// 参数：rowId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertRow(int rowId,BOOL bRedraw = FALSE);
			// 函数 InsertRowSetHeight
			// 作用：创建或加入InsertRowSetHeight。
			// 参数：rowId；iRowH：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InsertRowSetHeight(int rowId,int iRowH,BOOL bRedraw = FALSE);

			// 函数 DeleteColumn
			// 作用：更新或清除DeleteColumn。
			// 参数：colId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteColumn(int colId,BOOL bRedraw = TRUE);
			// 函数 DeleteAllColumn
			// 作用：更新或清除DeleteAllColumn。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteAllColumn(BOOL bRedraw = TRUE);
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

			// 函数 SetSelectedRowId
			// 作用：设置SetSelectedRowId。
			// 参数：vecSelRowId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSelectedRowId(vector<int>& vecSelRowId,BOOL bRedraw = FALSE);	//获取选中行的下标，从小到大的顺序
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

			// 函数 SetCellCheckFunc
			// 作用：设置SetCellCheckFunc。
			// 参数：rowId；colId；bCheckable：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellCheckFunc(int rowId,int colId,BOOL bCheckable,BOOL bRedraw = FALSE);
			// 函数 GetCellCheckFunc
			// 作用：读取GetCellCheckFunc。
			// 参数：rowId；colId；bCheckable：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCellCheckFunc(int rowId,int colId,BOOL& bCheckable);

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

			// 函数 SetColumnColorEditable
			// 作用：设置SetColumnColorEditable。
			// 参数：colId；bClrEditable：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnColorEditable(int colId,BOOL bClrEditable,BOOL bRedraw = FALSE);
			// 函数 GetColumnColorEditable
			// 作用：读取GetColumnColorEditable。
			// 参数：colId；bClrEditable：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnColorEditable(int colId,BOOL& bClrEditable);

			// 函数 SetColumnEditable
			// 作用：设置SetColumnEditable。
			// 参数：colId；bEditable：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnEditable(int colId,BOOL bEditable,BOOL bRedraw = FALSE);
			// 函数 GetColumnEditable
			// 作用：读取GetColumnEditable。
			// 参数：colId；bEditable：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnEditable(int colId,BOOL& bEditable);

			// 函数 SetColumnDisableState
			// 作用：设置SetColumnDisableState。
			// 参数：colId；bDisabled：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnDisableState(int colId,BOOL bDisabled,BOOL bRedraw = FALSE);
			// 函数 GetColumnDisableState
			// 作用：读取GetColumnDisableState。
			// 参数：colId；bDisabled：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnDisableState(int colId,BOOL& bDisabled);

			// 函数 SetColumnTextAlignFormat
			// 作用：设置SetColumnTextAlignFormat。
			// 参数：colId；dwTxAlign；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnTextAlignFormat(int colId,DWORD dwTxAlign,BOOL bRedraw = FALSE);
			// 函数 GetColumnTextAlignFormat
			// 作用：读取GetColumnTextAlignFormat。
			// 参数：colId；dwTxAlign。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnTextAlignFormat(int colId,DWORD& dwTxAlign);

			// 函数 SetColumnMultiDensityState
			// 作用：设置SetColumnMultiDensityState。
			// 参数：colId；bData：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnMultiDensityState(int colId,BOOL bData,BOOL bRedraw = FALSE);
			// 函数 GetColumnMultiDensityState
			// 作用：读取GetColumnMultiDensityState。
			// 参数：colId；bData：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnMultiDensityState(int colId,BOOL& bData);

			// 函数 SetCellEditable
			// 作用：设置SetCellEditable。
			// 参数：rowId；colId；bEditable：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellEditable(int rowId,int colId,BOOL bEditable,BOOL bRedraw = FALSE);
			// 函数 GetCellEditable
			// 作用：读取GetCellEditable。
			// 参数：rowId；colId；bEditable：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCellEditable(int rowId,int colId,BOOL& bEditable);

			// 函数 SetColumnCbtable
			// 作用：设置SetColumnCbtable。
			// 参数：colId；bCbtable：是或否；bCbEditable：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnCbtable(int colId,BOOL bCbtable,BOOL bCbEditable = FALSE,BOOL bRedraw = FALSE);
			// 函数 GetColumnCbtable
			// 作用：读取GetColumnCbtable。
			// 参数：colId；bCbtable：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnCbtable(int colId,BOOL& bCbtable);

			// 函数 SetColumnBeTellParentCellChanged
			// 作用：设置SetColumnBeTellParentCellChanged。
			// 参数：colId；bTellParentCellChanged：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnBeTellParentCellChanged(int colId,BOOL bTellParentCellChanged);
			// 函数 GetColumnBeTellParentCellChanged
			// 作用：读取GetColumnBeTellParentCellChanged。
			// 参数：colId；bTellParentCellChanged：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnBeTellParentCellChanged(int colId,BOOL& bTellParentCellChanged);

			// 函数 SetColumnCbString
			// 作用：设置SetColumnCbString。
			// 参数：colId；lnkCbStr；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnCbString(int colId,CLinkList<CString>& lnkCbStr,BOOL bRedraw = FALSE);
			// 函数 GetColumnCbString
			// 作用：读取GetColumnCbString。
			// 参数：colId；lnkCbStr。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnCbString(int colId,CLinkList<CString>& lnkCbStr);

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

			// 函数 SetColumnDataParam
			// 作用：设置SetColumnDataParam。
			// 参数：iColId：整数；dtParam；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnDataParam(int iColId,CDataParam& dtParam,BOOL bRedraw = FALSE);
			// 函数 GetColumnDataParam
			// 作用：读取GetColumnDataParam。
			// 参数：iColId：整数；dtParam。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetColumnDataParam(int iColId,CDataParam& dtParam);

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

			// 函数 SetColumnText
			// 作用：设置SetColumnText。
			// 参数：colId；strColTitle：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnText(int colId,CString strColTitle,BOOL bRedraw = FALSE);
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

			// 函数 SetItemColorParam
			// 作用：设置SetItemColorParam。
			// 参数：rowId；colId；clr：颜色；clrW：颜色；clrH：颜色；iRoundAngle：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetItemColorParam(int rowId,int colId,COLORREF clr,int clrW,int clrH,int iRoundAngle,BOOL bRedraw = FALSE);
			// 函数 GetItemColorParam
			// 作用：读取GetItemColorParam。
			// 参数：rowId；colId；clr：颜色；clrW：颜色；clrH：颜色；iRoundAngle：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetItemColorParam(int rowId,int colId,COLORREF& clr,int& clrW,int& clrH,int& iRoundAngle);
			// 函数 SetItemColor
			// 作用：设置SetItemColor。
			// 参数：rowId；colId；clr：颜色；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetItemColor(int rowId,int colId,COLORREF clr,BOOL bRedraw = FALSE);
			// 函数 GetItemColor
			// 作用：读取GetItemColor。
			// 参数：rowId；colId；clr：颜色。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetItemColor(int rowId,int colId,COLORREF& clr);

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
			// 函数 SetCellSelfCbInfo
			// 作用：设置SetCellSelfCbInfo。
			// 参数：rowId；colId；bCbable：是或否；bUseCellLnkCbStr：是或否；bEditableCb：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellSelfCbInfo(int rowId,int colId,BOOL bCbable,BOOL bUseCellLnkCbStr,BOOL bEditableCb,BOOL bRedraw = FALSE);	//设置单元格自定义的下拉框信息
			// 函数 SetCellSelfCbInfo
			// 作用：设置SetCellSelfCbInfo。
			// 参数：rowId；colId；lnkCbStr；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellSelfCbInfo(int rowId,int colId,CLinkList<CString>& lnkCbStr,BOOL bRedraw = FALSE);
			// 函数 GetCellSelfCbInfo
			// 作用：读取GetCellSelfCbInfo。
			// 参数：rowId；colId；bCbable：是或否；bUseCellLnkCbStr：是或否；lnkCbStr；bEditableCb：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCellSelfCbInfo(int rowId,int colId,BOOL& bCbable,BOOL& bUseCellLnkCbStr,CLinkList<CString>& lnkCbStr,BOOL& bEditableCb);
			// 函数 GetCellSelfCbInfo
			// 作用：读取GetCellSelfCbInfo。
			// 参数：rowId；colId；lnkCbStr。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCellSelfCbInfo(int rowId,int colId,CLinkList<CString>& lnkCbStr);
			// 函数 SetCellSelCbRowDelete
			// 作用：设置SetCellSelCbRowDelete。
			// 参数：rowId；colId；bEnableDelete：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCellSelCbRowDelete(int rowId, int colId, BOOL bEnableDelete);

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
			void SetBkColor(Color bkClr,BOOL bRedraw = FALSE);
			// 函数 GetBkColor
			// 作用：读取GetBkColor。
			// 参数：无。
			// 返回：返回 Color。
			Color GetBkColor();

			// 函数 SetHeaderBkColor
			// 作用：设置SetHeaderBkColor。
			// 参数：headerBkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHeaderBkColor(Color headerBkClr,BOOL bRedraw = FALSE);
			// 函数 GetHeaderBkColor
			// 作用：读取GetHeaderBkColor。
			// 参数：无。
			// 返回：返回 Color。
			Color GetHeaderBkColor();

			// 函数 SetBodyBkColor
			// 作用：设置SetBodyBkColor。
			// 参数：bodyBkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBodyBkColor(Color bodyBkClr,BOOL bRedraw = FALSE);
			// 函数 GetBodyBkColor
			// 作用：读取GetBodyBkColor。
			// 参数：无。
			// 返回：返回 Color。
			Color GetBodyBkColor();

			// 函数 SetHeaderHeight
			// 作用：设置SetHeaderHeight。
			// 参数：headerHeight；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHeaderHeight(COLORREF headerHeight,BOOL bRedraw = FALSE);
			// 函数 GetHeaderHeight
			// 作用：读取GetHeaderHeight。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetHeaderHeight();

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
			void SetFrameLineColor(Color frameLineColor,BOOL bRedraw = FALSE);
			// 函数 GetFrameLineColor
			// 作用：读取GetFrameLineColor。
			// 参数：无。
			// 返回：返回 Color。
			Color GetFrameLineColor();

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

			// 函数 SetBeAllowCancelRowSelect
			// 作用：设置SetBeAllowCancelRowSelect。
			// 参数：bValue：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeAllowCancelRowSelect(BOOL bValue,BOOL bRedraw = FALSE);
			// 函数 GetBeAllowCancelRowSelect
			// 作用：读取GetBeAllowCancelRowSelect。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeAllowCancelRowSelect();

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
			// 参数：beTellParentRowSelChange。
			// 返回：没有返回值。
			void SetBeTellParentRowSelChange(BOOL beTellParentRowSelChange);
			// 函数 GetBeTellParentRowSelChange
			// 作用：读取GetBeTellParentRowSelChange。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeTellParentRowSelChange();

			// 函数 SetFourAngleBkColor
			// 作用：设置SetFourAngleBkColor。
			// 参数：clr：颜色；bRedraw：是或否。
			// 返回：没有返回值。
			void SetFourAngleBkColor(COLORREF clr,BOOL bRedraw = FALSE);
			// 函数 GetFourAngleBkColor
			// 作用：读取GetFourAngleBkColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetFourAngleBkColor();

			// 函数 SetLargeCheckIconUseState
			// 作用：设置SetLargeCheckIconUseState。
			// 参数：bData：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetLargeCheckIconUseState(BOOL bData,BOOL bRedraw = FALSE);
			// 函数 GetLargeCheckIconUseState
			// 作用：读取GetLargeCheckIconUseState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetLargeCheckIconUseState();

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

			// 函数 SetMapColumnDisableControl
			// 作用：设置SetMapColumnDisableControl。
			// 参数：colId；lnkDisabledCol。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetMapColumnDisableControl(int colId,CLinkList<int>& lnkDisabledCol);
			// 函数 GetMapColumnDisableControl
			// 作用：读取GetMapColumnDisableControl。
			// 参数：colId；lnkDisabledCol。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetMapColumnDisableControl(int colId,CLinkList<int>& lnkDisabledCol);
			// 函数 DeleteColumnDisableControl
			// 作用：更新或清除DeleteColumnDisableControl。
			// 参数：colId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteColumnDisableControl(int colId,BOOL bRedraw = FALSE);
			// 函数 ClearMapColumnDisableControl
			// 作用：更新或清除ClearMapColumnDisableControl。
			// 参数：无。
			// 返回：没有返回值。
			void ClearMapColumnDisableControl();

			// 函数 SetMapRowOutsideControl
			// 作用：设置SetMapRowOutsideControl。
			// 参数：rowId；lnkDisabledRow。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetMapRowOutsideControl(int rowId,CLinkList<int>& lnkDisabledRow);
			// 函数 GetMapRowOutsideControl
			// 作用：读取GetMapRowOutsideControl。
			// 参数：rowId；lnkDisabledRow。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetMapRowOutsideControl(int rowId,CLinkList<int>& lnkDisabledRow);
			// 函数 DeleteRowOutsideControl
			// 作用：更新或清除DeleteRowOutsideControl。
			// 参数：rowId；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteRowOutsideControl(int rowId,BOOL bRedraw = FALSE);
			// 函数 ClearMapRowOutsideControl
			// 作用：更新或清除ClearMapRowOutsideControl。
			// 参数：无。
			// 返回：没有返回值。
			void ClearMapRowOutsideControl();

			// 函数 UpdateRowColumnDisableState
			// 作用：更新或清除UpdateRowColumnDisableState。
			// 参数：rowId；colId；strText：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UpdateRowColumnDisableState(int rowId,int colId,CString strText,BOOL bRedraw = FALSE);	//列表框内部列控制关系更新
			// 函数 TellParentSomething
			// 作用：执行TellParentSomething。
			// 参数：rowId；colId；strText：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int TellParentSomething(int rowId,int colId,CString strText,BOOL bRedraw = FALSE);	//通知父窗口行信息改变，由父窗口做出其它操作,目前只对 可使用编辑框、下拉框修改的单元格进行该处理
			// 函数 TellParentCellChanged
			// 作用：执行TellParentCellChanged。
			// 参数：rowId；colId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int TellParentCellChanged(int rowId,int colId);	//通知父窗口单元格信息改变，由父窗口做出其它操作,目前只对 可使用编辑框、下拉框修改的单元格进行该处理

			// 函数 AddPairToMapDisabledStateKeyString
			// 作用：创建或加入AddPairToMapDisabledStateKeyString。
			// 参数：strKey：字符串；bDisabled：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AddPairToMapDisabledStateKeyString(CString strKey,BOOL bDisabled,BOOL bRedraw = FALSE);
			// 函数 GetKeyStringDisabledState
			// 作用：读取GetKeyStringDisabledState。
			// 参数：strKey：字符串；bDisabled：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetKeyStringDisabledState(CString strKey,BOOL& bDisabled);
			// 函数 DeleteKeyStringDisabledState
			// 作用：更新或清除DeleteKeyStringDisabledState。
			// 参数：strKey：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteKeyStringDisabledState(CString strKey,BOOL bRedraw = FALSE);
			// 函数 ClearMapDisabledStateKeyString
			// 作用：更新或清除ClearMapDisabledStateKeyString。
			// 参数：无。
			// 返回：没有返回值。
			void ClearMapDisabledStateKeyString();

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

			// 函数 EndEDit
			// 作用：执行EndEDit。
			// 参数：无。
			// 返回：没有返回值。
			void EndEDit();	//结束编辑
			// 函数 EndEDitForFuncCtrlKillFocus
			// 作用：执行EndEDitForFuncCtrlKillFocus。
			// 参数：iCtrlTag：整数。
			// 返回：没有返回值。
			void EndEDitForFuncCtrlKillFocus(int iCtrlTag);

			// 函数 CbTextChanged
			// 作用：执行CbTextChanged。
			// 参数：无。
			// 返回：没有返回值。
			void CbTextChanged();

			// 函数 SetBeShowRowSelectState
			// 作用：设置SetBeShowRowSelectState。
			// 参数：bShowRowSelState：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeShowRowSelectState(BOOL bShowRowSelState,BOOL bRedraw = FALSE);
			// 函数 GetBeShowRowSelectState
			// 作用：读取GetBeShowRowSelectState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShowRowSelectState();

			// 函数 SetBeScrollInsideFrame
			// 作用：设置SetBeScrollInsideFrame。
			// 参数：bScrollInsideFrame：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeScrollInsideFrame(BOOL bScrollInsideFrame,BOOL bRedraw = FALSE);
			// 函数 GetBeScrollInsideFrame
			// 作用：读取GetBeScrollInsideFrame。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeScrollInsideFrame();

			// 函数 GetColorSelectDlgRect
			// 作用：读取GetColorSelectDlgRect。
			// 参数：rcBase；iWndW：整数；iWndH：整数。
			// 返回：返回 CRect。
			CRect GetColorSelectDlgRect(CRect rcBase,int iWndW,int iWndH);

			// 函数 SetRowBkSelectedColor
			// 作用：设置SetRowBkSelectedColor。
			// 参数：clrRowBkSel：颜色。
			// 返回：没有返回值。
			void SetRowBkSelectedColor(COLORREF clrRowBkSel);
			// 函数 GetRowBkSelectedColor
			// 作用：读取GetRowBkSelectedColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetRowBkSelectedColor();

			// 函数 SetRowBkUnSelectedColor
			// 作用：设置SetRowBkUnSelectedColor。
			// 参数：clrRowBkUnSel：颜色。
			// 返回：没有返回值。
			void SetRowBkUnSelectedColor(COLORREF clrRowBkUnSel);
			// 函数 GetRowBkUnSelectedColor
			// 作用：读取GetRowBkUnSelectedColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetRowBkUnSelectedColor();

			// 函数 CalculateFitRowHeight
			// 作用：计算CalculateFitRowHeight。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalculateFitRowHeight();	//计算自动适配的行高
			// 函数 SetAllRowHeight
			// 作用：设置SetAllRowHeight。
			// 参数：iRowH：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetAllRowHeight(int iRowH,BOOL bRedraw = FALSE);	//设置所有的行高

			// 函数 BottomBlankSetAutoFitHeight
			// 作用：执行BottomBlankSetAutoFitHeight。
			// 参数：bLastRowUseRemainder：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int BottomBlankSetAutoFitHeight(BOOL bLastRowUseRemainder = TRUE,BOOL bRedraw = FALSE);	//如果总的行高小于m_rcBody的高度，自动计算行高使m_rcBody完全填充，bLastRowUseRemainder最后一行是否加上余数

			// 函数 SetFuncEditCtrlFont
			// 作用：设置SetFuncEditCtrlFont。
			// 参数：strFtName：字符串；nHeight：整数；nWeight：整数；fontUnitType。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetFuncEditCtrlFont(CString strFtName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL);

			// 函数 RefreshSerialNumber
			// 作用：更新或清除RefreshSerialNumber。
			// 参数：iColId：整数；iIndex：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshSerialNumber(int iColId,int iIndex,BOOL bRedraw = FALSE);

			// 函数 IsCbEndEdit
			// 作用：判断IsCbEndEdit是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsCbEndEdit();
			// 函数 SetCbEndEditState
			// 作用：设置SetCbEndEditState。
			// 参数：bData：是或否。
			// 返回：没有返回值。
			void SetCbEndEditState(BOOL bData);
			// 函数 SetCbSelectItem
			// 作用：设置SetCbSelectItem。
			// 参数：iRowId：整数；iColId：整数；lnkStr。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCbSelectItem(int iRowId,int iColId,CLinkList<CString>& lnkStr);

protected:
			// 函数 RenewHoriScrollPos
			// 作用：执行RenewHoriScrollPos。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RenewHoriScrollPos();	//刷新水平滚动条位置
			// 函数 RenewVertScrollPos
			// 作用：执行RenewVertScrollPos。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RenewVertScrollPos();	//刷新垂直滚动条位置

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
			// 函数 CalcScrollPosStyle2
			// 作用：计算CalcScrollPosStyle2。
			// 参数：无。
			// 返回：没有返回值。
			void CalcScrollPosStyle2();

			// 函数 CheckMaxMinSet
			// 作用：判断CheckMaxMinSet是否成立。
			// 参数：strTemp：字符串；maxMinInfo。
			// 返回：没有返回值。
			void CheckMaxMinSet(CString& strTemp,CMaxMinInfo& maxMinInfo);	//结束编辑后，验证最大最小值设置是否在正确范围内，不在正确范围内则自动修正

public:
	CLinkList<CTitleInfo> m_lnkTitleInfo;	//保存标题信息
	CLinkList<CLinkList<CCellInfo>> m_2LnkCellInfo;	//保存行列内容信息
	CLinkList<CRowInfo> m_lnkRowInfo;	//保存行公共信息

	//水平滚动条
	CMyScrollInfo m_horiScroll;
	CMyScrollInfo m_vertScroll;
	ESCROLLHVCONFLICTMANAGE m_eScrollHVCM;

	CMyNewEdit m_edInput;	//用于编辑单元格信息
	CMyInputCb m_cbCtrl;	//用于下拉选择

	int m_iInputEdTag;	//编辑框标识号
	int m_iInputCbTag;	//下拉选择框标识号

	map<int,CLinkList<int>> m_mapColDisableCtrl;	//记录列之间的禁用控制关系，键为“列下标”,值为“列控制的其它列下标集合"
	map<int,CLinkList<int>> m_mapRowOutsideCtrl;	//记录行对外部关联控件的控制关系，键为“行下标”,值为“行控制的其它控件（列表框）行下标集合"
	map<CString,BOOL> m_mapDisabledStateKeyString;	//记录“获取禁用状态的索引词，键为“关键词”,值为“TRUE/FALSE"

	BOOL m_bCbEndEdit;	//标识下拉选择控件是否终止编辑

protected:
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
	int m_pxHeaderH;	//固定标题高度
	int m_pxFrame;	//边框宽度
	int m_pxRowColLine;	//行列分割线宽度

	BOOL m_bUseFixedHW;	//是否使用固定行高列宽模式
	BOOL m_bGradientHeader;	//标题栏是否使用渐变色背景

	Color m_clrBk;	//主窗口背景色
	Color m_clrHeaderBk;	//标题栏背景颜色
	Color m_clrBodyBk;	//body背景色
	Color m_clrFrame;	//边框颜色
	COLORREF m_clrRowColLine;	//行列分割线颜色
	COLORREF m_clrHeaderText;	//标题栏文字颜色

	Color m_clrGraHeadStart;
	Color m_clrGraHeadEnd;
	BOOL m_bEditable;	//是否可编辑

	COLORREF m_clrHeadBodySepa;	//Header和Body分隔线

	BOOL m_bShowHoriScroll;	//是否显示水平滚动条
	BOOL m_bShowVertScroll;	//是否显示垂直滚动条
	BOOL m_bShowFrameLine;	//是否显示列表框边框线
	BOOL m_bShowRowColLine;	//是否显示水平、垂直分割线
	BOOL m_bSingleSelect;	//标识是否是单选功能
	BOOL m_bAllowCancelRowSelect;	//标识是否允许取消行选中

	BOOL m_bTellParentRowSelChange;	//类表框选中行改变是否通知父窗口

	CRect m_rcLst;
	CRect m_rcHeader;
	CRect m_rcBody;

	int m_totalColW;	//所有列的宽度之和
	int m_totalRowH;	//所有行的高度之和

	int m_cdcW;	//记录显示列的总宽度（包括 左侧、右侧缩进像素） CDC Width
	int m_cdcH;	//记录显示行的总高度（包括 顶部、底部缩进像素） CDC Height

	CDotPosInfo m_curDotPosInfo;	//记录最近一次点击的行列信息
	CDotPosInfo m_preDotPosInfo;	//记录前一个点击的行列信息
	CLinkList<CDotPosInfo> m_lnkHistoryDotPosInfo;	//记录最近N个点击的行列信息

	CFont m_fontSetHeader;
	CFont m_fontSetTitle;
	LOGFONT m_logFontHeader;
	LOGFONT m_logFontTitle;

	Image m_image;
	Image m_img2;

	CRowColEditInfo m_rowColEditInfo;	//记录当前的编辑行列信息
	CRowColEditInfo m_preRowColEditInfo;	//记录上一次的编辑行列信息

	CString m_strLstTitle;	//列表框标题

	//圆角矩形样式参数
	BOOL m_bRoundRectStyle;	//标识是否使用圆角矩形样式
	COLORREF m_clrFourAngleBk;	//圆角矩形以外的背景色
	int m_iRoundAngleSize;	//圆角大小
	Color m_clrIndepent;	//独立第三方颜色，用于支持局部透明

	CColorSelectDlg m_clrSelDlg;

	BOOL m_bShowRowSelState;	//标识是否显示行选中状态

	BOOL m_bScrollInsideFrame;	//标识滚动条是否在边框之内

	COLORREF m_clrRowBkSel;	//选中行背景色
	COLORREF m_clrRowBkUnSel;	//未选中行背景色

	BOOL m_bLeftBtDown;	//记录左键按下、弹起是否成对发生在控件内部

	BOOL m_bUseLargeChkIcon;	//是否使用放大的CheckBox图标

	BOOL m_bUseFixedIdpd;	//浮点数是否使用固定小数位数
};





