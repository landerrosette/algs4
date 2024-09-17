#include "testUF.h"
#include "UF.h"
#include <iostream>

void testUF() {
    UF uf([]() {
        int N;
        return std::cin >> N, N;
    }());
    for (int p, q; std::cin >> p >> q;) {
        if (uf.connected(p, q)) continue;
        uf.unionize(p, q);
        std::cout << p << " " << q << "\n";
    }
    std::cout << uf.count() << " components" << "\n";
}
