// 【交接】 PCRCtrlLib\PCRAlgorithmLib\PcrAnaSort.h
// 作用：PcrAnaSort。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：CPcrAnalysisSort、void、bubble、insertion、quick、selection、quickHT、SelectSortType。

#ifndef _SORT_H
#define _SORT_H

#include <stdlib.h>
#include <vector>

using namespace std;
enum {BUBBLE = 0, INSERTION, QUICK, SELECTION};
enum {MYLONG = 0, MYDOUBLE, MYINTERGER};

template <class T>

class AFX_EXT_CLASS CPcrAnalysisSort
{
private:
	// 函数 CPcrAnalysisSort
	// 作用：执行CPcrAnalysisSort。
	// 参数：无。
	// 返回：没有返回值。
	CPcrAnalysisSort(){}
	// 函数 void
	// 作用：执行void。
	// 参数：funpt)(T。
	// 返回：返回 typedef。
	typedef void (CPcrAnalysisSort<T>:: * funpt)(T*);
	vector<funpt> f;

public:
	// 函数 CPcrAnalysisSort
	// 作用：执行CPcrAnalysisSort。
	// 参数：int。
	// 返回：没有返回值。
	CPcrAnalysisSort(int);								// constructor
	// 函数 bubble
	// 作用：执行bubble。
	// 参数：array[]。
	// 返回：没有返回值。
	void bubble(T array[]);					// bubble sort
	// 函数 insertion
	// 作用：执行insertion。
	// 参数：array[]。
	// 返回：没有返回值。
	void insertion(T array[]);				// insertion sort
	// 函数 quick
	// 作用：执行quick。
	// 参数：array[]；int；int。
	// 返回：没有返回值。
	void quick(T array[], int, int);		// quick sort
	// 函数 selection
	// 作用：执行selection。
	// 参数：array[]。
	// 返回：没有返回值。
	void selection(T array[]);				// selectioni sort
	// 函数 quickHT
	// 作用：执行quickHT。
	// 参数：array[]。
	// 返回：没有返回值。
	void quickHT(T array[]);
	// 函数 SelectSortType
	// 作用：执行SelectSortType。
	// 参数：i；array[]。
	// 返回：返回是或否。
	// 过程：函数里会调用 quick。
	bool SelectSortType(int i, T array[]);

private:
	int size;
};

template <class T>
void CPcrAnalysisSort<T>::quickHT(T array[])
{
	// 函数 quick
	// 作用：执行quick。
	// 参数：array；0；1。
	// 返回：没有返回值。失败时返回 false。
	// 过程：逻辑写在函数体内，没有再转调其他项目函数。
	quick(array, 0, size - 1);
} 

template <class T>
bool CPcrAnalysisSort<T>::SelectSortType(int i, T array[])
{
	if(i < BUBBLE || i > SELECTION)
		return false;

	(this->*f[i])(array);
	return true;
}


template <class T>
CPcrAnalysisSort<T>::CPcrAnalysisSort(int s) {
	if (s < 0) 	return;
	size = s;				// if the size is valid, assign it 

	f.push_back(&CPcrAnalysisSort<T>::bubble);
	f.push_back(&CPcrAnalysisSort<T>::insertion);
	f.push_back(&CPcrAnalysisSort<T>::quickHT);
	f.push_back(&CPcrAnalysisSort<T>::selection);
}


template <class T>
void CPcrAnalysisSort<T>::bubble(T array[]) {
	
	T temp;
	int last = size - 1;
	bool sorted = true;

	do {
		sorted = true;
		for (int i = 0; i < last; i++) 
		{
			//	swap elements if the higher index element is 
			//	greater than the smaller index element
			if (array[i] > array[i + 1]) {	
				temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				sorted = false;
			}
		} 

		last--;
	} while (!sorted);

}


template <class T>
void CPcrAnalysisSort<T>::insertion(T array[]) {

	T cVal;		// current value being examined
	
	for (int i = 1; i < size; i++) {

		cVal = array[i];
		int n = 0;
		for (int n = i - 1; n >= 0 && cVal < array[n]; n--) {
			array[n + 1] = array[n];
		}

		array[n + 1] = cVal;

	}	// end for loop

}


template <class T>
void CPcrAnalysisSort<T>::quick(T array[], int llimit, int rlimit) {

	T temp;
	int left = llimit;
	int right = rlimit;
	int pivot = (left + right) / 2;	// find the median
	T median = array[pivot];


	do {

		while ((array[left] < median) && (left < rlimit)) {
			left++;
		}

		while ((median < array[right]) && (right > llimit)) {
			right--;
		}

		if (left <= right) {

			// swap elements
			temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			left++;
			right--;
		}

	} while (left <= right);


	if (llimit < right) {
		CPcrAnalysisSort<T>::quick(array, llimit, right);
	}


	if (left < rlimit) {
		CPcrAnalysisSort<T>::quick(array, left, rlimit);
	}

}


template <class T>
void CPcrAnalysisSort<T>::selection(T array[]) {

	T temp;
	int min;

	for (int i = 0; i < size - 1; i++) 
	{
		min = i;

		for (int n = i + 1; n < size; n++) 
		{
			if (array[n] < array[min]) 
			{
				min = n;
			}

		}
		temp = array[min];
		array[min] = array[i];
		array[i] = temp;

	}

}

#endif
