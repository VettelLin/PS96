// 【交接】 GeneralPcr\PopTipInfo.cpp
// 作用：PopTipInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：PopTipInfo、geneTipDlg、SetNoteInfo、SetGeneTipType、DoModal、PopNormalTipInfo、PopQueryTipInfo、PopWarningTipInfo。
#include "StdAfx.h"
#include "PopTipInfo.h"
#include "MyGeneTipDlg.h"

int PopTipInfo(CMyGeneTipInfo geneTipInfo)
{
	CMyGeneTipDlg geneTipDlg(geneTipInfo.m_pParent);
	geneTipDlg.SetNoteInfo(geneTipInfo.m_strTipInfo);
	geneTipDlg.SetGeneTipType(geneTipInfo.m_eGeneTipType);
	geneTipDlg.DoModal();  
	return geneTipDlg.m_retCode;
}

int PopNormalTipInfo(CString strTip)
{
	CMyGeneTipDlg geneTipDlg;
	geneTipDlg.SetNoteInfo(strTip);
	geneTipDlg.DoModal();  
	return geneTipDlg.m_retCode;
}

int PopQueryTipInfo(CString strTip)
{
	CMyGeneTipDlg geneTipDlg;
	geneTipDlg.SetNoteInfo(strTip);
	geneTipDlg.SetGeneTipType(EGTT_QUERY);
	geneTipDlg.DoModal();  
	return geneTipDlg.m_retCode;
}

int PopWarningTipInfo(CString strTip)
{
	CMyGeneTipDlg geneTipDlg;
	geneTipDlg.SetNoteInfo(strTip);
	geneTipDlg.SetGeneTipType(EGTT_WARNING);
	geneTipDlg.DoModal();  
	return geneTipDlg.m_retCode;
}

