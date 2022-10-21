#pragma once
#include <iostream>
#include"Stack_Queue.h"

using namespace std;
template<typename,typename>class Graph;
template<typename vertextype, typename arctype>
ostream& operator<<(ostream& os, const Graph<vertextype, arctype>& G);

#define MAXVERTEX 50   //��󶥵���
#define MAXDISTANCE 65535  //���߳�
//typedef char vertextype;    //���嶥��Ĵ洢����
//typedef int arctype;    //����ߵ�Ȩֵ����

template<typename arctype>
struct ArcNode  //�߱�ڵ�
{
    int adjvex; //�ڽӵ��򣬴洢�ö����Ӧ���±�
    arctype wigth;  //���ڴ洢Ȩֵ
    struct ArcNode* next; //����ָ����һ���ڽӵ�
};

template<typename vertextype,typename arctype>
struct VertexNode   //�����ڵ�
{
    vertextype data;    //�洢�������ݵ���Ϣ
    ArcNode<arctype>* firstarc;  //�߱�ͷָ��
};

template<typename vertextype, typename arctype>
class Graph {
public:
    Graph() { numvertex = 0; numarc = 0; }
    ~Graph() {}
    void CreateByCin();
    bool dfs(int start);
    bool bfs(int start);
    bool MiniSpanTree_Prim(int start);
private:
    VertexNode<vertextype,arctype> VertexList[MAXVERTEX];
    int numvertex;
    int numarc;

    friend ostream& operator<< <vertextype, arctype>(ostream& os, const Graph& G);
};

//����ͼ���ڽӱ�
template<typename vertextype, typename arctype>
void Graph<vertextype, arctype>::CreateByCin()
{
    ArcNode<arctype>* e;
    cout << "�����뵱ǰͼ�Ķ����������" << endl;
    cin >> numvertex; //���뵱ǰͼ�Ķ�����
    cin >> numarc;    //���뵱ǰͼ�ı���
    for (int i = 0; i < numvertex; i++)    //���������
    {
        cout << "�������" << i << "���������" << endl;
        cin >> VertexList[i].data;   //���붥����Ϣ
        VertexList[i].firstarc = NULL;   //�����ָ����Ϊ��
    }
    for (int k = 0; k < numarc; k++)
    {
        int i, j, w;
        cout << "�������" << k << "����������������ñ��ϵ�Ȩ��" << endl;
        cin >> i >> j >> w; //��������ߵĶ���ͱ��ϵ�Ȩ��
        e = new ArcNode<arctype>;   //����һ����߽ڵ�ָ��
        e->adjvex = j;
        e->wigth = w;
        e->next = VertexList[i].firstarc;
        VertexList[i].firstarc = e;
        //��Ϊ������ͼ���˴���Գ�
        e = new ArcNode<arctype>;   //����һ����߽ڵ�ָ��(��Ϊ������ͼ��������Ҫָ)
        e->adjvex = i;
        e->wigth = w;
        e->next = VertexList[j].firstarc;
        VertexList[j].firstarc = e;
    }
}

template<typename vertextype, typename arctype>
bool Graph<vertextype,arctype>::dfs(int start) {
    cout << "������ȱ�����" << endl;
    Stack<VertexNode<vertextype, arctype>*> vertexCac;//���Դ������·��
    bool Done[MAXVERTEX]; //��¼ĳ�����Ƿ񱻷��ʹ�
    for (int i = 0; i < numvertex; i++)Done[i] = 0;
    Done[start] = 1;//��һ��Ĭ���Ƿ��ʹ���
    vertexCac.push(&VertexList[start]);
    VertexNode<vertextype, arctype>* curV; ArcNode<arctype>* curA;//��ǰ���ʵĵ����

    while (!vertexCac.isempty()) {
        vertexCac.pop(curV);//�Ӵ����㼯��ȡ��һ������
        cout << "��ǰ���ʵ����ݣ�" << curV->data << std::endl;
        for (curA = curV->firstarc; curA != NULL; curA = curA->next) {
            if (Done[curA->adjvex] == 0)//��δ���ʹ�
            {
                vertexCac.push(&VertexList[curA->adjvex]);
                Done[curA->adjvex] = 1;
            }
        }//�������뵱ǰ�����еĵ��ڽӵ�δ���ʵ�push��ջ
    }
    cout << "������ϣ�" << endl;
    return true;
}

template<typename vertextype, typename arctype>
bool Graph<vertextype, arctype>::bfs(int start) {
    cout << "������ȱ�����" << endl;
    Queue<VertexNode<vertextype, arctype>*> vertexCac;//���Դ������·��
    bool Done[MAXVERTEX]; //��¼ĳ�����Ƿ񱻷��ʹ�
    for (int i = 0; i < numvertex; i++)Done[i] = 0;
    Done[start] = 1;//��һ��Ĭ���Ƿ��ʹ���
    vertexCac.push(&VertexList[start]);
    VertexNode<vertextype, arctype>* curV; ArcNode<arctype>* curA;//��ǰ���ʵĵ����

    while (!vertexCac.isempty()) {
        vertexCac.pop(curV);//�Ӵ����㼯��ȡ��һ������
        cout << "��ǰ���ʵ����ݣ�" << curV->data << std::endl;
        for (curA = curV->firstarc; curA != NULL; curA = curA->next) {
            if (Done[curA->adjvex] == 0)//��δ���ʹ�
            {
                vertexCac.push(&VertexList[curA->adjvex]);
                Done[curA->adjvex] = 1;
            }
        }//�������뵱ǰ�����еĵ��ڽӵ�δ���ʵ�push���
    }
    cout << "������ϣ�" << endl;
    return true;
}

template<typename vertextype, typename arctype>
bool Graph<vertextype, arctype>::MiniSpanTree_Prim(int start) {
    int parent[MAXVERTEX];//�������������ĸ��ڵ�
    vertextype distance[MAXVERTEX];//������㵽��ǰ�������ľ���

    //��ʼ��
    for (int i = 0; i < numvertex; i++) {
        distance[i] = MAXDISTANCE;//Ĭ���޷��ִ�
    }
    distance[start] = -1;//��ʼ������Ϊ�ѷ���
    parent[start] = start;//�趨���������ڵ㣨����λ�ã��ĸ��ڵ�Ϊ�ڵ㱾��
    ArcNode<arctype>* cur = VertexList[start].firstarc;
    while (cur != NULL) {
        distance[cur->adjvex] = cur->wigth;
        parent[cur->adjvex] = start;
        cur = cur->next;
    }
    //����
    for (int i = 0; i < numvertex-1; i++) {
        int minVertex = 0, minDistance = MAXDISTANCE;
        for (int k = 0; k < numvertex; k++) {
            if (distance[k] != -1 && distance[k] < minDistance) {
                minVertex = k;
                minDistance = distance[k];
            }
        }//�ҵ�δ���ʵĵ��о�����������̵ĵ�
        distance[minVertex] = -1;//����Ϊ�ѷ���
        for (cur = VertexList[minVertex].firstarc; cur != NULL; cur = cur->next) {
            if (cur->wigth < distance[cur->adjvex]) {
                distance[cur->adjvex] = cur->wigth;
                parent[cur->adjvex] = minVertex;
            }//����ǰ�������µ�֮��ľ���С�ڱ�����ʾ�ľ���(������ʾ�ľ���Ϊ-1���Զ�����)����¾����
        }
    }
    cout << "��С������������ϣ�" << endl;
    cout << "        parent" << endl;
    for (int i = 0; i < numvertex; i++)  cout << "vertex " << i << ":" << parent[i] << endl;
    return true;
}

//����ostream
template<typename vertextype, typename arctype>
ostream& operator<<(ostream& os,const Graph<vertextype, arctype>& G)
{
    for (int i = 0; i < G.numvertex; i++)
    {
        ArcNode<arctype>* p = G.VertexList[i].firstarc;
        cout << "��"<<i<<"���㣺����" << G.VertexList[i].data << '\t'<<"�߼���";
        while (p)
        {
            cout << p->adjvex << ' ' << p->wigth << '\t';
            p = p->next;
        }
        cout << endl;
    }
    return os;
}