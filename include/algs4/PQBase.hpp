#ifndef ALGS4_PQBASE_H
#define ALGS4_PQBASE_H


#include <cassert>
#include <concepts>
#include <optional>
#include <utility>
#include <vector>

namespace algs4 {
    template<typename Key, std::strict_weak_order<Key, Key> Compare>
    class PQBase {
    protected:
        std::vector<std::optional<Key> > pq; // heap-ordered complete binary tree
        int N = 0;                           // in pq[1..N] with pq[0] unused

        explicit PQBase(int maxN) : pq(maxN + 1) { assert(maxN >= 0); }
        ~PQBase() = default;

        bool less(int i, int j) { return Compare()(*pq[i], *pq[j]); }
        void exch(int i, int j) { std::swap(pq[i], pq[j]); }
        void swim(int k);
        void sink(int k);
        std::optional<Key> delTop();

    public:
        bool isEmpty() const { return N == 0; }
        int size() const { return N; }
        void insert(const Key &v);
    };
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
void algs4::PQBase<Key, Compare>::swim(int k) {
    while (k > 1 && less(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
void algs4::PQBase<Key, Compare>::sink(int k) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && less(j, j + 1))
            ++j;
        if (!less(k, j))
            break;
        exch(k, j);
        k = j;
    }
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
std::optional<Key> algs4::PQBase<Key, Compare>::delTop() {
    assert(!isEmpty());
    auto top = pq[1];
    exch(1, N--);
    pq[N + 1] = std::nullopt;
    sink(1);
    return top;
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
void algs4::PQBase<Key, Compare>::insert(const Key &v) {
    assert(N < pq.size() - 1);
    pq[++N] = v;
    swim(N);
}


#endif //ALGS4_PQBASE_H
