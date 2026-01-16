#ifndef ALGS4_LZW_HPP
#define ALGS4_LZW_HPP

#include <string>
#include <utility>
#include <vector>

#include "BinaryStdIO.hpp"
#include "TST.hpp"

namespace algs4 {
    namespace LZW {
        namespace internal {
            constexpr int R = 256;  // number of input chars
            constexpr int L = 4096; // number of codewords = 2^12
            constexpr int W = 12;   // codeword width
        }

        void compress();
        void expand();
    }
}

inline void algs4::LZW::compress() {
    using namespace internal;
    auto input = BinaryStdIO::read<std::string>();
    TST<int> st;
    for (int i = 0; i < R; ++i)
        st.put(std::string(1, static_cast<char>(i)), i);
    int code = R + 1; // R is codeword for EOF.
    while (!input.empty()) {
        auto s = st.longestPrefixOf(input); // Find max prefix match.
        BinaryStdIO::write(*st.get(s), W);  // Print s's encoding.
        if (auto t = std::ssize(s); t < std::ssize(input) && code < L)
            st.put(input.substr(0, t + 1), code++);
        input.erase(0, std::ssize(s));
    }
    BinaryStdIO::write(R, W);
    BinaryStdIO::closeOut();
}

inline void algs4::LZW::expand() {
    using namespace internal;
    std::vector<std::string> st(L);
    int i; // next available codeword value
    for (i = 0; i < R; ++i)
        st[i] = std::string(1, static_cast<char>(i));
    st[i++] = "";
    int codeword = BinaryStdIO::read<int>(W);
    auto val = st[codeword];
    while (true) {
        BinaryStdIO::write(val); // Write current substring.
        codeword = BinaryStdIO::read<int>(W);
        if (codeword == R) break;
        std::string s;
        if (i == codeword)    // If lookahead is invalid,
            s = val + val[0]; // make codeword from last one.
        else
            s = st[codeword];
        if (i < L)
            st[i++] = std::move(val) + s[0]; // Add new entry to code table.
        val = std::move(s);                  // Update current codeword.
    }
    BinaryStdIO::closeOut();
}

#endif // ALGS4_LZW_HPP
