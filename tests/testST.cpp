#include "testST.h"
#include <iostream>
#include <iomanip>
#include <cassert>

namespace {
    constexpr char INVALID_KEY[] = "";
    constexpr int INVALID_VALUE = -1;
}

void testBasicST(ST<std::string, int> &&st, std::istream &&data) {
    std::string word;
    for (int i = 0; data >> word; ++i) st.put(word, i);

    std::cout << "size = " << st.size() << std::endl << std::endl;

    // print keys using keys()
    std::cout << "Testing keys()" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    for (const auto &s: st.keys()) {
        std::cout << s << " " << st.get(s).value_or(INVALID_VALUE) << std::endl;
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    // remove all keys
    for (const auto &s: st.keys()) {
        std::cout << "Removing " << s << std::endl;
        st.remove(s);
    }
    std::cout << "After removing all keys" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    assert(st.isEmpty());
    std::cout << "(Empty)" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
}

void testOrderedST(OrderedST<std::string, int> &&st, std::istream &&data) {
    std::string word;
    for (int i = 0; data >> word; ++i) st.put(word, i);

    std::cout << "size = " << st.size() << std::endl;
    std::cout << "min = " << st.min().value_or(INVALID_KEY) << std::endl;
    std::cout << "max = " << st.max().value_or(INVALID_KEY) << std::endl << std::endl;

    // print keys in order using keys()
    std::cout << "Testing keys()" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    for (const auto &s: st.keys()) {
        std::cout << s << " " << st.get(s).value_or(INVALID_VALUE) << std::endl;
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    // print keys in order using select
    std::cout << "Testing select()" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    for (int i = 0; i < st.size(); ++i) {
        std::cout << i << " " << st.select(i).value_or(INVALID_KEY) << std::endl;
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    // test rank, floor, ceiling
    std::cout << "key rank floor ceil" << std::endl;
    std::cout << "–––––––––––––––––––" << std::endl;
    for (char i = 'A'; i <= 'Z'; ++i) {
        std::string s(1, i);
        std::cout << std::setw(2) << s << " "
                << std::setw(4) << st.rank(s) << " "
                << std::setw(4) << st.floor(s).value_or(INVALID_KEY) << " "
                << std::setw(4) << st.ceiling(s).value_or(INVALID_KEY) << std::endl;
    }
    std::cout << "–––––––––––––––––––" << std::endl << std::endl;

    // test range search and range count
    std::vector<std::string> from = {"A", "Z", "X", "0", "B", "C"};
    std::vector<std::string> to = {"Z", "A", "X", "Z", "G", "L"};
    std::cout << "range search" << std::endl;
    std::cout << "–––––––––––––––––––" << std::endl;
    for (int i = 0; i < from.size(); ++i) {
        std::cout << from[i] << "-" << to[i] << " ("
                << std::setw(2) << st.size(from[i], to[i]) << ") : ";
        for (const auto &s: st.keys(from[i], to[i])) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "–––––––––––––––––––" << std::endl << std::endl;

    // remove the smallest keys
    for (int i = 0; i < st.size() / 2; ++i) {
        st.removeMin();
    }
    std::cout << "After removing the smallest " << st.size() / 2 << " keys" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    for (const auto &s: st.keys()) {
        std::cout << s << " " << st.get(s).value_or(INVALID_VALUE) << std::endl;
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    // remove all the remaining keys
    while (!st.isEmpty()) {
        std::cout << "Removing " << st.select(st.size() / 2).value_or(INVALID_KEY) << std::endl;
        st.remove(st.select(st.size() / 2).value_or(INVALID_KEY));
    }
    std::cout << "After removing the remaining keys" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    assert(st.isEmpty());
    std::cout << "(Empty)" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
}

void testStringST(StringST<int> &&st, std::istream &&data) {
    std::string word;
    for (int i = 0; data >> word; ++i) st.put(word, i);

    std::cout << "keys(\"\"):" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    for (const auto &key: st.keys()) {
        std::cout << key << " " << st.get(key).value_or(INVALID_VALUE) << std::endl;
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    std::cout << "longestPrefixOf(\"shellsort\"):" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    std::cout << st.longestPrefixOf("shellsort") << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    std::cout << "longestPrefixOf(\"shell\"):" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    std::cout << st.longestPrefixOf("shell") << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    std::cout << "keysWithPrefix(\"shor\"):" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    for (const auto &s: st.keysWithPrefix("shor")) {
        std::cout << s << std::endl;
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

    std::cout << "keysThatMatch(\".he.l.\"):" << std::endl;
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    for (const auto &s: st.keysThatMatch(".he.l.")) {
        std::cout << s << std::endl;
    }
    std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
}
