// 【交接】 GeneralPcr\TubeChanEditInfo.h
// 作用：TubeChanEditInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CTubeChanEditInfo、GetBeAllTubeSameSet。
#pragma once
class CTubeChanEditInfo
{
public:
	// 函数 CTubeChanEditInfo
	// 作用：执行CTubeChanEditInfo。
	// 参数：无。
	// 返回：没有返回值。
	CTubeChanEditInfo(void);
	// 函数 ~CTubeChanEditInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CTubeChanEditInfo(void);

	// 函数 CTubeChanEditInfo
	// 作用：执行CTubeChanEditInfo。
	// 参数：info。
	// 返回：没有返回值。
	CTubeChanEditInfo(const CTubeChanEditInfo& info);
	void operator=(const CTubeChanEditInfo& info);

	// 函数 GetBeAllTubeSameSet
	// 作用：读取GetBeAllTubeSameSet。
	// 参数：无。
	// 返回：返回是或否。
	BOOL GetBeAllTubeSameSet();	//判断是否是所有孔位在某些参数上要保持一致（通道的染料名和颜色标识）

public:
	int m_iRowId;
	int m_iColId;
	BOOL m_bChecked;
	double m_dData;
	int m_iDpd;	//m_dData的小数点位数
	CString m_strData;
	COLORREF m_clrData;
};

