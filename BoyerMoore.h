#ifndef BOYERMOORE_H
#define BOYERMOORE_H


#include "SubstrSearcher.h"
#include <vector>

class BoyerMoore : public SubstrSearcher {
private:
    std::vector<int> right;
    std::string pat;

public:
    explicit BoyerMoore(const std::string &pat);

    int search(const std::string &txt) const override;
};


#endif //BOYERMOORE_H
