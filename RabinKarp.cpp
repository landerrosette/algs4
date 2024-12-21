#include "RabinKarp.h"
#include <random>

long long RabinKarp::hash(std::string_view key, int M) const {
    long long h = 0;
    for (int j = 0; j < M; ++j) h = (R * h + key[j]) % Q;
    return h;
}

long long RabinKarp::longRandomPrime() {
    // a random 31-bit prime
    std::default_random_engine e(std::random_device{}());
    std::uniform_int_distribution u(1LL << 30, (1LL << 31) - 1);
    while (true) {
        long long num = u(e);
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

RabinKarp::RabinKarp(std::string_view pat) : M(pat.length()) {
    for (int i = 1; i <= M - 1; ++i) RM = (R * RM) % Q; // Compute R^(M-1) % Q for use in removing leading digit.
    patHash = hash(pat, M);
}

int RabinKarp::search(std::string_view txt) const {
    int N = txt.length();
    long long txtHash = hash(txt, M);
    if (patHash == txtHash && check(0)) return 0; // Match at beginning.
    for (int i = M; i < N; ++i) {
        // Remove leading digit, add trailing digit, check for match.
        txtHash = (txtHash + Q - RM * txt[i - M] % Q) % Q;
        txtHash = (txtHash * R + txt[i]) % Q;
        if (patHash == txtHash && check(i - M + 1)) return i - M + 1; // match
    }
    return N; // no match found
}
