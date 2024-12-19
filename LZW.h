#ifndef LZW_H
#define LZW_H


class LZW {
private:
    static constexpr int R = 256;  // 输入字符数
    static constexpr int L = 4096; // 编码总数=2^12
    static constexpr int W = 12;   // 编码宽度

public:
    static void compress();

    static void expand();
};


#endif //LZW_H
