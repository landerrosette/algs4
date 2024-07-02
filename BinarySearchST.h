#ifndef ALGS4_BINARYSEARCHST_H
#define ALGS4_BINARYSEARCHST_H


#include "OrderedST.h"
#include <vector>

template<typename Key, typename Value>
class BinarySearchST : public OrderedST<Key, Value> {
private:
    std::vector<Key> keys;
    std::vector<Value> vals;
    int N = 0;

public:
    BinarySearchST(int capacity) : keys(capacity), vals(capacity) {}

    Value get(const Key &key) const override {
        if (this->isEmpty()) return Value();
        int i = rank(key);
        if (i < N && keys[i] == key) return vals[i];
        else return Value();
    }

    void put(const Key &key, const Value &val) override {
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

    void remove(const Key &key) override {
        if (this->isEmpty()) return;
        int i = rank(key);
        if (i < N && keys[i] == key) {
            for (int j = i; j < N - 1; ++j) {
                keys[j] = keys[j + 1];
                vals[j] = vals[j + 1];
            }
        }
        --N;
        keys[N] = Key();    // 置空
        vals[N] = Value();  // 置空
    }

    int size() const override {
        return N;
    }

    Key min() const override {
        return keys[0];
    }

    Key max() const override {
        return keys[N - 1];
    }

    Key floor(const Key &key) const override {
        int i = rank(key);
        if (i < N && keys[i] == key) return keys[i];
        else return keys[i - 1];
    }

    Key ceiling(const Key &key) const override {
        int i = rank(key);
        return keys[i];
    }

    int rank(const Key &key) const override {
        int lo = 0, hi = N - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (key < keys[mid]) hi = mid - 1;
            else if (key > keys[mid]) lo = mid + 1;
            else return mid;
        }
        return lo;
    }

    Key select(int k) const override {
        return keys[k];
    }

    void removeMin() override {
        if (this->isEmpty()) return;
        remove(min());
    }

    void removeMax() override {
        if (this->isEmpty()) return;
        remove(max());
    }

    std::deque<Key> getKeys() const override {
        return getKeys(min(), max());
    }

    std::deque<Key> getKeys(const Key &lo, const Key &hi) const override {
        std::deque<Key> queue;
        if (hi < lo) return queue;
        for (int i = rank(lo); i < rank(hi); ++i) {
            queue.push_back(keys[i]);
        }
        if (this->contains(hi)) queue.push_back(keys[rank(hi)]);
        return queue;
    }
};


#endif //ALGS4_BINARYSEARCHST_H
