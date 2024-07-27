#ifndef ALGS4_ORDEREDST_H
#define ALGS4_ORDEREDST_H


#include "ST.h"
#include <deque>

template<typename Key, typename Value>
class OrderedST : public ST<Key, Value> {
public:
    virtual Key min() const = 0;

    virtual Key max() const = 0;

    virtual Key floor(const Key &key) const = 0;

    virtual Key ceiling(const Key &key) const = 0;

    virtual int rank(const Key &key) const = 0;

    virtual Key select(int k) const = 0;

    virtual void removeMin() = 0;

    virtual void removeMax() = 0;

    using ST<Key, Value>::size;

    int size(const Key &lo, const Key &hi) const {
        if (hi < lo) return 0;
        if (this->contains(hi)) return rank(hi) - rank(lo) + 1;
        else return rank(hi) - rank(lo);
    };

    using ST<Key, Value>::getKeys;

    virtual std::deque<Key> getKeys(const Key &lo, const Key &hi) const = 0;
};


#endif //ALGS4_ORDEREDST_H
