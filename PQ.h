#ifndef ALGS4_PQ_H
#define ALGS4_PQ_H


#include <vector>
#include <optional>

template <typename Key>
class PQ {
protected:
    std::vector<std::optional<Key>> pq; // 基于堆的完全二叉树
    int N = 0;                          // 存储于pq[1..N]中，pq[0]没有使用

    virtual bool lower(int i, int j) const = 0;

    virtual void exch(int i, int j);

    void swim(int k);

    void sink(int k);

    std::optional<Key> delTop();

public:
    PQ(int maxN) : pq(maxN + 1) {}

    virtual ~PQ() = default;

    bool isEmpty() const { return N == 0; }

    int size() const { return N; }

    void insert(const Key& v);
};

template <typename Key>
void PQ<Key>::exch(int i, int j) {
    auto t = pq[i];
    pq[i] = pq[j];
    pq[j] = t;
}

template <typename Key>
void PQ<Key>::swim(int k) {
    while (k > 1 && lower(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template <typename Key>
void PQ<Key>::sink(int k) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && lower(j, j + 1)) ++j;
        if (!lower(k, j)) break;
        exch(k, j);
        k = j;
    }
}

template <typename Key>
std::optional<Key> PQ<Key>::delTop() {
    auto top = pq[1];
    exch(1, N--);
    pq[N + 1] = std::nullopt; // 置空
    sink(1);
    return top;
}

template <typename Key>
void PQ<Key>::insert(const Key& v) {
    pq[++N] = v;
    swim(N);
}


#endif //ALGS4_PQ_H
