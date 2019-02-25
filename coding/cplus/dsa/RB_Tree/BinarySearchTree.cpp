#include "BinarySearchTree.h"


template <class T> 
BinarySearchTree<T>::BinarySearchTree() 
{ 
	m_root = NULL; 
}

template <class T> 
BinarySearchTree<T>:: BinarySearchTree(const BinarySearchTree& rhs) 
{ 
	m_root = rhs.m_root; 
}

template <class T> 
BinarySearchTree<T>:: ~BinarySearchTree() 
{ 
	makeEmpty(); 
}

// return true if the x is found in the tree 
template <class T> 
bool  BinarySearchTree<T>::contains(const T& x) const 
{ 
	return contains(x, m_root); 
}
template <class T> 
bool BinarySearchTree<T>::contains(const T& x, const BinaryNode<T>* t) const 
{ 
	if (!t) 
		return false; 
	else if (x < t->element) 
		return contains(x, t->left); 
	else if (x > t->element) 
		return contains(x, t->right); 
	else 
		return true; 
}
//clear the tree
template <class T> 
void  BinarySearchTree<T>::makeEmpty() 
{ 
	makeEmpty(m_root); 
}

template <class T> 
void  BinarySearchTree<T>::makeEmpty(BinaryNode<T>* t) 
{ 
	if (t) 
	{ 
		makeEmpty(t->left); 
		makeEmpty(t->right); 
		delete t; 
	} 
	t = NULL; 
}

//find the maximum node
template <class T> 
BinaryNode<T>* BinarySearchTree<T>::findMax( BinaryNode<T>* t) const 
{ 
	//二叉树的一个特点就是左子叶的值比根节点小， 右子叶的比根节点的大 
	if (t != NULL) 
		while (t->right != NULL) 
			t = t->right; 
	return t; 
}

//find the minimum node
template <class T> 
BinaryNode<T>* BinarySearchTree<T>::findMin( BinaryNode<T>* t) const 
{ 
	//二叉树的一个特点就是左子叶的值比根节点小， 右子叶的比根节点的大 
	if (!t) 
		return NULL; 
	if (t->left == NULL) 
		return t; 
	else 
		return findMin(t->left); 
}

//insert a node
template <class T> 
void  BinarySearchTree<T>::insert(const T& x) 
{ 
	insert(x, m_root); 
}

template <class T> 
void BinarySearchTree<T>::insert(const T& x, BinaryNode<T>* &t) 
{ 
	if (t == NULL) 
		t = new BinaryNode<T>(x, NULL, NULL);
	else if (x < t->element) 
		insert(x, t->left); 
	else if (x > t->element) 
		insert(x, t->right); 
	else 
		;//do nothing 
}

//remove a node
template <class T> 
void  BinarySearchTree<T>::remove(const T& x) 
{ 
	remove(x, m_root); 
}

template <class T> 
void BinarySearchTree<T>::remove(const T& x, BinaryNode<T>* &t) 
{ 
	if (t == NULL) 
		return; 
	if (x < t->element) 
		remove(x, t->left); 
	else if (x > t->element) 
		remove (x, t->right); 
	else // now == 
	{ 
		if (t->left != NULL && 
			t->right != NULL)//two child 
		{ 
			t->element = findMin(t->right)->element; 
			remove(t->element, t->right); 
		} 
		else 
		{ 
			BinaryNode<T> *oldNode = t; 
			t = (t->left != NULL) ? t->left : t->right; 
			delete oldNode; 
		} 
	} 
}


//Print tree
template <class T>
void BinarySearchTree<T>::printTree(/*ORDER_MODE eOrderMode = ORDER_MODE_PREV*/) const
{
/*
	if (ORDER_MODE_PREV == eOrderMode)
		printTreeInPrev(m_root);
	else if (ORDER_MODE_MID == eOrderMode)
		printTreeInMid(m_root);
	else if (ORDER_MODE_POST == eOrderMode)
		printTreeInPost(m_root);
	else 
		;
	*/
	printTreeInMid(m_root);
}


template <class T>
void BinarySearchTree<T>::printTreeInPrev(BinaryNode<T>* t) const
{
	if (t)
	{
		cout << t->element << "\n";
		printTreeInPrev(t->left);
		printTreeInPrev(t->right);
	}
}


template <class T>
void BinarySearchTree<T>::printTreeInMid(BinaryNode<T>* t) const
{
	if (t)
	{
		printTreeInPrev(t->left);
		cout << t->element << "\n";
		printTreeInPrev(t->right);
	}
}
/*
template <class T>
void BinarySearchTree<T>::printTreeInPost(BinaryNode<T>* t) const
{
	if (t)
	{
		printTreeInPost(t->left);
		printTreeInPost(t->right);
		cout << t->element << "\n";
	}
}
*/