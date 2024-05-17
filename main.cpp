#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include "Sorting.h"
#include "Selection.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"
#include "MergeBU.h"
#include "Quick.h"
#include "Quick3way.h"

int main(int argc, char *argv[]) {
    std::ifstream file(argv[1]);
    std::vector<std::string> a;
    std::string word;
    while (file >> word) a.push_back(word);
    file.close();

    Sorting::show(a);
//    Selection::sort(a);
//    Insertion::sort(a);
//    Shell::sort(a);
//    Merge::sort(a);
//    MergeBU::sort(a);
//    Quick::sort(a);
    Quick3way::sort(a);
    assert(Sorting::isSorted(a));
    Sorting::show(a);

    return 0;
}
