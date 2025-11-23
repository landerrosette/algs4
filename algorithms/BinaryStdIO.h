#ifndef ALGS4_BINARYSTDIO_H
#define ALGS4_BINARYSTDIO_H


#include <cstddef>
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


#endif //ALGS4_BINARYSTDIO_H
