// 【交接】 BWGenUILib\BWReportCtrl.h
// 作用：BWReportCtrl 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：_T、DECLARE_DYNAMIC、CBWReportCtrl、CReportItem、Empty、RGB、CReportRowItem、GetAt。
#pragma once

#include <afxtempl.h>
#include "BioInEdit.h"
#include "BioInComboBox.h"
#include "BWColorWnd.h"


// CBWReportCtrl
const CString CLASSNAME_REPORTCTRL =  _T("BWReportCtrl");
const UINT BWREPORT_SEL_CHANGE = WM_USER + 2001; // 行选择改变，第1个参数是选择行数，第2个参数保存行号的UINT*指针
//const UINT REPORT_ITEM_CHANGE = WM_USER + 2002; // 项数据改变

/**
 * \ingroup PublicLib
 * 列表类，类似于MFC的CListCtrl，提供排序功能，可以按行、列设置颜色
 */
class AFX_EXT_CLASS CBWReportCtrl : public CWnd
{
	// 函数 DECLARE_DYNAMIC
	// 作用：执行DECLARE_DYNAMIC。
	// 参数：CBWReportCtrl。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	DECLARE_DYNAMIC(CBWReportCtrl)

public:
	// 函数 CBWReportCtrl
	// 作用：执行CBWReportCtrl。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CBWReportCtrl();
	// 函数 ~CBWReportCtrl
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	virtual ~CBWReportCtrl();

	enum eColType
	{
		DATA_INTEGER = 0,
		DATA_FLOAT = 1,
		DATA_TEXT = 2
	};


	// 一个数据项的类
	class CReportItem : public CObject
	{
	public:
		CReportItem()
		{
			m_nFormat = DT_VCENTER | DT_SINGLELINE | DT_LEFT;
			m_strText.Empty();
			m_clrBkg = RGB(255, 255, 255);
			m_clrText = RGB(0, 0, 0);
			m_bEnable = TRUE;
			m_clrFill = RGB(228, 228, 228);
			m_iStatus = 0;
		}

		virtual ~CReportItem(){};

		// Attributes
		UINT		m_nFormat; // 文本格式
		CString		m_strText; // 文本数据
		COLORREF	m_clrBkg; // 背景色
		COLORREF	m_clrText; // 文本颜色
		BOOL	m_bEnable;
		COLORREF	m_clrFill; // 特殊状态时的填充色
		int		m_iStatus; // 状态，特殊栏使用，如CHECK
	};

	// 一个数据行的类，包括多个数据项
	class CReportRowItem
	{
	public:
		CReportRowItem()
		{
			m_clrBkg = RGB(255, 255, 255);
			m_dwParam = 0;
			m_bSelected = FALSE;
		}
		virtual ~CReportRowItem()
		{
			for (int j=0; j<m_arrayItems.GetSize(); j++)
			{
				CReportItem* pItemData = m_arrayItems.GetAt(j);
				if (pItemData != NULL)
				{
					delete pItemData;
				}
			}
			m_arrayItems.RemoveAll();
		}

		int AddChild(CReportItem* pItem){return (int)m_arrayItems.Add(pItem);}
		CReportItem* GetChildAt(int nIndex){return m_arrayItems.GetAt(nIndex);}
		int	GetChildCount(){return (int)m_arrayItems.GetSize();}

		CTypedPtrArray<CPtrArray, CReportItem*>  m_arrayItems;
		// Attributes
		COLORREF	m_clrBkg; // 背景色
		DWORD		m_dwParam;
		BOOL		m_bSelected; // 选中
	};

	typedef CTypedPtrArray<CPtrArray, CReportRowItem*> CReportDataArray;

	enum eSortType
	{
		SORT_NO = 0,
		SORT_ASCEND = 1,
		SORT_DESCEND = 2
	};
	
	struct tagReportColData
	{
		BOOL	bResize; // 宽度可改变
		UINT	nType; // HDI_BITMAP, HDI_TEXT
		CString	strText;
		int		iWidth;
		int		iImage; // 图像列表的序号
		UINT	nFormat; // DT_VCENTER | DT_SINGLELINE | DT_LEFT;
		BOOL	bClicked; // 是否已被按下
		eSortType	nSortType; // 是否排序及排序类型
		DWORD	dwParam;
		tagReportColData()
		{
			bResize = FALSE;
			nType = HDI_TEXT;
			strText.Empty();
			iWidth = 0;
			iImage = -1;
			nFormat = DT_VCENTER | DT_SINGLELINE | DT_LEFT;
			bClicked = FALSE;
			nSortType = SORT_NO;
			dwParam = 0;
		}
	};


	/** \brief 子项编辑时对象类型集合
	* 表示子窗口的类型，当前只完成文本编辑、数字编辑和列表选择
	*/
	enum eListItemType
	{
		LIST_ITEM_ENABLE = 0, // 有效
		LIST_ITEM_DISABLE, // 无效
		LIST_ITEM_EDIT, // 文本编辑
		LIST_ITEM_NUMEDIT, // 数字编辑
		LIST_ITEM_COMBO, // 列表选择， CBS_DROPDOWNLIST
		LIST_ITEM_CHECK, // 复选框
		LIST_ITEM_COLOR, // 颜色框
		LIST_ITEM_DELETE, // 删除框
	};

	// 列表子项编辑时对象类型信息集合，表明特殊子项的处理信息
	struct sListColAttribute
	{
		int nCol; // 列表的列数
		int nRow; // 行
		eListItemType nType; //  子项创建对象类型，只能时eListItemType中的一种
		int nMin;
		int nMax;
		int iDataCount; // 当子项对象为ComboBox时可供选择的数据项总数
		DWORD dwParam;// 当子项对象为ComboBox时可供选择的数据项集合
		sListColAttribute(){
			nCol = -1;
			nRow = -1;
			nType = LIST_ITEM_EDIT;
			nMin = 0;
			nMax = 0;
			iDataCount = 0;
			dwParam = 0;
		};
	};

	// 子项对象信息数组
	CArray<sListColAttribute,sListColAttribute&> m_arrayColAttr;

// Operations
public:
	// 函数 RemoveAll
	// 作用：更新或清除RemoveAll。
	// 参数：bHasCol：是或否；bHasAttri：是或否。
	// 返回：没有返回值。
	void RemoveAll(BOOL bHasCol=TRUE, BOOL bHasAttri=TRUE);
	// 设定标题栏数据
	// 函数 AddColumn
	// 作用：创建或加入AddColumn。
	// 参数：strText：字符串；nWidth：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddColumn(CString strText, int nWidth);
	// 函数 AddColumn
	// 作用：创建或加入AddColumn。
	// 参数：strText：字符串；nWidth：整数；nType：整数；nFormat：整数；iImage：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddColumn(CString strText, int nWidth, UINT nType, UINT nFormat, int iImage=-1);
	// 函数 SetColumnFormat
	// 作用：设置SetColumnFormat。
	// 参数：nIndex：整数；nFormat：整数。
	// 返回：没有返回值。
	void SetColumnFormat(int nIndex, UINT nFormat);
	// 函数 GetColumnFormat
	// 作用：读取GetColumnFormat。
	// 参数：nIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	UINT GetColumnFormat(int nIndex);
	// 函数 SetColumnType
	// 作用：设置SetColumnType。
	// 参数：nIndex：整数；nType：整数。
	// 返回：没有返回值。
	void SetColumnType(int nIndex, int nType);
	// 函数 SetColumnResize
	// 作用：设置SetColumnResize。
	// 参数：nIndex：整数；bEnable：是或否。
	// 返回：没有返回值。
	void SetColumnResize(int nIndex, BOOL bEnable);
	// 函数 SetColumnText
	// 作用：设置SetColumnText。
	// 参数：nIndex：整数；strText：字符串。
	// 返回：没有返回值。
	void SetColumnText(int nIndex, CString strText);
	// 函数 SetColumnData
	// 作用：设置SetColumnData。
	// 参数：nIndex：整数；dwParam。
	// 返回：没有返回值。
	void SetColumnData(int nIndex, DWORD dwParam);
	// 函数 GetColumnData
	// 作用：读取GetColumnData。
	// 参数：iIndex：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	DWORD GetColumnData(int iIndex);

	// 设定行数据
	// 函数 AddRow
	// 作用：创建或加入AddRow。
	// 参数：strText：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddRow(CString strText);
	// 函数 InsertRow
	// 作用：创建或加入InsertRow。
	// 参数：nRow：整数；strText：字符串。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int InsertRow(int nRow, CString strText);
	// 函数 RemoveRow
	// 作用：更新或清除RemoveRow。
	// 参数：nRow：整数。
	// 返回：没有返回值。
	void RemoveRow(int nRow);
	// 函数 SetItemFormat
	// 作用：设置SetItemFormat。
	// 参数：nRow：整数；nSubItem：整数；nFormat：整数。
	// 返回：没有返回值。
	void SetItemFormat(int nRow, int nSubItem, UINT nFormat = DT_VCENTER | DT_SINGLELINE | DT_LEFT);
	// 函数 GetItemText
	// 作用：读取GetItemText。
	// 参数：nRow：整数；nCol：整数。
	// 返回：返回一段文字。
	CString GetItemText(int nRow, int nCol);
	// 函数 SetItemText
	// 作用：设置SetItemText。
	// 参数：nRow：整数；nSubItem：整数；strText：字符串。
	// 返回：没有返回值。
	void SetItemText(int nRow, int nSubItem, CString strText);
	// 函数 SetItemBkgColor
	// 作用：设置SetItemBkgColor。
	// 参数：nRow：整数；nSubItem：整数；clrBkg：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetColCount。
	void SetItemBkgColor(int nRow, int nSubItem, COLORREF clrBkg);
	// 函数 SetItemTextColor
	// 作用：设置SetItemTextColor。
	// 参数：nRow：整数；nSubItem：整数；clrText：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetColCount。
	void SetItemTextColor(int nRow, int nSubItem, COLORREF clrText);
	// 函数 SetItemEnable
	// 作用：设置SetItemEnable。
	// 参数：nRow：整数；nSubItem：整数；bEnable：是或否。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetColCount。
	void SetItemEnable(int nRow, int nSubItem, BOOL bEnable);
	// 函数 SetItemFillColor
	// 作用：设置SetItemFillColor。
	// 参数：nRow：整数；nSubItem：整数；clrFill：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetColCount。
	void SetItemFillColor(int nRow, int nSubItem, COLORREF clrFill);
	// 函数 GetItemFillColor
	// 作用：读取GetItemFillColor。
	// 参数：iRow：整数；iSubItem：整数。
	// 返回：返回 COLORREF。
	// 过程：函数里会调用 GetColCount。
	COLORREF GetItemFillColor(int iRow, int iSubItem);
	// 函数 SetItemStatus
	// 作用：设置SetItemStatus。
	// 参数：nRow：整数；nSubItem：整数；iStatus：整数。
	// 返回：没有返回值。
	// 过程：函数里会调用 GetColCount。
	void SetItemStatus(int nRow, int nSubItem, int iStatus);
	// 函数 GetItemStatus
	// 作用：读取GetItemStatus。
	// 参数：iRow：整数；iSubItem：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 GetColCount。
	int GetItemStatus(int iRow, int iSubItem);
	
	// 函数 GetColCount
	// 作用：读取GetColCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetColCount(){return m_iColCount;}
	// 函数 GetRowCount
	// 作用：读取GetRowCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	int GetRowCount(){return m_iRowCount;}

	// 函数 SetRowColor
	// 作用：设置SetRowColor。
	// 参数：nRow：整数；clrBkg：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 EnableSort。
	void SetRowColor(int nRow, COLORREF clrBkg);

    int  GetColumnWidth(int iCol) const;
	// 函数 GetColumnName
	// 作用：读取GetColumnName。
	// 参数：iCol：整数。
	// 返回：返回一段文字。
	// 过程：函数里会调用 EnableSort。
	CString GetColumnName(int iCol) const;

	// 处理列表状态
	// 函数 EnableSort
	// 作用：改变EnableSort的显示或可用状态。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableSort(BOOL bEnable){m_bEnableSort=bEnable;}
	// 函数 EnableEdit
	// 作用：改变EnableEdit的显示或可用状态。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableEdit(BOOL bEnable){m_bEnableEdit=bEnable;}
	// 函数 EnableMultiSelect
	// 作用：改变EnableMultiSelect的显示或可用状态。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableMultiSelect(BOOL bEnable) {m_bEnableMultiSelected=bEnable;}
	// 函数 CanEdit
	// 作用：判断CanEdit是否成立。
	// 参数：nRow：整数；nCol：整数。
	// 返回：返回是或否。
	virtual BOOL CanEdit(int nRow, int nCol);

	// 函数 Create
	// 作用：创建或加入Create。
	// 参数：dwStyle；rect：矩形区域；pParentWnd：指针，指向调用方传入的对象；nID：整数。
	// 返回：返回是或否。
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

	// 设置列表项为ComboBox 控件
	// 函数 SetColumnComboBox
	// 作用：设置SetColumnComboBox。
	// 参数：nCol：整数；nRow：整数；arrayColText。
	// 返回：没有返回值。
	void SetColumnComboBox(int nCol, int nRow, CStringArray &arrayColText);
	// 设置列表项为数字编辑控件
	// 函数 SetColumnNumEdit
	// 作用：设置SetColumnNumEdit。
	// 参数：nCol：整数；nRow：整数；iPrecision：整数；nMin：整数；nMax：整数。
	// 返回：没有返回值。
	void SetColumnNumEdit(int nCol, int nRow=-1, int iPrecision=0, int nMin=0, int nMax=INT_MAX);
	// 设置列表项为不可编辑
	// 函数 SetColumnDisable
	// 作用：设置SetColumnDisable。
	// 参数：nCol：整数；nRow：整数。
	// 返回：没有返回值。
	void SetColumnDisable(int nCol, int nRow=-1);
	// 函数 SetColumnCheckBox
	// 作用：设置SetColumnCheckBox。
	// 参数：iCol：整数；iRow：整数。
	// 返回：没有返回值。
	void SetColumnCheckBox(int iCol, int iRow=-1);
	// 函数 SetColumnColor
	// 作用：设置SetColumnColor。
	// 参数：iCol：整数；iRow：整数；iColorCount：整数；pInputColor：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void SetColumnColor(int iCol, int iRow=-1, int iColorCount=0, COLORREF* pInputColor=NULL);
	// 函数 SetColumnDelete
	// 作用：设置SetColumnDelete。
	// 参数：iCol：整数；iRow：整数。
	// 返回：没有返回值。
	void SetColumnDelete(int iCol, int iRow=-1);

	// 函数 GetSelectedRow
	// 作用：读取GetSelectedRow。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetSelectedRow();
	// 函数 GetSelectedItems
	// 作用：读取GetSelectedItems。
	// 参数：pOutItems：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetSelectedItems(UINT* &pOutItems);
	// 函数 SelectAll
	// 作用：执行SelectAll。
	// 参数：无。
	// 返回：没有返回值。
	void SelectAll();
	// 函数 SetSelectedRow
	// 作用：设置SetSelectedRow。
	// 参数：nRowNo：整数。
	// 返回：没有返回值。
	void SetSelectedRow(int nRowNo);
	// 函数 SetSelectedItems
	// 作用：设置SetSelectedItems。
	// 参数：nCount：整数；pOutItems：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void SetSelectedItems(int nCount, UINT* pOutItems);
	
	// 保存一行数据的参数
	// 函数 SetRowData
	// 作用：设置SetRowData。
	// 参数：nRow：整数；dwData。
	// 返回：返回是或否。
	BOOL SetRowData(int nRow, DWORD dwData);
	// 函数 GetRowData
	// 作用：读取GetRowData。
	// 参数：nRow：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	DWORD GetRowData(int nRow);

	// 打印
	// 函数 Print
	// 作用：执行Print。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；f。
	// 返回：没有返回值。
	void Print(CDC* pDC, const RECT& rect, float f);
	// 函数 PrintItem
	// 作用：执行PrintItem。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；pItemData：指针，指向调用方传入的对象；IsFirst。
	// 返回：没有返回值。
	void PrintItem(CDC* pDC, const RECT& rect, CReportItem* pItemData, BOOL IsFirst = FALSE);
	// 函数 PrintHeadItem
	// 作用：执行PrintHeadItem。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；strText：字符串；format；IsFirst。
	// 返回：没有返回值。
	void PrintHeadItem(CDC* pDC, const RECT& rect, CString strText, UINT format, BOOL IsFirst = FALSE);
	// 函数 PrintLine
	// 作用：执行PrintLine。
	// 参数：pDC：指针，指向调用方传入的对象；ptStart；ptEnd；clrPen：颜色。
	// 返回：没有返回值。
	void PrintLine(CDC* pDC, CPoint ptStart, CPoint ptEnd, COLORREF clrPen = RGB(0,0,0));

protected:
	// 函数 RegisterWindowClass
	// 作用：执行RegisterWindowClass。
	// 参数：无。
	// 返回：返回是或否。
	BOOL RegisterWindowClass();
	
	// 绘制标题栏
	// 函数 DrawHeader
	// 作用：绘制DrawHeader。
	// 参数：pDC：指针，指向调用方传入的对象；rectHeader：矩形区域；nStartCol：整数。
	// 返回：没有返回值。
	virtual void DrawHeader(CDC* pDC, CRect rectHeader, UINT nStartCol);
	// 函数 DrawColItem
	// 作用：绘制DrawColItem。
	// 参数：pDC：指针，指向调用方传入的对象；rectItem：矩形区域；pColData：指针，指向调用方传入的对象；bIsFirst：是或否。
	// 返回：没有返回值。
	virtual void DrawColItem(CDC* pDC, CRect rectItem, tagReportColData* pColData, BOOL bIsFirst=FALSE);
	// 绘制行数据
	// 函数 DrawRow
	// 作用：绘制DrawRow。
	// 参数：pDC：指针，指向调用方传入的对象；rectRow：矩形区域；pRowData：指针，指向调用方传入的对象；nStartCol：整数；bIsLocked：是或否；bIsSelected：是或否。
	// 返回：没有返回值。
	virtual void DrawRow(CDC* pDC, CRect rectRow, CReportRowItem* pRowData, UINT nStartCol, BOOL bIsLocked=FALSE, BOOL bIsSelected=FALSE);
	// 函数 DrawRowItem
	// 作用：绘制DrawRowItem。
	// 参数：pDC：指针，指向调用方传入的对象；iRow：整数；rectItem：矩形区域；pItemData：指针，指向调用方传入的对象；bIsLocked：是或否；bIsSelected：是或否。
	// 返回：没有返回值。
	virtual void DrawRowItem(CDC* pDC, int iRow, CRect rectItem, CReportItem* pItemData, BOOL bIsLocked, BOOL bIsSelected);
	// 函数 DrawItemFrame
	// 作用：绘制DrawItemFrame。
	// 参数：pDC：指针，指向调用方传入的对象；rectItem：矩形区域；pItemData：指针，指向调用方传入的对象；bIsLocked：是或否；bIsSelected：是或否；bDisable：是或否。
	// 返回：没有返回值。
	virtual void DrawItemFrame(CDC* pDC, CRect rectItem, CReportItem* pItemData, BOOL bIsLocked, BOOL bIsSelected, BOOL bDisable=FALSE);
	// 函数 DrawTextItem
	// 作用：绘制DrawTextItem。
	// 参数：pDC：指针，指向调用方传入的对象；rectItem：矩形区域；pItemData：指针，指向调用方传入的对象；bIsLocked：是或否；bIsSelected：是或否；bDisable：是或否。
	// 返回：没有返回值。
	virtual void DrawTextItem(CDC* pDC, CRect rectItem, CReportItem* pItemData, BOOL bIsLocked=FALSE, BOOL bIsSelected=FALSE, BOOL bDisable=FALSE);
	// 函数 DrawCheckBoxItem
	// 作用：绘制DrawCheckBoxItem。
	// 参数：pDC：指针，指向调用方传入的对象；rectItem：矩形区域；pItemData：指针，指向调用方传入的对象；bIsLocked：是或否；bIsSelected：是或否。
	// 返回：没有返回值。
	virtual void DrawCheckBoxItem(CDC* pDC, CRect rectItem, CReportItem* pItemData, BOOL bIsLocked, BOOL bIsSelected);
	// 函数 DrawColorItem
	// 作用：绘制DrawColorItem。
	// 参数：pDC：指针，指向调用方传入的对象；rectItem：矩形区域；pItemData：指针，指向调用方传入的对象；bIsLocked：是或否；bIsSelected：是或否。
	// 返回：没有返回值。
	virtual void DrawColorItem(CDC* pDC, CRect rectItem, CReportItem* pItemData, BOOL bIsLocked, BOOL bIsSelected);
	// 函数 DrawDeleteItem
	// 作用：绘制DrawDeleteItem。
	// 参数：pDC：指针，指向调用方传入的对象；rectItem：矩形区域；pItemData：指针，指向调用方传入的对象；bIsLocked：是或否；bIsSelected：是或否。
	// 返回：没有返回值。
	virtual void DrawDeleteItem(CDC* pDC, CRect rectItem, CReportItem* pItemData, BOOL bIsLocked, BOOL bIsSelected);
	// 函数 DrawText
	// 作用：绘制DrawText。
	// 参数：pDC：指针，指向调用方传入的对象；rect：矩形区域；strText：字符串；nFormat：整数。
	// 返回：没有返回值。
	virtual void DrawText(CDC* pDC, CRect rect, CString strText, UINT nFormat=DT_VCENTER | DT_SINGLELINE | DT_LEFT);
	// 函数 DrawSortIcon
	// 作用：绘制DrawSortIcon。
	// 参数：pDC：指针，指向调用方传入的对象；rectIcon：矩形区域；nSortType：整数。
	// 返回：没有返回值。
	virtual void DrawSortIcon(CDC* pDC, CRect rectIcon, UINT nSortType);
	// 函数 GetTextWithDots
	// 作用：读取GetTextWithDots。
	// 参数：pDC：指针，指向调用方传入的对象；strText：字符串；nWidth：整数。
	// 返回：返回一段文字。
	CString GetTextWithDots(CDC* pDC, CString strText , int nWidth);
	
	// 公用绘制
	// 函数 DrawLine
	// 作用：绘制DrawLine。
	// 参数：pDC：指针，指向调用方传入的对象；ptStart；ptEnd；clrPen：颜色。
	// 返回：没有返回值。
	void DrawLine(CDC* pDC, CPoint ptStart, CPoint ptEnd, COLORREF clrPen=RGB(0,0,0));

	// 函数 ResetScrollBars
	// 作用：更新或清除ResetScrollBars。
	// 参数：无。
	// 返回：没有返回值。
	void ResetScrollBars();
	// 函数 RecalculateColWidth
	// 作用：执行RecalculateColWidth。
	// 参数：recClient。
	// 返回：没有返回值。
	void RecalculateColWidth(CRect recClient);

	// 函数 GetScrollPos32
	// 作用：读取GetScrollPos32。
	// 参数：nBar：整数；bGetTrackPos：是或否。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetScrollPos32(int nBar, BOOL bGetTrackPos = FALSE);
	// 函数 GetMouseScrollLines
	// 作用：读取GetMouseScrollLines。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	UINT GetMouseScrollLines();
	// 函数 GetTopleftNonFixedIndex
	// 作用：读取GetTopleftNonFixedIndex。
	// 参数：无。
	// 返回：返回 CSize。
	CSize GetTopleftNonFixedIndex() const;

    int  GetFixedRowHeight() const;
    int  GetFixedColumnWidth() const;
    long GetVirtualWidth() const;
    long GetVirtualHeight() const;
 	
	// 标题栏宽度修改
	// 函数 PtInColSizingRect
	// 作用：执行PtInColSizingRect。
	// 参数：point。
	// 返回：返回是或否。
	BOOL PtInColSizingRect(CPoint point);
	// 函数 GetColSizingRect
	// 作用：读取GetColSizingRect。
	// 参数：lOffset。
	// 返回：返回 CRect。
	CRect GetColSizingRect(long lOffset);
	// 函数 DrawSplittingLine
	// 作用：绘制DrawSplittingLine。
	// 参数：lHorzPos。
	// 返回：没有返回值。
	void DrawSplittingLine(long lHorzPos);

	// 行选择
	// 函数 GetRowIndexBy
	// 作用：读取GetRowIndexBy。
	// 参数：point。
	// 返回：返回 long。
	long GetRowIndexBy(CPoint point);
	// 函数 GetColIndexBy
	// 作用：读取GetColIndexBy。
	// 参数：point。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetColIndexBy(CPoint point);
	// 列选择
	// 函数 SetColSortState
	// 作用：设置SetColSortState。
	// 参数：nCol：整数；bIsAdd：是或否。
	// 返回：没有返回值。
	void SetColSortState(int nCol, BOOL bIsAdd=FALSE);
	// 函数 SetColClickedState
	// 作用：设置SetColClickedState。
	// 参数：nCol：整数；bIsClicked：是或否。
	// 返回：没有返回值。
	void SetColClickedState(int nCol, BOOL bIsClicked);

	// 排序
	// 函数 SortRows
	// 作用：执行SortRows。
	// 参数：nSortCol：整数。
	// 返回：没有返回值。
	void SortRows(int nSortCol);
	// 函数 SortRowsByRange
	// 作用：执行SortRowsByRange。
	// 参数：nSortCol：整数；nBeginRow：整数；nEndRow：整数；nSortType：整数；bIsIncludeEnd：是或否。
	// 返回：没有返回值。
	void SortRowsByRange(int nSortCol, int nBeginRow, int nEndRow, UINT nSortType, BOOL bIsIncludeEnd=FALSE);
	// 函数 MergePass
	// 作用：执行MergePass。
	// 参数：pData1：指针，指向调用方传入的对象；pData2：指针，指向调用方传入的对象；s；n；nSortCol：整数；nSortType：整数。
	// 返回：没有返回值。
	void MergePass(CReportDataArray* pData1, CReportDataArray* pData2, int s, int n, UINT nSortCol, UINT nSortType);
	// 函数 Merge
	// 作用：执行Merge。
	// 参数：pData1：指针，指向调用方传入的对象；pData2：指针，指向调用方传入的对象；l；m；r；nSortCol：整数；nSortType：整数。
	// 返回：没有返回值。
	void Merge(CReportDataArray* pData1, CReportDataArray* pData2, int l, int m, int r, UINT nSortCol, UINT nSortType);
	// 函数 CompareReportItem
	// 作用：执行CompareReportItem。
	// 参数：pData：指针，指向调用方传入的对象；nSortCol：整数；nIndex1：整数；nIndex2：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CompareReportItem(CReportDataArray* pData, UINT nSortCol, UINT nIndex1, UINT nIndex2);

	// 函数 GetOtherSortIndex
	// 作用：读取GetOtherSortIndex。
	// 参数：pSortIndexArray：指针，指向调用方传入的对象；nSortCol：整数。
	// 返回：没有返回值。
	void GetOtherSortIndex(CUIntArray* pSortIndexArray, int nSortCol);
	// 函数 GetNextDifferentDataIndex
	// 作用：读取GetNextDifferentDataIndex。
	// 参数：nBeginRow：整数；pSortIndexArray：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	UINT GetNextDifferentDataIndex(UINT nBeginRow, CUIntArray* pSortIndexArray);
	// 函数 IsTwoItemDataSameOfIndex
	// 作用：判断IsTwoItemDataSameOfIndex是否成立。
	// 参数：pRowData1：指针，指向调用方传入的对象；pRowData2：指针，指向调用方传入的对象；pSortIndex：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL IsTwoItemDataSameOfIndex(CReportRowItem* pRowData1, CReportRowItem* pRowData2, CUIntArray* pSortIndex);

	// 处理列表编辑 －－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
	// 函数 HandleEditSubitem
	// 作用：执行HandleEditSubitem。
	// 参数：nIndex：整数；nCol：整数；nType：整数；pColAttr：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void HandleEditSubitem(int nIndex, int nCol, int nType, sListColAttribute* pColAttr);// 对Edit 进行编辑	
	// 函数 HandleComboBoxSubitem
	// 作用：执行HandleComboBoxSubitem。
	// 参数：nIndex：整数；nCol：整数；pColAttr：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void HandleComboBoxSubitem(int nIndex, int nCol, sListColAttribute* pColAttr);// 对ComboBox 进行选择
	// 函数 HandleCheckBoxSubitem
	// 作用：执行HandleCheckBoxSubitem。
	// 参数：nIndex：整数；nCol：整数；pColAttr：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void HandleCheckBoxSubitem(int nIndex, int nCol, sListColAttribute* pColAttr);// 对CheckBox 进行选择
	// 函数 HandleColorSubitem
	// 作用：执行HandleColorSubitem。
	// 参数：nIndex：整数；nCol：整数；pColAttr：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void HandleColorSubitem(int nIndex, int nCol, sListColAttribute* pColAttr);// 设置颜色
	// 函数 HandleDeleteSubitem
	// 作用：执行HandleDeleteSubitem。
	// 参数：nIndex：整数；nCol：整数；pColAttr：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	void HandleDeleteSubitem(int nIndex, int nCol, sListColAttribute* pColAttr);// 删除
 
	// 取得给定行数和列数的列表项的区域
	// 函数 GetSubItemRect
	// 作用：读取GetSubItemRect。
	// 参数：nIndex：整数；nCol：整数。
	// 返回：返回 CRect。
	CRect GetSubItemRect(int nIndex, int nCol);
	// 函数 GetItemTypeBy
	// 作用：读取GetItemTypeBy。
	// 参数：nCol：整数；nRow：整数；pColAttr：指针，指向调用方传入的对象。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	virtual int GetItemTypeBy(int nCol, int nRow, sListColAttribute* &pColAttr);
	// 函数 FindItemBy
	// 作用：执行FindItemBy。
	// 参数：nType：整数；nCol：整数；nRow：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int FindItemBy(int nType, int nCol, int nRow);
	// 函数 FindItemBy
	// 作用：执行FindItemBy。
	// 参数：nCol：整数；nRow：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int FindItemBy(int nCol, int nRow);


	// 函数 IsRowSelected
	// 作用：判断IsRowSelected是否成立。
	// 参数：nRow：整数。
	// 返回：返回是或否。
	BOOL IsRowSelected(UINT nRow);
	// 函数 HandleRowSelected
	// 作用：执行HandleRowSelected。
	// 参数：nFlags：整数；nNewRow：整数。
	// 返回：没有返回值。
	void HandleRowSelected(UINT nFlags, int nNewRow);

	// 函数 SendMessageOfSelectChanged
	// 作用：执行SendMessageOfSelectChanged。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetColumnColor。
	virtual void SendMessageOfSelectChanged();
	// 函数 DeleteSelectedRows
	// 作用：更新或清除DeleteSelectedRows。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetColumnColor。
	virtual void DeleteSelectedRows();

	// 函数 GetRowItem
	// 作用：读取GetRowItem。
	// 参数：iRow：整数；iCol：整数。
	// 返回：返回指针 CReportItem*。指针为空表示没有取到对象。
	// 过程：函数里会调用 SetColumnColor。
	CReportItem* GetRowItem(int iRow, int iCol);

// Attributes
public:
	// 函数 SetColumnColor
	// 作用：设置SetColumnColor。
	// 参数：clrHeader：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetColumnColor(COLORREF clrHeader){m_clrHeader = clrHeader;}
	// 函数 EnableAutoFilling
	// 作用：改变EnableAutoFilling的显示或可用状态。
	// 参数：bEnable：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void EnableAutoFilling(BOOL bEnable) { m_bAutoFilling = bEnable; }
	// 函数 GetRowHeight
	// 作用：读取GetRowHeight。
	// 参数：iRow：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	// 过程：函数里会调用 SetMsgID。
	int  GetRowHeight(int iRow) const;
	// 函数 SetScrollPos32
	// 作用：设置SetScrollPos32。
	// 参数：nBar：整数；nPos：整数；bRedraw：是或否。
	// 返回：返回是或否。
	// 过程：函数里会调用 SetMsgID。
	BOOL SetScrollPos32(int nBar, int nPos, BOOL bRedraw = TRUE);
	// 函数 SetMsgID
	// 作用：设置SetMsgID。
	// 参数：nID：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetMsgID(UINT nID) { m_nMsgID=nID; }
	// 函数 SetColLockedCount
	// 作用：设置SetColLockedCount。
	// 参数：nCount：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetColLockedCount(UINT nCount){m_iFixedColCount=nCount;}
	// 函数 SetRowLockedCount
	// 作用：设置SetRowLockedCount。
	// 参数：nCount：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRowLockedCount(UINT nCount){m_iFixedRowCount=nCount;}
	// 函数 SetBkgColor
	// 作用：设置SetBkgColor。
	// 参数：clrBkg：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetBkgColor(COLORREF clrBkg){m_clrBkg = clrBkg;}

	// 函数 SetOddEvenColor
	// 作用：设置SetOddEvenColor。
	// 参数：clrOdd：颜色；clrEven：颜色。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetSelectedColor。
	void SetOddEvenColor(COLORREF clrOdd, COLORREF clrEven);
	// 函数 SetSelectedColor
	// 作用：设置SetSelectedColor。
	// 参数：clrSelected：颜色。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetSelectedColor(COLORREF clrSelected) { m_clrSelected = clrSelected; }

	// 函数 SetHeaderHeight
	// 作用：设置SetHeaderHeight。
	// 参数：nHeaderHeight：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetHeaderHeight(int nHeaderHeight) { m_iHeaderHeight = nHeaderHeight; }
	// 函数 SetRowHeight
	// 作用：设置SetRowHeight。
	// 参数：nRowHeight：整数。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetRowHeight(int nRowHeight) { m_iRowHeight = nRowHeight; }

protected:
	UINT	m_nMsgID; // 发送消息时的ID

	// 标题栏属性
	BOOL	m_bHasHeader; // 是否有标题栏
	BOOL	m_bAutoFilling; // 水平方向自动充满
	int		m_iHeaderHeight; // 标题栏的高度
	int		m_iMinColWidth; // 最小的栏宽度
	CPtrArray m_arrayColData; // 标题栏的数据
	COLORREF m_clrHeader;
	CFont	m_fontHeader; // 标题栏字体
	int		m_iColCount; // 列数
	
	// 报表属性
	int		m_iRowHeight; // 数据行的高度
	int		m_iFixedColCount; // 默认从左开始锁定
	int		m_iFixedRowCount; // 默认从上开始锁定
	COLORREF m_clrBkg; // 背景色
	CFont	m_fontItem; // 内容字体

	BOOL	m_bOddEvenColor;	// 是否使用奇偶色
	COLORREF m_clrOdd;	// 奇数行背景色
	COLORREF m_clrEven;	// 偶数行背景色
	COLORREF m_clrSelected; // 选中行的背景色

	// 报表数据
	CUIntArray m_arrayRowHeight; ///< 行的高度数组
    CReportDataArray m_arrayAllData; ///< 行数据数组
	int		m_iRowCount; ///< 行数

	CSize	m_sizeVirtual; ///< 实际report的滚动范围
	
	BOOL	m_bEnableMultiSelected; // 是否支持多选
	int		m_iLastSelectedRow; // 最后选择行，方便行多选时使用

	BOOL	m_bIsColClicked; // 标题栏被按下
	int		m_iColClickedIndex; 

	// 修改标题栏宽度
	BOOL	m_bIsColSizing; //  是否正在修改栏宽度
	int		m_iSizingColIndex; // 修改栏宽度时的栏序号
	long	m_lSizingColLeft; // 修改栏的最左边Client值
	long	m_lDrawingPos;

	// 当前状态
	BOOL	m_bEnableSort; //  是否支持排序
	BOOL	m_bEnableEdit; //  是否支持编辑等修改内容操作

	CBioInEdit*	m_pInEdit; // 当前编辑对象指针，当子项进行文本（数字）编辑时使用
	CBioInComboBox* m_pInComboBox;// 当前编辑对象指针，当子项进行数据选择时使用
	CBWColorWnd*	m_pColorWnd; // 颜色选择窗口
	int	m_iColorWndWidth;
	int	m_iColorWndHeight;

protected:
	// 函数 DECLARE_MESSAGE_MAP
	// 作用：执行DECLARE_MESSAGE_MAP。
	// 参数：无。
	// 返回：没有返回值。
	DECLARE_MESSAGE_MAP()

	// 函数 OnPaint
	// 作用：窗口需要重画时绘制内容。
	// 参数：无。
	// 返回：没有返回值。
	afx_msg void OnPaint();
	// 函数 OnEraseBkgnd
	// 作用：窗口擦除背景时绘制底色或背景图。
	// 参数：pDC：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 函数 OnHScroll
	// 作用：水平滚动条移动。
	// 参数：nSBCode：整数；nPos：整数；pScrollBar：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// 函数 OnVScroll
	// 作用：垂直滚动条移动。
	// 参数：nSBCode：整数；nPos：整数；pScrollBar：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// 函数 OnMouseWheel
	// 作用：转动鼠标滚轮。
	// 参数：nFlags：整数；zDelta；pt。
	// 返回：返回是或否。
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
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
	// 函数 OnSetCursor
	// 作用：响应 Windows 或自定义消息 OnSetCursor。
	// 参数：pWnd：指针，指向调用方传入的对象；nHitTest：整数；message。
	// 返回：返回是或否。
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	// 函数 OnLvnEndlabeledit
	// 作用：响应 Windows 或自定义消息 OnLvnEndlabeledit。
	// 参数：pNMHDR：指针，指向调用方传入的对象；pResult：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	afx_msg void OnLvnEndlabeledit(NMHDR *pNMHDR, LRESULT *pResult);
	// 函数 OnKeyDown
	// 作用：响应 Windows 或自定义消息 OnKeyDown。
	// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
	// 返回：没有返回值。
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	// 函数 PreTranslateMessage
	// 作用：消息送达窗口前先拦截键盘或鼠标。
	// 参数：pMsg：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	virtual BOOL PreTranslateMessage( MSG* pMsg );
};


