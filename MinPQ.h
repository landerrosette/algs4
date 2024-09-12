#ifndef ALGS4_MINPQ_H
#define ALGS4_MINPQ_H


#include "PQ.h"
#include <optional>

template<typename Key>
class MinPQ : public PQ<Key> {
protected:
    bool lower(int i, int j) const override { return this->pq[i] > this->pq[j]; }

public:
    MinPQ(int maxN) : PQ<Key>(maxN) {}

    virtual std::optional<Key> delMin() { return this->delTop(); }
};


#endif //ALGS4_MINPQ_H
