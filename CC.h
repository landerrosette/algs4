#ifndef ALGS4_CC_H
#define ALGS4_CC_H


#include "Graph.h"

class CC {
protected:
    bool *marked;
    int *id;
    int count = 0;

    void dfs(const Graph &G, int v);

public:
    CC(const Graph &G);

    bool connected(int v, int w) const { return id[v] == id[w]; }

    int getId(int v) const { return id[v]; }

    int getCount() const { return count; }

    ~CC() {
        delete[] marked;
        delete[] id;
    };
};


#endif //ALGS4_CC_H
