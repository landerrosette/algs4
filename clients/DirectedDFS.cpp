/******************************************************************************
 *  % ./DirectedDFS tinyDG.txt 1
 *  1
 *
 *  % ./DirectedDFS tinyDG.txt 2
 *  0 1 2 3 4 5
 *
 *  % ./DirectedDFS tinyDG.txt 1 2 6
 *  0 1 2 3 4 5 6 8 9 10 11 12
 *
 ******************************************************************************/


#include "algs4/DirectedDFS.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Cannot open file: " << argv[1] << std::endl;
        return 1;
    }
    algs4::Digraph G(in);
    std::vector<int> sources;
    for (int i = 2; i < argc; ++i) {
        int s = std::stoi(argv[i]);
        if (s < 0 || s >= G.V()) {
            std::cerr << "Source vertex out of range" << std::endl;
            return 1;
        }
        sources.push_back(s);
    }
    std::ranges::reverse(sources);
    algs4::DirectedDFS reachable(G, sources);
    for (int v = 0; v < G.V(); ++v)
        if (reachable.marked(v))
            std::cout << v << " ";
    std::cout << std::endl;
    return 0;
}
