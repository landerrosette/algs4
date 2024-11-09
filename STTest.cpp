#include "STTest.h"
#include <random>

namespace STTest {
    void init(ST<std::string, int> &st, std::istream &is, std::ostream &os) {
        std::string word;
        for (int i = 0; is >> word; ++i) st.put(word, i);
        os << "size = " << st.size() << std::endl;
    }

    void listAll(ST<std::string, int> &st, std::ostream &os) {
        // print keys using keys()
        for (const auto &s: st.keys()) {
            os << s << " " << st.get(s).value_or(INVALID_VALUE) << std::endl;
        }
    }

    void removeSome(ST<std::string, int> &st, std::ostream &os) {
        // remove some randomly selected keys
        std::mt19937 g(std::random_device{}());
        for (const auto &s: st.keys()) {
            if (std::bernoulli_distribution(0.5)(g)) st.remove(s);
        }
        os << "After removing some randomly selected keys, size = " << st.size() << ":" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    void removeAll(ST<std::string, int> &st, std::ostream &os) {
        // remove all the remaining keys
        for (const auto &s: st.keys()) {
            st.remove(s);
        }
        os << "After removing the remaining keys, size = " << st.size() << ":" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    void testKeys(ST<std::string, int> &st, std::ostream &os) {
        os << "Testing keys():" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }
}
