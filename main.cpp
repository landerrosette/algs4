#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <list>
#include "Selection.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"
#include "MergeBU.h"
#include "Quick.h"
#include "Quick3way.h"
#include "Heap.h"
#include "MaxPQ.h"
#include "SequentialSearchST.h"
#include "BinarySearchST.h"
#include "BST.h"
#include "RedBlackBST.h"
#include "SeparateChainingHashST.h"
#include "LinearProbingHashST.h"
#include "Graph.h"
#include "Digraph.h"
#include "SymbolDigraph.h"
#include "EdgeWeightedGraph.h"
#include "EdgeWeightedDigraph.h"
#include "DepthFirstPaths.h"
#include "BreadthFirstPaths.h"
#include "CC.h"
#include "DirectedDFS.h"
#include "Topological.h"
#include "KosarajuSCC.h"
#include "PrimMST.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"
#include "tests/testUF.h"
#include "tests/testSort.h"
#include "tests/testPQ.h"
#include "tests/testST.h"
#include "tests/testGraph.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // 测试union-find
        // ./algs4 < ../data/tinyUF.txt
        std::cout << "Testing 1.5 union-find" << "\n";
        std::cout << "================================================" << "\n";
        testUF();
        std::cout << "================================================" << "\n";
    } else if (std::filesystem::path dataFilePath(argv[1]); dataFilePath.filename() == "words3.txt") {
        // 测试排序算法
        // ./algs4 ../data/words3.txt
        std::cout << "Testing 2.1 selection sort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Selection>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.2 insertion sort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Insertion>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.3 shellsort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Shell>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.4 top-down mergesort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Merge>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing bottom-up mergesort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<MergeBU>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.5 quicksort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Quick>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing quicksort with 3-way partitioning" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Quick3way>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.7 heapsort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Heap>(std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyPQ.txt") {
        // 测试优先队列
        // ./algs4 ../data/tinyPQ.txt
        std::cout << "Testing 2.6 heap priority queue" << "\n";
        std::cout << "================================================" << "\n";
        testPQ(MaxPQ<std::string>(10), std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyST.txt") {
        // 测试搜索算法
        // ./algs4 ../data/tinyST.txt
        std::cout << "Testing 3.1 sequential search" << "\n";
        std::cout << "================================================" << "\n";
        testBasicST(SequentialSearchST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.2 binary search" << "\n";
        std::cout << "================================================" << "\n";
        testOrderedST(BinarySearchST<std::string, int>(20), std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.3 binary tree search" << "\n";
        std::cout << "================================================" << "\n";
        testOrderedST(BST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.4 red-black BST search" << "\n";
        std::cout << "================================================" << "\n";
        testOrderedST(RedBlackBST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.5 hashing with separate chaining" << "\n";
        std::cout << "================================================" << "\n";
        testBasicST(SeparateChainingHashST<std::string, int>(3), std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.6 hashing with linear probing" << "\n";
        std::cout << "================================================" << "\n";
        testBasicST(LinearProbingHashST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyCG.txt" || dataFilePath.filename() == "tinyG.txt") {
        // 测试无向图相关算法
        // ./algs4 ../data/tinyCG.txt 0
        Graph G([&dataFilePath] {
            std::cout << "Reading graph from file" << "\n";
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << "\n";
        int s = std::stoi(argv[2]);

        std::cout << "Testing 4.1 depth-first search" << "\n";
        std::cout << "================================================" << "\n";
        testPaths(G, s, DepthFirstPaths(G, s));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 4.2 breadth-first search" << "\n";
        std::cout << "================================================" << "\n";
        testPaths(G, s, BreadthFirstPaths(G, s));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 4.3 connected components" << "\n";
        std::cout << "================================================" << "\n";
        testCC(G, CC(G));
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyDG.txt") {
        // 测试有向图相关算法
        // ./algs4 ../data/tinyDG.txt 1 2 6
        Digraph G([&dataFilePath] {
            std::cout << "Reading graph from file" << "\n";
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << "\n";
        std::list<int> sources;
        for (int i = 2; i < argc; ++i) sources.push_front(std::stoi(argv[i]));

        std::cout << "Testing 4.4 reachability" << "\n";
        std::cout << "================================================" << "\n";
        testSearch(G, DirectedDFS(G, sources));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 4.6 strong components (Kosaraju)" << "\n";
        std::cout << "================================================" << "\n";
        testCC(G, KosarajuSCC(G));
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "jobs.txt") {
        // 测试符号图相关算法
        // ./algs4 ../data/jobs.txt "/"
        std::cout << "Reading graph from file" << "\n";
        SymbolDigraph sg(dataFilePath, *argv[2]);

        std::cout << "Testing 4.5 topological sort" << "\n";
        std::cout << "================================================" << "\n";
        testTopological(sg, Topological(sg.G()));
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyEWG.txt") {
        // 测试加权无向图相关算法
        // ./algs4 ../data/tinyEWG.txt
        EdgeWeightedGraph G([&dataFilePath] {
            std::cout << "Reading graph from file" << "\n";
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << "\n";

        std::cout << "Testing 4.7 minimum spanning tree (Prim)" << "\n";
        std::cout << "================================================" << "\n";
        testMST(G, PrimMST(G));
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 4.8 minimum spanning tree (Kruskal)" << "\n";
        std::cout << "================================================" << "\n";
        testMST(G, KruskalMST(G));
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyEWD.txt") {
        // 测试加权有向图相关算法
        // ./algs4 ../data/tinyEWD.txt 0
        EdgeWeightedDigraph G([&dataFilePath] {
            std::cout << "Reading graph from file" << "\n";
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << "\n";
        int s = std::stoi(argv[2]);

        std::cout << "Testing 4.9 shortest paths (Dijkstra)" << "\n";
        std::cout << "================================================" << "\n";
        testSP(G, s, DijkstraSP(G, s));
        std::cout << "================================================" << "\n";
    }
    return 0;
}
