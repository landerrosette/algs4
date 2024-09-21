#ifndef SP_H
#define SP_H


#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include <list>
#include <vector>
#include <limits>

class SP {
protected:
    std::vector<DirectedEdge> edgeTo;
    std::vector<double> distTo_;

    void relax(const EdgeWeightedDigraph& G, int v);

    virtual void onRelax(const DirectedEdge& e, int w) {}

public:
    SP(const EdgeWeightedDigraph& G, int s);

    virtual ~SP() = default;

    double distTo(int v) const { return distTo_[v]; }

    bool hasPathTo(int v) const { return distTo_[v] < std::numeric_limits<double>::infinity(); }

    std::list<DirectedEdge> pathTo(int v) const;
};


#endif //SP_H
