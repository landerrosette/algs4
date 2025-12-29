#ifndef ALGS4_DIRECTEDEDGE_H
#define ALGS4_DIRECTEDEDGE_H


#include <iomanip>
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

inline std::ostream &algs4::operator<<(std::ostream &os, const DirectedEdge &e) {
    return os << e.v << "->" << e.w << " " << std::fixed << std::setprecision(2) << e.weight_ << " ";
}


#endif //ALGS4_DIRECTEDEDGE_H
