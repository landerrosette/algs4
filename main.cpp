#include <iostream>
#include <cassert>
#include "Sorting.h"
#include "Selection.h"
#include "Insertion.h"
#include "Shell.h"
#include "Merge.h"

int main() {
    std::vector<char> a = {'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    Sorting::show(a);
//    Selection::sort(a);
//    Insertion::sort(a);
//    Shell::sort(a);
    Merge::sort(a);
    assert(Sorting::isSorted(a));
    Sorting::show(a);
    return 0;
}
