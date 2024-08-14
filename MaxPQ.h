#ifndef ALGS4_MAXPQ_H
#define ALGS4_MAXPQ_H


#include <vector>
#include <optional>

template<typename Key>
class MaxPQ {
private:
    std::vector<std::optional<Key>> pq;
    int N = 0;

    bool less(int i, int j) const {
        return pq[i] < pq[j];
    }

    void exch(int i, int j) {
        auto t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }

    void swim(int k) {
        while (k > 1 && less(k / 2, k)) {
            exch(k / 2, k);
            k = k / 2;
        }
    }

    void sink(int k) {
        while (2 * k <= N) {
            int j = 2 * k;
            if (j < N && less(j, j + 1)) ++j;
            if (!less(k, j)) break;
            exch(k, j);
            k = j;
        }
    }

public:
    MaxPQ(int maxN) : pq(maxN + 1) {}

    bool isEmpty() const {
        return N == 0;
    }

    int size() const {
        return N;
    }

    void insert(const Key &v) {
        pq[++N] = v;
        swim(N);
    }

    std::optional<Key> delMax() {
        auto max = pq[1];
        exch(1, N--);
        pq[N + 1] = std::nullopt;  // 置空
        sink(1);
        return max;
    }
};


#endif //ALGS4_MAXPQ_H
