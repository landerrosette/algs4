#include "RabinKarp.h"
#include <random>

long long RabinKarp::hash(const std::string &key, int M) const {
    long long h = 0;
    for (int j = 0; j < M; ++j) h = (R * h + key[j]) % Q;
    return h;
}

// a random 31-bit prime
long long RabinKarp::longRandomPrime() {
    std::mt19937 g(std::random_device{}());
    std::uniform_int_distribution dis(1LL << 30, (1LL << 31) - 1);
    while (true) {
        long long num = dis(g);
        if (num % 3 == 0) continue;
        bool isPrime = true;
        for (long i = 5; i <= num / i; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) return num;
    }
}

RabinKarp::RabinKarp(const std::string &pat) : M(pat.length()) {
    for (int i = 1; i <= M - 1; ++i) RM = (R * RM) % Q; // 计算 R^(M-1) % Q
    patHash = hash(pat, M);
}

int RabinKarp::search(const std::string &txt) const {
    int N = txt.length();
    long long txtHash = hash(txt, M);
    if (patHash == txtHash && check(0)) return 0; // 一开始就匹配成功
    for (int i = M; i < N; ++i) {
        // 减去第一个数字，加上最后一个数字，再次检查匹配
        txtHash = (txtHash + Q - RM * txt[i - M] % Q) % Q;
        txtHash = (txtHash * R + txt[i]) % Q;
        if (patHash == txtHash && check(i - M + 1)) return i - M + 1; // 找到匹配
    }
    return N; // 未找到匹配
}
