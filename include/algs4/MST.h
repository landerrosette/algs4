#ifndef ALGS4_MST_H
#define ALGS4_MST_H


#include <list>

#include "Edge.h"

namespace algs4 {
    class MST {
    public:
        virtual ~MST() = default;

        virtual std::list<Edge> edges() const = 0;
        double weight() const;
    };
}

inline double algs4::MST::weight() const {
    double weight = 0.0;
    for (const auto &e: edges())
        weight += e.weight();
    return weight;
}


#endif //ALGS4_MST_H
