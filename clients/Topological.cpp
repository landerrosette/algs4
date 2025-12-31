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


#include "algs4/Topological.h"

#include <iostream>

#include "algs4/SymbolDigraph.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    try {
        algs4::SymbolDigraph sg(argv[1], *argv[2]);
        algs4::Topological top(sg.G());
        for (int v: top.order())
            std::cout << sg.name(v) << std::endl;
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
