#include<iostream>
#include<queue>
#include<string>
#include<stack>

using namespace std;
template<class T>
//二叉树的数组表示
struct BinaryTree
{
	T element;
	int parent, lchild, rchild;
	bool occupy=true;
};

template<class T>
BinaryTree<T>* HuffmanTree(T* vector,int lenght)
{
	int size = 2 * lenght - 1;
	BinaryTree<T> *root = new BinaryTree<T>[size];
	int min1, min2;
	for (int i = size - lenght; i < size; i++)
	{
		if (vector[i + lenght - size] <= 0)
			throw "All parameters should be >0";
		root[i].element = vector[i + lenght - size];		
		root[i].lchild = -1;
		root[i].rchild = -1;
	}
	//对数组进行排序
	T a = 0;
	for (int i = 0; i < lenght; i++)
	{
		for (int j = 1; j < lenght - i; j++)
		{
			if (vector[j-1]>vector[j])
			{
				a = vector[j-1];
				vector[j-1] = vector[j];
				vector[j] = a;
			}
		}
	}
	for (int i = size - lenght-1; i >=0; i--)
	{
		T weight=select(root,vector, lenght, min1, min2);
		root[i].element = weight;
		root[i].lchild = min1;
		root[i].rchild = min2;
		root[min1].parent = i;
		root[min2].parent = i;
	}
	root[0].parent = -1;
	return root;
}

template<class T>
T select(BinaryTree<T>* root,T* vector, int lenght, int &min1, int &min2)
{
	//选择最小的两个节点
	int size = 2 * lenght - 1;
	for (int i = 0; i < size; i++)
	{
		if (root[i].element == vector[0] && root[i].occupy)
		{
			min1 = i;
			root[i].occupy = false;
			break;
		}
	}
	for (int i = 0; i < size; i++)
	{
		if (root[i].element == vector[1] && root[i].occupy)
		{
			min2 = i;
			root[i].occupy = false;
			break;
		}
	}
	T sum = vector[0] + vector[1];
	vector[0] = -1;
	vector[1] = -1;
	queue<T> q;
	for (int i = 0; i < lenght; i++)
	{
		if (vector[i] != -1)
		{
			q.push(vector[i]);
			vector[i] = -1;
		}
	}
	int i = 0;
	size = q.size();
	for (i = 0; i < size; i++)
	{
		if (q.front() <= sum)
		{
			vector[i] = q.front();
			q.pop();
		}
		else
		{
			vector[i] = sum;
			break;
		}			
	}
	if (i == size)
	{
		vector[i] = sum;
	}
	else
	{
		while (!q.empty())
		{
			vector[++i] = q.front();
			q.pop();
		}
	}
	return sum;
}

template<class T>
string *HuffmanCode(BinaryTree<T>* root, int lenght)
{
	string *code = new string[lenght];
	int size = lenght * 2 - 1;
	stack<char> q;
	for (int i = lenght - 1; i < size; i++)
	{
		int j = i;
		while (root[j].parent != -1)
		{
			if (root[root[j].parent].lchild == j)q.push('0'); 
			else if(root[root[j].parent].rchild == j)q.push('1');
			j = root[j].parent;
		}
		while (!q.empty())
		{
			code[i-lenght+1].push_back(q.top());
			q.pop();
		}
	}
	return code;
}