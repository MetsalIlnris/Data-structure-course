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
	void clear(); //清空栈

	//constructor

	Stack();
	Stack(Stack& S);//copy constructor 
	~Stack();//destructor

	//member function

//	bool assign(Item item,int i = 1);//给第i个Node赋值
	bool isempty() { return top == NULL; } //如果stack是空的则返回true
	bool pop(); //弹出并删除一个元素
	bool pop(Item& item); //弹出一个元素
	virtual bool push(Item item); //压入一个元素
	int size() { return NodeAmount; }; //返回Stack中的元素个数

	//advanced member function options

	void merge(Stack<Item> S); //将S融合入stack
//	void swap(); //交换两个stack
//	void unique(); //删除stack中重复的元素
//	void search(); //按指定条件搜索元素
//	void remove(); //从Stack删除元素
//	void remove_if(); //按指定条件删除元素 

	//iterator
//	void begin() //返回指向第一个元素的迭代器
//	void end() //返回末尾的迭代器
//	void rbegin() //返回指向第一个元素的逆向迭代器
//	void rend() //指向Stack末尾的逆向迭代器
//	void get_allocator() //返回Stack的配置器

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

//---------------------------------------————————————
//advanced Member function implementation 
//---------------------------------------——————————



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
	void clear(); //清空队列

	//constructor

	Queue();
	Queue(Queue& Q);//copy constructor 
	~Queue();//destructor

	//member function

	bool isempty() { return head == NULL; } //如果queue是空的则返回true
	bool pop(); //弹出并删除一个元素
	bool pop(Item& item); //弹出一个元素
	virtual bool push(Item item); //压入一个元素
	int size() { return NodeAmount; }; //返回Queue中的元素个数
	int check_rear() { if (isempty())return 0; return rear->data; };
	int check_head() { if (isempty())return 0; return head->data; };
	//advanced member function options

	void merge(Queue<Item> Q); //将Q融合入queue
//	void swap(); //交换两个queue
//	void unique(); //删除queue中重复的元素
//	void search(); //按指定条件搜索元素
//	void remove(); //从Queue删除元素
//	void remove_if(); //按指定条件删除元素 

	//iterator
//	void begin() //返回指向第一个元素的迭代器
//	void end() //返回末尾的迭代器
//	void rbegin() //返回指向第一个元素的逆向迭代器
//	void rend() //指向Queue末尾的逆向迭代器
//	void get_allocator() //返回Queue的配置器

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

//---------------------------------------————————————
//advanced Member function implementation 
//---------------------------------------——————————



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

