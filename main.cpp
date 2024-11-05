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
#include "AcyclicSP.h"
#include "BellmanFordSP.h"
#include "LSD.h"
#include "MSD.h"
#include "Quick3string.h"
#include "TrieST.h"
#include "TST.h"
#include "tests/testUF.h"
#include "tests/testSort.h"
#include "tests/testPQ.h"
#include "tests/testST.h"
#include "tests/testGraph.h"

int main(int argc, char *argv[]) {
    if (std::filesystem::path dataFilePath(argv[1]); dataFilePath.filename() == "tinyUF.txt") {
        // 测试union-find
        // Example: ./algs4 ../data/tinyUF.txt
        std::cout << "Testing 1.5 union-find" << std::endl;
        std::cout << "======================================================" << std::endl;
        testUF(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "words3.txt" || dataFilePath.filename() == "shells.txt") {
        // 测试排序算法
        // Example: ./algs4 ../data/words3.txt
        // Example: ./algs4 ../data/shells.txt
        std::cout << "Testing 2.1 selection sort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Selection>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 2.2 insertion sort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Insertion>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 2.3 shellsort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Shell>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 2.4 top-down mergesort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Merge>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing bottom-up mergesort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<MergeBU>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 2.5 quicksort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Quick>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing quicksort with 3-way partitioning" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Quick3way>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 2.7 heapsort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Heap>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 5.1 LSD string sort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<LSD>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 5.2 MSD string sort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<MSD>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 5.3 three-way string quicksort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSort<Quick3string>(std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "tinyPQ.txt") {
        // 测试优先队列
        // Example: ./algs4 ../data/tinyPQ.txt
        std::cout << "Testing 2.6 heap priority queue" << std::endl;
        std::cout << "======================================================" << std::endl;
        testPQ(MaxPQ<std::string>(10), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "tinyST.txt") {
        // 测试搜索算法
        // Example: ./algs4 ../data/tinyST.txt
        std::cout << "Testing 3.1 sequential search" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(SequentialSearchST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 3.2 binary search" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(BinarySearchST<std::string, int>(20), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 3.3 binary tree search" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(BST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 3.4 red-black BST search" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(RedBlackBST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 3.5 hashing with separate chaining" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(SeparateChainingHashST<std::string, int>(3), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 3.6 hashing with linear probing" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(LinearProbingHashST<std::string, int>(), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "tinyCG.txt" || dataFilePath.filename() == "tinyG.txt") {
        // 测试无向图相关算法
        // Example: ./algs4 ../data/tinyCG.txt 0
        // Example: ./algs4 ../data/tinyG.txt 0
        Graph G([&dataFilePath] {
            std::cout << "Reading graph from file" << std::endl;
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << std::endl;
        int s = std::stoi(argv[2]);

        std::cout << "Testing 4.1 depth-first search" << std::endl;
        std::cout << "======================================================" << std::endl;
        testPaths(G, s, DepthFirstPaths(G, s));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 4.2 breadth-first search" << std::endl;
        std::cout << "======================================================" << std::endl;
        testPaths(G, s, BreadthFirstPaths(G, s));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 4.3 connected components" << std::endl;
        std::cout << "======================================================" << std::endl;
        testCC(G, CC(G));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "tinyDG.txt") {
        // 测试有向图相关算法
        // Example: ./algs4 ../data/tinyDG.txt 1 2 6
        Digraph G([&dataFilePath] {
            std::cout << "Reading graph from file" << std::endl;
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << std::endl;
        std::list<int> sources;
        for (int i = 2; i < argc; ++i) sources.push_front(std::stoi(argv[i]));

        std::cout << "Testing 4.4 reachability" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSearch(G, DirectedDFS(G, sources));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 4.6 strong components (Kosaraju)" << std::endl;
        std::cout << "======================================================" << std::endl;
        testCC(G, KosarajuSCC(G));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "jobs.txt") {
        // 测试符号图相关算法
        // Example: ./algs4 ../data/jobs.txt "/"
        std::cout << "Reading graph from file" << std::endl;
        SymbolDigraph sg(dataFilePath, *argv[2]);

        std::cout << "Testing 4.5 topological sort" << std::endl;
        std::cout << "======================================================" << std::endl;
        testTopological(sg, Topological(sg.G()));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "tinyEWG.txt") {
        // 测试加权无向图相关算法
        // Example: ./algs4 ../data/tinyEWG.txt
        EdgeWeightedGraph G([&dataFilePath] {
            std::cout << "Reading graph from file" << std::endl;
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << std::endl;

        std::cout << "Testing 4.7 minimum spanning tree (Prim)" << std::endl;
        std::cout << "======================================================" << std::endl;
        testMST(G, PrimMST(G));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 4.8 minimum spanning tree (Kruskal)" << std::endl;
        std::cout << "======================================================" << std::endl;
        testMST(G, KruskalMST(G));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "tinyEWD.txt" || dataFilePath.filename() == "tinyEWDAG.txt" || dataFilePath.
               filename() == "tinyEWDn.txt") {
        // 测试加权有向图相关算法
        // Example: ./algs4 ../data/tinyEWD.txt 0
        // Example: ./algs4 ../data/tinyEWDAG.txt 5
        // Example: ./algs4 ../data/tinyEWDn.txt 0
        EdgeWeightedDigraph G([&dataFilePath] {
            std::cout << "Reading graph from file" << std::endl;
            return std::ifstream(dataFilePath);
        }());
        std::cout << G << std::endl;
        int s = std::stoi(argv[2]);

        std::cout << "Testing 4.9 shortest paths (Dijkstra)" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSP(G, s, DijkstraSP(G, s));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 4.10 shortest paths in DAGs" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSP(G, s, AcyclicSP(G, s));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 4.11 shortest paths (Bellman-Ford)" << std::endl;
        std::cout << "======================================================" << std::endl;
        testSP(G, s, BellmanFordSP(G, s));
        std::cout << "======================================================" << std::endl;
    } else if (dataFilePath.filename() == "shellsST.txt") {
        // 测试单词查找树
        // Example: ./algs4 ../data/shellsST.txt
        std::cout << "Testing 5.4 trie symbol table" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(TrieST<int>(), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl << std::endl;
        std::cout << "Testing 5.5 TST symbol table" << std::endl;
        std::cout << "======================================================" << std::endl;
        testST(TST<int>(), std::ifstream(dataFilePath));
        std::cout << "======================================================" << std::endl;
    }
    return 0;
}
