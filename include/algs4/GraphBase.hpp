#ifndef ALGS4_GRAPHBASE_HPP
#define ALGS4_GRAPHBASE_HPP


#include <cassert>
#include <cstddef>
#include <istream>
#include <ostream>
#include <ranges>
#include <vector>

namespace algs4 {
    template<typename EdgeType>
    class GraphBase {
    protected:
        int V_;                                   // number of vertices
        std::ptrdiff_t E_;                        // number of edges
        std::vector<std::vector<EdgeType> > adj_; // adjacency lists

        explicit GraphBase(int V) : V_(V), E_(0), adj_(V) { assert(V >= 0); }
        explicit GraphBase(std::istream &in);
        ~GraphBase() = default;
        GraphBase(const GraphBase &) = default;
        GraphBase &operator=(const GraphBase &) = default;
        GraphBase(GraphBase &&) noexcept = default;
        GraphBase &operator=(GraphBase &&) noexcept = default;

    public:
        int V() const { return V_; }
        auto E() const { return E_; }
        auto adj(int v) const & { return std::views::reverse(adj_[v]); }
    };
}

template<typename EdgeType>
algs4::GraphBase<EdgeType>::GraphBase(std::istream &in) : GraphBase([&in] {
    int i;
    in >> i;
    return i;
}()) {}

template<typename EdgeType>
std::ostream &operator<<(std::ostream &os, const algs4::GraphBase<EdgeType> &G) {
    os << G.V() << " vertices, " << G.E() << " edges" << std::endl;
    for (int v = 0; v < G.V(); ++v) {
        os << v << ": ";
        for (const EdgeType &w: G.adj(v)) os << w << " ";
        os << std::endl;
    }
    return os;
}


#endif //ALGS4_GRAPHBASE_HPP
