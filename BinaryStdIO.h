#ifndef BINARYSTDIO_H
#define BINARYSTDIO_H


#include <string>
#include <cstddef>

class BinaryStdIO {
private:
    inline static std::byte outBuffer;
    inline static int outN = 0;
    inline static std::byte inBuffer;
    inline static int inN = 0;

    static void writeBit(std::byte bit);

    static void writeByte(std::byte byte);

    static void fillInBuffer();

public:
    static void write(bool x) { writeBit(static_cast<std::byte>(x)); }

    static void write(char x) { writeByte(static_cast<std::byte>(x)); }

    static void write(int x);

    static bool readBool();

    static char readChar();

    static int readInt();

    static std::string readString();

    static bool isEmpty() { return inN < 0; }

    static void closeOut();

    static void closeIn();
};


#endif //BINARYSTDIO_H
