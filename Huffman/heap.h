#ifndef _heap
#define _heap
#include<iostream>
using namespace std;
const int DefaultSize = 50;
template <class T> 
class PQueue {         //��С�Ѽ̳�����С���ȼ�������
public:
	virtual bool Insert (const T& d) = 0;
	virtual bool RemoveMin (T& d) = 0;
};
template < class T> 
class MinHeap : public PQueue<T>
{ //��С�Ѽ̳����ȼ�����
public:
	MinHeap(int sz= DefaultSize); //���캯��
	MinHeap(T arr[], int n); //���캯��
	~MinHeap() { delete[]heap; } //��������
	bool Insert (const T& d); //����
	bool RemoveMin (T& d); //ɾ��
	bool IsEmpty()const //�жѿշ�?�շ���1������0
	{ return  (currentSize==0)?true:false; } 
	bool IsFull()const //�ж��������򷵻�1������0 
	{ return (currentSize==maxHeapSize)true:false; }
	void MakeEmpty(){ currentSize= 0; } //�ÿն�
private:
	T *heap; //�����С��Ԫ�ص�����
	int currentSize; //��С�ѵ�ǰԪ�ظ��� 
	int maxHeapSize; //��С���������
	void siftDown(int start, int m);//�����㷨����start��m�»���
	void siftUp(int start);    //�����㷨����start��0�ϻ���
};
#endif