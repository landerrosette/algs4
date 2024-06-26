#include "Quick3way.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>

int Quick3way::main() {
    std::vector<std::string> a;
    std::string word;
    while (std::cin >> word) a.push_back(word);

    show(a);
    sort(a);
    assert(isSorted(a));
    show(a);

    return 0;
}
