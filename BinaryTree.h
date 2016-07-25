#pragma once
#include<iostream>
#include<queue>
#include<assert.h>
#include<stack>
using namespace std;


template <typename T>
struct BinaryNode
{
	BinaryNode* _left;
	BinaryNode* _right;
	T    _data;
	BinaryNode(const T& d)
		:_data(d)
		,_left(NULL)
		,_right(NULL)
	{}
};

template<typename T>
class BinaryTree
{
	typedef BinaryNode<T>  Node;
public:
	BinaryTree()
		:root(NULL)
	{}
	BinaryTree(const T* a, size_t size, const T& invalid);
	BinaryTree(const BinaryTree<T>* t);

	BinaryTree<T>& operator=(const BinaryTree<T>* t);
	~BinaryTree()
	{
			Release(root);
	}
	//前序
	void PrevOrder()
	{
		_PrevOrder(root); 
	}
	//中序
	void InOrder()
	{
		_InOrder(root);
	}
	//后序
	void PostOrder()
	{
		_PostOrder(root);
	}
	//层序
	void LevelOrder()
	{
		_LevelOrder(root);
	}
	//非递归的前序
	void PrevOrder_NonR()
	{
		if (root != NULL)
			_PrevOrderNonR(root);
	}
		//非递归的中序
	void InOrder_NonR()
	{
		if (root != NULL)
			_InOrderNonR(root);
	}

	//非递归的后序
	void PostOrder_NonR()
	{
		if (root != NULL)
			_PostOrderNonR(root);
	}

	size_t Size()
	{
		
		return _Size(root);
	}
	size_t LeafSize()
	{
		return _LeafSize(root);
	}
	size_t Depth()
	{
		return _Depth(root);
	}
	size_t GetKLevel(size_t k)
	{
		return _GetKLevel(root,k);
	}

	Node* Find(const T& key)
	{
		Node* parent = NULL;
		_Find(root, key, parent);
		return parent;
	}

	Node* _Find(Node* root,const T& key,Node*& parent)
	{
		if (root == NULL)
		{
			return NULL;
		}
		if (root->_data == key)
			parent = root;

		_Find(root->_left, key, parent);
		_Find(root->_right, key, parent);
		return parent;
	}


	//将一个搜索二叉树转化为一个双向链表



	//求二叉树任意两个节点的最近公共祖先

	//节点结构中含有父亲节点


	//搜索二叉树
	Node* AVLParentNode(Node* root, T& key1, T& key2)
	{
		if (root == NULL)
			return NULL;

		if (root->_data > key1&&root->_data > key2)
			AVLParentNode(root->_left, key1, key2);
		
		else if (root->_data < key1&&root->_data < key2)
			AVLParentNode(root->_right, key1, key2);

		else
			return root;
	}

	//普通树
	int ParentNode(const T& n1,const T& n2,Node*& parent)
	{
		Node* node1 = Find(n1);
		Node* node2 = Find(n2);
		return _ParentNode(root, node1, node2, parent);
	}

	//int _ParentNode(Node* root, Node*& node1,Node*& node2, Node*& parent)
	//{
	//	assert(node1);
	//	assert(node2);
	//	
	//	/*if (root == NULL)
	//		return 0;*/
	//	if (root)
	//	{
	//		if (root == node1 || root == node2)
	//			return 1;

	//		int left = _ParentNode(root->_left, node1, node2, parent);
	//		if (left == 2)
	//			return 2;
	//		int right = _ParentNode(root->_right, node1, node2, parent);
	//		if (right == 2)
	//			return 2;

	//		if (left + right == 2)
	//			parent = root;

	//		return left + right;
	//	}
	//	
	//}

	//优化时间复杂度为O(N),使用链表

	int _ParentNode(Node* root, Node*& node1, Node*& node2, Node*& parent)
	{
		assert(node1);
		assert(node2);

		if (root)
		{
			int ret = root == node1 || root == node2 + _ParentNode(root->_left, node1, node2, parent) +_ParentNode(root->_right, node1, node2, parent);

			if (ret == 2)
			{
				parent = root;
				return 0;
			}
			return ret;
		}
		else
            return 0;
	}

	//求二叉树中最远两个节点的距离
	int GetLen()
	{
		if (root == NULL)
			return 0;
		int left = 0;
		int right = 0;
		if (root->_left)
		{
			left= _GetLen(root->_left);
		}
		if (root->_right)
		{
			right= _GetLen(root->_right);
		}
		/*if (root->_left == NULL || root->_right == NULL)
			return left + right + 1;
		else
			return left + right + 2;*/
		return left + right + 1;
	}
	int _GetLen(Node*& root)
	{
		if (root == NULL)
			return 0;

		int left=_GetLen(root->_left);
		int right=_GetLen(root->_right);

		return left > right ? left + 1 : right + 1;
	}
protected:
	void _BinaryTree(Node* &root, const T* arr, size_t size, const T& invalid, size_t& index);
	//void  _BinaryTreeNode(Node* &root1, const Node* &root2);
	//Node* _OPNode(const Node* &Troot);
	void _PrevOrder(Node* &root);
	void _InOrder(Node* &root);
	void _PostOrder(Node* &root);
	void _LevelOrder(Node* &root);
	size_t _Size(Node* &root);
	size_t _LeafSize(Node* &root);
    size_t _Depth(Node* &root);
    size_t _GetKLevel(Node* &root,size_t k);

	void _PrevOrderNonR(Node* root)
	{
		if (root == NULL)
			return;
		stack<Node*> Q;
		//Node* root = root;
		Q.push(root);
		while (!Q.empty())
		{
			Node* top = Q.top();
			cout << top->_data << " ";
			Q.pop();
			if (top->_right)
				Q.push(top->_right);
			if (top->_left)
				Q.push(top->_left);
		}
		cout << endl;
	}

	void _InOrderNonR(Node* root)
	{
		stack<Node*> Q;
		Node* cur = root;
		while (!Q.empty()||cur)
		{
			while (cur)//cur为了找左
			{
				Q.push(cur);
				cur = cur->_left;//指向NULL  
			}
			Node* top = Q.top();//输出左    3  2 4 1 6 5
			cout << top->_data << " ";
			Q.pop();
			if (top->_right)
			{
				cur = top->_right;// 
			}
		}
		cout << endl;
	}

	void _PostOrderNonR(Node* root)
	{
		stack<Node*> Q;
		Node* prev = NULL;
		Node* cur = root;
		while (cur || !Q.empty())
		{
			while (cur)
			{
				Q.push(cur);
				cur = cur->_left;
			}
			Node* top = Q.top();
			if (top->_right == NULL ||top->_right==prev)
			{
				cout << top->_data << " ";
				Q.pop();
				prev = top;
			}
			else
			{
				cur = top->_right;
			}
		}
	}
	
	void Release(Node* root)
	{
		if (root != NULL)
		{
			Release(root->_left);
			Release(root->_right);
			delete root;
		}
	}
private:
	Node*  root;//节点指针
};

//构造函数
template<typename T>
void BinaryTree<T>::_BinaryTree(Node* &root, const T* arr, size_t size, const T& invalid, size_t& index)
{
	if (index >= size || arr[index] == invalid)
	{
		return;
	}
	root = new Node(arr[index]);//前序构建二叉树
	_BinaryTree(root->_left, arr, size, invalid, ++index);
	_BinaryTree(root->_right, arr, size, invalid, ++index);  
}


template <typename T>
BinaryTree<T>::BinaryTree(const T* a, size_t size, const T& invalid)
:root(NULL)
{
	if (a == NULL)
	{
		return;
	}
	size_t index=0;
    _BinaryTree(root, a, size, invalid, index);
}


//拷贝构造函数
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>* t)
:root(NULL)
{
	if (t.root == NULL)
	{
		return;
	}
	root = new Node(t.root->_data);
	if(t.root->_left != NULL)
	{
		_left = new BinaryTree(t.root->_left);

	}
	if(t.root->_right != NULL)
	{
		_right = new BinaryTree(t.root->_right);
	}
}

//template<typename T>
//void BinaryTree<T>::_BinaryTreeNode(Node* &root1, const Node* &root2)
//{
//	if (root2 = NULL)
//		return;
//	root1 = new Node(root2->_data);
//	_BinaryTreeNode(root1->_left,root2->_left);
//	_BinaryTreeNode(root1->_right,root2->_right);
//}

//赋值运算符重载
template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>* t)
{
	if (t.root == NULL)
		return;
	root = new Node(t->root->_data);
	if (t->root->_left != NULL)
	{
		_left = new operator=(t->root->_left);
	}
	if (t->root->_right != NULL)
	{
		_right = new operator=(t->root->_right);
	}
}

//template <typename T>
//Node<T>* BinaryNode<T>::_OPNode(const Node* &Troot)
//{
//	Node<T>* root = new Node(Troot->_data);
//	if (Troot->_left != NULL)
//	{
//		root->_left = new  _operator(Troot->_left);
//	}
//	if (Troot->_right != NULL)
//	{
//		root->_right = new  _operator(Troot->_right);
//	}
//	return root;
//}

template <typename T>
void BinaryTree<T>::_PrevOrder(Node* &root)
{
	if (root == NULL)
	{
		return;
	}
	cout << root->_data << " ";
	_PrevOrder(root->_left);
	_PrevOrder(root->_right);
}

template <typename T>
void BinaryTree<T>::_InOrder(Node* &root)
{
	if (root == NULL)
		return;
	_InOrder(root->_left);
	cout << root->_data << " ";
	_InOrder(root->_right);
}

template <typename T>
void BinaryTree<T>::_PostOrder(Node* &root)
{
	if (root == NULL)
	{
		return;
	}
	_PostOrder(root->_left);
	_PostOrder(root->_right);
	cout << root->_data << " ";
}


template <typename T>
void BinaryTree<T>::_LevelOrder(Node* &root)
{
	if (root == NULL)
		return;
	queue<Node*> Q;
	Node* p = root;
	Q.push(p);
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		cout << p->_data << " ";
		if (p->_left)
		{
			Q.push(p->_left);
		}
		if (p->_right)
		{
			Q.push(p->_right);
		}
	}
}

template <typename T>
size_t BinaryTree<T>::_Size(Node* &root)
{
	if (root == NULL)
		return 0;
	return _Size(root->_left) + _Size(root->_right)+1;
}

template <typename T>
size_t BinaryTree<T>::_LeafSize(Node* &root)
{
	static size_t count = 0;
	if (root == NULL)
		return 0;
	if (root->_left == NULL&&root->_right == NULL)
	{
		count++;
    }
	_LeafSize(root->_left);
	_LeafSize(root->_right);
	return count;
}

template <typename T>
size_t BinaryTree<T>::_Depth(Node* &root)
{
	static size_t count = 0;
	if (root == NULL)
		return 0;
	size_t left = _Depth(root->_left);
	size_t right = _Depth(root->_right);
	return left > right ? left + 1 : right + 1;
}

template <typename T>
size_t BinaryTree<T>::_GetKLevel(Node* &root,size_t k)
{
	if (root == NULL)
		return 0;
	if ( 0 >= k > _Depth(root))
	{
		return 0;
	}
	if (k == 1)
		return 1;
	size_t left = _GetKLevel(root->_left, k - 1);
	size_t right = _GetKLevel(root->_right, k - 1);     
	return left + right;
}

void Test()
{
	int arr[10] = { 1, 2, 3, '#', '#', 4, '#', 7, 5, 6 };
	int arr2[15] = { 1, 2, 3, '#', '#', 4, '#', 5, '#', '#', 6, 7, '#', '#', 8 };
	BinaryTree<int> b2(arr, 10, '#');
	cout<<b2.GetLen();
	/*BinaryNode<int>* parent=NULL;

	int ret=b2.ParentNode(4,7,parent);
	if (parent)
	{
		cout << parent->_data;
	}
	else
		cout << "Not Find Node" << endl;*/
	//	BinaryTree<int> b1(arr, 10, '#');
	////BinaryTree<int> b2(b1);
	////BinaryTree<int> b3;
	////b3 = b1;
	//b1.PrevOrder();
	//cout<< endl;
	//b1.InOrder();
	//cout<< endl;
	//b1.PostOrder();
	//cout<< endl;
	//b1.LevelOrder();
	//cout<< endl;
	//cout << b1.Size();
	//cout << endl;
	//cout<<b1.LeafSize();
	//cout << endl;
	//cout<<b1.Depth();
	//cout << endl;
	//cout << b1.GetKLevel(1) << endl;
	//cout << b1.GetKLevel(2) << endl;
	//cout << b1.GetKLevel(3) << endl;
	//b1.PrevOrder_NonR();
	//b1.InOrder_NonR();
	//b1.PostOrder_NonR();
	//b2.InOrderThreading();
	//b2.PrevOrderThreading();
	//b2.PrevOrderThd();
	//b2.InOrderThreading();
	//b2.InOrderThd();
	//b2.PostOrderThreading();
}
