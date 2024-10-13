#ifndef ALGS4_SEPARATECHAININGHASHST_H
#define ALGS4_SEPARATECHAININGHASHST_H


#include "ST.h"
#include "SequentialSearchST.h"
#include <vector>
#include <functional>

template<typename Key, typename Value>
class SeparateChainingHashST : public ST<Key, Value> {
private:
    int M; // 散列表的大小
    std::vector<SequentialSearchST<Key, Value> > st;

    int hash(const Key &key) const;

public:
    SeparateChainingHashST(int M) : M(M), st(M) {}

    std::optional<Value> get(const Key &key) const override { return st[hash(key)].get(key); }

    void put(const Key &key, const Value &val) override { st[hash(key)].put(key, val); }

    void remove(const Key &key) override { st[hash(key)].remove(key); }

    int size() const override;

    std::list<Key> keys() const override;
};

template<typename Key, typename Value>
int SeparateChainingHashST<Key, Value>::hash(const Key &key) const {
    std::hash<Key> hasher;
    return hasher(key) % M;
}

template<typename Key, typename Value>
int SeparateChainingHashST<Key, Value>::size() const {
    int N = 0;
    for (int i = 0; i < M; ++i) N += st[i].size();
    return N;
}

template<typename Key, typename Value>
std::list<Key> SeparateChainingHashST<Key, Value>::keys() const {
    std::list<Key> queue;
    for (int i = 0; i < M; ++i) {
        for (const auto &key: st[i].keys()) {
            queue.push_back(key);
        }
    }
    return queue;
}


#endif //ALGS4_SEPARATECHAININGHASHST_H
