#ifndef KMP_H
#define KMP_H


#include "SubstrSearcher.h"
#include <vector>

class KMP : public SubstrSearcher {
private:
    std::string pat;
    std::vector<std::vector<int> > dfa;

public:
    KMP(const std::string &pat);

    int search(const std::string &txt) const override;
};


#endif //KMP_H
