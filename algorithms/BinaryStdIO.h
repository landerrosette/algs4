#ifndef ALGS4_BINARYSTDIO_H
#define ALGS4_BINARYSTDIO_H


#include <cstddef>
#include <iostream>
#include <string>

namespace algs4 {
    namespace BinaryStdIO {
        namespace internal {
            inline std::byte outBuffer;
            inline int outN = 0;
            inline std::byte inBuffer;
            inline int inN = 0;

            void writeBit(std::byte bit);
            void writeByte(std::byte byte);
            void fillInBuffer();
        }

        inline void write(bool x) { internal::writeBit(static_cast<std::byte>(x)); }
        inline void write(char x) { internal::writeByte(static_cast<std::byte>(x)); }
        void write(int x);
        void write(int x, int r);
        void write(const std::string &s);
        bool readBool();
        char readChar();
        int readInt();
        int readInt(int r);
        std::string readString();
        inline bool isEmpty() { return internal::inN < 0; }
        void closeOut();
        void closeIn();
    }
}

inline void algs4::BinaryStdIO::internal::writeBit(std::byte bit) {
    outBuffer = (outBuffer << 1) | bit; // Add bit to buffer.
    if (++outN == 8) {
        std::cout.put(std::to_integer<char>(outBuffer));
        outBuffer = std::byte();
        outN = 0;
    } // If buffer is full (8 bits), write out as a single byte.
}

inline void algs4::BinaryStdIO::internal::writeByte(std::byte byte) {
    if (outN == 0) {
        std::cout.put(std::to_integer<char>(byte));
        return;
    } // optimized if byte-aligned
    for (int i = 0; i < 8; ++i)
        writeBit(byte >> (8 - i - 1) & std::byte{1}); // Otherwise write one bit at a time.
}

inline void algs4::BinaryStdIO::internal::fillInBuffer() {
    inBuffer = static_cast<std::byte>(std::cin.get());
    if (std::cin.eof()) inN = -1;
    else if (inN == 0) inN = 8;
}

inline void algs4::BinaryStdIO::write(int x) {
    for (int i = 0; i < sizeof(int); ++i)
        internal::writeByte(static_cast<std::byte>(x >> (sizeof(int) - i - 1) * 8 & 0xFF));
}

inline void algs4::BinaryStdIO::write(int x, int r) {
    if (r == sizeof(int)) {
        write(x);
        return;
    }
    for (int i = 0; i < r; ++i)
        internal::writeBit(static_cast<std::byte>(x >> (r - i - 1) & 1));
}

inline void algs4::BinaryStdIO::write(const std::string &s) {
    for (int i = 0; i < s.length(); ++i)
        write(s[i]);
}

inline bool algs4::BinaryStdIO::readBool() {
    using namespace internal;
    if (inN == 0) fillInBuffer();
    bool bit = std::to_integer<bool>((inBuffer >> --inN) & std::byte{1});
    if (inN == 0) fillInBuffer();
    return bit;
}

inline char algs4::BinaryStdIO::readChar() {
    using namespace internal;
    if (inN == 0) fillInBuffer();
    auto x = inBuffer;
    if (inN == 8) fillInBuffer(); // special case when aligned byte
    else {
        x <<= 8 - inN;
        fillInBuffer();
        x |= inBuffer >> inN;
    } // Combine last n bits of current buffer with first 8-n bits of new buffer.
    return std::to_integer<char>(x);
}

inline int algs4::BinaryStdIO::readInt() {
    int x = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        x <<= 8;
        x |= readChar() & 0xFF;
    }
    return x;
}

inline int algs4::BinaryStdIO::readInt(int r) {
    if (r == sizeof(int)) readInt();
    int x = 0;
    for (int i = 0; i < r; ++i) {
        x <<= 1;
        x |= readBool();
    }
    return x;
}

inline std::string algs4::BinaryStdIO::readString() {
    std::string s;
    while (!isEmpty()) s += readChar();
    return s;
}

inline void algs4::BinaryStdIO::closeOut() {
    using namespace internal;
    if (outN > 0) {
        outBuffer <<= 8 - outN; // Pad 0s if number of bits written so far is not a multiple of 8.
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


#endif //ALGS4_BINARYSTDIO_H
