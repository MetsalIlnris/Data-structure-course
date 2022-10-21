#pragma once

//用链表实现二叉树

#include<iostream>
#include<cstdlib>
#include"Queue.h"

template<typename>class TreeNode;
template<typename>class BinaryTree;
template<typename Item>std::ostream& operator<<(std::ostream& os, const TreeNode<Item>& TNode);

//二叉树的结点

template<typename Item>
class TreeNode {
public:
	Item data;
	TreeNode<Item>* _right;
	TreeNode<Item>* _left;
	TreeNode<Item>* _parent;
	void clearNode();
	void assignAsLeaf(Item item) { data = item; _right = NULL; _left = NULL; }
	friend std::ostream& operator<< <Item>(std::ostream& os, const TreeNode<Item>& TNode);

	friend class BinaryTree<Item>;
};

template<typename Item>
void TreeNode<Item>::clearNode() {
	if (this != NULL) {
		if (_right != NULL)_right->clearNode();
		if (_left != NULL)_left->clearNode();
		delete this;
	}
}

template<typename Item>
std::ostream& operator<< (std::ostream& os, const TreeNode<Item>& TNode) {
	std::cout << TNode.data;
	return os;
}

//二叉树定义

template<typename Item>
class BinaryTree
{
protected:
	struct TreeNode<Item>* _root;
	int NodeAmount;

public:
	BinaryTree();
	BinaryTree(BinaryTree& BT);
	~BinaryTree();

	void clear() { _root->clearNode(); _root = NULL; } //清空二叉树
	int size() { return NodeAmount; }
	bool isempty() { return _root == NULL; }

	bool swapTree();
	Queue<TreeNode<Item>> find(Item item);
private:
	bool swapTree(TreeNode<Item>*& _root);

	//四种遍历方法
public:
	void preOrder();
	void inOrder();
	void postOrder();
	void levelOrder();

	//四种遍历方法调用的内部函数
private:
	void preOrder(TreeNode<Item>*& BT_root);
	void inOrder(TreeNode<Item>*& BT_root);
	void postOrder(TreeNode<Item>*& BT_root);
	void levelOrder(TreeNode<Item>*& BT_root);

};

//****************构造函数****************

template<typename Item>
BinaryTree<Item>::BinaryTree() {
	_root = NULL;
	NodeAmount = 0;
}

template<typename Item>
BinaryTree<Item>::BinaryTree(BinaryTree& BT) {

}

template<typename Item>
BinaryTree<Item>::~BinaryTree() {
	clear();
}

//**************** swap  ****************

template<typename Item>
bool BinaryTree<Item>::swapTree() {
	if (_root->_right != NULL)swapTree(_root->_right);
	if (_root->_left != NULL)swapTree(_root->_left);
	TreeNode<Item>* cac = _root->_left;
	_root->_left = _root->_right;
	_root->_right = cac;
	return true;
}

template<typename Item>
bool BinaryTree<Item>::swapTree(TreeNode<Item>*& _root) {
	if (_root->_right != NULL)swapTree(_root->_right);
	if (_root->_left != NULL)swapTree(_root->_left);
	TreeNode<Item>* cac = _root->_left;
	_root->_left = _root->_right;
	_root->_right = cac;
	return true;
}


//二叉树遍历：7个方法

template<typename Item>
void BinaryTree<Item>::preOrder() {
	std::cout << *_root << ' ';
	if (_root->_right != NULL)preOrder(_root->_right);
	if (_root->_left != NULL)preOrder(_root->_left);
}

template<typename Item>
void BinaryTree<Item>::inOrder() {
	if (_root->_right != NULL)inOrder(_root->_right);
	std::cout << *_root << ' ';
	if (_root->_left != NULL)inOrder(_root->_left);
}

template<typename Item>
void BinaryTree<Item>::postOrder() {
	if (_root->_right != NULL)postOrder(_root->_right);
	if (_root->_left != NULL)postOrder(_root->_left);
	std::cout << *_root << ' ';
}

template<typename Item>
void BinaryTree<Item>::levelOrder() {
	Queue<TreeNode<Item>*> cache;
	TreeNode<Item>* cur = _root;
	while (cur != NULL) {
		std::cout << *cur;
		if (cur->_left != NULL)cache.push(cur->_left);
		if (cur->_right != NULL)cache.push(cur->_right);
		if (!cache.pop(cur))break;
	}
}

template<typename Item>
void BinaryTree<Item>::preOrder(TreeNode<Item>*& BT_root) {
	std::cout << *BT_root << ' ';
	if (BT_root->_left != NULL)preOrder(BT_root->_left);
	if (BT_root->_right != NULL)preOrder(BT_root->_right);
}

template<typename Item>
void BinaryTree<Item>::inOrder(TreeNode<Item>*& BT_root) {
	if (BT_root->_left != NULL)inOrder(BT_root->_left);
	std::cout << *BT_root << ' ';
	if (BT_root->_right != NULL)inOrder(BT_root->_right);
}

template<typename Item>
void BinaryTree<Item>::postOrder(TreeNode<Item>*& BT_root) {
	if (BT_root->_left != NULL)inOrder(BT_root->_left);
	if (BT_root->_right != NULL)inOrder(BT_root->_right);
	std::cout << *BT_root << ' ';
}