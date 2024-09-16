#ifndef ALGS4_MAXPQ_H
#define ALGS4_MAXPQ_H


#include "PQ.h"
#include <optional>

template <typename Key>
class MaxPQ : public PQ<Key> {
private:
    bool lower(int i, int j) const override { return this->pq[i] < this->pq[j]; }

public:
    MaxPQ(int maxN) : PQ<Key>(maxN) {}

    std::optional<Key> delMax() { return this->delTop(); }
};


#endif //ALGS4_MAXPQ_H
