#ifndef BELLMANFORDSP_H
#define BELLMANFORDSP_H


#include "SP.h"
#include <vector>
#include <list>

class BellmanFordSP : public SP {
private:
    std::vector<bool> onQ;         // 顶点是否存在与队列中
    std::list<int> queue;          // 正在被放松的顶点
    int cost = 0;                  // relax()的调用次数
    std::list<DirectedEdge> cycle; // edgeTo[]表示的子图是否含有负权重环

    void onRelaxationSuccess(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

    void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;

    void findNegativeCycle();

public:
    BellmanFordSP(const EdgeWeightedDigraph &G, int s);

    bool hasNegativeCycle() const { return !cycle.empty(); }

    std::list<DirectedEdge> negativeCycle() const { return cycle; }
};


#endif //BELLMANFORDSP_H
