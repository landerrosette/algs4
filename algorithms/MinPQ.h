#ifndef ALGS4_MINPQ_H
#define ALGS4_MINPQ_H


#include <optional>

#include "PQ.h"

template<typename Key>
class MinPQ : public PQ<Key> {
protected:
    bool lower(int i, int j) const override { return this->pq[i] > this->pq[j]; }

public:
    using PQ<Key>::PQ;

    std::optional<Key> delMin() { return this->delTop(); }
};


#endif //ALGS4_MINPQ_H
