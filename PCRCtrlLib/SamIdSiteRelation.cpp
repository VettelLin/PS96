// 【交接】 PCRCtrlLib\SamIdSiteRelation.cpp
// 作用：SamIdSiteRelation。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CSamIdSiteRelation、AddSamIdSite、find、push_back、Clear、clear、GetRelationCount、size。
#include "StdAfx.h"
#include "SamIdSiteRelation.h"

// 函数 CSamIdSiteRelation::CSamIdSiteRelation
// 作用：执行CSamIdSiteRelation。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSamIdSiteRelation::CSamIdSiteRelation(void)
{

}

// 函数 CSamIdSiteRelation::~CSamIdSiteRelation
// 作用：析构函数。对象销毁时释放它占用的资源。
// 参数：无。
// 返回：没有返回值。
// 过程：逻辑写在函数体内，没有再转调其他项目函数。
CSamIdSiteRelation::~CSamIdSiteRelation(void)
{

}

// 函数 CSamIdSiteRelation::AddSamIdSite
// 作用：创建或加入AddSamIdSite。
// 参数：strSamId：字符串；iSiteIndex：整数。
// 返回：没有返回值。
// 过程：函数里会调用 find、end、push_back、size。
void CSamIdSiteRelation::AddSamIdSite(CString strSamId,int iSiteIndex)
{
#ifdef SAMIDSITEINDEX_USE_MAP_MODE
	map<CString,vector<int>>::iterator iter = m_mapRelation.find(strSamId);
	if(m_mapRelation.end() != iter)
	{
		iter->second.push_back(iSiteIndex);
		return;
	}

	vector<int> vecTemp;
	vecTemp.push_back(iSiteIndex);
	m_mapRelation[strSamId] = vecTemp;
#else
	BOOL bFind = FALSE;
	for(int i = 0;i < m_vecSamId.size();++i)
	{
		if(strSamId == m_vecSamId[i])
		{
			bFind = TRUE;
			m_2vecSiteIndex[i].push_back(iSiteIndex);
			break;
		}
	}

	if(!bFind)
	{
		m_vecSamId.push_back(strSamId);
		vector<int> vecTemp;
		vecTemp.push_back(iSiteIndex);
		m_2vecSiteIndex.push_back(vecTemp);
	}
#endif
	return;
}

// 函数 CSamIdSiteRelation::Clear
// 作用：更新或清除Clear。
// 参数：无。
// 返回：没有返回值。
// 过程：函数里会调用 clear。
void CSamIdSiteRelation::Clear()
{
#ifdef SAMIDSITEINDEX_USE_MAP_MODE
	m_mapRelation.clear();
#else
	m_vecSamId.clear();
	m_2vecSiteIndex.clear();
#endif
	return;
}

// 函数 CSamIdSiteRelation::GetRelationCount
// 作用：读取GetRelationCount。
// 参数：无。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size。
int CSamIdSiteRelation::GetRelationCount()
{
#ifdef SAMIDSITEINDEX_USE_MAP_MODE
	return m_mapRelation.size();
#else
	return m_vecSamId.size();
#endif
}

// 函数 CSamIdSiteRelation::GetRelationAt
// 作用：读取GetRelationAt。
// 参数：iRelationIndex：整数；strId：字符串；vecSiteIndex。
// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
// 过程：函数里会调用 size、begin、end。
int CSamIdSiteRelation::GetRelationAt(int iRelationIndex,CString& strId,vector<int>& vecSiteIndex)
{
#ifdef SAMIDSITEINDEX_USE_MAP_MODE
	if(iRelationIndex < 0)
	{
		return -1;
	}
	if(iRelationIndex >= m_mapRelation.size())
	{
		return -2;
	}

	int iCount = 0;
	for(map<CString,vector<int>>::iterator iter = m_mapRelation.begin();iter != m_mapRelation.end();++iter,++iCount)
	{
		if(iCount == iRelationIndex)
		{
			strId = iter->first;
			vecSiteIndex = iter->second;
			return 0;
		}
	}
	return -3;
#else
	if(iRelationIndex < 0)
	{
		return -1;
	}
	if(iRelationIndex >= m_vecSamId.size())
	{
		return -2;
	}

	strId = m_vecSamId[iRelationIndex];
	vecSiteIndex = m_2vecSiteIndex[iRelationIndex];

	return 0;
#endif
}
