// 【交接】 GeneralPcr\HoleSelectSet.h
// 作用：HoleSelectSet。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CHoleSelectSet。
#pragma once

typedef enum HoleDefaultDisplay{
	EHDD_PATIENTNAME,EHDD_TUBENAME,EHDD_SAMID,EHDD_SAMNAME
}EHOLEDEFAULTDISPLAY;

class CHoleSelectSet
{
public:
	// 函数 CHoleSelectSet
	// 作用：执行CHoleSelectSet。
	// 参数：无。
	// 返回：没有返回值。
	CHoleSelectSet(void);
	// 函数 ~CHoleSelectSet
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CHoleSelectSet(void);

	// 函数 CHoleSelectSet
	// 作用：执行CHoleSelectSet。
	// 参数：holeSelSet。
	// 返回：没有返回值。
	CHoleSelectSet(const CHoleSelectSet& holeSelSet);
	void operator=(const CHoleSelectSet& holeSelSet);

public:
	EHOLEDEFAULTDISPLAY m_eHoleDefDisplay;
};

