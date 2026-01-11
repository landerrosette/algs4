#include "BalancedTreeTestUtils.hpp"

#include <ostream>
#include <random>

void STTestUtils::testRedBlackBST(algs4::RedBlackBST<int, int> &st, int n, std::ostream &os) {
    // Insert N elements in order.
    os << "Inserting " << n << " elements in order" << std::endl;
    os << "--------------------------------" << std::endl;
    for (int i = 0; i < n; ++i) {
        st.put(i, i);
        os << "i = " << i << ", height = " << st.height() << ", size = " << st.size() << std::endl;
    }
    os << std::endl;

    // Delete keys in random order.
    os << "Deleting keys in random order" << std::endl;
    os << "--------------------------------" << std::endl;
    std::default_random_engine e(std::random_device{}());
    std::uniform_int_distribution u(0, n - 1);
    while (st.size() > 0) {
        if (int i = u(e); st.contains(i)) {
            st.remove(i);
            os << "i = " << i << ", height = " << st.height() << ", size = " << st.size() << std::endl;
        }
    }
    os << std::endl;

    os << "size = " << st.size() << std::endl;
}
