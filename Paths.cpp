#include "Paths.h"

std::deque<int> Paths::pathTo(int v) const {
    std::deque<int> path;
    for (int x = v; x != s; x = edgeTo[x]) path.push_front(x);
    path.push_front(s);
    return path;
}
