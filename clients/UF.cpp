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


#include "algs4/UF.hpp"

#include <iostream>

int main(int argc, char *argv[]) {
    int N;
    std::cin >> N;
    if (N < 0) {
        std::cerr << "Number of sites must be nonnegative" << std::endl;
        return 1;
    }
    algs4::UF uf(N);
    for (int p, q; std::cin >> p >> q;) {
        if (p < 0 || p >= N || q < 0 || q >= N) {
            std::cerr << "Index out of bounds" << std::endl;
            return 1;
        }
        if (uf.connected(p, q)) continue;
        uf.unionize(p, q);
        std::cout << p << " " << q << std::endl;
    }
    std::cout << uf.count() << " components" << std::endl;
    return 0;
}
