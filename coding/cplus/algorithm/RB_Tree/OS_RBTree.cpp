#include "OS_RBTree.h"


template <typename KEY>  
class OS_RBTree<KEY>::Node                                              //节点定义  
{  
public:  
	Node(KEY k ,NodeColor col):key(k),size(1),color(col),left(NULL),right(NULL),parent(NULL) {}  
	Node():key(-1),size(0),color(BLACK),left(NULL),right(NULL),parent(NULL) {}  
	KEY key;  
	int size;  
	NodeColor color;  
	Node *left,*right,*parent;  
};  
template <typename KEY>  
OS_RBTree<KEY>::OS_RBTree()  
{  
	nullNode = new Node();  
	nullNode->left = nullNode;          //此处是否可指向root？  
	nullNode->right = nullNode;  
	nullNode->parent = nullNode;  
	root = nullNode;  
}  


template <typename KEY>  
int OS_RBTree<KEY>::OS_Key_Rank(KEY key)  
{  
	Node *node = FindKey(key);  
	int r = node->left->size + 1;  
	while (node != root)  
	{  
		if(node == node->parent->right)  
			r += node->parent->left->size + 1;  
		node = node->parent;  
	}  
	return r;  
}  


template <typename KEY>  
void OS_RBTree<KEY>::Insert(KEY key)  
{  
	Node *node,*temp;  
	temp = NULL;  
	node = root;  
	while (node != nullNode)  
	{  
		++node->size;           //修改size域  
		temp = node;  
		if (key < node->key)  
		{  
			node = node->left;  
		}  
		else if(key > node->key)  
		{  
			node = node->right;  
		}  
		else  
			return;  
	}  
	Node *newNode = new Node(key,RED);  
	newNode->left = nullNode;  
	newNode->right = nullNode;  
	newNode->parent = nullNode;  
	if(root == nullNode)  
	{  
		root = newNode;  
		root->color = BLACK;  
		nullNode->left = root;  
		nullNode->right = root;  
		nullNode->parent = root;  
		return;                                 //如果插入根节点，不用fixup  
	}  
	else  
	{  
		node = temp;  
		if(key < node->key)  
			node->left = newNode;  
		else  
			node->right = newNode;  
	}  
	newNode->parent = node;  
	InsertFixup(newNode);  
}  

template <typename KEY>  
void OS_RBTree<KEY>::InsertFixup(Node *node)  
{  
	Node *parent = NULL;  
	while ((parent = node->parent) && node->parent->color == RED)  
	{  
		if (parent == parent->parent->left)  
		{  
			Node *uncle = GetUncle(node);  
			if (uncle->color == RED)       //uncle may be nullNode  
			{  
				parent->color = BLACK;  
				uncle->color = BLACK;  
				parent->parent->color = RED;  
				node = parent->parent;  
			}  
			else  
			{  
				if(node == parent->right)  
				{  
					node = parent;  
					LeftRotate(node);  
				}  
				parent = node->parent;  
				parent->color = BLACK;  
				parent->parent->color = RED;  
				RightRotate(parent->parent);  
			}  
		}  
		else  
		{  
			Node *uncle = GetUncle(node);  
			if (uncle->color == RED)  
			{  
				parent->color = BLACK;  
				uncle->color = BLACK;  
				parent->parent->color = RED;  
				node = parent->parent;  
			}  
			else  
			{  
				if(node == parent->left)  
				{  
					node = parent;  
					RightRotate(node);  
				}  
				parent = node->parent;  
				parent->color = BLACK;  
				parent->parent->color = RED;  
				LeftRotate(parent->parent);  
			}  
		}  
	}  
	root->color = BLACK;  
}  




template <typename KEY>  
void OS_RBTree<KEY>::Delete(KEY key)  
{  
	Node *node;  
	node = root;  
	while (node!=nullNode && key!=node->key)  
	{  
		--node->size;                       //修改node的size域  
		if (key < node->key)  
		{  
			node = node->left;  
		}  
		else if(key > node->key)  
		{  
			node = node->right;  
		}  
	}  

	if(node == nullNode)  
		return;  
	--node->size;                               //修改node的size域  
	Node *child = nullNode,*real = nullNode;  
	if(node->left==nullNode || node->right==nullNode)  
		real = node;  
	else  
	{  
		Node *result;  
		result = node->right;  
		if(result != nullNode)  
			while(result->left != nullNode)  
			{  
				--result->size;                     //修改node的size域  
				result = result->left;  
			}  
			real = result;                              //物理删除的节点  
	}  
	if (real->left != nullNode)  
	{  
		child = real->left;  
	}  
	else  
	{  
		child = real->right;  
	}  
	child->parent = real->parent;           //没有判断child是否为NIL  
	if(real->parent == nullNode)  
	{  
		root = child;  
		nullNode->left = root;  
		nullNode->right = root;  
		nullNode->parent = root;  
	}  
	else if (real == real->parent->left)  
	{  
		real->parent->left = child;  
	}  
	else  
	{  
		real->parent->right = child;  
	}  
	if(node != real)                            //物理删除的节点不是node  
		node->key = real->key;  
	if(real->color == BLACK)                        //颜色为黑，需要fixup  
		DeleteFixup(child);  
	delete real;  
	real = NULL;  
}  




template <typename KEY>  
void OS_RBTree<KEY>::DeleteFixup(Node *node)  
{  
	while (node!=root && node->color==BLACK)  
	{  
		Node* parent = node->parent;  
		if (node == parent->left)  
		{  
			Node *brother = parent->right;  
			if (brother->color == RED)          //case1  
			{  
				parent->color = RED;  
				brother->color = BLACK;  
				LeftRotate(parent);  
				brother = parent->right;        //reset brother node  
			}                                   //case1 can run into from case2 to case4  
			if (brother->left->color==BLACK && brother->right->color==BLACK)  //case2  
			{  
				brother->color = RED;  
				node = parent;  
			}  
			else            //case2 and case3 must not exist!!!  
			{  
				if(brother->right->color==BLACK) //case3  
				{  
					brother->left->color = BLACK;  
					brother->color = RED;  
					RightRotate(brother);  
					brother = parent->right;        //reset brother node  
				}                               //case3 can run into case4  
				brother->color = parent->color;         //case4  
				parent->color = BLACK;  
				brother->right->color = BLACK;  
				LeftRotate(parent);  
				node = root;                        //break  
			}  
		}  
		else  
		{  
			Node *brother = parent->left;  
			if (brother->color == RED)          //case1  
			{  
				parent->color = RED;  
				brother->color = BLACK;  
				RightRotate(parent);  
				brother = parent->left;        //reset brother node  
			}  
			if (brother->left->color==BLACK && brother->right->color==BLACK)  //case2  
			{  
				brother->color = RED;  
				node = parent;  
			}  
			else            //case2 and case3 must not exist!!!  
			{  
				if(brother->left->color==BLACK) //case3  
				{  
					brother->right->color = BLACK;  
					brother->color = RED;  
					LeftRotate(brother);  
					brother = parent->left;        //reset brother node  
				}  
				brother->color = parent->color;         //case4  
				parent->color = BLACK;  
				brother->left->color = BLACK;  
				RightRotate(parent);  
				node = root;                        //break  
			}  
		}  
	}  
	node->color = BLACK;  
	nullNode->parent = root;  
	root->color = BLACK;  
}  






template <typename KEY>  
void OS_RBTree<KEY>::RightRotate(Node *node)  
{  
	Node *leftNode = node->left;  
	//修改size域  
	leftNode->size = node->size;  
	node->size = leftNode->right->size + node->right->size + 1; //修改node的size域  

	node->left = leftNode->right;  
	leftNode->right->parent = node;  
	leftNode->parent = node->parent;  
	if(leftNode->right!=nullNode)  
	{  
		leftNode->right->parent = node;  
	}  
	if (node->parent != nullNode)  
	{  
		if (node == node->parent->left)  
		{  
			node->parent->left = leftNode;  
		}  
		else  
		{  
			node->parent->right = leftNode;  
		}  
	}  
	else  
	{  
		root = leftNode;  
		nullNode->left = root;  
		nullNode->right = root;  
	}  
	node->parent = leftNode;  
	leftNode->right = node;  
}  



template <typename KEY>  
void OS_RBTree<KEY>::LeftRotate(Node *node)  
{  
	Node *rightNode = node->right;  
	rightNode->size = node->size;           //修改size域  
	node->size = node->left->size + rightNode->left->size + 1;  //修改node的size域  
	node->right = rightNode->left;  
	rightNode->left->parent = node;  
	rightNode->parent = node->parent;  
	if(rightNode->left!=nullNode)  
	{  
		rightNode->left->parent = node;  
	}  
	if(node->parent != nullNode)  
	{  
		if(node == node->parent->left)          //node is the left child of its parent  
			node->parent->left = rightNode;  
		else  
			node->parent->right = rightNode;  
	}  
	else  
	{  
		root = rightNode;  
		nullNode->left = root;  
		nullNode->right = root;  
	}  
	//node is root  
	node->parent = rightNode;  
	rightNode->left = node;  
}  
template <typename KEY>  
void OS_RBTree<KEY>::MakeSpace(int level)  
{  
	for(int i=0; i<level; ++i)  
		cout << "   ";  
}  
template <typename KEY>  
void OS_RBTree<KEY>::PrintFormat(Node* node,int level)  
{  
	if(node == root)  
		cout << "(";  
	PrintKeyAndColor(node);  
	cout << endl;  
	MakeSpace(level + 1);  
	cout << "(";  
	if (node->left == nullNode)  
	{  
		PrintKeyAndColor(node->left);  
		//      cout << ",";  
	}  
	else  
	{  
		PrintFormat(node->left,level + 1);  
	}  
	cout << endl;  
	MakeSpace(level + 1);  
	if (node->right == nullNode)  
	{  
		PrintKeyAndColor(node->right);  
		//      cout << ")";  
	}  
	else  
	{  
		PrintFormat(node->right,level + 1);  
	}  
	cout << endl;  
	MakeSpace(level + 1);  
	cout << ")";  
	if(node == root)  
		cout << endl << ")";  
}  
template <typename KEY>  
void OS_RBTree<KEY>::PrintKeyAndColor(Node* node)  
{  
	if (node == nullNode)  
	{  
		cout << "NIL" ;  
	}  
	else  
	{  
		cout << node->key;  
		if(node->color == RED)  
			cout << "R" ;  
		else  
			cout << "B";  
		cout << ",size: " << node->size;  
	}  
	//    if(node == node->parent->left)  
	//        cout << "," << endl;  
}  

template <typename KEY>  
bool OS_RBTree<KEY>::Clear(Node * node)  
{  
	if (node != nullNode)  
	{  
		Clear(node->left);  
		Clear(node->right);  
		delete node;  
	}  
	delete nullNode;  
	return true;  
}  
template <typename KEY>  
OS_RBTree<KEY>::~OS_RBTree()  
{  
	Clear(root);  
}  

