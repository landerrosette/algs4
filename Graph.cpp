#include "Graph.h"

Graph::Graph(std::istream &in) : Graph([](std::istream &in) -> int {
    int i;
    in >> i;
    return i;
}(in)) {
    int E;
    in >> E;
    for (int i = 0; i < E; ++i) {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

void Graph::addEdge(int v, int w) {
    adj[v].push_front(w);
    adj[w].push_front(v);
    ++E;
}
