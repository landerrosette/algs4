#ifndef ALGS4_ORDEREDST_H
#define ALGS4_ORDEREDST_H


#include <cassert>
#include <concepts>
#include <list>
#include <optional>

#include "ST.h"

namespace algs4 {
    template<std::totally_ordered Key, typename Value>
    class OrderedST : public ST<Key, Value> {
    public:
        virtual std::optional<Key> min() const = 0;
        virtual std::optional<Key> max() const = 0;
        virtual std::optional<Key> floor(const Key &key) const = 0;
        virtual std::optional<Key> ceiling(const Key &key) const = 0;
        virtual int rank(const Key &key) const = 0;
        virtual Key select(int k) const = 0;
        virtual void removeMin();
        virtual void removeMax();
        using ST<Key, Value>::size;
        int size(const Key &lo, const Key &hi) const;
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
int algs4::OrderedST<Key, Value>::size(const Key &lo, const Key &hi) const {
    if (hi < lo) return 0;
    else if (this->contains(hi)) return rank(hi) - rank(lo) + 1;
    else return rank(hi) - rank(lo);
}

template<std::totally_ordered Key, typename Value>
std::list<Key> algs4::OrderedST<Key, Value>::keys() const {
    if (this->isEmpty()) return {};
    return keys(*min(), *max());
}


#endif //ALGS4_ORDEREDST_H
