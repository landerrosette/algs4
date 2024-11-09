#include "OrderedSTTest.h"
#include "STTest.h"
#include <iomanip>

namespace STTest {
    void init(OrderedST<std::string, int> &st, std::istream &is, std::ostream &os) {
        init(static_cast<ST<std::string, int> &>(st), is, os);
        os << "min  = " << st.min().value_or(INVALID_KEY) << std::endl;
        os << "max  = " << st.max().value_or(INVALID_KEY) << std::endl;
    }

    void removeSome(OrderedST<std::string, int> &st, std::ostream &os) {
        // remove the smallest keys
        for (int i = 0; i < st.size() / 2; ++i) {
            st.removeMin();
        }
        os << "After removing the smallest " << st.size() / 2 << " keys, size = " << st.size() << ":" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    void removeAll(OrderedST<std::string, int> &st, std::ostream &os) {
        // remove all the remaining keys
        while (!st.isEmpty()) {
            st.remove(st.select(st.size() / 2).value_or(INVALID_KEY));
        }
        std::cout << "After removing the remaining keys, size = " << st.size() << ":" << std::endl;
        os << "--------------------------------" << std::endl;
        listAll(st, os);
    }

    void testOrderedST(OrderedST<std::string, int> &st, std::ostream &os) {
        // print keys in order using select
        os << "Testing select:" << std::endl;
        os << "--------------------------------" << std::endl;
        for (int i = 0; i < st.size(); ++i) {
            os << i << " " << st.select(i).value_or(INVALID_KEY) << std::endl;
        }
        os << std::endl;

        // test rank, floor, ceiling
        os << "key rank floor ceil" << std::endl;
        os << "-------------------" << std::endl;
        for (char i = 'A'; i <= 'Z'; ++i) {
            std::string s(1, i);
            os << std::setw(2) << s << " "
                    << std::setw(4) << st.rank(s) << " "
                    << std::setw(4) << st.floor(s).value_or(INVALID_KEY) << " "
                    << std::setw(4) << st.ceiling(s).value_or(INVALID_KEY) << std::endl;
        }
        os << std::endl;

        // test range search and range count
        std::vector<std::string> from = {"A", "Z", "X", "0", "B", "C"};
        std::vector<std::string> to = {"Z", "A", "X", "Z", "G", "L"};
        os << "range search" << std::endl;
        os << "-------------------" << std::endl;
        for (int i = 0; i < from.size(); ++i) {
            os << from[i] << "-" << to[i] << " (" << std::setw(2) << st.size(from[i], to[i]) << ") : ";
            for (const auto &s: st.keys(from[i], to[i])) {
                os << s << " ";
            }
            os << std::endl;
        }
    }
}
