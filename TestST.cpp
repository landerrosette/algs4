#include "TestST.h"
#include <random>

namespace TestST {
    void init(ST<std::string, int> &st, std::istream &is, std::ostream &os) {
        std::string word;
        for (int i = 0; is >> word; ++i) st.put(word, i);
        os << "size = " << st.size() << std::endl;
    }

    void listAll(const ST<std::string, int> &st, std::ostream &os) {
        // Print keys using keys().
        for (const auto &s: st.keys()) {
            os << s << " " << st.get(s).value_or(INVALID_VALUE) << std::endl;
        }
    }

    void removeSome(ST<std::string, int> &st, std::ostream &os) {
        // Remove some randomly selected keys.
        std::default_random_engine e(std::random_device{}());
        std::bernoulli_distribution b;
        for (const auto &s: st.keys()) {
            if (b(e)) st.remove(s);
        }
        os << "After removing some randomly selected keys, size = " << st.size() << ":" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    void removeAll(ST<std::string, int> &st, std::ostream &os) {
        // Remove all the remaining keys.
        for (const auto &s: st.keys()) {
            st.remove(s);
        }
        os << "After removing the remaining keys, size = " << st.size() << ":" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    void testKeys(const ST<std::string, int> &st, std::ostream &os) {
        os << "Testing keys():" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }
}
