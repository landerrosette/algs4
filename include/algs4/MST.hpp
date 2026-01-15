#ifndef ALGS4_MST_HPP
#define ALGS4_MST_HPP


#include <vector>

#include "Edge.hpp"

namespace algs4 {
    class MST {
    protected:
        constexpr MST() = default;
        constexpr MST(const MST &) = default;
        constexpr MST &operator=(const MST &) = default;
        constexpr MST(MST &&) noexcept = default;
        constexpr MST &operator=(MST &&) noexcept = default;

    public:
        virtual constexpr ~MST() = default;

        virtual constexpr std::vector<Edge> edges() const = 0;
        constexpr double weight() const;
    };
}

constexpr double algs4::MST::weight() const {
    double weight = 0.0;
    for (const auto &e: edges())
        weight += e.weight();
    return weight;
}


#endif //ALGS4_MST_HPP
