#ifndef ALGS4_PATHS_HPP
#define ALGS4_PATHS_HPP

#include <algorithm>
#include <cassert>
#include <vector>

#include "Graph.hpp"

namespace algs4 {
    class Paths {
    protected:
        std::vector<bool> marked_; // Has dfs() been called for this vertex?
        std::vector<int> edgeTo_;  // last vertex on known path for this vertex
        int s_;                    // source

        constexpr Paths(const Graph &G, int s);

        constexpr Paths(const Paths &) = default;
        constexpr Paths &operator=(const Paths &) = default;
        constexpr Paths(Paths &&) noexcept = default;
        constexpr Paths &operator=(Paths &&) noexcept = default;

    public:
        virtual constexpr ~Paths() = default;

        constexpr bool hasPathTo(int v) const { return marked_[v]; }
        constexpr std::vector<int> pathTo(int v) const;
    };
}

constexpr algs4::Paths::Paths(const Graph &G, int s) : marked_(G.V()), edgeTo_(G.V()), s_(s) {
    assert(s >= 0 && s < std::ssize(marked_));
}

constexpr std::vector<int> algs4::Paths::pathTo(int v) const {
    assert(v >= 0 && v < std::ssize(marked_));
    std::vector<int> path;
    for (int x = v; x != s_; x = edgeTo_[x])
        path.push_back(x);
    path.push_back(s_);
    std::ranges::reverse(path);
    return path;
}

#endif // ALGS4_PATHS_HPP
