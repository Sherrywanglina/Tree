#pragma once
#include<iostream>
using namespace std;

template <typename K,typename V>
struct BSTreeNode
{
	K  _key;
	V  _value;
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>*  _right;
	BSTreeNode(const K key, const V value)
		: _left(NULL)
		, _right(NULL)
		, _key(key)
		, _value(value)
		
	{}
};

//二分搜索树
template <typename K,typename V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}

	void InOrder()
	{
		_InOrder(_root);
	}

	void _InOrder(Node* root)
	{
		if (root == NULL)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_key << "," << root->_value << endl;
		_InOrder(root->_right);

	}

	bool Insert(const K& key, const V& value)
	{
		Node* newNode = new Node(key, value);
		if (_root == NULL)
		{
			_root = newNode;
			return true;
		}
		Node* parent = NULL;
		Node* root = _root;
		while (root)
		{
			parent = root;
			if (root->_key > key)
				root = root->_left;
			else if (root->_key < key)
				root = root->_right;
			else
				return false;
		}
		if (parent->_key>key)
		{
			parent->_left = newNode;
		}
		else
		{
			parent->_right = newNode;
		}
		return true;
	}

	bool Insert_R(const K& key, const V& value)
	{
		return _Insert_R(_root, key, value);
	}

	bool _Insert_R(Node*& root, const K& key, const V& value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}

		else
		{
			if (root->_key > key)
				_Insert_R(root->_left, key, value);
			if (root->_key < key)
				_Insert_R(root->_right, key, value);
		}
		return false;
	}

	Node* Find(const K& key)
	{
		if (_root == NULL)
			return NULL;
		Node* FNode = _root;
		while (FNode)
		{
			if (FNode->_key > key)
			{
				FNode = FNode->_left;
			}
			else if (FNode->_key < key)
			{
				FNode = FNode->_right;
			}
			else
			{
				return FNode;
			}
		}
		return NULL;
	}

	Node* Find_R(const K& key)
	{
		return _Find_R(_root, key);
	}

	Node* _Find_R(Node* root, const K& key)
	{
		if (root == NULL)
			return NULL;

		if (root->_key > key)
			_Find_R(root->_left, key);
		else if (root->_key < key)
			_Find_R(root->_right, key);
		else
			return root;
	}

	bool Remove(const K& key)
	{
		if (_root == NULL)
			return false;
		Node* parent = NULL;
		Node* root = _root;
		while (root)
		{
			if (root->_key < key)
			{
				parent = root;
				root = root->_right;
			}
			else if (root->_key> key)
			{
				parent = root;
				root = root->_left;
			}
			else if (root->_key == key)
			{
				if (root->_left == NULL)
				{
					if (parent->_right == root)
					{
						parent->_right = root->_right;
						delete root;
					}
					else if (parent->_left == root)
					{
						parent->_left = root->_right;
						delete root;
					}
				}
				else if (root->_right == NULL)
				{
					if (parent->_left == root)
					{
						parent->_left = root->_left;
						delete root;
					}
					else if (parent->_right == root)
					{
						parent->_right = root->_left;
						delete root;
					}
				}
				else if (root->_left != NULL&&root->_right != NULL)
				{
					Node* delNode = root->_right;

					if (delNode->_left == NULL)
					{
						root->_key = delNode->_key;
						root->_value = delNode->_value;
						root->_right = delNode->_right;
						delete delNode;
						delNode = NULL;
					}
					else
					{
						Node* delparent = NULL;
						while (delNode->_left)
						{
							delparent = delNode;
							delNode = delNode->_left;
						}
						root->_key = delNode->_key;
						root->_value = delNode->_value;
						delete delNode;
						delNode = NULL;
						delparent->_left = NULL;

					}
				}
				return true;
			}
		}
		return false;
	}

	bool Remove_R(const K& key)
	{
		return _Remove_R(_root, key);
	}

	bool  _Remove_R(Node*& root, const K& key)
	{
		if (root == NULL)
			return false;

		if (root->_left == NULL&&root->_right == NULL)
		{
			if (root->_key == key)
			{
				delete root;
				root = NULL;
				return true;
			}
			else
			{
				return false;
			}
		}
		if (root->_key > key)
			_Remove_R(root->_left, key);

		else if (root->_key < key)
			_Remove_R(root->_right, key);

		else
		{
			Node* del = NULL;
			if (root->_left == NULL)
			{
				del = root;
				root = root->_right;
				delete del;
				del = NULL;
			}
			else if (root->_right == NULL)
			{
				del = root;
				root = root->_left;
				delete del;
				del = NULL;
			}
			else
			{
				Node* right = root->_right;
				Node* temp = right;
				while (right->_left)
				{
					temp = right;
					right = right->_left;
				}
				root->_key = right->_key;
				root->_value = right->_value;
				del = right;
				if (temp == right)
				{
					root->_right = right->_right;
				}
				delete del;
				temp->_left = NULL;
				del = NULL;
			}
			return true;
		}
		return false;
	}


	bool IsbalanceTree()
	{
		return _IsbalanceTree(_root);
	}
   //时间复杂度为O(N2)
	bool _IsbalanceTree(Node* root)
	{
		if (root == NULL)
			return true;
		int Left = Height(root->_left);
		int Right = Height(root->_right);
		if (abs(Left- Right)<2)
		{
			return true;
		}
		_IsbalanceTree(root->_left);
		_IsbalanceTree(root->_right);
		return false;
	}
	//优化，时间复杂度为O(N)
	bool IsbalanceTree_R()
	{
		int height = 0;
		return _IsBalanceTree_R(_root, height);
	}
	bool _IsBalanceTree_R(Node* root,int& height)
	{
		if (root == NULL)
		{
			height = 0;
			return true;
		}
		int heightleft=0, heightright=0;

		if (_IsBalanceTree_R(root->_left, heightleft) == false)
			return false;
		if (_IsBalanceTree_R(root->_right, heightright) == false)
			return false;
		//求高度
		height = heightleft > heightright ? heightleft + 1 : heightright + 1;

		return abs(heightleft - heightright) < 2;
	}
	
	Node* ToMirror()
	{
		return _ToMirror(_root);
	}

	Node* _ToMirror(Node* root)
	{
		if (!root)
		return NULL;

		swap(root->_left, root->_right);
		if (root->_left)
			_ToMirror(root->_left);
		if (root->_right)
			_ToMirror(root->_right);
		return root;
	}

protected:
	Node* _root;

	int Height(Node* root)
	{
		if (root == NULL)
			return 0;

		int Left = Height(root->_left);
		int Right = Height(root->_right);
		return Left > Right ? Left + 1 : Right + 1;
	}
};
void  Test()
{
	BSTree<int, int> b1;
	int a[10] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	int a1[9] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (int i = 0; i < 10; ++i)
	{
		//b1.Insert(a[i], i);
		b1.Insert_R(a[i], i);
	}

	b1.Find_R(3);
	//b1.InOrder();
	//cout << endl;
	//BSTreeNode<int, int>* node;
	//node = b1.Find_R(10);
	//cout << node->_key<<"===="<<node->_value << endl;
	/*b1.Remove_R(7);
	b1.InOrder();
	b1.Remove_R(5);
	b1.InOrder();*/
	//cout<<b1.IsbalanceTree_R();
	/*b1.ToMirror();
	b1.InOrder();*/
	//b1.IsbalanceTree_R();
}
