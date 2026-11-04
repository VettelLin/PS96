// 【交接】 GeneralPcr\SamBaseInfoEditDlg.h
// 作用：SamBaseInfoEditDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：DECLARE_DYNAMIC、CSamBaseInfoEditDlg、DoDataExchange、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnSize、OnLButtonDown、OnMsgTellParentTextChanged。
#pragma once

#include "FontSet.h"
#include "Resource.h"
#include "MyNewCb.h"
#include "MyNewEdit.h"
#include "MyLstCtrl.h"
#include "TubeInfo.h"
#include "InterfaceA.h"
#include "EditModeAbs.h"
#include "RectManage.h"

//class CProcSetDlg;

class CSamBaseInfoEditDlg: public CDialogEx,public CFontSet,public CEditModeAbs
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CSamBaseInfoEditDlg：字符串。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CSamBaseInfoEditDlg)

public:
	// 函数 CSamBaseInfoEditDlg
	// 作用：执行CSamBaseInfoEditDlg。
	// 参数：pParent：指针，指向调用方传入的对象；pInterfaceA：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CSamBaseInfoEditDlg(CWnd* pParent = NULL,CInterfaceA* pInterfaceA = NULL);
	// 函数 ~CSamBaseInfoEditDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	~CSamBaseInfoEditDlg(void);

	enum {IDD = IDD_POPUPDLG};

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
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnMsgTellParentTextChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentTextChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentTextChanged(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgTellParentLstCellChanged
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentLstCellChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentLstCellChanged(WPARAM wParam, LPARAM lParam);
	// 函数 OnMsgListDeleteComboRowString
	// 作用：响应 Windows 或自定义消息 OnMsgListDeleteComboRowString。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgListDeleteComboRowString(WPARAM wParam, LPARAM lParam);

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
			// 函数 InitLstSamBaseInfo
			// 作用：初始化InitLstSamBaseInfo。
			// 参数：无。
			// 返回：没有返回值。
			void InitLstSamBaseInfo();
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

			// 函数 AddChannel
			// 作用：创建或加入AddChannel。
			// 参数：pDyeChanInfo：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void AddChannel(tagDyeChannelInfo* pDyeChanInfo);

			// 函数 SetDefaultGeneName
			// 作用：设置SetDefaultGeneName。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultGeneName();	//设置默认的基因选择集合
			// 函数 SetDefaultColor
			// 作用：设置SetDefaultColor。
			// 参数：无。
			// 返回：没有返回值。
			void SetDefaultColor();	//初始化页面时，设置列表框行的默认颜色
			// 函数 SetDefaultDyeName
			// 作用：设置SetDefaultDyeName。
			// 参数：vecDyeName。
			// 返回：没有返回值。
			void SetDefaultDyeName(vector<CString>& vecDyeName);	//初始化页面时，设置默认的染料名

			// 函数 Clear
			// 作用：更新或清除Clear。
			// 参数：无。
			// 返回：没有返回值。
			void Clear();

			// 函数 SetEditableState
			// 作用：设置SetEditableState。
			// 参数：bEditable：是或否。
			// 返回：没有返回值。
			void SetEditableState(BOOL bEditable);
			// 函数 GetEditableState
			// 作用：读取GetEditableState。
			// 参数：无。
			// 返回：返回是或否。
			BOOL GetEditableState();

			// 函数 SetTubeInfo
			// 作用：设置SetTubeInfo。
			// 参数：info；bSetDensityEditState：是或否。
			// 返回：没有返回值。
			void SetTubeInfo(CTubeInfo& info,BOOL bSetDensityEditState);
			// 函数 SetDensityEditableState
			// 作用：设置SetDensityEditableState。
			// 参数：bEditable：是或否。
			// 返回：没有返回值。
			void SetDensityEditableState(BOOL bEditable);

			// 函数 LstRowHeightAutoFit
			// 作用：执行LstRowHeightAutoFit。
			// 参数：iChanCount：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int LstRowHeightAutoFit(int iChanCount);	//打开文件后，根据文件中的通道数，自动设置行高

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

public:
	CString m_strTitle;

	CMyNewCb m_cbSamType;
	CMyNewCb m_cbRepeatTubeNumber;
	CMyNewEdit m_edSamId;

	CMyLstCtrl m_lstSamBaseInfo;

private:
	int m_iWidth;	//窗口宽度
	int m_iHeight;	//窗口高度
	int m_iHeaderH;	//标题高度

	int m_roundValue;	//圆角数值
	int m_frameWidth;	//边框宽度

	BOOL m_bEditabe;	//窗口是否可编辑状态

	CInterfaceA* m_pInterfaceA;

	BOOL m_bDensityEditable;	//标识列表框的第五列是否处于可编辑状态

	CRectManage m_rcManage;

	BOOL m_bCtrlCreated;
};

