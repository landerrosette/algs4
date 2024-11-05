#include "testST.h"
#include <iostream>
#include <iomanip>
#include <random>

namespace {
    constexpr char INVALID_KEY[] = "";
    constexpr int INVALID_VALUE = -1;

    void insert(ST<std::string, int> &st, std::istream &data) {
        std::string word;
        for (int i = 0; data >> word; ++i) st.put(word, i);
        std::cout << "size = " << st.size() << std::endl;
    }

    void insert(OrderedST<std::string, int> &st, std::istream &data) {
        insert(static_cast<ST<std::string, int> &>(st), data);

        std::cout << "min = " << st.min().value_or(INVALID_KEY) << std::endl;
        std::cout << "max = " << st.max().value_or(INVALID_KEY) << std::endl;
    }

    void list(ST<std::string, int> &st) {
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
        for (const auto &s: st.keys()) {
            std::cout << s << " " << st.get(s).value_or(INVALID_VALUE) << std::endl;
        }
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    }

    void print(ST<std::string, int> &st) {
        // print keys using keys()
        std::cout << "Testing keys():" << std::endl;
        list(st);
    }

    void print(OrderedST<std::string, int> &st) {
        print(static_cast<ST<std::string, int> &>(st));
        std::cout << std::endl;

        // print keys in order using select
        std::cout << "Testing select():" << std::endl;
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
        for (int i = 0; i < st.size(); ++i) {
            std::cout << i << " " << st.select(i).value_or(INVALID_KEY) << std::endl;
        }
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    }

    void testOrderedST(OrderedST<std::string, int> &st) {
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
        std::cout << "–––––––––––––––––––" << std::endl;
    }

    void removeSome(ST<std::string, int> &st) {
        // remove some randomly selected keys
        std::mt19937 g(std::random_device{}());
        for (const auto &s: st.keys()) {
            if (std::bernoulli_distribution(0.5)(g)) st.remove(s);
        }
        std::cout << "After removing some randomly selected keys, size = " << st.size() << ":" << std::endl;
        list(st);
    }

    void removeSome(OrderedST<std::string, int> &st) {
        // remove the smallest keys
        for (int i = 0; i < st.size() / 2; ++i) {
            st.removeMin();
        }
        std::cout << "After removing the smallest " << st.size() / 2 << " keys, size = " << st.size() << ":" <<
                std::endl;
        list(st);
    }

    void removeAll(ST<std::string, int> &st) {
        // remove all the remaining keys
        for (const auto &s: st.keys()) {
            st.remove(s);
        }
        std::cout << "After removing the remaining keys, size = " << st.size() << ":" << std::endl;
        list(st);
    }

    void removeAll(OrderedST<std::string, int> &st) {
        // remove all the remaining keys
        while (!st.isEmpty()) {
            st.remove(st.select(st.size() / 2).value_or(INVALID_KEY));
        }
        std::cout << "After removing the remaining keys, size = " << st.size() << ":" << std::endl;
        list(st);
    }

    void testStringST(StringST<int> &st) {
        std::cout << "longestPrefixOf(\"shellsort\"):" << std::endl;
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
        std::cout << st.longestPrefixOf("shellsort") << std::endl;
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

        std::cout << "longestPrefixOf(\"shell\"):" << std::endl;
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
        std::cout << st.longestPrefixOf("shell") << std::endl;
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

        std::cout << "keysWithPrefix(\"shor\"):" << std::endl;
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
        for (const auto &s: st.keysWithPrefix("shor")) {
            std::cout << s << std::endl;
        }
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl << std::endl;

        std::cout << "keysThatMatch(\".he.l.\"):" << std::endl;
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
        for (const auto &s: st.keysThatMatch(".he.l.")) {
            std::cout << s << std::endl;
        }
        std::cout << "––––––––––––––––––––––––––––––––––––––––––––––––––––––" << std::endl;
    }
}

void testST(ST<std::string, int> &&st, std::istream &&data) {
    insert(st, data);
    std::cout << std::endl;
    print(st);
    std::cout << std::endl;
    removeSome(st);
    std::cout << std::endl;
    removeAll(st);
}

void testST(OrderedST<std::string, int> &&st, std::istream &&data) {
    insert(st, data);
    std::cout << std::endl;
    print(st);
    std::cout << std::endl;
    testOrderedST(st);
    std::cout << std::endl;
    removeSome(st);
    std::cout << std::endl;
    removeAll(st);
}

void testST(StringST<int> &&st, std::istream &&data) {
    insert(st, data);
    std::cout << std::endl;
    print(st);
    std::cout << std::endl;
    testStringST(st);
    std::cout << std::endl;
    removeSome(st);
    std::cout << std::endl;
    removeAll(st);
}
