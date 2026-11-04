// 【交接】 BWGenUILib\BioEdit.h
// 作用：BioEdit 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：CBioEdit、EnableMinus、EnableDefaultButton、EnableFileBrowseButton、EnableFolderBrowseButton、EnableSpinNumButton、EnableNumberEdit、EnableAutoCheck。
#pragma once

#define WM_EDIT_VALUE_CHANGED		WM_USER + 2101 // 数值改变，根据消息用户完成与改变相关的处理

// 增强性编辑框控件，提供文件选择、路径选择等操作

class AFX_EXT_CLASS CBioEdit : public CEdit
{
public:
	// 函数 CBioEdit
	// 作用：执行CBioEdit。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CBioEdit();
	// 函数 ~CBioEdit
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CBioEdit();

// Attributes
public:
	enum BioEditMode
	{
		EditMode_Normal = 0, ///< 通常编辑框
		EditMode_Default = 1, ///< 默认按钮
		EditMode_File = 2, ///< 文件选择按钮
		EditMode_Folder = 3, ///< 路径选择按钮
		EditMode_Number = 4, ///< 数字编辑框
		EditMode_Spin = 5 ///< 带spin按钮的编辑框 
	};

protected:
	BioEditMode	m_nMode; ///< 编辑框的操作模式
	int			m_nButtonWidth;
	CRect		m_rectButton;
	CImageList	m_ImageButton;
	CSize		m_sizeImage;

	BOOL		m_bIsMinus; ///< 是否支持负数，默认为正数
	BOOL		m_bIsButtonPressed;
	BOOL		m_bIsButtonHighlighted;
	BOOL		m_bIsButtonCaptured;
	CString		m_strLabel;
	CString		m_strFileExt;
	CString		m_strFileFilter;
	CString		m_strFolderTitle; ///< 浏览文件夹时的标题
	LPCTSTR		m_lpszInitPath; ///< 浏览文件夹时初始化路径

	// 处理数字编辑框
	CString m_strValue;
	double m_dStepValue; ///< 步长
	double m_dMinValue; ///< 最小值
	double m_dMaxValue; ///< 最大值
	UINT m_nPrecision; ///< 浮点数的精度
	// 处理spin编辑框
	BOOL m_bIsInTop;///< 上按钮是否按下
	CRect m_rectTop; ///< 上按钮大小
	CRect m_rectBottom; ///< 下按钮大小

	BOOL	m_bAutoCheck; ///< 是否自动检测数据的合法性
	UINT	m_nTimer; ///< 计时器ID
	UINT	m_nSleepTime; ///< 计数器间隔时间
	
	BOOL	m_bWantAllKeys;

// Operations
public:
	// 函数 EnableMinus
	// 作用：改变EnableMinus的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableMinus(){m_bIsMinus=TRUE;}
	// 函数 EnableDefaultButton
	// 作用：改变EnableDefaultButton的显示或可用状态。
	// 参数：strLabel：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableAutoCheck。
	void EnableDefaultButton(CString strLabel = _T("..."));
	// 函数 EnableFileBrowseButton
	// 作用：改变EnableFileBrowseButton的显示或可用状态。
	// 参数：strFileExt：字符串；strFilter：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableAutoCheck。
	void EnableFileBrowseButton(CString strFileExt = _T(""), CString strFilter = _T(""));
	// 函数 EnableFolderBrowseButton
	// 作用：改变EnableFolderBrowseButton的显示或可用状态。
	// 参数：strFolderTitle：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableAutoCheck。
	void EnableFolderBrowseButton(CString strFolderTitle = _T(""));
	// 函数 EnableSpinNumButton
	// 作用：改变EnableSpinNumButton的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableAutoCheck。
	void EnableSpinNumButton();
	// 函数 EnableNumberEdit
	// 作用：改变EnableNumberEdit的显示或可用状态。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableAutoCheck。
	void EnableNumberEdit();
	// 函数 EnableAutoCheck
	// 作用：改变EnableAutoCheck的显示或可用状态。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableAutoCheck(BOOL bEnable=TRUE){m_bAutoCheck=bEnable;}
	// 函数 EnableWantAllKeys
	// 作用：改变EnableWantAllKeys的显示或可用状态。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableWantAllKeys(BOOL bEnable=TRUE){ m_bWantAllKeys = bEnable; }

	// 函数 GetValue
	// 作用：读取GetValue。
	// 参数：dOutput：小数。
	// 返回：没有返回值。
	void GetValue(double &dOutput);
	// 函数 SetValue
	// 作用：设置SetValue。
	// 参数：dInput：小数。
	// 返回：没有返回值。
	void SetValue(double dInput);
	// 函数 GetValue
	// 作用：读取GetValue。
	// 参数：lOutput。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetTimerSleepTime。
	void GetValue(long &lOutput);
	// 函数 SetValue
	// 作用：设置SetValue。
	// 参数：lInput。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetTimerSleepTime。
	void SetValue(long lInput);
	// 函数 SetRange
	// 作用：设置SetRange。
	// 参数：dMinValue：小数；dMaxValue：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetTimerSleepTime。
	void SetRange(double dMinValue , double dMaxValue);
	// 函数 GetRange
	// 作用：读取GetRange。
	// 参数：dMinValue：小数；dMaxValue：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetTimerSleepTime。
	void GetRange(double& dMinValue, double& dMaxValue);
	// 函数 SetStepValue
	// 作用：设置SetStepValue。
	// 参数：dStep：小数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetTimerSleepTime。
	void SetStepValue(double dStep);
	// 函数 GetStepValue
	// 作用：读取GetStepValue。
	// 参数：无。
	// 返回：返回一个小数。
	// 过程：函数里会调用 SetTimerSleepTime。
	double GetStepValue(void);
	// 函数 SetPrecision
	// 作用：设置SetPrecision。
	// 参数：nInPrecision：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetTimerSleepTime。
	void SetPrecision(UINT nInPrecision);
	
	// 函数 SetTimerSleepTime
	// 作用：设置SetTimerSleepTime。
	// 参数：nTime：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetTimerSleepTime(UINT nTime){m_nSleepTime=nTime;}
	

protected:
	// 函数 SetIntenalImage
	// 作用：设置SetIntenalImage。
	// 参数：无。
	// 返回：没有返回值。
	void SetIntenalImage();
	// 函数 DrawButtonFrame
	// 作用：绘制DrawButtonFrame。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；bIsPressed：是或否。
	// 返回：没有返回值。
	void DrawButtonFrame(CDC* pDC, CRect rect, BOOL bIsPressed);
	// 函数 OnClickFileButton
	// 作用：响应 Windows 或自定义消息 OnClickFileButton。
	// 参数：无。
	// 返回：没有返回值。
	void OnClickFileButton();
	// 函数 OnClickFolderButton
	// 作用：响应 Windows 或自定义消息 OnClickFolderButton。
	// 参数：无。
	// 返回：没有返回值。
	void OnClickFolderButton();
	static int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData);
	
	// 函数 DrawDefaultButtonLabel
	// 作用：绘制DrawDefaultButtonLabel。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；bIsButtonPressed：是或否。
	// 返回：没有返回值。
	void DrawDefaultButtonLabel(CDC* pDC, CRect rect, BOOL bIsButtonPressed);
	// 函数 JudgeNumberIsLegal
	// 作用：执行JudgeNumberIsLegal。
	// 参数：无。
	// 返回：没有返回值。
	void JudgeNumberIsLegal(void);

// Overrides
protected:
	// 函数 OnClickButton
	// 作用：响应 Windows 或自定义消息 OnClickButton。
	// 参数：无。
	// 返回：没有返回值。
	virtual void OnClickButton();
	// 函数 DrawButton
	// 作用：绘制DrawButton。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；bIsButtonPressed：是或否；bIsButtonHot：是或否。
	// 返回：没有返回值。
	virtual void DrawButton(CDC* pDC, CRect rect, BOOL bIsButtonPressed, BOOL bIsButtonHot);
	// 函数 ChangeLayout
	// 作用：执行ChangeLayout。
	// 参数：无。
	// 返回：没有返回值。
	virtual void ChangeLayout();

// Implementation
protected:
	// 函数 OnNcPaint
	// 作用：绘制标题栏等非客户区。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnNcPaint();
	// 函数 OnLButtonDown
	// 作用：按下鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 函数 OnLButtonUp
	// 作用：松开鼠标左键。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 函数 OnMouseMove
	// 作用：鼠标在窗口上移动。
	// 参数：nFlags：整数；point。
	// 返回：没有返回值。
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	// 函数 OnNcCalcSize
	// 作用：响应 Windows 或自定义消息 OnNcCalcSize。
	// 参数：bCalcValidRects：是或否；lpncsp。
	// 返回：没有返回值。
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	//afx_msg UINT OnNcHitTest(CPoint point);
	// 函数 OnNcLButtonDblClk
	// 作用：响应 Windows 或自定义消息 OnNcLButtonDblClk。
	// 参数：nHitTest：整数；point。
	// 返回：没有返回值。
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	// 函数 OnNcMouseMove
	// 作用：响应 Windows 或自定义消息 OnNcMouseMove。
	// 参数：nHitTest：整数；point。
	// 返回：没有返回值。
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	// 函数 OnCancelMode
	// 作用：用户取消当前对话框。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnCancelMode();
	// 函数 OnTimer
	// 作用：定时器到期时刷新界面或推进状态。
	// 参数：nIDEvent：整数。
	// 返回：没有返回值。
	afx_msg void OnTimer(UINT nIDEvent);
	// 函数 OnChar
	// 作用：响应 Windows 或自定义消息 OnChar。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 OnKeyDown
	// 作用：响应 Windows 或自定义消息 OnKeyDown。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 OnGetDlgCode
	// 作用：响应 Windows 或自定义消息 OnGetDlgCode。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	afx_msg UINT OnGetDlgCode();

	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()
};
