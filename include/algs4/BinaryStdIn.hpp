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

#ifndef ALGS4_BINARYSTDIN_HPP
#define ALGS4_BINARYSTDIN_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

namespace algs4 {
namespace BinaryStdIn {
    namespace detail {
        inline std::byte buffer_;
        inline int n_ = 0;

        inline void fillBuffer() {
            auto c = std::cin.get();
            if (c == std::char_traits<char>::eof()) {
                n_ = -1;
                return;
            }
            buffer_ = static_cast<std::byte>(c);
            if (n_ == 0) n_ = std::numeric_limits<unsigned char>::digits;
        }

        inline bool isEmpty() { return n_ < 0; }

        inline bool readBit() {
            assert(!isEmpty());

            if (n_ == 0) fillBuffer();
            bool bit = ((buffer_ >> --n_) & std::byte{1}) == std::byte{1};
            if (n_ == 0) fillBuffer();
            return bit;
        }

        inline std::byte readByte() {
            assert(!isEmpty());

            if (n_ == 0) fillBuffer();
            auto x = buffer_;
            if (n_ == std::numeric_limits<unsigned char>::digits)
                fillBuffer();  // special case when aligned byte
            else {
                // Combine last n bits of current buffer with first 8-n bits of new buffer.
                x <<= std::numeric_limits<unsigned char>::digits - n_;
                fillBuffer();
                x |= buffer_ >> n_;
            }
            return x;
        }
    }  // namespace detail

    using detail::isEmpty;

    template <typename T>
        requires std::is_same_v<std::remove_cvref_t<T>, bool>
    T read() {
        return detail::readBit();
    }

    template <std::integral T>
        requires(!std::is_same_v<std::remove_cvref_t<T>, bool> && sizeof(T) == 1)
    T read() {
        return std::to_integer<T>(detail::readByte());
    }

    template <std::integral T>
        requires(sizeof(T) > 1)
    T read() {
        using namespace detail;
        T x = 0;
        for (int i = 0; i < sizeof(T); ++i) {
            x <<= std::numeric_limits<unsigned char>::digits;
            x |= std::to_integer<unsigned char>(readByte());
        }
        return x;
    }

    template <std::integral T>
        requires(!std::is_same_v<std::remove_cvref_t<T>, bool>)
    T read(int r) {
        using namespace detail;
        if (r == std::numeric_limits<T>::digits + (std::numeric_limits<T>::is_signed ? 1 : 0)) return read<T>();
        assert(r >= 1 && r <= std::numeric_limits<T>::digits + (std::numeric_limits<T>::is_signed ? 1 : 0));
        T x = 0;
        for (int i = 0; i < r; ++i) {
            x <<= 1;
            x |= readBit();
        }
        return x;
    }

    template <typename T>
        requires std::is_same_v<std::remove_cvref_t<T>, std::string>
    T read() {
        std::string s;
        while (!isEmpty()) s += read<char>();
        return s;
    }

    inline void close() {
        using namespace detail;
        n_ = 0;
        buffer_ = std::byte();
    }
}  // namespace BinaryStdIn
}  // namespace algs4

#endif  // ALGS4_BINARYSTDIN_HPP
