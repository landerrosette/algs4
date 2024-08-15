#ifndef ALGS4_LINEARPROBINGHASHST_H
#define ALGS4_LINEARPROBINGHASHST_H


#include "ST.h"
#include <vector>
#include <functional>

template<typename Key, typename Value>
class LinearProbingHashST : public ST<Key, Value> {
private:
    int N = 0;       // 符号表中键值对总数
    int M = 16;  // 线性探测表的大小
    std::vector<std::optional<Key>> keys;
    std::vector<std::optional<Value>> vals;

    int hash(const Key &key) const {
        std::hash<Key> hasher;
        return hasher(key) % M;
    }

    LinearProbingHashST(int M) : M(M), keys(M), vals(M) {}

    void resize(int cap) {
        LinearProbingHashST<Key, Value> t(cap);
        for (int i = 0; i < M; ++i) {
            if (keys[i] != std::nullopt) t.put(*keys[i], *vals[i]);
        }
        keys = t.keys;
        vals = t.vals;
        M = t.M;
    }

public:
    LinearProbingHashST() : keys(M), vals(M) {}

    std::optional<Value> get(const Key &key) const override {
        for (int i = hash(key); keys[i] != std::nullopt; i = (i + 1) % M) {
            if (keys[i] == key) return vals[i];
        }
        return std::nullopt;
    }

    void put(const Key &key, const Value &val) override {
        if (N >= M / 2) resize(2 * M);

        int i;
        for (i = hash(key); keys[i] != std::nullopt; i = (i + 1) % M) {
            if (keys[i] == key) {
                vals[i] = val;
                return;
            }
        }
        keys[i] = key;
        vals[i] = val;
        ++N;
    }

    void remove(const Key &key) override {
        if (!this->contains(key)) return;
        int i = hash(key);
        while (keys[i] != key) i = (i + 1) % M;
        keys[i] = std::nullopt;
        vals[i] = std::nullopt;
        i = (i + 1) % M;
        while (keys[i] != std::nullopt) {
            Key keyToRedo = *keys[i];
            Value valToRedo = *vals[i];
            keys[i] = std::nullopt;
            vals[i] = std::nullopt;
            --N;
            put(keyToRedo, valToRedo);
            i = (i + 1) % M;
        }
        --N;
        if (N > 0 && N == M / 8) resize(M / 2);
    }

    int size() const override {
        return N;
    }

    std::deque<Key> getKeys() const override {
        std::deque<Key> queue;
        for (int i = 0; i < M; ++i) {
            if (keys[i] != std::nullopt) queue.push_back(*keys[i]);
        }
        return queue;
    }
};


#endif //ALGS4_LINEARPROBINGHASHST_H
