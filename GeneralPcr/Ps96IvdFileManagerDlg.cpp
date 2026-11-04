// 【交接】 GeneralPcr\Ps96IvdFileManagerDlg.cpp
// 作用：Ps96IvdFileManagerDlg 窗口。负责这个界面的创建、控件摆放、按钮和输入响应。计算和仪器命令在对应的数据类或运行类里完成。
// 先看这些函数：CPs96IvdFileManagerDlg、BEGIN_MESSAGE_MAP、ON_WM_ERASEBKGND、ON_WM_CREATE、ON_WM_LBUTTONDOWN、END_MESSAGE_MAP、OnEraseBkgnd、GetClientRect。
#include "StdAfx.h"
#include "Ps96IvdFileManagerDlg.h"


// 函数 CPs96IvdFileManagerDlg::CPs96IvdFileManagerDlg
// 作用：执行CPs96IvdFileManagerDlg。
// 参数：pParent：指针，指向调用方传入的对象。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPs96IvdFileManagerDlg::CPs96IvdFileManagerDlg(CWnd* pParent /*= NULL*/)
{
	m_pWorkDlg = (CWorkDlg*)pParent;
	m_iAddIconWHFat = 16;
	m_iAddIconWHThin = 4;
	m_iAddIconLeftIndent = 5;
	m_iRightIndent = 290;
}

// 函数 CPs96IvdFileManagerDlg::~CPs96IvdFileManagerDlg
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CPs96IvdFileManagerDlg::~CPs96IvdFileManagerDlg(void)
{

}

BEGIN_MESSAGE_MAP(CPs96IvdFileManagerDlg,CFileManageDlg)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// 函数 CPs96IvdFileManagerDlg::OnEraseBkgnd
// 作用：窗口擦除背景时绘制底色或背景图。
// 参数：pDC：指针，指向调用方传入的对象。
// 返回：返回是或否。
// 过程：函数里会调用 GetClientRect、CreateCompatibleDC、CreateCompatibleBitmap、Width、Height、SelectObject。
BOOL CPs96IvdFileManagerDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect; 
	GetClientRect(&rect);

	CDC memDc;
	memDc.CreateCompatibleDC(pDC);

	CBitmap bitMapCB;
	bitMapCB.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	CBitmap* pOldBitmapCB = memDc.SelectObject(&bitMapCB);

	memDc.FillSolidRect(rect.left,rect.top,rect.Width(),rect.Height(),RGB(0XFF,0XFF,0XFF));

	//绘制logo
	Graphics graphics(memDc.m_hDC);
	graphics.SetInterpolationMode(InterpolationMode::InterpolationModeBicubic);
	ImageAttributes ImgAtt;
	ImgAtt.SetWrapMode(WrapModeTileFlipXY);
	Rect destRect;
	destRect.X = rect.right - m_iRightIndent + m_iAddIconWHFat + 12 * m_dHoriRatio;
	destRect.Y = 2 * m_dVertRatio;
	destRect.Width = 76 * m_dHoriRatio;
	destRect.Height = 40 * m_dVertRatio;
	graphics.DrawImage(&m_imgLogo,destRect,0,0,m_imgLogo.GetWidth(),m_imgLogo.GetHeight(),UnitPixel,&ImgAtt);

	graphics.ReleaseHDC(memDc.m_hDC);

	//绘制软件版本号，20220513
	CFont* pOldFont = memDc.SelectObject(&m_fontSet);
	memDc.SetTextColor(m_txClr1);
	memDc.SetBkMode(TRANSPARENT);
	memDc.DrawText(SOFRVERION_STRING,CRect(destRect.GetRight(),0,rect.right,rect.bottom),DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	memDc.SelectObject(pOldFont);

	//绘制添加页码符号
	if(!m_rcAddIcon.IsRectEmpty())
	{
		int iWH = 4 * m_dHoriRatio;

		memDc.FillSolidRect(m_rcAddIcon.left,m_rcAddIcon.top + (m_rcAddIcon.Height() - iWH) / 2,m_rcAddIcon.Width(),iWH,CLR_SOFT_THEME);
		memDc.FillSolidRect(m_rcAddIcon.left + (m_rcAddIcon.Width() - iWH) / 2,m_rcAddIcon.top,iWH,m_rcAddIcon.Height(),CLR_SOFT_THEME);
	}

	//pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memDc,0,0,SRCCOPY);

	clock_t ckStart = clock();	
	Node<CRect>* pNodeRst = m_rcManage.m_lnkRcRst.GetHead();
	while(NULL != pNodeRst)
	{
		pDC->BitBlt(pNodeRst->data.left,pNodeRst->data.top,pNodeRst->data.Width(),pNodeRst->data.Height(),&memDc,pNodeRst->data.left,pNodeRst->data.top,SRCCOPY);
		pNodeRst = pNodeRst->pNext;
	}
	ckStart = clock() - ckStart;

	memDc.SelectObject(pOldBitmapCB);
	bitMapCB.DeleteObject();
	memDc.DeleteDC();

	return TRUE;
}

// 函数 CPs96IvdFileManagerDlg::OnCreate
// 作用：响应 Windows 或自定义消息 OnCreate。
// 参数：lpCreateStruct。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 CFileManageDlg::OnCreate。
int CPs96IvdFileManagerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_iAddIconWHFat *= m_dHoriRatio;
	m_iAddIconWHThin *= m_dHoriRatio;
	m_iAddIconLeftIndent *= m_dHoriRatio;

	return CFileManageDlg::OnCreate(lpCreateStruct);
}

// 函数 CPs96IvdFileManagerDlg::OnLButtonDown
// 作用：按下鼠标左键。
// 参数：nFlags：整数；point。
// 返回：没有返回值。
// 过程：函数里会调用 PtInRect、AddPage。
void CPs96IvdFileManagerDlg::OnLButtonDown(UINT nFlags,CPoint point)
{
	if(m_rcAddIcon.PtInRect(point))
	{
		AddPage();
	}

	return CDialogEx::OnLButtonDown(nFlags, point);
}

// 函数 CPs96IvdFileManagerDlg::SetCtrlPos
// 作用：设置SetCtrlPos。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 GetClientRect、GetSize、SetWindowPos、ClearRectToDelete、AddRectToDelete、CalcRectResult。
void CPs96IvdFileManagerDlg::SetCtrlPos()
{
	CRect rect;
	GetClientRect(&rect);

	int iStartX = m_iLeftIndent;
	for(int i = 0;i < m_lnkPageSwitchBtPtr.GetSize();++i)
	{
		(*m_lnkPageSwitchBtPtr[i])->SetWindowPos(this,iStartX,BT_TOP_START,m_iBtDefWidth,m_iBtHeight,SWP_NOZORDER);
		iStartX += m_iBtDefWidth;
	}

	int iBtTotalW = m_iBtRealWidth * m_lnkPageSwitchBtPtr.GetSize();

	m_rcAddIcon.left = iBtTotalW + m_iAddIconLeftIndent;
	m_rcAddIcon.right = iBtTotalW + m_iAddIconWHFat;
	m_rcAddIcon.top = BT_TOP_START + (m_iBtHeight - m_iAddIconWHFat) / 2;
	m_rcAddIcon.bottom = m_rcAddIcon.top + m_iAddIconWHFat;

	m_rcManage.m_rcInit = rect;
	m_rcManage.ClearRectToDelete();
	m_rcManage.AddRectToDelete(iStartX,BT_TOP_START,iBtTotalW,m_iBtHeight);
	m_rcManage.CalcRectResult();

	return;
}

// 函数 CPs96IvdFileManagerDlg::SetPageSwitchBtPos
// 作用：设置SetPageSwitchBtPos。
// 参数：iStart：整数。
// 返回：没有返回值。
// 过程：函数里会调用 GetSize。
void CPs96IvdFileManagerDlg::SetPageSwitchBtPos(int iStart)
{
	CFileManageDlg::SetPageSwitchBtPos(iStart);

	m_rcAddIcon.left = m_iLeftIndent + m_iBtRealWidth * m_lnkPageSwitchBtPtr.GetSize() + m_iAddIconLeftIndent;
	m_rcAddIcon.right = m_rcAddIcon.left + m_iAddIconWHFat;
	m_rcAddIcon.top = BT_TOP_START + (m_iBtHeight - m_iAddIconWHFat) / 2;
	m_rcAddIcon.bottom = m_rcAddIcon.top + m_iAddIconWHFat;

	return;
}

// 函数 CPs96IvdFileManagerDlg::AddNewPage
// 作用：创建或加入AddNewPage。
// 参数：pExpData：指针，指向调用方传入的对象；strFileName：字符串。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Invalidate。
int CPs96IvdFileManagerDlg::AddNewPage(CExperimentData* pExpData,CString strFileName /*= _T("")*/)
{
	int iRet = CFileManageDlg::AddNewPage(pExpData,strFileName);
	Invalidate();
	return iRet;
}

// 函数 CPs96IvdFileManagerDlg::DeletePage
// 作用：更新或清除DeletePage。
// 参数：pageId。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 Invalidate。
int CPs96IvdFileManagerDlg::DeletePage(int pageId)
{
	int iRet = CFileManageDlg::DeletePage(pageId);
	Invalidate();
	return iRet;
}

