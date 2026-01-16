#ifndef ALGS4_UF_HPP
#define ALGS4_UF_HPP

#include <cassert>
#include <vector>

namespace algs4 {
    class UF {
    private:
        std::vector<int> id_; // parent link (site indexed)
        std::vector<int> sz_; // size of component for roots (site indexed)
        int count_;           // number of components

    public:
        constexpr explicit UF(int N);

        constexpr int count() const { return count_; }
        constexpr bool connected(int p, int q) const { return find(p) == find(q); }
        constexpr int find(int p) const;
        constexpr void unionize(int p, int q);
    };
}

constexpr algs4::UF::UF(int N) : id_(N), sz_(N), count_(N) {
    assert(N >= 0);
    for (int i = 0; i < N; i++) {
        id_[i] = i;
        sz_[i] = 1;
    }
}

constexpr int algs4::UF::find(int p) const {
    assert(p >= 0 && p < std::ssize(id_));
    while (p != id_[p])
        p = id_[p];
    return p;
}

constexpr void algs4::UF::unionize(int p, int q) {
    int i = find(p);
    int j = find(q);
    if (i == j)
        return;
    if (sz_[i] < sz_[j]) {
        id_[i] = j;
        sz_[j] += sz_[i];
    } else {
        id_[j] = i;
        sz_[i] += sz_[j];
    }
    --count_;
}

#endif // ALGS4_UF_HPP
