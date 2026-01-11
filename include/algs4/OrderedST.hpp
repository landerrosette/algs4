#ifndef ALGS4_ORDEREDST_HPP
#define ALGS4_ORDEREDST_HPP


#include <concepts>
#include <cstddef>
#include <list>
#include <optional>

#include "ST.hpp"

namespace algs4 {
    template<std::totally_ordered Key, typename Value>
    class OrderedST : public ST<Key, Value> {
    public:
        virtual std::optional<Key> min() const = 0;
        virtual std::optional<Key> max() const = 0;
        virtual std::optional<Key> floor(const Key &key) const = 0;
        virtual std::optional<Key> ceiling(const Key &key) const = 0;
        virtual std::ptrdiff_t rank(const Key &key) const = 0;
        virtual Key select(std::ptrdiff_t k) const = 0;
        virtual void removeMin();
        virtual void removeMax();
        using ST<Key, Value>::size;
        std::ptrdiff_t size(const Key &lo, const Key &hi) const;
        std::list<Key> keys() const override;
        virtual std::list<Key> keys(const Key &lo, const Key &hi) const = 0;
    };
}

template<std::totally_ordered Key, typename Value>
void algs4::OrderedST<Key, Value>::removeMin() {
    if (this->isEmpty()) return;
    this->remove(*min());
}

template<std::totally_ordered Key, typename Value>
void algs4::OrderedST<Key, Value>::removeMax() {
    if (this->isEmpty()) return;
    this->remove(*max());
}

template<std::totally_ordered Key, typename Value>
std::ptrdiff_t algs4::OrderedST<Key, Value>::size(const Key &lo, const Key &hi) const {
    if (hi < lo) return 0;
    else if (this->contains(hi)) return rank(hi) - rank(lo) + 1;
    else return rank(hi) - rank(lo);
}

template<std::totally_ordered Key, typename Value>
std::list<Key> algs4::OrderedST<Key, Value>::keys() const {
    if (this->isEmpty()) return {};
    return keys(*min(), *max());
}


#endif //ALGS4_ORDEREDST_HPP
