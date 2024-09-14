#include "Topological.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"

Topological::Topological(const Digraph &G) {
    DirectedCycle cyclefinder(G);
    if (!cyclefinder.hasCycle()) {
        DepthFirstOrder dfs(G);
        order_ = dfs.reversePost();
    }
}
