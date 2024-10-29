#ifndef STRINGST_H
#define STRINGST_H


#include "ST.h"
#include <string>
#include <list>

template<typename Value>
class StringST : public ST<std::string, Value> {
public:
    virtual std::string longestPrefixOf(const std::string &s) const = 0;

    virtual std::list<std::string> keysWithPrefix(const std::string &pre) const = 0;

    virtual std::list<std::string> keysThatMatch(const std::string &pat) const = 0;
};


#endif //STRINGST_H
