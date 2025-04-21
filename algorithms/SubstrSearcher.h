#ifndef SUBSTRSEARCHER_H
#define SUBSTRSEARCHER_H


#include <string_view>

class SubstrSearcher {
public:
    virtual ~SubstrSearcher() = default;

    virtual int search(std::string_view txt) const = 0;
};


#endif //SUBSTRSEARCHER_H
