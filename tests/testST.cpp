#include "testST.h"
#include <fstream>
#include <iostream>

void testST(ST<std::string, int> &&st, const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::string word;
    int i = 0;
    while (dataFile >> word) {
        st.put(word, i);
        ++i;
    }

    // print keys using getKeys()
    std::cout << "Testing getKeys()\n";
    std::cout << "--------------------------------\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << st.get(s) << "\n";
    }
    std::cout << "--------------------------------\n\n";

    // remove the first few keys
    int size = st.size();
    for (int j = 0; j < size / 2; ++j) {
        st.remove(st.getKeys()[0]);
    }
    std::cout << "After removing the first " << size / 2 << " keys" << "\n";
    std::cout << "--------------------------------\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << st.get(s) << "\n";
    }
    std::cout << "--------------------------------\n\n";

    // remove all the remaining keys
    while (!st.isEmpty()) {
        std::cout << "Removing " << st.getKeys()[st.size() / 2] << "\n";
        st.remove(st.getKeys()[st.size() / 2]);
    }
    std::cout << "After removing the remaining keys\n";
    std::cout << "--------------------------------\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << st.get(s) << "\n";
    }
    std::cout << "--------------------------------\n\n";
}
