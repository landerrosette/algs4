## Overview

This repository contains C++ implementations of the algorithms and clients in the textbook *Algorithms, 4th Edition* by
Robert Sedgewick and Kevin Wayne.

For the original Java source code, visit the [official repository](https://github.com/kevin-wayne/algs4).

## Algorithms

### Fundamentals

- **1.1** Pushdown stack (resizing array): [Stack.hpp](include/algs4/Stack.hpp)
- **1.3** FIFO queue: [Queue.hpp](include/algs4/Queue.hpp)
- **1.4** Bag: [Bag.hpp](include/algs4/Bag.hpp)
- **1.5** Union-find: [UF.hpp](include/algs4/UF.hpp)

### Sorting

- **2.1** Selection sort: [Selection.hpp](include/algs4/Selection.hpp)
- **2.2** Insertion sort: [Insertion.hpp](include/algs4/Insertion.hpp)
- **2.3** Shellsort: [Shell.hpp](include/algs4/Shell.hpp)
- **2.4** Top-down mergesort: [Merge.hpp](include/algs4/Merge.hpp)
- Bottom-up mergesort: [MergeBU.hpp](include/algs4/MergeBU.hpp)
- **2.5** Quicksort: [Quick.hpp](include/algs4/Quick.hpp)
- Quicksort with 3-way partitioning: [Quick3way.hpp](include/algs4/Quick3way.hpp)
- **2.6** Heap priority queue: [MaxPQ.hpp](include/algs4/MaxPQ.hpp)
- **2.7** Heapsort: [Heap.hpp](include/algs4/Heap.hpp)

### Symbol Tables

- **3.1** Sequential search: [SequentialSearchST.hpp](include/algs4/SequentialSearchST.hpp)
- **3.2** Binary search: [BinarySearchST.hpp](include/algs4/BinarySearchST.hpp)
- **3.3** Binary tree search: [BST.hpp](include/algs4/BST.hpp)
- **3.4** Red-black BST search: [RedBlackBST.hpp](include/algs4/RedBlackBST.hpp)
- **3.5** Hashing with separate chaining: [SeparateChainingHashST.hpp](include/algs4/SeparateChainingHashST.hpp)
- **3.6** Hashing with linear probing: [LinearProbingHashST.hpp](include/algs4/LinearProbingHashST.hpp)

### Graphs

- **4.1** Depth-first search: [DepthFirstPaths.hpp](include/algs4/DepthFirstPaths.hpp)
- **4.2** Breadth-first search: [BreadthFirstPaths.hpp](include/algs4/BreadthFirstPaths.hpp)
- **4.3** Connected components: [CC.hpp](include/algs4/CC.hpp)
- **4.4** Reachability: [DirectedDFS.hpp](include/algs4/DirectedDFS.hpp)
- **4.5** Topological order: [Topological.hpp](include/algs4/Topological.hpp)
- **4.6** Strong components (Kosaraju): [KosarajuSCC.hpp](include/algs4/KosarajuSCC.hpp)
- **4.7** Minimum spanning tree (Prim): [PrimMST.hpp](include/algs4/PrimMST.hpp)
- **4.8** Minimum spanning tree (Kruskal): [KruskalMST.hpp](include/algs4/KruskalMST.hpp)
- **4.9** Shortest paths (Dijkstra): [DijkstraSP.hpp](include/algs4/DijkstraSP.hpp)
- **4.10** Shortest paths in DAGs: [AcyclicSP.hpp](include/algs4/AcyclicSP.hpp)
- **4.11** Shortest paths (Bellman-Ford): [BellmanFordSP.hpp](include/algs4/BellmanFordSP.hpp)

### Strings

- **5.1** LSD string sort: [LSD.hpp](include/algs4/LSD.hpp)
- **5.2** MSD string sort: [MSD.hpp](include/algs4/MSD.hpp)
- **5.3** Three-way string quicksort: [Quick3string.hpp](include/algs4/Quick3string.hpp)
- **5.4** Trie symbol table: [TrieST.hpp](include/algs4/TrieST.hpp)
- **5.5** TST symbol table: [TST.hpp](include/algs4/TST.hpp)
- **5.6** Substring search (Knuth-Morris-Pratt): [KMP.hpp](include/algs4/KMP.hpp)
- **5.7** Substring search (Boyer-Moore): [BoyerMoore.hpp](include/algs4/BoyerMoore.hpp)
- **5.8** Substring search (Rabin-Karp): [RabinKarp.hpp](include/algs4/RabinKarp.hpp)
- **5.9** Regular expression pattern matching: [NFA.hpp](include/algs4/NFA.hpp)
- **5.10** Huffman compression/expansion: [Huffman.hpp](include/algs4/Huffman.hpp)
- **5.11** LZW compression/expansion: [LZW.hpp](include/algs4/LZW.hpp)

## Clients

### Fundamentals

- Union-find (`UF`): [UF.cpp](clients/UF.cpp)

### Sorting

- Sorts (`Selection`, `Insertion`, `Shell`, `Merge`, `MergeBU`, `Quick`, `Quick3way`, `Heap`):
  [Sorting.cpp.in](clients/Sorting.cpp.in)
- Heap priority queue (`MaxPQ`): [MaxPQ.cpp](clients/MaxPQ.cpp)

### Symbol Tables

- Symbol table tests (`TestSequentialSearchST`, `TestBinarySearchST`, `TestBST`, `TestRedBlackBST`,
  `TestSeparateChainingHashST`, `TestLinearProbingHashST`): [TestST.cpp.in](clients/TestST.cpp.in)

### Graphs

- Depth-first search (`DepthFirstPaths`) | Breadth-first search (`BreadthFirstPaths`):
  [Paths.cpp.in](clients/Paths.cpp.in)
- Connected components (`CC`, `KosarajuSCC`): [CC.cpp.in](clients/CC.cpp.in)
- Reachability (`DirectedDFS`): [DirectedDFS.cpp](clients/DirectedDFS.cpp)
- Topological order (`Topological`): [Topological.cpp](clients/Topological.cpp)
- Minimum spanning tree (`PrimMST`, `KruskalMST`): [MST.cpp.in](clients/MST.cpp.in)
- Shortest paths (`DijkstraSP`, `AcyclicSP`, `BellmanFordSP`): [SP.cpp.in](clients/SP.cpp.in)

### Strings

- String sorts (`LSD`, `MSD`, `Quick3string`): [Sorting.cpp.in](clients/Sorting.cpp.in)
- Trie symbol table tests (`TestTrieST`) | TST symbol table tests (`TestTST`): [TestST.cpp.in](clients/TestST.cpp.in)
- Substring search (`KMP`, `BoyerMoore`, `RabinKarp`): [SubstrSearch.cpp.in](clients/SubstrSearch.cpp.in)
- Regular expression pattern matching (`GREP`): [GREP.cpp](clients/GREP.cpp)
- Huffman compression/expansion (`Huffman`) | LZW compression/expansion (`LZW`):
  [Compress.cpp.in](clients/Compress.cpp.in)

## Usage

### Build

This project uses CMake as the build system. Ensure you have CMake 3.21+ and a C++20 compliant compiler.

```shell
cmake -B build
cmake --build build
```

### Run clients

By default, all clients are built and the executables can be found in the build directory. Refer to the comments in the
source files listed in [Clients](#clients) for instructions on how to run each client. Go to
the [book's website](https://algs4.cs.princeton.edu/code/) for test data.

### Use as header-only library

#### Option A: CMake `add_subdirectory`

Add to your `CMakeLists.txt`:

```cmake
add_subdirectory(/path/to/algs4)
target_link_libraries(your_target PRIVATE algs4)
```

#### Option B: Manual integration

If you are not using CMake, simply ensure the `include/` directory is in your compiler's include path and include the
headers you need.
