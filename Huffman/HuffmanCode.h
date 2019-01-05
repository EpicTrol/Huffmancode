#ifndef _HuffmanCode
#define _HuffmanCode
#include<cstdio>
#include<iostream>
#include<stack>
#include<string>
#include<fstream>
#include "heap.h"  
using namespace std;

//������������ַ�����
struct Code {
	char ch;	//�ַ�
	double key;	//Ȩֵ
	Code(char l = '#',double k = 0 ) { ch = l; key = k; }
	Code &operator=(const Code &right) { key = right.key; ch = right.ch; return *this; }
	friend bool operator>(const Code &r1, const Code &r2) { 
		if(r1.key!=r2.key)return r1.key > r2.key;
		else  return r1.ch > r2.ch;
	}
	friend bool operator>=(const Code &r1, const Code &r2) {
		if (r1.key != r2.key)return r1.key >= r2.key;
		else  return r1.ch >= r2.ch;
	}
	friend bool operator<(const Code &r1, const Code &r2) {
		if (r1.key != r2.key)return r1.key < r2.key;
		else  return r1.ch < r2.ch;
	}
	friend bool operator<=(const Code &r1, const Code &r2) {
		if (r1.key != r2.key)return r1.key <= r2.key;
		else  return r1.ch <= r2.ch;
	}
};

//���������Ľ�㶨�壨�α�Դ���룩
template <class T> 
struct HuffmanNode { //�������ඨ��
	T data; //�������
	HuffmanNode<T> *parent;
	HuffmanNode<T> *leftChild,*rightChild; //������Ů�͸����ָ��
	HuffmanNode():parent(NULL), leftChild(NULL), rightChild(NULL) { } //���캯��
	HuffmanNode(T elem, HuffmanNode< T> *pr = NULL, HuffmanNode<T> *left = NULL, HuffmanNode< T> *right = NULL) : data (elem), parent (pr),leftChild (left), rightChild (right) { }
	friend bool operator>(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data > r2.data; }
	friend bool operator>=(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data >= r2.data; }
	friend bool operator<(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data < r2.data; }
	friend bool operator<=(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data <= r2.data; }
};
//Huffman���ඨ�壨�α�Դ���룩
template<class T>
class HuffmanTree{ 
public:
	HuffmanTree() { root = NULL; }
	void Initialization(T w[], int n); //���캯��
	~HuffmanTree(){ deleteTree(root); }  //��������
	char* EnCoding(char ch);
	void EnCodeingIntoFile(char *code);
	void DeCoding(char *code);
	void Print();	//��ӡCodeFile�ļ�
	void TreePrint();//�ù��������ʾ��������
protected:
	HuffmanNode<T> *root; //���ĸ�
	void deleteTree (HuffmanNode<T> *t); //ɾ����tΪ�������� 
	void CreateTree(HuffmanNode<T>*& bt1, HuffmanNode<T>*& bt2, HuffmanNode<T> *& parent);
	bool EnCoding(HuffmanNode<T> *&subTree, stack<int> & Q, char ch);
	bool DeCoding(HuffmanNode<T> *&subTree, char* code, int &i,ofstream & out);
	void buildTree();	//���HuffmanΪ�գ�����ļ������������
	void TreePrint(HuffmanNode<T> *&subTree,ofstream &out);
};
#endif