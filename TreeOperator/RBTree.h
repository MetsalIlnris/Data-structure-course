#pragma once
#include<iostream>

template<typename>class RBTNode;
template<typename>class RBTree;
template<typename Item>std::ostream& operator<<(std::ostream& os, const RBTNode<Item>& TNode);

enum RBTColor { RED, BLACK };
//******************************
//          RBTNODE
//******************************
template<typename Item>
class RBTNode : public RBTNode<Item>
{
protected:
	RBTColor _color;
	Item _data;
	RBTNode<Item>* _right;
	RBTNode<Item>* _left;
	RBTNode<Item>* _parent;
public:
	void clearNode();
	void assignAsLeaf(Item item) { _data = item; _right = NULL; _left = NULL; }
    bool operator< (RBTNode<Item> n) { return _data < n._data; }
    bool operator< (Item item) { return _data < item; }
    bool operator> (RBTNode<Item> n) { return _data > n._data; }
    bool operator< (Item item) { return _data > item; }
    bool operator== (RBTNode<Item> n) { return _data == n._data; }
    bool operator== (Item item) { return _data == item; }
    bool operator= (RBTNode<Item> n) { return _data = n._data; }
    bool operator= (Item item) { return _data = item; }
	friend std::ostream& operator<< <Item>(std::ostream& os, const RBTNode<Item>& TNode);

	friend class RBTree<Item>;
};

template<typename Item>
void RBTNode<Item>::clearNode() {
	if (this != NULL) {
		if (_right != NULL)_right->clearNode();
		if (_left != NULL)_left->clearNode();
		delete this;
	}
}

template<typename Item>
std::ostream& operator<< (std::ostream& os, const RBTNode<Item>& TNode) {
	std::cout << TNode._data;
	return os;
}
//******************************
//          RBTree
//******************************

template<typename Item>
class RBTree
{
protected:
	struct RBTNode<Item>* _root;
	int NodeAmount;

public:
	RBTree();
	RBTree(RBTree& BT);
	~RBTree();

	void clear() { _root->clearNode(); _root = NULL; } //清空二叉树
	int size() { return NodeAmount; }
	bool isempty() { return _root == NULL; }

    bool push(Item item);
    bool remove(Item item);

    //四种遍历方法
    void preOrder();
    void inOrder();
    void postOrder();
    void levelOrder();

	//内部函数
private:
    bool swap(RBTNode<Item>*& _root);
    bool rotateR(RBTNode<Item>*& _root);
    bool rotateL(RBTNode<Item>*& _root);
	void preOrder(RBTNode<Item>*& BT_root);
	void inOrder(RBTNode<Item>*& BT_root);
	void postOrder(RBTNode<Item>*& BT_root);
	void levelOrder(RBTNode<Item>*& BT_root);

};

//****************构造函数****************

template<typename Item>
RBTree<Item>::RBTree() {
	_root = NULL;
	NodeAmount = 0;
}

template<typename Item>
RBTree<Item>::RBTree(RBTree& BT) {
    
}

template<typename Item>
RBTree<Item>::~RBTree() {
	clear();
}

//**************** swap & rotate ****************
template<typename Item>
bool RBTree<Item>::swap(RBTNode<Item>*& _root) {
	if (_root->_right != NULL)swap(_root->_right);
	if (_root->_left != NULL)swap(_root->_left);
	RBTNode<Item>* cac = _root->_left;
	_root->_left = _root->_right;
	_root->_right = cac;
	return true;
}

template<typename Item>
bool RBTree<Item>::rotateR(RBTNode<Item>*& _root) {
    if (_root->parent) {
        if (_root == _root->_parent->_left) {
            _root->_parent->_left = _root->_left;
        }
        else {
            _root->_parent->_right = _root->_left;
        }
    }
    _root->_left->_parent = _root->_parent;
    _root->_parent = _root_left;
    _root->_left = _root_left->_right;
    _root->_left->_parent = _root;
    _root->_parent->_right = _root;

}

template<typename Item>
bool RBTree<Item>::rotateL(RBTNode<Item>*& _root) {
    if (_root->parent) {
        if (_root == _root->_parent->_right) {
            _root->_parent->_right = _root->_right;
        }
        else {
            _root->_parent->_left = _root->_right;
        }
    }
    _root->_right->_parent = _root->_parent;
    _root->_parent = _root_right;
    _root->_right = _root_right->_left;
    _root->_right->_parent = _root;
    _root->_parent->_left = _root;
}
//**********二叉树遍历：7个方法***********

template<typename Item>
void RBTree<Item>::preOrder() {
	std::cout << *_root << ' ';
	if (_root->_right != NULL)preOrder(_root->_right);
	if (_root->_left != NULL)preOrder(_root->_left);
}

template<typename Item>
void RBTree<Item>::inOrder() {
	if (_root->_right != NULL)inOrder(_root->_right);
	std::cout << *_root << ' ';
	if (_root->_left != NULL)inOrder(_root->_left);
}

template<typename Item>
void RBTree<Item>::postOrder() {
	if (_root->_right != NULL)postOrder(_root->_right);
	if (_root->_left != NULL)postOrder(_root->_left);
	std::cout << *_root << ' ';
}

template<typename Item>
void RBTree<Item>::levelOrder() {
	Queue<RBTNode<Item>*> cache;
	RBTNode<Item>* cur = _root;
	while (cur != NULL) {
		std::cout << *cur;
		if (cur->_left != NULL)cache.push(cur->_left);
		if (cur->_right != NULL)cache.push(cur->_right);
		if (!cache.pop(cur))break;
	}
}

template<typename Item>
void RBTree<Item>::preOrder(RBTNode<Item>*& BT_root) {
	std::cout << *BT_root << ' ';
	if (BT_root->_left != NULL)preOrder(BT_root->_left);
	if (BT_root->_right != NULL)preOrder(BT_root->_right);
}

template<typename Item>
void RBTree<Item>::inOrder(RBTNode<Item>*& BT_root) {
	if (BT_root->_left != NULL)inOrder(BT_root->_left);
	std::cout << *BT_root << ' ';
	if (BT_root->_right != NULL)inOrder(BT_root->_right);
}

template<typename Item>
void RBTree<Item>::postOrder(RBTNode<Item>*& BT_root) {
	if (BT_root->_left != NULL)inOrder(BT_root->_left);
	if (BT_root->_right != NULL)inOrder(BT_root->_right);
	std::cout << *BT_root << ' ';
}

template<typename Item>
bool RBTree<Item>::push(Item item)
{
    //根节点为空
    if (_root == NULL)
    {
        _root = new RBTNode<Item>;
        _root->assignAsLeaf(item);
        _root->_color = BLACK;

        return true;
    }
    //根节点不为空

    //找到新节点插入位置
    RBTNode<Item>* parent = NULL;
    RBTNode<Item>* cur = _root;

    while (cur)
    {
        if (*cur < item)
        {
            parent = cur;
            cur = cur->_right;
        }
        else
        {
            parent = cur;
            cur = cur->_left;
        }
    }
    //插入新节点
    cur = new RBTNode<Item>;
    cur->_color = RED;
    if (*parent > item)
    {
        parent->_left = cur;
        cur->_parent = parent;
    }
    else
    {
        parent->_right = cur;
        cur->_parent = parent;
    }

    //插入节点后颜色的调整
    while (parent && parent->_color == RED)
    {
        RBTNode<Item>* grandfather = parent->_parent;//grandfather颜色一定为黑色
        if (parent == grandfather->_left)
        {
            RBTNode<Item>* uncle = grandfather->_right;

            //uncle存在且为红
            if (uncle && uncle->_color == RED)
            {
                parent->_color = uncle->_color = BLACK;
                grandfather->_color = RED;

                cur = grandfather;//往上继续调整
                parent = cur->_parent;
            }
            else//uncle不存在/uncle存在且为黑
            {
                if (cur == parent->_right)
                {
                    rotateL(parent);
                    //warning swap
                }
                rotateR(grandfather);
                parent->_color = BLACK;
                grandfather->_color = RED;
            }
        }
        else//grandfather->_right==parent
        {
            RBTNode<Item>* uncle = grandfather->_left;

            //uncle存在且为红
            if (uncle && uncle->_color == RED)
            {
                parent->_color = uncle->_color = BLACK;
                grandfather->_color = RED;

                cur = grandfather;//往上继续调整
                parent = cur->_parent;
            }
            else//不存在/存在且为黑
            {
                if (cur == parent->_left)
                {
                    rotateR(parent);
                    //warning swap
                }

                rotateL(grandfather);
                parent->_color = BLACK;
                grandfather->_color = RED;
            }
        }
    }//end while (parent && parent->_color == RED)

    _root->_color = BLACK;

    return true;
}

template<typename Item>
bool RBTree<Item>::Remove(Item item) {

}
private void deleteLeafFix(Node deletedNode) {
	while ((deletedNode != root) && (BLACK == deletedNode.color)) {
		Node parent = deletedNode.parentNode;
		Node brother = getBrother(deletedNode);
		if (deletedNode.key.compareTo(parent.key) > 0) { // 删除的是右叶子节点
			if (RED == brother.color) { // case5: 如果该兄弟节点是红色的，那么根据红黑树的特性可以得出它的一定有两个黑色的子节点
				brother.color = BLACK;
				brother.rightNode.color = RED;
				rightRotation(parent);
				break;
			}
			else {
				if ((null == brother.leftNode) && (null == brother.rightNode)) { // case4: 兄弟节点是黑色的，且没有子节点
					brother.color = RED; // 将兄弟节点设为红色，将父节点设为当前节点递归， 直到根节点，或遇到红色节点，
					deletedNode = parent;
				}
				else {
					if ((null != brother.leftNode) && (RED == brother.leftNode.color)) {// case1: 兄弟节点是黑色的，且有一个左节点（可以断定 左节点是红色的）
						//case3: 兄弟节点是黑色的，且有两个节点（可以断定 左右节点都是红色的） 这个和情况 1 是一样的
						brother.color = parent.color;
						parent.color = BLACK;
						brother.leftNode.color = BLACK;
						rightRotation(parent);
						break;
					}
					else {// case2: 兄弟节点是黑色的，且有一个右节点（可以断定 右节点是红色的）
						brother.rightNode.color = BLACK;
						brother.color = RED;
						leftRotation(brother);
					}
				}
			}
		}
		else {// 删除的是左叶子节点
			if (RED == brother.color) { // case5 : 如果该兄弟节点是红色的，那么根据红黑树的特性可以得出它的一定有两个黑色的子节点
				brother.color = BLACK;
				brother.leftNode.color = RED;
				leftRotation(parent);
				break;
			}
			else {
				if ((null == brother.leftNode) && (null == brother.rightNode)) { // case4: 兄弟节点是黑色的，且没有子节点
					brother.color = RED; // 将兄弟节点设为红色，将父节点设为当前节点递归， 直到根节点，或遇到红色节点，
					deletedNode = parent;
				}
				else {
					if ((null != brother.rightNode) && (RED == brother.rightNode.color)) { // case1 : 兄弟节点是黑色的，且有一个右节点（可以断定 右节点是红色的）
						// case3 : 兄弟节点是黑色的，且有两个节点（可以断定 左右节点都是红色的） 这个和情况 1 是一样的
						brother.color = parent.color;
						parent.color = BLACK;
						brother.rightNode.color = BLACK;
						leftRotation(parent);
						break;
					}
					else { // case2: 兄弟节点是黑色的，且有一个左节点（可以断定 左节点是红色的）
						brother.leftNode.color = BLACK;
						brother.color = RED;
						rightRotation(brother);
					}
				}
			}
		}
	}

	deletedNode.color = BLACK;
}

private Node getBrother(Node node) {
	if (null == node) {
		return null;
	}
	Node parent = node.parentNode;
	if (null == parent) {
		return null;
	}
	if (node.key.compareTo(parent.key) > 0) {
		return parent.leftNode;
	}
	else {
		return parent.rightNode;
	}
}

public boolean delete(K key) {
	if (null != key) {
		if (null != root) {
			return deleteNode(key, root, null);
		}
	}
	return false;
}

private boolean deleteNode(K key, Node current, Node parent) {
	if (null != current) {
		if (key.compareTo(current.key) > 0) {
			return deleteNode(key, current.rightNode, current);
		}
		if (key.compareTo(current.key) < 0) {
			return deleteNode(key, current.leftNode, current);
		}
		if (key.compareTo(current.key) == 0) {
			if ((null != current.leftNode) && (null != current.rightNode)) { //将要删除的节点下有两个子节点
				dleTwoChildrenNode(current);
				return true;
			}
			else {
				if ((null == current.leftNode) && (null == current.rightNode)) { //将要删除的节点没有子节点
					deleteLeafFix(current);
					if (current.key.compareTo(parent.key) > 0) {
						parent.rightNode = null;
					}
					else {
						parent.leftNode = null;
					}
					return true;
				}
				else { // 将要删除的节点下有一个子节点, 
					dleOneChildNode(current);
					return true;
				}
			}
		}
	}
	return false;
}

private void dleOneChildNode(Node delNode) {
	Node replaceNode = (null == delNode.leftNode) ? delNode.rightNode : delNode.leftNode;
	deltetLeafNode(delNode, replaceNode);
}

/**
 * 处理被删除节点有两个子节点的情况
 * @param target 将要被删除的节点
 */
private void dleTwoChildrenNode(Node target) {
	Node replaceNode = successor(target);
	if ((null == replaceNode.rightNode) && (null == replaceNode.leftNode)) {
		deltetLeafNode(target, replaceNode);
	}
	else {
		target.key = replaceNode.key;
		target.value = replaceNode.value;
		dleOneChildNode(replaceNode);
	}
}

private void deltetLeafNode(Node target, Node replaceNode) {
	target.key = replaceNode.key;
	target.value = replaceNode.value;
	deleteLeafFix(replaceNode);
	if (replaceNode == replaceNode.parentNode.rightNode) {
		replaceNode.parentNode.rightNode = null;
	}
	else {
		replaceNode.parentNode.leftNode = null;
	}
}

//找后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"
private Node successor(Node node) {
	if (node == null) {
		return null;
	}
	if (null != node.rightNode) { // 获取 后继节点
		Node p = node.rightNode;
		while (null != p.leftNode) {
			p = p.leftNode;
		}
		return p;
	}
	else {
		Node p = node.parentNode;
		Node ch = node;
		while (p != null && ch == p.rightNode) {
			ch = p;
			p = p.parentNode;
		}
		return p;
	}
}