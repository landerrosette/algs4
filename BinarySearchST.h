#ifndef ALGS4_BINARYSEARCHST_H
#define ALGS4_BINARYSEARCHST_H


#include "OrderedST.h"
#include <vector>

template<typename Key, typename Value>
class BinarySearchST : public OrderedST<Key, Value> {
private:
    std::vector<std::optional<Key> > keys_;
    std::vector<std::optional<Value> > vals;
    int N = 0;

public:
    explicit BinarySearchST(int capacity) : keys_(capacity), vals(capacity) {}

    std::optional<Value> get(const Key &key) const override;

    void put(const Key &key, const Value &val) override;

    void remove(const Key &key) override;

    int size() const override { return N; }

    std::optional<Key> min() const override { return keys_[0]; }

    std::optional<Key> max() const override { return keys_[N - 1]; }

    std::optional<Key> floor(const Key &key) const override;

    std::optional<Key> ceiling(const Key &key) const override;

    int rank(const Key &key) const override;

    std::optional<Key> select(int k) const override { return keys_[k]; }

    std::list<Key> keys(const Key &lo, const Key &hi) const override;
};

template<typename Key, typename Value>
std::optional<Value> BinarySearchST<Key, Value>::get(const Key &key) const {
    if (this->isEmpty()) return std::nullopt;
    int i = rank(key);
    if (i < N && keys_[i] == key) return vals[i];
    else return std::nullopt;
}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::put(const Key &key, const Value &val) {
    int i = rank(key);
    if (i < N && keys_[i] == key) {
        vals[i] = val;
        return;
    }
    for (int j = N; j > i; --j) {
        keys_[j] = keys_[j - 1];
        vals[j] = vals[j - 1];
    }
    keys_[i] = key;
    vals[i] = val;
    ++N;
}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::remove(const Key &key) {
    if (this->isEmpty()) return;
    int i = rank(key);
    if (i < N && keys_[i] == key) {
        for (int j = i; j < N - 1; ++j) {
            keys_[j] = keys_[j + 1];
            vals[j] = vals[j + 1];
        }
    }
    --N;
    keys_[N] = std::nullopt; // 置空
    vals[N] = std::nullopt;  // 置空
}

template<typename Key, typename Value>
std::optional<Key> BinarySearchST<Key, Value>::floor(const Key &key) const {
    int i = rank(key);
    if (i < N && keys_[i] == key) return keys_[i];
    else return keys_[i - 1];
}

template<typename Key, typename Value>
std::optional<Key> BinarySearchST<Key, Value>::ceiling(const Key &key) const {
    int i = rank(key);
    return keys_[i];
}

template<typename Key, typename Value>
int BinarySearchST<Key, Value>::rank(const Key &key) const {
    int lo = 0, hi = N - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (key < keys_[mid]) hi = mid - 1;
        else if (key > keys_[mid]) lo = mid + 1;
        else return mid;
    }
    return lo;
}

template<typename Key, typename Value>
std::list<Key> BinarySearchST<Key, Value>::keys(const Key &lo, const Key &hi) const {
    std::list<Key> queue;
    if (hi < lo) return queue;
    for (int i = rank(lo); i < rank(hi); ++i) queue.push_back(*keys_[i]);
    if (this->contains(hi)) queue.push_back(*keys_[rank(hi)]);
    return queue;
}


#endif //ALGS4_BINARYSEARCHST_H
