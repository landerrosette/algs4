#ifndef ACYCLICSP_H
#define ACYCLICSP_H


#include "SP.h"

class AcyclicSP : public SP {
public:
    AcyclicSP(const EdgeWeightedDigraph& G, int s);
};


#endif //ACYCLICSP_H
