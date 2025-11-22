#include "TestStringST.h"

namespace TestST {
    void testStringST(const algs4::StringST<int> &st, std::ostream &os) {
        os << "longestPrefixOf(\"shellsort\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        os << st.longestPrefixOf("shellsort") << std::endl;
        os << std::endl;

        os << "longestPrefixOf(\"shell\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        os << st.longestPrefixOf("shell") << std::endl;
        os << std::endl;

        os << "keysWithPrefix(\"shor\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        for (const auto &s: st.keysWithPrefix("shor"))
            os << s << std::endl;
        os << std::endl;

        os << "keysThatMatch(\".he.l.\"):" << std::endl;
        os << "--------------------------------" << std::endl;
        for (const auto &s: st.keysThatMatch(".he.l."))
            os << s << std::endl;
    }
}
