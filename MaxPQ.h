#ifndef ALGS4_MAXPQ_H
#define ALGS4_MAXPQ_H


#include <vector>

template<typename T>
class MaxPQ {
private:
    std::vector<T> pq;
    int N = 0;

    bool less(int i, int j) {
        return pq[i] < pq[j];
    }

    void exch(int i, int j) {
        T t = pq[i];
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
    MaxPQ(int maxN) {
        pq.resize(maxN + 1);
    }

    bool isEmpty() {
        return N == 0;
    }

    int size() {
        return N;
    }

    void insert(T v) {
        pq[++N] = v;
        swim(N);
    }

    T delMax() {
        T max = pq[1];
        exch(1, N--);
        sink(1);
        return max;
    }
};


#endif //ALGS4_MAXPQ_H
