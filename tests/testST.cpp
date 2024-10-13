#include "testST.h"
#include <iostream>
#include <iomanip>
#include <cassert>

static constexpr char INVALID_KEY[] = "";
static constexpr int INVALID_VALUE = -1;

void testBasicST(ST<std::string, int> &&st, std::istream &&data) {
    std::string word;
    int i = 0;
    while (data >> word) {
        st.put(word, i);
        ++i;
    }

    std::cout << "size = " << st.size() << "\n" << "\n";

    // print keys using keys()
    std::cout << "Testing keys()" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
    for (const auto &s: st.keys()) {
        std::cout << s << " " << st.get(s).value_or(INVALID_VALUE) << "\n";
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n" << "\n";

    // remove all keys
    for (const auto &s: st.keys()) {
        std::cout << "Removing " << s << "\n";
        st.remove(s);
    }
    std::cout << "After removing all keys" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
    assert(st.isEmpty());
    std::cout << "(Empty)" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
}

void testOrderedST(OrderedST<std::string, int> &&st, std::istream &&data) {
    std::string word;
    int i = 0;
    while (data >> word) {
        st.put(word, i);
        ++i;
    }

    std::cout << "size = " << st.size() << "\n";
    std::cout << "min = " << st.min().value_or(INVALID_KEY) << "\n";
    std::cout << "max = " << st.max().value_or(INVALID_KEY) << "\n" << "\n";

    // print keys in order using keys()
    std::cout << "Testing keys()" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
    for (const auto &s: st.keys()) {
        std::cout << s << " " << st.get(s).value_or(INVALID_VALUE) << "\n";
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n" << "\n";

    // print keys in order using select
    std::cout << "Testing select()" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
    for (int i = 0; i < st.size(); ++i) {
        std::cout << i << " " << st.select(i).value_or(INVALID_KEY) << "\n";
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n" << "\n";

    // test rank, floor, ceiling
    std::cout << "key rank floor ceil" << "\n";
    std::cout << "–––––––––––––––––––" << "\n";
    for (char i = 'A'; i <= 'Z'; ++i) {
        std::string s(1, i);
        std::cout << std::setw(2) << s << " "
                << std::setw(4) << st.rank(s) << " "
                << std::setw(4) << st.floor(s).value_or(INVALID_KEY) << " "
                << std::setw(4) << st.ceiling(s).value_or(INVALID_KEY) << "\n";
    }
    std::cout << "–––––––––––––––––––" << "\n" << "\n";

    // test range search and range count
    std::vector<std::string> from = {"A", "Z", "X", "0", "B", "C"};
    std::vector<std::string> to = {"Z", "A", "X", "Z", "G", "L"};
    std::cout << "range search" << "\n";
    std::cout << "–––––––––––––––––––" << "\n";
    for (int i = 0; i < from.size(); ++i) {
        std::cout << from[i] << "-" << to[i] << " ("
                << std::setw(2) << st.size(from[i], to[i]) << ") : ";
        for (const auto &s: st.keys(from[i], to[i])) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }
    std::cout << "–––––––––––––––––––" << "\n" << "\n";

    // remove the smallest keys
    for (int i = 0; i < st.size() / 2; ++i) {
        st.removeMin();
    }
    std::cout << "After removing the smallest " << st.size() / 2 << " keys" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
    for (const auto &s: st.keys()) {
        std::cout << s << " " << st.get(s).value_or(INVALID_VALUE) << "\n";
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n" << "\n";

    // remove all the remaining keys
    while (!st.isEmpty()) {
        std::cout << "Removing " << st.select(st.size() / 2).value_or(INVALID_KEY) << "\n";
        st.remove(st.select(st.size() / 2).value_or(INVALID_KEY));
    }
    std::cout << "After removing the remaining keys" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
    assert(st.isEmpty());
    std::cout << "(Empty)" << "\n";
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << "\n";
}
