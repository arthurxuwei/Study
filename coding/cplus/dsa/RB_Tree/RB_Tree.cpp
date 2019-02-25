#include "RB_Tree.h"

template<typename KEY, typename U>
RB_Tree<KEY, U>::RB_Tree(void)
	:m_nullNode(new RB_Node<KEY, U>()), m_root(m_nullNode)
{//构造函数
	m_nullNode->right = m_root;
	m_nullNode->left = m_root;
	m_nullNode->parent = m_root;
	m_nullNode->color = BLACK;
}

template<typename KEY, typename U>
RB_Tree<KEY, U>::~RB_Tree(void)
{
	Remove(m_root);
	delete m_nullNode;
}

template<typename KEY, typename U>
bool RB_Tree<KEY, U>::Empty()
{
	if (m_root == m_nullNode)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<typename KEY, typename U>
RB_Node<KEY, U>* RB_Tree<KEY, U>::Find(KEY key)
{//查找关键字
 //输入：key
 //输出：Node
	RB_Node<KEY, U>* index = m_root;
	while (index != m_nullNode)
	{
		if (key < index->key)
		{
			index = index->left;
		}
		else if (key > index->key)
		{
			index = index->right;
		}
		else
			break;
	}
	return index;
}

template<typename KEY, typename U>
bool RB_Tree<KEY, U>::Insert(KEY key, U data)
{//插入节点
 //输入：关键字、数据
 //输出：插入是否成功
	RB_Node<KEY, U>* insert_point = m_nullNode;
	RB_Node<KEY, U>* index = m_root;
	while (index != m_nullNode)
	{
		insert_point = index;
		if(key<index->key)  
		{  
			index = index->left;  
		}  
		else if(key>index->key)  
		{  
			index = index->right;  
		}  
		else  
		{  
			return false;  
		}
	}

	RB_Node<KEY, U>* insert_node = new RB_Node<KEY, U>();
	insert_node->key = key;  
	insert_node->data = data;  
	insert_node->color = RED;
	insert_node->right = m_nullNode;  
	insert_node->left = m_nullNode;  

	if(insert_point == m_nullNode) //如果插入的是一颗空树  
	{  
		m_root = insert_node;  
		m_root->parent = m_nullNode;  
		m_nullNode->left = m_root;  
		m_nullNode->right = m_root;  
		m_nullNode->parent = m_root;  
	}  
	else  
	{  
		if(key < insert_point->key)  
		{  
			insert_point->left = insert_node;  
		}  
		else  
		{  
			insert_point->right = insert_node;  
		}  
		insert_node->parent = insert_point;  
	}  
	InsertFixUp(insert_node);
}

template<typename KEY, typename U>
void RB_Tree<KEY, U>::InsertFixUp(RB_Node<KEY, U>* node)
{
	while(node->parent->color==RED)  
	{  
		if(node->parent==node->parent->parent->left)   //  
		{  
			RB_Node<KEY, U>* uncle = node->parent->parent->right;  
			if(uncle->color == RED)   //插入情况1，z的叔叔y是红色的。  
			{  
				node->parent->color = BLACK;  
				uncle->color = BLACK;  
				node->parent->parent->color = RED;  
				node = node->parent->parent;  
			}  
			else if(uncle->color == BLACK )  //插入情况2：z的叔叔y是黑色的，。  
			{  
				if(node == node->parent->right) //且z是右孩子  
				{  
					node = node->parent;  
					RotateLeft(node);  
				}  
				else                 //插入情况3：z的叔叔y是黑色的，但z是左孩子。  
				{  
					node->parent->color = BLACK;  
					node->parent->parent->color = RED;  
					RotateRight(node->parent->parent);  
				}  
			}  
		}  
		else //这部分是针对为插入情况1中，z的父亲现在作为祖父的右孩子了的情况，而写的。  
			//15 else (same as then clause with "right" and "left" exchanged)  
		{  
			RB_Node<KEY, U>* uncle = node->parent->parent->left;  
			if(uncle->color == RED)  
			{  
				node->parent->color = BLACK;  
				uncle->color = BLACK;  
				uncle->parent->color = RED;  
				node = node->parent->parent;  
			}  
			else if(uncle->color == BLACK)  
			{  
				if(node == node->parent->left)  
				{  
					node = node->parent;  
					RotateRight(node);     //与上述代码相比，左旋改为右旋  
				}  
				else  
				{  
					node->parent->color = BLACK;  
					node->parent->parent->color = RED;  
					RotateLeft(node->parent->parent);   //右旋改为左旋，即可。  
				}  
			}  
		}  
	}  
	m_root->color = BLACK; 
}

template<typename KEY, typename U>
bool RB_Tree<KEY, U>::RotateLeft(RB_Node<KEY, U>* node)  
{//左旋代码实现  
 //输入：要旋转节点
 //输出：旋转是否成功
	if(node == m_nullNode || node->right == m_nullNode)  
	{  
		return false;//无法旋转 
	}  
	RB_Node<KEY, U>* lower_right = node->right;  
	lower_right->parent =  node->parent;  
	node->right = lower_right->left;  
	if(lower_right->left != m_nullNode)  
	{  
		lower_right->left->parent = node;  
	}  
	if(node->parent == m_nullNode) //根节点 
	{  
		m_root = lower_right;  
		m_nullNode->left = m_root;  
		m_nullNode->right = m_root;  
		//m_nullNode->parent = m_root;  
	}  
	else  
	{  
		if(node == node->parent->left)  
		{  
			node->parent->left = lower_right;  
		}  
		else  
		{  
			node->parent->right = lower_right;  
		}  
	}  
	node->parent = lower_right;  
	lower_right->left = node;  
}  

template<typename KEY, typename U>
bool RB_Tree<KEY, U>::RotateRight(RB_Node<KEY, U>* node)  
{//右旋代码实现
 //输入：要旋转节点
 //输出：旋转是否成功
	if(node == m_nullNode || node->left == m_nullNode)  
	{  
		return false;
	}  
	RB_Node<KEY, U>* lower_left = node->left;  
	node->left = lower_left->right;  
	lower_left->parent = node->parent;  
	if(lower_left->right != m_nullNode)  
	{  
		lower_left->right->parent = node;  
	}  
	if(node->parent == m_nullNode)
	{  
		m_root = lower_left;  
		m_nullNode->left = m_root;  
		m_nullNode->right = m_root;  
		//m_nullNode->parent = m_root;  
	}  
	else  
	{  
		if(node == node->parent->right)  
		{  
			node->parent->right = lower_left;  
		}  
		else  
		{  
			node->parent->left = lower_left;  
		}  
	}  
	node->parent = lower_left;  
	lower_left->right = node;  
}  

//--------------------------删除结点操作----------------------------------  
template<typename KEY, typename U>
bool RB_Tree<KEY, U>::Delete(KEY key)  
{//删除节点
	RB_Node<KEY, U>* delete_point = Find(key);  
	if(delete_point == m_nullNode)  
	{  
		return false;  
	}  
	if(delete_point->left != m_nullNode && delete_point->right != m_nullNode)  //按二叉查找树规则删除
	{  
		RB_Node<KEY, U>* successor = InOrderSuccessor(delete_point);  
		delete_point->data = successor->data;  
		delete_point->key = successor->key;  
		delete_point = successor;  
	}  
	RB_Node<KEY, U>* delete_point_child;  
	if(delete_point->right != m_nullNode)  
	{  
		delete_point_child = delete_point->right;  
	}  
	else if(delete_point->left != m_nullNode)  
	{  
		delete_point_child = delete_point->left;  
	}  
	else  
	{  
		delete_point_child = m_nullNode;  
	}  
	delete_point_child->parent = delete_point->parent;  
	if(delete_point->parent == m_nullNode)
	{  
		m_root = delete_point_child;  
		m_nullNode->parent = m_root;  
		m_nullNode->left = m_root;  
		m_nullNode->right = m_root;  
	}  
	else if(delete_point == delete_point->parent->right)  
	{  
		delete_point->parent->right = delete_point_child;  
	}  
	else  
	{  
		delete_point->parent->left = delete_point_child;  
	}  
	if(delete_point->color == BLACK && !(delete_point_child == m_nullNode && delete_point_child->parent == m_nullNode))  
	{//如果删除的是黑节点，要调整
		DeleteFixUp(delete_point_child);  
	}  
	delete delete_point;  
	return true;  
}  

template<typename KEY, typename U>
void RB_Tree<KEY, U>::DeleteFixUp(RB_Node<KEY, U>* node)  
{  
	while(node != m_root && node->color == BLACK)  
	{  
		if(node == node->parent->left)  
		{//如果节点是左孩子
			RB_Node<KEY, U>* brother = node->parent->right;  
			if(brother->color == RED)   //情况1：x的兄弟w是红色的。  
			{  
				brother->color = BLACK;  
				node->parent->color = RED;  
				RotateLeft(node->parent);  
			}  
			else     //情况2：x的兄弟w是黑色的，  
			{  
				if(brother->left->color == BLACK && brother->right->color == BLACK)  
					//且w的俩个孩子都是黑色的。  
				{  
					brother->color = RED;  
					node = node->parent;  
				}  
				else if(brother->right->color == BLACK)  
					//情况3：x的兄弟w是黑色的，w的右孩子是黑色（w的左孩子是红色）。  
				{  
					brother->color = RED;  
					brother->left->color = BLACK;  
					RotateRight(brother);  
				}  
				else if(brother->right->color == RED)  
					//情况4：x的兄弟w是黑色的，且w的右孩子时红色的。  
				{  
					brother->color = node->parent->color;  
					node->parent->color = BLACK;  
					brother->right->color = BLACK;  
					RotateLeft(node->parent);  
					node = m_root;  
				}  
			}  
		}  
		else
		{//如果节点是右孩子，同上只是遇到左旋改为右旋，遇到右旋改为左旋
			RB_Node<KEY, U>* brother = node->parent->left;  
			if(brother->color == RED)  
			{  
				brother->color = BLACK;  
				node->parent->color = RED;  
				RotateRight(node->parent);  
			}  
			else  
			{  
				if(brother->left->color == BLACK && brother->right->color == BLACK)  
				{  
					brother->color = RED;  
					node = node->parent;  
				}  
				else if(brother->left->color == BLACK)  
				{  
					brother->color = RED;  
					brother->right->color = BLACK;  
					RotateLeft(brother);  
				}  
				else if(brother->left->color == RED)  
				{  
					brother->color = node->parent->color;  
					node->parent->color = BLACK;  
					brother->left->color = BLACK;  
					RotateRight(node->parent);  
					node = m_root;  
				}  
			}  
		}  
	}  
	m_nullNode->parent = m_root;   //最后将node置为根结点，  
	node->color = BLACK;    //并改为黑色。  
}  

template<typename KEY, typename U>
RB_Node<KEY, U>* RB_Tree<KEY, U>::InOrderPredecessor(RB_Node<KEY, U>* node)  
{//先序节点
	if(node == m_nullNode)
	{  
		return m_nullNode;  
	}  
	RB_Node<KEY, U>* result = node->left; 
	while(result != m_nullNode) //找左子树的最右孩子 
	{  
		if(result->right != m_nullNode)       
		{  
			result = result->right;  
		}  
		else  
		{  
			break;  
		}  
	}   
	if(result == m_nullNode)  
	{  
		RB_Node<KEY, U>* index = node->parent;  
		result = node;  
		while(index != m_nullNode && result == index->left)  
		{  
			result = index;  
			index = index->parent;  
		}  
		result = index; 
	}  
	return result;  
}  

template<typename KEY, typename U>
RB_Node<KEY, U>* RB_Tree<KEY, U>::InOrderSuccessor(RB_Node<KEY, U>* node)  
{//后继节点
	if(node == m_nullNode)
	{  
		return m_nullNode;  
	}  
	RB_Node<KEY, U>* result = node->right;
	while(result != m_nullNode)        //右子树的最左节点 
	{  
		if(result->left != m_nullNode)       
		{  
			result = result->left;  
		}  
		else  
		{  
			break;  
		}  
	}                            
	if(result == m_nullNode)  
	{  
		RB_Node<KEY, U>* index = node->parent;  
		result = node;  
		while(index != m_nullNode && result == index->right)  
		{  
			result = index;  
			index = index->parent;  
		}  
		result = index;   
	}  
	return result;  
}  

template<typename KEY, typename U>
void RB_Tree<KEY, U>::Remove(RB_Node<KEY, U>* node)
{//递归移除节点
	if (node == m_nullNode)
	{
		return;
	}
	Remove(node->left);
	Remove(node->right);
	delete node;
}

/*
template<typename KEY, typename U>
void RB_Tree<KEY, U>::InOrderTraverse()
{
	InOrderTraverse(m_root); 
}


template<typename KEY, typename U>
void RB_Tree<KEY, U>::InOrderTraverse(RB_Node<KEY, U>* node)  
{//LDR 中序遍历
	if(node==m_nullNode)  
	{  
		return;  
	}  
	else  
	{  
		InOrderTraverse(node->left);  
		cout<<node->key<<endl;  
		InOrderTraverse(node->right);  
	}  
}  
*/

template<typename KEY, typename U>
void RB_Tree<KEY, U>::PreOrderTraverse()
{
	int high = 0;
	PreOrderTraverse(m_root, high); 
}

template<typename KEY, typename U>
void RB_Tree<KEY, U>::PreOrderTraverse(RB_Node<KEY, U>* node, int high)  
{//先序
	if(node == m_nullNode)  
	{  
		cout << setw(4 * high) << "Nil," << "\n";
		return;  
	}  
	else  
	{  
		char col;
		if (node->color == BLACK)
			col = 'B';
		else
			col = 'R';
		cout << setw(4 * high) << "(" << node->key  << col << ","  << "\n";  
		++high;
		PreOrderTraverse(node->left, high);  
		PreOrderTraverse(node->right, high); 
		--high;
		cout << setw(4 * high) << ")" << "\n";
	}  
}  

template<typename KEY, typename U>
void RB_Tree<KEY, U>::PrintTree()
{
//	InOrderTraverse();
	//按题目要求输出
	PreOrderTraverse();
}

template <typename KEY, typename U>  
int RB_Tree<KEY, U>::GetBlackHeight()  
{  
	RB_Node<KEY, U> *pNode = m_root;  
	int height = 0;  
	while (pNode != m_nullNode)  
	{  
		if(pNode->color == BLACK)  
			++height;  
		pNode = pNode->left;  
	}  
	return height;  
}  