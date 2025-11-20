#ifndef ALGS4_MAXPQ_H
#define ALGS4_MAXPQ_H


#include <functional>
#include <optional>

#include "PQBase.h"

namespace algs4 {
    template<typename Key>
    class MaxPQ : public PQBase<Key, std::less<Key> > {
    public:
        using PQBase<Key, std::less<Key> >::PQBase;

        std::optional<Key> delMax() { return this->delTop(); }
    };
}


#endif //ALGS4_MAXPQ_H
