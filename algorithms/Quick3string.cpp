#include "Quick3string.h"

void Quick3string::sort(std::vector<std::string> &a, int lo, int hi, int d) {
    if (lo >= hi) return;
    int lt = lo, i = lo + 1, gt = hi;
    char v = a[lo][d];
    while (i <= gt) {
        char t = a[i][d];
        if (t < v) exch(a, lt++, i++);
        else if (t > v) exch(a, gt--, i);
        else i++;
    } // a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi]
    sort(a, lo, lt - 1, d);
    if (v > 0) sort(a, lt, gt, d + 1);
    sort(a, gt + 1, hi, d);
}
