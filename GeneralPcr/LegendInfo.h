// 【交接】 GeneralPcr\LegendInfo.h
// 作用：LegendInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CLegendInfo、AddSingleLegendInfo、GetSingleLegendCount、GetSingleLegendInfo、ResetSegLegendText。
#pragma once

#include "SingleLgdInfo.h"
#include "FontSet.h"
#include "LinkList.h"
#include <GdiPlus.h>
using namespace Gdiplus;

class CLegendInfo: public CFontSet
{
public:
	// 函数 CLegendInfo
	// 作用：执行CLegendInfo。
	// 参数：无。
	// 返回：没有返回值。
	CLegendInfo(void);
	// 函数 ~CLegendInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CLegendInfo(void);

	// 函数 CLegendInfo
	// 作用：执行CLegendInfo。
	// 参数：info。
	// 返回：没有返回值。
	CLegendInfo(const CLegendInfo& info);
	void operator=(const CLegendInfo& info);

			// 函数 AddSingleLegendInfo
			// 作用：创建或加入AddSingleLegendInfo。
			// 参数：singleLgdInfo。
			// 返回：没有返回值。
			void AddSingleLegendInfo(CSingleLgdInfo& singleLgdInfo);

			// 函数 GetSingleLegendCount
			// 作用：读取GetSingleLegendCount。
			// 参数：无。
			// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
			int GetSingleLegendCount();
			// 函数 GetSingleLegendInfo
			// 作用：读取GetSingleLegendInfo。
			// 参数：iIndex：整数。
			// 返回：返回指针 CSingleLgdInfo*。指针为空表示没有取到对象。
			CSingleLgdInfo* GetSingleLegendInfo(int iIndex);

	// 函数 ResetSegLegendText
	// 作用：更新或清除ResetSegLegendText。
	// 参数：pLgdInfo：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	static  void ResetSegLegendText(CLegendInfo* pLgdInfo);

public:
	int m_iLeftIndent;	//图例起始位置左侧缩进
	int m_iRoundRadius;	//圆形半径
	int m_iInrIconToTx;	//图形到文本之间的间隔
	int m_iInrTxToIcon;	//文本到图形之间的间隔
	int m_iOneCharW;	//单个字符占用的宽度（平均值）

	Color m_clrFrame;	//边框颜色
	Color m_clrBk;	//背景颜色
	Color m_clrBkEnd;	//背景颜色(渐变色终点颜色)

private:
	CLinkList<CSingleLgdInfo> m_lnkSingleLgdInfo;
};

