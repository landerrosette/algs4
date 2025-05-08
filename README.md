## Overview

<IMG SRC="http://algs4.cs.princeton.edu/cover.png"  align=right hspace=25 width=100 alt = "Algorithms 4/e textbook"> This repository contains C++ implementations of the algorithms and clients in the textbook <a href = "http://amzn.to/13VNJi7">Algorithms, 4th Edition</a> by Robert Sedgewick and Kevin Wayne.

For the original Java source code, visit the <a href = "https://github.com/kevin-wayne/algs4">official repository</a>.

## Algorithms

### Fundamentals

- **1.5** Union-find: [UF.h](algorithms/UF.h) | [UF.cpp](algorithms/UF.cpp)

### Sorting

- **2.1** Selection sort: [Selection.h](algorithms/Selection.h)
- **2.2** Insertion sort: [Insertion.h](algorithms/Insertion.h)
- **2.3** Shellsort: [Shell.h](algorithms/Shell.h)
- **2.4** Top-down mergesort: [Merge.h](algorithms/Merge.h)
- Bottom-up mergesort: [MergeBU.h](algorithms/MergeBU.h)
- **2.5** Quicksort: [Quick.h](algorithms/Quick.h)
- Quicksort with 3-way partitioning: [Quick3way.h](algorithms/Quick3way.h)
- **2.6** Heap priority queue: [MaxPQ.h](algorithms/MaxPQ.h)
- **2.7** Heapsort: [Heap.h](algorithms/Heap.h)

### Symbol Tables

- **3.1** Sequential search: [SequentialSearchST.h](algorithms/SequentialSearchST.h)
- **3.2** Binary search: [BinarySearchST.h](algorithms/BinarySearchST.h)
- **3.3** Binary tree search: [BST.h](algorithms/BST.h)
- **3.4** Red-black BST search: [RedBlackBST.h](algorithms/RedBlackBST.h)
- **3.5** Hashing with separate chaining: [SeparateChainingHashST.h](algorithms/SeparateChainingHashST.h)
- **3.6** Hashing with linear probing: [LinearProbingHashST.h](algorithms/LinearProbingHashST.h)

### Graphs

- **4.1** Depth-first
  search: [DepthFirstPaths.h](algorithms/DepthFirstPaths.h) | [DepthFirstPaths.cpp](algorithms/DepthFirstPaths.cpp)
- **4.2** Breadth-first
  search: [BreadthFirstPaths.h](algorithms/BreadthFirstPaths.h) | [BreadthFirstPaths.cpp](algorithms/BreadthFirstPaths.cpp)
- **4.3** Connected components: [CC.h](algorithms/CC.h) | [CC.cpp](algorithms/CC.cpp)
- **4.4** Reachability: [DirectedDFS.h](algorithms/DirectedDFS.h) | [DirectedDFS.cpp](algorithms/DirectedDFS.cpp)
- **4.5** Topological order: [Topological.h](algorithms/Topological.h)
- **4.6** Strong components (Kosaraju):
  [KosarajuSCC.h](algorithms/KosarajuSCC.h) | [KosarajuSCC.cpp](algorithms/KosarajuSCC.cpp)
- **4.7** Minimum spanning tree (Prim): [PrimMST.h](algorithms/PrimMST.h) | [PrimMST.cpp](algorithms/PrimMST.cpp)
- **4.8** Minimum spanning tree (Kruskal):
  [KruskalMST.h](algorithms/KruskalMST.h) | [KruskalMST.cpp](algorithms/KruskalMST.cpp)
- **4.9** Shortest paths (Dijkstra):
  [DijkstraSP.h](algorithms/DijkstraSP.h) | [DijkstraSP.cpp](algorithms/DijkstraSP.cpp)
- **4.10** Shortest paths in DAGs: [AcyclicSP.h](algorithms/AcyclicSP.h) | [AcyclicSP.cpp](algorithms/AcyclicSP.cpp)
- **4.11** Shortest paths (Bellman-Ford):
  [BellmanFord.h](algorithms/BellmanFordSP.h) | [BellmanFord.cpp](algorithms/BellmanFordSP.cpp)

### Strings

- **5.1** LSD string sort: [LSD.h](algorithms/LSD.h) | [LSD.cpp](algorithms/LSD.cpp)
- **5.2** MSD string sort: [MSD.h](algorithms/MSD.h) | [MSD.cpp](algorithms/MSD.cpp)
- **5.3** Three-way string quicksort:
  [Quick3string.h](algorithms/Quick3string.h) | [Quick3string.cpp](algorithms/Quick3string.cpp)
- **5.4** Trie symbol table: [TrieST.h](algorithms/TrieST.h)
- **5.5** TST symbol table: [TST.h](algorithms/TST.h)
- **5.6** Substring search (Knuth-Morris-Pratt): [KMP.h](algorithms/KMP.h) | [KMP.cpp](algorithms/KMP.cpp)
- **5.7** Substring search (Boyer-Moore):
  [BoyerMoore.h](algorithms/BoyerMoore.h) | [BoyerMoore.cpp](algorithms/BoyerMoore.cpp)
- **5.8** Substring search (Rabin-Karp):
  [RabinKarp.h](algorithms/RabinKarp.h) | [RabinKarp.cpp](algorithms/RabinKarp.cpp)
- **5.9** Regular expression pattern matching: [NFA.h](algorithms/NFA.h) | [NFA.cpp](algorithms/NFA.cpp)
- **5.10** Huffman compression/expansion: [Huffman.h](algorithms/Huffman.h) | [Huffman.cpp](algorithms/Huffman.cpp)
- **5.11** LZW compression/expansion: [LZW.h](algorithms/LZW.h) | [LZW.cpp](algorithms/LZW.cpp)

## Clients

### Fundamentals

- Union-find (`UF`): [main_UF.cpp](clients/main_UF.cpp)

### Sorting

- Sorts (`Selection`, `Insertion`, `Shell`, `Merge`, `MergeBU`, `Quick`, `Quick3way`, `Heap`): [main_Sorting.cpp.in](clients/main_Sorting.cpp.in)
- Heap priority queue (`MaxPQ`): [main_MaxPQ.cpp](clients/main_MaxPQ.cpp)

### Symbol Tables

- Symbol table tests (`TestSequentialSearchST`, `TestBinarySearchST`, `TestBST`, `TestRedBlackBST`, `TestSeparateChainingHashST`, `TestLinearProbingHashST`): [main_TestST.cpp.in](clients/main_TestST.cpp.in)

### Graphs

- Depth-first search (`DepthFirstPaths`) | Breadth-first search (`BreadthFirstPaths`): [main_Paths.cpp.in](clients/main_Paths.cpp.in)
- Connected components (`CC`, `KosarajuSCC`): [main_CC.cpp.in](clients/main_CC.cpp.in)
- Reachability (`DirectedDFS`): [main_DirectedDFS.cpp](clients/main_DirectedDFS.cpp)
- Topological order (`Topological`): [main_Topological.cpp](clients/main_Topological.cpp)
- Minimum spanning tree (`PrimMST`, `KruskalMST`): [main_MST.cpp.in](clients/main_MST.cpp.in)
- Shortest paths (`DijkstraSP`, `AcyclicSP`, `BellmanFordSP`): [main_SP.cpp.in](clients/main_SP.cpp.in)

### Strings

- String sorts (`LSD`, `MSD`, `Quick3string`): [main_Sorting.cpp.in](clients/main_Sorting.cpp.in)
- Trie symbol table tests (`TestTrieST`) | TST symbol table tests (`TestTST`): [main_TestST.cpp.in](clients/main_TestST.cpp.in)
- Substring search (`KMP`, `BoyerMoore`, `RabinKarp`): [main_SubstrSearch.cpp.in](clients/main_SubstrSearch.cpp.in)
- Regular expression pattern matching (`GREP`): [main_GREP.cpp](clients/main_GREP.cpp)
- Huffman compression/expansion (`Huffman`) | LZW compression/expansion (`LZW`): [main_Compress.cpp.in](clients/main_Compress.cpp.in)

## Build and Run

1. Configure the project in the `build` directory.

    ```shell
    cmake -B build
    ```

2. Build all clients.

    ```shell
    cmake --build build
    ```

   Alternatively, you can build only a specific client (e.g., the "Union-find" client).

    ```shell
    cmake --build build --target UF
    ```

3. (Optional) Download sample input files from the book's website: https://algs4.cs.princeton.edu/code/.
4. From the `build` directory, run the client. You may redirect the input from a file (possibly one obtained in step 3).

    ```shell
    ./UF < tinyUF.txt
    ```

   You may also pipe the output of one client to the input of another.

    ```shell
    ./Huffman - < abra.txt | ./Huffman +
    ```

   Some clients expect command-line arguments.

    ```shell
    ./DepthFirstPaths tinyCG.txt 0
    ```

   This will run depth-first search on the graph in `tinyCG.txt` starting from vertex 0.
