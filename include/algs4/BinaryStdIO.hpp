/*
 * Copyright (C) 2024-2026 landerrosette <57791410+landerrosette@users.noreply.github.com>
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

#ifndef ALGS4_BINARYSTDIO_HPP
#define ALGS4_BINARYSTDIO_HPP

#include <cassert>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

namespace algs4 {
    namespace BinaryStdIO {
        namespace detail {
            inline std::byte outBuffer_;
            inline int outN_ = 0;
            inline std::byte inBuffer_;
            inline int inN_ = 0;

            void writeBit(bool bit);
            void writeByte(std::byte byte);

            void fillInBuffer();
            bool readBit();
            std::byte readByte();
        }

        inline void write(bool x) { detail::writeBit(x); }

        template<std::integral T>
        void write(T x);

        template<std::integral T> requires (!std::is_same_v<std::remove_cvref_t<T>, bool>)
        void write(T x, int r);

        inline void write(const std::string &x) { for (char c: x) write(c); }

        inline bool isEmpty() { return detail::inN_ < 0; }

        template<typename T> requires std::is_same_v<std::remove_cvref_t<T>, bool>
        T read() { return detail::readBit(); }

        template<std::integral T> requires (!std::is_same_v<std::remove_cvref_t<T>, bool> && sizeof(T) == 1)
        T read() { return std::to_integer<T>(detail::readByte()); }

        template<std::integral T> requires (sizeof(T) > 1)
        T read();

        template<std::integral T> requires (!std::is_same_v<std::remove_cvref_t<T>, bool>)
        T read(int r);

        template<typename T> requires std::is_same_v<std::remove_cvref_t<T>, std::string>
        T read();

        void closeOut();
        void closeIn();
    }
}

inline void algs4::BinaryStdIO::detail::writeBit(bool bit) {
    // Add bit to buffer.
    outBuffer_ <<= 1;
    if (bit) outBuffer_ |= std::byte{1};

    // If buffer is full (8 bits), write out as a single byte.
    if (++outN_ == std::numeric_limits<unsigned char>::digits) {
        std::cout.put(std::to_integer<char>(outBuffer_));
        outBuffer_ = std::byte();
        outN_ = 0;
    }
}

inline void algs4::BinaryStdIO::detail::writeByte(std::byte byte) {
    // optimized if byte-aligned
    if (outN_ == 0) {
        std::cout.put(std::to_integer<char>(byte));
        return;
    }

    // Otherwise write one bit at a time.
    for (int i = std::numeric_limits<unsigned char>::digits - 1; i >= 0; --i) {
        bool bit = ((byte >> i) & std::byte{1}) == std::byte{1};
        writeBit(bit);
    }
}

inline void algs4::BinaryStdIO::detail::fillInBuffer() {
    auto c = std::cin.get();
    if (c == std::char_traits<char>::eof()) {
        inN_ = -1;
        return;
    }
    inBuffer_ = static_cast<std::byte>(c);
    if (inN_ == 0) inN_ = std::numeric_limits<unsigned char>::digits;
}

inline bool algs4::BinaryStdIO::detail::readBit() {
    assert(!isEmpty());
    if (inN_ == 0) fillInBuffer();
    bool bit = ((inBuffer_ >> --inN_) & std::byte{1}) == std::byte{1};
    if (inN_ == 0) fillInBuffer();
    return bit;
}

inline std::byte algs4::BinaryStdIO::detail::readByte() {
    assert(!isEmpty());
    if (inN_ == 0) fillInBuffer();
    auto x = inBuffer_;
    if (inN_ == std::numeric_limits<unsigned char>::digits) fillInBuffer(); // special case when aligned byte
    else {
        // Combine last n bits of current buffer with first 8-n bits of new buffer.
        x <<= std::numeric_limits<unsigned char>::digits - inN_;
        fillInBuffer();
        x |= inBuffer_ >> inN_;
    }
    return x;
}

template<std::integral T>
void algs4::BinaryStdIO::write(T x) {
    using namespace detail;
    for (int i = sizeof(T) - 1; i >= 0; --i)
        writeByte(static_cast<std::byte>((x >> i * std::numeric_limits<unsigned char>::digits) & 0xFF));
}

template<std::integral T> requires (!std::is_same_v<std::remove_cvref_t<T>, bool>)
void algs4::BinaryStdIO::write(T x, int r) {
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

template<std::integral T> requires (sizeof(T) > 1)
T algs4::BinaryStdIO::read() {
    using namespace detail;
    T x = 0;
    for (int i = 0; i < sizeof(T); ++i) {
        x <<= std::numeric_limits<unsigned char>::digits;
        x |= std::to_integer<unsigned char>(readByte());
    }
    return x;
}

template<std::integral T> requires (!std::is_same_v<std::remove_cvref_t<T>, bool>)
T algs4::BinaryStdIO::read(int r) {
    using namespace detail;
    if (r == std::numeric_limits<T>::digits + (std::numeric_limits<T>::is_signed ? 1 : 0))
        return read<T>();
    assert(r >= 1 && r <= std::numeric_limits<T>::digits + (std::numeric_limits<T>::is_signed ? 1 : 0));
    T x = 0;
    for (int i = 0; i < r; ++i) {
        x <<= 1;
        x |= readBit();
    }
    return x;
}

template<typename T> requires std::is_same_v<std::remove_cvref_t<T>, std::string>
T algs4::BinaryStdIO::read() {
    std::string s;
    while (!isEmpty()) s += read<char>();
    return s;
}

inline void algs4::BinaryStdIO::closeOut() {
    using namespace detail;
    if (outN_ > 0) {
        // Pad 0s if number of bits written so far is not a multiple of 8.
        outBuffer_ <<= std::numeric_limits<unsigned char>::digits - outN_;
        std::cout.put(std::to_integer<char>(outBuffer_));
    }
    outN_ = 0;
    outBuffer_ = std::byte();
}

inline void algs4::BinaryStdIO::closeIn() {
    using namespace detail;
    inN_ = 0;
    inBuffer_ = std::byte();
}

#endif // ALGS4_BINARYSTDIO_HPP
