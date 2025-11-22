#ifndef ALGS4_CC_H
#define ALGS4_CC_H


#include "CCBase.h"
#include "Graph.h"

namespace algs4 {
    class CC : public CCBase {
    public:
        explicit CC(const Graph &G);
    };
}


#endif //ALGS4_CC_H