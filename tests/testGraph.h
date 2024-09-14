#ifndef ALGS4_TESTGRAPH_H
#define ALGS4_TESTGRAPH_H


#include <iostream>
#include <forward_list>
#include <string>
#include <sstream>

template<class GraphType, class PathsSearcher>
void testPaths(const GraphType &G);

template<class GraphType, class CCSearcher>
void testCC(const GraphType &G);

template<class GraphType, class Searcher>
void testSearch(const GraphType &G);

template<class GraphType, class Sorter>
void testSort(const GraphType &G);

template<class GraphType, class PathsSearcher>
void testPaths(const GraphType &G) {
    std::cout << "Vertex to search from: ";
    int s;
    std::cin >> s;

    PathsSearcher search(G, s);
    for (int v = 0; v < G.V(); ++v) {
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

template<class GraphType, class CCSearcher>
void testCC(const GraphType &G) {
    CCSearcher cc(G);
    int M = cc.count();
    std::cout << M << " components" << "\n";

    std::forward_list<int> components[M];
    for (int v = 0; v < G.V(); ++v) components[cc.id(v)].push_front(v);
    for (int i = 0; i < M; ++i) {
        for (int v: components[i]) std::cout << v << " ";
        std::cout << "\n";
    }
}

template<class GraphType, class Searcher>
void testSearch(const GraphType &G) {
    std::cout << "Vertices to search from: ";
    std::string line;
    std::getline(std::cin, line);
    std::istringstream iss(line);
    std::forward_list<int> sources;
    int s;
    while (iss >> s) sources.push_front(s);

    Searcher search(G, sources);
    for (int v = 0; v < G.V(); ++v) {
        if (search.marked(v)) std::cout << v << " ";
    }
    std::cout << "\n";
}

template<class GraphType, class Sorter>
void testSort(const GraphType &G) {
    Sorter order(G.G());
    for (int v: order.order()) {
        std::cout << G.name(v) << "\n";
    }
}


#endif //ALGS4_TESTGRAPH_H
