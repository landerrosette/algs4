#ifndef ALGS4_MAXPQ_HPP
#define ALGS4_MAXPQ_HPP


#include <concepts>
#include <functional>
#include <optional>

#include "PQBase.hpp"

namespace algs4 {
    template<std::totally_ordered Key>
    class MaxPQ : public PQBase<Key, std::less<Key> > {
    public:
        explicit MaxPQ(int maxN) : PQBase<Key, std::less<Key> >(maxN) {}

        std::optional<Key> delMax() { return this->delTop(); }
    };
}


#endif //ALGS4_MAXPQ_HPP
