#ifndef ALGS4_UF_H
#define ALGS4_UF_H


#include <vector>

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


#endif //ALGS4_UF_H
