#include "OrderedSTTestUtils.hpp"

#include <array>
#include <iomanip>
#include <istream>
#include <ostream>

#include "STTestUtils.hpp"

namespace STTestUtils {
    void init(algs4::OrderedST<std::string, int> &st, std::istream &is, std::ostream &os) {
        init(static_cast<algs4::ST<std::string, int> &>(st), is, os);
        const auto *min = st.min(), *max = st.max();
        os << "min  = " << (min ? *min : INVALID_KEY) << std::endl;
        os << "max  = " << (max ? *max : INVALID_KEY) << std::endl;
    }

    // Remove the smallest keys.
    void removeSome(algs4::OrderedST<std::string, int> &st, std::ostream &os) {
        auto N = st.size();
        for (int i = 0; i < N / 2; ++i)
            st.removeMin();
        os << "After removing the smallest " << N / 2 << " keys, size = " << st.size() << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    // Remove all the remaining keys.
    void removeAll(algs4::OrderedST<std::string, int> &st, std::ostream &os) {
        while (!st.isEmpty())
            st.remove(*st.select(st.size() / 2));
        os << "After removing the remaining keys, size = " << st.size() << std::endl;
    }

    void testOrderedST(const algs4::OrderedST<std::string, int> &st, std::ostream &os) {
        // Print keys in order using select.
        os << "Testing select" << std::endl;
        os << "--------------------------------" << std::endl;
        for (int i = 0; i < st.size(); ++i)
            os << i << " " << *st.select(i) << std::endl;
        os << std::endl;

        // Test rank, floor, ceiling.
        os << "key rank floor ceil" << std::endl;
        os << "-------------------" << std::endl;
        for (char i = 'A'; i <= 'Z'; ++i) {
            std::string s(1, i);
            const auto *floor = st.floor(s), *ceiling = st.ceiling(s);
            os << std::setw(2) << s << " "
                    << std::setw(4) << st.rank(s) << " "
                    << std::setw(4) << (floor ? *floor : INVALID_KEY) << " "
                    << std::setw(4) << (ceiling ? *ceiling : INVALID_KEY) << std::endl;
        }
        os << std::endl;

        // Test range search and range count.
        std::array<std::string, 6> from = {"A", "Z", "X", "0", "B", "C"};
        std::array<std::string, 6> to = {"Z", "A", "X", "Z", "G", "L"};
        os << "range search" << std::endl;
        os << "-------------------" << std::endl;
        for (int i = 0; i < std::ssize(from); ++i) {
            os << from[i] << "-" << to[i] << " (" << std::setw(2) << st.size(from[i], to[i]) << ") : ";
            for (const auto &s: st.keys(from[i], to[i]))
                os << s << " ";
            os << std::endl;
        }
    }
}
