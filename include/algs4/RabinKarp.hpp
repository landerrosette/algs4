/*
 * Copyright (C) 2024-2026  landerrosette <57791410+landerrosette@users.noreply.github.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ALGS4_RABINKARP_HPP
#define ALGS4_RABINKARP_HPP

#include <cstddef>
#include <random>
#include <string_view>

#include "SubstrSearcher.hpp"

namespace algs4 {
class RabinKarp : public SubstrSearcher {
private:
    long long patHash_;                // pattern hash value
    std::ptrdiff_t M_;                 // pattern length
    long long Q_ = longRandomPrime();  // a large prime
    static constexpr int R = 256;      // alphabet size
    long long RM_ = 1;                 // R^(M_-1) % Q_

    // a random 31-bit prime
    static long long longRandomPrime() {
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

    long long hash(std::string_view key, std::ptrdiff_t M) const {
        long long h = 0;
        for (decltype(M) j = 0; j < M; ++j) h = (R * h + key[j]) % Q_;
        return h;
    }

    bool check(int i) const { return true; }  // Monte Carlo

public:
    explicit RabinKarp(std::string_view pat) : M_(std::ssize(pat)) {
        // Compute R^(M_-1) % Q_ for use in removing leading digit.
        for (decltype(M_) i = 1; i <= M_ - 1; ++i) RM_ = (R * RM_) % Q_;
        patHash_ = hash(pat, M_);
    }

    std::ptrdiff_t search(std::string_view txt) const override {
        auto N = std::ssize(txt);
        long long txtHash = hash(txt, M_);
        if (patHash_ == txtHash && check(0)) return 0;  // match at beginning
        for (auto i = M_; i < N; ++i) {
            // Remove leading digit, add trailing digit, check for match.
            txtHash = (txtHash + Q_ - RM_ * txt[i - M_] % Q_) % Q_;
            txtHash = (txtHash * R + txt[i]) % Q_;
            if (patHash_ == txtHash && check(i - M_ + 1)) return i - M_ + 1;  // match
        }
        return N;  // no match found
    }
};
}  // namespace algs4

#endif  // ALGS4_RABINKARP_HPP
