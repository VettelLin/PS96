// 【交接】 BWGenUILib\BioInComboBox.cpp
// 作用：BioInComboBox 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CBioInComboBox、DeleteObject、BEGIN_MESSAGE_MAP、ON_WM_CREATE、ON_WM_KILLFOCUS、ON_WM_KEYDOWN、END_MESSAGE_MAP。
// BioInComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "BioInComboBox.h"
#include ".\bioincombobox.h"


// CBioInComboBox

IMPLEMENT_DYNAMIC(CBioInComboBox, CComboBox)

/**
 * 对象构造函数，对父窗口是ListCtrl适用
 * \param nItem 列表控件的行数
 * \param nSubItem 项的列数
 * \param strText 初始文本
 * \param pArrayColText 可供选择的数据项数组
 * \return 
 */
// 函数 CBioInComboBox::CBioInComboBox
// 作用：执行CBioInComboBox。
// 参数：nItem：整数；nSubItem：整数；strText：字符串；pArrayColText：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CBioInComboBox::CBioInComboBox(int nItem, int nSubItem, CString strText, CStringArray* pArrayColText)
{
	m_nParentType = TYPE_LISTCTRL;
	m_nItem = nItem;
	m_nSubItem = nSubItem;
	m_strInitText = strText;
	m_pArrayColText = pArrayColText;

	m_bEscPressed = FALSE;
	m_pFont = NULL;
	m_bTabDown = FALSE;
}

/**
 * 对象构造函数，对父窗口是TreeCtrl适用
 * \param hItem 树型控件的项句柄
 * \param nSubItem 项的列数
 * \param strText 初始文本
 * \param pArrayColText 可供选择的数据项数组
 * \return 
 */
// 函数 CBioInComboBox::CBioInComboBox
// 作用：执行CBioInComboBox。
// 参数：hItem；nSubItem：整数；strText：字符串；pArrayColText：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CBioInComboBox::CBioInComboBox(HTREEITEM hItem, int nSubItem, CString strText, CStringArray* pArrayColText)
{
	m_nParentType = TYPE_TREECTRL;
	m_hItem = hItem;
	m_nSubItem = nSubItem;
	m_strInitText = strText;
	m_pArrayColText = pArrayColText;

	m_bEscPressed = FALSE;

	m_pFont = NULL;
	m_bTabDown = FALSE;
}

/** 
 * 对象析构函数，无操作
 * \return 
 */
// 函数 CBioInComboBox::~CBioInComboBox
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject。
CBioInComboBox::~CBioInComboBox()
{
	if (m_pFont != NULL)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
		m_pFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CBioInComboBox, CComboBox)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CBioInComboBox message handlers


/**
 * 对象创建，设置焦点，保存需要属性
 * \param lpCreateStruct 被创建窗口的结构信息
 * \return 0：继续创建，-1：消灭
 */
// 函数 CBioInComboBox::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetFont、GetParent、GetFont、GetSize、AddString、GetAt。
int CBioInComboBox::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (m_pFont == NULL)
	{
		SetFont(GetParent()->GetFont());
	}else
	{
		SetFont(m_pFont);
	}

	for (int i=0; i<m_pArrayColText->GetSize(); i++)
	{
		AddString(m_pArrayColText->GetAt(i));
	}

	SelectString(-1, m_strInitText);
	SetFocus();

	return 0;
}

/**
 * 在失去焦点时向父窗口发送修改数据消息
 * \param pNewWnd 得到焦点的窗口指针
 */
// 函数 CBioInComboBox::OnKillFocus
// 作用：响应 Windows 或自定义消息 OnKillFocus。
// 参数：pNewWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetCurSel、Empty、GetLBText、GetParent、GetDlgCtrlID、LPTSTR。
void CBioInComboBox::OnKillFocus(CWnd* pNewWnd)
{
	CComboBox::OnKillFocus(pNewWnd);

	CString strText;
	int nSel = GetCurSel();
	if (nSel == -1)
		strText.Empty();
	else
        GetLBText(nSel, strText);
	
	// Send Notification to parent
	if (m_nParentType == TYPE_LISTCTRL)
	{
		LV_DISPINFO dispinfo;
		dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
		dispinfo.hdr.idFrom = GetDlgCtrlID();
		dispinfo.hdr.code = LVN_ENDLABELEDIT;
		
		dispinfo.item.mask = LVIF_TEXT;
		dispinfo.item.iItem = m_nItem;
		dispinfo.item.iSubItem = m_nSubItem;
		dispinfo.item.pszText = m_bEscPressed ? LPTSTR((LPCTSTR)m_strInitText) : LPTSTR((LPCTSTR)strText);
		dispinfo.item.cchTextMax = m_bEscPressed ? m_strInitText.GetLength() : strText.GetLength();
		
		GetParent()->SendMessage( WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo );
	}
	else 
	{
		NMTVDISPINFO  dispinfo;
		dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
		dispinfo.hdr.idFrom = GetDlgCtrlID();
		dispinfo.hdr.code = TVN_ENDLABELEDIT;
		
		dispinfo.item.mask = LVIF_TEXT;
		dispinfo.item.hItem = m_hItem;
		dispinfo.item.pszText = m_bEscPressed ? LPTSTR((LPCTSTR)m_strInitText) : LPTSTR((LPCTSTR)strText);
		dispinfo.item.cchTextMax = m_bEscPressed ? m_strInitText.GetLength() : strText.GetLength();
		dispinfo.item.lParam = m_nSubItem; // 列序号
		
		GetParent()->SendMessage( WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo );
	}
}

/**
 * 取得选择框的初始选择文本
 * \return 选择框初始文本
 */
// 函数 CBioInComboBox::GetInitText
// 作用：读取GetInitText。
// 参数：无。
// 返回：返回一段文字。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CString CBioInComboBox::GetInitText()
{
	return m_strInitText;
}

// 函数 CBioInComboBox::SetUserFont
// 作用：设置SetUserFont。
// 参数：lf。
// 返回：没有返回值。
// 过程：函数里会调用 CFont、DeleteObject、CreateFontIndirect。
void CBioInComboBox::SetUserFont(LOGFONT lf)
{
	if (m_pFont == NULL)
	{
		m_pFont = new CFont();
	}
	else
	{
		m_pFont->DeleteObject();
	}

	m_pFont->CreateFontIndirect(&lf);
}

// 函数 CBioInComboBox::OnKeyDown
// 作用：响应 Windows 或自定义消息 OnKeyDown。
// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetParent、SetFocus。
void CBioInComboBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		m_bTabDown = TRUE;
		GetParent()->SetFocus();
		return;
	}
	else if (nChar == VK_RETURN)
	{
		GetParent()->SetFocus();
		return;
	}

	CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}
