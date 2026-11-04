// 【交接】 GeneralPcr\RunMonitorDlg.h
// 作用：RunMonitorDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CRunMonitorDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnCreate、OnBnClickedSwtBtRunSegment。
#pragma once

#include "MySamPlateDlg.h"
#include "RunStateDlg.h"
#include "MyButton.h"
#include "MyDrawCurveDlg.h"
#include "MyStatic.h"
#include "MySegDlg.h"
#include "ExperimentData.h"
#include "LegendInfo.h"
#include "RectManage.h"

class CMiddleDlg;

typedef enum _RUNMONITOR_SONPAGETYPE
{
	ERST_RUNSEGDLG = 1,ERST_TEMCRV
}ERUNMONITORSONPAGETYPE;

typedef enum _RUNMONITOR_AMLMELTPAGETYPE
{
	ERAMPT_ORIGINAML = 1,ERAMPT_ORIGINMELT
}ERUNMONITOR_AMLMELTPAGETYPE;

class CRunMonitorDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CRunMonitorDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CRunMonitorDlg)

public:
	// 函数 CRunMonitorDlg
	// 作用：执行CRunMonitorDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CRunMonitorDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CRunMonitorDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CRunMonitorDlg();

// Dialog Data
	enum { IDD = IDD_RUNMONITORDLG };

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
	// 函数 OnCreate
	// 作用：响应 Windows 或自定义消息 OnCreate。
	// 参数：lpCreateStruct。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 函数 OnBnClickedSwtBtRunSegment
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtRunSegment();
	// 函数 OnBnClickedSwtBtTemCurve
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtTemCurve();
	// 函数 OnBnClickedSwtBtOriginAml
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtOriginAml();
	// 函数 OnBnClickedSwtBtOriginMelt
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtOriginMelt();
	// 函数 OnMsgPlateSiteSelectChanged
	// 作用：响应 Windows 或自定义消息 OnMsgPlateSiteSelectChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgPlateSiteSelectChanged(WPARAM wParam,LPARAM lParam);

	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();

			// 函数 InitDlg
			// 作用：初始化InitDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitDlg();
			// 函数 InitSegLegend
			// 作用：初始化InitSegLegend。
			// 参数：无。
			// 返回：没有返回值。
			void InitSegLegend();

			// 函数 InitSonDlg
			// 作用：初始化InitSonDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSonDlg();
			// 函数 InitRunStateDlg
			// 作用：初始化InitRunStateDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitRunStateDlg();

			// 函数 CreateCtrl
			// 作用：创建或加入CreateCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCtrl();
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
			// 函数 CreateSeg
			// 作用：创建或加入CreateSeg。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSeg();
			// 函数 CreateSamPlateDlg
			// 作用：创建或加入CreateSamPlateDlg。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSamPlateDlg();
			// 函数 InitCrv
			// 作用：初始化InitCrv。
			// 参数：无。
			// 返回：没有返回值。
			void InitCrv();
			// 函数 InitCtrl
			// 作用：初始化InitCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void InitCtrl();
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
			// 函数 InitSeg
			// 作用：初始化InitSeg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSeg();
			// 函数 InitSamPlateDlg
			// 作用：初始化InitSamPlateDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSamPlateDlg();
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

			// 函数 SetCtrlText
			// 作用：设置SetCtrlText。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlText();

			// 函数 SetCrvLineParam
			// 作用：设置SetCrvLineParam。
			// 参数：vecTubeInfo。
			// 返回：没有返回值。
			void SetCrvLineParam(vector<CTubeInfo>& vecTubeInfo);	//设置曲线控件线条参数
			// 函数 SetCrvLineParam
			// 作用：设置SetCrvLineParam。
			// 参数：vecPTubeInfo。
			// 返回：没有返回值。
			void SetCrvLineParam(vector<CTubeInfo*>& vecPTubeInfo);
			// 函数 SetCrvLineParam
			// 作用：设置SetCrvLineParam。
			// 参数：pTubeInfo：指针，指向调用方传入的对象；iSiteNum：整数。
			// 返回：没有返回值。
			void SetCrvLineParam(CTubeInfo* pTubeInfo,int iSiteNum);

			// 函数 UpdateCurveSelectState
			// 作用：更新或清除UpdateCurveSelectState。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void UpdateCurveSelectState(BOOL bRedraw = FALSE);

			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：sonPageType。
			// 返回：没有返回值。
			void SetPageSelected(ERUNMONITORSONPAGETYPE sonPageType);
			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：sonPageType。
			// 返回：没有返回值。
			void SetPageSelected(ERUNMONITOR_AMLMELTPAGETYPE sonPageType);

			// 函数 ClearPage
			// 作用：更新或清除ClearPage。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void ClearPage(BOOL bRedraw = TRUE);
			// 函数 ClearExperiment
			// 作用：更新或清除ClearExperiment。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void ClearExperiment(BOOL bRedraw = TRUE);

			// 函数 FileOpened
			// 作用：执行FileOpened。
			// 参数：pExpData：指针，指向调用方传入的对象；bTemplate：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int FileOpened(CExperimentData* pExpData = NULL,BOOL bTemplate = FALSE);	//打开文件后设置监控页面
			// 函数 ReAnalysed
			// 作用：执行ReAnalysed。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReAnalysed(CExperimentData* pExpData = NULL);	//重新分析后设置监控页面

			// 函数 SetCurveData
			// 作用：设置SetCurveData。
			// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCurveData(CExperimentData* pExpData,BOOL bRedraw = FALSE);
			// 函数 SetTemperatureData
			// 作用：设置SetTemperatureData。
			// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetTemperatureData(CExperimentData* pExpData,BOOL bRedraw);

			// 函数 CurrentSegmentStepChangedOnRun
			// 作用：执行CurrentSegmentStepChangedOnRun。
			// 参数：iCycle：整数；iSeg：整数；iStep：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CurrentSegmentStepChangedOnRun(int iCycle,int iSeg,int iStep);

			// 函数 SetCurveHoriAxisParam
			// 作用：设置SetCurveHoriAxisParam。
			// 参数：iStart：整数；iEnd：整数；iHoriStep：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCurveHoriAxisParam(int iStart,int iEnd,int iHoriStep,BOOL bRedraw = TRUE);

			// 函数 ResetCurveMaxMinValue
			// 作用：更新或清除ResetCurveMaxMinValue。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ResetCurveMaxMinValue(BOOL bRedraw);	//从新计算曲线控件最大最小值

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshLanguageDisplay();

			// 函数 CycleAddSuccessful
			// 作用：执行CycleAddSuccessful。
			// 参数：iSegId：整数；iCount：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CycleAddSuccessful(int iSegId,int iCount);
			// 函数 ShowRemainTimeOnce
			// 作用：改变ShowRemainTimeOnce的显示或可用状态。
			// 参数：无。
			// 返回：没有返回值。
			void ShowRemainTimeOnce();

public:
	CMySamPalteDlg m_samPlateDlg;
	CMySegDlg m_segDlg;

	CRunStateDlg m_runStateDlg;

	CMyDrawCurveDlg m_crvAmlOri;
	CMyDrawCurveDlg m_crvMeltOri;	
	CMyDrawCurveDlg m_crvTem;

	CMyButton m_swtBtAmlOri;	//20220622，切换为显示DeltaRn数据，孙文郎
	CMyButton m_swtBtMeltOri;
	CMyButton m_swtBtSegMonitor;
	CMyButton m_swtBtTemMonitor;

	CMyStatic m_stLidTem;
	CMyStatic m_stTubeTem;

	CMiddleDlg* m_pParent;

	CMyButton* m_pCurSelAmlMelt;
	CWnd* m_pCurSelAMDlg;

	CMyButton* m_pCurSelSwt;
	CWnd* m_pCurSelDlg;

	ERUNMONITORSONPAGETYPE m_curSonPageType;
	ERUNMONITOR_AMLMELTPAGETYPE  m_eCurAmlMeltPageType;

	vector<int> m_vecPlateSelectedSite;	//记录孔板选中孔位下标

	CLegendInfo m_segLgdInfo;	//样本信息控件图例

private:
	BOOL m_bCtrlCreated;

	int m_iSwitchBtBkH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtBkW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值
	int m_iSwitchBtW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值

	BOOL m_bInstruHaveLid;	//标识仪器是否有热盖，没有热盖的话，不显示热盖温度
	CRect m_rcLidInstruRegion;	//标识 热盖、仪器温度图例区域，刷新页面时使用

	CRectManage m_rcManage;
};


