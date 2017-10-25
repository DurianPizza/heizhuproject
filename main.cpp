#include "Huffman.h"

using namespace std;
int main()
{
	int a[5] = { -1, 10, 5, 20, 15 };
	int b[5] ;
	for (int i = 0; i < sizeof(b) / sizeof(int); i++)
	{
		b[i] = a[i];
	}
	BinaryTree<int> *root;
	int size = sizeof(a) / sizeof(a[0]);
	try{ root = HuffmanTree(a, size); }
	catch (char * e)
	{
		cout << e << endl;
		system("pause");
		return 1;
	}
	cout << "The structure of huffman tree is" << endl;
	for (int i = 0; i < 2*sizeof(a) / sizeof(a[0])-1; i++)
		cout << " " << root[i].element << " " << root[i].parent << " " << root[i].lchild << " " << root[i].rchild << " " << endl;
	string *code;
	code=HuffmanCode(root, sizeof(a) / sizeof(a[0]));
	cout << endl << "The huffman code is" << endl;
	for (int i = 0; i < size; i++)
	{
		cout <<"'"<< b[i] <<"'"<<":"<< code[i] << endl;
	}
	system("pause");
	return 0;
}

