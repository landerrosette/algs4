#ifndef ALGS4_MINPQ_HPP
#define ALGS4_MINPQ_HPP


#include <concepts>
#include <functional>
#include <optional>

#include "PQBase.hpp"

namespace algs4 {
    template<std::totally_ordered Key>
    class MinPQ : public PQBase<Key, std::greater<Key> > {
    public:
        explicit MinPQ(std::ptrdiff_t maxN) : PQBase<Key, std::greater<Key> >(maxN) {}

        std::optional<Key> delMin() { return this->delTop(); }
    };
}


#endif //ALGS4_MINPQ_HPP
