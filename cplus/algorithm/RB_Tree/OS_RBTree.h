#pragma once
#ifndef OS_RBTREE_H  
#define OS_RBTREE_H  

#include <iostream>  
#include <stack>  
#include <fstream>  
#include <string>  
using std::string;  
using std::cin;  
using std::cout;  
using std::endl;  
using std::stack;  
using std::ifstream;  
using std::ofstream;  
template <typename KEY>  
class OS_RBTree  
{  
	class Node ;                                            //节点定义  
public:  
	OS_RBTree();  

	~OS_RBTree();  
	void Insert(KEY key);  
	void Delete(KEY key);  
	void BuildTree(const string &name);  
	int OS_Key_Rank(KEY key);  
	void PrintFormat(Node* node,int level);  
	void MakeSpace(int);  
	void PrintKeyAndColor(Node* node);  
	Node* GetRoot()  
	{  
		return root;  
	}  
private:  
	enum NodeColor {RED,BLACK};                             //节点颜色，枚举类型  
	Node *root,*nullNode;  
	void LeftRotate(Node *node);                            //左旋  
	void RightRotate(Node *node);                           //右旋  
	void InsertFixup(Node *node);                           //插入调整  
	void DeleteFixup(Node *node);                           //删除调整  
	bool Clear(Node *);  
	Node* GetUncle(Node *node)  
	{  
		Node *result = NULL,*parent,*grandFather;  
		parent = node->parent;  
		grandFather = parent->parent;  
		if(parent == grandFather->left)  
			result = grandFather->right;  
		else  
			result = grandFather->left;  
		return result;  
	}  
	Node* FindKey(KEY key)  
	{  
		Node *result;  
		result = root;  
		while (result!=nullNode && key!=result->key)  
		{  
			if (key < result->key)  
			{  
				result = result->left;  
			}  
			else if(key > result->key)  
			{  
				result = result->right;  
			}  
		}  
		return result;  
	}  
	Node* OS_RBTreeSuccessor(Node *node)  
	{  
		Node *result;  
		result = node->right;  
		if(result != nullNode)  
			while(result->left != nullNode)  
				result = result->left;  
		else  
		{  
			result = node->parent;  
			while (result!=nullNode && node==result->right)  
			{  
				node = result;  
				result = result->parent;  
			}  
		}  
		return result;  

	}  
};  

#endif //OS_RBTREE_H
