#ifndef ALGS4_INDEXMINPQ_H
#define ALGS4_INDEXMINPQ_H


#include "MinPQ.h"
#include <vector>
#include <optional>

template<typename Key>
class IndexMinPQ : private MinPQ<int> {
private:
    std::vector<std::optional<int> > qp;   // inverse: qp[pq[i]] = pq[qp[i]] = i
    std::vector<std::optional<Key> > keys; // items with priorities

    bool lower(int i, int j) const override { return keys[*pq[i]] > keys[*pq[j]]; }

    void exch(int i, int j) override;

public:
    explicit IndexMinPQ(int maxN) : MinPQ(maxN), qp(maxN + 1), keys(maxN + 1) {}

    using MinPQ::isEmpty, MinPQ::size;

    bool contains(int k) const { return qp[k].has_value(); }

    void insert(int k, const Key &key);

    void change(int k, const Key &key);

    std::optional<int> delMin();
};

template<typename Key>
void IndexMinPQ<Key>::exch(int i, int j) {
    MinPQ::exch(i, j);
    qp[*pq[i]] = i;
    qp[*pq[j]] = j;
}

template<typename Key>
void IndexMinPQ<Key>::insert(int k, const Key &key) {
    qp[k] = N + 1;
    keys[k] = key;
    MinPQ::insert(k);
}

template<typename Key>
void IndexMinPQ<Key>::change(int k, const Key &key) {
    keys[k] = key;
    swim(*qp[k]);
    sink(*qp[k]);
}

template<typename Key>
std::optional<int> IndexMinPQ<Key>::delMin() {
    int indexOfLast = *pq[N + 1];
    int indexOfMin = *MinPQ::delMin();
    qp[indexOfLast] = std::nullopt;
    keys[indexOfLast] = std::nullopt;
    return indexOfMin;
}


#endif //ALGS4_INDEXMINPQ_H
