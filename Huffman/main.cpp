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
			cout << "��������뼯���ȣ�";
			cin >> num;
			cout << "��������ַ�����ӦƵ��(�ո���#���棩��\n";
			for (int i = 0; i < num; ++i) {
				cin >> W[i].ch >> W[i].key;
				
			}
			ht.Initialization(W, num); break;
		case 'E':
		case 'e':
			cout << "���������:";
			cin.getline(C, 100,'\n');
			while (!strcmp(C, "\0")) 
				cin.getline(C, 100, '\n');
			ht.EnCodeingIntoFile(C); break;
		case 'D':
		case 'd':
			cout << "����������:";
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
	cout << "---------Huffman���빦�ܱ�----------" << endl;
	cout << "-----I:��ʼ��������Huffman�����������ļ���:" << endl;
	cout << "-----E:���룬����������ļ�CodeFile:"<<endl;
	cout << "-----D:���룬����������ļ�TextFile:"<<endl;
	cout << "-----P:ӡ�����ļ�:" << endl;
	cout << "-----T:ֱ�۴�ӡHuffman��:" << endl;
	cout << "-----Q:�˳�:" << endl;
	cout << "�������Ӧ���ܷ��ţ�";
}

//HuffmanCoding ʵ�ִ���
//��ʼ������huffman�������ݽṹ���ۿ�pdf�н��⣩
template<class T>
void HuffmanTree<T>::Initialization(T w[], int n) { //���� n ��Ȩֵw[1]��w[n], ����Huffman��
	MinHeap<HuffmanNode<T>> hp; //ʹ����С�Ѵ��ɭ��
	HuffmanNode<T> *parent, *first, *second; 
	HuffmanNode<T> *NodeList = new HuffmanNode<T>[n];//ɭ��
	for (int i = 0; i < n; i++) {
		NodeList[i].data = w[i]; 
		NodeList[i].leftChild = NULL; 
		NodeList[i].rightChild = NULL; 
		NodeList[i].parent = NULL; 
		hp.Insert(NodeList[i]); //������С����
	}
	for (int i = 0; i < n - 1; i++) { //n-1��, ��Huffman��
		first = new HuffmanNode<T>;
		second = new HuffmanNode<T>;
		hp.RemoveMin (*first); //��Ȩֵ��С����
		hp.RemoveMin (*second); //��Ȩֵ��С���� 
		mergeTree(first, second, parent); //�ϲ�
		hp.Insert (*parent); //���²������
		root = parent; //��������� 
	}

	//��Huffman������hfm�ļ���
	ofstream out("hfmTree");
	char *code;
	for (int i = 0; i < n; ++i) {
		code = EnCoding(w[i].ch);
		out << code << w[i].ch<<" ";
	}
	out.close();
}
//����
template<class T> 
void HuffmanTree<T>::CreateTree(HuffmanNode<T>*& bt1, HuffmanNode<T>*& bt2, HuffmanNode<T> *& parent) {
	parent = new HuffmanNode<T>;
	parent->leftChild = bt1;
	parent->rightChild = bt2;
	parent->data.key = bt1->data.key + bt2->data.key;
	bt1->parent = parent;
	bt2->parent = parent;
}
//�ͷź���
template<class T>
void HuffmanTree<T>::deleteTree(HuffmanNode<T> *t)
{
	if (t != NULL) {
		deleteTree(t->leftChild);
		deleteTree(t->rightChild);
		delete t;
	}
}


//����
//�Ե����ַ����б���
template<class T>
bool HuffmanTree<T>::EnCoding(HuffmanNode<T> *&subTree, stack<int> & Q, char ch)
{
	bool flag = false;
	if (subTree != NULL) {
		if (subTree->leftChild == NULL && subTree->rightChild == NULL)
		{
			//Ҷ�ӽ��ʱflag=false ����ѹջ
			if (subTree->data.ch == ch) flag = true;
		}
		else {			
			if (flag == false) { 
				//����Ϊ0����0ѹ��ջ�ڣ�ֱ�����һ�����ΪҶ�ӽ��
				Q.push(0); 
				flag=EnCoding(subTree->leftChild, Q, ch);	
			}			
			if (flag == false) {
				//�ҽ��Ϊ1����1ѹ��ջ�ڣ�֪�����һ�����ΪҶ�ӽ��
				Q.pop();//?Ϊʲô����Ҫ����ջ
				Q.push(1);
				flag=EnCoding(subTree->rightChild, Q, ch);
				if (flag == false) Q.pop();	//��������Ҳһ����
			}
		}
	}
	return flag;
}
template<class T>
char* HuffmanTree<T>::EnCoding(char ch) {
	buildTree();
	stack<int> Q, S;	//ջQ�õ��ı����ǵ���ģ���һ��ջs��ԭΪ����
	if (EnCoding(root, Q, ch)) {
		//��ΪҶ�ӽ��ʱ
		while (!Q.empty()) {
			S.push(Q.top());
			Q.pop();
		}
		static char code[50];	//�������ַ���
		int i = 0;	//������ַ����ĳ���
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
//��һ���ַ������б��벢д���ļ�CodeFile
template<class T>
void HuffmanTree<T>::EnCodeingIntoFile(char *code) {
	ofstream out("CodeFile");
	int n = strlen(code);
	int length;//ÿ���ַ�����ĳ���
	char *temp;
	for (int i = 0; i < n; ++i)
	{
		if (code[i] == ' ') {//��#����ո�
			code[i] = '#';
		}
		temp = EnCoding(code[i]);
		if (temp == NULL) {
			cerr << "�������" << endl; exit(1);
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

//����
template<class T>
bool HuffmanTree<T>::DeCoding(HuffmanNode<T> *&subTree,char *code,int & i,ofstream & out){
	bool flag = false;
	if(subTree!=NULL){
		if (subTree->leftChild == NULL && subTree->rightChild == NULL) {
			if (subTree->data.ch == '#') out << " ";
			else out << subTree->data.ch ; flag = true;
		}
		else {
			if (code[i] != '0' && code[i] != '1'){	cerr << "�������" << endl; exit(1);
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
//���ַ����������벢д���ļ�TextFile
template<class T>
void HuffmanTree<T>::DeCoding(char *code) {
	buildTree();  //�ж����Ƿ�Ϊ����������
	int i = 0;
	int n = strlen(code);
	ofstream out("TextFile");
	while (i < n) {
		if (!DeCoding(root, code, i, out))
		{cerr<< "��Ϊ�ջ�������" << endl; exit(1);
	}
	}
	out.close();
}

//���HuffmanΪ�գ�����ļ������������
template<class T>
void HuffmanTree<T>::buildTree()
{
	if (root == NULL) {  //���Huffman�������ڣ����hfmTree�ļ�����
		root = new HuffmanNode<T>;
		HuffmanNode<T>  *current;
		ifstream in("hfmTree");
		char code[50];
		while (in >> code,!in.eof()) {  //��ȡ�ļ�
			 //���������ˢ��
			int i = 0;
			current = root;
			while (code[i] != '\0') { //����Huffman�����ֶΣ���110A;			
				if (code[i] == '0') {   //����������
					if (current->leftChild == NULL) current->leftChild = new HuffmanNode<E>; //����������
					current->leftChild->parent = current;
					current = current->leftChild; ++i;
				}
				else {
					if (code[i] == '1') {
						if (current->rightChild == NULL) current->rightChild = new HuffmanNode<E>;//����������
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

//��ӡCodeFile�ļ�
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

//�ù��������ʾ
template<class T>
void HuffmanTree<T>::TreePrint() {
	if (root == NULL)  buildTree();
	ofstream out("TreePrint");
	cout << "Huffman���Ĺ�����ʾ(@��ʾ������ַ�)��" << endl;
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

