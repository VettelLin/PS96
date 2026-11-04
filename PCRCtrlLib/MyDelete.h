// 【交接】 PCRCtrlLib\MyDelete.h
// 作用：MyDelete 界面控件。负责绘制、鼠标键盘输入和外观，不保存实验结论。
// 先看这些函数：MyDeletePtr、MyMulitDeletePtr。

#pragma once

template<typename T>
void MyDeletePtr(T** pData)
{
	if((NULL != pData) && (NULL != *pData))
	{
		delete *pData;
		*pData = NULL;
	}
}

template<typename T>
void MyMulitDeletePtr(T** pData)
{
	if((NULL != pData) && (NULL != *pData))
	{
		delete [] *pData;
		*pData = NULL;
	}
}







