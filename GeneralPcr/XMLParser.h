// 【交接】 GeneralPcr\XMLParser.h
// 作用：XMLParser。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：XML_Node、GetAttrValue、at、CompareAttrName、CompareAttrValue、CompareOneOfTheAttr、CompareNoCase、size。
#pragma once

#include <vector>
#import "msxml3.dll"
#include "GeneralOperator.h"

struct XML_Node
{
	CString nodeName;
	CString nodeValue;
	std::vector<CString> vAttrName;
	std::vector<CString> vAttrValue;
	
	// 函数 XML_Node
	// 作用：执行XML_Node。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	XML_Node()
	{
		nodeName = "";
		nodeValue = "";
	}

	// 函数 GetAttrValue
	// 作用：读取GetAttrValue。
	// 参数：strName：字符串；strValue：字符串。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 size、at、CompareNoCase。
	BOOL GetAttrValue(CString strName, CString& strValue)
	{
		for(UINT i = 0; i < vAttrName.size(); i++)
		{
			if(!vAttrName.at(i).CompareNoCase(strName))
			{
				strValue = vAttrValue.at(i);
				return TRUE;
			}
		}
		return FALSE;
	}
	// 函数 CompareAttrName
	// 作用：执行CompareAttrName。
	// 参数：node。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 size、at、CompareNoCase。
	BOOL CompareAttrName(const XML_Node& node)
	{
		if(vAttrName.size() != node.vAttrName.size())
			return FALSE;
		for(UINT i = 0; i < vAttrName.size(); i++)
		{
			if(vAttrName.at(i).CompareNoCase(node.vAttrName.at(i)))
				return FALSE;
		}
		return TRUE;
	}
	// 函数 CompareAttrValue
	// 作用：执行CompareAttrValue。
	// 参数：node。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 size、at、CompareNoCase。
	BOOL CompareAttrValue(const XML_Node& node)
	{
		if(vAttrValue.size() != node.vAttrValue.size())
			return FALSE;
		for(UINT i = 0; i < vAttrValue.size(); i++)
		{
			if(vAttrValue.at(i).CompareNoCase(node.vAttrValue.at(i)))
				return FALSE;
		}
		return TRUE;
	}
	// 函数 CompareOneOfTheAttr
	// 作用：执行CompareOneOfTheAttr。
	// 参数：node。
	// 返回：返回是或否。失败时返回 FALSE。
	// 过程：函数里会调用 size、GetAttrValue、at、CompareNoCase。
	BOOL CompareOneOfTheAttr(const XML_Node& node)
	{
		for(UINT i = 0; i < node.vAttrName.size(); i++)
		{
			CString strName;
			if(!GetAttrValue(node.vAttrName.at(i), strName)
				&& node.vAttrValue.at(i).CompareNoCase(strName))
				return FALSE;			
		}
		return TRUE;
	}
	BOOL operator == (const XML_Node& node)
	{
		if(nodeName.CompareNoCase(node.nodeName)
			|| nodeValue.CompareNoCase(node.nodeValue)
			|| vAttrName.size() != node.vAttrName.size()
			|| vAttrValue.size() != node.vAttrValue.size()
			|| node.vAttrName.size() != node.vAttrValue.size())
		{
			return FALSE;
		}
		for(UINT i = 0; i < vAttrName.size(); i++)
		{
			if(vAttrName.at(i).CompareNoCase(node.vAttrName.at(i))
				|| vAttrValue.at(i).CompareNoCase(node.vAttrValue.at(i)))
			{
				return FALSE;
			}
		}
		return TRUE;
	}
	// 函数 Clear
	// 作用：更新或清除Clear。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 clear。
	void Clear()
	{
		nodeName = "";
		nodeValue = "";
		vAttrName.clear();
		vAttrValue.clear();
	}

};

class XMLParser
{
public:
	// 函数 XMLParser
	// 作用：执行XMLParser。
	// 参数：无。
	// 返回：没有返回值。
	XMLParser();
	// 函数 ~XMLParser
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~XMLParser(void);
	
	// 函数 GetFirstNode
	// 作用：读取GetFirstNode。
	// 参数：NodeName；node。
	// 返回：返回是或否。
	BOOL GetFirstNode(CString NodeName, XML_Node& node);
	// 函数 GetFirstNode
	// 作用：读取GetFirstNode。
	// 参数：node；pNode：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL GetFirstNode(XML_Node node, MSXML2::IXMLDOMElementPtr& pNode);
	// 函数 GetNodes
	// 作用：读取GetNodes。
	// 参数：NodeName；nodes。
	// 返回：返回是或否。
	BOOL GetNodes(CString NodeName, std::vector<XML_Node>& nodes);
	// 函数 GetNodeCount
	// 作用：读取GetNodeCount。
	// 参数：strNode：字符串；nCount：整数。
	// 返回：返回是或否。
	BOOL GetNodeCount(CString strNode, long& nCount);
	// 函数 GetChildNode
	// 作用：读取GetChildNode。
	// 参数：ParentName；lIndex；ChildNode。
	// 返回：返回是或否。
	BOOL GetChildNode(CString ParentName, long lIndex, XML_Node& ChildNode);
	// 函数 GetChildNodes
	// 作用：读取GetChildNodes。
	// 参数：ParentName；ChildNodes。
	// 返回：返回是或否。
	BOOL GetChildNodes(CString ParentName, std::vector<XML_Node>& ChildNodes);
	// 函数 GetChildCount
	// 作用：读取GetChildCount。
	// 参数：ParentName；lCount。
	// 返回：返回是或否。
	BOOL GetChildCount(CString ParentName, long& lCount);
	// 函数 GetXMLString
	// 作用：读取GetXMLString。
	// 参数：strXML：字符串。
	// 返回：返回是或否。
	BOOL GetXMLString(CString& strXML);
	// 函数 GetXMLString
	// 作用：读取GetXMLString。
	// 参数：strXML：字符串。
	// 返回：返回是或否。
	BOOL GetXMLString(BSTR& strXML);
	// 函数 GetFirstChild
	// 作用：读取GetFirstChild。
	// 参数：pParentNode：指针，指向调用方传入的对象；strChildNode：字符串；pChild：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL GetFirstChild(MSXML2::IXMLDOMNodePtr pParentNode, CString strChildNode, MSXML2::IXMLDOMElementPtr& pChild);

	// 函数 InsertItem
	// 作用：创建或加入InsertItem。
	// 参数：strParent：字符串；NewNode。
	// 返回：返回是或否。
	BOOL InsertItem(CString strParent, XML_Node NewNode);
	// 函数 InsertItem
	// 作用：创建或加入InsertItem。
	// 参数：strParent：字符串；pElement：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL InsertItem(CString strParent, MSXML2::IXMLDOMElementPtr pElement);
	// 函数 CreateElement
	// 作用：创建或加入CreateElement。
	// 参数：node；pElement：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL CreateElement(XML_Node node, MSXML2::IXMLDOMElementPtr& pElement);
	// 函数 CreateElement
	// 作用：创建或加入CreateElement。
	// 参数：strNode：字符串；pElement：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL CreateElement(CString strNode, MSXML2::IXMLDOMElementPtr& pElement);
	// 函数 DeleteItem
	// 作用：更新或清除DeleteItem。
	// 参数：strNode：字符串。
	// 返回：返回是或否。
	BOOL DeleteItem(CString strNode);
	// 函数 ModifyItemValue
	// 作用：执行ModifyItemValue。
	// 参数：strNode：字符串；strValue：字符串。
	// 返回：返回是或否。
	BOOL ModifyItemValue(CString strNode, CString strValue);
	// 函数 ModifyItemAttrValue
	// 作用：执行ModifyItemAttrValue。
	// 参数：strNode：字符串；strAttrName：字符串；strAttrValue：字符串。
	// 返回：返回是或否。
	BOOL ModifyItemAttrValue(CString strNode, CString strAttrName, CString strAttrValue);

	// 函数 XMLValidate
	// 作用：执行XMLValidate。
	// 参数：无。
	// 返回：返回是或否。
	BOOL XMLValidate();
	// 以XML格式字符串方式载入xml
	// 函数 LoadXML
	// 作用：读入LoadXML。
	// 参数：strXML：字符串。
	// 返回：返回是或否。
	BOOL LoadXML(CString strXML);
	// 函数 LoadXML
	// 作用：读入LoadXML。
	// 参数：bsXML。
	// 返回：返回是或否。
	BOOL LoadXML(const BSTR& bsXML);
	// 以文件路径方式载入xml
	// 函数 Load
	// 作用：读入Load。
	// 参数：strXMLFile：字符串。
	// 返回：返回是或否。
	BOOL Load(CString strXMLFile);
	// 将xml保存到给定文件路径中
	// 函数 SaveXMLFile
	// 作用：把SaveXMLFile写入文件、仪器或界面。
	// 参数：strFile：字符串。
	// 返回：返回是或否。
	BOOL SaveXMLFile(CString strFile);
	// 为xml增加StyleSheet 或 DTD
	// 函数 AddProcessingInstruction
	// 作用：创建或加入AddProcessingInstruction。
	// 参数：strType：字符串；strData：字符串。
	// 返回：返回是或否。
	BOOL AddProcessingInstruction(CString strType, CString strData);
	//
	// 函数 TransformToHTML
	// 作用：执行TransformToHTML。
	// 参数：strXSLTFile：字符串；strOut：字符串。
	// 返回：返回是或否。
	BOOL TransformToHTML(IN CString strXSLTFile, OUT _bstr_t& strOut);

protected:
	// 函数 InitialXMLCom
	// 作用：初始化InitialXMLCom。
	// 参数：无。
	// 返回：返回是或否。
	BOOL InitialXMLCom();//XML Com对象初始化

	// 函数 FindFirstNode
	// 作用：执行FindFirstNode。
	// 参数：name；pNode：指针，指向调用方传入的对象。
	// 返回：返回是或否。
	BOOL FindFirstNode(CString name, MSXML2::IXMLDOMNodePtr& pNode);
	// 函数 FindNodes
	// 作用：执行FindNodes。
	// 参数：name；vNodes。
	// 返回：返回是或否。
	BOOL FindNodes(CString name, std::vector<MSXML2::IXMLDOMNodePtr>& vNodes);
	// 函数 ParseSingleNode
	// 作用：执行ParseSingleNode。
	// 参数：name；node。
	// 返回：没有返回值。
	void ParseSingleNode(CString name, XML_Node& node);
	// 函数 NodeToNode
	// 作用：执行NodeToNode。
	// 参数：pNode：指针，指向调用方传入的对象；node。
	// 返回：返回是或否。
	BOOL NodeToNode(MSXML2::IXMLDOMNodePtr pNode, XML_Node& node);
	// 函数 FindChildNodes
	// 作用：执行FindChildNodes。
	// 参数：pParentNode：指针，指向调用方传入的对象；strChildNode：字符串；vNodes；bOnlyFirst：是或否。
	// 返回：返回是或否。
	BOOL FindChildNodes(MSXML2::IXMLDOMNodePtr pParentNode, CString strChildNode, std::vector<MSXML2::IXMLDOMNodePtr>& vNodes, BOOL bOnlyFirst = FALSE);
	// 函数 GetElementsCount
	// 作用：读取GetElementsCount。
	// 参数：nodes；nType：整数。
	// 返回：返回一个整数。0 经常表示没有数据或成功，负值经常表示失败。
	int  GetElementsCount(MSXML2::IXMLDOMNodeListPtr nodes, int nType = MSXML2::NODE_ELEMENT);


protected:
	MSXML2::IXMLDOMDocumentPtr m_Doc; // XML Document
};
