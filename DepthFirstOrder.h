#ifndef ALGS4_DEPTHFIRSTORDER_H
#define ALGS4_DEPTHFIRSTORDER_H


#include "DirectedDFS.h"
#include <list>
#include <vector>

class DepthFirstOrder {
private:
    std::vector<bool> marked;
    std::list<int> pre_, post_, reversePost_;

    void dfs(const Digraph& G, int v);

public:
    DepthFirstOrder(const Digraph& G);

    std::list<int> pre() const { return pre_; }

    std::list<int> post() const { return post_; }

    std::list<int> reversePost() const { return reversePost_; }
};


#endif //ALGS4_DEPTHFIRSTORDER_H
