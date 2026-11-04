// 【交接】 PCRCtrlLib\SamIdSiteRelation.h
// 作用：SamIdSiteRelation。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSamIdSiteRelation、AddSamIdSite、Clear、GetRelationCount、GetRelationAt。
#pragma once

#include<map>
#include <vector>

using namespace std;

//#define SAMIDSITEINDEX_USE_MAP_MODE	//使用映射结构体保存对应关系

class AFX_EXT_CLASS CSamIdSiteRelation
{
public:
	// 函数 CSamIdSiteRelation
	// 作用：执行CSamIdSiteRelation。
	// 参数：无。
	// 返回：没有返回值。
	CSamIdSiteRelation(void);
	// 函数 ~CSamIdSiteRelation
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CSamIdSiteRelation(void);

	// 函数 AddSamIdSite
	// 作用：创建或加入AddSamIdSite。
	// 参数：strSamId：字符串；iSiteIndex：整数。
	// 返回：没有返回值。
	void AddSamIdSite(CString strSamId,int iSiteIndex);	//添加样本ID、孔位下标组合信息
	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	void Clear();	//清空map

	// 函数 GetRelationCount
	// 作用：读取GetRelationCount。
	// 参数：无。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetRelationCount();
	// 函数 GetRelationAt
	// 作用：读取GetRelationAt。
	// 参数：iRelationIndex：整数；strId：字符串；vecSiteIndex。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int GetRelationAt(int iRelationIndex,CString& strId,vector<int>& vecSiteIndex);

public:

#ifdef SAMIDSITEINDEX_USE_MAP_MODE
	map<CString,vector<int>> m_mapRelation;
#else
	vector<CString> m_vecSamId;
	vector<vector<int>> m_2vecSiteIndex;
#endif
};

