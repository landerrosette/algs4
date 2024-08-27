#ifndef ALGS4_TESTGRAPH_H
#define ALGS4_TESTGRAPH_H


#include <iostream>
#include <forward_list>
#include <string>
#include <sstream>

template<class Graph, class PathsSearcher>
void testPaths(const Graph &G) {
    std::cout << "Searching from: ";
    int s;
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
void testCC(const Graph &G) {
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

template<class Graph, class Searcher>
void testSearch(const Graph &G) {
    std::cout << "Searching from: ";
    std::string line;
    getline(std::cin, line);
    std::istringstream iss(line);
    std::forward_list<int> sources;
    int s;
    while (iss >> s) sources.push_front(s);

    Searcher search(G, sources);
    for (int v = 0; v < G.getV(); ++v) if (search.isMarked(v)) std::cout << v << " ";
    std::cout << "\n";
}

#endif //ALGS4_TESTGRAPH_H
