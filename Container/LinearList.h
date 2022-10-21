#ifndef LINEARLIST_H_
#define LINEARLIST_H_

//enum bool{false,true};

template<typename T>
class Linearlist {
public:
	Linearlist();
	~Linearlist();

	//const����������������޸��κγ�Ա����
	//=0��Ϊ���麯��

	virtual int Size()const = 0; //����������
	virtual int Length()const = 0; //�����
	virtual int Search(T& x)const = 0; //�ڱ�����������ֵx�����ر������
	virtual int Locate(int i)const = 0; //�ڱ��ж�λ��i��Ԫ��λ�ã����ر������
	virtual bool getData(int i, T& x)const = 0; //ȡ��i�������ֵ
	virtual void setData(int i, T& x) = 0; //�޸ĵ�i�������ֵ
	virtual bool Insert(int i, T& x) = 0; //�ڵ�i����������x
	virtual bool Remove(int i, T& x) = 0; //ɾ����i������ģ�ͨ��x����
	virtual bool IsEmpty()const = 0;
	virtual bool IsFull()const = 0;
	virtual void Sort() = 0; //����
	virtual void input() = 0; //����
	virtual void output() = 0; //���
//	virtual Linearlist<T> operator = (Linearlist<T>& L) = 0; //����
};

#endif
