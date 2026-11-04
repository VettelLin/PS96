// 【交接】 GeneralPcr\Ps96SimpleDlg.h
// 作用：Ps96SimpleDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：CPs96SimpleDlg、DECLARE_MESSAGE_MAP、OnEraseBkgnd、OnBnClickedRunStop、OnBnClickedSet、OnBnClickedSwtAssaySelect、OnBnClickedSwtSamInfo、OnInitDialog。
#pragma once

#include "FontSet.h"
#include "MiddleDlg.h"
#include "AssaySelectDlg.h"
#include "LoadSamDlg.h"
#include "MyStatic.h"

typedef enum PS96Simple_Son_Page_Type
{
	EPS96SSPT_NONE,EPS96SSPT_ASSAYSELECT,EPS96SSPT_LOADSAM
}EPS96SIMPLE_SON_PAGE_TYPE;

class CPs96SimpleDlg: public CMiddleDlg
{
public:
	// 函数 CPs96SimpleDlg
	// 作用：执行CPs96SimpleDlg。
	// 参数：无。
	// 返回：没有返回值。
	CPs96SimpleDlg(void);
	// 函数 ~CPs96SimpleDlg
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CPs96SimpleDlg(void);

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

	// 函数 OnBnClickedRunStop
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedRunStop();
	// 函数 OnBnClickedSet
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSet();
	// 函数 OnBnClickedSwtAssaySelect
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtAssaySelect();
	// 函数 OnBnClickedSwtSamInfo
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedSwtSamInfo();
		
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
	// 函数 InitSonDlg
	// 作用：初始化InitSonDlg。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void InitSonDlg();

	// 函数 CreateCtrl
	// 作用：创建或加入CreateCtrl。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateCtrl();
	// 函数 CreateBt
	// 作用：创建或加入CreateBt。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateBt();
	// 函数 CreateSt
	// 作用：创建或加入CreateSt。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void CreateSt();
	// 函数 InitCtrl
	// 作用：初始化InitCtrl。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitCtrl();
	// 函数 InitBt
	// 作用：初始化InitBt。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitBt();
			// 函数 InitOneBt
			// 作用：初始化InitOneBt。
			// 参数：pBt：指针，指向调用方传入的对象。
			// 返回：没有返回值。
			void InitOneBt(CMyButton* pBt);
	// 函数 InitSt
	// 作用：初始化InitSt。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitSt();
	// 函数 InitCb
	// 作用：初始化InitCb。
	// 参数：无。
	// 返回：没有返回值。
	virtual void InitCb();
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

	// 函数 SetCtrlText
	// 作用：设置SetCtrlText。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void SetCtrlText();

	// 函数 SetExpDataPtr
	// 作用：设置SetExpDataPtr。
	// 参数：pExpData：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	virtual void SetExpDataPtr(CExperimentData* pExpData);
	// 函数 EmbodyBaseSetInfo
	// 作用：执行EmbodyBaseSetInfo。
	// 参数：无。
	// 返回：没有返回值。
	virtual void EmbodyBaseSetInfo();

	// 函数 RefreshExpDlgRunState
	// 作用：更新或清除RefreshExpDlgRunState。
	// 参数：bOccupy：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int RefreshExpDlgRunState(BOOL bOccupy);

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

	// 函数 OnMsgExperFluChanged
	// 作用：响应 Windows 或自定义消息 OnMsgExperFluChanged。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgExperFluChanged(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgExperRun
	// 作用：响应 Windows 或自定义消息 OnMsgExperRun。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgExperRun(WPARAM wParam,LPARAM lParam);
	// 函数 OnMsgExperFinished
	// 作用：响应 Windows 或自定义消息 OnMsgExperFinished。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgExperFinished(WPARAM wParam,LPARAM lParam);
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
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT_PTR nIDEvent);

			// 函数 SetPageSelected
			// 作用：设置SetPageSelected。
			// 参数：eSonPageType。
			// 返回：没有返回值。
			void SetPageSelected(EPS96SIMPLE_SON_PAGE_TYPE eSonPageType);

			// 函数 RefreshExpNameAndSavePath
			// 作用：更新或清除RefreshExpNameAndSavePath。
			// 参数：无。
			// 返回：没有返回值。
			void RefreshExpNameAndSavePath();

	// 函数 RefreshExpEmbody
	// 作用：更新或清除RefreshExpEmbody。
	// 参数：无。
	// 返回：没有返回值。
	virtual	void RefreshExpEmbody();
			// 函数 ClearExpEmbody
			// 作用：更新或清除ClearExpEmbody。
			// 参数：无。
			// 返回：没有返回值。
			void ClearExpEmbody();

	// 函数 SetTemplateListSelectedRow
	// 作用：设置SetTemplateListSelectedRow。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	virtual void SetTemplateListSelectedRow(int iIndex);
	// 函数 NewTemplateAdded
	// 作用：执行NewTemplateAdded。
	// 参数：iIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int NewTemplateAdded(int iIndex);
			
			// 函数 DeleteTemplate
			// 作用：更新或清除DeleteTemplate。
			// 参数：iIndex：整数。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int DeleteTemplate(int iIndex);
	// 函数 DeleteTemplateListRow
	// 作用：更新或清除DeleteTemplateListRow。
	// 参数：iIndex：整数。
	// 返回：没有返回值。
	virtual	void DeleteTemplateListRow(int iIndex);
	// 函数 SetEditMode
	// 作用：设置SetEditMode。
	// 参数：eExpEditMode。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int SetEditMode(EEXPEDITMODE eExpEditMode);

			// 函数 ImportId
			// 作用：读入ImportId。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int ImportId();

	// 函数 ExportResult
	// 作用：执行ExportResult。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int ExportResult();
	// 函数 SetConnectState
	// 作用：设置SetConnectState。
	// 参数：bRunExp：是或否。
	// 返回：没有返回值。
	virtual void SetConnectState(BOOL bRunExp);
	// 函数 OnBnClickedFindInstrument
	// 作用：响应按钮点击。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnBnClickedFindInstrument();
	// 函数 OnMsgTellParentSetNewText
	// 作用：响应 Windows 或自定义消息 OnMsgTellParentSetNewText。
	// 参数：wParam；lParam。
	// 返回：返回 LRESULT。
	afx_msg LRESULT OnMsgTellParentSetNewText(WPARAM wParam, LPARAM lParam);
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

	// 函数 InitExperimentData
	// 作用：初始化InitExperimentData。
	// 参数：pExpData：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	virtual void InitExperimentData(CExperimentData* pExpData);

protected:
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

	// 函数 DataProcess
	// 作用：执行DataProcess。
	// 参数：bNewOver：是或否；iAmlFlag：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DataProcess(BOOL bNewOver,int iAmlFlag = 5);

	// 函数 InitInstrument
	// 作用：初始化InitInstrument。
	// 参数：无。
	// 返回：没有返回值。
	void InitInstrument();
	// 函数 CombineModelAndSN
	// 作用：执行CombineModelAndSN。
	// 参数：strModel：字符串；strSN：字符串。
	// 返回：返回一段文字。
	CString CombineModelAndSN(CString strModel,CString strSN);
		
public:
	CMyStatic m_stRemainTm;
	CMyStatic m_stAssayName;
	CMyStatic m_stFileSaveFolder;

	CMyNewCb m_cbInstrumentType;
	CMyButton m_btnFindInstrument; // 查找设备

	CMyButton m_btRunStop;
	CMyButton m_btSet;
	CMyButton m_swtBtAssaySel;
	CMyButton m_swtBtSamInfo;

	CAssaySelDlg m_assaySelDlg;
	CLoadSamDlg m_loadSamDlg;

protected:
	EPS96SIMPLE_SON_PAGE_TYPE m_eCurSelPage;

};

