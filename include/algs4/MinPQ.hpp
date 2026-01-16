#ifndef ALGS4_MINPQ_HPP
#define ALGS4_MINPQ_HPP

#include <concepts>
#include <functional>

#include "PQBase.hpp"

namespace algs4 {
    template<std::totally_ordered Key>
    class MinPQ : public PQBase<Key, std::greater<Key> > {
    public:
        constexpr Key delMin() { return this->delTop(); }
    };
}

#endif // ALGS4_MINPQ_HPP
