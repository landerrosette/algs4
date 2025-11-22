#ifndef ALGS4_SYMBOLDIGRAPH_H
#define ALGS4_SYMBOLDIGRAPH_H


#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

#include "Digraph.h"
#include "RedBlackBST.h"

namespace algs4 {
    class SymbolDigraph {
    private:
        RedBlackBST<std::string, int> st; // symbol -> index
        std::vector<std::string> keys;    // index -> symbol
        std::unique_ptr<Digraph> G_;      // the graph

    public:
        SymbolDigraph(const std::filesystem::path &stream, char sp);

        bool contains(const std::string &s) const { return st.contains(s); }
        std::string_view name(int v) const { return keys[v]; }
        const Digraph &G() const { return *G_; }
    };
}


#endif //ALGS4_SYMBOLDIGRAPH_H
