#include "BreadthFirstPaths.h"
#include <queue>

void BreadthFirstPaths::bfs(const Graph &G, int s) {
    std::queue<int> queue;
    marked[s] = true;
    queue.push(s);
    while (!queue.empty()) {
        int v = queue.front();
        queue.pop();
        for (int w: G.adj(v)) {
            if (!marked[w]) {
                edgeTo[w] = v;
                marked[w] = true;
                queue.push(w);
            }
        }

    }
}
