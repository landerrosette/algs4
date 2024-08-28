#ifndef ALGS4_GRAPH_H
#define ALGS4_GRAPH_H


#include <forward_list>
#include <iostream>
#include <vector>

class Graph {
protected:
    const int V;                                // 顶点数目
    int E;                                      // 边的数目
    std::vector<std::forward_list<int>> adj;    // 邻接表

    static int readInt(std::istream &in);

public:
    Graph(int V) : V(V), E(0), adj(V) {}

    Graph(std::istream &in);

    int getV() const { return V; }

    int getE() const { return E; }

    void addEdge(int v, int w);

    std::forward_list<int> getAdj(int v) const { return adj[v]; }

    friend std::ostream &operator<<(std::ostream &os, const Graph &G);
};


#endif //ALGS4_GRAPH_H
