#ifndef ALGS4_STRINGST_HPP
#define ALGS4_STRINGST_HPP


#include <string>
#include <string_view>
#include <vector>

#include "ST.hpp"

namespace algs4 {
    template<typename Value>
    class StringST : public ST<std::string, Value> {
    public:
        virtual std::string longestPrefixOf(std::string_view s) const = 0;
        virtual std::vector<std::string> keysWithPrefix(const std::string &pre) const = 0;
        virtual std::vector<std::string> keysThatMatch(std::string_view pat) const = 0;
    };
}


#endif //ALGS4_STRINGST_HPP
