#include "testUF.h"
#include "UF.h"

void testUF(std::istream &&data) {
    UF uf([&data]() {
        int N;
        return data >> N, N;
    }());
    for (int p, q; data >> p >> q;) {
        if (uf.connected(p, q)) continue;
        uf.unionize(p, q);
        std::cout << p << " " << q << "\n";
    }
    std::cout << uf.count() << " components" << "\n";
}
