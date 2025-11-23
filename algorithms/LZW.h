#ifndef ALGS4_LZW_H
#define ALGS4_LZW_H


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


#endif //ALGS4_LZW_H
