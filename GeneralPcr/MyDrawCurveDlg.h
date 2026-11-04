// 【交接】 GeneralPcr\MyDrawCurveDlg.h
// 作用：MyDrawCurveDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CMyDrawCurveDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnInitDialog、OnPaint、DrawThreLine、CurveToPic。
#pragma once

#include "MyPoint.h"
#include "MyButton.h"
#include "MyStatic.h"
#include "LinkList.h"
#include "LineInfo.h"
#include "TubeInfo.h"
#include "ChanThreInfo.h"
#include "LinearFitData.h"
#include "FloatDlg.h"
#include "resource.h"
#include<vector>

using namespace std;
// CMyDrawCurveDlg dialog 


#define WM_THRELINESTOPMOVE	WM_USER + 6009	//释放阈值线，通知父窗口
#define WM_THRECHANGED	WM_USER + 6010	//阈值线被拖动，通知父窗口

typedef enum CurveType{
	STDLINE = 1,GENERALCURVE
}ECURVETYPE;

typedef enum XAxisMode{
	NORMALXAXIS = 1,TIMERXAXIS
}EXAXISMODE;

class CMyDrawCurveDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMyDrawCurveDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CMyDrawCurveDlg)

public:
	// 函数 CMyDrawCurveDlg
	// 作用：执行CMyDrawCurveDlg。
	// 参数：pParent：指针，指向调用方传入的对象；beFilter。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CMyDrawCurveDlg(CWnd* pParent = NULL,BOOL beFilter = FALSE);   // standard constructor
	// 函数 ~CMyDrawCurveDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CMyDrawCurveDlg();

// Dialog Data
	enum { IDD = IDD_MIDDLEDLG};

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
	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();

private:
	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();
			// 函数 DrawThreLine
			// 作用：绘制DrawThreLine。
			// 参数：pDC：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DrawThreLine(CDC* pDC);

public:
			// 函数 CurveToPic
			// 作用：执行CurveToPic。
			// 参数：vecCurMonitorChan；strPicName：字符串。
			// 返回：返回是或否。
			BOOL CurveToPic(vector<BOOL>& vecCurMonitorChan,CString strPicName);
			// 函数 CurveToPic
			// 作用：执行CurveToPic。
			// 参数：strPicName：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CurveToPic(CString strPicName);
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags,CPoint point);
	// 函数 OnLButtonUp
	// 作用：松开鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonUp(UINT nFlags,CPoint point);
	// 函数 OnLButtonDblClk
	// 作用：双击鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	// 函数 OnRButtonDown
	// 作用：按下鼠标右键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// 函数 OnMouseMove
	// 作用：鼠标在窗口上移动。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnMouseMove(UINT nFlags,CPoint point);
	// 函数 OnMouseWheel
	// 作用：转动鼠标滚轮。
	// 参数：nFlags：整数；zDelta；pt。
	// 返回：返回是或否。
	afx_msg BOOL OnMouseWheel(UINT nFlags,short zDelta,CPoint pt);
	// 函数 OnSize
	// 作用：窗口大小变化时重新摆放控件。
	// 参数：nType：整数；cx；cy。
	// 返回：没有返回值。
	afx_msg void OnSize(UINT nType, int cx, int cy);
			
			// 函数 SetHoriStepNums
			// 作用：设置SetHoriStepNums。
			// 参数：horiStepNums；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriStepNums(double horiStepNums,BOOL bRedraw = FALSE);
			// 函数 GetHoriStepNums
			// 作用：读取GetHoriStepNums。
			// 参数：无。
			// 返回：返回一个小数。
			double GetHoriStepNums();
			// 函数 SetVertStepNums
			// 作用：设置SetVertStepNums。
			// 参数：vertStepNums；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertStepNums(double vertStepNums,BOOL bRedraw = FALSE);
			// 函数 GetVertStepNums
			// 作用：读取GetVertStepNums。
			// 参数：无。
			// 返回：返回一个小数。
			double GetVertStepNums();
			// 函数 SetHoriStep
			// 作用：设置SetHoriStep。
			// 参数：horiStep；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriStep(double horiStep,BOOL bRedraw = FALSE);
			// 函数 GetHoriStep
			// 作用：读取GetHoriStep。
			// 参数：无。
			// 返回：返回一个小数。
			double GetHoriStep();
			// 函数 SetVertStep
			// 作用：设置SetVertStep。
			// 参数：vertStep；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertStep(double vertStep,BOOL bRedraw = FALSE);
			// 函数 GetVertStep
			// 作用：读取GetVertStep。
			// 参数：无。
			// 返回：返回一个小数。
			double GetVertStep();

			// 函数 SetHoriAxisParam
			// 作用：设置SetHoriAxisParam。
			// 参数：iStart：整数；iEnd：整数；iHoriStep：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetHoriAxisParam(int iStart,int iEnd,int iHoriStep,BOOL bRedraw = FALSE);	//设置X轴参数，防止横坐标标识不明确

			// 函数 SetHoriStartValue
			// 作用：设置SetHoriStartValue。
			// 参数：horiStartValue；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriStartValue(double horiStartValue,BOOL bRedraw = FALSE);
			// 函数 GetHoriStartValue
			// 作用：读取GetHoriStartValue。
			// 参数：无。
			// 返回：返回一个小数。
			double GetHoriStartValue();
			// 函数 SetHoriEndValue
			// 作用：设置SetHoriEndValue。
			// 参数：horiEndValue；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriEndValue(double horiEndValue,BOOL bRedraw = FALSE);
			// 函数 GetHoriEndValue
			// 作用：读取GetHoriEndValue。
			// 参数：无。
			// 返回：返回一个小数。
			double GetHoriEndValue();
			// 函数 SetVertStartValue
			// 作用：设置SetVertStartValue。
			// 参数：vertStartValue；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertStartValue(double vertStartValue,BOOL bRedraw = FALSE);
			// 函数 GetVertStartValue
			// 作用：读取GetVertStartValue。
			// 参数：无。
			// 返回：返回一个小数。
			double GetVertStartValue();
			// 函数 SetVertEndValue
			// 作用：设置SetVertEndValue。
			// 参数：vertEndValue；bRedraw：是或否；bUseMinOfMax：是或否。
			// 返回：没有返回值。
			void SetVertEndValue(double vertEndValue,BOOL bRedraw = FALSE,BOOL bUseMinOfMax = TRUE);
			// 函数 GetVertEndValue
			// 作用：读取GetVertEndValue。
			// 参数：无。
			// 返回：返回一个小数。
			double GetVertEndValue();
			
			// 函数 SetHoriStrColor
			// 作用：设置SetHoriStrColor。
			// 参数：horiStrClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriStrColor(COLORREF horiStrClr,BOOL bRedraw = FALSE);
			// 函数 GetHoriStrColor
			// 作用：读取GetHoriStrColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetHoriStrColor();
			// 函数 SetHoriLineColor
			// 作用：设置SetHoriLineColor。
			// 参数：horiLineClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriLineColor(COLORREF horiLineClr,BOOL bRedraw = FALSE);
			// 函数 GetHoriLineColor
			// 作用：读取GetHoriLineColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetHoriLineColor();
			// 函数 SetVertStrColor
			// 作用：设置SetVertStrColor。
			// 参数：vertStrClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertStrColor(COLORREF vertStrClr,BOOL bRedraw = FALSE);
			// 函数 GetVertStrColor
			// 作用：读取GetVertStrColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetVertStrColor();
			// 函数 SetVertLineColor
			// 作用：设置SetVertLineColor。
			// 参数：vertLineClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertLineColor(COLORREF vertLineClr,BOOL bRedraw = FALSE);
			// 函数 GetVertLineColor
			// 作用：读取GetVertLineColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetVertLineColor();
			// 函数 SetHoriBaseLineColor
			// 作用：设置SetHoriBaseLineColor。
			// 参数：horiBaseLineClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriBaseLineColor(COLORREF horiBaseLineClr,BOOL bRedraw = FALSE);
			// 函数 GetHoriBaseLineColor
			// 作用：读取GetHoriBaseLineColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetHoriBaseLineColor();

			// 函数 SetVertBaseLineColor
			// 作用：设置SetVertBaseLineColor。
			// 参数：vertBaseLineClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertBaseLineColor(COLORREF vertBaseLineClr,BOOL bRedraw = FALSE);
			// 函数 GetVertBaseLineColor
			// 作用：读取GetVertBaseLineColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetVertBaseLineColor();

			// 函数 SetXSeparatorColor
			// 作用：设置SetXSeparatorColor。
			// 参数：xSptClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetXSeparatorColor(COLORREF xSptClr,BOOL bRedraw = FALSE);
			// 函数 GetXSeparatorColor
			// 作用：读取GetXSeparatorColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetXSeparatorColor();
			// 函数 SetRoundTagInnerColor
			// 作用：设置SetRoundTagInnerColor。
			// 参数：roundTagInnerClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRoundTagInnerColor(COLORREF roundTagInnerClr,BOOL bRedraw = FALSE);
			// 函数 GetRoundTagInnerColor
			// 作用：读取GetRoundTagInnerColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetRoundTagInnerColor();
			// 函数 SetRoundTagLineWidth
			// 作用：设置SetRoundTagLineWidth。
			// 参数：roundTagLineWidth；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetRoundTagLineWidth(int roundTagLineWidth,BOOL bRedraw = FALSE);
			// 函数 GetRoundTagLineWidth
			// 作用：读取GetRoundTagLineWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetRoundTagLineWidth();
			// 函数 SetRoundTagLineRadius
			// 作用：设置SetRoundTagLineRadius。
			// 参数：roundTagLineRadius；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetRoundTagLineRadius(int roundTagLineRadius,BOOL bRedraw = FALSE);
			// 函数 GetRoundTagLineRadius
			// 作用：读取GetRoundTagLineRadius。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetRoundTagLineRadius();
			// 函数 SetHoriLineWidth
			// 作用：设置SetHoriLineWidth。
			// 参数：horiLineWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriLineWidth(int horiLineWidth,BOOL bRedraw = FALSE);
			// 函数 GetHoriLineWidth
			// 作用：读取GetHoriLineWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetHoriLineWidth();
			// 函数 SetVertLineWidth
			// 作用：设置SetVertLineWidth。
			// 参数：vertLineWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertLineWidth(int vertLineWidth,BOOL bRedraw = FALSE);
			// 函数 GetVertLineWidth
			// 作用：读取GetVertLineWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetVertLineWidth();
			// 函数 SetHoriSptWidth
			// 作用：设置SetHoriSptWidth。
			// 参数：horiSptWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriSptWidth(int horiSptWidth,BOOL bRedraw = FALSE);
			// 函数 GetHoriSptWidth
			// 作用：读取GetHoriSptWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetHoriSptWidth();
			// 函数 SetCurveWidth
			// 作用：设置SetCurveWidth。
			// 参数：curveWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCurveWidth(int curveWidth,BOOL bRedraw = FALSE);
			// 函数 GetCurveWidth
			// 作用：读取GetCurveWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCurveWidth();
			// 函数 SetHoriBaseLineWidth
			// 作用：设置SetHoriBaseLineWidth。
			// 参数：horiBaseLineWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHoriBaseLineWidth(int horiBaseLineWidth,BOOL bRedraw = FALSE);
			// 函数 GetHoriBaseLineWidth
			// 作用：读取GetHoriBaseLineWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetHoriBaseLineWidth();
			// 函数 SetVertBaseLineWidth
			// 作用：设置SetVertBaseLineWidth。
			// 参数：vertBaseLineWidth；bRedraw：是或否。
			// 返回：没有返回值。
			void SetVertBaseLineWidth(int vertBaseLineWidth,BOOL bRedraw = FALSE);
			// 函数 GetVertBaseLineWidth
			// 作用：读取GetVertBaseLineWidth。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetVertBaseLineWidth();
			// 函数 SetShowVertLine
			// 作用：设置SetShowVertLine。
			// 参数：bShowVertLine：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetShowVertLine(BOOL bShowVertLine,BOOL bRedraw = FALSE);
			// 函数 GetShowVertLine
			// 作用：读取GetShowVertLine。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShowVertLine();
			// 函数 SetShowHoriLine
			// 作用：设置SetShowHoriLine。
			// 参数：bShowHoriLine：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetShowHoriLine(BOOL bShowHoriLine,BOOL bRedraw = FALSE);
			// 函数 GetShowHoriLine
			// 作用：读取GetShowHoriLine。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShowHoriLine();
			// 函数 SetShowHoriSeparator
			// 作用：设置SetShowHoriSeparator。
			// 参数：bShowHoriSpt：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetShowHoriSeparator(BOOL bShowHoriSpt,BOOL bRedraw = FALSE);
			// 函数 GetShowHoriSeparator
			// 作用：读取GetShowHoriSeparator。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShowHoriSeparator();
			// 函数 SetShowRoundTag
			// 作用：设置SetShowRoundTag。
			// 参数：bShowRoundTag：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetShowRoundTag(BOOL bShowRoundTag,BOOL bRedraw = FALSE);
			// 函数 GetShowRoundTag
			// 作用：读取GetShowRoundTag。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShowRoundTag();

			// 函数 SetShowVertBaseLine
			// 作用：设置SetShowVertBaseLine。
			// 参数：bShowVertBaseLine：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetShowVertBaseLine(BOOL bShowVertBaseLine,BOOL bRedraw = FALSE);
			// 函数 GetShowVertBaseLine
			// 作用：读取GetShowVertBaseLine。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShowVertBaseLine();

			// 函数 SetShowHoriBaseLine
			// 作用：设置SetShowHoriBaseLine。
			// 参数：bShowHoriBaseLine：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetShowHoriBaseLine(BOOL bShowHoriBaseLine,BOOL bRedraw = FALSE);
			// 函数 GetShowHoriBaseLine
			// 作用：读取GetShowHoriBaseLine。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetShowHoriBaseLine();
			// 函数 SetHoriStringOutStep
			// 作用：设置SetHoriStringOutStep。
			// 参数：horiStrOutStep；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetHoriStringOutStep(int horiStrOutStep,BOOL bRedraw = FALSE);
			// 函数 GetHoriStringOutStep
			// 作用：读取GetHoriStringOutStep。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int  GetHoriStringOutStep();
			// 函数 SetVertStringOutStep
			// 作用：设置SetVertStringOutStep。
			// 参数：vertStrOutStep；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetVertStringOutStep(int vertStrOutStep,BOOL bRedraw = FALSE);
			// 函数 GetVertStringOutStep
			// 作用：读取GetVertStringOutStep。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int  GetVertStringOutStep();
			// 函数 SetHoriDecimalPointLength
			// 作用：设置SetHoriDecimalPointLength。
			// 参数：horiDecPtLen；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetHoriDecimalPointLength(UINT horiDecPtLen,BOOL bRedraw = FALSE);
			// 函数 GetHoriDecimalPointLength
			// 作用：读取GetHoriDecimalPointLength。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetHoriDecimalPointLength();
			// 函数 SetVertDecimalPointLength
			// 作用：设置SetVertDecimalPointLength。
			// 参数：horiDecPtLen；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetVertDecimalPointLength(UINT horiDecPtLen,BOOL bRedraw = FALSE);
			// 函数 GetVertDecimalPointLength
			// 作用：读取GetVertDecimalPointLength。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			UINT GetVertDecimalPointLength();

	// 函数 GetChannelCurveColor
	// 作用：读取GetChannelCurveColor。
	// 参数：chanId。
	// 返回：返回 COLORREF。
	static  COLORREF GetChannelCurveColor(int chanId);

			// 函数 SetCaptionHeight
			// 作用：设置SetCaptionHeight。
			// 参数：capHeight；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCaptionHeight(int capHeight,BOOL bRedraw = FALSE);
			// 函数 GetCaptionHeght
			// 作用：读取GetCaptionHeght。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int  GetCaptionHeght();
			// 函数 SetRoundRectParam
			// 作用：设置SetRoundRectParam。
			// 参数：roundX；roundY；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetRoundRectParam(int roundX,int roundY,BOOL bRedraw = FALSE);
			// 函数 GetRoundRectParam
			// 作用：读取GetRoundRectParam。
			// 参数：roundX；roundY。
			// 返回：没有返回值。
			void GetRoundRectParam(int& roundX,int& roundY);
			// 函数 SetDlgSize
			// 作用：设置SetDlgSize。
			// 参数：dlgWidth；dlgHeight；bRedraw：是或否。
			// 返回：没有返回值。
			void SetDlgSize(int dlgWidth,int dlgHeight,BOOL bRedraw = FALSE);
			// 函数 GetDlgSize
			// 作用：读取GetDlgSize。
			// 参数：dlgWidth；dlgHeight。
			// 返回：没有返回值。
			void GetDlgSize(int& dlgWidth,int& dlgHeight);

			// 函数 SetLeftTopPosition
			// 作用：设置SetLeftTopPosition。
			// 参数：left；top；bRedraw：是或否。
			// 返回：没有返回值。
			void SetLeftTopPosition(int left,int top,BOOL bRedraw = FALSE);
			// 函数 GetLeftTopPosition
			// 作用：读取GetLeftTopPosition。
			// 参数：left；top。
			// 返回：没有返回值。
			void GetLeftTopPosition(int& left,int& top);

			// 函数 SetLegendHeight
			// 作用：设置SetLegendHeight。
			// 参数：legendHeight；bRedraw：是或否。
			// 返回：没有返回值。
			void SetLegendHeight(int legendHeight,BOOL bRedraw = FALSE);
			// 函数 GetLegendHeight
			// 作用：读取GetLegendHeight。
			// 参数：legendHeight。
			// 返回：没有返回值。
			void GetLegendHeight(int& legendHeight);
			// 函数 SetLeftIndent
			// 作用：设置SetLeftIndent。
			// 参数：leftIndent；bRedraw：是或否。
			// 返回：没有返回值。
			void SetLeftIndent(int leftIndent,BOOL bRedraw = FALSE);
			// 函数 GetLeftIndent
			// 作用：读取GetLeftIndent。
			// 参数：leftIndent。
			// 返回：没有返回值。
			void GetLeftIndent(int& leftIndent);
			// 函数 SetRightIndent
			// 作用：设置SetRightIndent。
			// 参数：rightIndent；bRedraw：是或否。
			// 返回：没有返回值。
			void SetRightIndent(int rightIndent,BOOL bRedraw = FALSE);
			// 函数 GetRightIndent
			// 作用：读取GetRightIndent。
			// 参数：rightIndent。
			// 返回：没有返回值。
			void GetRightIndent(int& rightIndent);
			// 函数 SetTopIndent
			// 作用：设置SetTopIndent。
			// 参数：topIndent；bRedraw：是或否。
			// 返回：没有返回值。
			void SetTopIndent(int topIndent,BOOL bRedraw = FALSE);
			// 函数 GetTopIndent
			// 作用：读取GetTopIndent。
			// 参数：topIndent。
			// 返回：没有返回值。
			void GetTopIndent(int& topIndent);
			// 函数 SetBottomIndent
			// 作用：设置SetBottomIndent。
			// 参数：bottomIndent；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBottomIndent(int bottomIndent,BOOL bRedraw = FALSE);
			// 函数 GetBottomIndent
			// 作用：读取GetBottomIndent。
			// 参数：bottomIndent。
			// 返回：没有返回值。
			void GetBottomIndent(int& bottomIndent);
			// 函数 SetHaveCaptionOrNot
			// 作用：设置SetHaveCaptionOrNot。
			// 参数：bHaveCap：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHaveCaptionOrNot(BOOL bHaveCap,BOOL bRedraw = FALSE);
			// 函数 GetHaveCaptionOrNot
			// 作用：读取GetHaveCaptionOrNot。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetHaveCaptionOrNot();
			// 函数 SetHaveLegendOrNot
			// 作用：设置SetHaveLegendOrNot。
			// 参数：bHaveLgd：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetHaveLegendOrNot(BOOL bHaveLgd,BOOL bRedraw = FALSE);
			// 函数 GetHaveLegendOrNot
			// 作用：读取GetHaveLegendOrNot。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetHaveLegendOrNot();
			// 函数 SetLeanXOrNot
			// 作用：设置SetLeanXOrNot。
			// 参数：bLeanX：是或否。
			// 返回：没有返回值。
			void SetLeanXOrNot(BOOL bLeanX);
			// 函数 GetLeanXOrNot
			// 作用：读取GetLeanXOrNot。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetLeanXOrNot();
			// 函数 SetBackgrounColor
			// 作用：设置SetBackgrounColor。
			// 参数：bkClr；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBackgrounColor(BOOL bkClr,BOOL bRedraw = FALSE);
			// 函数 GetBackgrounColor
			// 作用：读取GetBackgrounColor。
			// 参数：无。
			// 返回：返回 COLORREF。
			COLORREF GetBackgrounColor();

			// 函数 SetXAxisMode
			// 作用：设置SetXAxisMode。
			// 参数：eXAxisMode；bRedraw：是或否。
			// 返回：没有返回值。
			void SetXAxisMode(EXAXISMODE eXAxisMode,BOOL bRedraw = FALSE);
			// 函数 GetXAxisMode
			// 作用：读取GetXAxisMode。
			// 参数：无。
			// 返回：返回 EXAXISMODE。
			EXAXISMODE GetXAxisMode();

			// 函数 SetBeHaveData
			// 作用：设置SetBeHaveData。
			// 参数：bHaveData：是或否。
			// 返回：没有返回值。
			void SetBeHaveData(BOOL bHaveData);
			// 函数 GetBeHaveData
			// 作用：读取GetBeHaveData。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeHaveData();

			// 函数 SetExpressionShowState
			// 作用：设置SetExpressionShowState。
			// 参数：lineId；bShowExpression：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetExpressionShowState(int lineId,BOOL bShowExpression,BOOL bRedraw = FALSE);
			// 函数 GetExpressionShowState
			// 作用：读取GetExpressionShowState。
			// 参数：lineId；bShowExpression：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetExpressionShowState(int lineId,BOOL& bShowExpression);
			// 函数 SetXAxisExplainShowState
			// 作用：设置SetXAxisExplainShowState。
			// 参数：bShowXAxisExplain：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetXAxisExplainShowState(BOOL bShowXAxisExplain,BOOL bRedraw = FALSE);
			// 函数 GetXAxisExplainShowState
			// 作用：读取GetXAxisExplainShowState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetXAxisExplainShowState();
			// 函数 SetXAxisExplain
			// 作用：设置SetXAxisExplain。
			// 参数：strXAxisExplain：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetXAxisExplain(CString strXAxisExplain,BOOL bRedraw = FALSE);
			// 函数 GetXAxisExplain
			// 作用：读取GetXAxisExplain。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetXAxisExplain();
			// 函数 SetExpressionAutoXYMinMax
			// 作用：设置SetExpressionAutoXYMinMax。
			// 参数：bExpressionAutoXYMinMax：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetExpressionAutoXYMinMax(BOOL bExpressionAutoXYMinMax,BOOL bRedraw = FALSE);
			// 函数 GetExpressionAutoXYMinMax
			// 作用：读取GetExpressionAutoXYMinMax。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetExpressionAutoXYMinMax();

			// 函数 SetBeHaveThreLineFunc
			// 作用：设置SetBeHaveThreLineFunc。
			// 参数：bHaveThreLineFunc：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeHaveThreLineFunc(BOOL bHaveThreLineFunc,BOOL bRedraw = FALSE);
			// 函数 GetBeHaveThreLineFunc
			// 作用：读取GetBeHaveThreLineFunc。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeHaveThreLineFunc();
			// 函数 SetBeUseThreLineFunc
			// 作用：设置SetBeUseThreLineFunc。
			// 参数：bUseThreLineFunc：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeUseThreLineFunc(BOOL bUseThreLineFunc,BOOL bRedraw = FALSE);
			// 函数 GetBeUseThreLineFunc
			// 作用：读取GetBeUseThreLineFunc。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeUseThreLineFunc();

			// 函数 SetXAxisTag
			// 作用：设置SetXAxisTag。
			// 参数：xAxisTag；bRedraw：是或否。
			// 返回：没有返回值。
			void SetXAxisTag(CString xAxisTag,BOOL bRedraw = FALSE);
			// 函数 GetXAxisTag
			// 作用：读取GetXAxisTag。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetXAxisTag();
			// 函数 SetYAxisTag
			// 作用：设置SetYAxisTag。
			// 参数：yAxisTag；bRedraw：是或否。
			// 返回：没有返回值。
			void SetYAxisTag(CString yAxisTag,BOOL bRedraw = FALSE);
			// 函数 GetYAxisTag
			// 作用：读取GetYAxisTag。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetYAxisTag();

			// 函数 SetBeStdCrv
			// 作用：设置SetBeStdCrv。
			// 参数：bStdCrv：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void SetBeStdCrv(BOOL bStdCrv,BOOL bRedraw = FALSE);
			// 函数 GetBeStdCrv
			// 作用：读取GetBeStdCrv。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeStdCrv();

			// 函数 SetBeUseFloatFunc
			// 作用：设置SetBeUseFloatFunc。
			// 参数：bUseFloatFunc：是或否。
			// 返回：没有返回值。
			void SetBeUseFloatFunc(BOOL bUseFloatFunc);
			// 函数 GetBeUseFloatFunc
			// 作用：读取GetBeUseFloatFunc。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeUseFloatFunc();

			// 函数 SetYAxisMinOfMax
			// 作用：设置SetYAxisMinOfMax。
			// 参数：dMinOfMax：小数。
			// 返回：没有返回值。
			void SetYAxisMinOfMax(double dMinOfMax);
			// 函数 GetYAxisMinOfMax
			// 作用：读取GetYAxisMinOfMax。
			// 参数：无。
			// 返回：返回一个小数。
			double GetYAxisMinOfMax();

			// 函数 SetBeShieldYAxisMinOfMax
			// 作用：设置SetBeShieldYAxisMinOfMax。
			// 参数：bShield：是或否。
			// 返回：没有返回值。
			void SetBeShieldYAxisMinOfMax(BOOL bShield);
			// 函数 GetBeShieldYAxisMinOfMax
			// 作用：读取GetBeShieldYAxisMinOfMax。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShieldYAxisMinOfMax();

			// 函数 SetLinearFitData
			// 作用：设置SetLinearFitData。
			// 参数：lineId；pLinearFitData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLinearFitData(int lineId,LINEARFITDATA* pLinearFitData,BOOL bRedraw = FALSE);
			// 函数 SetLinearFitData
			// 作用：设置SetLinearFitData。
			// 参数：iLineId：整数；pLinearFitData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLinearFitData(int iLineId,CLinearFitData* pLinearFitData,BOOL bRedraw = FALSE);

			// 函数 SetMinYDecrementParam
			// 作用：设置SetMinYDecrementParam。
			// 参数：bUse：是或否；dThre：小数；dDecre：小数。
			// 返回：没有返回值。
			void SetMinYDecrementParam(BOOL bUse,double dThre,double dDecre);
			// 函数 IsUseMinYDecrement
			// 作用：判断IsUseMinYDecrement是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsUseMinYDecrement();
			// 函数 GetMinYDecrementThreshold
			// 作用：读取GetMinYDecrementThreshold。
			// 参数：无。
			// 返回：返回一个小数。
			double GetMinYDecrementThreshold();
			// 函数 GetMinYDecrement
			// 作用：读取GetMinYDecrement。
			// 参数：无。
			// 返回：返回一个小数。
			double GetMinYDecrement();

			// 函数 AddNewDot
			// 作用：创建或加入AddNewDot。
			// 参数：lineIndex；myPoint；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AddNewDot(int lineIndex,CMyPoint& myPoint,BOOL bRedraw = FALSE);	//添加数据点，自动比较X轴最大值、最小值
			// 函数 AddNewDotAutoCompareXYMinMax
			// 作用：创建或加入AddNewDotAutoCompareXYMinMax。
			// 参数：lineIndex；myPoint；bRedraw：是或否；dZoomRatio：小数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AddNewDotAutoCompareXYMinMax(int lineIndex,CMyPoint& myPoint,BOOL bRedraw = FALSE,double dZoomRatio = 1.3);	//添加数据点，自动比较X轴、Y轴最大值、最小值，dZoomRatio应该是正数

			// 函数 ClearLine
			// 作用：更新或清除ClearLine。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void ClearLine(BOOL bRedraw = FALSE);	//清空原始数据点
			// 函数 DeleteLineData
			// 作用：更新或清除DeleteLineData。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void DeleteLineData(BOOL bRedraw);
			// 函数 DeleteOneLineData
			// 作用：更新或清除DeleteOneLineData。
			// 参数：lineIndex；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteOneLineData(int lineIndex,BOOL bRedraw);

			// 函数 SetLineString
			// 作用：设置SetLineString。
			// 参数：lineIndex；iChanIndex：整数；strTag：字符串；strDyeName：字符串；strTarget：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLineString(int lineIndex,int iChanIndex,CString strTag,CString strDyeName,CString strTarget);

			// 函数 HandSetExpressionXYAxisMinMax
			// 作用：执行HandSetExpressionXYAxisMinMax。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void HandSetExpressionXYAxisMinMax(BOOL bRedraw = FALSE);
			// 函数 HandSetGeneralLineXYAxisMinMax
			// 作用：执行HandSetGeneralLineXYAxisMinMax。
			// 参数：dMultiplier：小数；bRedraw：是或否。
			// 返回：没有返回值。
			void HandSetGeneralLineXYAxisMinMax(double dMultiplier = 1.1,BOOL bRedraw = FALSE);	//计算X/Y轴最大最小值
			// 函数 HandSetGeneralLineYAxisMinMax
			// 作用：执行HandSetGeneralLineYAxisMinMax。
			// 参数：dMultiplier：小数；bRedraw：是或否。
			// 返回：没有返回值。
			void HandSetGeneralLineYAxisMinMax(double dMultiplier = 1.1,BOOL bRedraw = FALSE);	//只计算Y轴最大最小值

			// 函数 SetLineNum
			// 作用：设置SetLineNum。
			// 参数：lineNum；bRedraw：是或否。
			// 返回：返回是或否。
			BOOL SetLineNum(int lineNum,BOOL bRedraw = FALSE);
			// 函数 SetLineParam
			// 作用：设置SetLineParam。
			// 参数：lineIndex；lineClr；chanId；bShow：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLineParam(int lineIndex,COLORREF lineClr,int chanId,BOOL bShow,BOOL bRedraw = FALSE);
			// 函数 SetLineParam
			// 作用：设置SetLineParam。
			// 参数：iChanId：整数；strDyeName：字符串；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLineParam(int iChanId,CString strDyeName,BOOL bRedraw = FALSE);
			// 函数 SetLineShow
			// 作用：设置SetLineShow。
			// 参数：lineIndex；bShow：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLineShow(int lineIndex,BOOL bShow,BOOL bRedraw = FALSE);
			// 函数 SetLineXAxisMillisecondTime
			// 作用：设置SetLineXAxisMillisecondTime。
			// 参数：lineIndex；bXAxisMsTime：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLineXAxisMillisecondTime(int lineIndex,BOOL bXAxisMsTime,BOOL bRedraw = FALSE);

			// 函数 SetCurveType
			// 作用：设置SetCurveType。
			// 参数：eCurveType；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCurveType(ECURVETYPE eCurveType,BOOL bRedraw = FALSE);
			// 函数 GetCurveType
			// 作用：读取GetCurveType。
			// 参数：无。
			// 返回：返回 ECURVETYPE。
			ECURVETYPE GetCurveType();

			// 函数 SetLineColorMode
			// 作用：设置SetLineColorMode。
			// 参数：eLineClrMode；bRedraw：是或否。
			// 返回：没有返回值。
			void SetLineColorMode(ELINECLRMODE eLineClrMode,BOOL bRedraw = FALSE);
			// 函数 GetLineColorMode
			// 作用：读取GetLineColorMode。
			// 参数：无。
			// 返回：返回 ELINECLRMODE。
			ELINECLRMODE GetLineColorMode();
			
			// 函数 SetThreLineDataType
			// 作用：设置SetThreLineDataType。
			// 参数：eLineDataType；bRedraw：是或否。
			// 返回：没有返回值。
			void SetThreLineDataType(ELINEDATATYPE eLineDataType,BOOL bRedraw = FALSE);	//多通道统一设置
			// 函数 GetThreLineDataType
			// 作用：读取GetThreLineDataType。
			// 参数：iChanId：整数；eLineDataType。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetThreLineDataType(int iChanId,ELINEDATATYPE& eLineDataType);	//单通道单独获取

			// 函数 SetThreLineShowForamt
			// 作用：设置SetThreLineShowForamt。
			// 参数：eLineShowFormat；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetThreLineShowForamt(ELINESHOWFORMAT eLineShowFormat,BOOL bRedraw = FALSE);	//多通道统一设置
			// 函数 GetThreLineShowForamt
			// 作用：读取GetThreLineShowForamt。
			// 参数：iChanId：整数；eLineShowFormat。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetThreLineShowForamt(int iChanId,ELINESHOWFORMAT& eLineShowFormat);	//单通道单独获取

			// 函数 SetBeShowThreLine
			// 作用：设置SetBeShowThreLine。
			// 参数：iChanId：整数；bShowThreLine：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetBeShowThreLine(int iChanId,BOOL bShowThreLine,BOOL bRedraw = FALSE);	//单通道单独设置，所有阈值线显示状态相同
			// 函数 GetBeShowThreLine
			// 作用：读取GetBeShowThreLine。
			// 参数：iChanId：整数；bShowThreLine：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetBeShowThreLine(int iChanId,BOOL& bShowThreLine);	//单通道单独获取

			// 函数 SetThreLineColor
			// 作用：设置SetThreLineColor。
			// 参数：iChanId：整数；clrThreLine：颜色；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetThreLineColor(int iChanId,Color clrThreLine,BOOL bRedraw = FALSE);	//单通道单独设置
			// 函数 GetThreLineColor
			// 作用：读取GetThreLineColor。
			// 参数：iChanId：整数；clrThreLine：颜色。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetThreLineColor(int iChanId,Color& clrThreLine);	//单通道单独获取

			// 函数 SetBeShowExpression
			// 作用：设置SetBeShowExpression。
			// 参数：bShowExpression：是或否；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetBeShowExpression(BOOL bShowExpression,BOOL bRedraw = FALSE);	//设置是否显示表达式
			// 函数 GetBeShowExpression
			// 作用：读取GetBeShowExpression。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeShowExpression();	

			// 函数 PixelHeightToYValue
			// 作用：执行PixelHeightToYValue。
			// 参数：pixelH。
			// 返回：返回一个小数。
			double PixelHeightToYValue(int pixelH);

			// 函数 AddHighlightIndex
			// 作用：创建或加入AddHighlightIndex。
			// 参数：index；bUnique：是或否；bRedraw：是或否。
			// 返回：没有返回值。
			void AddHighlightIndex(int index,BOOL bUnique,BOOL bRedraw = FALSE);
			// 函数 GetHighlightIndex
			// 作用：读取GetHighlightIndex。
			// 参数：vecHighlightIndex。
			// 返回：没有返回值。
			void GetHighlightIndex(vector<int>& vecHighlightIndex);

			// 函数 GetFloatWndRegion
			// 作用：读取GetFloatWndRegion。
			// 参数：rcOrigin。
			// 返回：返回 CRect。
			CRect GetFloatWndRegion(CRect rcOrigin);

			// 函数 SetThrelineFstShow
			// 作用：设置SetThrelineFstShow。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetThrelineFstShow(BOOL bRedraw = FALSE);	//设置阈值线为“第一次绘制”，重新计算阈值线在控件中的高度

			// 函数 GetExpressionString
			// 作用：读取GetExpressionString。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetExpressionString();

			// 函数 IsExistVisibleExpression
			// 作用：判断IsExistVisibleExpression是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsExistVisibleExpression();	//获取是否存在可见的关系式，不受m_bShowExpressoin影响
			// 函数 GetVisibleExpressionCount
			// 作用：读取GetVisibleExpressionCount。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetVisibleExpressionCount();	//获取可见的关系式个数，不受m_bShowExpressoin影响
			// 函数 GetVisibleExpressionHeight
			// 作用：读取GetVisibleExpressionHeight。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetVisibleExpressionHeight();	//获取可见的关系式占用的高度

			// 函数 SetExpressionTag
			// 作用：设置SetExpressionTag。
			// 参数：strData：字符串；bRedraw：是或否。
			// 返回：没有返回值。
			void SetExpressionTag(CString strData,BOOL bRedraw = FALSE);
			// 函数 GetExpressionTag
			// 作用：读取GetExpressionTag。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetExpressionTag();

			// 函数 CreateCtrl
			// 作用：创建或加入CreateCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCtrl();
			// 函数 InitCtrl
			// 作用：初始化InitCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void InitCtrl();
			// 函数 SetCtrlPos
			// 作用：设置SetCtrlPos。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlPos();
			// 函数 ShowCtrl
			// 作用：改变ShowCtrl的显示或可用状态。
			// 参数：无。
			// 返回：没有返回值。
			void ShowCtrl();
			// 函数 CreateBt
			// 作用：创建或加入CreateBt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateBt();
			// 函数 CreateSt
			// 作用：创建或加入CreateSt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSt();
			// 函数 InitBt
			// 作用：初始化InitBt。
			// 参数：无。
			// 返回：没有返回值。
			void InitBt();
			// 函数 InitSt
			// 作用：初始化InitSt。
			// 参数：无。
			// 返回：没有返回值。
			void InitSt();

	// 函数 OnBnClickedClose
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedClose();
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnUpdateCurve
	// 作用：响应 Windows 或自定义消息 OnUpdateCurve。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnUpdateCurve(WPARAM wParam, LPARAM lParam);
	// 函数 OnCurveMenuExportPicture
	// 作用：响应 Windows 或自定义消息 OnCurveMenuExportPicture。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnCurveMenuExportPicture();

protected:
	// 函数 RecalculateStartEndValue
	// 作用：执行RecalculateStartEndValue。
	// 参数：dExRatio：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetRealUsedHoriDotLen。
	void RecalculateStartEndValue(double dExRatio=0.15);

private:
	// 函数 SetRoundRect
	// 作用：设置SetRoundRect。
	// 参数：x；y。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetRealUsedHoriDotLen。
	BOOL SetRoundRect(int x = 5,int y = 5);

public:
	// 函数 SetRealUsedHoriDotLen
	// 作用：设置SetRealUsedHoriDotLen。
	// 参数：iDotLen：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRealUsedHoriDotLen(int iDotLen) { m_realUsedHoriDotLen = iDotLen; }

private:
	int  m_horiStepNums;	//水平方向上基本单元的个数
	int  m_vertStepNums;	//垂直方向上基本单元的个数
	int  m_horiStrOutStep;	//水平方向上文字输出间隔（隔几个Step输出一次文字）
	int  m_vertStrOutStep;	//垂直方向上文字输出间隔（隔几个Step输出一次文字）
	double m_horiStep;	//水平方向上基本单元的对应的数据大小（线段对应的数据值）
	int m_intHoriStep;	//m_horiStep的整型数值
	double m_vertStep;	//垂直方向上基本单元的对应的数据大小（线段对应的数据值）
	int m_intVertStep;	//m_vertStep的整型数值

	double m_horiStartValue;
	double m_horiEndValue;
	double m_vertStartValue;
	double m_vertEndValue;

	COLORREF m_horiStrClr;
	COLORREF m_horiLineClr;
	COLORREF m_vertStrClr;
	COLORREF m_vertLineClr;
	COLORREF m_horiBaseLineClr;
	COLORREF m_vertBaseLineClr;
	COLORREF m_xSptClr;	//X轴分割线Spt=Separator
	COLORREF m_roundTagInnerClr;	//圆形标识点
	int m_horiLineWidth;
	int m_vertLineWidth;
	int m_horiSptWidth;
	int m_horiBaseLineWidth;
	int m_vertBaseLineWidth;
	int m_curveWidth;
	BOOL m_bShowVertBaseLine;	//是否显示垂直基线（不包括Y轴）
	int m_iVertLineInterval;	//垂直分割线间隔步骤数

	BOOL m_bShowHoriBaseLine;//是否显示水平基线（不包括X轴）
	BOOL m_bShowVertLine;	//是否显示Y轴
	BOOL m_bShowHoriLine;	//是否显示X轴
	BOOL m_bShowHoriSpt;	//暂时没有用到该成员变量
	BOOL m_bShowRoundTag;
	UINT m_roundTagLineWidth;
	UINT m_roundTagRadius;
	UINT m_horiDecPtLen;	//不参与计算，水平方向坐标轴文字标识小数点后位数,最大值为20
	UINT m_vertDecPtLen;	//不参与计算，垂直方向坐标轴文字标识小数点后位数，最大值为20
	UINT m_realUsedHoriDotLen;	//真正参与计算的水平方向坐标轴文字标识小数点后位数,最大值为20
	UINT m_realUsedVertDotLen;	//真正参与计算的垂直方向坐标轴文字标识小数点后位数，最大值为20
	int m_figureStartX;		//图形区域在窗口中的水平方向起始位置，下面三个成员变量意义相近
	int m_figureEndX;
	int m_figureStartY;
	int m_figureEndY;

	int	m_roundX;	//窗口圆角X值
	int	m_roundY;	//窗口圆角Y值

	int m_capHeight;//标题栏高度
	CSize m_dlgSize;	//窗口尺寸
	int m_left;		//窗口左上角X坐标
	int m_top;		//窗口左上角Y坐标
	int m_lgdHeight;	//图例区域高度
	int m_leftIndent;	//图形区域左侧缩进
	int m_rightIndent;	//图形区域右侧缩进
	int m_topIndent;	//图形区域顶部缩进
	int m_bottomIndent;	//图形区域底部缩进

	BOOL m_bHaveCap;	//是否显示标题栏
	BOOL m_bHaveLgd;	//是否显示图例
	BOOL m_bLeanX;		//是否垂直显示X轴文字
	
	BOOL m_bExpressionAutoXYMinMax;	//表达式模式（STDLINE）下，是否自动扩展（相对于手动计算）X/Y轴最大值、最小值
	BOOL m_bShowXAxisExplain;	//是否显示X轴内容说明
	CString m_strXAxisExplain;

	COLORREF m_rgbBkClr;//除标题栏外的背景颜色

	int m_lineNum;	//曲线条数

	ECURVETYPE m_eCurveType;
	EXAXISMODE m_eXAxisMode;

	double m_dAxisHoriRt;
	double m_dAxisVertRt;

	BOOL m_bHaveThreLineFunc;	//标识是否包含阈值线功能
	BOOL m_bUseThreLineFunc;	//标识是否使用阈值线功能

	BOOL m_bHaveData;	//标识图形控件是否有数据存在

	CDC* m_pMemDc;	//加速图形绘制
	HBITMAP m_hBitmap;
	BOOL m_bFstPaint;
	int  m_fstPaintWidth;
	int  m_fstPaintHeight;

	BOOL m_bThreMove;	//标识是否是阈值线导致的重绘

	ELINECLRMODE m_eLineClrMode;	//曲线颜色选型

	vector<int> m_vecHighLightIndex;	//保存高亮显示曲线下标

	CString m_strXAxisTag;
	CString m_strYAxisTag;

	BOOL m_bstdCrv;	//标识是否是标曲功能
	int m_stdFrameH;	//标曲标题栏高度

	//圆角矩形样式参数
	BOOL m_bRoundRectStyle;	//标识是否使用圆角矩形样式
	COLORREF m_clrFourAngleBk;	//圆角矩形以外的背景色
	int m_iRoundAngleSize;	//圆角大小
	Color m_clrIndepent;	//独立第三方颜色，用于支持局部透明

	CFloatDlg m_floatDlg;	//悬浮窗

	BOOL m_bUseFloatFunc;	//标识是否使用悬浮提示窗口

	double m_dYAxisMinOfMax;	//纵坐标最大值的最小值，默认值为1000
	BOOL m_bShieldYAxisMinOfMax;	//是否屏蔽m_dYAxisMinOfMax功能

	int m_iHoriDecPtLenSet;	//用于临时保存最新设置的水平文字小数点位数，在类的内部使用

	BOOL m_bShowExpressoin;	//标识“是否显示关系式信息(对于整个图形控件，而不是单条曲线)”

	int m_iEprVertInterval;	//标曲关系式之间的垂直间隔
	int m_iEprXStart;
	int m_iEprYStart;
	int m_iEprEndY;	//记录 整体的标曲关系式 底部Y坐标

	CString m_strEprTag;	//关系式标识
	CRect m_rcEprTag;	//关系式标识所在区域

	BOOL m_bUseMinYDecre;	//是否使用纵坐标最小值减量
	double m_dMinYDecreThre;	//使用纵坐标最小值减量的阈值条件
	double m_dMinYDecrement;	//纵坐标最小值减量

public:
	CMyButton m_btClose;
	CMyStatic m_stCapInfo;

	CLineInfo* m_pLineInfo;	//图形原始数据

	vector<CChanThreInfo> m_vecChanThreInfo;

	CFontSet m_fontExpression;	//表达式字体
};







