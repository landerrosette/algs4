#ifndef ALGS4_UF_H
#define ALGS4_UF_H


#include <vector>

namespace algs4 {
    class UF {
    private:
        std::vector<int> id; // parent link (site indexed)
        std::vector<int> sz; // size of component for roots (site indexed)
        int count_;          // number of components

    public:
        explicit UF(int N);

        int count() const { return count_; }
        bool connected(int p, int q) const { return find(p) == find(q); }
        int find(int p) const;
        void unionize(int p, int q);
    };
}

inline algs4::UF::UF(int N) : id(N), sz(N), count_(N) {
    for (int i = 0; i < N; i++) {
        id[i] = i;
        sz[i] = 1;
    }
}

inline int algs4::UF::find(int p) const {
    while (p != id[p])
        p = id[p];
    return p;
}

inline void algs4::UF::unionize(int p, int q) {
    int i = find(p);
    int j = find(q);
    if (i == j)
        return;
    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    } else {
        id[j] = i;
        sz[i] += sz[j];
    }
    --count_;
}


#endif //ALGS4_UF_H
