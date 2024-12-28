#ifndef ALGS4_DIRECTEDCYCLE_H
#define ALGS4_DIRECTEDCYCLE_H


#include <list>
#include "GraphBase.h"
#include <vector>
#include "DirectedEdge.h"
#include <optional>
#include <type_traits>

template<typename T>
class DirectedCycle {
private:
    std::vector<bool> marked;
    std::vector<std::optional<T> > edgeTo;
    std::list<T> cycle_;
    std::vector<bool> onStack; // vertices on recursive call stack

    void dfs(const GraphBase<T> &G, int v);

public:
    explicit DirectedCycle(const GraphBase<T> &G);

    bool hasCycle() const { return !cycle_.empty(); }

    std::list<T> cycle() const { return cycle_; }
};

template<typename T>
void DirectedCycle<T>::dfs(const GraphBase<T> &G, int v) {
    onStack[v] = true;
    marked[v] = true;
    for (const auto &e: G.adj(v)) {
        int w;
        if constexpr (std::is_same_v<std::decay_t<decltype(e)>, DirectedEdge>) w = e.to();
        else w = e;
        if (hasCycle()) {
            return;
        } else if (!marked[w]) {
            edgeTo[w] = e;
            dfs(G, w);
        } else if (onStack[w]) {
            if constexpr (std::is_same_v<std::decay_t<decltype(e)>, DirectedEdge>) {
                auto x = e;
                for (; x.from() != w; x = *edgeTo[x.from()]) {
                    cycle_.push_front(x);
                }
                cycle_.push_front(x);
            } else {
                for (int x = v; x != w; x = *edgeTo[x]) {
                    cycle_.push_front(x);
                }
                cycle_.push_front(w);
                cycle_.push_front(v);
            }
        }
    }
    onStack[v] = false;
}

template<typename T>
DirectedCycle<T>::DirectedCycle(const GraphBase<T> &G) : marked(G.V()), edgeTo(G.V()), onStack(G.V()) {
    for (int v = 0; v < G.V(); ++v) {
        if (!marked[v]) dfs(G, v);
    }
}


#endif //ALGS4_DIRECTEDCYCLE_H
