#ifndef ALGS4_LZW_HPP
#define ALGS4_LZW_HPP


#include <string>
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
    std::string input = BinaryStdIO::readString();
    TST<int> st;
    for (int i = 0; i < R; ++i)
        st.put(std::string(1, static_cast<char>(i)), i);
    int code = R + 1; // R is codeword for EOF.
    while (!input.empty()) {
        auto s = st.longestPrefixOf(input); // Find max prefix match.
        BinaryStdIO::write(*st.get(s), W);  // Print s's encoding.
        if (int t = s.length(); t < input.length() && code < L)
            st.put(input.substr(0, t + 1), code++);
        input.erase(0, s.length());
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
    ++i;
    int codeword = BinaryStdIO::readInt(W);
    auto val = st[codeword];
    while (true) {
        BinaryStdIO::write(val); // Write current substring.
        codeword = BinaryStdIO::readInt(W);
        if (codeword == R) break;
        std::string s = st[codeword];
        if (i == codeword) // If lookahead is invalid, ...
            s = val + val[0];
        if (i < L)
            st[i++] = val + s[0]; // otherwise add new entry to code table.
        val = s;
    }
    BinaryStdIO::closeOut();
}


#endif //ALGS4_LZW_HPP
