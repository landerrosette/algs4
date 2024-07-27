#ifndef ALGS4_SEPARATECHAININGHASHST_H
#define ALGS4_SEPARATECHAININGHASHST_H


#include "ST.h"
#include "SequentialSearchST.h"
#include <vector>
#include <functional>

template<typename Key, typename Value>
class SeparateChainingHashST : public ST<Key, Value> {
private:
    int M = 0;  // 散列表的大小
    std::vector<SequentialSearchST<Key, Value>> st;

    int hash(const Key &key) const {
        std::hash<Key> hasher;
        return hasher(key) % M;
    }

public:
    SeparateChainingHashST(int M) : M(M), st(M) {}

    Value get(const Key &key) const override {
        return st[hash(key)].get(key);
    }

    void put(const Key &key, const Value &val) override {
        st[hash(key)].put(key, val);
    }

    void remove(const Key &key) override {
        st[hash(key)].remove(key);
    }

    int size() const override {
        int N = 0;
        for (int i = 0; i < M; ++i) N += st[i].size();
        return N;
    }

    std::deque<Key> getKeys() const override {
        std::deque<Key> queue;
        for (int i = 0; i < M; ++i) {
            for (auto key: st[i].getKeys()) {
                queue.push_back(key);
            }
        }
        return queue;
    }
};


#endif //ALGS4_SEPARATECHAININGHASHST_H
