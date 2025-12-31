#ifndef ALGS4_BELLMANFORDSP_HPP
#define ALGS4_BELLMANFORDSP_HPP


#include <list>
#include <vector>

#include "DirectedCycle.hpp"
#include "SP.hpp"

namespace algs4 {
    class BellmanFordSP : public SP {
    private:
        std::vector<bool> onQ;         // Is this vertex on the queue?
        std::list<int> queue;          // vertices being relaxed
        int cost = 0;                  // number of calls to relax()
        std::list<DirectedEdge> cycle; // negative cycle in edgeTo[]?

        void onRelaxationSuccess(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;
        void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;
        void findNegativeCycle();

    public:
        BellmanFordSP(const EdgeWeightedDigraph &G, int s);

        bool hasNegativeCycle() const { return !cycle.empty(); }
        std::list<DirectedEdge> negativeCycle() const { return cycle; }
    };
}

inline void algs4::BellmanFordSP::onRelaxationSuccess(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e,
                                                      int w) {
    if (!onQ[w]) {
        queue.push_back(w);
        onQ[w] = true;
    }
}

inline void algs4::BellmanFordSP::afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (cost++ % G.V() == 0)
        findNegativeCycle();
}

inline void algs4::BellmanFordSP::findNegativeCycle() {
    int V = edgeTo.size();
    EdgeWeightedDigraph spt(V);
    for (int v = 0; v < V; ++v) {
        if (edgeTo[v])
            spt.addEdge(*edgeTo[v]);
    }
    DirectedCycle cf(spt);
    cycle = cf.cycle();
}

inline algs4::BellmanFordSP::BellmanFordSP(const EdgeWeightedDigraph &G, int s) : SP(G, s), onQ(G.V()) {
    queue.push_back(s);
    onQ[s] = true;
    while (!queue.empty() && !hasNegativeCycle()) {
        int v = queue.front();
        queue.pop_front();
        onQ[v] = false;
        relax(G, v);
    }
}


#endif //ALGS4_BELLMANFORDSP_HPP
