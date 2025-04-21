#ifndef NFA_H
#define NFA_H


#include <string>
#include <string_view>

#include "Digraph.h"

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
