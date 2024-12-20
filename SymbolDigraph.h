#ifndef ALGS4_SYMBOLDIGRAPH_H
#define ALGS4_SYMBOLDIGRAPH_H


#include "Digraph.h"
#include "RedBlackBST.h"
#include <string>
#include <filesystem>
#include <vector>
#include <memory>

class SymbolDigraph {
private:
    RedBlackBST<std::string, int> st; // symbol -> index
    std::vector<std::string> keys;    // index -> symbol
    std::unique_ptr<Digraph> G_;      // the graph

public:
    SymbolDigraph(const std::filesystem::path &stream, char sp);

    bool contains(const std::string &s) const { return st.contains(s); }

    std::optional<int> index(const std::string &s) const { return st.get(s); }

    std::string name(int v) const { return keys[v]; }

    Digraph G() const { return *G_; }
};


#endif //ALGS4_SYMBOLDIGRAPH_H
