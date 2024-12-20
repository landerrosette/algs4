#include "SymbolDigraph.h"
#include <fstream>
#include <string>
#include <sstream>

SymbolDigraph::SymbolDigraph(const std::filesystem::path &stream, char sp) {
    std::ifstream in(stream);
    for (std::string line; std::getline(in, line);) {
        // First pass builds the index by reading strings to associate each distinct string with an index.
        std::string name;
        for (std::istringstream iss(line); std::getline(iss, name, sp);) {
            if (!st.contains(name)) st.put(name, st.size());
        }
    }
    keys = std::vector<std::string>(st.size()); // Inverted index to get string keys is an array.
    for (const auto &name: st.keys()) keys[*st.get(name)] = name;

    G_ = std::make_unique<Digraph>(st.size());
    in = std::ifstream(stream);
    for (std::string line; std::getline(in, line);) {
        // Second pass builds the graph by connecting the first vertex on each line to all the others.
        std::string name;
        std::istringstream iss(line);
        std::getline(iss, name, sp);
        int v = *st.get(name);
        while (std::getline(iss, name, sp)) {
            G_->addEdge(v, *st.get(name));
        }
    }
}
