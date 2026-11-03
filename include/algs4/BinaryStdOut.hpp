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

#ifndef ALGS4_BINARYSTDOUT_HPP
#define ALGS4_BINARYSTDOUT_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

namespace algs4 {
namespace BinaryStdOut {
    namespace detail {
        inline std::byte buffer_;
        inline int n_ = 0;

        inline void writeBit(bool bit) {
            // Add bit to buffer.
            buffer_ <<= 1;
            if (bit) buffer_ |= std::byte{1};

            // If buffer is full (8 bits), write out as a single byte.
            if (++n_ == std::numeric_limits<unsigned char>::digits) {
                std::cout.put(std::to_integer<char>(buffer_));
                buffer_ = std::byte();
                n_ = 0;
            }
        }

        inline void writeByte(std::byte byte) {
            // optimized if byte-aligned
            if (n_ == 0) {
                std::cout.put(std::to_integer<char>(byte));
                return;
            }

            // Otherwise write one bit at a time.
            for (int i = std::numeric_limits<unsigned char>::digits - 1; i >= 0; --i) {
                bool bit = ((byte >> i) & std::byte{1}) == std::byte{1};
                writeBit(bit);
            }
        }
    }  // namespace detail

    inline void write(bool x) { detail::writeBit(x); }

    template <std::integral T>
    void write(T x) {
        using namespace detail;
        for (int i = sizeof(T) - 1; i >= 0; --i)
            writeByte(static_cast<std::byte>((x >> i * std::numeric_limits<unsigned char>::digits) & 0xFF));
    }

    template <std::integral T>
        requires(!std::is_same_v<std::remove_cvref_t<T>, bool>)
    void write(T x, int r) {
        using namespace detail;
        if (r == std::numeric_limits<T>::digits + (std::numeric_limits<T>::is_signed ? 1 : 0)) {
            write(x);
            return;
        }
        assert(r >= 1 && r <= std::numeric_limits<T>::digits + (std::numeric_limits<T>::is_signed ? 1 : 0));
        for (int i = r - 1; i >= 0; --i) {
            bool bit = ((x >> i) & 1) == 1;
            writeBit(bit);
        }
    }

    inline void write(const std::string& x) {
        for (char c : x) write(c);
    }

    inline void close() {
        using namespace detail;
        if (n_ > 0) {
            // Pad 0s if number of bits written so far is not a multiple of 8.
            buffer_ <<= std::numeric_limits<unsigned char>::digits - n_;
            std::cout.put(std::to_integer<char>(buffer_));
        }
        n_ = 0;
        buffer_ = std::byte();
    }
}  // namespace BinaryStdOut
}  // namespace algs4

#endif  // ALGS4_BINARYSTDOUT_HPP
