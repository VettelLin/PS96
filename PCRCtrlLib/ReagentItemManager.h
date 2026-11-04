// 【交接】 PCRCtrlLib\ReagentItemManager.h
// 作用：ReagentItemManager。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CReagentItemManager、GetInstance、DestroyInstance、Initialize、InputItems、OutputItems、FindItemBy、AddItem。
#pragma once

#include "ReagentItem.h"



// 试剂项目管理器，对多个试剂项目进行保存、读取、删除等
class AFX_EXT_CLASS CReagentItemManager
{
public:
	// 函数 CReagentItemManager
	// 作用：执行CReagentItemManager。
	// 参数：无。
	// 返回：没有返回值。
	CReagentItemManager(void);
	// 函数 ~CReagentItemManager
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	~CReagentItemManager(void);
	 
// Operations
public:
	// 函数 GetInstance
	// 作用：读取GetInstance。
	// 参数：无。
	// 返回：返回指针 CReagentItemManager*。指针为空表示没有取到对象。
	// 过程：函数里会调用 AddItem、Add。
	static CReagentItemManager* GetInstance();
	// 函数 DestroyInstance
	// 作用：执行DestroyInstance。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 AddItem、Add。
	static void DestroyInstance();

	// 函数 Initialize
	// 作用：初始化Initialize。
	// 参数：strUserPath：字符串；strStartupPath：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 AddItem、Add。
	void Initialize(CString strUserPath, CString strStartupPath); // 读取项目目录下全部项目
	// 函数 InputItems
	// 作用：执行InputItems。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 AddItem、Add。
	void InputItems(); // 选择项目文件导入
	// 函数 OutputItems
	// 作用：执行OutputItems。
	// 参数：strSavePath：字符串；pArrayName：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	// 过程：函数里会调用 AddItem、Add。
	void OutputItems(CString strSavePath, CStringArray* pArrayName=NULL); // 选择项目文件导出

	// 函数 FindItemBy
	// 作用：执行FindItemBy。
	// 参数：strName：字符串。
	// 返回：返回指针 CReagentItem*。指针为空表示没有取到对象。
	// 过程：函数里会调用 AddItem、Add。
	CReagentItem* FindItemBy(CString strName);
	// 函数 AddItem
	// 作用：创建或加入AddItem。
	// 参数：m_arrayItems.Add(pItem。
	// 返回：没有返回值。
	// 过程：函数里会调用 Add。
	void AddItem(CReagentItem* pItem) { m_arrayItems.Add(pItem); }
	// 函数 DeleteItem
	// 作用：更新或清除DeleteItem。
	// 参数：strName：字符串。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetArrayItems。
	BOOL DeleteItem(CString strName);
	// 函数 DeleteItem
	// 作用：更新或清除DeleteItem。
	// 参数：iIndex：整数。
	// 返回：返回是或否。
	// 过程：函数里会调用 GetArrayItems。
	BOOL DeleteItem(int iIndex);
	// 函数 GetArrayItems
	// 作用：读取GetArrayItems。
	// 参数：无。
	// 返回：返回指针 CPtrArray*。指针为空表示没有取到对象。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	CPtrArray* GetArrayItems(){return &m_arrayItems;}
	// 函数 CanDelete
	// 作用：判断CanDelete是否成立。
	// 参数：iIndex：整数。
	// 返回：返回是或否。
	BOOL CanDelete(int iIndex);
	// 函数 NewOneItem
	// 作用：执行NewOneItem。
	// 参数：无。
	// 返回：返回指针 CReagentItem*。指针为空表示没有取到对象。
	CReagentItem* NewOneItem(); // 创建一个新的项目

	// 函数 GetBeNewPrj
	// 作用：读取GetBeNewPrj。
	// 参数：iIndex：整数。
	// 返回：返回是或否。
	BOOL GetBeNewPrj(int iIndex);

protected:
	// 函数 CreateFileNameByName
	// 作用：创建或加入CreateFileNameByName。
	// 参数：strPath：字符串；strName：字符串。
	// 返回：返回一段文字。
	CString CreateFileNameByName(CString strPath, CString strName);
	// 函数 InitializeFromPath
	// 作用：初始化InitializeFromPath。
	// 参数：strPath：字符串。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetItemChanged。
	void InitializeFromPath(CString strPath);

	// 函数 DeleteAll
	// 作用：更新或清除DeleteAll。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetItemChanged。
	void DeleteAll();

	// 函数 FindNameIndex
	// 作用：执行FindNameIndex。
	// 参数：无。
	// 返回：没有返回值。
	// 过程：函数里会调用 SetItemChanged。
	void FindNameIndex();

// Attributes
public:
	// 函数 SetItemChanged
	// 作用：设置SetItemChanged。
	// 参数：bChange：是或否。
	// 返回：没有返回值。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	void SetItemChanged(BOOL bChange) { m_bItemChanged = bChange; }
	// 函数 GetItemChanged
	// 作用：读取GetItemChanged。
	// 参数：无。
	// 返回：返回是或否。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	BOOL GetItemChanged() { return m_bItemChanged; }

protected:
	static CReagentItemManager* m_pManager;

	CPtrArray	m_arrayItems; // 项目目录下的全部项目	
	CString		m_strProjectPath; // 项目目录
	BOOL	m_bItemChanged; // 项目信息改变，需要提示保存
	int		m_iNameIndex; // 自动命名的序号
};

