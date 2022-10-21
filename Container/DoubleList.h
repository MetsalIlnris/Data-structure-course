#pragma once

#include<iostream>
//#include"LinearList.h" 
#include<cstdlib>

//basic type name: Item
template<typename>class List;
template<typename Item>
std::ostream & operator<< (std::ostream & os,const List<Item> & L);


template<typename Item>
struct LinkNode{
	Item data;
	LinkNode<Item>* lLink;
	LinkNode<Item>* rLink;
};

template<typename Item> 
class List 
{
protected:
	struct LinkNode<Item> * head;
	struct LinkNode<Item> * rear;
	int NodeAmount;
	
public:
	void clear(); //������� 
	
	//constructor
	
	List(); 
	List(List & L);//copy constructor 
	~List();//destructor
	
	//member function
	
//	bool assign(Item item,int i = 1);//����i��Node��ֵ
	bool isempty(){return head == rear;} //���list�ǿյ��򷵻�true
//	void insert(); //����һ��Ԫ�ص�list��
	bool pop_back();
	bool pop_back(Item & item); //�������һ��Ԫ��
	bool pop_front();
	bool pop_front(Item & item); //������һ��Ԫ��
	bool push_back(Item item); //��list��ĩβ���һ��Ԫ��
	bool push_front(Item item); //��list��ͷ�����һ��Ԫ��
	int size() {return NodeAmount;}; //����list�е�Ԫ�ظ���
	
	//advanced member function options
	
	void cat(List<Item> L); //��L�����ĩβ 
//	void sort(); //��list����
//	void swap(); //��������list
//	void unique(); //ɾ��list���ظ���Ԫ��
//	void reverse(); //��list��Ԫ�ص�ת
//	void search(); //��ָ����������Ԫ��
//	void remove(); //��listɾ��Ԫ��
//	void remove_if(); //��ָ������ɾ��Ԫ�� 
	
	//iterator
//	void begin() //����ָ���һ��Ԫ�صĵ�����
//	void end() //����ĩβ�ĵ�����
//	void rbegin() //����ָ���һ��Ԫ�ص����������
//	void rend() //ָ��listĩβ�����������
//	void get_allocator() //����list��������
	
	//operator overloading
	
//	List & operator+(const List & L);
//	List & operator*(double n);
	
//	friend List & operator*(double n,List & n);
	friend std::ostream & operator<< <Item>(std::ostream & os,const List<Item> & L);

}; 

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item>
List<Item>::List(){
	head = new LinkNode<Item>;
	head->data = NULL;
	head->lLink = NULL;
	head->rLink = NULL;
	rear = head;
	NodeAmount = 0;
}

template<typename Item>
List<Item>::List(List & L){
	head = new LinkNode<Item>;
	head->data = NULL;
	head->lLink = NULL;
	head->rLink = NULL;
	rear = head;
	if (!L.isempty()) {
		struct LinkNode<Item>* now = L.head->rLink;
		while (now!=NULL)
		{
			push_back(now->data);
			now = now->rLink;
		}
		
	}
	NodeAmount = L.NodeAmount;
}

template<typename Item>
List<Item>::~List(){
	clear();
}

template<typename Item>
void List<Item>::clear(){
	struct LinkNode<Item> * now;
	while (head != NULL) {
		now = head;
		head = head->rLink;
		delete now;
	}
	rear = NULL;
	NodeAmount = 0;
}

template<typename Item>
bool List<Item>::pop_back() {
	if (isempty())return false;
	rear = rear->lLink;
	rear->rLink = NULL;
	delete rear->rLink;
	NodeAmount--;
	return true;
}

template<typename Item>
bool List<Item>::pop_back(Item & item){
	if (isempty())return false;
	rear = rear->lLink;
	rear->rLink = NULL;
	delete rear->rLink;
	NodeAmount--;
	return true;
}

template<typename Item>
bool List<Item>::pop_front() {
	if (isempty())return false;
	LinkNode<Item>* cur = head->rLink;
	head->rLink = cur->rLink;
	if (cur->rLink != NULL)cur->rLink->lLink = head;
	delete cur;
	NodeAmount--;
	return true;
}

template<typename Item>
bool List<Item>::pop_front(Item & item){
	if (isempty())return false;
	LinkNode<Item>* cur = head->rLink;
	head->rLink = cur->rLink;
	if (cur->rLink != NULL)cur->rLink->lLink = head;
	else rear = head;
	item = cur->data;
	delete cur;
	return true;
}

template<typename Item>
bool List<Item>::push_back(Item item){
	rear->rLink = new LinkNode<Item>;
	rear->rLink->lLink = rear;
	rear = rear->rLink;
	rear->data = item;
	rear->rLink = NULL;
	NodeAmount++;
	return true;
}

template<typename Item>
bool List<Item>::push_front(Item item){
	LinkNode<Item>* cur = head->rLink;
	head->rLink = new LinkNode<Item>;
	head->rLink->lLink = head;
	head->rLink->rLink = cur;
	head->rLink->data = item;
	NodeAmount++;
	return true;
}


//---------------------------------------������������������������
//advanced Member function implementation 
//---------------------------------------��������������������



template<typename Item>
void List<Item>::cat(List<Item> L){
	Item tem;
	while(L.pop_front(tem)){
		push_back(tem);
	}
}

//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item>
std::ostream & operator<<(std::ostream & os,const List<Item> & L){
	struct LinkNode<Item> * cur;
	for(cur = L.head->rLink;cur != NULL;cur = cur->rLink){
		os<<cur->data<<std::endl;
	}
	return os;
}


