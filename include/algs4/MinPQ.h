#ifndef ALGS4_MINPQ_H
#define ALGS4_MINPQ_H


#include <concepts>
#include <functional>
#include <optional>

#include "PQBase.h"

namespace algs4 {
    template<std::totally_ordered Key>
    class MinPQ : public PQBase<Key, std::greater<Key> > {
    public:
        explicit MinPQ(int maxN) : PQBase<Key, std::greater<Key> >(maxN) {}

        std::optional<Key> delMin() { return this->delTop(); }
    };
}


#endif //ALGS4_MINPQ_H
