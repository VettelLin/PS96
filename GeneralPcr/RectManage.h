// 【交接】 GeneralPcr\RectManage.h
// 作用：RectManage。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CRectManage、RectMinusRect、CalcRectResult、AddRectToDelete、ClearRectToDelete、AddRect、DeleteRect、AddRectRoundFrame。
#pragma once

#include "LinkList.h"

class CRectManage
{
public:
	// 函数 CRectManage
	// 作用：执行CRectManage。
	// 参数：无。
	// 返回：没有返回值。
	CRectManage(void);
	// 函数 ~CRectManage
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CRectManage(void);

	// 函数 CRectManage
	// 作用：执行CRectManage。
	// 参数：info。
	// 返回：没有返回值。
	CRectManage(const CRectManage& info);
	void operator=(const CRectManage& info);

	// 函数 RectMinusRect
	// 作用：执行RectMinusRect。
	// 参数：rcSource；rect：矩形区域；rcRst。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int RectMinusRect(CRect rcSource,CRect rect,CLinkList<CRect>& rcRst);
	// 函数 CalcRectResult
	// 作用：计算CalcRectResult。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int CalcRectResult();
	// 函数 AddRectToDelete
	// 作用：创建或加入AddRectToDelete。
	// 参数：rect：矩形区域。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddRectToDelete(CRect rect);
	// 函数 AddRectToDelete
	// 作用：创建或加入AddRectToDelete。
	// 参数：iLeft：整数；iTop：整数；iWidth：整数；iHeight：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddRectToDelete(int iLeft,int iTop,int iWidth,int iHeight);
	// 函数 ClearRectToDelete
	// 作用：更新或清除ClearRectToDelete。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int ClearRectToDelete();
	// 函数 AddRect
	// 作用：创建或加入AddRect。
	// 参数：rect：矩形区域。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddRect(CRect rect);
	// 函数 AddRect
	// 作用：创建或加入AddRect。
	// 参数：iLeft：整数；iTop：整数；iWidth：整数；iHeight：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddRect(int iLeft,int iTop,int iWidth,int iHeight);
	// 函数 DeleteRect
	// 作用：更新或清除DeleteRect。
	// 参数：rect：矩形区域。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int DeleteRect(CRect rect);

	// 函数 AddRectRoundFrame
	// 作用：创建或加入AddRectRoundFrame。
	// 参数：rect：矩形区域；iRoundH：整数；iFrameW：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddRectRoundFrame(CRect rect,int iRoundH,int iFrameW);	//添加圆角矩形的四角和边框矩形
	// 函数 AddRectRoundFrame
	// 作用：创建或加入AddRectRoundFrame。
	// 参数：iLeft：整数；iTop：整数；iWidth：整数；iHeight：整数；iRoundH：整数；iFrameW：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int AddRectRoundFrame(int iLeft,int iTop,int iWidth,int iHeight,int iRoundH,int iFrameW);	//添加圆角矩形的四角和边框矩形

public:
	CRect m_rcInit;

	CLinkList<CRect> m_lnkRcToDelete;
	CLinkList<CRect> m_lnkRcRst;
};

