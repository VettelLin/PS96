// 【交接】 BWGenUILib\BWInEdit.cpp
// 作用：BWInEdit 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：IMPLEMENT_DYNAMIC、CBWInEdit、DeleteObject、BEGIN_MESSAGE_MAP、ON_WM_CREATE、ON_WM_CHAR、ON_WM_KILLFOCUS、ON_WM_KEYDOWN。
// BWInEdit.cpp : implementation file
//

#include "stdafx.h"
#include "BWGenUILib.h"
#include "BWInEdit.h"


// CBWInEdit

IMPLEMENT_DYNAMIC(CBWInEdit, CEdit)

// 函数 CBWInEdit::CBWInEdit
// 作用：执行CBWInEdit。
// 参数：iItem：整数；iSubItem：整数；strText：字符串。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CBWInEdit::CBWInEdit(int iItem, int iSubItem, CString strText)
{
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_nFlag = 0;
	m_strInitText = strText;

	m_bIsNumEdit = FALSE;
	m_dMinValue = -DBL_MAX;
	m_nPrecision = 0;
	m_dMaxValue = DBL_MAX;

	m_bTabDown = FALSE;
	m_bEscPressed = FALSE;

	m_pFont = NULL;
}

// 函数 CBWInEdit::~CBWInEdit
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 DeleteObject。
CBWInEdit::~CBWInEdit()
{
	if (m_pFont != NULL)
	{
		m_pFont->DeleteObject();
		delete m_pFont;
		m_pFont = NULL;
	}
}


BEGIN_MESSAGE_MAP(CBWInEdit, CEdit)
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CBWInEdit message handlers

/**
 * 对象创建，设置焦点，保存需要属性
 * \param lpCreateStruct 被创建窗口的结构信息
 * \return 0：继续创建，-1：消灭
 */
// 函数 CBWInEdit::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 SetFont、GetParent、GetFont、SetWindowText、SetFocus、SetSel。
int CBWInEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Set the proper font
	if (m_pFont == NULL)
	{
		SetFont(GetParent()->GetFont());
	}else
	{
		SetFont(m_pFont);
	}

	SetWindowText(m_strInitText);
	SetFocus();
	SetSel(0, -1 );

	return 0;
}


/**
 * \brief 在字母输入时处理特殊输入
 *
 * 可以根据编辑要求的具体类型，根据不同输入的要求对输入进行过滤，如只能输入
 * 数字时，对字母输入进行忽略。
 * \param nChar  输入键的字母代码
 * \param nRepCnt 重复次数
 * \param nFlags 标记
 */
// 函数 CBWInEdit::OnChar
// 作用：响应 Windows 或自定义消息 OnChar。
// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetParent、SetFocus、isdigit。
void CBWInEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if( nChar == VK_ESCAPE || nChar == VK_RETURN)
	{
		if( nChar == VK_ESCAPE )
			m_bEscPressed = TRUE;

		GetParent()->SetFocus();
		return;
	}

	if (m_bIsNumEdit)
	{
		if (nChar == 46/*处理小数点*/)
		{
			if (m_nPrecision != 0)
				CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		//else if (m_bIsMinus && nChar == 45/*处理负号*/) 
		//{
		//	CEdit::OnChar(nChar, nRepCnt, nFlags);
		//}
		else if (isdigit(nChar) || nChar == VK_BACK || nChar == VK_DELETE || nChar == VK_SPACE)
		{
			CEdit::OnChar(nChar, nRepCnt, nFlags);
		}
		return;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}


/**
 * 在失去焦点时向父窗口发送修改数据消息
 * \param pNewWnd 得到焦点的窗口指针
 */
// 函数 CBWInEdit::OnKillFocus
// 作用：响应 Windows 或自定义消息 OnKillFocus。
// 参数：pNewWnd：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：函数里会调用 GetWindowText、TrimLeft、TrimRight、_tstof、Format、_T。
void CBWInEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	CString strText;
	GetWindowText(strText);

	strText.TrimLeft();
	strText.TrimRight();
	if (m_bIsNumEdit)
	{	
		double dValue = _tstof(strText);
		if (dValue < m_dMinValue)
			dValue = m_dMinValue;
		else if (dValue > m_dMaxValue)
			dValue = m_dMaxValue;
		CString strFormat;
		strFormat.Format(_T("%%.%df"), m_nPrecision);
		strText.Format(strFormat, dValue);
	}

	LV_DISPINFO dispinfo;
	dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	dispinfo.hdr.idFrom = GetDlgCtrlID();
	dispinfo.hdr.code = LVN_ENDLABELEDIT;

	dispinfo.item.mask = LVIF_TEXT;
	dispinfo.item.iItem = m_iItem;
	dispinfo.item.iSubItem = m_iSubItem;
	dispinfo.item.lParam = m_nFlag;
	dispinfo.item.pszText = m_bEscPressed ? LPTSTR((LPCTSTR)m_strInitText) : LPTSTR((LPCTSTR)strText);
	dispinfo.item.cchTextMax = m_bEscPressed ? m_strInitText.GetLength() : strText.GetLength();

	GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&dispinfo );
}

// 设置是否是数字编辑
// 函数 CBWInEdit::EnableNumEdit
// 作用：改变EnableNumEdit的显示或可用状态。
// 参数：dMinValue：小数；dMaxValue：小数。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
void CBWInEdit::EnableNumEdit(double dMinValue, double dMaxValue)
{
	m_bIsNumEdit = TRUE;
	m_dMinValue = dMinValue;
	m_dMaxValue = dMaxValue;
}

// 函数 CBWInEdit::SetUserFont
// 作用：设置SetUserFont。
// 参数：lf。
// 返回：没有返回值。
// 过程：函数里会调用 CFont、DeleteObject、CreateFontIndirect。
void CBWInEdit::SetUserFont(LOGFONT lf)
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

// 函数 CBWInEdit::OnKeyDown
// 作用：响应 Windows 或自定义消息 OnKeyDown。
// 参数：nChar：整数；nRepCnt：整数；nFlags：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetParent、SetFocus。
void CBWInEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_TAB)
	{
		m_bTabDown = TRUE;
		GetParent()->SetFocus();
		return;
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
