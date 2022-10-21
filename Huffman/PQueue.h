#pragma once


/*��˳��ṹ�������ȼ�����
���ȼ�����<��>�ж�
����Item�������������غ����ȼ��ıȽϷ���*/

#include<cstdlib>
#include<iostream>

#define DefaultSize 300;

//basic type name: Item
template<typename>class PQueue;
template<typename Item> 
std::ostream& operator<< (std::ostream& os, const PQueue<Item>& PQ);

template<typename Item> 
class PQueue
{
protected:
	Item* PQElem;
	int currentSize; //��ǰԪ������
	int maxSize;		 //Ԫ������

public:
	void clear() { currentSize = 0; } //��ն���

	//constructor

	PQueue(int sz = 300);
	PQueue(PQueue& PQ);//copy constructor 
	~PQueue() { delete[] PQElem; };//destructor

	//member function

	bool isempty() { return currentSize; } //���queue�ǿյ��򷵻�true
	bool isfull() { return currentSize == maxSize; } //���queue�������򷵻�true
	bool pop(); //������ɾ��һ��Ԫ��
	bool pop(Item& item); //����һ��Ԫ��
	virtual bool push(Item item); //ѹ��һ��Ԫ��
	int size() { return currentSize; }; //����PQueue�е�Ԫ�ظ���
	Item check_head() {  return PQElem[0]; };

	//operator overloading

	friend std::ostream& operator<< <Item>(std::ostream& os, const PQueue<Item>& PQ);

};

//---------------------------------------
//Member function implementation 
//---------------------------------------

template<typename Item> 
PQueue<Item>::PQueue(int sz) {
	maxSize = sz;
	PQElem = new Item[sz];
	currentSize = 0;
}

template<typename Item> 
PQueue<Item>::PQueue(PQueue& PQ) {
	delete[] PQElem;
	maxSize = PQ.maxSize;
	PQElem = new Item[PQ.maxSize];
	currentSize = 0;
}

template<typename Item>
bool PQueue<Item>::push(Item item) {
	if (!isfull()) {
		int i, k;
		for (i = 0; i < currentSize; i++) {
			if (PQElem[i] < item)break;
		}
		for (k = currentSize - 1; k >= i;k--) {
			PQElem[k + 1] = PQElem[k];
		}
		PQElem[i] = item;
		currentSize++;
		return true;
	}
	else return false;
}

template<typename Item>
bool PQueue<Item>::pop() {
	if (currentSize == 0)return false;
	else {
		for (int i = 0; i < currentSize; i++) {
			PQElem[i] = PQElem[i + 1];
		}
		currentSize--;
	}
	return true;
}

template<typename Item>
bool PQueue<Item>::pop(Item& item) {
	if (currentSize == 0)return false;
	else {
		item = PQElem[--currentSize];
		for (int i = 0; i < currentSize; i++) {
			PQElem[i] = PQElem[i + 1];
		}
	}
	return true;
}

//---------------------------------------
//friend function implementation
//---------------------------------------

template<typename Item> 
std::ostream& operator<<(std::ostream& os, const PQueue<Item>& PQ) {
	for (int i = 0; i < PQ.currentSize; i++) {
		os << PQ.PQElem[i] << ' ';
	}
	return os;
}



