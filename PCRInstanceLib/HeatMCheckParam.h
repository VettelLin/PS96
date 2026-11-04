// 【交接】 PCRInstanceLib\HeatMCheckParam.h
// 作用：HeatMCheckParam。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CHeatMCheckParam、GetPeltierCheckParam、IsNeedCheck、ResetCheckResult、AddCheckResult、GetCheckResult、IsSuccessful。
#pragma once

#include "PeltierCheckParam.h"

class AFX_EXT_CLASS CHeatMCheckParam
{
public:
	// 函数 CHeatMCheckParam
	// 作用：执行CHeatMCheckParam。
	// 参数：无。
	// 返回：没有返回值。
	CHeatMCheckParam(void);
	// 函数 ~CHeatMCheckParam
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CHeatMCheckParam(void);

	// 函数 CHeatMCheckParam
	// 作用：执行CHeatMCheckParam。
	// 参数：info。
	// 返回：没有返回值。
	CHeatMCheckParam(const CHeatMCheckParam& info);
	void operator=(const CHeatMCheckParam& info);

	// 函数 GetPeltierCheckParam
	// 作用：读取GetPeltierCheckParam。
	// 参数：iPeltierId：整数。
	// 返回：返回指针 CPeltierCheckParam*。指针为空表示没有取到对象。
	virtual CPeltierCheckParam* GetPeltierCheckParam(int iPeltierId);
	// 函数 IsNeedCheck
	// 作用：判断IsNeedCheck是否成立。
	// 参数：无。
	// 返回：返回是或否。
	virtual	BOOL IsNeedCheck();
			
			// 函数 ResetCheckResult
			// 作用：更新或清除ResetCheckResult。
			// 参数：无。
			// 返回：没有返回值。
			void ResetCheckResult();
			// 函数 AddCheckResult
			// 作用：创建或加入AddCheckResult。
			// 参数：strData：字符串。
			// 返回：没有返回值。
			void AddCheckResult(CString strData);
			// 函数 GetCheckResult
			// 作用：读取GetCheckResult。
			// 参数：无。
			// 返回：返回一段文字。
			CString GetCheckResult();	
			// 函数 IsSuccessful
			// 作用：判断IsSuccessful是否成立。
			// 参数：无。
			// 返回：返回是或否。
			BOOL IsSuccessful();

protected:
	CPeltierCheckParam m_peltier1ChkParam;
	CPeltierCheckParam m_peltier2ChkParam;
	CPeltierCheckParam m_peltier3ChkParam;

	CString m_strChkRst;
};

