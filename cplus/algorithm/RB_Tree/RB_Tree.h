#pragma once
#include <boost/noncopyable.hpp>

enum COLOR{RED, BLACK};
//Node
template<typename KTYPE, typename DTYPE>
struct RB_Node
{
	RB_Node()
	{
		right = NULL;
		left = NULL;
		parent = NULL;
	}
	COLOR color;
	RB_Node* right;
	RB_Node* left;
	RB_Node* parent;
	KTYPE key;
	DTYPE data;
};

template<typename KEY, typename U>
class RB_Tree : boost :: noncopyable
{
public:
	RB_Tree(void);
	~RB_Tree(void);

	bool Empty();
	RB_Node<KEY, U>* Find(KEY key);
	bool Insert(KEY key, U data);
	bool Delete(KEY key);
	void PrintTree();
	int GetBlackHeight();

private:
	void InsertFixUp(RB_Node<KEY, U>* Node);
	void DeleteFixUp(RB_Node<KEY, U>* Node);
	bool RotateLeft(RB_Node<KEY, U>* Node);
	bool RotateRight(RB_Node<KEY, U>* Node);

	RB_Node<KEY, U>* InOrderPredecessor(RB_Node<KEY, U>* node);
	RB_Node<KEY, U>* InOrderSuccessor(RB_Node<KEY, U>* node);


	void PreOrderTraverse();
	void PreOrderTraverse(RB_Node<KEY, U>* node, int h);

	void InOrderTraverse();
	void InOrderTraverse(RB_Node<KEY, U>* node);
	void Remove(RB_Node<KEY, U>* node);
private:  
	RB_Node<KEY, U>* m_nullNode;  
	RB_Node<KEY, U>* m_root; 
};

