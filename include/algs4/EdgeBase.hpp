#ifndef ALGS4_EDGEBASE_HPP
#define ALGS4_EDGEBASE_HPP

#include <cassert>
#include <compare>
#include <limits>

namespace algs4 {
    class EdgeBase {
    protected:
        int v_, w_;
        double weight_ = std::numeric_limits<double>::quiet_NaN();

        constexpr EdgeBase() = default;
        constexpr EdgeBase(int v, int w, double weight);
        constexpr ~EdgeBase() = default;
        constexpr EdgeBase(const EdgeBase &) = default;
        constexpr EdgeBase &operator=(const EdgeBase &) = default;
        constexpr EdgeBase(EdgeBase &&) noexcept = default;
        constexpr EdgeBase &operator=(EdgeBase &&) noexcept = default;

    public:
        constexpr double weight() const { return weight_; }
        constexpr explicit operator bool() const { return weight_ == weight_; }
    };

    constexpr auto operator<=>(const EdgeBase &l, const EdgeBase &r) { return l.weight() <=> r.weight(); }
    constexpr bool operator==(const EdgeBase &l, const EdgeBase &r) { return l.weight() == r.weight(); }
}

constexpr algs4::EdgeBase::EdgeBase(int v, int w, double weight) : v_(v), w_(w), weight_(weight) {
    assert(v >= 0);
    assert(w >= 0);
    assert(weight == weight);
}

#endif // ALGS4_EDGEBASE_HPP
