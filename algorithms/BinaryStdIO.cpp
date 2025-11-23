#include "BinaryStdIO.h"

#include <iostream>

void algs4::BinaryStdIO::internal::writeBit(std::byte bit) {
    outBuffer = (outBuffer << 1) | bit; // Add bit to buffer.
    if (++outN == 8) {
        std::cout.put(std::to_integer<char>(outBuffer));
        outBuffer = std::byte();
        outN = 0;
    } // If buffer is full (8 bits), write out as a single byte.
}

void algs4::BinaryStdIO::internal::writeByte(std::byte byte) {
    if (outN == 0) {
        std::cout.put(std::to_integer<char>(byte));
        return;
    } // optimized if byte-aligned
    for (int i = 0; i < 8; ++i)
        writeBit(byte >> (8 - i - 1) & std::byte{1}); // Otherwise write one bit at a time.
}

void algs4::BinaryStdIO::internal::fillInBuffer() {
    inBuffer = static_cast<std::byte>(std::cin.get());
    if (std::cin.eof()) inN = -1;
    else if (inN == 0) inN = 8;
}

void algs4::BinaryStdIO::write(int x) {
    for (int i = 0; i < sizeof(int); ++i)
        internal::writeByte(static_cast<std::byte>(x >> (sizeof(int) - i - 1) * 8 & 0xFF));
}

void algs4::BinaryStdIO::write(int x, int r) {
    if (r == sizeof(int)) {
        write(x);
        return;
    }
    for (int i = 0; i < r; ++i)
        internal::writeBit(static_cast<std::byte>(x >> (r - i - 1) & 1));
}

void algs4::BinaryStdIO::write(const std::string &s) {
    for (int i = 0; i < s.length(); ++i)
        write(s[i]);
}

bool algs4::BinaryStdIO::readBool() {
    using namespace internal;
    if (inN == 0) fillInBuffer();
    bool bit = std::to_integer<bool>((inBuffer >> --inN) & std::byte{1});
    if (inN == 0) fillInBuffer();
    return bit;
}

char algs4::BinaryStdIO::readChar() {
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

int algs4::BinaryStdIO::readInt() {
    int x = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        x <<= 8;
        x |= readChar() & 0xFF;
    }
    return x;
}

int algs4::BinaryStdIO::readInt(int r) {
    if (r == sizeof(int)) readInt();
    int x = 0;
    for (int i = 0; i < r; ++i) {
        x <<= 1;
        x |= readBool();
    }
    return x;
}

std::string algs4::BinaryStdIO::readString() {
    std::string s;
    while (!isEmpty()) s += readChar();
    return s;
}

void algs4::BinaryStdIO::closeOut() {
    using namespace internal;
    if (outN > 0) {
        outBuffer <<= 8 - outN; // Pad 0s if number of bits written so far is not a multiple of 8.
        std::cout.put(std::to_integer<char>(outBuffer));
    }
    outN = 0;
    outBuffer = std::byte();
}

void algs4::BinaryStdIO::closeIn() {
    using namespace internal;
    inN = 0;
    inBuffer = std::byte();
}
