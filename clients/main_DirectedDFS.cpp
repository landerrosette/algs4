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


#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "DirectedDFS.h"

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    Digraph G(in);
    std::list<int> sources;
    for (int i = 2; i < argc; ++i) sources.push_front(std::stoi(argv[i]));
    DirectedDFS reachable(G, sources);
    for (int v = 0; v < G.V(); ++v) {
        if (reachable.marked(v)) std::cout << v << " ";
    }
    std::cout << std::endl;
    return 0;
}
