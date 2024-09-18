#ifndef ALGS4_LINEARPROBINGHASHST_H
#define ALGS4_LINEARPROBINGHASHST_H


#include "ST.h"
#include <vector>
#include <functional>

template <typename Key, typename Value>
class LinearProbingHashST : public ST<Key, Value> {
private:
    int N = 0;  // 符号表中键值对总数
    int M = 16; // 线性探测表的大小
    std::vector<std::optional<Key>> keys_;
    std::vector<std::optional<Value>> vals;

    int hash(const Key& key) const;

    LinearProbingHashST(int M) : M(M), keys_(M), vals(M) {}

    void resize(int cap);

public:
    LinearProbingHashST() : keys_(M), vals(M) {}

    std::optional<Value> get(const Key& key) const override;

    void put(const Key& key, const Value& val) override;

    void remove(const Key& key) override;

    int size() const override { return N; }

    std::list<Key> keys() const override;
};

template <typename Key, typename Value>
int LinearProbingHashST<Key, Value>::hash(const Key& key) const {
    std::hash<Key> hasher;
    return hasher(key) % M;
}

template <typename Key, typename Value>
void LinearProbingHashST<Key, Value>::resize(int cap) {
    LinearProbingHashST<Key, Value> t(cap);
    for (int i = 0; i < M; ++i) {
        if (keys_[i]) t.put(*keys_[i], *vals[i]);
    }
    keys_ = t.keys_;
    vals = t.vals;
    M = t.M;
}

template <typename Key, typename Value>
std::optional<Value> LinearProbingHashST<Key, Value>::get(const Key& key) const {
    for (int i = hash(key); keys_[i]; i = (i + 1) % M) {
        if (keys_[i] == key) return vals[i];
    }
    return std::nullopt;
}

template <typename Key, typename Value>
void LinearProbingHashST<Key, Value>::put(const Key& key, const Value& val) {
    if (N >= M / 2) resize(2 * M);

    int i;
    for (i = hash(key); keys_[i]; i = (i + 1) % M) {
        if (keys_[i] == key) {
            vals[i] = val;
            return;
        }
    }
    keys_[i] = key;
    vals[i] = val;
    ++N;
}

template <typename Key, typename Value>
void LinearProbingHashST<Key, Value>::remove(const Key& key) {
    if (!this->contains(key)) return;
    int i = hash(key);
    while (keys_[i] != key) i = (i + 1) % M;
    keys_[i] = std::nullopt;
    vals[i] = std::nullopt;
    i = (i + 1) % M;
    while (keys_[i]) {
        Key keyToRedo = *keys_[i];
        Value valToRedo = *vals[i];
        keys_[i] = std::nullopt;
        vals[i] = std::nullopt;
        --N;
        put(keyToRedo, valToRedo);
        i = (i + 1) % M;
    }
    --N;
    if (N > 0 && N == M / 8) resize(M / 2);
}

template <typename Key, typename Value>
std::list<Key> LinearProbingHashST<Key, Value>::keys() const {
    std::list<Key> queue;
    for (int i = 0; i < M; ++i) {
        if (keys_[i]) queue.push_back(*keys_[i]);
    }
    return queue;
}


#endif //ALGS4_LINEARPROBINGHASHST_H
