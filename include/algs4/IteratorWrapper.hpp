/*
 * Copyright (C) 2026 landerrosette
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ALGS4_ITERATORWRAPPER_HPP
#define ALGS4_ITERATORWRAPPER_HPP

#include <iterator>
#include <type_traits>

namespace algs4 {
    namespace internal {
        template<typename Container, bool Reverse, bool Const>
        class IteratorWrapper;

        template<typename Container, bool Reverse, bool Const>
        constexpr bool operator==(const IteratorWrapper<Container, Reverse, Const> &l,
                                  const IteratorWrapper<Container, Reverse, Const> &r);

        template<typename Container, bool Reverse, bool Const>
        class IteratorWrapper {
            friend class IteratorWrapper<Container, Reverse, !Const>;
            friend constexpr bool operator==<>(const IteratorWrapper &l, const IteratorWrapper &r);

        private:
            using underlying_iterator = std::conditional_t<Reverse,
                std::conditional_t<Const,
                    typename Container::const_reverse_iterator, typename Container::reverse_iterator>,
                std::conditional_t<Const,
                    typename Container::const_iterator, typename Container::iterator> >;
            underlying_iterator it_;

        public:
            using difference_type = Container::difference_type;
            using value_type = Container::value_type;
            using pointer = std::conditional_t<Const, const value_type *, value_type *>;
            using reference = std::conditional_t<Const, const value_type &, value_type &>;
            using iterator_category = std::forward_iterator_tag;

            constexpr explicit IteratorWrapper(underlying_iterator it) : it_(it) {}

            template<bool OtherConst, typename = std::enable_if_t<Const && !OtherConst> >
            constexpr IteratorWrapper(const IteratorWrapper<Container, Reverse, OtherConst> &other) : it_(other.it_) {}

            constexpr reference operator*() const { return *it_; }
            constexpr pointer operator->() const { return &*it_; }
            constexpr IteratorWrapper &operator++();
            constexpr IteratorWrapper operator++(int);
        };
    }
}

template<typename Container, bool Reverse, bool Const>
constexpr bool algs4::internal::operator==(const IteratorWrapper<Container, Reverse, Const> &l,
                                           const IteratorWrapper<Container, Reverse, Const> &r) {
    return l.it_ == r.it_;
}

template<typename Container, bool Reverse, bool Const>
constexpr auto algs4::internal::IteratorWrapper<Container, Reverse, Const>::operator++() -> IteratorWrapper & {
    ++it_;
    return *this;
}

template<typename Container, bool Reverse, bool Const>
constexpr auto algs4::internal::IteratorWrapper<Container, Reverse, Const>::operator++(int) -> IteratorWrapper {
    IteratorWrapper t = *this;
    ++*this;
    return t;
}

#endif // ALGS4_ITERATORWRAPPER_HPP
