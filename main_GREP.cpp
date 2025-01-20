/******************************************************************************
 *  % more tinyL.txt
 *  AC
 *  AD
 *  AAA
 *  ABD
 *  ADD
 *  BCD
 *  ABCCBD
 *  BABAAA
 *  BABBAAA
 *
 *  % ./GREP "(A*B|AC)D" < tinyL.txt
 *  ABD
 *  ABCCBD
 *
 ******************************************************************************/


#include <iostream>
#include <string>

#include "NFA.h"

int main(int argc, char *argv[]) {
    std::string regexp = "(.*" + std::string(argv[1]) + ".*)";
    NFA nfa(regexp);
    for (std::string txt; std::getline(std::cin, txt);)
        if (nfa.recognizes(txt)) std::cout << txt << std::endl;
    return 0;
}
