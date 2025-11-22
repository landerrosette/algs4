#ifndef ALGS4_SP_H
#define ALGS4_SP_H


#include <limits>
#include <list>
#include <optional>
#include <vector>

#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"

namespace algs4 {
    class SP {
    protected:
        std::vector<std::optional<DirectedEdge> > edgeTo;
        std::vector<double> distTo_;

        void relax(const EdgeWeightedDigraph &G, int v);
        virtual void onRelaxationSuccess(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {}
        virtual void afterRelaxation(const EdgeWeightedDigraph &G, int v, const DirectedEdge &e, int w) {}

    public:
        SP(const EdgeWeightedDigraph &G, int s);
        virtual ~SP() = default;

        double distTo(int v) const { return distTo_[v]; }
        bool hasPathTo(int v) const { return distTo_[v] < std::numeric_limits<double>::infinity(); }
        std::list<DirectedEdge> pathTo(int v) const;
    };
}


#endif //ALGS4_SP_H
