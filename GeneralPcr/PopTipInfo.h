// 【交接】 GeneralPcr\PopTipInfo.h
// 作用：PopTipInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：PopTipInfo、PopNormalTipInfo、PopQueryTipInfo、PopWarningTipInfo。
#pragma once

#include "MyGeneTipInfo.h"

int PopTipInfo(CMyGeneTipInfo geneTipInfo);

int PopNormalTipInfo(CString strTip);

int PopQueryTipInfo(CString strTip);

int PopWarningTipInfo(CString strTip);
