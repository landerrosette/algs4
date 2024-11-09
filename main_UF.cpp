/******************************************************************************
 *  % ./UF < tinyUF.txt
 *  4 3
 *  3 8
 *  6 5
 *  9 4
 *  2 1
 *  5 0
 *  7 2
 *  6 1
 *  2 components
 *
 ******************************************************************************/


#include <iostream>
#include "UF.h"

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    UF uf(N);
    for (int p, q; std::cin >> p >> q;) {
        if (uf.connected(p, q)) continue;
        uf.unionize(p, q);
        std::cout << p << " " << q << std::endl;
    }
    std::cout << uf.count() << " components" << std::endl;
    return 0;
}
