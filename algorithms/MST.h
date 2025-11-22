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


#endif //ALGS4_MST_H
