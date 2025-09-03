#ifndef ALGS4_BOYERMOORE_H
#define ALGS4_BOYERMOORE_H


#include <string>
#include <vector>

#include "SubstrSearcher.h"

class BoyerMoore : public SubstrSearcher {
private:
    std::vector<int> right;
    std::string pat;

public:
    explicit BoyerMoore(std::string pat);

    int search(std::string_view txt) const override;
};


#endif //ALGS4_BOYERMOORE_H