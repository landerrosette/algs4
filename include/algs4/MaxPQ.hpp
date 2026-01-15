#ifndef ALGS4_MAXPQ_HPP
#define ALGS4_MAXPQ_HPP


#include <concepts>
#include <functional>

#include "PQBase.hpp"

namespace algs4 {
    template<std::totally_ordered Key>
    class MaxPQ : public PQBase<Key, std::less<Key> > {
    public:
        constexpr Key delMax() { return this->delTop(); }
    };
}


#endif //ALGS4_MAXPQ_HPP
