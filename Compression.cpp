#include "Compression.h"
#include <iostream>

void Compression::writeBit(bool bit) {
    writeBuffer = (writeBuffer << 1) | bit; // add bit to buffer
    if (++writeN == 8) {
        // if buffer is full (8 bits), write out as a single byte
        std::cout.put(writeBuffer);
        writeBuffer = 0;
        writeN = 0;
    }
}

void Compression::write(char x) {
    if (writeN == 0) {
        // optimized if byte-aligned
        std::cout.put(x);
        return;
    }
    for (int i = 0; i < 8; ++i) writeBit((x >> (8 - i - 1)) & 1); // otherwise write one bit at a time
}

bool Compression::readBool() {
    if (readN == 0) {
        readBuffer = std::cin.get();
        readN = !std::cin.eof() ? 8 : -1;
    }
    return (readBuffer >> --readN) & 1;
}

char Compression::readChar() {
    if (readN == 0) {
        readBuffer = std::cin.get();
        readN = !std::cin.eof() ? 8 : -1;
    }
    if (readN == 8) {
        // special case when aligned byte
        readN = 0;
        return readBuffer;
    } else {
        // otherwise combine last n bits of current buffer with first 8-n bits of new buffer
        unsigned char x = readBuffer;
        x <<= 8 - readN;
        readBuffer = std::cin.get();
        if (std::cin.eof()) readN = -1;
        else x |= readBuffer >> readN;
        return x;
    }
}

std::string Compression::readString() {
    std::string s;
    while (true) {
        char c = readChar();
        if (readN >= 0) s += c;
        else break;
    }
    return s;
}

void Compression::closeWrite() {
    if (writeN > 0) {
        writeBuffer <<= 8 - writeN; // pad 0s if number of bits written so far is not a multiple of 8
        std::cout.put(writeBuffer);
        writeN = 0;
    }
    writeBuffer = 0;
}

void Compression::closeRead() {
    readN = 0;
    readBuffer = 0;
}
