//heap.h_��С�ѵ���ʵ��
//ʵ�ִ��루�α�Դ���룩
#include"heap.h"
template <class T>
MinHeap<T>::MinHeap(int sz) {
	maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new T[maxHeapSize];  //�����ѿռ�
	if (heap == NULL) { cerr << "�Ѵ洢����ʧ�ܣ�" << endl;  exit(1); }
	currentSize = 0; //������ǰ��С 
}

template <class T>
MinHeap<T>::MinHeap(T arr[], int n) {
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new T[maxHeapSize];
	if (heap == NULL) { cerr << "�Ѵ洢����ʧ�ܣ�" << endl;  exit(1); }
	for (int i = 0; i < n; i++)
		heap[i] = arr[i];
	currentSize = n; //���ƶ�����, ������ǰ��С 
					 //����������Ԫ�أ�ʹ��������ѵ�Ҫ�� 
	int currentPos = (currentSize - 2) / 2;
	//���������λ��:����֧��� 
	//currentPos�����ľ����ӽ��Ľ��
	while (currentPos >= 0) { //�����������
		siftDown(currentPos, currentSize - 1); //�ֲ����������»�����
		currentPos--;
	}
}

template <class T>
void MinHeap<T>::siftDown(int start, int m) { //���ܣ�ʹ����startΪ������������ѵ�Ҫ��
		//ǰ�������������Ѿ�����ѵ�Ҫ���ˡ� 
		//m�����Ľ���±� 
	int i = start, j = 2 * i + 1;  //j��i������Ůλ��
	T temp = heap[i]; //temp��������heap[i]�ĳ�ʼֵ
	while (j <= m) { //����Ƿ����λ��
					 //j��i�����ӽ��
		if (j < m&& heap[j]> heap[j + 1]) j++; //jָ��i��������Ů�е�С�� 
		if (temp <= heap[j])break; //С��������
		else { heap[i] = heap[j];  i = j; j = 2 * j + 1; } //����С������, i, j�½� 
	}
	heap[i] = temp; //�ط�temp���ݴ��Ԫ��
}
template < class T>
bool MinHeap<T>::Insert(const T& x) { //��������: ��x���뵽��С����
	if (currentSize == maxHeapSize) //���� 
	{
		cerr << "Heap Full" << endl;
		return false;
	}
	heap[currentSize] = x;  //����
	siftUp(currentSize); //���ϵ��� 
	currentSize++; //�Ѽ�����1 
	return true;
}
template<class T>
void MinHeap<T>::siftUp(int start) {
	//�ѽ��start�����ϸ���
	//ǰ�᣺����start�������㶼���ڸ����
	int j = start, i = (j - 1) / 2;
	T temp = heap[j];
	while (j > 0) { //i��j�ĸ���㣻
		if (heap[i] <= temp)
			break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		} //i��Ȼ�Ǹ���㣻
		  //��j֮�⣬����Ľ�㶼���ڸ���㣻
	}
	heap[j] = temp; //����
}
template <class T>
bool MinHeap<T>::RemoveMin(T& x) {
	if (!currentSize) { //�ѿ�, ����false
		cout << "Heap empty" << endl;
		return false;
	}
	x = heap[0];  //ɾ����С��Ԫ�� 
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);    //�������µ���Ϊ�� 
	return true; //������СԪ�� 
}