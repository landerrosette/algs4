#ifndef ALGS4_MINPQ_H
#define ALGS4_MINPQ_H


#include <functional>
#include <optional>

#include "PQBase.h"

namespace algs4 {
    template<typename Key>
    class MinPQ : public PQBase<Key, std::greater<Key> > {
    public:
        using PQBase<Key, std::greater<Key> >::PQBase;

        std::optional<Key> delMin() { return this->delTop(); }
    };
}


#endif //ALGS4_MINPQ_H
