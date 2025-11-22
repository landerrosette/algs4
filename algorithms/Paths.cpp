#include "Paths.h"

std::list<int> algs4::Paths::pathTo(int v) const {
    std::list<int> path;
    for (int x = v; x != s; x = edgeTo[x])
        path.push_front(x);
    path.push_front(s);
    return path;
}