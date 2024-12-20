#ifndef NFA_H
#define NFA_H


#include "Digraph.h"
#include <string_view>
#include <string>

class NFA {
private:
    std::string re; // match transitions
    int M;          // number of states
    Digraph G;      // epsilon transitions

public:
    explicit NFA(std::string_view regexp);

    bool recognizes(std::string_view txt) const;
};


#endif //NFA_H
