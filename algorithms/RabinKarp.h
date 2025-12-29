#ifndef ALGS4_RABINKARP_H
#define ALGS4_RABINKARP_H


#include <random>
#include <string_view>

#include "SubstrSearcher.h"

namespace algs4 {
    class RabinKarp : public SubstrSearcher {
    private:
        long long patHash;               // pattern hash value
        int M;                           // pattern length
        long long Q = longRandomPrime(); // a large prime
        int R = 256;                     // alphabet size
        long long RM = 1;                // R^(M-1) % Q

        long long hash(std::string_view key, int M) const;
        static long long longRandomPrime();
        bool check(int i) const { return true; } // monte carlo

    public:
        explicit RabinKarp(std::string_view pat);

        int search(std::string_view txt) const override;
    };
}

inline long long algs4::RabinKarp::hash(std::string_view key, int M) const {
    long long h = 0;
    for (int j = 0; j < M; ++j) h = (R * h + key[j]) % Q;
    return h;
}

// a random 31-bit prime
inline long long algs4::RabinKarp::longRandomPrime() {
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

inline algs4::RabinKarp::RabinKarp(std::string_view pat) : M(pat.length()) {
    for (int i = 1; i <= M - 1; ++i) RM = (R * RM) % Q; // Compute R^(M-1) % Q for use in removing leading digit.
    patHash = hash(pat, M);
}

inline int algs4::RabinKarp::search(std::string_view txt) const {
    int N = txt.length();
    long long txtHash = hash(txt, M);
    if (patHash == txtHash && check(0)) return 0; // match at beginning
    // Remove leading digit, add trailing digit, check for match.
    for (int i = M; i < N; ++i) {
        txtHash = (txtHash + Q - RM * txt[i - M] % Q) % Q;
        txtHash = (txtHash * R + txt[i]) % Q;
        if (patHash == txtHash && check(i - M + 1)) return i - M + 1; // match
    }
    return N; // no match found
}


#endif //ALGS4_RABINKARP_H
