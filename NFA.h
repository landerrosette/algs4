#ifndef NFA_H
#define NFA_H


#include "Digraph.h"
#include <string_view>
#include <string>

class NFA {
private:
    std::string re; // 匹配转换
    int M;          // 状态数量
    Digraph G;      // epsilon转换

public:
    explicit NFA(std::string_view regexp);

    bool recognizes(std::string_view txt) const;
};


#endif //NFA_H
