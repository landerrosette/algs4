#include <iostream>
#include <string>
#include <filesystem>
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
#include "DepthFirstPaths.h"
#include "BreadthFirstPaths.h"
#include "CC.h"
#include "DirectedDFS.h"
#include "SymbolDigraph.h"
#include "KosarajuSCC.h"
#include "tests/testSort.h"
#include "tests/testPQ.h"
#include "tests/testST.h"
#include "tests/testGraph.h"

int main(int argc, char *argv[]) {
    std::filesystem::path dataFilePath(argv[1]);
    if (dataFilePath.filename() == "words3.txt") {
        // 测试排序算法
        // words3.txt
        std::cout << "Testing 2.1 selection sort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Selection>(dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.2 insertion sort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Insertion>(dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.3 shellsort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Shell>(dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.4 top-down mergesort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Merge>(dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing bottom-up mergesort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<MergeBU>(dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.5 quicksort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Quick>(dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing quicksort with 3-way partitioning" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Quick3way>(dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 2.7 heapsort" << "\n";
        std::cout << "================================================" << "\n";
        testSort<Heap>(dataFilePath);
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyPQ.txt") {
        // 测试优先队列
        // tinyPQ.txt
        std::cout << "Testing 2.6 heap priority queue" << "\n";
        std::cout << "================================================" << "\n";
        testPQ(MaxPQ<std::string>(10), dataFilePath);
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyST.txt") {
        // 测试搜索算法
        // tinyST.txt
        std::cout << "Testing 3.1 sequential search" << "\n";
        std::cout << "================================================" << "\n";
        testBasicST(SequentialSearchST<std::string, int>(), dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.2 binary search" << "\n";
        std::cout << "================================================" << "\n";
        testOrderedST(BinarySearchST<std::string, int>(20), dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.3 binary tree search" << "\n";
        std::cout << "================================================" << "\n";
        testOrderedST(BST<std::string, int>(), dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.4 red-black BST search" << "\n";
        std::cout << "================================================" << "\n";
        testOrderedST(RedBlackBST<std::string, int>(), dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.5 hashing with separate chaining" << "\n";
        std::cout << "================================================" << "\n";
        testBasicST(SeparateChainingHashST<std::string, int>(3), dataFilePath);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 3.6 hashing with linear probing" << "\n";
        std::cout << "================================================" << "\n";
        testBasicST(LinearProbingHashST<std::string, int>(), dataFilePath);
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyG.txt") {
        // 测试无向图相关算法
        // tinyG.txt
        std::cout << "Reading graph from file" << "\n";
        std::ifstream dataFile(dataFilePath);
        Graph G(dataFile);
        std::cout << G << "\n";

        std::cout << "Testing 4.1 depth-first search" << "\n";
        std::cout << "================================================" << "\n";
        testPaths<Graph, DepthFirstPaths>(G);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 4.2 breadth-first search" << "\n";
        std::cout << "================================================" << "\n";
        testPaths<Graph, BreadthFirstPaths>(G);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 4.3 connected components" << "\n";
        std::cout << "================================================" << "\n";
        testCC<Graph, CC>(G);
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "tinyDG.txt") {
        // 测试有向图相关算法
        // tinyDG.txt
        std::cout << "Reading graph from file" << "\n";
        std::ifstream dataFile(dataFilePath);
        Digraph G(dataFile);
        std::cout << G << "\n";

        std::cout << "Testing 4.4 reachability" << "\n";
        std::cout << "================================================" << "\n";
        testSearch<Digraph, DirectedDFS>(G);
        std::cout << "================================================" << "\n" << "\n";
        std::cout << "Testing 4.6 strong components (Kosaraju)" << "\n";
        std::cout << "================================================" << "\n";
        testCC<Digraph, KosarajuSCC>(G);
        std::cout << "================================================" << "\n";
    } else if (dataFilePath.filename() == "jobs.txt") {
        // 测试符号图相关算法
        // jobs.txt
        std::cout << "Reading graph from file" << "\n";
        std::cout << "Separator: ";
        char separator;
        std::cin.get(separator);
        SymbolDigraph sg(dataFilePath, separator);
        std::cout << "\n";

        std::cout << "Testing 4.5 topological sort" << "\n";
        std::cout << "================================================" << "\n";
        testTopoSort(sg);
        std::cout << "================================================" << "\n";
    }
    return 0;
}
