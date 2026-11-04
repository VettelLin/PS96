// 【交接】 GeneralPcr\AnaMeltParamDlg.h
// 作用：AnaMeltParamDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CAnaMeltParamDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnCreate、OnLButtonDown、OnInitDialog。

#pragma once

#include "MyButton.h"
#include "MyLstCtrl.h"
#include "ExperimentData.h"
#include "MeltAnaParamChangeInfo.h"

typedef enum MeltParamChangeType{
	EMPCT_NONE,EMPCT_PEAKTHRESHOLD,EMPCT_LOWERTEM,EMPCT_HIGHTEM
}EMELTPARAMCHANGETYPE;

class CAnaMeltParamDlg : public CDialogEx,public CFontSet
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CAnaMeltParamDlg。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CAnaMeltParamDlg)

public:
	// 函数 CAnaMeltParamDlg
	// 作用：执行CAnaMeltParamDlg。
	// 参数：pExpData：指针，指向调用方传入的对象；pParent：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CAnaMeltParamDlg(CExperimentData* pExpData,CWnd* pParent = NULL);   // standard constructor
	// 函数 ~CAnaMeltParamDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CAnaMeltParamDlg();

	enum { IDD = IDD_POPUPDLG};

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
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnInitDialog
	// 作用：对话框创建后做初始化。
	// 参数：无。
	// 返回：返回是或否。
	virtual BOOL OnInitDialog();
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
			// 函数 CreateCkBt
			// 作用：创建或加入CreateCkBt。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCkBt();
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
			// 函数 CreateCb
			// 作用：创建或加入CreateCb。
			// 参数：无。
			// 返回：没有返回值。
			void CreateCb();
			// 函数 CreateLst
			// 作用：创建或加入CreateLst。
			// 参数：无。
			// 返回：没有返回值。
			void CreateLst();
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
			// 函数 InitCkBt
			// 作用：初始化InitCkBt。
			// 参数：无。
			// 返回：没有返回值。
			void InitCkBt();
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
			// 函数 InitCb
			// 作用：初始化InitCb。
			// 参数：无。
			// 返回：没有返回值。
			void InitCb();
			// 函数 InitLst
			// 作用：初始化InitLst。
			// 参数：无。
			// 返回：没有返回值。
			void InitLst();
			// 函数 InitLstCrossSet
			// 作用：初始化InitLstCrossSet。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstCrossSet();
			// 函数 InitLstMeltParam
			// 作用：初始化InitLstMeltParam。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstMeltParam();

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

	// 函数 OnBnClickedSave
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSave();
	// 函数 OnBnClickedCancel
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedCancel();

			// 函数 SetRoundRect
			// 作用：设置SetRoundRect。
			// 参数：x；y。
			// 返回：返回是或否。
			BOOL SetRoundRect(int x = 5,int y = 5);

			// 函数 SetCrossSetParam
			// 作用：设置SetCrossSetParam。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetCrossSetParam();
			// 函数 GetCrossSetParam
			// 作用：读取GetCrossSetParam。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetCrossSetParam();

			// 函数 SetLstMeltParam
			// 作用：设置SetLstMeltParam。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetLstMeltParam();
			// 函数 GetLstMeltParam
			// 作用：读取GetLstMeltParam。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetLstMeltParam();

			// 函数 SetColumnRowNum
			// 作用：设置SetColumnRowNum。
			// 参数：iChanNum：整数；bRedraw：是或否。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int SetColumnRowNum(int iChanNum,BOOL bRedraw = FALSE);

public:
	CMyLstCtrl m_lstCrossSet;
	CMyLstCtrl m_lstMeltParam;	//熔解曲线参数

	CMyButton m_btSave;
	CMyButton m_btCancel;

	CExperimentData* m_pExpData;

	BOOL m_bCrossParamChanged;	//标识熔曲使用的串扰系数是否改变
	CMeltAnaParamChangeInfo m_meltAnaParamChangeInfo;	//标识熔曲分析参数是否改变

private:
	int m_roundValue;	//圆角数值
	int m_frameWidth;	//边框宽度

	int m_iWndWidth;	//窗口宽度
	int m_iWndHeight;	//窗口高度
	int m_iCaptionHeight;	//标题栏高度
};
