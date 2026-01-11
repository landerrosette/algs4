#ifndef ALGS4_LINEARPROBINGHASHST_HPP
#define ALGS4_LINEARPROBINGHASHST_HPP


#include <cstddef>
#include <functional>
#include <optional>
#include <utility>
#include <vector>

#include "ST.hpp"

namespace algs4 {
    template<typename Key, typename Value>
    class LinearProbingHashST : public ST<Key, Value> {
    private:
        std::ptrdiff_t N = 0;  // number of key-value pairs in the table
        std::ptrdiff_t M = 16; // size of linear-probing table
        std::vector<std::optional<Key> > keys_;
        std::vector<std::optional<Value> > vals;

        explicit LinearProbingHashST(std::ptrdiff_t M) : M(M), keys_(M), vals(M) {}

        std::ptrdiff_t hash(const Key &key) const { return std::hash<Key>()(key) % M; }
        void resize(std::ptrdiff_t cap);

    public:
        LinearProbingHashST() : keys_(M), vals(M) {}

        std::optional<Value> get(const Key &key) const override;
        void put(const Key &key, const Value &val) override;
        void remove(const Key &key) override;
        std::ptrdiff_t size() const override { return N; }
        std::list<Key> keys() const override;
    };
}

template<typename Key, typename Value>
void algs4::LinearProbingHashST<Key, Value>::resize(std::ptrdiff_t cap) {
    LinearProbingHashST t(cap);
    for (decltype(M) i = 0; i < M; ++i)
        if (keys_[i])
            t.put(*keys_[i], *vals[i]);
    keys_ = std::move(t.keys_);
    vals = std::move(t.vals);
    M = t.M;
}

template<typename Key, typename Value>
std::optional<Value> algs4::LinearProbingHashST<Key, Value>::get(const Key &key) const {
    for (auto i = hash(key); keys_[i]; i = (i + 1) % M)
        if (keys_[i] == key)
            return vals[i];
    return std::nullopt;
}

template<typename Key, typename Value>
void algs4::LinearProbingHashST<Key, Value>::put(const Key &key, const Value &val) {
    if (N >= M / 2) resize(2 * M);

    auto i = hash(key);
    for (; keys_[i]; i = (i + 1) % M)
        if (keys_[i] == key) {
            vals[i] = val;
            return;
        }
    keys_[i] = key;
    vals[i] = val;
    ++N;
}

template<typename Key, typename Value>
void algs4::LinearProbingHashST<Key, Value>::remove(const Key &key) {
    if (!this->contains(key)) return;
    auto i = hash(key);
    while (keys_[i] != key) i = (i + 1) % M;
    keys_[i] = std::nullopt;
    vals[i] = std::nullopt;
    i = (i + 1) % M;
    while (keys_[i]) {
        Key keyToRedo = std::move(*keys_[i]);
        Value valToRedo = std::move(*vals[i]);
        keys_[i] = std::nullopt;
        vals[i] = std::nullopt;
        --N;
        put(keyToRedo, valToRedo);
        i = (i + 1) % M;
    }
    --N;
    if (N > 0 && N == M / 8) resize(M / 2);
}

template<typename Key, typename Value>
std::list<Key> algs4::LinearProbingHashST<Key, Value>::keys() const {
    std::list<Key> queue;
    for (decltype(M) i = 0; i < M; ++i)
        if (keys_[i])
            queue.push_back(*keys_[i]);
    return queue;
}


#endif //ALGS4_LINEARPROBINGHASHST_HPP
