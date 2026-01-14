set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# 1.5
add_executable(UF UF.cpp)
target_link_libraries(UF PRIVATE algs4)

# 2.1, 2.2, 2.3, 2.4, 2.5, 2.7, 5.1, 5.2, 5.3
foreach (SORTER "Selection" "Insertion" "Shell" "Merge" "MergeBU" "Quick" "Quick3way" "Heap" "LSD" "MSD" "Quick3string")
    configure_file(Sorting.cpp.in ${SORTER}.cpp @ONLY)
    add_executable(${SORTER} ${SORTER}.cpp)
    target_link_libraries(${SORTER} PRIVATE algs4)
endforeach ()

# 2.6
add_executable(MaxPQ MaxPQ.cpp)
target_link_libraries(MaxPQ PRIVATE algs4)

# 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 5.4, 5.5
foreach (ST "SequentialSearchST" "BinarySearchST" "BST" "RedBlackBST" "SeparateChainingHashST" "LinearProbingHashST"
        "TrieST" "TST")
    if (ST STREQUAL "SeparateChainingHashST")
        set(ST_INIT_ARGS "4")
    endif ()

    configure_file(TestST.cpp.in Test${ST}.cpp @ONLY)
    add_executable(Test${ST} Test${ST}.cpp STTestUtils.cpp)
    target_link_libraries(Test${ST} PRIVATE algs4)
    target_include_directories(Test${ST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    if (ST STREQUAL "BinarySearchST" OR ST STREQUAL "BST" OR ST STREQUAL "RedBlackBST")
        target_compile_definitions(Test${ST} PRIVATE ORDERED)
        target_sources(Test${ST} PRIVATE OrderedSTTestUtils.cpp)
    endif ()

    if (ST STREQUAL "TrieST" OR ST STREQUAL "TST")
        target_compile_definitions(Test${ST} PRIVATE STRING)
        target_sources(Test${ST} PRIVATE StringSTTestUtils.cpp)
    endif ()

    if (ST STREQUAL "RedBlackBST")
        target_compile_definitions(Test${ST} PRIVATE BALANCED_TREE)
        target_sources(Test${ST} PRIVATE BalancedTreeTestUtils.cpp)
    endif ()

    unset(ST_INIT_ARGS)
endforeach ()

# 4.1, 4.2
foreach (PATHS_SEARCHER "DepthFirstPaths" "BreadthFirstPaths")
    configure_file(Paths.cpp.in ${PATHS_SEARCHER}.cpp @ONLY)
    add_executable(${PATHS_SEARCHER} ${PATHS_SEARCHER}.cpp)
    target_link_libraries(${PATHS_SEARCHER} PRIVATE algs4)
endforeach ()

# 4.3, 4.6
foreach (CC "CC" "KosarajuSCC")
    configure_file(CC.cpp.in ${CC}.cpp @ONLY)
    add_executable(${CC} ${CC}.cpp)
    target_link_libraries(${CC} PRIVATE algs4)

    if (CC STREQUAL "KosarajuSCC")
        target_compile_definitions(${CC} PRIVATE DIRECTED)
    endif ()
endforeach ()

# 4.4
add_executable(DirectedDFS DirectedDFS.cpp)
target_link_libraries(DirectedDFS PRIVATE algs4)

# 4.5
add_executable(Topological Topological.cpp)
target_link_libraries(Topological PRIVATE algs4)

# 4.7, 4.8
foreach (MST "PrimMST" "KruskalMST")
    configure_file(MST.cpp.in ${MST}.cpp @ONLY)
    add_executable(${MST} ${MST}.cpp)
    target_link_libraries(${MST} PRIVATE algs4)
endforeach ()

# 4.9, 4.10, 4.11
foreach (SP "DijkstraSP" "AcyclicSP" "BellmanFordSP")
    configure_file(SP.cpp.in ${SP}.cpp @ONLY)
    add_executable(${SP} ${SP}.cpp)
    target_link_libraries(${SP} PRIVATE algs4)
endforeach ()

# 5.6, 5.7, 5.8
foreach (SUBSTR_SEARCHER "KMP" "BoyerMoore" "RabinKarp")
    configure_file(SubstrSearch.cpp.in ${SUBSTR_SEARCHER}.cpp @ONLY)
    add_executable(${SUBSTR_SEARCHER} ${SUBSTR_SEARCHER}.cpp)
    target_link_libraries(${SUBSTR_SEARCHER} PRIVATE algs4)
endforeach ()

# 5.9
add_executable(GREP GREP.cpp)
target_link_libraries(GREP PRIVATE algs4)

# 5.10, 5.11
foreach (COMPRESSOR "Huffman" "LZW")
    configure_file(Compress.cpp.in ${COMPRESSOR}.cpp @ONLY)
    add_executable(${COMPRESSOR} ${COMPRESSOR}.cpp)
    target_link_libraries(${COMPRESSOR} PRIVATE algs4)
endforeach ()
add_executable(BinaryDump BinaryDump.cpp)
target_link_libraries(BinaryDump PRIVATE algs4)
