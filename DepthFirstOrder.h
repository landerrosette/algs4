#ifndef ALGS4_DEPTHFIRSTORDER_H
#define ALGS4_DEPTHFIRSTORDER_H


#include "DirectedDFS.h"
#include <deque>
#include <vector>

class DepthFirstOrder {
private:
    std::vector<bool> marked;
    std::deque<int> pre, post, reversePost;

    void dfs(const Digraph &G, int v);

public:
    DepthFirstOrder(const Digraph &G);

    std::deque<int> getPre() const { return pre; }

    std::deque<int> getPost() const { return post; }

    std::deque<int> getReversePost() const { return reversePost; }
};


#endif //ALGS4_DEPTHFIRSTORDER_H
