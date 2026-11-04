// 【交接】 BWGenUILib\ResizeContainer.h
// 作用：ResizeContainer。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CResizeContainer、CResizeItem、SetRect、GetRect、FindAndSetShow、GetShow、SetNewRow、GetNewRow。
#pragma once

/**
 * 处理控件位置大小改变的容器。
 * 特别注意，添加时按先上后下，先左后右的顺序添加，如果存在水平、垂直方向完全改变的控件，应该在最后添加
 */
class AFX_EXT_CLASS CResizeContainer : public CObject
{
public:
	// 函数 CResizeContainer
	// 作用：执行CResizeContainer。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CResizeContainer();
	// 函数 ~CResizeContainer
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CResizeContainer();

	enum eResizeType
	{
		LEFT_SIZE_NO, // 靠左，不改变大小
		LEFT_SIZE_H, // 靠左，水平放缩
		LEFT_SIZE_V, // 靠左，上下放缩
		LEFT_SIZE_HV, // 靠左，水平上下放缩

		RIGHT_SIZE_NO, // 靠右，不改变大小
		RIGHT_SIZE_H, // 靠右，水平放缩
		RIGHT_SIZE_V, // 靠右，上下放缩
		RIGHT_SIZE_HV, // 靠右，水平上下放缩
	};

	enum eResizeFillType
	{
		FILL_NO_RESIZE, // 不改变大小的填充
		FILL_RESIZE_H, // 水平充满
		FILL_RESIZE_V, // 垂直充满
		//FILL_RESIZE_M, // 中间充满，三个以上一组控件
		FILL_RESIZE_LEFT, // 左充满
	};

	enum eDockType
	{
		DOCK_TOP = 0,
		DOCK_BOTTOM,
	};

	// CResizeContainer command target

	class CResizeItem : public CObject
	{
	public:
		CResizeItem(CWnd* pWnd, CRect rect, eResizeType nType, int iIndent=0);
		virtual ~CResizeItem();

	// Operations
	public:
		virtual void SetRect(CRect rect);
		CRect GetRect() { return m_rect; }
		virtual BOOL FindAndSetShow(CWnd* pInputWnd, BOOL bShow);
		BOOL GetShow() { return m_bShow; }
		void SetNewRow(BOOL bNew) { m_bNewRow = bNew; }
		BOOL GetNewRow() { return m_bNewRow; }
		eResizeType GetResizeType() { return m_nResizeType; }

	protected:
		CRect GetPosition(CRect rect);
		void MoveWindow(CWnd* pWnd, CRect rect);

	protected:
		CWnd*	m_pResizeWnd; // 需要改变大小的窗口
		CRect	m_rect; // 相对于父窗口的窗口位置大小
		eResizeType	m_nResizeType;
		int		m_iIndent; // 相对于停靠位置点的缩进距离
		BOOL	m_bNewRow; // 会否新起一行
		BOOL	m_bShow;
	};

	class CResizeGroup : public CResizeItem
	{
	public:
		CResizeGroup(CRect rect, eResizeType nType, eResizeFillType nFillType, int iIndent=0);
		virtual ~CResizeGroup();

	public:
		void SetChildren(CPtrArray* pChildren);
		virtual void SetRect(CRect rect);
		virtual BOOL FindAndSetShow(CWnd* pInputWnd, BOOL bShow);

	protected:
		eResizeFillType	m_nFillType;
		CPtrArray	m_arrayChildren;
		UINT	m_nSeparator; // 分割区域大小
	};

public:
	// 函数 SetParent
	// 作用：设置SetParent。
	// 参数：pWnd：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetParent(CWnd* pWnd) { m_pParentWnd=pWnd; }

	// 函数 SetDockType
	// 作用：设置SetDockType。
	// 参数：nType：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetDockType(eDockType nType) { m_nDockType = nType; }
	// 函数 SetMargin
	// 作用：设置SetMargin。
	// 参数：sizeLT；sizeRB。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetMargin(CSize sizeLT, CSize sizeRB) { m_sizeMarginLT = sizeLT; m_sizeMarginRB = sizeRB; }
	// 函数 SetRowSpace
	// 作用：设置SetRowSpace。
	// 参数：iSpace：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRowSpace(int iSpace) { m_iRowSpace = iSpace; }

	// 函数 SetRect
	// 作用：设置SetRect。
	// 参数：rect：矩形区域。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetAt。
	void SetRect(CRect rect);
	// 函数 AddChild
	// 作用：创建或加入AddChild。
	// 参数：pChild：指针，指向调用方传入的对象；nType：整数；iIndent：整数；bNewRow：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetAt。
	int AddChild(CWnd* pChild, eResizeType nType, int iIndent, BOOL bNewRow=TRUE);
	// 函数 AddGroupChild
	// 作用：创建或加入AddGroupChild。
	// 参数：pChildArray：指针，指向调用方传入的对象；nType：整数；nFillType：整数；iIndent：整数；bNewRow：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetAt。
	int AddGroupChild(CPtrArray* pChildArray, eResizeType nType, eResizeFillType nFillType, int iIndent, BOOL bNewRow=TRUE);
	// 函数 GetAt
	// 作用：读取GetAt。
	// 参数：)m_arrayChild.GetAt(nIndex。
	// 返回：返回指针 CResizeItem*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CResizeItem* GetAt(int nIndex) { return (CResizeItem*)m_arrayChild.GetAt(nIndex);}

	// 函数 SetWndShow
	// 作用：设置SetWndShow。
	// 参数：pInputWnd：指针，指向调用方传入的对象；bShow：是或否。
	// 返回：没有返回值。
	void SetWndShow(CWnd* pInputWnd, BOOL bShow);

protected:
	// 函数 GetRowRect
	// 作用：读取GetRowRect。
	// 参数：iStartIndex：整数。
	// 返回：返回 CRect。
	CRect GetRowRect(int iStartIndex);
	// 函数 CalculateRowSpace
	// 作用：计算CalculateRowSpace。
	// 参数：rectArea：矩形区域。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalculateRowSpace(CRect rectArea);

protected:
	CWnd*	m_pParentWnd; // 父类窗口
	CPtrArray	m_arrayChild; // 对象指针

	eDockType m_nDockType; 
	CSize	m_sizeMarginLT; // 左上边空
	CSize	m_sizeMarginRB; // 右下边空
	int		m_iRowSpace; // 行间空白
	CSize	m_sizeResizeMax; // 窗口缩放的水平垂直最大值
};
