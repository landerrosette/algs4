#include "KMP.h"
#include <utility>

KMP::KMP(std::string pat) : pat(std::move(pat)) {
    // 构造DFA
    int M = this->pat.length(), R = 256;
    dfa = std::vector(R, std::vector<int>(M));
    dfa[this->pat[0]][0] = 1;
    for (int X = 0, j = 1; j < M; ++j) {
        // 计算dfa[][j]
        for (int c = 0; c < R; ++c) dfa[c][j] = dfa[c][X]; // 复制匹配失败情况下的值
        dfa[this->pat[j]][j] = j + 1;                      // 设置匹配成功情况下的值
        X = dfa[this->pat[j]][X];                          // 更新重启状态
    }
}

int KMP::search(std::string_view txt) const {
    int i, j, N = txt.length(), M = pat.length();
    for (i = 0, j = 0; i < N && j < M; ++i) j = dfa[txt[i]][j];
    if (j == M) return i - M; // 找到匹配（到达模式字符串的末尾）
    else return N;            // 未找到匹配（到达文本字符串的末尾）
}
