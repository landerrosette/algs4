#ifndef ALGS4_DIRECTEDEDGE_HPP
#define ALGS4_DIRECTEDEDGE_HPP

#include <iomanip>
#include <ostream>

#include "EdgeBase.hpp"

namespace algs4 {
    class DirectedEdge : public EdgeBase {
        friend std::ostream &operator<<(std::ostream &os, const DirectedEdge &e);

    public:
        constexpr DirectedEdge() = default;
        constexpr DirectedEdge(int v, int w, double weight) : EdgeBase(v, w, weight) {}

        constexpr int from() const { return v_; }
        constexpr int to() const { return w_; }
    };

    std::ostream &operator<<(std::ostream &os, const DirectedEdge &e);
}

inline std::ostream &algs4::operator<<(std::ostream &os, const DirectedEdge &e) {
    return os << e.v_ << "->" << e.w_ << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
}

#endif // ALGS4_DIRECTEDEDGE_HPP
