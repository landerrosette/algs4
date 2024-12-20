#include "BinaryStdIO.h"
#include <iostream>

void BinaryStdIO::writeBit(std::byte bit) {
    outBuffer = (outBuffer << 1) | bit; // Add bit to buffer.
    if (++outN == 8) {
        // If buffer is full (8 bits), write out as a single byte.
        std::cout.put(std::to_integer<char>(outBuffer));
        outBuffer = std::byte();
        outN = 0;
    }
}

void BinaryStdIO::writeByte(std::byte byte) {
    if (outN == 0) {
        // optimized if byte-aligned
        std::cout.put(std::to_integer<char>(byte));
        return;
    }
    for (int i = 0; i < 8; ++i) writeBit(byte >> (8 - i - 1) & std::byte{1}); // Otherwise write one bit at a time.
}

void BinaryStdIO::fillInBuffer() {
    inBuffer = static_cast<std::byte>(std::cin.get());
    if (std::cin.eof()) inN = -1;
    else if (inN == 0) inN = 8;
}

void BinaryStdIO::write(int x) {
    for (int i = 0; i < sizeof(int); ++i)
        writeByte(static_cast<std::byte>(x >> (sizeof(int) - i - 1) * 8 & 0xFF));
}

void BinaryStdIO::write(int x, int r) {
    if (r == sizeof(int)) {
        write(x);
        return;
    }
    for (int i = 0; i < r; ++i)
        writeBit(static_cast<std::byte>(x >> (r - i - 1) & 1));
}

void BinaryStdIO::write(const std::string &s) {
    for (int i = 0; i < s.length(); ++i) write(s[i]);
}

bool BinaryStdIO::readBool() {
    if (inN == 0) fillInBuffer();
    bool bit = std::to_integer<bool>((inBuffer >> --inN) & std::byte{1});
    if (inN == 0) fillInBuffer();
    return bit;
}

char BinaryStdIO::readChar() {
    if (inN == 0) fillInBuffer();
    auto x = inBuffer;
    if (inN == 8) fillInBuffer(); // special case when aligned byte
    else {
        // Combine last n bits of current buffer with first 8-n bits of new buffer.
        x <<= 8 - inN;
        fillInBuffer();
        x |= inBuffer >> inN;
    }
    return std::to_integer<char>(x);
}

int BinaryStdIO::readInt() {
    int x = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        x <<= 8;
        x |= readChar() & 0xFF;
    }
    return x;
}

int BinaryStdIO::readInt(int r) {
    if (r == sizeof(int)) readInt();
    int x = 0;
    for (int i = 0; i < r; ++i) {
        x <<= 1;
        x |= readBool();
    }
    return x;
}

std::string BinaryStdIO::readString() {
    std::string s;
    while (!isEmpty()) s += readChar();
    return s;
}

void BinaryStdIO::closeOut() {
    if (outN > 0) {
        outBuffer <<= 8 - outN; // Pad 0s if number of bits written so far is not a multiple of 8.
        std::cout.put(std::to_integer<char>(outBuffer));
    }
    outN = 0;
    outBuffer = std::byte();
}

void BinaryStdIO::closeIn() {
    inN = 0;
    inBuffer = std::byte();
}
