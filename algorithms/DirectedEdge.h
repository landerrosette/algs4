#ifndef ALGS4_DIRECTEDEDGE_H
#define ALGS4_DIRECTEDEDGE_H


#include <iostream>

#include "EdgeBase.h"

namespace algs4 {
    class DirectedEdge : public EdgeBase {
        friend std::ostream &operator<<(std::ostream &os, const DirectedEdge &e);

    public:
        DirectedEdge(int v, int w, double weight) : EdgeBase(v, w, weight) {}

        int from() const { return v; }
        int to() const { return w; }
    };

    std::ostream &operator<<(std::ostream &os, const DirectedEdge &e);
}


#endif //ALGS4_DIRECTEDEDGE_H
