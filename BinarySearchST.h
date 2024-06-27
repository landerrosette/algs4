#ifndef ALGS4_BINARYSEARCHST_H
#define ALGS4_BINARYSEARCHST_H


#include "ST.h"
#include <vector>

template<typename Key, typename Value>
class BinarySearchST : public ST<Key, Value> {
private:
    std::vector<Key> keys;
    std::vector<Value> vals;
    int N;

public:
    BinarySearchST(int capacity) : keys(capacity), vals(capacity), N(0) {}

    bool isEmpty() {
        return N == 0;
    }

    int rank(Key key) {
        int lo = 0, hi = N - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (key < keys[mid]) hi = mid - 1;
            else if (key > keys[mid]) lo = mid + 1;
            else return mid;
        }
        return lo;
    }

    Value get(Key key) override {
        if (isEmpty()) return Value();
        int i = rank(key);
        if (i < N && keys[i] == key) return vals[i];
        else return Value();
    }

    void put(Key key, Value val) override {
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

    std::deque<Key> getKeys() override {
        return std::deque<Key>(keys.begin(), keys.begin() + N);
    }

    // % algs4 < tinyST.txt
    static void main() {
        BinarySearchST<std::string, int> st(10);
        std::string key;
        for (int i = 0; std::cin >> key; ++i) {
            st.put(key, i);
        }
        for (const auto &s: st.getKeys()) {
            std::cout << s << " " << st.get(s) << "\n";
        }
    }
};


#endif //ALGS4_BINARYSEARCHST_H
