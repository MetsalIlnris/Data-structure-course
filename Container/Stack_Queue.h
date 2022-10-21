#pragma once

#include<cstdlib>
#include<iostream>

//basic type name: Item
template<typename>class Stack;
template<typename Item> 
std::ostream& operator<< (std::ostream& os, const Stack<Item>& S);
template<typename>class Queue;
template<typename Item>
std::ostream& operator<< (std::ostream& os, const Queue<Item>& Q);


template<typename Item> 
class LinkNode
{
public:
	Item data;
	LinkNode<Item>* link;

	friend class Stack<Item>;
	friend std::ostream& operator<< <Item>(std::ostream& os, const Stack<Item>& S);
};

//**********************************************
//
//                   Stack
//
//**********************************************

template<typename Item> 
class Stack
{
protected:
	int NodeAmount;
	LinkNode<Item>* bottom;
	LinkNode<Item>* top;

public:
	void clear(); //���ջ

	//constructor

	Stack();
	Stack(Stack& S);//copy constructor 
	~Stack();//destructor

	//member function

//	bool assign(Item item,int i = 1);//����i��Node��ֵ
	bool isempty() { return top == NULL; } //���stack�ǿյ��򷵻�true
	bool pop(); //������ɾ��һ��Ԫ��
	bool pop(Item& item); //����һ��Ԫ��
	virtual bool push(Item item); //ѹ��һ��Ԫ��
	int size() { return NodeAmount; }; //����Stack�е�Ԫ�ظ���

	//advanced member function options

	void merge(Stack<Item> S); //��S�ں���stack
//	void swap(); //��������stack
//	void unique(); //ɾ��stack���ظ���Ԫ��
//	void search(); //��ָ����������Ԫ��
//	void remove(); //��Stackɾ��Ԫ��
//	void remove_if(); //��ָ������ɾ��Ԫ�� 

	//iterator
//	void begin() //����ָ���һ��Ԫ�صĵ�����
//	void end() //����ĩβ�ĵ�����
//	void rbegin() //����ָ���һ��Ԫ�ص����������
//	void rend() //ָ��Stackĩβ�����������
//	void get_allocator() //����Stack��������

	//operator overloading

//	Stack & operator+(const Stack & S);
//	Stack & operator*(double n);

//	friend Stack & operator*(double n,Stack & n);
	friend std::ostream& operator<< <Item>(std::ostream& os, const Stack<Item>& S);

};

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item> 
Stack<Item>::Stack() {
	bottom = NULL;
	top = NULL;
	NodeAmount = 0;
}

template<typename Item> 
Stack<Item>::Stack(Stack& S) {
	bottom = NULL;
	top = NULL;
	NodeAmount = S.NodeAmount;
	if (S.isempty())return;
	Item tem;
	while(S.pop(tem))
		push(tem);

}

template<typename Item> 
Stack<Item>::~Stack() {
	clear();
}

template<typename Item> 
void Stack<Item>::clear() {
	 LinkNode<Item>* cur;
	while (top != NULL) {
		cur = top;
		top = top->link;
		delete cur;
	}
	bottom = NULL;
	NodeAmount = 0;
}

template<typename Item>
bool Stack<Item>::push(Item item) {
	LinkNode<Item>* tem = top;
	top = new LinkNode<Item>;
	if (tem == NULL)bottom = top;
	top->link = tem;
	top->data = item;
	NodeAmount++;
	return true;
}

template<typename Item>
bool Stack<Item>::pop() {
	if (isempty())return false;
	if (top == bottom) {
		clear();
	}
	else {
		LinkNode<Item>* tem = top;
		top = top->link;
		NodeAmount--;
		delete tem;
	}
	return true;
}

template<typename Item>
bool Stack<Item>::pop(Item& item) {
	if (isempty())return false;
	if (top == bottom) {
		item = top->data;
		clear();
	}
	else {
		LinkNode<Item>* tem = top;
		top = top->link;
		item = tem->data;
		NodeAmount--;
		delete tem;
	}
	return true;
}

//---------------------------------------������������������������
//advanced Member function implementation 
//---------------------------------------��������������������



template<typename Item> 
void Stack<Item>::merge(Stack<Item> S) {
	if (S.isempty())return;
	Item tem;
	NodeAmount += S.NodeAmount;
	while (S.pop(tem))
		push(tem);
}


//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item> 
std::ostream& operator<<(std::ostream& os, const Stack<Item>& S) {
	 LinkNode<Item>* cur;
	for (cur = S.top; cur != NULL; cur = cur->link) {
		os << cur->data << std::endl;
	}
	return os;
}
//**********************************************
//
//                   Queue
//
//**********************************************

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
		NodeAmount--;
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
		NodeAmount--;
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

