#ifndef ALGS4_BINARYSEARCHST_H
#define ALGS4_BINARYSEARCHST_H


#include <cassert>
#include <optional>
#include <utility>
#include <vector>

#include "OrderedST.h"

namespace algs4 {
    template<std::totally_ordered Key, typename Value>
    class BinarySearchST : public OrderedST<Key, Value> {
    private:
        std::vector<std::optional<Key> > keys_;
        std::vector<std::optional<Value> > vals;
        int N = 0;

    public:
        explicit BinarySearchST(int capacity) : keys_(capacity), vals(capacity) { assert(capacity >= 0); }

        std::optional<Value> get(const Key &key) const override;
        void put(const Key &key, const Value &val) override;
        void remove(const Key &key) override;
        int size() const override { return N; }
        std::optional<Key> min() const override { return keys_[0]; }
        std::optional<Key> max() const override { return keys_[N - 1]; }
        std::optional<Key> floor(const Key &key) const override;
        std::optional<Key> ceiling(const Key &key) const override;
        int rank(const Key &key) const override;
        Key select(int k) const override;
        std::list<Key> keys(const Key &lo, const Key &hi) const override;
    };
}

template<std::totally_ordered Key, typename Value>
std::optional<Value> algs4::BinarySearchST<Key, Value>::get(const Key &key) const {
    if (this->isEmpty()) return std::nullopt;
    int i = rank(key);
    if (i < N && keys_[i] == key) return vals[i];
    else return std::nullopt;
}

template<std::totally_ordered Key, typename Value>
void algs4::BinarySearchST<Key, Value>::put(const Key &key, const Value &val) {
    int i = rank(key);
    if (i < N && keys_[i] == key) {
        vals[i] = val;
        return;
    }
    assert(N < keys_.size());
    for (int j = N; j > i; --j) {
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
    int i = rank(key);
    if (i == N || keys_[i] != key)
        return;
    for (int j = i; j < N - 1; ++j) {
        keys_[j] = std::move(keys_[j + 1]);
        vals[j] = std::move(vals[j + 1]);
    }
    --N;
    keys_[N] = std::nullopt;
    vals[N] = std::nullopt;
}

template<std::totally_ordered Key, typename Value>
std::optional<Key> algs4::BinarySearchST<Key, Value>::floor(const Key &key) const {
    int i = rank(key);
    if (i < N && keys_[i] == key) return keys_[i];
    if (i == 0) return std::nullopt;
    else return keys_[i - 1];
}

template<std::totally_ordered Key, typename Value>
std::optional<Key> algs4::BinarySearchST<Key, Value>::ceiling(const Key &key) const {
    int i = rank(key);
    if (i == N) return std::nullopt;
    else return keys_[i];
}

template<std::totally_ordered Key, typename Value>
int algs4::BinarySearchST<Key, Value>::rank(const Key &key) const {
    int lo = 0, hi = N - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (key < keys_[mid]) hi = mid - 1;
        else if (key > keys_[mid]) lo = mid + 1;
        else return mid;
    }
    return lo;
}

template<std::totally_ordered Key, typename Value>
Key algs4::BinarySearchST<Key, Value>::select(int k) const {
    assert(k >= 0 && k < size());
    return *keys_[k];
}

template<std::totally_ordered Key, typename Value>
std::list<Key> algs4::BinarySearchST<Key, Value>::keys(const Key &lo, const Key &hi) const {
    std::list<Key> queue;
    for (int i = rank(lo); i < rank(hi); ++i)
        queue.push_back(*keys_[i]);
    if (this->contains(hi))
        queue.push_back(*keys_[rank(hi)]);
    return queue;
}


#endif //ALGS4_BINARYSEARCHST_H
