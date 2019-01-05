//heap.h_最小堆的类实现
//实现代码（课本源代码）
#include"heap.h"
template <class T>
MinHeap<T>::MinHeap(int sz) {
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new T[maxHeapSize];  //创建堆空间
	if (heap == NULL) { cerr << "堆存储分配失败！" << endl;  exit(1); }
	currentSize = 0; //建立当前大小 
}

template <class T>
MinHeap<T>::MinHeap(T arr[], int n) {
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new T[maxHeapSize];
	if (heap == NULL) { cerr << "堆存储分配失败！" << endl;  exit(1); }
	for (int i = 0; i < n; i++)
		heap[i] = arr[i];
	currentSize = n; //复制堆数组, 建立当前大小 
					 //接下来调整元素，使他们满足堆的要求； 
	int currentPos = (currentSize - 2) / 2;
	//找最初调整位置:最后分支结点 
	//currentPos是最大的具有子结点的结点
	while (currentPos >= 0) { //逐步向上扩大堆
		siftDown(currentPos, currentSize - 1); //局部自上向下下滑调整
		currentPos--;
	}
}

template <class T>
void MinHeap<T>::siftDown(int start, int m) { //功能：使得以start为根的子树满足堆的要求；
		//前提是它的子树已经满足堆的要求了。 
		//m是最大的结点下标 
	int i = start, j = 2 * i + 1;  //j是i的左子女位置
	T temp = heap[i]; //temp里面存放了heap[i]的初始值
	while (j <= m) { //检查是否到最后位置
					 //j是i的左子结点
		if (j < m&& heap[j]> heap[j + 1]) j++; //j指向i的两个子女中的小者 
		if (temp <= heap[j])break; //小则不做调整
		else { heap[i] = heap[j];  i = j; j = 2 * j + 1; } //否则小者上移, i, j下降 
	}
	heap[i] = temp; //回放temp中暂存的元素
}
template < class T>
bool MinHeap<T>::Insert(const T& x) { //公共函数: 将x插入到最小堆中
	if (currentSize == maxHeapSize) //堆满 
	{
		cerr << "Heap Full" << endl;
		return false;
	}
	heap[currentSize] = x;  //插入
	siftUp(currentSize); //向上调整 
	currentSize++; //堆计数加1 
	return true;
}
template<class T>
void MinHeap<T>::siftUp(int start) {
	//把结点start不断上浮；
	//前提：除了start，其余结点都大于父结点
	int j = start, i = (j - 1) / 2;
	T temp = heap[j];
	while (j > 0) { //i是j的父结点；
		if (heap[i] <= temp)
			break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		} //i仍然是父结点；
		  //除j之外，其余的结点都大于父结点；
	}
	heap[j] = temp; //回送
}
template <class T>
bool MinHeap<T>::RemoveMin(T& x) {
	if (!currentSize) { //堆空, 返回false
		cout << "Heap empty" << endl;
		return false;
	}
	x = heap[0];  //删除最小的元素 
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);    //自上向下调整为堆 
	return true; //返回最小元素 
}