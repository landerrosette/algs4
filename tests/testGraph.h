#ifndef ALGS4_TESTGRAPH_H
#define ALGS4_TESTGRAPH_H


#include <filesystem>
#include <fstream>
#include <iostream>
#include <forward_list>

template<class Graph, class PathsSearcher>
void testPaths(const std::filesystem::path &dataFilePath) {
    std::cout << "Reading graph from file" << "\n";
    std::ifstream dataFile(dataFilePath);
    Graph G(dataFile);
    std::cout << G << "\n";

    int s;
    std::cout << "Searching for paths from: ";
    std::cin >> s;
    PathsSearcher search(G, s);
    for (int v = 0; v < G.getV(); ++v) {
        std::cout << s << " to " << v << ": ";
        if (search.hasPathTo(v)) {
            for (int x: search.pathTo(v)) {
                if (x == s) std::cout << x;
                else std::cout << "-" << x;
            }
        }
        std::cout << "\n";
    }
}

template<class Graph, class CC>
void testCC(const std::filesystem::path &dataFilePath) {
    std::cout << "Reading graph from file" << "\n";
    std::ifstream dataFile(dataFilePath);
    Graph G(dataFile);
    std::cout << G << "\n";

    CC cc(G);
    int M = cc.getCount();
    std::cout << M << " components" << "\n";

    std::forward_list<int> components[M];
    for (int v = 0; v < G.getV(); ++v) components[cc.getId(v)].push_front(v);
    for (int i = 0; i < M; ++i) {
        for (int v: components[i]) std::cout << v << " ";
        std::cout << "\n";
    }
}

#endif //ALGS4_TESTGRAPH_H
