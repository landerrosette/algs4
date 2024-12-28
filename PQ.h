#ifndef ALGS4_PQ_H
#define ALGS4_PQ_H


#include <vector>
#include <optional>
#include <utility>

template<typename Key>
class PQ {
protected:
    std::vector<std::optional<Key> > pq; // heap-ordered complete binary tree
    int N = 0;                           // in pq[1..N] with pq[0] unused

    virtual bool lower(int i, int j) const = 0;

    void exch(int i, int j) { std::swap(pq[i], pq[j]); }

    void swim(int k);

    void sink(int k);

    std::optional<Key> delTop();

public:
    explicit PQ(int maxN) : pq(maxN + 1) {}

    virtual ~PQ() = default;

    bool isEmpty() const { return N == 0; }

    int size() const { return N; }

    void insert(const Key &v);
};

template<typename Key>
void PQ<Key>::swim(int k) {
    while (k > 1 && lower(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template<typename Key>
void PQ<Key>::sink(int k) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && lower(j, j + 1)) ++j;
        if (!lower(k, j)) break;
        exch(k, j);
        k = j;
    }
}

template<typename Key>
std::optional<Key> PQ<Key>::delTop() {
    auto top = pq[1];
    exch(1, N--);
    pq[N + 1] = std::nullopt;
    sink(1);
    return top;
}

template<typename Key>
void PQ<Key>::insert(const Key &v) {
    pq[++N] = v;
    swim(N);
}


#endif //ALGS4_PQ_H
