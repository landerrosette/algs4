#ifndef ALGS4_BINARYSEARCHST_H
#define ALGS4_BINARYSEARCHST_H


#include "OrderedST.h"
#include <vector>

template<typename Key, typename Value>
class BinarySearchST : public OrderedST<Key, Value> {
private:
    std::vector<std::optional<Key>> keys;
    std::vector<std::optional<Value>> vals;
    int N = 0;

public:
    BinarySearchST(int capacity) : keys(capacity), vals(capacity) {}

    std::optional<Value> get(const Key &key) const override;

    void put(const Key &key, const Value &val) override;

    void remove(const Key &key) override;

    int size() const override { return N; }

    std::optional<Key> min() const override { return keys[0]; }

    std::optional<Key> max() const override { return keys[N - 1]; }

    std::optional<Key> floor(const Key &key) const override;

    std::optional<Key> ceiling(const Key &key) const override;

    int rank(const Key &key) const override;

    std::optional<Key> select(int k) const override { return keys[k]; }

    void removeMin() override;

    void removeMax() override;

    std::deque<Key> getKeys() const override { return getKeys(*min(), *max()); }

    std::deque<Key> getKeys(const Key &lo, const Key &hi) const override;
};

template<typename Key, typename Value>
std::optional<Value> BinarySearchST<Key, Value>::get(const Key &key) const {
    if (this->isEmpty()) return std::nullopt;
    int i = rank(key);
    if (i < N && keys[i] == key) return vals[i];
    else return std::nullopt;
}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::put(const Key &key, const Value &val) {
    int i = rank(key);
    if (i < N && keys[i] == key) {
        vals[i] = val;
        return;
    }
    for (int j = N; j > i; --j) {
        keys[j] = keys[j - 1];
        vals[j] = vals[j - 1];
    }
    keys[i] = key;
    vals[i] = val;
    ++N;
}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::remove(const Key &key) {
    if (this->isEmpty()) return;
    int i = rank(key);
    if (i < N && keys[i] == key) {
        for (int j = i; j < N - 1; ++j) {
            keys[j] = keys[j + 1];
            vals[j] = vals[j + 1];
        }
    }
    --N;
    keys[N] = std::nullopt;  // 置空
    vals[N] = std::nullopt;  // 置空
}

template<typename Key, typename Value>
std::optional<Key> BinarySearchST<Key, Value>::floor(const Key &key) const {
    int i = rank(key);
    if (i < N && keys[i] == key) return keys[i];
    else return keys[i - 1];
}

template<typename Key, typename Value>
std::optional<Key> BinarySearchST<Key, Value>::ceiling(const Key &key) const {
    int i = rank(key);
    return keys[i];
}

template<typename Key, typename Value>
int BinarySearchST<Key, Value>::rank(const Key &key) const {
    int lo = 0, hi = N - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (key < keys[mid]) hi = mid - 1;
        else if (key > keys[mid]) lo = mid + 1;
        else return mid;
    }
    return lo;
}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::removeMin() {
    if (this->isEmpty()) return;
    remove(*min());
}

template<typename Key, typename Value>
void BinarySearchST<Key, Value>::removeMax() {
    if (this->isEmpty()) return;
    remove(*max());
}

template<typename Key, typename Value>
std::deque<Key> BinarySearchST<Key, Value>::getKeys(const Key &lo, const Key &hi) const {
    std::deque<Key> queue;
    if (hi < lo) return queue;
    for (int i = rank(lo); i < rank(hi); ++i) queue.push_back(*keys[i]);
    if (this->contains(hi)) queue.push_back(*keys[rank(hi)]);
    return queue;
}


#endif //ALGS4_BINARYSEARCHST_H
