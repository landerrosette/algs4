#ifndef ALGS4_BINARYSEARCHST_HPP
#define ALGS4_BINARYSEARCHST_HPP


#include <cassert>
#include <utility>
#include <vector>

#include "OrderedST.hpp"
#include "SequentialSearchST.hpp"

namespace algs4 {
    template<std::totally_ordered Key, typename Value>
    class BinarySearchST : public OrderedST<Key, Value> {
    private:
        std::vector<Key> keys_;
        std::vector<Value> vals;

    public:
        using OrderedST<Key, Value>::get;
        const Value *get(const Key &key) const override;
        void put(Key key, Value val) override;
        void remove(const Key &key) override;
        std::ptrdiff_t size() const override { return std::ssize(keys_); }
        const Key *min() const override;
        const Key *max() const override;
        const Key *floor(const Key &key) const override;
        const Key *ceiling(const Key &key) const override;
        std::ptrdiff_t rank(const Key &key) const override;
        const Key *select(std::ptrdiff_t k) const override;
        std::vector<Key> keys(const Key &lo, const Key &hi) const override;
    };
}

template<std::totally_ordered Key, typename Value>
const Value *algs4::BinarySearchST<Key, Value>::get(const Key &key) const {
    if (this->isEmpty()) return nullptr;
    auto i = rank(key);
    if (i < size() && keys_[i] == key) return &vals[i];
    else return nullptr;
}

template<std::totally_ordered Key, typename Value>
void algs4::BinarySearchST<Key, Value>::put(Key key, Value val) {
    auto i = rank(key);
    if (i < size() && keys_[i] == key) {
        vals[i] = std::move(val);
        return;
    }
    if (i == size()) {
        keys_.push_back(std::move(key));
        vals.push_back(std::move(val));
        return;
    }
    keys_.push_back(std::move(keys_.back()));
    vals.push_back(std::move(vals.back()));
    for (auto j = size() - 2; j > i; --j) {
        keys_[j] = std::move(keys_[j - 1]);
        vals[j] = std::move(vals[j - 1]);
    }
    keys_[i] = std::move(key);
    vals[i] = std::move(val);
}

template<std::totally_ordered Key, typename Value>
void algs4::BinarySearchST<Key, Value>::remove(const Key &key) {
    if (this->isEmpty()) return;
    auto i = rank(key);
    if (i == size() || keys_[i] != key)
        return;
    for (auto j = i; j < size() - 1; ++j) {
        keys_[j] = std::move(keys_[j + 1]);
        vals[j] = std::move(vals[j + 1]);
    }
    keys_.pop_back();
    vals.pop_back();
}

template<std::totally_ordered Key, typename Value>
const Key *algs4::BinarySearchST<Key, Value>::min() const {
    if (this->isEmpty()) return nullptr;
    return &keys_[0];
}

template<std::totally_ordered Key, typename Value>
const Key *algs4::BinarySearchST<Key, Value>::max() const {
    if (this->isEmpty()) return nullptr;
    return &keys_[size() - 1];
}

template<std::totally_ordered Key, typename Value>
const Key *algs4::BinarySearchST<Key, Value>::floor(const Key &key) const {
    auto i = rank(key);
    if (i < size() && keys_[i] == key) return &keys_[i];
    if (i == 0) return nullptr;
    else return &keys_[i - 1];
}

template<std::totally_ordered Key, typename Value>
const Key *algs4::BinarySearchST<Key, Value>::ceiling(const Key &key) const {
    auto i = rank(key);
    if (i == size()) return nullptr;
    else return &keys_[i];
}

template<std::totally_ordered Key, typename Value>
std::ptrdiff_t algs4::BinarySearchST<Key, Value>::rank(const Key &key) const {
    std::ptrdiff_t lo = 0, hi = size() - 1;
    while (lo <= hi) {
        auto mid = lo + (hi - lo) / 2;
        if (key < keys_[mid]) hi = mid - 1;
        else if (key > keys_[mid]) lo = mid + 1;
        else return mid;
    }
    return lo;
}

template<std::totally_ordered Key, typename Value>
const Key *algs4::BinarySearchST<Key, Value>::select(ptrdiff_t k) const {
    assert(k >= 0 && k < size());
    return &keys_[k];
}

template<std::totally_ordered Key, typename Value>
std::vector<Key> algs4::BinarySearchST<Key, Value>::keys(const Key &lo, const Key &hi) const {
    std::vector<Key> queue;
    for (auto i = rank(lo); i < rank(hi); ++i)
        queue.push_back(keys_[i]);
    if (this->contains(hi))
        queue.push_back(keys_[rank(hi)]);
    return queue;
}


#endif //ALGS4_BINARYSEARCHST_HPP
