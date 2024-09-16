#ifndef ALGS4_MST_H
#define ALGS4_MST_H


#include "Edge.h"
#include <forward_list>

class MST {
public:
    virtual ~MST() = default;

    virtual std::forward_list<Edge> edges() const = 0;

    virtual double weight() const = 0;
};


#endif //ALGS4_MST_H
