// 【交接】 GeneralPcr\SamSetDlg.h
// 作用：SamSetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CSamSetDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnCreate、OnBnClickedSwtBtPlate。
#pragma once

#include "MySamPlateDlg.h"
#include "SamLst.h"
#include "SamInfoDlg.h"
#include "SelfDefType.h"
#include "ExperimentData.h"
#include "LegendInfo.h"
#include "EditModeAbs.h"
#include "RectManage.h"
#include "InterfaceC.h"
#include "CYSamInfoDlg.h"

typedef enum _ESamDisplayMode
{
	SAMPLATE = 1,SAMCHART
}ESAMDISPALYMODE;

class CMiddleDlg;

class CSamSetDlg : public CDialogEx,public CFontSet,public CEditModeAbs,public CInterfaceC
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CSamSetDlg：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CSamSetDlg)

public:
	// 函数 CSamSetDlg
	// 作用：执行CSamSetDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CSamSetDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CSamSetDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CSamSetDlg();

// Dialog Data
	enum { IDD = IDD_SAMSETDLG };

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
	// 函数 OnBnClickedSwtBtPlate
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtPlate();
	// 函数 OnBnClickedSwtBtChart
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtBtChart();
	// 函数 OnMsgPlateSiteSelectChanged
	// 作用：响应 Windows 或自定义消息 OnMsgPlateSiteSelectChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgPlateSiteSelectChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgLstSelectChanged
	// 作用：响应 Windows 或自定义消息 OnMsgLstSelectChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgLstSelectChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgSamplateDeleteKeyPressed
	// 作用：响应 Windows 或自定义消息 OnMsgSamplateDeleteKeyPressed。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgSamplateDeleteKeyPressed(WPARAM wParam, LPARAM lParam);

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

			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：eSamDisplayMode。
			// 返回：没有返回值。
			void SetPageSelected(ESAMDISPALYMODE eSamDisplayMode);

			// 函数 SetRowColNum
			// 作用：设置SetRowColNum。
			// 参数：iRowNum：整数；iColNum：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRowColNum(int iRowNum,int iColNum);

			// 函数 ReSetLstSamInfo
			// 作用：执行ReSetLstSamInfo。
			// 参数：vecSamInfoPtr；bRedraw：是或否。
			// 返回：没有返回值。
			void ReSetLstSamInfo(vector<CTubeInfo*>& vecSamInfoPtr,BOOL bRedraw = FALSE);
			// 函数 ReSetLstSamInfo
			// 作用：执行ReSetLstSamInfo。
			// 参数：vecSamInfo；bRedraw：是或否。
			// 返回：没有返回值。
			void ReSetLstSamInfo(vector<CTubeInfo>& vecSamInfo,BOOL bRedraw = FALSE);
			// 函数 ReSetLstSamInfo
			// 作用：执行ReSetLstSamInfo。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void ReSetLstSamInfo(BOOL bRedraw = FALSE);

			// 函数 SetLstSamInfo
			// 作用：设置SetLstSamInfo。
			// 参数：index；tubeInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLstSamInfo(int index,CTubeInfo& tubeInfo);
			// 函数 SetLstSamInfo
			// 作用：设置SetLstSamInfo。
			// 参数：index；tubeInfo；eItemInfoType。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLstSamInfo(int index,CTubeInfo& tubeInfo,EITEMINFOTYPE eItemInfoType);

			// 函数 LstSamLanguageChanged
			// 作用：执行LstSamLanguageChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int LstSamLanguageChanged();

	// 函数 SetPlateSelectedSiteSamInfo
	// 作用：设置SetPlateSelectedSiteSamInfo。
	// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
	// 返回：没有返回值。
	virtual void SetPlateSelectedSiteSamInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData = 0,double dData = 0);
			// 函数 CYSamInfoChangedProcess
			// 作用：执行CYSamInfoChangedProcess。
			// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CYSamInfoChangedProcess(EITEMINFOTYPE eItemInfoType,CString strData,int intData = 0,double dData = 0);		

			// 函数 AutoSetPlateSelectedSiteSamId
			// 作用：执行AutoSetPlateSelectedSiteSamId。
			// 参数：samNameAutoSetInfo。
			// 返回：没有返回值。
			void AutoSetPlateSelectedSiteSamId(CSamNameAutoSetInfo samNameAutoSetInfo);
			// 函数 AutoSetPlateSelectedSiteCalibratorDensity
			// 作用：执行AutoSetPlateSelectedSiteCalibratorDensity。
			// 参数：calibAutoSetInfo。
			// 返回：没有返回值。
			void AutoSetPlateSelectedSiteCalibratorDensity(CCalibAutoSetInfo calibAutoSetInfo);

			// 函数 ReSetTubeInfo
			// 作用：执行ReSetTubeInfo。
			// 参数：vecPlateSelectedSite；vecTubeInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReSetTubeInfo(vector<int> &vecPlateSelectedSite,vector<CTubeInfo> &vecTubeInfo);	//选择项目页面样本信息改变后，同步到样本登记页面
			// 函数 ResetProcSetDlgTubeInfo
			// 作用：更新或清除ResetProcSetDlgTubeInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ResetProcSetDlgTubeInfo();

			// 函数 ClearPage
			// 作用：更新或清除ClearPage。
			// 参数：bRedraw：是或否。
			// 返回：没有返回值。
			void ClearPage(BOOL bRedraw = TRUE);
			// 函数 FileOpened
			// 作用：执行FileOpened。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int FileOpened(CExperimentData* pExpData = NULL);

			// 函数 DeleteSelectedSampleInfo
			// 作用：更新或清除DeleteSelectedSampleInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteSelectedSampleInfo();	//删除选中孔位的样本信息

			// 函数 ResetLstTitle
			// 作用：更新或清除ResetLstTitle。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstTitle();
			// 函数 ResetLstColumnWidth
			// 作用：更新或清除ResetLstColumnWidth。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstColumnWidth();

			// 函数 RefreshLanguageDisplay
			// 作用：更新或清除RefreshLanguageDisplay。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshLanguageDisplay();

	// 函数 SetEditMode
	// 作用：设置SetEditMode。
	// 参数：eExpEditMode。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int SetEditMode(EEXPEDITMODE eExpEditMode);

public:
	CMySamPalteDlg m_samPlateDlg;
	CSamLst m_lstSamInfo;

#ifdef CAN_YOUNG
	CCYSamInfoDlg m_samInfoDlg;
#else
	CSamInfoDlg m_samInfoDlg;
#endif
	
	CMyButton m_swtBtPlate;
	CMyButton m_swtBtChart;

	CMiddleDlg* m_pParent;

	vector<int> m_vecPlateSamIndex;	//存储列表框每行对应的孔位下标（正向正序）

	vector<int> m_vecCurSelSite;	//记录当前选择的孔位

	CLegendInfo m_segLgdInfo;	//样本信息控件图例

private:
	BOOL m_bCtrlCreated;

	CMyButton* m_pCurSelSwt;
	CWnd* m_pCurSelWnd;

	int m_iSwitchBtBkH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtH;	//记录页面切换按钮外部圆角背景高度，确保高度是个偶数值
	int m_iSwitchBtBkW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值
	int m_iSwitchBtW;	//记录页面切换按钮外部圆角背景宽度，确保高度是个偶数值

	CRectManage m_rcManage;
};

#include "MiddleDlg.h"












