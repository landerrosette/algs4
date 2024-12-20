## Overview

<IMG SRC="http://algs4.cs.princeton.edu/cover.png"  align=right hspace=25 width=100 alt = "Algorithms 4/e textbook">
This repository contains C++ implementations of (most) algorithms and (a few) clients in the textbook
<a href = "http://amzn.to/13VNJi7">Algorithms, 4th Edition</a> by Robert Sedgewick and Kevin Wayne.

## Algorithms

### Fundamentals

- **1.5** Union-find: [UF.h](UF.h) | [UF.cpp](UF.cpp)

### Sorting

- **2.1** Selection sort: [Selection.h](Selection.h)
- **2.2** Insertion sort: [Insertion.h](Insertion.h)
- **2.3** Shellsort: [Shell.h](Shell.h)
- **2.4** Top-down mergesort: [Merge.h](Merge.h)
- Bottom-up mergesort: [MergeBU.h](MergeBU.h)
- **2.5** Quicksort: [Quick.h](Quick.h)
- Quicksort with 3-way partitioning: [Quick3way.h](Quick3way.h)
- **2.6** Heap priority queue: [MaxPQ.h](MaxPQ.h)
- **2.7** Heapsort: [Heap.h](Heap.h)

### Symbol Tables

- **3.1** Sequential search: [SequentialSearchST.h](SequentialSearchST.h)
- **3.2** Binary search: [BinarySearch.h](BinarySearchST.h)
- **3.3** Binary tree search: [BST.h](BST.h)
- **3.4** Red-black BST search: [RedBlackBST.h](RedBlackBST.h)
- **3.5** Hashing with separate chaining: [SeparateChainingHashST.h](SeparateChainingHashST.h)
- **3.6** Hashing with linear probing: [LinearProbingHashST.h](LinearProbingHashST.h)

### Graphs

- **4.1** Depth-first search: [DepthFirstPaths.h](DepthFirstPaths.h) | [DepthFirstPaths.cpp](DepthFirstPaths.cpp)
- **4.2** Breadth-first
  search: [BreadthFirstPaths.h](BreadthFirstPaths.h) | [BreadthFirstPaths.cpp](BreadthFirstPaths.cpp)
- **4.3** Connected components: [CC.h](CC.h) | [CC.cpp](CC.cpp)
- **4.4** Reachability: [DirectedDFS.h](DirectedDFS.h) | [DirectedDFS.cpp](DirectedDFS.cpp)
- **4.5** Topological order: [Topological.h](Topological.h)
- **4.6** Strong components (Kosaraju): [KosarajuSCC.h](KosarajuSCC.h) | [KosarajuSCC.cpp](KosarajuSCC.cpp)
- **4.7** Minimum spanning tree (Prim): [PrimMST.h](PrimMST.h) | [PrimMST.cpp](PrimMST.cpp)
- **4.8** Minimum spanning tree (Kruskal): [KruskalMST.h](KruskalMST.h) | [KruskalMST.cpp](KruskalMST.cpp)
- **4.9** Shortest paths (Dijkstra): [DijkstraSP.h](DijkstraSP.h) | [DijkstraSP.cpp](DijkstraSP.cpp)
- **4.10** Shortest paths in DAGs: [AcyclicSP.h](AcyclicSP.h) | [AcyclicSP.cpp](AcyclicSP.cpp)
- **4.11** Shortest paths (Bellman-Ford): [BellmanFord.h](BellmanFordSP.h) | [BellmanFord.cpp](BellmanFordSP.cpp)

### Strings

- **5.1** LSD string sort: [LSD.h](LSD.h) | [LSD.cpp](LSD.cpp)
- **5.2** MSD string sort: [MSD.h](MSD.h) | [MSD.cpp](MSD.cpp)
- **5.3** Three-way string quicksort: [Quick3string.h](Quick3string.h) | [Quick3string.cpp](Quick3string.cpp)
- **5.4** Trie symbol table: [TrieST.h](TrieST.h)
- **5.5** TST symbol table: [TST.h](TST.h)
- **5.6** Substring search (Knuth-Morris-Pratt): [KMP.h](KMP.h) | [KMP.cpp](KMP.cpp)
- **5.7** Substring search (Boyer-Moore): [BoyerMoore.h](BoyerMoore.h) | [BoyerMoore.cpp](BoyerMoore.cpp)
- **5.8** Substring search (Rabin-Karp): [RabinKarp.h](RabinKarp.h) | [RabinKarp.cpp](RabinKarp.cpp)
- **5.9** Regular expression pattern matching: [NFA.h](NFA.h) | [NFA.cpp](NFA.cpp)
- **5.10** Huffman compression/expansion: [Huffman.h](Huffman.h) | [Huffman.cpp](Huffman.cpp)
- **5.11** LZW compression/expansion: [LZW.h](LZW.h) | [LZW.cpp](LZW.cpp)

## Clients

### Fundamentals

- UF: [main_UF.cpp](main_UF.cpp)

### Sorting

- Selection | Insertion | Shell | Merge | MergeBU | Quick | Quick3way | Heap: [main_Sorting.cpp.in](main_Sorting.cpp.in)
- MaxPQ: [main_MaxPQ.cpp](main_MaxPQ.cpp)

### Symbol Tables

- TestSequentialSearchST | TestBinarySearchST | TestBST | TestRedBlackBST | TestSeparateChainingHashST |
  TestLinearProbingHashST: [main_TestST.cpp.in](main_TestST.cpp.in)

### Graphs

- DepthFirstPaths | BreadthFirstPaths: [main_Paths.cpp.in](main_Paths.cpp.in)
- CC | KosarajuSCC: [main_CC.cpp.in](main_CC.cpp.in)
- DirectedDFS: [main_DirectedDFS.cpp](main_DirectedDFS.cpp)
- Topological: [main_Topological.cpp](main_Topological.cpp)
- PrimMST | KruskalMST: [main_MST.cpp.in](main_MST.cpp.in)
- DijkstraSP | AcyclicSP | BellmanFordSP: [main_SP.cpp.in](main_SP.cpp.in)

### Strings

- LSD | MSD | Quick3string: [main_Sorting.cpp.in](main_Sorting.cpp.in)
- TestTrieST | TestTST: [main_TestST.cpp.in](main_TestST.cpp.in)
- KMP | BoyerMoore | RabinKarp: [main_SubstrSearch.cpp.in](main_SubstrSearch.cpp.in)
- GREP: [main_GREP.cpp](main_GREP.cpp)
- Huffman | LZW: [main_Compress.cpp.in](main_Compress.cpp.in)
- BinaryDump: [main_BinaryDump.cpp](main_BinaryDump.cpp)

## Build and Run

### Prerequisites

- CMake 3.20 or later
- C++ compiler with C++17 support

### Steps

1. Create and navigate to a build directory:

    ```shell
    mkdir build
    cd build
    ```

2. Configure and build all targets. This will produce all clients:

    ```shell
    cmake ..
    cmake --build .
    ```

   Alternatively, build a specific target that produces a specific client:

    ```shell
    cmake --build . --target UF
    ```

3. (Optional) Download sample input files from the book's website: https://algs4.cs.princeton.edu/code/.
4. Run the client. You may redirect the input from a file (possibly one obtained in step 3):

    ```shell
    ./UF < tinyUF.txt
    ```

   Some clients may expect command-line arguments. For example:

    ```shell
    ./DepthFirstPaths tinyCG.txt 0
    ```

   This will run `DepthFirstPaths` on the graph in `tinyCG.txt` starting from vertex 0.
