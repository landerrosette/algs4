set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 1.5
add_executable(UF main_UF.cpp)
target_link_libraries(UF PRIVATE algs4)

# 2.1, 2.2, 2.3, 2.4, 2.5, 2.7, 5.1, 5.2, 5.3
foreach (SORTER "Selection" "Insertion" "Shell" "Merge" "MergeBU" "Quick" "Quick3way" "Heap" "LSD" "MSD" "Quick3string")
    configure_file(main_Sorting.cpp.in main_${SORTER}.cpp @ONLY)
    add_executable(${SORTER} main_${SORTER}.cpp)
    target_link_libraries(${SORTER} PRIVATE algs4)
endforeach ()

# 2.6
add_executable(MaxPQ main_MaxPQ.cpp)
target_link_libraries(MaxPQ PRIVATE algs4)

# 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 5.4, 5.5
foreach (ST "SequentialSearchST" "BinarySearchST" "BST" "RedBlackBST" "SeparateChainingHashST" "LinearProbingHashST"
        "TrieST" "TST")
    if (ST STREQUAL "SeparateChainingHashST")
        set(ST_INIT_ARGS "4")
    elseif (ST STREQUAL "BinarySearchST")
        set(ST_INIT_ARGS "20")
    endif ()

    configure_file(main_TestST.cpp.in main_Test${ST}.cpp @ONLY)
    add_executable(Test${ST} main_Test${ST}.cpp TestST.cpp)
    target_link_libraries(Test${ST} PRIVATE algs4)
    target_include_directories(Test${ST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    if (ST STREQUAL "BinarySearchST" OR ST STREQUAL "BST" OR ST STREQUAL "RedBlackBST")
        target_compile_definitions(Test${ST} PRIVATE ORDERED)
        target_sources(Test${ST} PRIVATE TestOrderedST.cpp)
    endif ()

    if (ST STREQUAL "TrieST" OR ST STREQUAL "TST")
        target_compile_definitions(Test${ST} PRIVATE STRING)
        target_sources(Test${ST} PRIVATE TestStringST.cpp)
    endif ()

    if (ST STREQUAL "RedBlackBST")
        target_compile_definitions(Test${ST} PRIVATE BALANCED_TREE)
        target_sources(Test${ST} PRIVATE TestBalancedTree.cpp)
    endif ()

    unset(ST_INIT_ARGS)
endforeach ()

# 4.1, 4.2
foreach (PATHS_SEARCHER "DepthFirstPaths" "BreadthFirstPaths")
    configure_file(main_Paths.cpp.in main_${PATHS_SEARCHER}.cpp @ONLY)
    add_executable(${PATHS_SEARCHER} main_${PATHS_SEARCHER}.cpp)
    target_link_libraries(${PATHS_SEARCHER} PRIVATE algs4_algorithms)
endforeach ()

# 4.3, 4.6
foreach (CC "CC" "KosarajuSCC")
    configure_file(main_CC.cpp.in main_${CC}.cpp @ONLY)
    add_executable(${CC} main_${CC}.cpp)
    target_link_libraries(${CC} PRIVATE algs4_algorithms)

    if (CC STREQUAL "KosarajuSCC")
        target_compile_definitions(${CC} PRIVATE DIRECTED)
    endif ()
endforeach ()

# 4.4
add_executable(DirectedDFS main_DirectedDFS.cpp)
target_link_libraries(DirectedDFS PRIVATE algs4_algorithms)

# 4.5
add_executable(Topological main_Topological.cpp)
target_link_libraries(Topological PRIVATE algs4_algorithms)

# 4.7, 4.8
foreach (MST "PrimMST" "KruskalMST")
    configure_file(main_MST.cpp.in main_${MST}.cpp @ONLY)
    add_executable(${MST} main_${MST}.cpp)
    target_link_libraries(${MST} PRIVATE algs4_algorithms)
endforeach ()

# 4.9, 4.10, 4.11
foreach (SP "DijkstraSP" "AcyclicSP" "BellmanFordSP")
    configure_file(main_SP.cpp.in main_${SP}.cpp @ONLY)
    add_executable(${SP} main_${SP}.cpp)
    target_link_libraries(${SP} PRIVATE algs4_algorithms)
endforeach ()

# 5.6, 5.7, 5.8
foreach (SUBSTR_SEARCHER "KMP" "BoyerMoore" "RabinKarp")
    configure_file(main_SubstrSearch.cpp.in main_${SUBSTR_SEARCHER}.cpp @ONLY)
    add_executable(${SUBSTR_SEARCHER} main_${SUBSTR_SEARCHER}.cpp)
    target_link_libraries(${SUBSTR_SEARCHER} PRIVATE algs4_algorithms)
endforeach ()

# 5.9
add_executable(GREP main_GREP.cpp)
target_link_libraries(GREP PRIVATE algs4_algorithms)

# 5.10, 5.11
foreach (COMPRESSOR "Huffman" "LZW")
    configure_file(main_Compress.cpp.in main_${COMPRESSOR}.cpp @ONLY)
    add_executable(${COMPRESSOR} main_${COMPRESSOR}.cpp)
    target_link_libraries(${COMPRESSOR} PRIVATE algs4_algorithms)
endforeach ()
add_executable(BinaryDump main_BinaryDump.cpp)
target_link_libraries(BinaryDump PRIVATE algs4_algorithms)
