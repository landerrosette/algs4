#ifndef NFA_H
#define NFA_H


#include "Digraph.h"
#include <vector>
#include <string_view>

class NFA {
private:
    std::vector<char> re; // 匹配转换
    int M;                // 状态数量
    Digraph G;            // epsilon转换

public:
    explicit NFA(std::string_view regexp);

    bool recognizes(std::string_view txt) const;
};


#endif //NFA_H
