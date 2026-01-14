#ifndef ALGS4_BINARYSTDIO_HPP
#define ALGS4_BINARYSTDIO_HPP


#include <cassert>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>

namespace algs4 {
    namespace BinaryStdIO {
        namespace internal {
            inline std::byte outBuffer;
            inline int outN = 0;
            inline std::byte inBuffer;
            inline int inN = 0;

            void writeBit(bool bit);
            void writeByte(std::byte byte);

            void fillInBuffer();
            bool readBit();
            std::byte readByte();
        }

        inline void write(bool x) { internal::writeBit(x); }

        template<std::integral T>
        void write(T x);

        template<std::integral T> requires (!std::same_as<T, bool>)
        void write(T x, int r);

        inline void write(const std::string &x) { for (char c: x) write(c); }

        inline bool isEmpty() { return internal::inN < 0; }

        template<std::same_as<bool> T>
        T read() { return internal::readBit(); }

        template<std::integral T> requires (!std::same_as<T, bool> && sizeof(T) == 1)
        T read() { return std::to_integer<T>(internal::readByte()); }

        template<std::integral T> requires (sizeof(T) > 1)
        T read();

        template<std::integral T> requires (!std::same_as<T, bool>)
        T read(int r);

        template<std::same_as<std::string> T>
        T read();

        void closeOut();
        void closeIn();
    }
}

inline void algs4::BinaryStdIO::internal::writeBit(bool bit) {
    // Add bit to buffer.
    outBuffer <<= 1;
    if (bit) outBuffer |= std::byte{1};

    // If buffer is full (8 bits), write out as a single byte.
    if (++outN == std::numeric_limits<unsigned char>::digits) {
        std::cout.put(std::to_integer<char>(outBuffer));
        outBuffer = std::byte();
        outN = 0;
    }
}

inline void algs4::BinaryStdIO::internal::writeByte(std::byte byte) {
    // optimized if byte-aligned
    if (outN == 0) {
        std::cout.put(std::to_integer<char>(byte));
        return;
    }

    // Otherwise write one bit at a time.
    for (int i = std::numeric_limits<unsigned char>::digits - 1; i >= 0; --i) {
        bool bit = ((byte >> i) & std::byte{1}) == std::byte{1};
        writeBit(bit);
    }
}

inline void algs4::BinaryStdIO::internal::fillInBuffer() {
    auto c = std::cin.get();
    if (c == std::char_traits<char>::eof()) {
        inN = -1;
        return;
    }
    inBuffer = static_cast<std::byte>(c);
    if (inN == 0) inN = std::numeric_limits<unsigned char>::digits;
}

inline bool algs4::BinaryStdIO::internal::readBit() {
    assert(!isEmpty());
    if (inN == 0) fillInBuffer();
    bool bit = ((inBuffer >> --inN) & std::byte{1}) == std::byte{1};
    if (inN == 0) fillInBuffer();
    return bit;
}

inline std::byte algs4::BinaryStdIO::internal::readByte() {
    assert(!isEmpty());
    if (inN == 0) fillInBuffer();
    auto x = inBuffer;
    if (inN == std::numeric_limits<unsigned char>::digits) fillInBuffer(); // special case when aligned byte
    else {
        // Combine last n bits of current buffer with first 8-n bits of new buffer.
        x <<= std::numeric_limits<unsigned char>::digits - inN;
        fillInBuffer();
        x |= inBuffer >> inN;
    }
    return x;
}

template<std::integral T>
void algs4::BinaryStdIO::write(T x) {
    using namespace internal;
    for (int i = sizeof(T) - 1; i >= 0; --i)
        writeByte(static_cast<std::byte>((x >> i * std::numeric_limits<unsigned char>::digits) & 0xFF));
}

template<std::integral T> requires (!std::same_as<T, bool>)
void algs4::BinaryStdIO::write(T x, int r) {
    using namespace internal;
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
    using namespace internal;
    T x = 0;
    for (int i = 0; i < sizeof(T); ++i) {
        x <<= std::numeric_limits<unsigned char>::digits;
        x |= std::to_integer<unsigned char>(readByte());
    }
    return x;
}

template<std::integral T> requires (!std::same_as<T, bool>)
T algs4::BinaryStdIO::read(int r) {
    using namespace internal;
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

template<std::same_as<std::string> T>
T algs4::BinaryStdIO::read() {
    std::string s;
    while (!isEmpty()) s += read<char>();
    return s;
}

inline void algs4::BinaryStdIO::closeOut() {
    using namespace internal;
    if (outN > 0) {
        // Pad 0s if number of bits written so far is not a multiple of 8.
        outBuffer <<= std::numeric_limits<unsigned char>::digits - outN;
        std::cout.put(std::to_integer<char>(outBuffer));
    }
    outN = 0;
    outBuffer = std::byte();
}

inline void algs4::BinaryStdIO::closeIn() {
    using namespace internal;
    inN = 0;
    inBuffer = std::byte();
}


#endif //ALGS4_BINARYSTDIO_HPP
