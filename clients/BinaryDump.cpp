#include <iostream>
#include <string>

#include "BinaryStdIO.h"

int main(int argc, char *argv[]) {
    int width = std::stoi(argv[1]), cnt;
    for (cnt = 0; !algs4::BinaryStdIO::isEmpty(); ++cnt) {
        if (width == 0) {
            algs4::BinaryStdIO::readBool();
            continue;
        }
        if (cnt != 0 && cnt % width == 0) std::cout << std::endl;
        if (algs4::BinaryStdIO::readBool()) std::cout << "1";
        else std::cout << "0";
    }
    if (width != 0) std::cout << std::endl;
    std::cout << cnt << " bits" << std::endl;
    return 0;
}
