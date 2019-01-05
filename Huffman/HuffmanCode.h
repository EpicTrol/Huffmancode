#ifndef _HuffmanCode
#define _HuffmanCode
#include<cstdio>
#include<iostream>
#include<stack>
#include<string>
#include<fstream>
#include "heap.h"  
using namespace std;

//哈夫曼编码的字符类型
struct Code {
	char ch;	//字符
	double key;	//权值
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

//哈夫曼树的结点定义（课本源代码）
template <class T> 
struct HuffmanNode { //树结点的类定义
	T data; //结点数据
	HuffmanNode<T> *parent;
	HuffmanNode<T> *leftChild,*rightChild; //左、右子女和父结点指针
	HuffmanNode():parent(NULL), leftChild(NULL), rightChild(NULL) { } //构造函数
	HuffmanNode(T elem, HuffmanNode< T> *pr = NULL, HuffmanNode<T> *left = NULL, HuffmanNode< T> *right = NULL) : data (elem), parent (pr),leftChild (left), rightChild (right) { }
	friend bool operator>(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data > r2.data; }
	friend bool operator>=(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data >= r2.data; }
	friend bool operator<(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data < r2.data; }
	friend bool operator<=(const HuffmanNode<T> &r1, const HuffmanNode<T> &r2) { return r1.data <= r2.data; }
};
//Huffman树类定义（课本源代码）
template<class T>
class HuffmanTree{ 
public:
	HuffmanTree() { root = NULL; }
	void Initialization(T w[], int n); //构造函数
	~HuffmanTree(){ deleteTree(root); }  //析构函数
	char* EnCoding(char ch);
	void EnCodeingIntoFile(char *code);
	void DeCoding(char *code);
	void Print();	//打印CodeFile文件
	void TreePrint();//用广义表来表示哈夫曼树
protected:
	HuffmanNode<T> *root; //树的根
	void deleteTree (HuffmanNode<T> *t); //删除以t为根的子树 
	void CreateTree(HuffmanNode<T>*& bt1, HuffmanNode<T>*& bt2, HuffmanNode<T> *& parent);
	bool EnCoding(HuffmanNode<T> *&subTree, stack<int> & Q, char ch);
	bool DeCoding(HuffmanNode<T> *&subTree, char* code, int &i,ofstream & out);
	void buildTree();	//如果Huffman为空，则从文件里读出并建树
	void TreePrint(HuffmanNode<T> *&subTree,ofstream &out);
};
#endif