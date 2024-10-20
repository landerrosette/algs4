#include "SymbolDigraph.h"
#include <fstream>
#include <string>
#include <sstream>

SymbolDigraph::SymbolDigraph(const std::filesystem::path &dataFilePath, char sp) {
    std::ifstream dataFile(dataFilePath); // 第一遍
    std::string line;
    while (std::getline(dataFile, line)) {
        // 构造索引
        std::string name;
        std::istringstream iss(line);
        while (std::getline(iss, name, sp)) {
            // 为每个不同的字符串关联一个索引
            if (!st.contains(name)) st.put(name, st.size());
        }
    }
    keys = std::vector<std::string>(st.size()); // 用来获得顶点名的反向索引是一个数组
    for (const auto &name: st.keys()) keys[*st.get(name)] = name;

    G_ = std::make_unique<Digraph>(st.size());
    dataFile = std::ifstream(dataFilePath); // 第二遍
    while (std::getline(dataFile, line)) {
        // 构造图
        std::string name;
        std::istringstream iss(line);
        std::getline(iss, name, sp);
        int v = *st.get(name);
        while (std::getline(iss, name, sp)) {
            // 将每一行的第一个顶点和该行的其他顶点相连
            G_->addEdge(v, *st.get(name));
        }
    }
}
