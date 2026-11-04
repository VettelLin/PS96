// 【交接】 GeneralPcr\LoadSamDlg.h
// 作用：LoadSamDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CLoadSamDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnBnClickedLoadId、OnInitDialog。

#pragma once

#include "FontSet.h"
#include "MyButton.h"
#include "MySamPlateDlg.h"
#include "LegendInfo.h"
#include "RectManage.h"
#include "ExperimentData.h"
#include "EditModeAbs.h"
#include "Resource.h"
#include "MySegDlg.h"

class CPs96SimpleDlg;

class CLoadSamDlg : public CDialogEx,public CFontSet,public CEditModeAbs
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CLoadSamDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CLoadSamDlg)

public:
	// 函数 CLoadSamDlg
	// 作用：执行CLoadSamDlg。
	// 参数：pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CLoadSamDlg(CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CLoadSamDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CLoadSamDlg();

	enum { IDD = IDD_MIDDLEDLG };

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
	afx_msg void OnSize(UINT nType,int cx,int cy);
	// 函数 OnBnClickedLoadId
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedLoadId();
	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
			
			// 函数 InitSegLegend
			// 作用：初始化InitSegLegend。
			// 参数：无。
			// 返回：没有返回值。
			void InitSegLegend();

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
			// 函数 CreateCkbt
			// 作用：创建或加入CreateCkbt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCkbt();
			// 函数 CreateSt
			// 作用：创建或加入CreateSt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateSt();
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
			// 函数 InitDlg
			// 作用：初始化InitDlg。
			// 参数：无。
			// 返回：没有返回值。
			void InitDlg();
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
			// 函数 InitOneBt
			// 作用：初始化InitOneBt。
			// 参数：pBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitOneBt(CMyButton* pBt);
			// 函数 InitCkbt
			// 作用：初始化InitCkbt。
			// 参数：无。
			// 返回：没有返回值。
			void InitCkbt();
			// 函数 InitSt
			// 作用：初始化InitSt。
			// 参数：无。
			// 返回：没有返回值。
			void InitSt();
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
			// 函数 InitSegment
			// 作用：初始化InitSegment。
			// 参数：无。
			// 返回：没有返回值。
			void InitSegment();

			// 函数 SetCtrlText
			// 作用：设置SetCtrlText。
			// 参数：无。
			// 返回：没有返回值。
			void SetCtrlText();

			// 函数 RefreshExpEmbody
			// 作用：更新或清除RefreshExpEmbody。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int RefreshExpEmbody();
			// 函数 ClearExpEmbody
			// 作用：更新或清除ClearExpEmbody。
			// 参数：无。
			// 返回：没有返回值。
			void ClearExpEmbody();

			// 函数 ImportId
			// 作用：读入ImportId。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ImportId();

			// 函数 SetEditMode
			// 作用：设置SetEditMode。
			// 参数：eExpEditMode。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetEditMode(EEXPEDITMODE eExpEditMode);

			// 函数 SetExpDataPtr
			// 作用：设置SetExpDataPtr。
			// 参数：pExpData：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void SetExpDataPtr(CExperimentData* pExpData);
			// 函数 CurrentSegmentStepChangedOnRun
			// 作用：执行CurrentSegmentStepChangedOnRun。
			// 参数：iCycle：整数；iSeg：整数；iStep：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int CurrentSegmentStepChangedOnRun(int iCycle,int iSeg,int iStep);

public:
	CMyButton m_btLoad;

	CMySamPalteDlg m_samPlateDlg;
	CLegendInfo m_segLgdInfo;	//样本信息控件图例

	CMyButton m_swtBtSegMonitor;
	CMySegDlg m_segDlg;


	CExperimentData* m_pExpData;
	CPs96SimpleDlg* m_pParent;

private:
	BOOL m_bCtrlCreated;
	CRectManage m_rcManage;
};



