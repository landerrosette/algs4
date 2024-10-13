#ifndef UF_H
#define UF_H


#include <vector>

class UF {
private:
    std::vector<int> id; // 父链接数组（以触点为索引）
    std::vector<int> sz; // 各个根节点对应的分量的大小（以触点为索引）
    int count_;          // 分量数量

public:
    UF(int N);

    int count() const { return count_; }

    bool connected(int p, int q) const { return find(p) == find(q); }

    int find(int p) const;

    void unionize(int p, int q);
};


#endif //UF_H
