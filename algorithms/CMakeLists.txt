add_library(algs4_algorithms STATIC
        AcyclicSP.cpp
        BellmanFordSP.cpp
        BinaryStdIO.cpp
        BoyerMoore.cpp
        BreadthFirstPaths.cpp
        CC.cpp
        CCBase.cpp
        DepthFirstPaths.cpp
        Digraph.cpp
        DijkstraSP.cpp
        DirectedDFS.cpp
        Edge.cpp
        EdgeWeightedDigraph.cpp
        EdgeWeightedGraph.cpp
        Graph.cpp
        Huffman.cpp
        KMP.cpp
        KosarajuSCC.cpp
        KruskalMST.cpp
        LSD.cpp
        LZW.cpp
        MSD.cpp
        MST.cpp
        NFA.cpp
        Paths.cpp
        PrimMST.cpp
        Quick3string.cpp
        RabinKarp.cpp
        SP.cpp
        SymbolDigraph.cpp
        UF.cpp
)

target_include_directories(algs4_algorithms PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
