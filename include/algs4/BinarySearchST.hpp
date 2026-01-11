#ifndef ALGS4_BINARYSEARCHST_HPP
#define ALGS4_BINARYSEARCHST_HPP


#include <cassert>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "OrderedST.hpp"

namespace algs4 {
    template<std::totally_ordered Key, typename Value>
    class BinarySearchST : public OrderedST<Key, Value> {
    private:
        std::vector<std::optional<Key> > keys_;
        std::vector<std::optional<Value> > vals;
        std::ptrdiff_t N = 0;

    public:
        explicit BinarySearchST(std::ptrdiff_t capacity) : keys_(capacity), vals(capacity) { assert(capacity >= 0); }

        std::optional<Value> get(const Key &key) const override;
        void put(const Key &key, const Value &val) override;
        void remove(const Key &key) override;
        std::ptrdiff_t size() const override { return N; }
        std::optional<Key> min() const override;
        std::optional<Key> max() const override;
        std::optional<Key> floor(const Key &key) const override;
        std::optional<Key> ceiling(const Key &key) const override;
        std::ptrdiff_t rank(const Key &key) const override;
        Key select(std::ptrdiff_t k) const override;
        std::list<Key> keys(const Key &lo, const Key &hi) const override;
    };
}

template<std::totally_ordered Key, typename Value>
std::optional<Value> algs4::BinarySearchST<Key, Value>::get(const Key &key) const {
    if (this->isEmpty()) return std::nullopt;
    auto i = rank(key);
    if (i < N && keys_[i] == key) return vals[i];
    else return std::nullopt;
}

template<std::totally_ordered Key, typename Value>
void algs4::BinarySearchST<Key, Value>::put(const Key &key, const Value &val) {
    auto i = rank(key);
    if (i < N && keys_[i] == key) {
        vals[i] = val;
        return;
    }
    assert(N < keys_.size());
    for (auto j = N; j > i; --j) {
        keys_[j] = std::move(keys_[j - 1]);
        vals[j] = std::move(vals[j - 1]);
    }
    keys_[i] = key;
    vals[i] = val;
    ++N;
}

template<std::totally_ordered Key, typename Value>
void algs4::BinarySearchST<Key, Value>::remove(const Key &key) {
    if (this->isEmpty()) return;
    auto i = rank(key);
    if (i == N || keys_[i] != key)
        return;
    for (auto j = i; j < N - 1; ++j) {
        keys_[j] = std::move(keys_[j + 1]);
        vals[j] = std::move(vals[j + 1]);
    }
    --N;
    keys_[N] = std::nullopt;
    vals[N] = std::nullopt;
}

template<std::totally_ordered Key, typename Value>
std::optional<Key> algs4::BinarySearchST<Key, Value>::min() const {
    if (this->isEmpty()) return std::nullopt;
    return keys_[0];
}

template<std::totally_ordered Key, typename Value>
std::optional<Key> algs4::BinarySearchST<Key, Value>::max() const {
    if (this->isEmpty()) return std::nullopt;
    return keys_[N - 1];
}

template<std::totally_ordered Key, typename Value>
std::optional<Key> algs4::BinarySearchST<Key, Value>::floor(const Key &key) const {
    auto i = rank(key);
    if (i < N && keys_[i] == key) return keys_[i];
    if (i == 0) return std::nullopt;
    else return keys_[i - 1];
}

template<std::totally_ordered Key, typename Value>
std::optional<Key> algs4::BinarySearchST<Key, Value>::ceiling(const Key &key) const {
    auto i = rank(key);
    if (i == N) return std::nullopt;
    else return keys_[i];
}

template<std::totally_ordered Key, typename Value>
ptrdiff_t algs4::BinarySearchST<Key, Value>::rank(const Key &key) const {
    std::ptrdiff_t lo = 0, hi = N - 1;
    while (lo <= hi) {
        auto mid = lo + (hi - lo) / 2;
        if (key < keys_[mid]) hi = mid - 1;
        else if (key > keys_[mid]) lo = mid + 1;
        else return mid;
    }
    return lo;
}

template<std::totally_ordered Key, typename Value>
Key algs4::BinarySearchST<Key, Value>::select(ptrdiff_t k) const {
    assert(k < size());
    return *keys_[k];
}

template<std::totally_ordered Key, typename Value>
std::list<Key> algs4::BinarySearchST<Key, Value>::keys(const Key &lo, const Key &hi) const {
    std::list<Key> queue;
    for (auto i = rank(lo); i < rank(hi); ++i)
        queue.push_back(*keys_[i]);
    if (this->contains(hi))
        queue.push_back(*keys_[rank(hi)]);
    return queue;
}


#endif //ALGS4_BINARYSEARCHST_HPP
