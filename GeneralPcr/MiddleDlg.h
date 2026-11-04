// 【交接】 GeneralPcr\MiddleDlg.h
// 作用：CMiddleDlg 的声明。实验运行消息、荧光更新、实验结束、报告导出都从这里分发。
// 先看这些函数：DECLARE_DYNAMIC、CMiddleDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnTimer、OnInitDialog。
#pragma once

// CMiddleDlg dialog

#include "MyButton.h"
#include "BaseSetDlg.h"
#include "ProcSetDlg.h"
#include "SamSetDlg.h"
#include "RunMonitorDlg.h"
#include "DataAnaDlg.h"
#include "ExpRunCtrl.h"
#include "RectManage.h"
#include "ExperimentData.h"
#include "LinkList.h"
#include "libxl.h"
#include "EditModeType.h"
#include "RunProgressRecord.h"
#include "SamInfoExportMode.h"
#include "FuncBtDlg.h"

typedef enum Son_Page_Type
{
	ESPT_BASEINFODLG = 1,ESPT_PROCSET,ESPT_SAMSET,ESPT_RUNMONITOR,ESPT_DATAANALYSE
}ESON_PAGE_TYPE;

class CMiddleDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CMiddleDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CMiddleDlg)

public:
	// 函数 CMiddleDlg
	// 作用：执行CMiddleDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CMiddleDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CMiddleDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CMiddleDlg();

// Dialog Data
	enum {IDD = IDD_MIDDLEDLG};

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
	virtual afx_msg BOOL OnEraseBkgnd(CDC* pDC);
			// 函数 OnSize
			// 作用：窗口大小变化时重新摆放控件。
			// 参数：nType：整数；cx；cy。
			// 返回：没有返回值。
			afx_msg void OnSize(UINT nType, int cx, int cy);
			// 函数 OnTimer
			// 作用：定时器到期时刷新界面或推进状态。
			// 参数：nIDEvent：整数。
			// 返回：没有返回值。
			afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
	// 函数 CreateCtrl
	// 作用：创建或加入CreateCtrl。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateCtrl();
			// 函数 InitCtrl
			// 作用：初始化InitCtrl。
			// 参数：无。
			// 返回：没有返回值。
			void InitCtrl();
	// 函数 SetCtrlPos
	// 作用：设置SetCtrlPos。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void SetCtrlPos();
	// 函数 ShowCtrl
	// 作用：改变ShowCtrl的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void ShowCtrl();
			// 函数 ShowBt
			// 作用：改变ShowBt的显示或可用状态。
			// 参数：无。
			// 返回：没有返回值。
			void ShowBt();
	// 函数 InitSonDlg
	// 作用：初始化InitSonDlg。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitSonDlg();
			// 函数 InitBaseSetDlg
			// 作用：初始化InitBaseSetDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitBaseSetDlg();
			// 函数 InitSelectPrjDlg
			// 作用：初始化InitSelectPrjDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSelectPrjDlg();
			// 函数 InitSamSetDlg
			// 作用：初始化InitSamSetDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSamSetDlg();
			// 函数 InitRunMonitroDlg
			// 作用：初始化InitRunMonitroDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitRunMonitroDlg();
			// 函数 InitDataAnaDlg
			// 作用：初始化InitDataAnaDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitDataAnaDlg();

	// 函数 SetCtrlText
	// 作用：设置SetCtrlText。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void SetCtrlText();

	// 函数 OnBnClickedSwtBaseSet
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBaseSet();
	// 函数 OnBnClickedSwtSelectProject
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtSelectProject();
	// 函数 OnBnClickedSwtSamSet
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtSamSet();
	// 函数 OnBnClickedSwtRunMonitor
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtRunMonitor();
	// 函数 OnBnClickedSwtDataAnalyse
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtDataAnalyse();

	// 函数 OnBnClickedSwtBtRunStop
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtRunStop();

	// 函数 OnMsgExperFluChanged
	// 作用：响应 Windows 或自定义消息 OnMsgExperFluChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgExperFluChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgExperRun
	// 作用：响应 Windows 或自定义消息 OnMsgExperRun。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	virtual afx_msg LRESULT OnMsgExperRun(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgExperFinished
	// 作用：响应 Windows 或自定义消息 OnMsgExperFinished。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	virtual afx_msg LRESULT OnMsgExperFinished(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgSegmentOver
	// 作用：响应 Windows 或自定义消息 OnMsgSegmentOver。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgSegmentOver(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgMeltOneTemOver
	// 作用：响应 Windows 或自定义消息 OnMsgMeltOneTemOver。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgMeltOneTemOver(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgExperTempChanged
	// 作用：响应 Windows 或自定义消息 OnMsgExperTempChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgExperTempChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgExperStepChanged
	// 作用：响应 Windows 或自定义消息 OnMsgExperStepChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgExperStepChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgRunPowerOffProtect
	// 作用：响应 Windows 或自定义消息 OnMsgRunPowerOffProtect。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgRunPowerOffProtect(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgExperimentDisconnect
	// 作用：响应 Windows 或自定义消息 OnMsgExperimentDisconnect。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgExperimentDisconnect(WPARAM wParam,LPARAM lParam);

	// 函数 OnMsgInstrumentSelected
	// 作用：响应 Windows 或自定义消息 OnMsgInstrumentSelected。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgInstrumentSelected(WPARAM wParam,LPARAM lParam);

	// 函数 SetPageSelected
	// 作用：设置SetPageSelected。
	// 参数：eSonPageType；bInit：是或否。
	// 返回：没有返回值。
	void SetPageSelected(ESON_PAGE_TYPE eSonPageType,BOOL bInit = FALSE);

			// 函数 UpdateFuncBtMode
			// 作用：更新或清除UpdateFuncBtMode。
			// 参数：无。
			// 返回：没有返回值。
			void UpdateFuncBtMode();
			
			// 函数 SetPageId
			// 作用：设置SetPageId。
			// 参数：pageId。
			// 返回：没有返回值。
			void SetPageId(int pageId);
			// 函数 GetPageId
			// 作用：读取GetPageId。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetPageId();
			// 函数 Save
			// 作用：把Save写入文件、仪器或界面。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int Save();
			// 函数 SaveAsFile
			// 作用：把SaveAsFile写入文件、仪器或界面。
			// 参数：bTemplate：是或否。
			// 返回：返回是或否。
			BOOL SaveAsFile(BOOL bTemplate);
			// 函数 Delete
			// 作用：更新或清除Delete。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int Delete();

			// 函数 ExportCompleteInfo
			// 作用：执行ExportCompleteInfo。
			// 参数：strFilePath：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportCompleteInfo(CString strFilePath);	//导出完整实验数据及信息,bNoData:标识是否只导出结果报告和仪器信息
			// 函数 ExportTemperature
			// 作用：执行ExportTemperature。
			// 参数：strFilePath：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportTemperature(CString strFilePath = _T(""));	//导出温度

			// 函数 ExportPS96ResultSheet
			// 作用：执行ExportPS96ResultSheet。
			// 参数：pBook：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportPS96ResultSheet(libxl::Book* pBook);
			// 函数 ExprotPS96OldResultSheet
			// 作用：执行ExprotPS96OldResultSheet。
			// 参数：pBook：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExprotPS96OldResultSheet(libxl::Book* pBook);
			// 函数 ExportResultSheet
			// 作用：执行ExportResultSheet。
			// 参数：pBook：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportResultSheet(libxl::Book* pBook);

			// 函数 ExportInstrumentInfoSheet
			// 作用：执行ExportInstrumentInfoSheet。
			// 参数：pBook：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportInstrumentInfoSheet(libxl::Book* pBook);
			// 函数 ExportTubeInfoSheet
			// 作用：执行ExportTubeInfoSheet。
			// 参数：pBook：指针，指向调用方传入的对象；eSamExportMode。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportTubeInfoSheet(libxl::Book* pBook,ESAMINFOEXPORTMODE eSamExportMode);
			// 函数 ExportAmlDataSheet
			// 作用：执行ExportAmlDataSheet。
			// 参数：pBook：指针，指向调用方传入的对象；eSamExportMode。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportAmlDataSheet(libxl::Book* pBook,ESAMINFOEXPORTMODE eSamExportMode);
			// 函数 ExportTemperatureLogSheet
			// 作用：执行ExportTemperatureLogSheet。
			// 参数：pBook：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportTemperatureLogSheet(libxl::Book* pBook);

			// 函数 Analyse
			// 作用：计算Analyse。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int Analyse();
			// 函数 SetCrossParam
			// 作用：设置SetCrossParam。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCrossParam();
			// 函数 SetFilterParam
			// 作用：设置SetFilterParam。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetFilterParam();
			// 函数 SetBaseSet
			// 作用：设置SetBaseSet。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetBaseSet();
			// 函数 SetMotChannelAdjust
			// 作用：设置SetMotChannelAdjust。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetMotChannelAdjust();
			// 函数 SetMeltAnalyseParam
			// 作用：设置SetMeltAnalyseParam。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetMeltAnalyseParam();	//编辑熔曲分析参数信息

			// 函数 SaveProject
			// 作用：把SaveProject写入文件、仪器或界面。
			// 参数：iIndex：整数；bNew：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SaveProject(int iIndex,BOOL bNew);	//项目已被保存，更新到实验页面
			// 函数 DeleteProject
			// 作用：更新或清除DeleteProject。
			// 参数：iIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteProject(int iIndex);	//删除一个项目
			// 函数 SetDefaultGeneName
			// 作用：设置SetDefaultGeneName。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultGeneName();

			// 函数 SynchronizeExperimentSet
			// 作用：执行SynchronizeExperimentSet。
			// 参数：无。
			// 返回：没有返回值。
			void SynchronizeExperimentSet();	//同步实验设置信息
			// 函数 SynchronizeSampleSet
			// 作用：执行SynchronizeSampleSet。
			// 参数：无。
			// 返回：没有返回值。
			void SynchronizeSampleSet();
			// 函数 SynchronizeExperimentSetOnReAnalyse
			// 作用：执行SynchronizeExperimentSetOnReAnalyse。
			// 参数：无。
			// 返回：没有返回值。
			void SynchronizeExperimentSetOnReAnalyse();	//同步实验设置信息，重分析功能使用

	// 函数 Run
	// 作用：执行Run。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int Run();	//运行
	// 函数 RunPowerOffProtectExperiment
	// 作用：执行RunPowerOffProtectExperiment。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int RunPowerOffProtectExperiment();	//运行断电保护实验
	// 函数 Stop
	// 作用：执行Stop。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int Stop();	//停止

	// 函数 RefreshExpDlgRunState
	// 作用：更新或清除RefreshExpDlgRunState。
	// 参数：bOccupy：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int RefreshExpDlgRunState(BOOL bOccupy);

			// 函数 SetInstrumentLidTem
			// 作用：设置SetInstrumentLidTem。
			// 参数：iLidtem：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetInstrumentLidTem(int iLidtem);	//设置仪器EEPROM里的热盖温度
			// 函数 ReadInstrumentLidTem
			// 作用：读取ReadInstrumentLidTem。
			// 参数：dLidtem：小数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadInstrumentLidTem(double& dLidtem);	//读取仪器EEPROM里的热盖温度

			// 函数 SetInstrumentLidPreheatTem
			// 作用：设置SetInstrumentLidPreheatTem。
			// 参数：iLidtem：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetInstrumentLidPreheatTem(int iLidtem);	//设置仪器EEPROM里的热盖预热温度
			// 函数 ReadInstrumentLidPreheatTem
			// 作用：读取ReadInstrumentLidPreheatTem。
			// 参数：fLidtem：小数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReadInstrumentLidPreheatTem(float& fLidtem);	//读取仪器EEPROM里的热盖预热温度
			// 函数 TransportLock
			// 作用：执行TransportLock。
			// 参数：strErrInfo：字符串。
			// 返回：返回是或否。
			BOOL TransportLock(CString &strErrInfo);

			// 函数 InitExperimentData
			// 作用：初始化InitExperimentData。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			virtual void InitExperimentData(CExperimentData* pExpData);

			// 函数 Export
			// 作用：执行Export。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int Export();	//导出功能
			// 函数 ExportPicture
			// 作用：执行ExportPicture。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportPicture();
			// 函数 Import
			// 作用：读入Import。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int Import();	//导入功能
			// 函数 ExportResult
			// 作用：执行ExportResult。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportResult();
			// 函数 ExportResultReport
			// 作用：执行ExportResultReport。
			// 参数：strFilename：字符串；strFilename2：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportResultReport(CString strFilename, CString strFilename2);
			// 函数 ExportResultReportToCSV
			// 作用：执行ExportResultReportToCSV。
			// 参数：strFileExcel：字符串；strFilCSV：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ExportResultReportToCSV(CString strFileExcel, CString strFilCSV);

			// 函数 GetAverageLidTem
			// 作用：读取GetAverageLidTem。
			// 参数：无。
			// 返回：返回一个小数。
			double GetAverageLidTem();
			// 函数 GetAveragePeltiaTem
			// 作用：读取GetAveragePeltiaTem。
			// 参数：无。
			// 返回：返回一个小数。
			double GetAveragePeltiaTem();
			// 函数 PeltiaTemAmend
			// 作用：执行PeltiaTemAmend。
			// 参数：dTem：小数；dAmendScope：小数。
			// 返回：返回一个小数。
			double PeltiaTemAmend(double dTem,double dAmendScope = 3.0);
			// 函数 LidTemAmend
			// 作用：执行LidTemAmend。
			// 参数：dTem：小数；dAmendScope：小数。
			// 返回：返回一个小数。
			double LidTemAmend(double dTem,double dAmendScope = 3.0);

			// 函数 InitFluBackUp
			// 作用：初始化InitFluBackUp。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int InitFluBackUp();	//初始化“保存实验荧光数据”excel文件

			// 函数 ClearBackupFileParam
			// 作用：更新或清除ClearBackupFileParam。
			// 参数：无。
			// 返回：没有返回值。
			void ClearBackupFileParam();	//清空荧光数据备份文件（excel文件）相关参数

	// 函数 SetEditMode
	// 作用：设置SetEditMode。
	// 参数：eExpEditMode。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int SetEditMode(EEXPEDITMODE eExpEditMode);	//设置编辑模式，无限制模式、IVD模式

			// 函数 SampleDyeNameChanged
			// 作用：执行SampleDyeNameChanged。
			// 参数：iChanId：整数；strNewDyeName：字符串。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SampleDyeNameChanged(int iChanId,CString strNewDyeName);	//样本的某个通道的染料名称手动变更了，更新“通道切换按钮标识”和“分析页面阈值对应通道标识”

			// 函数 ClearExperiment
			// 作用：更新或清除ClearExperiment。
			// 参数：无。
			// 返回：没有返回值。
			void ClearExperiment();	//清空实验信息

			// 函数 FileOpened
			// 作用：执行FileOpened。
			// 参数：无。
			// 返回：没有返回值。
			void FileOpened();	//打开了一个新的实验文件或者模板

	// 函数 SetTemplateListSelectedRow
	// 作用：设置SetTemplateListSelectedRow。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	virtual void SetTemplateListSelectedRow(int iIndex);	//设置模板文件列表选中行

	// 函数 NewTemplateAdded
	// 作用：执行NewTemplateAdded。
	// 参数：iIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int NewTemplateAdded(int iIndex);	//新的模板文件成功添加

			// 函数 GetBeExportData
			// 作用：读取GetBeExportData。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetBeExportData();	//导出实验数据时，判断是否导出荧光信号相关信息

			// 函数 IsExpRunning
			// 作用：判断IsExpRunning是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsExpRunning();

			// 函数 SetGradientFuncShieldState
			// 作用：设置SetGradientFuncShieldState。
			// 参数：bData：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetGradientFuncShieldState(BOOL bData);	//设置梯度功能屏蔽状态
			// 函数 SetTemperatureRateShowState
			// 作用：设置SetTemperatureRateShowState。
			// 参数：bData：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetTemperatureRateShowState(BOOL bData);

			// 函数 SetPowerOffExpInfo
			// 作用：设置SetPowerOffExpInfo。
			// 参数：runPrgRcd。
			// 返回：没有返回值。
			void SetPowerOffExpInfo(CRunProgressRecord runPrgRcd);

			// 函数 GetAllSampleType
			// 作用：读取GetAllSampleType。
			// 参数：vecSamType。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetAllSampleType(vector<eSampleType>& vecSamType);	//按下标顺序获取孔板的样本类型信息

			// 函数 UploadInspectResultToLis
			// 作用：执行UploadInspectResultToLis。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int UploadInspectResultToLis();	//上传检测结果到LIS 系统

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

			// 函数 RefreshExpTotalTime
			// 作用：更新或清除RefreshExpTotalTime。
			// 参数：iTotalSec：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshExpTotalTime(int iTotalSec);

			// 函数 SetCurveHoriAxisParam
			// 作用：设置SetCurveHoriAxisParam。
			// 参数：无。
			// 返回：没有返回值。
			void SetCurveHoriAxisParam();

	// 函数 SetExpDataPtr
	// 作用：设置SetExpDataPtr。
	// 参数：pExpData：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	virtual void SetExpDataPtr(CExperimentData* pExpData);
	// 函数 EmbodyBaseSetInfo
	// 作用：执行EmbodyBaseSetInfo。
	// 参数：无。
	// 返回：没有返回值。
	virtual void EmbodyBaseSetInfo();	//显示实验文件中的基本设置信息
	// 函数 RefreshExpEmbody
	// 作用：更新或清除RefreshExpEmbody。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void RefreshExpEmbody();
	// 函数 DeleteTemplateListRow
	// 作用：更新或清除DeleteTemplateListRow。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	virtual	void DeleteTemplateListRow(int iIndex);

	// 函数 GetBeDataAnaDlgVisible
	// 作用：读取GetBeDataAnaDlgVisible。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeDataAnaDlgVisible();
	// 函数 ResetTubeInfo
	// 作用：更新或清除ResetTubeInfo。
	// 参数：vecPlateSelectedSite；vecTubeInfo；iFlag：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ResetTubeInfo(vector<int> &vecPlateSelectedSite,vector<CTubeInfo> &vecTubeInfo, int iFlag);	//选择项目页面样本信息改变后，同步到样本登记页面

	// 函数 SetChannelDyeBtn
	// 作用：设置SetChannelDyeBtn。
	// 参数：无。
	// 返回：没有返回值。
	void SetChannelDyeBtn();
	// 函数 OnMsgChanBtClicked
	// 作用：响应 Windows 或自定义消息 OnMsgChanBtClicked。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgChanBtClicked(WPARAM wParam,LPARAM lParam);
	// 函数 SetConnectState
	// 作用：设置SetConnectState。
	// 参数：bRunExp：是或否。
	// 返回：没有返回值。
	virtual void SetConnectState(BOOL bRunExp);
	// 函数 SetRunBtnState
	// 作用：设置SetRunBtnState。
	// 参数：bRunning：是或否。
	// 返回：没有返回值。
	void SetRunBtnState(BOOL bRunning);

	// 函数 SetInstrumentConnectState
	// 作用：设置SetInstrumentConnectState。
	// 参数：strModel：字符串；strSN：字符串；bConnected：是或否。
	// 返回：没有返回值。
	void SetInstrumentConnectState(CString strModel, CString strSN, BOOL bConnected);
	// 函数 ReshowInstrumentList
	// 作用：执行ReshowInstrumentList。
	// 参数：无。
	// 返回：没有返回值。
	virtual void ReshowInstrumentList();
	// 函数 SetSelectedInstrument
	// 作用：设置SetSelectedInstrument。
	// 参数：strModel：字符串；strSN：字符串。
	// 返回：没有返回值。
	virtual void SetSelectedInstrument(CString strModel, CString strSN);

	// 函数 ExportPS96ResultSheetFormat
	// 作用：执行ExportPS96ResultSheetFormat。
	// 参数：pBook：指针，指向调用方传入的对象；pSheetId：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void ExportPS96ResultSheetFormat(libxl::Book* pBook, libxl::Sheet* pSheetId);
	// 函数 ExportPS96ResultSheetRectBorder
	// 作用：执行ExportPS96ResultSheetRectBorder。
	// 参数：pBook：指针，指向调用方传入的对象；pSheetId：指针，指向调用方传入的对象；iStartRow：整数；iStartCol：整数；iEndRow：整数；iEndCol：整数。
	// 返回：没有返回值。
	void ExportPS96ResultSheetRectBorder(libxl::Book* pBook, libxl::Sheet* pSheetId, int iStartRow, int iStartCol, int iEndRow, int iEndCol);
	// 函数 ExportPS96ResultWriteStrBold
	// 作用：执行ExportPS96ResultWriteStrBold。
	// 参数：pBook：指针，指向调用方传入的对象；pSheetId：指针，指向调用方传入的对象；iRow：整数；iCol：整数；strText：字符串；iFontSize：整数。
	// 返回：没有返回值。
	void ExportPS96ResultWriteStrBold(libxl::Book* pBook, libxl::Sheet* pSheetId, int iRow, int iCol, CString strText, int iFontSize=-1);
	// 函数 ExportPS96ResultWriteStrUnderline
	// 作用：执行ExportPS96ResultWriteStrUnderline。
	// 参数：pBook：指针，指向调用方传入的对象；pSheetId：指针，指向调用方传入的对象；iRow：整数；iCol：整数；strText：字符串。
	// 返回：没有返回值。
	void ExportPS96ResultWriteStrUnderline(libxl::Book* pBook, libxl::Sheet* pSheetId, int iRow, int iCol, CString strText);
	// 函数 ExportPS96ResultWriteStrTitle
	// 作用：执行ExportPS96ResultWriteStrTitle。
	// 参数：pBook：指针，指向调用方传入的对象；pSheetId：指针，指向调用方传入的对象；iRow：整数；iCol：整数；strText：字符串；iFontSize：整数。
	// 返回：没有返回值。
	void ExportPS96ResultWriteStrTitle(libxl::Book* pBook, libxl::Sheet* pSheetId, int iRow, int iCol, CString strText, int iFontSize=-1);

private:
	// 函数 ExportMeltData
	// 作用：执行ExportMeltData。
	// 参数：pBook：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ExportMeltData(libxl::Book* pBook);	//导出熔曲数据

public: 
	int	m_iFunBtnHeight;
	CFuncBtDlg m_funcBtDlg;

	CMyButton m_swtBaseSet;
	CMyButton m_swtSelectPrj;
	CMyButton m_swtSamSet;
	CMyButton m_swtRunMonitor;
	CMyButton m_swtDataAna;

	CMyButton m_btnRunStop; 
	CMyStatic m_stcConnectState;
	CRect	m_rectConntectState;

	CMyButton* m_pCurSelSwt;
	CDialogEx* m_pCurSelDlg;


	ESON_PAGE_TYPE m_curSelSonPage;

	int m_pageId;

	CExperimentData* m_pExpData;	//创建窗口后保实验数据对象指针，方便操作

	CLinkList<double> m_lnkLidTem;	//记录热盖温度，滤波使用
	CLinkList<double> m_lnkPeltiaTem;	//记录帕尔贴温度，滤波使用

	int m_iCurCycle;
	int m_iCurSeg;
	int m_iCurStep;

	CExpRunCtrl* m_pRunCtrl; // 实验运行线程

protected:
	Son_Page_Type m_nSelPageID;
	CBaseSetDlg m_baseSetDlg;
	CProcSetDlg m_selPrjDlg;
	CSamSetDlg m_samSetDlg;
	CRunMonitorDlg m_runMonitorDlg;
	CDataAnaDlg m_dataAnaDlg;

	BOOL	m_bExpRunning;
	BOOL	m_bCtrlCreated;
	BOOL	m_bInstruConnected;

protected:

	//保存荧光备份数据
	libxl::Book* m_pBook;
	libxl::Sheet** m_ppSheet;
	CString m_strBackupFilePath;	//保存备份文件的完整路径名

	CRunProgressRecord m_runRrgRcd;	//运行断电保护实验时，传入的断电保护实验信息
	BOOL m_bPowerOffExp;	//标识是否是断电保护实验 继续运行的实验


	int m_iColCount;
	int m_iStartCol;
	int m_iFirstPaneStart; // 第1区域行数
	int m_iFirstPaneEnd;
	int m_iSecondPaneStart; 
	int m_iSecondPaneEnd; 
	int m_iThirdPaneStart; 
	int m_iThirdPaneEnd; 
	int m_iFourthPaneStart; 
	int m_iFourthPaneEnd; 
};




