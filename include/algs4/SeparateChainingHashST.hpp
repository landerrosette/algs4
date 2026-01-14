#ifndef ALGS4_SEPARATECHAININGHASHST_HPP
#define ALGS4_SEPARATECHAININGHASHST_HPP


#include <cassert>
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

#include "SequentialSearchST.hpp"
#include "ST.hpp"

namespace algs4 {
    template<typename Key, typename Value>
    class SeparateChainingHashST : public ST<Key, Value> {
    private:
        std::ptrdiff_t M; // hash table size
        std::vector<SequentialSearchST<Key, Value> > st;

        auto hash(const Key &key) const { return std::hash<Key>()(key) % M; }

    public:
        SeparateChainingHashST() : SeparateChainingHashST(997) {}
        explicit SeparateChainingHashST(std::ptrdiff_t M) : M(M), st(M) { assert(M >= 0); }

        using ST<Key, Value>::get;
        const Value *get(const Key &key) const override { return st[hash(key)].get(key); }
        void put(Key key, Value val) override { st[hash(key)].put(std::move(key), std::move(val)); }
        void remove(const Key &key) override { st[hash(key)].remove(key); }
        std::ptrdiff_t size() const override;
        std::vector<Key> keys() const override;
    };
}

template<typename Key, typename Value>
std::ptrdiff_t algs4::SeparateChainingHashST<Key, Value>::size() const {
    std::ptrdiff_t N = 0;
    for (const auto &t: st)
        N += t.size();
    return N;
}

template<typename Key, typename Value>
std::vector<Key> algs4::SeparateChainingHashST<Key, Value>::keys() const {
    std::vector<Key> queue;
    for (const auto &t: st) {
        for (const auto &key: t.keys())
            queue.push_back(key);
    }
    return queue;
}


#endif //ALGS4_SEPARATECHAININGHASHST_HPP
