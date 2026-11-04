// 【交接】 BWGenUILib\BWGenUILib.h
// 作用：BWGenUILib 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：CBWGenUILibResource。
#pragma once

#include "resource.h"

// 处理当前程序的资源，需要在使用当前程序资源时先声明一个变量
class CBWGenUILibResource  
{
public:
	// 函数 CBWGenUILibResource
	// 作用：执行CBWGenUILibResource。
	// 参数：无。
	// 返回：没有返回值。
	CBWGenUILibResource();
	// 函数 ~CBWGenUILibResource
	// 作用：析构函数。对象销毁时释放它占用的资源。
	// 参数：无。
	// 返回：没有返回值。
	virtual ~CBWGenUILibResource();

protected:
	HINSTANCE m_hInstOld;
};
