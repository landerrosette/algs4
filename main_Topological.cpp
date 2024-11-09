/******************************************************************************
 *  % ./Topological jobs.txt "/"
 *  Calculus
 *  Linear Algebra
 *  Introduction to CS
 *  Advanced Programming
 *  Algorithms
 *  Theoretical CS
 *  Artificial Intelligence
 *  Robotics
 *  Machine Learning
 *  Neural Networks
 *  Databases
 *  Scientific Computing
 *  Computational Biology
 *
 ******************************************************************************/


#include <iostream>
#include "Topological.h"
#include "SymbolDigraph.h"

int main(int argc, char *argv[]) {
    SymbolDigraph sg(argv[1], *argv[2]);
    Topological top(sg.G());
    for (int v: top.order()) {
        std::cout << sg.name(v) << std::endl;
    }
    return 0;
}
