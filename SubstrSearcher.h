#ifndef SUBSTRSEARCHER_H
#define SUBSTRSEARCHER_H


#include <string>

class SubstrSearcher {
public:
    virtual ~SubstrSearcher() = default;

    virtual int search(const std::string &txt) const = 0;
};


#endif //SUBSTRSEARCHER_H
