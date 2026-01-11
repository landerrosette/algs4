#ifndef ALGS4_SUBSTRSEARCHER_HPP
#define ALGS4_SUBSTRSEARCHER_HPP


#include <cstddef>
#include <string_view>

namespace algs4 {
    class SubstrSearcher {
    public:
        virtual ~SubstrSearcher() = default;

        virtual std::ptrdiff_t search(std::string_view txt) const = 0;
    };
}


#endif //ALGS4_SUBSTRSEARCHER_HPP
