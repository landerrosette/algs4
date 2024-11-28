#ifndef BOYERMOORE_H
#define BOYERMOORE_H


#include "SubstrSearcher.h"
#include <vector>
#include <string>

class BoyerMoore : public SubstrSearcher {
private:
    std::vector<int> right;
    std::string pat;

public:
    explicit BoyerMoore(std::string pat);

    int search(std::string_view txt) const override;
};


#endif //BOYERMOORE_H
