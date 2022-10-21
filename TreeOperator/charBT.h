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
	if (_root->data == '#')return false;//�Ѿ�����Ϊ�������޷�����
	if (_root->_left == NULL) {
		_root->_left = new TreeNode<char>;
		_root->_left->assignAsLeaf(ch);
		return true;//���ӽڵ��п�λ��ֱ�Ӳ���
	}
	else if (insert(ch, _root->_left))return true;//���������������ɹ����������
	//���������������ʧ�ܣ����Բ���������
	if (_root->_right == NULL) {
		_root->_right = new TreeNode<char>;
		_root->_right->assignAsLeaf(ch);
		return true;//���ӽڵ��п�λ��ֱ�Ӳ���
	}
	else if (insert(ch, _root->_right))return true;//���������������ɹ����������
	return false;//��������������޷����룬�����ʧ��
}

bool charBT::insert(char ch,TreeNode<char>*& _root) {
	if (_root == NULL) {
		_root = new TreeNode<char>;
		_root->assignAsLeaf(ch);
		NodeAmount++;
		return true;
	}
	if (_root->data == '#')return false;//�Ѿ�����Ϊ�������޷�����
	if (_root->_left == NULL) {
		_root->_left = new TreeNode<char>;
		_root->_left->assignAsLeaf(ch);;
		NodeAmount++;
		return true;//���ӽڵ�Ϊ����ֱ�Ӳ���
	}
	else if (insert(ch, _root->_left))return true;//���������������ɹ����������
	//���������������ʧ�ܣ����Բ���������
	if (_root->_right == NULL) {
		_root->_right = new TreeNode<char>;
		_root->_right->assignAsLeaf(ch);
		NodeAmount++;
		return true;//���ӽڵ�Ϊ����ֱ�Ӳ���
	}
	else if (insert(ch, _root->_right))return true;//���������������ɹ����������
	return false;//��������������޷����룬�����ʧ��
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
	//printf("������ڵ����");
	//int Amount;
	//std::cin >> Amount;
	//prev = new char[Amount];
	//in = new char[Amount];
	//printf("\n������ǰ���������\n");
	//for (int i = 0; i < Amount; i++)prev[i - 1] = getchar();
	//while ((ch = getchar()) != '\n' && ch != EOF);//�������
	//printf("\n�����������������\n");
	//for (int i = 0; i < Amount; i++)in[i - 1] = getchar();
	//while ((ch = getchar()) != '\n' && ch != EOF);//�������
	char prev[5] = { '1','2','3','4','5'};
	char in[5] = { '2','1','4','3','5'};
	clear();
	if (ConstructByArray(prev, in, 5 , _root)) {
		std::cout << "����ɹ�" << std::endl;
		levelOrder();
		return true;
	}
	std::cout << "����ʧ��" << std::endl;
	return false;
}

bool charBT::ConstructByArray(char prev[], char in[],int length,TreeNode<char>*& subtree) {
	//����ʲô������ʽ��������ȿ϶���һ���ģ������ܽ����
	if (length < 1) {
		return false;
	}
	//ֻ��һ���ڵ㣬�Ǿ��Ǹ��ڵ�
	if (length == 1) {
		subtree = new TreeNode<char>;
		subtree->assignAsLeaf(prev[0]);
		return true;
	}
	//���������������Ҹ��ڵ�
	int index = -1;
	for (int i = 0; i < length; i++) {
		if (in[i] == prev[0]) {
			index = i;
			break;
		}
	}
	//û�ҵ���˵������������
	if (index == -1) {
		return false;
	}
	//�ҵ����ڵ���
	subtree = new TreeNode<char>;
	subtree->assignAsLeaf(prev[0]);
	/*subtree->data = prev[0];
	subtree->_left = NULL;
	subtree->_right = NULL;*/

	if (index > 0) //��ʱ����������
	{
		//�õ���������ǰ��������
		char* lChildPrev = new char[index];
		for (int i = 0; i < index; i++) {
			lChildPrev[i] = prev[i + 1];
		}
		//�õ�������������������
		char* lChildIn = new char[index];
		for (int i = 0; i < index; i++) {
			lChildIn[i] = in[i];
		}
		//ͨ���ݹ飬�õ��������ṹ
		ConstructByArray(lChildPrev, lChildIn, index, subtree->_left);
	}

	if(length - index - 1 > 0)//��ʱ����������
	{
		//�õ���������ǰ��������
		char* rChildPrev = new char[length - index - 1];
		for (int i = index; i < length; i++) {
			rChildPrev[i - index] = prev[i + 1];
		}
		//�õ�������������������
		char* rChildIn = new char[index];
		for (int i = index; i < length; i++) {
			rChildIn[i - index] = in[i + 1];
		}
		//ͨ���ݹ飬�õ��������ṹ
		ConstructByArray(rChildPrev, rChildIn, length - index - 1, subtree->_right);
	}

	
	//�õ������Ķ������ṹ
	return true;


}
