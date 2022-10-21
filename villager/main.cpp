#include"Graph_AdjacencyList.h"

int main() {
	Graph<int, int> G;
	G.CreateByCin();
	cout << G;
	G.MiniSpanTree_Prim(0);
}