#ifndef KMP_H
#define KMP_H


#include "SubstrSearcher.h"
#include <vector>
#include <string>

class KMP : public SubstrSearcher {
private:
    std::string pat;
    std::vector<std::vector<int> > dfa;

public:
    explicit KMP(std::string pat);

    int search(std::string_view txt) const override;
};


#endif //KMP_H
