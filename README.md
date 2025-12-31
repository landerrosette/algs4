## Overview

This repository contains C++ implementations of the algorithms and clients in the textbook *Algorithms, 4th Edition* by
Robert Sedgewick and Kevin Wayne.

For the original Java source code, visit the [official repository](https://github.com/kevin-wayne/algs4).

## Algorithms

### Fundamentals

- **1.5** Union-find: [UF.h](include/algs4/UF.h)

### Sorting

- **2.1** Selection sort: [Selection.h](include/algs4/Selection.h)
- **2.2** Insertion sort: [Insertion.h](include/algs4/Insertion.h)
- **2.3** Shellsort: [Shell.h](include/algs4/Shell.h)
- **2.4** Top-down mergesort: [Merge.h](include/algs4/Merge.h)
- Bottom-up mergesort: [MergeBU.h](include/algs4/MergeBU.h)
- **2.5** Quicksort: [Quick.h](include/algs4/Quick.h)
- Quicksort with 3-way partitioning: [Quick3way.h](include/algs4/Quick3way.h)
- **2.6** Heap priority queue: [MaxPQ.h](include/algs4/MaxPQ.h)
- **2.7** Heapsort: [Heap.h](include/algs4/Heap.h)

### Symbol Tables

- **3.1** Sequential search: [SequentialSearchST.h](include/algs4/SequentialSearchST.h)
- **3.2** Binary search: [BinarySearchST.h](include/algs4/BinarySearchST.h)
- **3.3** Binary tree search: [BST.h](include/algs4/BST.h)
- **3.4** Red-black BST search: [RedBlackBST.h](include/algs4/RedBlackBST.h)
- **3.5** Hashing with separate chaining: [SeparateChainingHashST.h](include/algs4/SeparateChainingHashST.h)
- **3.6** Hashing with linear probing: [LinearProbingHashST.h](include/algs4/LinearProbingHashST.h)

### Graphs

- **4.1** Depth-first search: [DepthFirstPaths.h](include/algs4/DepthFirstPaths.h)
- **4.2** Breadth-first search: [BreadthFirstPaths.h](include/algs4/BreadthFirstPaths.h)
- **4.3** Connected components: [CC.h](include/algs4/CC.h)
- **4.4** Reachability: [DirectedDFS.h](include/algs4/DirectedDFS.h)
- **4.5** Topological order: [Topological.h](include/algs4/Topological.h)
- **4.6** Strong components (Kosaraju): [KosarajuSCC.h](include/algs4/KosarajuSCC.h)
- **4.7** Minimum spanning tree (Prim): [PrimMST.h](include/algs4/PrimMST.h)
- **4.8** Minimum spanning tree (Kruskal): [KruskalMST.h](include/algs4/KruskalMST.h)
- **4.9** Shortest paths (Dijkstra): [DijkstraSP.h](include/algs4/DijkstraSP.h)
- **4.10** Shortest paths in DAGs: [AcyclicSP.h](include/algs4/AcyclicSP.h)
- **4.11** Shortest paths (Bellman-Ford): [BellmanFordSP.h](include/algs4/BellmanFordSP.h)

### Strings

- **5.1** LSD string sort: [LSD.h](include/algs4/LSD.h)
- **5.2** MSD string sort: [MSD.h](include/algs4/MSD.h)
- **5.3** Three-way string quicksort: [Quick3string.h](include/algs4/Quick3string.h)
- **5.4** Trie symbol table: [TrieST.h](include/algs4/TrieST.h)
- **5.5** TST symbol table: [TST.h](include/algs4/TST.h)
- **5.6** Substring search (Knuth-Morris-Pratt): [KMP.h](include/algs4/KMP.h)
- **5.7** Substring search (Boyer-Moore): [BoyerMoore.h](include/algs4/BoyerMoore.h)
- **5.8** Substring search (Rabin-Karp): [RabinKarp.h](include/algs4/RabinKarp.h)
- **5.9** Regular expression pattern matching: [NFA.h](include/algs4/NFA.h)
- **5.10** Huffman compression/expansion: [Huffman.h](include/algs4/Huffman.h)
- **5.11** LZW compression/expansion: [LZW.h](include/algs4/LZW.h)

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

### Build the project

This project uses CMake as the build system. Ensure you have CMake 3.21+ and a C++20 compliant compiler.

```shell
cmake -B build
cmake --build build
```

### Run the clients

By default, all clients are built and the executables can be found in the build directory. Refer to the comments in the
source files listed in [Clients](#clients) for instructions on how to run each client. Go to
the [book's website](https://algs4.cs.princeton.edu/code/) for test data.

### Use as a header-only library

#### Option A: CMake `add_subdirectory`

Add to your `CMakeLists.txt`:

```cmake
add_subdirectory(/path/to/algs4)
target_link_libraries(your_target PRIVATE algs4)
```

#### Option B: Simple include

If you are not using CMake, simply ensure the `include/` directory is in your compiler's include path and include the
headers you need. For example:

```cpp
#include <iostream>
#include <string>

#include "algs4/BST.h"

int main() {
    algs4::BST<std::string, int> st;
    
    st.put("A", 1);
    st.put("B", 2);
    
    if (const auto &val = st.get("A"))
        std::cout << "Key A has value: " << *val << std::endl;
    
    return 0;
}
```
