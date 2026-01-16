#ifndef ALGS4_STRINGSORTUTILS_H
#define ALGS4_STRINGSORTUTILS_H

#include <cassert>
#include <cstddef>
#include <string>

namespace algs4 {
    namespace StringSortUtils {
        namespace internal {
            constexpr int charAt(const std::string &s, std::ptrdiff_t d);
        }
    }
}

constexpr int algs4::StringSortUtils::internal::charAt(const std::string &s, std::ptrdiff_t d) {
    assert(d >= 0 && d <= std::ssize(s));
    if (d == std::ssize(s)) return -1;
    return static_cast<unsigned char>(s[d]);
}

#endif // ALGS4_STRINGSORTUTILS_H
