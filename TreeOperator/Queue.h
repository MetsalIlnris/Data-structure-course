#pragma once

#include<cassert>
#include<iostream>
#include<cstdlib>

//basic type name: Item
template<typename>class Queue;
template<typename Item>
std::ostream& operator<< (std::ostream& os, const Queue<Item>& Q);


template<typename Item>
class LinkNode
{
public:
	Item data;
	LinkNode<Item>* link;

	friend class Queue<Item>;
	friend std::ostream& operator<< <Item>(std::ostream& os, const Queue<Item>& Q);
};

template<typename Item>
class Queue
{
protected:
	int NodeAmount;
	LinkNode<Item>* rear;
	LinkNode<Item>* head;

public:
	void clear(); //��ն���

	//constructor

	Queue();
	Queue(Queue& Q);//copy constructor 
	~Queue();//destructor

	//member function

	bool isempty() { return head == NULL; } //���queue�ǿյ��򷵻�true
	bool pop(); //������ɾ��һ��Ԫ��
	bool pop(Item& item); //����һ��Ԫ��
	virtual bool push(Item item); //ѹ��һ��Ԫ��
	int size() { return NodeAmount; }; //����Queue�е�Ԫ�ظ���
	int check_rear() { if (isempty())return 0; return rear->data; };
	int check_head() { if (isempty())return 0; return head->data; };
	//advanced member function options

	void merge(Queue<Item> Q); //��Q�ں���queue
//	void swap(); //��������queue
//	void unique(); //ɾ��queue���ظ���Ԫ��
//	void search(); //��ָ����������Ԫ��
//	void remove(); //��Queueɾ��Ԫ��
//	void remove_if(); //��ָ������ɾ��Ԫ�� 

	//iterator
//	void begin() //����ָ���һ��Ԫ�صĵ�����
//	void end() //����ĩβ�ĵ�����
//	void rbegin() //����ָ���һ��Ԫ�ص����������
//	void rend() //ָ��Queueĩβ�����������
//	void get_allocator() //����Queue��������

	//operator overloading

//	Queue & operator+(const Queue & Q);
//	Queue & operator*(double n);

//	friend Queue & operator*(double n,Queue & n);
	friend std::ostream& operator<< <Item>(std::ostream& os, const Queue<Item>& Q);

};

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item>
Queue<Item>::Queue() {
	rear = NULL;
	head = NULL;
	NodeAmount = 0;
}

template<typename Item>
Queue<Item>::Queue(Queue& Q) {
	rear = NULL;
	head = NULL;
	NodeAmount = Q.NodeAmount;
	if (Q.isempty())return;
	Item tem;
	while (Q.pop(tem))
		push(tem);

}

template<typename Item>
Queue<Item>::~Queue() {
	clear();
}

template<typename Item>
void Queue<Item>::clear() {
	LinkNode<Item>* cur;
	while (head != NULL) {
		cur = head;
		head = head->link;
		delete cur;
	}
	rear = NULL;
	NodeAmount = 0;
}

template<typename Item>
bool Queue<Item>::push(Item item) {
	LinkNode<Item>* tem = rear;
	rear = new LinkNode<Item>;
	if (tem == NULL)head = rear;
	else tem->link = rear;
	rear->data = item;
	rear->link = NULL;
	NodeAmount++;
	return true;
}

template<typename Item>
bool Queue<Item>::pop() {
	if (isempty())return false;
	if (head == rear) {
		clear();
	}
	else {
		LinkNode<Item>* tem = head;
		head = head->link;
		delete tem;
	}
	return true;
}

template<typename Item>
bool Queue<Item>::pop(Item& item) {
	if (isempty())return false;
	if (head == rear) {
		item = head->data;
		clear();
	}
	else {
		LinkNode<Item>* tem = head;
		head = head->link;
		item = tem->data;
		delete tem;
	}
	return true;
}

//---------------------------------------������������������������
//advanced Member function implementation 
//---------------------------------------��������������������



template<typename Item>
void Queue<Item>::merge(Queue<Item> Q) {
	if (Q.isempty())return;
	Item tem;
	NodeAmount += Q.NodeAmount;
	while (Q.pop(tem))
		push(tem);
}


//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item>
std::ostream& operator<<(std::ostream& os, const Queue<Item>& Q) {
	LinkNode<Item>* cur;
	for (cur = Q.head; cur != NULL; cur = cur->link) {
		os << cur->data << std::endl;
	}
	return os;
}
