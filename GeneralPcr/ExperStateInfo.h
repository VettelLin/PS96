// 【交接】 GeneralPcr\ExperStateInfo.h
// 作用：ExperStateInfo 数据对象。保存一组界面或算法要用的参数，并提供赋值、比较或读写。
// 先看这些函数：CExperStateInfo。
#pragma once

typedef enum InstruConnectState{
	EICS_CONNECT_SUCCESS,EICS_CONNECT_FAIL,EICS_NONE
}EINSTRUCONNECTSTATE;

typedef enum ExperType{
	EET_ABSOLUTE,EET_MELT,EET_NONE
}EEXPERTYPE;

class CExperStateInfo
{
public:
	// 函数 CExperStateInfo
	// 作用：执行CExperStateInfo。
	// 参数：无。
	// 返回：没有返回值。
	CExperStateInfo(void);
	// 函数 ~CExperStateInfo
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CExperStateInfo(void);

	// 函数 CExperStateInfo
	// 作用：执行CExperStateInfo。
	// 参数：info。
	// 返回：没有返回值。
	CExperStateInfo(const CExperStateInfo& info);
	void operator=(const CExperStateInfo& info);

public:
	EINSTRUCONNECTSTATE m_eInstruConnectState;	//仪器连接状态
	EEXPERTYPE m_eExperType;	//实验类型

	CString m_strModel;	//仪器型号
	CString m_strExperName;	//实验名称
	CString m_strRemainTime;	//剩余时间
	CString m_strExperStartTime;	//实验开始时间
	double m_dProgress;	//实验进度
	double m_dExperTem;	//实验运行过程中的实时温度
};

