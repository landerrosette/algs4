#ifndef COMPRESSION_H
#define COMPRESSION_H


#include <string>

class Compression {
private:
    inline static unsigned char writeBuffer = 0;
    inline static int writeN = 0;
    inline static unsigned char readBuffer = 0;
    inline static int readN = 0;

    static void writeBit(bool bit);

protected:
    static void write(bool x) { writeBit(x); }

    static void write(char x);

    static bool readBool();

    static char readChar();

    static std::string readString();

    static void closeWrite();

    static void closeRead();
};


#endif //COMPRESSION_H
