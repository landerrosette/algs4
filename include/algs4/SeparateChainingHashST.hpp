#ifndef ALGS4_SEPARATECHAININGHASHST_HPP
#define ALGS4_SEPARATECHAININGHASHST_HPP


#include <cassert>
#include <cstddef>
#include <functional>
#include <vector>

#include "SequentialSearchST.hpp"
#include "ST.hpp"

namespace algs4 {
    template<typename Key, typename Value>
    class SeparateChainingHashST : public ST<Key, Value> {
    private:
        std::ptrdiff_t M; // hash table size
        std::vector<SequentialSearchST<Key, Value> > st;

        std::ptrdiff_t hash(const Key &key) const { return std::hash<Key>()(key) % M; }

    public:
        explicit SeparateChainingHashST(std::ptrdiff_t M) : M(M), st(M) { assert(M >= 0); }

        std::optional<Value> get(const Key &key) const override { return st[hash(key)].get(key); }
        void put(const Key &key, const Value &val) override { st[hash(key)].put(key, val); }
        void remove(const Key &key) override { st[hash(key)].remove(key); }
        std::ptrdiff_t size() const override;
        std::list<Key> keys() const override;
    };
}

template<typename Key, typename Value>
ptrdiff_t algs4::SeparateChainingHashST<Key, Value>::size() const {
    std::ptrdiff_t N = 0;
    for (decltype(M) i = 0; i < M; ++i)
        N += st[i].size();
    return N;
}

template<typename Key, typename Value>
std::list<Key> algs4::SeparateChainingHashST<Key, Value>::keys() const {
    std::list<Key> queue;
    for (decltype(M) i = 0; i < M; ++i) {
        for (const auto &key: st[i].keys())
            queue.push_back(key);
    }
    return queue;
}


#endif //ALGS4_SEPARATECHAININGHASHST_HPP
