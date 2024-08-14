#include "testST.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void testBasicST(ST<std::string, int> &&st, const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::string word;
    int i = 0;
    while (dataFile >> word) {
        st.put(word, i);
        ++i;
    }

    std::cout << "size = " << st.size() << "\n";

    // print keys using getKeys()
    std::cout << "Testing getKeys()" << "\n";
    std::cout << "--------------------------------" << "\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << *st.get(s) << "\n";
    }
    std::cout << "--------------------------------" << "\n" << "\n";

    // remove the first few keys
    for (int i = 0; i < st.size() / 2; ++i) {
        st.remove(st.getKeys()[0]);
    }
    std::cout << "After removing the first " << st.size() / 2 << " keys" << "\n";
    std::cout << "--------------------------------" << "\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << *st.get(s) << "\n";
    }
    std::cout << "--------------------------------" << "\n" << "\n";

    // remove all the remaining keys
    while (!st.isEmpty()) {
        std::cout << "Removing " << st.getKeys()[st.size() / 2] << "\n";
        st.remove(st.getKeys()[st.size() / 2]);
    }
    std::cout << "After removing the remaining keys" << "\n";
    std::cout << "--------------------------------" << "\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << *st.get(s) << "\n";
    }
    std::cout << "--------------------------------" << "\n" << "\n";
}

void testOrderedST(OrderedST<std::string, int> &&st, const std::filesystem::path &dataFilePath) {
    std::ifstream dataFile(dataFilePath);
    std::string word;
    int i = 0;
    while (dataFile >> word) {
        st.put(word, i);
        ++i;
    }

    std::cout << "size = " << st.size() << "\n";
    std::cout << "min = " << *st.min() << "\n";
    std::cout << "max = " << *st.max() << "\n";

    // print keys in order using getKeys()
    std::cout << "Testing getKeys()" << "\n";
    std::cout << "--------------------------------" << "\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << *st.get(s) << "\n";
    }
    std::cout << "--------------------------------" << "\n" << "\n";

    // print keys in order using select
    std::cout << "Testing select()" << "\n";
    std::cout << "--------------------------------" << "\n";
    for (int i = 0; i < st.size(); ++i) {
        std::cout << i << " " << *st.select(i) << "\n";
    }
    std::cout << "--------------------------------" << "\n" << "\n";

    // test rank, floor, ceiling
    std::cout << "key rank floor ceil" << "\n";
    std::cout << "-------------------" << "\n";
    for (char i = 'A'; i <= 'Z'; ++i) {
        std::string s(1, i);
        std::cout << std::setw(2) << s << " "
                  << std::setw(4) << st.rank(s) << " "
                << std::setw(4) << *st.floor(s) << " "
                << std::setw(4) << *st.ceiling(s) << "\n";
    }
    std::cout << "-------------------" << "\n" << "\n";

    // test range search and range count
    std::vector<std::string> from = {"A", "Z", "X", "0", "B", "C"};
    std::vector<std::string> to = {"Z", "A", "X", "Z", "G", "L"};
    std::cout << "range search" << "\n";
    std::cout << "-------------------" << "\n";
    for (int i = 0; i < from.size(); ++i) {
        std::cout << from[i] << "-" << to[i] << " ("
                  << std::setw(2) << st.size(from[i], to[i]) << ") : ";
        for (const auto &s: st.getKeys(from[i], to[i])) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------" << "\n" << "\n";

    // remove the smallest keys
    for (int i = 0; i < st.size() / 2; ++i) {
        st.removeMin();
    }
    std::cout << "After removing the smallest " << st.size() / 2 << " keys" << "\n";
    std::cout << "--------------------------------" << "\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << *st.get(s) << "\n";
    }
    std::cout << "--------------------------------" << "\n" << "\n";

    // remove all the remaining keys
    while (!st.isEmpty()) {
        std::cout << "Removing " << *st.select(st.size() / 2) << "\n";
        st.remove(*st.select(st.size() / 2));
    }
    std::cout << "After removing the remaining keys" << "\n";
    std::cout << "--------------------------------" << "\n";
    for (const auto &s: st.getKeys()) {
        std::cout << s << " " << *st.get(s) << "\n";
    }
    std::cout << "--------------------------------" << "\n" << "\n";
}
