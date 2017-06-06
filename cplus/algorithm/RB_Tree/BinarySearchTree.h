#pragma once
template <class T> 
struct BinaryNode 
{ 
	T                element; 
	BinaryNode        *left; 
	BinaryNode        *right;
	BinaryNode(const T& theElement, 
		BinaryNode *lt, 
		BinaryNode *rt): 
	element(theElement), 
		left(lt), 
		right(rt) 
	{
	} 
};

enum ORDER_MODE 
{ 
     ORDER_MODE_PREV = 0, 
     ORDER_MODE_MID, 
     ORDER_MODE_POST 
};

template <class T> 
class BinarySearchTree 
{ 
private:
	BinaryNode<T>            *m_root;
public: 
	BinarySearchTree(); 
	BinarySearchTree(const BinarySearchTree& rhs); 
	~BinarySearchTree();
	const T& findMin() const; 
	const T& findMax() const; 
	bool contains(const T& x) const; 
	void printTree(/*ORDER_MODE eOrderMode = ORDER_MODE_PREV*/) const;
	void makeEmpty(); 
	void insert(const T& x); 
	void remove(const T& x);
private: 
	//私有成员函数 
	void insert(const T& x, BinaryNode<T>* &t) ; 
	void remove(const T& x, BinaryNode<T>* &t) ; 
	BinaryNode<T>* findMin( BinaryNode<T>* t) const; 
	BinaryNode<T>* findMax( BinaryNode<T>* t) const; 
	bool contains(const T& x, const BinaryNode<T>* t) const; 

	void makeEmpty(BinaryNode<T>* t); 

	void printTreeInPrev(BinaryNode<T>* t) const; 
	void printTreeInMid(BinaryNode<T>* t)const; 
//	void printTreeInPost(BinaryNode<T>* t)const; 
};