#ifndef ALGS4_INDEXMINPQ_HPP
#define ALGS4_INDEXMINPQ_HPP


#include <cassert>
#include <concepts>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

namespace algs4 {
    template<std::totally_ordered Key>
    class IndexMinPQ {
    private:
        std::ptrdiff_t N = 0;
        std::vector<std::ptrdiff_t> pq;        // binary heap using 1-based indexing
        std::vector<std::ptrdiff_t> qp;        // inverse: qp[pq[i]] = pq[qp[i]] = i
        std::vector<std::optional<Key> > keys; // items with priorities

        constexpr bool greater(std::ptrdiff_t i, std::ptrdiff_t j) const { return keys[pq[i]] > keys[pq[j]]; }
        constexpr void exch(std::ptrdiff_t i, std::ptrdiff_t j);
        constexpr void swim(std::ptrdiff_t k);
        constexpr void sink(std::ptrdiff_t k);

    public:
        constexpr explicit IndexMinPQ(std::ptrdiff_t maxN) : pq(maxN + 1), qp(maxN + 1, -1), keys(maxN + 1) {
            assert(maxN >= 0);
        }

        constexpr bool isEmpty() const { return N == 0; }
        constexpr std::ptrdiff_t size() const { return N; }
        constexpr bool contains(std::ptrdiff_t k) const;

        template<typename K> requires std::constructible_from<Key, K>
        constexpr void insert(std::ptrdiff_t k, K &&key);

        template<typename K> requires std::constructible_from<Key, K>
        constexpr void change(std::ptrdiff_t k, K &&key);

        constexpr std::ptrdiff_t delMin();
    };
}

template<std::totally_ordered Key>
constexpr void algs4::IndexMinPQ<Key>::exch(std::ptrdiff_t i, std::ptrdiff_t j) {
    using std::swap;
    swap(pq[i], pq[j]);
    qp[pq[i]] = i;
    qp[pq[j]] = j;
}

template<std::totally_ordered Key>
constexpr void algs4::IndexMinPQ<Key>::swim(std::ptrdiff_t k) {
    while (k > 1 && greater(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template<std::totally_ordered Key>
constexpr void algs4::IndexMinPQ<Key>::sink(std::ptrdiff_t k) {
    while (2 * k <= N) {
        auto j = 2 * k;
        if (j < N && greater(j, j + 1))
            ++j;
        if (!greater(k, j))
            break;
        exch(k, j);
        k = j;
    }
}

template<std::totally_ordered Key>
constexpr bool algs4::IndexMinPQ<Key>::contains(std::ptrdiff_t k) const {
    assert(k >= 0 && k < std::ssize(qp) - 1);
    return qp[k] != -1;
}

template<std::totally_ordered Key>
template<typename K> requires std::constructible_from<Key, K>
constexpr void algs4::IndexMinPQ<Key>::insert(std::ptrdiff_t k, K &&key) {
    assert(k >= 0 && k < std::ssize(qp) - 1);
    assert(!contains(k));
    qp[k] = ++N;
    pq[N] = k;
    keys[k].emplace(std::forward<K>(key));
    swim(N);
}

template<std::totally_ordered Key>
template<typename K> requires std::constructible_from<Key, K>
constexpr void algs4::IndexMinPQ<Key>::change(std::ptrdiff_t k, K &&key) {
    assert(k >= 0 && k < std::ssize(qp) - 1);
    assert(contains(k));
    keys[k].emplace(std::forward<K>(key));
    swim(qp[k]);
    sink(qp[k]);
}

template<std::totally_ordered Key>
constexpr std::ptrdiff_t algs4::IndexMinPQ<Key>::delMin() {
    assert(!isEmpty());
    auto indexOfMin = pq[1];
    exch(1, N--);
    sink(1);
    keys[pq[N + 1]] = std::nullopt;
    qp[pq[N + 1]] = -1;
    return indexOfMin;
}


#endif //ALGS4_INDEXMINPQ_HPP
