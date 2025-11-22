#ifndef ALGS4_KMP_H
#define ALGS4_KMP_H


#include <string>
#include <vector>

#include "SubstrSearcher.h"

namespace algs4 {
    class KMP : public SubstrSearcher {
    private:
        std::string pat;
        std::vector<std::vector<int> > dfa;

    public:
        explicit KMP(std::string pat);

        int search(std::string_view txt) const override;
    };
}


#endif //ALGS4_KMP_H
