#ifndef STRINGST_H
#define STRINGST_H


#include "ST.h"
#include <string>
#include <list>
#include <string_view>

template<typename Value>
class StringST : public ST<std::string, Value> {
public:
    virtual std::string longestPrefixOf(std::string_view s) const = 0;

    virtual std::list<std::string> keysWithPrefix(const std::string &pre) const = 0;

    virtual std::list<std::string> keysThatMatch(std::string_view pat) const = 0;
};


#endif //STRINGST_H
