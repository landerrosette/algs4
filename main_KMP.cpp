#include <iostream>
#include <string>
#include "KMP.h"

int main(int argc, char *argv[]) {
    std::string pat = argv[1], txt = argv[2];
    KMP kmp(pat);
    std::cout << "text:    " << txt << std::endl;
    int offset = kmp.search(txt);
    std::cout << "pattern: ";
    for (int i = 0; i < offset; ++i) std::cout << " ";
    std::cout << pat << std::endl;
}
