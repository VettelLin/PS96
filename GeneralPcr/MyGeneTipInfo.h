// 【交接】 GeneralPcr\MyGeneTipInfo.h
// 作用：MyGeneTipInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CMyGeneTipInfo。
#pragma once

typedef enum TipType
{
	EGTT_NORMAL = 1,EGTT_QUERY,EGTT_WARNING
}EGENETIPTYPE;

class CMyGeneTipInfo
{
public:
	// 函数 CMyGeneTipInfo
	// 作用：执行CMyGeneTipInfo。
	// 参数：无。
	// 返回：没有返回值。
	CMyGeneTipInfo(void);
	// 函数 ~CMyGeneTipInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CMyGeneTipInfo(void);

	// 函数 CMyGeneTipInfo
	// 作用：执行CMyGeneTipInfo。
	// 参数：geneTipInfo。
	// 返回：没有返回值。
	CMyGeneTipInfo(const CMyGeneTipInfo& geneTipInfo);
	void operator=(const CMyGeneTipInfo& geneTipInfo);

public:
	CWnd* m_pParent;
	CString m_strTipInfo;
	EGENETIPTYPE m_eGeneTipType;
};

