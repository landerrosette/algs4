#include "UF.h"

UF::UF(int N) : id(N), sz(N), count_(N) {
    for (int i = 0; i < N; i++) {
        id[i] = i;
        sz[i] = 1;
    }
}

int UF::find(int p) const {
    while (p != id[p]) p = id[p];
    return p;
}

void UF::unionize(int p, int q) {
    int i = find(p);
    int j = find(q);
    if (i == j) return;
    if (sz[i] < sz[j]) {
        id[i] = j;
        sz[j] += sz[i];
    } else {
        id[j] = i;
        sz[i] += sz[j];
    }
    --count_;
}
