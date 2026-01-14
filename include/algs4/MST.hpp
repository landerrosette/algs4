#ifndef ALGS4_MST_HPP
#define ALGS4_MST_HPP


#include <vector>

#include "Edge.hpp"

namespace algs4 {
    class MST {
    protected:
        MST() = default;
        MST(const MST &) = default;
        MST &operator=(const MST &) = default;
        MST(MST &&) noexcept = default;
        MST &operator=(MST &&) noexcept = default;

    public:
        virtual ~MST() = default;

        virtual std::vector<Edge> edges() const = 0;
        double weight() const;
    };
}

inline double algs4::MST::weight() const {
    double weight = 0.0;
    for (const auto &e: edges())
        weight += e.weight();
    return weight;
}


#endif //ALGS4_MST_HPP
