#ifndef COMPRESSION_H
#define COMPRESSION_H


#include <string>
#include <cstddef>

class Compression {
private:
    inline static std::byte writeBuffer;
    inline static int writeN = 0;
    inline static std::byte readBuffer;
    inline static int readN = 0;

    static void writeBit(std::byte bit);

    static void writeByte(std::byte byte);

protected:
    static void write(bool x) { writeBit(static_cast<std::byte>(x)); }

    static void write(char x) { writeByte(static_cast<std::byte>(x)); }

    static void write(int x);

    static bool readBool();

    static char readChar();

    static int readInt();

    static std::string readString();

    static void closeWrite();

    static void closeRead();
};


#endif //COMPRESSION_H
