#ifndef ALGS4_SYMBOLDIGRAPH_HPP
#define ALGS4_SYMBOLDIGRAPH_HPP


#include <cassert>
#include <filesystem>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "Digraph.hpp"
#include "RedBlackBST.hpp"

namespace algs4 {
    class SymbolDigraph {
    private:
        RedBlackBST<std::string, int> st; // symbol -> index
        std::vector<std::string> keys;    // index -> symbol
        std::unique_ptr<Digraph> G_;      // the graph

    public:
        SymbolDigraph(const std::filesystem::path &stream, char sp);

        bool contains(const std::string &s) const { return st.contains(s); }
        std::string_view name(int v) const;
        const Digraph &G() const { return *G_; }
    };
}

inline algs4::SymbolDigraph::SymbolDigraph(const std::filesystem::path &stream, char sp) {
    std::ifstream in(stream);
    if (!in.is_open())
        throw std::invalid_argument("Cannot open file: " + stream.string());
    // First pass builds the index by reading strings to associate each distinct string with an index.
    for (std::string line; std::getline(in, line);) {
        std::string name;
        for (std::istringstream iss(line); std::getline(iss, name, sp);)
            if (!st.contains(name))
                st.put(name, static_cast<int>(st.size()));
    }
    keys.resize(st.size()); // Inverted index to get string keys is an array.
    for (const auto &name: st.keys())
        keys[*st.get(name)] = name;

    G_ = std::make_unique<Digraph>(st.size());
    in = std::ifstream(stream);
    if (!in.is_open())
        throw std::invalid_argument("Cannot open file: " + stream.string());
    // Second pass builds the graph by connecting the first vertex on each line to all the others.
    for (std::string line; std::getline(in, line);) {
        std::string name;
        std::istringstream iss(line);
        std::getline(iss, name, sp);
        int v = *st.get(name);
        while (std::getline(iss, name, sp))
            G_->addEdge(v, *st.get(name));
    }
}

inline std::string_view algs4::SymbolDigraph::name(int v) const {
    assert(v >= 0 && v < G_->V());
    return keys[v];
}


#endif //ALGS4_SYMBOLDIGRAPH_HPP
