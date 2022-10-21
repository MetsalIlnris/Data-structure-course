#pragma once
#include <iostream>
#include"Stack_Queue.h"

using namespace std;
template<typename,typename>class Graph;
template<typename vertextype, typename arctype>
ostream& operator<<(ostream& os, const Graph<vertextype, arctype>& G);

#define MAXVERTEX 50   //最大顶点数
#define MAXDISTANCE 65535  //最大边长
//typedef char vertextype;    //定义顶点的存储类型
//typedef int arctype;    //定义边的权值类型

template<typename arctype>
struct ArcNode  //边表节点
{
    int adjvex; //邻接点域，存储该顶点对应的下标
    arctype wigth;  //用于存储权值
    struct ArcNode* next; //链域，指向下一个邻接点
};

template<typename vertextype,typename arctype>
struct VertexNode   //顶点表节点
{
    vertextype data;    //存储顶点数据的信息
    ArcNode<arctype>* firstarc;  //边表头指针
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

//建立图的邻接表
template<typename vertextype, typename arctype>
void Graph<vertextype, arctype>::CreateByCin()
{
    ArcNode<arctype>* e;
    cout << "请输入当前图的顶点数与边数" << endl;
    cin >> numvertex; //输入当前图的顶点数
    cin >> numarc;    //输入当前图的边数
    for (int i = 0; i < numvertex; i++)    //建立顶点表
    {
        cout << "请输入第" << i << "顶点的数据" << endl;
        cin >> VertexList[i].data;   //输入顶点信息
        VertexList[i].firstarc = NULL;   //将表边指针置为空
    }
    for (int k = 0; k < numarc; k++)
    {
        int i, j, w;
        cout << "请输入第" << k << "条边上两个顶点与该边上的权重" << endl;
        cin >> i >> j >> w; //输入边两边的顶点和边上的权重
        e = new ArcNode<arctype>;   //创建一个表边节点指针
        e->adjvex = j;
        e->wigth = w;
        e->next = VertexList[i].firstarc;
        VertexList[i].firstarc = e;
        //因为是无向图，彼此相对称
        e = new ArcNode<arctype>;   //创建一个表边节点指针(因为是无向图所以两向都要指)
        e->adjvex = i;
        e->wigth = w;
        e->next = VertexList[j].firstarc;
        VertexList[j].firstarc = e;
    }
}

template<typename vertextype, typename arctype>
bool Graph<vertextype,arctype>::dfs(int start) {
    cout << "深度优先遍历：" << endl;
    Stack<VertexNode<vertextype, arctype>*> vertexCac;//用以储存遍历路径
    bool Done[MAXVERTEX]; //记录某个点是否被访问过
    for (int i = 0; i < numvertex; i++)Done[i] = 0;
    Done[start] = 1;//第一个默认是访问过的
    vertexCac.push(&VertexList[start]);
    VertexNode<vertextype, arctype>* curV; ArcNode<arctype>* curA;//当前访问的点与边

    while (!vertexCac.isempty()) {
        vertexCac.pop(curV);//从待命点集中取出一个访问
        cout << "当前访问点数据：" << curV->data << std::endl;
        for (curA = curV->firstarc; curA != NULL; curA = curA->next) {
            if (Done[curA->adjvex] == 0)//还未访问过
            {
                vertexCac.push(&VertexList[curA->adjvex]);
                Done[curA->adjvex] = 1;
            }
        }//将所有与当前访问中的点邻接的未访问点push入栈
    }
    cout << "访问完毕！" << endl;
    return true;
}

template<typename vertextype, typename arctype>
bool Graph<vertextype, arctype>::bfs(int start) {
    cout << "广度优先遍历：" << endl;
    Queue<VertexNode<vertextype, arctype>*> vertexCac;//用以储存遍历路径
    bool Done[MAXVERTEX]; //记录某个点是否被访问过
    for (int i = 0; i < numvertex; i++)Done[i] = 0;
    Done[start] = 1;//第一个默认是访问过的
    vertexCac.push(&VertexList[start]);
    VertexNode<vertextype, arctype>* curV; ArcNode<arctype>* curA;//当前访问的点与边

    while (!vertexCac.isempty()) {
        vertexCac.pop(curV);//从待命点集中取出一个访问
        cout << "当前访问点数据：" << curV->data << std::endl;
        for (curA = curV->firstarc; curA != NULL; curA = curA->next) {
            if (Done[curA->adjvex] == 0)//还未访问过
            {
                vertexCac.push(&VertexList[curA->adjvex]);
                Done[curA->adjvex] = 1;
            }
        }//将所有与当前访问中的点邻接的未访问点push入队
    }
    cout << "访问完毕！" << endl;
    return true;
}

template<typename vertextype, typename arctype>
bool Graph<vertextype, arctype>::MiniSpanTree_Prim(int start) {
    int parent[MAXVERTEX];//储存生成树结点的父节点
    vertextype distance[MAXVERTEX];//储存各点到当前生成树的距离

    //初始化
    for (int i = 0; i < numvertex; i++) {
        distance[i] = MAXDISTANCE;//默认无法抵达
    }
    distance[start] = -1;//初始点设置为已访问
    parent[start] = start;//设定生成树根节点（出发位置）的父节点为节点本身
    ArcNode<arctype>* cur = VertexList[start].firstarc;
    while (cur != NULL) {
        distance[cur->adjvex] = cur->wigth;
        parent[cur->adjvex] = start;
        cur = cur->next;
    }
    //生成
    for (int i = 0; i < numvertex-1; i++) {
        int minVertex = 0, minDistance = MAXDISTANCE;
        for (int k = 0; k < numvertex; k++) {
            if (distance[k] != -1 && distance[k] < minDistance) {
                minVertex = k;
                minDistance = distance[k];
            }
        }//找到未访问的点中距离生成树最短的点
        distance[minVertex] = -1;//设置为已访问
        for (cur = VertexList[minVertex].firstarc; cur != NULL; cur = cur->next) {
            if (cur->wigth < distance[cur->adjvex]) {
                distance[cur->adjvex] = cur->wigth;
                parent[cur->adjvex] = minVertex;
            }//若当前点与最新点之间的距离小于表中显示的距离(表中显示的距离为-1则自动跳过)则更新距离表
        }
    }
    cout << "最小生成树构建完毕！" << endl;
    cout << "        parent" << endl;
    for (int i = 0; i < numvertex; i++)  cout << "vertex " << i << ":" << parent[i] << endl;
    return true;
}

//重载ostream
template<typename vertextype, typename arctype>
ostream& operator<<(ostream& os,const Graph<vertextype, arctype>& G)
{
    for (int i = 0; i < G.numvertex; i++)
    {
        ArcNode<arctype>* p = G.VertexList[i].firstarc;
        cout << "第"<<i<<"个点：数据" << G.VertexList[i].data << '\t'<<"边集：";
        while (p)
        {
            cout << p->adjvex << ' ' << p->wigth << '\t';
            p = p->next;
        }
        cout << endl;
    }
    return os;
}