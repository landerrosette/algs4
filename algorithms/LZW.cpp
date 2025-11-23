#include "LZW.h"

#include <string>
#include <vector>

#include "BinaryStdIO.h"
#include "TST.h"

void algs4::LZW::compress() {
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

void algs4::LZW::expand() {
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
