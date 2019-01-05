#include"HuffmanCode.h"
#include <cstdlib>
void menu();
int main()
{
	HuffmanTree<Code> ht;
	Code W[30];
	char C[100];
	char code[400];
	int num;
	char choice;
	menu();
	cin >> choice;
	while (choice != 'Q'||choice!='q') {
		switch (choice)
		{
		case 'I':
		case 'i':
			cout << "请输入编码集长度：";
			cin >> num;
			cout << "请输入各字符及对应频率(空格用#代替）：\n";
			for (int i = 0; i < num; ++i) {
				cin >> W[i].ch >> W[i].key;
				
			}
			ht.Initialization(W, num); break;
		case 'E':
		case 'e':
			cout << "请输入编码:";
			cin.getline(C, 100,'\n');
			while (!strcmp(C, "\0")) 
				cin.getline(C, 100, '\n');
			ht.EnCodeingIntoFile(C); break;
		case 'D':
		case 'd':
			cout << "请输入译码:";
			cin >> code; 
			ht.DeCoding(code); break;
		case 'P':
		case 'p':
			ht.Print(); break;
		case 'T':
		case 't':
			ht.TreePrint(); break;
		}
		menu();
		cin >> choice;
	}
	system("pause");
	return 0;
}
void menu() {
	cout << "---------Huffman编码功能表----------" << endl;
	cout << "-----I:初始化，建立Huffman树。并存入文件中:" << endl;
	cout << "-----E:编码，将结果存入文件CodeFile:"<<endl;
	cout << "-----D:译码，将结果存入文件TextFile:"<<endl;
	cout << "-----P:印代码文件:" << endl;
	cout << "-----T:直观打印Huffman树:" << endl;
	cout << "-----Q:退出:" << endl;
	cout << "请输入对应功能符号：";
}

//HuffmanCoding 实现代码
//初始化创建huffman树（数据结构理论课pdf有讲解）
template<class T>
void HuffmanTree<T>::Initialization(T w[], int n) { //给出 n 个权值w[1]～w[n], 构造Huffman树
	MinHeap<HuffmanNode<T>> hp; //使用最小堆存放森林
	HuffmanNode<T> *parent, *first, *second; 
	HuffmanNode<T> *NodeList = new HuffmanNode<T>[n];//森林
	for (int i = 0; i < n; i++) {
		NodeList[i].data = w[i]; 
		NodeList[i].leftChild = NULL; 
		NodeList[i].rightChild = NULL; 
		NodeList[i].parent = NULL; 
		hp.Insert(NodeList[i]); //插入最小堆中
	}
	for (int i = 0; i < n - 1; i++) { //n-1趟, 建Huffman树
		first = new HuffmanNode<T>;
		second = new HuffmanNode<T>;
		hp.RemoveMin (*first); //根权值最小的树
		hp.RemoveMin (*second); //根权值次小的树 
		mergeTree(first, second, parent); //合并
		hp.Insert (*parent); //重新插入堆中
		root = parent; //建立根结点 
	}

	//将Huffman树存入hfm文件中
	ofstream out("hfmTree");
	char *code;
	for (int i = 0; i < n; ++i) {
		code = EnCoding(w[i].ch);
		out << code << w[i].ch<<" ";
	}
	out.close();
}
//建树
template<class T> 
void HuffmanTree<T>::CreateTree(HuffmanNode<T>*& bt1, HuffmanNode<T>*& bt2, HuffmanNode<T> *& parent) {
	parent = new HuffmanNode<T>;
	parent->leftChild = bt1;
	parent->rightChild = bt2;
	parent->data.key = bt1->data.key + bt2->data.key;
	bt1->parent = parent;
	bt2->parent = parent;
}
//释放函数
template<class T>
void HuffmanTree<T>::deleteTree(HuffmanNode<T> *t)
{
	if (t != NULL) {
		deleteTree(t->leftChild);
		deleteTree(t->rightChild);
		delete t;
	}
}


//编码
//对单个字符进行编码
template<class T>
bool HuffmanTree<T>::EnCoding(HuffmanNode<T> *&subTree, stack<int> & Q, char ch)
{
	bool flag = false;
	if (subTree != NULL) {
		if (subTree->leftChild == NULL && subTree->rightChild == NULL)
		{
			//叶子结点时flag=false 不用压栈
			if (subTree->data.ch == ch) flag = true;
		}
		else {			
			if (flag == false) { 
				//左结点为0；将0压入栈内，直到最后一个结点为叶子结点
				Q.push(0); 
				flag=EnCoding(subTree->leftChild, Q, ch);	
			}			
			if (flag == false) {
				//右结点为1，将1压入栈内，知道最后一个结点为叶子结点
				Q.pop();//?为什么这里要弹出栈
				Q.push(1);
				flag=EnCoding(subTree->rightChild, Q, ch);
				if (flag == false) Q.pop();	//还有这里也一样？
			}
		}
	}
	return flag;
}
template<class T>
char* HuffmanTree<T>::EnCoding(char ch) {
	buildTree();
	stack<int> Q, S;	//栈Q得到的编码是倒序的，用一个栈s还原为正的
	if (EnCoding(root, Q, ch)) {
		//当为叶子结点时
		while (!Q.empty()) {
			S.push(Q.top());
			Q.pop();
		}
		static char code[50];	//编码后的字符串
		int i = 0;	//编码后字符串的长度
		while (!S.empty()) {
			if (S.top() == 1)code[i] = '1';
			else code[i] = '0';
			S.pop();
			i++;
		}
		code[i] = '\0';
		return code;
	}
	return NULL;
}
//对一个字符串进行编码并写入文件CodeFile
template<class T>
void HuffmanTree<T>::EnCodeingIntoFile(char *code) {
	ofstream out("CodeFile");
	int n = strlen(code);
	int length;//每个字符编码的长度
	char *temp;
	for (int i = 0; i < n; ++i)
	{
		if (code[i] == ' ') {//将#代替空格
			code[i] = '#';
		}
		temp = EnCoding(code[i]);
		if (temp == NULL) {
			cerr << "编码错误！" << endl; exit(1);
		}
		else {
			length = strlen(temp);
			for (int j = 0; j < length; ++j)
			{
				out << temp[j] ;			
			}
		}
	}
	out.close();

}

//译码
template<class T>
bool HuffmanTree<T>::DeCoding(HuffmanNode<T> *&subTree,char *code,int & i,ofstream & out){
	bool flag = false;
	if(subTree!=NULL){
		if (subTree->leftChild == NULL && subTree->rightChild == NULL) {
			if (subTree->data.ch == '#') out << " ";
			else out << subTree->data.ch ; flag = true;
		}
		else {
			if (code[i] != '0' && code[i] != '1'){	cerr << "输入错误！" << endl; exit(1);
		}
			if (code[i] == '0') {
				++i; flag=DeCoding(subTree->leftChild, code, i,out);
			}
			else {
					if (code[i] == '1')
					++i; flag=DeCoding(subTree->rightChild, code, i,out);				
			}
		}
		}
	return flag;
}
//对字符串进行译码并写入文件TextFile
template<class T>
void HuffmanTree<T>::DeCoding(char *code) {
	buildTree();  //判断树是否为空来建树；
	int i = 0;
	int n = strlen(code);
	ofstream out("TextFile");
	while (i < n) {
		if (!DeCoding(root, code, i, out))
		{cerr<< "树为空或编码错误！" << endl; exit(1);
	}
	}
	out.close();
}

//如果Huffman为空，则从文件里读出并建树
template<class T>
void HuffmanTree<T>::buildTree()
{
	if (root == NULL) {  //如果Huffman树不存在，则从hfmTree文件读入
		root = new HuffmanNode<T>;
		HuffmanNode<T>  *current;
		ifstream in("hfmTree");
		char code[50];
		while (in >> code,!in.eof()) {  //读取文件
			 //假设存入有刷新
			int i = 0;
			current = root;
			while (code[i] != '\0') { //读出Huffman编码字段，如110A;			
				if (code[i] == '0') {   //遍历左子树
					if (current->leftChild == NULL) current->leftChild = new HuffmanNode<E>; //建立左子树
					current->leftChild->parent = current;
					current = current->leftChild; ++i;
				}
				else {
					if (code[i] == '1') {
						if (current->rightChild == NULL) current->rightChild = new HuffmanNode<E>;//建立右子树
						current->rightChild->parent = current;
						current = current->rightChild; ++i;
					}
					else {
						current->data.ch = code[i]; ++i;
					}
				}
			}

		}
		in.close();
	}
}

//打印CodeFile文件
template<class T>
void HuffmanTree<T>::Print() {
	ifstream in("CodeFile");
	char C;
	int i = 0;
	while (in.get(C),!in.eof()) {	
		cout << C;
		if (i == 49) cout << endl;
		i = (i + 1) % 50;
	}
	cout << endl;
}

//用广义表来表示
template<class T>
void HuffmanTree<T>::TreePrint() {
	if (root == NULL)  buildTree();
	ofstream out("TreePrint");
	cout << "Huffman树的广义表表示(@表示结点无字符)：" << endl;
	TreePrint(root, out);
	cout << endl;
	out.close();

}
template<class T>
void HuffmanTree<T>::TreePrint(HuffmanNode<T> *& subTree,ofstream &out) {
	if(subTree!=NULL) {
		cout << subTree->data.ch;
		out<< subTree->data.ch;
		if (subTree->leftChild != NULL || subTree->rightChild != NULL) {
			cout << "("; out << "("; TreePrint(subTree->leftChild,out);
			cout << ","; out << ",";
			TreePrint(subTree->rightChild,out); cout << ")"; out << ")";
		}
	}


}

