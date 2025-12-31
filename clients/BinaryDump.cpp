#include <iostream>
#include <string>

#include "algs4/BinaryStdIO.hpp"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Not enough arguments" << std::endl;
        return 1;
    }
    int width = std::stoi(argv[1]);
    if (width < 0) {
        std::cerr << "Width must be nonnegative" << std::endl;
        return 1;
    }
    int cnt;
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
