#include "BoyerMoore.h"

BoyerMoore::BoyerMoore(const std::string &pat) : pat(pat) {
    // 计算跳跃表
    int M = pat.length(), R = 256;
    right = std::vector(R, -1);
    for (int j = 0; j < M; ++j) right[pat[j]] = j;
}

int BoyerMoore::search(const std::string &txt) const {
    int N = txt.length(), M = pat.length();
    for (int skip, i = 0; i <= N - M; i += skip) {
        // 模式字符串和文本在位置i匹配吗？
        skip = 0;
        for (int j = M - 1; j >= 0; --j) {
            if (pat[j] != txt[i + j]) {
                skip = j - right[txt[i + j]];
                if (skip < 1) skip = 1;
                break;
            }
        }
        if (skip == 0) return i; // 找到匹配
    }
    return N; // 未找到匹配
}
