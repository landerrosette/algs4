#ifndef ALGS4_LZW_H
#define ALGS4_LZW_H


class LZW {
private:
    static constexpr int R = 256;  // number of input chars
    static constexpr int L = 4096; // number of codewords = 2^12
    static constexpr int W = 12;   // codeword width

public:
    static void compress();

    static void expand();
};


#endif //ALGS4_LZW_H