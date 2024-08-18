#include "Paths.h"

std::forward_list<int> Paths::pathTo(int v) const {
    std::forward_list<int> path;
    for (int x = v; x != s; x = edgeTo[x]) path.push_front(x);
    path.push_front(s);
    return path;
}
