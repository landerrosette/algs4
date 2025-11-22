#ifndef ALGS4_SUBSTRSEARCHER_H
#define ALGS4_SUBSTRSEARCHER_H


#include <string_view>

namespace algs4 {
    class SubstrSearcher {
    public:
        virtual ~SubstrSearcher() = default;

        virtual int search(std::string_view txt) const = 0;
    };
}


#endif //ALGS4_SUBSTRSEARCHER_H
