// 【交接】 GeneralPcr\MySegDlg.h
// 作用：MySegDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CMySegDlg、DECLARE_MESSAGE_MAP、OnPaint、DrawSegment、DrawHoriScroll、DrawVertScroll、DrawHoriScrollStyle2。
#pragma once

#include "FontSet.h"
#include "LinkList.h"
#include "MyScrollInfo.h"
#include "SegItemInfo.h"
#include "LinkList.h"
#include "SegDotPosInfo.h"
#include "SegStepRange.h"
#include "MySegDlgParam.h"
#include "MyStepEditDlg.h"
#include "MyNewEdit.h"
#include <GdiPlus.h>

//荧光采集图标标识
typedef enum CollectFluTagType{
	ECFTT_TRIANGLE,ECFTT_CAMERA
}ECOLLECTFLUTAGTYPE;

class CMySegDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMySegDlg。
	// 返回：没有返回值。
	DECLARE_DYNAMIC(CMySegDlg)
	
public:
	// 函数 CMySegDlg
	// 作用：执行CMySegDlg。
	// 参数：无。
	// 返回：没有返回值。
	CMySegDlg();
	// 函数 ~CMySegDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CMySegDlg();
	
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
			// 函数 DrawSegment
			// 作用：绘制DrawSegment。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawSegment(CDC* pDC);
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
			// 函数 DrawGradientData
			// 作用：绘制DrawGradientData。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawGradientData(CDC* pDC);

	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
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
	
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
	// 函数 OnKeyDown
	// 作用：响应 Windows 或自定义消息 OnKeyDown。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 OnGetDlgCode
	// 作用：响应 Windows 或自定义消息 OnGetDlgCode。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg UINT OnGetDlgCode();
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

	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL PreTranslateMessage(MSG* pMsg);

			// 函数 FindDotPosInfo
			// 作用：执行FindDotPosInfo。
			// 参数：pt。
			// 返回：返回 CSegDotPosInfo。
			CSegDotPosInfo FindDotPosInfo(CPoint pt); 
			// 函数 PixelHeightToTem
			// 作用：执行PixelHeightToTem。
			// 参数：pixelH。
			// 返回：返回一个小数。
			float PixelHeightToTem(int pixelH);

			// 函数 UpdateSegStepRange
			// 作用：更新或清除UpdateSegStepRange。
			// 参数：segId；stepId。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UpdateSegStepRange(int segId,int stepId);

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

			// 函数 AddSegment
			// 作用：创建或加入AddSegment。
			// 参数：无。
			// 返回：没有返回值。
			void AddSegment();
			// 函数 AddStep
			// 作用：创建或加入AddStep。
			// 参数：segId；bMelt：是或否。
			// 返回：没有返回值。
			void AddStep(int segId,BOOL bMelt = FALSE);
			// 函数 SetSegmentStepSelectState
			// 作用：设置SetSegmentStepSelectState。
			// 参数：bCtrlClicked：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSegmentStepSelectState(BOOL bCtrlClicked,BOOL bRedraw = FALSE);
			// 函数 SetSegmentSelectState
			// 作用：设置SetSegmentSelectState。
			// 参数：bCtrlClicked：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSegmentSelectState(BOOL bCtrlClicked,BOOL bRedraw = FALSE);
			// 函数 SetStepSelectState
			// 作用：设置SetStepSelectState。
			// 参数：bCtrlClicked：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetStepSelectState(BOOL bCtrlClicked,BOOL bRedraw = FALSE);
			// 函数 SetSegmentFullSelectState
			// 作用：设置SetSegmentFullSelectState。
			// 参数：bSel：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSegmentFullSelectState(BOOL bSel,BOOL bRedraw = TRUE);

			// 函数 SetDefaultSingleSelectStep
			// 作用：设置SetDefaultSingleSelectStep。
			// 参数：iSegIndex：整数；iStepIndex：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetDefaultSingleSelectStep(int iSegIndex,int iStepIndex,BOOL bRedraw = FALSE);	//没有步骤被选中的时候，设置默认选中的步骤

			// 函数 InsertSegment
			// 作用：创建或加入InsertSegment。
			// 参数：insetSel。
			// 返回：没有返回值。
			void InsertSegment(EINSERTSELECT insetSel);
			// 函数 InsertStep
			// 作用：创建或加入InsertStep。
			// 参数：insetSel。
			// 返回：没有返回值。
			void InsertStep(EINSERTSELECT insetSel);
			// 函数 DeleteSelectedItem
			// 作用：更新或清除DeleteSelectedItem。
			// 参数：无。
			// 返回：没有返回值。
			void DeleteSelectedItem();
			// 函数 Clear
			// 作用：更新或清除Clear。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void Clear(BOOL bRedraw = TRUE);

			// 函数 DeleteMeltSeg
			// 作用：更新或清除DeleteMeltSeg。
			// 参数：无。
			// 返回：没有返回值。
			void DeleteMeltSeg();
			// 函数 AddMeltSegIfNoMeltSegExist
			// 作用：创建或加入AddMeltSegIfNoMeltSegExist。
			// 参数：无。
			// 返回：没有返回值。
			void AddMeltSegIfNoMeltSegExist();
			// 函数 SetDefaultAmlProgramForProject
			// 作用：设置SetDefaultAmlProgramForProject。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultAmlProgramForProject();
			// 函数 SetDefaultAmlProgramForProject2
			// 作用：设置SetDefaultAmlProgramForProject2。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultAmlProgramForProject2();
			// 函数 SetDefaultMeltProgramForProject
			// 作用：设置SetDefaultMeltProgramForProject。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultMeltProgramForProject();
			// 函数 SetDefaultAbsoluteQuantification
			// 作用：设置SetDefaultAbsoluteQuantification。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultAbsoluteQuantification();	//设置绝对定量默认实验流程
			// 函数 SetDefaultStandardMeltingCurve
			// 作用：设置SetDefaultStandardMeltingCurve。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultStandardMeltingCurve();	//设置标准熔解曲线默认实验流程

			// 函数 SetBeMonitorFunc
			// 作用：设置SetBeMonitorFunc。
			// 参数：beMonitorFunc；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeMonitorFunc(BOOL beMonitorFunc,BOOL bRedraw = FALSE);
			// 函数 GetBeMonitorFunc
			// 作用：读取GetBeMonitorFunc。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeMonitorFunc();
			// 函数 SetSegmentInfo
			// 作用：设置SetSegmentInfo。
			// 参数：lnkSegItemInfo；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetSegmentInfo(CLinkList<CSegItemInfo>& lnkSegItemInfo,BOOL bRedraw = FALSE);
			// 函数 GetSegmentInfo
			// 作用：读取GetSegmentInfo。
			// 参数：lnkSegItemInfo。
			// 返回：返回是或否。
			BOOL GetSegmentInfo(CLinkList<CSegItemInfo>& lnkSegItemInfo);

			// 函数 SetBeEditable
			// 作用：设置SetBeEditable。
			// 参数：bEditable：是或否。
			// 返回：没有返回值。
			void SetBeEditable(BOOL bEditable);
			// 函数 GetBeEditable
			// 作用：读取GetBeEditable。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeEditable();

			// 函数 UpdateCurSelectStepCycleInfo
			// 作用：更新或清除UpdateCurSelectStepCycleInfo。
			// 参数：item；sub；cycle；bSelState：是或否；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL UpdateCurSelectStepCycleInfo(int item,int sub,int cycle,BOOL bSelState,BOOL bRedraw = FALSE);
			// 函数 ResetCurItemSubCycle
			// 作用：更新或清除ResetCurItemSubCycle。
			// 参数：无。
			// 返回：没有返回值。
			void ResetCurItemSubCycle();

			// 函数 EditStep
			// 作用：执行EditStep。
			// 参数：iSegId：整数；iStepId：整数。
			// 返回：没有返回值。
			void EditStep(int iSegId,int iStepId);
			// 函数 EditSegment
			// 作用：执行EditSegment。
			// 参数：iSegId：整数。
			// 返回：没有返回值。
			void EditSegment(int iSegId);

			// 函数 GetBeHaveGetDataStep
			// 作用：读取GetBeHaveGetDataStep。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeHaveGetDataStep();	//判断所有程序段是否已经存在扩增步骤
			// 函数 GetSegmentBeHaveGetDataStep
			// 作用：读取GetSegmentBeHaveGetDataStep。
			// 参数：iSegId：整数。
			// 返回：返回是或否。
			BOOL GetSegmentBeHaveGetDataStep(int iSegId);	//判断单个程序段中是否已经存在扩增步骤

			// 函数 GetBeHaveAmlCollectStepExcept
			// 作用：读取GetBeHaveAmlCollectStepExcept。
			// 参数：iSegId：整数；iStepId：整数。
			// 返回：返回是或否。
			BOOL GetBeHaveAmlCollectStepExcept(int iSegId,int iStepId);	//判断除了特定步骤，是否已经存在扩增步骤
			// 函数 GetBeHaveMeltCollectStepExcept
			// 作用：读取GetBeHaveMeltCollectStepExcept。
			// 参数：iSegId：整数；iStepId：整数。
			// 返回：返回是或否。
			BOOL GetBeHaveMeltCollectStepExcept(int iSegId,int iStepId);	//判断除了特定步骤，是否已经存在熔曲步骤

			// 函数 SetScrollArrowWH
			// 作用：设置SetScrollArrowWH。
			// 参数：iWidth：整数；iHeight：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetScrollArrowWH(int iWidth,int iHeight,BOOL bRedraw = FALSE);

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

			// 函数 SetSegStepName
			// 作用：设置SetSegStepName。
			// 参数：iStartSegIndex：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetSegStepName(int iStartSegIndex,BOOL bRedraw = FALSE);	//自动设置程序段和步骤名称

			// 函数 SetCollectFluTagType
			// 作用：设置SetCollectFluTagType。
			// 参数：eType；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCollectFluTagType(ECOLLECTFLUTAGTYPE eType,BOOL bRedraw = FALSE);
			// 函数 GetCollectFluTagType
			// 作用：读取GetCollectFluTagType。
			// 参数：无。
			// 返回：返回 ECOLLECTFLUTAGTYPE。
			ECOLLECTFLUTAGTYPE GetCollectFluTagType();

			// 函数 SetShieldGradientSetState
			// 作用：设置SetShieldGradientSetState。
			// 参数：bData：是或否。
			// 返回：没有返回值。
			void SetShieldGradientSetState(BOOL bData);
			// 函数 GetShieldGradientSetState
			// 作用：读取GetShieldGradientSetState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShieldGradientSetState();

			// 函数 SetTemperatureRateShowState
			// 作用：设置SetTemperatureRateShowState。
			// 参数：bData：是或否。
			// 返回：没有返回值。
			void SetTemperatureRateShowState(BOOL bData);
			// 函数 GetTemperatureRateShowState
			// 作用：读取GetTemperatureRateShowState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetTemperatureRateShowState();
			
			// 函数 GetStepIndexAt
			// 作用：读取GetStepIndexAt。
			// 参数：iSegId：整数；iStepId：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetStepIndexAt(int iSegId,int iStepId);	//获取当前步骤是流程的第几个步骤
			// 函数 SetSegmentSetpShow
			// 作用：设置SetSegmentSetpShow。
			// 参数：iSegId：整数；iStepId：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSegmentSetpShow(int iSegId,int iStepId,BOOL bRedraw = FALSE);

			// 函数 SetFuncEditCtrlFont
			// 作用：设置SetFuncEditCtrlFont。
			// 参数：strFtName：字符串；nHeight：整数；nWeight：整数；fontUnitType。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetFuncEditCtrlFont(CString strFtName,int nHeight,int nWeight = FW_NORMAL,FONT_UNIT_TYPE fontUnitType = TYPE_PIXEL);

			// 函数 SetGradientInfoUseState
			// 作用：设置SetGradientInfoUseState。
			// 参数：bUse：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetGradientInfoUseState(BOOL bUse,BOOL bRedraw = FALSE);
			// 函数 GetGradientInfoUseState
			// 作用：读取GetGradientInfoUseState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetGradientInfoUseState();

			// 函数 SetGradientString
			// 作用：设置SetGradientString。
			// 参数：strData：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetGradientString(CString strData,BOOL bRedraw = FALSE);
			// 函数 SetColumnString
			// 作用：设置SetColumnString。
			// 参数：strData：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetColumnString(CString strData,BOOL bRedraw = FALSE);
			// 函数 SetSegmentString
			// 作用：设置SetSegmentString。
			// 参数：strData：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetSegmentString(CString strData,BOOL bRedraw = FALSE);
			// 函数 SetStepString
			// 作用：设置SetStepString。
			// 参数：strData：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetStepString(CString strData,BOOL bRedraw = FALSE);
			// 函数 SetRangeString
			// 作用：设置SetRangeString。
			// 参数：strData：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRangeString(CString strData,BOOL bRedraw = FALSE);

			// 函数 IsSelectMultiSegment
			// 作用：判断IsSelectMultiSegment是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsSelectMultiSegment();
			// 函数 IsOnlyOneSegmentSelected
			// 作用：判断IsOnlyOneSegmentSelected是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsOnlyOneSegmentSelected();
			// 函数 GetSelectedSegmentCount
			// 作用：读取GetSelectedSegmentCount。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSelectedSegmentCount();
			// 函数 GetFirstSelectedSegmentId
			// 作用：读取GetFirstSelectedSegmentId。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetFirstSelectedSegmentId();

			// 函数 GetGradientInfoString
			// 作用：读取GetGradientInfoString。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetGradientInfoString();

			// 函数 CorrectSegmentName
			// 作用：执行CorrectSegmentName。
			// 参数：无。
			// 返回：没有返回值。
			void CorrectSegmentName();
			// 函数 CorrectSegmengIndex
			// 作用：执行CorrectSegmengIndex。
			// 参数：无。
			// 返回：没有返回值。
			void CorrectSegmengIndex();

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

			// 函数 CalcSegStepToShow
			// 作用：计算CalcSegStepToShow。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CalcSegStepToShow();
			// 函数 GetStepNum
			// 作用：读取GetStepNum。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetStepNum();
			// 函数 GetStepNum
			// 作用：读取GetStepNum。
			// 参数：segStart；segEnd。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetStepNum(int segStart,int segEnd);
			// 函数 StartEndShowColToSegStepRange
			// 作用：执行StartEndShowColToSegStepRange。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int StartEndShowColToSegStepRange();

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

			// 函数 InitHoriScrollParam
			// 作用：初始化InitHoriScrollParam。
			// 参数：无。
			// 返回：没有返回值。
			void InitHoriScrollParam();
			// 函数 InitVertScrollParam
			// 作用：初始化InitVertScrollParam。
			// 参数：无。
			// 返回：没有返回值。
			void InitVertScrollParam();

			// 函数 GetSegLastStepTem
			// 作用：读取GetSegLastStepTem。
			// 参数：segId；stepId。
			// 返回：返回一个小数。
			float GetSegLastStepTem(int segId,int stepId);
			// 函数 GetMeltSegStartEndTemperature
			// 作用：读取GetMeltSegStartEndTemperature。
			// 参数：dStartTem：小数；dEndTem：小数。
			// 返回：返回是或否。
			BOOL GetMeltSegStartEndTemperature(double& dStartTem,double& dEndTem);
			// 函数 UpdateSegStepScrollPosInfo
			// 作用：更新或清除UpdateSegStepScrollPosInfo。
			// 参数：无。
			// 返回：没有返回值。
			void UpdateSegStepScrollPosInfo();
			// 函数 EndEdit
			// 作用：执行EndEdit。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int EndEdit();

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

protected:
			// 函数 IsExistGradientStep
			// 作用：判断IsExistGradientStep是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsExistGradientStep();
			// 函数 IsShowGradientData
			// 作用：判断IsShowGradientData是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsShowGradientData();
			// 函数 GradientSetChanged
			// 作用：执行GradientSetChanged。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GradientSetChanged(BOOL bRedraw);

public:
	CMyNewEdit m_edSegInfo;

	//字体变量
	CFontSet m_fontGeneral;
	CFontSet m_fontStepTag;
	CFontSet m_fontSegTag;
	
	int m_priorItem;	//标识前一个segment（相对于当前正在运行的segment），默认为-1
	int m_priorStep;	//标识前一个step（相对于当前正在运行的step），默认为-1
	int m_curRunCycle;	//记录当前运行的是单个segment中第几个循环
	int m_curRunItem;	//记录当前运行的是哪个segment
	int m_curRunStep;	//记录当前运行的是哪个step

	CLinkList<CSegItemInfo> m_lnkSegItemInfo;

	//水平滚动条
	CMyScrollInfo m_horiScroll;
	CMyScrollInfo m_vertScroll;

	// 函数 GetHeaderHeight
	// 作用：读取GetHeaderHeight。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetHeaderHeight() { return m_pxHeaderH; }
	// 函数 SetHeaderHeight
	// 作用：设置SetHeaderHeight。
	// 参数：iHeight：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetHeaderHeight(int iHeight) { m_pxHeaderH = iHeight; }

protected:
	double m_dMaxTem;	//可设置最大温度值
	double m_dMinTem;	//可设置的最低温度值
	int m_iMaxCycleNum;	//可设置的最大循环数
	int m_iMinCycleNum;	//可设置的最小循环数
	int m_iMaxDelaySec;	//可设置的最大延时时间
	int m_iMinDelaySec;	//可设置的最小延时时间

	BOOL m_bShieldGradientSet;	//是否屏蔽梯度设置项
	BOOL m_bShowTemRate;	//是否显示升降温速率

private:
	int m_rowNum;
	int m_colNum;

	int m_rowIdStartShow;
	int m_rowIdEndShow;
	int m_ssColLeftIndent;	//起始显示列左侧缩进
	int m_esColRightIndent;	//终止显示列左侧缩进
	int m_ssRowTopIndent;	//起始显示行顶部缩进
	int m_esRowBottomIndent;	//终止显示列底部缩进

	int m_pxRowH;	//固定行高 
	int m_pxColW;	//固定列宽
	int m_pxHeaderH;	//固定标题高度
	BOOL m_bUseFixedHW;	//是否使用固定行高列宽模式

	Color m_clrGraHeadStart;
	Color m_clrGraHeadEnd;
	BOOL m_bEditable;	//是否可编辑

	BOOL m_bShowHoriScroll;	//是否显示水平滚动条
	BOOL m_bShowVertScroll;	//是否显示垂直滚动条

	CRect m_rcLst;
	CRect m_rcHeader;
	CRect m_rcBody;
	CRect m_rcGrad;	//梯度信息显示区域

	int m_totalColW;	//所有列的宽度之和
	int m_totalRowH;	//所有行的高度之和

	int m_cdcW;	//记录显示列的总宽度（包括 左侧、右侧缩进像素） CDC Width
	int m_cdcH;	//记录显示行的总高度（包括 顶部、底部缩进像素） CDC Height

	ESCROLLHVCONFLICTMANAGE m_eScrollHVCM;

	COLORREF m_clrHeaderBk;
	COLORREF m_clrBodyBk;

	int m_colIdStartShow;
	int m_colIdEndShow;

	CSegStepRange m_segStepRange;	//从零开始
	CSegDotPosInfo m_segDotPosInfo;	//实时记录鼠标当前位置信息
	CSegDotPosInfo m_preEditDotInfo;	//记录编辑框弹出时的位置信息,用于在编辑框失去焦点时正确保存编辑框内容

	int m_stepWidth;	//步骤项宽度

	BOOL m_bMonitorFunc;	//标识是否用于监控
	BOOL m_bEditDataProcessed;	//标识编辑框数据是否已经获取，防止（编辑框）Enter和失去焦点响应函数重复处理

	int m_visibleStepNum;	//页面可见的最大步骤个数

	Gdiplus::Image m_image;
	Gdiplus::Image m_imgTriangle;	//三角形标识
	Gdiplus::Image m_imgCamera;	//相机标识
	Gdiplus::Image m_imageMelt;	//熔曲类型背景图标
	Gdiplus::Image m_imgAllPtIcon;	//熔曲段AllPoint模式图标

	int m_roundHeight;	//温度、延时时间背景图中小圆圈高度

	BOOL m_bSelMoveStart;	//标识是否选中温度线段

	CPoint m_ptPre;

	float m_minTem;
	float m_maxTem;
	float m_oneTemH;	//1℃对应的像素高度

	int m_frameW;	//边框宽度

	CMySegDlgParam m_segParam;

	COLORREF m_clrFourAngleBk;	//圆角矩形以外的背景色
	int m_iRoundAngleSize;	//圆角大小
	Color m_clrIndepent;	//独立第三方颜色，用于支持局部透明

	ECOLLECTFLUTAGTYPE m_eCollectFluTagType;	//标识采集荧光或者不采集荧光的 图标类型

	CString m_strSegDefName;	//程序段默认名称
	CString m_strStepDefName;	//步骤默认名称

	int m_iGradInfoW;	//梯度信息显示宽度
	CLinkList<double> m_lnkGradData;
	BOOL m_bHaveGrad;	//是否包含梯度信息
	BOOL m_bUseGradInfo;	//是否使用梯度信息
	CString m_strGrad;
	CString m_strCol;
	CString m_strSeg;
	CString m_strStep;
	CString m_strRange;
};


