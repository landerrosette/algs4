#ifndef RABINKARP_H
#define RABINKARP_H


#include "SubstrSearcher.h"
#include <string_view>

class RabinKarp : public SubstrSearcher {
private:
    long long patHash;               // 模式字符串的散列值
    int M;                           // 模式字符串的长度
    long long Q = longRandomPrime(); // 一个很大的素数
    int R = 256;                     // 字母表的大小
    long long RM = 1;                // R^(M-1) % Q

    long long hash(std::string_view key, int M) const;

    static long long longRandomPrime();

    bool check(int i) const { return true; } // 蒙特卡洛算法（只要散列值相同就认为找到了）

public:
    explicit RabinKarp(std::string_view pat);

    int search(std::string_view txt) const override;
};


#endif //RABINKARP_H
