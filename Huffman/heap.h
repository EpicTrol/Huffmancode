#ifndef _heap
#define _heap
#include<iostream>
using namespace std;
const int DefaultSize = 50;
template <class T> 
class PQueue {         //最小堆继承了最小优先级队列类
public:
	virtual bool Insert (const T& d) = 0;
	virtual bool RemoveMin (T& d) = 0;
};
template < class T> 
class MinHeap : public PQueue<T>
{ //最小堆继承优先级队列
public:
	MinHeap(int sz= DefaultSize); //构造函数
	MinHeap(T arr[], int n); //构造函数
	~MinHeap() { delete[]heap; } //析构函数
	bool Insert (const T& d); //插入
	bool RemoveMin (T& d); //删除
	bool IsEmpty()const //判堆空否?空返回1，否则0
	{ return  (currentSize==0)?true:false; } 
	bool IsFull()const //判堆满否？满则返回1，否则0 
	{ return (currentSize==maxHeapSize)true:false; }
	void MakeEmpty(){ currentSize= 0; } //置空堆
private:
	T *heap; //存放最小堆元素的数组
	int currentSize; //最小堆当前元素个数 
	int maxHeapSize; //最小堆最大容量
	void siftDown(int start, int m);//调整算法（从start到m下滑）
	void siftUp(int start);    //调整算法（从start到0上滑）
};
#endif