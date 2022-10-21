#pragma once

#include"BinaryTree.h"
#include<array>

class charBT :public BinaryTree<char>
{
public:
	charBT(){}
	charBT(charBT * charBT){}
	~charBT(){}

	bool insert(char ch);
	bool insert(char ch, TreeNode<char>*& _root);
	bool ConstructByCin();
	bool reconstruct();
	bool ConstructByArray(char prev[], char in[], int length, TreeNode<char>*& _root);
};

bool charBT::insert(char ch) {
	if (isempty()) {
		_root = new TreeNode<char>;
		_root->assignAsLeaf(ch);
		_root->_right = NULL;
		_root->_left = NULL;
		return true;
	}
	if (_root->data == '#')return false;//已经构建为满树，无法插入
	if (_root->_left == NULL) {
		_root->_left = new TreeNode<char>;
		_root->_left->assignAsLeaf(ch);
		return true;//左子节点有空位则直接插入
	}
	else if (insert(ch, _root->_left))return true;//如果在左子树插入成功则结束插入
	//如果在左子树插入失败，尝试插入右子树
	if (_root->_right == NULL) {
		_root->_right = new TreeNode<char>;
		_root->_right->assignAsLeaf(ch);
		return true;//右子节点有空位则直接插入
	}
	else if (insert(ch, _root->_right))return true;//如果在左子树插入成功则结束插入
	return false;//如果左右子树都无法插入，则插入失败
}

bool charBT::insert(char ch,TreeNode<char>*& _root) {
	if (_root == NULL) {
		_root = new TreeNode<char>;
		_root->assignAsLeaf(ch);
		NodeAmount++;
		return true;
	}
	if (_root->data == '#')return false;//已经构建为满树，无法插入
	if (_root->_left == NULL) {
		_root->_left = new TreeNode<char>;
		_root->_left->assignAsLeaf(ch);;
		NodeAmount++;
		return true;//左子节点为空则直接插入
	}
	else if (insert(ch, _root->_left))return true;//如果在左子树插入成功则结束插入
	//如果在左子树插入失败，尝试插入右子树
	if (_root->_right == NULL) {
		_root->_right = new TreeNode<char>;
		_root->_right->assignAsLeaf(ch);
		NodeAmount++;
		return true;//右子节点为空则直接插入
	}
	else if (insert(ch, _root->_right))return true;//如果在左子树插入成功则结束插入
	return false;//如果左右子树都无法插入，则插入失败
}

bool charBT::ConstructByCin() {
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF) {
		insert(ch);
	}
	return true;
}

bool charBT::reconstruct() {
	//char* prev, * in;
	//char ch;
	//printf("请输入节点个数");
	//int Amount;
	//std::cin >> Amount;
	//prev = new char[Amount];
	//in = new char[Amount];
	//printf("\n请输入前序遍历序列\n");
	//for (int i = 0; i < Amount; i++)prev[i - 1] = getchar();
	//while ((ch = getchar()) != '\n' && ch != EOF);//清空输入
	//printf("\n请输入中序遍历序列\n");
	//for (int i = 0; i < Amount; i++)in[i - 1] = getchar();
	//while ((ch = getchar()) != '\n' && ch != EOF);//清空输入
	char prev[5] = { '1','2','3','4','5'};
	char in[5] = { '2','1','4','3','5'};
	clear();
	if (ConstructByArray(prev, in, 5 , _root)) {
		std::cout << "构造成功" << std::endl;
		levelOrder();
		return true;
	}
	std::cout << "构造失败" << std::endl;
	return false;
}

bool charBT::ConstructByArray(char prev[], char in[],int length,TreeNode<char>*& subtree) {
	//不管什么遍历方式，结果长度肯定是一样的，都是总结点数
	if (length < 1) {
		return false;
	}
	//只有一个节点，那就是根节点
	if (length == 1) {
		subtree = new TreeNode<char>;
		subtree->assignAsLeaf(prev[0]);
		return true;
	}
	//在中序遍历结果中找根节点
	int index = -1;
	for (int i = 0; i < length; i++) {
		if (in[i] == prev[0]) {
			index = i;
			break;
		}
	}
	//没找到，说明数据有问题
	if (index == -1) {
		return false;
	}
	//找到根节点了
	subtree = new TreeNode<char>;
	subtree->assignAsLeaf(prev[0]);
	/*subtree->data = prev[0];
	subtree->_left = NULL;
	subtree->_right = NULL;*/

	if (index > 0) //此时存在左子树
	{
		//得到左子树的前序遍历结果
		char* lChildPrev = new char[index];
		for (int i = 0; i < index; i++) {
			lChildPrev[i] = prev[i + 1];
		}
		//得到左子树的中序遍历结果
		char* lChildIn = new char[index];
		for (int i = 0; i < index; i++) {
			lChildIn[i] = in[i];
		}
		//通过递归，得到左子树结构
		ConstructByArray(lChildPrev, lChildIn, index, subtree->_left);
	}

	if(length - index - 1 > 0)//此时存在右子树
	{
		//得到右子树的前序遍历结果
		char* rChildPrev = new char[length - index - 1];
		for (int i = index; i < length; i++) {
			rChildPrev[i - index] = prev[i + 1];
		}
		//得到右子树的中序遍历结果
		char* rChildIn = new char[index];
		for (int i = index; i < length; i++) {
			rChildIn[i - index] = in[i + 1];
		}
		//通过递归，得到右子树结构
		ConstructByArray(rChildPrev, rChildIn, length - index - 1, subtree->_right);
	}

	
	//得到完整的二叉树结构
	return true;


}
