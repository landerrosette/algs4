#ifndef ALGS4_BELLMANFORDSP_HPP
#define ALGS4_BELLMANFORDSP_HPP


#include <queue>
#include <vector>

#include "DirectedCycle.hpp"
#include "SP.hpp"

namespace algs4 {
    class BellmanFordSP : public SP {
    private:
        std::vector<bool> onQ;           // Is this vertex on the queue?
        std::queue<int> queue;           // vertices being relaxed
        int cost = 0;                    // number of calls to relax()
        std::vector<DirectedEdge> cycle; // negative cycle in edgeTo[]?

        void onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;
        void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) override;
        void findNegativeCycle();

    public:
        BellmanFordSP(const EdgeWeightedDigraph &G, int s);

        bool hasNegativeCycle() const { return !cycle.empty(); }
        std::vector<DirectedEdge> negativeCycle() const { return cycle; }
    };
}

inline void algs4::BellmanFordSP::onEdgeRelaxed(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (!onQ[w]) {
        queue.push(w);
        onQ[w] = true;
    }
}

inline void algs4::BellmanFordSP::afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {
    if (cost++ % G.V() == 0)
        findNegativeCycle();
}

inline void algs4::BellmanFordSP::findNegativeCycle() {
    int V = static_cast<int>(std::ssize(edgeTo));
    EdgeWeightedDigraph spt(V);
    for (int v = 0; v < V; ++v) {
        if (edgeTo[v])
            spt.addEdge(edgeTo[v]);
    }
    DirectedCycle cf(spt);
    auto c = cf.cycle();
    cycle = {c.begin(), c.end()};
}

inline algs4::BellmanFordSP::BellmanFordSP(const EdgeWeightedDigraph &G, int s) : SP(G, s), onQ(G.V()) {
    queue.push(s);
    onQ[s] = true;
    while (!queue.empty() && !hasNegativeCycle()) {
        int v = queue.front();
        queue.pop();
        onQ[v] = false;
        relax(G, v);
    }
}


#endif //ALGS4_BELLMANFORDSP_HPP
