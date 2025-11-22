#ifndef ALGS4_INDEXMINPQ_H
#define ALGS4_INDEXMINPQ_H


#include <optional>
#include <utility>
#include <vector>

namespace algs4 {
    template<typename Key>
    class IndexMinPQ {
    private:
        int N = 0;
        std::vector<int> pq;                   // binary heap using 1-based indexing
        std::vector<int> qp;                   // inverse: qp[pq[i]] = pq[qp[i]] = i
        std::vector<std::optional<Key> > keys; // items with priorities

        bool greater(int i, int j) const { return keys[pq[i]] > keys[pq[j]]; }
        void exch(int i, int j);
        void swim(int k);
        void sink(int k);

    public:
        explicit IndexMinPQ(int maxN) : pq(maxN + 1), qp(maxN + 1, -1), keys(maxN + 1) {}

        bool isEmpty() const { return N == 0; }
        int size() const { return N; }
        bool contains(int k) const { return qp[k] != -1; }
        void insert(int k, const Key &key);
        void change(int k, const Key &key);
        int delMin();
    };
}

template<typename Key>
void algs4::IndexMinPQ<Key>::exch(int i, int j) {
    std::swap(pq[i], pq[j]);
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

template<typename Key>
void algs4::IndexMinPQ<Key>::swim(int k) {
    while (k > 1 && greater(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template<typename Key>
void algs4::IndexMinPQ<Key>::sink(int k) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && greater(j, j + 1))
            ++j;
        if (!greater(k, j))
            break;
        exch(k, j);
        k = j;
    }
}

template<typename Key>
void algs4::IndexMinPQ<Key>::insert(int k, const Key &key) {
    qp[k] = ++N;
    pq[N] = k;
    keys[k] = key;
    swim(N);
}

template<typename Key>
void algs4::IndexMinPQ<Key>::change(int k, const Key &key) {
    keys[k] = key;
    swim(qp[k]);
    sink(qp[k]);
}

template<typename Key>
int algs4::IndexMinPQ<Key>::delMin() {
    int indexOfMin = pq[1];
    exch(1, N--);
    sink(1);
    keys[pq[N + 1]] = std::nullopt;
    qp[pq[N + 1]] = -1;
    return indexOfMin;
}


#endif //ALGS4_INDEXMINPQ_H