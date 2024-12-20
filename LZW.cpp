#include "LZW.h"
#include "TST.h"
#include <string>
#include "BinaryStdIO.h"
#include <vector>

void LZW::compress() {
    std::string input = BinaryStdIO::readString();
    TST<int> st;
    for (int i = 0; i < R; ++i) st.put(std::string(1, static_cast<char>(i)), i);
    int code = R + 1; // R为文件结束（EOF）的编码
    while (!input.empty()) {
        auto s = st.longestPrefixOf(input); // 找到匹配的最长前缀
        BinaryStdIO::write(*st.get(s), W);  // 打印出s的编码
        if (int t = s.length(); t < input.length() && code < L) st.put(input.substr(0, t + 1), code++);
        input.erase(0, s.length());
    }
    BinaryStdIO::write(R, W);
    BinaryStdIO::closeOut();
}

void LZW::expand() {
    std::vector<std::string> st(L);
    int i; // next available codeword value
    for (i = 0; i < R; ++i) st[i] = std::string(1, static_cast<char>(i));
    ++i;
    int codeword = BinaryStdIO::readInt(W);
    auto val = st[codeword];
    while (true) {
        BinaryStdIO::write(val); // write current substring
        codeword = BinaryStdIO::readInt(W);
        if (codeword == R) break;
        std::string s = st[codeword];
        if (i == codeword) s = val + val[0]; // if lookahead is invalid
        if (i < L) st[i++] = val + s[0];     // add new entry to code table
        val = s;
    }
    BinaryStdIO::closeOut();
}
