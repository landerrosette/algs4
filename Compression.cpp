#include "Compression.h"
#include <iostream>

void Compression::writeBit(std::byte bit) {
    writeBuffer = (writeBuffer << 1) | bit; // add bit to buffer
    if (++writeN == 8) {
        // if buffer is full (8 bits), write out as a single byte
        std::cout.put(std::to_integer<char>(writeBuffer));
        writeBuffer = std::byte();
        writeN = 0;
    }
}

void Compression::writeByte(std::byte byte) {
    if (writeN == 0) {
        // optimized if byte-aligned
        std::cout.put(std::to_integer<char>(byte));
        return;
    }
    for (int i = 0; i < 8; ++i) writeBit((byte >> (8 - i - 1)) & std::byte{1}); // otherwise write one bit at a time
}

void Compression::write(int x) {
    for (int i = 0; i < sizeof(int); ++i)
        writeByte(static_cast<std::byte>(x >> ((sizeof(int) - i - 1) * 8) & 0xFF));
}

bool Compression::readBool() {
    if (readN == 0) {
        readBuffer = static_cast<std::byte>(std::cin.get());
        readN = !std::cin.eof() ? 8 : -1;
    }
    return std::to_integer<bool>((readBuffer >> --readN) & std::byte{1});
}

char Compression::readChar() {
    if (readN == 0) {
        readBuffer = static_cast<std::byte>(std::cin.get());
        readN = !std::cin.eof() ? 8 : -1;
    }
    if (readN == 8) {
        // special case when aligned byte
        readN = 0;
        return std::to_integer<char>(readBuffer);
    } else {
        // otherwise combine last n bits of current buffer with first 8-n bits of new buffer
        auto x = readBuffer;
        x <<= 8 - readN;
        readBuffer = static_cast<std::byte>(std::cin.get());
        if (std::cin.eof()) readN = -1;
        else x |= readBuffer >> readN;
        return std::to_integer<char>(x);
    }
}

int Compression::readInt() {
    int x = 0;
    for (int i = 0; i < sizeof(int); ++i) {
        x <<= 8;
        x |= readChar() & 0xFF;
    }
    return x;
}

std::string Compression::readString() {
    std::string s;
    do {
        char c = readChar();
        if (readN >= 0) s += c;
    } while (readN >= 0);
    return s;
}

void Compression::closeWrite() {
    if (writeN > 0) {
        writeBuffer <<= 8 - writeN; // pad 0s if number of bits written so far is not a multiple of 8
        std::cout.put(std::to_integer<char>(writeBuffer));
        writeN = 0;
    }
    writeBuffer = std::byte();
}

void Compression::closeRead() {
    readN = 0;
    readBuffer = std::byte();
}
