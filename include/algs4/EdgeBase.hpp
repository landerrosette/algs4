#ifndef ALGS4_EDGEBASE_HPP
#define ALGS4_EDGEBASE_HPP


#include <cassert>
#include <cmath>
#include <compare>

namespace algs4 {
    class EdgeBase {
    protected:
        int v, w;
        double weight_;

        EdgeBase(int v, int w, double weight);
        ~EdgeBase() = default;

    public:
        double weight() const { return weight_; }
    };

    inline auto operator<=>(const EdgeBase &l, const EdgeBase &r) { return l.weight() <=> r.weight(); }
    inline bool operator==(const EdgeBase &l, const EdgeBase &r) { return l.weight() == r.weight(); }
}

inline algs4::EdgeBase::EdgeBase(int v, int w, double weight) : v(v), w(w), weight_(weight) {
    assert(v >= 0);
    assert(w >= 0);
    assert(!std::isnan(weight));
}


#endif //ALGS4_EDGEBASE_HPP
