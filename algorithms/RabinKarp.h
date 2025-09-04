#ifndef ALGS4_RABINKARP_H
#define ALGS4_RABINKARP_H


#include <string_view>

#include "SubstrSearcher.h"

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


#endif //ALGS4_RABINKARP_H
