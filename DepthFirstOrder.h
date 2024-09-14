#ifndef ALGS4_DEPTHFIRSTORDER_H
#define ALGS4_DEPTHFIRSTORDER_H


#include "DirectedDFS.h"
#include <deque>
#include <vector>

class DepthFirstOrder {
private:
    std::vector<bool> marked;
    std::deque<int> pre_, post_, reversePost_;

    void dfs(const Digraph &G, int v);

public:
    DepthFirstOrder(const Digraph &G);

    std::deque<int> pre() const { return pre_; }

    std::deque<int> post() const { return post_; }

    std::deque<int> reversePost() const { return reversePost_; }
};


#endif //ALGS4_DEPTHFIRSTORDER_H
