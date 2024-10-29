# Algorithms 4th Edition in C++

This repository provides C++ implementations of the algorithms from the book *Algorithms, 4th Edition* by Robert
Sedgewick and Kevin Wayne. These implementations adhere closely to the original Java code from the book, while
incorporating modern C++ practices.

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
- ...

## Build and Run

To compile and run this project, ensure you have CMake 3.28 or higher and a C++17 compatible compiler. Follow these
steps:

1. Clone this repository and navigate to the cloned directory.
2. Create a build directory and compile the project using the following commands:
    ```shell
    mkdir build && cd build
    cmake ..
    cmake --build .
    ```
3. Once the build is complete, you can run the program by providing the path to an input file as a command-line
   argument:
   ```shell
   ./algs4 path/to/input_file.txt
   ```
   Input files correspond to different tests and data sets. For example:
   ```shell
   ./algs4 ../data/words3.txt
   ```
   This will execute tests for sorting algorithms.
4. Some of the tests require additional arguments. For example:
   ```shell
   ./algs4 ../data/tinyDG.txt 1 2 6
   ```
   This will run directed graph algorithms, with vertices 1, 2, and 6 as starting points for the search.
