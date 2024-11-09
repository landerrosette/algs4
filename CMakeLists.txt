cmake_minimum_required(VERSION 3.28)
project(algs4)

set(CMAKE_CXX_STANDARD 17)

# 1.5
add_executable(UF main_UF.cpp UF.cpp)

# 2.1, 2.2, 2.3, 2.4, 2.5, 2.7, 5.1, 5.2, 5.3
foreach (SORTER "Selection" "Insertion" "Shell" "Merge" "MergeBU" "Quick" "Quick3way" "Heap" "LSD" "MSD" "Quick3string")
    configure_file(main_Sorting.cpp.in main_${SORTER}.cpp @ONLY)

    add_executable(${SORTER} main_${SORTER}.cpp)

    target_include_directories(${SORTER} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    if (SORTER STREQUAL "LSD" OR SORTER STREQUAL "MSD" OR SORTER STREQUAL "Quick3string")
        target_sources(${SORTER} PRIVATE ${SORTER}.cpp)
    endif ()
endforeach ()

# 2.6
add_executable(MaxPQ main_MaxPQ.cpp)

# 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 5.4, 5.5
foreach (ST "SequentialSearchST" "BinarySearchST" "BST" "RedBlackBST" "SeparateChainingHashST" "LinearProbingHashST"
        "TrieST" "TST")
    if (ST STREQUAL "SeparateChainingHashST")
        set(ST_INIT_ARGS "4")
    elseif (ST STREQUAL "BinarySearchST")
        set(ST_INIT_ARGS "20")
    endif ()

    configure_file(main_ST.cpp.in main_${ST}.cpp @ONLY)

    add_executable(${ST} main_${ST}.cpp STTest.cpp)

    target_include_directories(${ST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    if (ST STREQUAL "BinarySearchST" OR ST STREQUAL "BST" OR ST STREQUAL "RedBlackBST")
        target_sources(${ST} PRIVATE OrderedSTTest.cpp)

        target_compile_definitions(${ST} PRIVATE ORDERED)
    elseif (ST STREQUAL "TrieST" OR ST STREQUAL "TST")
        target_sources(${ST} PRIVATE StringSTTest.cpp)

        target_compile_definitions(${ST} PRIVATE STRING)
    endif ()

    unset(ST_INIT_ARGS)
endforeach ()

# 4.1, 4.2
foreach (PATHS_SEARCHER "DepthFirstPaths" "BreadthFirstPaths")
    configure_file(main_Paths.cpp.in main_${PATHS_SEARCHER}.cpp @ONLY)

    add_executable(${PATHS_SEARCHER} main_${PATHS_SEARCHER}.cpp ${PATHS_SEARCHER}.cpp Paths.cpp Graph.cpp)

    target_include_directories(${PATHS_SEARCHER} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endforeach ()

# 4.3, 4.6
foreach (CC "CC" "KosarajuSCC")
    configure_file(main_CC.cpp.in main_${CC}.cpp @ONLY)

    add_executable(${CC} main_${CC}.cpp ${CC}.cpp CCBase.cpp)

    target_include_directories(${CC} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    if (CC STREQUAL "CC")
        target_sources(${CC} PRIVATE Graph.cpp)
    elseif (CC STREQUAL "KosarajuSCC")
        target_sources(${CC} PRIVATE Digraph.cpp)

        target_compile_definitions(${CC} PRIVATE DIRECTED)
    endif ()
endforeach ()

# 4.4
add_executable(DirectedDFS main_DirectedDFS.cpp DirectedDFS.cpp Digraph.cpp)

# 4.5
add_executable(Topological main_Topological.cpp SymbolDigraph.cpp Digraph.cpp)

# 4.7, 4.8
foreach (MST "PrimMST" "KruskalMST")
    configure_file(main_MST.cpp.in main_${MST}.cpp @ONLY)

    add_executable(${MST} main_${MST}.cpp ${MST}.cpp MST.cpp EdgeWeightedGraph.cpp Edge.cpp)

    target_include_directories(${MST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    if (MST STREQUAL "KruskalMST")
        target_sources(${MST} PRIVATE UF.cpp)
    endif ()
endforeach ()

# 4.9, 4.10, 4.11
foreach (SP "DijkstraSP" "AcyclicSP" "BellmanFordSP")
    configure_file(main_SP.cpp.in main_${SP}.cpp @ONLY)

    add_executable(${SP} main_${SP}.cpp ${SP}.cpp SP.cpp EdgeWeightedDigraph.cpp DirectedEdge.cpp)

    target_include_directories(${SP} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endforeach ()
