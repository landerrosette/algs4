#include "STTestUtils.h"

#include <random>

namespace STTestUtils {
    void init(algs4::ST<std::string, int> &st, std::istream &is, std::ostream &os) {
        std::string word;
        for (int i = 0; is >> word; ++i)
            st.put(word, i);
        os << "size = " << st.size() << std::endl;
    }

    // Print keys using keys().
    void listAll(const algs4::ST<std::string, int> &st, std::ostream &os) {
        for (const auto &s: st.keys())
            os << s << " " << st.get(s).value_or(INVALID_VALUE) << std::endl;
    }

    // Remove some randomly selected keys.
    void removeSome(algs4::ST<std::string, int> &st, std::ostream &os) {
        std::default_random_engine e(std::random_device{}());
        std::bernoulli_distribution b;
        int i = 0;
        for (const auto &s: st.keys()) {
            if (b(e)) {
                st.remove(s);
                ++i;
            }
        }
        os << "After removing " << i << " randomly selected keys, size = " << st.size() << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    // Remove all the remaining keys.
    void removeAll(algs4::ST<std::string, int> &st, std::ostream &os) {
        for (const auto &s: st.keys())
            st.remove(s);
        os << "After removing the remaining keys, size = " << st.size() << std::endl;
    }

    void testKeys(const algs4::ST<std::string, int> &st, std::ostream &os) {
        os << "Testing keys()" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }
}
