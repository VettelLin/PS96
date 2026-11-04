// 【交接】 GeneralPcr\DataAnaDlg.h
// 作用：数据分析页声明。DataProcess 负责调用实验数据里的荧光处理和 GenerateCt。
// 先看这些函数：DECLARE_DYNAMIC、CDataAnaDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnCreate、OnSize、OnBnClickedBtAxisZoom。
#pragma once

#include "MyLstCtrl.h"
#include "MyButton.h"
#include "MyNewCb.h"
#include "MyNewEdit.h"
#include "MySamPlateDlg.h"
#include "MyDrawCurveDlg.h"
#include "ExperimentData.h"
#include "LegendInfo.h"
#include "StdProc.h"
#include "RectManage.h"

class CMiddleDlg;

typedef enum _AmlOriginalCurveType
{
	EAOCT_AMLCURVE = 1,EAOCT_ORIGINALCURVE
}EAMLORIGINALCURVETYPE;

typedef enum _MeltOriginalCurveType
{
	EMOCT_MELTPEAKCURVE = 1,EMOCT_ORIGINALMELTCRV
}EMELTORIGINALCURVETYPE;

class CDataAnaDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CDataAnaDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CDataAnaDlg)

public:
	// 函数 CDataAnaDlg
	// 作用：执行CDataAnaDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CDataAnaDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CDataAnaDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CDataAnaDlg();

// Dialog Data
	enum { IDD = IDD_DATAANADLG };

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
	// 函数 OnBnClickedBtAxisZoom
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtAxisZoom();
	// 函数 OnBnClickedBtAxisZoomSecond
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedBtAxisZoomSecond();
	// 函数 OnMsgPlateSiteSelectChanged
	// 作用：响应 Windows 或自定义消息 OnMsgPlateSiteSelectChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgPlateSiteSelectChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgThreChanged
	// 作用：响应 Windows 或自定义消息 OnMsgThreChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgThreChanged(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam);
	//afx_msg LRESULT OnMsgRowSelectedChange(WPARAM wParam,LPARAM lParam);

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
			// 函数 CreateCb
			// 作用：创建或加入CreateCb。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCb();
			// 函数 CreateEd
			// 作用：创建或加入CreateEd。
			// 参数：无。
			// 返回：没有返回值。
			void CreateEd();
			// 函数 CreateLst
			// 作用：创建或加入CreateLst。
			// 参数：无。
			// 返回：没有返回值。
			void CreateLst();
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
			// 函数 InitCb
			// 作用：初始化InitCb。
			// 参数：无。
			// 返回：没有返回值。
			void InitCb();
			// 函数 InitEd
			// 作用：初始化InitEd。
			// 参数：无。
			// 返回：没有返回值。
			void InitEd();
			// 函数 InitLst
			// 作用：初始化InitLst。
			// 参数：无。
			// 返回：没有返回值。
			void InitLst();
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
			void SetCrvLineParam(vector<CTubeInfo>& vecTubeInfo);
			// 函数 SetCrvLineParam
			// 作用：设置SetCrvLineParam。
			// 参数：vecPTubeInfo。
			// 返回：没有返回值。
			void SetCrvLineParam(vector<CTubeInfo*>& vecPTubeInfo);

			// 函数 SetCrvThreLineInfo
			// 作用：设置SetCrvThreLineInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCrvThreLineInfo();	//设置曲线控件阈值信息
			// 函数 RenewNormalizeCrvThreLineInfo
			// 作用：执行RenewNormalizeCrvThreLineInfo。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RenewNormalizeCrvThreLineInfo(BOOL bRedraw = FALSE);	//更新归一化曲线控件阈值信息
			// 函数 RenewDeltaRnCrvThreLineInfo
			// 作用：执行RenewDeltaRnCrvThreLineInfo。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RenewDeltaRnCrvThreLineInfo(BOOL bRedraw = FALSE);	//更新DeltaRn曲线控件阈值信息

			// 函数 ThreLineModified
			// 作用：执行ThreLineModified。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ThreLineModified();	//在基本参数设置窗口中修改了手动阈值

			// 函数 UpdateCurveSelectState
			// 作用：更新或清除UpdateCurveSelectState。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void UpdateCurveSelectState(BOOL bRedraw = FALSE);	//更新曲线、阈值线显示状态，

			// 函数 CurveAxisEdit
			// 作用：执行CurveAxisEdit。
			// 参数：pCrvCtrl：指针，指向调用方传入的对象；bHaveLogFunc：是或否；bLogMode：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CurveAxisEdit(CMyDrawCurveDlg* pCrvCtrl,BOOL bHaveLogFunc = FALSE,BOOL bLogMode = FALSE);

			// 函数 SetBaseSet
			// 作用：设置SetBaseSet。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetBaseSet();	//编辑基本分析参数信息
			// 函数 SetMotChannelAdjust
			// 作用：设置SetMotChannelAdjust。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetMotChannelAdjust();	//编辑浊度校准参数信息

			// 函数 ClearPage
			// 作用：更新或清除ClearPage。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void ClearPage(BOOL bRedraw = TRUE);
			// 函数 FileOpened
			// 作用：执行FileOpened。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int FileOpened(CExperimentData* pExpData = NULL);	//打开文件后设置分析页面
			// 函数 ExperimentOver
			// 作用：执行ExperimentOver。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExperimentOver(CExperimentData* pExpData = NULL);	//实验结束后设置分析页面
			// 函数 ReAnalysed
			// 作用：执行ReAnalysed。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReAnalysed(CExperimentData* pExpData = NULL);	//重新分析后设置分析页面

			// 函数 SetCurveData
			// 作用：设置SetCurveData。
			// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCurveData(CExperimentData* pExpData,BOOL bRedraw = FALSE);	//设置曲线控件中的曲线数据
			// 函数 SetMeltCurveData
			// 作用：设置SetMeltCurveData。
			// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetMeltCurveData(CExperimentData* pExpData,BOOL bRedraw = FALSE);

			// 函数 SetNormalizeCurveData
			// 作用：设置SetNormalizeCurveData。
			// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetNormalizeCurveData(CExperimentData* pExpData,BOOL bRedraw = FALSE);	//设置归一化曲线控件中的曲线数据
			// 函数 SetDeltaRnCurveData
			// 作用：设置SetDeltaRnCurveData。
			// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetDeltaRnCurveData(CExperimentData* pExpData,BOOL bRedraw = FALSE);	//设置DeltaRn曲线控件中的曲线数据
			// 函数 SetFilterCurveData
			// 作用：设置SetFilterCurveData。
			// 参数：pExpData：指针，指向调用方传入的对象；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetFilterCurveData(CExperimentData* pExpData,BOOL bRedraw = FALSE);	//设置滤波后的原始数据曲线控件中的曲线数据

			// 函数 SetCurveHoriAxisParam
			// 作用：设置SetCurveHoriAxisParam。
			// 参数：iStart：整数；iEnd：整数；iHoriStep：整数；bRedraw：是或否。
			// 返回：没有返回值。
			void SetCurveHoriAxisParam(int iStart,int iEnd,int iHoriStep,BOOL bRedraw = TRUE);

			// 函数 DataProcess
			// 作用：执行DataProcess。
			// 参数：bNewOver：是或否；iAmlFlag：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DataProcess(BOOL bNewOver,int iAmlFlag = 5);	//数据分析

			// 函数 ResetResultLst
			// 作用：更新或清除ResetResultLst。
			// 参数：无。
			// 返回：没有返回值。
			void ResetResultLst();	//重新设置结果列表框内容
			// 函数 LstResultLanguageChanged
			// 作用：执行LstResultLanguageChanged。
			// 参数：无。
			// 返回：没有返回值。
			void LstResultLanguageChanged();	//结果列表语言改变了

			// 函数 AddOneResult
			// 作用：创建或加入AddOneResult。
			// 参数：tubeInfo；iChanIndex：整数；strCt：字符串；strTm：字符串。
			// 返回：没有返回值。
			void AddOneResult(CTubeInfo& tubeInfo,int iChanIndex,CString strCt,CString strTm = _T(""));

			// 函数 NewResultCalculated
			// 作用：执行NewResultCalculated。
			// 参数：iChanId：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int NewResultCalculated(int iChanId);	//通道结果信息（Ct值、Tm值）改变后，更新结果列表信息

			// 函数 ExportPicture
			// 作用：执行ExportPicture。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportPicture();	//导出图片
			
			// 函数 AmlDataShowTypeChanged
			// 作用：执行AmlDataShowTypeChanged。
			// 参数：iNewIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AmlDataShowTypeChanged(int iNewIndex);	//m_cbSelCrvToShow选中项更改了

			// 函数 CheckAmlDataShowType
			// 作用：判断CheckAmlDataShowType是否成立。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CheckAmlDataShowType();	//打开文件时，根据文件里的分析参数设置当前是查看归一化还是DeltaRn数据

			// 函数 StdLineProcess
			// 作用：执行StdLineProcess。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int StdLineProcess(CExperimentData* pExpData);	//计算所有通道的标曲
			// 函数 StdLineProcess
			// 作用：执行StdLineProcess。
			// 参数：pExpData：指针，指向调用方传入的对象；iChanId：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int StdLineProcess(CExperimentData* pExpData,int iChanId);

			// 函数 GetCtTitle
			// 作用：读取GetCtTitle。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetCtTitle();
			// 函数 GetAverageCtTitle
			// 作用：读取GetAverageCtTitle。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetAverageCtTitle();

			// 函数 CbSelectCrvToShowChanged
			// 作用：执行CbSelectCrvToShowChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CbSelectCrvToShowChanged();	//下拉选择看选择项改变了
			// 函数 CbSelectChannelThresholdChanged
			// 作用：执行CbSelectChannelThresholdChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CbSelectChannelThresholdChanged();	//下拉选择看选择项改变了

			// 函数 ShowThreValue
			// 作用：改变ShowThreValue的显示或可用状态。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ShowThreValue();	//打开文件、重新分析、实验结束后更新阈值显示

			// 函数 ResetCurveMaxMinValue
			// 作用：更新或清除ResetCurveMaxMinValue。
			// 参数：bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ResetCurveMaxMinValue(BOOL bRedraw);	//从新计算曲线控件最大最小值

			// 函数 GetExpDataPtr
			// 作用：读取GetExpDataPtr。
			// 参数：无。
			// 返回：返回指针 CExperimentData*。指针为空表示没有取到对象。
			CExperimentData* GetExpDataPtr();

			// 函数 SetCbSelectChanThreString
			// 作用：设置SetCbSelectChanThreString。
			// 参数：无。
			// 返回：没有返回值。
			void SetCbSelectChanThreString();	//设置当前显示阈值通道名称集
			
			// 函数 SetOneChannelDyeName
			// 作用：设置SetOneChannelDyeName。
			// 参数：iChanId：整数；strNewDyeName：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetOneChannelDyeName(int iChanId,CString strNewDyeName);

			// 函数 NormalizeLogModeChanged
			// 作用：执行NormalizeLogModeChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int NormalizeLogModeChanged();	//归一化数据对数坐标模式选项改变了
			// 函数 DeltaRnLogModeChanged
			// 作用：执行DeltaRnLogModeChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeltaRnLogModeChanged();	//DeltaRn数据对数坐标模式选项改变了

			// 函数 RecordDefaultAxisInfo
			// 作用：执行RecordDefaultAxisInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RecordDefaultAxisInfo();	//记录每个曲线控件的默认值

			// 函数 AdjudicateAmpMeltWhichToShow
			// 作用：执行AdjudicateAmpMeltWhichToShow。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int AdjudicateAmpMeltWhichToShow();	//实验结束或者打开文件时，判断显示扩增类型数据还是熔曲类型数据

			// 函数 RefreshTheChannelToShowThre
			// 作用：更新或清除RefreshTheChannelToShowThre。
			// 参数：iBtIndex：整数；bChecked：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshTheChannelToShowThre(int iBtIndex,BOOL bChecked);	//刷新需要显示阈值的通道（发生于通道选中状态改变）

			// 函数 UploadInspectResultToLis
			// 作用：执行UploadInspectResultToLis。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UploadInspectResultToLis();	//上传数据到LIS系统
			// 函数 SendDataByTcpIp
			// 作用：执行SendDataByTcpIp。
			// 参数：vecLisInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SendDataByTcpIp(vector<CStringA>& vecLisInfo);

			// 函数 ResetLstTitle
			// 作用：更新或清除ResetLstTitle。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstTitle();
			// 函数 ResetLstColumnWidth
			// 作用：更新或清除ResetLstColumnWidth。
			// 参数：无。
			// 返回：没有返回值。
			// 过程：函数里会调用 GetCtDataType。
			void ResetLstColumnWidth();

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			// 过程：函数里会调用 GetCtDataType。
			int RefreshLanguageDisplay();

protected:
	// 函数 ResetThresholdLineValueBySelTube
	// 作用：更新或清除ResetThresholdLineValueBySelTube。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetCtDataType。
	void ResetThresholdLineValueBySelTube();

public:
	// 函数 GetCtDataType
	// 作用：读取GetCtDataType。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetCtDataType() { return m_iPreCbSelIndex; }

public:
	CMyButton m_btAxisZoom;	
	CMyButton m_btAxisZoom2nd;

	CMyNewCb m_cbSelCrvToShow;
	CMyNewCb m_cbSelChanThre;

	CMyNewEdit m_edThreValue;

	CMyDrawCurveDlg m_crvAml;	//归一化数据
	CMyDrawCurveDlg m_crvAmlDelRn;	//DeltaRn数据
	CMyDrawCurveDlg m_crvOriginAml;
	CMyDrawCurveDlg m_crvPeakMelt;
	CMyDrawCurveDlg m_crvOriginMelt;
	CMyDrawCurveDlg m_crvStd; 

	CMyLstCtrl m_lstAnaResult;

	CMySamPalteDlg m_samPlateDlg;

	CMiddleDlg* m_pParent;

	vector<BOOL> m_vecPlateSelectState;	//记录所有孔位的选中状态
	vector<int> m_vecPlateSelectedSite;	//记录孔板选中孔位下标

	CMyDrawCurveDlg* m_pCurSelCrvToShow;	//当前要显示曲线控件

	CLegendInfo m_segLgdInfo;	//样本信息控件图例

	CStdProc m_stdProc;

private:
	BOOL m_bCtrlCreated;
	int m_iPreCbSelIndex;	//记录曲线类型下拉选择窗口上一个选择项

	CRect m_rcThresholdText;	//记录“阈值”文本的显示区域

	CRectManage m_rcManage;
};

