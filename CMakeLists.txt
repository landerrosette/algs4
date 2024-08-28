cmake_minimum_required(VERSION 3.28)
project(algs4)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(algs4
        Insertion.h
        main.cpp
        Merge.h
        MergeBU.h
        Quick.h
        Selection.h
        Shell.h
        Sorting.h
        Quick3way.h
        Heap.h
        MaxPQ.h
        SequentialSearchST.h
        ST.h
        BinarySearchST.h
        BST.h
        OrderedST.h
        tests/testSort.h
        tests/testPQ.h
        tests/testPQ.cpp
        tests/testST.h
        tests/testST.cpp
        RedBlackBST.h
        SeparateChainingHashST.h
        LinearProbingHashST.h
        Graph.cpp
        Graph.h
        Paths.h
        Paths.cpp
        DepthFirstPaths.cpp
        DepthFirstPaths.h
        tests/testGraph.h
        BreadthFirstPaths.cpp
        BreadthFirstPaths.h
        Digraph.cpp
        Digraph.h
        CC.cpp
        CC.h
        DirectedDFS.cpp
        DirectedDFS.h
        DirectedCycle.cpp
        DirectedCycle.h
        DepthFirstOrder.cpp
        DepthFirstOrder.h
        SymbolDigraph.cpp
        SymbolDigraph.h
        Topological.cpp
        Topological.h
)
