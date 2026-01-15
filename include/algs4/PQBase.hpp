#ifndef ALGS4_PQBASE_HPP
#define ALGS4_PQBASE_HPP


#include <cassert>
#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

namespace algs4 {
    template<typename Key, std::strict_weak_order<Key, Key> Compare>
    class PQBase {
    protected:
        std::vector<Key> pq;
        [[no_unique_address]] Compare comp;

        constexpr PQBase() = default;
        constexpr explicit PQBase(const Compare &comp) : comp(comp) {}
        constexpr ~PQBase() = default;
        constexpr PQBase(const PQBase &) = default;
        constexpr PQBase &operator=(const PQBase &) = default;
        constexpr PQBase(PQBase &&) noexcept = default;
        constexpr PQBase &operator=(PQBase &&) noexcept = default;

        constexpr bool less(std::ptrdiff_t i, std::ptrdiff_t j) { return comp(pq[i - 1], pq[j - 1]); }
        constexpr void exch(std::ptrdiff_t i, std::ptrdiff_t j);
        constexpr void swim(std::ptrdiff_t k);
        constexpr void sink(std::ptrdiff_t k);
        constexpr Key delTop();

    public:
        constexpr bool isEmpty() const { return pq.empty(); }
        constexpr std::ptrdiff_t size() const { return std::ssize(pq); }

        template<typename K> requires std::constructible_from<Key, K>
        constexpr void insert(K &&v);
    };
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr void algs4::PQBase<Key, Compare>::exch(std::ptrdiff_t i, std::ptrdiff_t j) {
    using std::swap;
    swap(pq[i - 1], pq[j - 1]);
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr void algs4::PQBase<Key, Compare>::swim(std::ptrdiff_t k) {
    while (k > 1 && less(k / 2, k)) {
        exch(k / 2, k);
        k = k / 2;
    }
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr void algs4::PQBase<Key, Compare>::sink(std::ptrdiff_t k) {
    while (2 * k <= size()) {
        auto j = 2 * k;
        if (j < size() && less(j, j + 1))
            ++j;
        if (!less(k, j))
            break;
        exch(k, j);
        k = j;
    }
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
constexpr Key algs4::PQBase<Key, Compare>::delTop() {
    assert(!isEmpty());
    auto top = std::move(pq[0]);
    exch(1, size());
    pq.pop_back();
    sink(1);
    return top;
}

template<typename Key, std::strict_weak_order<Key, Key> Compare>
template<typename K> requires std::constructible_from<Key, K>
constexpr void algs4::PQBase<Key, Compare>::insert(K &&v) {
    pq.emplace_back(std::forward<K>(v));
    swim(size());
}


#endif //ALGS4_PQBASE_HPP
