// 【交接】 GeneralPcr\ProcSetDlg.h
// 作用：ProcSetDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CProcSetDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnInitDialog、InitDlg。
#pragma once

#include "PrjBaseInfoDlg.h"
#include "MyButton.h"
#include "MyInsertBt.h"
#include "MyLstCtrl.h"
#include "MySegDlg.h"
#include "SamBaseInfoEditDlg.h"
#include "MySamPlateDlg.h"
#include "TubeChanEditInfo.h"
#include "ExperimentData.h"
#include "InterfaceA.h"
#include "LegendInfo.h"
#include "EditModeAbs.h"
#include "RectManage.h"
#include "InterfaceB.h"

class CMiddleDlg;

class CProcSetDlg : public CDialogEx,public CInterfaceA,public CFontSet,public CEditModeAbs,public CInterfaceB,public CRectManage
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CProcSetDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CProcSetDlg)

public:
	// 函数 CProcSetDlg
	// 作用：执行CProcSetDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CProcSetDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CProcSetDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CProcSetDlg();

// Dialog Data
	enum { IDD = IDD_PROCSETDLG };

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
			// 函数 InitSamBaseInfoEditDlg
			// 作用：初始化InitSamBaseInfoEditDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSamBaseInfoEditDlg();

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
			// 函数 CreateSeg
			// 作用：创建或加入CreateSeg。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSeg();
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
			// 函数 InitInsertBt
			// 作用：初始化InitInsertBt。
			// 参数：pInsertBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitInsertBt(CMyInsertBt *pInsertBt);
			// 函数 InitOtherBt
			// 作用：初始化InitOtherBt。
			// 参数：pBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitOtherBt(CMyButton *pBt);
			// 函数 InitLst
			// 作用：初始化InitLst。
			// 参数：无。
			// 返回：没有返回值。
			void InitLst();
			// 函数 InitLstSelectPrj
			// 作用：初始化InitLstSelectPrj。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstSelectPrj();
			// 函数 InitSamPlateDlg
			// 作用：初始化InitSamPlateDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSamPlateDlg();
			// 函数 InitSeg
			// 作用：初始化InitSeg。
			// 参数：无。
			// 返回：没有返回值。
			void InitSeg();
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

			// 函数 SetRowColNum
			// 作用：设置SetRowColNum。
			// 参数：iRowNum：整数；iColNum：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetRowColNum(int iRowNum,int iColNum);

	// 函数 SetPlateSelectedSiteSamInfo
	// 作用：设置SetPlateSelectedSiteSamInfo。
	// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
	// 返回：没有返回值。
	virtual	void SetPlateSelectedSiteSamInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/);
	// 函数 SetPlateSelectedSiteSamInfo
	// 作用：设置SetPlateSelectedSiteSamInfo。
	// 参数：tubeChanEditInfo。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual	int SetPlateSelectedSiteSamInfo(CTubeChanEditInfo tubeChanEditInfo);

			// 函数 ReSetTubeInfo
			// 作用：执行ReSetTubeInfo。
			// 参数：vecPlateSelectedSite；vecTubeInfo。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ReSetTubeInfo(vector<int> &vecPlateSelectedSite,vector<CTubeInfo> &vecTubeInfo);	//样本登记页面样本信息改变后，同步到选择项目页面
			// 函数 ResetSamSetDlgTubeInfo
			// 作用：更新或清除ResetSamSetDlgTubeInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ResetSamSetDlgTubeInfo();

	// 函数 OnBnClickedInsertSegment
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedInsertSegment();
	// 函数 OnBnClickedInsertStep
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedInsertStep();
	// 函数 OnBnClickedEditStep
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedEditStep();
	// 函数 OnBnClickedEditSegment
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedEditSegment();
	// 函数 OnBnClickedDelete
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedDelete();
	// 函数 OnBnClickedAddCycle
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedAddCycle();

	// 函数 OnFileMenuSegInsertBefore
	// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertBefore。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuSegInsertBefore();
	// 函数 OnFileMenuSegInsertAfter
	// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertAfter。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuSegInsertAfter();
	// 函数 OnFileMenuSegInsertLast
	// 作用：响应 Windows 或自定义消息 OnFileMenuSegInsertLast。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuSegInsertLast();

	// 函数 OnFileMenuStepInsertBefore
	// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertBefore。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuStepInsertBefore();
	// 函数 OnFileMenuStepInsertAfter
	// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertAfter。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuStepInsertAfter();
	// 函数 OnFileMenuStepInsertLast
	// 作用：响应 Windows 或自定义消息 OnFileMenuStepInsertLast。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnFileMenuStepInsertLast();

	// 函数 OnMsgPlateSiteSelectChanged
	// 作用：响应 Windows 或自定义消息 OnMsgPlateSiteSelectChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgPlateSiteSelectChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgRowSelectedChange
	// 作用：响应 Windows 或自定义消息 OnMsgRowSelectedChange。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgRowSelectedChange(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgSamplateDeleteKeyPressed
	// 作用：响应 Windows 或自定义消息 OnMsgSamplateDeleteKeyPressed。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgSamplateDeleteKeyPressed(WPARAM wParam, LPARAM lParam);

			// 函数 SimulatePlateSiteSelectChanged
			// 作用：执行SimulatePlateSiteSelectChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SimulatePlateSiteSelectChanged();

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
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int FileOpened(CExperimentData* pExpData = NULL);

			// 函数 SavePrj
			// 作用：把SavePrj写入文件、仪器或界面。
			// 参数：iIndex：整数；bNew：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SavePrj(int iIndex,BOOL bNew);	//项目已被保存，更新到实验页面
			// 函数 DeletePrj
			// 作用：更新或清除DeletePrj。
			// 参数：iIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeletePrj(int iIndex);	//删除一个项目

			// 函数 SetSelectPrjLstInfo
			// 作用：设置SetSelectPrjLstInfo。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSelectPrjLstInfo();	//初始化项目信息列表框，默认模式
			// 函数 SetSelectPrjLstInfoIVDNoProject
			// 作用：设置SetSelectPrjLstInfoIVDNoProject。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetSelectPrjLstInfoIVDNoProject();	//初始化项目信息列表框，IVD模式，使用模板文件，不使用项目

			// 函数 SetProjectInfo
			// 作用：设置SetProjectInfo。
			// 参数：reagentItem。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetProjectInfo(CReagentItem& reagentItem);	//设置选中的项目信息到实验数据中

			// 函数 HandleProjectLstRowSelectChanged
			// 作用：执行HandleProjectLstRowSelectChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int HandleProjectLstRowSelectChanged();	//处理项目信息列表框行选中状态改变
			// 函数 HandleTemplateFileLstRowSelectChanged
			// 作用：执行HandleTemplateFileLstRowSelectChanged。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int HandleTemplateFileLstRowSelectChanged();	//处理模板文件列表框行选中状态改变

			// 函数 SetTemplateListSelectedRow
			// 作用：设置SetTemplateListSelectedRow。
			// 参数：iIndex：整数。
			// 返回：没有返回值。
			void SetTemplateListSelectedRow(int iIndex);	//设置模板文件列表选中行
			// 函数 NewTemplateAdded
			// 作用：执行NewTemplateAdded。
			// 参数：iIndex：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int NewTemplateAdded(int iIndex,BOOL bRedraw = TRUE);	//打开了新的模板文件，添加到模板文件列表框中

			// 函数 SetGradientFuncShieldState
			// 作用：设置SetGradientFuncShieldState。
			// 参数：bData：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetGradientFuncShieldState(BOOL bData);
			// 函数 SetTemperatureRateShowState
			// 作用：设置SetTemperatureRateShowState。
			// 参数：bData：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetTemperatureRateShowState(BOOL bData);

			// 函数 GetAllSampleType
			// 作用：读取GetAllSampleType。
			// 参数：vecSamType。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetAllSampleType(vector<eSampleType>& vecSamType);

			// 函数 ResetLstTitle
			// 作用：更新或清除ResetLstTitle。
			// 参数：无。
			// 返回：没有返回值。
			void ResetLstTitle();

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

	// 函数 SetNewPrjBaseInfo
	// 作用：设置SetNewPrjBaseInfo。
	// 参数：eItemInfoType；strData：字符串；intData；dData：小数。
	// 返回：没有返回值。
	virtual void SetNewPrjBaseInfo(EITEMINFOTYPE eItemInfoType,CString strData,int intData /*= 0*/,double dData /*= 0*/);

public:
	CMyLstCtrl m_lstSelPrj;
	CPrjBaseInfoDlg m_prjBaseInfoDlg;
	CMySegDlg m_segDlg; 
	CMySamPalteDlg m_samPlateDlg;
	CSamBaseInfoEditDlg m_samBaseInfoEditDlg;

	CMiddleDlg* m_pParent;

	CMyInsertBt m_btInsertSegment;
	CMyInsertBt m_btInsertStep;
	CMyButton m_btEditStep;
	CMyButton m_btEditSegment;
	CMyButton m_btDelete;
	CMyButton m_btAddCycle;

	vector<int> m_vecPlateSelectedSite;	//记录孔板选中孔位下标
	
	CLegendInfo m_segLgdInfo;	//样本信息控件图例

private:
	BOOL m_bCtrlCreated;
};



